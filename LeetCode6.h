#ifndef _LEETCODE6_H_
#define _LEETCODE6_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 658. Find K Closest Elements
        // Given a sorted array, two integers k and x, find the k closest elements to x
        // in the array. The result should also be sorted in ascending order. If there
        // is a tie, the smaller elements are always preferred. Example 1: Input:
        // [1,2,3,4,5], k=4, x=3 Output: [1,2,3,4] Example 2: Input: [1,2,3,4,5], k=4,
        // x=-1 Output: [1,2,3,4] Note: The value k is positive and will always be
        // smaller than the length of the sorted array. Length of the given array is
        // positive and will not exceed 10^4. Absolute value of elements in the array
        // and x will not exceed 10^4. UPDATE (2017/9/19): The arr parameter had been
        // changed to an array of integers (instead of a list of integers). Please
        // reload the code definition to get the latest changes. arr: [1,2,3,4,5] k: 4
        // x: -1
        vector<int> findClosestElements(const vector<int> &arr, int k, int x)
        {
            if (arr.empty())
                return {};
            if (arr.size() == 1)
                return arr;
            int b = 0;
            int e = (int)arr.size() - 1;
            int m;
            while (b + 1 < e)
            {
                m = b + ((e - b) >> 1);
                if (arr[m] < x)
                    b = m;
                else if (arr[m] > x)
                    e = m;
                else
                    break;
            }
            vector<int> result;
            if (b + 1 < e)
            {
                // Must have found x
                result.push_back(arr[m]);
                b = m - 1;
                e = m + 1;
            }
            else if (arr[b] >= x)
            {
                // b = 0, e = 1, x <= arr[b] <= arr[e]
                result.push_back(arr[b--]);
            }
            else if (arr[e] <= x)
            {
                // b = e - 1, e = arr.size - 1, arr[b] < arr[e] <= x
                result.push_back(arr[e++]);
            }
            else
            {
                // 0 < b < b + 1 == e < arr.size - 1
                // arr[b] < x << arr[e]
            }
            // b and e point to next possible candidates
            while (e - b - 1 < k)
            {
                if (b < 0)
                    result.push_back(arr[e++]);
                else if (e >= (int)arr.size())
                    result.insert(result.begin(), 1, arr[b--]);
                else if (x - arr[b] <= arr[e] - x)
                    result.insert(result.begin(), 1, arr[b--]);
                else
                    result.push_back(arr[e++]);
            }
            return result;
        }
        // This may not output the smaller ones on tie
        // arr:[0,0,1,2,3,3,4,7,7,8]
        // k: 3
        // x: 5
        // Output: [4,7,7]
        // Expected: [3,3,4]
        vector<int> findClosestElements2(vector<int> &arr, int k, int x)
        {
            vector<int> result;
            int b = 0;
            int e = (int)arr.size() - 1;
            int i = b;
            while (b <= e)
            {
                i = b;
                int j = e - 1;
                while (i <= j)
                {
                    if (abs(arr[i] - x) > abs(arr[e] - x))
                        swap(arr[i], arr[j--]);
                    else
                        i++;
                }
                swap(arr[i++], arr[e]);
                if (i - b < k)
                {
                    k -= i - b;
                    b = i;
                }
                else if (i - b > k)
                {
                    e = i - 2;
                }
                else
                {
                    break;
                }
            }
            result.insert(result.begin(), arr.begin(), arr.begin() + i);
            sort(result.begin(), result.end());
            return result;
        }

    }
}

#endif
