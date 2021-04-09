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

        // 167. Two Sum II - Input array is sorted
        // Given an array of integers that is already sorted in ascending order, find
        // two numbers such that they add up to a specific target number. The function
        // twoSum should return indices of the two numbers such that they add up to the
        // target, where index1 must be less than index2. Note: Your returned answers
        // (both index1 and index2) are not zero-based. You may assume that each input
        // would have exactly one solution and you may not use the same element twice.
        // Example:
        // Input: numbers = [2,7,11,15], target = 9
        // Output: [1,2]
        // Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
        vector<int> twoSumII(const vector<int> &numbers, int target)
        {
            int i = 0;
            int j = numbers.size() - 1;
            while (i < j)
            {
                int t = numbers[i] + numbers[j];
                if (t < target)
                    i++;
                else if (t > target)
                    j--;
                else
                    break;
            }
            return {i + 1, j + 1};
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
                            twosum[t].begin(), twosum[t].end(), [&](pair<int, int> p) {
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
        vector<vector<int>> fourSum3(vector<int> &num, int target)
        {
            if (num.size() < 4)
                return vector<vector<int>>{};
            sort(num.begin(), num.end());
            function<void(vector<int> &, int, int, const vector<int> &,
                          vector<vector<int>> &)>
                solve = [&](vector<int> &n, int i, int t, const vector<int> &s,
                            vector<vector<int>> &o) {
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
        vector<vector<int>> fourSum4(vector<int> &num, int target)
        {
            if (num.size() < 4)
                return vector<vector<int>>{};
            sort(num.begin(), num.end());
            function<void(vector<int> &, int, int, int, const vector<int> &,
                          vector<vector<int>> &)>
                solve = [&](vector<int> &n, int i, int r, int t, const vector<int> &s,
                            vector<vector<int>> &o) {
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
        vector<vector<int>> fourSum5(vector<int> &nums, int target)
        {
            vector<vector<int>> result;
            sort(nums.begin(), nums.end());
            vector<vector<int>> tuple(1, vector<int>{});
            size_t i = 0;
            while (i < nums.size())
            {
                size_t j = i;
                while (j + 1 < nums.size() && nums[j + 1] == nums[j])
                    j++;
                // nums[i..j] are the same
                size_t m = tuple.size();
                vector<int> c;
                for (size_t k = i; k <= j && k < i + 4; k++)
                {
                    c.push_back(nums[k]);
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
                [&](int a, int b, int c, int d) {
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
                [&](const vector<int> &v, int &i) -> int {
                int s = 1;
                while (i + 1 < (int)v.size() && v[i] == v[i + 1])
                {
                    i++;
                    s++;
                }
                return s;
            };
            function<int(const vector<int> &, int &)> decrease =
                [&](const vector<int> &v, int &i) -> int {
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
                [&](int k, int a, int b, int c, int d) {
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
                [&](const vector<int> &s, const vector<int> &l) -> double {
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

    } // namespace LeetCode
} // namespace Test

#endif
