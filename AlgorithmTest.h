#ifndef _ALGORITHMTEST_H_
#define _ALGORITHMTEST_H_

#include "Algorithm.h"
#include "Test.h"
#include "Util.h"
#include <limits.h>

using namespace Test;

class AlgorithmTest : public TestClass
{
public:
    AlgorithmTest(Log &log) : TestClass(log) {}
    ~AlgorithmTest(void) {}
    void Init(void);
};

void AlgorithmTest::Init(void)
{
    Add("BinarySearch", [&]() {
        auto check = [&](const vector<int> &v, int t) {
            Logger() << "Search " << t << " in " << v;
            int i = BinarySearch(v, t);
            int i2 = BinarySearch2(v, t);
            int i2_2 = BinarySearch2_2(v, t);
            int i3 = BinarySearch3(v, t);
            Logger() << "at " << i << ", " << i2 << ", " << i2_2 << ", " << i3
                     << endl;
            if (i == -1)
            {
                ASSERT1(i2 == -1);
                ASSERT1(i2_2 == -1);
                ASSERT1(i3 == -1);
            }
            else
            {
                ASSERT1(v[i] == t);
                ASSERT1(v[i2] == t);
                ASSERT1(v[i2_2] == t);
                ASSERT1(v[i3] == t);
            }
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100);
            vector<int> v = Random::Vector(n, 50);
            sort(v.begin(), v.end());
            check(v, -10);
            set<int> s;
            for (int e : v)
            {
                if (s.find(e) == s.end())
                {
                    check(v, e);
                    s.insert(e);
                }
            }
            check(v, 100);
        }
    });

    Add("FindClosest", [&]() {
        auto check = [&](const vector<int> &v, int t) {
            Logger() << "Search " << t << " in " << v;
            int i = FindClosest(v, t);
            int i2 = FindClosest2(v, t);
            Logger() << "at " << i << ", " << i2 << endl;
            if (i == -1)
                ASSERT1(i == i2);
            else
                ASSERT1(v[i] == v[i2]);
        };
        for (int i = 0; i < 100; i++)
        {
            int n = Random::Int(100);
            vector<int> v = Random::Vector(n, 5000, -5000);
            sort(v.begin(), v.end());
            for (int i = 0; i < 1000; i++)
            {
                int t = Random::Int(5000, -5000);
                check(v, t);
            }
        }
    });

    Add("KMP", [&]() {
        for (int i = 0; i < 50; i++)
        {
            Logger().WriteInformation("Run %d\n", i);
            string pattern = Random::String(1 + rand() % 10, string("abc"));
            string input = Random::String(1 + rand() % 1000, string("abc"));
            KMP kmp(pattern.c_str());
            kmp.Print();
            vector<int> indices =
                kmp.SearchString(input.c_str(), strlen(input.c_str()));
            printf("Pattern: %s\n", pattern.c_str());
            printf("Input: %s\n", input.c_str());
            for_each(indices.begin(), indices.end(), [&](int i) {
                printf("Found a match at index %d\n", i);
                ASSERT1(input.substr(i, pattern.size()) == pattern);
            });
        }
    });

    Add("Monge", [&]() {
        for (int i = 0; i < 10; i++)
        {
            int m = Random::Int(20, 2);
            int n = Random::Int(20, 2);
            int h = Random::Int(100);
            vector<vector<int>> grid = Monge::Random(m, n, h);
            vector<vector<int>> grid2 = Monge::Random2(m, n, h);
            bool r = Monge::IsMonge(grid);
            bool r2 = Monge::IsMonge(grid2);
            Logger() << grid << grid2;
            Logger() << "IsMonge = " << r << ", " << r2 << endl;
            ASSERT1(r);
            ASSERT1(r2);
        }
    });

    Add("RandomInt", [&]() {
        auto check = [&](int a, int b) {
            map<int, int> m;
            int n = 100 * (b - a + 1);
            for (int i = 0; i < n; i++)
            {
                int j = RandomInt(a, b);
                if (m.find(j) == m.end())
                    m[j] = 1;
                else
                    m[j]++;
            }
            Logger() << "RandomInt(" << a << ", " << b << ") distribution:" << endl;
            Logger() << m;
            ASSERT1((int)m.size() == b - a + 1);
            for (int i = a; i <= b; i++)
                ASSERT1(m.find(i) != m.end());
        };
        for (int i = 0; i < 10; i++)
        {
            check(0, i);
        }
    });
}

#endif