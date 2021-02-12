#ifndef _LEETCODE2_H_
#define _LEETCODE2_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 257. Binary Tree Paths
        // Given a binary tree, return all root-to-leaf paths.
        // Note: A leaf is a node with no children.
        // Example:
        // Input:
        //    1
        //  /   \
        // 2     3
        //  \
        //   5
        // Output: ["1->2->5", "1->3"]
        // Explanation: All root-to-leaf paths are: 1->2->5, 1->3
        vector<string> binaryTreePaths(TreeNode *root)
        {
            vector<TreeNode *> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            vector<string> paths;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push_back(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.back();
                    if (t->left == nullptr && t->right == nullptr)
                    {
                        ostringstream ss;
                        for (size_t i = 0; i < s.size(); i++)
                        {
                            if (i > 0)
                                ss << "->";
                            ss << s[i]->val;
                        }
                        paths.push_back(ss.str());
                    }
                    if (t->right == nullptr || t->right == last)
                    {
                        s.pop_back();
                    }
                    else
                    {
                        n = t->right;
                    }
                    last = t;
                }
            }
            return paths;
        }

        // 258. Add Digits
        // Given a non-negative integer num, repeatedly add all its digits
        // until the result has only one digit.
        // Example:
        // Input: 38
        // Output: 2
        // Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
        // Since 2 has only one digit, return it.
        // Follow up:
        // Could you do it without any loop/recursion in O(1) runtime?
        // Digital Root
        int addDigits(int num)
        {
            while (num >= 10)
            {
                int s = 0;
                while (num > 0)
                {
                    s += num % 10;
                    num /= 10;
                }
                num = s;
            }
            return num;
        }

        // 260. Single Number III
        // Given an integer array nums, in which exactly two elements appear only once and
        // all the other elements appear exactly twice. Find the two elements that appear only
        // once. You can return the answer in any order.
        // Follow up: Your algorithm should run in linear runtime complexity.
        // Could you implement it using only constant space complexity?
        // Example 1:
        // Input: nums = [1,2,1,3,2,5]
        // Output: [3,5]
        // Explanation:  [5, 3] is also a valid answer.
        // Example 2:
        // Input: nums = [-1,0]
        // Output: [-1,0]
        // Example 3:
        // Input: nums = [0,1]
        // Output: [1,0]
        // Constraints:
        // 2 <= nums.length <= 3 * 10^4
        // -2^31 <= nums[i] <= 2^31 - 1
        // Each integer in nums will appear twice, only two integers will appear once.
        vector<int> singleNumber(vector<int> &nums)
        {
            long long x = 0; // must be long long
            for (const int &n : nums)
            {
                x ^= n;
            }
            int n1 = 0;
            int n2 = 0;
            x = x & (-x);
            for (const int &n : nums)
            {
                if (x & n)
                    n1 ^= n; // must use xor
                else
                    n2 ^= n;
            }
            return vector<int>{n1, n2};
        }
        vector<int> singleNumber2(vector<int> &nums)
        {
            set<int> s;
            for (const int n : nums)
            {
                if (s.find(n) == s.end())
                    s.insert(n);
                else
                    s.erase(n);
            }
            return vector<int>(s.cbegin(), s.cend());
        }

    } // namespace LeetCode
} // namespace Test

#endif
