#ifndef _LEETCODETEST7_H_
#define _LEETCODETEST7_H_

#include "LeetCodeTest.h"

void LeetCodeTest::Init7(void)
{
    Add("719. Find K-th Smallest Pair Distance", [&]()
        {
            auto check = [&](const vector<int> &v, int k)
            {
                Logger() << v;
                vector<int> v1(v);
                vector<int> v2(v);
                vector<int> v3(v);
                vector<int> v4(v);
                int d = smallestDistancePair(v1, k);
                int d2 = smallestDistancePair2(v2, k);
                int d3 = smallestDistancePair3(v3, k);
                int d4 = smallestDistancePair4(v4, k);
                Logger() << k << "-th smallest distance: " << d << ", " << d2
                         << ", " << d3 << ", " << d4 << endl;
                ASSERT1(d == d2);
                ASSERT1(d == d3);
                ASSERT1(d == d4);
            };
            check({0, 1, 2, 3, 100}, 4);
            check({10, 6, 2, 10, 5, 4, 0, 1, 5, 2, 5, 5, 5, 0, 4, 9, 8,
                   6, 7, 9, 1, 10, 4, 8, 6, 3, 6, 2, 1, 7, 5, 0, 2, 6,
                   10, 10, 0, 3, 9, 0, 8, 3, 5, 9, 4, 4, 5, 2, 2, 7},
                  444);
        });

    Add("744. Find Smallest Letter Greater Than Target", [&]()
        {
            auto check = [&](vector<char> &v, char t)
            {
                Logger() << v << "nextGreatestLetter(" << t << ") = ";
                char c = nextGreatestLetter(v, t);
                char c2 = nextGreatestLetter2(v, t);
                char c3 = nextGreatestLetter3(v, t);
                Logger() << c << ", " << c2 << ", " << c3 << endl;
                ASSERT1(c == c2);
                ASSERT1(c == c3);
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100, 1);
                vector<char> v;
                v.resize(n);
                generate(v.begin(), v.end(), [&]()
                         { return 'a' + (rand() % 26); });
                sort(v.begin(), v.end());
                for (char c = 'a'; c <= 'z'; c++)
                    check(v, c);
            }
        });
}
#endif