#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "LeetCode0.h"
#include "LeetCode1.h"
#include "LeetCode2.h"
#include "LeetCode3.h"
#include "LeetCode4.h"
#include "LeetCode6.h"
#include "LeetCode7.h"
#include "Test.h"
#include "Util.h"
#include <math.h>

using namespace std;
using namespace Test;
using namespace Test::LeetCode;

class LeetCodeTest : public TestClass
{
public:
    LeetCodeTest(Log &log) : TestClass(log) {}
    ~LeetCodeTest(void) {}
    void Init(void);
    void Init0(void);
    void Init1(void);
    void Init2(void);
    void Init3(void);
    void Init6(void);
    void Init7(void);
};

void LeetCodeTest::Init(void)
{
    Init0();
    Init1();
    Init2();
    Init3();
    Init6();
    Init7();

    Add("Find Pivot Index", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                Logger() << v;
                int i = pivotIndex(v);
                int i2 = pivotIndex2(v);
                Logger() << "pivotIndex: " << i << ", " << i2 << endl;
                ASSERT1(i == i2);
            };
            check({1, 7, 3, 6, 5, 6});
            check({1, 2, 3});
            check({1});
            check({1, -1});
            check({1, 1, -1});
            check({1, -1, -1});
            // check({-627, -39, -497, 501, -826, -791, -975, -94, 958, -750, 800, 564, -779, 395, 328, 755, 864, 6, -628, -217, -422, 706, -618, 640, 886, -91, -680, -135, -527, -398, -695, -597, 563, -635, 904, 294, -426, 486, -800, -912, 737, 1000, 209, 515, -49, -463, -173, -629, 100, -244, 155, 678, -538, 537, -125, 905, -998, 195, -231, -524, 354, -369, -121, -83, -4, -660, 768, 127, 826, 525, -228, 562, 525, 982, -366, -968});
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100, 1);
                // vector<int> v = Random::Vector(n, 1000, -1000);
                vector<int> v = Random::Vector(n, 100, 0);
                check(v);
            }
        });

    Add("Open the Lock", [&]()
        {
            auto check = [&](const vector<string> &deadends, const string &target)
            {
                Logger() << deadends;
                Logger() << "0000 => " << target << ": ";
                int c = openLock(deadends, target);
                int c2 = -1; // openLock2(deadends, target);
                Logger() << c << ", " << c2 << " steps" << endl;
            };
            // check({"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"}, "8888");
            check({"0201", "0101", "0102", "1212", "2002"}, "0202");
            check({"8888"}, "0009");
            check({"0000"}, "8888");
        });

    Add("Target Sum", [&]()
        {
            auto check = [&](const vector<int> &v, int t)
            {
                Logger() << v;
                Logger() << "target sum: " << t << endl;
                int c = findTargetSumWays(v, t);
                int c2 = findTargetSumWays2(v, t);
                int c3 = findTargetSumWays3(v, t);
                int c4 = findTargetSumWays4(v, t);
                Logger() << "Count ways: " << c << ", " << c2 << ", " << c3 << ", " << c4 << endl;
                ASSERT1(c == c2);
                ASSERT1(c == c3);
                ASSERT1(c == c4);
            };
            check({1, 1, 1, 1, 1}, 3);
            check({1, 0}, 1);
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(10, 1);
                vector<int> v = Random::Vector(n, 10);
                int t = Random::Int(100, -100);
                check(v, t);
            }
        });
}
#endif