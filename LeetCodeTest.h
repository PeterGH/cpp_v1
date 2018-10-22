#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "Random.h"
#include "Test.h"

using namespace Test;

class LeetCodeTest : public TestClass
{
  public:
    LeetCodeTest(Log &log) : TestClass(log) {}
    ~LeetCodeTest(void) {}
    void Init(void);
};

void LeetCodeTest::Init(void)
{
    Add("TwoSum-UnsortedMultiSolutions", [&]() {
        auto check = [&](vector<int> &input, int sum) {
            auto pairs = LeetCode::TwoSum::unsortedMultiSolutions(input, sum);
            vector<int> input2(input);
            auto pairs2 = LeetCode::TwoSum::unsortedMultiSolutions2(input2, sum);
            sort(pairs.begin(), pairs.end());
            sort(pairs2.begin(), pairs2.end());
            Logger() << "Target " << sum << ", pairs count " << pairs.size()
                     << (pairs.size() == pairs2.size() ? "==" : "!=")
                     << pairs2.size() << endl;
            ASSERT1(pairs.size() == pairs2.size());
            for (size_t i = 0; i < pairs.size(); i++)
            {
                if (pairs[i] != pairs2[i])
                {
                    Logger() << "pairs " << i << "<" << pairs[i].first << "," << pairs[i].second
                             << "> != <" << pairs2[i].first << "," << pairs2[i].second << ">" << endl;
                }
                ASSERT1(pairs[i] == pairs2[i]);
            }
        };

        for (int i = 0; i < 20; i++)
        {
            vector<int> input = Random::Vector(Random::Int(50, 2), 20, -20);
            int length = (int)input.size();
            Logger() << "Run " << i << ": " << length << " numbers" << endl;
            for (int j = 0; j < length - 1; j++)
            {
                for (int k = j + 1; k < length; k++)
                {
                    check(input, input[j] + input[k]);
                }
            }
        }
    });

    Add("TwoSum-SortedMultiSolutions", [&]() {
        auto check = [&](vector<int> &input, int sum) {
            auto pairs = LeetCode::TwoSum::sortedMultiSolutions(input, sum);
            auto pairs2 = LeetCode::TwoSum::sortedMultiSolutions2(input, sum);
            sort(pairs.begin(), pairs.end());
            sort(pairs2.begin(), pairs2.end());
            Logger() << "Target: " << sum << ", pairs count " << pairs.size()
                     << (pairs.size() == pairs2.size() ? "==" : "!=")
                     << pairs2.size() << endl;
            ASSERT1(pairs.size() == pairs2.size());
            for (size_t i = 0; i < pairs.size(); i++)
            {
                if (pairs[i] != pairs2[i])
                {
                    Logger() << "pairs " << i << "<" << pairs[i].first << "," << pairs[i].second
                             << "> != <" << pairs2[i].first << "," << pairs2[i].second << ">" << endl;
                }
                ASSERT1(pairs[i] == pairs2[i]);
            }
        };
        for (int i = 0; i < 20; i++)
        {
            vector<int> input = Random::Vector(Random::Int(50, 2), 20, -20);
            sort(input.begin(), input.end());
            int length = (int)input.size();
            Logger() << "Run " << i << ": " << length << " numbers" << endl;
            for (int j = 0; j < length - 1; j++)
            {
                for (int k = j + 1; k < length; k++)
                {
                    check(input, input[j] + input[k]);
                }
            }
        }
    });

    Add("MedianOfTwoSortedArrays", [&]() {
        auto search = [&](vector<int> &v1, vector<int> &v2) -> double {
            vector<int> v(v1);
            v.insert(v.end(), v2.begin(), v2.end());
            sort(v.begin(), v.end());
            int n = v.size();
            int m = (n - 1) / 2;
            if ((n & 0x1) == 0)
                return (v[m] + v[m + 1]) / 2.0;
            else
                return v[m];
        };

        auto check = [&](vector<int> &v1, vector<int> &v2) {
            Logger() << v1 << v2;
            double e = search(v1, v2);
            double m = LeetCode::findMedianSortedArrays(v1, v2);
            Logger() << "Median " << m << (m == e ? " == " : " != ") << e << endl;
            ASSERT1(m == e);
        };

        for (int i = 0; i < 1000; i++)
        {
            vector<int> v1 = Random::Vector(Random::Int(50), 50);
            vector<int> v2 = Random::Vector(Random::Int(50), 50);
            if (v1.empty() && v2.empty())
                v1.push_back(Random::Int(50));
            sort(v1.begin(), v1.end());
            sort(v2.begin(), v2.end());
            check(v1, v2);
        }
    });

    Add("LongestPalindromeSubstring", [&]() {
        auto check = [&](const string &s) {
            string p1 = LeetCode::LongestPalindrome::solve1(s);
            string p2 = LeetCode::LongestPalindrome::solve2(s);
            string p3 = LeetCode::LongestPalindrome::solve3(s);
            Logger() << s << ", '" << p1 << "', '" << p2 << "', '" << p3 << "'" << endl;
            ASSERT1(p1 == p2);
            ASSERT1(p1 == p3);
        };

        check("babad");
    });
}
#endif