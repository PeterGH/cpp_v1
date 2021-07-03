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
                [&](size_t i, string v, int l, int r, const queue<char> &q)
            {
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
                [&](size_t i, string v, int l, int r, const queue<char> &q)
            {
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
            function<void(int)> bfs = [&](int node)
            {
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
            function<int(int)> get = [&](int i) -> int
            {
                if (i < 0 || i >= n)
                    return 1;
                return nums[i];
            };
            function<int(int, int)> solve = [&](int i, int j) -> int
            {
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
            function<int(int)> get = [&](int i) -> int
            {
                if (i < 0 || i >= n)
                    return 1;
                return nums[i];
            };
            function<int(int, int)> solve = [&](int i, int j) -> int
            {
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
            function<int(int)> getN = [&](int i) -> int
            {
                if (i < 0 || i >= n)
                    return 1;
                return nums[i];
            };
            function<int(int, int)> getM = [&](int i, int j) -> int
            {
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
                greater = [&](const pair<long long, long long> &x, const pair<long long, long long> &y) -> bool
            {
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
                pv = [&](const string &s, const vector<int> &v)
            {
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
            function<void(int, int, int)> mergeRange = [&](int low, int median, int high)
            {
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
            function<void(int, int)> sortRange = [&](int low, int high)
            {
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

        // 316. Remove Duplicate Letters
        // Given a string s, remove duplicate letters so that every letter appears once and only once.
        // You must make sure your result is the smallest in lexicographical order among all possible results.
        // Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
        // Example 1:
        // Input: s = "bcabc"
        // Output: "abc"
        // Example 2:
        // Input: s = "cbacdcbc"
        // Output: "acdb"
        // Constraints:
        // 1 <= s.length <= 10^4
        // s consists of lowercase English letters.
        string removeDuplicateLetters(string s)
        {
            bitset<26> valid;
            vector<int> count(26, 0);
            for (const char c : s)
            {
                count[c - 'a']++;
            }
            string r;
            for (const char c : s)
            {
                if (!valid.test(c - 'a'))
                {
                    while (!r.empty() && r.back() > c && count[r.back() - 'a'] > 0)
                    {
                        valid.reset(r.back() - 'a');
                        r.pop_back();
                    }
                    valid.set(c - 'a');
                    r.append(1, c);
                }
                count[c - 'a']--;
            }
            return r;
        }

        // 318. Maximum Product of Word Lengths
        // Given a string array words, return the maximum value of length(word[i]) * length(word[j])
        // where the two words do not share common letters. If no such two words exist, return 0.
        // Example 1:
        // Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
        // Output: 16
        // Explanation: The two words can be "abcw", "xtfn".
        // Example 2:
        // Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
        // Output: 4
        // Explanation: The two words can be "ab", "cd".
        // Example 3:
        // Input: words = ["a","aa","aaa","aaaa"]
        // Output: 0
        // Explanation: No such pair of words.
        // Constraints:
        // 2 <= words.length <= 1000
        // 1 <= words[i].length <= 1000
        // words[i] consists only of lowercase English letters.
        int maxProduct(vector<string> &words)
        {
            function<bool(const set<char> &, const set<char> &)>
                hasCommonLetter = [&](const set<char> &a, const set<char> &b) -> bool
            {
                auto i = a.begin();
                auto j = b.begin();
                while (i != a.end() && j != b.end())
                {
                    if (*i < *j)
                        ++i;
                    else if (*i > *j)
                        ++j;
                    else
                        return true;
                }
                return false;
            };
            vector<set<char>> n;
            for (const string &w : words)
            {
                n.push_back(set<char>(w.begin(), w.end()));
            }
            int l = 0;
            for (size_t i = 0; i + 1 < n.size(); i++)
            {
                for (size_t j = i + 1; j < n.size(); j++)
                {
                    if (!hasCommonLetter(n[i], n[j]))
                        l = max(l, (int)words[i].size() * (int)words[j].size());
                }
            }
            return l;
        }
        int maxProduct2(vector<string> &words)
        {
            size_t l = 0;
            vector<unsigned int> v(words.size(), 0);
            for (size_t j = 0; j < words.size(); j++)
            {
                unsigned int b = 0;
                for (const char &c : words[j])
                {
                    b |= (0x1 << (c - 'a'));
                }
                for (size_t i = 0; i < j; i++)
                {
                    if ((v[i] & b) == 0)
                    {
                        l = max(l, words[i].size() * words[j].size());
                    }
                }
                v[j] = b;
            }
            return l;
        }

        // 319. Bulb Switcher
        // There are n bulbs that are initially off. You first turn on all the bulbs,
        // then you turn off every second bulb. On the third round, you toggle every
        // third bulb (turning on if it's off or turning off if it's on). For the ith
        // round, you toggle every i bulb. For the nth round, you only toggle the last bulb.
        // Return the number of bulbs that are on after n rounds.
        // Example 1:
        // Input: n = 3
        // Output: 1
        // Explanation: At first, the three bulbs are [off, off, off].
        // After the first round, the three bulbs are [on, on, on].
        // After the second round, the three bulbs are [on, off, on].
        // After the third round, the three bulbs are [on, off, off].
        // So you should return 1 because there is only one bulb is on.
        // Example 2:
        // Input: n = 0
        // Output: 0
        // Example 3:
        // Input: n = 1
        // Output: 1
        // Constraints:
        // 0 <= n <= 10^9
        // The n-th bulb toggles at the i-th round if i divides n.
        int bulbSwitch(int n)
        {
            int i = 1;
            while (i * i <= n)
            {
                i++;
            }
            return i - 1;
        }

        // 321. Create Maximum Number
        // You are given two integer arrays nums1 and nums2 of lengths m and n respectively.
        // nums1 and nums2 represent the digits of two numbers. You are also given an integer k.
        // Create the maximum number of length k <= m + n from digits of the two numbers.
        // The relative order of the digits from the same array must be preserved.
        // Return an array of the k digits representing the answer.
        // Example 1:
        // Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
        // Output: [9,8,6,5,3]
        // Example 2:
        // Input: nums1 = [6,7], nums2 = [6,0,4], k = 5
        // Output: [6,7,6,0,4]
        // Example 3:
        // Input: nums1 = [3,9], nums2 = [8,9], k = 3
        // Output: [9,8,9]
        // Constraints:
        // m == nums1.length
        // n == nums2.length
        // 1 <= m, n <= 500
        // 0 <= nums1[i], nums2[i] <= 9
        // 1 <= k <= m + n
        // Follow up: Try to optimize your time and space complexity.
        vector<int> maxNumber(const vector<int> &nums1, const vector<int> &nums2, int k)
        {
            vector<int> m;
            int n1 = nums1.size();
            int n2 = nums2.size();
            function<bool(const vector<int> &, const vector<int> &)>
                greater = [&](const vector<int> &v1, const vector<int> &v2) -> bool
            {
                if (v1.size() < v2.size())
                    return false;
                if (v1.size() > v2.size())
                    return true;
                for (size_t i = 0; i < v1.size(); i++)
                {
                    if (v1[i] > v2[i])
                    {
                        return true;
                    }
                    else if (v1[i] < v2[i])
                    {
                        return false;
                    }
                }
                return false;
            };
            function<void(int, int, vector<int> &)>
                solve = [&](int i, int j, vector<int> &v)
            {
                cout << string(i + j, ' ') << "f(" << i << ", " << j << ", {";
                for (size_t i = 0; i < v.size(); i++)
                {
                    if (i > 0)
                        cout << ", ";
                    cout << v[i];
                }
                cout << "})" << endl;

                if ((int)v.size() > k)
                    return;
                if ((int)v.size() == k)
                {
                    if (greater(v, m))
                    {
                        m.assign(v.begin(), v.end());
                        print("max", m);
                    }
                    return;
                }
                if (!m.empty())
                {
                    for (size_t l = 0; l < v.size(); l++)
                    {
                        if (v[l] < m[l])
                            return;
                        else if (v[l] > m[l])
                            break;
                    }
                }
                if (i < n1)
                {
                    v.push_back(nums1[i]);
                    solve(i + 1, j, v);
                    v.pop_back();
                    solve(i + 1, j, v);
                }
                if (j < n2)
                {
                    v.push_back(nums2[j]);
                    solve(i, j + 1, v);
                    v.pop_back();
                    solve(i, j + 1, v);
                }
            };
            vector<int> t;
            solve(0, 0, t);
            return m;
        }
        vector<int> maxNumber2(const vector<int> &nums1, const vector<int> &nums2, int k)
        {
            function<vector<int>(const vector<int> &, int)>
                max1 = [&](const vector<int> &v, int l) -> vector<int>
            {
                vector<int> r;
                int n = v.size();
                for (int i = 0; i < n; i++)
                {
                    while (!r.empty() && r.back() < v[i] && ((int)r.size() - 1 + n - i >= l))
                        r.pop_back();
                    r.push_back(v[i]);
                }
                if ((int)r.size() > l)
                    r.resize(l);
                return r;
            };
            function<vector<int>(const vector<int> &, const vector<int> &)>
                max2 = [&](const vector<int> &v1, const vector<int> &v2) -> vector<int>
            {
                vector<int> r;
                auto b1 = v1.begin();
                auto e1 = v1.end();
                auto b2 = v2.begin();
                auto e2 = v2.end();
                while (b1 != e1 && b2 != e2)
                {
                    if (lexicographical_compare(b1, e1, b2, e2))
                    {
                        r.push_back(*b2);
                        ++b2;
                    }
                    else
                    {
                        r.push_back(*b1);
                        ++b1;
                    }
                }
                if (b1 != e1)
                    r.insert(r.end(), b1, e1);
                if (b2 != e2)
                    r.insert(r.end(), b2, e2);
                return r;
            };
            vector<int> m;
            function<bool(const vector<int> &, const vector<int> &)>
                greater = [&](const vector<int> &x, const vector<int> &y) -> bool
            {
                if (x.size() > y.size())
                    return true;
                if (x.size() < y.size())
                    return false;
                for (size_t i = 0; i < x.size(); i++)
                {
                    if (x[i] > y[i])
                        return true;
                    else if (x[i] < y[i])
                        return false;
                }
                return false;
            };
            for (int l = 0; l <= k; l++)
            {
                vector<int> n1 = max1(nums1, l);
                vector<int> n2 = max1(nums2, k - (int)n1.size());
                vector<int> n = max2(n1, n2);
                if (greater(n, m))
                    m.assign(n.begin(), n.end());
            }
            return m;
        }

        // 322. Coin Change
        // You are given an integer array coins representing coins of different denominations
        // and an integer amount representing a total amount of money.
        // Return the fewest number of coins that you need to make up that amount. If that
        // amount of money cannot be made up by any combination of the coins, return -1.
        // You may assume that you have an infinite number of each kind of coin.
        // Example 1:
        // Input: coins = [1,2,5], amount = 11
        // Output: 3
        // Explanation: 11 = 5 + 5 + 1
        // Example 2:
        // Input: coins = [2], amount = 3
        // Output: -1
        // Example 3:
        // Input: coins = [1], amount = 0
        // Output: 0
        // Example 4:
        // Input: coins = [1], amount = 1
        // Output: 1
        // Example 5:
        // Input: coins = [1], amount = 2
        // Output: 2
        // Constraints:
        // 1 <= coins.length <= 12
        // 1 <= coins[i] <= 2^31 - 1
        // 0 <= amount <= 10^4
        int coinChange(const vector<int> &coins, int amount)
        {
            map<pair<size_t, int>, int> m;
            function<int(size_t, int)> count = [&](size_t i, int a) -> int
            {
                cout << string(i, ' ') << "c(" << i << "," << a << ")" << endl;
                pair<size_t, int> p = make_pair(i, a);
                if (m.find(p) == m.end())
                {
                    if (a == 0)
                    {
                        m[p] = 0;
                    }
                    else if (i >= coins.size())
                    {
                        m[p] = -1;
                    }
                    else
                    {
                        int c = count(i + 1, a);
                        if (a >= coins[i])
                        {
                            int d = coins[i];
                            int c1 = 1;
                            while (d <= a)
                            {
                                int c2 = count(i + 1, a - d);
                                if (c2 != -1)
                                {
                                    c = (c == -1 ? c1 + c2 : min(c, c1 + c2));
                                }
                                d += coins[i];
                                c1++;
                            }
                        }
                        m[p] = c;
                    }
                }
                cout << string(i, ' ') << "= " << m[p] << endl;
                return m[p];
            };
            return count(0, amount);
        }
        int coinChange2(const vector<int> &coins, int amount)
        {
            vector<int> change(amount, 0);
            function<int(int)> count = [&](int a) -> int
            {
                if (a < 0)
                    return -1;
                if (a == 0)
                    return 0;
                if (change[a - 1] != 0)
                    return change[a - 1];
                int r = -1;
                for (int c : coins)
                {
                    int s = count(a - c);
                    if (s != -1)
                        r = (r == -1 ? 1 + s : min(r, 1 + s));
                }
                change[a - 1] = r;
                return r;
            };
            return count(amount);
        }
        int coinChange3(const vector<int> &coins, int amount)
        {
            vector<int> count(amount + 1, amount + 1);
            count[0] = 0;
            for (int a = 1; a <= amount; a++)
            {
                for (int c : coins)
                {
                    if (c <= a)
                        count[a] = min(count[a], 1 + count[a - c]);
                }
            }
            return count[amount] > amount ? -1 : count[amount];
        }

        // 324. Wiggle Sort II
        // Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3] ...
        // You may assume the input array always has a valid answer.
        // Example 1:
        // Input: nums = [1,5,1,1,6,4]
        // Output: [1,6,1,5,1,4]
        // Explanation: [1,4,1,5,1,6] is also accepted.
        // Example 2:
        // Input: nums = [1,3,2,2,3,1]
        // Output: [2,3,1,3,1,2]
        // Constraints:
        // 1 <= nums.length <= 5 * 10^4
        // 0 <= nums[i] <= 5000
        // It is guaranteed that there will be an answer for the given input nums.
        // Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra space?
        void wiggleSort(vector<int> &nums)
        {
            vector<int> v(nums.begin(), nums.end());
            sort(v.begin(), v.end());
            int n = nums.size();
            int largeCount = n >> 1;
            int smallCount = n - largeCount;
            int i = 1;
            n--;
            while (largeCount > 0)
            {
                nums[i] = v[n--];
                i += 2;
                largeCount--;
            }
            i = 0;
            while (smallCount > 0)
            {
                nums[i] = v[n--];
                i += 2;
                smallCount--;
            }
        }
        void wiggleSort2(vector<int> &nums)
        {
            int n = nums.size();
            int m = (n - 1) >> 1;
            // Rearrange so that nums[m] is the m-th element
            nth_element(nums.begin(), nums.begin() + m, nums.end());
            int median = nums[m];
            int o = 1;                              // odd position
            int e = ((n & 1) == 0) ? n - 2 : n - 1; // even position
            for (int i = 0; i < n; i++)
            {
                if (nums[i] > median)
                {
                    if ((i & 1) && i < o) // i is odd and already processed
                        continue;
                    swap(nums[o], nums[i--]);
                    o += 2;
                }
                else if (nums[i] < median)
                {
                    if (!(i & 1) && i > e) // i is even and already processed
                        continue;
                    swap(nums[e], nums[i--]);
                    e -= 2;
                }
            }
        }

        // 326. Power of Three
        // Given an integer n, return true if it is a power of three. Otherwise, return false.
        // An integer n is a power of three, if there exists an integer x such that n == 3^x.
        // Example 1:
        // Input: n = 27
        // Output: true
        // Example 2:
        // Input: n = 0
        // Output: false
        // Example 3:
        // Input: n = 9
        // Output: true
        // Example 4:
        // Input: n = 45
        // Output: false
        // Constraints:
        // -2^31 <= n <= 2^31 - 1
        // Follow up: Could you solve it without loops/recursion?
        bool isPowerOfThree(int n)
        {
            if (n <= 0)
                return false;
            if (n == 1)
                return true;
            int d = n % 10;
            if (d != 1 && d != 3 && d != 7 && d != 9)
                return false;
            while (n > 1)
            {
                if (n % 3 != 0)
                    return false;
                n /= 3;
            }
            return true;
        }
        bool isPowerOfThree2(int n)
        {
            if (n <= 0)
                return false;
            if (n == 1)
                return true;
            long long d = n % 10;
            if (d != 1 && d != 3 && d != 7 && d != 9)
                return false;
            d = 3;
            while (n > 1 && d > 1)
            {
                if (d > n)
                {
                    d /= 3;
                }
                else
                {
                    if (n % d != 0)
                        return false;
                    long long e = d * d;
                    if (e <= n)
                    {
                        d = e;
                    }
                    else
                    {
                        n /= d;
                    }
                }
            }
            return n == 1;
        }

        // 327. Count of Range Sum
        // Given an integer array nums and two integers lower and upper,
        // return the number of range sums that lie in [lower, upper] inclusive.
        // Range sum S(i, j) is defined as the sum of the elements in nums
        // between indices i and j inclusive, where i <= j.
        // Example 1:
        // Input: nums = [-2,5,-1], lower = -2, upper = 2
        // Output: 3
        // Explanation: The three ranges are: [0,0], [2,2], and [0,2] and
        // their respective sums are: -2, -1, 2.
        // Example 2:
        // Input: nums = [0], lower = 0, upper = 0
        // Output: 1
        // Constraints:
        // 1 <= nums.length <= 104
        // -2^31 <= nums[i] <= 2^31 - 1
        // -3 * 10^4 <= lower <= upper <= 3 * 10^4
        // Follow up: A naive algorithm of O(n^2) is trivial, Could you do better than that?
        int countRangeSum(vector<int> &nums, int lower, int upper)
        {
            vector<long long> r(nums.begin(), nums.end());
            int c = 0;
            for (size_t l = 1; l <= nums.size(); l++)
            {
                for (size_t i = 0; i + l - 1 < nums.size(); i++)
                {
                    if (l > 1)
                        r[i] += nums[i + l - 1];
                    if (lower <= r[i] && r[i] <= upper)
                        c++;
                }
            }
            return c;
        }
        int countRangeSum2(vector<int> &nums, int lower, int upper)
        {
            vector<long long> r(nums.begin(), nums.end());
            // r[i] = sum(nums[0..i]);
            partial_sum(r.begin(), r.end(), r.begin());
            function<int(int, int)> mergeSort = [&](int b, int e) -> int
            {
                if (b > e)
                    return 0;
                if (b == e)
                    return (lower <= r[b] && r[b] <= upper) ? 1 : 0;
                int m = b + ((e - b) >> 1);
                int c1 = mergeSort(b, m);     // sort(r[b..m])
                int c2 = mergeSort(m + 1, e); // sort(r[(m+1)..e])
                int c3 = 0;
                int l = m + 1;
                int h = m + 1;
                for (int i = b; i <= m; i++)
                {
                    while (l <= e && (r[l] - r[i]) < lower)
                        l++;
                    while (h <= e && (r[h] - r[i]) <= upper)
                        h++;
                    c3 += h - l;
                }
                // sort(r[b..e])
                inplace_merge(r.begin() + b, r.begin() + m + 1, r.begin() + e + 1);
                return c1 + c2 + c3;
            };
            return mergeSort(0, r.size() - 1);
        }
        // idea of twosum
        int countRangeSum3(vector<int> &nums, int lower, int upper)
        {
            map<long long, int> m;
            int n = nums.size();
            int c = 0;
            long long sum = 0;
            for (int i = 0; i < n; i++)
            {
                sum += nums[i];
                for (int j = lower; j <= upper; j++)
                {
                    if (sum == j)
                        c++;
                    long long d = sum - j; // lower <= sum - d <= upper
                    if (m.find(d) != m.end())
                        c += m[d];
                }
                if (m.find(sum) == m.end())
                    m[sum] = 0;
                m[sum]++;
            }
            return c;
        }
        // Let partial sum a[i] = sum(nums[0..i])
        // Order all unique partial sums upto index i, so
        // b[1] < b[2] < ... < b[j],
        // where assuming there are j unique sums from a[0] to a[i].
        // We want to find all the ranges whose ending is at i such that its range sum
        // is within [lower, upper]. So we need to find b[p] and b[q], such that
        // b[q] = a[i], and
        // lower <= a[i] - b[p] <= upper, i.e., a[i] - upper <= b[p] <= a[i] - lower.
        // So we need to count all the b[p] in the range. Let the accumulative count
        // c[j] be the count of all the unique partial sums upto b[j], then we have
        // c[1] < c[2] < ... < c[j].
        // Now the count of b[p] within [a[i] - upper, a[i] - lower] is just the difference
        // of two c[l] and c[u] that match the range of b[p], and this can be solved
        // by binary index tree.
        int countRangeSum4(vector<int> &nums, int lower, int upper)
        {
            if (nums.empty())
                return 0;
            vector<long long> sums(nums.begin(), nums.end());
            partial_sum(sums.begin(), sums.end(), sums.begin()); // sums[i] = sum(nums[0..i])
            set<long long> sorted(sums.begin(), sums.end());
            sorted.insert(0); // sorted sums from 0 to the largest sum
            unordered_map<long long, int> m;
            int rank = 1;
            for (auto s : sorted)
                m[s] = rank++;
            // binary index tree. bit[i] is the count of the unique sum whose rank <= i
            class BIT
            {
            private:
                int lsb(int i)
                {
                    return i & (-i);
                }

            public:
                vector<long long> sum;
                BIT(int n) { sum.resize(n); }
                void update(int i, long long val)
                {
                    while (i < (int)sum.size())
                    {
                        sum[i] += val;
                        i += lsb(i);
                    }
                }
                long long query(int i)
                {
                    long long r = 0;
                    while (i > 0)
                    {
                        r += sum[i];
                        i -= lsb(i);
                    }
                    return r;
                }
            } bit(rank);
            bit.update(m[0], 1); // there is only one sum 0
            int res = 0;
            for (auto sum : sums)
            {
                // *it is the least element such that sum - lower < *it, i.e., sum - *it < lower
                auto it = sorted.upper_bound(sum - lower);
                if (it != sorted.begin())
                {
                    it--;                      // now *it <= sum - lower, i.e., lower <= sum - *it
                    int u = bit.query(m[*it]); // count of sums whose rank <= (*it)'s rank
                    // *it2 is the least element such that sum - upper <= *it2, i.e., sum - *it2 <= upper
                    auto it2 = sorted.lower_bound(sum - upper);
                    if (it2 != sorted.end())
                    {
                        int l = bit.query(m[*it2] - 1);
                        res += u - l;
                    }
                }
                bit.update(m[sum], 1);
            }
            return res;
        }

        // Odd Even Linked List
        // Given a singly linked list, group all odd nodes together followed by the even
        // nodes. Please note here we are talking about the node number and not the value
        // in the nodes. You should try to do it in place. The program should run in O(1)
        // space complexity and O(nodes) time complexity.
        // Example 1:
        // Input: 1->2->3->4->5->NULL
        // Output: 1->3->5->2->4->NULL
        // Example 2:
        // Input: 2->1->3->5->6->4->7->NULL
        // Output: 2->3->6->7->1->5->4->NULL
        // Note: The relative order inside both the even and odd groups should remain as
        // it was in the input. The first node is considered odd, the second node even and so on ...
        ListNode *oddEvenList(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *p = head;
            ListNode *h2 = nullptr;
            ListNode *t2 = nullptr;
            while (p->next != nullptr)
            {
                ListNode *q = p->next;
                p->next = q->next;
                q->next = nullptr; // tail
                if (h2 == nullptr)
                    h2 = q;
                else
                    t2->next = q;
                t2 = q;
                if (p->next == nullptr)
                    break;
                p = p->next;
            }
            p->next = h2;
            return head;
        }
        ListNode *oddEvenList2(ListNode *head)
        {
            ListNode *t1 = head;                                     // tail of odds
            ListNode *t2 = (head == nullptr ? nullptr : head->next); // tail of evens
            while (t2 != nullptr && t2->next != nullptr)
            {
                ListNode *p = t2->next;
                t2->next = p->next;
                t2 = t2->next;
                p->next = t1->next;
                t1->next = p;
                t1 = p;
            }
            return head;
        }

        // 329. Longest Increasing Path in a Matrix
        // Given an m x n integers matrix, return the length of the longest increasing path in matrix.
        // From each cell, you can either move in four directions: left, right, up, or down. You may
        // not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
        // Example 1:
        // Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
        // Output: 4
        // Explanation: The longest increasing path is [1, 2, 6, 9].
        // Example 2:
        // Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
        // Output: 4
        // Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
        // Example 3:
        // Input: matrix = [[1]]
        // Output: 1
        // Constraints:
        // m == matrix.length
        // n == matrix[i].length
        // 1 <= m, n <= 200
        // 0 <= matrix[i][j] <= 2^31 - 1
        int longestIncreasingPath(vector<vector<int>> &matrix)
        {
            if (matrix.empty() || matrix[0].empty())
                return 0;
            int r = 0;
            int m = matrix.size();
            int n = matrix[0].size();
            function<void(int, int, int, int)> walk = [&](int i, int j, int p, int l)
            {
                if (i < 0 || i >= m || j < 0 || j >= n)
                    return;
                int e = matrix[i][j];
                if (e <= p)
                    return;
                l++;
                r = max(r, l);
                walk(i - 1, j, e, l);
                walk(i, j + 1, e, l);
                walk(i + 1, j, e, l);
                walk(i, j - 1, e, l);
            };
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    walk(i, j, -1, 0);
                }
            }
            return r;
        }
        int longestIncreasingPath2(vector<vector<int>> &matrix)
        {
            if (matrix.empty() || matrix[0].empty())
                return 0;
            int m = matrix.size();
            int n = matrix[0].size();
            map<pair<int, int>, int> l; // max length at a point
            function<int(int, int, int)> length = [&](int i, int j, int p)
            {
                if (i < 0 || i >= m || j < 0 || j >= n)
                    return 0;
                int e = matrix[i][j];
                if (e <= p)
                    return 0;
                auto k = make_pair(i, j);
                if (l.find(k) != l.end())
                    return l[k];
                int r = 0;
                r = max(r, length(i - 1, j, e));
                r = max(r, length(i, j + 1, e));
                r = max(r, length(i + 1, j, e));
                r = max(r, length(i, j - 1, e));
                l[k] = r + 1;
                return l[k];
            };
            int o = 0;
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    o = max(o, length(i, j, -1));
                }
            }
            return o;
        }

        // 330. Patching Array
        // Given a sorted integer array nums and an integer n, add/patch elements
        // to the array such that any number in the range [1, n] inclusive can be
        // formed by the sum of some elements in the array.
        // Return the minimum number of patches required.
        // Example 1:
        // Input: nums = [1,3], n = 6
        // Output: 1
        // Explanation:
        // Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
        // Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
        // Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
        // So we only need 1 patch.
        // Example 2:
        // Input: nums = [1,5,10], n = 20
        // Output: 2
        // Explanation: The two patches can be [2, 4].
        // Example 3:
        // Input: nums = [1,2,2], n = 5
        // Output: 0
        // Constraints:
        // 1 <= nums.length <= 1000
        // 1 <= nums[i] <= 10^4
        // nums is sorted in ascending order.
        // 1 <= n <= 2^31 - 1
        int minPatches(const vector<int> &nums, int n)
        {
            function<bool(size_t, int, const vector<int> &)>
                has = [&](size_t i, int t, const vector<int> &v) -> bool
            {
                if (i >= v.size())
                    return t == 0;
                if (t == 0)
                    return true;
                if (t < 0)
                    return false;
                size_t j = i;
                while (j + 1 < v.size() && v[j] == v[j + 1])
                    j++;
                int a = 0;
                for (size_t k = i; k <= j; k++)
                {
                    a += v[k];
                    if (a > t)
                        break;
                    if (has(j + 1, t - a, v))
                        return true;
                }
                return has(j + 1, t, v);
            };
            int c = 0;
            long long d = 1;
            vector<int> v(nums);
            while (d <= (long long)n)
            {
                if (!has(0, d, v))
                {
                    c++;
                    auto it = upper_bound(v.begin(), v.end(), d);
                    v.insert(it, d);
                    cout << d << endl;
                }
                d = d << 1;
            }
            return c;
        }
        int minPatches2(const vector<int> &nums, int n)
        {
            function<bool(size_t, int, const vector<int> &, map<pair<size_t, int>, bool> &)>
                has = [&](size_t i, int t, const vector<int> &v, map<pair<size_t, int>, bool> &m) -> bool
            {
                if (i >= v.size())
                    return t == 0;
                if (t == 0)
                    return true;
                if (t < 0)
                    return false;
                pair<size_t, int> p = make_pair(i, t);
                if (m.find(p) != m.end())
                    return m[p];
                size_t j = i;
                while (j + 1 < v.size() && v[j] == v[j + 1])
                    j++;
                int a = 0;
                for (size_t k = i; k <= j; k++)
                {
                    a += v[k];
                    if (a > t)
                        break;
                    if (has(j + 1, t - a, v, m))
                    {
                        m[p] = true;
                        return true;
                    }
                }
                m[p] = has(j + 1, t, v, m);
                return m[p];
            };
            int c = 0;
            long long d = 1;
            vector<int> v(nums);
            map<pair<size_t, int>, bool> m;
            while (d <= (long long)n)
            {
                if (!has(0, d, v, m))
                {
                    c++;
                    auto it = upper_bound(v.begin(), v.end(), d);
                    v.insert(it, d);
                }
                d = d << 1;
                m.clear();
            }
            return c;
        }
        // Given sum range  [1,K], adding K+1 to the set making the resulting range to be [1,2*K+1].
        // To extend the range using an int A, we need to have K>=A+1.
        int minPatches3(const vector<int> &nums, int n)
        {
            long long k = 0;
            int c = 0;
            for (auto val : nums)
            {
                if (k >= n)
                    break;
                while (k + 1 < val && k < n)
                {
                    k += (k + 1);
                    c++;
                }
                k += val;
            }

            while (k < n)
            {
                k += (k + 1);
                c++;
            }

            return c;
        }
        // The idea is to greedily add the maximum missing number, and the numbers
        // from nums once we can reach those numbers. Assume we have nums = [1, 5, 10]
        // and we want all numbers to 20. To start thing off, we need to look for a 1.
        // We have a 1 in the array, so are we good. Then we look for a 2. We do not
        // have a 2 in the array, and the next element in the array is 5. This means
        // we must add a patch to get 2. Since we already have 1, we can either add a 1,
        // or we can add a 2. However, if we add a 2, we will be able to make 2 and 3,
        // but if we add a 1, we will only be able to get 2. Since we want the minimum
        // number of patches, we should aim to maximize the new numbers we can make from
        // each patch. Now we can make [1, 4), and we are missing 4, so by the previous
        // logic we would add a 4 as the second patch, to get all numbers between 0 and 7.
        // If we look at the next number in nums, we can see that it is a 5, so we have
        // already covered it. But this is a "free" number. We can add it to any of our
        // sums from 0 ... 7 and get a new number. The maximum number is now 12. This
        // means we are able to increase the numbers we can reach without having to add
        // a patch. Thus, we keep this up, and either add mandatory patches that maximizes
        // the numbers we get, or add in free numbers from nums that extends our maximum
        // range, until we reach the required range.
        int minPatches4(const vector<int> &nums, int n)
        {
            long long k = 1;
            size_t i = 0;
            int c = 0;
            while (k <= n)
            {
                if (i < nums.size() && nums[i] <= k)
                {
                    k += nums[i++];
                }
                else
                {
                    k += k;
                    ++c;
                }
            }
            return c;
        }

        // 331. Verify Preorder Serialization of a Binary Tree
        // One way to serialize a binary tree is to use preorder traversal.
        // When we encounter a non-null node, we record the node's value.
        // If it is a null node, we record using a sentinel value such as '#'.
        // For example, the above binary tree can be serialized to the string
        // "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.
        // Given a string of comma-separated values preorder, return true
        // if it is a correct preorder traversal serialization of a binary tree.
        // It is guaranteed that each comma-separated value in the string must
        // be either an integer or a character '#' representing null pointer.
        // You may assume that the input format is always valid.
        // For example, it could never contain two consecutive commas, such as "1,,3".
        // Example 1:
        // Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
        // Output: true
        // Example 2:
        // Input: preorder = "1,#"
        // Output: false
        // Example 3:
        // Input: preorder = "9,#,#,1"
        // Output: false
        // Constraints:
        // 1 <= preorder.length <= 10^4
        // preoder consist of integers in the range [0, 100] and '#' separated by commas ','.
        // Follow up: Find an algorithm without reconstructing the tree.
        bool isValidSerialization(const string &preorder)
        {
            function<bool(size_t &)> check = [&](size_t &i) -> bool
            {
                if (i >= preorder.size())
                    return false;
                if (preorder[i] == '#')
                {
                    i++; // skip '#'
                    if (i < preorder.size())
                        i++; // skip ','
                    return true;
                }
                while (i < preorder.size() && preorder[i] != ',')
                    i++;
                if (i == preorder.size())
                    return false; // integer without children '#'
                i++;
                if (!check(i)) // check left subtree
                    return false;
                return check(i); // check right subtree
            };
            size_t i = 0;
            return check(i) && i == preorder.size();
        }
        bool isValidSerialization2(const string &preorder)
        {
            if (preorder.empty())
                return false;
            function<void(int, int, const vector<int> &)>
                print = [&](int c, int i, const vector<int> &s)
            {
                cout << "c=" << c << " p[" << c << "]='" << (c == -1 ? '#' : preorder[c - 1]) << "' ";
                cout << "i=" << i << " p[" << i << "]='" << preorder[i] << "' ";
                cout << "s={";
                for (size_t j = 0; j < s.size(); j++)
                {
                    if (j > 0)
                        cout << ",";
                    cout << preorder[s[j] - 1]; // s[j];
                }
                cout << "}" << endl;
            };
            int n = preorder.size();
            int i = 0;
            vector<int> s;
            int c = -1;
            if (preorder[i] == '#')
                return n == 1; // "#" is ok
            while (i < n && preorder[i] != ',')
                i++;
            if (i == n)
                return false;
            c = i;
            i++;
            if (i == n)
                return false;
            while (!s.empty() || c != -1)
            {
                print(c, i, s);
                if (c != -1)
                {
                    s.push_back(c);
                    if (preorder[i] == '#')
                    {
                        i++;
                        if (i < n)
                            i++;
                        if (i == n)
                            return false;
                        c = -1;
                    }
                    else
                    {
                        while (i < n && preorder[i] != ',')
                            i++;
                        if (i == n)
                            return false;
                        c = i;
                        i++;
                    }
                }
                else
                {
                    s.pop_back();
                    if (preorder[i] == '#')
                    {
                        i++;
                        if (i < n)
                            i++;
                    }
                    else
                    {
                        while (i < n && preorder[i] != ',')
                            i++;
                        if (i == n)
                            return false;
                        c = i;
                        i++;
                    }
                }
            }
            return i == n;
        }
        // If current node is a right child, then the node before it must be '#'
        //     parent
        //     /    \
        //    '#'  right
        // or
        //     parent
        //     /    \
        //   left  right
        //   /  \
        // '#'  '#'
        // If current node is a left child, then the node before it must be its parent
        //     parent
        //     /
        //   left
        // or
        //     parent
        //     /
        //   '#'
        bool isValidSerialization3(const string &preorder)
        {
            if (preorder.empty())
                return false;
            int i = preorder.size() - 1;
            if (preorder[i] != '#')
                return false;
            stack<int> s;
            while (i >= 0)
            {
                while (i >= 0 && preorder[i] != ',')
                    i--;
                if ((i - 1 >= 0) && (preorder[i - 1] == '#'))
                {
                    if ((i - 2 >= 0) && (preorder[i - 2] == ','))
                        s.push(i);
                    else
                        return false;
                }
                else if (i >= 0)
                {
                    if (s.empty())
                        return false;
                    s.pop();
                }
                i--;
            }
            return s.empty();
        }

        // 349. Intersection of Two Arrays
        // Given two arrays, write a function to compute their intersection.
        // Example 1:
        // Input: nums1 = [1,2,2,1], nums2 = [2,2]
        // Output: [2]
        // Example 2:
        // Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
        // Output: [9,4]
        // Note: Each element in the result must be unique. The result can be in any
        // order.
        vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> result;
            function<void(vector<int> &, vector<int> &)>
                solve = [&](vector<int> &n1, vector<int> &n2)
            {
                for (int i = 0; i < (int)n1.size(); i++)
                {
                    if (i > 0 && n1[i - 1] == n1[i])
                        continue;
                    int b = 0;
                    int e = (int)n2.size() - 1;
                    while (b <= e)
                    {
                        int m = b + ((e - b) >> 1);
                        if (n2[m] < n1[i])
                            b = m + 1;
                        else if (n2[m] > n1[i])
                            e = m - 1;
                        else
                        {
                            result.push_back(n1[i]);
                            break;
                        }
                    }
                }
            };
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            if (nums1.size() < nums2.size())
                solve(nums1, nums2);
            else
                solve(nums2, nums1);
            return result;
        }
        vector<int> intersection2(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> result;
            set<int> s1(nums1.cbegin(), nums1.cend());
            set<int> s2(nums2.cbegin(), nums2.cend());
            result.resize(min(s1.size(), s2.size()));
            auto it = set_intersection(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(),
                                       result.begin());
            result.resize(it - result.begin());
            return result;
        }
        vector<int> intersection3(const vector<int> &nums1, const vector<int> &nums2)
        {
            vector<int> o;
            function<void(const vector<int> &, const vector<int> &)> solve =
                [&](const vector<int> &n1, const vector<int> &n2)
            {
                set<int> s(n1.cbegin(), n1.cend());
                set<int> u;
                for (int n : n2)
                {
                    if (s.find(n) != s.end() && u.find(n) == u.end())
                    {
                        o.push_back(n);
                        u.insert(n);
                    }
                }
            };
            if (nums1.size() < nums2.size())
                solve(nums1, nums2);
            else
                solve(nums2, nums1);
            return o;
        }
        vector<int> intersection4(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> o;
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            size_t i = 0;
            size_t j = 0;
            while (i < nums1.size() && j < nums2.size())
            {
                if (nums1[i] < nums2[j])
                    i++;
                else if (nums1[i] > nums2[j])
                    j--;
                else
                {
                    o.push_back(nums1[i]);
                    while (i + 1 < nums1.size() && nums1[i] == nums1[i + 1])
                        i++;
                    i++;
                    while (j + 1 < nums2.size() && nums2[j] == nums2[j + 1])
                        j++;
                    j++;
                }
            }
            return o;
        }

        // 350. Intersection of Two Arrays II
        // Given two arrays, write a function to compute their intersection.
        // Example 1:
        // Input: nums1 = [1,2,2,1], nums2 = [2,2]
        // Output: [2,2]
        // Example 2:
        // Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
        // Output: [4,9]
        // Note: Each element in the result should appear as many times as it shows in
        // both arrays. The result can be in any order.
        // Follow up:
        // What if the given array is already sorted? How would you optimize your
        // algorithm? What if nums1's size is small compared to nums2's size? Which
        // algorithm is better? What if elements of nums2 are stored on disk, and the
        // memory is limited such that you cannot load all elements into the memory at
        // once?
        vector<int> intersectII(const vector<int> &nums1, const vector<int> &nums2)
        {
            function<map<int, int>(const vector<int> &)> count =
                [&](const vector<int> &n) -> map<int, int>
            {
                map<int, int> m;
                for (int x : n)
                {
                    if (m.find(x) == m.end())
                        m[x] = 1;
                    else
                        m[x]++;
                }
                return m;
            };
            map<int, int> m1 = count(nums1);
            map<int, int> m2 = count(nums2);
            vector<int> result;
            for (auto it = m1.begin(); it != m1.end(); it++)
            {
                if (m2.find(it->first) != m2.end())
                    result.insert(result.end(), min(it->second, m2[it->first]),
                                  it->first);
            }
            return result;
        }
        vector<int> intersectII2(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> result;
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            result.resize(min(nums1.size(), nums2.size()));
            auto it = set_intersection(nums1.cbegin(), nums1.cend(), nums2.cbegin(),
                                       nums2.cend(), result.begin());
            result.resize(it - result.begin());
            return result;
        }
        vector<int> intersectII3(const vector<int> &nums1, const vector<int> &nums2)
        {
            vector<int> o;
            function<void(const vector<int> &, const vector<int> &)> solve =
                [&](const vector<int> &n1, const vector<int> &n2)
            {
                map<int, int> m;
                for (int n : n1)
                {
                    if (m.find(n) == m.end())
                        m[n] = 1;
                    else
                        m[n]++;
                }
                for (int n : n2)
                {
                    if (m.find(n) != m.end())
                    {
                        o.push_back(n);
                        m[n]--;
                        if (m[n] == 0)
                            m.erase(n);
                    }
                }
            };
            if (nums1.size() < nums2.size())
                solve(nums1, nums2);
            else
                solve(nums2, nums1);
            return o;
        }
        vector<int> intersectII4(vector<int> &nums1, vector<int> &nums2)
        {
            vector<int> o;
            sort(nums1.begin(), nums1.end());
            sort(nums2.begin(), nums2.end());
            size_t i = 0;
            size_t j = 0;
            while (i < nums1.size() && j < nums2.size())
            {
                if (nums1[i] < nums2[j])
                    i++;
                else if (nums1[i] > nums2[j])
                    j++;
                else
                {
                    o.push_back(nums1[i]);
                    i++;
                    j++;
                }
            }
            return o;
        }

        // 367. Valid Perfect Square
        // Given a positive integer num, write a function which returns True if num is a
        // perfect square else False. Note: Do not use any built-in library function
        // such as sqrt. Example 1: Input: 16 Output: true Example 2: Input: 14 Output:
        // false
        bool isPerfectSquare(int num)
        {
            long long x = num;
            long long b = 1;
            long long e = x;
            while (b <= e)
            {
                long long m = b + ((e - b) >> 1);
                long long s = m * m;
                if (s < x)
                    b = m + 1;
                else if (s > x)
                    e = m - 1;
                else
                    return true;
            }
            return false;
        }
        bool isPerfectSquare2(int num)
        {
            long long x = num;
            long long b = 1;
            long long e = x;
            while (b < e)
            {
                long long m = b + ((e - b) >> 1);
                long long s = m * m;
                if (s < x)
                    b = m + 1;
                else if (s > x)
                    e = m;
                else
                    return true;
            }
            return b == e && b * b == x;
        }
        bool isPerfectSquare3(int num)
        {
            long long x = num;
            long long b = 1;
            long long e = x;
            while (b + 1 < e)
            {
                long long m = b + ((e - b) >> 1);
                long long s = m * m;
                if (s < x)
                    b = m;
                else if (s > x)
                    e = m;
                else
                    return true;
            }
            if (b <= e)
            {
                if (b * b == x)
                    return true;
                if (b < e && e * e == x)
                    return true;
            }
            return false;
        }

        // 374. Guess Number Higher or Lower
        // We are playing the Guess Game. The game is as follows:
        // I pick a number from 1 to n. You have to guess which number I picked.
        // Every time you guess wrong, I'll tell you whether the number is higher or
        // lower. You call a pre-defined API guess(int num) which returns 3 possible
        // results: -1 : My number is lower
        //  1 : My number is higher
        //  0 : Congrats! You got it!
        // Example :
        // Input: n = 10, pick = 6
        // Output: 6
        int guess(int x, int pick)
        {
            if (pick < x)
                return -1;
            else if (pick > x)
                return 1;
            else
                return 0;
        }
        int guessNumber(int n, int pick)
        {
            int b = 1;
            int e = n;
            int m = b;
            while (b <= e)
            {
                m = b + ((e - b) >> 1);
                int c = guess(m, pick);
                if (c == -1)
                    e = m - 1;
                else if (c == 1)
                    b = m + 1;
                else
                    break;
            }
            return m;
        }
        int guessNumber2(int n, int pick)
        {
            int b = 1;
            int e = n;
            while (b < e)
            {
                int m = b + ((e - b) >> 1);
                int c = guess(m, pick);
                if (c == -1)
                    e = m;
                else if (c == 1)
                    b = m + 1;
                else
                    return m;
            }
            return b;
        }
        int guessNumber3(int n, int pick)
        {
            int b = 1;
            int e = n;
            while (b + 1 < e)
            {
                int m = b + ((e - b) >> 1);
                int c = guess(m, pick);
                if (c == -1)
                    e = m;
                else if (c == 1)
                    b = m;
                else
                    return m;
            }
            return guess(b, pick) == 0 ? b : e;
        }

    }
}

#endif
