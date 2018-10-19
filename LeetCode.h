#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include <algorithm>
#include <functional>
#include <limits.h>
#include <map>
#include <set>
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
} // namespace LeetCode
} // namespace Test

#endif