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
            function<int(int, int)> expand = [&](int i, int j) -> int {
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
                expand = [&](int l, int r) -> pair<int, int> {
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
        int myAtoi(string str)
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
        int myAtoi2(string str)
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
        int myAtoi3(string str)
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
                                                          size_t i) -> size_t {
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
                                                                 size_t i) {
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
                              map<char, vector<char>> &m, vector<string> &o) {
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

    } // namespace LeetCode
} // namespace Test

#endif
