#ifndef _LEETCODE4_H_
#define _LEETCODE4_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 400. Nth Digit
        // Given an integer n, return the nth digit of the infinite integer sequence
        // [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
        // Example 1:
        // Input: n = 3
        // Output: 3
        // Example 2:
        // Input: n = 11
        // Output: 0
        // Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0,
        // which is part of the number 10.
        // Constraints:
        // 1 <= n <= 2^31 - 1
        // Group numbers into ranges per number of digits:
        // [1..9]
        // [10..99]
        // [100..999]
        // [1000..9999]
        // [10000..99999]
        // ......
        int findNthDigit(int n)
        {
            long long b = 1; // base for a range
            long long c = 1; // count digits per number in a range
            long long a = 9 * b * c; // accumulated count of digits
            while (a < n)
            {
                b *= 10;
                c++;
                a += 9 * b * c;
            }
            a -= 9 * b * c;
            n -= a;
            n--;
            // Now n is the index (0-based) of the target digit in the
            // range where every number has c digits and the base is b.
            // Find the number having the target digit.
            int d = b + n / c;
            // Find the index of the target digit in the target number.
            n %= c;
            while (n + 1 < c)
            {
                d /= 10;
                c--;
            }
            return d % 10;
        }

        // 410. Split Array Largest Sum
        // Given an array which consists of non-negative integers and an integer m, you
        // can split the array into m non-empty continuous subarrays. Write an algorithm
        // to minimize the largest sum among these m subarrays. Note: If n is the length
        // of array, assume the following constraints are satisfied:
        // 1 <= n <= 1000
        // 1 <= m <= min(50, n)
        // Examples:
        // Input:
        // nums = [7,2,5,10,8]
        // m = 2
        // Output:
        // 18
        // Explanation:
        // There are four ways to split nums into two subarrays.
        // The best way is to split it into [7,2,5] and [10,8],
        // where the largest sum among the two subarrays is only 18.
        int splitArray(const vector<int> &nums, int m)
        {
            long long l = 0;
            long long h = 0;
            for (int n : nums)
            {
                l = max(l, (long long)n);
                h += n;
            }
            while (l < h)
            {
                long long t = l + ((h - l) >> 1);
                int c = 0;
                long long s = 0;
                for (size_t i = 0; i < nums.size(); i++)
                {
                    s += nums[i];
                    if (s > t)
                    {
                        c++;
                        s = nums[i];
                    }
                }
                if (s > 0)
                    c++;
                if (c > m)
                    l = t + 1;
                else
                    h = t;
            }
            return l;
        }

    }
}

#endif
