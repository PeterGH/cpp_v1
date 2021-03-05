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

    }
}

#endif
