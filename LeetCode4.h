#ifndef _LEETCODE4_H_
#define _LEETCODE4_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
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
