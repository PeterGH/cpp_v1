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
    auto getChar = [&](int i) -> char {
        if ((i & 0x1) == 0)
            return '#';
        return s[i >> 1];
    };
    auto expand = [&](int c, int &l) {
        int n = (s.size() << 1) + 1;
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
    if (s.empty())
        return s;
    int n = (s.size() << 1) + 1;
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