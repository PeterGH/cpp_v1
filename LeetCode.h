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

// 88. Merge Sorted Array
// Given two sorted integer arrays nums1 and nums2, merge nums2 into
// nums1 as one sorted array. Note: You may assume that nums1 has enough
// space(size that is greater or equal to m + n) to hold additional elements
// from nums2. The number of elements initialized in nums1 and nums2
// are m and n respectively.
// @array, @merge
// Another solution: shift elements in nums1 to the end, and then merge
// with nums2 starting from the beginning of nums1.
static void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    vector<int>::iterator it1 = nums1.begin();
    vector<int>::iterator it2 = nums2.begin();
    // No need for these two
    int i = 0;
    int j = 0;
    while (i < m || j < n)
    {
        if (i < m && j < n)
        {
            if (*it1 <= *it2)
            {
                it1++;
                i++;
            }
            else
            {
                it1 = nums1.insert(it1, *it2);
                it1++;
                it2 = nums2.erase(it2);
                j++;
            }
        }
        else if (j < n)
        {
            it1 = nums1.insert(it1, *it2);
            it1++;
            it2 = nums2.erase(it2);
            j++;
        }
        else
        {
            it1++;
            i++;
        }
    }
    while (it1 != nums1.end()) // Why need this?
        it1 = nums1.erase(it1);
}

// 26. Remove Duplicates from Sorted Array
// Given a sorted array, remove the duplicates in place such that each
// element appear only once and return the new length. Do not allocate extra
// space for another array, you must do this in place with constant memory.
// For example, Given input array nums = [1, 1, 2], Your function should return
// length = 2, with the first two elements of nums being 1 and 2 respectively.
// It does not matter what you leave beyond the new length.
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

// 80. Remove Duplicates from Sorted Array II
// Follow up for "Remove Duplicates": What if duplicates are allowed at most
// twice? For example, Given sorted array nums = [1, 1, 1, 2, 2, 3], Your
// function should return length = 5, with the first five elements of nums
// being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.
// @array, @linear
static int removeDuplicates2(vector<int> &nums)
{
    int i = -1;
    int j = 0;
    while (j < (int)nums.size())
    {
        // Find the first instance of next number (at j)
        if (0 <= j - 1 && nums[j] == nums[j - 1])
        {
            j++;
            continue;
        }
        // Move nums[j] ahead
        i++;
        if (i < j)
            nums[i] = nums[j];
        if (j + 1 < (int)nums.size() && nums[j] == nums[j + 1])
        {
            // Move the second instance of next number (at j + 1) ahead
            i++;
            if (i < j + 1)
                nums[i] = nums[j + 1];
            j += 2;
        }
        else
        {
            // next number has only one instance
            j++;
        }
    }
    return i + 1;
}
// This is wrong. For input [1, 1, 1, 2, 2, 3], output is [1, 1, 2, 3]
static int removeDuplicates2_1(vector<int> &nums)
{
    if (nums.size() < 3)
        return nums.size();
    int i = 1;
    for (int j = 2; j < (int)nums.size(); j++)
    {
        if (nums[j] == nums[j - 1] && nums[j] == nums[j - 2])
        {
            continue;
        }
        i++;
        if (i < j)
        {
            nums[i] = nums[j];
        }
    }
    return i + 1;
}

// 27. Remove Element
// Given an array and a value, remove all instances of that value in
// place and return the new length. Do not allocate extra space for
// another array, you must do this in place with constant memory.
// The order of elements cannot be changed. It does not matter what you
// leave beyond the new length. Example: Given input array nums = [3, 2, 2, 3],
// val = 3. Your function should return length = 2, with the first two
// elements of nums being 2.
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
// leave beyond the new length. Example: Given input array nums = [3, 2, 2, 3],
// val = 3. Your function should return length = 2, with the first two elements
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

// 81. Search in Rotated Sorted Array II
// Follow up for "Search in Rotated Sorted Array": What if duplicates are allowed?
// Would this affect the run - time complexity? How and why? Suppose an array
// sorted in ascending order is rotated at some pivot unknown to you beforehand.
// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2). Write a function to
// determine if a given target is in the array. The array may contain duplicates.
static bool search2(vector<int> &nums, int target)
{
    if (nums.size() == 0)
        return false;
    function<bool(int, int)>
        search = [&](int l, int r) -> bool {
        if (l > r)
            return false;
        int m = l + ((r - l) >> 1);
        if (nums[m] == target)
            return true;
        if (nums[m] < target)
        {
            if (nums[0] < nums[m])
                return search(m + 1, r);
            if (target < nums[r])
                return search(m + 1, r);
        }
        else
        {
            if (nums[l] < target)
                return search(l, m - 1);
            if (nums[m] < nums[nums.size() - 1])
                return search(l, m - 1);
        }
        if (search(l, m - 1))
            return true;
        return search(m + 1, r);
    };
    return search(0, nums.size() - 1);
}

// 153. Find Minimum in Rotated Sorted Array
// Suppose an array sorted in ascending order is rotated at some pivot unknown
// to you beforehand. (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2). Find
// the minimum element. You may assume no duplicate exists in the array.
static int findMin(vector<int> &nums)
{
    int l = 0;
    int h = nums.size() - 1;
    int m;
    while (l <= h)
    {
        m = l + ((h - l) >> 1);
        if (nums[l] < nums[m])
        {
            if (nums[m] < nums[h])
            {
                h = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        else if (nums[l] > nums[m])
        {
            h = m;
        }
        else
        {
            if (nums[m] < nums[h])
            {
                h = m;
            }
            else if (nums[m] > nums[h])
            {
                l = m + 1;
            }
            else
            {
                break;
            }
        }
    }
    return nums[m];
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

// 162. Find Peak Element
// A peak element is an element that is greater than its neighbors.
// Given an input array where num[i] != num[i + 1], find a peak element
// and return its index. The array may contain multiple peaks, in that case
// return the index to any one of the peaks is fine. You may imagine that
// num[-1] = num[n] = negative infinity. For example, in array[1, 2, 3, 1],
// 3 is a peak element and your function should return the index number 2.
// Note: Your solution should be in logarithmic complexity.
// @array, @binarysearch
static int findPeakElement(vector<int> &nums)
{
    int l = 0;
    int h = nums.size() - 1;
    int m;
    while (l <= h)
    {
        m = l + ((h - l) >> 1);
        if (m == h)
        {
            return m;
        }
        else if (l == m)
        {
            if (nums[m] <= nums[m + 1])
            {
                l = m + 1;
            }
            else
            {
                return m;
            }
        }
        else
        {
            if (nums[m - 1] < nums[m] && nums[m] > nums[m + 1])
            {
                return m;
            }
            else if (nums[m - 1] <= nums[m + 1])
            {
                l = m + 1;
            }
            else
            {
                h = m - 1;
            }
        }
    }
    throw AssertError("No result");
}

// 121. Best Time to Buy and Sell Stock
// Say you have an array for which the i-th element is the price of a given
// stock on day i. If you were only permitted to complete at most one
// transaction (ie, buy one and sell one share of the stock), design an
// algorithm to find the maximum profit. Example 1: Input: [7, 1, 5, 3, 6, 4],
// Output : 5, max.difference = 6 - 1 = 5 (not 7 - 1 = 6, as selling price needs
// to be larger than buying price) Example 2 : Input : [7, 6, 4, 3, 1],
// Output : 0, In this case, no transaction is done, i.e.max profit = 0.
static int maxProfit(vector<int> &prices)
{
    if (prices.empty())
        return 0;
    int min = prices[0];
    int profit = 0;
    for (size_t i = 1; i < prices.size(); i++)
    {
        if (prices[i] - min > profit)
        {
            profit = prices[i] - min;
        }
        else if (prices[i] < min)
        {
            min = prices[i];
        }
    }
    return profit;
}

// 122. Best Time to Buy and Sell Stock II
// Say you have an array for which the ith element is the price of a given
// stock on day i. Design an algorithm to find the maximum profit. You may
// complete as many transactions as you like (ie, buy one and sell one share
// of the stock multiple times). However, you may not engage in multiple
// transactions at the same time (ie, you must sell the stock before you buy
// again).
static int maxProfit2(vector<int> &prices)
{
    if (prices.empty())
        return 0;
    int profit = 0;
    for (size_t i = 1; i < prices.size(); i++)
    {
        if (prices[i] > prices[i - 1])
        {
            profit += (prices[i] - prices[i - 1]);
        }
    }
    return profit;
}

// 169. Majority Element
// Given an array of size n, find the majority element. The majority element is
// the element that appears more than ⌊ n/2 ⌋ times. You may assume that the
// array is non-empty and the majority element always exist in the array.
static int majorityElement(vector<int> &nums)
{
    map<int, int> m;
    for (size_t i = 0; i < nums.size(); i++)
    {
        if (m.find(nums[i]) == m.end())
        {
            m[nums[i]] = 1;
        }
        else
        {
            m[nums[i]]++;
        }
        if (m[nums[i]] > (int)nums.size() / 2)
        {
            return nums[i];
        }
    }
    throw AssertError("No result");
}

// 53. Maximum Subarray
// Find the contiguous subarray within an array (containing at least one number)
// which has the largest sum. For example, given the array [-2, 1, -3, 4, -1, 2,
// 1, -5, 4], the contiguous subarray[4, -1, 2, 1] has the largest sum = 6.
// @array, @linear
static int maxSubArray(vector<int> &nums)
{
    // Another option could be to init minSum and sum to nums[0]
    // and loop start at 1
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
    int l = 0;       // Beginning
    long long c = 0; // Cumulative sum up to current element
    int max = 0;     // The index of the maximum element seen so far

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

// 152. Maximum Product Subarray
// Find the contiguous subarray within an array (containing at least one number)
// which has the largest product. For example, given the array[2, 3, -2, 4],
// the contiguous subarray[2, 3] has the largest product = 6.
static int maxProduct(vector<int> &nums)
{
    long long maxProd = LLONG_MIN;
    vector<long long> product(nums.begin(), nums.end());
    for (size_t l = 1; l <= nums.size(); l++)
    {
        for (size_t i = 0; i <= nums.size() - l; i++)
        {
            if (l > 1)
            {
                product[i] *= nums[i + l - 1];
            }
            maxProd = max(product[i], maxProd);
        }
    }
    return (int)maxProd;
}
static int maxProduct2(vector<int> &nums)
{
    long long maxNegative = LLONG_MIN;
    long long maxProd = LLONG_MIN;
    long long prod = 1;
    for (size_t i = 0; i < nums.size(); i++)
    {
        prod *= nums[i];
        if (prod < 0)
        {
            if (maxNegative == LLONG_MIN)
            {
                maxProd = max(maxProd, prod);
            }
            else
            {
                maxProd = max(maxProd, prod / maxNegative);
            }
            maxNegative = max(maxNegative, prod);
        }
        else if (prod > 0)
        {
            maxProd = max(maxProd, prod);
        }
        else
        {
            maxProd = max(maxProd, prod);
            maxNegative = LLONG_MIN;
            prod = 1;
        }
    }
    return (int)maxProd;
}

// 55. Jump Game
// Given an array of non-negative integers, you are initially positioned at
// the first index of the array. Each element in the array represents your
// maximum jump length at that position. Determine if you are able to reach
// the last index. For example : A = [2, 3, 1, 1, 4], return true.
// A = [3, 2, 1, 0, 4], return false.
// @array, @linear
static bool canJump(vector<int> &nums)
{
    if (nums.empty())
        return false;
    int index = nums.size() - 1;
    for (int i = nums.size() - 2; i >= 0; i--)
    {
        if (i + nums[i] >= index)
            index = i;
    }
    return index == 0;
}
// @array, @linear
static bool canJump2(vector<int> &nums)
{
    if (nums.empty())
        return false;
    size_t index = 0;
    size_t i = 0;
    while (i < nums.size() && i <= index)
    {
        index = max(index, i + nums[i]);
        i++;
    }
    return index >= nums.size() - 1;
}

// 70. Climbing Stairs
// You are climbing a stair case. It takes n steps to reach to the top. Each
// time you can either climb 1 or 2 steps. In how many distinct ways can you
// climb to the top? Note : Given n will be a positive integer.
// C[n] = C[n - 1] + C[n - 2]
// Another option is C[i] = C[i + 1] + C[i + 2], where C[n] = 0, C[n - 1] = 1,
// C[n - 2] = 2, C[n - 3] = 3, ..., C[1] = ?
// @array, @dynamicprogramming
static int climbStairs(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    int a = 1;
    int b = 2;
    int c;
    for (int i = 3; i <= n; i++)
    {
        c = b + a;
        a = b;
        b = c;
    }
    return c;
}

// 198. House Robber
// You are a professional robber planning to rob houses along a street. Each
// house has a certain amount of money stashed, the only constraint stopping
// you from robbing each of them is that adjacent houses have security system
// connected and it will automatically contact the police if two adjacent houses
// were broken into on the same night. Given a list of non-negative integers
// representing the amount of money of each house, determine the maximum amount
// of money you can rob tonight without alerting the police.
// [Why not just count the odd houses and the even houses?
// Doesn't work, e.g. [3, 1, 1, 3]]
static int rob(vector<int> &nums)
{
    int a = 0; // max at i - 2
    int b = 0; // max at i - 1
    int c;     // max at i
    for (size_t i = 0; i < nums.size(); i++)
    {
        c = max(a + nums[i], b);
        a = b;
        b = c;
    }
    return b;
}

// 134. Gas Station
// There are N gas stations along a circular route, where the amount of gas at
// station i is gas[i]. You have a car with an unlimited gas tank and it costs
// cost[i] of gas to travel from station i to its next station(i + 1). You begin
// the journey with an empty tank at one of the gas stations. Return the starting
// gas station's index if you can travel around the circuit once, otherwise
// return -1. Note: The solution is guaranteed to be unique.
static int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    size_t s = 0;
    while (s < gas.size())
    {
        size_t i = s;
        int t = 0;
        size_t j;
        while (t >= 0 && (i - s) < gas.size())
        {
            j = (i++) % gas.size();
            t += (gas[j] - cost[j]);
        }
        if (t >= 0)
            return s;
        s = i;
    }
    return -1;
}

// 136. Single Number
// Given an array of integers, every element appears twice except for one.
// Find that single one. Note: Your algorithm should have a linear runtime
// complexity. Could you implement it without using extra memory?
static int singleNumber(vector<int> &nums)
{
    int n = 0;
    for_each(nums.begin(), nums.end(), [&](int e) {
        n ^= e;
    });
    return n;
}

// 66. Plus One
// Given a non-negative integer represented as a non-empty array of digits,
// plus one to the integer. You may assume the integer do not contain any
// leading zero, except the number 0 itself. The digits are stored such that
// the most significant digit is at the head of the list.
// @array, @linear
static vector<int> plusOne(vector<int> &digits)
{
    vector<int> result(digits);
    int c = 1;
    for (int i = result.size() - 1; i >= 0; i--)
    {
        result[i] += c;
        if (result[i] >= 10)
        {
            c = 1;
            result[i] -= 10;
        }
        else
        {
            c = 0;
            break;
        }
    }
    if (c == 1)
    {
        result.insert(result.begin(), c);
    }
    return result;
}

// 75. Sort Colors
// Given an array with n objects colored red, white or blue, sort them so that
// objects of the same color are adjacent, with the colors in the order red,
// white and blue. Here, we will use the integers 0, 1, and 2 to represent the
// color red, white, and blue respectively. Note: You are not suppose to use
// the library's sort function for this problem.
static void sortColors(vector<int> &nums)
{
    if (nums.size() == 0)
        return;
    int i = -1;
    int j = 0;
    int k = nums.size();
    while (j < k)
    {
        if (nums[j] == 0)
        {
            if (i < j)
            {
                i++;
                swap(nums[i], nums[j]);
            }
            else
            {
                j++;
            }
        }
        else if (nums[j] == 2)
        {
            if (j < k)
            {
                k--;
                swap(nums[j], nums[k]);
            }
            else
            {
                j++;
            }
        }
        else
        {
            j++;
        }
    }
}

// 56. Merge Intervals
// Given a collection of intervals, merge all overlapping intervals. For example,
// Given[1, 3], [2, 6], [8, 10], [15, 18], return[1, 6], [8, 10], [15, 18].
struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
// @array, @linear
static vector<Interval> merge(vector<Interval> &intervals)
{
    function<bool(const Interval &, const Interval &)>
        less = [&](const Interval &first, const Interval &second) -> bool {
        if (first.start == second.start)
            return first.end < second.end;
        return first.start < second.start;
    };
    vector<Interval> result = vector<Interval>{};
    if (intervals.size() == 0)
        return result;
    sort(intervals.begin(), intervals.end(), less);
    Interval v = intervals[0];
    for (size_t i = 1; i < intervals.size(); i++)
    {
        if (v.start <= intervals[i].end && intervals[i].start <= v.end)
        {
            v.start = min(v.start, intervals[i].start);
            v.end = max(v.end, intervals[i].end);
        }
        else
        {
            result.push_back(v);
            v = intervals[i];
        }
    }
    result.push_back(v);
    return result;
}

namespace Permutation
{
// 31. Next Permutation
// Implement next permutation, which rearranges numbers into the lexicographically
// next greater permutation of numbers. If such arrangement is not possible, it
// must rearrange it as the lowest possible order (ie, sorted in ascending order).
// The replacement must be in-place, do not allocate extra memory. Here are some
// examples. Inputs are in the left-hand column and its corresponding outputs are
// in the right-hand column.
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
// For example, [1, 2, 3] have the following permutations :
// [[1, 2, 3],
//  [1, 3, 2],
//  [2, 1, 3],
//  [2, 3, 1],
//  [3, 1, 2],
//  [3, 2, 1]]
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
                    // Erase and insert, which effectively push ns[i] one more
                    // positin to the right. This way keeps the lexicographical
                    // order.
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
// Given a collection of numbers that might contain duplicates, return all
// possible unique permutations. For example,
// [1, 1, 2] have the following unique permutations :
// [[1, 1, 2],
//  [1, 2, 1],
//  [2, 1, 1]]
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

// 60. Permutation Sequence
// The set [1,2,3,...,n] contains a total of n! unique permutations. By listing
// and labeling all of the permutations in order, We get the following sequence
// (ie, for n = 3) :
// "123"
// "132"
// "213"
// "231"
// "312"
// "321"
// Given n and k, return the k-th permutation sequence.
// Note: Given n will be between 1 and 9 inclusive.
static string getPermutation(int n, int k)
{
    if (n <= 0 || k <= 0)
        return string();
    int m = 1;
    string p;
    for (int i = 1; i <= n; i++)
    {
        m *= i;
        p.append(1, '0' + i);
    }
    vector<int> indices = vector<int>{};
    for (int i = n; i >= 1; i--)
    {
        m = m / i;
        indices.push_back(((k - 1) / m + 1));
        k = ((k - 1) % m) + 1;
    }
    for (int i = 0; i < n; i++)
    {
        if (indices[i] > 1)
        {
            int j = i + indices[i] - 1;
            char c = p[j];
            p.erase(j, 1);
            p.insert(i, 1, c);
        }
    }
    return p;
}

} // namespace Permutation

// 189. Rotate Array
// Rotate an array of n elements to the right by k steps. For example, with
// n = 7 and k = 3, the array[1, 2, 3, 4, 5, 6, 7] is rotated to
// [5, 6, 7, 1, 2, 3, 4]. Note: Try to come up as many solutions as you can,
// there are at least 3 different ways to solve this problem.
// Hint: Could you do it in-place with O(1) extra space?
static void rotate(vector<int> &nums, int k)
{
    if (nums.empty())
        return;
    k %= nums.size();
    if (k == 0)
        return;
    function<void(int, int)>
        swapRange = [&](int i, int j) {
            while (i < j)
            {
                swap(nums[i++], nums[j--]);
            }
        };
    swapRange(0, nums.size() - 1);
    swapRange(0, k - 1);
    swapRange(k, nums.size() - 1);
}
// This one works only if n and k are co-prime
static void rotate2(vector<int> &nums, int k)
{
    if (nums.empty())
        return;
    k %= nums.size();
    if (k == 0)
        return;
    size_t i = 0;
    do
    {
        i = (i + k) % nums.size();
        swap(nums[0], nums[i]);
    } while (i != 0);
}

namespace Combination
{
// 39. Combination Sum
// Given a set of candidate numbers (C) (without duplicates) and a target number
// (T), find all unique combinations in C where the candidate numbers sums to T.
// The same repeated number may be chosen from C unlimited number of times.
// Note: All numbers (including target) will be positive integers. The solution
// set must not contain duplicate combinations. For example, given candidate set
// [2, 3, 6, 7] and target 7, A solution set is:
// [[7],
//  [2, 2, 3]]
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
// Given a collection of candidate numbers (C) and a target number (T), find
// all unique combinations in C where the candidate numbers sums to T. Each
// number in C may only be used once in the combination. Note: All numbers
// (including target) will be positive integers. The solution set must not
// contain duplicate combinations. For example, given candidate set
// [10, 1, 2, 7, 6, 1, 5] and target 8, A solution set is:
// [[1, 7],
//  [1, 2, 5],
//  [2, 6],
//  [1, 1, 6]]
// @array, @combination, @recurse
static vector<vector<int>> combinationSumNoReuse(vector<int> &candidates, int target)
{
    vector<vector<int>> result = vector<vector<int>>{};
    // Sort so we can eliminate duplicate solutions later
    // [Can we not use sort? Instead using a set of <i,t> pairs to track the visited?]
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

// 77. Combinations
// Given two integers n and k, return all possible combinations of k numbers out
// of 1 ... n. For example, If n = 4 and k = 2, a solution is:
// [[2, 4],
//  [3, 4],
//  [2, 3],
//  [1, 2],
//  [1, 3],
//  [1, 4]]
// @combination, @recurse
static vector<vector<int>> combine(int n, int k)
{
    vector<vector<int>> result = vector<vector<int>>{};
    if (k <= 0 || n <= 0 || k > n)
        return result;
    function<void(int, int, vector<int> &)>
        select = [&](int i, int l, vector<int> &c) {
            if (l == 0)
            {
                result.push_back(c);
                return;
            }
            for (int j = i; j <= n; j++)
            {
                vector<int> c1(c);
                c1.push_back(j);
                select(j + 1, l - 1, c1);
            }
        };
    vector<int> c = vector<int>{};
    select(1, k, c);
    return result;
}

// 78. Subsets
// Given a set of distinct integers, nums, return all possible subsets. Note:
// The solution set must not contain duplicate subsets. For example,
// If nums = [1, 2, 3], a solution is:
// [[3],
//  [1],
//  [2],
//  [1, 2, 3],
//  [1, 3],
//  [2, 3],
//  [1, 2],
//  []]
static vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> result = vector<vector<int>>{};
    result.push_back(vector<int>{});
    for (size_t i = 0; i < nums.size(); i++)
    {
        size_t n = result.size();
        for (size_t j = 0; j < n; j++)
        {
            vector<int> e(result[j]);
            e.push_back(nums[i]);
            result.push_back(e);
        }
    }
    return result;
}

// 90. Subsets II
// Given a collection of integers that might contain duplicates, nums, return
// all possible subsets. Note: The solution set must not contain duplicate
// subsets. For example, If nums = [1, 2, 2], a solution is:
// [[2],
//  [1],
//  [1, 2, 2],
//  [2, 2],
//  [1, 2],
//  []]
static vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    vector<vector<int>> result = vector<vector<int>>{vector<int>{}};
    if (nums.size() == 0)
        return result;
    sort(nums.begin(), nums.end());
    size_t i = 0;
    while (i < nums.size())
    {
        size_t j = i;
        while (j + 1 < nums.size() && nums[j] == nums[j + 1])
            j++;
        vector<int> c;
        size_t n = result.size();
        for (size_t k = i; k <= j; k++)
        {
            c.push_back(nums[k]);
            for (size_t l = 0; l < n; l++)
            {
                vector<int> e(result[l]);
                e.insert(e.end(), c.begin(), c.end());
                result.push_back(e);
            }
        }
        i = j + 1;
    }
    return result;
}

} // namespace Combination

// 150. Evaluate Reverse Polish Notation
// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
// Valid operators are + , -, *, /. Each operand may be an integer or another
// expression. Some examples :
// ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
// ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
static int evalRPN(vector<string> &tokens)
{
    int n1;
    int n2;
    stack<int> nums;
    function<void(int &, int &)>
        pop = [&](int &m1, int &m2) {
            m2 = nums.top();
            nums.pop();
            m1 = nums.top();
            nums.pop();
        };
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].compare("+") == 0)
        {
            pop(n1, n2);
            nums.push(n1 + n2);
        }
        else if (tokens[i].compare("-") == 0)
        {
            pop(n1, n2);
            nums.push(n1 - n2);
        }
        else if (tokens[i].compare("*") == 0)
        {
            pop(n1, n2);
            nums.push(n1 * n2);
        }
        else if (tokens[i].compare("/") == 0)
        {
            pop(n1, n2);
            nums.push(n1 / n2);
        }
        else
        {
            nums.push(atoi(tokens[i].c_str()));
        }
    }
    return nums.top();
}

// 28. Implement strStr()
// Returns the index of the first occurrence of needle in haystack,
// or -1 if needle is not part of haystack.
// @string, @linear
static int strStr(string haystack, string needle)
{
    if (needle.empty())
        return 0;
    size_t i = 0;
    while (i + needle.size() <= haystack.size())
    {
        while (i + needle.size() <= haystack.size() && haystack[i] != needle[0])
            i++;
        if (i + needle.size() > haystack.size())
            break;
        size_t j = 1;
        while (j < needle.size() && haystack[i + j] == needle[j])
            j++;
        if (j == needle.size())
            return i;
        i++;
    }
    return -1;
}

// 38. Count and Say
// The count-and-say sequence is the sequence of integers beginning as follows:
// 1, 11, 21, 1211, 111221, ...
// 1 is read off as "one 1" or 11.
// 11 is read off as "two 1s" or 21.
// 21 is read off as "one 2, then one 1" or 1211.
// Given an integer n, generate the nth sequence.
// Note: The sequence of integers will be represented as a string.
// @string
static string countAndSay(int n)
{
    if (n <= 0)
        return string();
    string s = "1";
    for (int i = 2; i <= n; i++)
    {
        ostringstream oss;
        size_t j = 0;
        size_t c = 1;
        while (j < s.size())
        {
            while (j + 1 < s.size() && s[j] == s[j + 1])
            {
                j++;
                c++;
            }
            oss << c << s[j];
            j++;
            c = 1;
        }
        s = oss.str();
    }
    return s;
}

namespace LengthOfLongestSubstring
{
// 3. Longest Substring Without Repeating Characters
// Given a string, find the length of the longest substring without repeating
// characters.
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

// 125. Valid Palindrome
// Given a string, determine if it is a palindrome, considering only alphanumeric
// characters and ignoring cases. For example, "A man, a plan, a canal: Panama"
// is a palindrome. "race a car" is not a palindrome. Note: Have you consider
// that the string might be empty? This is a good question to ask during an
// interview. For the purpose of this problem, we define empty string as valid
// palindrome.
static bool isPalindrome(string s)
{
    function<bool(char)>
        isDigit = [&](char c) -> bool {
        return '0' <= c && c <= '9';
    };
    function<bool(char)>
        isLower = [&](char c) -> bool {
        return 'a' <= c && c <= 'z';
    };
    function<bool(char)>
        isUpper = [&](char c) -> bool {
        return 'A' <= c && c <= 'Z';
    };
    int i = 0;
    int j = s.size() - 1;
    while (i < j)
    {
        char a = s[i];
        if (!isDigit(a) && !isLower(a) && !isUpper(a))
        {
            i++;
            continue;
        }
        char b = s[j];
        if (!isDigit(b) && !isLower(b) && !isUpper(b))
        {
            j--;
            continue;
        }
        if (isDigit(a) != isDigit(b))
            return false;
        if (isDigit(a) && a != b)
            return false;
        if (isLower(a) && a - 'a' != b - 'a' && a - 'a' != b - 'A')
            return false;
        if (isUpper(a) && a - 'A' != b - 'a' && a - 'A' != b - 'A')
            return false;
        i++;
        j--;
    }
    return true;
}

// 49. Group Anagrams
// Given an array of strings, group anagrams together. For example, given:
// ["eat", "tea", "tan", "ate", "nat", "bat"], Return :
// [
//   ["ate", "eat", "tea"],
//   ["nat", "tan"],
//   ["bat"]
// ]
static vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    vector<vector<string>> result = vector<vector<string>>{};
    map<string, vector<string>> m = map<string, vector<string>>{};
    for_each(strs.begin(), strs.end(), [&](string &s) {
        string k(s);
        sort(k.begin(), k.end());
        if (m.find(k) == m.end())
            m[k] = vector<string>{};
        m[k].push_back(s);
    });
    for (map<string, vector<string>>::iterator it = m.begin(); it != m.end(); it++)
    {
        result.push_back(it->second);
    }
    return result;
}

// 131. Palindrome Partitioning
// Given a string s, partition s such that every substring of the partition is
// a palindrome. Return all possible palindrome partitioning of s. For example,
// given s = "aab", Return
// [["aa", "b"],
//  ["a", "a", "b"]]
static vector<vector<string>> partition(string s)
{
    vector<vector<string>> result;
    if (s.empty())
        return result;
    function<bool(size_t, size_t)>
        isPalindrome = [&](size_t i, size_t j) -> bool {
        while (i < j)
        {
            if (s[i++] != s[j--])
                return false;
        }
        return true;
    };
    function<void(size_t, vector<string> &)>
        solve = [&](size_t i, vector<string> &p) {
            if (i == s.length())
            {
                result.push_back(p);
                return;
            }
            for (size_t j = i; j < s.length(); j++)
            {
                if (isPalindrome(i, j))
                {
                    vector<string> p2(p);
                    p2.push_back(s.substr(i, j - i + 1));
                    solve(j + 1, p2);
                }
            }
        };
    vector<string> r;
    solve(0, r);
    return result;
}

// 127. Word Ladder
// Given two words (beginWord and endWord), and a dictionary's word list, find
// the length of shortest transformation sequence from beginWord to endWord, such
// that: Only one letter can be changed at a time. Each transformed word must
// exist in the word list. Note that beginWord is not a transformed word. For
// example, Given:
// beginWord = "hit"
// endWord = "cog"
// wordList = ["hot", "dot", "dog", "lot", "log", "cog"]
// As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
// return its length 5. Note : Return 0 if there is no such transformation sequence.
// All words have the same length. All words contain only lowercase alphabetic
// characters. You may assume no duplicates in the word list. You may assume beginWord
// and endWord are non-empty and are not the same. UPDATE(2017/1/20): The wordList
// parameter had been changed to a list of strings (instead of a set of strings).
// Please reload the code definition to get the latest changes
static int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    function<int(bool, string, vector<string> &)>
        search = [&](bool transformed, string word, vector<string> &list) -> int {
        vector<string> list2(list);
        auto it = find(list2.begin(), list2.end(), word);
        if (it == list2.end())
        {
            if (transformed)
                return 0;
        }
        else
        {
            list2.erase(it);
        }
        if (word == endWord)
            return 1;
        int min = INT_MAX;
        for (size_t i = 0; i < word.length(); i++)
        {
            string word2(word);
            for (char j = 0; j < 26; j++)
            {
                if (word[i] != 'a' + j)
                {
                    word2[i] = 'a' + j;
                    int m = search(true, word2, list2);
                    if (m > 0 && m < min)
                    {
                        min = m;
                    }
                }
            }
        }
        if (min != INT_MAX)
            return min + 1;
        else
            return 0;
    };
    return search(false, beginWord, wordList);
}

// 139. Word Break
// Given a non-empty string s and a dictionary wordDict containing a list of
// non-empty words, determine if s can be segmented into a space-separated
// sequence of one or more dictionary words. You may assume the dictionary does
// not contain duplicate words. For example, given s = "leetcode",
// dict = ["leet", "code"]. Return true because "leetcode" can be segmented as
// "leet code". Note: Each word in the dictionary can be used more than once.
// UPDATE(2017 / 1 / 4): The wordDict parameter had been changed to a list of
// strings(instead of a set of strings). Please reload the code definition to
// get the latest changes.
static bool wordBreak(string s, vector<string> &wordDict)
{
    if (wordDict.empty())
        return false;
    size_t minLength = wordDict[0].size();
    size_t maxLength = wordDict[0].size();
    for (size_t i = 1; i < wordDict.size(); i++)
    {
        if (wordDict[i].size() < minLength)
            minLength = wordDict[i].size();
        if (wordDict[i].size() > maxLength)
            maxLength = wordDict[i].size();
    }
    map<size_t, bool> breakable;
    function<bool(size_t)>
        solve = [&](size_t i) -> bool {
        if (breakable.find(i) != breakable.end())
            return breakable[i];
        breakable[i] = false;
        if (i == s.size())
        {
            breakable[i] = true;
        }
        else
        {
            for (size_t j = minLength; j <= min(maxLength, s.size() - i); j++)
            {
                auto it = find(wordDict.begin(), wordDict.end(), s.substr(i, j));
                if (it != wordDict.end())
                {
                    if (breakable.find(i + j) == breakable.end())
                    {
                        breakable[i + j] = solve(i + j);
                    }
                    if (breakable[i + j])
                    {
                        breakable[i] = true;
                        break;
                    }
                }
            }
        }
        return breakable[i];
    };
    return solve(0);
}

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

// 58. Length of Last Word
// Given a string s consists of upper/lower-case alphabets and empty space
// characters ' ', return the length of last word in the string. If the last
// word does not exist, return 0. Note: A word is defined as a character
// sequence consists of non-space characters only. For example, Given
// s = "Hello World", return 5.
// @string
static int lengthOfLastWord(string s)
{
    int length = 0;
    size_t i = 0;
    while (i < s.size())
    {
        if (s[i] != ' ')
        {
            size_t j = 0;
            while ((i + j) < s.size() && s[i + j] != ' ')
                j++;
            length = j;
            i += j;
        }
        else
        {
            i++;
        }
    }
    return length;
}
// @string
static int lengthOfLastWord2(string s)
{
    int length = 0;
    int i = s.size() - 1;
    while (i >= 0 && s[i] == ' ')
        i--;
    while (i >= 0 && s[i] != ' ')
    {
        length++;
        i--;
    }
    return length;
}

// 151. Reverse Words in a String
// Given an input string, reverse the string word by word. For example, Given
// s = "the sky is blue", return "blue is sky the". Update(2015-02-12): For C
// programmers: Try to solve it in-place in O(1) space. Clarification: What
// constitutes a word? A sequence of non-space characters constitutes a word.
// Could the input string contain leading or trailing spaces? Yes. However, your
// reversed string should not contain leading or trailing spaces. How about
// multiple spaces between two words? Reduce them to a single space in the
// reversed string.
static void reverseWords(string &s)
{
    if (s.length() == 0)
        return;
    int i = -1;
    size_t j = 0;
    while (j < s.length() && s[j] == ' ')
        j++;
    if (j == s.length())
    {
        s.resize(0);
        return;
    }
    while (j < s.length())
    {
        if (s[j] != ' ' || s[j - 1] != ' ')
        {
            i++;
            if (i < (int)j)
                s[i] = s[j];
        }
        j++;
    }
    if (0 <= i && s[i] == ' ')
        i--;
    s.resize(i + 1);
    function<void(int, int)>
        reverse = [&](int b, int e) {
            while (b < e)
            {
                swap(s[b++], s[e--]);
            }
        };
    reverse(0, s.length() - 1);
    i = 0;
    j = 0;
    while (j <= s.length())
    {
        if (j == s.length() || s[j] == ' ')
        {
            reverse(i, j - 1);
            i = j + 1;
        }
        j++;
    }
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

// 71. Simplify Path
// Given an absolute path for a file (Unix-style), simplify it. For example,
// path = "/home/", => "/home"
// path = "/a/./b/../../c/", => "/c"
// Corner Cases: Did you consider the case where path = "/../"? In this case,
// you should return "/". Another corner case is the path might contain
// multiple slashes // '/' together, such as "/home//foo/". In this case,
// you should ignore redundant slashes and return "/home/foo".
// @string, @linear
static string simplifyPath(string path)
{
    int len = path.length();
    if (len == 0 || path[0] != '/')
        return path;
    int i = -1;
    int j = 0;
    while (j < len)
    {
        if (path[j] == '/')
        {
            while (j < len && path[j] == '/')
                j++;
            if (j == len)
                break; // ////
            if (path[j] == '.')
            {
                if (j + 1 == len)
                {
                    break; // /.
                }
                else if (path[j + 1] == '/')
                { // /./
                    j = j + 1;
                    continue;
                }
                else if (path[j + 1] == '.')
                {
                    if (j + 2 == len)
                    { // /..
                        while (i > 0 && path[i] != '/')
                            i--;
                        if (i > 0)
                            i--;
                        break;
                    }
                    else if (path[j + 2] == '/')
                    { //  /../
                        while (i > 0 && path[i] != '/')
                            i--;
                        if (i > 0)
                            i--;
                        j = j + 2;
                        continue;
                    }
                }
            }
            if (i == -1 || path[i] != '/')
            {
                i++;
                path[i] = '/';
            }
            if (i + 1 < j)
            {
                while (j < len && path[j] != '/')
                {
                    i++;
                    path[i] = path[j++];
                }
            }
            else
            {
                while (j < len && path[j] != '/')
                    j++;
                i = j - 1;
            }
        }
        else
        {
            j++;
        }
    }
    if (i == -1)
        return string("/");
    else
        return path.substr(0, i + 1);
}

// 91. Decode Ways
// A message containing letters from A-Z is being encoded to numbers
// using the following mapping:
// 'A' -> 1
// 'B' -> 2
// ...
// 'Z' -> 26
// Given an encoded message containing digits, determine the total
// number of ways to decode it. For example, Given encoded message "12",
// it could be decoded as "AB" (1 2) or "L" (12).
// The number of ways decoding "12" is 2.
// @string, @dynamicprogramming
// Another solution is to compute from the beginning towards the end.
static int numDecodings(string s)
{
    if (s.length() == 0)
        return 0;
    int n;
    function<int(int)>
        solve = [&](int i) -> int {
        if (i == (int)s.length())
            return 0;
        if (i == (int)s.length() - 1)
        {
            if (s[i] == '0')
                return 0;
            else
                return 1;
        }
        switch (s[i])
        {
        case '0':
            return 0;
        case '1':
            if (s[i + 1] == '0')
            {
                if (s[i + 2] == '0')
                    return 0;
                else
                    return solve(i + 2);
            }
            else
            {
                if (s[i + 2] == '0')
                    return solve(i + 1);
                else
                    return solve(i + 1) + solve(i + 2);
            }
        case '2':
            if (s[i + 1] == '0')
            {
                if (s[i + 2] == '0')
                    return 0;
                else
                    return solve(i + 2);
            }
            else if ('1' <= s[i + 1] && s[i + 1] <= '6')
            {
                n = solve(i + 2);
                if (n == 0)
                    n++;
                return solve(i + 1) + n;
            }
            else
            {
                return solve(i + 1);
            }
        default:
            return solve(i + 1);
        }
    };
    return solve(0);
}

// 93. Restore IP Addresses
// Given a string containing only digits, restore it by returning
// all possible valid IP address combinations.
// For example :
// Given "25525511135",
// return["255.255.11.135", "255.255.111.35"]. (Order does not matter)
// @string, @recurse
static vector<string> restoreIpAddresses(string s)
{
    vector<string> result;
    function<void(int, int, string &)>
        solve = [&](int i, int j, string &p) {
            if (i > 4)
            {
                if (j == (int)s.length())
                {
                    p.pop_back();
                    result.push_back(p);
                }
                return;
            }
            if (j == (int)s.length())
                return;
            string p1(p);
            solve(i + 1, j + 1, p1.append(1, s[j]).append(1, '.'));
            if (j + 1 == (int)s.length() || s[j] == '0')
                return;
            string p2(p);
            solve(i + 1, j + 2, p2.append(s.substr(j, 2)).append(1, '.'));
            if (j + 2 == (int)s.length())
                return;
            int c = s[j] - '0';
            c = 10 * c + s[j + 1] - '0';
            c = 10 * c + s[j + 2] - '0';
            if (c <= 255)
            {
                string p3(p);
                solve(i + 1, j + 3, p3.append(s.substr(j, 3)).append(1, '.'));
            }
        };
    string prefix;
    solve(1, 0, prefix);
    return result;
}

// 165. Compare Version Numbers
// Compare two version numbers version1 and version2. If version1 > version2
// return 1, if version1 < version2 return -1, otherwise return 0. You may assume
// that the version strings are non-empty and contain only digits and the . character.
// The . character does not represent a decimal point and is used to separate
// number sequences. For instance, 2.5 is not "two and a half" or "half way to
// version three", it is the fifth second-level revision of the second first-level
// revision. Here is an example of version numbers ordering:
// 0.1 < 1.1 < 1.2 < 13.37
static int compareVersion(string version1, string version2)
{
    function<int(const string &, size_t &)>
        version = [&](const string &str, size_t &i) -> int {
        int val = 0;
        while (i < str.size() && str[i] == '.')
            i++;
        if (i >= str.size())
            return val;
        size_t j = str.find_first_of('.', i);
        if (j == string::npos)
        {
            val = atoi(str.substr(i).c_str());
            i = str.size();
        }
        else
        {
            val = atoi(str.substr(i, j - i).c_str());
            i = j;
        }
        return val;
    };
    size_t i1 = 0;
    size_t i2 = 0;
    int v1;
    int v2;
    while (i1 < version1.size() || i2 < version2.size())
    {
        v1 = version(version1, i1);
        v2 = version(version2, i2);
        if (v1 < v2)
            return -1;
        else if (v1 > v2)
            return 1;
    }
    return 0;
}

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
        l = y >= d ? (y / d) : 0; // what if just l = y / d ?
        r = y % 10;
        if (l != r)
            return false;
        y = (y % d) / 10;
        d /= 100;
    }
    return true;
}

// 89. Gray Code
// The gray code is a binary numeral system where two successive values differ
// in only one bit. Given a non-negative integer n representing the total
// number of bits in the code, print the sequence of gray code. A gray code
// sequence must begin with 0. For example, given n = 2, return [0, 1, 3, 2].
// Its gray code sequence is:
// 00 - 0
// 01 - 1
// 11 - 3
// 10 - 2
// Note :
// For a given n, a gray code sequence is not uniquely defined. For example,
// [0, 2, 3, 1] is also a valid gray code sequence according to the above
// definition. For now, the judge is able to judge based on one instance of
// gray code sequence. Sorry about that.
static vector<int> grayCode(int n)
{
    vector<int> gray = {0};
    int b = 0x1;
    for (int i = 0; i < n; i++)
    {
        int m = gray.size();
        for (int j = m - 1; j >= 0; j--)
        {
            int c = gray[j];
            c |= b;
            gray.push_back(c);
        }
        b = (b << 1);
    }
    return gray;
}

// 67. Add Binary
// Given two binary strings, return their sum (also a binary string).
// For example,
// a = "11"
// b = "1"
// Return "100"
static string addBinary(string a, string b)
{
    string result;
    int i = a.length() - 1;
    int j = b.length() - 1;
    int c = 0;
    int d = 0;
    while (i >= 0 || j >= 0)
    {
        if (i >= 0 && j >= 0)
        {
            d = c + (a[i--] - '0') + (b[j--] - '0');
        }
        else if (i >= 0)
        {
            d = c + (a[i--] - '0');
        }
        else
        {
            d = c + (b[j--] - '0');
        }
        if (d == 2 || d == 3)
            c = 1;
        else
            c = 0;
        d %= 2;
        result.insert(result.begin(), 1, d + '0');
    }
    if (c == 1)
    {
        result.insert(result.begin(), 1, c + '0');
    }
    return result;
}

// 43. Multiply Strings
// Given two non-negative integers num1 and num2 represented as strings, return
// the product of num1 and num2. Note: The length of both num1 and num2 is < 110.
// Both num1 and num2 contains only digits 0 - 9. Both num1 and num2 does not
// contain any leading zero. You must not use any built-in BigInteger library or
// convert the inputs to integer directly.
// @string
static string multiply(string num1, string num2)
{
    if (num1.length() == 1 && num1[0] == '0')
        return string("0");
    if (num2.length() == 1 && num2[0] == '0')
        return string("0");
    function<int(char)> toDigit = [&](char c) {
        return c - '0';
    };
    function<char(int)> toChar = [&](int i) {
        return i + '0';
    };
    function<string(string, char)> multiplyDigit = [&](string str, char ch) {
        string result;
        int i = str.length() - 1;
        int c = 0;
        int m;
        while (0 <= i)
        {
            m = c + toDigit(str[i--]) * toDigit(ch);
            c = m / 10;
            result.insert(result.begin(), toChar(m % 10));
        }
        if (c > 0)
            result.insert(result.begin(), toChar(c));
        return result;
    };
    function<string(string, string)> sum = [&](string str1, string str2) {
        string result;
        int i = str1.length() - 1;
        int j = str2.length() - 1;
        int c = 0;
        int m;
        while (0 <= i || 0 <= j)
        {
            if (0 <= i && 0 <= j)
                m = toDigit(str1[i--]) + toDigit(str2[j--]);
            else if (0 <= i)
                m = toDigit(str1[i--]);
            else
                m = toDigit(str2[j--]);
            m += c;
            c = m / 10;
            result.insert(result.begin(), toChar(m % 10));
        }
        if (c > 0)
            result.insert(result.begin(), toChar(c));
        return result;
    };
    string result = "0";
    char c;
    int i = num2.length() - 1;
    while (0 <= i)
    {
        c = num2[i--];
        if (c != '0')
            result = sum(result, multiplyDigit(num1, c));
        num1.append(1, '0');
    }
    return result;
}

// 29. Divide Two Integers
// Divide two integers without using multiplication, division and mod operator.
// If it is overflow, return MAX_INT.
static int divide(int dividend, int divisor)
{
    if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
        return INT_MAX;
    bool negative = false;
    // use long in case of overflow when fliping the sign
    long longDividend = (long)dividend;
    long longDivisor = (long)divisor;
    if (longDividend < 0)
    {
        longDividend = -longDividend;
        if (longDivisor < 0)
            longDivisor = -longDivisor;
        else
            negative = true;
    }
    else if (longDivisor < 0)
    {
        longDivisor = -longDivisor;
        negative = true;
    }
    int quotient = 0;
    // use long in case of overflow when left shift by 1
    long d = longDivisor;
    int m = 1;
    while (longDividend >= longDivisor)
    {
        if (d <= longDividend && longDividend < d << 1)
        {
            quotient += m;
            longDividend -= d;
        }
        else if (longDividend < d)
        {
            d = d >> 1;
            m = m >> 1;
        }
        else
        { // d << 1 <= longDividend
            d = d << 1;
            m = m << 1;
        }
    }
    return negative ? -quotient : quotient;
}

// 50. Pow(x, n)
static double myPow(double x, int n)
{
    // Use long long to avoid overflow when flip the sign.
    long long n1 = n;
    bool inverse = false;
    if (n1 < 0)
    {
        inverse = true;
        n1 = -n1;
    }
    // Use long long to avoid overflow when left-shift the bits.
    long long d;
    double y;
    double z = 1;
    while (n1 > 0)
    {
        d = 1;
        y = x;
        while ((d << 1) <= n1)
        {
            y *= y;
            d = d << 1;
        }
        z *= y;
        n1 -= d;
    }
    return inverse ? 1 / z : z;
}

// 69. Sqrt(x)
// Implement int sqrt(int x). Compute and return the square root of x.
static int mySqrt(int x)
{
    long long l = 0;
    long long r = x;
    // Use long long to avoid overflow of m * m.
    long long m;
    while (l <= r)
    {
        m = l + ((r - l) >> 1);
        long long low = m * m;
        long long high = (m + 1) * (m + 1);
        if (low <= x && x < high)
        {
            break;
        }
        else if (x < low)
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return (int)m;
}

class SpiralMatrix
{
public:
    // 54. Spiral Matrix
    // Given a matrix of m x n elements (m rows, n columns), return all
    // elements of the matrix in spiral order. For example,
    // Given the following matrix :
    // [
    //   [1, 2, 3],
    //   [4, 5, 6],
    //   [7, 8, 9]
    // ]
    // You should return [1, 2, 3, 6, 9, 8, 7, 4, 5].
    static vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> result = vector<int>{};
        if (matrix.empty() || matrix[0].empty())
            return result;
        int h = matrix[0].size();
        int v = matrix.size();
        int i = 0;
        int j = -1;
        int k;
        while (h > 0 && v > 0)
        {
            for (k = j + 1; k <= j + h; k++)
                result.push_back(matrix[i][k]);
            v--;
            j = k - 1;
            if (v == 0)
                break;
            for (k = i + 1; k <= i + v; k++)
                result.push_back(matrix[k][j]);
            h--;
            i = k - 1;
            if (h == 0)
                break;
            for (k = j - 1; k >= j - h; k--)
                result.push_back(matrix[i][k]);
            v--;
            j = k + 1;
            if (v == 0)
                break;
            for (k = i - 1; k >= i - v; k--)
                result.push_back(matrix[k][j]);
            h--;
            i = k + 1;
            if (h == 0)
                break;
        }
        return result;
    }
    static vector<int> spiralOrder2(vector<vector<int>> &matrix)
    {
        vector<int> result = vector<int>{};
        if (matrix.empty() || matrix[0].empty())
            return result;
        function<void(int, int, int, int)>
            solve = [&](int i, int j, int m, int n) {
                for (int k = 0; k < n; k++)
                    result.push_back(matrix[i][j + k]);
                if (m == 1)
                    return;
                for (int k = 1; k < m; k++)
                    result.push_back(matrix[i + k][j + n - 1]);
                if (n == 1)
                    return;
                for (int k = 1; k < n; k++)
                    result.push_back(matrix[i + m - 1][j + n - 1 - k]);
                for (int k = 1; k < m - 1; k++)
                    result.push_back(matrix[i + m - 1 - k][j]);
            };
        int m = matrix.size();
        int n = matrix[0].size();
        int i = 0;
        int j = 0;
        while (m > 0 && n > 0)
        {
            solve(i, j, m, n);
            i++;
            j++;
            m -= 2;
            n -= 2;
        }
        return result;
    }

    // 59. Spiral Matrix II
    // Given an integer n, generate a square matrix filled with elements
    // from 1 to n^2 in spiral order.
    // For example,
    // Given n = 3,
    // You should return the following matrix :
    // [
    //   [1, 2, 3],
    //   [8, 9, 4],
    //   [7, 6, 5]
    // ]
    // @grid
    static vector<vector<int>> generateMatrix(int n)
    {
        if (n <= 0)
            return vector<vector<int>>{};
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int h = n; // horizontal steps
        int v = n; // vertical steps
        int i = 0;
        int j = -1;
        int e = 1; // element value
        int k;
        while (h >= 0 || v >= 0)
        {
            for (k = j + 1; k <= j + h; k++)
            {
                matrix[i][k] = e++;
            }
            v--;
            j = k - 1;
            if (v == 0)
                break;
            for (k = i + 1; k <= i + v; k++)
            {
                matrix[k][j] = e++;
            }
            h--;
            i = k - 1;
            if (h == 0)
                break;
            for (k = j - 1; k >= j - h; k--)
            {
                matrix[i][k] = e++;
            }
            v--;
            j = k + 1;
            if (v == 0)
                break;
            for (k = i - 1; k >= i - v; k--)
            {
                matrix[k][j] = e++;
            }
            h--;
            i = k + 1;
            if (h == 0)
                break;
        }
        return matrix;
    }
};

// 62. Unique Paths
// A robot is located at the top-left corner of a m x n grid (marked 'Start'
// in the diagram below). The robot can only move either down or right at any
// point in time. The robot is trying to reach the bottom-right corner of the
// grid (marked 'Finish' in the diagram below). How many possible unique paths
// are there? Note: m and n will be at most 100.
// @grid, @dynamicprogramming
// Can solve by using one array.
static int uniquePaths(int m, int n)
{
    if (m <= 0 || n <= 0)
        return 0;
    vector<vector<int>> grid(m, vector<int>(n, 0));
    for (int j = n - 1; j >= 0; j--)
    {
        grid[m - 1][j] = 1;
    }
    for (int i = m - 2; i >= 0; i--)
    {
        grid[i][n - 1] = 1;
        for (int j = n - 2; j >= 0; j--)
        {
            grid[i][j] = grid[i + 1][j] + grid[i][j + 1];
        }
    }
    return grid[0][0];
}

// 63. Unique Paths II
// Follow up for "Unique Paths": Now consider if some obstacles are added to
// the grids. How many unique paths would there be? An obstacle and empty space
// is marked as 1 and 0 respectively in the grid. For example, There is one
// obstacle in the middle of a 3x3 grid as illustrated below.
// [
//   [0, 0, 0],
//   [0, 1, 0],
//   [0, 0, 0]
// ]
// The total number of unique paths is 2.
// Note: m and n will be at most 100.
// Can solve by using one array.
static int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    if (m == 0 || n == 0)
        return 0;
    vector<vector<int>> grid(obstacleGrid);
    grid[m - 1][n - 1] = (obstacleGrid[m - 1][n - 1] == 0) ? 1 : 0;
    for (int j = n - 2; j >= 0; j--)
    {
        grid[m - 1][j] = (obstacleGrid[m - 1][j] == 0) ? grid[m - 1][j + 1] : 0;
    }
    for (int i = m - 2; i >= 0; i--)
    {
        grid[i][n - 1] = (obstacleGrid[i][n - 1] == 0) ? grid[i + 1][n - 1] : 0;
        for (int j = n - 2; j >= 0; j--)
        {
            grid[i][j] = (obstacleGrid[i][j] == 0) ? (grid[i + 1][j] + grid[i][j + 1]) : 0;
        }
    }
    return grid[0][0];
}

// 64. Minimum Path Sum
// Given a m x n grid filled with non-negative numbers, find a path from top
// left to bottom right which minimizes the sum of all numbers along its path.
// Note: You can only move either down or right at any point in time.
// Note: Greedy search does not work here. e.g.,
// [[1, 3,   0]
//  [2, 100, 0]
//  [1, 1,   1]]
// @grid, @dynamicprogramming
// Can solve by using one array.
static int minPathSum(vector<vector<int>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return 0;
    size_t m = grid.size();
    size_t n = grid[0].size();
    vector<vector<int>> sum(grid);
    for (size_t j = 1; j < n; j++)
    {
        sum[0][j] += sum[0][j - 1];
    }
    for (size_t i = 1; i < m; i++)
    {
        sum[i][0] += sum[i - 1][0];
        for (size_t j = 1; j < n; j++)
        {
            sum[i][j] += min(sum[i][j - 1], sum[i - 1][j]);
        }
    }
    return sum[m - 1][n - 1];
}

// 74. Search a 2D Matrix
// Write an efficient algorithm that searches for a value in an m x n matrix.
// This matrix has the following properties: Integers in each row are sorted
// from left to right. The first integer of each row is greater than the last
// integer of the previous row. For example, Consider the following matrix:
// [
//   [1, 3, 5, 7],
//   [10, 11, 16, 20],
//   [23, 30, 34, 50]
// ]
// Given target = 3, return true.
// @grid, @linear
static bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;
    int m = matrix.size();
    int n = matrix[0].size();
    int i = 0;
    int j = n - 1;
    while (i < m && j >= 0)
    {
        if (matrix[i][j] == target)
            return true;
        else if (matrix[i][j] < target)
        {
            i++;
        }
        else
        {
            j--;
        }
    }
    return false;
}

// 79. Word Search
// Given a 2D board and a word, find if the word exists in the grid. The word
// can be constructed from letters of sequentially adjacent cell, where "adjacent"
// cells are those horizontally or vertically neighboring. The same letter cell
// may not be used more than once. For example, Given board =
// [
//   ['A', 'B', 'C', 'E'],
//   ['S', 'F', 'C', 'S'],
//   ['A', 'D', 'E', 'E']
// ]
// word = "ABCCED", ->returns true,
// word = "SEE", ->returns true,
// word = "ABCB", ->returns false.
// @grid, @bfs
static bool exist(vector<vector<char>> &board, string word)
{
    if (board.size() == 0 || board[0].size() == 0)
        return false;
    int m = board.size();
    int n = board[0].size();
    int l = word.size();
    function<bool(pair<int, int> &, int, set<pair<int, int>> &)>
        search = [&](pair<int, int> &p, int i, set<pair<int, int>> &v) -> bool {
        if (p.first < 0 || p.first >= m || p.second < 0 || p.second >= n || i < 0 || i >= l || board[p.first][p.second] != word[i] || v.find(p) != v.end())
        {
            return false;
        }
        if (i == l - 1)
            return true;
        v.insert(p);
        pair<int, int> p1 = make_pair(p.first, p.second - 1);
        if (search(p1, i + 1, v))
        {
            return true;
        }
        p1 = make_pair(p.first, p.second + 1);
        if (search(p1, i + 1, v))
        {
            return true;
        }
        p1 = make_pair(p.first - 1, p.second);
        if (search(p1, i + 1, v))
        {
            return true;
        }
        p1 = make_pair(p.first + 1, p.second);
        if (search(p1, i + 1, v))
        {
            return true;
        }
        v.erase(p);
        return false;
    };
    for (int j = 0; j < m; j++)
    {
        for (int k = 0; k < n; k++)
        {
            pair<int, int> point = make_pair(j, k);
            set<pair<int, int>> visited = set<pair<int, int>>{};
            if (search(point, 0, visited))
                return true;
        }
    }
    return false;
}

// 36. Valid Sudoku
// Determine if a Sudoku is valid, according to: Sudoku Puzzles The Rules.
// The Sudoku board could be partially filled, where empty cells are filled with
// the character '.'. A partially filled sudoku which is valid. Note: A valid
// Sudoku board (partially filled) is not necessarily solvable. Only the filled
// cells need to be validated.
static bool isValidSudoku(vector<vector<char>> &board)
{
    map<size_t, set<char>> rows;
    map<size_t, set<char>> cols;
    map<size_t, set<char>> grids;
    for (size_t i = 0; i < board.size(); i++)
    {
        if (rows.find(i) == rows.end())
            rows[i] = set<char>{};
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (i == 0 && cols.find(j) == cols.end())
                cols[j] = set<char>();
            if (i % 3 == 0 && j % 3 == 0 && grids.find(i * 3 + j) == grids.end())
            {
                grids[i * 3 + j] = set<char>{};
            }
            if (board[i][j] != '.')
            { // A real check may be against '0'-'9'
                if (rows[i].find(board[i][j]) != rows[i].end())
                    return false;
                rows[i].insert(board[i][j]);
                if (cols[j].find(board[i][j]) != cols[j].end())
                    return false;
                cols[j].insert(board[i][j]);
                auto k = (i / 3) * 3 + (j / 3);
                if (grids[k].find(board[i][j]) != grids[k].end())
                    return false;
                grids[k].insert(board[i][j]);
            }
        }
    }
    return true;
}

// 48. Rotate Image
// You are given an n x n 2D matrix representing an image. Rotate the image by
// 90 degrees(clockwise).
// 0 1        3 0
// 3 2        2 1
static void rotate(vector<vector<int>> &matrix)
{
    int d = matrix.size();
    for (int i = 0; i < d - 1; i++)
    {
        for (int j = 0; j < d - i - 1; j++)
        {
            swap(matrix[i][j], matrix[d - j - 1][d - i - 1]);
        }
    }
    for (int i = 0; i < (d >> 1); i++)
    {
        for (int j = 0; j < d; j++)
        {
            swap(matrix[i][j], matrix[d - i - 1][j]);
        }
    }
}

// 73. Set Matrix Zeroes
// Given a m x n matrix, if an element is 0, set its entire row and column to 0.
// Do it in place.
static void setZeroes(vector<vector<int>> &matrix)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return;
    size_t m = matrix.size();
    size_t n = matrix[0].size();
    bool zeroFirstColumn = false;
    bool zeroFirstRow = false;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0)
            {
                if (i == 0)
                    zeroFirstRow = true;
                if (j == 0)
                    zeroFirstColumn = true;
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for (size_t i = 1; i < m; i++)
    {
        if (matrix[i][0] == 0)
        {
            for (size_t j = 1; j < n; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    for (size_t j = 1; j < n; j++)
    {
        if (matrix[0][j] == 0)
        {
            for (size_t i = 1; i < m; i++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    if (zeroFirstColumn)
    {
        for (size_t i = 1; i < m; i++)
        {
            matrix[i][0] = 0;
        }
    }
    if (zeroFirstRow)
    {
        for (size_t j = 1; j < n; j++)
        {
            matrix[0][j] = 0;
        }
    }
}

// 130. Surrounded Regions
// Given a 2D board containing 'X' and 'O' (the letter O), capture all regions
// surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in
// that surrounded region. For example,
//    X X X X
//    X O O X
//    X X O X
//    X O X X
// After running your function, the board should be :
//    X X X X
//    X X X X
//    X X X X
//    X O X X
static void solve(vector<vector<char>> &board)
{
    size_t m = board.size();
    if (m == 0)
        return;
    size_t n = board[0].size();
    if (n == 0)
        return;
    function<void(size_t, size_t)>
        mark = [&](size_t x, size_t y) {
            if (board[x][y] != 'O')
                return;
            board[x][y] = 'Y';
            if (0 < x)
                mark(x - 1, y);
            if (y < n - 1)
                mark(x, y + 1);
            if (x < m - 1)
                mark(x + 1, y);
            if (0 < y)
                mark(x, y - 1);
        };
    for (size_t i = 0; i < n; i++)
    {
        if (board[0][i] == 'O')
            mark(0, i);
        if (m > 1 && board[m - 1][i] == 'O')
            mark(m - 1, i);
    }
    for (size_t i = 0; i < m; i++)
    {
        if (board[i][0] == 'O')
            mark(i, 0);
        if (n > 1 && board[i][n - 1] == 'O')
            mark(i, n - 1);
    }
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (board[i][j] == 'O')
            {
                board[i][j] = 'X';
            }
            else if (board[i][j] == 'Y')
            {
                board[i][j] = 'O';
            }
        }
    }
}

// 200. Number of Islands
// Given a 2d grid map of '1's (land) and '0's (water), count the number of
// islands. An island is surrounded by water and is formed by connecting adjacent
// lands horizontally or vertically. You may assume all four edges of the grid
// are all surrounded by water. Example 1:
//  11110
//  11010
//  11000
//  00000
// Answer: 1
// Example 2:
//  11000
//  11000
//  00100
//  00011
// Answer: 3
static int numIslands(vector<vector<char>> &grid)
{
    int m = grid.size();
    if (m == 0)
        return 0;
    int n = grid[0].size();
    if (n == 0)
        return 0;
    function<void(int, int)>
        visit = [&](int i, int j) {
            if (grid[i][j] == '1')
            {
                grid[i][j] = '2';
                if (i > 0)
                    visit(i - 1, j);
                if (j < n - 1)
                    visit(i, j + 1);
                if (i < m - 1)
                    visit(i + 1, j);
                if (j > 0)
                    visit(i, j - 1);
            }
        };
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '1')
            {
                c++;
                visit(i, j);
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] != '0')
            {
                grid[i][j] = '1';
            }
        }
    }
    return c;
}

// 118. Pascal's Triangle
// Given numRows, generate the first numRows of Pascal's triangle. For example,
// given numRows = 5, Return
// [
//      [1],
//     [1, 1],
//    [1, 2, 1],
//   [1, 3, 3, 1],
//  [1, 4, 6, 4, 1]
// ]
static vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> result;
    if (numRows <= 0)
        return result;
    vector<int> row;
    for (int i = 0; i < numRows; i++)
    {
        row.push_back(1);
        for (int j = row.size() - 2; j > 0; j--)
        {
            row[j] += row[j - 1];
        }
        result.push_back(row);
        row = vector<int>(row);
    }
    return result;
}

// 119. Pascal's Triangle II
// Given an index k, return the kth row of the Pascal's triangle. For example,
// given k = 3, Return [1, 3, 3, 1]. Note: Could you optimize your algorithm
// to use only O(k) extra space ?
static vector<int> getRow(int rowIndex)
{
    vector<int> row;
    for (int k = 0; k <= rowIndex; k++)
    {
        row.push_back(1);
        for (int i = row.size() - 2; i > 0; i--)
        {
            row[i] += row[i - 1];
        }
    }
    return row;
}

// 120. Triangle
// Given a triangle, find the minimum path sum from top to bottom. Each step you
// may move to adjacent numbers on the row below. For example, given the following
// triangle
// [
//     [2],
//    [3, 4],
//   [6, 5, 7],
//  [4, 1, 8, 3]
// ]
// The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
// Note: Bonus point if you are able to do this using only O(n) extra space,
// where n is the total number of rows in the triangle.
static int minimumTotal(vector<vector<int>> &triangle)
{
    vector<int> row(triangle[0]);
    for (size_t i = 1; i < triangle.size(); i++)
    {
        size_t n = triangle[i].size();
        row.push_back(row[n - 2] + triangle[i][n - 1]);
        for (int j = n - 2; j > 0; j--)
        {
            row[j] = triangle[i][j] + min(row[j - 1], row[j]);
        }
        row[0] += triangle[i][0];
    }
    int min = row[0];
    for (size_t i = 1; i < row.size(); i++)
    {
        if (row[i] < min)
            min = row[i];
    }
    return min;
}

// 155. Min Stack
// Design a stack that supports push, pop, top, and retrieving the minimum
// element in constant time.
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
// Given two non-empty linked lists representing two non-negative integers. The
// digits are stored in reverse order (LSB is the head) and each node contain a
// single digit. Add the two numbers and return a linked list. The two numbers
// do not contain leading zero, except the number 0 itself.
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

// 133. Clone Graph
// Clone an undirected graph. Each node in the graph contains a label and a list
// of its neighbors. OJ's undirected graph serialization: Nodes are labeled uniquely.
// We use # as a separator for each node, and , as a separator for node label and
// each neighbor of the node. As an example, consider the serialized graph
// { 0,1,2#1,2#2,2 }. The graph has a total of three nodes, and therefore contains
// three parts as separated by #. First node is labeled as 0. Connect node 0 to
// both nodes 1 and 2. Second node is labeled as 1. Connect node 1 to node 2.
// Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a
// self-cycle. Visually, the graph looks like the following :
//    1
//   /  \
//  /    \
// 0 -- - 2
//       / \
//       \_/
struct UndirectedGraphNode
{
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x){};
};
static UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
{
    map<int, UndirectedGraphNode *> cloned;
    function<UndirectedGraphNode *(UndirectedGraphNode *)>
        clone = [&](UndirectedGraphNode *n) -> UndirectedGraphNode * {
        if (n == nullptr)
            return nullptr;
        if (cloned.find(n->label) != cloned.end())
            return cloned[n->label];
        UndirectedGraphNode *copy = new UndirectedGraphNode(n->label);
        cloned[n->label] = copy;
        for (size_t i = 0; i < n->neighbors.size(); i++)
        {
            int label = n->neighbors[i]->label;
            if (cloned.find(label) == cloned.end())
            {
                cloned[label] = clone(n->neighbors[i]);
            }
            copy->neighbors.push_back(cloned[label]);
        }
        return copy;
    };
    return clone(node);
}

struct RandomListNode
{
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
};
// 138. Copy List with Random Pointer
// A linked list is given such that each node contains an additional random pointer
// which could point to any node in the list or null. Return a deep copy of the list.
static RandomListNode *copyRandomList(RandomListNode *head)
{
    map<RandomListNode *, RandomListNode *> copied;
    function<RandomListNode *(RandomListNode *)>
        copy = [&](RandomListNode *node) -> RandomListNode * {
        if (node == nullptr)
            return nullptr;
        RandomListNode *c = new RandomListNode(node->label);
        copied[node] = c;
        if (copied.find(node->next) == copied.end())
        {
            copied[node->next] = copy(node->next);
        }
        c->next = copied[node->next];
        if (copied.find(node->random) == copied.end())
        {
            copied[node->random] = copy(node->random);
        }
        c->random = copied[node->random];
        return c;
    };
    return copy(head);
}
} // namespace LeetCode
} // namespace Test

#endif
