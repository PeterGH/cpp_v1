#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include <algorithm>
#include <functional>
#include <limits.h>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Test
{
namespace LeetCode
{
namespace TwoSum
{
// 1. Two Sum
// Given an array of integers find the indices of the two numbers adding up to
// a specific target. Assuming only one solution exists. Should not use the
// same element twice.
// @array, @linear, @hash
static vector<int> unsortedUniqueSolution(vector<int> &nums, int target)
{
    map<int, int> firstIndex;
    for (int i = 0; i < (int)nums.size(); i++)
    {
        int first = target - nums[i];
        if (firstIndex.find(first) != firstIndex.end())
            return vector<int>{firstIndex[first], i};
        firstIndex[nums[i]] = i;
    }
    return vector<int>();
}

// @array, @linear, @hash
static vector<pair<int, int>> unsortedMultiSolutions(vector<int> &nums, int target)
{
    vector<pair<int, int>> result;
    unordered_multimap<int, int> m;
    for (int i = 0; i < (int)nums.size(); i++)
    {
        // range is a list of pairs, where the value first is the key
        // and the second is the index. range.first is the lower bound
        // inclusively, and range.second is the upper bound exclusively.
        auto range = m.equal_range(target - nums[i]);
        for_each(range.first, range.second,
                 [&](unordered_multimap<int, int>::value_type &v) {
                     result.push_back(make_pair(v.second, i));
                 });
        m.insert(make_pair(nums[i], i));
    }
    return result;
}

// @array, @partition, @binarysearch
static vector<pair<int, int>> unsortedMultiSolutions2(vector<int> &nums, int target)
{
    vector<pair<int, int>> result;

    size_t length = nums.size();
    vector<pair<int, size_t>> valueIndex;
    for (size_t i = 0; i < length; i++)
    {
        valueIndex.push_back(make_pair(nums[i], i));
    }

    // partition valueIndex[b..e] by v, return index i where valueIndex[i]
    // is the first element greater than or equal to v.
    function<size_t(int, size_t, size_t)> partition =
        [&](int v, size_t b, size_t e) -> size_t {
        size_t i = b;
        for (size_t j = b; j <= e; j++)
        {
            if (valueIndex[j].first < v)
            {
                if (i++ != j)
                    swap(valueIndex[i - 1], valueIndex[j]);
            }
        }
        return i;
    };

    size_t shortRangeBegin, shortRangeEnd;
    size_t longRangeBegin, longRangeEnd;
    int half = (target >> 1);

    if ((target & 0x1) == 0)
    {
        // target is even
        // +---------------+-----------------+------------------+
        // 0               i1                i2                 length-1
        //    < target/2       = target/2         > target/2
        size_t i1 = partition(half, 0, length - 1);

        if (i1 == length)
            return result; // All numbers are less than half

        size_t i2 = partition(half + 1, i1, length - 1);

        // every pair in valueIndex[i1..i2) sums up to target
        for (size_t i = i1; i < i2 - 1; i++)
        {
            for (size_t j = i + 1; j < i2; j++)
            {
                result.push_back(make_pair(
                    min(valueIndex[i].second, valueIndex[j].second),
                    max(valueIndex[i].second, valueIndex[j].second)));
            }
        }

        if (i1 == 0 || i2 == length)
            return result;

        if (i1 <= length - i2)
        {
            shortRangeBegin = 0;
            shortRangeEnd = i1 - 1;
            longRangeBegin = i2;
            longRangeEnd = length - 1;
        }
        else
        {
            shortRangeBegin = i2;
            shortRangeEnd = length - 1;
            longRangeBegin = 0;
            longRangeEnd = i1 - 1;
        }
    }
    else
    {
        // target is odd
        // +-------------------------+---------------------------+
        // 0                         i1                          length-1
        //    <= target/2                >= target/2 + 1
        size_t i1 = partition(half + 1, 0, length - 1);

        if (i1 == 0)
            return result; // All numbers are greater than half, no matter whether target is positive or negative
        if (i1 == length)
            return result; // All numbers are less than or equal to half, no matter whether target is positive or negative

        if (i1 <= length - i1)
        {
            shortRangeBegin = 0;
            shortRangeEnd = i1 - 1;
            longRangeBegin = i1;
            longRangeEnd = length - 1;
        }
        else
        {
            shortRangeBegin = i1;
            shortRangeEnd = length - 1;
            longRangeBegin = 0;
            longRangeEnd = i1 - 1;
        }
    }

    sort(valueIndex.begin() + longRangeBegin, valueIndex.begin() + longRangeEnd + 1);

    // find the first element in valueIndex[b..e] equal to v
    function<int(int, int, int)> search =
        [&](int v, int b, int e) -> int {
        while (b <= e)
        {
            int m = b + ((e - b) >> 1);
            if (v < valueIndex[m].first)
                e = m - 1;
            else if (v > valueIndex[m].first)
                b = m + 1;
            else if (b == m)
                return m;
            else
                e = m;
        }
        return -1;
    };

    for (size_t i = shortRangeBegin; i <= shortRangeEnd; i++)
    {
        int v = target - valueIndex[i].first;
        int j = search(v, longRangeBegin, longRangeEnd);
        if (j == -1)
            continue;
        do
        {
            result.push_back(make_pair(
                min(valueIndex[i].second, valueIndex[j].second),
                max(valueIndex[i].second, valueIndex[j].second)));
            j++;
        } while (j <= (int)longRangeEnd && valueIndex[j].first == v);
    }
    return result;
}

// 167. Two Sum II - Input array is sorted
// Given a sorted array of integers, find two numbers summing up to a specific
// target. Return the indices (1-based) and the first index must be less than the
// second.
// @array, @linear
static vector<int> sortedUniqueSolution(vector<int> &numbers, int target)
{
    int i = 0;
    int j = numbers.size() - 1;
    while (i < j)
    {
        int sum = numbers[i] + numbers[j];
        if (sum == target)
            return vector<int>{i + 1, j + 1};
        if (sum < target)
            i++;
        else
            j--;
    }
    return vector<int>();
}

// @array, @binarysearch
static vector<pair<int, int>> sortedMultiSolutions(vector<int> &nums, int target)
{
    vector<pair<int, int>> result;
    function<int(int, int, int)> search =
        [&](int v, int b, int e) -> int {
        while (b <= e)
        {
            int m = b + ((e - b) >> 1);
            if (v < nums[m])
                e = m - 1;
            else if (v > nums[m])
                b = m + 1;
            else if (b == m)
                return m;
            else
                e = m;
        }
        return -1;
    };
    for (int i = 0; i < (int)nums.size(); i++)
    {
        int second = target - nums[i];
        int j = search(second, i + 1, nums.size() - 1);
        if (j == -1)
            continue;
        do
        {
            result.push_back(make_pair(i, j));
            j++;
        } while (j < (int)nums.size() && nums[j] == second);
    }
    return result;
}

// @array, @linear
static vector<pair<int, int>> sortedMultiSolutions2(vector<int> &nums, int target)
{
    vector<pair<int, int>> result;
    int i = 0;
    int j = nums.size() - 1;
    while (i < j)
    {
        int sum = nums[i] + nums[j];
        if (sum < target)
            i++;
        else if (sum > target)
            j--;
        else
        {
            int p = i;
            while (p + 1 <= j && nums[p + 1] == nums[p])
                p++;
            int q = j;
            while (i <= q - 1 && nums[q - 1] == nums[q])
                q--;
            if (p < q)
            {
                for (int r = i; r <= p; r++)
                    for (int s = q; s <= j; s++)
                        result.push_back(make_pair(r, s));
            }
            else // p == j && q == i
            {
                for (int r = i; r < j; r++)
                    for (int s = r + 1; s <= j; s++)
                        result.push_back(make_pair(r, s));
            }
            i = p + 1;
            j = q - 1;
        }
    }
    return result;
}
} // namespace TwoSum

// 4. Median of Two Sorted Arrays
// Find the median of the two sorted arrays.
// [1, 3], [2] -> 2.0
// [1, 2], [3, 4] -> 2.5
// @array, @binarysearch
static double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    // For an array a[0..n-1]
    // If n is even, its medians are indexed at (n-1)/2 and n/2
    // If n is odd, its median is indexed at (n-1)/2 == n/2
    function<double(vector<int> &, vector<int> &)> search =
        [&](vector<int> &s, vector<int> &l) -> double {
        // Assume s.size() <= l.size()
        int bs = 0;
        int es = s.size() - 1;
        int n = s.size() + l.size();
        bool odd = ((n & 0x1) == 1);
        // index of the lower median is (n-1)/2 whether n is odd or even
        // index of the upper median is n/2 whether n is odd or even
        int m = (n - 1) / 2;
        if (s.empty())
        {
            if (odd)
                return l[m];
            else
                return (l[m] + l[m + 1]) / 2.0;
        }
        while (bs <= es)
        {
            // index of the lower median
            // 0 <= ms <= s.size() - 1
            int ms = bs + ((es - bs) >> 1);

            // s[0..ms] has ms + 1 elements
            // l[0..ml] has ml + 1 elements
            // Combining two has m + 1 elements, i.e., n[0..m]
            // so ms + 1 + ml + 1 = m + 1
            // (1) ml = -1, if ms = s.size() - 1 && s.size() == l.size()
            // (2) 0 <= ml < l.size() - 1, otherwise
            int ml = m - ms - 1;

            if (ml == -1)
                return (s[ms] + l[0]) / 2.0;

            if (s[ms] >= l[ml])
            {
                if (s[ms] <= l[ml + 1])
                {
                    if (odd)
                        return s[ms];
                    else if (ms + 1 < (int)s.size())
                        return (s[ms] + min(s[ms + 1], l[ml + 1])) / 2.0;
                    else
                        return (s[ms] + l[ml + 1]) / 2.0;
                }
                if (bs == ms)
                {
                    if (odd)
                        return l[ml + 1];
                    else if (ml + 2 < (int)l.size())
                        return (l[ml + 1] + min(s[ms], l[ml + 2])) / 2.0;
                    else
                        return (l[ml + 1] + s[ms]) / 2.0;
                }
                es = ms - 1;
            }
            else
            {
                if (ms == (int)s.size() - 1)
                {
                    if (odd)
                        return l[ml];
                    else
                        return (l[ml] + l[ml + 1]) / 2.0;
                }
                if (l[ml] <= s[ms + 1])
                {
                    if (odd)
                        return l[ml];
                    else
                        return (l[ml] + min(s[ms + 1], l[ml + 1])) / 2.0;
                }
                if (ms == es)
                {
                    if (odd)
                        return s[ms + 1];
                    else if (ms + 2 < (int)s.size())
                        return (s[ms + 1] + min(s[ms + 2], l[ml + 1])) / 2.0;
                    else
                        return (s[ms + 1] + l[ml + 1]) / 2.0;
                }
                bs = ms + 1;
            }
        }
        throw runtime_error("The median is not found.");
    };

    if (nums1.size() <= nums2.size())
        return search(nums1, nums2);
    else
        return search(nums2, nums1);
}

// 26. Remove Duplicates from Sorted Array
// Given a sorted array, remove the duplicates in place such that each
// element appear only once and return the new length.
// Do not allocate extra space for another array, you must do this in
// place with constant memory. For example,
// Given input array nums = [1, 1, 2],
// Your function should return length = 2, with the first two elements
// of nums being 1 and 2 respectively. It does not matter what you leave
// beyond the new length.
// @array, @linear
static size_t removeDuplicates(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    size_t i = 0;
    for (size_t j = 1; j < nums.size(); j++)
    {
        // i increases only when j should be kept
        if (nums[j - 1] != nums[j] && (++i) != j)
            nums[i] = nums[j];
    }
    return i + 1;
}

// 27. Remove Element
// Given an array and a value, remove all instances of that value in
// place and return the new length. Do not allocate extra space for
// another array, you must do this in place with constant memory.
// The order of elements cannot be changed. It does not matter what you
// leave beyond the new length. Example:
// Given input array nums = [3, 2, 2, 3], val = 3
// Your function should return length = 2, with the first two elements
// of nums being 2.
// @array, @linear
static size_t removeElementStable(vector<int> &nums, int val)
{
    int i = -1;
    for (int j = 0; j < (int)nums.size(); j++)
    {
        // i increases only when j should be kept
        if (nums[j] != val && (++i) != j)
            nums[i] = nums[j];
    }
    return i + 1;
}

// Given an array and a value, remove all instances of that value in
// place and return the new length. Do not allocate extra space for
// another array, you must do this in place with constant memory.
// The order of elements can be changed. It does not matter what you
// leave beyond the new length. Example:
// Given input array nums = [3, 2, 2, 3], val = 3
// Your function should return length = 2, with the first two elements
// of nums being 2.
// @array, @linear
static size_t removeElementUnstable(vector<int> &nums, int val)
{
    int i = 0;
    int n = nums.size();
    while (i < n)
    {
        if (nums[i] == val)
            swap(nums[i], nums[--n]);
        else
            i++;
    }
    return n;
}

// 33. Search in Rotated Sorted Array
// Suppose an array sorted in ascending order is rotated at some pivot
// unknown to you beforehand. (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
// You are given a target value to search. If found in the array return
// its index, otherwise return -1. You may assume no duplicate exists in the array.
// @array, @binarysearch
static int search(vector<int> &nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r)
    {
        int m = l + ((r - l) >> 1);
        if (nums[m] == target)
            return m;
        else if (nums[m] < target)
        {
            if (nums[0] < nums[m])
                l = m + 1;
            else if (target <= nums[r])
                l = m + 1;
            else
                r = m - 1;
        }
        else
        {
            if (nums[0] > nums[m])
                r = m - 1;
            else if (nums[l] <= target)
                r = m - 1;
            else
                l = m + 1;
        }
    }
    return -1;
}

// 34. Search for a Range
// Given an array of integers sorted in ascending order,
// find the starting and ending position of a given target value.
// Your algorithm's runtime complexity must be in the order of O(log n).
// If the target is not found in the array, return [-1, -1].
// For example,
// Given[5, 7, 7, 8, 8, 10] and target value 8,
// return[3, 4].
// @array, @binarysearch
static vector<int> searchRange(vector<int> &nums, int target)
{
    if (nums.empty())
        return vector<int>{-1, -1};
    int l = 0;
    int r = nums.size() - 1;
    int m = -1;
    while (l <= r)
    {
        m = l + ((r - l) >> 1);
        if (nums[m] == target)
            break;
        if (nums[m] < target)
            l = m + 1;
        else
            r = m - 1;
    }
    if (l > r)
        return vector<int>{-1, -1};
    int b = m;
    int n;
    if (l < m)
    {
        n = m - 1;
        while (l <= n)
        {
            b = l + ((n - l) >> 1);
            if (nums[b] == target)
            {
                if (b == 0 || nums[b - 1] < target)
                    break;
                else
                    n = b - 1;
            }
            else
            {
                if (nums[b + 1] == target)
                {
                    b++;
                    break;
                }
                else
                    l = b + 1;
            }
        }
        if (l > n)
            b = -1;
    }
    int e = m;
    if (m < r)
    {
        n = m + 1;
        while (n <= r)
        {
            e = n + ((r - n) >> 1);
            if (nums[e] == target)
            {
                if (e == (int)nums.size() - 1 || nums[e + 1] > target)
                    break;
                else
                    n = e + 1;
            }
            else
            {
                if (nums[e - 1] == target)
                {
                    e--;
                    break;
                }
                else
                    r = e - 1;
            }
        }
        if (n > r)
            e = -1;
    }
    return vector<int>{b, e};
}
// @array, @binarysearch
static vector<int> searchRange2(vector<int> &nums, int target)
{
    int b = -1;
    int e = -1;
    bool foundBegin = false;
    bool foundEnd = false;
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r)
    {
        int m = l + ((r - l) >> 1);
        if (nums[m] < target)
            l = m + 1;
        else if (target < nums[m])
            r = m - 1;
        else if (!foundBegin)
        {
            if (l == m)
            {
                foundBegin = true;
                b = m;
                l = b;
                r = nums.size() - 1;
            }
            else
                r = m;
        }
        else if (!foundEnd)
        {
            if (l < m)
                l = m;
            else
            {
                foundEnd = true;
                e = m == r ? m : (nums[r] == target ? r : m);
            }
        }
        else
        {
            break;
        }
    }
    return vector<int>{b, e};
}

// 35. Search Insert Position
// Given a sorted array and a target value, return the index if the
// target is found. If not, return the index where it would be if it
// were inserted in order. You may assume no duplicates in the array.
// Here are few examples.
// [1, 3, 5, 6], 5 -> 2
// [1, 3, 5, 6], 2 -> 1
// [1, 3, 5, 6], 7 -> 4
// [1, 3, 5, 6], 0 -> 0
// @array, @binarysearch
static int searchInsert(vector<int> &nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r)
    {
        int m = l + ((r - l) >> 1);
        if (nums[m] == target)
            return m;
        if (nums[m] < target)
        {
            if (m == r || nums[m + 1] > target)
                return m + 1;
            else
                l = m + 1;
        }
        else
        {
            if (m == l || nums[m - 1] < target)
                return m;
            else
                r = m - 1;
        }
    }
    return -1;
}

// 53. Maximum Subarray
// Find the contiguous subarray within an array (containing at least one number)
// which has the largest sum.
// For example, given the array[-2, 1, -3, 4, -1, 2, 1, -5, 4],
// the contiguous subarray[4, -1, 2, 1] has the largest sum = 6.
// @array, @linear
static int maxSubArray(vector<int> &nums)
{
    long long minSum = 0;
    long long sum = 0;
    long long delta = INT_MIN;
    for (size_t i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
        if (sum - minSum >= delta)
            delta = sum - minSum;
        if (sum < minSum)
            minSum = sum;
    }
    return (int)delta; // may overflow
}
// @array, @linear
static int maxSubArray2(vector<int> &nums, int &begin, int &end)
{
    begin = -1;
    end = -1;
    long long delta = INT_MIN;

    int minIndex = -1;
    long long minSum = 0; // sum[0..minIndex]
    long long sum = 0;    // sum[0..i]

    for (size_t i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
        long long d = sum - minSum;
        if (d > delta)
        {
            delta = d;
            begin = minIndex + 1;
            end = i;
        }
        if (d <= 0)
        {
            minSum = sum;
            minIndex = i;
        }
    }
    return (int)delta; // may overflow
}
// @array, @linear
static int maxSubArray3(vector<int> &nums, int &begin, int &end)
{
    begin = -1;
    end = -1;
    long long delta = INT_MIN;

    if (nums.empty())
        return (int)delta;

    // Track the last maximum sum so far
    begin = 0;
    end = 0;
    delta = 0;

    // Track the current streak
    int l = 0;   // Beginning
    long long c = 0;   // Cumulative sum up to current element
    int max = 0; // The index of the maximum element seen so far

    for (int i = 0; i < (int)nums.size(); i++)
    {
        c += nums[i];

        if (c > delta)
        {
            // Current element is positive and the current sum is larger than the last one.
            // Update the last seen maximum sum
            begin = l;
            end = i;
            delta = c;
        }
        else if (c <= 0)
        {
            // Current element is negative and everything cancel out
            // Reset and start from the next element
            l = i + 1;
            c = 0;
        }

        // Record the max element so far
        if (nums[i] > nums[max])
            max = i;
    }

    if (delta <= 0)
    {
        // All elements are zero or negative
        // Return the maximum element
        begin = max;
        end = max;
        delta = nums[max];
    }

    return (int)delta;
}

namespace Permutation
{
// 31. Next Permutation
// Implement next permutation, which rearranges numbers into
// the lexicographically next greater permutation of numbers.
// If such arrangement is not possible, it must rearrange it
// as the lowest possible order(ie, sorted in ascending order).
// The replacement must be in-place, do not allocate extra memory.
// Here are some examples. Inputs are in the left-hand column
// and its corresponding outputs are in the right-hand column.
// 1, 2, 3 -> 1, 3, 2
// 3, 2, 1 -> 1, 2, 3
// 1, 1, 5 -> 1, 5, 1
// @array, @permutation
static void next(vector<int> &nums)
{
    if (nums.size() < 2)
        return;
    size_t i = nums.size() - 1;
    while (1 <= i && nums[i - 1] >= nums[i])
        i--;
    size_t j = i;
    size_t k = nums.size() - 1;
    while (j < k)
        swap(nums[j++], nums[k--]);
    if (1 <= i)
    {
        j = i;
        while (j < nums.size() && nums[i - 1] >= nums[j])
            j++;
        if (j < nums.size())
            swap(nums[i - 1], nums[j]);
    }
}

// @array, @permutation, @binarysearch
static void next2(vector<int> &nums)
{
    if (nums.size() < 2)
        return;
    size_t i = nums.size() - 1;
    while (1 <= i && nums[i - 1] >= nums[i])
        i--;
    size_t j = i;
    size_t k = nums.size() - 1;
    while (j < k)
        swap(nums[j++], nums[k--]);
    if (1 <= i)
    {
        j = i;
        k = nums.size() - 1;
        while (j <= k)
        {
            size_t m = j + ((k - j) >> 1);
            if (nums[i - 1] >= nums[m])
            {
                if (nums[i - 1] < nums[m + 1])
                {
                    swap(nums[i - 1], nums[m + 1]);
                    break;
                }
                else
                {
                    j = m + 1;
                }
            }
            else
            {
                if (m == j || nums[i - 1] >= nums[m - 1])
                {
                    swap(nums[i - 1], nums[m]);
                    break;
                }
                else
                {
                    k = m - 1;
                }
            }
        }
    }
}

// 46. Permutations
// Given a collection of distinct numbers, return all possible permutations.
// For example,
//   [1, 2, 3] have the following permutations :
// [
//   [1, 2, 3],
//   [1, 3, 2],
//   [2, 1, 3],
//   [2, 3, 1],
//   [3, 1, 2],
//   [3, 2, 1]
// ]
// @array, @permutation, @recurse
static vector<vector<int>> permuteDistinct(vector<int> &nums)
{
    vector<vector<int>> result = vector<vector<int>>{};
    function<void(size_t, vector<int> &)>
        solve = [&](size_t i, vector<int> &n) {
            if (i == nums.size())
            {
                result.push_back(n);
                return;
            }
            for (size_t j = i; j < nums.size(); j++)
            {
                vector<int> n1(n);
                swap(n1[i], n1[j]);
                solve(i + 1, n1);
            }
        };
    solve(0, nums);
    return result;
}
// @array, @permutation, @recurse
static vector<vector<int>> permuteDistinct2(vector<int> &nums)
{
    vector<vector<int>> result = vector<vector<int>>{};
    function<void(size_t, vector<int> &)>
        solve = [&](size_t i, vector<int> &n) {
            if (i == nums.size())
            {
                result.push_back(n);
                return;
            }
            for (size_t j = i; j < nums.size(); j++)
            {
                vector<int> n1(n);
                if (j > i)
                {
                    // Erase and insert, which effectively push m[i] one more positin to the right.
                    // This way keeps the lexicographical order.
                    int t = n1[j];
                    n1.erase(n1.begin() + j);
                    n1.insert(n1.begin() + i, t);
                }
                solve(i + 1, n1);
            }
        };
    solve(0, nums);
    return result;
}

// 47. Permutations II
// Given a collection of numbers that might contain duplicates, return all possible unique permutations.
// For example,
// [1, 1, 2] have the following unique permutations :
// [
//   [1, 1, 2],
//   [1, 2, 1],
//   [2, 1, 1]
// ]
// @array, @permutation, @recurse
static vector<vector<int>> permuteUnique(vector<int> &nums)
{
    vector<vector<int>> result = vector<vector<int>>{};
    function<void(size_t, vector<int> &)>
        solve = [&](size_t i, vector<int> &n) {
            if (i == nums.size())
            {
                result.push_back(n);
                return;
            }
            set<int> visited = {};
            for (size_t j = i; j < nums.size(); j++)
            {
                if (visited.find(n[j]) == visited.end())
                {
                    vector<int> n1(n);
                    swap(n1[i], n1[j]);
                    solve(i + 1, n1);
                    visited.insert(n[j]);
                }
            }
        };
    solve(0, nums);
    return result;
}
} // namespace Permutation

namespace Combination
{
// 39. Combination Sum
// Given a set of candidate numbers (C) (without duplicates) and a
// target number (T), find all unique combinations in C where the
// candidate numbers sums to T. The same repeated number may be chosen
// from C unlimited number of times.
// Note:
// All numbers (including target) will be positive integers.
// The solution set must not contain duplicate combinations.
// For example, given candidate set [2, 3, 6, 7] and target 7,
// A solution set is :
// [
//    [7],
//    [2, 2, 3]
// ]
// @array, @combination, @recurse
static vector<vector<int>> combinationSumReuse(vector<int> &candidates, int target)
{
    vector<vector<int>> result = vector<vector<int>>{};
    function<void(size_t, int, vector<int> &)>
        solve = [&](size_t i, int t, vector<int> &c) {
            if (i >= candidates.size())
                return;
            if (candidates[i] <= t)
            {
                vector<int> c1(c);
                c1.push_back(candidates[i]);
                if (candidates[i] == t)
                    result.push_back(c1);
                else
                    solve(i, t - candidates[i], c1);
            }
            solve(i + 1, t, c);
        };
    vector<int> s;
    solve(0, target, s);
    return result;
}
// @array, @combination, @recurse
static vector<vector<int>> combinationSumReuse2(vector<int> &candidates, int target)
{
    vector<vector<int>> result = vector<vector<int>>{};
    sort(candidates.begin(), candidates.end());
    function<void(int, int, vector<int> &)>
        solve = [&](int i, int t, vector<int> &s) {
            for (int j = i; j < (int)candidates.size(); j++)
            {
                if (candidates[j] > t)
                    break;
                vector<int> r(s);
                r.push_back(candidates[j]);
                if (candidates[j] == t)
                {
                    result.push_back(r);
                    break;
                }
                solve(j, t - candidates[j], r);
            }
        };
    vector<int> s;
    solve(0, target, s);
    return result;
}
// @array, @combination, @recurse, @dynamicprogramming
static vector<vector<int>> combinationSumReuse3(vector<int> &candidates, int target)
{
    sort(candidates.begin(), candidates.end());
    map<pair<int, int>, vector<vector<int>>> m;
    function<void(int, int)> solve = [&](int i, int t) {
        pair<int, int> p = make_pair(i, t);
        if (m.find(p) != m.end())
            return;
        m[p] = vector<vector<int>>{};
        for (int j = i; j < (int)candidates.size(); j++)
        {
            if (candidates[j] > t)
                break;
            if (candidates[j] == t)
            {
                m[p].push_back(vector<int>{candidates[j]});
                break;
            }
            int d = t - candidates[j];
            solve(j, d);
            pair<int, int> p1 = make_pair(j, d);
            for_each(m[p1].begin(), m[p1].end(), [&](vector<int> &s) {
                vector<int> r(s);
                r.insert(r.begin(), candidates[j]);
                m[p].push_back(r);
            });
        }
    };
    solve(0, target);
    return m[make_pair(0, target)];
}

// 40. Combination Sum II
// Given a collection of candidate numbers (C) and a target number (T),
// find all unique combinations in C where the candidate numbers sums
// to T. Each number in C may only be used once in the combination.
// Note:
// All numbers (including target) will be positive integers.
// The solution set must not contain duplicate combinations.
// For example, given candidate set[10, 1, 2, 7, 6, 1, 5] and target 8,
// A solution set is :
// [
//    [1, 7],
//    [1, 2, 5],
//    [2, 6],
//    [1, 1, 6]
// ]
// @array, @combination, @recurse
static vector<vector<int>> combinationSumNoReuse(vector<int> &candidates, int target)
{
    vector<vector<int>> result = vector<vector<int>>{};
    // Sort so we can eliminate duplicate solutions later
    std::sort(candidates.begin(), candidates.end());
    function<void(size_t, int, vector<int> &)>
        solve = [&](size_t i, int t, vector<int> &c) {
            if (i >= candidates.size() || candidates[i] > t)
                return;
            vector<int> c1(c);
            c1.push_back(candidates[i]);
            if (candidates[i] == t)
            {
                result.push_back(c1);
                return;
            }
            solve(i + 1, t - candidates[i], c1);
            while (i + 1 < candidates.size() && candidates[i] == candidates[i + 1])
            {
                // This is needed to eliminate duplicate solutions
                i++;
            }
            solve(i + 1, t, c);
        };
    vector<int> s;
    solve(0, target, s);
    return result;
}
// @array, @combination, @recurse
static vector<vector<int>> combinationSumNoReuse2(vector<int> &candidates, int target)
{
    vector<vector<int>> result = vector<vector<int>>{};
    // Sort so we can eliminate duplicate solutions later
    std::sort(candidates.begin(), candidates.end());
    function<void(size_t, int, vector<int> &)>
        solve = [&](size_t i, int t, vector<int> &c) {
            if (i >= candidates.size() || candidates[i] > t)
                return;
            size_t j = i;
            while (j + 1 < candidates.size() && candidates[j] == candidates[j + 1])
                j++;
            int s = 0;
            for (size_t k = i; k <= j; k++)
            {
                s += candidates[k];
                if (s > t)
                    break;
                vector<int> c1(c);
                c1.insert(c1.end(), k - i + 1, candidates[i]);
                if (s == t)
                {
                    result.push_back(c1);
                    break;
                }
                solve(j + 1, t - s, c1);
            }
            solve(j + 1, t, c);
        };
    vector<int> s;
    solve(0, target, s);
    return result;
}
} // namespace Combination

namespace LengthOfLongestSubstring
{
// 3. Longest Substring Without Repeating Characters
// Given a string, find the length of the longest substring without repeating characters.
// "abcabcbb" -> "abc"
// "bbbbb" -> "b"
// "pwwkew" -> "wke"
// @string, @hash
static int solve1(string s)
{
    map<char, int> m;
    int l = 0;
    int i = 0;
    int j = 0;
    for (j = 0; j < (int)s.size(); j++)
    {
        if (m.find(s[j]) != m.end())
        {
            l = max(l, j - i);
            while (i <= m[s[j]])
            {
                m.erase(s[i]);
                i++;
            }
        }
        m[s[j]] = j;
    }
    l = max(l, j - i);
    return l;
}
// @string, @set
static int solve2(string s)
{
    set<char> chars;
    int i = 0;
    int l = 0;
    int j = 0;
    for (j = 0; j < (int)s.size(); j++)
    {
        if (chars.find(s[j]) == chars.end())
            chars.insert(s[j]);
        else
        {
            l = max(l, j - i);
            while (s[i] != s[j])
            {
                chars.erase(s[i]);
                i++;
            }
            i++;
        }
    }
    l = max(l, j - i);
    return l;
}
} // namespace LengthOfLongestSubstring

namespace LongestPalindrome
{
// 5. Longest Palindromic Substring
// Assume the max length is 1000.
// "babad" -> "bab" or "aba"
// "cbbd" -> "bb"
// @string, @bruteforce
static string solve1(string s)
{
    function<pair<int, int>(int, int)> expand =
        [&](int l, int r) -> pair<int, int> {
        while (0 <= l && r < (int)s.size() && s[l] == s[r])
        {
            l--;
            r++;
        }
        return make_pair(l + 1, r - 1);
    };
    int begin = 0, end = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        auto p = expand(i, i);
        if (p.second - p.first > end - begin)
        {
            begin = p.first;
            end = p.second;
        }
        if (i < (int)s.size() - 1)
        {
            p = expand(i, i + 1);
            if (p.second - p.first > end - begin)
            {
                begin = p.first;
                end = p.second;
            }
        }
    }
    return s.substr(begin, end - begin + 1);
}
// @string, @dynamicprogramming
static string solve2(string s)
{
    vector<vector<int>> len(2, vector<int>(s.size(), 1));
    int begin = 0, end = 0;
    for (size_t i = 0; i + 1 < s.size(); i++)
    {
        if (s[i] == s[i + 1])
        {
            len[1][i] = 2;
            if (2 > end - begin + 1)
            {
                begin = i;
                end = i + 1;
            }
        }
    }
    for (int l = 3; l <= (int)s.size(); l++)
    {
        int v = ((l & 0x1) == 1 ? 0 : 1);
        for (size_t i = 0; i + l - 1 < s.size(); i++)
        {
            if (s[i] == s[i + l - 1] && len[v][i + 1] == l - 2)
            {
                // s[i..(i + l - 1)] is a palindrome of length l, if
                // (1) s[i] == s[i + l - 1], and
                // (2) s[(i + 1)..(i + l - 2)] is a palindrome (of length (l - 2))
                len[v][i] = l;
                if (l > end - begin + 1)
                {
                    begin = i;
                    end = i + l - 1;
                }
            }
        }
    }
    return s.substr(begin, end - begin + 1);
}
// @string, @linear
static string solve3(string s)
{
    if (s.empty())
        return s;
    auto getChar = [&](int i) -> char {
        if ((i & 0x1) == 0)
            return '#';
        return s[i >> 1];
    };
    int n = (s.size() << 1) + 1;
    auto expand = [&](int c, int &l) {
        while (true)
        {
            int i = c - l;
            int j = c + l;
            if (i - 1 >= 0 && j + 1 < n && getChar(i - 1) == getChar(j + 1))
                l++;
            else
                break;
        }
    };
    vector<int> l(n, 0);
    int c = 0, r = 0;
    int mi = 0, ml = 0;
    int i = 0;
    while (i < n)
    {
        if (i < r)
        {
            int j = (c << 1) - i;
            l[i] = min(l[j], r - i);
            if (i + l[i] < r)
            {
                i++;
                continue;
            }
        }
        expand(i, l[i]);
        if (i + l[i] >= r)
        {
            c = i;
            r = i + l[i];
        }
        if (l[i] > ml)
        {
            mi = i;
            ml = l[i];
        }
        i++;
    }
    return s.substr((mi - ml) >> 1, ml);
}
} // namespace LongestPalindrome

// 6. ZigZag Conversion
// "PAYPALISHIRING"
// P   A   H   N
// A P L S I I G
// Y   I   R
// "PAHNAPLSIIGYIR"
// @string
static string convert(string s, int numRows)
{
    string output;
    int len = s.size();
    int delta = numRows == 1 ? 1 : (numRows << 1) - 2;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < len; j += delta)
        {
            if (j + i < len)
                output.append(1, s[j + i]);
            if (i != 0 && i != (numRows - 1) && (j + delta - i < len))
                output.append(1, s[j + delta - i]);
        }
    }
    return output;
}

// 7. Reverse Integer
// 123 => 321
// -123 => -321
// 120 => 21
// Assume 32-bit int. Return 0 if overflow.
// @numeric
static int reverse(int x)
{
    bool negative = false;
    if (x < 0)
    {
        negative = true;
        x = -x;
    }
    long r = 0;
    while (x > 0)
    {
        int d = x % 10;
        x = x / 10;
        r = r * 10 + d;
        if ((negative && -r < INT_MIN) || r > INT_MAX)
            return 0;
    }
    return negative ? -r : r;
}

namespace AToI
{
// 8. String to Integer (atoi)
// The function first discards as many whitespace characters as necessary until
// the first non-whitespace character is found. Then, takes an optional initial
// plus or minus sign followed by as many numerical digits as possible, and
// convert them as an integer. Any additional characters after those will be
// ignored. If the first sequence of non-whitespace characters in the input is not
// a valid integer, or the input is empty, or the input contains only whitespaces,
// then no conversion is performed, and a zero value is returned.
// If overflow, then INT_MIN (-2147483648) or INT_MAX(2147483647) is returned.
// @numeric
static int solve1(string str)
{
    long r = 0;
    bool negative = false;
    bool foundStart = false;
    size_t i = 0;
    while (i < str.length())
    {
        char c = str[i++];
        if (c == '+' || c == '-')
        {
            if (foundStart)
                break;
            foundStart = true;
            negative = (c == '-');
        }
        else if ('0' <= c && c <= '9')
        {
            if (!foundStart)
                foundStart = true;

            r = r * 10 + c - '0';
            if (negative && -r <= INT_MIN)
                return INT_MIN;
            else if (!negative && r >= INT_MAX)
                return INT_MAX;
        }
        else if (c == ' ')
        {
            if (foundStart)
                break;
        }
        else
            break;
    }
    return negative ? -r : r;
}
// @numeric
static int solve2(string str)
{
    size_t i = 0;
    while (i < str.length() && str[i] == ' ')
        i++;
    if (i == str.length())
        return 0;
    bool negative = false;
    if (str[i] == '+' || str[i] == '-')
    {
        negative = (str[i++] == '-');
    }
    if (i == str.length() || str[i] < '0' || str[i] > '9')
        return 0;
    long r = 0;
    while (i < str.length() && '0' <= str[i] && str[i] <= '9')
    {
        r = r * 10 + str[i++] - '0';
        if (negative && -r <= INT_MIN)
            return INT_MIN;
        else if (!negative && r >= INT_MAX)
            return INT_MAX;
    }
    return negative ? -r : r;
}
} // namespace AToI

// 9. Palindrome Number
// Determine whether an integer is a palindrome. Do this without extra space.
static bool isPalindrome(int x)
{
    if (x < 0)
        return false;
    long long y = x;
    long long d = 1;
    while (y >= 10 * d)
    {
        d *= 10;
    }

    int l = 0;
    int r = 0;
    while (y > 0)
    {
        l = y >= d ? (y / d) : 0;
        r = y % 10;
        if (l != r)
            return false;
        y = (y % d) / 10;
        d /= 100;
    }
    return true;
}

// 155. Min Stack
// Design a stack that supports push, pop, top, and retrieving
// the minimum element in constant time.
// push(x) --  Push element x onto stack.
// pop()   --  Removes the element on top of the stack.
// top()   --  Get the top element.
// getMin() -- Retrieve the minimum element in the stack.
// Example:
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin();   --> Returns -3.
// minStack.pop();
// minStack.top();      --> Returns 0.
// minStack.getMin();   --> Returns -2.
class MinStack
{
  private:
    stack<int> _items;
    stack<int> _mins;

  public:
    // initialize your data structure here.
    MinStack() {}

    void push(int x)
    {
        _items.push(x);
        if (!_mins.empty())
            x = min(_mins.top(), x);
        _mins.push(x);
    }

    void pop()
    {
        _items.pop();
        _mins.pop();
    }

    int top() { return _items.top(); }

    int getMin() { return _mins.top(); }
};

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 2. Add Two Numbers
// Given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order (LSB is the head) and each node contain
// a single digit. Add the two numbers and return a linked list.
// The two numbers do not contain leading zero, except the number 0 itself.
// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: (7 -> 0 -> 8)
// @list
static ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    if (l1 == nullptr)
        return l2;
    if (l2 == nullptr)
        return l1;
    ListNode *l = nullptr;
    ListNode *n = nullptr;
    int c = 0;
    while (l1 != nullptr || l2 != nullptr || c == 1)
    {
        int v = c;
        if (l1 != nullptr)
        {
            v += l1->val;
            l1 = l1->next;
        }
        if (l2 != nullptr)
        {
            v += l2->val;
            l2 = l2->next;
        }
        if (v >= 10)
        {
            v -= 10;
            c = 1;
        }
        else
            c = 0;
        if (l == nullptr)
        {
            l = new ListNode(v);
            n = l;
        }
        else
        {
            n->next = new ListNode(v);
            n = n->next;
        }
    }
    return l;
}
} // namespace LeetCode
} // namespace Test

#endif