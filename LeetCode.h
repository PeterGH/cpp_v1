#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include <algorithm>
#include <functional>
#include <limits.h>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Test
{
namespace LeetCode
{
static bool Equal(const map<char, int> &m1, const map<char, int> &m2)
{
    if (m1.size() != m2.size())
        return false;
    for (map<char, int>::const_iterator it1 = m1.begin(); it1 != m1.end(); it1++)
    {
        map<char, int>::const_iterator it2 = m2.find(it1->first);
        if (it2 == m2.end())
            return false;
        if (it2->second != it1->second)
            return false;
    }
    return true;
}

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

    // m*log(m) + n*log(m) = (m + n)*log(m)
    // m*log(n) + n*log(n) = (m + n)*log(n)
    // Should sort the shorter range
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

// Given an array S of n integers, are there elements a, b, c, and d in S
// such that a + b + c + d = target? Find all unique quadruplets in the array
// which gives the sum of target. Note: Elements in a quadruplet (a,b,c,d)
// must be in non-descending order. (ie, a ≤ b ≤ c ≤ d) The solution set must
// not contain duplicate quadruplets. For example, given array
// S = {1 0 -1 0 -2 2}, and target = 0. A solution set is:
// (-1,  0, 0, 1)
// (-2, -1, 1, 2)
// (-2,  0, 0, 2)
static vector<vector<int>> FourSum(vector<int> &num, int target)
{
    if (num.size() < 4)
        return vector<vector<int>>{};
    sort(num.begin(), num.end());
    unordered_map<int, set<pair<int, int>>> twosum;
    set<vector<int>> ans;
    for (int i = 0; i < (int)num.size() - 1; i++)
    {
        for (int j = i + 1; j < (int)num.size(); j++)
        {
            int s = num[i] + num[j];
            int t = target - s;
            if (twosum.find(t) != twosum.end())
            {
                for_each(twosum[t].begin(), twosum[t].end(), [&](pair<int, int> p) {
                    vector<int> a = {p.first, p.second, num[i], num[j]};
                    ans.insert(a);
                });
            }
        }
        for (int j = 0; j < i; j++)
        {
            int s = num[j] + num[i];
            if (twosum.find(s) == twosum.end())
            {
                twosum[s] = set<pair<int, int>>{};
            }
            twosum[s].insert(make_pair(num[j], num[i]));
        }
    }
    return vector<vector<int>>(ans.begin(), ans.end());
}
// [TODO] Generalize to X-Sum
static vector<vector<int>> FourSum2(vector<int> &num, int target)
{
    if (num.size() < 4)
        return vector<vector<int>>{};
    sort(num.begin(), num.end());

    function<void(vector<int> &, int, int, const vector<int> &, vector<vector<int>> &)>
        solve = [&](vector<int> &n, int i, int t, const vector<int> &s, vector<vector<int>> &o) {
            if (s.size() == 3)
            {
                // Already have 3 number, just need one more between index i and the end
                int l = i;
                int h = n.size() - 1;
                int m;
                while (l <= h)
                {
                    m = l + ((h - l) >> 1);
                    if (t < n[m])
                    {
                        if (l == m)
                            break;
                        h = m - 1;
                    }
                    else if (n[m] < t)
                    {
                        if (m == h)
                            break;
                        l = m + 1;
                    }
                    else
                    {
                        vector<int> v(s);
                        v.push_back(n[m]);
                        o.push_back(v);
                        break;
                    }
                }
                return;
            }
            while (i <= (int)n.size() - 4 + (int)s.size() && n[i] <= t)
            {
                int j = i;
                while (j + 1 < (int)n.size() && n[j + 1] == n[j])
                    j++;
                int k = i;
                int u = n[k];
                vector<int> v(s);
                while (k <= j)
                {
                    v.push_back(n[k]);
                    if (v.size() == 4)
                    {
                        if (u == t)
                            o.push_back(v);
                        break;
                    }
                    else
                    {
                        solve(n, j + 1, t - u, v, o);
                    }
                    k++;
                    u += n[k];
                }
                i = j + 1;
            }
        };
    vector<vector<int>> o;
    solve(num, 0, target, vector<int>{}, o);
    return o;
}
// [TODO] Generalize to X-Sum
static vector<vector<int>> FourSum3(vector<int> &num, int target)
{
    if (num.size() < 4)
        return vector<vector<int>>{};
    sort(num.begin(), num.end());

    function<void(vector<int> &, int, int, int, const vector<int> &, vector<vector<int>> &)>
        solve = [&](vector<int> &n, int i, int r, int t, const vector<int> &s, vector<vector<int>> &o) {
            while (r > 0 && i <= (int)n.size() - r && n[i] <= t)
            {
                int j = i;
                while (j + 1 < (int)n.size() && n[j + 1] == n[j])
                    j++;
                int k = i;
                int u = n[k];
                int c = 1;
                vector<int> v(s);
                while (k <= j && u <= t && c <= r)
                {
                    v.push_back(n[k]);
                    if (c == r)
                    {
                        if (u == t)
                            o.push_back(v);
                        break;
                    }
                    else
                    {
                        solve(n, j + 1, r - c, t - u, v, o);
                    }
                    k++;
                    u += n[k];
                    c++;
                }
                i = j + 1;
            }
        };
    vector<vector<int>> o;
    solve(num, 0, 4, target, vector<int>{}, o);
    return o;
}

// Given an array S of n integers, are there elements a, b, c in S
// such that a + b + c = 0? Find all unique triplets in the array
// which gives the sum of zero. Note: Elements in a triplet (a,b,c)
// must be in non-descending order. (ie, a ≤ b ≤ c) The solution set
// must not contain duplicate triplets. For example, given array
// S = {-1 0 1 2 -1 -4}, A solution set is:
//  (-1, 0, 1)
//  (-1, -1, 2)
static vector<vector<int>> ThreeSum(vector<int> &num)
{
    vector<vector<int>> ans;
    int n = num.size();
    if (n < 3)
        return ans;
    sort(num.begin(), num.end());
    if (num[0] > 0 || num[n - 1] < 0)
        return ans;
    int i = 0;
    while (i <= n - 3)
    {
        if (num[i] > 0)
            break;
        int j = i + 1;
        int k = n - 1;
        while (j < k)
        {
            int s = num[j] + num[k];
            if (s == -num[i])
            {
                ans.push_back(vector<int>{num[i], num[j], num[k]});
            }
            if (s <= -num[i])
            {
                while (j + 1 < k && num[j + 1] == num[j])
                    j++;
                j++;
            }
            if (s >= -num[i])
            {
                while (j < k - 1 && num[k - 1] == num[k])
                    k--;
                k--;
            }
        }
        while (i + 1 <= n - 3 && num[i + 1] == num[i])
            i++;
        i++;
    }
    return ans;
}
static vector<vector<int>> ThreeSum2(vector<int> &num)
{
    vector<vector<int>> ans;
    int n = num.size();
    if (n < 3)
        return ans;
    sort(num.begin(), num.end());
    if (num[0] > 0 || num[n - 1] < 0)
        return ans;
    int i = 0;
    while (i <= n - 3)
    {
        if (num[i] > 0)
            break;
        int j = i + 1;
        while (j <= n - 2)
        {
            int s = num[i] + num[j];
            if (s > 0)
                break;
            int t = -s;
            int l = j + 1;
            int h = n - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (t < num[m])
                {
                    if (l == m)
                        break;
                    h = m - 1;
                }
                else if (num[m] < t)
                {
                    if (m == h)
                        break;
                    l = m + 1;
                }
                else
                {
                    ans.push_back(vector<int>{num[i], num[j], num[m]});
                    break;
                }
            }
            while (j + 1 <= n - 2 && num[j + 1] == num[j])
                j++;
            j++;
        }
        while (i + 1 <= n - 3 && num[i + 1] == num[i])
            i++;
        i++;
    }
    return ans;
}

// Given an array S of n integers, find three integers in S such that the sum
// is closest to a given number, target. Return the sum of the three integers.
// You may assume that each input would have exactly one solution. For example,
// given array S = {-1 2 1 -4}, and target = 1. The sum that is closest to the
// target is 2. (-1 + 2 + 1 = 2).
static int ThreeSumClosest(vector<int> &num, int target)
{
    int n = num.size();
    sort(num.begin(), num.end());
    int i = 0;
    int d = INT_MAX;
    int t = target;
    while (i <= n - 3)
    {
        int j = i + 1;
        int k = n - 1;
        while (j < k)
        {
            int s = num[i] + num[j] + num[k];
            if (s < target)
            {
                if (target - s <= d)
                {
                    d = target - s;
                    t = s;
                }
                while (j + 1 < k && num[j + 1] == num[j])
                    j++;
                j++;
            }
            else if (s > target)
            {
                if (s - target <= d)
                {
                    d = s - target;
                    t = s;
                }
                while (j < k - 1 && num[k - 1] == num[k])
                    k--;
                k--;
            }
            else
            {
                return s;
            }
        }
        while (i + 1 <= n - 3 && num[i + 1] == num[i])
            i++;
        i++;
    }
    return t;
}

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
                    // The median or the lower median is in s
                    if (odd)
                    {
                        // s[0..(ms-1)], s[ms], s[(ms+1)..(ls-1)]
                        //     l[0..ml],        l[(ml+1)..(ll-1)]
                        return s[ms];
                    }
                    else if (ms + 1 < (int)s.size())
                    {
                        // even
                        // s[0..(ms-1)], s[ms], s[ms+1], s[(ms+2)..(ls-1)]
                        //     l[0..ml],        l[ml+1], l[(ml+2)..(ll-1)]
                        return (s[ms] + min(s[ms + 1], l[ml + 1])) / 2.0;
                    }
                    else
                    {
                        // even
                        // s[0..(ms-1)], s[ms]
                        //     l[0..ml],        l[(ml+1)..(ll-1)]
                        return (s[ms] + l[ml + 1]) / 2.0;
                    }
                }
                if (bs == ms)
                {
                    // The median or the lower median is in l
                    if (odd)
                    {
                        // s[0..(ms-1)],          s[ms], s[(ms+1)..(ls-1)]
                        //     l[0..ml], l[ml+1],        l[(ml+2)..(ll-1)]
                        return l[ml + 1];
                    }
                    else if (ml + 2 < (int)l.size())
                    {
                        // even
                        // s[0..(ms-1)],          s[ms], s[(ms+1)..(ls-1)]
                        //     l[0..ml], l[ml+1], l[(ml+2)..(ll-1)]
                        return (l[ml + 1] + min(s[ms], l[ml + 2])) / 2.0;
                    }
                    else
                    {
                        // even
                        // s[0..(ms-1)],          s[ms], s[(ms+1)..(ls-1)]
                        //     l[0..ml], l[ml+1]
                        return (l[ml + 1] + s[ms]) / 2.0;
                    }
                }
                es = ms - 1;
            }
            else
            {
                if (ms == (int)s.size() - 1)
                {
                    if (odd)
                    {
                        //     s[0..ms]
                        // l[0..(ml-1)], l[ml], l[(ml+1)..(ll-1)]
                        return l[ml];
                    }
                    else
                    {
                        //     s[0..ms]
                        // l[0..(ml-1)], l[ml], l[(ml+1)], l[(ml+2)..(ll-1)]
                        return (l[ml] + l[ml + 1]) / 2.0;
                    }
                }
                if (l[ml] <= s[ms + 1])
                {
                    if (odd)
                    {
                        //     s[0..ms],        s[(ms+1)..(ls-1)]
                        // l[0..(ml-1)], l[ml], l[(ml+1)..(ll-1)]
                        return l[ml];
                    }
                    else
                    {
                        // even
                        //     s[0..ms],        s[(ms+1)..(ls-1)]
                        // l[0..(ml-1)], l[ml], l[(ml+1)..(ll-1)]
                        return (l[ml] + min(s[ms + 1], l[ml + 1])) / 2.0;
                    }
                }
                if (ms == es)
                {
                    if (odd)
                    {
                        //     s[0..ms], s[ms+1],        s[(ms+2)..(ls-1)]
                        // l[0..(ml-1)],          l[ml], l[(ml+1)..(ll-1)]
                        return s[ms + 1];
                    }
                    else if (ms + 2 < (int)s.size())
                    {
                        //     s[0..ms], s[ms+1], s[(ms+2)..(ls-1)]
                        // l[0..(ml-1)],          l[ml], l[(ml+1)..(ll-1)]
                        return (s[ms + 1] + min(s[ms + 2], l[ml])) / 2.0;
                    }
                    else
                    {
                        //     s[0..ms], s[ms+1]
                        // l[0..(ml-1)],          l[ml], l[(ml+1)..(ll-1)]
                        return (s[ms + 1] + l[ml]) / 2.0;
                    }
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
    // Remove empty positions in nums1
    while (it1 != nums1.end())
        it1 = nums1.erase(it1);
}
static void MergeSortedArrays(int A[], int m, int B[], int n)
{
    if (A == nullptr || m < 0 || B == nullptr || n < 0)
        return;
    int i = 0;
    int j = 0;
    while (i < m && j < n)
    {
        if (A[i] <= B[j])
            i++;
        else
        {
            for (int k = m; k > i; k--)
            {
                A[k] = A[k - 1];
            }
            A[i] = B[j];
            m++;
            i++;
            j++;
        }
    }
    if (j < n)
    {
        for (int k = j; k < n; k++)
        {
            A[i] = B[k];
            i++;
        }
    }
}
static void MergeSortedArrays2(int A[], int m, int B[], int n)
{
    if (A == nullptr || m < 0 || B == nullptr || n < 0)
        return;
    int i = m - 1;
    int j = n - 1;
    while (i >= 0 && j >= 0)
    {
        if (A[i] > B[j])
        {
            A[i + j + 1] = A[i];
            i--;
        }
        else
        {
            A[i + j + 1] = B[j];
            j--;
        }
    }
    if (j >= 0)
    {
        for (int p = j; p >= 0; p--)
        {
            A[p] = B[p];
        }
    }
}

// An inversion is a pair (i, j) such that i < j and I[i] > I[j].
// Find an inversion such that j - i is maximized.
// Use parameter first to return value i and distance to return value j - i
static void MaxInversionDistance(const int *input, int length, int &first, int &distance)
{
    first = 0;
    distance = 0;
    if (input == nullptr || length <= 1)
        return;

    // Array firstIndices to contain the indices of a increasing subsequence of input
    // Each element of firstIndices is a candidate for the first index of maximum inversion
    //       firstIndices[0]  <       firstIndices[1]  <       firstIndices[2]  < ...
    // input[firstIndices[0]] < input[firstIndices[1]] < input[firstIndices[2]] < ...
    unique_ptr<int[]> firstIndices(new int[length]);
    int index = 0;
    firstIndices[index] = 0;
    // Ignore input[length - 1]
    for (int i = 1; i < length - 1; i++)
    {
        if (input[i] > input[firstIndices[index]])
        {
            index++;
            firstIndices[index] = i;
        }
    }

    int prev;
    // Ignore input[0]
    for (int i = length - 1; i > 0; i--)
    {
        if (i < length - 1 && input[i] >= prev)
        {
            // if there is an inversion ending at i, then
            // prev would extend it by one more position.
            // So input[i] should be ignored.
            continue;
        }

        prev = input[i];

        while (i <= firstIndices[index])
            index--;

        // now [firstIndices[index], i] is a candidate
        if (prev >= input[firstIndices[index]])
        {
            // prev is greater than all possible first indices
            continue;
        }

        while (index > 0 && input[firstIndices[index - 1]] > prev)
        {
            index--;
        }

        // Now firstIndices[index] is the first element greater than input[i]
        int d = i - firstIndices[index];
        if (d > distance)
        {
            first = firstIndices[index];
            distance = i - first;
        }

        if (index == 0)
        {
            // All elements of firstIndices are examined
            break;
        }
    }
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
static int removeDuplicates2_1(int A[], int n)
{
    if (A == nullptr || n <= 2)
        return n;

    int i = 0;
    int j = 1;

    while (j < n)
    {
        if (i + 1 < j)
            A[i + 1] = A[j];
        i++;
        j++;
        if (A[i - 1] == A[i])
        {
            while (j < n && A[j] == A[i])
                j++;
        }
    }

    return i + 1;
}
// This is wrong. For input [1, 1, 1, 2, 2, 3], output is [1, 1, 2, 3]
static int removeDuplicates2_2(vector<int> &nums)
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

// Slide a window across an input, output the maximum on every move.
static void MaxInSlidingWindow(const int *input, int length, int window, vector<int> &output)
{
    if (input == nullptr)
        throw invalid_argument("input is a nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));
    if (window <= 0 || window > length)
        throw invalid_argument(String::Format("window %d is out of range (0, %d]", window, length));

    priority_queue<pair<int, int>> heap; // Default it is a max-heap

    for (int i = 0; i < window; i++)
    {
        heap.push(make_pair(input[i], i));
    }

    output.push_back(heap.top().first);

    for (int i = window; i < length; i++)
    {
        // The size of heap may be more than the window size.
        // Consider one case where the input contains increasing numbers.
        // But the top of heap is always the max within the current window.

        while (!heap.empty() && heap.top().second <= i - window)
        {
            heap.pop();
        }

        heap.push(make_pair(input[i], i));
        output.push_back(heap.top().first);
    }
}
static void MaxInSlidingWindow2(const int *input, int length, int window, vector<int> &output)
{
    if (input == nullptr)
        throw invalid_argument("input is a nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));
    if (window <= 0 || window > length)
        throw invalid_argument(String::Format("window %d is out of range (0, %d]", window, length));

    deque<int> queue;

    // Establish the baseline:
    // 1. queue contains the latest k elements where k <= window
    // 2. queue is sorted and the maximum is queue.front()
    // 3. queue.back() is the latest element
    // 4. queue.front() is the oldest element
    // so effectively the queue contains a decreasing sequence between [max, i]
    for (int i = 0; i < window; i++)
    {
        while (!queue.empty() && input[i] >= input[queue.back()])
        {
            queue.pop_back();
        }
        queue.push_back(i);
    }

    output.push_back(input[queue.front()]);

    for (int i = window; i < length; i++)
    {
        while (!queue.empty() && input[i] >= input[queue.back()])
        {
            queue.pop_back();
        }
        while (!queue.empty() && queue.front() <= i - window)
        {
            queue.pop_front();
        }
        queue.push_back(i);
        output.push_back(input[queue.front()]);
    }
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
        // nums[l] == nums[m] == nums[r]
        // target could be either in [l, m) or (m, r]
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

// Given an unsorted integer array, find the first missing positive
// integer. For example, Given [1,2,0] return 3, and [3,4,-1,1] return 2.
// Your algorithm should run in O(n) time and uses constant space.
static int FirstMissingPositive(int A[], int n)
{
    if (A == nullptr || n <= 0)
        return 1;
    for (int i = 0; i < n; i++)
    {
        // Make sure A[i] = i + 1
        while (A[i] > 0 && A[i] - 1 != i)
        {
            // A[i] should be at another index j
            int j = A[i] - 1;
            if (j >= n)
                break; // A[i] is out of range
            if (A[i] == A[j])
                break;
            int t = A[j];
            A[j] = A[i];
            A[i] = t;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (A[i] != i + 1)
            return i + 1;
    }
    return n + 1;
}
static int FirstMissingPositive2(int A[], int n)
{
    if (A == nullptr || n <= 0)
        return 1;
    for (int i = 0; i < n; i++)
    {
        // This is wrong. After switching A[i] and A[j],
        // it does not check whether A[j] (now at i) is valid or not.
        if (A[i] > 0 && A[i] - 1 != i)
        {
            // A[i] should be at another index j
            int j = A[i] - 1;
            if (j >= n)
                break; // A[i] is out of range
            if (A[i] == A[j])
                break;
            int t = A[j];
            A[j] = A[i];
            A[i] = t;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (A[i] != i + 1)
            return i + 1;
    }
    return n + 1;
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
static void maxProfit(const int *input, int length, int &buy, int &sell, int &profit)
{
    buy = 0;
    sell = 0;
    profit = 0;
    stack<int> sellCandidates; // track the increasing values from end to beginning
    sellCandidates.push(length - 1);
    for (int i = length - 2; i > 0; i--)
    {
        if (input[i] >= input[sellCandidates.top()])
        {
            // i is the possible sell date, because
            // other dates later than i have less stock values
            sellCandidates.push(i);
        }
    }
    int min = 0;
    for (int i = 0; i < length - 1; i++)
    {
        if (i == 0 || input[i] < input[min])
        {
            min = i;
            while (min >= sellCandidates.top())
            {
                // i may be way later than top candidates
                sellCandidates.pop();
            }
            int diff = input[sellCandidates.top()] - input[min];
            if (diff > profit)
            {
                buy = min;
                sell = sellCandidates.top();
                profit = diff;
            }
        }
    }
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
// Multiple transactions. But two transactions cannot overlap, i.e., must
// sell before buy again. However, sell and buy can happen on the same day.
// Use as less transactions as possible.
static void maxProfit2(const int *input, int length, vector<int> &buy, vector<int> &sell, vector<int> &profit)
{
    if (input == nullptr || length < 2)
        return;
    int i = 0;
    int j = 0;
    while (j < length)
    {
        while (j + 1 < length && input[j + 1] >= input[j])
            j++;
        if (i < j)
        {
            // input[i..j] is increasing
            buy.push_back(i);
            sell.push_back(j);
            profit.push_back(input[j] - input[i]);
        }
        i = j + 1;
        j++;
    }
}

// At most two transactions. But two transactions cannot overlap,
// i.e., must sell before buy again. However, sell and buy can happen on the same day.
static void BuyAndSellTwoTransactions(const int *input, int length, vector<int> &buy, vector<int> &sell, vector<int> &profit)
{
    if (input == nullptr || length < 2)
        return;

    // Find one transaction during input[begin..end]
    auto maxProfit = [&](int begin, int end, int &buy, int &sell, int &profit) {
        int min = begin;
        buy = begin;
        sell = begin;
        profit = 0;
        if (end == begin)
            return;
        for (int i = begin + 1; i <= end; i++)
        {
            if (input[i] < input[min])
            {
                min = i;
            }
            else
            {
                if (input[i] - input[min] > profit)
                {
                    buy = min;
                    sell = i;
                    profit = input[i] - input[min];
                }
            }
        }
    };

    int buy1 = 0;
    int sell1 = 0;
    int profit1 = 0;
    int buy2 = 0;
    int sell2 = 0;
    int profit2 = 0;

    int b1 = 0;
    int s1 = 0;
    int p1 = 0;
    int b2 = 0;
    int s2 = 0;
    int p2 = 0;
    int i = 0;
    while (i < length - 1)
    {
        // Increase i so that [0..i] contains one more increasing subarray
        while (i < length - 1 && input[i + 1] <= input[i])
            i++;
        if (i == length - 1)
            break;
        while (i < length - 1 && input[i + 1] > input[i])
            i++;

        // Find the max transaction before i
        maxProfit(b1, i, b1, s1, p1);

        // Find the max transaction after i
        if (i > b2)
        {
            // If i <= b2, then no need to reevaluate because b2/s2 is already maximum after i
            maxProfit(i, length - 1, b2, s2, p2);
        }

        if (p1 + p2 > profit1 + profit2)
        {
            buy1 = b1;
            sell1 = s1;
            profit1 = p1;
            buy2 = b2;
            sell2 = s2;
            profit2 = p2;
        }

        i++;
    }

    int b3;
    int s3;
    int p3;
    maxProfit(0, length - 1, b3, s3, p3);
    if (p3 > profit1 + profit2)
    {
        buy.push_back(b3);
        sell.push_back(s3);
        profit.push_back(p3);
    }
    else
    {
        buy.push_back(buy1);
        sell.push_back(sell1);
        profit.push_back(profit1);
        buy.push_back(buy2);
        sell.push_back(sell2);
        profit.push_back(profit2);
    }
}
// Linear
static void BuyAndSellTwoTransactions2(const int *input, int length, vector<int> &buy, vector<int> &sell, vector<int> &profit)
{
    if (input == nullptr || length < 2)
        return;

    // Record the maximum two transactions
    int buy1 = 0;
    int sell1 = 0;
    int buy2 = 0;
    int sell2 = 0;
    // Record the maximum transactions
    int buym = 0;
    int sellm = 0;
    // Record the latest potential sell-buy candidate
    int i = 0;
    int j = 0;
    while (j < length)
    {
        while (j + 1 < length && input[j] >= input[j + 1])
        {
            // Find the next local minimum
            j++;
        }
        if (i < sell2 || input[i] >= input[j])
        {
            // i is the minimal in the range [sell2, j]
            // [sell2, j] may contain multiple increasing ranges
            i = j;
        }
        while (j + 1 < length && input[j] < input[j + 1])
        {
            // Find the next local maximum
            j++;
        }
        if (i == j)
        {
            j++;
            continue;
        }
        // now input[i..j] is next potential sell-buy candidate.
        // input[i..j] may contain more than one increasing ranges.
        if (buy1 == sell1)
        {
            // Get the first two increasing ranges
            buy1 = buy2;
            sell1 = sell2;
            buy2 = i;
            sell2 = j;
        }
        else
        {
            // Given [buy1, sell1], [buy2, sell2] and [i, j]
            // Compute new [buy1, sell1] and [buy2, sell2]
            // Need to compare following cases:
            // 1. [buy1, sell1], [buy2, sell2]
            // 2. [buy1, sell1], [buy2, j]
            // 3. [buy1, sell1], [i, j]
            // 4. [buy2, sell2], [i, j]
            // 5. [buy1, sell2], [i, j]
            // Start with case 1
            int b1 = buy1;
            int s1 = sell1;
            int b2 = buy2;
            int s2 = sell2;
            if (input[j] > input[s2])
            {
                // Covered case 2
                s2 = j;
            }
            if (input[j] - input[i] + input[sellm] - input[buym] >
                input[s2] - input[b2] + input[s1] - input[b1])
            {
                // Covered case 3, 4 and 5
                b1 = buym;
                s1 = sellm;
                b2 = i;
                s2 = j;
            }
            buy1 = b1;
            sell1 = s1;
            buy2 = b2;
            sell2 = s2;
        }
        if (input[sell1] - input[buy1] > input[sellm] - input[buym])
        {
            buym = buy1;
            sellm = sell1;
        }
        if (input[sell2] - input[buy2] > input[sellm] - input[buym])
        {
            buym = buy2;
            sellm = sell2;
        }
        if (input[sell2] - input[buy1] > input[sellm] - input[buym])
        {
            buym = buy1;
            sellm = sell2;
        }
        j++;
    }
    if (input[sellm] - input[buym] >= input[sell2] - input[buy2] + input[sell1] - input[buy1])
    {
        buy.push_back(buym);
        sell.push_back(sellm);
        profit.push_back(input[sellm] - input[buym]);
    }
    else
    {
        buy.push_back(buy1);
        sell.push_back(sell1);
        profit.push_back(input[sell1] - input[buy1]);
        buy.push_back(buy2);
        sell.push_back(sell2);
        profit.push_back(input[sell2] - input[buy2]);
    }
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
// Jump Game
// Given an array of non-negative integers, you are initially positioned at
// the first index of the array. Each element in the array represents your
// maximum jump length at that position. Your goal is to reach the last index
// in the minimum number of jumps. For example: Given array A = [2,3,1,1,4]
// The minimum number of jumps to reach the last index is 2. (Jump 1 step from
// index 0 to 1, then 3 steps to the last index.) Note: The array is designed
// such that no element is 0.
// minSteps[i] = min{1 + minStep[k]} for i < k <= i + A[i]
static int Jump(int A[], int n)
{
    if (A == nullptr || n <= 1)
        return 0;
    vector<int> steps(n, 0);
    for (int i = n - 2; i >= 0; i--)
    {
        int j = i + A[i];
        if (j >= n - 1)
            steps[i] = 1;
        else
        {
            int m = steps[j];
            for (int k = j - 1; k > i; k--)
            {
                if (steps[k] < m)
                    m = steps[k];
            }
            steps[i] = 1 + m;
        }
    }
    return steps[0];
}
static int Jump2(int A[], int n)
{
    if (A == nullptr || n <= 1)
        return 0;
    map<int, int> step; // Key is the number of steps, value is the index where to take the steps
    map<int, int>::iterator it;
    step[0] = n - 1;
    for (int i = n - 2; i >= 0; i--)
    {
        int j = i + A[i];
        for (it = step.begin(); it != step.end(); it++)
        {
            if (j >= it->second)
            {
                int s = it->first + 1;
                if (i == 0)
                    return s;
                else
                    step[s] = i;
                break;
            }
        }
    }
    return 0;
}
// @greedy
static int Jump3(int A[], int n)
{
    if (A == nullptr || n <= 1)
        return 0;
    int currentIndex = A[0];      // max distance current step can reach
    int nextIndex = currentIndex; // max distance next step can reach
    int step = 1;
    int i = 1;
    while (currentIndex < n - 1 && i <= currentIndex)
    {
        if (i + A[i] > nextIndex)
            nextIndex = i + A[i];
        i++;
        if (i > currentIndex)
        {
            step++;
            currentIndex = nextIndex;
        }
    }
    return step;
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

// Allocate candies to children with ratings.
// Each child gets at least one candy.
// The children with higher rating get more candies than their neighbors.
static int AllocateCandy(int ratings[], int length, int amount[])
{
    amount[0] = 1;
    // Increasing range has amount [2, 3, ...]
    // Decreasing range has amout [1, 0, -1, ...]
    for (int i = 1; i < length; i++)
    {
        if (ratings[i] > ratings[i - 1])
            amount[i] = amount[i - 1] <= 1 ? 2 : amount[i - 1] + 1;
        else if (ratings[i] == ratings[i - 1])
            amount[i] = amount[i - 1];
        else
            amount[i] = amount[i - 1] > 1 ? 1 : amount[i - 1] - 1;
    }
    // Scan backward and compensate negative amount with a delta
    // so that the minimum amout is 1.
    int delta = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        if (amount[i] > 1)
        {
            if (i < length - 1)
                if (ratings[i] == ratings[i + 1])
                    amount[i] = amount[i + 1];
            if (amount[i] <= 1 + delta)
                amount[i] = 2 + delta;
            delta = 0;
        }
        else
        {
            if (delta == 0)
                delta = 1 - amount[i];
            amount[i] += delta;
        }
    }
    int s = 0;
    for (int i = 0; i < length; i++)
        s += amount[i];
    return s;
}
static int AllocateCandy2(int ratings[], int length, int amount[])
{
    amount[0] = 1;
    // Increasing range has amount [2, 3, ...]
    // Decreasing range has amout [0, 0, ...]
    for (int i = 1; i < length; i++)
    {
        if (ratings[i] > ratings[i - 1])
            amount[i] = amount[i - 1] == 0 ? 2 : amount[i - 1] + 1;
        else if (ratings[i] == ratings[i - 1])
            amount[i] = amount[i - 1];
        else
            amount[i] = 0;
    }
    if (amount[length - 1] == 0)
        amount[length - 1] = 1;
    for (int i = length - 2; i >= 0; i--)
    {
        if (amount[i] == 0)
        {
            if (ratings[i] < ratings[i + 1])
                amount[i] = 1;
            else if (ratings[i] == ratings[i + 1])
                amount[i] = amount[i + 1];
            else
                amount[i] = amount[i + 1] + 1;
        }
        else
        {
            if (ratings[i] > ratings[i + 1] && amount[i] <= amount[i + 1])
                amount[i] = amount[i + 1] + 1;
            else if (ratings[i] == ratings[i + 1])
                amount[i] = amount[i + 1];
        }
    }
    int s = 0;
    for (int i = 0; i < length; i++)
        s += amount[i];
    return s;
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
static void sortColors2(int A[], int n)
{
    if (A == nullptr || n <= 1)
        return;

    int i = 0;
    int j = 0;
    int k = n - 1;
    int t;
    while (i < k)
    {
        while (A[i] == 0)
            i++;
        while (A[k] == 2)
            k--;
        if (i >= k)
            return;
        // A[i] in {1,2}
        // A[k] in {0,1}
        if (A[i] > A[k])
        {
            //    A[i] = 1 && A[k] = 0
            // || A[i] = 2 && A[k] = {0,1}
            t = A[i];
            A[i] = A[k];
            A[k] = t;
        }
        else
        {
            // A[i] == A[k] == 1
            if (j <= i)
                j = i + 1;
            while (A[j] == 1)
                j++;
            if (j >= k)
                return;
            if (A[j] == 0)
            {
                t = A[i];
                A[i] = A[j];
                A[j] = t;
            }
            else
            { // A[j] == 2
                t = A[k];
                A[k] = A[j];
                A[j] = t;
            }
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
// Comparer Design:
// It will produce Runtime Error simply because you provide the sort() with a
// wrong comparator.
// 1. A correct comparator should have determined behavior, i.e. return the same
//    result on same input.
// 2. The result should be transitive, i.e., if you return true for a<b and b<c,
//    you should return true for a<c
// 3. The result should not contain conflicts, e.g., if you return true for a<b,
//    you should return false for b<a
// 4. return false for both a<b and b<a will means that a == b.
// Violating the above rules and trying to pass an invalid comparator to sort()
// will result in undefined behavior, usually crash.
static bool IntervalLess(const Interval &i1, const Interval &i2)
{
    if (i1.start < i2.start)
        return true;
    if (i1.start == i2.start)
    {
        // cannot use <=, otherwise violates 3.
        return i1.end < i2.end;
    }
    return false;
}
static vector<Interval> MergeIntervals(vector<Interval> &intervals)
{
    vector<Interval> output;
    int len = intervals.size();
    if (len == 0)
        return output;
    sort(intervals.begin(), intervals.end(), IntervalLess);
    output.push_back(intervals[0]);
    int i = 0;
    for (int j = 1; j < len; j++)
    {
        if (output[i].end < intervals[j].start)
        {
            output.push_back(intervals[j]);
            i++;
        }
        else
        {
            output[i].start = min(output[i].start, intervals[j].start);
            output[i].end = max(output[i].end, intervals[j].end);
        }
    }
    return output;
}

// Given a set of non-overlapping intervals, insert a new interval into the
// intervals (merge if necessary). Example 1: Given intervals [1,3],[6,9],
// insert and merge [2,5] in as [1,5],[6,9]. Example 2: Given [1,2],[3,5],
// [6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
// This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
static vector<Interval> InsertMergeInterval(vector<Interval> &intervals, Interval newInterval)
{
    vector<Interval> output;
    for_each(intervals.begin(), intervals.end(), [&](Interval i) {
        if (i.end < newInterval.start || newInterval.end < i.start)
        {
            output.push_back(i);
        }
        else
        {
            newInterval.start = min(newInterval.start, i.start);
            newInterval.end = max(newInterval.end, i.end);
        }
    });
    output.push_back(newInterval);
    return output;
}

// Given a set of non-overlapping intervals, insert a new interval into the
// intervals (merge if necessary). You may assume that the intervals were
// initially sorted according to their start times. Example 1: Given intervals
// [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9]. Example 2: Given
// [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],
// [12,16]. This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
static vector<Interval> InsertMergeSortedInterval(vector<Interval> &intervals, Interval newInterval)
{
    vector<Interval> output;
    int len = intervals.size();
    int i = 0;
    while (i < len && intervals[i].end < newInterval.start)
        output.push_back(intervals[i++]);
    output.push_back(newInterval);
    int j = i;
    while (j < len && output[i].end >= intervals[j].start)
    {
        output[i].start = min(output[i].start, intervals[j].start);
        output[i].end = max(output[i].end, intervals[j].end);
        j++;
    }
    while (j < len)
        output.push_back(intervals[j++]);
    return output;
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
// 0, k, 2k, 3k, ..., (n-1)k, nk
// 0, k % n, 2k % n, 3k % n, ..., (n-1)k % n, nk % n = 0
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
// Let s(i, j) be the solution of choosing j numbers out of {1, 2, ..., i}
// then we need s(n, k).
// s(n, k) = s(n-1, k-1) + s(n-1, k)
// where s(i-1, j-1) contains solutions each of which contains i, and
// s(i-1, j) contains solutions each of which does not contain i.
static vector<vector<int>> combine2(int n, int k)
{
    if (n < k)
        return vector<vector<int>>{{}};
    function<void(int, int, map<pair<int, int>, vector<vector<int>>> &)>
        combine = [&](int i, int j, map<pair<int, int>, vector<vector<int>>> &s) {
            pair<int, int> p = make_pair(i, j);
            s[p] = vector<vector<int>>{};

            if (i <= 0 || j <= 0 || i < j)
            {
                s[p].push_back(vector<int>{});
                return;
            }

            if (i == j)
            {
                vector<int> v;
                for (int k = 1; k <= j; k++)
                {
                    v.push_back(k);
                }
                s[p].push_back(v);
                return;
            }

            pair<int, int> q1 = make_pair(i - 1, j - 1);
            if (s.find(q1) == s.end())
                combine(i - 1, j - 1, s);
            for_each(s[q1].begin(), s[q1].end(), [&](vector<int> &v) {
                vector<int> ex(v.begin(), v.end());
                ex.push_back(i);
                s[p].push_back(ex);
            });

            pair<int, int> q2 = make_pair(i - 1, j);
            if (s.find(q2) == s.end())
                combine(i - 1, j, s);
            for_each(s[q2].begin(), s[q2].end(), [&](vector<int> &v) {
                s[p].push_back(v);
            });
        };

    map<pair<int, int>, vector<vector<int>>> sets;
    combine(n, k, sets);
    pair<int, int> p = make_pair(n, k);
    return sets[p];
}
// Let s(i, j) be the solution of choosing j numbers out of {1, 2, ..., i}
// then we need s(n, k).
// s(n, k) = s(n-1, k-1) + s(n-1, k)
//
// s(1,1)
// s(2,1)     s(2,2)
// s(3,1)     s(3,2)     s(3,3)
// s(4,1)     s(4,2)     s(4,3)     s(4,4)
// ......     ......     ......     ......
// ......     ......     ......     ......  ......
// ......     ......     ......     ......  ...... ......
// ......     ......     ......     ......  ...... s(k,k-1)   s(k,k)
// ......     ......     ......     ......  ...... s(k+1,k-1) s(k+1,k)
// ......     ......     ......     ......  ...... ......     ......
// ......     ......     ......     ......  ...... ......     ......
// s(n-k+1,1) s(n-k+1,2) ......     ......  ...... ......     ......
//            s(n-k+2,2) ......     ......  ...... ......     ......
//                       s(n-k+2,3) ......  ...... ......     ......
//                                  ......  ...... ......     ......
//                                          ...... ......     ......
//                                                 s(n-1,k-1) s(n-1,k)
//                                                            s(n,k)
//
// [TODO] Use subset algorithm to solve this problem
static vector<vector<int>> combine3(int n, int k)
{
    if (n <= 0 || k <= 0 || n < k)
        return vector<vector<int>>{{}};

    // Represent a column
    vector<vector<vector<int>>> s(n - k + 1, vector<vector<int>>{{}});

    for (int j = 1; j <= k; j++)
    {
        // s(j,j) = {{1,2,...,j}}
        s[0][0].push_back(j);
        for (int i = 1; i <= n - k; i++)
        {
            // Extend s(i,j) by adding i+j to each of s(i-1,j-1)
            for_each(s[i].begin(), s[i].end(), [&](vector<int> &v) {
                v.push_back(i + j);
            });
            // Extend s(i,j) by adding s(i-1,j)
            for_each(s[i - 1].begin(), s[i - 1].end(), [&](vector<int> &v) {
                s[i].push_back(v);
            });
        }
    }

    return s[n - k];
}
static vector<vector<int>> combine4(int n, int k)
{
    vector<vector<int>> sets = {vector<int>{}};
    vector<vector<int>> output = {};
    for (int i = 1; i <= n; i++)
    {
        int size = sets.size();
        for (int j = 0; j < size; j++)
        {
            if ((int)sets[j].size() < k)
            {
                vector<int> ex(sets[j].begin(), sets[j].end());
                ex.push_back(i);
                if ((int)ex.size() == k)
                {
                    output.push_back(ex);
                }
                else
                {
                    sets.push_back(ex);
                }
            }
        }
    }
    return output;
}
static vector<vector<int>> combine5(int n, int k)
{
    function<void(vector<int>, int, int, vector<vector<int>> &)>
        solve = [&](vector<int> pre, int i, int k1, vector<vector<int>> &s) {
            if (k1 == 0)
            {
                s.push_back(pre);
                return;
            }
            if (n - i + 1 == k1)
            {
                // pre contains i - 1 numbers
                // There k1 numbers from i to n
                for (int j = i; j <= n; j++)
                {
                    pre.push_back(j);
                }
                s.push_back(pre);
                return;
            }
            for (int j = i; j <= n - k1 + 1; j++)
            {
                vector<int> p(pre.begin(), pre.end());
                p.push_back(j);
                solve(p, j + 1, k1 - 1, s);
            }
        };
    vector<vector<int>> set = {};
    solve(vector<int>{}, 1, k, set);
    return set;
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

namespace CoinChange
{
// Given an amount n and a set of coin denominations:
// d_0, d_1, d_2, ......, d_(k-1)
// The minimum count of coins to make up n:
// N(n) = 1 + min{N(n - d_0), N(n - d_1), ..., N(n - d_(k-1))}
static void ComputeMinCounts(unsigned int amount, vector<unsigned int> &denominations, vector<pair<unsigned int, unsigned int>> &counts)
{
    // Sort coins increasingly
    sort(denominations.begin(), denominations.end());

    // counts[i] tracks the min count to make up amount i, and
    // the last change coin picked.
    counts.push_back(make_pair(0, 0));
    counts.push_back(make_pair(1, 1));
    for (unsigned int i = 2; i <= amount; i++)
    {
        unsigned int minCount = amount;
        unsigned int change;
        unsigned int j = 0;
        while (j < denominations.size() && denominations[j] <= i)
        {
            if (counts[i - denominations[j]].first < minCount)
            {
                minCount = counts[i - denominations[j]].first;
                change = denominations[j];
            }

            j++;
        }

        counts.push_back(make_pair(1 + minCount, change));
    }
}
static void ComputeSolution(unsigned int amount, vector<unsigned int> &denominations, map<unsigned int, unsigned int> &changes)
{
    vector<pair<unsigned int, unsigned int>> counts;
    ComputeMinCounts(amount, denominations, counts);
    int i = amount;
    while (i > 0)
    {
        unsigned int c = counts[i].second;
        if (changes.find(c) == changes.end())
        {
            changes[c] = 1;
        }
        else
        {
            changes[c]++;
        }

        i -= (int)c;
    }
}

static unsigned int GreedySolution(unsigned int amount, vector<unsigned int> &denominations, map<unsigned int, unsigned int> &changes)
{
    function<bool(unsigned int, unsigned int)>
        greater = [&](unsigned int first, unsigned int second) -> bool {
        return first > second;
    };

    // Sort in decreasing order
    sort(denominations.begin(), denominations.end(), greater);

    for_each(denominations.begin(), denominations.end(), [&](unsigned int d) {
        if (amount == 0)
            return;

        if (amount >= d)
        {
            unsigned int count = amount / d;
            changes[d] = count;
            amount = amount % d;
        }
    });

    // Return what ever cannot be changed, e.g. the minimum denomination is not 1.
    return amount;
}

// http://leetcode.com/2010/09/print-all-combinations-of-number-as-sum.html
// Compute all sets of changes sum up to a given ammount
static void ComputeAllSolutions(unsigned int amount, vector<unsigned int> &denominations, vector<map<unsigned int, unsigned int>> &changes)
{
    // [TODO] no need to sort if use minIndex instead of minD in compute()
    sort(denominations.begin(), denominations.end());

    function<void(int, unsigned int, map<unsigned int, unsigned int> &)>
        compute = [&](int sum, unsigned int minD, map<unsigned int, unsigned int> &s) {
            for_each(denominations.begin(), denominations.end(), [&](unsigned int d) {
                if (d >= minD && sum >= (int)d)
                {
                    // Since denominations is already sorted, we can use
                    // minD as a gate to avoid to recompute solutions with smaller denoms.
                    map<unsigned int, unsigned int> copy(s);
                    if (copy.find(d) == copy.end())
                    {
                        copy[d] = 1;
                    }
                    else
                    {
                        copy[d]++;
                    }

                    if (sum == (int)d)
                    {
                        changes.push_back(copy);
                    }
                    else
                    {
                        compute(sum - d, d, copy);
                    }
                }
            });
        };

    map<unsigned int, unsigned int> s;
    compute(amount, denominations.front(), s);
}

// http://leetcode.com/2010/09/print-all-combinations-of-number-as-sum.html
// Compute all sub sets of changes sum up to a given ammount.
// Duplication of a change is disallowed.
static void ComputeSubSetSolutions(unsigned int amount, vector<unsigned int> &denominations, vector<map<unsigned int, unsigned int>> &changes)
{
    // [TODO] no need to sort if use minIndex instead of minD in compute()
    sort(denominations.begin(), denominations.end());

    function<void(int, unsigned int, map<unsigned int, unsigned int> &)>
        compute = [&](int sum, unsigned int minD, map<unsigned int, unsigned int> &s) {
            for_each(denominations.begin(), denominations.end(), [&](unsigned int d) {
                if (d >= minD && sum >= (int)d)
                {
                    // Since denominations is already sorted, we can use
                    // minD as a gate to avoid to recompute solutions with smaller denoms.
                    map<unsigned int, unsigned int> copy(s);
                    if (copy.find(d) == copy.end())
                    {
                        copy[d] = 1;
                    }
                    else
                    {
                        copy[d]++;
                    }

                    if (sum == (int)d)
                    {
                        changes.push_back(copy);
                    }
                    else
                    {
                        compute(sum - d, d + 1, copy);
                    }
                }
            });
        };

    map<unsigned int, unsigned int> s;
    compute(amount, denominations.front(), s);
}
} // namespace CoinChange

// Given a phone digit string, return all possible letter combinations
// that the number could represent. A mapping of digit to letters (just
// like on the telephone buttons) is given below.
//  0  { ' ' }
//  1  { '#' }
//  2  { 'a', 'b', 'c' }
//  3  { 'd', 'e', 'f' }
//  4  { 'g', 'h', 'i' }
//  5  { 'j', 'k', 'l' }
//  6  { 'm', 'n', 'o' }
//  7  { 'p', 'q', 's' }
//  8  { 't', 'u', 'v' }
//  9  { 'w', 'x', 'y', 'z' }
// Input:Digit string "23"
// Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
static vector<string> LetterCombinationsOfPhoneNumbers(const string &digits)
{
    if (digits.length() == 0)
        return vector<string>{};

    function<void(const string &, int, const string &, map<char, vector<char>> &, vector<string> &)>
        combine = [&](const string &s, int i, const string &r, map<char, vector<char>> &m, vector<string> &o) {
            if (i == (int)s.length())
            {
                o.push_back(r);
                return;
            }
            if (m.find(s[i]) == m.end())
            {
                // Why need this? Should not throw an error?
                combine(s, i + 1, r, m, o);
                return;
            }
            for_each(m[s[i]].begin(), m[s[i]].end(), [&](char c) {
                string t(r);
                t.append(1, c);
                combine(s, i + 1, t, m, o);
            });
        };

    map<char, vector<char>> m;
    m['0'] = {' '};
    m['1'] = {'#'};
    m['2'] = {'a', 'b', 'c'};
    m['3'] = {'d', 'e', 'f'};
    m['4'] = {'g', 'h', 'i'};
    m['5'] = {'j', 'k', 'l'};
    m['6'] = {'m', 'n', 'o'};
    m['7'] = {'p', 'q', 'r', 's'};
    m['8'] = {'t', 'u', 'v'};
    m['9'] = {'w', 'x', 'y', 'z'};

    vector<string> o;
    combine(digits, 0, "", m, o);
    return o;
}

// Given n non-negative integers representing the histogram's bar height
// where the width of each bar is 1, find the area of largest rectangle in
// the histogram. One example histogram has width of each bar 1, given
// height = [2,1,5,6,2,3]. The largest rectangle has area = 10 unit, which
// is under the 3rd and 4th columns. Note: the bars between two sides of
// rectangle must have the height no less than the minimum height of the two sides.
static int LargestRectangleInHistogram(const vector<int> &height)
{
    if (height.size() == 0)
        return 0;

    // Track rectangle [i, j] with area a such that rec[i] = <j, a>;
    map<int, pair<int, int>> rec = {{0, make_pair(0, height[0])}};
    int maxArea = height[0];

    for (int i = 1; i < (int)height.size(); i++)
    {
        if (height[i] == 0)
        {
            rec.clear();
            continue;
        }

        for (map<int, pair<int, int>>::iterator it = rec.begin(); it != rec.end(); it++)
        {
            if (height[i] < it->second.second)
            {
                it->second.second = height[i];
            }

            it->second.first++;

            // TODO: Can this be done only when height[i] = 0?
            int area = (it->second.first - it->first + 1) * it->second.second;
            if (area > maxArea)
            {
                maxArea = area;
            }
        }

        if (height[i] > height[i - 1])
        {
            rec[i] = make_pair(i, height[i]);
            if (height[i] > maxArea)
            {
                maxArea = height[i];
            }
        }
    }

    return maxArea;
}
static int LargestRectangleInHistogram2(const vector<int> &height)
{
    if (height.size() == 0)
        return 0;

    int maxArea = 0;
    stack<int> rec;
    for (int i = 0; i < (int)height.size(); i++)
    {
        while (!rec.empty() && height[rec.top()] > height[i])
        {
            int t = rec.top();
            rec.pop();
            // area [t, i-1] is a rectangle and the min height is at t
            int area = height[t] * (i - 1 - (rec.empty() ? -1 : rec.top()));
            if (area > maxArea)
                maxArea = area;
        }
        rec.push(i);
    }
    // Now rec contains indices of non-decreasing elements
    // including the last element of height at the end.
    while (!rec.empty())
    {
        int t = rec.top();
        rec.pop();
        // area [t, n-1] is a rectangle and the min height is at t
        int area = height[t] * ((int)height.size() - 1 - (rec.empty() ? -1 : rec.top()));
        if (area > maxArea)
            maxArea = area;
    }

    return maxArea;
}
// This is wrong, e.g., for [2 1 2] it returns 2 but answer should be 3
static int LargestRectangleInHistogram3(const vector<int> &height)
{
    if (height.empty())
        return 0;

    int maxArea = height[0];
    int i = 0;
    int j = 1;
    int n = (int)height.size();
    while (j < n)
    {
        // Find [i, j-1] where elements in between are no less than min of boundaries
        while (j < n && height[j - 1] <= height[j])
            j++;
        while (j < n && height[j - 1] >= height[j])
            j++;
        int p = i;
        int q = j - 1;
        while (p <= q)
        {
            maxArea = std::max(maxArea,
                               (q - p + 1) * std::min(height[p], height[q]));
            if (height[p] < height[q])
                p++;
            else
                q--;
        }
        i = j - 1;
    }
    return maxArea;
}

// Given n non-negative integers representing an elevation map where the
// width of each bar is 1, compute how much water it is able to trap after
// raining. For example, Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
static int TrapWater(int A[], int n)
{
    if (A == nullptr || n <= 2)
        return 0;

    function<int(int[], int, int)>
        count = [&](int a[], int i, int j) -> int {
        int m = min(a[i], a[j]);
        int s = 0;
        for (int k = i + 1; k < j; k++)
        {
            s += (m - a[k]);
        }
        return s;
    };

    // contains non-increasing integers
    stack<int> tips;
    tips.push(0);
    int i;
    int v = 0;
    for (int j = 1; j < n; j++)
    {
        while (!tips.empty() && A[tips.top()] < A[j])
        {
            i = tips.top();
            tips.pop();
        }
        if (tips.empty())
        {
            // Now A[i] and A[j] are the two most higher tips seen so far
            // and A[i] < A[j]
            if (j - i > 1)
            {
                v += count(A, i, j);
            }
        }
        tips.push(j);
    }

    if (tips.size() == 1)
        return v; // A is an increasing sequence

    int j = tips.top();
    tips.pop();
    while (!tips.empty())
    {
        // A[i] >= A[j]
        i = tips.top();
        if (j - i > 1)
        {
            v += count(A, i, j);
        }
        j = i;
        tips.pop();
    }

    return v;
}
// This algorithm is wrong.
// Not every tip is a valid tip.
// If a tip is trapped between two higher tips, then it should be removed.
static int TrapWater2(int A[], int n)
{
    if (A == nullptr || n <= 2)
        return 0;

    stack<int> tips;
    if (A[0] > A[1])
        tips.push(0);
    for (int i = 1; i < n; i++)
    {
        if (A[i - 1] < A[i] && (i == n - 1 || A[i] >= A[i + 1]))
        {
            // This loop is wrong because tips[0] can be the lowest tip
            // e.g., [1, 0, 2, 0, 3]
            while (tips.size() > 1 && A[tips.top()] < A[i])
            {
                tips.pop();
            }
            tips.push(i);
        }
    }

    if (tips.size() == 1)
        return 0;

    int v = 0;
    int j = tips.top();
    tips.pop();
    while (!tips.empty())
    {
        int i = tips.top();
        if (j - i > 1)
        {
            int m = min(A[i], A[j]);
            for (int k = i + 1; k < j; k++)
            {
                if (A[k] < m)
                {
                    v += (m - A[k]);
                }
            }
        }
        j = i;
        tips.pop();
    }

    return v;
}

// Container With Most Water
// Given n non-negative integers a1, a2, ..., an, where each represents a
// point at coordinate (i, ai). n vertical lines are drawn such that the two
// endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together
// with x-axis forms a container, such that the container contains the most water.
// Note: You may not slant the container.
static int MaxContainerArea(vector<int> &height)
{
    int n = height.size();
    if (n <= 1)
        return 0;
    int l = 0;
    int h = n - 1;
    int a = 0;
    while (l < h)
    {
        a = max(a, (h - l) * min(height[l], height[h]));
        if (height[l] < height[h])
            l++;
        else
            h--;
    }
    return a;
}
static int MaxContainerArea2(vector<int> &height)
{
    int n = height.size();
    if (n <= 1)
        return 0;
    vector<int> begin = {0};
    for (int i = 1; i < n; i++)
    {
        if (height[i] > height[begin.back()])
            begin.push_back(i);
    }
    // begin contains increasing elements
    vector<int> end = {n - 1};
    for (int i = n - 2; i >= 0; i--)
    {
        if (height[i] > height[end.front()])
            end.insert(end.begin(), i);
    }
    // end contains decreasing elements
    int a = 0;
    for (int j = 0; j < (int)end.size(); j++)
    {
        int i = 0;
        while (i < (int)begin.size() && begin[i] < end[j])
        {
            int b = (end[j] - begin[i]) * min(height[begin[i]], height[end[j]]);
            if (b > a)
                a = b;
            i++;
        }
    }
    return a;
}

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
static char *strStr2(char *haystack, char *needle)
{
    if (*needle == '\0')
        return haystack;
    if (*haystack == '\0')
        return nullptr;
    int lh = 0;
    char *h = haystack;
    while (*h != '\0')
    {
        lh++;
        h++;
    }
    int ln = 0;
    char *n = needle;
    while (*n != '\0')
    {
        ln++;
        n++;
    }
    if (lh < ln)
        return nullptr;
    for (int i = 0; i <= lh - ln; i++, haystack++)
    {
        if (*haystack == *needle)
        {
            h = haystack;
            n = needle;
            while (*h != '\0' && *n != '\0' && *n == *h)
            {
                h++;
                n++;
            }
            if (*n == '\0')
                return haystack;
        }
    }
    return nullptr;
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
static string countAndSay2(int n)
{
    if (n <= 0)
        return "";
    string s = "1";
    for (int i = 0; i < n - 1; i++)
    {
        int j = 0;
        string o;
        while (j < (int)s.length())
        {
            int k = j;
            while (k + 1 < (int)s.length() && s[k + 1] == s[k])
                k++;
            int c = k - j + 1;
            int m = o.length();
            while (c > 0)
            {
                o.insert(m, 1, '0' + (c % 10));
                c = c / 10;
            }
            o.append(1, s[j]);
            j = k + 1;
        }
        s = o;
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

// Find the longest common prefix string amongst an array of strings
static string LongestCommonPrefix(vector<string> &strs)
{
    string p;
    int n = strs.size();
    if (n == 0)
        return p;
    int i = 0;
    while (i < (int)strs[0].size())
    {
        char c = strs[0][i];
        for (int j = 1; j < n; j++)
        {
            if (i == (int)strs[j].length() || strs[j][i] != c)
                return p;
        }
        p.append(1, c);
        i++;
    }
    return p;
}

// Given a string containing just the characters '(' and ')',
// find the length of the longest valid (well-formed) parentheses substring.
// For "(()", the longest valid parentheses substring is "()", which has
// length = 2. Another example is ")()())", where the longest valid parentheses
// substring is "()()", which has length = 4.
static int LongestValidParentheses(const string &s)
{
    int len = s.length();
    if (len == 0)
        return 0;

    vector<pair<int, int>> p;
    int i = 0;
    while (i + 1 < len)
    {
        if (s[i] == '(' && s[i + 1] == ')')
        {
            int j = i;
            int k = i + 1;
            while (j >= 0 && k < len && s[j] == '(' && s[k] == ')')
            {
                j--;
                k++;
            }
            p.push_back(make_pair(j + 1, k - 1));
            i = k;
        }
        else
            i++;
    }

    if (p.size() == 0)
        return 0;

    vector<pair<int, int>>::iterator it = p.begin();
    while (it + 1 != p.end())
    {
        if (it->second + 1 == (it + 1)->first)
        {
            it->second = (it + 1)->second;
            p.erase(it + 1);
        }
        else
        {
            it++;
        }
    }

    bool stop = false;
    while (!stop)
    {
        stop = true;
        for (int j = 0; j < (int)p.size(); j++)
        {
            int l = p[j].first - 1;
            int r = p[j].second + 1;
            while (l >= 0 && r < len && s[l] == '(' && s[r] == ')')
            {
                stop = false;
                p[j].first = l;
                p[j].second = r;
                l--;
                r++;
            }
        }
        it = p.begin();
        while (it + 1 != p.end())
        {
            if (it->second + 1 == (it + 1)->first)
            {
                stop = false;
                it->second = (it + 1)->second;
                p.erase(it + 1);
            }
            else
            {
                it++;
            }
        }
    }

    int m = 0;
    for (int j = 0; j < (int)p.size(); j++)
    {
        if (p[j].second - p[j].first + 1 > m)
        {
            m = p[j].second - p[j].first + 1;
        }
    }

    return m;
}
static int LongestValidParentheses2(const string &s)
{
    int len = s.length();
    if (len == 0)
        return 0;

    function<bool(int &, int &)>
        expand = [&](int &j, int &k) -> bool {
        bool e = false;
        while (j - 1 >= 0 && k + 1 < len && s[j - 1] == '(' && s[k + 1] == ')')
        {
            e = true;
            j--;
            k++;
        }
        return e;
    };

    int m = 0;
    stack<pair<int, int>> p;
    int i = 0;
    while (i + 1 < len)
    {
        if (s[i] == '(' && s[i + 1] == ')')
        {
            int j = i;
            int k = i + 1;
            expand(j, k);

            while (!p.empty() && p.top().second + 1 == j)
            {
                j = p.top().first;
                p.pop();

                if (!expand(j, k))
                    break;
            }

            if (k - j + 1 > m)
                m = k - j + 1;
            p.push(make_pair(j, k));
            i = k + 1;
        }
        else
            i++;
    }

    return m;
}
// This is wrong. e.g. "((()())((" return 0 but the answer should be 6
static int LongestValidParentheses3(const string &s)
{
    int len = s.length();
    if (len == 0)
        return 0;
    int i = -1;
    int n = -1;
    int m = 0;
    for (int j = 0; j < len; j++)
    {
        if (s[j] == '(')
        {
            if (n < 0)
            {
                n = 1;
                i = j;
            }
            else
            {
                n++;
            }
        }
        else if (s[j] == ')')
        {
            if (n == 0)
            {
                m = std::max(m, j - i);
            }
            n--;
        }
    }
    if (n == 0)
    {
        m = std::max(m, len - i);
    }
    return m;
}
// This is wrong. e.g. "()()" return 2 but the answer should be 4
static int LongestValidParentheses4(const string &s)
{
    int m = 0;
    stack<int> p;
    for (int i = 0; i < (int)s.length(); i++)
    {
        switch (s[i])
        {
        case '(':
            p.push(i);
            break;
        case ')':
            if (!p.empty())
            {
                m = std::max(m, i - p.top() + 1);
                p.pop();
            }
            break;
        default:
            break;
        }
    }
    return m;
}

// Given n pairs of parentheses, write a function to generate all combinations
// of well-formed parentheses. For example, given n = 3, a solution set is:
// "((()))", "(()())", "(())()", "()(())", "()()()"
static vector<string> GenerateParentheses(int n)
{
    if (n <= 0)
        return vector<string>{};

    function<void(int, int, map<pair<int, int>, vector<string>> &)>
        solve = [&](
                    // l <= r
                    int l, // count '(' needed
                    int r, // count ')' needed
                    map<pair<int, int>, vector<string>> &m) {
            pair<int, int> p = make_pair(l, r);
            m[p] = vector<string>{};
            string s;
            for (int i = 1; i < l; i++)
            {
                s.append(1, '(');
                string t(s);
                for (int j = 1; j <= r - l + i; j++)
                {
                    t.append(1, ')');
                    // l - i <= r - j
                    pair<int, int> q = make_pair(l - i, r - j);
                    if (m.find(q) == m.end())
                        solve(l - i, r - j, m);
                    for_each(m[q].begin(), m[q].end(), [&](string &u) {
                        string v(t);
                        v.append(u);
                        m[p].push_back(v);
                    });
                }
            }
            s.append(1, '(');
            s.append(r, ')');
            m[p].push_back(s);
        };

    map<pair<int, int>, vector<string>> m;
    solve(n, n, m);
    pair<int, int> p = make_pair(n, n);
    return m[p];
}
static vector<string> GenerateParentheses2(int n)
{
    if (n <= 0)
        return vector<string>{};
    if (n == 1)
        return vector<string>{"()"};

    function<void(string, int, int, int, vector<string> &)>
        solve = [&](
                    string s,
                    int l, // count '(' in s
                    int r, // count ')' in s
                    int n,
                    vector<string> &o) {
            for (int i = 1; i < n - l; i++)
            {
                s.append(1, '(');
                string t(s);
                for (int j = 1; j <= l - r + i; j++)
                {
                    t.append(1, ')');
                    solve(t, l + i, r + j, n, o);
                }
            }
            s.append(1, '(');
            s.append(n - r, ')');
            o.push_back(s);
        };

    vector<string> result;
    string s;
    solve(s, 0, 0, n, result);
    return result;
}
// This algorithm is wrong
static vector<string> GenerateParentheses3(int n)
{
    vector<string> result;
    if (n <= 0)
        return result;
    result.push_back("()");
    if (n == 1)
        return result;
    for (int i = 2; i <= n; i++)
    {
        int j = result.size();
        for (int k = 0; k < j; k++)
        {
            string s = result.front();
            result.erase(result.begin());
            string o = s;
            o.append("()");
            result.push_back(o);
            bool symmetric = true;
            int a = 0;
            int b = o.length() - 1;
            while (a < b)
            {
                if (o[a] == o[b])
                {
                    symmetric = false;
                    break;
                }
                a++;
                b--;
            }
            if (!symmetric)
            {
                o = "()";
                o.append(s);
                result.push_back(o);
            }
            o = "(";
            o.append(s);
            o.append(")");
            result.push_back(o);
        }
    }
    return result;
}
static vector<string> GenerateParentheses4(int n)
{
    if (n <= 0)
        return vector<string>{};
    if (n == 1)
        return vector<string>{"()"};

    function<void(string, int, int, int, vector<string> &)>
        solve = [&](
                    string s,
                    int l, // count '(' in s
                    int r, // count ')' in s
                    int n,
                    vector<string> &o) {
            if (l == n)
            {
                s.append(n - r, ')');
                o.push_back(s);
                return;
            }

            string tl(s);
            tl.append(1, '(');
            solve(tl, l + 1, r, n, o);
            if (l > r)
            {
                string tr(s);
                tr.append(1, ')');
                solve(tr, l, r + 1, n, o);
            }
        };

    vector<string> result;
    string s;
    solve(s, 0, 0, n, result);
    return result;
}

// Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
// determine if the input string is valid. The brackets must close in the correct
// order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
static bool IsValidParentheses(const string &s)
{
    if (s.length() == 0)
        return true;
    stack<char> p;
    for (int i = 0; i < (int)s.length(); i++)
    {
        char c = s[i];
        switch (c)
        {
        case '(':
        case '{':
        case '[':
            p.push(c);
            break;
        case ')':
            if (p.empty() || p.top() != '(')
                return false;
            p.pop();
            break;
        case '}':
            if (p.empty() || p.top() != '{')
                return false;
            p.pop();
            break;
        case ']':
            if (p.empty() || p.top() != '[')
                return false;
            p.pop();
            break;
        default:
            break;
        }
    }
    return p.empty();
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
// TODO: can we use BFS here?
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

// You are given a string, S, and a list of words, L, that are all of the
// same length. Find all starting indices of substring(s) in S that is a
// concatenation of each word in L exactly once and without any intervening
// characters. For example, given: S: "barfoothefoobarman" L: ["foo", "bar"]
// You should return the indices: [0,9]. (order does not matter).
// [TODO] Think about the simple case where each word of L is a character.
static vector<int> SubstringOfConcatenation(const string &S, vector<string> &L)
{
    vector<int> result;
    int len = S.length();
    if (len == 0 || L.size() == 0)
        return result;
    int sl = L.size() * L[0].length();
    if (len < sl)
        return result;
    map<string, int> m;
    for_each(L.begin(), L.end(), [&](string &s) {
        if (m.find(s) == m.end())
        {
            m[s] = 1;
        }
        else
        {
            m[s] += 1;
        }
    });
    for (int i = 0; i <= len - sl; i++)
    {
        string s = S.substr(i, L[0].length());
        if (m.find(s) != m.end())
        {
            map<string, int> n(m);
            for (int j = i; j < i + sl; j += L[0].length())
            {
                s = S.substr(j, L[0].length());
                if (n.find(s) == n.end())
                    break;
                if (n[s] == 1)
                    n.erase(s);
                else
                    n[s]--;
            }
            if (n.size() == 0)
                result.push_back(i);
        }
    }
    return result;
}

// Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2.
// (each operation is counted as 1 step.)
// You have the following 3 operations permitted on a word:
//  a) Insert a character
//  b) Delete a character
//  c) Replace a character
static int MinDistance(const string &word1, const string &word2)
{
    // Compute distance from w1[i:] to w2[j:]
    function<int(const string &, int, const string &, int, map<pair<int, int>, int> &)>
        distance = [&](const string &w1, int i, const string &w2, int j, map<pair<int, int>, int> &d) -> int {
        pair<int, int> p = make_pair(i, j);
        if (d.find(p) == d.end())
        {
            if (i == (int)w1.length())
            {
                // Need to insert d[p] chars to w1
                d[p] = (int)w2.length() - j;
            }
            else if (j == (int)w2.length())
            {
                // Need to delete d[p] chars from w1
                d[p] = (int)w1.length() - i;
            }
            else if (w1[i] == w2[j])
            {
                d[p] = distance(w1, i + 1, w2, j + 1, d);
            }
            else
            {
                int ins = distance(w1, i, w2, j + 1, d);
                int rep = distance(w1, i + 1, w2, j + 1, d);
                int del = distance(w1, i + 1, w2, j, d);
                int min = ins;
                if (rep < min)
                    min = rep;
                if (del < min)
                    min = del;
                d[p] = 1 + min;
            }
        }
        return d[p];
    };

    map<pair<int, int>, int> d;
    return distance(word1, 0, word2, 0, d);
}
// d[i,j]
//     j 0 1 2 3 ...... n-1
// i 0
//   1
//   2
//   .
//   m-1
//
// d[m-1][n-1] = 0,                                             if w1[m-1] == w2[n-1]
//               1,                                             if w1[m-1] != w2[n-1]
// d[m-1][j]   = n - 1 - j,                                     if w1[m-1] == w2[j]
//               1 + min { n - 1 - j, d[m-1][j+1] },            if w1[m-1] != w2[j]
// d[i][n-1]   = m - 1 - i,                                     if w1[i] == w2[n-1]
//               1 + min { m - 1 - i, d[i+1][n-1] },            if w1[i] != w2[n-1]
// d[i][j]     = d[i+1][j+1],                                   if w1[i] == w2[j]
//               1 + min { d[i][j+1], d[i+1][j+1], d[i+1][j] }, if w1[i] != w2[j]
static int MinDistance2(const string &word1, const string &word2)
{
    int m = word1.length();
    int n = word2.length();

    if (m == 0)
        return n;
    if (n == 0)
        return m;

    vector<vector<int>> d(m, vector<int>(n, 0));

    d[m - 1][n - 1] = word1[m - 1] == word2[n - 1] ? 0 : 1;

    for (int j = n - 2; j >= 0; j--)
    {
        if (word1[m - 1] == word2[j])
        {
            d[m - 1][j] = n - 1 - j;
        }
        else
        {
            d[m - 1][j] = n - 1 - j;
            if (d[m - 1][j + 1] < d[m - 1][j])
                d[m - 1][j] = d[m - 1][j + 1];
            d[m - 1][j] += 1;
        }
    }

    for (int i = m - 2; i >= 0; i--)
    {
        if (word1[i] == word2[n - 1])
        {
            d[i][n - 1] = m - 1 - i;
        }
        else
        {
            d[i][n - 1] = m - 1 - i;
            if (d[i + 1][n - 1] < d[i][n - 1])
                d[i][n - 1] = d[i + 1][n - 1];
            d[i][n - 1] += 1;
        }
    }

    for (int i = m - 2; i >= 0; i--)
    {
        for (int j = n - 2; j >= 0; j--)
        {
            if (word1[i] == word2[j])
            {
                d[i][j] = d[i + 1][j + 1];
            }
            else
            {
                d[i][j] = d[i][j + 1];
                if (d[i + 1][j + 1] < d[i][j])
                    d[i][j] = d[i + 1][j + 1];
                if (d[i + 1][j] < d[i][j])
                    d[i][j] = d[i + 1][j];
                d[i][j] += 1;
            }
        }
    }

    return d[0][0];
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
static int lengthOfLastWord3(const char *s)
{
    if (*s == '\0')
        return 0;
    while (*s == ' ')
        s++;
    int i = 0;
    while (*s != '\0')
    {
        while (*s != '\0' && *s != ' ')
        {
            i++;
            s++;
        }
        while (*s == ' ')
            s++;
        if (*s != '\0')
            i = 0;
    }
    return i;
}
static int lengthOfLastWord4(string s)
{
    int length = 0;
    size_t i = 0;
    int n = 0; // count every word encountered
    while (i < s.size())
    {
        if (s[i] == ' ')
        {
            if (n > 0)
            {
                length = n;
                n = 0;
            }
        }
        else
        {
            n++;
        }
        i++;
    }
    return n > 0 ? n : length;
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

// Given an array of words and a length L, format the text such that each line
// has exactly L characters and is fully (left and right) justified. You should
// pack your words in a greedy approach; that is, pack as many words as you can
// in each line. Pad extra spaces ' ' when necessary so that each line has
// exactly L characters. Extra spaces between words should be distributed as
// evenly as possible. If the number of spaces on a line do not divide evenly
// between words, the empty slots on the left will be assigned more spaces than
// the slots on the right. For the last line of text, it should be left justified
// and no extra space is inserted between words. For example,
// words: ["This", "is", "an", "example", "of", "text", "justification."]
// L: 16.
// Return the formatted lines as:
// [
//   "This    is    an",
//   "example  of text",
//   "justification.  "
// ]
// Note: Each word is guaranteed not to exceed L in length.
// Corner Cases:
// A line other than the last line might contain only one word. What should you
// do in this case? In this case, that line should be left-justified.
static vector<string> TextJustification(vector<string> &words, int L)
{
    if (words.size() == 0)
        return vector<string>{};
    vector<string> output;
    int i = 0;
    int j = 0;
    int count = (int)words.size();
    int len = 0;
    while (i < count && j < count)
    {
        while (j < count && len + (int)words[j].length() + j - i <= L)
        {
            len += words[j].length();
            j++;
        }
        if (j == count)
        {
            // last line with words[i..j-1]
            string line;
            for (int k = i; k < j; k++)
            {
                if (k != i)
                    line.append(1, ' ');
                line.append(words[k]);
            }
            int extra = L - len - (j - 1 - i);
            if (extra > 0)
                line.append(extra, ' ');
            output.push_back(line);
            break;
        }
        else
        {
            // one line with words[i..j-1]
            string line(words[i]);
            int totalSpaces = L - len;
            int intervals = j - 1 - i;
            if (intervals == 0)
            {
                line.append(totalSpaces, ' ');
            }
            else
            {
                int spaces = totalSpaces / intervals;
                int extra = totalSpaces % intervals;
                for (int k = i + 1; k <= i + extra; k++)
                {
                    line.append(spaces + 1, ' ');
                    line.append(words[k]);
                }
                for (int k = i + extra + 1; k < j; k++)
                {
                    line.append(spaces, ' ');
                    line.append(words[k]);
                }
            }
            output.push_back(line);
            i = j;
            len = 0;
        }
    }
    return output;
}

// The n-queens puzzle is the problem of placing n queens on an n×n chessboard
// such that no two queens attack each other. Given an integer n, return all
// distinct solutions to the n-queens puzzle. Each solution contains a distinct
// board configuration of the n-queens' placement, where 'Q' and '.' both
// indicate a queen and an empty space respectively. For example,
// There exist two distinct solutions to the 4-queens puzzle:
// [
//  [".Q..",  // Solution 1
//   "...Q",
//   "Q...",
//   "..Q."],
//  ["..Q.",  // Solution 2
//   "Q...",
//   "...Q",
//   ".Q.."]
// ]
static vector<vector<string>> NQueens(int n)
{
    if (n <= 0)
        return vector<vector<string>>{};

    function<void(vector<string> &, int, vector<vector<string>> &)>
        solve = [&](vector<string> &board, size_t line, vector<vector<string>> &solutions) {
            for (size_t i = 0; i < board[line].size(); i++)
            {
                if (board[line][i] == '.')
                {
                    vector<string> next(board);
                    next[line][i] = 'Q';
                    if (line == board.size() - 1)
                    {
                        for_each(next.begin(), next.end(), [&](string &l) {
                            for (size_t j = 0; j < l.length(); j++)
                            {
                                if (l[j] == 'X')
                                    l[j] = '.';
                            }
                        });
                        solutions.push_back(next);
                    }
                    else
                    {
                        int a = i;
                        int b = i;
                        for (size_t j = line + 1; j < board.size(); j++)
                        {
                            a--;
                            if (a >= 0)
                                next[j][a] = 'X';
                            next[j][i] = 'X';
                            b++;
                            if (b < (int)next[j].size())
                                next[j][b] = 'X';
                        }
                        solve(next, line + 1, solutions);
                    }
                }
            }
        };

    vector<vector<string>> solutions;
    vector<string> board(n, string(n, '.'));
    solve(board, 0, solutions);
    return solutions;
}

static int NQeensSolutionsCount(int n)
{
    if (n <= 0)
        return 0;

    function<int(vector<vector<bool>> &, int)>
        count = [&](vector<vector<bool>> &board, int line) -> int {
        int c = 0;
        for (size_t i = 0; i < board[line].size(); i++)
        {
            if (board[line][i] == true)
            {
                if (line == (int)board.size() - 1)
                    c++;
                else
                {
                    vector<vector<bool>> next(board);
                    next[line][i] = false;
                    int a = i;
                    int b = i;
                    bool proceed = false;
                    for (size_t j = line + 1; j < board.size(); j++)
                    {
                        a--;
                        if (a >= 0)
                            next[j][a] = false;
                        next[j][i] = false;
                        b++;
                        if (b < (int)next[j].size())
                            next[j][b] = false;
                        proceed = false;
                        for (size_t k = 0; k < next[j].size(); k++)
                        {
                            if (next[j][k] == true)
                            {
                                proceed = true;
                                break;
                            }
                        }
                        if (proceed == false)
                            break;
                    }
                    if (proceed)
                        c += count(next, line + 1);
                }
            }
        }
        return c;
    };

    vector<vector<bool>> board(n, vector<bool>(n, true));
    return count(board, 0);
}

// Write a program to solve a Sudoku puzzle by filling the empty cells.
// Empty cells are indicated by the character '.'.
// You may assume that there will be only one unique solution.
static void Sudoku(vector<vector<char>> &board)
{
    function<void(int &, int, int &, int)>
        oneStep = [&](int &i, int r, int &j, int c) {
            j++;
            j = j % c;
            if (j == 0)
            {
                i++;
                i = i % r;
            }
        };

    function<bool(
        vector<vector<char>> &,
        int,
        int,
        vector<set<char>> &,
        vector<set<char>> &,
        vector<vector<set<char>>> &,
        map<pair<int, int>, set<char>> &)>
        solve = [&](
                    vector<vector<char>> &b,
                    int i,
                    int j,
                    vector<set<char>> &row,           // existing characters on every row
                    vector<set<char>> &col,           // existing characters on every column
                    vector<vector<set<char>>> cell,   // existing characters in every 3x3 cell
                    map<pair<int, int>, set<char>> &m // available characters for every empty cell
                    ) -> bool {
        while (i != (int)b.size() - 1 || j != (int)b[i].size() - 1)
        {
            if (b[i][j] == '.')
                break;
            oneStep(i, (int)b.size(), j, (int)b[i].size());
        }
        // Now (i, j) is either empty or it is the bottom-right element of b
        if (b[i][j] != '.')
            return true;
        pair<int, int> p = make_pair(i, j);
        for (set<char>::iterator it = m[p].begin(); it != m[p].end(); it++)
        {
            char c = *it;
            if (row[i].find(c) == row[i].end() && col[j].find(c) == col[j].end() && cell[i / 3][j / 3].find(c) == cell[i / 3][j / 3].end())
            {
                b[i][j] = c;
                row[i].insert(c);
                col[j].insert(c);
                cell[i / 3][j / 3].insert(c);
                if (i == (int)b.size() - 1 && j == (int)b[i].size() - 1)
                    return true;
                int i1 = i;
                int j1 = j;
                oneStep(i1, (int)b.size(), j1, (int)b[i].size());
                if (solve(b, i1, j1, row, col, cell, m))
                    return true;
                b[i][j] = '.';
                row[i].erase(c);
                col[j].erase(c);
                cell[i / 3][j / 3].erase(c);
            }
        }
        return false;
    };

    if (board.size() == 0 || board[0].size() == 0)
        return;

    vector<set<char>> row = vector<set<char>>(9, set<char>{});
    vector<set<char>> col = vector<set<char>>(9, set<char>{});
    vector<vector<set<char>>> cell = vector<vector<set<char>>>(3, vector<set<char>>(3, set<char>{}));
    for (int i = 0; i < (int)board.size(); i++)
    {
        for (int j = 0; j < (int)board[i].size(); j++)
        {
            if (board[i][j] != '.')
            {
                row[i].insert(board[i][j]);
                col[j].insert(board[i][j]);
                cell[i / 3][j / 3].insert(board[i][j]);
            }
        }
    }
    map<pair<int, int>, set<char>> m;
    for (int i = 0; i < (int)board.size(); i++)
    {
        for (int j = 0; j < (int)board[i].size(); j++)
        {
            if (board[i][j] == '.')
            {
                pair<int, int> p = make_pair(i, j);
                m[p] = set<char>{};
                for (char c = '1'; c <= '9'; c++)
                {
                    if (row[i].find(c) == row[i].end() && col[j].find(c) == col[j].end() && cell[i / 3][j / 3].find(c) == cell[i / 3][j / 3].end())
                    {
                        m[p].insert(c);
                    }
                }
            }
        }
    }

    solve(board, 0, 0, row, col, cell, m);
    return;
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

// Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
// Below is one possible representation of s1 = "great":
//     great
//    /    \
//   gr    eat
//  / \    /  \
// g   r  e   at
//            / \
//           a   t
// To scramble the string, we may choose any non-leaf node and swap its two children.
// For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".
//     rgeat
//    /    \
//   rg    eat
//  / \    /  \
// r   g  e   at
//            / \
//           a   t
// We say that "rgeat" is a scrambled string of "great".
// Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".
//     rgtae
//    /    \
//   rg    tae
//  / \    /  \
// r   g  ta   e
//       / \
//      t   a
// We say that "rgtae" is a scrambled string of "great".
// Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
static bool IsScramble(const string &s1, const string &s2)
{
    if (s1.length() != s2.length())
        return false;
    if (s1.length() == 0)
        return true;

    int len = s1.length();

    map<char, int> m1;
    map<char, int> m2;

    for (int i = 0; i < len; i++)
    {
        if (m1.find(s1[i]) == m1.end())
            m1[s1[i]] = 1;
        else
            m1[s1[i]] += 1;
        if (m2.find(s2[i]) == m2.end())
            m2[s2[i]] = 1;
        else
            m2[s2[i]] += 1;
        // TODO: do we still need further check once two maps are equal?
        if (Equal(m1, m2))
        {
            // s1[0..i] and s2[0..i] may be scramble
            if (i == 0 || i == 1)
            {
                // s1[0] and s2[0], or s1[0..1] and s2[0..1] are scramble
                if (i == len - 1 || IsScramble(s1.substr(i + 1, len - 1 - i), s2.substr(i + 1, len - 1 - i)))
                    return true;
            }
            else if (i < len - 1)
            {
                if (IsScramble(s1.substr(0, i + 1), s2.substr(0, i + 1)) && IsScramble(s1.substr(i + 1, len - 1 - i), s2.substr(i + 1, len - 1 - i)))
                    return true;
            }
        }
    }

    m1.clear();
    m2.clear();

    for (int i = 0; i < len; i++)
    {
        int j = len - 1 - i;
        if (m1.find(s1[j]) == m1.end())
            m1[s1[j]] = 1;
        else
            m1[s1[j]] += 1;
        if (m2.find(s2[i]) == m2.end())
            m2[s2[i]] = 1;
        else
            m2[s2[i]] += 1;
        if (Equal(m1, m2))
        {
            // s1[len-1-i..len-1] and s2[0..i] may be scramble
            if (i == 0 || i == 1)
            {
                if (i == len - 1 || IsScramble(s1.substr(0, len - 1 - i), s2.substr(i + 1, len - 1 - i)))
                    return true;
            }
            else if (i < len - 1)
            {
                if (IsScramble(s1.substr(0, len - 1 - i), s2.substr(i + 1, len - 1 - i)) && IsScramble(s1.substr(len - 1 - i, i + 1), s2.substr(0, i + 1)))
                    return true;
            }
        }
    }

    return false;
}
static bool IsScramble2(const string &s1, const string &s2)
{
    if (s1.length() != s2.length())
        return false;
    if (s1.length() == 0)
        return true;

    map<pair<int, int>, map<pair<int, int>, bool>> scramble;

    function<bool(int, int, int, int)>
        isScramble = [&](int i1, int i2, int j1, int j2) -> bool {
        // check s1[i1..i2] and s2[j1..j2]
        pair<int, int> pi = make_pair(i1, i2);
        pair<int, int> pj = make_pair(j1, j2);

        if (scramble.find(pi) != scramble.end() && scramble[pi].find(pj) != scramble[pi].end())
            return scramble[pi][pj];

        if (scramble.find(pi) == scramble.end())
            scramble[pi] = map<pair<int, int>, bool>{};

        if (scramble[pi].find(pj) == scramble[pi].end())
            scramble[pi][pj] = false;

        map<char, int> m1;
        map<char, int> m2;

        for (int i = i1, j = j1; i <= i2 && j <= j2; i++, j++)
        {
            if (m1.find(s1[i]) == m1.end())
                m1[s1[i]] = 1;
            else
                m1[s1[i]] += 1;
            if (m2.find(s2[j]) == m2.end())
                m2[s2[j]] = 1;
            else
                m2[s2[j]] += 1;
            if (Equal(m1, m2))
            {
                // s1[i1..i] and s2[j1..j] may be scramble
                if (j - j1 <= 1)
                {
                    if (j == j2 || isScramble(i + 1, i2, j + 1, j2))
                    {
                        scramble[pi][pj] = true;
                        return true;
                    }
                }
                else if (j < j2)
                {
                    if (isScramble(i1, i, j1, j) && isScramble(i + 1, i2, j + 1, j2))
                    {
                        scramble[pi][pj] = true;
                        return true;
                    }
                }
            }
        }

        m1.clear();
        m2.clear();

        for (int i = i2, j = j1; i >= i1 && j <= j2; i--, j++)
        {
            if (m1.find(s1[i]) == m1.end())
                m1[s1[i]] = 1;
            else
                m1[s1[i]] += 1;
            if (m2.find(s2[j]) == m2.end())
                m2[s2[j]] = 1;
            else
                m2[s2[j]] += 1;
            if (Equal(m1, m2))
            {
                // s1[i..i2] and s2[j1..j] may be scramble
                if (j - j1 <= 1)
                {
                    if (j == j2 || isScramble(i1, i - 1, j + 1, j2))
                    {
                        scramble[pi][pj] = true;
                        return true;
                    }
                }
                else if (j < j2)
                {
                    if (isScramble(i1, i - 1, j + 1, j2) && isScramble(i, i2, j1, j))
                    {
                        scramble[pi][pj] = true;
                        return true;
                    }
                }
            }
        }

        return false;
    };

    return isScramble(0, (int)s1.length() - 1, 0, (int)s2.length() - 1);
}

// Implement wildcard pattern matching with support for '?' and '*'.
// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).
// The matching should cover the entire input string (not partial).
// The function prototype should be:
// bool isMatch(const char *s, const char *p)
// Some examples:
// isMatch("aa","a") false
// isMatch("aa","aa") true
// isMatch("aaa","aa") false
// isMatch("aa", "*") true
// isMatch("aa", "a*") true
// isMatch("ab", "?*") true
// isMatch("aab", "c*a*b") false
static bool isMatch(const char *s, const char *p)
{
    function<int(const char *)> length = [&](const char *c) -> int {
        // Count characters in c that is not '*'
        int i = 0;
        while (*c != '\0')
        {
            if (*c != '*')
                i++;
            c++;
        }
        return i;
    };

    function<bool(const char *, const char *, map<pair<const char *, const char *>, bool> &)>
        isMatchInternal = [&](const char *s, const char *p, map<pair<const char *, const char *>, bool> &m) -> bool {
        pair<const char *, const char *> c = make_pair(s, p);
        if (m.find(c) != m.end())
            return m[c];

        m[c] = false;

        int i = length(s);
        int j = length(p);
        if (i < j)
            return false;

        while (*s != '\0' && *p != '\0' && (*s == *p || *p == '?'))
        {
            ++s;
            ++p;
        }
        // Now *s == '\0' || *p == '\0' || (*s != *p && *p != '?')
        if (*s == '\0' && *p == '\0')
        {
            m[c] = true;
            return true;
        }
        if (*p == '\0' || *p != '*')
            return false;
        // Now *p == '*'
        while (*p == '*')
            p++;
        // Now *p == '\0' || *p == '?' || *p != '*'
        while (*s != '\0' && i >= j)
        {
            if ((*s == *p || *p == '?') && isMatchInternal(s + 1, p + 1, m))
            {
                m[c] = true;
                return true;
            }
            s++;
            i--;
        }
        m[c] = (*s == *p) && (i >= j);
        return m[c];
    };

    map<pair<const char *, const char *>, bool> m;
    return isMatchInternal(s, p, m);
}
// Implement regular expression matching with support for '.' and '*'.
// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.
// The matching should cover the entire input string (not partial).
// The function prototype should be:
// bool isMatch(const char *s, const char *p)
// Some examples:
// isMatch("aa","a") → false
// isMatch("aa","aa") → true
// isMatch("aaa","aa") → false
// isMatch("aa", "a*") → true
// isMatch("aa", ".*") → true
// isMatch("ab", ".*") → true
// isMatch("aab", "c*a*b") → true
static bool isMatch2(const char *s, const char *p)
{
    while (*p == '*')
        p++;
    if (*s == '\0' && *p == '\0')
        return true;
    if (*p == '\0')
        return false;
    if (*(p + 1) != '*')
    {
        if (*s != '\0' && (*s == *p || *p == '.'))
            return isMatch2(++s, ++p);
        else
            return false;
    }
    // Now *(p + 1) == '*'
    while (*s != '\0' && (*s == *p || *p == '.'))
    {
        if (isMatch2(s, p + 2))
            return true;
        s++;
    }
    // *s and *p are not matching, skip *p because *(p + 1) is '*'
    return isMatch2(s, p + 2);
}

// Minimum Window Substring
// Given a string S and a string T, find the minimum window in S which will
// contain all the characters in T in complexity O(n).
// For example,
// S = "ADOBECODEBANC"
// T = "ABC"
// Minimum window is "BANC".
// Note: If there is no such window in S that covers all characters in T, return
// the emtpy string "". If there are multiple such windows, you are guaranteed
// that there will always be only one unique minimum window in S.
static string MinWindow(const string &s, const string &t)
{
    if (s.empty() || t.empty() || s.length() < t.length())
        return "";

    map<char, int> countT;
    for (size_t i = 0; i < t.length(); i++)
    {
        if (countT.find(t[i]) == countT.end())
            countT[t[i]] = 1;
        else
            countT[t[i]] += 1;
    }

    // c1 count should be no less than c2 count
    auto compare = [&](map<char, int> &c1, map<char, int> &c2) -> bool {
        if (c1.size() != c2.size())
            return false;
        for (map<char, int>::iterator it = c1.begin(); it != c1.end(); it++)
        {
            if (c2.find(it->first) == c2.end())
                return false;
            if (c2[it->first] > it->second)
                return false;
        }
        return true;
    };

    map<char, int> countS;
    queue<pair<char, int>> indices;
    int begin = -1;
    int end = (int)s.length();
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (countT.find(s[i]) != countT.end())
        {
            if (countS.find(s[i]) == countS.end())
                countS[s[i]] = 1;
            else
                countS[s[i]] += 1;
            // indices contains a range of characters that are also in T
            indices.push(make_pair(s[i], i));
            // Shorten the range
            while (countS[indices.front().first] > countT[indices.front().first])
            {
                countS[indices.front().first] -= 1;
                indices.pop();
            }

            if (compare(countS, countT))
            {
                if (i - indices.front().second < end - begin)
                {
                    begin = indices.front().second;
                    end = i;
                }
            }
        }
    }

    if (begin == -1)
        return "";
    else
        return s.substr(begin, end - begin + 1);
}
static string MinWindow2(const string &s, const string &t)
{
    if (s.empty() || t.empty() || s.length() < t.length())
        return "";

    map<char, int> countT;
    for (size_t i = 0; i < t.length(); i++)
    {
        if (countT.find(t[i]) == countT.end())
            countT[t[i]] = 1;
        else
            countT[t[i]] += 1;
    }

    map<char, int> countS;
    int total = 0;
    queue<pair<char, int>> indices;
    int begin = -1;
    int end = (int)s.length();
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (countT.find(s[i]) != countT.end())
        {
            if (countS.find(s[i]) == countS.end())
                countS[s[i]] = 1;
            else
                countS[s[i]] += 1;

            if (countS[s[i]] <= countT[s[i]])
                total++;

            indices.push(make_pair(s[i], i));

            while (countS[indices.front().first] > countT[indices.front().first])
            {
                countS[indices.front().first] -= 1;
                indices.pop();
            }

            if (total == (int)t.length())
            {
                if (i - indices.front().second < end - begin)
                {
                    begin = indices.front().second;
                    end = i;
                }
            }
        }
    }

    if (begin == -1)
        return "";
    else
        return s.substr(begin, end - begin + 1);
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

// Validate if a given string is numeric. Some examples:
// "0" => true
// " 0.1 " => true
// "abc" => false
// "1 a" => false
// "2e10" => true
static bool IsNumber(const char *s)
{
    if (s == nullptr || *s == '\0')
        return false;
    while (*s == ' ')
        s++;
    if (*s == '\0')
        return false;
    if (*s != '+' && *s != '-' && *s != '.' && (*s < '0' || *s > '9'))
        return false;
    if ((*s == '+' || *s == '-') && *(s + 1) == '.' && (*(s + 2) == '\0' || *(s + 2) == ' '))
        return false;
    bool foundDot = *s == '.';
    if (foundDot && (*(s + 1) < '0' || *(s + 1) > '9'))
        return false;
    bool foundE = false;
    s++;
    while (*s != '\0' && *s != ' ')
    {
        switch (*s)
        {
        case '+':
        case '-':
            if (*(s - 1) != 'e' && *(s - 1) != 'E')
                return false;
            if (*(s + 1) < '0' || *(s + 1) > '9')
                return false;
            break;
        case '.':
            if (foundE || foundDot)
                return false;
            foundDot = true;
            if (*(s + 1) != '\0' && *(s + 1) != ' ' && *(s + 1) != 'e' && *(s + 1) != 'E' && (*(s + 1) < '0' || *(s + 1) > '9'))
                return false;
            break;
        case 'e':
        case 'E':
            if (foundE)
                return false;
            foundE = true;
            if (*(s - 1) != '.' && (*(s - 1) < '0' || *(s - 1) > '9'))
                return false;
            if (*(s + 1) != '+' && *(s + 1) != '-' && (*(s + 1) < '0' || *(s + 1) > '9'))
                return false;
            break;
        default:
            if (*s < '0' || *s > '9')
                return false;
            break;
        }
        s++;
    }
    while (*s == ' ')
        s++;
    if (*s == '\0')
        return true;
    else
        return false;
}

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
static string simplifyPath2(string path)
{
    int len = path.length();
    if (len == 0)
        return "";
    vector<string> tokens;
    int i = 0;
    while (i < len)
    {
        while (i < len && path[i] == '/')
            i++;
        if (i == len)
            break;
        if (path[i] == '.')
        {
            if (i + 1 == len)
                break;
            if (path[i + 1] == '/')
            {
                i += 2;
                continue;
            }
            else if (path[i + 1] == '.')
            {
                if (i + 2 == len || path[i + 2] == '/')
                {
                    if (!tokens.empty())
                    {
                        tokens.pop_back();
                    }
                    i += 3;
                    continue;
                }
            }
        }
        string token;
        int j = i;
        while (j < len && path[j] != '/')
        {
            token.append(1, path[j]);
            j++;
        }
        tokens.push_back(token);
        i = j;
    }
    string output;
    if (tokens.size() == 0)
    {
        output.append(1, '/');
    }
    else
    {
        for_each(tokens.begin(), tokens.end(), [&](string &t) {
            output.append(1, '/');
            output.append(t.begin(), t.end());
        });
    }
    return output;
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
static int numDecodings2(const string &s)
{
    if (s.size() == 0)
        return 0;
    if (s[0] < '1' || s[0] > '9')
        return 0;
    int c0 = 1;
    int c1 = 1;
    int c2;
    for (size_t i = 1; i < s.size(); i++)
    {
        if (s[i] < '0' && '9' < s[i])
            return 0;
        c2 = 0;
        if ('1' <= s[i] && s[i] <= '9')
            c2 = c1;
        if ((s[i - 1] == '1' && s[i] >= '0' && s[i] <= '9') || (s[i - 1] == '2' && s[i] >= '0' && s[i] <= '6'))
            c2 += c0;
        c0 = c1;
        c1 = c2;
    }
    return c2;
}

// Given a roman numeral, convert it to an integer.
// Input is guaranteed to be within the range from 1 to 3999.
// I can be placed before V and X to make 4 units (IV) and 9 units (IX) respectively
// X can be placed before L and C to make 40 (XL) and 90 (XC) respectively
// C can be placed before D and M to make 400 (CD) and 900 (CM) according to the same pattern
static int RomanToInt(const string &s)
{
    int n = s.length();
    if (n == 0)
        return 0;
    int i = 0;
    int r = 0;
    while (i < n)
    {
        switch (s[i])
        {
        case 'I': // 1
            if (i + 1 < n && s[i + 1] == 'V')
            {
                r += 4;
                i += 2;
            }
            else if (i + 1 < n && s[i + 1] == 'X')
            {
                r += 9;
                i += 2;
            }
            else
            {
                r += 1;
                i++;
            }
            break;
        case 'V': // 5
            r += 5;
            i++;
            break;
        case 'X': // 10
            if (i + 1 < n && s[i + 1] == 'L')
            {
                r += 40;
                i += 2;
            }
            else if (i + 1 < n && s[i + 1] == 'C')
            {
                r += 90;
                i += 2;
            }
            else
            {
                r += 10;
                i++;
            }
            break;
        case 'L': // 50
            r += 50;
            i++;
            break;
        case 'C': // 100
            if (i + 1 < n && s[i + 1] == 'D')
            {
                r += 400;
                i += 2;
            }
            else if (i + 1 < n && s[i + 1] == 'M')
            {
                r += 900;
                i += 2;
            }
            else
            {
                r += 100;
                i++;
            }
            break;
        case 'D': // 500
            r += 500;
            i++;
            break;
        case 'M': // 1,000
            r += 1000;
            i++;
            break;
        default:
            i++;
            break;
        }
    }
    return r;
}

// Given an integer, convert it to a roman numeral.
// Input is guaranteed to be within the range from 1 to 3999.
static string IntToRomain(int num)
{
    string s;
    if (num <= 0)
        return s;
    int d = num / 1000;
    if (d > 0)
        s.append(d, 'M');
    num = num % 1000;
    if (num == 0)
        return s;
    if (num >= 900)
    {
        s.append(1, 'C');
        s.append(1, 'M');
        num -= 900;
    }
    else if (num >= 500)
    {
        s.append(1, 'D');
        num -= 500;
        if (num == 0)
            return s;
        d = num / 100;
        if (d > 0)
            s.append(d, 'C');
        num = num % 100;
    }
    else if (num >= 400)
    {
        s.append(1, 'C');
        s.append(1, 'D');
        num -= 400;
    }
    else
    {
        d = num / 100;
        if (d > 0)
            s.append(d, 'C');
        num = num % 100;
    }
    // Now 0 <= num < 100
    if (num == 0)
        return s;
    if (num >= 90)
    {
        s.append(1, 'X');
        s.append(1, 'C');
        num -= 90;
    }
    else if (num >= 50)
    {
        s.append(1, 'L');
        num -= 50;
        if (num == 0)
            return s;
        d = num / 10;
        if (d > 0)
            s.append(d, 'X');
        num = num % 10;
    }
    else if (num >= 40)
    {
        s.append(1, 'X');
        s.append(1, 'L');
        num -= 40;
    }
    else
    {
        d = num / 10;
        if (d > 0)
            s.append(d, 'X');
        num = num % 10;
    }
    // Now 0 <= num < 10
    if (num == 0)
        return s;
    if (num == 9)
    {
        s.append(1, 'I');
        s.append(1, 'X');
    }
    else if (num >= 5)
    {
        s.append(1, 'V');
        num -= 5;
        s.append(num, 'I');
    }
    else if (num == 4)
    {
        s.append(1, 'I');
        s.append(1, 'V');
    }
    else
    {
        s.append(num, 'I');
    }
    return s;
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
static vector<string> restoreIpAddresses2(const string &s)
{
    vector<string> ips;
    int len = s.length();
    if (len < 4 || len > 12)
        return ips;

    auto check = [&](const string &octet) -> bool {
        int l = octet.length();
        for (int i = 0; i < min(3, l); i++)
        {
            if (octet[i] < '0' || octet[i] > '9')
                return false;
        }
        int m = 0;
        for (int i = 0; i < min(3, l); i++)
        {
            m = 10 * m + octet[i] - '0';
        }
        return 0 <= m && m <= 255;
    };

    for (int i = 1; i <= (s[0] == '0' ? 1 : min(3, len - 3)); i++)
    {
        for (int j = i + 1; j <= (s[i] == '0' ? i + 1 : min(i + 3, len - 2)); j++)
        {
            for (int k = j + 1; k <= (s[j] == '0' ? j + 1 : min(j + 3, len - 1)); k++)
            {
                if ((len - k > 3) || (len - k > 1 && s[k] == '0'))
                    continue;
                if (check(s.substr(0, i)) && check(s.substr(i, j - i)) && check(s.substr(j, k - j)) && check(s.substr(k, len - k)))
                {
                    string ip(s.substr(0, i));
                    ip.append(1, '.');
                    ip.append(s.substr(i, j - i));
                    ip.append(1, '.');
                    ip.append(s.substr(j, k - j));
                    ip.append(1, '.');
                    ip.append(s.substr(k, len - k));
                    ips.push_back(ip);
                }
            }
        }
    }

    return ips;
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
// Another option is to compare characters directly:
// 0.1 < 1.1 because 0 < 1 at index 0
// 0.3.0 < 0.12.1 because . < 2 at index 3
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

// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
// For example,
// s1 = "aabcc",
// s2 = "dbbca",
// When s3 = "aadbbcbcac", return true.
// When s3 = "aadbbbaccc", return false.
//   j 0 1 2
// i 0
//   1
//   2
// Let M[i][j] indicates whether s3[0..i+j-1] is interleave of s1[0..i-1] and s2[0..j-1]
// M[i][j] =   s1[i-1] == s3[i+j-1] && M[i-1][j]
//          || s2[j-1] == s3[i+j-1] && M[i][j-1]
static bool IsInterLeave(const string &s1, const string &s2, const string &s3)
{
    if (s3.length() != s1.length() + s2.length())
        return false;
    if (s3.length() == 0)
        return true;

    vector<bool> match(1 + s2.size(), true);
    for (size_t j = 1; j <= s2.size(); j++)
    {
        match[j] = match[j - 1] && s2[j - 1] == s3[j - 1];
    }

    for (size_t i = 1; i <= s1.size(); i++)
    {
        match[0] = match[0] && s1[i - 1] == s3[i - 1];
        for (size_t j = 1; j <= s2.size(); j++)
        {
            match[j] = (match[j] && s1[i - 1] == s3[i + j - 1]) || (match[j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }

    return match[s2.size()];
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
static vector<int> grayCode2(int n)
{
    vector<int> codes = {};
    if (n <= 0 || n > 8 * (int)sizeof(int))
        return codes;
    function<void(int &, int)> toggle = [&](int &code, int position) {
        code = code ^ (0x1 << position);
        codes.push_back(code);
        if (position > 0)
        {
            for (int i = 0; i < position; i++)
                toggle(code, i);
        }
    };

    int code = 0;
    codes.push_back(code);
    for (int i = 0; i < n; i++)
        toggle(code, i);

    return codes;
}

// 168. Excel Sheet Column Title
// Given a positive integer, return its corresponding column title
// as appear in an Excel sheet. For example :
// 1 -> A
// 2 -> B
// 3 -> C
//   ...
// 26 -> Z
// 27 -> AA
// 28 -> AB
static string convertToTitle(int n)
{
    string e;
    while (n > 0)
    {
        int r = n % 26;
        n = (n - r) / 26;
        if (r == 0)
        {
            r = 26;
            n--;
        }
        e.insert(e.begin(), 'A' + r - 1);
    }
    return e;
}

// 171. Excel Sheet Column Number
// Related to question Excel Sheet Column Title. Given a column title
// as appear in an Excel sheet, return its corresponding column number.
// For example :
// A -> 1
// B -> 2
// C -> 3
//   ...
// Z -> 26
// AA -> 27
// AB -> 28
static int titleToNumber(string s)
{
    int n = 0;
    for (size_t i = 0; i < s.length(); i++)
    {
        n *= 26;
        n += (s[i] - 'A' + 1);
    }
    return n;
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
static int divide2(int dividend, int divisor)
{
    if (divisor == 0)
        throw invalid_argument("divided by zero");
    if (dividend == 0)
        return 0;
    if (divisor == 1)
        return dividend;
    if (divisor == -1)
        return -dividend;

    long long de = dividend;
    long long ds = divisor;

    bool negative = false;
    if (de > 0 && ds < 0)
    {
        negative = true;
        ds = -ds;
    }
    else if (de < 0 && ds > 0)
    {
        negative = true;
        de = -de;
    }
    else if (de < 0 && ds < 0)
    {
        de = -de;
        ds = -ds;
    }

    long long r = 0;
    while (de >= ds)
    {
        long long d = ds;
        long long i = 1;
        while (de >= d)
        {
            d = d << 1;
            i = i << 1;
        }
        d = d >> 1;
        i = i >> 1;
        de -= d;
        r += i;
    }

    if (negative)
        r = -r;
    return (int)r;
}
static int divide3(int dividend, int divisor)
{
    if (divisor == 0)
        throw invalid_argument("divided by zero");
    if (dividend == 0)
        return 0;

    long long de = dividend;
    long long ds = divisor;

    bool negative = false;
    if (de > 0 && ds < 0)
    {
        negative = true;
        ds = -ds;
    }
    else if (de < 0 && ds > 0)
    {
        negative = true;
        de = -de;
    }
    else if (de < 0 && ds < 0)
    {
        de = -de;
        ds = -ds;
    }

    if (de < ds)
        return 0;
    if (de == ds)
        return negative ? -1 : 1;

    long long r = 0;
    long long d = ds;
    long long i = 1;
    vector<long long> v(1, d);
    while (de >= d)
    {
        d = d << 1;
        i = i << 1;
        v.push_back(d);
    }
    d = d >> 1;
    i = i >> 1;
    de -= d;
    v.pop_back();
    r += i;

    while (de >= ds)
    {
        int j = 0;
        int k = v.size() - 1;
        while (j <= k)
        {
            int m = j + ((k - j) >> 1);
            if (de < v[m])
            {
                if (j == m)
                {
                    if (m > 0)
                    {
                        r += (long long)(1 << (m - 1));
                        de -= v[m - 1];
                    }
                    while ((int)v.size() > m)
                        v.pop_back();
                    break;
                }
                k = m - 1;
            }
            else if (v[m] < de)
            {
                if (m == k)
                {
                    r += (long long)(1 << m);
                    de -= v[m];
                    while ((int)v.size() > m + 1)
                        v.pop_back();
                    break;
                }
                j = m + 1;
            }
            else
            {
                r += (long long)(1 << m);
                de -= v[m];
                break;
            }
        }
    }

    if (negative)
        r = -r;
    return (int)r;
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
        y = x; // = x^d
        // loop x^2, x^4, x^8, ...
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
// Keep dividing n by 2 and get the remainder r (0 or 1)
// then there is a sequence:
// n n_1 n_2 n_3 n_4 ...... n_k (= 0)
//   r_1 r_2 r_3 r_4 ...... r_k (= 0)
// x^n = x^{r_1} * (x^2)^{n_1}
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{n_2}
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{n_3}
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{r_4} * (x^16)^{n_4}
//     ......
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{r_4} * (x^16)^{n_4} ...... * (x^{2^(k-1)})^{r_(k-1)} * (x^{2^k})^{n_k}
static double myPow2(double x, int n)
{
    if (x == 0)
        return 0;
    if (n == 0)
        return 1;
    bool negative = n < 0;
    if (negative)
        n = -n;
    double m = x;
    double p = (n & 0x1) == 1 ? x : 1;
    n = n >> 1;
    while (n > 0)
    {
        m = m * m;
        if ((n & 0x1) == 1)
        {
            p = p * m;
        }
        n = n >> 1;
    }
    if (negative)
        p = 1 / p;
    return p;
}
static double myPow3(double x, int n)
{
    if (x == 0)
        return 0;
    if (n == 0)
        return 1;
    bool negative = n < 0;
    if (negative)
        n = -n;
    double m = x;
    double p = 1;
    while (n > 0)
    {
        if ((n & 0x1) == 1)
        {
            p = p * m;
        }
        m = m * m;
        n = n >> 1;
    }
    if (negative)
        p = 1 / p;
    return p;
}
static double myPow4(double x, int n)
{
    if (x == 0)
        return 0;
    if (n == 0)
        return 1;
    bool negative = n < 0;
    if (negative)
        n = -n;
    double p = (n & 0x1) == 1 ? x : 1;
    p = p * myPow4(x * x, n >> 1);
    if (negative)
        p = 1 / p;
    return p;
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
static int mySqrt2(int x)
{
    if (x < 0)
        throw invalid_argument("x cannot be negative");
    if (x < 2)
        return x;
    long long l = 1;
    long long h = (x >> 1) + 1;
    while (l <= h)
    {
        long long m = l + ((h - l) >> 1);
        long long s = m * m;
        if (x == s)
            return (int)m;
        else if (x < s)
        {
            if (l == m)
                break;
            h = m;
        }
        else
        {
            if (l == m)
            {
                s = h * h;
                if (x == s)
                    return (int)h;
                return (int)m;
            }
            else
            {
                l = m;
            }
        }
    }
    throw runtime_error("sqrt(x) cannot be found");
}

// 172. Factorial Trailing Zeroes
// Given an integer n, return the number of trailing zeroes in n!.
// Note: Your solution should be in logarithmic time complexity.
static int trailingZeroes(int n)
{
    // n! = 1 * 2 * 3 * 4 * 5 * ... * 10 * ... * 15 * ... * n
    //    = 2^x * 5^y * z
    // Usually x >= y. So just need to count occurrence of 5.
    //   n:      1, 2, 3, 4, 5, 6, ..., 2*5, ..., 3*5, ..., n1*5, ..., n
    // n/5 = n1:             1,    ..., 2,   ..., 3,   ..., n2*5, ..., n1
    // n1/5 = n2:                                   1, ..., n3*5, ..., n2
    // n2/5 = n3: ...
    // ...
    int c = 0;
    while (n >= 5)
    {
        n /= 5;
        c += n;
    }
    return c;
}

// 179. Largest Number
// Given a list of non negative integers, arrange them such that they form the
// largest number. For example, given [3, 30, 34, 5, 9], the largest formed
// number is 9534330. Note: The result may be very large, so you need to return
// a string instead of an integer.
static string largestNumber(vector<int> &nums)
{
    vector<string> strs;
    strs.resize(nums.size());
    transform(nums.begin(), nums.end(), strs.begin(), [&](int i) {
        ostringstream oss;
        oss << i;
        return oss.str();
    });
    sort(strs.begin(), strs.end(),
         [&](const string &str1, const string &str2) {
             string str12(str1);
             str12.append(str2);
             string str21(str2);
             str21.append(str1);
             return str12.compare(str21) > 0;
         });
    string result;
    if (strs[0] == "0")
    {
        result = "0";
    }
    else
    {
        for_each(strs.begin(), strs.end(), [&](const string &str) {
            result.append(str);
        });
    }
    return result;
}

// 190. Reverse Bits
// Reverse bits of a given 32 bits unsigned integer. For example, given input
// 43261596 (represented in binary as 00000010100101000001111010011100), return
// 964176192 (represented in binary as 00111001011110000010100101000000). Follow
// up: If this function is called many times, how would you optimize it?
static uint32_t reverseBits(uint32_t n)
{
    // b31 b30 b29 ... b18 b17 b16 b15 b14 b13 ... b2  b1  b0
    // reverse higher 16 bits and lower 16 bits
    // b16 b17 b18 ... b29 b30 b31 b0  b1  b2  ... b13 b14 b15
    // exchange higher 16 bits and lower 16 bits
    // b0  b1  b2  ... b13 b14 b15 b16 b17 b18 ... b29 b30 b31
    // reverse(n) = exchange(reverse(higher_half(n)), reverse(lower_half(n)))
    n = (n & 0x55555555) << 1 | (n & 0xaaaaaaaa) >> 1;
    n = (n & 0x33333333) << 2 | (n & 0xcccccccc) >> 2;
    n = (n & 0x0f0f0f0f) << 4 | (n & 0xf0f0f0f0) >> 4;
    n = (n & 0x00ff00ff) << 8 | (n & 0xff00ff00) >> 8;
    n = (n & 0x0000ffff) << 16 | (n & 0xffff0000) >> 16;
    return n;
}

// 191. Number of 1 Bits
// Write a function that takes an unsigned integer and returns the number of
// ’1' bits it has (also known as the Hamming weight). For example, the 32-bit
// integer ’11' has binary representation 00000000000000000000000000001011, so
// the function should return 3.
static int hammingWeight(uint32_t n)
{
    int h = 0;
    while (n != 0)
    {
        n &= (n - 1);
        h++;
    }
    return h;
}

// 201. Bitwise AND of Numbers Range
// Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND
// of all numbers in this range, inclusive. For example, given the range [5, 7],
// you should return 4.
static int rangeBitwiseAnd(int m, int n)
{
    int x = 0;
    while (m != n)
    {
        m >>= 1;
        n >>= 1;
        x++;
    }
    return m << x;
}

// 202. Happy Number
// Write an algorithm to determine if a number is "happy". A happy number is a
// number defined by the following process: Starting with any positive integer,
// replace the number by the sum of the squares of its digits, and repeat the
// process until the number equals 1 (where it will stay), or it loops endlessly
// in a cycle which does not include 1. Those numbers for which this process ends
// in 1 are happy numbers. Example: 19 is a happy number
//  1^2 + 9^2 = 82
//  8^2 + 2^2 = 68
//  6^2 + 8^2 = 100
//  1^2 + 0^2 + 0^2 = 1
static bool isHappy(int n)
{
    int x = n;
    cout << n;
    do
    {
        int y = 0;
        while (x > 0)
        {
            int r = x % 10;
            y += (r * r);
            x /= 10;
        }
        x = y;
        cout << ", " << x;
    } while (x != n && x != 1);
    return x == 1;
}

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
static vector<vector<int>> generateMatrix2(int n)
{
    if (n == 0)
        return vector<vector<int>>();
    if (n < 0)
        n = -n;
    vector<vector<int>> o(n, vector<int>(n, 0));
    int h = n;
    int v = n;
    int i = 0;
    int j = -1;
    int t = 1;
    int d = 0;
    while (h > 0 && v > 0)
    {
        d = d % 4;
        switch (d)
        {
        case 0:
            for (int k = 1; k <= h; k++)
            {
                j++;
                o[i][j] = t++;
            }
            v--;
            d++;
            break;
        case 1:
            for (int k = 1; k <= v; k++)
            {
                i++;
                o[i][j] = t++;
            }
            h--;
            d++;
            break;
        case 2:
            for (int k = 1; k <= h; k++)
            {
                j--;
                o[i][j] = t++;
            }
            v--;
            d++;
            break;
        default:
            for (int k = 1; k <= v; k++)
            {
                i--;
                o[i][j] = t++;
            }
            h--;
            d++;
            break;
        }
    }
    return o;
}

// 62. Unique Paths
// A robot is located at the top-left corner of a m x n grid (marked 'Start'
// in the diagram below). The robot can only move either down or right at any
// point in time. The robot is trying to reach the bottom-right corner of the
// grid (marked 'Finish' in the diagram below). How many possible unique paths
// are there? Note: m and n will be at most 100.
// @grid, @dynamicprogramming
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
// sum[i][j] = sum[i+1][j] + sum[i][j+1]
static int uniquePaths2(int m, int n)
{
    if (m <= 0 || n <= 0)
        return 0;
    vector<int> sum(n, 1);
    for (int i = m - 2; i >= 0; i--)
    {
        for (int j = n - 2; j >= 0; j--)
        {
            sum[j] += sum[j + 1];
        }
    }
    return sum[0];
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
static int uniquePathsWithObstacles2(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size();
    if (m == 0)
        return 0;
    int n = obstacleGrid[0].size();
    if (n == 0)
        return 0;
    if (obstacleGrid[m - 1][n - 1] == 1)
        return 0;
    vector<int> sum(n, 0);
    sum[n - 1] = 1;
    for (int j = n - 2; j >= 0; j--)
    {
        sum[j] = obstacleGrid[m - 1][j] == 1 ? 0 : sum[j + 1];
    }
    for (int i = m - 2; i >= 0; i--)
    {
        sum[n - 1] = obstacleGrid[i][n - 1] == 1 ? 0 : sum[n - 1];
        for (int j = n - 2; j >= 0; j--)
        {
            sum[j] = obstacleGrid[i][j] == 1 ? 0 : (sum[j] + sum[j + 1]);
        }
    }
    return sum[0];
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
static int minPathSum2(vector<vector<int>> &grid)
{
    if (grid.size() == 0 && grid[0].size() == 0)
        return 0;
    vector<int> sum(grid[0].size(), 0);
    sum[0] = grid[0][0];
    int i = 0;
    int j = 0;
    for (j = 1; j < (int)grid[0].size(); j++)
    {
        sum[j] = sum[j - 1] + grid[0][j];
    }
    for (i = 1; i < (int)grid.size(); i++)
    {
        sum[0] = sum[0] + grid[i][0];
        for (j = 1; j < (int)grid[i].size(); j++)
        {
            sum[j] = grid[i][j] + min(sum[j - 1], sum[j]);
        }
    }
    return sum[j - 1];
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
static bool searchMatrix2(vector<vector<int>> &matrix, int target)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;

    int l = 0;
    int h = matrix.size() - 1;
    int m;
    while (l <= h)
    {
        m = l + ((h - l) >> 1);
        if (target == matrix[m][0])
            return true;
        if (target < matrix[m][0])
        {
            if (l == m)
                return false;
            h = m - 1;
        }
        else
        {
            if (l == m)
            {
                if (target >= matrix[h][0])
                    m = h;
                break;
            }

            l = m;
        }
    }

    l = 0;
    h = matrix[m].size() - 1;
    int n;
    while (l <= h)
    {
        n = l + ((h - l) >> 1);
        if (target == matrix[m][n])
            return true;
        if (target < matrix[m][n])
        {
            if (l == n)
                break;
            h = n - 1;
        }
        else
        {
            if (n == h)
                break;
            l = n + 1;
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
// @grid, @dfs
// [TODO] What if a letter can be reused?
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

// 48. Rotate Image
// You are given an n x n 2D matrix representing an image. Rotate the image by
// 90 degrees(clockwise).
// 0 1        3 0
// 3 2        2 1
static void rotate(vector<vector<int>> &matrix)
{
    int d = matrix.size();
    // Swap up-left with bottom-right
    for (int i = 0; i < d - 1; i++)
    {
        for (int j = 0; j < d - i - 1; j++)
        {
            swap(matrix[i][j], matrix[d - j - 1][d - i - 1]);
        }
    }
    // Swap up with bottom
    for (int i = 0; i < (d >> 1); i++)
    {
        for (int j = 0; j < d; j++)
        {
            swap(matrix[i][j], matrix[d - i - 1][j]);
        }
    }
}
static void rotate2(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    // Swap up-right with bottom-left
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int t = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = t;
        }
    }
    // Swap left with right
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            int t = matrix[i][j];
            matrix[i][j] = matrix[i][n - 1 - j];
            matrix[i][n - 1 - j] = t;
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

// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
// containing all ones and return its area.
static int MaximalRectangle(vector<vector<char>> &matrix)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    bool foundOne = false;
    int imin = -1;
    int imax = -1;
    int jmin = -1;
    int jmax = -1;
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[i].size(); j++)
        {
            if (matrix[i][j] == 1)
            {
                if (foundOne)
                {
                    if (i < imin)
                        imin = i;
                    if (i > imax)
                        imax = i;
                    if (j < jmin)
                        jmin = j;
                    if (j > jmax)
                        jmax = j;
                }
                else
                {
                    imin = i;
                    imax = i;
                    jmin = j;
                    jmax = j;
                    foundOne = true;
                }
            }
        }
    }

    if (!foundOne)
        return 0;

    int area = (imax - imin + 1) * (jmax - jmin + 1);
    return area;
}

// Given a 2D binary matrix filled with 0's and 1's,
// find the largest rectangle full of ones and with a give point on its top-left
// corner, return the rectangle area.
static int MaximalRectangleAtPoint(vector<vector<char>> &matrix, int pi, int pj)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    if (pi < 0 || pi >= (int)matrix.size() || pj < 0 || pj >= (int)matrix[0].size())
        return 0;
    if (matrix[pi][pj] != 1)
        return 0;

    int i = pi;
    int j = pj;

    while (j + 1 < (int)matrix[0].size() && matrix[i][j + 1] == 1)
        j++;

    int maxj = j;
    int maxArea = j - pj + 1;

    while (i + 1 < (int)matrix.size() && matrix[i + 1][pj] == 1)
    {
        i++;
        j = pj;
        while (j + 1 <= maxj && matrix[i][j + 1] == 1 && matrix[i - 1][j + 1] == 1)
            j++;
        int area = (i - pi + 1) * (j - pj + 1);
        if (area > maxArea)
            maxArea = area;
        maxj = j;
    }

    return maxArea;
}

// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
// full of ones, return its area.
static int MaximalRectangleFullOnes(vector<vector<char>> &matrix)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return 0;
    int maxArea = 0;
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[i].size(); j++)
        {
            if (matrix[i][j] == 1)
            {
                int area = MaximalRectangleAtPoint(matrix, i, j);
                if (area > maxArea)
                    maxArea = area;
            }
        }
    }
    return maxArea;
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

static void Print(ListNode *node)
{
    if (node == nullptr)
        return;
    while (node != nullptr)
    {
        cout << node->val << "->";
        node = node->next;
    }
    cout << "null" << endl;
}

static void DeleteList(ListNode *node)
{
    if (node == nullptr)
        return;
    ListNode *p = node;
    while (p != nullptr)
    {
        node = p->next;
        delete p;
        p = node;
    }
}

static ListNode *ToList(vector<int> &numbers)
{
    ListNode *list = nullptr;
    if (numbers.size() == 0)
        return list;
    list = new ListNode(numbers[0]);
    ListNode *n = list;
    for (size_t i = 1; i < numbers.size(); i++)
    {
        n->next = new ListNode(numbers[i]);
        n = n->next;
    }
    return list;
}

static ListNode *MergeSortedLists(ListNode *l1, ListNode *l2)
{
    if (l1 == nullptr)
        return l2;
    if (l2 == nullptr)
        return l1;

    ListNode *head = l1;
    if (l1->val > l2->val)
    {
        head = l2;
        l2 = l2->next;
    }
    else
    {
        l1 = l1->next;
    }

    ListNode *p = head;

    while (l1 != nullptr && l2 != nullptr)
    {
        if (l1->val <= l2->val)
        {
            if (p->next != l1)
                p->next = l1;
            p = l1;
            l1 = p->next;
        }
        else
        {
            if (p->next != l2)
                p->next = l2;
            p = l2;
            l2 = p->next;
        }
    }

    ListNode *q = l1 == nullptr ? l2 : l1;
    if (q != nullptr && p->next != q)
        p->next = q;

    return head;
}

// Merge k sorted linked lists and return it as one sorted list.
static ListNode *MergeKLists(vector<ListNode *> &lists)
{
    if (lists.size() == 0)
        return nullptr;
    ListNode *list = nullptr;
    ListNode *tail = list;
    while (true)
    {
        ListNode *mp = nullptr;
        int mi = 0;
        for (int i = 0; i < (int)lists.size(); i++)
        {
            if (lists[i] != nullptr)
            {
                if (mp == nullptr || lists[i]->val < mp->val)
                {
                    mp = lists[i];
                    mi = i;
                }
            }
        }
        if (mp == nullptr)
            break;
        if (list == nullptr)
            list = mp;
        else
            tail->next = mp;
        tail = mp;
        lists[mi] = mp->next;
    }
    return list;
}
static bool Greater(ListNode *first, ListNode *second)
{
    if (first == nullptr && second == nullptr)
        return false;
    if (first == nullptr && second != nullptr)
        return true;
    if (first != nullptr && second == nullptr)
        return false;
    if (first->val > second->val)
        return true;
    else
        return false;
}
static ListNode *MergeKLists2(vector<ListNode *> &lists)
{
    if (lists.size() == 0)
        return nullptr;
    ListNode *list = nullptr;
    ListNode *tail = list;
    make_heap(lists.begin(), lists.end(), Greater);
    while (lists.front() != nullptr)
    {
        pop_heap(lists.begin(), lists.end(), Greater);
        if (list == nullptr)
            list = lists.back();
        else
            tail->next = lists.back();
        tail = lists.back();
        lists.back() = lists.back()->next;
        push_heap(lists.begin(), lists.end(), Greater);
    }
    return list;
}
static ListNode *MergeKLists3(vector<ListNode *> &lists)
{
    if (lists.size() == 0)
        return nullptr;
    ListNode *list = nullptr;
    ListNode *tail = list;
    make_heap(lists.begin(), lists.end(), Greater);
    while (lists.size() > 0)
    {
        pop_heap(lists.begin(), lists.end(), Greater);
        if (lists.back() == nullptr)
            break;
        if (list == nullptr)
            list = lists.back();
        else
            tail->next = lists.back();
        tail = lists.back();
        lists.back() = lists.back()->next;
        if (lists.back() == nullptr)
            lists.pop_back();
        else
            push_heap(lists.begin(), lists.end(), Greater);
    }
    return list;
}

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

// 61. Rotate List
// Given a list, rotate the list to the right by k places, where k is non-negative.
// For example : Given 1->2->3->4->5->NULL and k = 2, return 4->5->1->2->3->NULL.
static ListNode *rotateRight(ListNode *head, int k)
{
    if (head == nullptr)
        return head;
    ListNode *tail = head;
    int i = 1;
    while (tail->next != nullptr)
    {
        i++;
        tail = tail->next;
    }
    // tail is the last element and is the i-th element (1-based)
    k %= i;
    if (k == 0)
        return head;
    int j = i - k;
    // TODO: compute p in the while loop above.
    // Be careful when k is larger than the list length.
    ListNode *p = head;
    while (j > 1)
    {
        p = p->next;
        j--;
    }
    tail->next = head;
    head = p->next;
    p->next = nullptr;
    return head;
}
static ListNode *rotateRight2(ListNode *head, int k)
{
    if (head == nullptr || k <= 0)
        return head;
    ListNode *p = head;
    ListNode *q = head;
    int i = 0;
    while (i < k && q->next != nullptr)
    {
        q = q->next;
        i++;
    }
    // q is the i-th element (0-based)
    if (q->next == nullptr)
    {
        int l = i + 1; // total length
        k = k % l;
        if (k == 0)
            return head;
        i = 0;
        q = head;
        while (i < k && q->next != nullptr)
        {
            q = q->next;
            i++;
        }
    }
    // q is the k-th element (0-based)
    while (q->next != nullptr)
    {
        q = q->next;
        p = p->next;
    }
    q->next = head;
    head = p->next;
    p->next = nullptr;
    return head;
}

// 92. Reverse Linked List II
// Reverse a linked list from position m to n. Do it in-place and in one-pass.
// For example : Given 1->2->3->4->5->NULL, m = 2 and n = 4,
// return 1->4->3->2->5->NULL.
// Note : Given m, n satisfy the following condition :
// 1 <= m <= n <= length of list.
static ListNode *reverseBetween(ListNode *head, int m, int n)
{
    if (head == nullptr)
        return nullptr;
    ListNode *pm_prev = nullptr;
    ListNode *pm = nullptr;
    int i;
    if (m == 1)
    {
        pm = head;
    }
    else
    {
        pm_prev = head;
        i = 1;
        while (i < m - 1 && pm_prev->next != nullptr)
        {
            pm_prev = pm_prev->next;
            i++;
        }
        if (i < m - 1)
            return head;
        pm = pm_prev->next;
    }
    ListNode *pn = pm;
    i = m;
    while (i < n && pn->next != nullptr)
    {
        pn = pn->next;
        i++;
    }
    ListNode *pn_next = pn->next;
    ListNode *prev = pn_next;
    ListNode *curr = pm;
    ListNode *next = pm->next;
    while (curr != pn)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }
    curr->next = prev;
    if (pm_prev == nullptr)
    {
        head = pn;
    }
    else
    {
        pm_prev->next = pn;
    }
    return head;
}
static ListNode *reverseBetween2(ListNode *head, int m, int n)
{
    if (head == nullptr || m <= 0 || n <= 0 || m >= n)
        return head;

    ListNode *ph = nullptr;
    ListNode *pm = head;
    int i = 1;
    while (i < m && pm->next != nullptr)
    {
        ph = pm;
        pm = pm->next;
        i++;
    }

    if (i < m)
        return head;

    ListNode *r = ph;
    ListNode *s = pm;
    ListNode *t = pm->next;

    while (i <= n && t != nullptr)
    {
        s->next = r;
        r = s;
        s = t;
        t = t->next;
        i++;
    }

    if (i <= n && t == nullptr)
    {
        s->next = r;
        r = s;
        s = t;
    }

    pm->next = s;
    if (ph != nullptr)
        ph->next = r;
    else
        head = r;

    return head;
}

// Given a linked list, reverse the nodes of a linked list k at a time and
// return its modified list. If the number of nodes is not a multiple of k
// then left-out nodes in the end should remain as it is. You may not alter
// the values in the nodes, only nodes itself may be changed. Only constant
// memory is allowed. For example, Given this linked list: 1->2->3->4->5
// For k = 2, you should return: 2->1->4->3->5
// For k = 3, you should return: 3->2->1->4->5
static ListNode *ReverseKGroup(ListNode *head, int k)
{
    if (head == nullptr || k <= 1)
        return head;

    ListNode *begin = head;
    ListNode *prev = begin;
    while (begin != nullptr)
    {
        ListNode *end = begin;
        int i = 1;
        while (i < k && end != nullptr)
        {
            end = end->next;
            i++;
        }
        if (end == nullptr)
            return head;

        ListNode *f = begin;
        ListNode *s = f->next;
        ListNode *t = nullptr;
        begin->next = end->next;

        while (f != end)
        {
            t = s->next;
            s->next = f;
            f = s;
            s = t;
        }

        if (head == begin)
            head = end;
        else
            prev->next = end;

        prev = begin;
        begin = begin->next;
    }
    return head;
}

// Given a linked list, swap every two adjacent nodes and return its head.
// For example, Given 1->2->3->4, you should return the list as 2->1->4->3.
// Your algorithm should use only constant space. You may not modify the
// values in the list, only nodes itself can be changed.
static ListNode *SwapPairs(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *f = head;
    ListNode *s = f->next;

    f->next = s->next;
    s->next = f;
    head = s;

    ListNode *p = f;
    f = f->next;
    while (f != nullptr)
    {
        s = f->next;
        if (s == nullptr)
            break;
        f->next = s->next;
        s->next = f;
        p->next = s;
        p = f;
        f = f->next;
    }
    return head;
}

// 143. Reorder List
// Given a singly linked list L: L0->L1->...->Ln-1->Ln, reorder it to:
// L0->Ln->L1->Ln-1->L2->Ln-2->... You must do this in-place without altering
// the nodes' values. For example, Given { 1,2,3,4 }, reorder it to { 1,4,2,3 }.
static void reorderList(ListNode *head)
{
    if (head == nullptr)
        return;
    // Find the middle node. When the while-loop stops, pointer first
    // is the median node if there are odd number of nodes, or the higher
    // median node if there are even number of nodes.
    ListNode *first = head;
    ListNode *second = head;
    while (second != nullptr && second->next != nullptr)
    {
        first = first->next;
        second = second->next->next;
    }
    // Break the list into two lists
    ListNode *tail = first;
    ListNode *head2 = tail->next;
    tail->next = nullptr;
    if (head2 == nullptr)
        return;
    // Reverse the second list
    ListNode *prev = nullptr;
    ListNode *middle = head2;
    ListNode *next = middle->next;
    while (next != nullptr)
    {
        middle->next = prev;
        prev = middle;
        middle = next;
        next = middle->next;
    }
    middle->next = prev;
    // Merge the two lists
    head2 = middle;
    first = head;
    while (head2 != nullptr)
    {
        second = head2;
        head2 = second->next;
        second->next = first->next;
        first->next = second;
        first = second->next;
    }
}

// Given a linked list, remove the nth node from the end of list and return its head.
// For example,
// Given linked list: 1->2->3->4->5, and n = 2.
// After removing the second node from the end, the linked list becomes 1->2->3->5.
static ListNode *RemoveNthFromEnd(ListNode *head, int n)
{
    if (head == nullptr || n <= 0)
        return head;
    ListNode *q = head;
    int i = 0;
    while (i < n && q->next != nullptr)
    {
        q = q->next;
        i++;
    }
    if (i < n - 1) // only i + 1 (less than n) nodes in the list
        return head;
    ListNode *p = head;
    if (i == n - 1)
    {
        // Exact i + 1 (= n) nodes in the list
        head = p->next;
        delete p;
        return head;
    }
    while (q->next != nullptr)
    {
        p = p->next;
        q = q->next;
    }
    q = p->next;
    p->next = q->next;
    delete q;
    return head;
}

// 83. Remove Duplicates from Sorted List
// Given a sorted linked list, delete all duplicates such that each element
// appear only once. For example, Given 1->1->2, return 1->2.
// Given 1->1->2->3->3, return 1->2->3.
static ListNode *deleteDuplicates(ListNode *head)
{
    ListNode *p = head;
    while (p != nullptr)
    {
        if (p->next != nullptr && p->val == p->next->val)
        {
            ListNode *n = p->next;
            p->next = n->next;
            delete n;
        }
        else
        {
            p = p->next;
        }
    }
    return head;
}

// 82. Remove Duplicates from Sorted List II
// Given a sorted linked list, delete all nodes that have duplicate numbers,
// leaving only distinct numbers from the original list. For example,
// Given 1->2->3->3->4->4->5, return 1->2->5.
// Given 1->1->1->2->3, return 2->3.
static ListNode *deleteDuplicates2(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *p = head;
    ListNode *next = nullptr;
    while (p != nullptr)
    {
        if (p->next != nullptr && p->val == p->next->val)
        {
            int v = p->val;
            while (p != nullptr && p->val == v)
            {
                next = p->next;
                delete p;
                p = next;
            }
            if (prev == nullptr)
            {
                head = p;
            }
            else
            {
                prev->next = p;
            }
        }
        else
        {
            if (prev == nullptr)
            {
                head = p;
            }
            else
            {
                prev->next = p;
            }
            prev = p;
            p = p->next;
        }
    }
    return head;
}
static ListNode *deleteDuplicates2_1(ListNode *head)
{
    if (head == nullptr)
        return nullptr;

    ListNode *p;

    while (head->next != nullptr && head->val == head->next->val)
    {
        int dup = head->val;
        while (head != nullptr && head->val == dup)
        {
            p = head;
            head = p->next;
            delete p;
        }

        if (head == nullptr)
            return nullptr;
    }

    if (head->next == nullptr)
        return head;

    p = head;
    ListNode *q = p->next;

    while (q->next != nullptr)
    {
        if (q->val != q->next->val)
        {
            p = q;
            q = p->next;
        }
        else
        {
            int dup = q->val;
            while (q != nullptr && q->val == dup)
            {
                p->next = q->next;
                delete q;
                q = p->next;
            }
            if (q == nullptr)
                return head;
        }
    }

    return head;
}

// 86. Partition List
// Given a linked list and a value x, partition it such that all nodes less than
// x come before nodes greater than or equal to x. You should preserve the original
// relative order of the nodes in each of the two partitions. For example,
// Given 1->4->3->2->5->2 and x = 3,
// return 1->2->2->4->3->5.
static ListNode *partition(ListNode *head, int x)
{
    if (head == nullptr)
        return head;
    ListNode *prev = nullptr;
    if (head->val < x)
    {
        prev = head;
    }
    ListNode *p = head;
    while (p->next != nullptr)
    {
        if (p->next->val < x)
        {
            if (prev == p)
            {
                prev = p->next;
                p = p->next;
            }
            else
            {
                ListNode *next = p->next;
                p->next = next->next;
                if (prev == nullptr)
                {
                    next->next = head;
                    head = next;
                    prev = next;
                }
                else
                {
                    next->next = prev->next;
                    prev->next = next;
                    prev = next;
                }
            }
        }
        else
        {
            p = p->next;
        }
    }
    return head;
}
static ListNode *partition2(ListNode *head, int x)
{
    if (head == nullptr)
        return nullptr;

    // p is the last node less than x
    ListNode *p = head;

    // q is the last node no less than x
    ListNode *q = head;

    if (head->val >= x)
    {
        while (q->next != nullptr && q->next->val >= x)
            q = q->next;
        if (q->next == nullptr)
        {
            // every node is equal to or greater than x
            return head;
        }

        // q->next is less than x
        ListNode *t = q->next;
        q->next = t->next;
        t->next = head;
        head = t;

        p = head;
    }
    else
    {
        while (p->next != nullptr && p->next->val < x)
            p = p->next;
        if (p->next == nullptr)
        {
            // every node is less than x
            return head;
        }

        q = p->next;
    }

    // Now check if q->next should be moved to be after p

    while (q->next != nullptr)
    {
        if (q->next->val < x)
        {
            ListNode *t = q->next;
            q->next = t->next;
            t->next = p->next;
            p->next = t;
            p = t;
        }
        else
        {
            q = q->next;
        }
    }

    return head;
}

// 147. Insertion Sort List
// Sort a linked list using insertion sort.
static ListNode *insertionSortList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    ListNode *p = head;
    while (p->next != nullptr)
    {
        if (p->val <= p->next->val)
        {
            p = p->next;
        }
        else
        {
            ListNode *q = p->next;
            p->next = q->next;
            q->next = nullptr;
            if (q->val < head->val)
            {
                q->next = head;
                head = q;
            }
            else
            {
                ListNode *s = head;
                while (s != p && s->next != nullptr && s->next->val <= q->val)
                {
                    s = s->next;
                }
                q->next = s->next;
                s->next = q;
            }
        }
    }
    return head;
}

// 148. Sort List
// Sort a linked list in O(nlogn) time using constant space complexity.
static ListNode *sortList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    function<ListNode *(ListNode *, ListNode *)>
        merge = [&](ListNode *l1, ListNode *l2) -> ListNode * {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;
        ListNode *h = nullptr;
        if (l1->val <= l2->val)
        {
            h = l1;
            l1 = l1->next;
        }
        else
        {
            h = l2;
            l2 = l2->next;
        }
        ListNode *p = h;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val <= l2->val)
            {
                p->next = l1;
                l1 = l1->next;
            }
            else
            {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        p->next = l1 == nullptr ? l2 : l1;
        return h;
    };
    function<ListNode *(ListNode *)>
        sort = [&](ListNode *h) -> ListNode * {
        if (h == nullptr || h->next == nullptr)
            return h;
        ListNode *p = h;
        ListNode *q = h->next;
        while (q != nullptr && q->next != nullptr)
        {
            p = p->next;
            q = q->next->next;
        }
        q = p->next;
        p->next = nullptr;
        p = sort(h);
        q = sort(q);
        p = merge(p, q);
        return p;
    };
    return sort(head);
}

// 141. Linked List Cycle
// Given a linked list, determine if it has a cycle in it.
// Follow up: Can you solve it without using extra space?
static bool hasCycle(ListNode *head)
{
    if (head == nullptr)
        return false;
    ListNode *p1 = head;
    ListNode *p2 = head;
    while (p2 != nullptr && p2->next != nullptr)
    {
        p1 = p1->next;
        p2 = p2->next->next;
        if (p1 == p2)
            return true;
    }
    return false;
}

// 142. Linked List Cycle II
// Given a linked list, return the node where the cycle begins. If there is no
// cycle, return null. Note: Do not modify the linked list.
// Follow up: Can you solve it without using extra space?
static ListNode *detectCycle(ListNode *head)
{
    ListNode *p1 = head;
    ListNode *p2 = head;
    while (p2 != nullptr && p2->next != nullptr)
    {
        p1 = p1->next;
        p2 = p2->next->next;
        if (p1 == p2)
            break;
    }
    if (p2 == nullptr || p2->next == nullptr)
        return nullptr;
    p1 = head;
    while (p1 != p2)
    {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

// 160. Intersection of Two Linked Lists
// Write a program to find the node at which the intersection of two singly
// linked lists begins. For example, the following two linked lists:
// A:        a1 -> a2
//                   \
//                    >
//                     c1 -> c2 -> c3
//                    >
//                   /
// B : b1 -> b2 -> b3
// begin to intersect at node c1. Notes: If the two linked lists have no intersection
// at all, return null. The linked lists must retain their original structure
// after the function returns. You may assume there are no cycles anywhere in
// the entire linked structure. Your code should preferably run in O(n) time and
// use only O(1) memory.
static ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    function<int(ListNode *)>
        getLength = [&](ListNode *h) -> int {
        int i = 0;
        while (h != nullptr)
        {
            i++;
            h = h->next;
        }
        return i;
    };
    function<ListNode *(ListNode *, int)>
        advance = [&](ListNode *h, int n) -> ListNode * {
        while (n > 0)
        {
            h = h->next;
            n--;
        }
        return h;
    };
    int la = getLength(headA);
    int lb = getLength(headB);
    ListNode *pa = headA;
    ListNode *pb = headB;
    if (la > lb)
        pa = advance(pa, la - lb);
    else
        pb = advance(pb, lb - la);
    while (pa != pb)
    {
        pa = pa->next;
        pb = pb->next;
    }
    return pa;
}
static ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB)
{
    ListNode *pa = headA;
    ListNode *pb = headB;
    while (pa != nullptr && pb != nullptr && pa != pb)
    {
        pa = pa->next;
        pb = pb->next;
        if (pa == pb)
            break;
        if (pa == nullptr)
            pa = headB;
        if (pb == nullptr)
            pb = headA;
    }
    return pa == pb ? pa : nullptr;
}

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

static void Print(TreeNode *node)
{
    function<void(stringstream *, int, char)>
        printChar = [&](stringstream *s, int n, char c) {
            if (n > 0)
            {
                string chars(n, c);
                *s << chars;
            }
        };

    function<void(TreeNode *, unsigned int, int &, int &, vector<stringstream *> &)>
        toString = [&](
                       TreeNode *n,               // current node to print
                       unsigned int y,            // current node level
                       int &x,                    // x-axis position of root of last printed sub tree
                       int &r,                    // x-axis position of right-most boundary of last printed sub tree
                       vector<stringstream *> &ss // output streams, one per level
                   ) {
            if (n == nullptr)
                return;

            if (ss.size() <= y)
                ss.push_back(new stringstream());

            // print left tree, update x and r accordingly
            toString(n->left, y + 1, x, r, ss);

            stringstream *s = ss[y];

            int l = (int)(s->str().length());
            if (l < x)
                printChar(s, x - l, ' ');

            if (n->left != nullptr && r > x)
            {
                *s << '/';
                printChar(s, r - x - 1, '-');
            }

            string nc = to_string(n->val);
            *s << nc;

            x = (r + (nc.length() >> 1));
            r = r + nc.length();

            int rx = r;
            int rr = r;
            toString(n->right, y + 1, rx, rr, ss);

            if (n->right != nullptr && rx >= r)
            {
                printChar(s, rx - r - 1, '-');
                *s << '\\';
            }

            // Update the right most boundary
            r = rr;
        };

    vector<stringstream *> streams;
    int x = 0;
    int r = 0;
    toString(node, 0, x, r, streams);

    for_each(streams.begin(), streams.end(), [&](stringstream *s) {
        cout << s->str() << endl;
        delete s;
    });
}

static void DeleteTree(TreeNode *root)
{
    if (root == nullptr)
        return;
    if (root->left != nullptr)
    {
        DeleteTree(root->left);
        root->left = nullptr;
    }
    if (root->right != nullptr)
    {
        DeleteTree(root->right);
        root->right = nullptr;
    }
    delete root;
}

static TreeNode *Clone(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    TreeNode *clone = new TreeNode(root->val);
    clone->left = Clone(root->left);
    clone->right = Clone(root->right);
    return clone;
}

// The root-to-leaf path 1->2 represents the number 12.
// The root-to-leaf path 1->3 represents the number 13.
// Return the sum = 12 + 13 = 25.
static int sumNumbers(TreeNode *root)
{
    function<void(TreeNode *, int, int &)>
        sum = [&](TreeNode *node, int pathSum, int &totalSum) {
            if (node == nullptr)
                return;
            pathSum = pathSum * 10 + node->val;
            if (node->left == nullptr && node->right == nullptr)
            {
                totalSum += pathSum;
                return;
            }
            if (node->left != nullptr)
                sum(node->left, pathSum, totalSum);
            if (node->right != nullptr)
                sum(node->right, pathSum, totalSum);
        };
    int total = 0;
    sum(root, 0, total);
    return total;
}

// 112. Path Sum
// Given a binary tree and a sum, determine if the tree has a root-to-leaf path
// such that adding up all the values along the path equals the given sum. For
// example: Given the below binary tree and sum = 22,
//       5
//      / \
//     4   8
//    /   / \
//   11  13  4
//  / \       \
// 7    2      1
// return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
static bool hasPathSum(TreeNode *root, int sum)
{
    function<bool(TreeNode *, int)>
        solve = [&](TreeNode *node, int parentSum) -> bool {
        if (node == nullptr)
            return false;
        parentSum += node->val;
        if (node->left == nullptr && node->right == nullptr)
            return parentSum == sum;
        return (node->left != nullptr && solve(node->left, parentSum)) || (node->right != nullptr && solve(node->right, parentSum));
    };
    return solve(root, 0);
}

// 113. Path Sum II
// Given a binary tree and a sum, find all root-to-leaf paths where each path's
// sum equals the given sum. For example: Given the below binary tree and sum = 22,
//       5
//      / \
//     4   8
//    /   / \
//   11  13  4
//  /  \    / \
// 7    2  5   1
// return
// [
//  [5, 4, 11, 2],
//  [5, 8, 4, 5]
// ]
static vector<vector<int>> pathSum(TreeNode *root, int sum)
{
    vector<vector<int>> result;
    function<void(TreeNode *, int, vector<int> &)>
        solve = [&](TreeNode *node, int parentSum, vector<int> &parents) {
            if (node == nullptr)
                return;
            parentSum += node->val;
            parents.push_back(node->val);
            if (node->left == nullptr && node->right == nullptr)
            {
                if (parentSum == sum)
                {
                    result.push_back(parents);
                }
            }
            else
            {
                if (node->left != nullptr)
                {
                    vector<int> v(parents);
                    solve(node->left, parentSum, v);
                }
                if (node->right != nullptr)
                {
                    vector<int> v(parents);
                    solve(node->right, parentSum, v);
                }
            }
        };
    vector<int> c;
    solve(root, 0, c);
    return result;
}

// 144. Binary Tree Preorder Traversal
// Given a binary tree, return the preorder traversal of its nodes' values.
// For example: Given binary tree { 1,#,2,3 },
//  1
//   \
//    2
//   /
//  3
// return [1, 2, 3].
// Note: Recursive solution is trivial, could you do it iteratively?
static vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode *> stack;
    stack.push(root);
    TreeNode *node;
    while (!stack.empty())
    {
        node = stack.top();
        stack.pop();
        result.push_back(node->val);
        if (node->right != nullptr)
            stack.push(node->right);
        if (node->left != nullptr)
            stack.push(node->left);
    }
    return result;
}

// 94. Binary Tree Inorder Traversal
// Given a binary tree, return the inorder traversal of its nodes' values.
// For example : Given binary tree[1, null, 2, 3],
//   1
//    \
//     2
//    /
//   3
// return[1, 3, 2].
// Note: Recursive solution is trivial, could you do it iteratively?
static vector<int> inorderTraversal(TreeNode *root)
{
    stack<TreeNode *> path;
    TreeNode *node = root;
    vector<int> result;
    while (!path.empty() || node != nullptr)
    {
        if (node != nullptr)
        {
            path.push(node);
            node = node->left;
        }
        else
        {
            node = path.top();
            path.pop();
            result.push_back(node->val);
            node = node->right;
        }
    }
    return result;
}
static vector<int> inorderTraversal_2(TreeNode *root)
{
    if (root == nullptr)
        return vector<int>{};
    stack<TreeNode *> path;
    TreeNode *lastVisited = nullptr;
    path.push(root);
    TreeNode *node;
    vector<int> result;
    while (!path.empty())
    {
        node = path.top();
        if (node->right != nullptr && node->right == lastVisited)
        {
            path.pop();
            lastVisited = node;
        }
        else if (node->left != nullptr && node->left != lastVisited)
        {
            path.push(node->left);
            lastVisited = node;
        }
        else
        {
            // left is null or left is just visited
            result.push_back(node->val);
            lastVisited = node;
            if (node->right != nullptr)
            {
                path.push(node->right);
            }
            else
            {
                path.pop();
            }
        }
    }
    return result;
}

// 145. Binary Tree Postorder Traversal
// Given a binary tree, return the postorder traversal of its nodes' values.
// For example: Given binary tree { 1,#,2,3 },
//  1
//   \
//    2
//   /
//  3
// return [3, 2, 1].
// Note: Recursive solution is trivial, could you do it iteratively?
static vector<int> postorderTraversal(TreeNode *root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode *> stack;
    TreeNode *lastVisited = nullptr;
    TreeNode *node = root;
    while (!stack.empty() || node != nullptr)
    {
        if (node != nullptr)
        {
            stack.push(node);
            lastVisited = node;
            node = node->left;
        }
        else
        {
            TreeNode *top = stack.top();
            if (top->right != nullptr && lastVisited != top->right)
            {
                node = top->right;
            }
            else
            {
                stack.pop();
                result.push_back(top->val);
                lastVisited = top;
            }
        }
    }
    return result;
}

// 95. Unique Binary Search Trees II
// Given an integer n, generate all structurally unique BST's (binary search
// trees) that store values 1...n. For example, Given n = 3, your program should
// return all 5 unique BST's shown below.
//  1         3     3      2      1
//   \       /     /      / \      \
//    3     2     1      1   3      2
//   /     /       \                 \
//  2     1         2                 3
static vector<TreeNode *> generateTrees(int n)
{
    if (n <= 0)
        return vector<TreeNode *>{};
    function<vector<vector<int>>(int, int)>
        generateSerializations = [&](int i, int j) -> vector<vector<int>> {
        vector<vector<int>> serializations;
        if (i > j)
        {
            serializations.push_back(vector<int>{0});
        }
        else
        {
            for (int k = i; k <= j; k++)
            {
                vector<vector<int>> leftSerializations = generateSerializations(i, k - 1);
                vector<vector<int>> rightSerializations = generateSerializations(k + 1, j);
                for (size_t l = 0; l < leftSerializations.size(); l++)
                {
                    for (size_t r = 0; r < rightSerializations.size(); r++)
                    {
                        vector<int> serialization = {k};
                        serialization.insert(serialization.end(), leftSerializations[l].begin(), leftSerializations[l].end());
                        serialization.insert(serialization.end(), rightSerializations[r].begin(), rightSerializations[r].end());
                        serializations.push_back(serialization);
                    }
                }
            }
        }
        return serializations;
    };
    function<TreeNode *(size_t &, vector<int> &)>
        generateTree = [&](size_t &i, vector<int> &serialization) -> TreeNode * {
        if (i >= serialization.size())
            return nullptr;
        if (serialization[i] == 0)
        {
            i++;
            return nullptr;
        }
        TreeNode *node = new TreeNode(serialization[i++]);
        node->left = generateTree(i, serialization);
        node->right = generateTree(i, serialization);
        return node;
    };
    vector<vector<int>> serializations = generateSerializations(1, n);
    vector<TreeNode *> trees;
    for (size_t i = 0; i < serializations.size(); i++)
    {
        size_t j = 0;
        trees.push_back(generateTree(j, serializations[i]));
    }
    return trees;
}
// incomplete
static vector<TreeNode *> generateTrees_2(int n)
{
    if (n <= 0)
        return vector<TreeNode *>{};
    function<vector<TreeNode *>(int, int)>
        solve = [&](int i, int j) -> vector<TreeNode *> {
        if (i > j)
        {
            return vector<TreeNode *>{nullptr};
        }
        if (i == j)
        {
            return vector<TreeNode *>{new TreeNode(i)};
        }
        for (int k = i; k <= j; k++)
        {
            vector<TreeNode *> leftChildren = solve(i, k - 1);
            vector<TreeNode *> rightChildren = solve(k + 1, j);
        }
        return vector<TreeNode *>{};
    };
    return solve(1, n);
}

// 96. Unique Binary Search Trees
// Given n, how many structurally unique BST's (binary search trees) that store
// values 1...n? For example, Given n = 3, there are a total of 5 unique BST's.
// 1         3     3      2      1
//  \       /     /      / \      \
//   3     2     1      1   3      2
//  /     /       \                 \
// 2     1         2                 3
static int numTrees(int n)
{
    if (n <= 0)
        return 0;
    map<pair<int, int>, int> solved;
    function<int(int, int)>
        count = [&](int i, int j) -> int {
        if (i >= j)
            return 1;
        pair<int, int> p = make_pair(i, j);
        if (solved.find(p) != solved.end())
            return solved[p];
        int c = 0;
        for (int k = i; k <= j; k++)
        {
            c += (count(i, k - 1) * count(k + 1, j));
        }
        solved[p] = c;
        return c;
    };
    return count(1, n);
}
// c[n] = c[0]*c[n-1] + c[1]*c[n-2] + ... + c[n-2]*c[1] + c[n-1]*c[0]
static int numTrees2(int n)
{
    if (n <= 0)
        return 0;
    vector<int> count(n + 1, 0);
    count[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            count[i] += count[j] * count[i - j - 1];
        }
    }
    return count[n];
}

// 98. Validate Binary Search Tree
// Given a binary tree, determine if it is a valid binary search tree (BST).
// Assume a BST is defined as follows: The left subtree of a node contains only
// nodes with keys less than the node's key. The right subtree of a node contains
// only nodes with keys greater than the node's key. Both the left and right
// subtrees must also be binary search trees. Example 1:
//   2
//  / \
// 1   3
// Binary tree [2, 1, 3], return true. Example 2:
//   1
//  / \
// 2   3
// Binary tree [1, 2, 3], return false.
// In-order traverse and check whether values are increasing.
static bool isValidBST(TreeNode *root)
{
    stack<TreeNode *> path;
    TreeNode *node = root;
    TreeNode *prev = nullptr;
    while (!path.empty() || node != nullptr)
    {
        if (node != nullptr)
        {
            // Move left as much as possible
            path.push(node);
            node = node->left;
        }
        else
        {
            // == case 1 ========
            // node is null and is the left child of the top of stack
            //   top
            //   / \
            // null ...
            // == case 2 ========
            // node is null and is the right child of the last visited node
            //     top
            //     /
            //    o
            //   / \
            // null ...
            //       \
            //        o <-- last visited (prev)
            //       / \
            //    null null
            // In both cases, left subtree is done, the top is the one to visit
            node = path.top();
            // Pop the top because no need to visit it again
            path.pop();
            // Visit current node
            if (prev != nullptr && prev->val >= node->val)
                return false;
            prev = node;
            // Move right
            node = node->right;
        }
    }
    return true;
}
static bool isValidBST2(TreeNode *root)
{
    if (root == nullptr)
        return true;
    stack<TreeNode *> path;
    path.push(root);
    TreeNode *node = root;
    TreeNode *prev = nullptr;
    TreeNode *lastVisited = nullptr;
    while (!path.empty())
    {
        node = path.top();
        if (node->right != nullptr && node->right == lastVisited)
        {
            lastVisited = node;
            path.pop();
        }
        else if (node->left != nullptr && node->left != lastVisited)
        {
            lastVisited = node;
            path.push(node->left);
        }
        else
        {
            if (prev != nullptr && prev->val >= node->val)
                return false;
            prev = node;
            lastVisited = node;
            if (node->right != nullptr)
                path.push(node->right);
            else
                path.pop();
        }
    }
    return true;
}
static bool isValidBST3(TreeNode *root)
{
    function<bool(TreeNode *, int &, int &)>
        verify = [&](TreeNode *node, int &min, int &max) -> bool {
        if (node == nullptr)
            return true;
        if (node->left == nullptr && node->right == nullptr)
        {
            min = node->val;
            max = node->val;
            return true;
        }

        if (node->left == nullptr)
        {
            min = node->val;
        }
        else
        {
            int leftMin;
            int leftMax;
            if (!verify(node->left, leftMin, leftMax))
                return false;
            if (leftMax >= node->val)
                return false;
            min = leftMin;
        }

        if (node->right == nullptr)
        {
            max = node->val;
        }
        else
        {
            int rightMin;
            int rightMax;
            if (!verify(node->right, rightMin, rightMax))
                return false;
            if (rightMin <= node->val)
                return false;
            max = rightMax;
        }

        return true;
    };

    int min;
    int max;
    return verify(root, min, max);
}

// 100. Same Tree
// Given two binary trees, write a function to check if they are equal or not.
// Two binary trees are considered equal if they are structurally identical and
// the nodes have the same value.
static bool isSameTree(TreeNode *p, TreeNode *q)
{
    function<bool(TreeNode *, TreeNode *)>
        isSame = [&](TreeNode *node1, TreeNode *node2) -> bool {
        if (node1 == nullptr && node2 == nullptr)
            return true;
        if (node1 == nullptr || node2 == nullptr)
            return false;
        if (node1->val != node2->val)
            return false;
        if (!isSame(node1->left, node2->left))
            return false;
        return isSame(node1->right, node2->right);
    };
    return isSame(p, q);
}

// 101. Symmetric Tree
// Given a binary tree, check whether it is a mirror of itself (ie, symmetric
// around its center). For example, this binary tree [1, 2, 2, 3, 4, 4, 3] is
// symmetric :
//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3
// But the following[1, 2, 2, null, 3, null, 3] is not:
//   1
//  / \
// 2   2
//  \   \
//   3   3
// Note: Bonus points if you could solve it both recursively and iteratively.
static bool isSymmetric(TreeNode *root)
{
    function<bool(TreeNode *, TreeNode *)>
        isSame = [&](TreeNode *node1, TreeNode *node2) -> bool {
        if (node1 == nullptr && node2 == nullptr)
            return true;
        if (node1 == nullptr || node2 == nullptr)
            return false;
        if (node1->val != node2->val)
            return false;
        if (!isSame(node1->left, node2->right))
            return false;
        return isSame(node1->right, node2->left);
    };
    return isSame(root, root);
}
static bool isSymmetric_2(TreeNode *root)
{
    deque<TreeNode *> deq;
    deq.push_front(root);
    deq.push_back(root);
    TreeNode *node1;
    TreeNode *node2;
    while (!deq.empty())
    {
        node1 = deq.front();
        deq.pop_front();
        node2 = deq.back();
        deq.pop_back();
        if (node1 == nullptr && node2 == nullptr)
            continue;
        if (node1 == nullptr || node2 == nullptr)
            return false;
        if (node1->val != node2->val)
            return false;
        deq.push_front(node1->right);
        deq.push_front(node1->left);
        deq.push_back(node2->left);
        deq.push_back(node2->right);
    }
    return true;
}

// 110. Balanced Binary Tree
// Given a binary tree, determine if it is height-balanced. For this problem,
// a height-balanced binary tree is defined as a binary tree in which the depth
// of the two subtrees of every node never differ by more than 1.
static bool isBalanced(TreeNode *root)
{
    function<bool(TreeNode *, int &)>
        solve = [&](TreeNode *node, int &depth) -> bool {
        if (node == nullptr)
        {
            depth = 0;
            return true;
        }
        int leftDepth;
        if (!solve(node->left, leftDepth))
            return false;
        int rightDepth;
        if (!solve(node->right, rightDepth))
            return false;
        if (abs(leftDepth - rightDepth) > 1)
            return false;
        depth = 1 + max(leftDepth, rightDepth);
        return true;
    };
    int depth;
    return solve(root, depth);
}

// 102. Binary Tree Level Order Traversal
// Given a binary tree, return the level order traversal of its nodes' values.
// (ie, from left to right, level by level). For example :
// Given binary tree [3, 9, 20, null, null, 15, 7],
//   3
//  / \
// 9  20
//    / \
//  15   7
// return its level order traversal as :
// [
//  [3],
//  [9, 20],
//  [15, 7]
// ]
static vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    if (root == nullptr)
        return result;
    queue<TreeNode *> q[2];
    q[0].push(root);
    int level = 0;
    while (!q[0].empty() || !q[1].empty())
    {
        int currentLevel = level % 2;
        int nextLevel = (level + 1) % 2;
        vector<int> v;
        TreeNode *node;
        while (!q[currentLevel].empty())
        {
            node = q[currentLevel].front();
            q[currentLevel].pop();
            v.push_back(node->val);
            if (node->left != nullptr)
                q[nextLevel].push(node->left);
            if (node->right != nullptr)
                q[nextLevel].push(node->right);
        }
        result.push_back(v);
        level++;
    }
    return result;
}

// 103. Binary Tree Zigzag Level Order Traversal
// Given a binary tree, return the zigzag level order traversal of its nodes'
// values. (ie, from left to right, then right to left for the next level and
// alternate between). For example :
// Given binary tree [3, 9, 20, null, null, 15, 7],
//   3
//  / \
// 9  20
//    / \
//  15   7
// return its zigzag level order traversal as :
// [
//  [3],
//  [20, 9],
//  [15, 7]
// ]
static vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    if (root == nullptr)
        return result;
    deque<TreeNode *> q[2];
    int level = 0;
    bool leftToRight = true;
    q[0].push_back(root);
    while (!q[0].empty() || !q[1].empty())
    {
        int currentLevel = level % 2;
        int nextLevel = (level + 1) % 2;
        vector<int> v;
        TreeNode *node;
        if (leftToRight)
        {
            while (!q[currentLevel].empty())
            {
                node = q[currentLevel].front();
                q[currentLevel].pop_front();
                v.push_back(node->val);
                if (node->left != nullptr)
                    q[nextLevel].push_back(node->left);
                if (node->right != nullptr)
                    q[nextLevel].push_back(node->right);
            }
        }
        else
        {
            while (!q[currentLevel].empty())
            {
                node = q[currentLevel].back();
                q[currentLevel].pop_back();
                v.push_back(node->val);
                if (node->right != nullptr)
                    q[nextLevel].push_front(node->right);
                if (node->left != nullptr)
                    q[nextLevel].push_front(node->left);
            }
        }
        result.push_back(v);
        level++;
        leftToRight = !leftToRight;
    }
    return result;
}

// 107. Binary Tree Level Order Traversal II
// Given a binary tree, return the bottom-up level order traversal of its nodes'
// values. (ie, from left to right, level by level from leaf to root). For example :
// Given binary tree [3, 9, 20, null, null, 15, 7],
//   3
//  / \
// 9  20
//    / \
//  15   7
// return its bottom - up level order traversal as :
// [
//   [15, 7],
//   [9, 20],
//   [3]
// ]
static vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    vector<vector<int>> result;
    if (root == nullptr)
        return result;
    queue<TreeNode *> q[2];
    q[0].push(root);
    int level = 0;
    TreeNode *node;
    while (!q[0].empty() || !q[1].empty())
    {
        int currentLevel = level % 2;
        int nextLevel = (level + 1) % 2;
        vector<int> v;
        while (!q[currentLevel].empty())
        {
            node = q[currentLevel].front();
            q[currentLevel].pop();
            v.push_back(node->val);
            if (node->left != nullptr)
                q[nextLevel].push(node->left);
            if (node->right != nullptr)
                q[nextLevel].push(node->right);
        }
        result.insert(result.begin(), v);
        level++;
    }
    return result;
}

// 199. Binary Tree Right Side View
// Given a binary tree, imagine yourself standing on the right side of it,
// return the values of the nodes you can see ordered from top to bottom.
// For example: Given the following binary tree,
//   1      <---
//  / \
// 2   3    <---
//  \   \
//   5   4  <---
// You should return [1, 3, 4].
static vector<int> rightSideView(TreeNode *root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    queue<TreeNode *> q[2];
    q[0].push(root);
    int level = 0;
    int current = 0;
    int next = 0;
    TreeNode *p;
    while (!q[0].empty() || !q[1].empty())
    {
        current = level % 2;
        next = (level + 1) % 2;
        p = q[current].front();
        result.push_back(p->val);
        while (!q[current].empty())
        {
            p = q[current].front();
            q[current].pop();
            if (p->right != nullptr)
            {
                q[next].push(p->right);
            }
            if (p->left != nullptr)
            {
                q[next].push(p->left);
            }
        }
        level++;
    }
    return result;
}

// 104. Maximum Depth of Binary Tree
// Given a binary tree, find its maximum depth. The maximum depth is the number
// of nodes along the longest path from the root node down to the farthest leaf node.
static int maxDepth(TreeNode *root)
{
    function<int(TreeNode *)>
        depth = [&](TreeNode *node) -> int {
        if (node == nullptr)
            return 0;
        if (node->left == nullptr && node->right == nullptr)
            return 1;
        return 1 + max(depth(node->left), depth(node->right));
    };
    return depth(root);
}
// This is wrong
static int maxDepth_2(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    stack<TreeNode *> path;
    path.push(root);
    TreeNode *node;
    int depth = 1;
    int maxDepth = 0;
    while (!path.empty())
    {
        if (depth > maxDepth)
        {
            maxDepth = depth;
        }
        node = path.top();
        path.pop();
        if (node->right == nullptr && node->left == nullptr)
        {
            depth--;
        }
        else
        {
            depth++;
            if (node->right != nullptr)
                path.push(node->right);
            if (node->left != nullptr)
                path.push(node->left);
        }
    }
    return maxDepth;
}

// 111. Minimum Depth of Binary Tree
// Given a binary tree, find its minimum depth. The minimum depth is the number
// of nodes along the shortest path from the root node down to the nearest leaf node.
static int minDepth(TreeNode *root)
{
    function<int(TreeNode *, int)>
        solve = [&](TreeNode *node, int depth) -> int {
        if (node == nullptr)
            return depth;
        depth++;
        if (node->left == nullptr)
            return solve(node->right, depth);
        else if (node->right == nullptr)
            return solve(node->left, depth);
        else
            return min(solve(node->left, depth), solve(node->right, depth));
    };
    return solve(root, 0);
}

// 105. Construct Binary Tree from Preorder and Inorder Traversal
// Given preorder and inorder traversal of a tree, construct the binary tree.
// Note: You may assume that duplicates do not exist in the tree.
static TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    function<TreeNode *(int, int, int, int)>
        build = [&](int i1, int i2, int j1, int j2) -> TreeNode * {
        if (i1 > i2)
            return nullptr;
        TreeNode *node = new TreeNode(preorder[i1]);
        int k;
        for (k = j1; k <= j2; k++)
        {
            if (preorder[i1] == inorder[k])
                break;
        }
        if (k <= j2)
        {
            node->left = build(i1 + 1, i1 + k - j1, j1, k - 1);
            node->right = build(i1 + k - j1 + 1, i2, k + 1, j2);
        }
        return node;
    };
    return build(0, preorder.size() - 1, 0, inorder.size() - 1);
}

// 106. Construct Binary Tree from Inorder and Postorder Traversal
// Given inorder and postorder traversal of a tree, construct the binary tree.
// Note: You may assume that duplicates do not exist in the tree.
static TreeNode *buildTreeInOrderPostOrder(vector<int> &inorder, vector<int> &postorder)
{
    function<TreeNode *(int, int, int, int)>
        build = [&](int i1, int i2, int j1, int j2) -> TreeNode * {
        if (j1 > j2)
            return nullptr;
        TreeNode *node = new TreeNode(postorder[j2]);
        int k;
        for (k = i1; k <= i2; k++)
        {
            if (inorder[k] == postorder[j2])
                break;
        }
        if (k <= i2)
        {
            node->left = build(i1, k - 1, j1, j2 - i2 + k - 1);
            node->right = build(k + 1, i2, j2 - i2 + k, j2 - 1);
        }
        return node;
    };
    return build(0, inorder.size() - 1, 0, postorder.size() - 1);
}

// 108. Convert Sorted Array to Binary Search Tree
// Given an array where elements are sorted in ascending order, convert it to a
// height balanced BST.
static TreeNode *sortedArrayToBST(vector<int> &nums)
{
    function<TreeNode *(int, int)>
        build = [&](int i, int j) -> TreeNode * {
        if (i > j)
            return nullptr;
        int k = i + ((j - i) >> 1);
        TreeNode *node = new TreeNode(nums[k]);
        node->left = build(i, k - 1);
        node->right = build(k + 1, j);
        return node;
    };
    return build(0, nums.size() - 1);
}

// 109. Convert Sorted List to Binary Search Tree
// Given a singly linked list where elements are sorted in ascending order,
// convert it to a height balanced BST.
static TreeNode *sortedListToBST(ListNode *head)
{
    if (head == nullptr)
        return nullptr;
    if (head->next == nullptr)
        return new TreeNode(head->val);
    function<TreeNode *(ListNode *, ListNode *)>
        build = [&](ListNode *b, ListNode *e) -> TreeNode * {
        if (b == nullptr || e == nullptr)
            return nullptr;
        TreeNode *node;
        if (b == e)
        {
            node = new TreeNode(b->val);
        }
        else if (b->next == e)
        {
            node = new TreeNode(b->val);
            node->right = new TreeNode(e->val);
        }
        else
        {
            ListNode *p = b;
            ListNode *q = p->next->next;
            while (q != e && q->next != e)
            {
                p = p->next;
                q = q->next;
                q = q->next;
            }
            node = new TreeNode(p->next->val);
            node->left = build(b, p);
            node->right = build(p->next->next, e);
        }
        return node;
    };
    ListNode *p = head;
    ListNode *q = p->next;
    while (q->next != nullptr && q->next->next != nullptr)
    {
        p = p->next;
        q = q->next;
        q = q->next;
    }
    TreeNode *node = new TreeNode(p->next->val);
    node->left = build(head, p);
    node->right = build(p->next->next, q->next == nullptr ? q : q->next);
    return node;
}

// 114. Flatten Binary Tree to Linked List
// Given a binary tree, flatten it to a linked list in-place. For example, Given
//     1
//    / \
//   2   5
//  / \   \
// 3   4   6
// The flattened tree should look like:
// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
//          \
//           6
static void flatten(TreeNode *root)
{
    function<TreeNode *(TreeNode *)>
        solve = [&](TreeNode *node) -> TreeNode * {
        if (node == nullptr)
            return nullptr;
        if (node->left == nullptr && node->right == nullptr)
        {
            return node;
        }
        TreeNode *leftTail = solve(node->left);
        TreeNode *rightTail = solve(node->right);
        if (leftTail != nullptr)
        {
            leftTail->right = node->right;
            node->right = node->left;
            node->left = nullptr;
        }
        return rightTail == nullptr ? leftTail : rightTail;
    };
    solve(root);
}

// 173. Binary Search Tree Iterator
// Implement an iterator over a binary search tree (BST). Your iterator will be
// initialized with the root node of a BST. Calling next() will return the next
// smallest number in the BST. Note: next() and hasNext() should run in average
// O(1) time and uses O(h) memory, where h is the height of the tree.
class BSTIterator
{
private:
    stack<TreeNode *> _stack;
    TreeNode *_node;

public:
    BSTIterator(TreeNode *root)
    {
        _node = root;
    }

    /** @return whether we have a next smallest number */
    bool hasNext()
    {
        return !_stack.empty() || _node != nullptr;
    }

    /** @return the next smallest number */
    int next()
    {
        int val;
        while (hasNext())
        {
            if (_node != nullptr)
            {
                _stack.push(_node);
                _node = _node->left;
            }
            else
            {
                _node = _stack.top();
                _stack.pop();
                val = _node->val;
                _node = _node->right;
                break;
            }
        }
        return val;
    }
};

struct TreeLinkNode
{
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
};

// 116. Populating Next Right Pointers in Each Node
// Given a binary tree Populate each next pointer to point to its next right node.
// If there is no next right node, the next pointer should be set to NULL. Initially,
// all next pointers are set to NULL. Note: You may only use constant extra space.
// You may assume that it is a perfect binary tree (ie, all leaves are at the same
// level, and every parent has two children).
// For example, Given the following perfect binary tree,
//      1
//    /   \
//   2     3
//  / \   / \
// 4   5 6   7
// After calling your function, the tree should look like :
//      1->NULL
//    /   \
//   2 ->  3->NULL
//  / \   / \
// 4-> 5->6->7->NULL
static void connect(TreeLinkNode *root)
{
    TreeLinkNode *leftMost = root;
    while (leftMost != nullptr && leftMost->left != nullptr)
    {
        TreeLinkNode *node = leftMost;
        leftMost = leftMost->left;
        TreeLinkNode *left = nullptr;
        while (node != nullptr)
        {
            if (left != nullptr)
            {
                left->next = node->left;
            }
            node->left->next = node->right;
            left = node->right;
            node = node->next;
        }
    }
}

// 117. Populating Next Right Pointers in Each Node II
// Follow up for problem "Populating Next Right Pointers in Each Node". What if
// the given tree could be any binarytree ? Would your previous solution still
// work? Note: You may only use constant extra space. For example, Given the
// following binary tree,
//     1
//    / \
//   2    3
//  / \    \
// 4   5    7
// After calling your function, the tree should look like :
//     1->NULL
//    / \
//   2 -> 3->NULL
//  / \    \
// 4-> 5 -> 7->NULL
static void connect2(TreeLinkNode *root)
{
    TreeLinkNode *leftMost = root;
    while (leftMost != nullptr)
    {
        TreeLinkNode *node = leftMost;
        leftMost = nullptr;
        TreeLinkNode *left = nullptr;
        while (node != nullptr)
        {
            if (node->left != nullptr)
            {
                if (leftMost == nullptr)
                {
                    leftMost = node->left;
                }
                if (left != nullptr)
                {
                    left->next = node->left;
                }
                left = node->left;
            }
            if (node->right != nullptr)
            {
                if (leftMost == nullptr)
                {
                    leftMost = node->right;
                }
                if (left != nullptr)
                {
                    left->next = node->right;
                }
                left = node->right;
            }
            node = node->next;
        }
    }
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
