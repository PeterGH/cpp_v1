#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "Random.h"
#include "Test.h"
#include "Util.h"

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

    Add("StringToInteger", [&]() {
        auto check = [&](const string &s, int e) {
            int r1 = LeetCode::AToI::solve1(s);
            int r2 = LeetCode::AToI::solve2(s);
            Logger() << "atoi(\"" << s << "\") = " << r1 << (r1 == e ? " == " : " != ") << e << endl;
            Logger() << "atoi2(\"" << s << "\") = " << r2 << (r2 == e ? " == " : " != ") << e << endl;
            ASSERT1(r1 == e);
            ASSERT1(r2 == e);
        };

        check("-2147483647", -2147483647);
    });

    Add("NextPermutation", [&]() {
        auto check = [&](vector<int> &v) {
            sort(v.begin(), v.end());
            Logger() << v;
            vector<int> v2(v);
            vector<int> v3(v);
            while (std::next_permutation(v.begin(), v.end()))
            {
                LeetCode::Permutation::next(v2);
                LeetCode::Permutation::next2(v3);
                Logger() << v2;
                for (size_t i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == v2[i]);
                    ASSERT1(v[i] == v3[i]);
                }
            }
            LeetCode::Permutation::next(v2);
            LeetCode::Permutation::next2(v3);
            Logger() << v2;
            for (size_t i = 0; i < v.size(); i++)
            {
                ASSERT1(v[i] == v2[i]);
                ASSERT1(v[i] == v3[i]);
            }
        };
        for (int i = 0; i < 10; i++)
        {
            vector<int> input = Random::Vector(Random::Int(6, 1), 6);
            int length = (int)input.size();
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            check(input);
        }
        for (int i = 0; i < 100; i++)
        {
            vector<int> v = Random::Vector(Random::Int(10, 1), 10);
            int length = (int)v.size();
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            Logger() << v;
            vector<int> v2(v);
            vector<int> v3(v);
            std::next_permutation(v.begin(), v.end());
            LeetCode::Permutation::next(v2);
            LeetCode::Permutation::next2(v3);
            Logger() << v2;
            for (size_t i = 0; i < v.size(); i++)
            {
                ASSERT1(v[i] == v2[i]);
                ASSERT1(v[i] == v3[i]);
            }
        }
    });

    Add("Permutation", [&]() {
        auto check = [&](vector<int> &v) {
            sort(v.begin(), v.end());
            Logger() << v;
            vector<vector<int>> p = {v};
            while (std::next_permutation(v.begin(), v.end()))
                p.push_back(vector<int>(v));
            Logger() << p;
            Util::Sort(p);
            vector<int> v2(v);
            vector<vector<int>> p2 = LeetCode::Permutation::permuteDistinct(v2);
            Logger() << p2;
            Util::Sort(p2);
            vector<int> v3(v);
            vector<vector<int>> p3 = LeetCode::Permutation::permuteDistinct2(v3);
            Logger() << p3;
            Util::Sort(p3);
            vector<int> v4(v);
            vector<vector<int>> p4 = LeetCode::Permutation::permuteUnique(v4);
            Logger() << p4;
            Util::Sort(p4);
            ASSERT1(p.size() == p2.size());
            ASSERT1(p.size() == p3.size());
            ASSERT1(p.size() == p4.size());
            for (size_t i = 0; i < p.size(); i++)
            {
                ASSERT1(0 == Util::Compare(p[i], p2[i]));
                ASSERT1(0 == Util::Compare(p[i], p3[i]));
                ASSERT1(0 == Util::Compare(p[i], p4[i]));
            }
        };
        {
            vector<int> v = {0, 1, 2, 3, 4};
            check(v);
        }
        {
            vector<int> v = {1, 2, 3, 4};
            check(v);
        }
    });

    Add("CombinationSumReuse", [&]() {
        auto check = [&](vector<int> &v, int t) {
            Logger() << v << "Target " << t << endl;
            vector<int> v1(v);
            vector<int> v2(v);
            vector<int> v3(v);
            auto c1 = LeetCode::Combination::combinationSumReuse(v1, t);
            auto c2 = LeetCode::Combination::combinationSumReuse2(v2, t);
            auto c3 = LeetCode::Combination::combinationSumReuse3(v3, t);
            Util::SortGrid(c1);
            Util::SortGrid(c2);
            Util::SortGrid(c3);
            Logger() << c1;
            ASSERT1(c1.size() == c2.size());
            ASSERT1(c1.size() == c3.size());
            for (size_t i = 0; i < c1.size(); i++)
            {
                ASSERT1(c1[i].size() == c2[i].size());
                ASSERT1(c1[i].size() == c3[i].size());
                for (size_t j = 0; j < c1[i].size(); j++)
                {
                    ASSERT1(c1[i][j] == c2[i][j]);
                    ASSERT1(c1[i][j] == c3[i][j]);
                }
            }
        };
        for (int i = 0; i < 20; i++)
        {
            vector<int> input = Util::IncreasingVector(Random::Int(10, 1), 2);
            Util::Shuffle(input);
            int t = 0;
            int c = 1 + (input.size() >> 2);
            for (int j = 0; j < c; j++)
            {
                t += input[Random::Int(input.size() - 1)];
            }
            check(input, t);
        }
        {
            //vector<int> v = { 6, 11, 5, 3, 2, 8, 7, 4, 10, 9 };
            vector<int> v = {6, 7, 5};
            check(v, 24);
        }
        {
            vector<int> v = {7, 10};
            check(v, 24);
        }
        {
            vector<int> v = {6, 11, 5, 3, 2, 8, 7, 4, 10, 9};
            check(v, 24);
        }
    });

    Add("CombinationSumNoReuse", [&]() {
        auto check = [&](vector<int> &v, int t) {
            Logger() << v << "Target " << t << endl;
            vector<int> v1(v);
            vector<int> v2(v);
            auto c1 = LeetCode::Combination::combinationSumNoReuse(v1, t);
            auto c2 = LeetCode::Combination::combinationSumNoReuse2(v2, t);
            Util::SortGrid(c1);
            Util::SortGrid(c2);
            Logger() << c1 << c2;
            ASSERT1(c1.size() == c2.size());
            for (size_t i = 0; i < c1.size(); i++)
            {
                ASSERT1(c1[i].size() == c2[i].size());
                for (size_t j = 0; j < c1[i].size(); j++)
                {
                    ASSERT1(c1[i][j] == c2[i][j]);
                }
            }
        };
        {
            vector<int> v = {10, 1, 2, 7, 6, 1, 5};
            check(v, 8);
        }
    });

    Add("RemoveDuplicates", [&]() {
        auto check = [&](vector<int> &v) {
            Logger() << v;
            set<int> s;
            for (size_t i = 0; i < v.size(); i++)
            {
                s.insert(v[i]);
            }
            size_t len = LeetCode::removeDuplicates(v);
            Logger() << v;
            ASSERT1(len == s.size());
            for (size_t i = 0; i < len; i++)
            {
                ASSERT1(v[i] == *s.begin());
                s.erase(s.begin());
            }
        };
        {
            vector<int> v = {0, 1, 2, 3, 4, 5};
            check(v);
        }
        {
            vector<int> v = {0, 0, 0};
            check(v);
        }
        {
            for (int i = 0; i < 20; i++)
            {
                vector<int> input = Random::Vector(Random::Int(50, 1), 10, -10);
                sort(input.begin(), input.end());
                int length = (int)input.size();
                Logger().WriteInformation("Run %d: %d elements\n", i, length);
                check(input);
            }
        }
    });

    Add("RemoveElement", [&]() {
        auto check = [&](vector<int> &v, int e) {
            Logger() << v << "Removing " << e << endl;
            vector<int> s;
            for (size_t i = 0; i < v.size(); i++)
            {
                if (v[i] != e)
                    s.push_back(v[i]);
            }
            vector<int> v2(v);

            size_t len = LeetCode::removeElementStable(v, e);
            Logger() << v << "Length " << len << endl;
            size_t len2 = LeetCode::removeElementUnstable(v2, e);
            Logger() << v2 << "Length " << len2 << endl;
            ASSERT1(len == s.size());
            ASSERT1(len2 == s.size());

            sort(v.begin(), v.begin() + len);
            sort(v2.begin(), v2.begin() + len2);
            sort(s.begin(), s.end());
            for (size_t i = 0; i < len; i++)
            {
                ASSERT1(v[i] == s[i]);
                ASSERT1(v2[i] == s[i]);
            }
        };
        {
            vector<int> v = {0, 1, 2, 3, 4, 5};
            check(v, 0);
        }
        {
            vector<int> v = {0, 0, 0};
            check(v, 0);
        }
        for (int i = 0; i < 20; i++)
        {
            vector<int> input = Random::Vector(Random::Int(50, 1), 10, -10);
            int length = (int)input.size();
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            check(input, Random::Int(10, -10));
        }
    });

    Add("SearchRange", [&]() {
        auto check = [&](vector<int> &v, int e) {
            Logger() << v;
            Logger() << "Range " << e << ": ";
            vector<int> p = LeetCode::searchRange(v, e);
            vector<int> p2 = LeetCode::searchRange2(v, e);
            Logger() << "[" << p[0] << ", " << p[1] << "], [" << p2[0] << ", " << p2[1] << "]" << endl;
            ASSERT1(p[0] == p2[0]);
            ASSERT1(p[1] == p2[1]);
            if (p[0] > 0)
            {
                ASSERT1(v[p[0] - 1] < v[p[0]]);
                ASSERT1(v[p[0]] == e);
            }
            if (0 <= p[1] && p[1] < (int)v.size() - 1)
            {
                ASSERT1(v[p[1]] < v[p[1] + 1]);
                ASSERT1(v[p[1]] == e);
            }
        };
        {
            vector<int> v = {0};
            check(v, 0);
            check(v, 1);
        }
        {
            vector<int> v = {1, 1};
            check(v, 1);
            check(v, 2);
        }
        {
            vector<int> v = {2, 3};
            check(v, 1);
            check(v, 2);
            check(v, 3);
            check(v, 4);
        }
        for (int i = 0; i < 100; i++)
        {
            vector<int> input = Random::Vector(Random::Int(100, 1), 5, -5);
            sort(input.begin(), input.end());
            check(input, Random::Int(6, -6));
        }
    });

    Add("MaxSubarray", [&]() {
        auto check = [&](vector<int> &a, int el, int er, int es) -> void {
            Logger() << a;
            int sum = LeetCode::maxSubArray(a);
            int l2, r2;
            int sum2 = LeetCode::maxSubArray2(a, l2, r2);
            Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
            int l3, r3;
            int sum3 = LeetCode::maxSubArray3(a, l3, r3);
            Logger().WriteInformation("a[%d..%d] = %d\n", l3, r3, sum3);
            ASSERT1(es == sum);
            ASSERT1(el == l2);
            ASSERT1(er == r2);
            ASSERT1(es == sum2);
            ASSERT1(el == l3);
            ASSERT1(er == r3);
            ASSERT1(es == sum3);
        };
        {
            vector<int> A = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
            check(A, 7, 10, 43);
        }
        {
            vector<int> A = {13};
            check(A, 0, 0, 13);
        }
        {
            vector<int> A = {13, -3};
            check(A, 0, 0, 13);
        }
        {
            vector<int> A = {13, -3, -25};
            check(A, 0, 0, 13);
        }
        {
            vector<int> A = {13, -3, -25, 20};
            check(A, 3, 3, 20);
        }
        {
            vector<int> A = {13, -3, -25, 20, -3};
            check(A, 3, 3, 20);
        }
        {
            vector<int> A = {13, -3, -25, 20, -3, -16, -23, 18};
            check(A, 3, 3, 20);
        }
        {
            vector<int> A = {13, 3, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 4, 7};
            check(A, 0, (int)A.size() - 1, 213);
        }
        {
            vector<int> A = {13, 3};
            check(A, 0, 1, 16);
        }
        {
            vector<int> A = {13, 3, 25};
            check(A, 0, 2, 41);
        }
        {
            vector<int> A = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
            check(A, 1, 1, -3);
        }
        {
            vector<int> A = {-13};
            check(A, 0, 0, -13);
        }
        {
            vector<int> A = {-13, -3};
            check(A, 1, 1, -3);
        }
        {
            vector<int> A = {0, 0, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
            check(A, 0, 0, 0);
        }
        {
            vector<int> A = {0};
            check(A, 0, 0, 0);
        }
        {
            vector<int> A = {0, 0, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 0, 0};
            check(A, 2, 13, 186);
        }
        {
            vector<int> A = {-25, -20, -3, 0, 0, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
            check(A, 3, 3, 0);
        }
        {
            vector<int> A = {-25, -20, -3, 0, 0};
            check(A, 3, 3, 0);
        }
        {
            vector<int> A = {1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, -7};
            check(A, 0, 2, 3);
        }
        {
            vector<int> A = {1, 1, 1, -1, -1, -1};
            check(A, 0, 2, 3);
        }
        {
            vector<int> A = {1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, 7};
            check(A, (int)A.size() - 1, (int)A.size() - 1, 7);
        }
        {
            int d = RAND_MAX >> 1;
            for (int i = 0; i < 1000; i++)
            {
                vector<int> input;
                int length = 1 + (rand() % 100);
                for (int j = 0; j < length; j++)
                {
                    input.push_back(rand() - d);
                }
                Logger() << input;
                int sum = LeetCode::maxSubArray(input);
                Logger().WriteInformation("MaxSubArraySum = %d\n", sum);
                int l2, r2;
                int sum2 = LeetCode::maxSubArray2(input, l2, r2);
                Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
                int l3, r3;
                int sum3 = LeetCode::maxSubArray3(input, l3, r3);
                Logger().WriteInformation("a[%d..%d] = %d\n", l3, r3, sum3);
                ASSERT1(l2 == l3);
                ASSERT1(r2 == r3);
                ASSERT1(sum == sum2);
                ASSERT1(sum == sum3);
            }
        }
        {
            for (int i = 0; i < 1000; i++)
            {
                vector<int> input;
                int length = 1 + (rand() % 100);
                for (int j = 0; j < length; j++)
                {
                    input.push_back(rand() % 20 - 10);
                }
                Logger() << input;
                int sum = LeetCode::maxSubArray(input);
                int l2, r2;
                int sum2 = LeetCode::maxSubArray2(input, l2, r2);
                Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
                int l3, r3;
                int sum3 = LeetCode::maxSubArray3(input, l3, r3);
                Logger().WriteInformation("a[%d..%d] = %d\n", l3, r3, sum3);
                ASSERT1(l2 == l3);
                ASSERT1(r2 == r3);
                ASSERT1(sum == sum2);
                ASSERT1(sum == sum3);
            }
        }
    });
}
#endif