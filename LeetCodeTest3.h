#ifndef _LEETCODETEST3_H_
#define _LEETCODETEST3_H_

#include "LeetCodeTest.h"

void LeetCodeTest::Init3(void)
{
    Add("300. Longest Increasing Subsequence", [&]()
        {
            auto check = [&](const vector<int> &v, int e)
            {
                int l = lengthOfLIS(v);
                int l2 = lengthOfLIS2(v);
                int l3 = lengthOfLIS3(v);
                int l4 = lengthOfLIS4(v);
                int l5 = lengthOfLIS5(v);
                ASSERT1(l == e);
                ASSERT1(l2 == e);
                ASSERT1(l3 == e);
                ASSERT1(l4 == e);
                ASSERT1(l5 == e);
            };
            check({10, 9, 2, 5, 3, 7, 101, 18}, 4);
        });

    Add("306. Additive Number", [&]()
        {
            auto check = [&](const string &n, bool e)
            {
                bool r = isAdditiveNumber(n);
                ASSERT1(r == e);
            };
            check("199100199", true);
            check("11111111111011111111111", true);
        });

    Add("307. Range Sum Query - Mutable", [&]()
        {
            {
                NumArrayMutable6 a6({1, 3, 5});
                int v = a6.sumRange(0, 2);
                Logger() << "sumRange(0, 2) = " << v << endl;
                Logger() << "update(1, 2)" << endl;
                a6.update(1, 2);
                v = a6.sumRange(0, 2);
                Logger() << "sumRange(0, 2) = " << v << endl;
            }
            {
                NumArrayMutable6 a6({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
                a6.print();
            }
            {
                NumArrayMutable6 a6({-28, -39, 53, 65, 11, -56, -65, -39, -43, 97});
                a6.sumRange(5, 6);
                a6.update(9, 27);
                a6.sumRange(2, 3);
                a6.sumRange(6, 7);
                a6.update(1, -82);
                a6.update(3, -72);
                a6.sumRange(3, 7);
                a6.sumRange(1, 8);
                a6.update(5, 13);
                a6.update(4, -67);
            }
        });

    Add("310. Minimum Height Trees", [&]()
        {
            auto check = [&](int n, const vector<vector<int>> &edges)
            {
                vector<int> roots = findMinHeightTrees(n, edges);
            };
            check(4, {{1, 0}, {1, 2}, {1, 3}});
        });

    Add("315. Count of Smaller Numbers After Self", [&]()
        {
            auto check = [&](const vector<int> &v)
            {
                vector<int> c = countSmaller(v);
                Logger() << "Input: " << v << endl;
                Logger() << "Output: " << c << endl;
            };
            check({5, 2, 6, 1});
        });

    Add("321. Create Maximum Number", [&]()
        {
            auto check = [&](const vector<int> &n1, const vector<int> &n2, int k)
            {
                Logger() << "Input1: " << n1 << endl;
                Logger() << "Input2: " << n2 << endl;
                Logger() << "k = " << k << endl;
                vector<int> m = maxNumber(n1, n2, k);
                vector<int> m2 = maxNumber2(n1, n2, k);
                Logger() << m << m2;
                ASSERT1(Util::Compare(m, m2) == 0);
            };
            check({3, 4, 6, 5}, {9, 1, 2, 5, 8, 3}, 5);
        });

    Add("322. Coin Change", [&]()
        {
            auto check = [&](const vector<int> &coins, int amount)
            {
                Logger() << "coins: " << coins;
                Logger() << "amount: " << amount << endl;
                int c = coinChange(coins, amount);
                int c2 = coinChange2(coins, amount);
                int c3 = coinChange3(coins, amount);
                Logger() << "min count: " << c << ", " << c2 << ", " << c3 << endl;
                ASSERT1(c == c2);
                ASSERT1(c == c3);
            };
            check({336, 288, 378, 16, 319, 146}, 9212);
        });

    Add("330. Patching Array", [&]()
        {
            auto check = [&](const vector<int> &nums, int n, int e)
            {
                Logger() << nums;
                Logger() << n;
                int c = minPatches(nums, n);
                Logger() << c << (c == e ? "==" : "!=") << e << endl;
                ASSERT1(c == e);
            };
            check({1, 2, 31, 33}, 2147483647, 27);
        });

    Add("331. Verify Preorder Serialization of a Binary Tree", [&]()
        {
            auto check = [&](const string &p, bool e)
            {
                bool r = isValidSerialization2(p);
                ASSERT1(r == e);
            };
            check("9,3,4,#,#,1,#,#,2,#,6,#,#", true);
        });

    Add("341. Flatten Nested List Iterator", [&]()
        {
            auto check = [&](const vector<NestedListIterator::NestedInteger> &list, const vector<int> &e)
            {
                NestedListIterator::NestedIterator it(list);
                vector<int> r;
                while (it.hasNext())
                {
                    r.push_back(it.next());
                }
                Logger() << r;
                ASSERT1(0 == Util::Compare(r, e));
            };
            {
                vector<NestedListIterator::NestedInteger> l;
                vector<NestedListIterator::NestedInteger> l1;
                l1.push_back(NestedListIterator::NestedInteger(1));
                l1.push_back(NestedListIterator::NestedInteger(1));
                l.push_back(NestedListIterator::NestedInteger(l1));
                l.push_back(NestedListIterator::NestedInteger(2));
                vector<NestedListIterator::NestedInteger> l2;
                l2.push_back(NestedListIterator::NestedInteger(1));
                l2.push_back(NestedListIterator::NestedInteger(1));
                l.push_back(NestedListIterator::NestedInteger(l2));
                check(l, {1, 1, 2, 1, 1});
            }
        });

    Add("354. Russian Doll Envelopes", [&]()
        {
            auto check = [&](vector<vector<int>> &v, int e)
            {
                Logger() << v;
                vector<vector<int>> v1(v);
                int c = maxEnvelopes(v1);
                vector<vector<int>> v2(v);
                int c2 = maxEnvelopes2(v2);
                Logger() << c << ", " << c2 << ", " << e << endl;
                ASSERT1(c == e);
                ASSERT1(c2 == e);
            };
            {
                vector<vector<int>> v = {{2, 100}, {3, 200}, {4, 300}, {5, 500}, {5, 400}, {5, 250}, {6, 370}, {6, 360}, {7, 380}};
                check(v, 5);
            }
        });

    Add("377. Combination Sum IV", [&]()
        {
            auto check = [&](const vector<int> &v, int t)
            {
                Logger() << v;
                Logger() << "Target: " << t << endl;
                vector<int> v1(v);
                int c = LeetCode::combinationSumIV(v1, t);
                vector<int> v2(v);
                int c2 = LeetCode::combinationSumIV2(v2, t);
                Logger() << "Count: " << c << ", " << c2 << endl;
                ASSERT1(c == c2);
            };
            check({1, 2, 3}, 4);
            check({3, 1, 2, 4}, 4);
            check({1, 2, 3}, 32);
        });

    Add("386. Lexicographical Numbers", [&]()
        {
            auto check = [&](int n)
            {
                Logger() << n << endl;
                vector<int> r = LeetCode::lexicalOrder(n);
                Logger() << r;
            };
            check(13);
        });
}

#endif