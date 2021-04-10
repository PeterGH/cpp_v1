#ifndef _LEETCODE3_H_
#define _LEETCODE3_H_

#include "LeetCode.h"

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        // 301. Remove Invalid Parentheses
        // Remove the minimum number of invalid parentheses in order to make the input string valid.
        // Return all possible results.
        // Note: The input string may contain letters other than the parentheses ( and ).
        // Example 1:
        // Input: "()())()"
        // Output: ["()()()", "(())()"]
        // Example 2:
        // Input: "(a)())()"
        // Output: ["(a)()()", "(a())()"]
        // Example 3:
        // Input: ")("
        // Output: [""]
        vector<string> removeInvalidParentheses(string s)
        {
            vector<string> output;
            deque<char> d;
            for (const char &c : s)
            {
                if (c == '(')
                {
                    d.push_back(c);
                }
                else if (c == ')')
                {
                    if (!d.empty() && d.back() == '(')
                        d.pop_back();
                    else
                        d.push_back(c);
                }
            }
            function<void(size_t, string, int, int, const queue<char> &)> remove =
                [&](size_t i, string v, int l, int r, const queue<char> &q) {
                    while (i < s.size() && s[i] != '(' && s[i] != ')')
                    {
                        v.append(1, s[i++]);
                    }
                    if (i >= s.size())
                    {
                        // Need to remove duplicates
                        if (l == r && q.empty() && find(output.begin(), output.end(), v) == output.end())
                            output.push_back(v);
                        return;
                    }
                    // If we have "))" and need to remove one ')', the logic below will generate duplicates.
                    // Same will happen if need to remove two ')'s from ")))".
                    if (!q.empty() && s[i] == q.front())
                    {
                        queue<char> q1(q);
                        q1.pop();
                        remove(i + 1, v, l, r, q1);
                    }
                    if (s[i] == '(')
                    {
                        v.append(1, '(');
                        remove(i + 1, v, l + 1, r, q);
                    }
                    else if (l > r)
                    {
                        v.append(1, ')');
                        remove(i + 1, v, l, r + 1, q);
                    }
                };
            queue<char> e(d);
            string o;
            remove(0, o, 0, 0, e);
            return output;
        }
        vector<string> removeInvalidParentheses2(string s)
        {
            vector<string> output;
            deque<char> d;
            for (const char &c : s)
            {
                if (c == '(')
                {
                    d.push_back(c);
                }
                else if (c == ')')
                {
                    if (!d.empty() && d.back() == '(')
                        d.pop_back();
                    else
                        d.push_back(c);
                }
            }
            function<void(size_t, string, int, int, const queue<char> &)> remove =
                [&](size_t i, string v, int l, int r, const queue<char> &q) {
                    while (i < s.size() && s[i] != '(' && s[i] != ')')
                    {
                        v.append(1, s[i++]);
                    }
                    if (i >= s.size())
                    {
                        if (l == r && q.empty())
                            output.push_back(v);
                        return;
                    }
                    if (!q.empty() && s[i] == q.front())
                    {
                        queue<char> q1(q);
                        q1.pop();
                        remove(i + 1, v, l, r, q1);
                        while (i + 1 < s.size() && s[i] == s[i + 1])
                        {
                            i++;
                            v.append(1, s[i]);
                            if (s[i] == '(')
                            {
                                l++;
                            }
                            else
                            {
                                r++;
                            }
                        }
                    }
                    if (s[i] == '(')
                    {
                        v.append(1, '(');
                        remove(i + 1, v, l + 1, r, q);
                    }
                    else if (l > r)
                    {
                        v.append(1, ')');
                        remove(i + 1, v, l, r + 1, q);
                    }
                };
            queue<char> e(d);
            string o;
            remove(0, o, 0, 0, e);
            return output;
        }

        // 303. Range Sum Query - Immutable
        // Given an integer array nums, find the sum of the elements between indices i and j (i <= j), inclusive.
        // Implement the NumArray class:
        // NumArray(int[] nums) Initializes the object with the integer array nums.
        // int sumRange(int i, int j) Return the sum of the elements of the nums array in the range [i, j] inclusive
        // (i.e., sum(nums[i], nums[i + 1], ... , nums[j]))
        // Example 1:
        // Input
        // ["NumArray", "sumRange", "sumRange", "sumRange"]
        // [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
        // Output
        // [null, 1, -1, -3]
        // Explanation
        // NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
        // numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
        // numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1))
        // numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))
        // Constraints:
        // 0 <= nums.length <= 10^4
        // -10^5 <= nums[i] <= 10^5
        // 0 <= i <= j < nums.length
        // At most 10^4 calls will be made to sumRange.
        class NumArray
        {
        private:
            vector<int> acc;

        public:
            NumArray(vector<int> &nums)
            {
                acc.resize(nums.size());
                int a = 0;
                for (size_t i = 0; i < nums.size(); i++)
                {
                    a += nums[i];
                    acc[i] = a;
                }
            }

            int sumRange(int i, int j)
            {
                int s = acc[j];
                if (i > 0)
                    s -= acc[i - 1];
                return s;
            }
        };

        // 304. Range Sum Query 2D - Immutable
        // Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined
        // by its upper left corner (row1, col1) and lower right corner (row2, col2).
        // Range Sum Query 2D
        // The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and
        // (row2, col2) = (4, 3), which contains sum = 8.
        // Example:
        // Given matrix = [
        //   [3, 0, 1, 4, 2],
        //   [5, 6, 3, 2, 1],
        //   [1, 2, 0, 1, 5],
        //   [4, 1, 0, 1, 7],
        //   [1, 0, 3, 0, 5]
        // ]
        // sumRegion(2, 1, 4, 3) -> 8
        // sumRegion(1, 1, 2, 2) -> 11
        // sumRegion(1, 2, 2, 4) -> 12
        // Note:
        // You may assume that the matrix does not change.
        // There are many calls to sumRegion function.
        // You may assume that row1 <= row2 and col1 <= col2.
        class NumMatrix
        {
        private:
            vector<vector<int>> acc;

        public:
            NumMatrix(vector<vector<int>> &matrix)
            {
                acc.resize(matrix.size());
                for (size_t i = 0; i < matrix.size(); i++)
                {
                    acc[i].resize(matrix[i].size());
                    for (size_t j = 0; j < matrix[i].size(); j++)
                    {
                        if (i == 0 && j == 0)
                        {
                            acc[i][j] = matrix[i][j];
                        }
                        else if (i == 0 && j > 0)
                        {
                            acc[i][j] = acc[i][j - 1] + matrix[i][j];
                        }
                        else if (i > 0 && j == 0)
                        {
                            acc[i][j] = acc[i - 1][j] + matrix[i][j];
                        }
                        else
                        {
                            acc[i][j] = acc[i][j - 1] + acc[i - 1][j] - acc[i - 1][j - 1] + matrix[i][j];
                        }
                    }
                }
            }

            int sumRegion(int row1, int col1, int row2, int col2)
            {
                int s = acc[row2][col2];
                if (row1 == 0 && col1 > 0)
                {
                    s -= acc[row2][col1 - 1];
                }
                else if (row1 > 0 && col1 == 0)
                {
                    s -= acc[row1 - 1][col2];
                }
                else if (row1 > 0 && col1 > 0)
                {
                    s = s - acc[row2][col1 - 1] - acc[row1 - 1][col2] + acc[row1 - 1][col1 - 1];
                }
                return s;
            }
        };

        // 306. Additive Number
        // Additive number is a string whose digits can form additive sequence.
        // A valid additive sequence should contain at least three numbers. Except
        // for the first two numbers, each subsequent number in the sequence must
        // be the sum of the preceding two. Given a string containing only digits
        // '0'-'9', write a function to determine if it's an additive number.
        // Note: Numbers in the additive sequence cannot have leading zeros,
        // so sequence 1, 2, 03 or 1, 02, 3 is invalid.
        // Example 1:
        // Input: "112358"
        // Output: true
        // Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
        // 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
        // Example 2:
        // Input: "199100199"
        // Output: true
        // Explanation: The additive sequence is: 1, 99, 100, 199.
        // 1 + 99 = 100, 99 + 100 = 199
        // Constraints:
        // num consists only of digits '0'-'9'.
        // 1 <= num.length <= 35
        // Follow up:
        // How would you handle overflow for very large input integers?
        bool isAdditiveNumber(const string &num)
        {
            unsigned long long a = 0;
            for (size_t i = 0; i + 2 < num.size(); i++)
            {
                if (i > 0 && num[0] == '0')
                    break;
                a = 10 * a + num[i] - '0';
                unsigned long long b = 0;
                for (size_t j = i + 1; j + 1 < num.size(); j++)
                {
                    if (j > i + 1 && num[i + 1] == '0')
                        break;
                    b = 10 * b + num[j] - '0';
                    unsigned long long x = a;
                    unsigned long long y = b;
                    size_t k = j + 1;
                    bool match = true;
                    while (k < num.size() && match)
                    {
                        unsigned long long z = x + y;
                        if (z < x && z < y)
                        {
                            match = false;
                            break;
                        }
                        string s = to_string(z);
                        if (k + s.size() > num.size())
                        {
                            match = false;
                            break;
                        }
                        size_t l = 0;
                        for (l = 0; l < s.size(); l++)
                        {
                            if (num[k + l] != s[l])
                            {
                                match = false;
                                break;
                            }
                        }
                        if (l < s.size())
                            match = false;
                        x = y;
                        y = z;
                        k += l;
                    }
                    if (match)
                        return true;
                }
            }
            return false;
        }

        // 307. Range Sum Query - Mutable
        // Given an array nums and two types of queries where you should update the value
        // of an index in the array, and retrieve the sum of a range in the array.
        // Implement the NumArray class:
        // NumArray(int[] nums) Initializes the object with the integer array nums.
        // void update(int index, int val) Updates the value of nums[index] to be val.
        // int sumRange(int left, int right) Returns the sum of the subarray nums[left, right]
        // (i.e., nums[left] + nums[left + 1], ..., nums[right]).
        // Example 1:
        // Input
        // ["NumArray", "sumRange", "update", "sumRange"]
        // [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
        // Output
        // [null, 9, null, 8]
        // Explanation
        // NumArray numArray = new NumArray([1, 3, 5]);
        // numArray.sumRange(0, 2); // return 9 = sum([1,3,5])
        // numArray.update(1, 2);   // nums = [1,2,5]
        // numArray.sumRange(0, 2); // return 8 = sum([1,2,5])
        // Constraints:
        // 1 <= nums.length <= 3 * 10^4
        // -100 <= nums[i] <= 100
        // 0 <= index < nums.length
        // -100 <= val <= 100
        // 0 <= left <= right < nums.length
        // At most 3 * 10^4 calls will be made to update and sumRange.
        class NumArrayMutable
        {
        private:
            vector<int> acc;

        public:
            NumArrayMutable(vector<int> &nums)
            {
                acc.resize(nums.size());
                int a = 0;
                for (size_t i = 0; i < nums.size(); i++)
                {
                    a += nums[i];
                    acc[i] = a;
                }
            }

            void update(int index, int val)
            {
                if (0 <= index && index < (int)acc.size())
                {
                    int x = acc[index];
                    if (index > 0)
                        x -= acc[index - 1];
                    int d = val - x;
                    for (size_t i = index; i < acc.size(); i++)
                        acc[i] += d;
                }
            }

            int sumRange(int left, int right)
            {
                int r = acc[right];
                if (left > 0)
                    r -= acc[left - 1];
                return r;
            }
        };
        class NumArrayMutable2
        {
        private:
            vector<int> acc;

        public:
            NumArrayMutable2(vector<int> &nums)
            {
                acc.insert(acc.begin(), nums.begin(), nums.end());
            }

            void update(int index, int val)
            {
                if (0 <= index && index < (int)acc.size())
                {
                    acc[index] = val;
                }
            }

            int sumRange(int left, int right)
            {
                return accumulate(acc.begin() + left, acc.begin() + right + 1, 0);
            }
        };
        class NumArrayMutable3
        {
        private:
            vector<int> num;
            vector<int> block;
            int blockLen;

        public:
            NumArrayMutable3(vector<int> &nums)
            {
                num.insert(num.begin(), nums.begin(), nums.end());
                blockLen = sqrt(num.size());
                int a = 0;
                for (int i = 0; i < (int)num.size(); i++)
                {
                    a += num[i];
                    if ((i + 1) % blockLen == 0)
                    {
                        block.push_back(a);
                        a = 0;
                    }
                }
                if (blockLen * block.size() < num.size())
                    block.push_back(a);
            }

            void update(int index, int val)
            {
                if (0 <= index && index < (int)num.size())
                {
                    int blockIndex = index / blockLen;
                    block[blockIndex] += val - num[index];
                    num[index] = val;
                }
            }

            int sumRange(int left, int right)
            {
                int blockLeft = left / blockLen;
                int blockRight = right / blockLen;
                int a = 0;
                if (blockLeft == blockRight)
                {
                    for (int i = left; i <= right; i++)
                        a += num[i];
                }
                else
                {
                    for (int i = blockLeft + 1; i < blockRight; i++)
                        a += block[i];
                    for (int i = left; i < (blockLeft + 1) * blockLen; i++)
                        a += num[i];
                    for (int i = blockRight * blockLen; i <= right; i++)
                        a += num[i];
                }
                return a;
            }
        };
        class NumArrayMutable4
        {
        private:
            // Given n numbers [0..(n-1)]
            // The tree array has 2n-1 entries
            // index 0 1 ... (n-2) (n-1) n ... (2n-2)
            //       ~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~
            //       internal nodes   leaf nodes
            // The leaf nodes at indices [(n-1)..(2n-2)] will be the n numbers.
            // The internal nodes at indices [0..(n-2)] will be aggregates.
            // An internal node at index i has left node 2i+1 and right node 2i+2.
            // For example, given 10 numbers [0..9], the leaf indices are [9..18]
            // 1. Build tree bottom up until index 2.
            //             2           3
            //           /   \       /   \
            //    4     5     6     7     8
            //   / \   / \   / \   / \   / \
            //  9  10 11 12 13 14 15 16 17 18
            // 2. Build tree at index 1
            //                           -- 1 --
            //                          /      \
            //             2           3        4
            //           /   \       /   \     / \
            //          5     6     7     8   9  10
            //         / \   / \   / \   / \
            //        11 12 13 14 15 16 17 18
            // 3. Build tree at index 0
            //                               ---- 0 ----
            //                              /           \
            //                           --1 --          2
            //                          /      \       /   \
            //                         3        4     5     6
            //                       /   \     / \   / \   / \
            //                      7     8   9  10 11 12 13 14
            //                     / \   / \
            //                    15 16 17 18
            // Another example, given 11 numbers [0..10], the leaf indices are [10..20]
            // 1. Build tree bottom up until index 5.
            //       5     6     7     8     9
            //      / \   / \   / \   / \   / \
            //  10 11 12 13 14 15 16 17 18 19 20
            // 2. Build tree from index 4 to 1
            //                        --- 1 ---
            //                       /         \
            //          2           3           4
            //        /   \       /   \       /   \
            //       5     6     7     8     9    10
            //      / \   / \   / \   / \   / \
            //     11 12 13 14 15 16 17 18 19 20
            // 3. Build tree at index 0
            //                              ----- 0 -----
            //                             /             \
            //                        --- 1 ---           2
            //                       /         \        /   \
            //                      3           4      5     6
            //                    /   \       /   \   / \   / \
            //                   7     8     9    10 11 12 13 14
            //                  / \   / \   / \
            //                 15 16 17 18 19 20
            void buildTree(const vector<int> &num, vector<int> &tree)
            {
                if (num.empty())
                    return;
                int n = num.size();
                tree.resize(2 * n - 1);
                for (int i = n - 1, j = 0; i < 2 * n - 1; i++, j++)
                {
                    tree[i] = num[j];
                }
                for (int i = n - 2; i >= 0; i--)
                {
                    tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
                }
            }

            vector<int> tree;
            int n;

        public:
            NumArrayMutable4(vector<int> &nums)
            {
                n = nums.size();
                buildTree(nums, tree);
            }

            void update(int index, int val)
            {
                if (0 <= index && index < n)
                {
                    index += n - 1;
                    int d = val - tree[index];
                    while (index > 0)
                    {
                        tree[index] += d;
                        index = (index - 1) >> 1;
                    }
                    tree[index] += d;
                }
            }

            int sumRange(int left, int right)
            {
                left += n - 1;
                right += n - 1;
                int s = 0;
                while (left <= right)
                {
                    if ((left & 0x1) == 0)
                    {
                        s += tree[left];
                        left++;
                    }
                    if ((right & 0x1) == 1)
                    {
                        s += tree[right];
                        right--;
                    }
                    left = (left - 1) >> 1;
                    right = (right - 1) >> 1;
                }
                return s;
            }
        };
        class NumArrayMutable5
        {
            // https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
            // https://en.wikipedia.org/wiki/Fenwick_tree
            // Given an array of 16 numbers, construct a binary-indexed-tree (BIT) of 17 numbers
            //                index       Value       Parent
            // |------------- 16 [10000]  sum[0..16]   0
            // |           |- 15 [01111]  sum[15]     14
            // |        |---- 14 [01110]  sum[13..14] 12
            // |        |  |- 13 [01101]  sum[13]     12
            // |     |------- 12 [01100]  sum[9..12]   8
            // |     |     |- 11 [01011]  sum[11]     10
            // |     |  |---- 10 [01010]  sum[9..10]   8
            // |     |  |  |-  9 [01001]  sum[9]       8
            // |  |----------  8 [01000]  sum[0..8]    0
            // |  |        |-  7 [00111]  sum[7]       6
            // |  |     |----  6 [00110]  sum[5..6]    4
            // |  |     |  |-  5 [00101]  sum[5]       4
            // |  |  |-------  4 [00100]  sum[0..4]    0
            // |  |  |     |-  3 [00011]  sum[3]       2
            // |  |  |  |----  2 [00010]  sum[0..2]    0
            // |  |  |  |  |-  1 [00001]  sum[1]       0
            // ----------------0 [00000]  0            0
            // Given an index i in the BIT, its parent index is (i - lsb1(i)).
            // Least Significant Bit One
            // Given a binary 10110000, we want to get the binary represented by
            // the least significant bit one, i.e., 10000, then we can compute
            // the bitwise-and between the binary number and its two's complement:
            //   10110000 & (~10110000)
            // = 10110000 & ( 01001111 + 1)
            // = 10110000 &   01010000
            // = 00010000
            int lsb1(int b)
            {
                return b & (~b);
            }
            // Build a BIT tree from nums
            void buildbit(const vector<int> &nums)
            {
                count = nums.size();
                bit = vector<int>(1, 0);
                for (int i = 1; i <= count; i++)
                {
                    int s = nums[i - 1];
                    if ((i & 0x1) == 0)
                    {
                        int k = i - lsb1(i);
                        int j = i - 1;
                        while (j > k)
                        {
                            s += bit[j];
                            j -= lsb1(j);
                        }
                    }
                    bit.push_back(s);
                }
            }
            // Read the original nums[i]
            int getOriginalNumber(int i)
            {
                i++;
                int n = bit[i];
                int j = i - lsb1(i); // index of parent bit[i]
                i--;
                while (i != j)
                {
                    n -= bit[i];
                    i -= lsb1(i);
                }
                return n;
            }

        private:
            int count;
            vector<int> bit; // [0..count]
            // Add val to nums[i] (i.e., bit[i+1]) and update all the affected entries
            void add(int i, int val)
            {
                i++;
                while (i <= count)
                {
                    bit[i] += val;
                    i += lsb1(i);
                }
            }
            // sum of nums[0..i]
            int sumUpTo(int i)
            {
                i++;
                int s = 0;
                while (i > 0)
                {
                    s += bit[i];
                    i -= lsb1(i);
                }
                return s;
            }

        public:
            NumArrayMutable5(vector<int> &nums)
            {
                count = nums.size();
                // Build bit with all zeros, which is a valid BIT tree
                bit = vector<int>(count + 1, 0);
                // Update bit with nums, which will be the actual BIT tree for nums
                for (int i = 0; i < count; i++)
                {
                    add(i, nums[i]);
                }
            }

            void update(int index, int val)
            {
                int v = getOriginalNumber(index);
                int d = val - v;
                add(index, d);
            }

            int sumRange(int left, int right)
            {
                return sumUpTo(right) - sumUpTo(left - 1);
            }
        };
        // Idea of NumArrayMutable5 and validated
        class NumArrayMutable6
        {
        private:
            int count;
            vector<int> bit;

            int lsb1(int b)
            {
                return b & (~b + 1);
            }

            int getOriginalNumber(int i)
            {
                i++;
                int n = bit[i];
                int j = i - lsb1(i);
                i--;
                while (i != j)
                {
                    n -= bit[i];
                    i -= lsb1(i);
                }
                return n;
            }

            int sumUpTo(int i)
            {
                i++;
                int s = 0;
                while (i > 0)
                {
                    s += bit[i];
                    i -= lsb1(i);
                }
                return s;
            }

        public:
            NumArrayMutable6(const vector<int> &nums)
            {
                count = nums.size();
                bit.push_back(0);
                for (int i = 1; i <= count; i++)
                {
                    int s = nums[i - 1];
                    if ((i & 0x1) == 0)
                    {
                        int k = i - lsb1(i);
                        int j = i - 1;
                        while (j > k)
                        {
                            s += bit[j];
                            j -= lsb1(j);
                        }
                    }
                    bit.push_back(s);
                }
            }

            void update(int index, int val)
            {
                if (0 <= index && index < count)
                {
                    int n = getOriginalNumber(index);
                    int d = val - n;
                    index++;
                    while (index <= count)
                    {
                        bit[index] += d;
                        index += lsb1(index);
                    }
                }
            }

            int sumRange(int left, int right)
            {
                int s = sumUpTo(right);
                if (left > 0)
                    s -= sumUpTo(left - 1);
                return s;
            }

            void print()
            {
                cout << "{";
                for (size_t i = 0; i < bit.size(); i++)
                {
                    if (i > 0)
                        cout << ", ";
                    cout << bit[i];
                }
                cout << "}" << endl;
            }
        };
        class NumArrayMutable7
        {
            // Same as NumArrayMutable6 except the bit array has the same length as the input
        private:
            int count;
            vector<int> bit;

            int lsb1(int b)
            {
                return b & (~b + 1);
            }

            int getOriginalNumber(int i)
            {
                int n = bit[i];
                i++; // convert to BIT index
                int j = i - lsb1(i);
                i--;
                while (i != j)
                {
                    n -= bit[i - 1]; // bit array is biased from BIT index
                    i -= lsb1(i);
                }
                return n;
            }

            int sumUpTo(int i)
            {
                i++; // convert to BIT index
                int s = 0;
                while (i > 0)
                {
                    s += bit[i - 1]; // bit array is biased from BIT index
                    i -= lsb1(i);
                }
                return s;
            }

        public:
            NumArrayMutable7(vector<int> &nums)
            {
                count = nums.size();
                for (int i = 0; i < count; i++)
                {
                    int s = nums[i];
                    int j = i + 1; // convert to BIT index
                    if ((j & 0x1) == 0)
                    {
                        int k = j - lsb1(j);
                        int l = j - 1;
                        while (l > k)
                        {
                            s += bit[l - 1]; // bit array is biased from BIT index
                            l -= lsb1(l);
                        }
                    }
                    bit.push_back(s);
                }
            }

            void update(int index, int val)
            {
                if (0 <= index && index < count)
                {
                    int n = getOriginalNumber(index);
                    int d = val - n;
                    index++;
                    while (index <= count)
                    {
                        bit[index - 1] += d; // bit array is biased from BIT index
                        index += lsb1(index);
                    }
                }
            }

            int sumRange(int left, int right)
            {
                int s = sumUpTo(right);
                if (left > 0)
                    s -= sumUpTo(left - 1);
                return s;
            }
        };
        class NumArrayMutable8
        {
        private:
            int count;
            vector<int> bit;

            int lsb1(int b)
            {
                return b & (~b + 1);
            }

            void add(int i, int val)
            {
                i++;
                while (i <= count)
                {
                    bit[i - 1] += val;
                    i += lsb1(i);
                }
            }

            int getOriginalNumber(int i)
            {
                int n = bit[i];
                i++;
                int j = i - lsb1(i);
                i--;
                while (i != j)
                {
                    n -= bit[i - 1];
                    i -= lsb1(i);
                }
                return n;
            }

            int sumUpTo(int i)
            {
                i++;
                int s = 0;
                while (i > 0)
                {
                    s += bit[i - 1];
                    i -= lsb1(i);
                }
                return s;
            }

        public:
            NumArrayMutable8(vector<int> &nums)
            {
                count = nums.size();
                bit.resize(count, 0); // init a valid BIT
                for (int i = 0; i < count; i++)
                {
                    add(i, nums[i]); // update bit while maintaining it as a valid BIT
                }
            }

            void update(int index, int val)
            {
                if (0 <= index && index < count)
                {
                    int v = getOriginalNumber(index);
                    int d = val - v;
                    add(index, d);
                }
            }

            int sumRange(int left, int right)
            {
                int s = sumUpTo(right);
                if (left > 0)
                    s -= sumUpTo(left - 1);
                return s;
            }
        };

        // 309. Best Time to Buy and Sell Stock with Cooldown
        // You are given an array prices where prices[i] is the price of a given stock on the ith day.
        // Find the maximum profit you can achieve. You may complete as many transactions as you like
        // (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
        // After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
        // Note: You may not engage in multiple transactions simultaneously
        // (i.e., you must sell the stock before you buy again).
        // Example 1:
        // Input: prices = [1,2,3,0,2]
        // Output: 3
        // Explanation: transactions = [buy, sell, cooldown, buy, sell]
        // Example 2:
        // Input: prices = [1]
        // Output: 0
        // Constraints:
        // 1 <= prices.length <= 5000
        // 0 <= prices[i] <= 1000
        // Let m[i] be the max profit at day i.
        // m[i] = max{ m[i-1],
        //             m[i-3] + p[i] - p[i-1],
        //             m[i-4] + p[i] - p[i-2],
        //             ......
        //             m[1] + p[i] - p[3],
        //                    p[i] - p[2],
        //                    p[i] - p[1],
        //                    p[i] - p[0]
        //           }
        //  let s[i] be the state at i
        //  i  p[i]  s[i]                                           m[i]
        //  0  p[0]  -p[0]                                          0
        //  1  p[1]  max{-p[1], -p[0]}                              max{m[0], p[1]-p[0]}
        //  2  p[2]  max{-p[2], -p[1], -p[0]}                       max{m[1], p[2]-p[1], p[2]-p[0]}
        //  3  p[3]  max{m[1]-p[3], -p[2], -p[1], -p[0]}            max{m[2], p[3]-p[2], p[3]-p[1], p[3]-p[0]}
        //  4  p[4]  max{m[2]-p[4], m[1]-p[3], -p[2], -p[1], -p[0]} max{m[3], m[1]+p[4]-p[3], p[4]-p[2], p[4]-p[1], p[4]-p[0]}
        //  5  p[5]                                                 max{m[4], m[2]+p[5]-p[4], m[1]+p[5]-p[3], p[5]-p[2], p[5]-p[1], p[5]-p[0]}
        int maxProfit(vector<int> &prices)
        {
            int m = 0;   // m[i]
            int m_1 = 0; // m[i-1]
            int m_2 = 0; // m[i-2]
            int s = 0;
            for (int i = 0; i < (int)prices.size(); i++)
            {
                if (i == 0)
                {
                    m = 0;
                    s = -prices[0];
                }
                else if (i < 3)
                {
                    m = max(m_1, prices[i] + s);
                    s = max(-prices[i], s);
                }
                else // i>= 3
                {
                    m = max(m_1, prices[i] + s);
                    s = max(m_2 - prices[i], s);
                }
                m_2 = m_1;
                m_1 = m;
            }
            return m;
        }

        // 310. Minimum Height Trees
        // A tree is an undirected graph in which any two vertices are connected by exactly one path.
        // In other words, any connected graph without simple cycles is a tree.
        // Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges
        // where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes
        // ai and bi in the tree, you can choose any node of the tree as the root. When you select a
        // node x as the root, the result tree has height h. Among all possible rooted trees, those
        // with minimum height (i.e. min(h))  are called minimum height trees (MHTs).
        // Return a list of all MHTs' root labels. You can return the answer in any order.
        // The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
        // Example 1:
        // Input: n = 4, edges = [[1,0],[1,2],[1,3]]
        // Output: [1]
        // Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.
        // Example 2:
        // Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
        // Output: [3,4]
        // Example 3:
        // Input: n = 1, edges = []
        // Output: [0]
        // Example 4:
        // Input: n = 2, edges = [[0,1]]
        // Output: [0,1]
        // Constraints:
        // 1 <= n <= 2 * 10^4
        // edges.length == n - 1
        // 0 <= ai, bi < n
        // ai != bi
        // All the pairs (ai, bi) are distinct.
        // The given input is guaranteed to be a tree and there will be no repeated edges.
        // The roots to look for are centroids who are close to all the other nodes.
        // For the tree-alike graph, the number of centroids is no more than 2.
        // If the nodes form a chain, it is intuitive to see that the above statement holds,
        // which can be broken into the following two cases:
        // If the number of nodes is even, then there would be two centroids.
        // If the number of nodes is odd, then there would be only one centroid.
        // For the rest of cases, we could prove by contradiction. Suppose that we have 3 centroids
        // in the graph, if we remove all the non-centroid nodes in the graph, then the 3 centroids
        // nodes must form a triangle shape.
        // Because these centroids are equally important to each other, and they should equally
        // close to each other as well. If any of the edges that is missing from the triangle,
        // then the 3 centroids would be reduced down to a single centroid.
        // However, the triangle shape forms a cycle which is contradicted to the condition
        // that there is no cycle in our tree-alike graph. Similarly, for any of the cases that
        // have more than 2 centroids, they must form a cycle among the centroids, which is
        // contradicted to our condition. Therefore, there cannot be more than 2 centroids
        // in a tree-alike graph.
        // The idea is that we trim out the leaf nodes layer by layer, until we reach the core
        // of the graph, which are the centroids nodes. We could implement it via the Breadth
        // First Search (BFS) strategy, to trim the leaf nodes layer by layer (i.e. level by level).
        // Initially, we would build a graph with the adjacency list from the input.
        // We then create a queue which would be used to hold the leaf nodes.
        // At the beginning, we put all the current leaf nodes into the queue.
        // We then run a loop until there is only two nodes left in the graph.
        // At each iteration, we remove the current leaf nodes from the queue. While removing the
        // nodes, we also remove the edges that are linked to the nodes. As a consequence, some
        // of the non-leaf nodes would become leaf nodes. And these are the nodes that would be
        // trimmed out in the next iteration.
        // The iteration terminates when there are no more than two nodes left in the graph, which
        // are the desired centroids nodes.
        vector<int> findMinHeightTrees(int n, const vector<vector<int>> &edges)
        {
            if (edges.empty())
                return vector<int>{0};
            unordered_map<int, unordered_set<int>> g;
            for (const auto &e : edges)
            {
                if (g.find(e[0]) == g.end())
                    g[e[0]] = unordered_set<int>{};
                g[e[0]].insert(e[1]);
                if (g.find(e[1]) == g.end())
                    g[e[1]] = unordered_set<int>{};
                g[e[1]].insert(e[0]);
            }
            queue<int> current;
            queue<int> next;
            for (const auto &p : g)
            {
                if (p.second.size() <= 1)
                    current.push(p.first);
            }
            while (g.size() > 2)
            {
                while (!current.empty())
                {
                    int l = current.front();
                    current.pop();
                    for (const int &t : g[l])
                    {
                        g[t].erase(l);
                        if (g[t].size() == 1)
                            next.push(t);
                    }
                    g.erase(l);
                }
                current.swap(next);
            }
            vector<int> roots;
            for (const auto &p : g)
            {
                roots.push_back(p.first);
            }
            return roots;
        }
        vector<int> findMinHeightTrees2(int n, const vector<vector<int>> &edges)
        {
            multimap<int, int> g;
            for (const auto &e : edges)
            {
                g.emplace(e[0], e[1]);
                g.emplace(e[1], e[0]);
            }
            int height = INT_MAX;
            vector<int> roots;
            function<void(int)> bfs = [&](int node) {
                cout << "bfs(" << node << ")" << endl;
                queue<int> current;
                queue<int> next;
                current.push(node);
                int h = 0;
                set<int> visited;
                while (!current.empty())
                {
                    h++;
                    cout << "current h = " << h << endl;
                    if (h > height)
                        break;
                    while (!current.empty())
                    {
                        int i = current.front();
                        current.pop();
                        visited.insert(i);
                        cout << i << "-> {";
                        pair<multimap<int, int>::iterator, multimap<int, int>::iterator> range = g.equal_range(i);
                        for (multimap<int, int>::iterator it = range.first; it != range.second; ++it)
                        {
                            if (visited.find(it->second) == visited.end())
                            {
                                next.push(it->second);
                                cout << it->second << ", ";
                            }
                        }
                        cout << "}" << endl;
                        // this_thread::sleep_for(chrono::seconds(1));
                    }
                    current.swap(next);
                }
                if (h < height)
                {
                    roots.clear();
                    roots.push_back(node);
                    height = h;
                }
                else if (h == height)
                {
                    roots.push_back(node);
                }
            };
            for (int i = 0; i < n; i++)
            {
                bfs(i);
            }
            return roots;
        }

        // 312. Burst Balloons
        // You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number
        // on it represented by an array nums. You are asked to burst all the balloons.
        // If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
        // If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
        // Return the maximum coins you can collect by bursting the balloons wisely.
        // Example 1:
        // Input: nums = [3,1,5,8]
        // Output: 167
        // Explanation:
        // nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
        // coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
        // Example 2:
        // Input: nums = [1,5]
        // Output: 10
        // Constraints:
        // n == nums.length
        // 1 <= n <= 500
        // 0 <= nums[i] <= 100
        // m[i..j] be the max collected from n[i..j]
        // m[i..j] = max{              n[i-1]*n[i]*n[j+1]   + m[(i+1)..j],
        //               m[i..i]     + n[i-1]*n[i+1]*n[j+1] + m[(i+2)..j],
        //               m[i..(i+1)] + n[i-1]*n[i+2]*n[j+1] + m[(i+3)..j],
        //               ......
        //               m[i..(j-2)] + n[i-1]*n[j-1]*n[j+1] + m[j..j],
        //               m[i..(j-1)] + n[i-1]*n[j]*n[j+1]}
        //     0       1       2              i              j
        // 0   m[0][0] m[0][1] m[0][2] ...... m[0][i] ...... m[0][j]
        // 1           m[1][1] m[1][2] ...... m[1][i] ...... m[1][j]
        // 2                   m[2][2] ...... m[2][i] ...... m[2][j]
        //                             ......
        // i                                  m[i][i] ...... m[i][j]
        //                                            ......
        // j                                                 m[j][j]
        int maxCoins(vector<int> &nums)
        {
            map<pair<int, int>, int> m;
            int n = nums.size();
            function<int(int)> get = [&](int i) -> int {
                if (i < 0 || i >= n)
                    return 1;
                return nums[i];
            };
            function<int(int, int)> solve = [&](int i, int j) -> int {
                if (i > j)
                    return 0;
                pair<int, int> p = make_pair(i, j);
                if (m.find(p) == m.end())
                {
                    int s = 0;
                    for (int k = i; k <= j; k++)
                    {
                        s = max(s, solve(i, k - 1) + get(i - 1) * get(k) * get(j + 1) + solve(k + 1, j));
                    }
                    m[p] = s;
                }
                return m[p];
            };
            return solve(0, n - 1);
        }
        int maxCoins2(vector<int> &nums)
        {
            int n = nums.size();
            vector<vector<int>> m(n, vector<int>(n, -1)); // faster than using a map
            function<int(int)> get = [&](int i) -> int {
                if (i < 0 || i >= n)
                    return 1;
                return nums[i];
            };
            function<int(int, int)> solve = [&](int i, int j) -> int {
                if (i > j)
                    return 0;
                if (m[i][j] < 0)
                {
                    int s = 0;
                    for (int k = i; k <= j; k++)
                    {
                        s = max(s, solve(i, k - 1) + get(i - 1) * get(k) * get(j + 1) + solve(k + 1, j));
                    }
                    m[i][j] = s;
                }
                return m[i][j];
            };
            return solve(0, n - 1);
        }
        int maxCoins3(vector<int> &nums)
        {
            int n = nums.size();
            vector<vector<int>> m(n, vector<int>(n, -1));
            function<int(int)> getN = [&](int i) -> int {
                if (i < 0 || i >= n)
                    return 1;
                return nums[i];
            };
            function<int(int, int)> getM = [&](int i, int j) -> int {
                if (i > j)
                    return 0;
                return m[i][j];
            };
            for (int r = n - 1; r >= 0; r--)
            {
                for (int s = 0; s <= r; s++)
                {
                    int i = r - s;
                    int j = n - 1 - s;
                    int t = 0;
                    int c = getN(i - 1) * getN(j + 1);
                    for (int k = i; k <= j; k++)
                    {
                        t = max(t, getM(i, k - 1) + c * getN(k) + getM(k + 1, j));
                    }
                    m[i][j] = t;
                }
            }
            return m[0][n - 1];
        }

        // 313. Super Ugly Number
        // Given an integer n and an array of integers primes, return the nth super ugly number.
        // Super ugly number is a positive number whose all prime factors are in the array primes.
        // The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
        // Example 1:
        // Input: n = 12, primes = [2,7,13,19]
        // Output: 32
        // Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 super ugly
        // numbers given primes == [2,7,13,19].
        // Example 2:
        // Input: n = 1, primes = [2,3,5]
        // Output: 1
        // Explanation: 1 is a super ugly number for any given primes.
        // Constraints:
        // 1 <= n <= 10^6
        // 1 <= primes.length <= 100
        // 2 <= primes[i] <= 1000
        // primes[i] is guaranteed to be a prime number.
        // All the values of primes are unique and sorted in ascending order.
        // Let (a,b) be the node where a is the accumulative product and b is the multiplier to get to a from the parent.
        // So given primes {2, 3, 5} we can generate following tree.
        // (1,1)
        //  |------------------------------------------------------------------------|------------------------------|
        // (2,2)                                                                    (3,3)                          (5,5)
        //  |------------------------------------------|---------------------|       |----------------------|       |
        // (4,2)                                      (6,3)                 (10,5)  (9,3)                  (15,5)  (25,5)
        //  |--------------------|-------------|       |-------------|       |       |--------------|       |       |
        // (8,2)                (12,3)        (20,5)  (18,3)        (30,5)  (50,5)  (27,3)         (45,5)  (75,5)  (125,5)
        //  |------|------|      |------|      |       |------|      |       |       |------|       |       |       |
        // (16,2) (24,3) (40,5) (36,3) (60,5) (100,5) (54,3) (90,5) (150,5) (250,5) (81,3) (135,5) (225,5) (375,5) (625,5)
        int nthSuperUglyNumber(int n, vector<int> &primes)
        {
            unordered_map<int, size_t> index;
            index[1] = 0;
            for (size_t i = 0; i < primes.size(); i++)
                index[primes[i]] = i;
            function<bool(const pair<long long, long long> &, const pair<long long, long long> &)>
                greater = [&](const pair<long long, long long> &x, const pair<long long, long long> &y) -> bool {
                return x.first > y.first;
            };
            vector<pair<long long, long long>> v;
            v.push_back(make_pair(1, 1));
            int i = 0;
            pair<long long, long long> r = v.front();
            while (true)
            {
                pop_heap(v.begin(), v.end(), greater); // min-heap
                r = v.back();
                v.pop_back();
                i++;
                if (i == n)
                    break;
                for (size_t j = index[r.second]; j < primes.size(); j++)
                {
                    v.push_back(make_pair(r.first * primes[j], primes[j]));
                    push_heap(v.begin(), v.end(), greater); // min-heap
                }
            }
            return r.first;
        }
        // primes  {2, 3, 5}   v
        // cnt      0  0  0   {1}
        //          1  0  0   {1,2}
        //          1  1  0   {1,2,3}
        //          2  1  0   {1,2,3,4}
        //          2  1  1   {1,2,3,4,5}
        //          3  1  1   {1,2,3,4,5,6}
        int nthSuperUglyNumber2(int n, vector<int> &primes)
        {
            vector<int> v;
            v.push_back(1);
            int m = primes.size();
            vector<int> cnt(m, 0);
            while ((int)v.size() < n)
            {
                int mn = INT_MAX;
                for (int i = 0; i < m; i++)
                    mn = min(mn, v[cnt[i]] * primes[i]);
                v.push_back(mn);
                for (int i = 0; i < m; i++)
                    if (mn == v[cnt[i]] * primes[i])
                        cnt[i]++;
            }
            return v.back();
        }

        // 315. Count of Smaller Numbers After Self
        // You are given an integer array nums and you have to return a new counts array.
        // The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].
        // Example 1:
        // Input: nums = [5,2,6,1]
        // Output: [2,1,1,0]
        // Explanation:
        // To the right of 5 there are 2 smaller elements (2 and 1).
        // To the right of 2 there is only 1 smaller element (1).
        // To the right of 6 there is 1 smaller element (1).
        // To the right of 1 there is 0 smaller element.
        // Example 2:
        // Input: nums = [-1]
        // Output: [0]
        // Example 3:
        // Input: nums = [-1,-1]
        // Output: [0,0]
        // Constraints:
        // 1 <= nums.length <= 10^5
        // -10^4 <= nums[i] <= 10^4
        vector<int> countSmaller(const vector<int> &nums)
        {
            function<void(const string &, const vector<int> &)>
                pv = [&](const string &s, const vector<int> &v) {
                    cout << s << ": {";
                    for (size_t i = 0; i < v.size(); i++)
                    {
                        if (i > 0)
                            cout << ",";
                        cout << v[i];
                    }
                    cout << "}" << endl;
                };
            vector<int> counts(nums.size(), 0);
            vector<int> index(nums.size(), 0);
            for (int i = 0; i < (int)nums.size(); i++)
                index[i] = i;
            function<void(int, int, int)> mergeRange = [&](int low, int median, int high) {
                cout << "merge(" << low << "," << median << "," << high << ")" << endl;
                if (low >= high)
                    return;
                vector<int> left(index.begin() + low, index.begin() + median + 1);
                vector<int> right(index.begin() + median + 1, index.begin() + high + 1);
                pv("left", left);
                pv("right", right);
                int leftSize = left.size();
                int rightSize = right.size();
                int i = 0;
                int j = 0;
                int k = low;
                while (i < leftSize || j < rightSize)
                {
                    if (i < leftSize && (j >= rightSize || nums[left[i]] <= nums[right[j]]))
                    {
                        index[k] = left[i];
                        counts[left[i]] += j;
                        i++;
                    }
                    else
                    {
                        index[k] = right[j];
                        j++;
                    }
                    k++;
                }
                pv("index", index);
                pv("counts", counts);
            };
            function<void(int, int)> sortRange = [&](int low, int high) {
                cout << "sort(" << low << "," << high << ")" << endl;
                if (low >= high)
                    return;
                int median = low + ((high - low) >> 1);
                sortRange(low, median);
                sortRange(median + 1, high);
                mergeRange(low, median, high);
            };
            sortRange(0, nums.size() - 1);
            return counts;
        }

    }
}

#endif
