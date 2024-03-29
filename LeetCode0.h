#ifndef _LEETCODE0_H_
#define _LEETCODE0_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 1. Two Sum
        // Given an array of integers nums and an integer target,
        // return indices of the two numbers such that they add up to target.
        // You may assume that each input would have exactly one solution,
        // and you may not use the same element twice.
        // You can return the answer in any order.
        // Example 1:
        // Input: nums = [2,7,11,15], target = 9
        // Output: [0,1]
        // Output: Because nums[0] + nums[1] == 9, we return [0, 1].
        // Example 2:
        // Input: nums = [3,2,4], target = 6
        // Output: [1,2]
        // Example 3:
        // Input: nums = [3,3], target = 6
        // Output: [0,1]
        // Constraints:
        // 2 <= nums.length <= 10^3
        // -10^9 <= nums[i] <= 10^9
        // -10^9 <= target <= 10^9
        // Only one valid answer exists.
        vector<int> twoSum(const vector<int> &nums, int target)
        {
            unordered_map<int, int> m;
            vector<int> output;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                int t = target - nums[i];
                if (m.find(t) != m.end())
                {
                    output.push_back(m[t]);
                    output.push_back(i);
                    break;
                }
                m[nums[i]] = i;
            }
            return output;
        }

        static vector<pair<int, int>> twoSumUnsortedMultiSolutions(vector<int> &nums, int target)
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
                         [&](unordered_multimap<int, int>::value_type &v)
                         {
                             result.push_back(make_pair(v.second, i));
                         });
                m.insert(make_pair(nums[i], i));
            }
            return result;
        }
        static vector<pair<int, int>> twoSumUnsortedMultiSolutions2(vector<int> &nums,
                                                                    int target)
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
            function<size_t(int, size_t, size_t)> partition = [&](int v, size_t b,
                                                                  size_t e) -> size_t
            {
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
                        result.push_back(
                            make_pair(min(valueIndex[i].second, valueIndex[j].second),
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
                    return result; // All numbers are greater than half, no matter
                                   // whether target is positive or negative
                if (i1 == length)
                    return result; // All numbers are less than or equal to half, no
                                   // matter whether target is positive or negative
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
            sort(valueIndex.begin() + longRangeBegin,
                 valueIndex.begin() + longRangeEnd + 1);
            // find the first element in valueIndex[b..e] equal to v
            function<int(int, int, int)> search = [&](int v, int b, int e) -> int
            {
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
                    result.push_back(
                        make_pair(min(valueIndex[i].second, valueIndex[j].second),
                                  max(valueIndex[i].second, valueIndex[j].second)));
                    j++;
                } while (j <= (int)longRangeEnd && valueIndex[j].first == v);
            }
            return result;
        }

        // 15. 3Sum
        // Given an array nums of n integers, are there elements a, b, c in nums such
        // that a + b + c = 0? Find all unique triplets in the array which gives the sum
        // of zero. Note: The solution set must not contain duplicate triplets. Example:
        // Given array nums = [-1, 0, 1, 2, -1, -4], A solution set is:
        // [
        //   [-1, 0, 1],
        //   [-1, -1, 2]
        // ]
        vector<vector<int>> threeSum(vector<int> &nums)
        {
            vector<vector<int>> result;
            set<tuple<int, int>> m; // dedup
            for (size_t i = 0; i + 2 < nums.size(); i++)
            {
                set<int> s;
                for (size_t j = i + 1; j < nums.size(); j++)
                {
                    if (s.find(-nums[i] - nums[j]) != s.end())
                    {
                        vector<int> r = {nums[i], -nums[i] - nums[j], nums[j]};
                        sort(r.begin(), r.end());
                        tuple<int, int> t = make_tuple(r[0], r[1]);
                        if (m.find(t) == m.end())
                        {
                            result.push_back(r);
                            m.insert(t);
                        }
                    }
                    s.insert(nums[j]);
                }
            }
            return result;
        }
        vector<vector<int>> threeSum2(vector<int> &nums)
        {
            vector<vector<int>> ans;
            int n = nums.size();
            if (n < 3)
                return ans;
            sort(nums.begin(), nums.end());
            if (nums[0] > 0 || nums[n - 1] < 0)
                return ans;
            int i = 0;
            while (i <= n - 3)
            {
                if (nums[i] > 0)
                    break;
                // Two-sum [i+1..n-1]
                int j = i + 1;
                int k = n - 1;
                while (j < k)
                {
                    int s = nums[j] + nums[k];
                    if (s == -nums[i])
                        ans.push_back(vector<int>{nums[i], nums[j], nums[k]});
                    if (s <= -nums[i])
                    {
                        while (j + 1 < k && nums[j + 1] == nums[j])
                            j++;
                        j++;
                    }
                    if (s >= -nums[i])
                    {
                        while (j < k - 1 && nums[k - 1] == nums[k])
                            k--;
                        k--;
                    }
                }
                while (i + 1 <= n - 3 && nums[i + 1] == nums[i])
                    i++;
                i++;
            }
            return ans;
        }
        vector<vector<int>> threeSum3(vector<int> &nums)
        {
            vector<vector<int>> ans;
            int n = nums.size();
            if (n < 3)
                return ans;
            sort(nums.begin(), nums.end());
            if (nums[0] > 0 || nums[n - 1] < 0)
                return ans;
            int i = 0;
            while (i <= n - 3)
            {
                if (nums[i] > 0)
                    break;
                int j = i + 1;
                while (j <= n - 2)
                {
                    int s = nums[i] + nums[j];
                    if (s > 0)
                        break;
                    // Binary search [j+1..n-1]
                    int t = -s;
                    int l = j + 1;
                    int h = n - 1;
                    int m;
                    while (l <= h)
                    {
                        m = l + ((h - l) >> 1);
                        if (t < nums[m])
                        {
                            if (l == m)
                                break;
                            h = m - 1;
                        }
                        else if (nums[m] < t)
                        {
                            if (m == h)
                                break;
                            l = m + 1;
                        }
                        else
                        {
                            ans.push_back(vector<int>{nums[i], nums[j], nums[m]});
                            break;
                        }
                    }
                    while (j + 1 <= n - 2 && nums[j + 1] == nums[j])
                        j++;
                    j++;
                }
                while (i + 1 <= n - 3 && nums[i + 1] == nums[i])
                    i++;
                i++;
            }
            return ans;
        }

        // 16. 3Sum Closest
        // Given an array nums of n integers and an integer target, find three integers
        // in nums such that the sum is closest to target. Return the sum of the three
        // integers. You may assume that each input would have exactly one solution.
        // Example: Given array nums = [-1, 2, 1, -4], and target = 1. The sum that is
        // closest to the target is 2. (-1 + 2 + 1 = 2).
        // Similar to 3sum but instead of searching for exact match
        // track and minimize the distance to the target.
        int threeSumClosest(vector<int> &nums, int target)
        {
            sort(nums.begin(), nums.end());
            size_t i = 0;
            int r = 0;
            int d = INT_MAX;
            while (i + 2 < nums.size())
            {
                int j = i + 1;
                int k = nums.size() - 1;
                while (j < k)
                {
                    int s = nums[i] + nums[j] + nums[k];
                    if (abs(target - s) < d)
                    {
                        d = abs(target - s);
                        r = s;
                    }
                    if (d == 0)
                        return target;
                    if (s < target)
                        j++;
                    else
                        k--;
                }
                i++;
            }
            return r;
        }
        int threeSumClosest2(vector<int> &nums, int target)
        {
            int n = nums.size();
            sort(nums.begin(), nums.end());
            int i = 0;
            int d = INT_MAX;
            int t = target;
            while (i <= n - 3)
            {
                int j = i + 1;
                int k = n - 1;
                while (j < k)
                {
                    int s = nums[i] + nums[j] + nums[k];
                    if (s < target)
                    {
                        if (target - s <= d)
                        {
                            d = target - s;
                            t = s;
                        }
                        while (j + 1 < k && nums[j + 1] == nums[j])
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
                        while (j < k - 1 && nums[k - 1] == nums[k])
                            k--;
                        k--;
                    }
                    else
                    {
                        return s;
                    }
                }
                while (i + 1 <= n - 3 && nums[i + 1] == nums[i])
                    i++;
                i++;
            }
            return t;
        }

        // 18. 4Sum
        // Given an array nums of n integers and an integer target, are there
        // elements a, b, c, and d in nums such that a + b + c + d = target?
        // Find all unique quadruplets in the array which gives the sum of target.
        // Note: The solution set must not contain duplicate quadruplets.
        // Example: Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
        // A solution set is:
        // [
        //   [-1,  0, 0, 1],
        //   [-2, -1, 1, 2],
        //   [-2,  0, 0, 2]
        // ]
        vector<vector<int>> fourSum(vector<int> &nums, int target)
        {
            vector<vector<int>> result;
            sort(nums.begin(), nums.end());
            size_t i = 0;
            while (i + 3 < nums.size())
            {
                size_t j = i + 1;
                while (j + 2 < nums.size())
                {
                    int t = target - nums[i] - nums[j];
                    int m = j + 1;
                    int n = nums.size() - 1;
                    while (m < n)
                    {
                        int s = nums[m] + nums[n];
                        if (s == t)
                            result.push_back(
                                vector<int>{nums[i], nums[j], nums[m], nums[n]});
                        if (s <= t)
                        {
                            while (m + 1 < n && nums[m] == nums[m + 1])
                                m++;
                            m++;
                        }
                        if (s >= t)
                        {
                            while (m < n - 1 && nums[n - 1] == nums[n])
                                n--;
                            n--;
                        }
                    }
                    while (j + 1 < nums.size() && nums[j] == nums[j + 1])
                        j++;
                    j++;
                }
                while (i + 1 < nums.size() && nums[i] == nums[i + 1])
                    i++;
                i++;
            }
            return result;
        }
        vector<vector<int>> fourSum2(vector<int> &num, int target)
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
                        for_each(
                            twosum[t].begin(), twosum[t].end(), [&](pair<int, int> p)
                            {
                                vector<int> a = {p.first, p.second, num[i], num[j]};
                                ans.insert(a); });
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
        vector<vector<int>> fourSum3(vector<int> &nums, int target)
        {
            vector<vector<int>> output;
            sort(nums.begin(), nums.end());
            function<void(size_t, int, vector<int> &)>
                solve = [&](size_t i, int t, vector<int> &c)
            {
                if (c.size() == 4)
                {
                    if (t == 0)
                        output.push_back(c);
                    return;
                }
                // cannot add nums[i] > t because there can be negative numbers
                // i >= nums.size() || nums[i] > t)
                if (i >= nums.size())
                    return;
                c.push_back(nums[i]);
                solve(i + 1, t - nums[i], c);
                c.pop_back();
                while (i + 1 < nums.size() && nums[i] == nums[i + 1])
                    i++;
                i++;
                solve(i, t, c);
            };
            vector<int> a;
            solve(0, target, a);
            return output;
        }
        // [TODO] Generalize to X-Sum
        vector<vector<int>> fourSum4(vector<int> &num, int target)
        {
            if (num.size() < 4)
                return vector<vector<int>>{};
            sort(num.begin(), num.end());
            function<void(vector<int> &, int, int, const vector<int> &,
                          vector<vector<int>> &)>
                solve = [&](vector<int> &n, int i, int t, const vector<int> &s,
                            vector<vector<int>> &o)
            {
                // Search n[i..] for target sum t, where s contains candidates
                // found so far and o is the output collection.
                if (s.size() == 3)
                {
                    // Already have 3 numbers, just need one more
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
                // while (i <= (int)n.size() - 4 + (int)s.size() && n[i] <= t) {
                while (i <= (int)n.size() - 4 + (int)s.size())
                {
                    // Skip all the duplicates of n[i]
                    int j = i;
                    while (j + 1 < (int)n.size() && n[j + 1] == n[j])
                        j++;
                    // Now all n[i..j] are the same
                    int k = i;    // k iterates from i to j
                    int u = n[k]; // partial sum n[i..k]
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
                    i = j + 1; // Move to next number, i.e., skip n[i..j]
                }
            };
            vector<vector<int>> o;
            solve(num, 0, target, vector<int>{}, o);
            return o;
        }
        vector<vector<int>> fourSum5(vector<int> &num, int target)
        {
            if (num.size() < 4)
                return vector<vector<int>>{};
            sort(num.begin(), num.end());
            function<void(vector<int> &, int, int, int, const vector<int> &,
                          vector<vector<int>> &)>
                solve = [&](vector<int> &n, int i, int r, int t, const vector<int> &s,
                            vector<vector<int>> &o)
            {
                // Search n[i..] for remaining r numbers whose sum is t
                // while (r > 0 && i <= (int)n.size() - r && n[i] <= t) {
                while (r > 0 && i <= (int)n.size() - r)
                {
                    int j = i;
                    while (j + 1 < (int)n.size() && n[j + 1] == n[j])
                        j++;
                    // Range num[i..j] contains the same number
                    int k = i;
                    int u = 0; // n[k];
                    int c = 0; // 1;
                    vector<int> v(s);
                    // while (k <= j && u <= t && c <= r) {
                    while (k <= j && c <= r)
                    {
                        v.push_back(n[k]);
                        u += n[k];
                        c++;
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
                        // u += n[k];
                        // c++;
                    }
                    i = j + 1;
                }
            };
            vector<vector<int>> o;
            solve(num, 0, 4, target, vector<int>{}, o);
            return o;
        }
        vector<vector<int>> fourSum6(vector<int> &nums, int target)
        {
            vector<vector<int>> result;
            sort(nums.begin(), nums.end());
            vector<vector<int>> tuple(1, vector<int>{}); // contain tuples of less than 4 numbers
            size_t i = 0;
            while (i < nums.size())
            {
                size_t j = i;
                while (j + 1 < nums.size() && nums[j + 1] == nums[j])
                    j++;
                // nums[i..j] are the same
                size_t m = tuple.size(); // will try to extend m tuples, i.e., tuple[0..(m-1)]
                vector<int> c;
                for (size_t k = i; k <= j && k < i + 4; k++)
                {
                    c.push_back(nums[k]); // contain nums[i..k]
                    for (size_t l = 0; l < m; l++)
                    {
                        vector<int> v = tuple[l];
                        v.insert(v.end(), c.begin(), c.end());
                        if (v.size() < 4)
                        {
                            tuple.push_back(v);
                        }
                        else if (v.size() == 4)
                        {
                            int s = accumulate(v.begin(), v.end(), 0);
                            if (s == target)
                                result.push_back(v);
                        }
                    }
                }
                i = j + 1;
            }
            return result;
        }
        // Find 4 indices from 0 to n-1 such that the sum of the 4 numbers sum up to target
        // DFS indice tree
        // ()----------------------------------------
        // |                                  |     |
        // 0-----------------------------     1 .. n-1
        // |                            |     |
        // 1--------------------------  2 ..  2 ..
        // |          |              |  |     |
        // 2--------  3-------- ..  n-1 3 ..  3 ..
        // | |     |  | |     |         |     |
        // 3 4 .. n-1 4 5 .. n-1        4 ..  5 ..
        vector<vector<int>> fourSum7(vector<int> &nums, int target)
        {
            vector<vector<int>> output;
            int n = nums.size();
            if (n < 4)
                return output;
            sort(nums.begin(), nums.end());
            vector<int> c;
            int i = 0;
            int last = -1;
            while (!c.empty() || i != n)
            {
                if (i != n)
                {
                    if (c.size() < 4 && last != n)
                    {
                        c.push_back(i++);
                    }
                    else
                    {
                        c.back() = i++;
                        if (nums[c.back()] == nums[c.back() - 1])
                            continue; // dedup
                    }
                    last = c.back();
                    if (c.size() == 4)
                    {
                        if (nums[c[0]] + nums[c[1]] + nums[c[2]] + nums[c[3]] == target)
                        {
                            vector<int> o;
                            for (int j : c)
                            {
                                o.push_back(nums[j]);
                            }
                            output.push_back(o);
                        }
                    }
                }
                else
                {
                    last = i; // == n
                    c.pop_back();
                    if (!c.empty())
                        i = c.back() + 1;
                }
            }
            return output;
        }
        // BFS indices tree
        vector<vector<int>> fourSum8(vector<int> &nums, int target)
        {
            vector<vector<int>> output;
            int n = nums.size();
            if (n < 4)
                return output;
            sort(nums.begin(), nums.end());
            queue<pair<vector<int>, int>> c;
            for (int i = 0; i < n; i++)
            {
                if (i == 0 || nums[i - 1] != nums[i])
                {
                    c.push(make_pair(vector<int>{i}, nums[i]));
                }
            }
            while (!c.empty())
            {
                pair<vector<int>, int> p = c.front();
                c.pop();
                if (p.first.size() < 4)
                {
                    for (int i = p.first.back() + 1; i < n; i++)
                    {
                        if (i == p.first.back() + 1 || nums[i - 1] != nums[i])
                        {
                            auto q = p;
                            q.first.push_back(i);
                            q.second += nums[i];
                            c.push(q);
                        }
                    }
                }
                else if (p.second == target)
                {
                    vector<int> o;
                    for (int i : p.first)
                    {
                        o.push_back(nums[i]);
                    }
                    output.push_back(o);
                }
            }
            return output;
        }
        vector<vector<int>> fourSum9(vector<int> &nums, int target)
        {
            vector<vector<int>> output;
            size_t n = nums.size();
            if (n < 4)
                return output;
            sort(nums.begin(), nums.end());
            for (size_t a = 0; a + 3 < n; a++)
            {
                if (a > 0 && nums[a - 1] == nums[a])
                    continue;
                for (size_t b = a + 1; b + 2 < n; b++)
                {
                    if (b > a + 1 && nums[b - 1] == nums[b])
                        continue;
                    for (size_t c = b + 1; c + 1 < n; c++)
                    {
                        if (c > b + 1 && nums[c - 1] == nums[c])
                            continue;
                        for (size_t d = c + 1; d < n; d++)
                        {
                            if (d > c + 1 && nums[d - 1] == nums[d])
                                continue;
                            if (nums[a] + nums[b] + nums[c] + nums[d] == target)
                            {
                                output.push_back(vector<int>{nums[a], nums[b], nums[c], nums[d]});
                            }
                        }
                    }
                }
            }
            return output;
        }
        // wrong
        vector<vector<int>> fourSum10(vector<int> &nums, int target)
        {
            vector<vector<int>> output;
            int n = nums.size();
            if (n < 4)
                return output;
            function<int(int)> next = [&](int i) -> int
            {
                while (i + 1 < n && nums[i] == nums[i + 1])
                    i++;
                return i + 1;
            };
            vector<int> c(1, 0);
            long long s = nums[0];
            while (!c.empty())
            {
                if (c.size() == 4 && s == target)
                {
                    vector<int> o;
                    for (int i : c)
                    {
                        o.push_back(nums[i]);
                    }
                    output.push_back(o);
                }
                if (c.back() == n - 1)
                {
                    s -= nums[c.back()];
                    c.pop_back();
                    if (c.empty())
                        break;
                    c.back() = next(c.back());
                    if (c.back() == n)
                    {
                        c.back() = n - 1;
                    }
                    else
                    {
                        s += nums[c.back()] - nums[c.back() - 1];
                    }
                }
                else if (c.size() < 4)
                {
                    c.push_back(c.back() + 1);
                    s += nums[c.back()];
                }
                else
                {
                    c.back() = next(c.back());
                    if (c.back() == n)
                    {
                        c.back() = n - 1;
                    }
                    else
                    {
                        s += nums[c.back()] - nums[c.back() - 1];
                    }
                }
            }
            return output;
        }

        // 4Sum II
        // Given four lists A, B, C, D of integer values, compute how many
        // tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.
        // To make problem a bit easier, all A, B, C, D have same length of
        // N where 0 <= N <= 500. All integers are in the range of -2^28 to
        // 2^28 - 1 and the result is guaranteed to be at most 2^31 - 1.
        // Example:
        // Input:
        // A = [ 1, 2]
        // B = [-2,-1]
        // C = [-1, 2]
        // D = [ 0, 2]
        // Output:
        // 2
        // Explanation:
        // The two tuples are:
        // 1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
        // 2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
        int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
        {
            multimap<int, pair<int, int>> ab;
            for (int i = 0; i < (int)A.size(); i++)
            {
                for (int j = 0; j < (int)B.size(); j++)
                {
                    ab.emplace(A[i] + B[j], make_pair(i, j));
                }
            }
            int c = 0;
            for (int i = 0; i < (int)C.size(); i++)
            {
                for (int j = 0; j < (int)D.size(); j++)
                {
                    c += ab.count(-(C[i] + D[j]));
                }
            }
            return c;
        }
        int fourSumCount2(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
        {
            sort(A.begin(), A.end());
            sort(B.begin(), B.end());
            sort(C.begin(), C.end());
            sort(D.begin(), D.end());
            int nA = (int)A.size();
            int nB = (int)B.size();
            int nC = (int)C.size();
            int nD = (int)D.size();
            int count = 0;
            set<tuple<int, int, int, int>> s;
            function<void(int, int, int, int)> solve =
                [&](int a, int b, int c, int d)
            {
                if (a < 0 || a >= nA || b < 0 || b >= nB || c < 0 || c >= nC || d < 0 || d >= nD)
                    return;
                int t = A[a] + B[b] + C[c] + D[d];
                auto i = make_tuple(a, b, c, d);
                if (t == 0)
                {
                    if (s.find(i) == s.end())
                    {
                        count++;
                        s.insert(i);
                    }
                }
                solve(a + 1, b, c, d);
                solve(a, b + 1, c, d);
                solve(a, b, c - 1, d);
                solve(a, b, c, d - 1);
            };
            solve(0, 0, nC - 1, nD - 1);
            return count;
        }
        // This is wrong
        // Given
        // {-1, -1}
        // {-1, 1}
        // {-1, 1}
        // {-1, 1}
        // Output is
        // count(0, 0, 1, 1) = 2
        //  count(1, 1, 1, 1) = 2
        //   count(1, 1, 0, 1) = 3
        //    count(1, 1, 0, 0) = 3
        //   count(1, 1, 1, 0) = 4
        //    count(1, 1, 0, 0) = 4
        //  count(1, 0, 0, 1) = 4
        //   count(1, 1, 0, 1) = 4
        //    count(1, 1, 0, 0) = 4
        //   count(1, 0, 0, 0) = 4
        //    count(1, 1, 0, 0) = 4
        //  count(1, 0, 1, 0) = 4
        //   count(1, 1, 1, 0) = 4
        //    count(1, 1, 0, 0) = 4
        //   count(1, 0, 0, 0) = 4
        //    count(1, 1, 0, 0) = 4
        // Two are missing: (0, 1, 0, 1) and (0, 1, 1, 0)
        int fourSumCount3(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
        {
            function<int(const vector<int> &, int &)> increase =
                [&](const vector<int> &v, int &i) -> int
            {
                int s = 1;
                while (i + 1 < (int)v.size() && v[i] == v[i + 1])
                {
                    i++;
                    s++;
                }
                return s;
            };
            function<int(const vector<int> &, int &)> decrease =
                [&](const vector<int> &v, int &i) -> int
            {
                int s = 1;
                while (i > 0 && v[i - 1] == v[i])
                {
                    i--;
                    s++;
                }
                return s;
            };
            sort(A.begin(), A.end());
            sort(B.begin(), B.end());
            sort(C.begin(), C.end());
            sort(D.begin(), D.end());
            int nA = (int)A.size();
            int nB = (int)B.size();
            int nC = (int)C.size();
            int nD = (int)D.size();
            int count = 0;
            set<tuple<int, int, int, int>> s;
            function<void(int, int, int, int, int)> solve =
                [&](int k, int a, int b, int c, int d)
            {
                if (a < 0 || a >= nA || b < 0 || b >= nB || c < 0 || c >= nC || d < 0 || d >= nD)
                    return;
                cout << string(k, ' ') << "count(" << a << ", " << b
                     << ", " << c << ", " << d << ") = ";
                int t = A[a] + B[b] + C[c] + D[d];
                auto i = make_tuple(a, b, c, d);
                int cA = increase(A, a);
                int cB = increase(B, b);
                int cC = decrease(C, c);
                int cD = decrease(D, d);
                if (t == 0)
                {
                    if (s.find(i) == s.end())
                    {
                        count += cA * cB * cC * cD;
                        s.insert(i);
                    }
                }
                cout << count << endl;
                solve(k + 1, a + 1, b, c, d);
                solve(k + 1, a, b + 1, c, d);
                solve(k + 1, a, b, c - 1, d);
                solve(k + 1, a, b, c, d - 1);
            };
            solve(0, 0, 0, nC - 1, nD - 1);
            return count;
        }

        // 2. Add Two Numbers
        // Given two non-empty linked lists representing two non-negative integers. The
        // digits are stored in reverse order (LSB is the head) and each node contain a
        // single digit. Add the two numbers and return a linked list. The two numbers
        // do not contain leading zero, except the number 0 itself.
        // Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
        // Output: (7 -> 0 -> 8)
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
        static ListNode *addTwoNumbers2(ListNode *l1, ListNode *l2)
        {
            ListNode *h = nullptr;
            ListNode *t = nullptr;
            int c = 0;
            while (l1 != nullptr || l2 != nullptr || c > 0)
            {
                ListNode *n = new ListNode(c);
                if (l1 != nullptr)
                {
                    n->val += l1->val;
                    l1 = l1->next;
                }
                if (l2 != nullptr)
                {
                    n->val += l2->val;
                    l2 = l2->next;
                }
                if (n->val >= 10)
                {
                    n->val -= 10;
                    c = 1;
                }
                else
                {
                    c = 0;
                }
                if (h == nullptr)
                    h = n;
                else
                    t->next = n;
                t = n;
            }
            return h;
        }

        // 3. Longest Substring Without Repeating Characters
        // Given a string, find the length of the longest substring
        // without repeating characters.
        // Example 1:
        // Input: "abcabcbb"
        // Output: 3
        // Explanation: The answer is "abc", with the length of 3.
        // Example 2:
        // Input: "bbbbb"
        // Output: 1
        // Explanation: The answer is "b", with the length of 1.
        // Example 3:
        // Input: "pwwkew"
        // Output: 3
        // Explanation: The answer is "wke", with the length of 3.
        // Note that the answer must be a substring, "pwke" is a subsequence and not a
        // substring.
        int lengthOfLongestSubstring(const string &s)
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
        int lengthOfLongestSubstring2(const string &s)
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
        int lengthOfLongestSubstring3(const string &s)
        {
            bitset<256> m;
            int i = 0;
            int l = 0;
            int j = 0;
            for (j = 0; j < (int)s.size(); j++)
            {
                if (m.test(s[j]))
                {
                    if (j - i > l)
                        l = j - i;
                    while (s[i] != s[j])
                    {
                        m.reset(s[i]);
                        i++;
                    }
                    i++;
                }
                else
                {
                    m.set(s[j]);
                }
            }
            if (j - i > l)
                l = j - i;
            return l;
        }

        // 4. Median of Two Sorted Arrays
        // There are two sorted arrays nums1 and nums2 of size m and n respectively.
        // Find the median of the two sorted arrays. The overall run time complexity
        // should be O(log (m+n)). You may assume nums1 and nums2 cannot be both empty.
        // Example 1:
        // nums1 = [1, 3]
        // nums2 = [2]
        // The median is 2.0
        // Example 2:
        // nums1 = [1, 2]
        // nums2 = [3, 4]
        // The median is (2 + 3)/2 = 2.5
        double findMedianSortedArrays(const vector<int> &nums1,
                                      const vector<int> &nums2)
        {
            // For an array a[0..n-1]
            // If n is even, its medians are indexed at (n-1)/2 and n/2
            // If n is odd, its median is indexed at (n-1)/2 == n/2
            function<double(const vector<int> &, const vector<int> &)> search =
                [&](const vector<int> &s, const vector<int> &l) -> double
            {
                // Assume s.size() <= l.size()
                int bs = 0;
                int es = s.size() - 1;
                int n = s.size() + l.size();
                bool odd = ((n & 0x1) == 1);
                // index of the lower median is (n-1)/2 whether n is odd or even
                // index of the upper median is n/2 whether n is odd or even
                int m = (n - 1) / 2;
                if (s.empty())
                    return odd ? l[m] : (l[m] + l[m + 1]) / 2.0;
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

        // 5. Longest Palindromic Substring
        // Given a string s, find the longest palindromic substring in s.
        // You may assume that the maximum length of s is 1000.
        // Example 1:
        // Input: "babad"
        // Output: "bab"
        // Note: "aba" is also a valid answer.
        // Example 2:
        // Input: "cbbd"
        // Output: "bb"
        string longestPalindrome(const string &s)
        {
            if (s.empty())
                return string();
            function<int(int, int)> expand = [&](int i, int j) -> int
            {
                while (0 <= i && j < (int)s.size() && s[i] == s[j])
                {
                    i--;
                    j++;
                }
                // s[(i + 1) .. (j - 1)] is a palindrome
                return j - i - 1;
            };
            int m = 1;
            int b = 0;
            for (int i = 0; i < (int)s.size(); i++)
            {
                int n;
                if (i + 1 < (int)s.size())
                    n = max(expand(i, i), expand(i, i + 1));
                else
                    n = expand(i, i);
                if (n > m)
                {
                    // If n is odd, b + (n - 1) / 2 = i
                    // If n is even, b + n / 2 - 1 = i
                    b = i - ((n - 1) >> 1);
                    m = n;
                }
            }
            return s.substr(b, m);
        }
        string longestPalindrome2(const string &s)
        {
            function<pair<int, int>(int, int)>
                expand = [&](int l, int r) -> pair<int, int>
            {
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
        string longestPalindrome3(const string &s)
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
                        // (2) s[(i + 1)..(i + l - 2)] is a palindrome (of length (l -
                        // 2))
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
        string longestPalindrome4(const string &s)
        {
            if (s.empty())
                return s;
            // #b#a#b#a#d#
            auto getChar = [&](int i) -> char
            {
                if ((i & 0x1) == 0)
                    return '#';
                return s[i >> 1];
            };
            int n = (s.size() << 1) + 1;
            auto expand = [&](int c, int &l)
            {
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

        // 6. ZigZag Conversion
        // The string "PAYPALISHIRING" is written in a zigzag pattern
        // on a given number of rows like this: (you may want to display
        // this pattern in a fixed font for better legibility)
        // P   A   H   N
        // A P L S I I G
        // Y   I   R
        // And then read line by line: "PAHNAPLSIIGYIR"
        // Write the code that will take a string and make this conversion given a
        // number of rows: Example 1: Input: s = "PAYPALISHIRING", numRows = 3 Output:
        // "PAHNAPLSIIGYIR" Example 2: Input: s = "PAYPALISHIRING", numRows = 4 Output:
        // "PINALSIGYAHRPI" Explanation: P     I    N A   L S  I G Y A   H R P     I
        // Example 3:
        // Input: s = "ABCD", numRows = 3
        // Output: "ABDC"
        // A
        // B D
        // C
        string convert(const string &s, int numRows)
        {
            if (numRows <= 1)
                return s;
            ostringstream ss;
            int d = (numRows << 1) - 2;
            for (int i = 0; i < numRows; i++)
            {
                for (int j = 0; j < (int)s.size(); j += d)
                {
                    if (j + i < (int)s.size())
                        ss << s[j + i];
                    if (0 < i && i + 1 < numRows && 0 <= j + d - i &&
                        j + d - i < (int)s.size())
                        ss << s[j + d - i];
                }
            }
            return ss.str();
        }
        string convert2(const string &s, int numRows)
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
        // Given a 32-bit signed integer, reverse digits of an integer.
        // Example 1:
        // Input: 123
        // Output: 321
        // Example 2:
        // Input: -123
        // Output: -321
        // Example 3:
        // Input: 120
        // Output: 21
        // Note:
        // Assume we are dealing with an environment which could only store
        // integers within the 32-bit signed integer range: [−2^31,  2^31 − 1].
        // For the purpose of this problem, assume that your function returns 0
        // when the reversed integer overflows.
        int reverse(int x)
        {
            long long y = x;
            bool isNegative = false;
            if (y < 0)
            {
                isNegative = true;
                y = -y;
            }
            long long z = 0;
            while (y > 0)
            {
                z = z * 10 + (y % 10);
                if (isNegative && -z < INT_MIN)
                    return 0;
                else if (z > INT_MAX)
                    return 0;
                y = y / 10;
            }
            return isNegative ? -z : z;
        }
        int reverse2(int x)
        {
            int minh = -214748364; // INT_MIN / 10 = -214748364;
            int mind = -8;         // INT_MIN % 10 = -8;
            int maxh = 214748364;  // INT_MAX / 10 = 214748364;
            int maxd = 7;          // INT_MAX % 10 = 7;
            int y = 0;
            while (x != 0)
            {
                int d = x % 10; // d < 0 if x < 0
                if (y < minh || (y == minh && d < mind))
                    return 0;
                else if (y > maxh || (y == maxh && d > maxd))
                    return 0;
                y = y * 10 + d;
                x = x / 10;
            }
            return y;
        }

        // 8. String to Integer (atoi)
        // Implement atoi which converts a string to an integer.
        // The function first discards as many whitespace characters as necessary
        // until the first non-whitespace character is found. Then, starting from
        // this character, takes an optional initial plus or minus sign followed by
        // as many numerical digits as possible, and interprets them as a numerical
        // value. The string can contain additional characters after those that form the
        // integral number, which are ignored and have no effect on the behavior of this
        // function. If the first sequence of non-whitespace characters in str is not a
        // valid integral number, or if no such sequence exists because either str is
        // empty or it contains only whitespace characters, no conversion is performed.
        // If no valid conversion could be performed, a zero value is returned.
        // Note: Only the space character ' ' is considered as whitespace character.
        // Assume we are dealing with an environment which could only store integers
        // within the 32-bit signed integer range: [−2^31,  2^31 − 1]. If the numerical
        // value is out of the range of representable values, INT_MAX (2^31 − 1) or
        // INT_MIN (−2^31) is returned. Example 1: Input: "42" Output: 42 Example 2:
        // Input: "   -42"
        // Output: -42
        // Explanation: The first non-whitespace character is '-', which is the minus
        // sign. Then take as many numerical digits as possible, which gets 42. Example
        // 3: Input: "4193 with words" Output: 4193 Explanation: Conversion stops at
        // digit '3' as the next character is not a numerical digit. Example 4: Input:
        // "words and 987" Output: 0 Explanation: The first non-whitespace character is
        // 'w', which is not a numerical digit or a +/- sign. Therefore no valid
        // conversion could be performed. Example 5: Input: "-91283472332" Output:
        // -2147483648 Explanation: The number "-91283472332" is out of the range of a
        // 32-bit signed integer. Thefore INT_MIN (−2^31) is returned.
        int myAtoi(const string &str)
        {
            bool foundStart = false;
            bool isNegative = false;
            int r = 0;
            for (size_t i = 0; i < str.size(); i++)
            {
                if (str[i] == ' ')
                {
                    if (foundStart)
                        break;
                }
                else if (str[i] == '+')
                {
                    if (foundStart)
                        break;
                    foundStart = true;
                }
                else if (str[i] == '-')
                {
                    if (foundStart)
                        break;
                    foundStart = true;
                    isNegative = true;
                }
                else if (str[i] < '0' || str[i] > '9')
                {
                    if (foundStart)
                        break;
                    return 0;
                }
                else
                {
                    if (!foundStart)
                        foundStart = true;
                    if (isNegative &&
                        (r < -214748364 || (r == -214748364 && str[i] > '8')))
                    {
                        return INT_MIN;
                    }
                    if (!isNegative &&
                        (r > 214748364 || (r == 214748364 && str[i] > '7')))
                    {
                        return INT_MAX;
                    }
                    r = r * 10 + (isNegative ? ('0' - str[i]) : (str[i] - '0'));
                }
            }
            return r;
        }
        int myAtoi2(const string &str)
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
        int myAtoi3(const string &str)
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

        // 9. Palindrome Number
        // Determine whether an integer is a palindrome. An integer is a palindrome
        // when it reads the same backward as forward.
        // Example 1:
        // Input: 121
        // Output: true
        // Example 2:
        // Input: -121
        // Output: false
        // Explanation: From left to right, it reads -121. From right to left,
        // it becomes 121-. Therefore it is not a palindrome.
        // Example 3:
        // Input: 10
        // Output: false
        // Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
        // Follow up:
        // Coud you solve it without converting the integer to a string?
        bool isPalindrome(int x)
        {
            if (x < 0)
                return false;
            int d = 1;
            // d is int, so 10 * d will overflow if d is too large,
            // e.g. when x = 1000000001
            // while (10 * d <= x)
            //     d *= 10;
            int y = x;
            while (y >= 10)
            {
                d *= 10;
                y /= 10;
            }
            while (x > 0)
            {
                int l = x % 10;
                int h = x / d;
                if (h != l)
                    return false;
                x = (x % d) / 10;
                d /= 100;
            }
            return true;
        }
        bool isPalindrome2(int x)
        {
            if (x < 0)
                return false;
            long long y = x;
            long long d = 1; // use long long to avoid overflow
            while (y >= 10 * d)
                d *= 10;
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
        bool isPalindrome3(unsigned int number)
        {
            if (number < 10)
                return true;
            unsigned int base = 1;
            while ((number / base) >= 10)
                base *= 10;
            // Compare the most significant digit (MSD) and
            // the least significant digit (LSD)
            while (number >= 10)
            {
                if ((number / base) != (number % 10))
                {
                    // MSD is different from LSD
                    return false;
                }
                // Peel off MSD and LSD
                number = (number % base) / 10;
                base /= 100;
            }
            return true;
        }

        // 11. Container With Most Water
        // Given n non-negative integers a1, a2, ..., an , where each represents a point
        // at coordinate (i, ai). n vertical lines are drawn such that the two endpoints
        // of line i is at (i, ai) and (i, 0). Find two lines, which together with
        // x-axis forms a container, such that the container contains the most water.
        // Note: You may not slant the container and n is at least 2.
        // Example:
        // Input: [1,8,6,2,5,4,8,3,7]
        // Output: 49 (between a[1] and a[8]), note that a[6] does not divide the container
        // formed by a[1] and a[8].
        int maxArea(const vector<int> &height)
        {
            size_t i = 0;
            size_t j = height.size() - 1;
            int m = 0;
            while (i < j)
            {
                int a = 0;
                if (height[i] <= height[j])
                {
                    // Increasing i is the only way we may find a larger container.
                    // Cannot decrease j, because container [h[i], h[j-1]] is guaranteed
                    // to be smaller.
                    a = height[i] * (j - i);
                    i++;
                }
                else
                {
                    a = height[j] * (j - i);
                    j--;
                }
                m = std::max(m, a);
            }
            return m;
        }
        int maxArea2(const vector<int> &height)
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
        int maxArea3(const vector<int> &height)
        {
            int m = 0;
            for (int i = 0; i < (int)height.size() - 1; i++)
            {
                for (int j = i + 1; j < (int)height.size(); j++)
                {
                    m = std::max(m, (j - i) * std::min(height[i], height[j]));
                }
            }
            return m;
        }

        // 12. Integer to Roman
        // Roman numerals are represented by seven different symbols: I, V, X, L, C, D
        // and M. (Symbol,Value) = (I,1), (V,5), (X,10), (L,50), (C,100), (D,500),
        // (M,1000). For example, two is written as II in Roman numeral, just two one's
        // added together. Twelve is written as, XII, which is simply X + II. The number
        // twenty seven is written as XXVII, which is XX + V + II. Roman numerals are
        // usually written largest to smallest from left to right. However, the numeral
        // for four is not IIII. Instead, the number four is written as IV. Because the
        // one is before the five we subtract it making four. The same principle applies
        // to the number nine, which is written as IX. There are six instances where
        // subtraction is used:
        //     I can be placed before V (5) and X (10) to make 4 and 9.
        //     X can be placed before L (50) and C (100) to make 40 and 90.
        //     C can be placed before D (500) and M (1000) to make 400 and 900.
        // Given an integer, convert it to a roman numeral. Input is guaranteed to be
        // within the range from 1 to 3999. Example 1: Input: 3 Output: "III" Example 2:
        // Input: 4
        // Output: "IV"
        // Example 3:
        // Input: 9
        // Output: "IX"
        // Example 4:
        // Input: 58
        // Output: "LVIII"
        // Explanation: L = 50, V = 5, III = 3.
        // Example 5:
        // Input: 1994
        // Output: "MCMXCIV"
        // Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
        string intToRoman(int num)
        {
            string r;
            if (num >= 1000)
            {
                r.append(num / 1000, 'M');
                num %= 1000;
            }
            if (num >= 900)
            {
                r.append("CM");
                num -= 900;
            }
            if (num >= 500)
            {
                r.append(1, 'D');
                num -= 500;
            }
            if (num >= 400)
            {
                r.append("CD");
                num -= 400;
            }
            if (num >= 100)
            {
                r.append(num / 100, 'C');
                num %= 100;
            }
            if (num >= 90)
            {
                r.append("XC");
                num -= 90;
            }
            if (num >= 50)
            {
                r.append(1, 'L');
                num -= 50;
            }
            if (num >= 40)
            {
                r.append("XL");
                num -= 40;
            }
            if (num >= 10)
            {
                r.append(num / 10, 'X');
                num %= 10;
            }
            if (num == 9)
            {
                r.append("IX");
                num -= 9;
            }
            if (num >= 5)
            {
                r.append(1, 'V');
                num -= 5;
            }
            if (num == 4)
            {
                r.append("IV");
                num -= 4;
            }
            if (num >= 1)
            {
                r.append(num, 'I');
            }
            return r;
        }
        string intToRoman2(int num)
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

        // 13. Roman to Integer
        // Roman numerals are represented by seven different symbols: I, V, X, L, C, D
        // and M. (Symbol,Value) = (I,1), (V,5), (X,10), (L,50), (C,100), (D,500), For
        // example, two is written as II in Roman numeral, just two one's added
        // together. Twelve is written as, XII, which is simply X + II. The number
        // twenty seven is written as XXVII, which is XX + V + II. Roman numerals are
        // usually written largest to smallest from left to right. However, the numeral
        // for four is not IIII. Instead, the number four is written as IV. Because the
        // one is before the five we subtract it making four. The same principle applies
        // to the number nine, which is written as IX. There are six instances where
        // subtraction is used:
        //     I can be placed before V (5) and X (10) to make 4 and 9.
        //     X can be placed before L (50) and C (100) to make 40 and 90.
        //     C can be placed before D (500) and M (1000) to make 400 and 900.
        // Given a roman numeral, convert it to an integer. Input is guaranteed to be
        // within the range from 1 to 3999. Example 1: Input: "III" Output: 3 Example 2:
        // Input: "IV"
        // Output: 4
        // Example 3:
        // Input: "IX"
        // Output: 9
        // Example 4:
        // Input: "LVIII"
        // Output: 58
        // Explanation: L = 50, V= 5, III = 3.
        // Example 5:
        // Input: "MCMXCIV"
        // Output: 1994
        // Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
        int romanToInt(const string &s)
        {
            int r = 0;
            size_t i = 0;
            while (i < s.size())
            {
                switch (s[i])
                {
                case 'I':
                    if (i + 1 < s.size() && s[i + 1] == 'V')
                    {
                        r += 4;
                        i += 2;
                    }
                    else if (i + 1 < s.size() && s[i + 1] == 'X')
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
                case 'V':
                    r += 5;
                    i++;
                    break;
                case 'X':
                    if (i + 1 < s.size() && s[i + 1] == 'L')
                    {
                        r += 40;
                        i += 2;
                    }
                    else if (i + 1 < s.size() && s[i + 1] == 'C')
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
                case 'L':
                    r += 50;
                    i++;
                    break;
                case 'C':
                    if (i + 1 < s.size() && s[i + 1] == 'D')
                    {
                        r += 400;
                        i += 2;
                    }
                    else if (i + 1 < s.size() && s[i + 1] == 'M')
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
                case 'D':
                    r += 500;
                    i++;
                    break;
                case 'M':
                    r += 1000;
                    i++;
                    break;
                default:
                    throw invalid_argument(s);
                }
            }
            return r;
        }

        // 14. Longest Common Prefix
        // Write a function to find the longest common prefix string amongst an array of
        // strings. If there is no common prefix, return an empty string "". Example 1:
        // Input: ["flower","flow","flight"]
        // Output: "fl"
        // Example 2:
        // Input: ["dog","racecar","car"]
        // Output: ""
        // Explanation: There is no common prefix among the input strings.
        // Note: All given inputs are in lowercase letters a-z.
        string longestCommonPrefix(const vector<string> &strs)
        {
            if (strs.empty())
                return "";
            if (strs.size() == 1)
                return strs[0];
            size_t i = 0;
            while (i < strs[0].size())
            {
                for (size_t j = 1; j < strs.size(); j++)
                {
                    if (i == strs[j].size() || strs[0][i] != strs[j][i])
                        return strs[0].substr(0, i);
                }
                i++;
            }
            return strs[0];
        }
        string longestCommonPrefix2(const vector<string> &strs)
        {
            if (strs.empty())
                return "";
            if (strs.size() == 1)
                return strs[0];
            function<size_t(size_t, size_t)> prefix = [&](size_t l,
                                                          size_t i) -> size_t
            {
                size_t j = 0;
                while (j < l && j < strs[i].size() && strs[0][j] == strs[i][j])
                    j++;
                return j;
            };
            size_t k = strs[0].size();
            for (size_t i = 1; i < strs.size(); i++)
            {
                k = prefix(k, i);
                if (k == 0)
                    break;
            }
            return strs[0].substr(0, k);
        }
        string longestCommonPrefix3(const vector<string> &strs)
        {
            if (strs.empty())
                return "";
            int l = strs[0].size();
            for (int i = 1; i < (int)strs.size() && l > 0; i++)
            {
                int j = 0;
                for (j = 0; j < l && j < (int)strs[i].size(); j++)
                {
                    if (strs[0][j] != strs[i][j])
                        break;
                }
                l = min(l, j);
            }
            return l > 0 ? strs[0].substr(0, l) : "";
        }

        // 17. Letter Combinations of a Phone Number
        // Given a string containing digits from 2-9 inclusive, return all possible
        // letter combinations that the number could represent. A mapping of digit to
        // letters (just like on the telephone buttons) is given below. Note that 1 does
        // not map to any letters. Example: Input: "23" Output: ["ad", "ae", "af", "bd",
        // "be", "bf", "cd", "ce", "cf"]. Note: Although the above answer is in
        // lexicographical order, your answer could be in any order you want.
        vector<string> letterCombinations(const string &digits)
        {
            vector<string> result;
            if (digits.empty())
                return result;
            map<char, vector<char>> m = {
                {'2', {'a', 'b', 'c'}},
                {'3', {'d', 'e', 'f'}},
                {'4', {'g', 'h', 'i'}},
                {'5', {'j', 'k', 'l'}},
                {'6', {'m', 'n', 'o'}},
                {'7', {'p', 'q', 'r', 's'}},
                {'8', {'t', 'u', 'v'}},
                {'9', {'w', 'x', 'y', 'z'}}};
            queue<string> q;
            for (char c : m[digits[0]])
                q.push(string(1, c));
            while (!q.empty())
            {
                string s = q.front();
                q.pop();
                if (s.size() == digits.size())
                    result.push_back(s);
                else // if (s.size() < digits.size())
                {
                    string t(s);
                    t.resize(s.size() + 1);
                    for (char c : m[digits[s.size()]])
                    {
                        t[s.size()] = c;
                        q.push(t);
                    }
                }
            }
            return result;
        }
        vector<string> letterCombinations2(const string &digits)
        {
            map<char, vector<char>> m = {
                {'2', {'a', 'b', 'c'}},
                {'3', {'d', 'e', 'f'}},
                {'4', {'g', 'h', 'i'}},
                {'5', {'j', 'k', 'l'}},
                {'6', {'m', 'n', 'o'}},
                {'7', {'p', 'q', 'r', 's'}},
                {'8', {'t', 'u', 'v'}},
                {'9', {'w', 'x', 'y', 'z'}}};
            vector<string> result;
            function<void(const string &, size_t)> combine = [&](const string &s,
                                                                 size_t i)
            {
                if (i == digits.size())
                {
                    if (!s.empty())
                        result.push_back(s);
                    return;
                }
                if (m.find(digits[i]) == m.end())
                {
                    combine(s, i + 1);
                    return;
                }
                for (size_t j = 0; j < m[digits[i]].size(); j++)
                {
                    string s1(s);
                    s1.append(1, m[digits[i]][j]);
                    combine(s1, i + 1);
                }
            };
            combine("", 0);
            return result;
        }
        vector<string> letterCombinations3(const string &digits)
        {
            vector<string> result;
            if (digits.empty())
                return result;
            map<char, vector<char>> m = {
                {'2', {'a', 'b', 'c'}},
                {'3', {'d', 'e', 'f'}},
                {'4', {'g', 'h', 'i'}},
                {'5', {'j', 'k', 'l'}},
                {'6', {'m', 'n', 'o'}},
                {'7', {'p', 'q', 'r', 's'}},
                {'8', {'t', 'u', 'v'}},
                {'9', {'w', 'x', 'y', 'z'}}};
            vector<pair<char, size_t>> c;
            for (size_t i = 0; i < digits.size(); i++)
            {
                pair<char, size_t> p = make_pair(digits[i], 0);
                c.push_back(p);
            }
            bool allZeros;
            do
            {
                string s;
                for (vector<pair<char, size_t>>::iterator it = c.begin();
                     it != c.end();
                     it++)
                    s.append(1, m[it->first][it->second]);
                result.push_back(s);
                allZeros = true;
                bool carry = true;
                for (vector<pair<char, size_t>>::reverse_iterator it = c.rbegin();
                     it != c.rend();
                     it++)
                {
                    if (carry)
                    {
                        it->second++;
                        if (it->second >= m[it->first].size())
                            it->second = 0;
                        else
                            carry = false;
                    }
                    if (it->second > 0)
                        allZeros = false;
                }
            } while (!allZeros);
            return result;
        }
        vector<string> letterCombinations4(const string &digits)
        {
            if (digits.length() == 0)
                return vector<string>{};
            function<void(const string &, int, const string &,
                          map<char, vector<char>> &, vector<string> &)>
                combine = [&](const string &s, int i, const string &r,
                              map<char, vector<char>> &m, vector<string> &o)
            {
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
                for_each(m[s[i]].begin(), m[s[i]].end(), [&](char c)
                         {
                             string t(r);
                             t.append(1, c);
                             combine(s, i + 1, t, m, o); });
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

        // 19. Remove Nth Node From End of List
        // Given a linked list, remove the n-th node from the end of list and return its
        // head. Example: Given linked list: 1->2->3->4->5, and n = 2. After removing
        // the second node from the end, the linked list becomes 1->2->3->5. Note: Given
        // n will always be valid. Follow up: Could you do this in one pass?
        ListNode *removeNthFromEnd(ListNode *head, int n)
        {
            ListNode *q = head;
            int i;
            for (i = 0; i < n && q != nullptr; i++)
                q = q->next;
            // q is at index i
            if (i < n)
                return head; // q == nullptr. List[0..(i-1)] contain less than n nodes.
            if (q == nullptr)
            {
                // List[n] == nullptr. List[0..(n-1)] contains n nodes.
                q = head;
                head = head->next;
                delete q;
                return head;
            }
            // List[0..n] contain (1 + n) nodes
            ListNode *p = head;
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
        ListNode *removeNthFromEnd2(ListNode *head, int n)
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
            // i = n
            // q is the (i+1)-th, i.e. (n+1)-th, node
            // p is the 1-st node
            while (q->next != nullptr)
            {
                p = p->next;
                q = q->next;
            }
            // q is the 1-st node from the end, i.e. the last node
            // p is the (n+1)-th node from the end
            q = p->next;
            p->next = q->next;
            delete q;
            return head;
        }

        // 20. Valid Parentheses
        // Given a string containing just the characters '(', ')', '{', '}', '[' and
        // ']', determine if the input string is valid. An input string is valid if:
        // Open brackets must be closed by the same type of brackets.
        // Open brackets must be closed in the correct order.
        // Note that an empty string is also considered valid.
        // Example 1: Input: "()" Output: true
        // Example 2: Input: "()[]{}" Output: true
        // Example 3: Input: "(]" Output: false
        // Example 4: Input: "([)]" Output: false
        // Example 5: Input: "{[]}" Output: true
        bool isValid(const string &s)
        {
            stack<char> a;
            for (size_t i = 0; i < s.size(); i++)
            {
                switch (s[i])
                {
                case '(':
                case '{':
                case '[':
                    a.push(s[i]);
                    break;
                case ')':
                    if (a.empty() || a.top() != '(')
                        return false;
                    a.pop();
                    break;
                case '}':
                    if (a.empty() || a.top() != '{')
                        return false;
                    a.pop();
                    break;
                case ']':
                    if (a.empty() || a.top() != '[')
                        return false;
                    a.pop();
                    break;
                default:
                    return false;
                }
            }
            return a.empty();
        }

        // 21. Merge Two Sorted Lists
        // Merge two sorted linked lists and return it as a new list.
        // The new list should be made by splicing together the nodes
        // of the first two lists. Example:
        // Input: 1->2->4, 1->3->4
        // Output: 1->1->2->3->4->4
        ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
        {
            if (l1 == nullptr)
                return l2;
            if (l2 == nullptr)
                return l1;
            ListNode *l = nullptr;
            if (l1->val < l2->val)
            {
                l = l1;
                l1 = l1->next;
            }
            else
            {
                l = l2;
                l2 = l2->next;
            }
            ListNode *n = l;
            while (l1 != nullptr && l2 != nullptr)
            {
                if (l1->val < l2->val)
                {
                    n->next = l1;
                    n = n->next;
                    l1 = l1->next;
                }
                else
                {
                    n->next = l2;
                    n = n->next;
                    l2 = l2->next;
                }
            }
            if (l1 == nullptr)
                n->next = l2;
            else
                n->next = l1;
            return l;
        }
        ListNode *mergeTwoLists2(ListNode *l1, ListNode *l2)
        {
            ListNode *h = nullptr;
            ListNode *t = nullptr;
            while (l1 != nullptr && l2 != nullptr)
            {
                if (l1->val <= l2->val)
                {
                    if (t != nullptr)
                        t->next = l1;
                    t = l1;
                    l1 = l1->next;
                }
                else
                {
                    if (t != nullptr)
                        t->next = l2;
                    t = l2;
                    l2 = l2->next;
                }
                t->next = nullptr;
                if (h == nullptr)
                    h = t;
            }
            if (l1 != nullptr)
            {
                if (h == nullptr)
                    h = l1;
                else
                    t->next = l1;
            }
            else if (l2 != nullptr)
            {
                if (h == nullptr)
                    h = l2;
                else
                    t->next = l2;
            }
            return h;
        }
        ListNode *mergeTwoLists3(ListNode *l1, ListNode *l2)
        {
            function<ListNode *(ListNode *, ListNode *)> merge = [&](ListNode *n1, ListNode *n2) -> ListNode *
            {
                if (n1 == nullptr)
                    return n2;
                if (n2 == nullptr)
                    return n1;
                if (n1->val < n2->val)
                {
                    n1->next = merge(n1->next, n2);
                    return n1;
                }
                else
                {
                    n2->next = merge(n1, n2->next);
                    return n2;
                }
            };
            return merge(l1, l2);
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

        // 22. Generate Parentheses
        // Given n pairs of parentheses, write a function to generate all combinations
        // of well-formed parentheses. For example, given n = 3, a solution set is:
        // [
        //   "((()))",
        //   "(()())",
        //   "(())()",
        //   "()(())",
        //   "()()()"
        // ]
        // Let [l,r] represent a string of l '('s and r ')'s, then
        // ''[0,0] -> '('[1,0] -> '(('[2,0] -> '((('[3,0] -> '(((('[4,0]
        //                                                -> '((()'[3,1]
        //                                  -> '(()'[2,1] -> '(()('[3,1]
        //                                                -> '(())'[2,2]
        //                     -> '()'[1,1] -> '()('[2,1] -> '()(('[3,1]
        //                                                -> '()()'[2,2]
        vector<string> generateParenthesis(int n)
        {
            vector<string> result;
            function<void(int, int, const string &)> gen = [&](int l, int r,
                                                               const string &s)
            {
                if (l == n && r == n)
                {
                    result.push_back(s);
                    return;
                }
                if (l < n)
                {
                    string s1(s);
                    s1.append(1, '(');
                    gen(l + 1, r, s1);
                }
                if (r < n && l > r)
                {
                    string s2(s);
                    s2.append(1, ')');
                    gen(l, r + 1, s2);
                }
            };
            gen(0, 0, "");
            return result;
        }
        vector<string> generateParenthesis2(int n)
        {
            vector<string> result;
            queue<tuple<string, int, int>> q;
            q.push(make_tuple("", 0, 0));
            while (!q.empty())
            {
                auto t = q.front();
                q.pop();
                string s = get<0>(t);
                int l = get<1>(t);
                int r = get<2>(t);
                if (l == n && r == n)
                    result.push_back(s);
                if (l < n)
                    q.push(make_tuple(string(s).append(1, '('), l + 1, r));
                if (r < n && l > r)
                    q.push(make_tuple(string(s).append(1, ')'), l, r + 1));
            }
            return result;
        }
        vector<string> generateParenthesis3(int n)
        {
            if (n <= 0)
                return vector<string>{};
            function<void(int, int, map<pair<int, int>, vector<string>> &)>
                solve = [&](       // l <= r
                            int l, // count '(' needed, l >= 1
                            int r, // count ')' needed, r >= l >= 1
                            map<pair<int, int>, vector<string>> &m)
            {
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
                        for_each(m[q].begin(), m[q].end(), [&](string &u)
                                 {
                                     string v(t);
                                     v.append(u);
                                     m[p].push_back(v); });
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
        vector<string> generateParenthesis4(int n)
        {
            if (n <= 0)
                return vector<string>{};
            if (n == 1)
                return vector<string>{"()"};
            function<void(string, int, int, int, vector<string> &)>
                solve = [&](string s,
                            int l, // count '(' in s
                            int r, // count ')' in s
                            int n, vector<string> &o)
            {
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
        // Given X = (()), it generates (())(), ()(()), ((()))
        // but misses (()())
        vector<string> generateParenthesis5(int n)
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
                    // Given s = X containing i - 1 pairs of ()
                    // extend it with one more pair
                    string s = result.front();
                    result.erase(result.begin());
                    string o = s;
                    o.append("()");
                    result.push_back(o); // X()
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
                        result.push_back(o); // ()X
                    }
                    o = "(";
                    o.append(s);
                    o.append(")");
                    result.push_back(o); // (X)
                }
            }
            return result;
        }

        // 24. Swap Nodes in Pairs
        // Given a linked list, swap every two adjacent nodes and return its head.
        // You may not modify the values in the list's nodes, only nodes itself may
        // be changed. Example:
        // Given 1->2->3->4, you should return the list as 2->1->4->3.
        ListNode *swapPairs(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return head;
            // swap first two nodes
            ListNode *p = head;
            head = p->next;
            p->next = head->next;
            head->next = p;
            // Swap the two nodes after p
            // i.e. p->next->next
            while (p->next != nullptr && p->next->next != nullptr)
            {
                ListNode *q = p->next->next;
                p->next->next = q->next;
                q->next = p->next;
                p->next = q;
                p = p->next->next;
            }
            return head;
        }
        ListNode *swapPairs2(ListNode *head)
        {
            function<ListNode *(ListNode *)> solve = [&](ListNode *node) -> ListNode *
            {
                if (node == nullptr || node->next == nullptr)
                    return node;
                ListNode *next = node->next;
                node->next = solve(next->next);
                next->next = node;
                return next;
            };
            return solve(head);
        }

        // 25. Reverse Nodes in k-Group
        // Given a linked list, reverse the nodes of a linked list k at a time
        // and return its modified list. k is a positive integer and is less than
        // or equal to the length of the linked list. If the number of nodes is
        // not a multiple of k then left-out nodes in the end should remain as it is.
        // Example:
        // Given this linked list: 1->2->3->4->5
        // For k = 2, you should return: 2->1->4->3->5
        // For k = 3, you should return: 3->2->1->4->5
        // Note: Only constant extra memory is allowed.
        // You may not alter the values in the list's nodes, only nodes itself may be changed.
        ListNode *reverseKGroup(ListNode *head, int k)
        {
            if (head == nullptr || k <= 1)
                return head;
            ListNode *h = nullptr; // h->next is the beginning of a k segament
            ListNode *t = head;    // t is the next of the ending of a k segament
            while (t != nullptr)
            {
                int i = 0;
                while (i < k && t != nullptr)
                {
                    i++;
                    t = t->next;
                }
                if (i < k)
                    break; // i-th node is nullptr, less than k nodes in total
                ListNode *p = (h == nullptr ? head : h->next);
                // Move p->next to be after h until p->next hits t
                while (p->next != t)
                {
                    ListNode *q = p->next;
                    p->next = q->next;
                    if (h == nullptr)
                    {
                        q->next = head;
                        head = q;
                    }
                    else
                    {
                        q->next = h->next;
                        h->next = q;
                    }
                }
                h = p;
            }
            return head;
        }
        ListNode *reverseKGroup2(ListNode *head, int k)
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
                // Reverse every node between begin and end
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
                // Now begin->next starts the next segament
                prev = begin;
                begin = begin->next;
            }
            return head;
        }
        ListNode *reverseKGroup3(ListNode *head, int k)
        {
            function<ListNode *(ListNode *)> reverse =
                [&](ListNode *h) -> ListNode *
            {
                int i = 0;
                ListNode *t = h;
                while (i < k - 1 && t != nullptr)
                {
                    i++;
                    t = t->next;
                }
                if (t == nullptr)
                    return h;
                ListNode *h2 = reverse(t->next);
                while (h != t)
                {
                    ListNode *p = h->next;
                    h->next = h2;
                    h2 = h;
                    h = p;
                }
                h->next = h2;
                return h;
            };
            return reverse(head);
        }

        // 26. Remove Duplicates from Sorted Array
        // Given a sorted array nums, remove the duplicates in-place such that each
        // element appear only once and return the new length. Do not allocate extra
        // space for another array, you must do this by modifying the input array
        // in-place with O(1) extra memory.
        // Example 1:
        // Given nums = [1,1,2], Your function should return length = 2, with the first
        // two elements of nums being 1 and 2 respectively.
        // It doesn't matter what you leave beyond the returned length.
        // Example 2:
        // Given nums = [0,0,1,1,1,2,2,3,3,4], Your function should return length = 5,
        // with the first five elements of nums being modified to 0, 1, 2, 3, and 4
        // respectively. It doesn't matter what values are set beyond the returned
        // length.
        int removeDuplicates(vector<int> &nums)
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
        int removeDuplicates2(vector<int> &nums)
        {
            int i = nums.empty() ? -1 : 0;
            for (int j = 1; j < (int)nums.size(); j++)
            {
                if (nums[j] != nums[j - 1])
                {
                    i++;
                    if (i < j)
                        nums[i] = nums[j];
                }
            }
            return i + 1;
        }

        // 27. Remove Element
        // Given an array nums and a value val, remove all instances of that value
        // in-place and return the new length. Do not allocate extra space for another
        // array, you must do this by modifying the input array in-place with O(1)
        // extra memory. The order of elements can be changed. It doesn't matter what
        // you leave beyond the new length.
        // Example 1:
        // Given nums = [3,2,2,3], val = 3, Your function should return length = 2,
        // with the first two elements of nums being 2.
        // It doesn't matter what you leave beyond the returned length.
        // Example 2:
        // Given nums = [0,1,2,2,3,0,4,2], val = 2, Your function should return length =
        // 5, with the first five elements of nums containing 0, 1, 3, 0, and 4. Note
        // that the order of those five elements can be arbitrary. It doesn't matter
        // what values are set beyond the returned length.
        int removeElement(vector<int> &nums, int val)
        {
            int i = -1;
            for (int j = 0; j < (int)nums.size(); j++)
            {
                if (nums[j] != val)
                {
                    if (i + 1 != j)
                        nums[i + 1] = nums[j];
                    i++;
                }
            }
            return i + 1;
        }
        int removeElement2(vector<int> &nums, int val)
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
        // Remove by swaping to end, not stable
        int removeElement3(vector<int> &nums, int val)
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

        // 28. Implement strStr()
        // Return the index of the first occurrence of needle in haystack, or -1 if
        // needle is not part of haystack.
        // Example 1:
        // Input: haystack = "hello", needle = "ll", Output: 2
        // Example 2:
        // Input: haystack = "aaaaa", needle = "bba", Output: -1
        // Clarification:
        // What should we return when needle is an empty string? This is a great
        // question to ask during an interview. For the purpose of this problem, we will
        // return 0 when needle is an empty string. This is consistent to C's strstr()
        // and Java's indexOf().
        int strStr(string haystack, string needle)
        {
            if (needle.empty())
                return 0;
            if (haystack.size() < needle.size())
                return -1;
            size_t i = 0;
            while (i <= haystack.size() - needle.size())
            {
                if (haystack[i] == needle[0])
                {
                    size_t j = i;
                    size_t k = 0;
                    while (j < haystack.size() && k < needle.size() &&
                           haystack[j] == needle[k])
                    {
                        j++;
                        k++;
                    }
                    if (k == needle.size())
                        return i;
                }
                i++;
            }
            return -1;
        }
        int strStr2(string haystack, string needle)
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
        const char *strStr3(const char *haystack, const char *needle)
        {
            if (*needle == '\0')
                return haystack;
            if (*haystack == '\0')
                return nullptr;
            int lh = 0;
            const char *h = haystack;
            while (*h != '\0')
            {
                lh++;
                h++;
            }
            int ln = 0;
            const char *n = needle;
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
        const char *strStr4(const char *input1, const char *input2)
        {
            if (input1 == nullptr || input2 == nullptr)
                return nullptr;
            if (*input2 == '\0')
                return input1;
            const char *q = input1;
            const char *p = input2;
            while (*(q + 1) != '\0' && *(p + 1) != '\0')
            {
                q++;
                p++;
            }
            if (*(q + 1) == '\0' && *(p + 1) != '\0')
            {
                return nullptr; // input2 is longer than input1
            }
            // now input1 is not shorter than input2
            // set p to the beginning of input1
            p = input1;
            // Hop p and q at same step until q reaches the end of input1
            while (*q != '\0')
            {
                if (*p == *input2)
                {
                    const char *r = p;
                    const char *s = input2;
                    while (*s != '\0' && *r == *s)
                    {
                        r++;
                        s++;
                    }
                    if (*s == '\0')
                        return p;
                }
                p++;
                q++;
            }
            return nullptr;
        }
        // Return a pointer to the first occurrence of input2 in input1, or nullptr
        const char *strStr5(const char *input1, const char *input2)
        {
            if (input1 == nullptr || input2 == nullptr)
                return nullptr;
            const char *p = input1;
            while (*p != '\0')
            {
                if (*p == *input2)
                {
                    const char *r = p;
                    const char *s = input2;
                    while (*r != '\0' && *s != '\0' && *r == *s)
                    {
                        r++;
                        s++;
                    }
                    if (*s == '\0')
                        return p;
                }
                p++;
            }
            return *input2 == '\0' ? input1 : nullptr;
        }

        // 29. Divide Two Integers
        // Given two integers dividend and divisor, divide two integers without using
        // multiplication, division and mod operator. Return the quotient after dividing
        // dividend by divisor. The integer division should truncate toward zero.
        // Example 1:
        // Input: dividend = 10, divisor = 3
        // Output: 3
        // Example 2:
        // Input: dividend = 7, divisor = -3
        // Output: -2
        // Note: Both dividend and divisor will be 32-bit signed integers. The divisor
        // will never be 0. Assume we are dealing with an environment which could only
        // store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1].
        // For the purpose of this problem, assume that your function returns 2^31 − 1
        // when the division result overflows.
        int divide(int dividend, int divisor)
        {
            if (divisor == 1)
                return dividend;
            if (divisor == -1)
                return dividend == INT_MIN ? INT_MAX : -dividend;
            if (divisor == INT_MIN)
                return dividend == INT_MIN ? 1 : 0;
            bool negative = false;
            if (divisor < 0)
            {
                if (dividend < 0)
                {
                    if (divisor < dividend)
                        return 0;
                    dividend -= divisor; // Minus one to ensure dividend != INT_MIN
                    dividend = -dividend;
                }
                else
                {
                    if (dividend < -divisor)
                        return 0;
                    dividend += divisor; // Minus one to be consistent with the negative case
                    negative = true;
                }
                divisor = -divisor;
            }
            else
            {
                if (dividend < 0)
                {
                    if (-divisor < dividend)
                        return 0;
                    dividend += divisor; // Minus one to ensure dividend != INT_MIN
                    negative = true;
                    dividend = -dividend;
                }
                else
                {
                    if (dividend < divisor)
                        return 0;
                    dividend -= divisor; // Minus one to be consistent with the negative case
                }
            }
            int q = 1; // already subtract one divisor from dividend
            int n = 1;
            int d = divisor;
            while (dividend >= divisor)
            {
                if (dividend - d < 0)
                {
                    d = d >> 1;
                    n = n >> 1;
                }
                else if (dividend - d >= d)
                {
                    d = d << 1;
                    n = n << 1;
                }
                else
                {
                    dividend -= d;
                    q += n;
                }
            }
            return negative ? -q : q;
        }
        int divide2(int dividend, int divisor)
        {
            if (divisor == 1)
                return dividend;
            if (divisor == -1)
                return dividend == INT_MIN ? INT_MAX : -dividend;
            if (divisor == INT_MIN)
                return dividend == INT_MIN ? 1 : 0;
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
        int divide3(int dividend, int divisor)
        {
            if (divisor == 1)
                return dividend;
            if (divisor == -1)
                return dividend == INT_MIN ? INT_MAX : -dividend;
            if (divisor == INT_MIN)
                return dividend == INT_MIN ? 1 : 0;
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
        int divide4(int dividend, int divisor)
        {
            if (divisor == 1)
                return dividend;
            if (divisor == -1)
                return dividend == INT_MIN ? INT_MAX : -dividend;
            if (divisor == INT_MIN)
                return dividend == INT_MIN ? 1 : 0;
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
        int divide5(int dividend, int divisor)
        {
            bool negative = false;
            if (dividend < 0)
            {
                if (divisor > 0)
                {
                    negative = true;
                    divisor = -divisor;
                }
                else
                {
                    if (dividend == INT_MIN && divisor == -1)
                        return INT_MAX;
                }
            }
            else
            {
                if (divisor < 0)
                {
                    negative = true;
                    divisor = -divisor;
                }
            }
            int q = 0;
            int n = 1;
            int d = divisor;
            if (dividend < 0)
            {
                while (dividend <= divisor)
                {
                    if (dividend - d > 0)
                    {
                        d = d >> 1;
                        n = n >> 1;
                    }
                    else if (dividend - d <= d)
                    {
                        d = d << 1; // runtime error: left shift of negative value -1
                                    // when dividing -1 by 1
                        n = n << 1;
                    }
                    else
                    {
                        dividend += d; // BUG, shoud be subtraction
                        q += n;
                    }
                }
            }
            else
            {
                while (dividend >= divisor)
                {
                    if (dividend - d < 0)
                    {
                        d = d >> 1;
                        n = n >> 1;
                    }
                    else if (dividend - d >= d)
                    {
                        d = d << 1;
                        n = n << 1;
                    }
                    else
                    {
                        dividend -= d;
                        q += n;
                    }
                }
            }
            return negative ? -q : q;
        }
        int divide6(int dividend, int divisor)
        {
            bool negative = false;
            if (dividend < 0)
            {
                if (divisor > 0)
                {
                    if (dividend == INT_MIN && divisor == 1)
                        return INT_MIN;
                    negative = true;
                    divisor = -divisor;
                }
                else
                {
                    if (dividend == INT_MIN && divisor == -1)
                        return INT_MAX;
                }
            }
            else
            {
                if (divisor < 0)
                {
                    negative = true;
                    divisor = -divisor;
                }
            }
            int q = 0;
            int n = 1;
            int d = divisor;
            if (dividend < 0)
            {
                while (dividend <= divisor)
                {
                    if (dividend - d > 0)
                    {
                        d = (d & (0x7FFFFFFF) >> 1) & 0x80000000;
                        n = n >> 1;
                    }
                    else if (dividend - d <= d)
                    {
                        d = d + d;
                        n = n << 1; // runtime error: left shift of negative value
                                    // -2147483648 when divided by -3
                    }
                    else
                    {
                        dividend -= d;
                        q += n;
                    }
                }
            }
            else
            {
                while (dividend >= divisor)
                {
                    if (dividend - d < 0)
                    {
                        d = d >> 1;
                        n = n >> 1;
                    }
                    else if (dividend - d >= d)
                    {
                        d = d << 1;
                        n = n << 1;
                    }
                    else
                    {
                        dividend -= d;
                        q += n;
                    }
                }
            }
            return negative ? -q : q;
        }
        int divide7(int dividend, int divisor)
        {
            if (dividend == INT_MIN)
            {
                if (divisor == -1)
                    return INT_MAX;
                if (divisor == 1)
                    return INT_MIN;
                if (divisor == INT_MIN)
                    return 1;
            }
            if (divisor == INT_MIN)
                return 0;
            bool negative =
                (dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0);
            unsigned int udividend = dividend;
            unsigned int udivisor = divisor; // wrong if divide 7 by -3
            int q = 0;
            int n = 1;
            unsigned int d = udivisor;
            while (udividend >= udivisor)
            {
                if (udividend < d)
                {
                    d = d >> 1;
                    n = n >> 1;
                }
                else if (udividend - d >= d)
                {
                    d = d << 1;
                    n = n << 1;
                }
                else
                {
                    udividend -= d;
                    q += n;
                }
            }
            return negative ? -q : q;
        }

        // 30. Substring with Concatenation of All Words
        // You are given a string s and an array of strings words of the same length.
        // Return all starting indices of substring(s) in s that is a concatenation
        // of each word in words exactly once, in any order, and without any intervening
        // characters. You can return the answer in any order.
        // Example 1:
        // Input: s = "barfoothefoobarman", words = ["foo","bar"]
        // Output: [0,9]
        // Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar"
        // respectively. The output order does not matter, returning [9,0] is fine too.
        // Example 2:
        // Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
        // Output: []
        // Example 3:
        // Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
        // Output: [6,9,12]
        // Note: once matched foobarthe at 6, then next just need to check s[6..8] == s[15..17] to find 9.
        // Constraints:
        // 1 <= s.length <= 104
        // s consists of lower-case English letters.
        // 1 <= words.length <= 5000
        // 1 <= words[i].length <= 30
        // words[i] consists of lower-case English letters.
        // This is wrong:
        vector<int> findSubstring(const string &s, const vector<string> &words)
        {
            function<void(const string &, const map<string, int> &)>
                pmap = [&](const string &msg, const map<string, int> &m)
            {
                cout << msg << ": {";
                for (const auto &p : m)
                {
                    cout << "{" << p.first << ": " << p.second << "}, ";
                }
                cout << "}" << endl;
            };
            function<bool(const map<string, int> &, const map<string, int> &)>
                match = [&](const map<string, int> &a, const map<string, int> &b) -> bool
            {
                if (a.size() != b.size())
                    return false;
                for (const auto &p : a)
                {
                    if (b.find(p.first) == b.end())
                        return false;
                    if (b.at(p.first) != p.second)
                        return false;
                }
                return true;
            };
            map<string, int> wordsMap;
            for (const string &w : words)
            {
                if (wordsMap.find(w) == wordsMap.end())
                    wordsMap[w] = 1;
                else
                    wordsMap[w]++;
            }
            pmap("input", wordsMap);
            const int wordLen = words[0].size();
            const int wordCount = words.size();
            const int wordLenTotal = wordCount * wordLen;
            map<string, int> m;
            int c = 0;
            int i = 0;
            vector<int> output;
            const int sl = s.size();
            while (i + wordLen <= sl)
            {
                string w = s.substr(i, wordLen);
                if (m.find(w) == m.end())
                    m[w] = 1;
                else
                    m[w]++;
                ostringstream o;
                o << i;
                pmap(o.str(), m);
                c++;
                i += wordLen;
                if (c < wordCount)
                    continue;
                int begin = i - wordLenTotal;
                if (match(m, wordsMap))
                {
                    cout << "matched at " << begin << endl;
                    output.push_back(begin);
                }
                string beginWord = s.substr(begin, wordLen);
                m[beginWord]--;
                if (m[beginWord] == 0)
                    m.erase(beginWord);
                c--;
            }
            return output;
        }
        vector<int> findSubstring2(const string &s, const vector<string> &words)
        {
            map<string, int> wordCount;
            for (const string &w : words)
            {
                if (wordCount.find(w) == wordCount.end())
                    wordCount[w] = 1;
                else
                    wordCount[w]++;
            }
            // cout << "{" << endl;
            // for (const auto& p : wordCount)
            // {
            //     cout << "  " << p.first << ": " << p.second << endl;
            // }
            // cout << "}" << endl;
            int wordLen = (int)words[0].size();
            int i = 0;
            vector<int> result;
            while (i < (int)s.size())
            {
                string e = s.substr(i, wordLen);
                if (wordCount.find(e) != wordCount.end())
                {
                    int j = i;
                    map<string, int> m(wordCount);
                    int count = (int)words.size();
                    // cout << "j = ";
                    while (j < (int)s.size() && count > 0)
                    {
                        // cout << j;
                        e = s.substr(j, wordLen);
                        if (m.find(e) == m.end() || m[e] == 0)
                        {
                            break;
                        }
                        else
                        {
                            m[e]--;
                            count--;
                            j += wordLen;
                        }
                    }
                    // cout << endl;
                    // cout << "count = " << count << endl;
                    if (count == 0)
                        result.push_back(i);
                }
                i++;
            }
            return result;
        }
        vector<int> findSubstring3(const string &s, const vector<string> &words)
        {
            function<bool(const map<char, int> &, const map<char, int> &)> equal =
                [&](const map<char, int> &m1, const map<char, int> &m2) -> bool
            {
                if (m1.size() != m2.size())
                    return false;
                for (const auto &p : m1)
                {
                    if (m2.find(p.first) == m2.end())
                        return false;
                    if (m2.at(p.first) != p.second)
                        return false;
                }
                return true;
            };
            map<string, int> wc;
            map<char, int> cc;
            for (const string &w : words)
            {
                if (wc.find(w) == wc.end())
                    wc[w] = 1;
                else
                    wc[w]++;
                for (size_t i = 0; i < w.size(); i++)
                {
                    if (cc.find(w[i]) == cc.end())
                        cc[w[i]] = 1;
                    else
                        cc[w[i]]++;
                }
            }
            int w = words[0].size();
            int n = (int)words.size() * w;
            vector<int> result;
            map<char, int> c;
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (c.find(s[i]) == c.end())
                    c[s[i]] = 1;
                else
                    c[s[i]]++;
                if (i >= n)
                {
                    c[s[i - n]]--;
                    if (c[s[i - n]] == 0)
                        c.erase(s[i - n]);
                }
                if (equal(c, cc))
                {
                    map<string, int> wc2(wc);
                    int j = i - n + 1;
                    int count = words.size();
                    while (j < (int)s.size() && count > 0)
                    {
                        string e = s.substr(j, w);
                        if (wc2.find(e) == wc2.end() || wc2[e] == 0)
                            break;
                        else
                        {
                            wc2[e]--;
                            count--;
                            j += w;
                        }
                    }
                    if (count == 0)
                        result.push_back(i - n + 1);
                }
            }
            return result;
        }
        static vector<int> SubstringOfConcatenation(const string &S,
                                                    vector<string> &L)
        {
            vector<int> result;
            int len = S.length();
            if (len == 0 || L.size() == 0)
                return result;
            int sl = L.size() * L[0].length();
            if (len < sl)
                return result;
            map<string, int> m;
            for_each(L.begin(), L.end(), [&](string &s)
                     {
                if (m.find(s) == m.end()) {
                    m[s] = 1;
                } else {
                    m[s] += 1;
                } });
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

        // 31. Next Permutation
        // Implement next permutation, which rearranges numbers into the
        // lexicographically next greater permutation of numbers. If such arrangement is
        // not possible, it must rearrange it as the lowest possible order (ie, sorted
        // in ascending order). The replacement must be in-place and use only constant
        // extra memory. Here are some examples. Inputs are in the left-hand column and
        // its corresponding outputs are in the right-hand column. 1,2,3 -> 1,3,2 3,2,1
        // -> 1,2,3 1,1,5 -> 1,5,1
        void nextPermutation(vector<int> &nums)
        {
            if (nums.empty())
                return;
            int i = nums.size() - 1;
            while (0 < i && nums[i - 1] >= nums[i])
                i--;
            int j = i;
            int k = nums.size() - 1;
            while (j < k)
                swap(nums[j++], nums[k--]);
            if (i == 0)
                return;
            j = i;
            k = nums.size() - 1;
            i--;
            while (j <= k)
            {
                int m = j + ((k - j) >> 1);
                if (nums[i] < nums[m])
                {
                    if (0 <= m - 1 && nums[m - 1] <= nums[i])
                    {
                        swap(nums[i], nums[m]);
                        break;
                    }
                    k = m - 1;
                }
                else
                {
                    if (m + 1 < (int)nums.size() && nums[i] < nums[m + 1])
                    {
                        swap(nums[i], nums[m + 1]);
                        break;
                    }
                    j = m + 1;
                }
            }
        }
        void nextPermutation2(vector<int> &nums)
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

        // 32. Longest Valid Parentheses
        // Given a string containing just the characters '(' and ')', find the length
        // of the longest valid (well-formed) parentheses substring.
        // Example 1:
        // Input: "(()", Output: 2
        // Explanation: The longest valid parentheses substring is "()"
        // Example 2:
        // Input: ")()())", Output: 4
        // Explanation: The longest valid parentheses substring is "()()"
        int longestValidParentheses(const string &s)
        {
            size_t m = 0;
            stack<size_t> p;
            // compute max length at every valid ')'
            for (size_t i = 0; i < s.size(); i++)
            {
                if (!p.empty() && s[i] == ')' && s[p.top()] == '(')
                {
                    p.pop();
                    m = max(m, p.empty() ? i + 1 : i - p.top());
                }
                else
                {
                    p.push(i);
                }
            }
            return (int)m;
        }
        int longestValidParentheses2(const string &s)
        {
            stack<int> p;
            int m = 0;
            int i = 0;
            // compute max length at every '(' or invalid ')'
            for (; i < (int)s.size(); i++)
            {
                if (s[i] == ')' && !p.empty() && s[p.top()] == '(')
                {
                    p.pop();
                }
                else // '(' or invalid ')'
                {
                    m = max(m, p.empty() ? i : i - p.top() - 1);
                    p.push(i);
                }
            }
            m = max(m, p.empty() ? i : i - p.top() - 1);
            return m;
        }
        int longestValidParentheses3(const string &s)
        {
            int len = s.length();
            if (len == 0)
                return 0;
            // Every element of p represents a string of valid parentheses
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
                    // it and it + 1 are disjoint but ajacent, so merge them
                    it->second = (it + 1)->second;
                    p.erase(it + 1);
                }
                else
                {
                    it++;
                }
            }
            // Now p contains disjoint strings of valid parentheses
            bool stop = false;
            while (!stop)
            {
                stop = true;
                // expand each element of p
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
                // now some neighboring elements of p may be adjacent, merge them
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
        int longestValidParentheses4(const string &s)
        {
            int len = s.length();
            if (len == 0)
                return 0;
            function<bool(int &, int &)> expand = [&](int &j, int &k) -> bool
            {
                bool e = false;
                while (j - 1 >= 0 && k + 1 < len && s[j - 1] == '(' &&
                       s[k + 1] == ')')
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
                {
                    i++;
                }
            }
            return m;
        }
        // This is wrong. e.g. "((()())((" return 0 but the answer should be 6
        int longestValidParentheses5(const string &s)
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
        int longestValidParentheses6(const string &s)
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

        // 33. Search in Rotated Sorted Array
        // Suppose an array sorted in ascending order is rotated at some pivot unknown
        // to you beforehand. (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
        // You are given a target value to search. If found in the array return its
        // index, otherwise return -1. You may assume no duplicate exists in the array.
        // Your algorithm's runtime complexity must be in the order of O(log n).
        // Example 1:
        // Input: nums = [4,5,6,7,0,1,2], target = 0
        // Output: 4
        // Example 2:
        // Input: nums = [4,5,6,7,0,1,2], target = 3
        // Output: -1
        // Note: The pivot may be 0, i.e., no rotation
        int search(const vector<int> &nums, int target)
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
        int search2(const vector<int> &nums, int target)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (target < nums[m])
                {
                    if (nums[0] <= target)
                        h = m - 1;
                    else if (nums[0] <= nums[m])
                        l = m + 1;
                    else
                        h = m - 1;
                }
                else if (nums[m] < target)
                {
                    if (nums[0] <= nums[m])
                        l = m + 1;
                    else if (nums[0] <= target)
                        h = m - 1;
                    else
                        l = m + 1;
                }
                else
                {
                    return m;
                }
            }
            return -1;
        }
        int search3(const vector<int> &nums, int target)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (target < nums[m])
                {
                    if (nums[0] <= target)
                        h = m;
                    else if (nums[0] <= nums[m])
                        l = m + 1;
                    else
                        h = m;
                }
                else if (nums[m] < target)
                {
                    if (nums[0] <= nums[m])
                        l = m + 1;
                    else if (nums[0] <= target)
                        h = m;
                    else
                        l = m + 1;
                }
                else
                {
                    return m;
                }
            }
            if (l == h && nums[l] == target)
                return l;
            return -1;
        }
        int search4(const vector<int> &nums, int target)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (target < nums[m])
                {
                    if (nums[0] <= target)
                        h = m;
                    else if (nums[0] <= nums[m])
                        l = m;
                    else
                        h = m;
                }
                else if (nums[m] < target)
                {
                    if (nums[0] <= nums[m])
                        l = m;
                    else if (nums[0] <= target)
                        h = m;
                    else
                        l = m;
                }
                else
                {
                    return m;
                }
            }
            if (l <= h)
            {
                if (nums[l] == target)
                    return l;
                if (nums[h] == target)
                    return h;
            }
            return -1;
        }
        int search5(const vector<int> &nums, int target)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (target < nums[m])
                {
                    if (nums[0] <= nums[m])
                    {
                        if (nums[0] <= target)
                            h = m - 1;
                        else
                            l = m + 1;
                    }
                    else
                    {
                        h = m - 1;
                    }
                }
                else if (nums[m] < target)
                {
                    if (nums[0] <= nums[m])
                    {
                        l = m + 1;
                    }
                    else
                    {
                        if (nums[0] <= target)
                            h = m - 1;
                        else
                            l = m + 1;
                    }
                }
                else
                {
                    return m;
                }
            }
            return -1;
        }

        // 34. Find First and Last Position of Element in Sorted Array
        // Given an array of integers nums sorted in ascending order, find the starting
        // and ending position of a given target value. Your algorithm's runtime
        // complexity must be in the order of O(log n). If the target is not found in
        // the array, return [-1, -1]. Example 1: Input: nums = [5,7,7,8,8,10], target =
        // 8 Output: [3,4] Example 2: Input: nums = [5,7,7,8,8,10], target = 6 Output:
        // [-1,-1]
        vector<int> searchRange(const vector<int> &nums, int target)
        {
            auto b = lower_bound(nums.begin(), nums.end(), target);
            auto e = upper_bound(nums.begin(), nums.end(), target);
            vector<int> range(2, -1);
            if (b != nums.end() && *b == target)
                range[0] = b - nums.begin();
            if (e != nums.begin() && *(e - 1) == target)
                range[1] = e - nums.begin() - 1;
            return range;
        }
        vector<int> searchRange2(const vector<int> &nums, int target)
        {
            vector<int> range = {-1, -1};
            bool foundFirst = false;
            int l = 0;
            int h = (int)nums.size() - 1;
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] < target)
                {
                    l = m + 1;
                }
                else if (nums[m] > target)
                {
                    h = m - 1;
                }
                else if (!foundFirst)
                {
                    if (l == m || nums[m - 1] < target)
                    {
                        foundFirst = true;
                        range[0] = m;
                        l = m;
                        h = (int)nums.size() - 1;
                    }
                    else
                    {
                        // l < m < h && nums[m - 1] == target
                        h = m - 1;
                    }
                }
                else
                {
                    if (m == h || nums[m] < nums[m + 1])
                    {
                        range[1] = m;
                        break;
                    }
                    else
                    {
                        // l <= m < h && nums[m] == nums[m + 1]
                        l = m + 1;
                    }
                }
            }
            return range;
        }
        vector<int> searchRange3(const vector<int> &nums, int target)
        {
            vector<int> range = {-1, -1};
            bool foundFirst = false;
            int l = 0;
            int h = (int)nums.size() - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] < target)
                {
                    l = m + 1;
                }
                else if (nums[m] > target)
                {
                    h = m;
                }
                else if (!foundFirst)
                {
                    if (l == m || nums[m - 1] < target)
                    {
                        foundFirst = true;
                        range[0] = m;
                        l = m;
                        h = (int)nums.size() - 1;
                    }
                    else
                    {
                        h = m;
                    }
                }
                else
                {
                    if (nums[m] < nums[m + 1])
                    {
                        range[1] = m;
                        break;
                    }
                    else
                    {
                        l = m + 1;
                    }
                }
            }
            if (l == h && nums[l] == target)
            {
                if (range[0] == -1)
                    range[0] = l;
                if (range[1] == -1)
                    range[1] = l;
            }
            return range;
        }
        vector<int> searchRange4(const vector<int> &nums, int target)
        {
            if (nums.empty())
                return {-1, -1};
            if (nums.size() == 1)
                return nums[0] == target ? vector<int>({0, 0}) : vector<int>({-1, -1});
            vector<int> range = {-1, -1};
            int l = 0;
            int h = (int)nums.size() - 1;
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] < target)
                    l = m;
                else
                    h = m;
            }
            range[0] = (nums[l] == target ? l : (nums[h] == target ? h : -1));
            h = (int)nums.size() - 1;
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] <= target)
                    l = m;
                else
                    h = m;
            }
            range[1] = (nums[h] == target ? h : (nums[l] == target ? l : -1));
            return range;
        }
        vector<int> searchRange5(const vector<int> &nums, int target)
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

        // 35. Search Insert Position
        // Given a sorted array and a target value, return the index if the target is
        // found. If not, return the index where it would be if it were inserted in
        // order. You may assume no duplicates in the array. Example 1: Input:
        // [1,3,5,6], 5 Output: 2 Example 2: Input: [1,3,5,6], 2 Output: 1 Example 3:
        // Input: [1,3,5,6], 7
        // Output: 4
        // Example 4:
        // Input: [1,3,5,6], 0
        // Output: 0
        int searchInsert(const vector<int> &nums, int target)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (target < nums[m])
                {
                    if (l == m)
                        return m;
                    h = m - 1;
                }
                else if (nums[m] < target)
                {
                    if (m == h)
                        return m + 1;
                    l = m + 1;
                }
                else
                {
                    return m;
                }
            }
            return 0;
        }
        int searchInsert2(const vector<int> &nums, int target)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (target < nums[m])
                {
                    if (l == m)
                        return m;
                    h = m;
                }
                else if (nums[m] < target)
                {
                    l = m + 1;
                }
                else
                {
                    return m;
                }
            }
            if (target <= nums[l])
                return l;
            else
                return l + 1;
        }
        int searchInsert3(const vector<int> &nums, int target)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (target < nums[m])
                {
                    h = m;
                }
                else if (nums[m] < target)
                {
                    l = m;
                }
                else
                {
                    return m;
                }
            }
            if (target <= nums[l])
                return l;
            else if (target <= nums[h])
                return h;
            else
                return h + 1;
        }
        int searchInsert4(const vector<int> &nums, int target)
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

        // 36. Valid Sudoku
        // Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be
        // validated according to the following rules:
        // Each row must contain the digits 1-9 without repetition.
        // Each column must contain the digits 1-9 without repetition.
        // Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without
        // repetition. A partially filled sudoku which is valid. The Sudoku board could
        // be partially filled, where empty cells are filled with the character '.'.
        // Example 1:
        // Input:
        // [
        //   ["5","3",".",".","7",".",".",".","."],
        //   ["6",".",".","1","9","5",".",".","."],
        //   [".","9","8",".",".",".",".","6","."],
        //   ["8",".",".",".","6",".",".",".","3"],
        //   ["4",".",".","8",".","3",".",".","1"],
        //   ["7",".",".",".","2",".",".",".","6"],
        //   [".","6",".",".",".",".","2","8","."],
        //   [".",".",".","4","1","9",".",".","5"],
        //   [".",".",".",".","8",".",".","7","9"]
        // ]
        // Output: true
        // Example 2:
        // Input:
        // [
        //   ["8","3",".",".","7",".",".",".","."],
        //   ["6",".",".","1","9","5",".",".","."],
        //   [".","9","8",".",".",".",".","6","."],
        //   ["8",".",".",".","6",".",".",".","3"],
        //   ["4",".",".","8",".","3",".",".","1"],
        //   ["7",".",".",".","2",".",".",".","6"],
        //   [".","6",".",".",".",".","2","8","."],
        //   [".",".",".","4","1","9",".",".","5"],
        //   [".",".",".",".","8",".",".","7","9"]
        // ]
        // Output: false
        // Explanation: Same as Example 1, except with the 5 in the top left corner
        // being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it
        // is invalid. Note: A Sudoku board (partially filled) could be valid but is not
        // necessarily solvable. Only the filled cells need to be validated according to
        // the mentioned rules. The given board contain only digits 1-9 and the
        // character '.'. The given board size is always 9x9.
        bool isValidSudoku(const vector<vector<char>> &board)
        {
            vector<set<char>> row(9);
            vector<set<char>> col(9);
            vector<set<char>> cell(9);
            for (int i = 0; i < (int)board.size(); i++)
            {
                for (int j = 0; j < (int)board[i].size(); j++)
                {
                    char c = board[i][j];
                    if (c == '.')
                        continue;
                    if (row[i].find(c) != row[i].end())
                        return false;
                    if (col[j].find(c) != col[j].end())
                        return false;
                    int k = (i / 3) * 3 + (j / 3);
                    if (cell[k].find(c) != cell[k].end())
                        return false;
                    row[i].insert(c);
                    col[j].insert(c);
                    cell[k].insert(c);
                }
            }
            return true;
        }
        bool isValidSudoku2(const vector<vector<char>> &board)
        {
            map<size_t, set<char>> row;
            map<size_t, set<char>> col;
            map<size_t, set<char>> cell;
            for (size_t i = 0; i < board.size(); i++)
            {
                row[i] = set<char>{};
                for (size_t j = 0; j < board[0].size(); j++)
                {
                    if (i == 0)
                        col[j] = set<char>{};
                    int k = (i / 3) * 3 + (j / 3);
                    if (cell.find(k) == cell.end())
                        cell[k] = set<char>{};
                    if (board[i][j] != '.')
                    {
                        if (row[i].find(board[i][j]) != row[i].end())
                            return false;
                        row[i].insert(board[i][j]);
                        if (col[j].find(board[i][j]) != col[j].end())
                            return false;
                        col[j].insert(board[i][j]);
                        if (cell[k].find(board[i][j]) != cell[k].end())
                            return false;
                        cell[k].insert(board[i][j]);
                    }
                }
            }
            return true;
        }
        bool isValidSudoku3(const vector<vector<char>> &board)
        {
            map<char, set<size_t>> row;
            map<char, set<size_t>> col;
            map<char, set<size_t>> cell;
            for (size_t i = 0; i < board.size(); i++)
            {
                for (size_t j = 0; j < board[0].size(); j++)
                {
                    char c = board[i][j];
                    if (c != '.')
                    {
                        if (row.find(c) == row.end())
                            row[c] = set<size_t>{};
                        if (row[c].find(i) != row[c].end())
                            return false;
                        row[c].insert(i);
                        if (col.find(c) == col.end())
                            col[c] = set<size_t>{};
                        if (col[c].find(j) != col[c].end())
                            return false;
                        col[c].insert(j);
                        size_t k = (i / 3) * 3 + (j / 3);
                        if (cell.find(c) == cell.end())
                            cell[c] = set<size_t>{};
                        if (cell[c].find(k) != cell[c].end())
                            return false;
                        cell[c].insert(k);
                    }
                }
            }
            return true;
        }

        // 37. Sudoku Solver
        // Write a program to solve a Sudoku puzzle by filling the empty cells.
        // A sudoku solution must satisfy all of the following rules:
        // Each of the digits 1-9 must occur exactly once in each row.
        // Each of the digits 1-9 must occur exactly once in each column.
        // Each of the the digits 1-9 must occur exactly once in each of
        // the 9 3x3 sub-boxes of the grid.
        // Empty cells are indicated by the character '.'. Note:
        // The given board contain only digits 1-9 and the character '.'.
        // You may assume that the given Sudoku puzzle will have a single unique
        // solution. The given board size is always 9x9.
        void solveSudoku(vector<vector<char>> &board)
        {
            function<bool(size_t, size_t, vector<vector<char>> &)> solve =
                [&](size_t i, size_t j, vector<vector<char>> &b) -> bool
            {
                if (i == 9 && j == 0)
                    return true;
                if (b[i][j] != '.')
                    return solve(j < 8 ? i : i + 1, j < 8 ? j + 1 : 0, b);
                for (char c = '1'; c <= '9'; c++)
                {
                    bool isCandidate = true;
                    for (size_t k = 0; k < 9; k++)
                    {
                        if (b[i][k] == c)
                        {
                            isCandidate = false;
                            break;
                        }
                    }
                    if (!isCandidate)
                        continue;
                    for (size_t k = 0; k < 9; k++)
                    {
                        if (b[k][j] == c)
                        {
                            isCandidate = false;
                            break;
                        }
                    }
                    if (!isCandidate)
                        continue;
                    size_t m = (i / 3) * 3;
                    size_t n = (j / 3) * 3;
                    for (size_t p = m; p < m + 3; p++)
                    {
                        for (size_t q = n; q < n + 3; q++)
                        {
                            if (b[p][q] == c)
                            {
                                isCandidate = false;
                                break;
                            }
                        }
                        if (!isCandidate)
                            break;
                    }
                    if (!isCandidate)
                        continue;
                    b[i][j] = c;
                    if (solve(j < 8 ? i : i + 1, j < 8 ? j + 1 : 0, b))
                        return true;
                }
                b[i][j] = '.';
                return false;
            };
            solve(0, 0, board);
        }
        void solveSudoku2(vector<vector<char>> &board)
        {
            function<void(int &, int, int &, int)>
                oneStep = [&](int &i, int r, int &j, int c)
            {
                j++;
                j = j % c;
                if (j == 0)
                {
                    i++;
                    i = i % r;
                }
            };
            function<bool(vector<vector<char>> &, int, int, vector<set<char>> &,
                          vector<set<char>> &, vector<vector<set<char>>> &,
                          map<pair<int, int>, set<char>> &)>
                solve =
                    [&](vector<vector<char>> &b, int i, int j,
                        vector<set<char>> &row, // existing characters on every row
                        vector<set<char>> &col, // existing characters on every column
                        vector<vector<set<char>>>
                            cell, // existing characters in every 3x3 cell
                        map<pair<int, int>, set<char>>
                            &m // available characters for every empty cell
                        ) -> bool
            {
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
                    if (row[i].find(c) == row[i].end() &&
                        col[j].find(c) == col[j].end() &&
                        cell[i / 3][j / 3].find(c) == cell[i / 3][j / 3].end())
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
            vector<vector<set<char>>> cell =
                vector<vector<set<char>>>(3, vector<set<char>>(3, set<char>{}));
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
                            if (row[i].find(c) == row[i].end() &&
                                col[j].find(c) == col[j].end() &&
                                cell[i / 3][j / 3].find(c) ==
                                    cell[i / 3][j / 3].end())
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
        void solveSudoku3(vector<vector<char>> &board)
        {
            vector<set<char>> row(9, set<char>{});
            vector<set<char>> col(9, set<char>{});
            vector<set<char>> cell(9, set<char>{});
            function<int(int, int)> cellIndex = [&](int i, int j) -> int
            {
                return 3 * (i / 3) + (j / 3);
            };
            set<pair<int, int>> fix;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (board[i][j] != '.')
                    {
                        row[i].insert(board[i][j]);
                        col[j].insert(board[i][j]);
                        int k = cellIndex(i, j);
                        cell[k].insert(board[i][j]);
                        fix.insert(make_pair(i, j));
                    }
                }
            }
            map<pair<int, int>, char> m;
            stack<pair<int, int>> s;
            int i = 0;
            int j = 0;
            char v = '1';
            while (true)
            {
                int k = cellIndex(i, j);
                auto p = make_pair(i, j);
                if (0 <= i && i < 9 && 0 <= j && j < 9 && v <= '9' && row[i].find(v) == row[i].end() && col[j].find(v) == col[j].end() && cell[k].find(v) == cell[k].end() && fix.find(p) == fix.end())
                {
                    board[i][j] = v;
                    s.push(p);
                    m[p] = v;
                    row[i].insert(v);
                    col[j].insert(v);
                    cell[k].insert(v);
                    j = (j + 1) % 9;
                    if (j == 0)
                        i++;
                    v = '1';
                }
                else
                {
                    if (i == 9 && j == 0)
                        break;
                    if (fix.find(p) != fix.end())
                    {
                        j = (j + 1) % 9;
                        if (j == 0)
                            i++;
                        v = '1';
                    }
                    else if (v <= '9')
                    {
                        v++;
                    }
                    else // v > '9'
                    {
                        if (s.empty())
                            break;
                        p = s.top();
                        s.pop();
                        i = p.first;
                        j = p.second;
                        v = m[p];
                        row[i].erase(v);
                        col[j].erase(v);
                        cell[cellIndex(i, j)].erase(v);
                        board[i][j] = '.';
                        v++;
                    }
                }
            }
        }

        // 38. Count and Say
        // The count-and-say sequence is the sequence of integers with the first five
        // terms as following:
        // 1.     1
        // 2.     11
        // 3.     21
        // 4.     1211
        // 5.     111221
        // 1 is read off as "one 1" or 11.
        // 11 is read off as "two 1s" or 21.
        // 21 is read off as "one 2, then one 1" or 1211.
        // Given an integer n where 1 <= n <= 30, generate the nth term of the
        // count-and-say sequence. You can do so recursively, in other words from the
        // previous member read off the digits, counting the number of digits in groups
        // of the same digit. Note: Each term of the sequence of integers will be
        // represented as a string. Example 1: Input: 1 Output: "1" Explanation: This is
        // the base case. Example 2: Input: 4 Output: "1211" Explanation: For n = 3 the
        // term was "21" in which we have two groups "2" and "1", "2" can be read as
        // "12" which means frequency = 1 and value = 2, the same way "1" is read as
        // "11", so the answer is the concatenation of "12" and "11" which is "1211".
        string countAndSay(int n)
        {
            string s = "1";
            for (int i = 2; i <= n; i++)
            {
                size_t j = 0;
                stringstream ss;
                while (j < s.size())
                {
                    size_t k = j;
                    while (k + 1 < s.size() && s[k + 1] == s[k])
                        k++;
                    ss << (k - j + 1) << s[j];
                    j = k + 1;
                }
                s = ss.str();
            }
            return s;
        }
        string countAndSay2(int n)
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

        // 39. Combination Sum
        // Given a set of candidate numbers (candidates) (without duplicates) and a
        // target number (target), find all unique combinations in candidates where
        // the candidate numbers sums to target. The same repeated number may be chosen
        // from candidates unlimited number of times. Note: All numbers (including
        // target) will be positive integers. The solution set must not contain
        // duplicate combinations. Example 1: Input: candidates = [2,3,6,7], target = 7,
        // A solution set is:
        // [
        //   [7],
        //   [2,2,3]
        // ]
        // Example 2:
        // Input: candidates = [2,3,5], target = 8,
        // A solution set is:
        // [
        //   [2,2,2,2],
        //   [2,3,3],
        //   [3,5]
        // ]
        vector<vector<int>> combinationSum(const vector<int> &candidates, int target)
        {
            vector<vector<int>> result;
            function<void(size_t, int, vector<int> &)>
                solve = [&](size_t i, int t, vector<int> &v)
            {
                if (i >= candidates.size())
                    return;
                if (candidates[i] <= t)
                {
                    vector<int> v1(v);
                    v1.push_back(candidates[i]);
                    if (candidates[i] == t)
                        result.push_back(v1);
                    else
                        solve(i, t - candidates[i], v1);
                }
                vector<int> v2(v);
                solve(i + 1, t, v2);
            };
            vector<int> v;
            solve(0, target, v);
            return result;
        }
        vector<vector<int>> combinationSum2(const vector<int> &candidates,
                                            int target)
        {
            vector<vector<int>> result;
            function<void(size_t, int, vector<int> &)>
                solve = [&](size_t i, int t, vector<int> &v)
            {
                if (i >= candidates.size())
                    return;
                if (candidates[i] <= t)
                {
                    v.push_back(candidates[i]);
                    if (candidates[i] == t)
                        result.push_back(v);
                    else
                        solve(i, t - candidates[i], v);
                    v.pop_back();
                }
                solve(i + 1, t, v);
            };
            vector<int> v;
            solve(0, target, v);
            return result;
        }
        vector<vector<int>> combinationSum3(vector<int> &candidates, int target)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            sort(candidates.begin(), candidates.end());
            function<void(int, int, vector<int> &)>
                solve = [&](int i, int t, vector<int> &s)
            {
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
        vector<vector<int>> combinationSum4(vector<int> &candidates, int target)
        {
            sort(candidates.begin(), candidates.end());
            map<pair<int, int>, vector<vector<int>>> m;
            function<void(int, int)> solve = [&](int i, int t)
            {
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
                    for_each(m[p1].begin(), m[p1].end(), [&](vector<int> &s)
                             {
                                 vector<int> r(s);
                                 r.insert(r.begin(), candidates[j]);
                                 m[p].push_back(r); });
                }
            };
            solve(0, target);
            return m[make_pair(0, target)];
        }
        vector<vector<int>> combinationSum5(vector<int> &candidates, int target)
        {
            vector<vector<int>> o;
            vector<pair<vector<int>, int>> s;
            s.push_back(make_pair(vector<int>{}, target));
            sort(candidates.begin(), candidates.end());
            for (const int c : candidates)
            {
                size_t n = s.size();
                for (size_t i = 0; i < n; i++)
                {
                    // for every element in s, append it with {c}, {c,c},...
                    // until reaching the target
                    vector<int> v(s[i].first);
                    int d = 0;
                    while (d < s[i].second)
                    {
                        v.push_back(c);
                        d += c;
                        if (d < s[i].second)
                            s.push_back(make_pair(v, s[i].second - d));
                        else if (d == s[i].second)
                            o.push_back(v);
                    }
                }
            }
            return o;
        }

        // 40. Combination Sum II
        // Given a collection of candidate numbers (candidates) and a target number
        // (target), find all unique combinations in candidates where the candidate
        // numbers sums to target. Each number in candidates may only be used once in
        // the combination. Note: All numbers (including target) will be positive
        // integers. The solution set must not contain duplicate combinations.
        // Example 1:
        // Input: candidates = [10,1,2,7,6,1,5], target = 8,
        // A solution set is:
        // [
        //   [1, 7],
        //   [1, 2, 5],
        //   [2, 6],
        //   [1, 1, 6]
        // ]
        // Example 2:
        // Input: candidates = [2,5,2,1,2], target = 5,
        // A solution set is:
        // [
        //   [1,2,2],
        //   [5]
        // ]
        vector<vector<int>> combinationSumII(vector<int> &candidates, int target)
        {
            vector<vector<int>> result;
            sort(candidates.begin(), candidates.end());
            function<void(size_t, int, vector<int> &)>
                solve = [&](size_t i, int t, vector<int> &v)
            {
                if (i >= candidates.size() || candidates[i] > t)
                    return;
                size_t j = i;
                while (j + 1 < candidates.size() && candidates[j] == candidates[j + 1])
                    j++;
                int s = 0;
                for (size_t k = i; k <= j; k++)
                {
                    s += candidates[k];
                    v.push_back(candidates[k]);
                    if (s == t)
                        result.push_back(v);
                    else
                        solve(j + 1, t - s, v);
                }
                for (size_t k = i; k <= j; k++)
                    v.pop_back();
                solve(j + 1, t, v);
            };
            vector<int> v;
            solve(0, target, v);
            return result;
        }
        vector<vector<int>> combinationSumII2(vector<int> &candidates, int target)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            // Sort so we can eliminate duplicate solutions later
            // [Can we not use sort? Instead using a set of <i,t> pairs to track the
            // visited?]
            std::sort(candidates.begin(), candidates.end());
            function<void(size_t, int, vector<int> &)>
                solve = [&](size_t i, int t, vector<int> &c)
            {
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
                while (i + 1 < candidates.size() &&
                       candidates[i] == candidates[i + 1])
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
        vector<vector<int>> combinationSumII3(vector<int> &candidates, int target)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            // Sort so we can eliminate duplicate solutions later
            std::sort(candidates.begin(), candidates.end());
            function<void(size_t, int, vector<int> &)>
                solve = [&](size_t i, int t, vector<int> &c)
            {
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
        vector<vector<int>> combinationSumII4(vector<int> &candidates, int target)
        {
            sort(candidates.begin(), candidates.end());
            vector<vector<int>> o;
            vector<pair<vector<int>, long long>> s;
            s.push_back(make_pair(vector<int>{}, target));
            size_t i = 0;
            while (i < candidates.size())
            {
                size_t j = i;
                while (j + 1 < candidates.size() && candidates[j] == candidates[j + 1])
                    j++;
                size_t n = s.size();
                long long a = 0;
                vector<int> v;
                for (size_t k = i; k <= j; k++)
                {
                    a += candidates[k];
                    v.push_back(candidates[k]);
                    for (size_t l = 0; l < n; l++)
                    {
                        if (a <= s[l].second)
                        {
                            auto p = s[l];
                            p.first.insert(p.first.end(), v.begin(), v.end());
                            p.second -= a;
                            if (p.second == 0)
                                o.push_back(p.first);
                            else
                                s.push_back(p);
                        }
                    }
                }
                i = j + 1;
            }
            return o;
        }

        // 41. First Missing Positive
        // Given an unsorted integer array, find the smallest missing positive integer.
        // Example 1: Input: [1,2,0], Output: 3
        // Example 2: Input: [3,4,-1,1], Output: 2
        // Example 3: Input: [7,8,9,11,12], Output: 1
        // Note: Your algorithm should run in O(n) time and uses constant extra space.
        int firstMissingPositive(vector<int> &nums)
        {
            if (nums.empty())
                return 1;
            int m = INT_MAX;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (nums[i] > 0 && m > nums[i])
                    m = nums[i];
            }
            if (m > 1)
                return 1;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                while (nums[i] > 0 && nums[i] != i + 1)
                {
                    int j = nums[i] - 1;
                    if (j >= (int)nums.size() || nums[j] == nums[i])
                        break;
                    swap(nums[i], nums[j]);
                }
            }
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (nums[i] != i + 1)
                    return i + 1;
            }
            return nums.size() + 1;
        }
        int firstMissingPositive2(vector<int> &nums)
        {
            if (nums.empty())
                return 1;
            set<int> s;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (nums[i] > 0)
                    s.insert(nums[i]);
            }
            int j = 1;
            for (auto it = s.cbegin(); it != s.cend(); it++)
            {
                if (*it != j)
                    break;
                j++;
            }
            return j;
        }
        // This is wrong because it does not handle duplicates.
        // For [0,2,2,1,1], expect 3 but get 2
        int firstMissingPositive3(vector<int> &nums)
        {
            if (nums.empty())
                return 1;
            sort(nums.begin(), nums.end());
            size_t i = 0;
            while (i < nums.size() && nums[i] <= 0)
                i++;
            int j = 1;
            while (i < nums.size() && nums[i] == j)
            {
                i++;
                j++;
            }
            return j;
        }

        // 42. Trapping Rain Water
        // Given n non-negative integers representing an elevation map where the width
        // of each bar is 1, compute how much water it is able to trap after raining.
        // The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
        // In this case, 6 units of rain water (blue section) are being trapped.
        // Example:
        // Input:  [0,1,0,2,1,0,1,3,2,1,2,1]
        // Trapped:[0,0,1,0,1,2,1,0,0,1,0,0]
        // Output: 6
        int trap(const vector<int> &height)
        {
            int v = 0;
            int i = 0;
            while (i < (int)height.size())
            {
                int j = i;
                // Find j such that h[i] <= h[j + 1]
                while (j + 1 < (int)height.size() && height[i] > height[j + 1])
                    j++;
                if (j + 1 == (int)height.size())
                    break;
                // Now h[i] <= h[j + 1]
                // Count volume h[(i+1)..j]
                for (int k = i + 1; k <= j; k++)
                {
                    v += (height[i] - height[k]);
                }
                i = j + 1;
            }
            int h = i; // The peak
            if (h < (int)height.size() - 1)
            {
                i = (int)height.size() - 1;
                while (h <= i)
                {
                    int j = i;
                    // Find j such that h[j - 1] >= h[i]
                    while (h <= j - 1 && height[j - 1] < height[i])
                        j--;
                    if (j == h)
                        break;
                    for (int k = i - 1; k >= j; k--)
                    {
                        v += (height[i] - height[k]);
                    }
                    i = j - 1;
                }
            }
            return v;
        }
        int trap2(const vector<int> &height)
        {
            if (height.size() <= 2)
                return 0;
            function<int(int, int)> count = [&](int i, int j) -> int
            {
                int m = min(height[i], height[j]);
                int s = 0;
                for (int k = i + 1; k < j; k++)
                    s += (m - height[k]);
                return s;
            };
            // contains non-increasing integers
            stack<int> tips;
            tips.push(0);
            int i;
            int v = 0;
            for (int j = 1; j < (int)height.size(); j++)
            {
                while (!tips.empty() && height[tips.top()] < height[j])
                {
                    i = tips.top();
                    tips.pop();
                }
                if (tips.empty())
                {
                    // Now A[i] and A[j] are the two most higher tips seen so far
                    // and A[i] < A[j]
                    if (j - i > 1)
                        v += count(i, j);
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
                    v += count(i, j);
                j = i;
                tips.pop();
            }
            return v;
        }
        int trap3(const vector<int> &height)
        {
            vector<int> h(height);
            int v = 0;
            int i = 0;
            int j = h.size() - 1;
            while (i < j)
            {
                if (h[i] <= h[j])
                {
                    if (i + 1 < j)
                    {
                        v += max(0, h[i] - h[i + 1]);
                        h[i + 1] = max(h[i], h[i + 1]);
                    }
                    i++;
                }
                else
                {
                    if (i + 1 < j)
                    {
                        v += max(0, h[j] - h[j - 1]);
                        h[j - 1] = max(h[j - 1], h[j]);
                    }
                    j--;
                }
            }
            return v;
        }
        // This algorithm is wrong.
        // Not every tip is a valid tip.
        // If a tip is trapped between two higher tips, then it should be removed.
        int TrapWater2(int A[], int n)
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

        // 43. Multiply Strings
        // Given two non-negative integers num1 and num2 represented as strings, return
        // the product of num1 and num2, also represented as a string.
        // Example 1: Input: num1 = "2", num2 = "3", Output: "6"
        // Example 2: Input: num1 = "123", num2 = "456", Output: "56088"
        // Note: The length of both num1 and num2 is < 110. Both num1 and num2 contain
        // only digits 0-9. Both num1 and num2 do not contain any leading zero, except
        // the number 0 itself. You must not use any built-in BigInteger library or
        // convert the inputs to integer directly.
        string multiply(string num1, string num2)
        {
            if (num1 == "0" || num2 == "0")
                return "0";
            function<string(const string &, char)>
                mul = [&](const string &s, char d) -> string
            {
                string r;
                char c = '0';
                int i = s.size() - 1;
                while (0 <= i || c != '0')
                {
                    int t = c - '0';
                    if (0 <= i)
                        t += (s[i--] - '0') * (d - '0');
                    if (t >= 10)
                    {
                        c = '0' + t / 10;
                        t %= 10;
                    }
                    else
                    {
                        c = '0';
                    }
                    r.insert(r.begin(), '0' + t);
                }
                return r;
            };
            function<string(const string &, const string &)> add =
                [&](const string &s1, const string &s2) -> string
            {
                string r;
                char c = '0';
                int i = s1.size() - 1;
                int j = s2.size() - 1;
                while (0 <= i || 0 <= j || c != '0')
                {
                    int t = c - '0';
                    if (0 <= i)
                        t += (s1[i--] - '0');
                    if (0 <= j)
                        t += (s2[j--] - '0');
                    if (t >= 10)
                    {
                        c = '1';
                        t -= 10;
                    }
                    else
                    {
                        c = '0';
                    }
                    r.insert(r.begin(), '0' + t);
                }
                return r;
            };
            string result = "0";
            for (int i = num2.size() - 1; i >= 0; i--)
            {
                string m = mul(num1, num2[i]);
                result = add(result, m);
                num1.append(1, '0');
            }
            return result;
        }
        string multiply2(string num1, string num2)
        {
            if (num1.length() == 1 && num1[0] == '0')
                return string("0");
            if (num2.length() == 1 && num2[0] == '0')
                return string("0");
            function<int(char)> toDigit = [&](char c)
            { return c - '0'; };
            function<char(int)> toChar = [&](int i)
            { return i + '0'; };
            function<string(string, char)> multiplyDigit = [&](string str, char ch)
            {
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
            function<string(string, string)> sum = [&](string str1, string str2)
            {
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

        // 44. Wildcard Matching
        // Given an input string (s) and a pattern (p), implement wildcard pattern
        // matching with support for '?' and '*'.
        // '?' Matches any single character.
        // '*' Matches any sequence of characters (including the empty sequence).
        // The matching should cover the entire input string (not partial).
        // Note:
        // s could be empty and contains only lowercase letters a-z.
        // p could be empty and contains only lowercase letters a-z, and characters like
        // ? or *. Example 1: Input: s = "aa" p = "a" Output: false Explanation: "a"
        // does not match the entire string "aa". Example 2: Input: s = "aa" p = "*"
        // Output: true
        // Explanation: '*' matches any sequence.
        // Example 3:
        // Input:
        // s = "cb"
        // p = "?a"
        // Output: false
        // Explanation: '?' matches 'c', but the second letter is 'a', which does not
        // match 'b'. Example 4: Input: s = "adceb" p = "*a*b" Output: true Explanation:
        // The first '*' matches the empty sequence, while the second '*' matches the
        // substring "dce". Example 5: Input: s = "acdcb" p = "a*c?b" Output: false
        bool isMatch(const string &s, const string &p)
        {
            function<bool(size_t, size_t)> match = [&](size_t i, size_t j) -> bool
            {
                if (i == s.size() && j == p.size())
                    return true;
                if (j == p.size())
                    return false;
                if (i < s.size() && (s[i] == p[j] || p[j] == '?'))
                    return match(i + 1, j + 1);
                // i == s.size()
                // s[i] != p[j] && p[j] != '?'
                if (p[j] == '*')
                {
                    // Skip all '*'
                    while (j < p.size() && p[j] == '*')
                        j++;
                    size_t k = i;
                    while (k <= s.size())
                    {
                        if (match(k, j))
                            return true;
                        k++;
                    }
                }
                return false;
            };
            return match(0, 0);
        }
        bool isMatch2(const string &s, const string &p)
        {
            stack<pair<size_t, size_t>> m;
            size_t i = 0;
            size_t j = 0;
            while (i <= s.size() && j <= p.size())
            {
                if (i < s.size() && j < p.size() && (s[i] == p[j] || p[j] == '?'))
                {
                    i++;
                    j++;
                }
                else if (j < p.size() && p[j] == '*')
                {
                    // i <= s.size()
                    j++;
                    if (j == p.size() || p[j] != '*')
                    {
                        // p[j-1] == '*'
                        // record (i, j) because we might need to check (i+1, j) (i+2, j), ...
                        m.push(make_pair(i, j));
                    }
                }
                else if (i == s.size())
                {
                    return j == p.size();
                }
                else
                {
                    if (m.empty())
                        break;
                    // last (i, j) does not work
                    // skip i and continue check (i + 1, j) because we known p[j-1] == '*'
                    auto t = m.top();
                    m.pop();
                    i = t.first + 1;
                    j = t.second;
                    m.push(make_pair(i, j));
                }
            }
            return false;
        }
        bool isMatch3(const string &s, const string &p)
        {
            map<pair<size_t, size_t>, bool> m;
            function<bool(size_t, size_t)> match = [&](size_t i, size_t j) -> bool
            {
                pair<size_t, size_t> v = make_pair(i, j);
                if (m.find(v) != m.end())
                    return m[v];
                if (i == s.size() && j == p.size())
                {
                    m[v] = true;
                    return true;
                }
                if (j == p.size())
                {
                    m[v] = false;
                    return false;
                }
                if (i < s.size() && (s[i] == p[j] || p[j] == '?'))
                    return match(i + 1, j + 1);
                if (p[j] == '*')
                {
                    while (j < p.size() && p[j] == '*')
                        j++;
                    size_t k = i;
                    while (k <= s.size())
                    {
                        if (match(k, j))
                        {
                            m[v] = true;
                            return true;
                        }
                        k++;
                    }
                }
                m[v] = false;
                return false;
            };
            return match(0, 0);
        }
        bool isMatch4(const string &s, const string &p)
        {
            map<pair<size_t, size_t>, bool> m;
            function<bool(size_t, size_t)> match = [&](size_t i, size_t j) -> bool
            {
                auto k = make_pair(i, j);
                if (m.find(k) != m.end())
                    return m[k];
                bool result = false;
                if (i == s.size() && j == p.size())
                {
                    result = true;
                }
                else if (i == s.size())
                {
                    result = p[j] == '*' ? match(i, j + 1) : false;
                }
                else if (j == p.size())
                {
                    result = false;
                }
                else if (s[i] == p[j] || p[j] == '?')
                {
                    result = match(i + 1, j + 1);
                }
                else if (p[j] == '*')
                {
                    result = match(i, j + 1) || match(i + 1, j);
                }
                else
                {
                    result = false;
                }
                m[k] = result;
                return m[k];
            };
            return match(0, 0);
        }
        // s = "adceb" p = "*a*b"
        //  ( ,*)->(a,a)->( ,  *)->(d,b)
        // |            |->(d,  *)->(c,b)
        // |            |->(dc, *)->(e,b)
        // |            |->(dce,*)->(b,b)
        // |(a,    *)->(d,a)
        // |(ad,   *)->(c,a)
        // |(adc,  *)->(e,a)
        // |(adce, *)->(b,a)
        // |(adceb,*)->( ,a)
        // s = "abcabc" p = "*a*c"
        // http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html
        bool isMatch5(const string &s, const string &p)
        {
            int lastStarIndex = -1;
            int currentIndex = 0;
            int i = 0;
            int j = 0;
            while (i < (int)s.size())
            {
                if (j < (int)p.size() && (s[i] == p[j] || p[j] == '?'))
                {
                    i++;
                    j++;
                    continue;
                }
                if (j < (int)p.size() && p[j] == '*')
                {
                    lastStarIndex = j++;
                    currentIndex = i;
                    continue;
                }
                if (lastStarIndex != -1)
                {
                    j = lastStarIndex + 1;
                    i = ++currentIndex;
                    continue;
                }
                return false;
            }
            while (j < (int)p.size() && p[j] == '*')
                j++;
            return j == (int)p.size();
        }
        bool isMatch(const char *s, const char *p)
        {
            function<int(const char *)> length = [&](const char *c) -> int
            {
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
            function<bool(const char *, const char *,
                          map<pair<const char *, const char *>, bool> &)>
                isMatchInternal =
                    [&](const char *s, const char *p,
                        map<pair<const char *, const char *>, bool> &m) -> bool
            {
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
        // isMatch("aa","a") -> false
        // isMatch("aa","aa") -> true
        // isMatch("aaa","aa") -> false
        // isMatch("aa", "a*") -> true
        // isMatch("aa", ".*") -> true
        // isMatch("ab", ".*") -> true
        // isMatch("aab", "c*a*b") -> true, this is different
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

        // 45. Jump Game II
        // Given an array of non-negative integers, you are initially positioned at
        // the first index of the array. Each element in the array represents your
        // maximum jump length at that position. Your goal is to reach the last index
        // in the minimum number of jumps.
        // Example:
        // Input: [2,3,1,1,4]
        // Output: 2
        // Explanation: The minimum number of jumps to reach the last index is 2.
        // Jump 1 step from index 0 to 1, then 3 steps to the last index.
        // Note: You can assume that you can always reach the last index.
        int jump(const vector<int> &nums)
        {
            size_t i = 0;
            int s = 0;
            size_t j = i + nums[i]; // max limit at i
            while (i + 1 < nums.size())
            {
                size_t t = j;
                // compute next max limit at j
                for (size_t k = i + 1; k <= j && k < nums.size(); k++)
                    t = max(t, k + nums[k]);
                s++;
                i = j;
                j = t;
            }
            return s;
        }
        // minSteps[i] = min{1 + minStep[k]} for i < k <= i + n[i]
        int jump2(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            vector<int> steps(nums.size(), 0);
            for (int i = (int)nums.size() - 2; i >= 0; i--)
            {
                int j = i + nums[i];
                if (j >= (int)nums.size() - 1)
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
        int jump3(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            map<int, int> step; // Key is the number of steps, value is the index where
                                // to take the steps
            map<int, int>::iterator it;
            step[0] = nums.size() - 1; // no steps to take at the end
            for (int i = (int)nums.size() - 2; i >= 0; i--)
            {
                int j = i + nums[i];
                // map is sorted by key, i.e., the number of steps
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
        int jump4(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            int currentIndex = nums[0];   // max distance current step can reach
            int nextIndex = currentIndex; // max distance next step can reach
            int step = 1;
            int i = 1;
            while (currentIndex < (int)nums.size() - 1 && i <= currentIndex)
            {
                if (i + nums[i] > nextIndex)
                    nextIndex = i + nums[i];
                i++;
                if (i > currentIndex)
                {
                    step++;
                    currentIndex = nextIndex;
                }
            }
            return step;
        }

        // 46. Permutations
        // Given a collection of distinct integers, return all possible permutations.
        // Example: Input: [1,2,3], Output:
        // [
        //   [1,2,3],
        //   [1,3,2],
        //   [2,1,3],
        //   [2,3,1],
        //   [3,1,2],
        //   [3,2,1]
        // ]
        vector<vector<int>> permute(vector<int> &nums)
        {
            vector<vector<int>> result;
            function<void(size_t)> solve = [&](size_t i)
            {
                if (i + 1 == nums.size())
                {
                    result.push_back(nums);
                    return;
                }
                for (size_t j = i; j < nums.size(); j++)
                {
                    swap(nums[i], nums[j]);
                    solve(i + 1);
                    swap(nums[i], nums[j]);
                }
            };
            solve(0);
            return result;
        }
        vector<vector<int>> permute2(vector<int> &nums)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            function<void(size_t, vector<int> &)>
                solve = [&](size_t i, vector<int> &n)
            {
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
        vector<vector<int>> permute3(vector<int> &nums)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            function<void(size_t, vector<int> &)>
                solve = [&](size_t i, vector<int> &n)
            {
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
        // Given a collection of numbers that might contain duplicates,
        // return all possible unique permutations.
        // Example:
        // Input: [1,1,2], Output:
        // [
        //   [1,1,2],
        //   [1,2,1],
        //   [2,1,1]
        // ]
        vector<vector<int>> permuteUnique(vector<int> &nums)
        {
            vector<vector<int>> result;
            function<void(size_t)> solve = [&](size_t i)
            {
                if (i + 1 == nums.size())
                {
                    result.push_back(nums);
                    return;
                }
                set<int> visited;
                for (size_t j = i; j < nums.size(); j++)
                {
                    if (visited.find(nums[j]) != visited.end())
                        continue;
                    swap(nums[i], nums[j]);
                    solve(i + 1);
                    swap(nums[i], nums[j]);
                    visited.insert(nums[j]);
                }
            };
            solve(0);
            return result;
        }
        vector<vector<int>> permuteUnique2(vector<int> &nums)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            function<void(size_t, vector<int> &)>
                solve = [&](size_t i, vector<int> &n)
            {
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
        vector<vector<int>> permuteUnique3(vector<int> &nums)
        {
            vector<vector<int>> output;
            function<void(size_t, vector<int> &)> permute = [&](size_t i, vector<int> &n)
            {
                if (i + 1 == n.size())
                {
                    output.push_back(n);
                    return;
                }
                sort(n.begin() + i, n.end());
                for (size_t j = i; j < n.size(); j++)
                {
                    if (j == i || n[j] != n[j - 1])
                    {
                        vector<int> n1(n);
                        swap(n1[i], n1[j]);
                        permute(i + 1, n1);
                    }
                }
            };
            vector<int> nums1(nums);
            permute(0, nums1);
            return output;
        }
        // wrong
        vector<vector<int>> permuteUnique4(vector<int> &nums)
        {
            sort(nums.begin(), nums.end());
            vector<vector<int>> output;
            function<void(size_t)> permute = [&](size_t i)
            {
                print(string(i << 2, ' '), nums);
                if (i + 1 == nums.size())
                {
                    output.push_back(nums);
                    return;
                }
                for (size_t j = i; j < nums.size(); j++)
                {
                    // nums may not be sorted any more after swaps
                    // nums[j] may be the same as nums[i]
                    if (j == i || nums[j] != nums[j - 1])
                    {
                        swap(nums[i], nums[j]);
                        permute(i + 1);
                        swap(nums[i], nums[j]);
                    }
                }
            };
            permute(0);
            return output;
        }

        // 48. Rotate Image
        // You are given an n x n 2D matrix representing an image. Rotate the image
        // by 90 degrees (clockwise). Note: You have to rotate the image in-place, which
        // means you have to modify the input 2D matrix directly. DO NOT allocate
        // another 2D matrix and do the rotation. Example 1: Given input matrix =
        // [
        //   [1,2,3],
        //   [4,5,6],
        //   [7,8,9]
        // ],
        // rotate the input matrix in-place such that it becomes:
        // [
        //   [7,4,1],
        //   [8,5,2],
        //   [9,6,3]
        // ]
        // Example 2: Given input matrix =
        // [
        //   [ 5, 1, 9,11],
        //   [ 2, 4, 8,10],
        //   [13, 3, 6, 7],
        //   [15,14,12,16]
        // ],
        // rotate the input matrix in-place such that it becomes:
        // [
        //   [15,13, 2, 5],
        //   [14, 3, 4, 1],
        //   [12, 6, 8, 9],
        //   [16, 7,10,11]
        // ]
        void rotate(vector<vector<int>> &matrix)
        {
            // Swap up-right with bottom-left
            for (size_t i = 1; i < matrix.size(); i++)
            {
                for (size_t j = 0; j < i; j++)
                    swap(matrix[i][j], matrix[j][i]);
            }
            size_t n = matrix[0].size();
            size_t c = n >> 1;
            // Swap left with right
            for (size_t i = 0; i < matrix.size(); i++)
            {
                for (size_t j = 0; j < c; j++)
                {
                    swap(matrix[i][j], matrix[i][n - 1 - j]);
                }
            }
        }
        void rotate2(vector<vector<int>> &matrix)
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

        // 49. Group Anagrams
        // Given an array of strings, group anagrams together.
        // Example:
        // Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
        // Output:
        // [
        //   ["ate","eat","tea"],
        //   ["nat","tan"],
        //   ["bat"]
        // ]
        // Note: All inputs will be in lowercase. The order of your output does not
        // matter.
        vector<vector<string>> groupAnagrams(const vector<string> &strs)
        {
            map<string, vector<size_t>> m;
            for (size_t i = 0; i < strs.size(); i++)
            {
                string s(strs[i]);
                sort(s.begin(), s.end());
                if (m.find(s) == m.end())
                    m[s] = {i};
                else
                    m[s].push_back(i);
            }
            vector<vector<string>> result;
            for (auto it = m.begin(); it != m.end(); it++)
            {
                vector<string> v;
                for (size_t i = 0; i < it->second.size(); i++)
                    v.push_back(strs[it->second[i]]);
                result.push_back(v);
            }
            return result;
        }
        vector<vector<string>> groupAnagrams2(const vector<string> &strs)
        {
            vector<vector<string>> result = vector<vector<string>>{};
            map<string, vector<string>> m = map<string, vector<string>>{};
            for_each(strs.begin(), strs.end(), [&](const string &s)
                     {
                         string k(s);
                         sort(k.begin(), k.end());
                         if (m.find(k) == m.end())
                             m[k] = vector<string>{};
                         m[k].push_back(s); });
            for (map<string, vector<string>>::iterator it = m.begin(); it != m.end();
                 it++)
            {
                result.push_back(it->second);
            }
            return result;
        }

        // 50. Pow(x, n)
        // Implement pow(x, n), which calculates x raised to the power n (x^n).
        // Example 1:
        // Input: 2.00000, 10
        // Output: 1024.00000
        // Example 2:
        // Input: 2.10000, 3
        // Output: 9.26100
        // Example 3:
        // Input: 2.00000, -2
        // Output: 0.25000
        // Explanation: 2^(-2) = 1/(2^2) = 1/4 = 0.25
        // Note:
        // -100.0 < x < 100.0
        // n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]
        // Keep dividing n by 2 and get the remainder r (0 or 1)
        // then there is a sequence:
        // n n_1 n_2 n_3 n_4 ...... n_k (= 0)
        //   r_1 r_2 r_3 r_4 ...... r_k (= 0)
        // The bits of n are {r_k, ..., r_2, r_1}
        // x^n = x^{r_1} * (x^2)^{n_1}
        //     = x^{r_1} * (x^2)^{r_2} * (x^4)^{n_2}
        //     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{n_3}
        //     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{r_4} * (x^16)^{n_4}
        //     ......
        //     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{r_4} * (x^16)^{r_5} ......
        //     * (x^{2^(k-1)})^{r_(k-1)} * (x^{2^k})^{n_k}
        double myPow(double x, int n)
        {
            double y = 1;
            bool negative = false;
            if (n < 0)
            {
                negative = true;
                if (n == INT_MIN)
                {
                    y = x;
                    n = -(n + 1);
                }
                else
                {
                    n = -n;
                }
            }
            while (n > 0)
            {
                if ((n & 0x1) > 0)
                {
                    y *= x;
                }
                n = n >> 1;
                x *= x;
            }
            return negative ? 1 / y : y;
        }
        double myPow2(double x, int n)
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
        double myPow3(double x, int n)
        {
            if (x == 0)
                return 0;
            if (n == 0)
                return 1;
            long long n1 = n;
            bool negative = n1 < 0;
            if (negative)
                n1 = -n1;
            double m = x;
            double p = (n1 & 0x1) == 1 ? x : 1;
            n1 = n1 >> 1;
            while (n1 > 0)
            {
                m = m * m;
                if ((n1 & 0x1) == 1)
                {
                    p = p * m;
                }
                n1 = n1 >> 1;
            }
            if (negative)
                p = 1 / p;
            return p;
        }
        double myPow4(double x, int n)
        {
            if (x == 0)
                return 0;
            if (n == 0)
                return 1;
            long long n1 = n;
            bool negative = n1 < 0;
            if (negative)
                n1 = -n1;
            double m = x;
            double p = 1;
            while (n1 > 0)
            {
                if ((n1 & 0x1) == 1)
                {
                    p = p * m;
                }
                m = m * m;
                n1 = n1 >> 1;
            }
            if (negative)
                p = 1 / p;
            return p;
        }
        double myPow5(double x, int n)
        {
            if (x == 0)
                return 0;
            if (n == 0)
                return 1;
            long long n1 = n;
            bool negative = n1 < 0;
            if (negative)
                n1 = -n1;
            double p = (n1 & 0x1) == 1 ? x : 1;
            p = p * myPow5(x * x, n1 >> 1);
            if (negative)
                p = 1 / p;
            return p;
        }
        double myPow6(double x, int n)
        {
            if (x == 0)
                return 0;
            map<int, double> m;
            function<double(int)> p = [&](int k) -> double
            {
                if (m.find(k) != m.end())
                    return m[k];
                if (k == 0)
                    m[k] = 1;
                else if (k == 1)
                    m[k] = x;
                else
                {
                    m[k] = p(k >> 1) * p(k >> 1);
                    if ((k & 0x1) == 1)
                        m[k] *= x;
                }
                return m[k];
            };
            if (n >= 0)
                return p(n);
            if (n == INT_MIN)
                return 1 / (x * p(INT_MAX));
            return 1 / p(-n);
        }

        // 51. N-Queens
        // The n-queens puzzle is the problem of placing n queens on an n×n chessboard
        // such that no two queens attack each other. Given an integer n, return all
        // distinct solutions to the n-queens puzzle. Each solution contains a distinct
        // board configuration of the n-queens' placement, where 'Q' and '.' both
        // indicate a queen and an empty space respectively.
        // Example:
        // Input: 4
        // Output: [
        //  [".Q..",  // Solution 1
        //   "...Q",
        //   "Q...",
        //   "..Q."],
        //  ["..Q.",  // Solution 2
        //   "Q...",
        //   "...Q",
        //   ".Q.."]
        // ]
        // Explanation: There exist two distinct solutions to the 4-queens puzzle as
        // shown above.
        vector<vector<string>> solveNQueens(int n)
        {
            vector<vector<string>> result;
            function<void(int, vector<string> &)>
                solve = [&](int i, vector<string> &b)
            {
                if (i == n)
                {
                    result.push_back(b);
                    return;
                }
                for (int j = 0; j < n; j++)
                {
                    bool ok = true;
                    for (int k = i - 1; k >= 0; k--)
                    {
                        if (j - (i - k) >= 0 && b[k][j - (i - k)] == 'Q')
                        {
                            ok = false;
                            break;
                        }
                        if (b[k][j] == 'Q')
                        {
                            ok = false;
                            break;
                        }
                        if (j + (i - k) < n && b[k][j + (i - k)] == 'Q')
                        {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok)
                        continue;
                    b[i][j] = 'Q';
                    solve(i + 1, b);
                    b[i][j] = '.';
                }
            };
            vector<string> board(n, string(n, '.'));
            solve(0, board);
            return result;
        }
        vector<vector<string>> solveNQueens2(int n)
        {
            if (n <= 0)
                return vector<vector<string>>{};
            function<void(vector<string> &, int, vector<vector<string>> &)> solve =
                [&](vector<string> &board, size_t line,
                    vector<vector<string>> &solutions)
            {
                for (size_t i = 0; i < board[line].size(); i++)
                {
                    if (board[line][i] == '.')
                    {
                        vector<string> next(board);
                        next[line][i] = 'Q';
                        if (line == board.size() - 1)
                        {
                            for_each(next.begin(), next.end(), [&](string &l)
                                     {
                                         for (size_t j = 0; j < l.length(); j++)
                                         {
                                             if (l[j] == 'X')
                                                 l[j] = '.';
                                         } });
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
        // (-7,0)
        // (-6,0)
        // (-5,0)
        // (-4,0)
        // (-3,0)
        // (-2,0)
        // (-1,0)
        //  (0,0) (0,1) (0,2) (0,3) (0,4) (0,5) (0,6) (0,7) (0,8) (0,9) (0,10) (0,11) (0,12) (0,13) (0,14)
        //  (1,0) (1,1) (1,2) (1,3) (1,4) (1,5) (1,6) (1,7)
        //  (2,0) (2,1) (2,2) (2,3) (2,4) (2,5) (2,6) (2,7)
        //  (3,0) (3,1) (3,2) (3,3) (3,4) (3,5) (3,6) (3,7)
        //  (4,0) (4,1) (4,2) (4,3) (4,4) (4,5) (4,6) (4,7)
        //  (5,0) (5,1) (5,2) (5,3) (5,4) (5,5) (5,6) (5,7)
        //  (6,0) (6,1) (6,2) (6,3) (6,4) (6,5) (6,6) (6,7)
        //  (7,0) (7,1) (7,2) (7,3) (7,4) (7,5) (7,6) (7,7)
        vector<vector<string>> solveNQueens3(int n)
        {
            vector<vector<string>> output;
            vector<bool> column(n, false); // whether column j is occupied
            // diag from up-left to bottom-right
            // (i,j) mapped to i - j + n - 1
            vector<bool> diag1(n + n - 1, false);
            // diag from up-right to bottom-left
            // (i,j) mapped to i + j
            vector<bool> diag2(n + n - 1, false);
            function<void(int, vector<string> &)>
                solve = [&](int i, vector<string> &b)
            {
                if (i == n)
                {
                    output.push_back(b);
                    return;
                }
                for (int j = 0; j < n; j++)
                {
                    if (column[j])
                        continue;
                    int d1 = i - j + n - 1;
                    if (diag1[d1])
                        continue;
                    int d2 = i + j;
                    if (diag2[d2])
                        continue;
                    column[j] = true;
                    diag1[d1] = true;
                    diag2[d2] = true;
                    b[i][j] = 'Q';
                    solve(i + 1, b);
                    b[i][j] = '.';
                    column[j] = false;
                    diag1[d1] = false;
                    diag2[d2] = false;
                }
            };
            vector<string> board(n, string(n, '.'));
            solve(0, board);
            return output;
        }
        vector<vector<string>> solveNQueens4(int n)
        {
            vector<vector<string>> output;
            vector<bool> column(n, false);
            vector<bool> diag1(n + n - 1, false);
            vector<bool> diag2(n + n - 1, false);
            stack<pair<int, int>> s;
            int i = 0;
            int j = 0;
            vector<string> board(n, string(n, '.'));
            while (true)
            {
                if (0 <= i && i < n && 0 <= j && j < n && !column[j] && !diag1[i - j + n - 1] && !diag2[i + j])
                {
                    board[i][j] = 'Q';
                    s.push(make_pair(i, j));
                    column[j] = true;
                    diag1[i - j + n - 1] = true;
                    diag2[i + j] = true;
                    i++;
                    j = 0;
                }
                else
                {
                    if (i == n || j >= n - 1)
                    {
                        if (i == n)
                        {
                            output.push_back(board);
                        }
                        if (s.empty())
                            break;
                        i = s.top().first;
                        j = s.top().second;
                        s.pop();
                        board[i][j] = '.';
                        column[j] = false;
                        diag1[i - j + n - 1] = false;
                        diag2[i + j] = false;
                    }
                    j++;
                }
            }
            return output;
        }

        // 52. N-Queens II
        // The n-queens puzzle is the problem of placing n queens on an n×n chessboard
        // such that no two queens attack each other. Given an integer n, return the
        // number of distinct solutions to the n-queens puzzle.
        // Example:
        // Input: 4
        // Output: 2
        // Explanation: There are two distinct solutions to the 4-queens puzzle as shown
        // below.
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
        int totalNQueens(int n)
        {
            if (n <= 0)
                return 0;
            int count = 0;
            vector<int> b(n, 0); // b[i] = j if (i,j) is a valid position
            function<void(int)> solve = [&](int i)
            {
                if (i == n)
                {
                    count++;
                    return;
                }
                for (int j = 0; j < n; j++)
                {
                    bool ok = true;
                    for (int k = i - 1; k >= 0; k--)
                    {
                        if ((j - (i - k) >= 0 && b[k] == (j - (i - k))) || b[k] == j ||
                            (j + (i - k) < n && b[k] == (j + (i - k))))
                        {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok)
                        continue;
                    b[i] = j;
                    solve(i + 1);
                    b[i] = 0;
                }
            };
            solve(0);
            return count;
        }
        int totalNQueens2(int n)
        {
            if (n <= 0)
                return 0;
            function<int(vector<vector<bool>> &, int)> count =
                [&](vector<vector<bool>> &board, int line) -> int
            {
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

        // 53. Maximum Subarray
        // Given an integer array nums, find the contiguous subarray (containing at
        // least one number) which has the largest sum and return its sum.
        // Example:
        // Input: [-2,1,-3,4,-1,2,1,-5,4],
        // Output: 6
        // Explanation: [4,-1,2,1] has the largest sum = 6.
        // Follow up:
        // If you have figured out the O(n) solution, try coding another solution
        // using the divide and conquer approach, which is more subtle.
        int maxSubArray(const vector<int> &nums)
        {
            long long maxSubSum = INT_MIN;
            long long minSum = 0;
            long long sum = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                sum += nums[i];
                maxSubSum = max(maxSubSum, sum - minSum);
                minSum = min(minSum, sum);
            }
            return (int)maxSubSum; // may overflow
        }
        int maxSubArray2(const vector<int> &nums)
        {
            // Another option could be to init minSum and sum to nums[0]
            // and loop start at 1. (No, this does not work, e.g. {1, 2})
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
        int maxSubArray2(const vector<int> &nums, int &begin, int &end)
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
        int maxSubArray3(const vector<int> &nums, int &begin, int &end)
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
                    // Current element is positive and the current sum is larger than
                    // the last one. Update the last seen maximum sum
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

        // 54. Spiral Matrix
        // Given a matrix of m x n elements (m rows, n columns), return all elements
        // of the matrix in spiral order.
        // Example 1:
        // Input:
        // [
        //  [ 1, 2, 3 ],
        //  [ 4, 5, 6 ],
        //  [ 7, 8, 9 ]
        // ]
        // Output: [1,2,3,6,9,8,7,4,5]
        // Example 2:
        // Input:
        // [
        //   [1, 2, 3, 4],
        //   [5, 6, 7, 8],
        //   [9,10,11,12]
        // ]
        // Output: [1,2,3,4,8,12,11,10,9,5,6,7]
        vector<int> spiralOrder(const vector<vector<int>> &matrix)
        {
            vector<int> result;
            int d = 0;
            int r = matrix.size();
            int c = matrix.empty() ? 0 : matrix[0].size();
            int i = 0;
            int j = -1;
            while (r > 0 && c > 0)
            {
                if (d == 0)
                {
                    for (int k = 1; k <= c; k++)
                        result.push_back(matrix[i][j + k]);
                    j += c;
                    r--;
                }
                else if (d == 1)
                {
                    for (int k = 1; k <= r; k++)
                        result.push_back(matrix[i + k][j]);
                    i += r;
                    c--;
                }
                else if (d == 2)
                {
                    for (int k = 1; k <= c; k++)
                        result.push_back(matrix[i][j - k]);
                    j -= c;
                    r--;
                }
                else
                {
                    for (int k = 1; k <= r; k++)
                        result.push_back(matrix[i - k][j]);
                    i -= r;
                    c--;
                }
                d = (d + 1) % 4;
            }
            return result;
        }
        vector<int> spiralOrder2(const vector<vector<int>> &matrix)
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
        vector<int> spiralOrder3(const vector<vector<int>> &matrix)
        {
            vector<int> o;
            if (matrix.empty() || matrix[0].empty())
                return o;
            int m = matrix.size();
            int n = matrix[0].size();
            int i = 0;
            int j = -1;
            while (m > 0 || n > 0)
            {
                for (int k = 0; k < n; k++)
                    o.push_back(matrix[i][++j]);
                m--;
                if (m == 0)
                    break;
                for (int k = 0; k < m; k++)
                    o.push_back(matrix[++i][j]);
                n--;
                if (n == 0)
                    break;
                for (int k = 0; k < n; k++)
                    o.push_back(matrix[i][--j]);
                m--;
                if (m == 0)
                    break;
                for (int k = 0; k < m; k++)
                    o.push_back(matrix[--i][j]);
                n--;
                if (n == 0)
                    break;
            }
            return o;
        }
        vector<int> spiralOrder4(const vector<vector<int>> &matrix)
        {
            vector<int> result = vector<int>{};
            if (matrix.empty() || matrix[0].empty())
                return result;
            function<void(int, int, int, int)> solve = [&](int i, int j, int m, int n)
            {
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

        // 55. Jump Game
        // Given an array of non-negative integers, you are initially positioned at
        // the first index of the array. Each element in the array represents your
        // maximum jump length at that position. Determine if you are able to reach
        // the last index.
        // Example 1:
        // Input: [2,3,1,1,4]
        // Output: true
        // Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
        // Example 2:
        // Input: [3,2,1,0,4]
        // Output: false
        // Explanation: You will always arrive at index 3 no matter what. Its maximum
        // jump length is 0, which makes it impossible to reach the last index.
        bool canJump(const vector<int> &nums)
        {
            size_t i = 0;
            size_t h = nums[0];
            // loop ensure we stop at the first i where able to reach the end
            while (i < nums.size() && i <= h && h + 1 < nums.size())
            {
                h = max(h, i + nums[i]);
                i++;
            }
            return h + 1 >= nums.size();
        }
        bool canJump2(const vector<int> &nums)
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

        // 56. Merge Intervals
        // Given a collection of intervals, merge all overlapping intervals.
        // Example 1:
        // Input: [[1,3],[2,6],[8,10],[15,18]]
        // Output: [[1,6],[8,10],[15,18]]
        // Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
        // Example 2:
        // Input: [[1,4],[4,5]]
        // Output: [[1,5]]
        // Explanation: Intervals [1,4] and [4,5] are considered overlapping.
        vector<vector<int>> merge(vector<vector<int>> &intervals)
        {
            vector<vector<int>> result;
            sort(intervals.begin(), intervals.end(),
                 [&](const vector<int> &l, const vector<int> &r) -> bool
                 {
                     if (l[0] == r[0])
                         return l[1] < r[1];
                     return l[0] < r[0];
                 });
            for (size_t i = 0; i < intervals.size(); i++)
            {
                // sort already ensures back()[0] <= intervals[i][1]
                if (!result.empty() && result.back()[1] >= intervals[i][0])
                {
                    result.back()[0] = min(result.back()[0], intervals[i][0]);
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                }
                else
                {
                    result.push_back(intervals[i]);
                }
            }
            return result;
        }
        struct Interval
        {
            int start;
            int end;
            Interval() : start(0), end(0) {}
            Interval(int s, int e) : start(s), end(e) {}
        };
        vector<Interval> merge(vector<Interval> &intervals)
        {
            function<bool(const Interval &, const Interval &)> less =
                [&](const Interval &first, const Interval &second) -> bool
            {
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
        vector<Interval> merge2(vector<Interval> &intervals)
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

        // 57. Insert Interval
        // Given a set of non-overlapping intervals, insert a new interval into
        // the intervals (merge if necessary). You may assume that the intervals
        // were initially sorted according to their start times.
        // Example 1:
        // Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
        // Output: [[1,5],[6,9]]
        // Example 2:
        // Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
        // Output: [[1,2],[3,10],[12,16]]
        // Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
        vector<vector<int>> insert(const vector<vector<int>> &intervals,
                                   const vector<int> &newInterval)
        {
            vector<vector<int>> result;
            int l = 0;
            int h = intervals.size() - 1;
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (intervals[m][1] < newInterval[0])
                {
                    l = m + 1;
                }
                else
                {
                    if (l == m)
                        break;
                    h = m - 1;
                }
            }
            for (int i = 0; i < l; i++)
            {
                result.push_back(intervals[i]);
            }
            result.push_back(newInterval);
            for (int i = l; i < (int)intervals.size(); i++)
            {
                if (result.back()[1] < intervals[i][0])
                {
                    result.push_back(intervals[i]);
                }
                else
                {
                    result.back()[0] = min(result.back()[0], intervals[i][0]);
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                }
            }
            return result;
        }
        vector<vector<int>> insert2(const vector<vector<int>> &intervals, vector<int> &newInterval)
        {
            function<bool(const vector<int> &, const vector<int> &)>
                less = [&](const vector<int> &i, const vector<int> &n) -> bool
            {
                return i[1] < n[0];
            };
            auto l = lower_bound(intervals.begin(), intervals.end(), newInterval, less);
            auto u = upper_bound(intervals.begin(), intervals.end(), newInterval, less);
            vector<vector<int>> output;
            auto it = intervals.begin();
            while (it != l)
            {
                output.push_back(*it);
                it++;
            }
            while (it != u)
            {
                newInterval[0] = min(newInterval[0], (*it)[0]);
                newInterval[1] = max(newInterval[1], (*it)[1]);
                it++;
            }
            output.push_back(newInterval);
            while (it != intervals.end())
            {
                output.push_back(*it);
                it++;
            }
            return output;
        }
        vector<Interval> InsertMergeSortedInterval(vector<Interval> &intervals,
                                                   Interval newInterval)
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
        // Given a set of non-overlapping NON-SORTED intervals, insert a new interval
        // into the intervals (merge if necessary). Example 1: Given intervals
        // [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9]. Example 2: Given
        // [1,2],[3,5], [6,7],[8,10],[12,16], insert and merge [4,9] in as
        // [1,2],[3,10],[12,16]. This is because the new interval [4,9] overlaps with
        // [3,5],[6,7],[8,10].
        static vector<Interval> InsertMergeInterval(vector<Interval> &intervals,
                                                    Interval newInterval)
        {
            vector<Interval> output;
            for_each(intervals.begin(), intervals.end(), [&](Interval i)
                     {
                         if (i.end < newInterval.start || newInterval.end < i.start)
                         {
                             output.push_back(i);
                         }
                         else
                         {
                             newInterval.start = min(newInterval.start, i.start);
                             newInterval.end = max(newInterval.end, i.end);
                         } });
            output.push_back(newInterval);
            return output;
        }

        // 58. Length of Last Word
        // Given a string s consists of upper/lower-case alphabets and empty space
        // characters ' ', return the length of last word (last word means the last
        // appearing word if we loop from left to right) in the string. If the last
        // word does not exist, return 0.
        // Note: A word is defined as a maximal substring consisting of non-space
        // characters only.
        // Example:
        // Input: "Hello World"
        // Output: 5
        int lengthOfLastWord(const string &s)
        {
            int i = s.size() - 1;
            while (i >= 0 && s[i] == ' ')
                i--;
            int j = 0;
            while (i >= 0 && s[i] != ' ')
            {
                i--;
                j++;
            }
            return j;
        }
        int lengthOfLastWord2(const string &s)
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
        int lengthOfLastWord3(const char *s)
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
        int lengthOfLastWord4(const string &s)
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

        // 59. Spiral Matrix II
        // Given a positive integer n, generate a square matrix filled with elements
        // from 1 to n^2 in spiral order.
        // Example:
        // Input: 3
        // Output:
        // [
        //  [ 1, 2, 3 ],
        //  [ 8, 9, 4 ],
        //  [ 7, 6, 5 ]
        // ]
        vector<vector<int>> generateMatrix(int n)
        {
            vector<vector<int>> m(n, vector<int>(n, 0));
            int r = n;
            int c = n;
            int e = 1;
            int i = 0;
            int j = -1;
            while (r > 0 && c > 0)
            {
                for (int k = 1; k <= c; k++)
                    m[i][j + k] = e++;
                j += c;
                r--;
                if (r == 0)
                    break;
                for (int k = 1; k <= r; k++)
                    m[i + k][j] = e++;
                i += r;
                c--;
                if (c == 0)
                    break;
                for (int k = 1; k <= c; k++)
                    m[i][j - k] = e++;
                j -= c;
                r--;
                if (r == 0)
                    break;
                for (int k = 1; k <= r; k++)
                    m[i - k][j] = e++;
                i -= r;
                c--;
                if (c == 0)
                    break;
            }
            return m;
        }
        vector<vector<int>> generateMatrix2(int n)
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
        vector<vector<int>> generateMatrix3(int n)
        {
            vector<vector<int>> m(n, vector<int>(n, 0));
            function<int(int, int, int, int, int)> generate =
                [&](int v, int i, int j, int r, int c) -> int
            {
                for (int k = 0; k < c; k++)
                    m[i][j + k] = v++;
                r--;
                if (r == 0)
                    return v;
                for (int k = 1; k <= r; k++)
                    m[i + k][j + c - 1] = v++;
                c--;
                if (c == 0)
                    return v;
                for (int k = c - 1; k >= 0; k--)
                    m[i + r][j + k] = v++;
                r--;
                for (int k = r; k >= 1; k--)
                    m[i + k][j] = v++;
                return v;
            };
            int r = n;
            int c = n;
            int i = 0;
            int j = 0;
            int v = 1;
            while (r > 0 && c > 0)
            {
                v = generate(v, i, j, r, c);
                i++;
                j++;
                r -= 2;
                c -= 2;
            }
            return m;
        }

        // 60. Permutation Sequence
        // The set [1,2,3,...,n] contains a total of n! unique permutations.
        // By listing and labeling all of the permutations in order, we get the
        // following sequence for n = 3:
        // 1    "123"
        // 2    "132"
        // 3    "213"
        // 4    "231"
        // 5    "312"
        // 6    "321"
        // Given n and k, return the k-th permutation sequence. Note:
        // Given n will be between 1 and 9 inclusive.
        // Given k will be between 1 and n! inclusive.
        // Example 1:
        // Input: n = 3, k = 3
        // Output: "213"
        // Example 2:
        // Input: n = 4, k = 9
        // Output: "2314"
        //   i  1  2  3  4  5  6  7  8  9
        //   f  8! 7! 6! 5! 4! 3! 2! 1! 0!
        // k
        // 1    1  2  3  4  5  6  7  8  9
        // 2    1  2  3  4  5  6  7  9  8
        // 3    1  2  3  4  5  6  8  7  9
        // 4    1  2  3  4  5  6  8  9  7
        //      ......
        //      2  1  3  4  5  6  7  8  9
        //      ......
        //      3  1  2  4  5  6  7  8  9
        //      ......
        //      9  1  2  3  4  5  6  7  8
        //      ......
        //      9  8  7  6  5  4  3  2  1
        // At postion i = 1, there are 9 ranges and each range has 8! entries.
        string getPermutation(int n, int k)
        {
            // f = (n - 1)!
            long long f = 1;
            for (int i = 1; i < n; i++)
                f *= i;
            vector<int> d(n, 0);
            k--; // Make k a 0-based index
            for (int i = 0; i < n - 1; i++)
            {
                d[i] = k / f; // distance to the right of i where to find the digit to swap with i
                k = k - (d[i] * f);
                f = f / (n - 1 - i);
            }
            string s;
            for (int i = 1; i <= n; i++)
                s.append(1, '0' + i);
            for (int i = 0; i < n; i++)
            {
                if (d[i] > 0)
                {
                    char c = s[i + d[i]];
                    s.erase(s.begin() + i + d[i]);
                    s.insert(s.begin() + i, c);
                }
            }
            return s;
        }
        string getPermutation2(int n, int k)
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

        // 61. Rotate List
        // Given a linked list, rotate the list to the right by k places,
        // where k is non-negative.
        // Example 1:
        // Input: 1->2->3->4->5->NULL, k = 2
        // Output: 4->5->1->2->3->NULL
        // Explanation:
        // rotate 1 steps to the right: 5->1->2->3->4->NULL
        // rotate 2 steps to the right: 4->5->1->2->3->NULL
        // Example 2:
        // Input: 0->1->2->NULL, k = 4
        // Output: 2->0->1->NULL
        // Explanation:
        // rotate 1 steps to the right: 2->0->1->NULL
        // rotate 2 steps to the right: 1->2->0->NULL
        // rotate 3 steps to the right: 0->1->2->NULL
        // rotate 4 steps to the right: 2->0->1->NULL
        ListNode *rotateRight(ListNode *head, int k)
        {
            if (head == nullptr)
                return head;
            ListNode *q = head;
            int i = 0;
            while (i < k)
            {
                q = q->next;
                i++; // q is i-th node (0 based)
                if (q == nullptr)
                {
                    k %= i;
                    q = head;
                    i = 0;
                }
            }
            if (k == 0)
                return head;
            ListNode *p = head;
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
        ListNode *rotateRight2(ListNode *head, int k)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *p = head;
            int i = 1;
            while (i <= k)
            {
                if (p->next == nullptr)
                {
                    k %= i;
                    p = head;
                    i = 1;
                }
                else
                {
                    p = p->next;
                    i++;
                }
            }
            if (p == head)
                return head;
            ListNode *q = p;
            p = head;
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
        ListNode *rotateRight3(ListNode *head, int k)
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
        ListNode *rotateRight4(ListNode *head, int k)
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

        // 62. Unique Paths
        // A robot is located at the top-left corner of a m x n grid (marked 'Start' in
        // the diagram below). The robot can only move either down or right at any point
        // in time. The robot is trying to reach the bottom-right corner of the grid
        // (marked 'Finish' in the diagram below). How many possible unique paths are
        // there? Above is a 7 x 3 grid. How many possible unique paths are there? Note:
        // m and n will be at most 100. Example 1: Input: m = 3, n = 2 Output: 3
        // Explanation:
        // From the top-left corner, there are a total of 3 ways to reach the
        // bottom-right corner:
        // 1. Right -> Right -> Down
        // 2. Right -> Down -> Right
        // 3. Down -> Right -> Right
        // Example 2:
        // Input: m = 7, n = 3
        // Output: 28
        // sum[i][j] = sum[i+1][j] + sum[i][j+1]
        int uniquePaths(int m, int n)
        {
            if (m <= 0 || n <= 0)
                return 0;
            vector<int> p(n, 1);
            for (int i = m - 2; i >= 0; i--)
            {
                for (int j = n - 2; j >= 0; j--)
                    p[j] += p[j + 1];
            }
            return p[0];
        }
        int uniquePaths2(int m, int n)
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
        // A robot is located at the top-left corner of a m x n grid (marked 'Start'
        // in the diagram below). The robot can only move either down or right at any
        // point in time. The robot is trying to reach the bottom-right corner of the
        // grid (marked 'Finish' in the diagram below). Now consider if some obstacles
        // are added to the grids. How many unique paths would there be?
        // An obstacle and empty space is marked as 1 and 0 respectively in the grid.
        // Note: m and n will be at most 100.
        // Example 1:
        // Input:
        // [
        //   [0,0,0],
        //   [0,1,0],
        //   [0,0,0]
        // ]
        // Output: 2
        // Explanation:
        // There is one obstacle in the middle of the 3x3 grid above.
        // There are two ways to reach the bottom-right corner:
        // 1. Right -> Right -> Down -> Down
        // 2. Down -> Down -> Right -> Right
        int uniquePathsWithObstacles(const vector<vector<int>> &obstacleGrid)
        {
            if (obstacleGrid.empty() || obstacleGrid[0].empty())
                return 0;
            int m = obstacleGrid.size();
            int n = obstacleGrid[0].size();
            vector<long long> p(n, 0); // long long to avoid overflow
            for (int j = n - 1; j >= 0; j--)
            {
                if (obstacleGrid[m - 1][j] == 1)
                    p[j] = 0;
                else if (j == n - 1)
                    p[j] = 1;
                else
                    p[j] = p[j + 1];
            }
            for (int i = m - 2; i >= 0; i--)
            {
                if (obstacleGrid[i][n - 1] == 1)
                    p[n - 1] = 0;
                for (int j = n - 2; j >= 0; j--)
                {
                    if (obstacleGrid[i][j] == 1)
                        p[j] = 0;
                    else
                        p[j] += p[j + 1];
                }
            }
            return p[0];
        }
        int uniquePathsWithObstacles2(const vector<vector<int>> &obstacleGrid)
        {
            int m = obstacleGrid.size();
            if (m == 0)
                return 0;
            int n = obstacleGrid[0].size();
            if (n == 0)
                return 0;
            vector<vector<long long>> grid(m, vector<long long>(n, 0));
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
                    grid[i][j] = (obstacleGrid[i][j] == 0)
                                     ? (grid[i + 1][j] + grid[i][j + 1])
                                     : 0;
                }
            }
            return grid[0][0];
        }

        // 64. Minimum Path Sum
        // Given a m x n grid filled with non-negative numbers, find a path from top
        // left to bottom right which minimizes the sum of all numbers along its path.
        // Note: You can only move either down or right at any point in time.
        // Example:
        // Input:
        // [
        //   [1,3,1],
        //   [1,5,1],
        //   [4,2,1]
        // ]
        // Output: 7
        // Explanation: Because the path 1->3->1->1->1 minimizes the sum.
        // Note: Greedy search does not work here. e.g.,
        // [[1, 3,   0]
        //  [2, 100, 0]
        //  [1, 1,   1]]
        int minPathSum(const vector<vector<int>> &grid)
        {
            if (grid.empty() || grid[0].empty())
                return 0;
            int m = grid.size();
            int n = grid[0].size();
            vector<int> s(1, grid[0][0]);
            for (int j = 1; j < n; j++)
                s.push_back(s[j - 1] + grid[0][j]);
            for (int i = 1; i < m; i++)
            {
                s[0] += grid[i][0];
                for (int j = 1; j < n; j++)
                    s[j] = grid[i][j] + min(s[j - 1], s[j]);
            }
            return s[n - 1];
        }
        int minPathSum2(const vector<vector<int>> &grid)
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

        // 65. Valid Number
        // Validate if a given string can be interpreted as a decimal number.
        // Some examples:
        // "0" => true
        // " 0.1 " => true
        // "abc" => false
        // "1 a" => false
        // "2e10" => true
        // " -90e3   " => true
        // " 1e" => false
        // "e3" => false
        // " 6e-1" => true
        // " 99e2.5 " => false
        // "53.5e93" => true
        // " --6 " => false
        // "-+3" => false
        // "95a54e53" => false
        bool isNumber(const string &s)
        {
            int b = 0;
            while (b < (int)s.size() && s[b] == ' ')
                b++;
            if (b >= (int)s.size())
                return false;
            int e = s.size() - 1;
            while (e >= 0 && s[e] == ' ')
                e--;
            if (e < 0)
                return false;
            bool foundDigit = false;
            bool foundSign = false;
            bool foundE = false;
            bool foundPoint = false;
            for (int i = b; i <= e; i++)
            {
                if (s[i] == '+' || s[i] == '-')
                {
                    if (foundSign)
                        return false;
                    if (foundDigit)
                        return false;
                    if (foundPoint)
                        return false;
                    foundSign = true;
                }
                else if ('0' <= s[i] && s[i] <= '9')
                {
                    foundDigit = true;
                }
                else if (s[i] == 'e')
                {
                    if (foundE)
                        return false;
                    if (!foundDigit)
                        return false;
                    foundE = true;
                    foundSign = false;
                    foundPoint = false;
                    foundDigit = false;
                }
                else if (s[i] == '.')
                {
                    if (foundPoint)
                        return false;
                    if (foundE)
                        return false;
                    foundPoint = true;
                }
                else
                {
                    return false;
                }
            }
            return foundDigit;
        }
        bool isNumber(const char *s)
        {
            if (s == nullptr || *s == '\0')
                return false;
            while (*s == ' ')
                s++;
            if (*s == '\0')
                return false;
            if (*s != '+' && *s != '-' && *s != '.' && (*s < '0' || *s > '9'))
                return false;
            if ((*s == '+' || *s == '-') && *(s + 1) == '.' &&
                (*(s + 2) == '\0' || *(s + 2) == ' '))
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
                    if (*(s + 1) != '\0' && *(s + 1) != ' ' && *(s + 1) != 'e' &&
                        *(s + 1) != 'E' && (*(s + 1) < '0' || *(s + 1) > '9'))
                        return false;
                    break;
                case 'e':
                case 'E':
                    if (foundE)
                        return false;
                    foundE = true;
                    if (*(s - 1) != '.' && (*(s - 1) < '0' || *(s - 1) > '9'))
                        return false;
                    if (*(s + 1) != '+' && *(s + 1) != '-' &&
                        (*(s + 1) < '0' || *(s + 1) > '9'))
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
            return *s == '\0';
        }

        // 66. Plus One
        // Given a non-empty array of digits representing a non-negative integer,
        // plus one to the integer. The digits are stored such that the most significant
        // digit is at the head of the list, and each element in the array contain
        // a single digit. You may assume the integer does not contain any leading zero,
        // except the number 0 itself.
        // Example 1:
        // Input: [1,2,3]
        // Output: [1,2,4]
        // Explanation: The array represents the integer 123.
        // Example 2:
        // Input: [4,3,2,1]
        // Output: [4,3,2,2]
        // Explanation: The array represents the integer 4321.
        vector<int> plusOne(const vector<int> &digits)
        {
            vector<int> v(digits);
            int c = 1;
            for (int i = v.size() - 1; i >= 0 && c > 0; i--)
            {
                v[i] += c;
                if (v[i] >= 10)
                {
                    v[i] -= 10;
                    c = 1;
                }
                else
                {
                    c = 0;
                }
            }
            if (c > 0)
                v.insert(v.begin(), c);
            return v;
        }
        vector<int> plusOne2(const vector<int> &digits)
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

        // 67. Add Binary
        // Given two binary strings, return their sum (also a binary string).
        // The input strings are both non-empty and contains only characters 1 or 0.
        // Example 1:
        // Input: a = "11", b = "1"
        // Output: "100"
        // Example 2:
        // Input: a = "1010", b = "1011"
        // Output: "10101"
        string addBinary(const string &a, const string &b)
        {
            string s;
            int c = 0;
            int i = a.size() - 1;
            int j = b.size() - 1;
            while (i >= 0 || j >= 0 || c > 0)
            {
                int d = c;
                if (i >= 0)
                    d += (a[i--] - '0');
                if (j >= 0)
                    d += (b[j--] - '0');
                if (d >= 2)
                {
                    d -= 2;
                    c = 1;
                }
                else
                {
                    c = 0;
                }
                s.insert(s.begin(), '0' + d);
            }
            return s;
        }
        string addBinary2(const string &a, const string &b)
        {
            string result;
            int i = a.length() - 1;
            int j = b.length() - 1;
            int c = 0;
            int d = 0;
            while (i >= 0 || j >= 0)
            {
                if (i >= 0 && j >= 0)
                    d = c + (a[i--] - '0') + (b[j--] - '0');
                else if (i >= 0)
                    d = c + (a[i--] - '0');
                else
                    d = c + (b[j--] - '0');
                if (d == 2 || d == 3)
                    c = 1;
                else
                    c = 0;
                d %= 2;
                result.insert(result.begin(), 1, d + '0');
            }
            if (c == 1)
                result.insert(result.begin(), 1, c + '0');
            return result;
        }
        string addBinary3(const string &a, const string &b)
        {
            if (a.length() == 0)
                return b;
            if (b.length() == 0)
                return a;
            int i = a.length() - 1;
            int j = b.length() - 1;
            int carry = 0;
            string c;
            while (i >= 0 && j >= 0)
            {
                if (a[i] == '0' && b[j] == '0')
                {
                    if (carry == 0)
                    {
                        c.insert(0, 1, '0');
                    }
                    else
                    {
                        c.insert(0, 1, '1');
                        carry = 0;
                    }
                }
                else if ((a[i] == '0' && b[j] == '1') ||
                         (a[i] == '1' && b[j] == '0'))
                {
                    c.insert(0, 1, carry == 0 ? '1' : '0');
                }
                else if (a[i] == '1' && b[j] == '1')
                {
                    if (carry == 0)
                    {
                        c.insert(0, 1, '0');
                        carry = 1;
                    }
                    else
                    {
                        c.insert(0, 1, '1');
                    }
                }
                i--;
                j--;
            }
            while (i >= 0)
            {
                if (carry == 0)
                {
                    c.insert(0, a, 0, i + 1);
                    break;
                }
                else
                {
                    if (a[i] == '0')
                    {
                        c.insert(0, 1, '1');
                        carry = 0;
                    }
                    else
                    {
                        c.insert(0, 1, '0');
                    }
                    i--;
                }
            }
            while (j >= 0)
            {
                if (carry == 0)
                {
                    c.insert(0, b, 0, j + 1);
                    break;
                }
                else
                {
                    if (b[j] == '0')
                    {
                        c.insert(0, 1, '1');
                        carry = 0;
                    }
                    else
                    {
                        c.insert(0, 1, '0');
                    }
                    j--;
                }
            }
            if (carry == 1)
                c.insert(0, 1, '1');
            return c;
        }

        // 68. Text Justification
        // Given an array of words and a width maxWidth, format the text such that each
        // line has exactly maxWidth characters and is fully (left and right) justified.
        // You should pack your words in a greedy approach; that is, pack as many words
        // as you can in each line. Pad extra spaces ' ' when necessary so that each
        // line has exactly maxWidth characters. Extra spaces between words should be
        // distributed as evenly as possible. If the number of spaces on a line do not
        // divide evenly between words, the empty slots on the left will be assigned
        // more spaces than the slots on the right. For the last line of text, it should
        // be left justified and no extra space is inserted between words. Note: A word
        // is defined as a character sequence consisting of non-space characters only.
        // Each word's length is guaranteed to be greater than 0 and not exceed
        // maxWidth. The input array words contains at least one word. Example 1: Input:
        // words = ["This", "is", "an", "example", "of", "text", "justification."]
        // maxWidth = 16
        // Output:
        // [
        //    "This    is    an",
        //    "example  of text",
        //    "justification.  "
        // ]
        // Example 2:
        // Input:
        // words = ["What","must","be","acknowledgment","shall","be"]
        // maxWidth = 16
        // Output:
        // [
        //   "What   must   be",
        //   "acknowledgment  ",
        //   "shall be        "
        // ]
        // Explanation: Note that the last line is "shall be    " instead of "shall be",
        // because the last line must be left-justified instead of fully-justified.
        // Note that the second line is also left-justified becase it contains only one
        // word. Example 3: Input: words =
        // ["Science","is","what","we","understand","well","enough","to","explain",
        //          "to","a","computer.","Art","is","everything","else","we","do"]
        // maxWidth = 20
        // Output:
        // [
        //   "Science  is  what we",
        //   "understand      well",
        //   "enough to explain to",
        //   "a  computer.  Art is",
        //   "everything  else  we",
        //   "do                  "
        // ]
        vector<string> fullJustify(const vector<string> &words, int maxWidth)
        {
            vector<string> result;
            size_t i = 0;
            while (i < words.size())
            {
                size_t w = words[i].size();
                size_t j = i + 1;
                while (j < words.size() &&
                       w + words[j].size() + 1 <= (size_t)maxWidth)
                {
                    w += words[j].size() + 1;
                    j++;
                }
                string line;
                if (j == words.size() || i + 1 == j)
                {
                    for (size_t k = i; k < j; k++)
                    {
                        if (k > i)
                            line.append(1, ' ');
                        line.append(words[k].begin(), words[k].end());
                    }
                    line.append(maxWidth - w, ' ');
                }
                else
                {
                    size_t extraSpaces = maxWidth - w;
                    size_t spacesInBetween = 1 + (extraSpaces / (j - i - 1));
                    extraSpaces %= (j - i - 1);
                    for (size_t k = i; k < j; k++)
                    {
                        if (k > i && k <= i + extraSpaces)
                            line.append(spacesInBetween + 1, ' ');
                        else if (k > i + extraSpaces)
                            line.append(spacesInBetween, ' ');
                        line.append(words[k].begin(), words[k].end());
                    }
                }
                result.push_back(line);
                i = j;
            }
            return result;
        }
        vector<string> fullJustify2(const vector<string> &words, int L)
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

        // 69. Sqrt(x)
        // Implement int sqrt(int x).
        // Compute and return the square root of x, where x is guaranteed to be a
        // non-negative integer. Since the return type is an integer, the decimal
        // digits are truncated and only the integer part of the result is returned.
        // Example 1:
        // Input: 4, Output: 2
        // Example 2:
        // Input: 8, Output: 2
        // Explanation: The square root of 8 is 2.82842..., and since the decimal part
        // is truncated, 2 is returned.
        int mySqrt(int x)
        {
            long long l = 0;
            long long h = x;
            while (l < h)
            {
                long long m = l + ((h - l) >> 1);
                long long m2 = m * m;
                if (x < m2)
                    h = m;
                else if (m2 < x)
                    l = m + 1;
                else
                    return m;
            }
            return h * h == x ? h : h - 1;
        }
        int mySqrt2(int x)
        {
            long long l = 0;
            long long h = x;
            while (l + 1 < h)
            {
                long long m = l + ((h - l) >> 1);
                long long m2 = m * m;
                if (x < m2)
                    h = m;
                else if (m2 < x)
                    l = m;
                else
                    return m;
            }
            return h * h == x ? h : l;
        }
        int mySqrt3(int x)
        {
            long long l = 0;
            long long h = x;
            long long m = 0;
            while (l <= h)
            {
                // [l..h] contain possible answers
                m = l + ((h - l) >> 1);
                long long m2 = m * m;
                if (x < m2)
                {
                    h = m - 1; // it is possible h * h <= x
                }
                else if (m2 < x)
                {
                    if (l < m)
                    {
                        l = m;
                    }
                    else
                    {
                        // case 1: l = m = h
                        // case 2: l = m < h (= m + 1)
                        if (m < h && x >= h * h)
                            m = h;
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            return m;
        }
        int mySqrt4(int x)
        {
            long long l = 0;
            long long h = x;
            long long m = 0;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                long long m2 = m * m; // long long to avoid overflow
                if (x < m2)
                {
                    h = m - 1;
                }
                else if (m2 < x)
                {
                    if (x < (m + 1) * (m + 1))
                        break;
                    l = m + 1;
                }
                else
                {
                    break;
                }
            }
            return m;
        }
        int mySqrt5(int x)
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
                    break;
                else if (x < low)
                    r = m - 1;
                else
                    l = m + 1;
            }
            return (int)m;
        }
        int mySqrt6(int x)
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

        // 70. Climbing Stairs
        // You are climbing a stair case. It takes n steps to reach to the top.
        // Each time you can either climb 1 or 2 steps. In how many distinct ways
        // can you climb to the top? Note: Given n will be a positive integer.
        // Example 1:
        // Input: 2
        // Output: 2
        // Explanation: There are two ways to climb to the top.
        // 1. 1 step + 1 step
        // 2. 2 steps
        // Example 2:
        // Input: 3
        // Output: 3
        // Explanation: There are three ways to climb to the top.
        // 1. 1 step + 1 step + 1 step
        // 2. 1 step + 2 steps
        // 3. 2 steps + 1 step
        int climbStairs(int n)
        {
            if (n == 1)
                return 1;
            if (n == 2)
                return 2;
            int a = 1; // at n
            int b = 2; // at n - 1
            int c;
            // c[n-2] = c[n-1] + c[n]
            for (int i = n - 2; i > 0; i--)
            {
                c = b + a;
                a = b;
                b = c;
            }
            return c;
        }
        int climbStairs2(int n)
        {
            if (n == 1)
                return 1;
            if (n == 2)
                return 2;
            int a = 1;
            int b = 2;
            int c;
            // C[n] = C[n - 1] + C[n - 2]
            for (int i = 3; i <= n; i++)
            {
                c = b + a;
                a = b;
                b = c;
            }
            return c;
        }
        int climbStairs3(int n)
        {
            map<int, int> m;
            function<int(int)> f = [&](int k) -> int
            {
                if (m.find(k) == m.end())
                {
                    if (k == 1 || k == 2)
                        m[k] = k;
                    else
                        m[k] = f(k - 1) + f(k - 2);
                }
                return m[k];
            };
            return f(n);
        }

        // 71. Simplify Path
        // Given an absolute path for a file (Unix-style), simplify it.
        // Or in other words, convert it to the canonical path.
        // In a UNIX-style file system, a period . refers to the current directory.
        // Furthermore, a double period .. moves the directory up a level.
        // For more information, see: Absolute path vs relative path in Linux/Unix
        // Note that the returned canonical path must always begin with a slash /,
        // and there must be only a single slash / between two directory names.
        // The last directory name (if it exists) must not end with a trailing /.
        // Also, the canonical path must be the shortest string representing the
        // absolute path. Example 1: Input: "/home/" Output: "/home" Explanation: Note
        // that there is no trailing slash after the last directory name. Example 2:
        // Input: "/../"
        // Output: "/"
        // Explanation: Going one level up from the root directory is a no-op, as the
        // root level is the highest level you can go. Example 3: Input: "/home//foo/"
        // Output: "/home/foo"
        // Explanation: In the canonical path, multiple consecutive slashes are replaced
        // by a single one.
        // Example 4:
        // Input: "/a/./b/../../c/"
        // Output: "/c"
        // Example 5:
        // Input: "/a/../../b/../c//.//"
        // Output: "/c"
        // Example 6:
        // Input: "/a//b////c/d//././/.."
        // Output: "/a/b/c"
        string simplifyPath(string path)
        {
            if (path.empty() || path[0] != '/')
                path.insert(0, 1, '/');
            size_t i = 0;
            size_t j = 0;
            size_t k = 1;
            while (k <= path.size())
            {
                if (k == path.size() || path[k] == '/')
                {
                    if (j + 1 == k)
                    {
                        j = k;
                    }
                    else if (j + 2 == k && path[j + 1] == '.')
                    {
                        j = k;
                    }
                    else if (j + 3 == k && path[j + 1] == '.' && path[j + 2] == '.')
                    {
                        if (i > 0 && path[i] == '/')
                            i--;
                        while (i > 0 && path[i] != '/')
                            i--;
                        j = k;
                    }
                    else if (i == j)
                    {
                        i = k;
                        j = k;
                    }
                    else
                    {
                        if (path[i] != '/')
                            path[++i] = '/';
                        j++;
                        while (j != k)
                            path[++i] = path[j++];
                    }
                }
                k++;
            }
            if (i < path.size())
            {
                if (i > 0 && path[i] == '/')
                    i--;
                path.resize(i + 1);
            }
            return path;
        }
        string simplifyPath2(string path)
        {
            if (path.empty())
                return path;
            if (path[0] != '/')
                path.insert(0, 1, '/');
            size_t i = 0;
            size_t j = 1;
            while (j < path.size())
            {
                // start at current '/' scan characters until next '/'
                while (j < path.size() && path[j] == '/')
                    j++;
                if (j == path.size())
                    break;
                if (path[j] == '.')
                {
                    if (j + 1 == path.size() || path[j + 1] == '/')
                    {
                        j++;
                        continue;
                    }
                    if (j + 1 < path.size() && path[j + 1] == '.')
                    {
                        if (j + 2 == path.size() || path[j + 2] == '/')
                        {
                            j += 2;
                            if (i > 0)
                            {
                                if (path[i] == '/')
                                    i--;
                                while (i > 0 && path[i] != '/')
                                    i--;
                            }
                            continue;
                        }
                    }
                }
                if (path[i] != '/')
                    path[++i] = '/';
                while (j < path.size() && path[j] != '/')
                {
                    i++;
                    if (i < j)
                        path[i] = path[j];
                    j++;
                }
            }
            if (path[i] == '/' && i > 0)
                i--;
            path.resize(i + 1);
            return path;
        }
        string simplifyPath3(string path)
        {
            if (path.empty())
                return path;
            if (path[0] != '/')
                path.insert(0, 1, '/');
            int len = path.length();
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
        string simplifyPath4(string path)
        {
            if (path.empty())
                return path;
            int len = path.length();
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
                for_each(tokens.begin(), tokens.end(), [&](string &t)
                         {
                             output.append(1, '/');
                             output.append(t.begin(), t.end()); });
            }
            return output;
        }

        // 72. Edit Distance
        // Given two words word1 and word2, find the minimum number of operations
        // required to convert word1 to word2. You have the following 3 operations
        // permitted on a word:
        // Insert a character
        // Delete a character
        // Replace a character
        // Example 1:
        // Input: word1 = "horse", word2 = "ros"
        // Output: 3
        // Explanation:
        // horse -> rorse (replace 'h' with 'r')
        // rorse -> rose (remove 'r')
        // rose -> ros (remove 'e')
        // Example 2:
        // Input: word1 = "intention", word2 = "execution"
        // Output: 5
        // Explanation:
        // intention -> inention (remove 't')
        // inention -> enention (replace 'i' with 'e')
        // enention -> exention (replace 'n' with 'x')
        // exention -> exection (replace 'n' with 'c')
        // exection -> execution (insert 'u')
        int minDistance(const string &word1, const string &word2)
        {
            map<pair<size_t, size_t>, int> m;
            function<int(size_t, size_t)> solve = [&](size_t i, size_t j) -> int
            {
                // distance between word1[i..] and word2[j..]
                pair<size_t, size_t> p = make_pair(i, j);
                if (m.find(p) != m.end())
                    return m[p];
                while (i < word1.size() && j < word2.size() && word1[i] == word2[j])
                {
                    i++;
                    j++;
                }
                if (i == word1.size() && j == word2.size())
                {
                    m[p] = 0;
                    return m[p];
                }
                if (i == word1.size())
                {
                    m[p] = word2.size() - j; // Insert
                    return m[p];
                }
                if (j == word2.size())
                {
                    m[p] = word1.size() - i; // Delete
                    return m[p];
                }
                int di = solve(i, j + 1);     // Insert
                int dd = solve(i + 1, j);     // Delete
                int dr = solve(i + 1, j + 1); // Replace
                int d = min(di, min(dd, dr));
                m[p] = d + 1;
                return m[p];
            };
            return solve(0, 0);
        }
        int minDistance2(const string &word1, const string &word2)
        {
            // Compute distance from w1[i:] to w2[j:]
            function<int(const string &, int, const string &, int,
                         map<pair<int, int>, int> &)>
                distance = [&](const string &w1, int i, const string &w2, int j,
                               map<pair<int, int>, int> &d) -> int
            {
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
        // d[i,j] is the distance between w1[i:] and w2[j:]
        //     j 0 1 2 3 ...... n-1
        // i 0
        //   1
        //   2
        //   .
        //   m-1
        //
        // d[m-1][n-1] =
        //     0, if w1[m-1] == w2[n-1]
        //     1, replace if w1[m-1] != w2[n-1]
        // d[m-1][j] =
        //     n - 1 - j, insert to w1 if w1[m-1] == w2[j]
        //     1 + min {                 if w1[m-1] != w2[j]
        //               n - 1 - j,      replace w1[m-1] with w2[j] and insert the rest from w2
        //               d[m-1][j+1] },  insert w2[j] before w1[m-1] and recurse
        // d[i][n-1] =
        //     m - 1 - i, delete from w1 if w1[i] == w2[n-1]
        //     1 + min {                 if w1[i] != w2[n-1]
        //               m - 1 - i,      replace w1[i] with w2[n-1] and delete the rest from w1
        //               d[i+1][n-1] },  delete w1[i] and recurse
        // d[i][j] =
        //     d[i+1][j+1], if w1[i] == w2[j]
        //     1 + min {               if w1[i] != w2[j]
        //               d[i][j+1],    insert w2[j] before w1[i] and recurse
        //               d[i+1][j+1],  replace w1[i] with w2[j] and recurse
        //               d[i+1][j] },  delete w1[i] and recurse
        int minDistance3(const string &word1, const string &word2)
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
        int minDistance4(const string &word1, const string &word2)
        {
            int m = word1.size();
            int n = word2.size();
            if (m == 0)
                return n;
            if (n == 0)
                return m;
            vector<int> d(n, 0);
            d[n - 1] = (word1[m - 1] == word2[n - 1] ? 0 : 1);
            for (int j = n - 2; j >= 0; j--)
            {
                if (word1[m - 1] == word2[j])
                {
                    d[j] = n - 1 - j;
                }
                else
                {
                    d[j] = 1 + min(n - 1 - j, d[j + 1]);
                }
            }
            for (int i = m - 2; i >= 0; i--)
            {
                // i    t = d[i][j]    p = d[i][j+1]
                // i+1  d[i+1][j]      d[i+1][j+1]
                int p = 0;
                if (word1[i] == word2[n - 1])
                {
                    p = m - 1 - i;
                }
                else
                {
                    p = 1 + min(m - 1 - i, d[n - 1]);
                }
                int t = 0;
                for (int j = n - 2; j >= 0; j--)
                {
                    if (word1[i] == word2[j])
                    {
                        t = d[j + 1];
                    }
                    else
                    {
                        t = 1 + min(p, min(d[j + 1], d[j]));
                    }
                    d[j + 1] = p;
                    p = t;
                }
                d[0] = p;
            }
            return d[0];
        }
        // BFS from [0][0] to [m-1][n-1]
        int minDistance5(const string &word1, const string &word2)
        {
            int n1 = (int)word1.size();
            int n2 = (int)word2.size();
            if (n1 == 0)
                return n2;
            if (n2 == 0)
                return n1;
            queue<pair<int, int>> q1, q2;
            set<pair<int, int>> s;
            int i = 0;
            int j = 0;
            auto p = make_pair(i, j);
            q1.push(p);
            s.insert(p);
            int d = 0;
            while (!q1.empty())
            {
                p = q1.front();
                q1.pop();
                i = p.first;
                j = p.second;
                while (i < n1 && j < n2 && word1[i] == word2[j])
                {
                    i++;
                    j++;
                }
                if (i == n1 && j == n2)
                    break;
                if (j + 1 <= n2)
                {
                    p = make_pair(i, j + 1);
                    if (s.find(p) == s.end())
                    {
                        q2.push(p);
                        s.insert(p);
                    }
                }
                if (i + 1 <= n1)
                {
                    p = make_pair(i + 1, j);
                    if (s.find(p) == s.end())
                    {
                        q2.push(p);
                        s.insert(p);
                    }
                }
                if (i + 1 <= n1 && j + 1 <= n2)
                {
                    p = make_pair(i + 1, j + 1);
                    if (s.find(p) == s.end())
                    {
                        q2.push(p);
                        s.insert(p);
                    }
                }
                if (q1.empty() && !q2.empty())
                {
                    d++;
                    q1.swap(q2);
                }
            }
            return d;
        }

        // 73. Set Matrix Zeroes
        // Given a m x n matrix, if an element is 0, set its entire row and column to 0.
        // Do it in-place.
        // Example 1:
        // Input:
        // [
        //   [1,1,1],
        //   [1,0,1],
        //   [1,1,1]
        // ]
        // Output:
        // [
        //   [1,0,1],
        //   [0,0,0],
        //   [1,0,1]
        // ]
        // Example 2:
        // Input:
        // [
        //   [0,1,2,0],
        //   [3,4,5,2],
        //   [1,3,1,5]
        // ]
        // Output:
        // [
        //   [0,0,0,0],
        //   [0,4,5,0],
        //   [0,3,1,0]
        // ]
        // Follow up:
        // A straight forward solution using O(mn) space is probably a bad idea.
        // A simple improvement uses O(m + n) space, but still not the best solution.
        // Could you devise a constant space solution?
        void setZeroes(vector<vector<int>> &matrix)
        {
            if (matrix.empty() || matrix[0].empty())
                return;
            bool setFirstRowZero = false;
            bool setFirstColZero = false;
            for (size_t j = 0; j < matrix[0].size() && !setFirstRowZero; j++)
            {
                if (matrix[0][j] == 0)
                    setFirstRowZero = true;
            }
            for (size_t i = 0; i < matrix.size() && !setFirstColZero; i++)
            {
                if (matrix[i][0] == 0)
                    setFirstColZero = true;
            }
            for (size_t i = 0; i < matrix.size(); i++)
            {
                for (size_t j = 0; j < matrix[i].size(); j++)
                {
                    if (matrix[i][j] == 0)
                    {
                        matrix[0][j] = 0;
                        matrix[i][0] = 0;
                    }
                }
            }
            for (size_t i = 1; i < matrix.size(); i++)
            {
                if (matrix[i][0] == 0)
                {
                    for (size_t j = 1; j < matrix[i].size(); j++)
                        matrix[i][j] = 0;
                }
            }
            for (size_t j = 1; j < matrix[0].size(); j++)
            {
                if (matrix[0][j] == 0)
                {
                    for (size_t i = 1; i < matrix.size(); i++)
                        matrix[i][j] = 0;
                }
            }
            if (setFirstRowZero)
            {
                for (size_t j = 0; j < matrix[0].size(); j++)
                    matrix[0][j] = 0;
            }
            if (setFirstColZero)
            {
                for (size_t i = 0; i < matrix.size(); i++)
                    matrix[i][0] = 0;
            }
        }
        void setZeroes2(vector<vector<int>> &matrix)
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
                        matrix[i][j] = 0;
                }
            }
            for (size_t j = 1; j < n; j++)
            {
                if (matrix[0][j] == 0)
                {
                    for (size_t i = 1; i < m; i++)
                        matrix[i][j] = 0;
                }
            }
            if (zeroFirstColumn)
            {
                for (size_t i = 1; i < m; i++)
                    matrix[i][0] = 0;
            }
            if (zeroFirstRow)
            {
                for (size_t j = 1; j < n; j++)
                    matrix[0][j] = 0;
            }
        }

        // 74. Search a 2D Matrix
        // Write an efficient algorithm that searches for a value in an m x n matrix.
        // This matrix has the following properties:
        // Integers in each row are sorted from left to right.
        // The first integer of each row is greater than the last integer of the
        // previous row. Example 1: Input: matrix = [
        //   [1,   3,  5,  7],
        //   [10, 11, 16, 20],
        //   [23, 30, 34, 50]
        // ]
        // target = 3
        // Output: true
        // Example 2:
        // Input:
        // matrix = [
        //   [1,   3,  5,  7],
        //   [10, 11, 16, 20],
        //   [23, 30, 34, 50]
        // ]
        // target = 13
        // Output: false
        bool searchMatrix(const vector<vector<int>> &matrix, int target)
        {
            if (matrix.empty() || matrix[0].empty())
                return false;
            int i = 0;
            int j = matrix[0].size() - 1;
            while (i < (int)matrix.size() && j >= 0)
            {
                if (target < matrix[i][j])
                    j--;
                else if (target > matrix[i][j])
                    i++;
                else
                    return true;
            }
            return false;
        }
        bool searchMatrix2(const vector<vector<int>> &matrix, int target)
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

        // 75. Sort Colors
        // Given an array with n objects colored red, white or blue, sort them in-place
        // so that objects of the same color are adjacent, with the colors in the order
        // red, white and blue. Here, we will use the integers 0, 1, and 2 to represent
        // the color red, white, and blue respectively.
        // Note: You are not suppose to use the library's sort function for this
        // problem. Example: Input: [2,0,2,1,1,0] Output: [0,0,1,1,2,2] Follow up: A
        // rather straight forward solution is a two-pass algorithm using counting sort.
        // First, iterate the array counting number of 0's, 1's, and 2's, then overwrite
        // array with total number of 0's, then 1's and followed by 2's.
        // Could you come up with a one-pass algorithm using only constant space?
        void sortColors(vector<int> &nums)
        {
            int i = -1;
            int k = nums.size();
            int j = 0;
            while (j < k)
            {
                switch (nums[j])
                {
                case 0:
                    swap(nums[++i], nums[j]);
                    if (i == j)
                        j++;
                    break;
                case 1:
                    j++;
                    break;
                case 2:
                    swap(nums[j], nums[--k]);
                    break;
                }
            }
        }
        void sortColors2(vector<int> &nums)
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
        void sortColors3(vector<int> &nums)
        {
            if (nums.empty())
                return;
            int i = 0;
            int j = 0;
            int k = nums.size() - 1;
            int t;
            while (i < k)
            {
                while (nums[i] == 0)
                    i++;
                while (nums[k] == 2)
                    k--;
                if (i >= k)
                    return;
                // A[i] in {1,2}
                // A[k] in {0,1}
                if (nums[i] > nums[k])
                {
                    //    A[i] = 1 && A[k] = 0
                    // || A[i] = 2 && A[k] = {0,1}
                    t = nums[i];
                    nums[i] = nums[k];
                    nums[k] = t;
                }
                else
                {
                    // A[i] == A[k] == 1
                    if (j <= i)
                        j = i + 1;
                    while (nums[j] == 1)
                        j++;
                    if (j >= k)
                        return;
                    if (nums[j] == 0)
                    {
                        t = nums[i];
                        nums[i] = nums[j];
                        nums[j] = t;
                    }
                    else
                    { // A[j] == 2
                        t = nums[k];
                        nums[k] = nums[j];
                        nums[j] = t;
                    }
                }
            }
        }

        // 76. Minimum Window Substring
        // Given a string S and a string T, find the minimum window in S which will
        // contain all the characters in T in complexity O(n).
        // Example:
        // Input: S = "ADOBECODEBANC", T = "ABC"
        // Output: "BANC"
        // Note: If there is no such window in S that covers all characters in T,
        // return the empty string "". If there is such window, you are guaranteed
        // that there will always be only one unique minimum window in S.
        string minWindow(const string &s, const string &t)
        {
            if (t.empty() || s.size() < t.size())
                return "";
            map<char, int> mt;
            for (int i = 0; i < (int)t.size(); i++)
            {
                if (mt.find(t[i]) == mt.end())
                    mt[t[i]] = 1;
                else
                    mt[t[i]]++;
            }
            int b = -1;
            int e = (int)s.size();
            queue<int> q;
            map<char, int> ms;
            map<char, int> c(mt); // characters to look for
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (mt.find(s[i]) == mt.end())
                    continue;
                q.push(i);
                if (ms.find(s[i]) == ms.end())
                    ms[s[i]] = 1;
                else
                    ms[s[i]]++;
                if (c.find(s[i]) != c.end())
                {
                    c[s[i]]--;
                    if (c[s[i]] == 0)
                        c.erase(s[i]);
                }
                if (c.empty())
                {
                    // all required characters are found
                    while (!q.empty() && ms[s[q.front()]] > mt[s[q.front()]])
                    {
                        ms[s[q.front()]]--;
                        q.pop();
                    }
                    if (!q.empty())
                    {
                        if (i - q.front() < e - b)
                        {
                            b = q.front();
                            e = i;
                        }
                        // look for next character that is also first one in current valid window
                        c[s[q.front()]] = 1;
                        ms[s[q.front()]]--;
                        q.pop();
                    }
                }
            }
            return b == -1 ? "" : s.substr(b, e - b + 1);
        }
        string minWindow2(const string &s, const string &t)
        {
            if (t.empty() || s.size() < t.size())
                return "";
            map<char, int> mt;
            for (size_t i = 0; i < t.size(); i++)
            {
                if (mt.find(t[i]) == mt.end())
                    mt[t[i]] = 1;
                else
                    mt[t[i]]++;
            }
            map<char, int> ms;
            size_t minIndex = INT_MAX;
            size_t minLen = INT_MAX;
            size_t i = 0;
            size_t j = 0;
            while (j < s.size())
            {
                if (mt.find(s[j]) == mt.end())
                {
                    j++;
                    continue;
                }
                if (ms.find(s[j]) == ms.end())
                    ms[s[j]] = 1;
                else
                    ms[s[j]]++;
                if (ms.size() < mt.size())
                {
                    j++;
                    continue;
                }
                bool hasT = true;
                for (auto it = ms.cbegin(); it != ms.cend(); it++)
                {
                    if (it->second < mt[it->first])
                    {
                        hasT = false;
                        break;
                    }
                }
                if (!hasT)
                {
                    j++;
                    continue;
                }
                while (ms.find(s[i]) == ms.end() || ms[s[i]] > mt[s[i]])
                {
                    if (ms.find(s[i]) != ms.end())
                        ms[s[i]]--;
                    i++;
                }
                if (j - i + 1 < minLen)
                {
                    minIndex = i;
                    minLen = j - i + 1;
                }
                j++;
            }
            return minIndex == INT_MAX ? "" : s.substr(minIndex, minLen);
        }
        string minWindow3(const string &s, const string &t)
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
            auto compare = [&](map<char, int> &c1, map<char, int> &c2) -> bool
            {
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
                    while (countS[indices.front().first] >
                           countT[indices.front().first])
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
        string minWindow4(const string &s, const string &t)
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
                    // TODO: investigate when and how to decrease total and see
                    // if can avoid using queue indices.
                    if (countS[s[i]] <= countT[s[i]])
                        total++;
                    indices.push(make_pair(s[i], i));
                    while (countS[indices.front().first] >
                           countT[indices.front().first])
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

        // 77. Combinations
        // Given two integers n and k, return all possible combinations of k numbers
        // out of 1 ... n.
        // Example:
        // Input: n = 4, k = 2
        // Output:
        // [
        //   [2,4],
        //   [3,4],
        //   [2,3],
        //   [1,2],
        //   [1,3],
        //   [1,4],
        // ]
        vector<vector<int>> combine(int n, int k)
        {
            vector<vector<int>> result;
            if (k <= 0 || n <= 0 || k > n)
                return result;
            function<void(int, int, vector<int> &)>
                solve = [&](int i, int c, vector<int> &v)
            {
                if (c == 0)
                {
                    result.push_back(v);
                    return;
                }
                for (int j = i; j <= n; j++)
                {
                    v.push_back(j);
                    solve(j + 1, c - 1, v);
                    v.pop_back();
                }
            };
            vector<int> c;
            solve(1, k, c);
            return result;
        }
        vector<vector<int>> combine2(int n, int k)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            if (k <= 0 || n <= 0 || k > n)
                return result;
            function<void(int, int, vector<int> &)>
                select = [&](int i, int l, vector<int> &c)
            {
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
        vector<vector<int>> combine3(int n, int k)
        {
            if (n < k)
                return vector<vector<int>>{{}};
            function<void(int, int, map<pair<int, int>, vector<vector<int>>> &)>
                combine =
                    [&](int i, int j, map<pair<int, int>, vector<vector<int>>> &s)
            {
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
                for_each(s[q1].begin(), s[q1].end(), [&](vector<int> &v)
                         {
                             vector<int> ex(v.begin(), v.end());
                             ex.push_back(i);
                             s[p].push_back(ex); });
                pair<int, int> q2 = make_pair(i - 1, j);
                if (s.find(q2) == s.end())
                    combine(i - 1, j, s);
                for_each(s[q2].begin(), s[q2].end(),
                         [&](vector<int> &v)
                         { s[p].push_back(v); });
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
        // j       1          2          3          4 ......      k-1         k
        // i 0 s(1,1)
        //   1 s(2,1)     s(2,2)
        //   2 s(3,1)     s(3,2)     s(3,3)
        //   3 s(4,1)     s(4,2)     s(4,3)     s(4,4)
        //     ......     ......     ......     ......
        //     ......     ......     ......     ......  ......
        //     ......     ......     ......     ......  ...... ......
        //     ......     ......     ......     ......  ...... s(k,k-1)   s(k,k)
        //     ......     ......     ......     ......  ...... s(k+1,k-1) s(k+1,k)
        //     ......     ......     ......     ......  ...... ......     ......
        //     ......     ......     ......     ......  ...... ......     ......
        // n-k s(n-k+1,1) s(n-k+1,2) ......     ......  ...... ......     ......
        //                s(n-k+2,2) ......     ......  ...... ......     ......
        //                           s(n-k+2,3) ......  ...... ......     ......
        //                                      ......  ...... ......     ......
        //                                              ...... ......     ......
        //                                                     s(n-1,k-1) s(n-1,k)
        //                                                                s(n,k)
        //
        vector<vector<int>> combine4(int n, int k)
        {
            if (n <= 0 || k <= 0 || n < k)
                return vector<vector<int>>{{}};
            // Represent a column
            vector<vector<vector<int>>> s(n - k + 1, vector<vector<int>>{{}});
            for (int j = 1; j <= k; j++)
            {
                // s[0] = s(0+j, j) = {{1,2,...,j}}
                s[0][0].push_back(j);
                for (int i = 1; i <= n - k; i++)
                {
                    // s[i] = s(i+j, j)
                    // Extend s[i] by adding i+j to each of s(i-1+j,j-1)
                    for_each(s[i].begin(), s[i].end(),
                             [&](vector<int> &v)
                             { v.push_back(i + j); });
                    // Extend s[i] = s(i+j,j) by adding s(i-1+j,j)
                    for_each(s[i - 1].begin(), s[i - 1].end(),
                             [&](vector<int> &v)
                             { s[i].push_back(v); });
                }
            }
            return s[n - k];
        }
        vector<vector<int>> combine5(int n, int k)
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
                            output.push_back(ex);
                        else
                            sets.push_back(ex);
                    }
                }
            }
            return output;
        }
        vector<vector<int>> combine6(int n, int k)
        {
            function<void(vector<int>, int, int, vector<vector<int>> &)> solve =
                [&](vector<int> pre, int i, int k1, vector<vector<int>> &s)
            {
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
                        pre.push_back(j);
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
        // Given a set of distinct integers, nums, return all possible subsets (the
        // power set). Note: The solution set must not contain duplicate subsets.
        // Example:
        // Input: nums = [1,2,3]
        // Output:
        // [
        //   [3],
        //   [1],
        //   [2],
        //   [1,2,3],
        //   [1,3],
        //   [2,3],
        //   [1,2],
        //   []
        // ]
        vector<vector<int>> subsets(const vector<int> &nums)
        {
            vector<vector<int>> sets = {{}};
            for (size_t i = 0; i < nums.size(); i++)
            {
                size_t n = sets.size();
                for (size_t j = 0; j < n; j++)
                {
                    vector<int> v(sets[j]);
                    v.push_back(nums[i]);
                    sets.push_back(v);
                }
            }
            return sets;
        }
        vector<vector<int>> subsets2(const vector<int> &nums)
        {
            vector<vector<int>> sets;
            function<void(size_t, size_t, vector<int> &)> select =
                [&](size_t i, size_t k, vector<int> &v)
            {
                if (k == 0)
                {
                    sets.push_back(v);
                    return;
                }
                for (size_t j = i; j < nums.size(); j++)
                {
                    v.push_back(nums[j]);
                    select(j + 1, k - 1, v);
                    v.pop_back();
                }
            };
            vector<int> s;
            for (size_t k = 0; k <= nums.size(); k++)
                select(0, k, s);
            return sets;
        }

        // 79. Word Search
        // Given a 2D board and a word, find if the word exists in the grid.
        // The word can be constructed from letters of sequentially adjacent
        // cell, where "adjacent" cells are those horizontally or vertically
        // neighboring. The same letter cell may not be used more than once.
        // Example:
        // board =
        // [
        //   ['A','B','C','E'],
        //   ['S','F','C','S'],
        //   ['A','D','E','E']
        // ]
        // Given word = "ABCCED", return true.
        // Given word = "SEE", return true.
        // Given word = "ABCB", return false.
        // [TODO] What if a letter can be reused?
        bool exist(const vector<vector<char>> &board, const string &word)
        {
            if (word.empty())
                return true;
            if (board.empty() || board[0].empty())
                return false;
            function<bool(size_t, size_t, size_t, set<pair<size_t, size_t>> &)>
                solve = [&](size_t i, size_t j, size_t k,
                            set<pair<size_t, size_t>> &v) -> bool
            {
                if (k == word.size())
                    return true;
                if (board[i][j] != word[k])
                    return false;
                pair<size_t, size_t> p = make_pair(i, j);
                if (v.find(p) != v.end())
                    return false;
                if (k + 1 == word.size())
                    return true;
                v.insert(p);
                if (i > 0 && solve(i - 1, j, k + 1, v))
                    return true;
                if (j + 1 < board[0].size() && solve(i, j + 1, k + 1, v))
                    return true;
                if (i + 1 < board.size() && solve(i + 1, j, k + 1, v))
                    return true;
                if (j > 0 && solve(i, j - 1, k + 1, v))
                    return true;
                v.erase(p);
                return false;
            };
            set<pair<size_t, size_t>> visited;
            for (size_t i = 0; i < board.size(); i++)
            {
                for (size_t j = 0; j < board[i].size(); j++)
                {
                    if (solve(i, j, 0, visited))
                        return true;
                }
            }
            return false;
        }
        bool exist2(const vector<vector<char>> &board, const string &word)
        {
            if (board.size() == 0 || board[0].size() == 0)
                return false;
            int m = board.size();
            int n = board[0].size();
            int l = word.size();
            function<bool(pair<int, int> &, int, set<pair<int, int>> &)> search =
                [&](pair<int, int> &p, int i, set<pair<int, int>> &v) -> bool
            {
                if (p.first < 0 || p.first >= m || p.second < 0 || p.second >= n ||
                    i < 0 || i >= l || board[p.first][p.second] != word[i] ||
                    v.find(p) != v.end())
                {
                    return false;
                }
                if (i == l - 1)
                    return true;
                v.insert(p);
                pair<int, int> p1 = make_pair(p.first, p.second - 1);
                if (search(p1, i + 1, v))
                    return true;
                p1 = make_pair(p.first, p.second + 1);
                if (search(p1, i + 1, v))
                    return true;
                p1 = make_pair(p.first - 1, p.second);
                if (search(p1, i + 1, v))
                    return true;
                p1 = make_pair(p.first + 1, p.second);
                if (search(p1, i + 1, v))
                    return true;
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
        bool exist3(const vector<vector<char>> &board, const string &word)
        {
            int m = board.size();
            int n = board[0].size();
            function<bool()> qcheck = [&]() -> bool
            {
                map<char, int> c;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (c.find(board[i][j]) == c.end())
                            c[board[i][j]] = 1;
                        else
                            c[board[i][j]]++;
                    }
                }
                map<char, int> d;
                for (size_t k = 0; k < word.size(); k++)
                {
                    if (d.find(word[k]) == d.end())
                        d[word[k]] = 1;
                    else
                        d[word[k]]++;
                }
                if (c.size() < d.size())
                    return false;
                for (const auto &p : d)
                {
                    if (c.find(p.first) == c.end())
                        return false;
                    if (c[p.first] < p.second)
                        return false;
                }
                return true;
            };
            // if (!qcheck())
            //    return false;
            function<bool(int, int)> search = [&](int i, int j) -> bool
            {
                set<pair<int, int>> v;
                stack<pair<int, int>> s;
                size_t k = 0;
                pair<int, int> p = make_pair(i, j);
                while (true)
                {
                    if (0 <= p.first && p.first < m && 0 <= p.second && p.second < n && v.find(p) == v.end() && board[p.first][p.second] == word[k])
                    {
                        if (k + 1 == word.size())
                            return true;
                        s.push(p);
                        v.insert(p);
                        k++;
                        p.second--;
                    }
                    else
                    {
                        while (!s.empty() && p.first == s.top().first + 1 && p.second == s.top().second)
                        {
                            p = s.top();
                            s.pop();
                            v.erase(p);
                        }
                        if (s.empty())
                            break;
                        auto t = s.top();
                        if (p.first == t.first && p.second + 1 == t.second)
                        {
                            p.first--;
                            p.second++;
                        }
                        else if (p.first + 1 == t.first && p.second == t.second)
                        {
                            p.first++;
                            p.second++;
                        }
                        else if (p.first == t.first && p.second == t.second + 1)
                        {
                            p.first++;
                            p.second--;
                        }
                        else
                        {
                            break;
                        }
                        k = s.size();
                    }
                }
                return false;
            };
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (board[i][j] == word[0] && search(i, j))
                        return true;
                }
            }
            return false;
        }

        // 80. Remove Duplicates from Sorted Array II
        // Given a sorted array nums, remove the duplicates in-place such that
        // duplicates appeared at most twice and return the new length. Do not
        // allocate extra space for another array, you must do this by modifying
        // the input array in-place with O(1) extra memory.
        // Example 1:
        // Given nums = [1,1,1,2,2,3], Your function should return length = 5,
        // with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
        // It doesn't matter what you leave beyond the returned length.
        // Example 2:
        // Given nums = [0,0,1,1,1,1,2,3,3], Your function should return length = 7,
        // with the first seven elements of nums being modified to 0, 0, 1, 1, 2, 3
        // and 3 respectively.
        // It doesn't matter what values are set beyond the returned length.
        int removeDuplicatesII(vector<int> &nums)
        {
            int i = -1;
            size_t j = 0;
            while (j < nums.size())
            {
                if (j == 0 || nums[j - 1] != nums[j])
                {
                    size_t k = j;
                    while (k <= j + 1 && k < nums.size() && nums[k] == nums[j])
                    {
                        ++i;
                        if (i < (int)k)
                            nums[i] = nums[k];
                        k++;
                    }
                    j = k;
                }
                else
                {
                    j++;
                }
            }
            return i + 1;
        }
        int removeDuplicatesII2(vector<int> &nums)
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
        int removeDuplicatesII3(vector<int> &nums)
        {
            int n = nums.size();
            if (n <= 2)
                return n;
            int i = 0;
            int j = 1;
            while (j < n)
            {
                if (i + 1 < j)
                    nums[i + 1] = nums[j];
                i++;
                j++;
                if (nums[i - 1] == nums[i])
                {
                    while (j < n && nums[j] == nums[i])
                        j++;
                }
            }
            return i + 1;
        }
        // This is wrong. For input [1, 1, 1, 2, 2, 3], output is [1, 1, 2, 3]
        int removeDuplicatesII4(vector<int> &nums)
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

        // 81. Search in Rotated Sorted Array II
        // Suppose an array sorted in ascending order is rotated at some pivot
        // unknown to you beforehand. (i.e., [0,0,1,2,2,5,6] might become
        // [2,5,6,0,0,1,2]). You are given a target value to search. If found
        // in the array return true, otherwise return false.
        // Example 1:
        // Input: nums = [2,5,6,0,0,1,2], target = 0
        // Output: true
        // Example 2:
        // Input: nums = [2,5,6,0,0,1,2], target = 3
        // Output: false
        // Follow up:
        // This is a follow up problem to Search in Rotated Sorted Array, where
        // nums may contain duplicates. Would this affect the run-time complexity?
        // How and why?
        bool searchII(const vector<int> &nums, int target)
        {
            function<bool(int, int)> solve = [&](int l, int h) -> bool
            {
                while (l <= h)
                {
                    int m = l + ((h - l) >> 1);
                    if (nums[0] < nums[m])
                    {
                        if (target < nums[m])
                        {
                            if (nums[0] < target)
                                h = m - 1;
                            else if (nums[0] > target)
                                l = m + 1;
                            else
                                return true;
                        }
                        else if (target > nums[m])
                        {
                            l = m + 1;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else if (nums[0] > nums[m])
                    {
                        if (target < nums[m])
                        {
                            h = m - 1;
                        }
                        else if (target > nums[m])
                        {
                            if (target < nums[nums.size() - 1])
                                l = m + 1;
                            else if (target > nums[nums.size() - 1])
                                h = m - 1;
                            else
                                return true;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        if (target == nums[m])
                            return true;
                        if (solve(l, m - 1))
                            return true;
                        return solve(m + 1, h);
                    }
                }
                return false;
            };
            return solve(0, nums.size() - 1);
        }
        bool searchII2(const vector<int> &nums, int target)
        {
            if (nums.size() == 0)
                return false;
            function<bool(int, int)> search = [&](int l, int r) -> bool
            {
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

        // 82. Remove Duplicates from Sorted List II
        // Given a sorted linked list, delete all nodes that have duplicate numbers,
        // leaving only distinct numbers from the original list.
        // Example 1:
        // Input: 1->2->3->3->4->4->5
        // Output: 1->2->5
        // Example 2:
        // Input: 1->1->1->2->3
        // Output: 2->3
        ListNode *deleteDuplicatesII(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return head;
            ListNode *p = nullptr;
            while (head != nullptr && head->next != nullptr &&
                   head->val == head->next->val)
            {
                int v = head->val;
                while (head != nullptr && head->val == v)
                {
                    p = head;
                    head = head->next;
                    delete p;
                }
            }
            if (head == nullptr || head->next == nullptr)
                return head;
            p = head;
            while (p->next != nullptr && p->next->next != nullptr)
            {
                if (p->next->val == p->next->next->val)
                {
                    int v = p->next->val;
                    while (p->next != nullptr && p->next->val == v)
                    {
                        ListNode *q = p->next;
                        p->next = q->next;
                        delete q;
                    }
                }
                else
                {
                    p = p->next;
                }
            }
            return head;
        }
        ListNode *deleteDuplicatesII2(ListNode *head)
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
                    // Note p may not be unique now
                    // No update prev because prev must be unique
                    // But still update the list linkage to maintain
                    // a valid list. Otherwise, head or prev->next
                    // will point to some deleted node.
                    if (prev == nullptr)
                        head = p;
                    else
                        prev->next = p;
                }
                else
                {
                    if (prev == nullptr)
                        head = p;
                    else
                        prev->next = p;
                    prev = p;
                    p = p->next;
                }
            }
            return head;
        }
        ListNode *deleteDuplicatesII3(ListNode *head)
        {
            function<ListNode *(ListNode *)> del =
                [&](ListNode *h) -> ListNode *
            {
                if (h == nullptr)
                    return h;
                bool delete_h = false;
                ListNode *p;
                while (h->next != nullptr && h->val == h->next->val)
                {
                    delete_h = true;
                    p = h;
                    h = h->next;
                    delete p;
                }
                if (delete_h)
                {
                    p = h;
                    h = h->next;
                    delete p;
                    h = del(h);
                }
                else
                {
                    h->next = del(h->next);
                }
                return h;
            };
            return del(head);
        }
        ListNode *deleteDuplicatesII4(ListNode *head)
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

        // 83. Remove Duplicates from Sorted List
        // Given a sorted linked list, delete all duplicates such that each element
        // appear only once.
        // Example 1:
        // Input: 1->1->2
        // Output: 1->2
        // Example 2:
        // Input: 1->1->2->3->3
        // Output: 1->2->3
        ListNode *deleteDuplicates(ListNode *head)
        {
            ListNode *p = head;
            while (p != nullptr)
            {
                while (p->next != nullptr && p->val == p->next->val)
                {
                    ListNode *q = p->next;
                    p->next = q->next;
                    delete q;
                }
                p = p->next;
            }
            return head;
        }
        ListNode *deleteDuplicates2(ListNode *head)
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

        // 84. Largest Rectangle in Histogram
        // Given n non-negative integers representing the histogram's bar height
        // where the width of each bar is 1, find the area of largest rectangle
        // in the histogram..
        // Above is a histogram where width of each bar is 1, given height =
        // [2,1,5,6,2,3]. The largest rectangle is shown in the shaded area (5,6), which
        // has area = 10 unit. Example: Input: [2,1,5,6,2,3] Output: 10
        int largestRectangleArea(const vector<int> &heights)
        {
            // Record the starting index and height of each candidate histogram
            stack<pair<int, int>> s;
            int m = 0;
            for (int i = 0; i < (int)heights.size(); i++)
            {
                if (s.empty() || s.top().second <= heights[i])
                {
                    s.push(make_pair(i, heights[i]));
                    continue;
                }
                int j; // starting index of rectangle with heights[i]
                while (!s.empty() && s.top().second > heights[i])
                {
                    // compute area in [top.first, i-1]
                    m = max(m, (i - s.top().first) * s.top().second);
                    j = s.top().first;
                    s.pop();
                }
                // Candidate height at j is heights[i] rather than heights[j]
                // because heights[j] > heights[i]
                s.push(make_pair(j, heights[i]));
            }
            while (!s.empty())
            {
                // compute area in [top.first, n-1]
                m = max(m, ((int)heights.size() - s.top().first) * s.top().second);
                s.pop();
            }
            return m;
        }
        int largestRectangleArea2(const vector<int> &height)
        {
            if (height.size() == 0)
                return 0;
            // Track rectangle [i, j] with height h such that rec[i] = <j, h>;
            map<int, pair<int, int>> rec = {{0, make_pair(0, height[0])}};
            int maxArea = height[0];
            for (int i = 1; i < (int)height.size(); i++)
            {
                if (height[i] == 0)
                {
                    rec.clear();
                    continue;
                }
                for (map<int, pair<int, int>>::iterator it = rec.begin();
                     it != rec.end(); it++)
                {
                    // height of [it->first, it->second.first] is
                    // min(it->second.second, height[i])
                    if (height[i] < it->second.second)
                    {
                        it->second.second = height[i];
                    }
                    it->second.first++;
                    // TODO: Can this be done only when height[i] = 0?
                    int area = (it->second.first - it->first + 1) * it->second.second;
                    if (area > maxArea)
                        maxArea = area;
                }
                if (height[i] > height[i - 1])
                {
                    // A new candidate starting at i
                    rec[i] = make_pair(i, height[i]);
                    if (height[i] > maxArea)
                        maxArea = height[i];
                }
            }
            return maxArea;
        }
        int largestRectangleArea3(const vector<int> &height)
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
                    // A candidate rectangle [t, i-1] and the min height is at t
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
                // A candidate rectangle (rec.top(), n-1] and the min height is at t
                int area = height[t] *
                           ((int)height.size() - 1 - (rec.empty() ? -1 : rec.top()));
                if (area > maxArea)
                    maxArea = area;
            }

            return maxArea;
        }
        // This is wrong, e.g., for [2 1 2] it returns 2 but answer should be 3
        int largestRectangleArea4(const vector<int> &height)
        {
            if (height.empty())
                return 0;
            int maxArea = height[0];
            int i = 0;
            int j = 1;
            int n = (int)height.size();
            while (j < n)
            {
                // Find [i, j-1] where elements in between are no less than min of
                // boundaries
                while (j < n && height[j - 1] <= height[j])
                    j++;
                while (j < n && height[j - 1] >= height[j])
                    j++;
                int p = i;
                int q = j - 1;
                while (p <= q)
                {
                    maxArea =
                        std::max(maxArea, (q - p + 1) * std::min(height[p], height[q]));
                    if (height[p] < height[q])
                        p++;
                    else
                        q--;
                }
                i = j - 1;
            }
            return maxArea;
        }

        // 85. Maximal Rectangle
        // Given a 2D binary matrix filled with 0's and 1's, find the largest
        // rectangle containing only 1's and return its area.
        // Example:
        // Input:
        // [
        //   ["1","0","1","0","0"],
        //   ["1","0","1","1","1"],
        //   ["1","1","1","1","1"],
        //   ["1","0","0","1","0"]
        // ]
        // Output: 6
        int maximalRectangle(const vector<vector<char>> &matrix)
        {
            if (matrix.empty() || matrix[0].empty())
                return 0;
            // find max rectangle given a histgram
            function<int(const vector<int> &)> solve =
                [&](const vector<int> &v) -> int
            {
                stack<pair<int, int>> s;
                int m = 0;
                for (int i = 0; i < (int)v.size(); i++)
                {
                    if (s.empty() || s.top().second <= v[i])
                    {
                        // i is starting point of a candidate rectangle with height v[i]
                        s.push(make_pair(i, v[i]));
                        continue;
                    }
                    int j = i;
                    while (!s.empty() && s.top().second > v[i])
                    {
                        m = max(m, (i - s.top().first) * s.top().second);
                        j = s.top().first;
                        s.pop();
                    }
                    s.push(make_pair(j, v[i]));
                }
                while (!s.empty())
                {
                    m = max(m, ((int)v.size() - s.top().first) * s.top().second);
                    s.pop();
                }
                return m;
            };
            int area = 0;
            vector<int> r(matrix[0].size(), 0);
            for (size_t i = 0; i < matrix.size(); i++)
            {
                for (size_t j = 0; j < matrix[i].size(); j++)
                {
                    if (matrix[i][j] == '1')
                        r[j] += 1;
                    else
                        r[j] = 0;
                }
                area = max(area, solve(r));
            }
            return area;
        }
        int maximalRectangle2(const vector<vector<char>> &matrix)
        {
            if (matrix.empty() || matrix[0].empty())
                return 0;
            // Compute max rectangle whose top-left point is at (pi, pj)
            function<int(int, int)> solve = [&](int pi, int pj)
            {
                if (pi < 0 || pi >= (int)matrix.size() || pj < 0 ||
                    pj >= (int)matrix[0].size())
                    return 0;
                if (matrix[pi][pj] != '1')
                    return 0;
                int i = pi;
                int j = pj;
                while (j + 1 < (int)matrix[i].size() && matrix[i][j + 1] == '1')
                    j++;
                int maxj = j;
                int maxArea = j - pj + 1;
                while (i + 1 < (int)matrix.size() && matrix[i + 1][pj] == '1')
                {
                    i++;
                    j = pj;
                    while (j + 1 <= maxj && matrix[i][j + 1] == '1' &&
                           matrix[i - 1][j + 1] == '1')
                        j++;
                    int area = (i - pi + 1) * (j - pj + 1);
                    if (area > maxArea)
                        maxArea = area;
                    maxj = j;
                }
                return maxArea;
            };
            int maxArea = 0;
            for (int i = 0; i < (int)matrix.size(); i++)
            {
                for (int j = 0; j < (int)matrix[i].size(); j++)
                {
                    if (matrix[i][j] == '1')
                    {
                        int area = solve(i, j);
                        if (area > maxArea)
                            maxArea = area;
                    }
                }
            }
            return maxArea;
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
        static int MaximalRectangle2(vector<vector<char>> &matrix)
        {
            if (matrix.size() == 0 || matrix[0].size() == 0)
                return 0;
            int imin = INT_MAX;
            int imax = INT_MIN;
            int jmin = INT_MAX;
            int jmax = INT_MIN;
            for (int i = 0; i < (int)matrix.size(); i++)
            {
                for (int j = 0; j < (int)matrix[i].size(); j++)
                {
                    if (matrix[i][j] == 1)
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
                }
            }
            if (imin > imax || jmin > jmax)
                return 0;
            int area = (imax - imin + 1) * (jmax - jmin + 1);
            return area;
        }
        // Given a 2D binary matrix filled with 0's and 1's,
        // find the largest rectangle full of ones and with a give point on its top-left
        // corner, return the rectangle area.
        static int MaximalRectangleAtPoint(vector<vector<char>> &matrix, int pi,
                                           int pj)
        {
            if (matrix.size() == 0 || matrix[0].size() == 0)
                return 0;
            if (pi < 0 || pi >= (int)matrix.size() || pj < 0 ||
                pj >= (int)matrix[0].size())
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
                while (j + 1 <= maxj && matrix[i][j + 1] == 1 &&
                       matrix[i - 1][j + 1] == 1)
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

        // 86. Partition List
        // Given a linked list and a value x, partition it such that all nodes less
        // than x come before nodes greater than or equal to x. You should preserve
        // the original relative order of the nodes in each of the two partitions.
        // Example:
        // Input: head = 1->4->3->2->5->2, x = 3
        // Output: 1->2->2->4->3->5
        ListNode *partition(ListNode *head, int x)
        {
            if (head == nullptr)
                return head;
            ListNode *p = nullptr; // last node smaller than x
            if (head->val < x)
                p = head;
            while (p != nullptr && p->next != nullptr && p->next->val < x)
                p = p->next;
            ListNode *q = p == nullptr ? head : p->next; // last node no smaller than x
            while (q != nullptr)
            {
                if (q->next == nullptr)
                    break;
                if (q->next->val >= x)
                {
                    q = q->next;
                    continue;
                }
                ListNode *t = q->next;
                q->next = t->next;
                if (p == nullptr)
                {
                    t->next = head;
                    head = t;
                    p = t;
                }
                else
                {
                    t->next = p->next;
                    p->next = t;
                    p = t;
                }
            }
            return head;
        }
        ListNode *partition2(ListNode *head, int x)
        {
            ListNode *p = nullptr;
            ListNode *q = nullptr;
            ListNode *n = head;
            while (n != nullptr)
            {
                if (n->val < x)
                {
                    if (p == nullptr)
                    {
                        if (n != head)
                        {
                            q->next = n->next;
                            n->next = head;
                            head = n;
                            p = n;
                            n = q->next;
                        }
                        else
                        {
                            p = n;
                            n = n->next;
                        }
                    }
                    else
                    {
                        if (p->next != n)
                        {
                            q->next = n->next;
                            n->next = p->next;
                            p->next = n;
                            p = n;
                            n = q->next;
                        }
                        else
                        {
                            p = n;
                            n = n->next;
                        }
                    }
                }
                else
                {
                    q = n;
                    n = n->next;
                }
            }
            return head;
        }
        ListNode *partition3(ListNode *head, int x)
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
        ListNode *partition4(ListNode *head, int x)
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

        // 87. Scramble String
        // Given a string s1, we may represent it as a binary tree by partitioning
        // it to two non-empty substrings recursively.
        // Below is one possible representation of s1 = "great":
        //     great
        //    /    \
        //   gr    eat
        //  / \    /  \
        // g   r  e   at
        //            / \
        //           a   t
        // To scramble the string, we may choose any non-leaf node and swap its two
        // children. For example, if we choose the node "gr" and swap its two children,
        // it produces a scrambled string "rgeat".
        //     rgeat
        //    /    \
        //   rg    eat
        //  / \    /  \
        // r   g  e   at
        //            / \
        //           a   t
        // We say that "rgeat" is a scrambled string of "great".
        // Similarly, if we continue to swap the children of nodes "eat" and "at",
        // it produces a scrambled string "rgtae".
        //     rgtae
        //    /    \
        //   rg    tae
        //  / \    /  \
        // r   g  ta  e
        //        / \
        //       t   a
        // We say that "rgtae" is a scrambled string of "great".
        // Given two strings s1 and s2 of the same length, determine if s2 is a
        // scrambled string of s1.
        // Example 1:
        // Input: s1 = "great", s2 = "rgeat"
        // Output: true
        // Example 2:
        // Input: s1 = "abcde", s2 = "caebd"
        // Output: false
        bool isScramble(const string &s1, const string &s2)
        {
            if (s1.empty() && s2.empty())
                return true;
            function<bool(const map<char, int> &, const map<char, int> &)> areEqual =
                [&](const map<char, int> &m1, const map<char, int> &m2) -> bool
            {
                if (m1.size() != m2.size())
                    return false;
                for (auto it = m1.cbegin(); it != m1.cend(); it++)
                {
                    if (m2.find(it->first) == m2.end())
                        return false;
                    if (m2.at(it->first) != it->second)
                        return false;
                }
                return true;
            };
            // Check if s1[i1..j1] is scramble of s2[i2..j2]
            function<bool(int, int, int, int)> solve = [&](int i1, int j1, int i2,
                                                           int j2) -> bool
            {
                if (j1 - i1 != j2 - i2)
                    return false;
                if (i1 == j1 && i2 == j2)
                    return s1[i1] == s2[i2];
                if (i1 + 1 == j1 && i2 + 1 == j2)
                    return (s1[i1] == s2[i2] && s1[j1] == s2[j2]) ||
                           (s1[i1] == s2[j2] && s1[j1] == s2[i2]);
                map<char, int> m1;
                map<char, int> m2;
                map<char, int> m3;
                // check s1[i1..(j1 - 1)] with s2[i2..(j2 - 1)] and s2[(i2 + 1)..j2]
                for (int i = 0; i < j1 - i1; i++)
                {
                    if (m1.find(s1[i1 + i]) == m1.end())
                        m1[s1[i1 + i]] = 1;
                    else
                        m1[s1[i1 + i]]++;
                    if (m2.find(s2[i2 + i]) == m2.end())
                        m2[s2[i2 + i]] = 1;
                    else
                        m2[s2[i2 + i]]++;
                    if (m3.find(s2[j2 - i]) == m3.end())
                        m3[s2[j2 - i]] = 1;
                    else
                        m3[s2[j2 - i]]++;
                    if (areEqual(m1, m2))
                    {
                        if (solve(i1, i1 + i, i2, i2 + i) &&
                            solve(i1 + i + 1, j1, i2 + i + 1, j2))
                            return true;
                    }
                    if (areEqual(m1, m3))
                    {
                        if (solve(i1, i1 + i, j2 - i, j2) &&
                            solve(i1 + i + 1, j1, i2, j2 - i - 1))
                            return true;
                    }
                }
                return false;
            };
            return solve(0, (int)s1.size() - 1, 0, (int)s2.size() - 1);
        }
        bool isScramble2(const string &s1, const string &s2)
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
                if (Util::Equal(m1, m2))
                {
                    // s1[0..i] and s2[0..i] may be scramble
                    if (i == 0 || i == 1)
                    {
                        // s1[0] and s2[0], or s1[0..1] and s2[0..1] are scramble
                        if (i == len - 1 || isScramble2(s1.substr(i + 1, len - 1 - i),
                                                        s2.substr(i + 1, len - 1 - i)))
                            return true;
                    }
                    else if (i < len - 1)
                    {
                        if (isScramble2(s1.substr(0, i + 1), s2.substr(0, i + 1)) &&
                            isScramble2(s1.substr(i + 1, len - 1 - i),
                                        s2.substr(i + 1, len - 1 - i)))
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
                if (Util::Equal(m1, m2))
                {
                    // s1[len-1-i..len-1] and s2[0..i] may be scramble
                    if (i == 0 || i == 1)
                    {
                        if (i == len - 1 || isScramble2(s1.substr(0, len - 1 - i),
                                                        s2.substr(i + 1, len - 1 - i)))
                            return true;
                    }
                    else if (i < len - 1)
                    {
                        if (isScramble2(s1.substr(0, len - 1 - i),
                                        s2.substr(i + 1, len - 1 - i)) &&
                            isScramble2(s1.substr(len - 1 - i, i + 1),
                                        s2.substr(0, i + 1)))
                            return true;
                    }
                }
            }
            return false;
        }
        bool isScramble3(const string &s1, const string &s2)
        {
            if (s1.length() != s2.length())
                return false;
            if (s1.length() == 0)
                return true;
            map<pair<int, int>, map<pair<int, int>, bool>> scramble;
            function<bool(int, int, int, int)> isscramble = [&](int i1, int i2, int j1,
                                                                int j2) -> bool
            {
                // check s1[i1..i2] and s2[j1..j2]
                pair<int, int> pi = make_pair(i1, i2);
                pair<int, int> pj = make_pair(j1, j2);
                if (scramble.find(pi) != scramble.end() &&
                    scramble[pi].find(pj) != scramble[pi].end())
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
                    if (Util::Equal(m1, m2))
                    {
                        // s1[i1..i] and s2[j1..j] may be scramble
                        if (j - j1 <= 1)
                        {
                            if (j == j2 || isscramble(i + 1, i2, j + 1, j2))
                            {
                                scramble[pi][pj] = true;
                                return true;
                            }
                        }
                        else if (j < j2)
                        {
                            if (isscramble(i1, i, j1, j) &&
                                isscramble(i + 1, i2, j + 1, j2))
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
                    if (Util::Equal(m1, m2))
                    {
                        // s1[i..i2] and s2[j1..j] may be scramble
                        if (j - j1 <= 1)
                        {
                            if (j == j2 || isscramble(i1, i - 1, j + 1, j2))
                            {
                                scramble[pi][pj] = true;
                                return true;
                            }
                        }
                        else if (j < j2)
                        {
                            if (isscramble(i1, i - 1, j + 1, j2) &&
                                isscramble(i, i2, j1, j))
                            {
                                scramble[pi][pj] = true;
                                return true;
                            }
                        }
                    }
                }
                return false;
            };
            return isscramble(0, (int)s1.length() - 1, 0, (int)s2.length() - 1);
        }

        // 88. Merge Sorted Array
        // Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1
        // as one sorted array. Note: The number of elements initialized in nums1
        // and nums2 are m and n respectively. You may assume that nums1 has enough
        // space (size that is greater or equal to m + n) to hold additional elements
        // from nums2.
        // Example:
        // Input:
        // nums1 = [1,2,3,0,0,0], m = 3
        // nums2 = [2,5,6],       n = 3
        // Output: [1,2,2,3,5,6]
        void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
        {
            int i = m + n - 1;
            while (n > 0)
            {
                if (m > 0 && nums1[m - 1] > nums2[n - 1])
                {
                    nums1[i] = nums1[m - 1];
                    m--;
                }
                else
                {
                    nums1[i] = nums2[n - 1];
                    n--;
                }
                i--;
            }
        }
        void merge2(vector<int> &nums1, int m, vector<int> &nums2, int n)
        {
            int i = m + n - 1;
            m--;
            n--;
            while (m >= 0 || n >= 0)
            {
                if (n < 0)
                    break;
                if (m >= 0 && nums1[m] > nums2[n])
                    nums1[i--] = nums1[m--];
                else
                    nums1[i--] = nums2[n--];
            }
        }
        // Another solution: shift elements in nums1 to the end, and then merge
        // with nums2 starting from the beginning of nums1.
        void merge3(vector<int> &nums1, int m, vector<int> &nums2, int n)
        {
            vector<int>::iterator it1 = nums1.begin();
            vector<int>::iterator it2 = nums2.begin();
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
        void merge4(vector<int> &nums1, int m, vector<int> &nums2, int n)
        {
            if (m < 0 || n < 0)
                return;
            int i = 0;
            int j = 0;
            while (i < m && j < n)
            {
                if (nums1[i] <= nums2[j])
                    i++;
                else
                {
                    for (int k = m; k > i; k--)
                    {
                        nums1[k] = nums1[k - 1];
                    }
                    nums1[i] = nums2[j];
                    m++;
                    i++;
                    j++;
                }
            }
            if (j < n)
            {
                for (int k = j; k < n; k++)
                {
                    nums1[i] = nums2[k];
                    i++;
                }
            }
        }
        void merge5(vector<int> &nums1, int m, vector<int> &nums2, int n)
        {
            if (m < 0 || n < 0)
                return;
            int i = m - 1;
            int j = n - 1;
            while (i >= 0 && j >= 0)
            {
                if (nums1[i] > nums2[j])
                {
                    nums1[i + j + 1] = nums1[i];
                    i--;
                }
                else
                {
                    nums1[i + j + 1] = nums2[j];
                    j--;
                }
            }
            if (j >= 0)
            {
                for (int p = j; p >= 0; p--)
                {
                    nums1[p] = nums2[p];
                }
            }
        }

        // 89. Gray Code
        // The gray code is a binary numeral system where two successive values differ
        // in only one bit. Given a non-negative integer n representing the total number
        // of bits in the code, print the sequence of gray code. A gray code sequence
        // must begin with 0.
        // Example 1:
        // Input: 2
        // Output: [0,1,3,2]
        // Explanation:
        // 00 - 0
        // 01 - 1
        // 11 - 3
        // 10 - 2
        // For a given n, a gray code sequence may not be uniquely defined.
        // For example, [0,2,3,1] is also a valid gray code sequence.
        // 00 - 0
        // 10 - 2
        // 11 - 3
        // 01 - 1
        // Example 2:
        // Input: 0
        // Output: [0]
        // Explanation: We define the gray code sequence to begin with 0.
        // A gray code sequence of n has size = 2^n, which for n = 0 the size is 2^0 = 1.
        // Therefore, for n = 0 the gray code sequence is [0].
        vector<int> grayCode(int n)
        {
            vector<int> g;
            if (n < 0)
                return g;
            g.push_back(0);
            int b = 1;
            for (int i = 0; i < n; i++)
            {
                int l = g.size();
                for (int j = l - 1; j >= 0; j--)
                    g.push_back(g[j] | b);
                b = b << 1;
            }
            return g;
        }
        vector<int> grayCode2(int n)
        {
            vector<int> codes = {};
            if (n <= 0 || n > 8 * (int)sizeof(int))
                return codes;
            function<void(int &, int)> toggle = [&](int &code, int position)
            {
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

        // 90. Subsets II
        // Given a collection of integers that might contain duplicates, nums, return
        // all possible subsets (the power set).
        // Note: The solution set must not contain duplicate subsets.
        // Example:
        // Input: [1,2,2]
        // Output:
        // [
        //   [2],
        //   [1],
        //   [1,2,2],
        //   [2,2],
        //   [1,2],
        //   []
        // ]
        vector<vector<int>> subsetsWithDup(vector<int> &nums)
        {
            vector<vector<int>> result = {{}};
            sort(nums.begin(), nums.end());
            size_t i = 0;
            while (i < nums.size())
            {
                size_t j = i;
                while (j + 1 < nums.size() && nums[j + 1] == nums[i])
                    j++;
                size_t m = result.size();
                for (size_t k = 0; k < m; k++)
                {
                    vector<int> r(result[k]);
                    for (size_t t = i; t <= j; t++)
                    {
                        r.push_back(nums[t]);
                        result.push_back(r);
                    }
                }
                i = j + 1;
            }
            return result;
        }
        vector<vector<int>> subsetsWithDup2(vector<int> &nums)
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
        vector<vector<int>> subsetsWithDup3(vector<int> &nums)
        {
            vector<vector<int>> output = {{}};
            sort(nums.begin(), nums.end());
            vector<int> d; // capture duplicates of a number
            size_t n = output.size();
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (!d.empty() && nums[i] != d.back())
                {
                    d.clear();
                    // capture output size before processing the new duplicates
                    // n should not change when processing the new duplicates
                    n = output.size();
                }
                d.push_back(nums[i]); // d contains one more duplicate of current number
                for (size_t j = 0; j < n; j++)
                {
                    vector<int> v(output[j]);
                    v.insert(v.end(), d.begin(), d.end());
                    output.push_back(v);
                }
            }
            return output;
        }
        vector<vector<int>> subsetsWithDup4(vector<int> &nums)
        {
            vector<vector<int>> output;
            sort(nums.begin(), nums.end());
            function<void(size_t, vector<int> &)> subset = [&](size_t i, vector<int> &v)
            {
                if (i >= nums.size())
                {
                    output.push_back(v);
                    return;
                }
                v.push_back(nums[i]);
                subset(i + 1, v);
                v.pop_back();
                while (i + 1 < nums.size() && nums[i] == nums[i + 1])
                    i++;
                subset(i + 1, v);
            };
            size_t i = 0;
            vector<int> v;
            subset(i, v);
            return output;
        }

        // 91. Decode Ways
        // A message containing letters from A-Z is being encoded to numbers using
        // the following mapping:
        // 'A' -> 1
        // 'B' -> 2
        // ...
        // 'Z' -> 26
        // Given a non-empty string containing only digits, determine the total number
        // of ways to decode it.
        // Example 1:
        // Input: "12"
        // Output: 2
        // Explanation: It could be decoded as "AB" (1 2) or "L" (12).
        // Example 2:
        // Input: "226"
        // Output: 3
        // Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2
        // 6).
        int numDecodings(const string &s)
        {
            if (s.empty())
                return 0;
            int i = (int)s.size() - 1;
            int c = s[i] == '0' ? 0 : 1;
            if (s.size() == 1)
                return c;
            i--;
            int b = s[i] == '0' ? 0 : c;
            if (s[i] == '1' || (s[i] == '2' && '0' <= s[i + 1] && s[i + 1] <= '6'))
                b += 1;
            i--;
            while (i >= 0)
            {
                int a = s[i] == '0' ? 0 : b;
                if (s[i] == '1' || (s[i] == '2' && '0' <= s[i + 1] && s[i + 1] <= '6'))
                    a += c;
                c = b;
                b = a;
                i--;
            }
            return b;
        }
        int numDecodings2(const string &s)
        {
            if (s.empty())
                return 0;
            int len = (int)s.size();
            function<int(int)> solve = [&](int i) -> int
            {
                if (i == len)
                    return 0;
                if (i == len - 1)
                    return s[i] == '0' ? 0 : 1;
                switch (s[i])
                {
                case '0':
                    return 0;
                case '1':
                    if (s[i + 1] == '0')
                    {
                        if (i + 2 == len)
                            return 1;
                        else if (s[i + 2] == '0')
                            return 0;
                        else
                            return solve(i + 2);
                    }
                    else
                    {
                        if (i + 2 == len)
                            return 2;
                        else if (s[i + 2] == '0')
                            return solve(i + 1);
                        else
                            return solve(i + 1) + solve(i + 2);
                    }
                case '2':
                    if (s[i + 1] == '0')
                    {
                        if (i + 2 == len)
                            return 1;
                        else if (s[i + 2] == '0')
                            return 0;
                        else
                            return solve(i + 2);
                    }
                    else if ('1' <= s[i + 1] && s[i + 1] <= '6')
                    {
                        if (i + 2 == len)
                            return 2;
                        else
                            return solve(i + 1) + solve(i + 2);
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
        int numDecodings3(const string &s)
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
                if ((s[i - 1] == '1' && s[i] >= '0' && s[i] <= '9') ||
                    (s[i - 1] == '2' && s[i] >= '0' && s[i] <= '6'))
                    c2 += c0;
                c0 = c1;
                c1 = c2;
            }
            return c2;
        }

        // 92. Reverse Linked List II
        // Reverse a linked list from position m to n. Do it in one-pass.
        // Note: 1 ≤ m ≤ n ≤ length of list.
        // Example:
        // Input: 1->2->3->4->5->NULL, m = 2, n = 4
        // Output: 1->4->3->2->5->NULL
        ListNode *reverseBetween(ListNode *head, int m, int n)
        {
            if (head == nullptr || m < 1 || n < m)
                return head;
            ListNode *p = nullptr; // p points to node at m - 1
            ListNode *q = head;    // q poinst to node at m
            int i = 1;
            while (i < m && q->next != nullptr)
            {
                if (i == m - 1)
                    p = q;
                i++;
                q = q->next;
            }
            if (i < m)
                return head;
            while (i < n && q->next != nullptr)
            {
                ListNode *t = q->next;
                q->next = t->next;
                if (p == nullptr) // m == 1
                {
                    t->next = head;
                    head = t;
                }
                else // m > 1
                {
                    t->next = p->next;
                    p->next = t;
                }
                i++;
            }
            return head;
        }
        ListNode *reverseBetween2(ListNode *head, int m, int n)
        {
            ListNode *p = nullptr; // node at m - 1
            int i = 1;
            ListNode *q = head; // node at n
            while (i < n && q != nullptr)
            {
                if (i == m - 1)
                    p = q;
                q = q->next;
                i++;
            }
            if (q == nullptr)
                return head;
            ListNode *t;
            if (p == nullptr)
            {
                while (head != q)
                {
                    t = head;
                    head = t->next;
                    t->next = q->next;
                    q->next = t;
                }
            }
            else
            {
                while (p->next != q)
                {
                    t = p->next;
                    p->next = t->next;
                    t->next = q->next;
                    q->next = t;
                }
            }
            return head;
        }
        ListNode *reverseBetween3(ListNode *head, int m, int n)
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
                head = pn;
            else
                pm_prev->next = pn;
            return head;
        }
        ListNode *reverseBetween4(ListNode *head, int m, int n)
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

        // 93. Restore IP Addresses
        // Given a string containing only digits, restore it by returning all possible
        // valid IP address combinations.
        // Example:
        // Input: "25525511135"
        // Output: ["255.255.11.135", "255.255.111.35"]
        vector<string> restoreIpAddresses(const string &s)
        {
            vector<string> ips;
            if (s.size() < 4)
                return ips;
            function<bool(int, int)> isValid = [&](int i, int j) -> bool
            {
                if (i > j || i + 3 <= j)
                    return false;
                if (s[i] == '0' && i < j)
                    return false;
                if (s[i] == '2' && i + 2 == j &&
                    (s[i + 1] > '5' || (s[i + 1] == '5' && s[j] > '5')))
                    return false;
                if (s[i] > '2' && i + 1 < j)
                    return false;
                return true;
            };
            int n = s.size();
            for (int i0 = 0; i0 < min(3, n); i0++)
            {
                if (!isValid(0, i0))
                    break;
                for (int i1 = i0 + 1; i1 < min(i0 + 4, n); i1++)
                {
                    if (!isValid(i0 + 1, i1))
                        break;
                    for (int i2 = i1 + 1; i2 < min(i1 + 4, n); i2++)
                    {
                        if (!isValid(i1 + 1, i2))
                            break;
                        if (!isValid(i2 + 1, n - 1))
                            continue;
                        string a;
                        a.append(s, 0, i0 + 1);
                        a.append(1, '.');
                        a.append(s, i0 + 1, i1 - i0);
                        a.append(1, '.');
                        a.append(s, i1 + 1, i2 - i1);
                        a.append(1, '.');
                        a.append(s, i2 + 1);
                        ips.push_back(a);
                    }
                }
            }
            return ips;
        }
        vector<string> restoreIpAddresses2(const string &s)
        {
            vector<string> result;
            function<void(int, int, string &)> solve = [&](int i, int j, string &p)
            {
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
        vector<string> restoreIpAddresses3(const string &s)
        {
            vector<string> ips;
            int len = s.length();
            if (len < 4 || len > 12)
                return ips;
            auto check = [&](const string &octet) -> bool
            {
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
                for (int j = i + 1; j <= (s[i] == '0' ? i + 1 : min(i + 3, len - 2));
                     j++)
                {
                    for (int k = j + 1;
                         k <= (s[j] == '0' ? j + 1 : min(j + 3, len - 1)); k++)
                    {
                        if ((len - k > 3) || (len - k > 1 && s[k] == '0'))
                            continue;
                        if (check(s.substr(0, i)) && check(s.substr(i, j - i)) &&
                            check(s.substr(j, k - j)) && check(s.substr(k, len - k)))
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
        vector<string> restoreIpAddresses4(const string &s)
        {
            vector<string> output;
            if (s.size() < 4 || 12 < s.size())
                return output;
            function<bool(size_t, size_t)> isvalid = [&](size_t i, size_t j) -> bool
            {
                if (j <= i || i + 3 < j)
                    return false;
                if (i + 1 == j)
                    return true;
                if (s[i] == '0')
                    return false;
                if (i + 2 == j)
                    return true;
                if (s[i] < '1' || s[i] > '2')
                    return false;
                if (s[i] == '1')
                    return true;
                return s[i + 1] < '5' || (s[i + 1] == '5' && s[i + 2] <= '5');
            };
            vector<size_t> d; // positions of dot
            size_t i = 1;
            while (true)
            {
                if (d.size() < 3 && isvalid(d.empty() ? 0 : d.back(), i))
                {
                    d.push_back(i);
                    i++;
                }
                else
                {
                    if (d.empty())
                        break;
                    if (d.size() == 3 && isvalid(d.back(), s.size()))
                    {
                        string t(s);
                        for (int j = (int)d.size() - 1; j >= 0; j--)
                        {
                            t.insert(d[j], 1, '.');
                        }
                        output.push_back(t);
                    }
                    i = d.back() + 1;
                    d.pop_back();
                }
            }
            return output;
        }
        vector<string> restoreIpAddresses5(const string &s)
        {
            vector<string> output;
            if (s.size() < 4 || 12 < s.size())
                return output;
            function<bool(size_t, size_t)> isvalid = [&](size_t i, size_t j) -> bool
            {
                return i + 1 == j || (i + 2 == j && s[i] != '0') || (i + 3 == j && (s[i] == '1' || (s[i] == '2' && (s[i + 1] < '5' || (s[i + 1] == '5' && s[i + 2] <= '5')))));
            };
            queue<vector<size_t>> q;
            q.push({0});
            while (!q.empty())
            {
                auto v = q.front();
                q.pop();
                if (v.size() == 4 && isvalid(v.back(), s.size()))
                {
                    string t(s);
                    for (int i = (int)v.size() - 1; i > 0; i--)
                        t.insert(v[i], 1, '.');
                    output.push_back(t);
                }
                if (v.size() < 4)
                {
                    for (size_t j = v.back() + 1; j <= min(s.size(), v.back() + 3); j++)
                    {
                        if (isvalid(v.back(), j))
                        {
                            vector<size_t> a(v);
                            a.push_back(j);
                            q.push(a);
                        }
                    }
                }
            }
            return output;
        }

        // 94. Binary Tree Inorder Traversal
        // Given a binary tree, return the inorder traversal of its nodes' values.
        // Example:
        // Input: [1,null,2,3]
        //    1
        //     \
        //      2
        //     /
        //    3
        // Output: [1,3,2]
        // Follow up: Recursive solution is trivial, could you do it iteratively?
        vector<int> inorderTraversal(TreeNode *root)
        {
            vector<int> v;
            stack<TreeNode *> s;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    v.push_back(s.top()->val);
                    n = s.top()->right;
                    s.pop();
                }
            }
            return v;
        }
        vector<int> inorderTraversal2(TreeNode *root)
        {
            vector<int> result;
            if (root == nullptr)
                return result;
            stack<TreeNode *> path;
            path.push(root);
            TreeNode *prev = nullptr;
            while (!path.empty())
            {
                TreeNode *node = path.top();
                if (node->right != nullptr && node->right == prev)
                {
                    path.pop();
                }
                else if (node->left != nullptr && node->left != prev)
                {
                    path.push(node->left);
                }
                else
                {
                    // left is null or left is just visited
                    result.push_back(node->val);
                    if (node->right != nullptr)
                        path.push(node->right);
                    else
                        path.pop();
                }
                prev = node;
            }
            return result;
        }
        vector<int> inorderTraversal3(TreeNode *root)
        {
            vector<int> result;
            if (root == nullptr)
                return result;
            stack<TreeNode *> path;
            path.push(root);
            set<TreeNode *> visited;
            while (!path.empty())
            {
                TreeNode *node = path.top();
                if (node->left == nullptr ||
                    visited.find(node->left) != visited.end())
                {
                    result.push_back(node->val);
                    path.pop();
                    visited.insert(node);
                    if (node->right != nullptr)
                        path.push(node->right);
                }
                else
                {
                    path.push(node->left);
                }
            }
            return result;
        }
        vector<int> inorderTraversal4(TreeNode *root)
        {
            vector<int> v;
            function<void(TreeNode *)> trav = [&](TreeNode *n)
            {
                if (n == nullptr)
                    return;
                trav(n->left);
                v.push_back(n->val);
                trav(n->right);
            };
            trav(root);
            return v;
        }

        // 95. Unique Binary Search Trees II
        // Given an integer n, generate all structurally unique BST's (binary
        // search trees) that store values 1 ... n.
        // Example:
        // Input: 3
        // Output:
        // [
        //   [1,null,3,2],
        //   [3,2,null,1],
        //   [3,1,null,null,2],
        //   [2,1,3],
        //   [1,null,2,null,3]
        // ]
        // Explanation:
        // The above output corresponds to the 5 unique BST's shown below:
        //    1         3     3      2      1
        //     \       /     /      / \      \
        //      3     2     1      1   3      2
        //     /     /       \                 \
        //    2     1         2                 3
        vector<TreeNode *> generateTrees(int n)
        {
            function<TreeNode *(TreeNode *)> clone = [&](TreeNode *m) -> TreeNode *
            {
                if (m == nullptr)
                    return nullptr;
                TreeNode *c = new TreeNode(m->val);
                c->left = clone(m->left);
                c->right = clone(m->right);
                return c;
            };
            function<void(TreeNode *)> deleteTree = [&](TreeNode *m)
            {
                if (m == nullptr)
                    return;
                deleteTree(m->left);
                m->left = nullptr;
                deleteTree(m->right);
                m->right = nullptr;
                delete m;
            };
            function<vector<TreeNode *>(int, int)> bst =
                [&](int i, int j) -> vector<TreeNode *>
            {
                vector<TreeNode *> v;
                if (i > j)
                    return v;
                for (int k = i; k <= j; k++)
                {
                    TreeNode *m = new TreeNode(k);
                    vector<TreeNode *> vl = bst(i, k - 1);
                    vector<TreeNode *> vr = bst(k + 1, j);
                    if (vl.empty() && vr.empty())
                    {
                        v.push_back(m);
                    }
                    else if (vl.empty())
                    {
                        for (size_t r = 0; r < vr.size(); r++)
                        {
                            TreeNode *c = clone(m);
                            c->right = clone(vr[r]);
                            v.push_back(c);
                        }
                        for (size_t r = 0; r < vr.size(); r++)
                            deleteTree(vr[r]);
                        delete m;
                    }
                    else if (vr.empty())
                    {
                        for (size_t l = 0; l < vl.size(); l++)
                        {
                            TreeNode *c = clone(m);
                            c->left = clone(vl[l]);
                            v.push_back(c);
                        }
                        for (size_t l = 0; l < vl.size(); l++)
                            deleteTree(vl[l]);
                        delete m;
                    }
                    else
                    {
                        for (size_t l = 0; l < vl.size(); l++)
                        {
                            for (size_t r = 0; r < vr.size(); r++)
                            {
                                TreeNode *c = clone(m);
                                c->left = clone(vl[l]);
                                c->right = clone(vr[r]);
                                v.push_back(c);
                            }
                        }
                        for (size_t l = 0; l < vl.size(); l++)
                            deleteTree(vl[l]);
                        for (size_t r = 0; r < vr.size(); r++)
                            deleteTree(vr[r]);
                        delete m;
                    }
                }
                return v;
            };
            return bst(1, n);
        }
        vector<TreeNode *> generateTrees2(int n)
        {
            if (n <= 0)
                return vector<TreeNode *>{};
            function<vector<vector<int>>(int, int)> generateSerializations =
                [&](int i, int j) -> vector<vector<int>>
            {
                vector<vector<int>> serializations;
                if (i > j)
                {
                    // Empty tree
                    serializations.push_back(vector<int>{0});
                }
                else
                {
                    for (int k = i; k <= j; k++)
                    {
                        vector<vector<int>> leftSerializations =
                            generateSerializations(i, k - 1);
                        vector<vector<int>> rightSerializations =
                            generateSerializations(k + 1, j);
                        // left and right vectors are guaranteed not empty
                        for (size_t l = 0; l < leftSerializations.size(); l++)
                        {
                            for (size_t r = 0; r < rightSerializations.size(); r++)
                            {
                                vector<int> serialization = {k};
                                serialization.insert(serialization.end(),
                                                     leftSerializations[l].begin(),
                                                     leftSerializations[l].end());
                                serialization.insert(serialization.end(),
                                                     rightSerializations[r].begin(),
                                                     rightSerializations[r].end());
                                serializations.push_back(serialization);
                            }
                        }
                    }
                }
                return serializations;
            };
            function<TreeNode *(size_t &, vector<int> &)> generateTree =
                [&](size_t &i, vector<int> &serialization) -> TreeNode *
            {
                if (i >= serialization.size())
                    return nullptr;
                if (serialization[i] == 0)
                {
                    i++;
                    return nullptr;
                }
                TreeNode *node = new TreeNode(serialization[i++]);
                // nullptr serialized as 0 so can just deserialize it
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
        vector<TreeNode *> generateTrees3(int n)
        {
            // Generate all the preorder serializations
            function<vector<vector<int>>(int, int)> generate =
                [&](int i, int j) -> vector<vector<int>>
            {
                if (i > j)
                    return vector<vector<int>>();
                vector<vector<int>> result;
                for (int k = i; k <= j; k++)
                {
                    vector<vector<int>> left = generate(i, k - 1);
                    vector<vector<int>> right = generate(k + 1, j);
                    if (left.empty() && right.empty())
                    {
                        result.push_back({k});
                    }
                    else if (left.empty())
                    {
                        for (const auto &r : right)
                        {
                            vector<int> t = {k};
                            t.insert(t.end(), r.begin(), r.end());
                            result.push_back(t);
                        }
                    }
                    else if (right.empty())
                    {
                        for (const auto &l : left)
                        {
                            vector<int> t = {k};
                            t.insert(t.end(), l.begin(), l.end());
                            result.push_back(t);
                        }
                    }
                    else
                    {
                        for (const auto &l : left)
                        {
                            for (const auto &r : right)
                            {
                                vector<int> t = {k};
                                t.insert(t.end(), l.begin(), l.end());
                                t.insert(t.end(), r.begin(), r.end());
                                result.push_back(t);
                            }
                        }
                    }
                }
                return result;
            };
            // Build a tree from a preorder serialization
            // The tree is built from t[i] to t[j] where t[j] <= p
            function<TreeNode *(const vector<int> &, int &, int)> build =
                [&](const vector<int> &t, int &i, int p) -> TreeNode *
            {
                if (i < 0 || i >= (int)t.size() || p < t[i])
                    return nullptr;
                TreeNode *node = new TreeNode(t[i++]);
                if (i < (int)t.size() && node->val > t[i])
                    node->left = build(t, i, node->val); // use node->val to indicate the end of left tree
                if (i < (int)t.size() && p > t[i])
                    node->right = build(t, i, p); // use the parent value p to indicate the end of right tree
                return node;
            };
            vector<vector<int>> preorders = generate(1, n);
            vector<TreeNode *> trees;
            for (const auto &t : preorders)
            {
                int i = 0;
                trees.push_back(build(t, i, n + 1));
            }
            return trees;
        }
        vector<TreeNode *> generateTrees4(int n)
        {
            // generate all preorder serializations
            function<vector<vector<int>>(int, int)> serialize = [&](int i, int j) -> vector<vector<int>>
            {
                vector<vector<int>> output;
                if (i > j)
                {
                    output.push_back(vector<int>{0});
                }
                else
                {
                    for (int k = i; k <= j; k++)
                    {
                        vector<int> v = {k};
                        vector<vector<int>> left = serialize(i, k - 1);
                        vector<vector<int>> right = serialize(k + 1, j);
                        for (const auto &l : left)
                        {
                            for (const auto &r : right)
                            {
                                vector<int> v = {k};
                                v.insert(v.end(), l.begin(), l.end());
                                v.insert(v.end(), r.begin(), r.end());
                                output.push_back(v);
                            }
                        }
                    }
                }
                return output;
            };
            // generate a tree from a preorder serialization
            function<TreeNode *(const vector<int> &)> generate = [&](const vector<int> &v) -> TreeNode *
            {
                TreeNode *t = nullptr;
                stack<TreeNode *> s;
                TreeNode *n = nullptr;
                size_t i = 0;
                bool left = true;
                while (i < v.size())
                {
                    if (v[i] != 0)
                    {
                        n = new TreeNode(v[i]);
                        if (t == nullptr)
                            t = n;
                        if (!s.empty())
                        {
                            if (left)
                            {
                                s.top()->left = n;
                            }
                            else
                            {
                                s.top()->right = n;
                                left = true;
                            }
                        }
                        s.push(n);
                    }
                    else
                    {
                        if (left)
                        {
                            // build right subtree
                            left = false;
                        }
                        else
                        {
                            // right child is nullptr.
                            // pop the insert point and its parents
                            // whose right subtree is complete.
                            while (!s.empty())
                            {
                                n = s.top();
                                s.pop();
                                if (s.empty() || n == s.top()->left)
                                    break;
                            }
                        }
                    }
                    i++;
                }
                return t;
            };
            auto serializations = serialize(1, n);
            vector<TreeNode *> trees;
            for (const auto &v : serializations)
            {
                trees.push_back(generate(v));
            }
            return trees;
        }
        vector<TreeNode *> generateTrees5(int n)
        {
            function<vector<vector<int>>(int, int)> serialize = [&](int i, int j) -> vector<vector<int>>
            {
                vector<vector<int>> output;
                if (i > j)
                {
                    output.push_back(vector<int>{0});
                }
                else
                {
                    for (int k = i; k <= j; k++)
                    {
                        vector<int> v = {k};
                        vector<vector<int>> left = serialize(i, k - 1);
                        vector<vector<int>> right = serialize(k + 1, j);
                        for (const auto &l : left)
                        {
                            for (const auto &r : right)
                            {
                                vector<int> v = {k};
                                v.insert(v.end(), l.begin(), l.end());
                                v.insert(v.end(), r.begin(), r.end());
                                output.push_back(v);
                            }
                        }
                    }
                }
                return output;
            };
            function<TreeNode *(const vector<int> &)> generate = [&](const vector<int> &v) -> TreeNode *
            {
                TreeNode *t = nullptr;
                stack<TreeNode *> s;
                TreeNode *n = nullptr;
                size_t i = 0;
                bool left = true;
                while (i < v.size())
                {
                    if (v[i] != 0)
                    {
                        n = new TreeNode(v[i]);
                        if (t == nullptr)
                            t = n;
                        if (!s.empty())
                        {
                            if (left)
                            {
                                s.top()->left = n;
                            }
                            else
                            {
                                s.top()->right = n;
                                left = true;
                            }
                        }
                        s.push(n);
                        i++; // next node
                    }
                    else
                    {
                        if (left)
                        {
                            left = false;
                            i++; // next node
                        }
                        else
                        {
                            if (!s.empty())
                            {
                                n = s.top();
                                s.pop();
                                if (!s.empty() && n == s.top()->right)
                                {
                                    // n is complete and is its parents right child
                                    // so its parent is also complete. do not move
                                    // to next, continue to pop its parent.
                                    continue;
                                }
                            }
                            i++;
                        }
                    }
                }
                return t;
            };
            auto serializations = serialize(1, n);
            vector<TreeNode *> trees;
            for (const auto &v : serializations)
            {
                trees.push_back(generate(v));
            }
            return trees;
        }

        // 96. Unique Binary Search Trees
        // Given n, how many structurally unique BST's (binary search trees)
        // that store values 1 ... n?
        // Example:
        // Input: 3
        // Output: 5
        // Explanation:
        // Given n = 3, there are a total of 5 unique BST's:
        //    1         3     3      2      1
        //     \       /     /      / \      \
        //      3     2     1      1   3      2
        //     /     /       \                 \
        //    2     1         2                 3
        // Let S_n be the number of trees given n, then
        // S_n = S_0 * S_(n-1) + S_1 * S_(n-2) + ... + S_(n-2) * S_1 + S_(n-1) * S_0
        // where
        // S_0 * S_(n-1) is the number of trees where value 1 is the root and
        // values [2..n] are in the right subtree,
        // S_(n-1) * S_0 is the number of trees where value n is the root and
        // values [1..(n-1)] are in the left subtree,
        // S_i * S_(n-1-i) is the number of trees where value (i+1) is the root and
        // values [1..i] are in the left subtree and values [(i+2)..n] are in
        // the right subtree.
        int numTrees(int n)
        {
            vector<int> c(n + 1, 0);
            c[0] = 1;
            c[1] = 1;
            for (int i = 2; i <= n; i++)
            {
                int j = 0;
                int k = i - 1;
                while (j < k)
                {
                    c[i] += ((c[j] * c[k]) << 1);
                    j++;
                    k--;
                }
                if (j == k)
                    c[i] += c[j] * c[k];
            }
            return c[n];
        }
        int numTrees2(int n)
        {
            if (n <= 0)
                return 0;
            map<pair<int, int>, int> solved;
            function<int(int, int)> count = [&](int i, int j) -> int
            {
                if (i >= j)
                    return 1;
                pair<int, int> p = make_pair(i, j);
                if (solved.find(p) != solved.end())
                    return solved[p];
                int c = 0;
                for (int k = i; k <= j; k++)
                    c += (count(i, k - 1) * count(k + 1, j));
                solved[p] = c;
                return c;
            };
            return count(1, n);
        }
        // c[n] = c[0]*c[n-1] + c[1]*c[n-2] + ... + c[n-2]*c[1] + c[n-1]*c[0]
        int numTrees3(int n)
        {
            if (n <= 0)
                return 0;
            vector<int> count(n + 1, 0);
            count[0] = 1;
            for (int i = 1; i <= n; i++)
            {
                for (int j = 0; j < i; j++)
                    count[i] += count[j] * count[i - j - 1];
            }
            return count[n];
        }

        // 97. Interleaving String
        // Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
        // Example 1:
        // Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
        // Output: true
        // Example 2:
        // Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
        // Output: false
        bool isInterleave(const string &s1, const string &s2, const string &s3)
        {
            // Check if s3[0..k] is interleaved of s1[0..i] and s2[0..j]
            function<bool(int, int, int)> solve = [&](int i, int j, int k) -> bool
            {
                if (i + j != k - 1)
                    return false;
                if (i == -1)
                    return s2.substr(0, j + 1).compare(s3.substr(0, k + 1)) == 0;
                if (j == -1)
                    return s1.substr(0, i + 1).compare(s3.substr(0, k + 1)) == 0;
                if (s1[i] == s3[k] && solve(i - 1, j, k - 1))
                    return true;
                if (s2[j] == s3[k] && solve(i, j - 1, k - 1))
                    return true;
                return false;
            };
            return solve((int)s1.size() - 1, (int)s2.size() - 1, (int)s3.size() - 1);
        }
        //   j 0 1 2
        // i 0
        //   1
        //   2
        // Let M[i][j] indicates whether s3[0..i+j-1] is interleave of s1[0..i-1] and
        // s2[0..j-1], then
        // M[i][j] =   s1[i-1] == s3[i+j-1] && M[i-1][j]
        //          || s2[j-1] == s3[i+j-1] && M[i][j-1]
        bool isInterleave2(const string &s1, const string &s2, const string &s3)
        {
            if (s3.length() != s1.length() + s2.length())
                return false;
            if (s3.length() == 0)
                return true;
            vector<bool> match(1 + s2.size(), true);
            for (size_t j = 1; j <= s2.size(); j++)
                match[j] = match[j - 1] && s2[j - 1] == s3[j - 1]; // M[0][j]
            for (size_t i = 1; i <= s1.size(); i++)
            {
                match[0] = match[0] && s1[i - 1] == s3[i - 1]; // M[i][0]
                for (size_t j = 1; j <= s2.size(); j++)
                {
                    match[j] = (match[j] && s1[i - 1] == s3[i + j - 1]) ||
                               (match[j - 1] && s2[j - 1] == s3[i + j - 1]); // M[i][j]
                }
            }
            return match[s2.size()];
        }

        // 98. Validate Binary Search Tree
        // Given a binary tree, determine if it is a valid binary search tree (BST).
        // Assume a BST is defined as follows: The left subtree of a node contains
        // only nodes with keys less than the node's key. The right subtree of a node
        // contains only nodes with keys greater than the node's key. Both the left
        // and right subtrees must also be binary search trees.
        // Example 1:
        //     2
        //    / \
        //   1   3
        // Input: [2,1,3]
        // Output: true
        // Example 2:
        //     5
        //    / \
        //   1   4
        //      / \
        //     3   6
        // Input: [5,1,4,null,null,3,6]
        // Output: false
        // Explanation: The root node's value is 5 but its right child's value is 4.
        // In-order traverse and check whether values are increasing.
        bool isValidBST(TreeNode *root)
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
        bool isValidBST2(TreeNode *root)
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
        bool isValidBST3(TreeNode *root)
        {
            function<bool(TreeNode *, int &, int &)> verify =
                [&](TreeNode *node, int &min, int &max) -> bool
            {
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
        bool isValidBST4(TreeNode *root)
        {
            function<bool(TreeNode *, int &, int &)> isValid =
                [&](TreeNode *node, int &min, int &max) -> bool
            {
                if (node == nullptr)
                    return true;
                min = node->val;
                max = node->val;
                if (node->left != nullptr)
                {
                    int lmin;
                    int lmax;
                    if (!isValid(node->left, lmin, lmax))
                        return false;
                    if (lmax >= node->val)
                        return false;
                    min = lmin;
                }
                if (node->right != nullptr)
                {
                    int rmin;
                    int rmax;
                    if (!isValid(node->right, rmin, rmax))
                        return false;
                    if (rmin <= node->val)
                        return false;
                    max = rmax;
                }
                return true;
            };
            int tmin;
            int tmax;
            return isValid(root, tmin, tmax);
        }
        bool isValidBST5(TreeNode *root)
        {
            // node value must be in [l, h]
            function<bool(TreeNode *, long, long)> check = [&](TreeNode *n, long l, long h) -> bool
            {
                if (n == nullptr)
                    return true;
                long v = n->val; // use long to avoid overflow if node value is INT_MIN or INT_MAX
                if (v < l || h < v)
                    return false;
                // left tree must be less than v, so range [l, v - 1]
                // right tree must be greater than v, so range [v + 1, h]
                return check(n->left, l, v - 1) && check(n->right, v + 1, h);
            };
            // node value is int type
            return check(root, INT_MIN, INT_MAX);
        }

        // 99. Recover Binary Search Tree
        // Two elements of a binary search tree (BST) are swapped by mistake.
        // Recover the tree without changing its structure.
        // Example 1:
        // Input: [1,3,null,null,2]
        //    1
        //   /
        //  3
        //   \
        //    2
        // Output: [3,1,null,null,2]
        //    3
        //   /
        //  1
        //   \
        //    2
        // Example 2:
        // Input: [3,1,4,null,null,2]
        //   3
        //  / \
        // 1   4
        //    /
        //   2
        // Output: [2,1,4,null,null,3]
        //   2
        //  / \
        // 1   4
        //    /
        //   3
        // Follow up:
        // A solution using O(n) space is pretty straight forward.
        // Could you devise a constant space solution? (Morris Traversal,
        // https://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html)
        void recoverTree(TreeNode *root)
        {
            TreeNode *a = nullptr;
            TreeNode *b = nullptr;
            stack<TreeNode *> s;
            TreeNode *p = nullptr;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    n = s.top();
                    s.pop();
                    if (p != nullptr && p->val > n->val)
                    {
                        if (a == nullptr)
                        {
                            // First inverse
                            // This will be the only inverse if the swapped
                            // nodes are neighbors
                            a = p;
                            b = n;
                        }
                        else
                        {
                            // Second inverse
                            // This may happen if the swapped nodes are
                            // not neighbors
                            b = n;
                            break;
                        }
                    }
                    p = n;
                    n = n->right;
                }
            }
            if (a != nullptr && b != nullptr)
            {
                int t = a->val;
                a->val = b->val;
                b->val = t;
            }
        }
        void recoverTree2(TreeNode *root)
        {
            if (root == nullptr || (root->left == nullptr && root->right == nullptr))
                return;
            function<void(TreeNode *, TreeNode *&, TreeNode *&, TreeNode *&,
                          TreeNode *&, TreeNode *&)>
                search = [&](TreeNode *current, TreeNode *&prev, TreeNode *&n1,
                             TreeNode *&n2, TreeNode *&n3, TreeNode *&n4)
            {
                if (current == nullptr)
                    return;
                search(current->left, prev, n1, n2, n3, n4);
                if (prev != nullptr && prev->val > current->val)
                {
                    if (n1 == nullptr && n2 == nullptr)
                    {
                        n1 = prev;
                        n2 = current;
                    }
                    else
                    {
                        n3 = prev;
                        n4 = current;
                        return;
                    }
                }
                prev = current;
                search(current->right, prev, n1, n2, n3, n4);
            };
            TreeNode *prev = nullptr;
            TreeNode *n1 = nullptr;
            TreeNode *n2 = nullptr;
            TreeNode *n3 = nullptr;
            TreeNode *n4 = nullptr;
            search(root, prev, n1, n2, n3, n4);
            if (n3 == nullptr && n4 == nullptr && n1 != nullptr && n2 != nullptr)
            {
                int t = n1->val;
                n1->val = n2->val;
                n2->val = t;
            }
            else if (n3 != nullptr && n4 != nullptr && n1 != nullptr &&
                     n2 != nullptr)
            {
                int t = n1->val;
                n1->val = n4->val;
                n4->val = t;
            }
        }

    } // namespace LeetCode
} // namespace Test

#endif
