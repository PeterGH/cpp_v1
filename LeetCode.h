#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include "Log.h"
#include "Util.h"
#include <algorithm>
#include <bitset>
#include <functional>
#include <limits.h>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace Test
{
    namespace LeetCode
    {
        struct ListNode
        {
            int val;
            ListNode *next;
            ListNode(int x) : val(x), next(nullptr) {}
        };

        // Get the node at the index (zero-based)
        static ListNode *GetNode(ListNode *head, int index)
        {
            if (index < 0)
                return nullptr;
            ListNode *p = head;
            int i = 0; // i is at the index of head
            while (i < index && p != nullptr)
            {
                // Hop p and i together
                p = p->next;
                i++;
            }
            // 1. i == index, p != nullptr
            // 2. i == index, p == nullptr
            // 3. i < index, p == nullptr
            return p;
        }
        static ListNode *GetNode2(ListNode *head, int index)
        {
            if (index < 0)
                return nullptr;
            ListNode *p = head;
            int i = 1; // i is at the index of head->next;
            while (i < index && p != nullptr)
            {
                p = p->next; // move p to catch i
                i++;         // but i moves again
                // so i will always be one step ahead
            }
            // 1. index == 0, p == head
            // 2. i == index, p != nullptr, p is at (i - 1)
            // 3. i == index, p == nullptr, p is at (i - 1)
            // 4. i < index, p == nullptr, p is at (i - 1)
            if (index > 0 && p != nullptr)
            {
                // If need to get the prev of the node at index, then just return p
                p = p->next;
            }
            return p;
        }

        // Assume the list has at least one node
        static ListNode *GetLowerMedian(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            // p and q are at the 1st node
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (1 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // 1. q->next == nullptr, p is the median
            // 2. q->next->next == nullptr, p is the lower median
            return p;
        }

        // Assume the list has at least 3 nodes
        static ListNode *GetLowerMedianPrev(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
                return nullptr;
            // p is the 1st node
            ListNode *p = head;
            // q is the 3rd node
            ListNode *q = head->next->next;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (3 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // 1. q->next == nullptr, p is the prev to the median at (2 + k)-th node
            // 2. q->next->next == nullptr, p is the prev to the lower median at (2 + k)-th node
            return p;
        }

        // Assume the list has at least one node
        static ListNode *GetHigherMedian(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            // p and q are at the 1st node
            ListNode *p = head;
            ListNode *q = head;
            while (q != nullptr && q->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (1 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // 1. q == nullptr, i.e, the list has 2k nodes and p is at (1 + k)-th node
            // 2. q->next == nullptr, i.e., the list has (1 + 2k) nodes and p is at (1 + k)-th node
            return p;
        }

        // Assume the list has at least 2 nodes
        static ListNode *GetHigherMedianPrev(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return nullptr;
            ListNode *p = head;
            ListNode *q = head->next;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                // p is (1 + k)-th node
                // q is (2 + 2k)-th node
                p = p->next;
                q = q->next->next;
            }
            // q->next == nullptr, p is the prev to the higher median at (2 + k)-th node
            // q->next->next == nullptr, p is the prev to the median at (2 + k)-th node
            return p;
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
            function<pair<int, int>(int, int)> expand = [&](int l,
                                                            int r) -> pair<int, int> {
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
            set<tuple<int, int>> m;
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
        // [TODO] Generalize to X-Sum
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

        void Print(ListNode *node)
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

        void DeleteList(ListNode *node)
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

        ListNode *ToList(const vector<int> &numbers)
        {
            ListNode *list = nullptr;
            if (numbers.empty())
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

        ListNode *DuplicateList(ListNode *node)
        {
            ListNode *list = nullptr;
            ListNode *node2 = nullptr;
            while (node != nullptr)
            {
                if (list == nullptr)
                {
                    list = new ListNode(node->val);
                    node2 = list;
                }
                else
                {
                    node2->next = new ListNode(node->val);
                    node2 = node2->next;
                }
                node = node->next;
            }
            return list;
        }

        int CompareLists(ListNode *node1, ListNode *node2)
        {
            while (node1 != nullptr && node2 != nullptr)
            {
                if (node1->val < node2->val)
                    return -1;
                if (node1->val > node2->val)
                    return 1;
                node1 = node1->next;
                node2 = node2->next;
            }
            if (node1 == nullptr && node2 == nullptr)
                return 0;
            if (node1 == nullptr)
                return -1;
            return 1;
        }

        vector<int> ToVector(ListNode *node)
        {
            vector<int> v;
            while (node != nullptr)
            {
                v.push_back(node->val);
                node = node->next;
            }
            return v;
        }

        bool IsSorted(ListNode *node)
        {
            while (node != nullptr && node->next != nullptr)
            {
                if (node->val > node->next->val)
                    return false;
                node = node->next;
            }
            return true;
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
        //     Open brackets must be closed by the same type of brackets.
        //     Open brackets must be closed in the correct order.
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
            function<ListNode *(ListNode *, ListNode *)> merge = [&](ListNode *n1, ListNode *n2) -> ListNode * {
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
                                                               const string &s) {
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
                            int n, vector<string> &o) {
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
            function<ListNode *(ListNode *)> solve = [&](ListNode *node) -> ListNode * {
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
                [&](ListNode *h) -> ListNode * {
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
        // Constraints:
        // 1 <= s.length <= 104
        // s consists of lower-case English letters.
        // 1 <= words.length <= 5000
        // 1 <= words[i].length <= 30
        // words[i] consists of lower-case English letters.
        vector<int> findSubstring(const string &s, const vector<string> &words)
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
        vector<int> findSubstring2(const string &s, const vector<string> &words)
        {
            function<bool(const map<char, int> &, const map<char, int> &)> equal =
                [&](const map<char, int> &m1, const map<char, int> &m2) -> bool {
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
            for (; i < (int)s.size(); i++)
            {
                if (s[i] == ')' && !p.empty() && s[p.top()] == '(')
                {
                    p.pop();
                }
                else
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
        int longestValidParentheses4(const string &s)
        {
            int len = s.length();
            if (len == 0)
                return 0;
            function<bool(int &, int &)> expand = [&](int &j, int &k) -> bool {
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
        vector<int> searchRange2(const vector<int> &nums, int target)
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
        vector<int> searchRange3(const vector<int> &nums, int target)
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
        vector<int> searchRange4(const vector<int> &nums, int target)
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
                [&](size_t i, size_t j, vector<vector<char>> &b) -> bool {
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
            function<void(int &, int, int &, int)> oneStep = [&](int &i, int r, int &j,
                                                                 int c) {
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
            function<void(size_t, int, vector<int> &)> solve = [&](size_t i, int t,
                                                                   vector<int> &v) {
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
        vector<vector<int>> combinationSum_2(const vector<int> &candidates,
                                             int target)
        {
            vector<vector<int>> result;
            function<void(size_t, int, vector<int> &)> solve = [&](size_t i, int t,
                                                                   vector<int> &v) {
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
        vector<vector<int>> combinationSum_3(vector<int> &candidates, int target)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            sort(candidates.begin(), candidates.end());
            function<void(int, int, vector<int> &)> solve = [&](int i, int t,
                                                                vector<int> &s) {
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
        vector<vector<int>> combinationSum_4(vector<int> &candidates, int target)
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
        vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
        {
            vector<vector<int>> result;
            sort(candidates.begin(), candidates.end());
            function<void(size_t, int, vector<int> &)> solve = [&](size_t i, int t,
                                                                   vector<int> &v) {
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
        vector<vector<int>> combinationSum2_2(vector<int> &candidates, int target)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            // Sort so we can eliminate duplicate solutions later
            // [Can we not use sort? Instead using a set of <i,t> pairs to track the
            // visited?]
            std::sort(candidates.begin(), candidates.end());
            function<void(size_t, int, vector<int> &)> solve = [&](size_t i, int t,
                                                                   vector<int> &c) {
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
        vector<vector<int>> combinationSum2_3(vector<int> &candidates, int target)
        {
            vector<vector<int>> result = vector<vector<int>>{};
            // Sort so we can eliminate duplicate solutions later
            std::sort(candidates.begin(), candidates.end());
            function<void(size_t, int, vector<int> &)> solve = [&](size_t i, int t,
                                                                   vector<int> &c) {
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
        // This is wrong. For [0,2,2,1,1], expect 3 but get 2
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
            function<int(int, int)> count = [&](int i, int j) -> int {
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
            function<string(const string &, char)> mul = [&](const string &s,
                                                             char d) -> string {
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
                [&](const string &s1, const string &s2) -> string {
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
            function<int(char)> toDigit = [&](char c) { return c - '0'; };
            function<char(int)> toChar = [&](int i) { return i + '0'; };
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
        bool isMatch(string s, string p)
        {
            function<bool(size_t, size_t)> match = [&](size_t i, size_t j) -> bool {
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
        bool isMatch2(string s, string p)
        {
            map<pair<size_t, size_t>, bool> m;
            function<bool(size_t, size_t)> match = [&](size_t i, size_t j) -> bool {
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
        // http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html
        bool isMatch3(string s, string p)
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
            function<bool(const char *, const char *,
                          map<pair<const char *, const char *>, bool> &)>
                isMatchInternal =
                    [&](const char *s, const char *p,
                        map<pair<const char *, const char *>, bool> &m) -> bool {
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
            size_t j = i + nums[i];
            while (i + 1 < nums.size())
            {
                size_t t = j;
                for (size_t k = i + 1; k <= j && k < nums.size(); k++)
                    t = max(t, k + nums[k]);
                s++;
                i = j;
                j = t;
            }
            return s;
        }
        int jump2(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            vector<int> steps(nums.size(), nums.size());
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
            step[0] = nums.size() - 1;
            for (int i = (int)nums.size() - 2; i >= 0; i--)
            {
                int j = i + nums[i];
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
            function<void(size_t)> solve = [&](size_t i) {
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
            function<void(size_t, vector<int> &)> solve = [&](size_t i,
                                                              vector<int> &n) {
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
            function<void(size_t, vector<int> &)> solve = [&](size_t i,
                                                              vector<int> &n) {
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
            function<void(size_t)> solve = [&](size_t i) {
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
            function<void(size_t, vector<int> &)> solve = [&](size_t i,
                                                              vector<int> &n) {
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
            for_each(strs.begin(), strs.end(), [&](const string &s) {
                string k(s);
                sort(k.begin(), k.end());
                if (m.find(k) == m.end())
                    m[k] = vector<string>{};
                m[k].push_back(s);
            });
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
            function<double(int)> p = [&](int k) -> double {
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
            function<void(int, vector<string> &)> solve = [&](int i,
                                                              vector<string> &b) {
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
                    vector<vector<string>> &solutions) {
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
            function<void(int)> solve = [&](int i) {
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
                [&](vector<vector<bool>> &board, int line) -> int {
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
            function<void(int, int, int, int)> solve = [&](int i, int j, int m, int n) {
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
                 [&](const vector<int> &l, const vector<int> &r) -> bool {
                     if (l[0] == r[0])
                         return l[1] < r[1];
                     return l[0] < r[0];
                 });
            for (size_t i = 0; i < intervals.size(); i++)
            {
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
                [&](const Interval &first, const Interval &second) -> bool {
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
                [&](int v, int i, int j, int r, int c) -> int {
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
                d[i] = k / f;
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
                i++;
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
            int a = 1;
            int b = 2;
            int c;
            for (int i = n - 2; i > 0; i--)
            {
                c = b + a;
                a = b;
                b = c;
            }
            return c;
        }
        // C[n] = C[n - 1] + C[n - 2]
        // Another option is C[i] = C[i + 1] + C[i + 2], where C[n] = 0, C[n - 1] = 1,
        // C[n - 2] = 2, C[n - 3] = 3, ..., C[1] = ?
        int climbStairs2(int n)
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
        int climbStairs3(int n)
        {
            map<int, int> m;
            function<int(int)> f = [&](int k) -> int {
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
            if (path.empty())
                return path;
            if (path[0] != '/')
                path.insert(0, 1, '/');
            size_t i = 0;
            size_t j = 1;
            while (j < path.size())
            {
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
        string simplifyPath2(string path)
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
        string simplifyPath3(string path)
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
                for_each(tokens.begin(), tokens.end(), [&](string &t) {
                    output.append(1, '/');
                    output.append(t.begin(), t.end());
                });
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
            function<int(size_t, size_t)> solve = [&](size_t i, size_t j) -> int {
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
                    m[p] = word2.size() - j;
                    return m[p];
                }
                if (j == word2.size())
                {
                    m[p] = word1.size() - i;
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
                               map<pair<int, int>, int> &d) -> int {
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
        // d[m-1][n-1] = 0,                                     if w1[m-1] == w2[n-1]
        //               1,                                     if w1[m-1] != w2[n-1]
        // d[m-1][j]   = n - 1 - j,                               if w1[m-1] == w2[j]
        //               1 + min { n - 1 - j, d[m-1][j+1] },      if w1[m-1] != w2[j]
        // d[i][n-1]   = m - 1 - i,                               if w1[i] == w2[n-1]
        //               1 + min { m - 1 - i, d[i+1][n-1] },      if w1[i] != w2[n-1]
        // d[i][j] = d[i+1][j+1],                                   if w1[i] == w2[j]
        //           1 + min { d[i][j+1], d[i+1][j+1], d[i+1][j] }, if w1[i] != w2[j]
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

        // Search a 2D Matrix II
        // Write an efficient algorithm that searches for a value in an m x n matrix.
        // This matrix has the following properties:
        // Integers in each row are sorted in ascending from left to right.
        // Integers in each column are sorted in ascending from top to bottom.
        // Example:
        // Consider the following matrix:
        // [
        //   [1,   4,  7, 11, 15],
        //   [2,   5,  8, 12, 19],
        //   [3,   6,  9, 16, 22],
        //   [10, 13, 14, 17, 24],
        //   [18, 21, 23, 26, 30]
        // ]
        // Given target = 5, return true.
        // Given target = 20, return false.
        bool searchMatrixII(vector<vector<int>> &matrix, int target)
        {
            if (matrix.empty() || matrix[0].empty())
                return false;
            function<bool(int, int, int, int)> search =
                [&](int r0, int r1, int c0, int c1) -> bool {
                if (r0 > r1 || c0 > c1)
                    return false;
                if (r1 - r0 <= 1 && c1 - c0 <= 1)
                {
                    for (int i = r0; i <= r1; i++)
                    {
                        for (int j = c0; j <= c1; j++)
                        {
                            if (matrix[i][j] == target)
                                return true;
                        }
                    }
                    return false;
                }
                int i = r0 + ((r1 - r0) >> 1);
                int j = c0 + ((c1 - c0) >> 1);
                if (matrix[i][j] < target)
                {
                    if (search(i + 1, r1, j + 1, c1))
                        return true;
                }
                else if (matrix[i][j] > target)
                {
                    if (search(r0, i - 1, c0, j - 1))
                        return true;
                }
                else
                {
                    return true;
                }
                if (search(r0, i, j, c1))
                    return true;
                if (search(i, r1, c0, j))
                    return true;
                return false;
            };
            int m = matrix.size();
            int n = matrix[0].size();
            return search(0, m - 1, 0, n - 1);
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
        string minWindow2(const string &s, const string &t)
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
            function<void(int, int, vector<int> &)> solve = [&](int i, int c,
                                                                vector<int> &v) {
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
            function<void(int, int, vector<int> &)> select = [&](int i, int l,
                                                                 vector<int> &c) {
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
                    [&](int i, int j, map<pair<int, int>, vector<vector<int>>> &s) {
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
                        for_each(s[q2].begin(), s[q2].end(),
                                 [&](vector<int> &v) { s[p].push_back(v); });
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
        // [TODO] Use subset algorithm to solve this problem
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
                             [&](vector<int> &v) { v.push_back(i + j); });
                    // Extend s[i] = s(i+j,j) by adding s(i-1+j,j)
                    for_each(s[i - 1].begin(), s[i - 1].end(),
                             [&](vector<int> &v) { s[i].push_back(v); });
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
                [&](vector<int> pre, int i, int k1, vector<vector<int>> &s) {
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
                [&](size_t i, size_t k, vector<int> &v) {
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
            function<bool(size_t, size_t, size_t, set<pair<size_t, size_t>> &)> solve =
                [&](size_t i, size_t j, size_t k,
                    set<pair<size_t, size_t>> &v) -> bool {
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
                [&](pair<int, int> &p, int i, set<pair<int, int>> &v) -> bool {
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
            function<bool(int, int)> solve = [&](int l, int h) -> bool {
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
            function<bool(int, int)> search = [&](int l, int r) -> bool {
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
                [&](ListNode *h) -> ListNode * {
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
                int j;
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
            function<int(const vector<int> &)> solve =
                [&](const vector<int> &v) -> int {
                stack<pair<int, int>> s;
                int m = 0;
                for (int i = 0; i < (int)v.size(); i++)
                {
                    if (s.empty() || s.top().second <= v[i])
                    {
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
            function<int(int, int)> solve = [&](int pi, int pj) {
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
            ListNode *p = nullptr;
            if (head->val < x)
                p = head;
            while (p != nullptr && p->next != nullptr && p->next->val < x)
                p = p->next;
            ListNode *q = p == nullptr ? head : p->next;
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
        ListNode *partition3(ListNode *head, int x)
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
                [&](const map<char, int> &m1, const map<char, int> &m2) -> bool {
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
                                                           int j2) -> bool {
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
                                                                int j2) -> bool {
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
        // A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
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
            function<int(int)> solve = [&](int i) -> int {
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
            ListNode *p = nullptr;
            ListNode *q = head;
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
                if (p == nullptr)
                {
                    t->next = head;
                    head = t;
                }
                else
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
            ListNode *p = nullptr;
            int i = 1;
            ListNode *q = head;
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
            function<bool(int, int)> isValid = [&](int i, int j) -> bool {
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
            function<void(int, int, string &)> solve = [&](int i, int j, string &p) {
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

        struct TreeNode
        {
            int val;
            TreeNode *left;
            TreeNode *right;
            TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        };

        void Print(TreeNode *node)
        {
            function<void(stringstream *, int, char)> printChar = [&](stringstream *s,
                                                                      int n, char c) {
                if (n > 0)
                {
                    string chars(n, c);
                    *s << chars;
                }
            };
            function<void(TreeNode *, unsigned int, int &, int &,
                          vector<stringstream *> &)>
                toString =
                    [&](TreeNode *n,               // current node to print
                        unsigned int y,            // current node level
                        int &x,                    // x-axis position of root of last printed sub tree
                        int &r,                    // x-axis position of right-most boundary of last
                                                   // printed sub tree
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

        void DeleteTree(TreeNode *root)
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

        TreeNode *Clone(TreeNode *root)
        {
            if (root == nullptr)
                return nullptr;
            TreeNode *clone = new TreeNode(root->val);
            clone->left = Clone(root->left);
            clone->right = Clone(root->right);
            return clone;
        }

        TreeNode *CloneReverse(TreeNode *root)
        {
            if (root == nullptr)
                return nullptr;
            TreeNode *clone = new TreeNode(root->val);
            clone->left = CloneReverse(root->right);
            clone->right = CloneReverse(root->left);
            return clone;
        }

        TreeNode *RandomTree(const vector<int> &values)
        {
            if (values.empty())
                return nullptr;
            function<TreeNode *(const vector<int> &, int, int)> create =
                [&](const vector<int> &v, int i, int j) -> TreeNode * {
                if (i > j)
                    return nullptr;
                TreeNode *n = nullptr;
                int k = rand() % 3;
                switch (k)
                {
                case 0: // preorder
                    n = new TreeNode(v[i]);
                    k = i + 1 + (rand() % (j - i + 1));
                    n->left = create(v, i + 1, k - 1);
                    n->right = create(v, k, j);
                    break;
                case 1: // inorder
                    k = i + (rand() % (j - i + 1));
                    n = new TreeNode(v[k]);
                    n->left = create(v, i, k - 1);
                    n->right = create(v, k + 1, j);
                    break;
                case 2: // postorder
                    n = new TreeNode(v[j]);
                    k = i - 1 + (rand() % (j - i + 1));
                    n->left = create(v, i, k);
                    n->right = create(v, k + 1, j - 1);
                    break;
                }
                return n;
            };
            return create(values, 0, values.size() - 1);
        }

        TreeNode *RandomTree(int num)
        {
            if (num <= 0)
                return nullptr;
            int t = 0;
            function<TreeNode *(int, int)> create = [&](int i, int j) -> TreeNode * {
                if (i > j || t >= num)
                    return nullptr;
                TreeNode *n = new TreeNode(t++);
                if (t >= num)
                    return n;
                int k = rand() % 3;
                switch (k)
                {
                case 0: // preorder
                    k = i + 1 + (rand() % (j - i + 1));
                    n->left = create(i + 1, k - 1);
                    n->right = create(k, j);
                    break;
                case 1: // inorder
                    k = i + (rand() % (j - i + 1));
                    n->left = create(i, k - 1);
                    n->right = create(k + 1, j);
                    break;
                case 2: // postorder
                    k = i - 1 + (rand() % (j - i + 1));
                    n->left = create(i, k);
                    n->right = create(k + 1, j - 1);
                    break;
                }
                return n;
            };
            return create(0, num - 1);
        }

        TreeNode *RandomTreeFromInOrder(const vector<int> &values)
        {
            if (values.empty())
                return nullptr;
            function<TreeNode *(const vector<int> &, int, int)> create =
                [&](const vector<int> &v, int i, int j) -> TreeNode * {
                if (i > j)
                    return nullptr;
                int k = i + (rand() % (j - i + 1));
                TreeNode *n = new TreeNode(v[k]);
                n->left = create(v, i, k - 1);
                n->right = create(v, k + 1, j);
                return n;
            };
            return create(values, 0, values.size() - 1);
        }

        TreeNode *RandomSymmetricTree(const vector<int> &values)
        {
            int i = rand() % values.size();
            int v = values[i];
            vector<int> w(values);
            w.erase(w.begin() + i);
            TreeNode *n = new TreeNode(v);
            n->left = RandomTree(w);
            n->right = CloneReverse(n->left);
            return n;
        }

        // 144. Binary Tree Preorder Traversal
        // Given a binary tree, return the preorder traversal of its nodes' values.
        // Example:
        // Input: [1,null,2,3]
        //    1
        //     \
        //      2
        //     /
        //    3
        // Output: [1,2,3]
        // Follow up: Recursive solution is trivial, could you do it iteratively?
        vector<int> preorderTraversal(TreeNode *root)
        {
            vector<int> v;
            // Simulate the stack in recursive traversal
            stack<TreeNode *> s;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    v.push_back(n->val);
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    n = s.top()->right;
                    // Pop the top. Do not want to come back to it
                    // after finishing its right tree.
                    s.pop();
                }
            }
            return v;
        }
        vector<int> preorderTraversal2(TreeNode *root)
        {
            vector<int> v;
            if (root == nullptr)
                return v;
            stack<TreeNode *> s;
            s.push(root);
            TreeNode *n;
            while (!s.empty())
            {
                n = s.top();
                s.pop();
                v.push_back(n->val);
                if (n->right != nullptr)
                    s.push(n->right);
                if (n->left != nullptr)
                    s.push(n->left);
            }
            return v;
        }
        vector<int> preorderTraversal3(TreeNode *root)
        {
            vector<int> v;
            if (root == nullptr)
                return v;
            // Track the path to the current node being visited
            stack<TreeNode *> path;
            path.push(root);
            TreeNode *prev = root;
            while (!path.empty())
            {
                TreeNode *n = path.top();
                if (prev == n->right)
                {
                    path.pop();
                }
                else if (n->left != nullptr && n->left != prev)
                {
                    v.push_back(n->val);
                    path.push(n->left);
                }
                else
                {
                    if (n->left == nullptr)
                        v.push_back(n->val);
                    if (n->right == nullptr)
                        path.pop();
                    else
                        path.push(n->right);
                }
                prev = n;
            }
            return v;
        }
        vector<int> preorderTraversal4(TreeNode *root)
        {
            vector<int> v;
            function<void(TreeNode *)> visit = [&](TreeNode *n) {
                if (n == nullptr)
                    return;
                v.push_back(n->val);
                visit(n->left);
                visit(n->right);
            };
            visit(root);
            return v;
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
            function<void(TreeNode *)> trav = [&](TreeNode *n) {
                if (n == nullptr)
                    return;
                trav(n->left);
                v.push_back(n->val);
                trav(n->right);
            };
            trav(root);
            return v;
        }

        // 145. Binary Tree Postorder Traversal
        // Given a binary tree, return the postorder traversal of its nodes' values.
        // Example:
        // Input: [1,null,2,3]
        //    1
        //     \
        //      2
        //     /
        //    3
        // Output: [3,2,1]
        // Follow up: Recursive solution is trivial, could you do it iteratively?
        vector<int> postorderTraversal(TreeNode *root)
        {
            vector<int> v;
            stack<TreeNode *> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    if (t->right != nullptr && t->right != last)
                    {
                        n = t->right;
                    }
                    else
                    {
                        v.push_back(t->val);
                        last = t;
                        s.pop();
                    }
                }
            }
            return v;
        }
        vector<int> postorderTraversal2(TreeNode *root)
        {
            vector<int> results;
            if (root == nullptr)
                return results;
            stack<TreeNode *> s;
            s.push(root);
            TreeNode *last = nullptr;
            while (!s.empty())
            {
                TreeNode *n = s.top();
                if (n->right != nullptr && n->right == last)
                {
                    results.push_back(n->val);
                    s.pop();
                }
                else if (n->left != nullptr && n->left != last)
                {
                    s.push(n->left);
                }
                else
                {
                    if (n->right == nullptr)
                    {
                        results.push_back(n->val);
                        s.pop();
                    }
                    else
                    {
                        s.push(n->right);
                    }
                }
                last = n;
            }
            return results;
        }
        vector<int> postorderTraversal3(TreeNode *root)
        {
            vector<int> results;
            if (root == nullptr)
                return results;
            stack<TreeNode *> s;
            s.push(root);
            set<TreeNode *> visited;
            while (!s.empty())
            {
                TreeNode *n = s.top();
                if ((n->right == nullptr || visited.find(n->right) != visited.end()) &&
                    (n->left == nullptr || visited.find(n->left) != visited.end()))
                {
                    results.push_back(n->val);
                    visited.insert(n);
                    s.pop();
                }
                else
                {
                    if (n->right != nullptr)
                        s.push(n->right);
                    if (n->left != nullptr)
                        s.push(n->left);
                }
            }
            return results;
        }
        vector<int> postorderTraversal4(TreeNode *root)
        {
            vector<int> v;
            function<void(TreeNode *)> trav = [&](TreeNode *n) {
                if (n == nullptr)
                    return;
                trav(n->left);
                trav(n->right);
                v.push_back(n->val);
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
            function<TreeNode *(TreeNode *)> clone = [&](TreeNode *m) -> TreeNode * {
                if (m == nullptr)
                    return nullptr;
                TreeNode *c = new TreeNode(m->val);
                c->left = clone(m->left);
                c->right = clone(m->right);
                return c;
            };
            function<void(TreeNode *)> deleteTree = [&](TreeNode *m) {
                if (m == nullptr)
                    return;
                deleteTree(m->left);
                m->left = nullptr;
                deleteTree(m->right);
                m->right = nullptr;
                delete m;
            };
            function<vector<TreeNode *>(int, int)> bst =
                [&](int i, int j) -> vector<TreeNode *> {
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
                [&](int i, int j) -> vector<vector<int>> {
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
                [&](size_t &i, vector<int> &serialization) -> TreeNode * {
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
        vector<TreeNode *> generateTrees3(int n)
        {
            // Generate all the preorder serializations
            function<vector<vector<int>>(int, int)> generate =
                [&](int i, int j) -> vector<vector<int>> {
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
                [&](const vector<int> &t, int &i, int p) -> TreeNode * {
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
            function<int(int, int)> count = [&](int i, int j) -> int {
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
            function<bool(int, int, int)> solve = [&](int i, int j, int k) -> bool {
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
                match[j] = match[j - 1] && s2[j - 1] == s3[j - 1];
            for (size_t i = 1; i <= s1.size(); i++)
            {
                match[0] = match[0] && s1[i - 1] == s3[i - 1];
                for (size_t j = 1; j <= s2.size(); j++)
                {
                    match[j] = (match[j] && s1[i - 1] == s3[i + j - 1]) ||
                               (match[j - 1] && s2[j - 1] == s3[i + j - 1]);
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
                [&](TreeNode *node, int &min, int &max) -> bool {
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
                [&](TreeNode *node, int &min, int &max) -> bool {
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
                             TreeNode *&n2, TreeNode *&n3, TreeNode *&n4) {
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

        // 100. Same Tree
        // Given two binary trees, write a function to check if they are the same or
        // not. Two binary trees are considered the same if they are structurally
        // identical and the nodes have the same value. Example 1:
        // Input:     1         1
        //           / \       / \
        //          2   3     2   3
        //         [1,2,3],   [1,2,3]
        // Output: true
        // Example 2:
        // Input:     1         1
        //           /           \
        //          2             2
        //         [1,2],     [1,null,2]
        // Output: false
        // Example 3:
        // Input:     1         1
        //           / \       / \
        //          2   1     1   2
        //         [1,2,1],   [1,1,2]
        // Output: false
        bool isSameTree(TreeNode *p, TreeNode *q)
        {
            function<bool(TreeNode *, TreeNode *)> same = [&](TreeNode *a,
                                                              TreeNode *b) -> bool {
                if (a == nullptr && b == nullptr)
                    return true;
                if (a == nullptr || b == nullptr)
                    return false;
                if (a->val != b->val)
                    return false;
                return same(a->left, b->left) && same(a->right, b->right);
            };
            return same(p, q);
        }
        bool isSameTree2(TreeNode *p, TreeNode *q)
        {
            stack<TreeNode *> sp;
            stack<TreeNode *> sq;
            while (!sp.empty() || p != nullptr || !sq.empty() || q != nullptr)
            {
                if (sp.size() != sq.size())
                    return false;
                if ((p == nullptr) != (q == nullptr))
                    return false;
                if (p != nullptr)
                {
                    if (p->val != q->val)
                        return false;
                    sp.push(p);
                    p = p->left;
                    sq.push(q);
                    q = q->left;
                }
                else
                {
                    p = sp.top()->right;
                    sp.pop();
                    q = sq.top()->right;
                    sq.pop();
                }
            }
            return true;
        }
        bool isSameTree3(TreeNode *p, TreeNode *q)
        {
            function<vector<TreeNode *>(TreeNode *)> serialize =
                [&](TreeNode *n) -> vector<TreeNode *> {
                vector<TreeNode *> v;
                stack<TreeNode *> s;
                while (!s.empty() || n != nullptr)
                {
                    // Need to include nullptr to make sure
                    // the serialization is unique
                    v.push_back(n);
                    if (n != nullptr)
                    {
                        s.push(n);
                        n = n->left;
                    }
                    else
                    {
                        n = s.top()->right;
                        s.pop();
                    }
                }
                return v;
            };
            function<void(const vector<TreeNode *> &)> print =
                [&](const vector<TreeNode *> &v) {
                    cout << "{";
                    for (size_t i = 0; i < v.size(); i++)
                    {
                        if (i > 0)
                            cout << ", ";
                        if (v[i] == nullptr)
                            cout << "null";
                        else
                            cout << v[i]->val;
                    }
                    cout << "}" << endl;
                };
            vector<TreeNode *> vp = serialize(p);
            vector<TreeNode *> vq = serialize(q);
            print(vp);
            print(vq);
            if (vp.size() != vq.size())
                return false;
            for (size_t i = 0; i < vp.size(); i++)
            {
                if ((vp[i] == nullptr) != (vq[i] == nullptr))
                    return false;
                if (vp[i] != nullptr && vp[i]->val != vq[i]->val)
                    return false;
            }
            return true;
        }

        // 101. Symmetric Tree
        // Given a binary tree, check whether it is a mirror of itself
        // (ie, symmetric around its center). For example, this binary
        // tree [1,2,2,3,4,4,3] is symmetric:
        //     1
        //    / \
        //   2   2
        //  / \ / \
        // 3  4 4  3
        // But the following [1,2,2,null,3,null,3] is not:
        //     1
        //    / \
        //   2   2
        //    \   \
        //    3    3
        // Note:
        // Bonus points if you could solve it both recursively and iteratively.
        bool isSymmetric(TreeNode *root)
        {
            function<bool(TreeNode *, TreeNode *)> same = [&](TreeNode *p,
                                                              TreeNode *q) -> bool {
                if (p == nullptr && q == nullptr)
                    return true;
                if (p == nullptr || q == nullptr)
                    return false;
                if (p->val != q->val)
                    return false;
                return same(p->left, q->right) && same(p->right, q->left);
            };
            return same(root, root);
        }
        bool isSymmetric2(TreeNode *root)
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
        bool isSymmetric3(TreeNode *root)
        {
            deque<TreeNode *> deq;
            TreeNode *p = root;
            TreeNode *q = root;
            while (!deq.empty() || p != nullptr || q != nullptr)
            {
                if ((p != nullptr) != (q != nullptr))
                    return false;
                if (p != nullptr && q != nullptr)
                {
                    if (p->val != q->val)
                        return false;
                    deq.push_front(p);
                    p = p->left;
                    deq.push_back(q);
                    q = q->right;
                }
                else
                {
                    p = deq.front()->right;
                    deq.pop_front();
                    q = deq.back()->left;
                    deq.pop_back();
                }
            }
            return true;
        }

        // 102. Binary Tree Level Order Traversal
        // Given a binary tree, return the level order traversal of its nodes' values.
        // (ie, from left to right, level by level).
        // For example: Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its level order traversal as:
        // [
        //   [3],
        //   [9,20],
        //   [15,7]
        // ]
        vector<vector<int>> levelOrder(TreeNode *root)
        {
            vector<vector<int>> result;
            if (root == nullptr)
                return result;
            queue<TreeNode *> q[2];
            q[0].push(root);
            int l = 0;
            while (!q[0].empty() || !q[1].empty())
            {
                l = l % 2;
                int n = (l + 1) % 2;
                vector<int> v;
                while (!q[l].empty())
                {
                    v.push_back(q[l].front()->val);
                    if (q[l].front()->left != nullptr)
                        q[n].push(q[l].front()->left);
                    if (q[l].front()->right != nullptr)
                        q[n].push(q[l].front()->right);
                    q[l].pop();
                }
                result.push_back(v);
                l++;
            }
            return result;
        }
        vector<vector<int>> levelOrder2(TreeNode *root)
        {
            vector<vector<int>> result;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int l = 0;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if ((int)result.size() <= l)
                        result.push_back({});
                    result[l].push_back(n->val);
                    s.push(make_pair(n, l));
                    n = n->left;
                    l++;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    l = p.second + 1;
                }
            }
            return result;
        }
        vector<vector<int>> levelOrder3(TreeNode *root)
        {
            vector<vector<int>> result;
            function<void(TreeNode *, size_t)> visit = [&](TreeNode *n, size_t l) {
                if (n == nullptr)
                    return;
                if (result.size() < l)
                    result.push_back({});
                result[l - 1].push_back(n->val);
                visit(n->left, l + 1);
                visit(n->right, l + 1);
            };
            visit(root, 1);
            return result;
        }

        // 103. Binary Tree Zigzag Level Order Traversal
        // Given a binary tree, return the zigzag level order traversal of
        // its nodes' values. (ie, from left to right, then right to left for
        // the next level and alternate between).
        // For example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its zigzag level order traversal as:
        // [
        //   [3],
        //   [20,9],
        //   [15,7]
        // ]
        vector<vector<int>> zigzagLevelOrder(TreeNode *root)
        {
            vector<vector<int>> result;
            if (root == nullptr)
                return result;
            stack<TreeNode *> s[2];
            int l = 0;
            s[0].push(root);
            while (!s[0].empty() || !s[1].empty())
            {
                l = l % 2;
                int n = (l + 1) % 2;
                vector<int> v;
                while (!s[l].empty())
                {
                    v.push_back(s[l].top()->val);
                    if (l == 0)
                    {
                        if (s[l].top()->left != nullptr)
                            s[n].push(s[l].top()->left);
                        if (s[l].top()->right != nullptr)
                            s[n].push(s[l].top()->right);
                    }
                    else
                    {
                        if (s[l].top()->right != nullptr)
                            s[n].push(s[l].top()->right);
                        if (s[l].top()->left != nullptr)
                            s[n].push(s[l].top()->left);
                    }
                    s[l].pop();
                }
                result.push_back(v);
                l++;
            }
            return result;
        }
        vector<vector<int>> zigzagLevelOrder2(TreeNode *root)
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

        // 104. Maximum Depth of Binary Tree
        // Given a binary tree, find its maximum depth. The maximum depth is the
        // number of nodes along the longest path from the root node down to the
        // farthest leaf node. Note: A leaf is a node with no children.
        // Example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its depth = 3.
        int maxDepth(TreeNode *root)
        {
            stack<pair<TreeNode *, int>> s;
            int m = 0;
            TreeNode *n = root;
            int d = 0;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    d++;
                    m = max(m, d);
                    s.push(make_pair(n, d));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    d = p.second;
                }
            }
            return m;
        }
        int maxDepth2(TreeNode *root)
        {
            function<int(TreeNode *)> depth = [&](TreeNode *node) -> int {
                if (node == nullptr)
                    return 0;
                if (node->left == nullptr && node->right == nullptr)
                    return 1;
                return 1 + max(depth(node->left), depth(node->right));
            };
            return depth(root);
        }
        int maxDepth3(TreeNode *root)
        {
            function<int(TreeNode *, int)> depth = [&](TreeNode *n, int d) -> int {
                if (n == nullptr)
                    return 0;
                if (n->left == nullptr && n->right == nullptr)
                    return d;
                return max(depth(n->left, d + 1), depth(n->right, d + 1));
            };
            return depth(root, 1);
        }
        // This is wrong
        int maxDepth4(TreeNode *root)
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

        // 105. Construct Binary Tree from Preorder and Inorder Traversal
        // Given preorder and inorder traversal of a tree, construct the binary tree.
        // Note: You may assume that duplicates do not exist in the tree.
        // For example, given
        // preorder = [3,9,20,15,7]
        // inorder = [9,3,15,20,7]
        // Return the following binary tree:
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        TreeNode *buildTree(const vector<int> &preorder, const vector<int> &inorder)
        {
            map<int, int> m;
            for (int i = 0; i < (int)inorder.size(); i++)
                m[inorder[i]] = i;
            function<TreeNode *(int, int, int, int)> build = [&](int p1, int p2, int i1,
                                                                 int i2) -> TreeNode * {
                if (p2 - p1 != i2 - i1)
                    return nullptr;
                if (p1 > p2 || i1 > i2)
                    return nullptr;
                int i = m[preorder[p1]];
                if (i < i1)
                    return nullptr;
                TreeNode *n = new TreeNode(preorder[p1]);
                n->left = build(p1 + 1, p1 + i - i1, i1, i - 1);
                n->right = build(p1 + i - i1 + 1, p2, i + 1, i2);
                return n;
            };
            return build(0, preorder.size() - 1, 0, inorder.size() - 1);
        }
        TreeNode *buildTree2(const vector<int> &preorder, const vector<int> &inorder)
        {
            if (preorder.size() != inorder.size() || preorder.empty())
                return nullptr;
            stack<TreeNode *> path;
            int i = 0; // index current element in preOrder
            int j = 0; // index current element in inOrder
            int f = 0; // flag to insert to left or right
            // Root
            TreeNode *node = new TreeNode(preorder[i]);
            path.push(node);
            // Current insertion point
            TreeNode *t = node;
            i++;
            while (i < (int)preorder.size())
            {
                if (!path.empty() && path.top()->val == inorder[j])
                {
                    // Done with a left substree, start to insert the right subtree
                    t = path.top();
                    path.pop();
                    f = 1;
                    j++;
                }
                else
                {
                    if (f == 0)
                    {
                        t->left = new TreeNode(preorder[i]);
                        t = t->left;
                    }
                    else
                    {
                        f = 0;
                        t->right = new TreeNode(preorder[i]);
                        t = t->right;
                    }
                    path.push(t);
                    i++;
                }
            }
            return node;
        }
        TreeNode *buildTree3(const vector<int> &preorder, const vector<int> &inorder)
        {
            if (preorder.size() != inorder.size() || preorder.empty())
                return nullptr;
            int p = 0;
            int i = 0;
            function<TreeNode *(int)> build = [&](int val) -> TreeNode * {
                if (i >= (int)inorder.size() || inorder[i] == val)
                    return nullptr;
                TreeNode *n = new TreeNode(preorder[p]);
                p++;
                n->left = build(n->val);
                i++;
                n->right = build(val);
                return n;
            };
            return build(INT_MIN);
        }

        // 106. Construct Binary Tree from Inorder and Postorder Traversal
        // Given inorder and postorder traversal of a tree, construct the binary tree.
        // Note: You may assume that duplicates do not exist in the tree.
        // For example, given
        // inorder = [9,3,15,20,7]
        // postorder = [9,15,7,20,3]
        // Return the following binary tree:
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        TreeNode *buildTreeInOrderPostOrder(const vector<int> &inorder,
                                            const vector<int> &postorder)
        {
            map<int, int> m;
            for (int i = 0; i < (int)inorder.size(); i++)
                m[inorder[i]] = i;
            function<TreeNode *(int, int, int, int)> build = [&](int i1, int i2, int p1,
                                                                 int p2) -> TreeNode * {
                if (i2 - i1 != p2 - p1 || i1 > i2 || p1 > p2)
                    return nullptr;
                TreeNode *n = new TreeNode(postorder[p2]);
                int i = m[postorder[p2]];
                n->left = build(i1, i - 1, p1, p1 + i - 1 - i1);
                n->right = build(i + 1, i2, p1 + i - i1, p2 - 1);
                return n;
            };
            return build(0, (int)inorder.size() - 1, 0, (int)postorder.size() - 1);
        }
        TreeNode *buildTreeInOrderPostOrder2(const vector<int> &inorder,
                                             const vector<int> &postorder)
        {
            if (inorder.size() != postorder.size() || inorder.empty())
                return nullptr;
            stack<TreeNode *> path;
            int i = (int)postorder.size() - 1; // index current element in postOrder
            int j = (int)inorder.size() - 1;   // index current element in inOrder
            int f = 0;                         // flag to insert to left or right
            // Root
            TreeNode *node = new TreeNode(postorder[i]);
            path.push(node);
            // Current insertion point
            TreeNode *t = node;
            i--;
            // Post {{l_0}, {{l_1}, {{l_2}, {r_2}, n_2}, n_1}, n_0}
            // In   {{l_0}, n_0, {{l_1}, n_1, {{l_2}, n_2, {r_2}}}}
            while (i >= 0)
            {
                if (!path.empty() && path.top()->val == inorder[j])
                {
                    // Done with a right subtree, start to insert the left subtree
                    // Pop the current top so that we can return to its parent after
                    // done with its left subtree
                    t = path.top();
                    path.pop();
                    f = 1;
                    j--;
                }
                else
                {
                    if (f == 0)
                    {
                        t->right = new TreeNode(postorder[i]);
                        t = t->right;
                    }
                    else
                    {
                        f = 0;
                        t->left = new TreeNode(postorder[i]);
                        t = t->left;
                    }
                    path.push(t);
                    i--;
                }
            }
            return node;
        }
        TreeNode *buildTreeInOrderPostOrder3(const vector<int> &inorder,
                                             const vector<int> &postorder)
        {
            if (inorder.size() != postorder.size() || inorder.empty())
                return nullptr;
            int p = (int)postorder.size() - 1;
            int i = (int)inorder.size() - 1;
            function<TreeNode *(int)> build = [&](int val) -> TreeNode * {
                if (i == -1 || inorder[i] == val)
                    return nullptr;
                TreeNode *n = new TreeNode(postorder[p]);
                p--;
                n->right = build(n->val);
                i--;
                n->left = build(val);
                return n;
            };
            return build(INT_MIN);
        }

        // 107. Binary Tree Level Order Traversal II
        // Given a binary tree, return the bottom-up level order traversal of its
        // nodes' values. (ie, from left to right, level by level from leaf to root).
        // For example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its bottom-up level order traversal as:
        // [
        //   [15,7],
        //   [9,20],
        //   [3]
        // ]
        vector<vector<int>> levelOrderBottom(TreeNode *root)
        {
            vector<vector<int>> result;
            if (root == nullptr)
                return result;
            queue<TreeNode *> q[2];
            q[0].push(root);
            int l = 0;
            while (!q[0].empty() || !q[1].empty())
            {
                l = l % 2;
                int n = (l + 1) % 2;
                vector<int> v;
                while (!q[l].empty())
                {
                    v.push_back(q[l].front()->val);
                    if (q[l].front()->left != nullptr)
                        q[n].push(q[l].front()->left);
                    if (q[l].front()->right != nullptr)
                        q[n].push(q[l].front()->right);
                    q[l].pop();
                }
                result.insert(result.begin(), v);
                l++;
            }
            return result;
        }
        vector<vector<int>> levelOrderBottom2(TreeNode *root)
        {
            vector<vector<int>> result;
            stack<pair<TreeNode *, int>> s;
            int l = 0;
            TreeNode *n = root;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if ((int)result.size() <= l)
                    {
                        // Cannot use {} because it is seen as an empty
                        // initializer list, so insert() will not insert
                        // anything.
                        // result.insert(result.begin(), {});
                        result.insert(result.begin(), vector<int>());
                    }
                    result[(int)result.size() - l - 1].push_back(n->val);
                    s.push(make_pair(n, l));
                    n = n->left;
                    l++;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    l = p.second + 1;
                }
            }
            return result;
        }

        // 108. Convert Sorted Array to Binary Search Tree
        // Given an array where elements are sorted in ascending order, convert it
        // to a height balanced BST. For this problem, a height-balanced binary tree
        // is defined as a binary tree in which the depth of the two subtrees of every
        // node never differ by more than 1.
        // Example:
        // Given the sorted array: [-10,-3,0,5,9],
        // One possible answer is: [0,-3,9,-10,null,5], which represents the following
        // height balanced BST:
        //       0
        //      / \
        //    -3   9
        //    /   /
        //  -10  5
        TreeNode *sortedArrayToBST(const vector<int> &nums)
        {
            function<TreeNode *(int, int)> bst = [&](int i, int j) -> TreeNode * {
                if (i > j || i < 0 || j >= (int)nums.size())
                    return nullptr;
                int k = i + ((j - i) >> 1);
                TreeNode *n = new TreeNode(nums[k]);
                n->left = bst(i, k - 1);
                n->right = bst(k + 1, j);
                return n;
            };
            return bst(0, (int)nums.size() - 1);
        }
        TreeNode *sortedArrayToBST2(const vector<int> &nums)
        {
            if (nums.empty())
                return nullptr;
            function<int(int, int)> middle = [&](int i, int j) -> int {
                return i + ((j - i) >> 1);
            };
            int i = 0;
            int j = (int)nums.size() - 1;
            int k = middle(i, j);
            stack<pair<TreeNode *, pair<int, int>>> s;
            TreeNode *root = nullptr;
            int last = -1;
            int f = 0;
            while (!s.empty() || i <= j)
            {
                if (i <= j)
                {
                    TreeNode *n = new TreeNode(nums[k]);
                    if (root == nullptr)
                        root = n;
                    if (!s.empty())
                    {
                        if (f == 0)
                            s.top().first->left = n;
                        else
                        {
                            s.top().first->right = n;
                            f = 0;
                        }
                    }
                    // Record the right range and then move to the left
                    s.push(make_pair(n, make_pair(k, j)));
                    j = k - 1;
                    k = middle(i, j);
                }
                else
                {
                    pair<TreeNode *, pair<int, int>> p = s.top();
                    int ti = p.second.first + 1;
                    int tj = p.second.second;
                    int tk = middle(ti, tj);
                    if (ti <= tj && last != tk)
                    {
                        f = 1;
                        i = ti;
                        j = tj;
                        k = tk;
                    }
                    else
                    {
                        last = ti - 1; // == p.second.first
                        s.pop();
                    }
                }
            }
            return root;
        }

        // 109. Convert Sorted List to Binary Search Tree
        // Given a singly linked list where elements are sorted in ascending order,
        // convert it to a height balanced BST. For this problem, a height-balanced
        // binary tree is defined as a binary tree in which the depth of the two
        // subtrees of every node never differ by more than 1.
        // Example:
        // Given the sorted linked list: [-10,-3,0,5,9],
        // One possible answer is: [0,-3,9,-10,null,5], which represents the following
        // height balanced BST:
        //       0
        //      / \
        //    -3   9
        //    /   /
        //  -10  5
        TreeNode *sortedListToBST(ListNode *head)
        {
            function<TreeNode *(ListNode *, ListNode *)> bst =
                [&](ListNode *b, ListNode *e) -> TreeNode * {
                if (b == e)
                    return nullptr;
                ListNode *p = b; // 1st
                ListNode *q = b; // 1st
                while (q->next != e && q->next->next != e)
                {
                    p = p->next;       // (1 + k)-th
                    q = q->next->next; // (1 + 2k)-th
                }
                // p is the median for odd length
                // or the lower median for even length
                TreeNode *n = new TreeNode(p->val);
                n->left = bst(b, p);
                n->right = bst(p->next, e);
                return n;
            };
            return bst(head, nullptr);
        }
        TreeNode *sortedListToBST2(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            if (head->next == nullptr)
                return new TreeNode(head->val);
            function<TreeNode *(ListNode *, ListNode *)> build =
                [&](ListNode *b, ListNode *e) -> TreeNode * {
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
                    ListNode *p = b;             // 1st
                    ListNode *q = p->next->next; // 3rd
                    while (q != e && q->next != e)
                    {
                        p = p->next; // (1 + k)-th
                        q = q->next;
                        q = q->next; // (3 + 2k)-th
                    }
                    // now p->next is the median for odd length
                    // or the lower-median for even length
                    node = new TreeNode(p->next->val);
                    node->left = build(b, p);
                    node->right = build(p->next->next, e);
                }
                return node;
            };
            ListNode *p = head;    // 1st
            ListNode *q = p->next; // 2nd
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next; // (1 + k)-th
                q = q->next;
                q = q->next; // (2 + 2k)-th
            }
            // p->next is median for odd length
            // or p is the lower median for even length
            TreeNode *node = new TreeNode(p->next->val);
            node->left = build(head, p);
            node->right = build(p->next->next, q->next == nullptr ? q : q->next);
            return node;
        }
        TreeNode *sortedListToBST3(ListNode *head)
        {
            ListNode *p = head;
            int c = 0;
            while (p != nullptr)
            {
                c++;
                p = p->next;
            }
            function<TreeNode *(ListNode *&, int, int)> bst = [&](ListNode *&h, int b,
                                                                  int e) -> TreeNode * {
                if (b > e)
                    return nullptr;
                int m = b + ((e - b) >> 1);
                TreeNode *left = bst(h, b, m - 1);
                TreeNode *n = new TreeNode(h->val);
                n->left = left;
                h = h->next;
                n->right = bst(h, m + 1, e);
                return n;
            };
            ListNode *h = head;
            return bst(h, 0, c - 1);
        }

        // 110. Balanced Binary Tree
        // Given a binary tree, determine if it is height-balanced.
        // For this problem, a height-balanced binary tree is defined as:
        // a binary tree in which the left and right subtrees of every node differ
        // in height by no more than 1.
        // Example 1:
        // Given the following tree [3,9,20,null,null,15,7]:
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // Return true.
        // Example 2:
        // Given the following tree [1,2,2,3,3,null,null,4,4]:
        //        1
        //       / \
        //      2   2
        //     / \
        //    3   3
        //   / \
        //  4   4
        // Return false.
        bool isBalanced(TreeNode *root)
        {
            function<bool(TreeNode *, int &)> balanced = [&](TreeNode *n,
                                                             int &h) -> bool {
                if (n == nullptr)
                {
                    h = 0;
                    return true;
                }
                int hl = 0;
                if (!balanced(n->left, hl))
                    return false;
                int hr = 0;
                if (!balanced(n->right, hr))
                    return false;
                h = 1 + max(hl, hr);
                return abs(hl - hr) <= 1;
            };
            int h = 0;
            return balanced(root, h);
        }
        bool isBalanced2(TreeNode *root)
        {
            stack<TreeNode *> s;
            map<TreeNode *, int> m;
            TreeNode *node = root;
            TreeNode *last = nullptr;
            while (!s.empty() || node != nullptr)
            {
                if (node != nullptr)
                {
                    s.push(node);
                    m[node] = 0;
                    node = node->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    if (t->left != nullptr && t->left == last)
                        m[t] = m[t->left]; // Record the left height temporarily
                    if (t->right != nullptr && t->right != last)
                    {
                        node = t->right;
                    }
                    else
                    {
                        s.pop();
                        int rightHeight = t->right == nullptr ? 0 : m[t->right];
                        if (abs(m[t] - rightHeight) > 1)
                            return false;
                        m[t] = 1 + max(m[t], rightHeight); // Record the real height
                    }
                    last = t;
                }
            }
            return true;
        }

        // 111. Minimum Depth of Binary Tree
        // Given a binary tree, find its minimum depth.
        // The minimum depth is the number of nodes along the shortest path
        // from the root node down to the nearest leaf node.
        // Note: A leaf is a node with no children.
        // Example:
        // Given binary tree [3,9,20,null,null,15,7],
        //     3
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // return its minimum depth = 2.
        int minDepth(TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            int m = INT_MAX;
            function<void(TreeNode *, int)> depth = [&](TreeNode *n, int d) {
                if (n == nullptr)
                    return;
                d++;
                if (n->left == nullptr && n->right == nullptr)
                    m = min(m, d);
                if (n->left != nullptr)
                    depth(n->left, d);
                if (n->right != nullptr)
                    depth(n->right, d);
            };
            depth(root, 0);
            return m;
        }
        int minDepth2(TreeNode *root)
        {
            if (root == nullptr)
                return 0;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int m = INT_MAX;
            int d = 1;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (n->left == nullptr && n->right == nullptr)
                        m = min(m, d);
                    s.push(make_pair(n, d));
                    n = n->left;
                    d++;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    d = p.second + 1;
                }
            }
            return m;
        }
        int minDepth3(TreeNode *root)
        {
            function<int(TreeNode *, int)> solve = [&](TreeNode *node,
                                                       int depth) -> int {
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

        // 112. Path Sum
        // Given a binary tree and a sum, determine if the tree has a root-to-leaf
        // path such that adding up all the values along the path equals the given sum.
        // Note: A leaf is a node with no children. Example:
        // Given the below binary tree and sum = 22,
        //       5
        //      / \
        //     4   8
        //    /   / \
        //   11  13  4
        //  /  \      \
        // 7    2      1
        // return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
        bool hasPathSum(TreeNode *root, int sum)
        {
            function<bool(TreeNode *, int)> solve = [&](TreeNode *n, int s) -> bool {
                if (n == nullptr)
                    return false;
                s = s + n->val;
                if (s == sum && n->left == nullptr && n->right == nullptr)
                    return true;
                return solve(n->left, s) || solve(n->right, s);
            };
            return solve(root, 0);
        }
        bool hasPathSum2(TreeNode *root, int sum)
        {
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int t = 0;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    t = t + n->val;
                    if (n->left == nullptr && n->right == nullptr && t == sum)
                        return true;
                    s.push(make_pair(n, t));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    s.pop();
                    n = p.first->right;
                    t = p.second;
                }
            }
            return false;
        }
        int pickPathSum(TreeNode *root)
        {
            int sum = 0;
            function<void(TreeNode *, int)> solve = [&](TreeNode *n, int s) {
                if (n == nullptr)
                    return;
                s += n->val;
                if (n->left == nullptr && n->right == nullptr)
                {
                    sum = s;
                    if (rand() < (RAND_MAX >> 1))
                        return;
                }
                solve(n->left, s);
                solve(n->right, s);
            };
            solve(root, 0);
            return sum;
        }

        // 113. Path Sum II
        // Given a binary tree and a sum, find all root-to-leaf paths where each
        // path's sum equals the given sum. Note: A leaf is a node with no children.
        // Example: Given the below binary tree and sum = 22,
        //       5
        //      / \
        //     4   8
        //    /   / \
        //   11  13  4
        //  /  \    / \
        // 7    2  5   1
        // Return:
        // [
        //    [5,4,11,2],
        //    [5,8,4,5]
        // ]
        vector<vector<int>> pathSum(TreeNode *root, int sum)
        {
            vector<vector<int>> result;
            function<void(TreeNode *, int, vector<int> &)> solve =
                [&](TreeNode *n, int s, vector<int> &v) {
                    if (n == nullptr)
                        return;
                    s += n->val;
                    v.push_back(n->val);
                    if (s == sum && n->left == nullptr && n->right == nullptr)
                        result.push_back(v);
                    else
                    {
                        if (n->left != nullptr)
                            solve(n->left, s, v);
                        if (n->right != nullptr)
                            solve(n->right, s, v);
                    }
                    v.pop_back();
                };
            vector<int> w;
            solve(root, 0, w);
            return result;
        }
        vector<vector<int>> pathSum2(TreeNode *root, int sum)
        {
            vector<vector<int>> result;
            vector<int> v;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int t = 0;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    t += n->val;
                    v.push_back(n->val);
                    if (n->left == nullptr && n->right == nullptr && t == sum)
                        result.push_back(v);
                    s.push(make_pair(n, t));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    if (p.first->right != nullptr && last != p.first->right)
                    {
                        n = p.first->right;
                        t = p.second;
                    }
                    else
                    {
                        last = p.first;
                        s.pop();
                        v.pop_back();
                    }
                }
            }
            return result;
        }
        void setPathSum(TreeNode *root, int sum)
        {
            function<void(TreeNode *, int)> solve = [&](TreeNode *n, int s) {
                if (n == nullptr)
                    return;
                if (n->left == nullptr && n->right == nullptr)
                {
                    if (rand() < (RAND_MAX >> 1))
                    {
                        n->val = sum - s;
                        return;
                    }
                }
                s += n->val;
                solve(n->left, s);
                solve(n->right, s);
            };
            solve(root, 0);
        }

        // 114. Flatten Binary Tree to Linked List
        // Given a binary tree, flatten it to a linked list in-place.
        // For example, given the following tree:
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
        void flatten(TreeNode *root)
        {
            function<void(TreeNode *, TreeNode *&, TreeNode *&)> flat =
                [&](TreeNode *n, TreeNode *&l, TreeNode *&r) {
                    if (n == nullptr)
                    {
                        l = nullptr;
                        r = nullptr;
                        return;
                    }
                    TreeNode *ll = nullptr;
                    TreeNode *lr = nullptr;
                    flat(n->left, ll, lr);
                    TreeNode *rl = nullptr;
                    TreeNode *rr = nullptr;
                    flat(n->right, rl, rr);
                    if (ll == nullptr)
                    {
                        l = n;
                        r = rl == nullptr ? n : rr;
                        return;
                    }
                    lr->right = rl;
                    n->right = ll;
                    n->left = nullptr;
                    l = n;
                    r = rl == nullptr ? lr : rr;
                };
            TreeNode *l = nullptr;
            TreeNode *r = nullptr;
            flat(root, l, r);
        }
        void flatten2(TreeNode *root)
        {
            function<TreeNode *(TreeNode *)> solve =
                [&](TreeNode *node) -> TreeNode * {
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
        void flatten3(TreeNode *root)
        {
            stack<TreeNode *> s;
            map<TreeNode *, TreeNode *> m;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    m[n] = n;
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    if (t->right != nullptr && t->right != last)
                    {
                        n = t->right;
                    }
                    else
                    {
                        TreeNode *l = t->left;
                        TreeNode *r = t->right;
                        if (l != nullptr)
                        {
                            m[l]->right = r;
                            t->right = l;
                            t->left = nullptr;
                        }
                        m[t] = (r == nullptr ? (l == nullptr ? m[t] : m[l]) : m[r]);
                        s.pop();
                    }
                    last = t;
                }
            }
        }

        // 115. Distinct Subsequences
        // Given a string S and a string T, count the number of distinct subsequences
        // of S which equals T. A subsequence of a string is a new string which is
        // formed from the original string by deleting some (can be none) of the
        // characters without disturbing the relative positions of the remaining
        // characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
        // Example 1:
        // Input: S = "rabbbit", T = "rabbit"
        // Output: 3
        // Explanation: As shown below, there are 3 ways you can generate "rabbit" from
        // S. (The caret symbol ^ means the chosen letters)
        // rabbbit
        // ^^^^ ^^
        // rabbbit
        // ^^ ^^^^
        // rabbbit
        // ^^^ ^^^
        // Example 2:
        // Input: S = "babgbag", T = "bag"
        // Output: 5
        // Explanation: As shown below, there are 5 ways you can generate "bag" from S.
        // (The caret symbol ^ means the chosen letters)
        // babgbag
        // ^^ ^
        // babgbag
        // ^^    ^
        // babgbag
        // ^    ^^
        // babgbag
        //   ^  ^^
        // babgbag
        //     ^^^
        int numDistinct(const string &s, const string &t)
        {
            map<pair<size_t, size_t>, int> m;
            function<int(size_t, size_t)> solve = [&](size_t i, size_t j) -> int {
                pair<size_t, size_t> p = make_pair(i, j);
                if (m.find(p) != m.end())
                    return m[p];
                if (j == t.size())
                {
                    m[p] = 1;
                    return m[p];
                }
                while (i < s.size() && s[i] != t[j])
                    i++;
                if (i == s.size())
                    m[p] = 0;
                else
                    m[p] = solve(i + 1, j + 1) + solve(i + 1, j);
                return m[p];
            };
            return solve(0, 0);
        }
        // c(i, j) is the count for s[0..i] and t[0..j]
        // c(i, j) = 0                              if i < j
        //         = c(i - 1, j)                    if j == 0 && s[i] != t[j]
        //         = c(i - 1, j) + 1                if j == 0 && s[i] == t[j]
        //         = c(i - 1, j)                    if s[i] != t[j]
        //         = c(i - 1, j - 1) + c(i - 1, j)  if s[i] == t[j]
        //   t     0        1    ......     n-2        n-1
        // s 0 c(0,0)   c(0,1)   ...... c(0,n-2)   c(0,n-1)
        //   1 c(1,0)   c(1,1)   ...... c(1,n-2)   c(1,n-1)
        //   2 c(2,0)   c(2,1)   ...... c(2,n-2)   c(2,n-1)
        //     ......
        // n-2 c(n-2,0) c(n-2,1) ...... c(n-2,n-2) c(n-2,n-1)
        // n-1 c(n-1,0) c(n-1,1) ...... c(n-1,n-2) c(n-1,n-1)
        //     ......
        // m-n c(m-n,0) c(m-n,1) ...... c(m-n,n-2) c(m-n,n-1)
        //     ......
        // m-2 c(m-2,0) c(m-2,1) ...... c(m-2,n-2) c(m-2,n-1)
        // m-1 c(m-1,0) c(m-1,1) ...... c(m-1,n-2) c(m-1,n-1)
        int numDistinct2(const string &s, const string &t)
        {
            if (s.size() < t.size())
                return 0;
            vector<unsigned long long> c(t.size(), 0);
            c[0] = s[0] == t[0] ? 1 : 0;
            for (int i = 1; i < (int)s.size(); i++)
            {
                for (int j = t.size() - 1; j > 0; j--)
                {
                    if (s[i] == t[j])
                        c[j] += c[j - 1];
                }
                if (s[i] == t[0])
                    c[0]++;
            }
            return c[t.size() - 1];
        }

        struct NodeWithNextLink
        {
            int val;
            NodeWithNextLink *left;
            NodeWithNextLink *right;
            NodeWithNextLink *next;
        };

        // 116. Populating Next Right Pointers in Each Node
        // You are given a perfect binary tree where all leaves are on the same level,
        // and every parent has two children. The binary tree has the following
        // definition: struct Node {
        //   int val;
        //   Node *left;
        //   Node *right;
        //   Node *next;
        // }
        // Populate each next pointer to point to its next right node. If there is no
        // next right node, the next pointer should be set to NULL. Initially, all next
        // pointers are set to NULL. Follow up: You may only use constant extra space.
        // Recursive approach is fine, you may assume implicit stack space does not
        // count as extra space for this problem. Example 1: Input: root =
        // [1,2,3,4,5,6,7] Output: [1,#,2,3,#,4,5,6,7,#] Explanation: Given the above
        // perfect binary tree (Figure A), your function should populate each next
        // pointer to point to its next right node, just like in Figure B. The
        // serialized output is in level order as connected by the next pointers, with
        // '#' signifying the end of each level. Constraints: The number of nodes in the
        // given tree is less than 4096. -1000 <= node.val <= 1000
        NodeWithNextLink *connect(NodeWithNextLink *root)
        {
            NodeWithNextLink *left = root;
            while (left != nullptr && left->left != nullptr)
            {
                NodeWithNextLink *n = left;
                while (n != nullptr)
                {
                    n->left->next = n->right;
                    if (n->next != nullptr)
                        n->right->next = n->next->left;
                    n = n->next;
                }
                left = left->left;
            }
            return root;
        }
        NodeWithNextLink *connect2(NodeWithNextLink *root)
        {
            NodeWithNextLink *leftMost = root;
            while (leftMost != nullptr && leftMost->left != nullptr)
            {
                NodeWithNextLink *node = leftMost;
                leftMost = leftMost->left;
                NodeWithNextLink *left = nullptr;
                while (node != nullptr)
                {
                    if (left != nullptr)
                        left->next = node->left;
                    node->left->next = node->right;
                    left = node->right;
                    node = node->next;
                }
            }
            return root;
        }
        NodeWithNextLink *connect3(NodeWithNextLink *root)
        {
            if (root != nullptr && root->left != nullptr && root->right != nullptr)
            {
                root->left->next = root->right;
                if (root->next != nullptr)
                    root->right->next = root->next->left;
                connect3(root->left);
                connect3(root->right);
            }
            return root;
        }

        // 117. Populating Next Right Pointers in Each Node II
        // Given a binary tree
        // struct Node {
        //   int val;
        //   Node *left;
        //   Node *right;
        //   Node *next;
        // }
        // Populate each next pointer to point to its next right node. If there is no
        // next right node, the next pointer should be set to NULL. Initially, all next
        // pointers are set to NULL. Follow up: You may only use constant extra space.
        // Recursive approach is fine, you may assume implicit stack space does not
        // count as extra space for this problem. Example 1: Input: root =
        // [1,2,3,4,5,null,7] Output: [1,#,2,3,#,4,5,7,#] Explanation: Given the above
        // binary tree (Figure A), your function should populate each next pointer to
        // point to its next right node, just like in Figure B. The serialized output is
        // in level order as connected by the next pointers, with '#' signifying the end
        // of each level. Constraints: The number of nodes in the given tree is less
        // than 6000. -100 <= node.val <= 100
        NodeWithNextLink *connectII(NodeWithNextLink *root)
        {
            NodeWithNextLink *node = root;
            while (node != nullptr)
            {
                NodeWithNextLink *left = nullptr;
                NodeWithNextLink *prev = nullptr;
                while (node != nullptr)
                {
                    if (node->left != nullptr)
                    {
                        if (left == nullptr)
                            left = node->left;
                        if (prev != nullptr)
                            prev->next = node->left;
                        prev = node->left;
                    }
                    if (node->right != nullptr)
                    {
                        if (left == nullptr)
                            left = node->right;
                        if (prev != nullptr)
                            prev->next = node->right;
                        prev = node->right;
                    }
                    node = node->next;
                }
                node = left;
            }
            return root;
        }
        NodeWithNextLink *connectII2(NodeWithNextLink *root)
        {
            if (root != nullptr && (root->left != nullptr || root->right != nullptr))
            {
                NodeWithNextLink *prev = nullptr;
                if (root->left != nullptr)
                    prev = root->left;
                if (root->right != nullptr)
                {
                    if (prev != nullptr)
                        prev->next = root->right;
                    prev = root->right;
                }
                NodeWithNextLink *n = root->next;
                while (n != nullptr)
                {
                    if (n->left != nullptr)
                    {
                        prev->next = n->left;
                        prev = n->left;
                    }
                    if (n->right != nullptr)
                    {
                        prev->next = n->right;
                        prev = n->right;
                    }
                    n = n->next;
                }
                connectII2(root->left);
                connectII2(root->right);
            }
            return root;
        }
        NodeWithNextLink *connectII3(NodeWithNextLink *root)
        {
            if (root != nullptr)
            {
                NodeWithNextLink *prev = nullptr;
                NodeWithNextLink *n = root;
                while (n != nullptr)
                {
                    if (n->left != nullptr)
                    {
                        if (prev != nullptr)
                            prev->next = n->left;
                        prev = n->left;
                    }
                    if (n->right != nullptr)
                    {
                        if (prev != nullptr)
                            prev->next = n->right;
                        prev = n->right;
                    }
                    n = n->next;
                }
                connectII3(root->left);
                connectII3(root->right);
            }
            return root;
        }

        // 118. Pascal's Triangle
        // Given a non-negative integer numRows, generate the first numRows of Pascal's
        // triangle. In Pascal's triangle, each number is the sum of the two numbers
        // directly above it. Example: Input: 5 Output:
        // [
        //      [1],
        //     [1,1],
        //    [1,2,1],
        //   [1,3,3,1],
        //  [1,4,6,4,1]
        // ]
        vector<vector<int>> generate(int numRows)
        {
            vector<vector<int>> result;
            vector<int> v;
            for (int i = 1; i <= numRows; i++)
            {
                v.push_back(1);
                for (int j = v.size() - 2; j > 0; j--)
                    v[j] += v[j - 1];
                result.push_back(v);
            }
            return result;
        }

        // 119. Pascal's Triangle II
        // Given a non-negative index k where k ≤ 33, return the kth index row of
        // the Pascal's triangle. Note that the row index starts from 0.
        // In Pascal's triangle, each number is the sum of the two numbers directly
        // above it. Example: Input: 3 Output: [1,3,3,1] Follow up: Could you optimize
        // your algorithm to use only O(k) extra space?
        vector<int> getRow(int rowIndex)
        {
            vector<int> v = {1};
            for (int i = 1; i <= rowIndex; i++)
            {
                v.push_back(1);
                for (int j = v.size() - 2; j > 0; j--)
                    v[j] += v[j - 1];
            }
            return v;
        }
        vector<int> getRow2(int rowIndex)
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
        vector<int> getRow3(int rowIndex)
        {
            if (rowIndex <= 0)
                return vector<int>{1};
            vector<int> row = getRow3(rowIndex - 1);
            for (int i = (int)row.size() - 1; i > 0; i--)
                row[i] += row[i - 1];
            row.push_back(1);
            return row;
        }

        // 120. Triangle
        // Given a triangle, find the minimum path sum from top to bottom. Each step you
        // may move to adjacent numbers on the row below.
        // For example, given the following triangle
        // [
        //      [2],
        //     [3,4],
        //    [6,5,7],
        //   [4,1,8,3]
        // ]
        // The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
        // Note: Bonus point if you are able to do this using only O(n) extra space,
        // where n is the total number of rows in the triangle.
        int minimumTotal(const vector<vector<int>> &triangle)
        {
            vector<int> v(triangle.size(), 0);
            for (size_t i = 0; i < triangle.size(); i++)
            {
                v[i] = triangle[i][i];
                if (i > 0)
                    v[i] += v[i - 1];
                for (int j = i - 1; j > 0; j--)
                    v[j] = triangle[i][j] + min(v[j - 1], v[j]);
                if (i > 0)
                    v[0] += triangle[i][0];
            }
            int m = INT_MAX;
            for (size_t i = 0; i < v.size(); i++)
                m = min(m, v[i]);
            return m;
        }
        int minimumTotal2(const vector<vector<int>> &triangle)
        {
            vector<int> row(triangle[0]);
            for (size_t i = 1; i < triangle.size(); i++)
            {
                size_t n = triangle[i].size();
                row.push_back(row[n - 2] + triangle[i][n - 1]);
                for (int j = n - 2; j > 0; j--)
                    row[j] = triangle[i][j] + min(row[j - 1], row[j]);
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

        // 121. Best Time to Buy and Sell Stock
        // Say you have an array for which the ith element is the price of a given stock
        // on day i. If you were only permitted to complete at most one transaction
        // (i.e., buy one and sell one share of the stock), design an algorithm to find
        // the maximum profit. Note that you cannot sell a stock before you buy one.
        // Example 1:
        // Input: [7,1,5,3,6,4]
        // Output: 5
        // Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6),
        // profit = 6-1 = 5. Not 7-1 = 6, as selling price needs to be larger than
        // buying price. Example 2: Input: [7,6,4,3,1] Output: 0 Explanation: In this
        // case, no transaction is done, i.e. max profit = 0.
        int maxProfit(const vector<int> &prices)
        {
            size_t low = 0;
            int profit = 0;
            for (size_t i = 1; i < prices.size(); i++)
            {
                if (prices[i] < prices[low])
                    low = i;
                else
                    profit = max(profit, prices[i] - prices[low]);
            }
            return profit;
        }

        // 122. Best Time to Buy and Sell Stock II
        // Say you have an array for which the ith element is the price of a given
        // stock on day i. Design an algorithm to find the maximum profit. You may
        // complete as many transactions as you like (i.e., buy one and sell one share
        // of the stock multiple times). Note: You may not engage in multiple
        // transactions at the same time (i.e., you must sell the stock before you buy
        // again).
        // Example 1:
        // Input: [7,1,5,3,6,4]
        // Output: 7
        // Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5),
        // profit = 5-1 = 4. Then buy on day 4 (price = 3) and sell on day 5
        // (price = 6), profit = 6-3 = 3.
        // Example 2:
        // Input: [1,2,3,4,5]
        // Output: 4
        // Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5),
        // profit = 5-1 = 4.
        // Note that you cannot buy on day 1, buy on day 2 and sell them later, as you
        // are engaging multiple transactions at the same time. You must sell before
        // buying again. Example 3: Input: [7,6,4,3,1] Output: 0 Explanation: In this
        // case, no transaction is done, i.e. max profit = 0.
        int maxProfitII(const vector<int> &prices)
        {
            int p = 0;
            for (size_t i = 1; i < prices.size(); i++)
                p += (prices[i] > prices[i - 1] ? prices[i] - prices[i - 1] : 0);
            return p;
        }

        // 123. Best Time to Buy and Sell Stock III
        // Say you have an array for which the ith element is the price of a given stock
        // on day i. Design an algorithm to find the maximum profit. You may complete at
        // most two transactions. Note: You may not engage in multiple transactions at
        // the same time (i.e., you must sell the stock before you buy again). Example
        // 1: Input: [3,3,5,0,0,3,1,4] Output: 6 Explanation: Buy on day 4 (price = 0)
        // and sell on day 6 (price = 3), profit = 3-0 = 3. Then buy on day 7 (price =
        // 1) and sell on day 8 (price = 4), profit = 4-1 = 3. Example 2: Input:
        // [1,2,3,4,5] Output: 4 Explanation: Buy on day 1 (price = 1) and sell on day 5
        // (price = 5), profit = 5-1 = 4. Note that you cannot buy on day 1, buy on day
        // 2 and sell them later, as you are engaging multiple transactions at the same
        // time. You must sell before buying again. Example 3: Input: [7,6,4,3,1]
        // Output: 0
        // Explanation: In this case, no transaction is done, i.e. max profit = 0.
        // Dynamic Programming
        // Let p[k, j] be the profit when k transactions are done at index j
        // Let p[j] = prices[j]
        // p[k, j] = max(p[k, j - 1],
        //               p[k - 1, j - 2] + p[j] - p[j - 1],
        //               p[k - 1, j - 3] + p[j] - p[j - 2],
        //               ......
        //               p[k - 1, 2(k - 1) - 1] + p[j] - p[2(k - 1)])
        // For k = 2
        // p[2, j] = max(p[2, j - 1],
        //               p[j] - p[j - 1] + p[1, j - 2],
        //               p[j] - p[j - 2] + p[1, j - 3],
        //               ......
        //               p[j] - p[2] + p[1, 1])
        // p[2, j - 1] = max(p[2, j - 2],
        //                   p[j - 1] - p[j - 2] + p[1, j - 3],
        //                   p[j - 1] - p[j - 3] + p[1, j - 4],
        //                   ......
        //                   p[j - 1] - p[2] + p[1, 1])
        // p[1, j] = max(p[1, j - 1],
        //               p[j] - p[j - 1] + p[0, j - 2],
        //               p[j] - p[j - 2] + p[0, j - 3],
        //               ......
        //               p[j] - p[1] + p[0, 0])
        //               p[j] - p[0] + p[0, -1])
        // p[1, j - 1] = max(p[1, j - 2],
        //                   p[j - 1] - p[j - 2] + p[0, j - 3],
        //                   p[j - 1] - p[j - 3] + p[0, j - 4],
        //                   ......
        //                   p[j - 1] - p[1] + p[0, 0])
        //                   p[j - 1] - p[0] + p[0, -1])
        //   j 0
        //       p[0]   p[1]   p[2]         p[3]         p[4]      ......    p[j-2]          p[j-1]          p[j]
        // max{ -p[0]  -p[1]  -p[2]        -p[3]        -p[4]      ......   -p[j-2]         -p[j-1]         -p[j] }
        // k 1        p[1,1] p[1,2]       p[1,3]       p[1,4]      ...... p[1,(j-2)]      p[1,(j-1)]       p[1,j]
        //              max{ p[1,1]-p[2]  p[1,2]-p[3]  p[1,3]-p[4] ...... p[1,(j-3)]-p[j-2] p[1,(j-2)]-p[j-1] }
        //   2                            p[2,3]       p[2,4]      ...... p[2,(j-2)]      p[2,(j-1)]        p[2,j]
        int maxProfitIII(const vector<int> &prices)
        {
            if (prices.size() < 2)
                return 0;
            int m1 = INT_MIN;
            int m2 = INT_MIN;
            int p1 = INT_MIN;
            int p2 = INT_MIN;
            for (size_t j = 0; j < prices.size(); j++)
            {
                if (j == 0)
                {
                    m1 = -prices[0];
                }
                else if (j == 1)
                {
                    p1 = prices[1] - prices[0];
                    m1 = max(m1, -prices[1]);
                }
                else if (j == 2)
                {
                    m2 = p1 - prices[2];
                    p1 = max(p1, prices[2] + m1);
                    m1 = max(m1, -prices[2]);
                }
                else if (j == 3)
                {
                    p2 = prices[3] + m2;
                    m2 = max(m2, p1 - prices[3]);
                    p1 = max(p1, prices[3] + m1);
                    m1 = max(m1, -prices[3]);
                }
                else
                {
                    p2 = max(p2, prices[j] + m2);
                    m2 = max(m2, p1 - prices[j]);
                    p1 = max(p1, prices[j] + m1);
                    m1 = max(m1, -prices[j]);
                }
            }
            int m = max(p1, p2);
            return m < 0 ? 0 : m;
        }
        int maxProfitIII2(const vector<int> &prices)
        {
            if (prices.empty())
                return 0;
            vector<vector<int>> p(3, vector<int>(prices.size(), 0));
            for (size_t j = 1; j < prices.size(); j++)
            {
                if (j == 1)
                {
                    p[1][1] = prices[1] - prices[0];
                }
                else if (j == 2)
                {
                    p[1][2] =
                        max(p[1][1], max(prices[2] - prices[1], prices[2] - prices[0]));
                }
                else
                {
                    int m = -prices[0];
                    for (size_t i = 1; i < j; i++)
                        m = max(m, p[0][i - 1] - prices[i]);
                    p[1][j] = max(p[1][j - 1], prices[j] + m);
                    m = INT_MIN;
                    for (size_t i = 2; i < j; i++)
                        m = max(m, p[1][i - 1] - prices[i]);
                    p[2][j] = max(p[2][j - 1], prices[j] + m);
                }
            }
            return max(p[1][prices.size() - 1], p[2][prices.size() - 1]);
        }
        int maxProfitIII3(const vector<int> &prices)
        {
            if (prices.size() < 2)
                return 0;
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
            int length = prices.size();
            while (j < length)
            {
                while (j + 1 < length && prices[j] >= prices[j + 1])
                {
                    // Find the next local minimum
                    j++;
                }
                if (i < sell2 || prices[i] >= prices[j])
                {
                    // i is the minimal in the range [sell2, j]
                    // [sell2, j] may contain multiple increasing ranges, because
                    // [i, j] may not overlap with previous [buy2, sell2]
                    i = j;
                }
                while (j + 1 < length && prices[j] < prices[j + 1])
                {
                    // Find the next local maximum
                    j++;
                }
                if (i == j)
                {
                    j++; // Why this can happen?
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
                    if (prices[j] > prices[s2])
                    {
                        // Covered case 2
                        s2 = j;
                    }
                    if (prices[j] - prices[i] + prices[sellm] - prices[buym] >
                        prices[s2] - prices[b2] + prices[s1] - prices[b1])
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
                if (prices[sell1] - prices[buy1] > prices[sellm] - prices[buym])
                {
                    buym = buy1;
                    sellm = sell1;
                }
                if (prices[sell2] - prices[buy2] > prices[sellm] - prices[buym])
                {
                    buym = buy2;
                    sellm = sell2;
                }
                if (prices[sell2] - prices[buy1] > prices[sellm] - prices[buym])
                {
                    buym = buy1;
                    sellm = sell2;
                }
                j++;
            }
            if (prices[sellm] - prices[buym] >=
                prices[sell2] - prices[buy2] + prices[sell1] - prices[buy1])
            {
                return prices[sellm] - prices[buym];
            }
            else
            {
                return prices[sell1] - prices[buy1] + prices[sell2] - prices[buy2];
            }
        }
        int maxProfitIII4(const vector<int> &prices)
        {
            if (prices.size() < 2)
                return 0;
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
                    if (prices[i] < prices[min])
                    {
                        min = i;
                    }
                    else
                    {
                        if (prices[i] - prices[min] > profit)
                        {
                            buy = min;
                            sell = i;
                            profit = prices[i] - prices[min];
                        }
                    }
                }
            };
            int profit1 = 0;
            int profit2 = 0;
            int b1 = 0;
            int s1 = 0;
            int p1 = 0;
            int b2 = 0;
            int s2 = 0;
            int p2 = 0;
            int i = 0;
            int length = prices.size();
            while (i < length - 1)
            {
                // Increase i so that [0..i] contains one more increasing subarray
                while (i < length - 1 && prices[i + 1] <= prices[i])
                    i++;
                if (i == length - 1)
                    break;
                while (i < length - 1 && prices[i + 1] > prices[i])
                    i++;
                // Find the max transaction before i
                maxProfit(b1, i, b1, s1, p1);
                // Find the max transaction after i
                if (i > b2)
                {
                    // If i <= b2, then no need to reevaluate because b2/s2 is already
                    // maximum after i
                    maxProfit(i, length - 1, b2, s2, p2);
                }
                if (p1 + p2 > profit1 + profit2)
                {
                    profit1 = p1;
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
                return p3;
            }
            else
            {
                return profit1 + profit2;
            }
        }

        // 124. Binary Tree Maximum Path Sum
        // Given a non-empty binary tree, find the maximum path sum. For this problem,
        // a path is defined as any sequence of nodes from some starting node to any
        // node in the tree along the parent-child connections. The path must contain
        // at least one node and does not need to go through the root.
        // Example 1:
        // Input: [1,2,3]
        //        1
        //       / \
        //      2   3
        // Output: 6
        // Example 2:
        // Input: [-10,9,20,null,null,15,7]
        //    -10
        //    / \
        //   9  20
        //     /  \
        //    15   7
        // Output: 42
        int maxPathSum(TreeNode *root)
        {
            function<void(TreeNode *, int &, int &)> solve =
                [&](TreeNode *n, int &pathSum, int &maxSum) {
                    if (n == nullptr)
                        return;
                    if (n->left == nullptr && n->right == nullptr)
                    {
                        pathSum = n->val;
                        maxSum = n->val;
                        return;
                    }
                    int leftPathSum = INT_MIN;
                    int leftMaxSum = INT_MIN;
                    if (n->left != nullptr)
                        solve(n->left, leftPathSum, leftMaxSum);
                    if (leftPathSum < 0)
                        leftPathSum = 0; // Ignore left path
                    int rightPathSum = INT_MIN;
                    int rightMaxSum = INT_MIN;
                    if (n->right != nullptr)
                        solve(n->right, rightPathSum, rightMaxSum);
                    if (rightPathSum < 0)
                        rightPathSum = 0; // Ignore right path
                    if (n->left == nullptr)
                    {
                        pathSum = n->val + rightPathSum;
                        maxSum = max(pathSum, rightMaxSum);
                    }
                    else if (n->right == nullptr)
                    {
                        pathSum = n->val + leftPathSum;
                        maxSum = max(pathSum, leftMaxSum);
                    }
                    else
                    {
                        pathSum = n->val + max(leftPathSum, rightPathSum);
                        maxSum = max(leftPathSum + n->val + rightPathSum,
                                     max(leftMaxSum, rightMaxSum));
                    }
                };
            int p;
            int m;
            solve(root, p, m);
            return m;
        }

        // 125. Valid Palindrome
        // Given a string, determine if it is a palindrome, considering only
        // alphanumeric characters and ignoring cases. Note: For the purpose of this
        // problem, we define empty string as valid palindrome. Example 1: Input: "A
        // man, a plan, a canal: Panama" Output: true Example 2: Input: "race a car"
        // Output: false
        bool isPalindrome(const string &s)
        {
            function<bool(char)> isAlphaNumeric = [&](char c) -> bool {
                return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
                       ('0' <= c && c <= '9');
            };
            int i = 0;
            int j = (int)s.size() - 1;
            while (i < j)
            {
                if (!isAlphaNumeric(s[i]))
                {
                    i++;
                }
                else if (!isAlphaNumeric(s[j]))
                {
                    j--;
                }
                else
                {
                    if ('a' <= s[i] && s[i] <= 'z')
                    {
                        if ((s[i] - 'a' != s[j] - 'a') && (s[i] - 'a' != s[j] - 'A'))
                            return false;
                    }
                    else if ('A' <= s[i] && s[i] <= 'Z')
                    {
                        if ((s[i] - 'A' != s[j] - 'a') && (s[i] - 'A' != s[j] - 'A'))
                            return false;
                    }
                    else if ('0' <= s[i] && s[i] <= '9')
                    {
                        if (s[i] - '0' != s[j] - '0')
                            return false;
                    }
                    i++;
                    j--;
                }
            }
            return true;
        }
        bool isPalindrome2(const string &s)
        {
            function<bool(char)> isDigit = [&](char c) -> bool {
                return '0' <= c && c <= '9';
            };
            function<bool(char)> isLower = [&](char c) -> bool {
                return 'a' <= c && c <= 'z';
            };
            function<bool(char)> isUpper = [&](char c) -> bool {
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
        bool isPalindrome3(const string &s)
        {
            if (s.empty())
                return true;
            auto isAlphaNumeric = [&](char c) -> bool {
                return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                       (c >= '0' && c <= '9');
            };
            auto equal = [&](char a, char b) -> bool {
                if (a >= 'a' && a <= 'z' &&
                    ((b - 'a' == a - 'a') || (b - 'A' == a - 'a')))
                    return true;
                else if (a >= 'A' && a <= 'Z' &&
                         ((b - 'a' == a - 'A') || (b - 'A' == a - 'A')))
                    return true;
                else if (a >= '0' && a <= '9' && b == a)
                    return true;
                return false;
            };
            int i = 0;
            int j = s.size() - 1;
            while (i <= j)
            {
                while (i <= j && !isAlphaNumeric(s[i]))
                    i++;
                while (i <= j && !isAlphaNumeric(s[j]))
                    j--;
                if (i > j)
                    return true;
                if (!equal(s[i], s[j]))
                    return false;
                i++;
                j--;
            }
            return true;
        }

        // 126. Word Ladder II
        // Given two words (beginWord and endWord), and a dictionary's word list, find
        // all shortest transformation sequence(s) from beginWord to endWord, such that:
        // Only one letter can be changed at a time and each transformed word must exist
        // in the word list. Note that beginWord is not a transformed word. Note: Return
        // an empty list if there is no such transformation sequence. All words have the
        // same length. All words contain only lowercase alphabetic characters. You may
        // assume no duplicates in the word list. You may assume beginWord and endWord
        // are non-empty and are not the same.
        // Example 1:
        // Input:
        // beginWord = "hit",
        // endWord = "cog",
        // wordList = ["hot","dot","dog","lot","log","cog"]
        // Output:
        // [
        //   ["hit","hot","dot","dog","cog"],
        //   ["hit","hot","lot","log","cog"]
        // ]
        // Example 2:
        // Input:
        // beginWord = "hit"
        // endWord = "cog"
        // wordList = ["hot","dot","dog","lot","log"]
        // Output: []
        // Explanation: The endWord "cog" is not in wordList, therefore no possible
        // transformation.
        vector<vector<string>> findLadders(const string &beginWord,
                                           const string &endWord,
                                           const vector<string> &wordList)
        {
            vector<vector<string>> results;
            map<string, bool> visited;
            for_each(wordList.cbegin(), wordList.cend(),
                     [&](const string &s) { visited[s] = false; });
            if (visited.find(endWord) == visited.end())
                return results;
            size_t minLen = wordList.size() + 1;
            function<void(string &, vector<string> &)> solve = [&](string &w,
                                                                   vector<string> &v) {
                if (v.size() >= minLen)
                    return;
                for (size_t i = 0; i < w.size(); i++)
                {
                    string s = w;
                    char c = s[i];
                    for (char k = 'a'; k <= 'z'; k++)
                    {
                        s[i] = k;
                        if (k == c || visited.find(s) == visited.end() || visited[s])
                            continue;
                        visited[s] = true;
                        v.push_back(s);
                        if (s.compare(endWord) == 0)
                        {
                            if (v.size() <= minLen)
                            {
                                results.push_back(v);
                                minLen = v.size();
                            }
                        }
                        else if (v.size() < minLen)
                        {
                            solve(s, v);
                        }
                        v.pop_back();
                        visited[s] = false;
                    }
                }
            };
            vector<string> p(1, beginWord);
            string word = beginWord;
            solve(word, p);
            auto it = results.begin();
            while (it != results.end())
            {
                if (it->size() > minLen)
                    it = results.erase(it);
                else
                    it++;
            }
            return results;
        }
        vector<vector<string>> findLadders2(const string &beginWord,
                                            const string &endWord,
                                            const vector<string> &wordList)
        {
            vector<vector<string>> ladders = {};
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return ladders;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return ladders;
            unordered_map<string, vector<vector<string>>>
                path; // Record paths ending at a word
            unordered_map<string, int> level;
            queue<string> q[2];
            int step = 0;
            bool stop = false;
            q[0].push(beginWord);
            level[beginWord] = step;
            path[beginWord] = vector<vector<string>>{};
            path[beginWord].push_back(vector<string>{beginWord});
            while (!q[0].empty() || !q[1].empty())
            {
                queue<string> &current = q[step & 0x1];
                queue<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.pop();
                    string temp;
                    for (size_t i = 0; i < word.size(); i++)
                    {
                        temp = word;
                        for (char j = 'a'; j <= 'z'; j++)
                        {
                            temp[i] = j;
                            if (temp.compare(endWord) == 0)
                            {
                                for_each(path[word].begin(), path[word].end(),
                                         [&](vector<string> &p) {
                                             vector<string> r(p);
                                             r.push_back(temp);
                                             ladders.push_back(r);
                                         });
                                stop = true;
                            }
                            else if (find(wordList.cbegin(), wordList.cend(), temp) !=
                                     wordList.cend())
                            {
                                if (level.find(temp) == level.end())
                                {
                                    level[temp] = step + 1;
                                    next.push(temp);
                                    path[temp] = vector<vector<string>>{};
                                }
                                if (level[temp] > step)
                                {
                                    for_each(path[word].begin(), path[word].end(),
                                             [&](vector<string> &p) {
                                                 vector<string> r(p);
                                                 r.push_back(temp);
                                                 path[temp].push_back(r);
                                             });
                                }
                            }
                        }
                    }
                }
                if (stop)
                    break; // Found the shortest paths. If need to find all, then do not
                           // stop.
                step++;
            }
            return ladders;
        }
        vector<vector<string>> findLadders3(const string &beginWord, const string &endWord, const vector<string> &wordList)
        {
            set<string> wordSet(wordList.begin(), wordList.end());
            vector<vector<string>> ladders;
            function<void(string &, vector<string> &)> solve =
                [&](string &word, vector<string> &ladder) {
                    for (size_t i = 0; i < word.size(); i++)
                    {
                        char c = word[i];
                        for (char j = 1; j < 26; j++)
                        {
                            word[i] = 'a' + ((c - 'a' + j) % 26);
                            if (wordSet.find(word) == wordSet.end())
                                continue;
                            if (word.compare(endWord) == 0)
                            {
                                vector<string> v(ladder.begin(), ladder.end());
                                v.push_back(word);
                                if (ladders.empty())
                                    ladders.push_back(v);
                                else if (v.size() < ladders.begin()->size())
                                {
                                    ladders.clear();
                                    ladders.push_back(v);
                                }
                                else if (v.size() == ladders.begin()->size())
                                {
                                    ladders.push_back(v);
                                }
                                break;
                            }
                            else if (std::find(ladder.begin(), ladder.end(), word) == ladder.end())
                            {
                                ladder.push_back(word);
                                solve(word, ladder);
                                ladder.pop_back();
                            }
                        }
                        word[i] = c;
                    }
                };
            vector<string> l;
            l.push_back(beginWord);
            string begin(beginWord);
            solve(begin, l);
            return ladders;
        }

        // 127. Word Ladder
        // Given two words (beginWord and endWord), and a dictionary's word list,
        // find the length of shortest transformation sequence from beginWord to
        // endWord, such that: Only one letter can be changed at a time. Each
        // transformed word must exist in the word list. Note that beginWord is
        // not a transformed word. Note: Return 0 if there is no such transformation
        // sequence. All words have the same length. All words contain only lowercase
        // alphabetic characters. You may assume no duplicates in the word list. You
        // may assume beginWord and endWord are non-empty and are not the same.
        // Example 1:
        // Input:
        // beginWord = "hit",
        // endWord = "cog",
        // wordList = ["hot","dot","dog","lot","log","cog"]
        // Output: 5
        // Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" ->
        // "dog" -> "cog", return its length 5. Example 2: Input: beginWord = "hit"
        // endWord = "cog"
        // wordList = ["hot","dot","dog","lot","log"]
        // Output: 0
        // Explanation: The endWord "cog" is not in wordList, therefore no possible
        // transformation.
        int ladderLength(const string &beginWord, const string &endWord,
                         const vector<string> &wordList)
        {
            map<string, bool> visited;
            for_each(wordList.cbegin(), wordList.cend(),
                     [&](const string &s) { visited[s] = false; });
            queue<vector<string>> paths;
            paths.push(vector<string>(1, beginWord));
            while (!paths.empty())
            {
                vector<string> path = paths.front();
                paths.pop();
                for (size_t i = 0; i < path.back().size(); i++)
                {
                    string s = path.back();
                    char c = s[i];
                    for (char k = 'a'; k <= 'z'; k++)
                    {
                        s[i] = k;
                        if (k == c || visited.find(s) == visited.end() || visited[s])
                            continue;
                        if (s.compare(endWord) == 0)
                            return path.size() + 1;
                        visited[s] = true;
                        vector<string> path1(path.cbegin(), path.cend());
                        path1.push_back(s);
                        paths.push(path1);
                    }
                }
            }
            return 0;
        }
        int ladderLength2(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            function<int(bool, const string &, const vector<string> &)> search =
                [&](bool transformed, const string &word,
                    const vector<string> &list) -> int {
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
                                min = m;
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
        int ladderLength3(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return 0;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return 0;
            unordered_set<string> dict;
            dict.insert(wordList.begin(), wordList.end());
            if (dict.find(beginWord) == dict.end())
                dict.insert(beginWord);
            if (dict.find(endWord) == dict.end())
                dict.insert(endWord);
            map<string, vector<string>> graph;
            for_each(dict.begin(), dict.end(),
                     [&](string word) { graph[word] = vector<string>{}; });
            for_each(dict.begin(), dict.end(), [&](string word) {
                int wordLen = word.length();
                for (map<string, vector<string>>::iterator it = graph.begin();
                     it != graph.end(); it++)
                {
                    if (wordLen == (int)it->first.length())
                    {
                        int diff = 0;
                        for (int i = 0; i < wordLen; i++)
                        {
                            if (word[i] != it->first[i])
                                diff++;
                            if (diff > 1)
                                break;
                        }
                        if (diff == 1)
                            it->second.push_back(word);
                    }
                }
            });
            bool found = false;
            unordered_set<string> visited;
            queue<string> q[2];
            int step = 0;
            q[0].push(beginWord);
            visited.insert(beginWord);
            while (!q[0].empty() || !q[1].empty())
            {
                queue<string> &current = q[step & 0x1];
                queue<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.pop();
                    for (size_t i = 0; i < graph[word].size(); i++)
                    {
                        if (graph[word][i].compare(endWord) == 0)
                        {
                            found = true;
                            break;
                        }
                        if (visited.find(graph[word][i]) == visited.end())
                        {
                            visited.insert(graph[word][i]);
                            next.push(graph[word][i]);
                        }
                    }
                    if (found)
                        return step + 2;
                }
                step++;
            }
            return 0;
        }
        int ladderLength4(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return 0;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return 0;
            unordered_set<string> dict;
            dict.insert(wordList.begin(), wordList.end());
            auto diff1 = [&](const string &first, const string &second) -> bool {
                if (first.size() != second.size())
                    return false;
                int diff = 0;
                for (size_t i = 0; i < first.length(); i++)
                {
                    if (first[i] != second[i])
                        diff++;
                    if (diff > 1)
                        return false;
                }
                return diff == 1;
            };
            vector<string> q[2];
            int step = 0;
            q[0].push_back(beginWord);
            while (!q[0].empty() || !q[1].empty())
            {
                vector<string> &current = q[step & 0x1];
                vector<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.erase(current.begin());
                    for (unordered_set<string>::iterator it = dict.begin();
                         it != dict.end(); it++)
                    {
                        if (diff1(word, *it))
                        {
                            if ((*it).compare(endWord) == 0)
                                return step + 2;
                            else
                                next.push_back(*it);
                        }
                    }
                }
                for_each(next.begin(), next.end(), [&](string &s) { dict.erase(s); });
                step++;
            }
            return 0;
        }
        int ladderLength5(const string &beginWord, const string &endWord,
                          const vector<string> &wordList)
        {
            if (beginWord.empty() || endWord.empty() || wordList.empty())
                return 0;
            if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend())
                return 0;
            unordered_set<string> visited;
            queue<string> q[2];
            int step = 0;
            q[0].push(beginWord);
            visited.insert(beginWord);
            while (!q[0].empty() || !q[1].empty())
            {
                queue<string> &current = q[step & 0x1];
                queue<string> &next = q[(step + 1) & 0x1];
                while (!current.empty())
                {
                    string word = current.front();
                    current.pop();
                    int wordLen = word.size();
                    string temp;
                    for (int i = 0; i < wordLen; i++)
                    {
                        temp = word;
                        for (char j = 'a'; j <= 'z'; j++)
                        {
                            temp[i] = j;
                            if (temp.compare(endWord) == 0)
                                return step + 2;
                            if (find(wordList.cbegin(), wordList.cend(), temp) !=
                                    wordList.cend() &&
                                visited.find(temp) == visited.end())
                            {
                                visited.insert(temp);
                                next.push(temp);
                            }
                        }
                    }
                }
                step++;
            }
            return 0;
        }

        // 128. Longest Consecutive Sequence
        // Given an unsorted array of integers, find the length of the longest
        // consecutive elements sequence. Your algorithm should run in O(n) complexity.
        // Example:
        // Input: [100, 4, 200, 1, 3, 2]
        // Output: 4
        // Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
        // Therefore its length is 4.
        // Keep a list of open ranges in two maps:
        // (b0, e0), (b1, e1), ......, (bi, ei)
        // endWith = {
        //   e0: b0,
        //   e1: b1,
        //   ......
        //   ei: bi
        // }
        // beginWith = {
        //   b0: e0,
        //   b1: e1,
        //   ......
        //   bi: ei
        // }
        // Make sure no overlapping beginning points and ending points, i.e.,
        // {b0, b1, ......, bi} should be distinct, and so should be
        // {e0, e1, ......, ei}. For each new number j, check whether j can:
        // 1. merge two existing ranges (b, j) and (j, e)
        // 2. extend one exsting range (b, j) or (j, e)
        // 3. insert a new range (j-1, j+1)
        // For #2 and #3, it may happen that the existing range and the new range is
        // already within a larger range, and in this case the larger range should be
        // preserved.
        int longestConsecutive(const vector<int> &nums)
        {
            map<int, int> endWith;
            map<int, int> beginWith;
            int m = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                auto eit = endWith.find(nums[i]);
                auto bit = beginWith.find(nums[i]);
                if (eit != endWith.end() && bit != beginWith.end())
                {
                    // Merge (eit->second, nums[i]) and (nums[i], bit->second)
                    m = max(m, bit->second - eit->second - 1);
                    endWith[bit->second] = eit->second;
                    beginWith[eit->second] = bit->second;
                    endWith.erase(eit);
                    beginWith.erase(bit);
                }
                else if (eit != endWith.end())
                {
                    // Extend (eit->second, nums[i])
                    m = max(m, nums[i] - eit->second);
                    if (endWith.find(nums[i] + 1) == endWith.end() ||
                        endWith[nums[i] + 1] > eit->second)
                    {
                        beginWith[eit->second] = nums[i] + 1;
                        endWith[nums[i] + 1] = eit->second;
                        endWith.erase(eit);
                    }
                }
                else if (bit != beginWith.end())
                {
                    // Extend (nums[i], bit->second)
                    m = max(m, bit->second - nums[i]);
                    if (beginWith.find(nums[i] - 1) == beginWith.end() ||
                        beginWith[nums[i] - 1] < bit->second)
                    {
                        endWith[bit->second] = nums[i] - 1;
                        beginWith[nums[i] - 1] = bit->second;
                        beginWith.erase(bit);
                    }
                }
                else
                {
                    // Insert (nums[i] - 1, nums[i] + 1)
                    m = max(m, 1);
                    if (endWith.find(nums[i] + 1) == endWith.end() &&
                        beginWith.find(nums[i] - 1) == beginWith.end())
                    {
                        endWith[nums[i] + 1] = nums[i] - 1;
                        beginWith[nums[i] - 1] = nums[i] + 1;
                    }
                }
            }
            return m;
        }
        int longestConsecutive2(const vector<int> &nums)
        {
            map<int, int> endWith;
            map<int, int> beginWith;
            int m = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                auto eit = endWith.find(nums[i]);
                auto bit = beginWith.find(nums[i]);
                int begin;
                int end;
                if (eit != endWith.end() && bit != beginWith.end())
                {
                    begin = eit->second;
                    end = bit->second;
                    endWith.erase(bit->second);
                    beginWith.erase(eit->second);
                    endWith.erase(eit);
                    beginWith.erase(bit);
                }
                else if (eit != endWith.end())
                {
                    begin = eit->second;
                    end = nums[i] + 1;
                    beginWith.erase(eit->second);
                    endWith.erase(eit);
                }
                else if (bit != beginWith.end())
                {
                    begin = nums[i] - 1;
                    end = bit->second;
                    endWith.erase(bit->second);
                    beginWith.erase(bit);
                }
                else
                {
                    begin = nums[i] - 1;
                    end = nums[i] + 1;
                }
                if ((endWith.find(end) != endWith.end() && endWith[end] <= begin) ||
                    (beginWith.find(begin) != beginWith.end() &&
                     beginWith[begin] >= end))
                    continue;
                m = max(m, end - begin - 1);
                endWith[end] = begin;
                beginWith[begin] = end;
            }
            return m;
        }
        int longestConsecutive3(const vector<int> &nums)
        {
            vector<int> n(nums);
            sort(n.begin(), n.end());
            int c = 0;
            int m = 0;
            for (size_t i = 0; i < n.size(); i++)
            {
                if (i == 0 || n[i - 1] + 1 < n[i])
                {
                    m = max(m, c);
                    c = 1;
                }
                else if (n[i - 1] + 1 == n[i])
                {
                    c++;
                }
            }
            m = max(m, c);
            return m;
        }

        // 129. Sum Root to Leaf Numbers
        // Given a binary tree containing digits from 0-9 only, each root-to-leaf path
        // could represent a number. An example is the root-to-leaf path 1->2->3 which
        // represents the number 123. Find the total sum of all root-to-leaf numbers.
        // Note: A leaf is a node with no children.
        // Example:
        // Input: [1,2,3]
        //     1
        //    / \
        //   2   3
        // Output: 25
        // Explanation:
        // The root-to-leaf path 1->2 represents the number 12.
        // The root-to-leaf path 1->3 represents the number 13.
        // Therefore, sum = 12 + 13 = 25.
        // Example 2:
        // Input: [4,9,0,5,1]
        //     4
        //    / \
        //   9   0
        //  / \
        // 5   1
        // Output: 1026
        // Explanation:
        // The root-to-leaf path 4->9->5 represents the number 495.
        // The root-to-leaf path 4->9->1 represents the number 491.
        // The root-to-leaf path 4->0 represents the number 40.
        // Therefore, sum = 495 + 491 + 40 = 1026.
        int sumNumbers(TreeNode *root)
        {
            stack<pair<TreeNode *, int>> p;
            TreeNode *n = root;
            int t = 0;
            int s = 0;
            while (!p.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s = s * 10 + n->val;
                    if (n->left == nullptr && n->right == nullptr)
                        t += s;
                    p.push(make_pair(n, s));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> v = p.top();
                    p.pop();
                    n = v.first->right;
                    s = v.second;
                }
            }
            return t;
        }
        int sumNumbers2(TreeNode *root)
        {
            int t = 0;
            function<void(TreeNode *, int)> solve = [&](TreeNode *n, int s) {
                if (n == nullptr)
                    return;
                s = s * 10 + n->val;
                if (n->left == nullptr && n->right == nullptr)
                    t += s;
                solve(n->left, s);
                solve(n->right, s);
            };
            int s = 0;
            solve(root, s);
            return t;
        }

        // 130. Surrounded Regions
        // Given a 2D board containing 'X' and 'O' (the letter O), capture all regions
        // surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in
        // that surrounded region.
        // Example:
        // X X X X
        // X O O X
        // X X O X
        // X O X X
        // After running your function, the board should be:
        // X X X X
        // X X X X
        // X X X X
        // X O X X
        // Explanation:
        // Surrounded regions shouldn’t be on the border, which means that any 'O' on
        // the border of the board are not flipped to 'X'. Any 'O' that is not on the
        // border and it is not connected to an 'O' on the border will be flipped to
        // 'X'. Two cells are connected if they are adjacent cells connected
        // horizontally or vertically.
        void solve(vector<vector<char>> &board)
        {
            if (board.empty() || board[0].empty())
                return;
            int rows = board.size();
            int cols = board[0].size();
            function<void(int, int)> mark = [&](int i, int j) {
                if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != 'O')
                    return;
                board[i][j] = 'Y';
                mark(i - 1, j);
                mark(i + 1, j);
                mark(i, j - 1);
                mark(i, j + 1);
            };
            for (int i = 0; i < rows; i++)
            {
                if (board[i][0] == 'O')
                    mark(i, 0);
                if (board[i][cols - 1] == 'O')
                    mark(i, cols - 1);
            }
            for (int i = 0; i < cols; i++)
            {
                if (board[0][i] == 'O')
                    mark(0, i);
                if (board[rows - 1][i] == 'O')
                    mark(rows - 1, i);
            }
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (board[i][j] == 'O')
                        board[i][j] = 'X';
                    else if (board[i][j] == 'Y')
                        board[i][j] = 'O';
                }
            }
        }
        void solve2(vector<vector<char>> &board)
        {
            int height = board.size();
            if (height == 0)
                return;
            int width = board[0].size();
            set<pair<int, int>> nocapture;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (board[i][j] == 'O')
                    {
                        pair<int, int> p = make_pair(i, j);
                        if (nocapture.find(p) != nocapture.end())
                            continue;
                        bool boundary =
                            i == 0 || i == height - 1 || j == 0 || j == width - 1;
                        set<pair<int, int>> region;
                        queue<pair<int, int>> q;
                        region.insert(p);
                        q.push(p);
                        while (!q.empty())
                        {
                            p = q.front();
                            q.pop();
                            pair<int, int> n;
                            if (p.first > 0 && board[p.first - 1][p.second] == 'O')
                            {
                                if (p.first - 1 == 0)
                                    boundary = true;
                                n = make_pair(p.first - 1, p.second);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.second > 0 && board[p.first][p.second - 1] == 'O')
                            {
                                if (p.second - 1 == 0)
                                    boundary = true;
                                n = make_pair(p.first, p.second - 1);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.second < width - 1 &&
                                board[p.first][p.second + 1] == 'O')
                            {
                                if (p.second + 1 == width - 1)
                                    boundary = true;
                                n = make_pair(p.first, p.second + 1);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.first < height - 1 &&
                                board[p.first + 1][p.second] == 'O')
                            {
                                if (p.first + 1 == height - 1)
                                    boundary = true;
                                n = make_pair(p.first + 1, p.second);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                        }
                        if (boundary)
                        {
                            nocapture.insert(region.begin(), region.end());
                        }
                        else
                        {
                            for_each(region.begin(), region.end(),
                                     [&](pair<int, int> p) {
                                         board[p.first][p.second] = 'X';
                                     });
                        }
                    }
                }
            }
        }
        void solve3(vector<vector<char>> &board)
        {
            int height = board.size();
            if (height == 0)
                return;
            int width = board[0].size();
            auto search = [&](int i, int j) {
                if (board[i][j] == 'O')
                {
                    board[i][j] = 'C';
                    pair<int, int> p = make_pair(i, j);
                    queue<pair<int, int>> q;
                    q.push(p);
                    while (!q.empty())
                    {
                        p = q.front();
                        q.pop();
                        pair<int, int> n;
                        if (p.first > 0 && board[p.first - 1][p.second] == 'O')
                        {
                            board[p.first - 1][p.second] = 'C';
                            n = make_pair(p.first - 1, p.second);
                            q.push(n);
                        }
                        if (p.second > 0 && board[p.first][p.second - 1] == 'O')
                        {
                            board[p.first][p.second - 1] = 'C';
                            n = make_pair(p.first, p.second - 1);
                            q.push(n);
                        }
                        if (p.second < width - 1 &&
                            board[p.first][p.second + 1] == 'O')
                        {
                            board[p.first][p.second + 1] = 'C';
                            n = make_pair(p.first, p.second + 1);
                            q.push(n);
                        }
                        if (p.first < height - 1 &&
                            board[p.first + 1][p.second] == 'O')
                        {
                            board[p.first + 1][p.second] = 'C';
                            n = make_pair(p.first + 1, p.second);
                            q.push(n);
                        }
                    }
                }
            };
            for (int i = 0; i < height; i++)
            {
                search(i, 0);
                search(i, width - 1);
            }
            for (int i = 0; i < width; i++)
            {
                search(0, i);
                search(height - 1, i);
            }
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (board[i][j] == 'O')
                        board[i][j] = 'X';
                    else if (board[i][j] == 'C')
                        board[i][j] = 'O';
                }
            }
        }

        // 131. Palindrome Partitioning
        // Given a string s, partition s such that every substring of the partition
        // is a palindrome. Return all possible palindrome partitioning of s.
        // Example:
        // Input: "aab"
        // Output:
        // [
        //   ["aa","b"],
        //   ["a","a","b"]
        // ]
        // Let p[i] be the solution for s[i..(n-1)], then
        // p[i] = {{s[i], p[i+1]},
        //         {s[i..(i+1)], p[i+2]},    if s[i..(i+1)] is a palindrome
        //         {s[i..(i+2)], p[i+3]},    if s[i..(i+2)] is a palindrome
        //         ......
        //         {s[i..(n-3)], p[n-2]},    if s[i..(n-3)] is a palindrome
        //         {s[i..(n-2)], p[n-1]},    if s[i..(n-2)] is a palindrome
        //         {s[i..(n-1)]}       if s[i..(n-1)] is a palindrome
        //        }
        vector<vector<string>> partition(const string &s)
        {
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool {
                while (i < j)
                {
                    if (s[i++] != s[j--])
                        return false;
                }
                return true;
            };
            map<int, vector<vector<string>>> m;
            int n = s.size();
            for (int i = n - 1; i >= 0; i--)
            {
                m[i] = {};
                for (int j = i; j < n - 1; j++)
                {
                    if (isPalindrome(i, j))
                    {
                        string p = s.substr(i, j - i + 1);
                        for_each(m[j + 1].begin(), m[j + 1].end(),
                                 [&](const vector<string> &v) {
                                     vector<string> v1 = {p};
                                     v1.insert(v1.end(), v.cbegin(), v.cend());
                                     m[i].push_back(v1);
                                 });
                    }
                }
                if (isPalindrome(i, n - 1))
                    m[i].push_back({s.substr(i, n - i)});
            }
            return m[0];
        }
        vector<vector<string>> partition2(const string &s)
        {
            map<int, vector<vector<string>>> m;
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool {
                while (i < j)
                {
                    if (s[i] != s[j])
                        return false;
                    i++;
                    j--;
                }
                return true;
            };
            function<void(int)> solve = [&](int i) {
                if (i < 0 || i >= (int)s.size() || m.find(i) != m.end())
                    return;
                m[i] = {};
                if (i == (int)s.size() - 1)
                {
                    m[i].push_back({s.substr(i, 1)});
                }
                else
                {
                    for (int j = i; j < (int)s.size(); j++)
                    {
                        if (isPalindrome(i, j))
                        {
                            if (j == (int)s.size() - 1)
                                m[i].push_back({s.substr(i, j - i + 1)});
                            else
                            {
                                if (m.find(j + 1) == m.end())
                                    solve(j + 1);
                                for (size_t k = 0; k < m[j + 1].size(); k++)
                                {
                                    vector<string> v(1, s.substr(i, j - i + 1));
                                    v.insert(v.end(), m[j + 1][k].begin(),
                                             m[j + 1][k].end());
                                    m[i].push_back(v);
                                }
                            }
                        }
                    }
                }
            };
            solve(0);
            return m[0];
        }
        vector<vector<string>> partition3(const string &s)
        {
            vector<vector<string>> result;
            if (s.empty())
                return result;
            function<bool(size_t, size_t)> isPalindrome = [&](size_t i,
                                                              size_t j) -> bool {
                while (i < j)
                {
                    if (s[i++] != s[j--])
                        return false;
                }
                return true;
            };
            function<void(size_t, vector<string> &)> solve = [&](size_t i,
                                                                 vector<string> &p) {
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

        // 132. Palindrome Partitioning II
        // Given a string s, partition s such that every substring of the partition is
        // a palindrome. Return the minimum cuts needed for a palindrome partitioning of
        // s. Example: Input: "aab" Output: 1 Explanation: The palindrome partitioning
        // ["aa","b"] could be produced using 1 cut. Let p[i] be the solution for
        // s[0..i], then
        // p[i] = min{p[i-1] + 1, since s[i..i] is a palindrome
        //            p[i-2] + 1, if s[(i-1)..i] is a palindrome
        //            p[i-3] + 1, if s[(i-2)..i] is a palindrome
        //            ......
        //            p[2] + 1, if s[3..i] is a palindrome
        //            p[1] + 1, if s[2..i] is a palindrome
        //            p[0] + 1, if s[1..i] is a palindrome
        //            0         if s[0..i] is a palindrome
        //           }
        int minCut(const string &s)
        {
            if (s.empty())
                return 0;
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool {
                while (i < j)
                {
                    if (s[i++] != s[j--])
                        return false;
                }
                return true;
            };
            vector<int> p(s.size(), 0);
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (!isPalindrome(0, i))
                {
                    p[i] = INT_MAX;
                    for (int j = 0; j < i; j++)
                    {
                        if (isPalindrome(j + 1, i))
                            p[i] = min(p[i], p[j]);
                    }
                    p[i]++;
                }
            }
            return p[(int)s.size() - 1];
        }
        int minCut2(const string &s)
        {
            if (s.empty())
                return 0;
            map<pair<int, int>, bool> m;
            // function<void(void)> printm = [&]() {
            //     cout << "m = {" << endl;
            //     for_each(m.cbegin(), m.cend(),
            //              [&](const pair<pair<int, int>, bool> &p) {
            //                  cout << "  (" << p.first.first << ", " << p.first.second
            //                       << ") : " << p.second << endl;
            //              });
            //     cout << "}" << endl;
            // };
            function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool {
                // cout << "Enter m[(" << i << "," << j << ")]" << endl;
                // printm();
                pair<int, int> p = make_pair(i, j);
                if (m.find(p) == m.end())
                {
                    if (i >= j)
                    {
                        // cout << i << " >= " << j << endl;
                        m[p] = true;
                    }
                    else if (s[i] != s[j])
                    {
                        // cout << "s[" << i << "] != s[" << j << "]" << endl;
                        m[p] = false;
                    }
                    else
                    {
                        // pair<int, int> p1 = make_pair(i + 1, j - 1);
                        // if (m.find(p1) == m.end()) {
                        //     cout << "Call m[" << i + 1 << ", " << j - 1 << "]" <<
                        //     endl;
                        //     // m[p1] actually will create the p1 entry before calling
                        //     into
                        //     // isPalindrome, which returns immediately because it
                        //     will find
                        //     // the p1 entry already exists.
                        //     m[p1] = isPalindrome(i + 1, j - 1);
                        // }
                        // m[p] = m[p1];
                        m[p] = isPalindrome(i + 1, j - 1);
                    }
                }
                // cout << "Exit  m[(" << i << "," << j << ")] = " << m[p] << endl;
                return m[p];
            };
            vector<int> p(s.size(), 0);
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (!isPalindrome(0, i))
                {
                    p[i] = INT_MAX;
                    for (int j = 0; j < i; j++)
                    {
                        if (isPalindrome(j + 1, i))
                            p[i] = min(p[i], p[j]);
                    }
                    p[i]++;
                }
                // cout << "i = " << i << endl;
                // cout << "{";
                // for (size_t k = 0; k < p.size(); k++) {
                //     if (k > 0)
                //         cout << ", ";
                //     cout << p[k];
                // }
                // cout << "}" << endl;
            }
            return p[(int)s.size() - 1];
        }

        // Definition for a Node.
        class Node
        {
        public:
            int val;
            vector<Node *> neighbors;

            Node()
            {
                val = 0;
                neighbors = vector<Node *>();
            }

            Node(int _val)
            {
                val = _val;
                neighbors = vector<Node *>();
            }

            Node(int _val, vector<Node *> _neighbors)
            {
                val = _val;
                neighbors = _neighbors;
            }
        };

        Node *RandomGraph(const vector<int> &v)
        {
            if (v.empty())
                return nullptr;
            int l = v.size();
            vector<Node *> n(l, nullptr);
            transform(v.begin(), v.end(), n.begin(),
                      [&](int i) { return new Node(i); });
            for (int i = 0; i < l; i++)
            {
                int c = 1 + (rand() % l);
                for (; c > 0; c--)
                {
                    int j = rand() % l;
                    if (j == 0)
                        j++;
                    j = (i + j) % l;
                    if (find(n[i]->neighbors.begin(), n[i]->neighbors.end(), n[j]) ==
                        n[i]->neighbors.end())
                        n[i]->neighbors.push_back(n[j]);
                }
            }
            // cout << "{" << endl;
            // for (size_t i = 0; i < n.size(); i++) {
            //     cout << "  " << n[i]->val << " : {";
            //     for (size_t j = 0; j < n[i]->neighbors.size(); j++) {
            //         if (j > 0)
            //             cout << ", ";
            //         cout << n[i]->neighbors[j]->val;
            //     }
            //     cout << "}" << endl;
            // }
            // cout << "}" << endl;
            return *n.begin();
        }

        void DeleteGraph(Node *node)
        {
            if (node == nullptr)
                return;
            set<Node *> m;
            m.insert(node);
            queue<Node *> q;
            q.push(node);
            while (!q.empty())
            {
                Node *f = q.front();
                q.pop();
                for_each(f->neighbors.begin(), f->neighbors.end(), [&](Node *n) {
                    if (m.find(n) == m.end())
                    {
                        m.insert(n);
                        q.push(n);
                    }
                });
                f->neighbors.clear();
            }
            for_each(m.begin(), m.end(), [&](Node *n) {
                // cout << "delete " << n->val << endl;
                delete n;
            });
            m.clear();
        }

        // Assume every node has a unique value
        map<int, vector<int>> ToMap(Node *node)
        {
            map<int, vector<int>> m;
            if (node == nullptr)
                return m;
            m[node->val] = {};
            queue<Node *> q;
            q.push(node);
            while (!q.empty())
            {
                Node *f = q.front();
                q.pop();
                for_each(f->neighbors.begin(), f->neighbors.end(), [&](Node *n) {
                    if (m.find(n->val) == m.end())
                    {
                        m[n->val] = {};
                        q.push(n);
                    }
                    m[f->val].push_back(n->val);
                });
            }
            return m;
        }

        // 133. Clone Graph
        // Given a reference of a node in a connected undirected graph. Return a deep
        // copy (clone) of the graph. Each node in the graph contains a val (int) and
        // a list (List[Node]) of its neighbors.
        // class Node {
        //     public int val;
        //     public List<Node> neighbors;
        // }
        // Test case format:
        // For simplicity sake, each node's value is the same as the node's index
        // (1-indexed). For example, the first node with val = 1, the second node with
        // val = 2, and so on. The graph is represented in the test case using an
        // adjacency list. Adjacency list is a collection of unordered lists used to
        // represent a finite graph. Each list describes the set of neighbors of a node
        // in the graph. The given node will always be the first node with val = 1. You
        // must return the copy of the given node as a reference to the cloned graph.
        // Example 1:
        // Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
        // Output: [[2,4],[1,3],[2,4],[1,3]]
        // Explanation: There are 4 nodes in the graph.
        // 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
        // 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
        // 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
        // 4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
        // Example 2:
        // Input: adjList = [[]]
        // Output: [[]]
        // Explanation: Note that the input contains one empty list. The graph consists
        // of only one node with val = 1 and it does not have any neighbors.
        // Example 3:
        // Input: adjList = []
        // Output: []
        // Explanation: This an empty graph, it does not have any nodes.
        // Example 4:
        // Input: adjList = [[2],[1]]
        // Output: [[2],[1]]
        // Constraints:
        // 1 <= Node.val <= 100
        // Node.val is unique for each node.
        // Number of Nodes will not exceed 100.
        // There is no repeated edges and no self-loops in the graph.
        // The Graph is connected and all nodes can be visited starting from the given
        // node.
        Node *cloneGraph(Node *node)
        {
            map<Node *, Node *> cloned;
            function<Node *(Node *)> clone = [&](Node *node) -> Node * {
                if (node == nullptr)
                    return nullptr;
                if (cloned.find(node) != cloned.end())
                    return cloned[node];
                Node *copy = new Node(node->val);
                cloned[node] = copy;
                for_each(node->neighbors.begin(), node->neighbors.end(),
                         [&](Node *n) { copy->neighbors.push_back(clone(n)); });
                return copy;
            };
            return clone(node);
        }
        Node *cloneGraph2(Node *node)
        {
            if (node == nullptr)
                return nullptr;
            map<Node *, Node *> m;
            m[node] = new Node(node->val);
            queue<Node *> q;
            q.push(node);
            while (!q.empty())
            {
                Node *f = q.front();
                q.pop();
                for_each(f->neighbors.begin(), f->neighbors.end(), [&](Node *n) {
                    if (m.find(n) == m.end())
                    {
                        m[n] = new Node(n->val);
                        q.push(n);
                    }
                    m[f]->neighbors.push_back(m[n]);
                });
            }
            return m[node];
        }

        // 134. Gas Station
        // There are N gas stations along a circular route, where the amount of gas at
        // station i is gas[i]. You have a car with an unlimited gas tank and it costs
        // cost[i] of gas to travel from station i to its next station (i+1). You begin
        // the journey with an empty tank at one of the gas stations. Return the
        // starting gas station's index if you can travel around the circuit once in the
        // clockwise direction, otherwise return -1. Note: If there exists a solution,
        // it is guaranteed to be unique. Both input arrays are non-empty and have the
        // same length. Each element in the input arrays is a non-negative integer.
        // Example 1:
        // Input:
        // gas  = [1,2,3,4,5]
        // cost = [3,4,5,1,2]
        // Output: 3
        // Explanation:
        // Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 +
        // 4 = 4 Travel to station 4. Your tank = 4 - 1 + 5 = 8 Travel to station 0.
        // Your tank = 8 - 2 + 1 = 7 Travel to station 1. Your tank = 7 - 3 + 2 = 6
        // Travel to station 2. Your tank = 6 - 4 + 3 = 5
        // Travel to station 3. The cost is 5. Your gas is just enough to travel back to
        // station 3. Therefore, return 3 as the starting index. Example 2: Input: gas
        // = [2,3,4] cost = [3,4,3] Output: -1 Explanation: You can't start at station 0
        // or 1, as there is not enough gas to travel to the next station. Let's start
        // at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4 Travel to
        // station 0. Your tank = 4 - 3 + 2 = 3 Travel to station 1. Your tank = 3 - 3 +
        // 3 = 3 You cannot travel back to station 2, as it requires 4 unit of gas but
        // you only have 3. Therefore, you can't travel around the circuit once no
        // matter where you start.
        int canCompleteCircuit(const vector<int> &gas, const vector<int> &cost)
        {
            size_t i = 0;
            while (i < gas.size())
            {
                int t = 0;
                size_t j = 0;
                while (j < gas.size())
                {
                    int k = (i + j) % gas.size();
                    t = t + gas[k] - cost[k];
                    if (t < 0)
                        break;
                    j++;
                }
                if (j == gas.size())
                    return i;
                i = i + j + 1;
            }
            return -1;
        }
        int canCompleteCircuit2(const vector<int> &gas, const vector<int> &cost)
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

        // 135. Candy
        // There are N children standing in a line. Each child is assigned a rating
        // value. You are giving candies to these children subjected to the following
        // requirements: Each child must have at least one candy. Children with a higher
        // rating get more candies than their neighbors. What is the minimum candies you
        // must give? Example 1: Input: [1,0,2] Output: 5 Explanation: You can allocate
        // to the first, second and third child with 2, 1, 2 candies respectively.
        // Example 2:
        // Input: [1,2,2]
        // Output: 4
        // Explanation: You can allocate to the first, second and third child with 1, 2,
        // 1 candies respectively. The third child gets 1 candy because it satisfies the
        // above two conditions.
        int candy(const vector<int> &ratings)
        {
            vector<int> c(ratings.size(), 1);
            for (int i = 1; i < (int)c.size(); i++)
            {
                if (ratings[i - 1] < ratings[i])
                    c[i] = c[i - 1] + 1;
            }
            int t = c[c.size() - 1];
            for (int i = c.size() - 2; i >= 0; i--)
            {
                if (ratings[i] > ratings[i + 1] && c[i] <= c[i + 1])
                    c[i] = c[i + 1] + 1;
                t += c[i];
            }
            return t;
        }

        // 136. Single Number
        // Given a non-empty array of integers, every element appears twice except for
        // one. Find that single one. Note: Your algorithm should have a linear runtime
        // complexity. Could you implement it without using extra memory?
        // Example 1:
        // Input: [2,2,1]
        // Output: 1
        // Example 2:
        // Input: [4,1,2,1,2]
        // Output: 4
        int singleNumber(const vector<int> &nums)
        {
            int r = 0;
            for_each(nums.begin(), nums.end(), [&](int n) { r ^= n; });
            return r;
        }
        int singleNumber2(const vector<int> &nums)
        {
            return accumulate(nums.cbegin(), nums.cend(), 0, [&](int x, int n) -> int { return x ^ n; });
        }

        // 137. Single Number II
        // Given a non-empty array of integers, every element appears three times except
        // for one, which appears exactly once. Find that single one. Note: Your
        // algorithm should have a linear runtime complexity. Could you implement it
        // without using extra memory? Example 1: Input: [2,2,3,2] Output: 3 Example 2:
        // Input: [0,1,0,1,0,1,99]
        // Output: 99
        int singleNumberII(const vector<int> &nums)
        {
            int length = nums.size();
            if (length % 3 != 1)
                throw invalid_argument("The count of numbers is not 3n+1");
            int n = 0;
            int bits = 8 * sizeof(int);
            for (int i = 0; i < bits; i++)
            {
                int count = 0;
                for (int j = 0; j < length; j++)
                    count += ((nums[j] >> i) & 0x1);
                n |= ((count % 3) << i);
            }
            return n;
        }
        int singleNumberII2(const vector<int> &nums)
        {
            int length = nums.size();
            if (length % 3 != 1)
                throw invalid_argument("The count of numbers is not 3n+1");
            int o0 = ~0; // positions that bit 1 occurred 0 or 3 times
            int o1 = 0;  // positions that bit 1 occurred 1 time
            int o2 = 0;  // positions that bit 1 occurred 2 times
            int t = 0;
            for (int i = 0; i < length; i++)
            {
                t = o2; // keep o2 temporarily to calculate o0 later
                o2 = (o1 & nums[i]) |
                     (o2 & ~nums[i]); // Update the positions that bit 1 occurred the
                                      // second time due to input[i], and keep the
                                      // positions that bit 1 already occurred two times
                                      // and not affected by input[i]
                o1 = (o0 & nums[i]) |
                     (o1 & ~nums[i]); // Update the positions that bit 1 occurred the
                                      // first time due to input[i], and keep the
                                      // positions that bit 1 already occurred one time
                                      // and not affected by input[i]
                o0 = (t & nums[i]) |
                     (o0 & ~nums[i]); // Update the positions that bit 1 occurred the
                                      // third time due to input[i], and keep the
                                      // positions that bit 1 already occurred zero or
                                      // three times and not affected by input[i]
            }
            return o1;
        }
        int singleNumberII3(const vector<int> &nums)
        {
            int length = nums.size();
            if (length % 3 != 1)
                throw invalid_argument("The count of numbers is not 3n+1");
            int o1 = 0; // positions that bit 1 occurred 0 or 3 times
            int o2 = 0; // positions that bit 1 occurred 1 time
            int o3 = 0; // positions that bit 1 occurred 2 times
            for (int i = 0; i < length; i++)
            {
                o2 |= o1 & nums[i];
                o1 ^= nums[i];
                o3 = o1 & o2;
                o1 &= ~o3;
                o2 &= ~o3;
            }
            return o1;
        }

        class NodeWithRandomLink
        {
        public:
            struct Node
            {
                int val;
                Node *next;
                Node *random;

                Node(int _val)
                {
                    val = _val;
                    next = nullptr;
                    random = nullptr;
                }
            };
            // 138. Copy List with Random Pointer
            // A linked list is given such that each node contains an additional random
            // pointer which could point to any node in the list or null. Return a deep
            // copy of the list. The Linked List is represented in the input/output as a
            // list of n nodes. Each node is represented as a pair of [val, random_index]
            // where: val: an integer representing Node.val, and random_index: the index
            // of the node (range from 0 to n-1) where random pointer points to, or null
            // if it does not point to any node.
            // Example 1:
            // Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
            // Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
            // Example 2:
            // Input: head = [[1,1],[2,1]]
            // Output: [[1,1],[2,1]]
            // Example 3:
            // Input: head = [[3,null],[3,0],[3,null]]
            // Output: [[3,null],[3,0],[3,null]]
            // Example 4:
            // Input: head = []
            // Output: []
            // Explanation: Given linked list is empty (null pointer), so return null.
            // Constraints: -10000 <= Node.val <= 10000. Node.random is null or pointing
            // to a node in the linked list. Number of Nodes will not exceed 1000.
            Node *copyRandomList(Node *head)
            {
                map<Node *, Node *> m;
                function<Node *(Node *)> copy =
                    [&](Node *n) -> Node * {
                    if (n == nullptr)
                        return nullptr;
                    if (m.find(n) == m.end())
                    {
                        m[n] = new Node(n->val);
                        m[n]->next = copy(n->next);
                        m[n]->random = copy(n->random);
                    }
                    return m[n];
                };
                return copy(head);
            }
            Node *copyRandomList2(Node *head)
            {
                map<Node *, Node *> m;
                function<Node *(Node *)> copy = [&](Node *n) -> Node * {
                    if (n == nullptr)
                        return nullptr;
                    if (m.find(n) != m.end())
                        return m[n];
                    Node *c = new Node(n->val);
                    m[n] = c; // save it before copying next and random
                    c->next = copy(n->next);
                    c->random = copy(n->random);
                    return c;
                };
                return copy(head);
            }
            Node *copyRandomList3(Node *head)
            {
                map<Node *, Node *> m;
                function<Node *(Node *)> copy = [&](Node *n) -> Node * {
                    if (n == nullptr)
                        return nullptr;
                    if (m.find(n) == m.end())
                        m[n] = new Node(n->val);
                    return m[n];
                };
                Node *n = head;
                while (n != nullptr)
                {
                    Node *c = copy(n);
                    c->next = copy(n->next);
                    c->random = copy(n->random);
                    n = n->next;
                }
                return head == nullptr ? nullptr : m[head];
            }
            Node *copyRandomList4(Node *head)
            {
                Node *n = head;
                while (n != nullptr)
                {
                    Node *c = new Node(n->val);
                    c->next = n->next;
                    n->next = c;
                    n = c->next;
                }
                n = head;
                while (n != nullptr)
                {
                    if (n->random != nullptr)
                        n->next->random = n->random->next;
                    n = n->next->next;
                }
                Node *h = nullptr;
                Node *t = nullptr;
                n = head;
                while (n != nullptr)
                {
                    if (h == nullptr)
                        h = n->next;
                    else
                        t->next = n->next;
                    t = n->next;
                    n->next = t->next;
                    t->next = nullptr;
                    n = n->next;
                }
                return h;
            }
        };

        // 139. Word Break
        // Given a non-empty string s and a dictionary wordDict containing a list of
        // non-empty words, determine if s can be segmented into a space-separated
        // sequence of one or more dictionary words. Note: The same word in the
        // dictionary may be reused multiple times in the segmentation. You may assume
        // the dictionary does not contain duplicate words.
        // Example 1:
        // Input: s = "leetcode", wordDict = ["leet", "code"]
        // Output: true
        // Explanation: Return true because "leetcode" can be segmented as "leet code".
        // Example 2:
        // Input: s = "applepenapple", wordDict = ["apple", "pen"]
        // Output: true
        // Explanation: Return true because "applepenapple" can be segmented as "apple
        // pen apple". Note that you are allowed to reuse a dictionary word. Example 3:
        // Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
        // Output: false
        bool wordBreak(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)> same = [&](size_t i,
                                                              const string &w) -> bool {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            map<size_t, bool> m;
            function<bool(size_t)> solve = [&](size_t i) -> bool {
                if (m.find(i) != m.end())
                    return m[i];
                if (i == s.size())
                    m[i] = true;
                else if (i > s.size())
                    m[i] = false;
                else
                {
                    bool match = false;
                    for (size_t j = 0; j < wordDict.size(); j++)
                    {
                        if (same(i, wordDict[j]) && solve(i + wordDict[j].size()))
                        {
                            match = true;
                            break;
                        }
                    }
                    m[i] = match;
                }
                return m[i];
            };
            return solve(0);
        }
        bool wordBreak2(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)> same = [&](size_t i,
                                                              const string &w) -> bool {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            set<size_t> m;
            queue<size_t> q;
            q.push(0);
            while (!q.empty())
            {
                size_t i = q.front();
                q.pop();
                for (size_t j = 0; j < wordDict.size(); j++)
                {
                    if (same(i, wordDict[j]))
                    {
                        if (i + wordDict[j].size() == s.size())
                            return true;
                        if (m.find(i + wordDict[j].size()) == m.end())
                            q.push(i + wordDict[j].size());
                    }
                }
                m.insert(i);
            }
            return false;
        }
        bool wordBreak3(const string &s, const vector<string> &wordDict)
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
            function<bool(size_t)> solve = [&](size_t i) -> bool {
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
                        auto it =
                            find(wordDict.begin(), wordDict.end(), s.substr(i, j));
                        if (it != wordDict.end())
                        {
                            if (breakable.find(i + j) == breakable.end())
                                solve(i + j);
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

        // 140. Word Break II
        // Given a non-empty string s and a dictionary wordDict containing a list of
        // non-empty words, add spaces in s to construct a sentence where each word is
        // a valid dictionary word. Return all such possible sentences. Note: The same
        // word in the dictionary may be reused multiple times in the segmentation. You
        // may assume the dictionary does not contain duplicate words.
        // Example 1:
        // Input:
        // s = "catsanddog"
        // wordDict = ["cat", "cats", "and", "sand", "dog"]
        // Output:
        // [
        //   "cats and dog",
        //   "cat sand dog"
        // ]
        // Example 2:
        // Input:
        // s = "pineapplepenapple"
        // wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
        // Output:
        // [
        //   "pine apple pen apple",
        //   "pineapple pen apple",
        //   "pine applepen apple"
        // ]
        // Explanation: Note that you are allowed to reuse a dictionary word.
        // Example 3:
        // Input:
        // s = "catsandog"
        // wordDict = ["cats", "dog", "sand", "and", "cat"]
        // Output:
        // []
        vector<string> wordBreakII(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)> same = [&](size_t i,
                                                              const string &w) -> bool {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            map<size_t, vector<string>> m;
            function<void(size_t)> solve = [&](size_t i) {
                if (i > s.size() || m.find(i) != m.end())
                    return;
                m[i] = {};
                if (i == s.size())
                    return;
                for (size_t j = 0; j < wordDict.size(); j++)
                {
                    if (same(i, wordDict[j]))
                    {
                        size_t k = i + wordDict[j].size();
                        if (k == s.size())
                        {
                            m[i].push_back(wordDict[j]);
                        }
                        else
                        {
                            solve(k);
                            for_each(m[k].begin(), m[k].end(), [&](string &r) {
                                string r1 = wordDict[j];
                                r1.append(1, ' ');
                                r1.append(r);
                                m[i].push_back(r1);
                            });
                        }
                    }
                }
            };
            solve(0);
            return m[0];
        }
        vector<string> wordBreakII2(const string &s, const vector<string> &wordDict)
        {
            function<bool(size_t, const string &)> same = [&](size_t i,
                                                              const string &w) -> bool {
                if (i + w.size() > s.size())
                    return false;
                for (size_t j = 0; j < w.size(); j++)
                {
                    if (s[i + j] != w[j])
                        return false;
                }
                return true;
            };
            vector<string> results;
            queue<pair<size_t, string>> q;
            q.push(make_pair(0, string()));
            while (!q.empty())
            {
                pair<size_t, string> p = q.front();
                q.pop();
                for (size_t i = 0; i < wordDict.size(); i++)
                {
                    if (same(p.first, wordDict[i]))
                    {
                        size_t k = p.first + wordDict[i].size();
                        string r = p.second;
                        if (!r.empty())
                            r.append(1, ' ');
                        r.append(wordDict[i]);
                        if (k == s.size())
                            results.push_back(r);
                        else
                            q.push(make_pair(k, r));
                    }
                }
            }
            return results;
        }

        // 141. Linked List Cycle
        // Given a linked list, determine if it has a cycle in it. To represent a cycle
        // in the given linked list, we use an integer pos which represents the position
        // (0-indexed) in the linked list where tail connects to. If pos is -1, then
        // there is no cycle in the linked list. Example 1: Input: head = [3,2,0,-4],
        // pos = 1 Output: true Explanation: There is a cycle in the linked list, where
        // tail connects to the second node. Example 2: Input: head = [1,2], pos = 0
        // Output: true
        // Explanation: There is a cycle in the linked list, where tail connects to the
        // first node. Example 3: Input: head = [1], pos = -1 Output: false Explanation:
        // There is no cycle in the linked list. Follow up: Can you solve it using O(1)
        // (i.e. constant) memory?
        bool hasCycle(ListNode *head)
        {
            if (head == nullptr)
                return false;
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
                if (p == q)
                    return true;
            }
            return false;
        }
        bool hasCycle2(ListNode *head)
        {
            ListNode *p = head;
            ListNode *q = head;
            while (q != nullptr && q->next != nullptr)
            {
                p = p->next;
                q = q->next;
                q = q->next;
                if (p == q)
                    return true;
            }
            return false;
        }

        // 142. Linked List Cycle II
        // Given a linked list, return the node where the cycle begins. If there is no
        // cycle, return null. To represent a cycle in the given linked list, we use an
        // integer pos which represents the position (0-indexed) in the linked list
        // where tail connects to. If pos is -1, then there is no cycle in the linked
        // list. Note: Do not modify the linked list. Example 1: Input: head =
        // [3,2,0,-4], pos = 1 Output: tail connects to node index 1 Explanation: There
        // is a cycle in the linked list, where tail connects to the second node.
        // Example 2:
        // Input: head = [1,2], pos = 0
        // Output: tail connects to node index 0
        // Explanation: There is a cycle in the linked list, where tail connects to the
        // first node. Example 3: Input: head = [1], pos = -1 Output: no cycle
        // Explanation: There is no cycle in the linked list.
        // Follow-up: Can you solve it without using extra space?
        ListNode *detectCycle(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
                if (p == q)
                    break;
            }
            if (q->next == nullptr || q->next->next == nullptr)
                return nullptr;
            q = head;
            while (q != p)
            {
                p = p->next;
                q = q->next;
            }
            return q;
        }
        ListNode *detectCycle2(ListNode *head)
        {
            ListNode *p = head;
            ListNode *q = head;
            while (q != nullptr && q->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
                if (p == q)
                    break;
            }
            if (q == nullptr || q->next == nullptr)
                return nullptr;
            p = head;
            while (p != q)
            {
                p = p->next;
                q = q->next;
            }
            return p;
        }

        // 143. Reorder List
        // Given a singly linked list L: L0->L1->......->Ln-1->Ln,
        // reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->......
        // You may not modify the values in the list's nodes, only nodes itself may be
        // changed. Example 1: Given 1->2->3->4, reorder it to 1->4->2->3. Example 2:
        // Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
        void reorderList(ListNode *head)
        {
            if (head == nullptr)
                return;
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
            }
            if (p == q)
                return; // List has only one or two nodes
            // Now p is the (1 + k)-th node
            // q is the (1 + 2k)-th node
            // The list has (1 + 2k) nodes or (2 + 2k) nodes
            // Break after p
            q = p->next;
            p->next = nullptr;
            // Reverse list at q
            p = q;
            q = p->next;
            p->next = nullptr;
            while (q != nullptr)
            {
                ListNode *t = q->next;
                q->next = p;
                p = q;
                q = t;
            }
            // Merge the list at head and the list at p
            q = head;
            while (p != nullptr)
            {
                ListNode *t = p->next;
                p->next = q->next;
                q->next = p;
                q = p->next;
                p = t;
            }
        }

        // 146. LRU Cache
        // Design and implement a data structure for Least Recently Used (LRU) cache.
        // It should support the following operations: get and put.
        // get(key) - Get the value (will always be positive) of the key if the key
        // exists in the cache, otherwise return -1.
        // put(key, value) - Set or insert the value if the key is not already present.
        // When the cache reached its capacity, it should invalidate the least recently
        // used item before inserting a new item.
        // The cache is initialized with a positive capacity.
        // Follow up: Could you do both operations in O(1) time complexity?
        // Example:
        // LRUCache cache = new LRUCache( 2 /* capacity */ );
        // cache.put(1, 1);
        // cache.put(2, 2);
        // cache.get(1);       // returns 1
        // cache.put(3, 3);    // evicts key 2
        // cache.get(2);       // returns -1 (not found)
        // cache.put(4, 4);    // evicts key 1
        // cache.get(1);       // returns -1 (not found)
        // cache.get(3);       // returns 3
        // cache.get(4);       // returns 4
        class LRUCache
        {
        private:
            int _capacity;
            struct Item
            {
                int key;
                int value;
                struct Item *prev;
                struct Item *next;
                Item(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
            } * head, *tail;
            map<int, struct Item *> keys;
            void MoveFront(struct Item *p)
            {
                if (p == this->head)
                    return;
                if (p == this->tail)
                {
                    this->tail = p->prev;
                    this->tail->next = nullptr;
                }
                else
                {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                }
                p->next = this->head;
                this->head->prev = p;
                p->prev = nullptr;
                this->head = p;
            }

        public:
            LRUCache(int capacity)
                : _capacity(capacity), head(nullptr), tail(nullptr) {}
            ~LRUCache(void)
            {
                while (this->head != nullptr)
                {
                    struct Item *p = this->head;
                    this->head = this->head->next;
                    delete p;
                }
            }
            int Get(int key)
            {
                if (this->keys.find(key) == this->keys.end())
                {
                    return -1;
                }
                else
                {
                    struct Item *p = this->keys[key];
                    MoveFront(p);
                    return p->value;
                }
            }
            void Set(int key, int value)
            {
                struct Item *p;
                if (this->keys.find(key) == this->keys.end())
                {
                    if ((int)this->keys.size() == this->_capacity)
                    {
                        int k = this->tail->key;
                        if (this->head == this->tail)
                        {
                            delete this->head;
                            this->head = nullptr;
                            this->tail = nullptr;
                        }
                        else
                        {
                            p = this->tail;
                            this->tail = p->prev;
                            this->tail->next = nullptr;
                            delete p;
                        }
                        this->keys.erase(k);
                    }
                    p = new struct Item(key, value);
                    if (this->head == nullptr)
                    {
                        this->head = p;
                        this->tail = p;
                    }
                    else
                    {
                        p->next = this->head;
                        this->head->prev = p;
                        this->head = p;
                    }
                    this->keys[key] = p;
                }
                else
                {
                    // Whether or not to change the value,
                    // it counts as an access.
                    p = this->keys[key];
                    p->value = value;
                    MoveFront(p);
                }
            }
        };

        // 147. Insertion Sort List
        // Sort a linked list using insertion sort. A graphical example of insertion
        // sort. The partial sorted list (black) initially contains only the first
        // element in the list. With each iteration one element (red) is removed from
        // the input data and inserted in-place into the sorted list. Algorithm of
        // Insertion Sort: Insertion sort iterates, consuming one input element each
        // repetition, and growing a sorted output list. At each iteration, insertion
        // sort removes one element from the input data, finds the location it belongs
        // within the sorted list, and inserts it there. It repeats until no input
        // elements remain. Example 1: Input: 4->2->1->3 Output: 1->2->3->4 Example 2:
        // Input: -1->5->3->4->0
        // Output: -1->0->3->4->5
        ListNode *insertionSortList(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *t = head;
            ListNode *p = head->next;
            while (p != nullptr)
            {
                ListNode *q = p;
                p = q->next;
                if (q->val < head->val)
                {
                    t->next = p;
                    q->next = head;
                    head = q;
                    continue;
                }
                ListNode *s = head;
                while (s != t && s->next->val <= q->val)
                {
                    s = s->next;
                }
                if (s == t)
                {
                    t = q;
                }
                else
                {
                    t->next = p;
                    q->next = s->next;
                    s->next = q;
                }
            }
            return head;
        }
        ListNode *insertionSortList2(ListNode *head)
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
        // Sort a linked list in O(n log n) time using constant space complexity.
        // Example 1:
        // Input: 4->2->1->3
        // Output: 1->2->3->4
        // Example 2:
        // Input: -1->5->3->4->0
        // Output: -1->0->3->4->5
        ListNode *sortList(ListNode *head)
        {
            function<ListNode *(ListNode *, ListNode *)> merge =
                [&](ListNode *p, ListNode *q) -> ListNode * {
                if (p == nullptr)
                    return q;
                if (q == nullptr)
                    return p;
                ListNode *h = nullptr;
                ListNode *t = nullptr;
                while (p != nullptr && q != nullptr)
                {
                    if (p->val <= q->val)
                    {
                        if (h == nullptr)
                            h = p;
                        else
                            t->next = p;
                        t = p;
                        p = p->next;
                    }
                    else
                    {
                        if (h == nullptr)
                            h = q;
                        else
                            t->next = q;
                        t = q;
                        q = q->next;
                    }
                }
                if (p == nullptr)
                    t->next = q;
                else
                    t->next = p;
                return h;
            };
            function<ListNode *(ListNode *)> sort = [&](ListNode *h) -> ListNode * {
                if (h == nullptr || h->next == nullptr)
                    return h;
                ListNode *p = h;
                ListNode *q = h;
                while (q->next != nullptr && q->next->next != nullptr)
                {
                    p = p->next;
                    q = q->next->next;
                }
                q = p->next;
                p->next = nullptr;
                h = sort(h);
                q = sort(q);
                return merge(h, q);
            };
            return sort(head);
        }

        // 149. Max Points on a Line
        // Given n points on a 2D plane, find the maximum number of points that lie on
        // the same straight line.
        // Example 1:
        // Input: [[1,1],[2,2],[3,3]]
        // Output: 3
        // Explanation:
        // ^
        // |
        // |        o
        // |     o
        // |  o
        // +------------->
        // 0  1  2  3  4
        // Example 2:
        // Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
        // Output: 4
        // Explanation:
        // ^
        // |
        // |  o
        // |     o        o
        // |        o
        // |  o        o
        // +------------------->
        // 0  1  2  3  4  5  6
        // NOTE: input types have been changed on April 15, 2019. Please reset to
        // default code definition to get new method signature.
        int maxPoints(const vector<vector<int>> &points)
        {
            if (points.size() < 2)
                return (int)points.size();
            function<int(int, int)> gcd = [&](int a, int b) -> int {
                if (a < b)
                    swap(a, b);
                while (b != 0)
                {
                    int c = a % b;
                    a = b;
                    b = c;
                }
                return a;
            };
            function<pair<int, int>(const vector<int> &, const vector<int> &)> slope =
                [&](const vector<int> &p, const vector<int> &q) -> pair<int, int> {
                if (p[0] == q[0])
                    return make_pair(0, 1);
                if (p[1] == q[1])
                    return make_pair(1, 0);
                int g = gcd(abs(q[0] - p[0]), abs(q[1] - p[1]));
                int x = (q[0] - p[0]) / g;
                int y = (q[1] - p[1]) / g;
                if (y < 0)
                {
                    x = -x;
                    y = -y;
                }
                // cout << "slope((" << p[0] << ", " << p[1] << "), (" << q[0] << ", "
                //      << q[1] << ")) = "
                //      << "(" << x << ", " << y << ")" << endl;
                // cout << "gcd = " << g << endl;
                return make_pair(x, y);
            };
            int mc = 0;
            for (size_t i = 0; i < points.size(); i++)
            {
                // cout << "Start (" << points[i][0] << ", " << points[i][1] << ")"
                //      << endl;
                map<pair<int, int>, int> m;
                int n = 1; // count duplicates of points[i]
                int c = 0; // count other points on the same line as points[i]
                for (size_t j = 0; j < points.size(); j++)
                {
                    if (j == i)
                        continue;
                    if (points[j][0] == points[i][0] && points[j][1] == points[i][1])
                        n++;
                    else
                    {
                        pair<int, int> k = slope(points[i], points[j]);
                        if (m.find(k) == m.end())
                            m[k] = 1;
                        else
                            m[k]++;
                        c = max(c, m[k]);
                    }
                }
                mc = max(mc, c + n);
                // cout << "m = {" << endl;
                // for_each(m.cbegin(), m.cend(), [&](const pair<pair<int, int>, int>
                // &p) {
                //     cout << "(" << p.first.first << ", " << p.first.second
                //          << ") : " << p.second << endl;
                // });
                // cout << "}" << endl;
            }
            return mc;
        }
        int maxPoints2(vector<vector<int>> &points)
        {
            if (points.size() <= 1)
                return points.size();
            function<int(int, int)> gcd = [&](int a, int b) -> int {
                if (a < b)
                    swap(a, b);
                while (b != 0)
                {
                    int c = a % b;
                    a = b;
                    b = c;
                }
                return a;
            };
            function<pair<int, int>(const vector<int> &, const vector<int> &)>
                get_slope =
                    [&](const vector<int> &p, const vector<int> &q) -> pair<int, int> {
                if (p[0] == q[0])
                    return make_pair(0, 1);
                if (p[1] == q[1])
                    return make_pair(1, 0);
                int g = gcd(abs(q[0] - p[0]), abs(q[1] - p[1]));
                int x = (q[0] - p[0]) / g;
                int y = (q[1] - p[1]) / g;
                if (y < 0)
                {
                    x = -x;
                    y = -y;
                }
                // cout << "slope((" << p[0] << ", " << p[1] << "), (" << q[0] << ", "
                //      << q[1] << ")) = "
                //      << "(" << x << ", " << y << ")" << endl;
                // cout << "gcd = " << g << endl;
                return make_pair(x, y);
            };
            // Group pairs of points by slopes. The points with the same slope
            // are potentially on the same lines.
            // Use comparer of IntPoint
            sort(points.begin(), points.end(),
                 [&](const vector<int> &l, const vector<int> &r) {
                     if (l[0] == r[0])
                         return l[1] < r[1];
                     return l[0] < r[0];
                 });
            map<vector<int>, int> dup;
            map<pair<int, int>, vector<pair<vector<int>, vector<int>>>> slopes;
            for (size_t i = 0; i < points.size(); i++)
            {
                if (dup.find(points[i]) == dup.end())
                    dup[points[i]] = 1;
                else
                    dup[points[i]]++;
                for (size_t j = i + 1; j < points.size(); j++)
                {
                    if (points[i] == points[j])
                    {
                        // Ignore duplication
                        continue;
                    }
                    pair<int, int> slope = get_slope(points[i], points[j]);
                    if (slopes.find(slope) == slopes.end())
                        slopes[slope] = vector<pair<vector<int>, vector<int>>>{};
                    slopes[slope].push_back(make_pair(points[i], points[j]));
                }
            }
            int max = 0;
            for (map<pair<int, int>, vector<pair<vector<int>, vector<int>>>>::iterator
                     slope = slopes.begin();
                 slope != slopes.end(); slope++)
            {
                // lines of the same slope
                vector<set<vector<int>>> lines;
                for_each(slope->second.begin(), slope->second.end(),
                         [&](pair<vector<int>, vector<int>> &s) {
                             // s is a line segament ending with two points.
                             // Check and assign the points into the set of points on
                             // the same line.
                             // first is the line containing the first point of segament
                             // s
                             vector<set<vector<int>>>::iterator first = lines.end();
                             // second is the line containing the second point of
                             // segament s
                             vector<set<vector<int>>>::iterator second = lines.end();
                             for (vector<set<vector<int>>>::iterator it = lines.begin();
                                  it != lines.end(); it++)
                             {
                                 // it refers to the set of points on the same line
                                 if (it->find(s.first) != it->end())
                                     first = it;
                                 if (it->find(s.second) != it->end())
                                     second = it;
                             }
                             if (first == lines.end() && second == lines.end())
                             {
                                 // Segament s is a new line
                                 set<vector<int>> line;
                                 line.insert(s.first);
                                 line.insert(s.second);
                                 lines.push_back(line);
                             }
                             else if (first == lines.end())
                             {
                                 second->insert(s.first);
                             }
                             else if (second == lines.end())
                             {
                                 first->insert(s.second);
                             }
                             else if (first == second)
                             {
                                 ;
                             }
                             else
                             {
                                 set<vector<int>> line;
                                 line.insert(first->begin(), first->end());
                                 line.insert(second->begin(), second->end());
                                 lines.erase(first);
                                 lines.erase(second);
                                 lines.push_back(line);
                             }
                         });
                for_each(lines.begin(), lines.end(), [&](set<vector<int>> &l) {
                    int m = 0;
                    for_each(l.cbegin(), l.cend(),
                             [&](const vector<int> &v) { m += dup[v]; });
                    if (m > max)
                        max = m;
                });
            }
            return max;
        }

        // 150. Evaluate Reverse Polish Notation
        // Evaluate the value of an arithmetic expression in Reverse Polish Notation.
        // Valid operators are +, -, *, /. Each operand may be an integer or another
        // expression. Note: Division between two integers should truncate toward zero.
        // The given RPN expression is always valid. That means the expression would
        // always evaluate to a result and there won't be any divide by zero operation.
        // Example 1:
        // Input: ["2", "1", "+", "3", "*"]
        // Output: 9
        // Explanation: ((2 + 1) * 3) = 9
        // Example 2:
        // Input: ["4", "13", "5", "/", "+"]
        // Output: 6
        // Explanation: (4 + (13 / 5)) = 6
        // Example 3:
        // Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
        // Output: 22
        // Explanation:
        //   ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
        // = ((10 * (6 / (12 * -11))) + 17) + 5
        // = ((10 * (6 / -132)) + 17) + 5
        // = ((10 * 0) + 17) + 5
        // = (0 + 17) + 5
        // = 17 + 5
        // = 22
        int evalRPN(const vector<string> &tokens)
        {
            stack<int> q;
            for_each(tokens.cbegin(), tokens.cend(), [&](const string &t) {
                if (t == "+")
                {
                    int a = q.top();
                    q.pop();
                    int b = q.top();
                    q.pop();
                    q.push(b + a);
                }
                else if (t == "-")
                {
                    int a = q.top();
                    q.pop();
                    int b = q.top();
                    q.pop();
                    q.push(b - a);
                }
                else if (t == "*")
                {
                    int a = q.top();
                    q.pop();
                    int b = q.top();
                    q.pop();
                    q.push(b * a);
                }
                else if (t == "/")
                {
                    int a = q.top();
                    q.pop();
                    int b = q.top();
                    q.pop();
                    q.push(b / a);
                }
                else
                {
                    q.push(stoi(t));
                }
            });
            return q.top();
        }
        int evalRPN2(const vector<string> &tokens)
        {
            int n1;
            int n2;
            stack<int> nums;
            function<void(int &, int &)> pop = [&](int &m1, int &m2) {
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

        // 151. Reverse Words in a String
        // Given an input string, reverse the string word by word.
        // Example 1:
        // Input: "the sky is blue"
        // Output: "blue is sky the"
        // Example 2:
        // Input: "  hello world!  "
        // Output: "world! hello"
        // Explanation: Your reversed string should not contain leading or trailing
        // spaces. Example 3: Input: "a good   example" Output: "example good a"
        // Explanation: You need to reduce multiple spaces between two words to a single
        // space in the reversed string. Note: A word is defined as a sequence of
        // non-space characters. Input string may contain leading or trailing spaces.
        // However, your reversed string should not contain leading or trailing spaces.
        // You need to reduce multiple spaces between two words to a single space in the
        // reversed string. Follow up: For C programmers, try to solve it in-place in
        // O(1) extra space.
        string reverseWords(string s)
        {
            function<void()> compact = [&]() {
                int i = -1;
                for (int j = 0; j < (int)s.size(); j++)
                {
                    if (s[j] == ' ' && (i == -1 || s[i] == ' '))
                        continue;
                    if (++i < j)
                        s[i] = s[j];
                }
                if (i == -1 || s[i] != ' ')
                    i++;
                s.resize(i);
            };
            function<void(int, int)> reverse = [&](int i, int j) {
                while (i < j)
                    swap(s[i++], s[j--]);
            };
            compact();
            reverse(0, (int)s.size() - 1);
            int i = 0;
            int j = 0;
            while (j <= (int)s.size())
            {
                if (j == (int)s.size() || s[j] == ' ')
                {
                    reverse(i, j - 1);
                    i = j + 1;
                }
                j++;
            }
            return s;
        }
        string reverseWords2(const string &s)
        {
            string r(s);
            int i = -1;
            int j;
            for (j = 0; j < (int)r.size(); j++)
            {
                if (r[j] == ' ' && (i < 0 || r[i] == ' '))
                    continue;
                i++;
                if (i != j)
                    r[i] = r[j];
            }
            if (i >= 0 && r[i] == ' ')
                i--;
            r.resize(i + 1);
            i = 0;
            while (i < (int)r.size())
            {
                if (r[i] != ' ')
                {
                    j = i;
                    while (j < (int)r.size() && r[j] != ' ')
                        j++;
                    int k = j;
                    j--;
                    while (i < j)
                    {
                        swap(r[i], r[j]);
                        i++;
                        j--;
                    }
                    i = k;
                }
                i++;
            }
            i = 0;
            j = (int)r.size() - 1;
            while (i < j)
            {
                swap(r[i], r[j]);
                i++;
                j--;
            }
            return r;
        }
        void reverseWords3(string &s)
        {
            if (s.empty())
                return;
            // step 1: remove extra spaces
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
            // step 2: reverse words
            function<void(int, int)> reverse = [&](int b, int e) {
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

        // Reverse Words in a String III
        // Given a string, you need to reverse the order of characters in each word
        // within a sentence while still preserving whitespace and initial word order.
        // Example 1:
        // Input: "Let's take LeetCode contest"
        // Output: "s'teL ekat edoCteeL tsetnoc"
        // Note: In the string, each word is separated by single space and there will
        // not be any extra space in the string.
        string reverseWordsIII(string s)
        {
            int i = 0;
            while (i < (int)s.size())
            {
                if (s[i] != ' ')
                {
                    int j = i;
                    while (j < (int)s.size() && s[j] != ' ')
                        j++;
                    int k = j--;
                    while (i < j)
                        swap(s[i++], s[j--]);
                    i = k;
                }
                i++;
            }
            return s;
        }

        // 152. Maximum Product Subarray
        // Given an integer array nums, find the contiguous subarray within an array
        // (containing at least one number) which has the largest product.
        // Example 1:
        // Input: [2,3,-2,4]
        // Output: 6
        // Explanation: [2,3] has the largest product 6.
        // Example 2:
        // Input: [-2,0,-1]
        // Output: 0
        // Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
        int maxProduct(const vector<int> &nums)
        {
            long long maxProd = LLONG_MIN;
            long long maxNeg = LLONG_MIN;
            long long p = 1;
            for (size_t i = 0; i < nums.size(); i++)
            {
                p *= nums[i];
                if (p < 0)
                {
                    if (maxNeg == LLONG_MIN)
                    {
                        maxProd = max(maxProd, p);
                        maxNeg = p;
                    }
                    else
                    {
                        maxProd = max(maxProd, p / maxNeg);
                        maxNeg = max(maxNeg, p);
                    }
                }
                else
                {
                    maxProd = max(maxProd, p);
                    if (p == 0)
                    {
                        p = 1;
                        maxNeg = LLONG_MIN;
                    }
                }
            }
            return maxProd;
        }
        int maxProduct2(const vector<int> &nums)
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
        int maxProduct3(const vector<int> &nums)
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
                    // if (product[i] > maxProd) {
                    //     cout << "prod[" << i << ".." << i + l - 1 << "] = " <<
                    //     product[i] << endl;
                    // }
                    maxProd = max(product[i], maxProd);
                }
            }
            return (int)maxProd;
        }

        // 153. Find Minimum in Rotated Sorted Array
        // Suppose an array sorted in ascending order is rotated at some pivot unknown
        // to you beforehand. (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
        // Find the minimum element. You may assume no duplicate exists in the array.
        // Example 1:
        // Input: [3,4,5,1,2]
        // Output: 1
        // Example 2:
        // Input: [4,5,6,7,0,1,2]
        // Output: 0
        int findMin(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int e = nums[h];
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (m < h)
                {
                    if (nums[m] > e)
                        l = m + 1;
                    else
                        h = m;
                }
                else
                {
                    return nums[m];
                }
            }
            throw runtime_error("not found");
        }
        int findMin2(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int e = nums[h];
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > e)
                    l = m + 1;
                else
                    h = m;
            }
            return nums[l];
        }
        int findMin3(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int e = nums[h];
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > e)
                    l = m;
                else
                    h = m;
            }
            if (l <= h)
                return min(nums[l], nums[h]);
            throw runtime_error("not found");
        }
        int findMin4(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (nums[m] > nums[h])
                {
                    if (m + 1 == h)
                        m = h;
                    if (m == h)
                        break;
                    l = m;
                }
                else
                {
                    if (l == m)
                        break;
                    h = m;
                }
            }
            return nums[m];
        }
        int findMin5(const vector<int> &nums)
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
                        h = m - 1;
                    else
                        l = m + 1;
                }
                else if (nums[l] > nums[m])
                {
                    h = m;
                }
                else
                {
                    if (nums[m] < nums[h])
                        h = m;
                    else if (nums[m] > nums[h])
                        l = m + 1;
                    else
                        break;
                }
            }
            return nums[m];
        }

        // 154. Find Minimum in Rotated Sorted Array II
        // Suppose an array sorted in ascending order is rotated at some pivot unknown
        // to you beforehand. (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
        // Find the minimum element. The array may contain duplicates.
        // Example 1:
        // Input: [1,3,5]
        // Output: 1
        // Example 2:
        // Input: [2,2,2,0,1]
        // Output: 0
        // Note: This is a follow up problem to Find Minimum in Rotated Sorted Array.
        // Would allow duplicates affect the run-time complexity? How and why?
        int findMinII(const vector<int> &nums)
        {
            int n = (int)nums.size();
            int e = nums[n - 1];
            function<int(int, int)> find = [&](int l, int h) -> int {
                int m;
                while (l < h)
                {
                    m = l + ((h - l) >> 1);
                    if (nums[m] < e)
                        h = m;
                    else if (nums[m] > e)
                        l = m + 1;
                    else
                        break;
                }
                if (l == h)
                    return nums[l];
                else if (l == m) // e.g. [1, 1]
                    return find(m + 1, h);
                else
                    return min(find(l, m - 1), find(m + 1, h));
            };
            return find(0, n - 1);
        }
        int findMinII2(const vector<int> &nums)
        {
            function<int(int, int)> find = [&](int l, int h) -> int {
                if (l == h)
                    return nums[l];
                if (l + 1 == h)
                    return min(nums[l], nums[h]);
                int m = l + ((h - l) >> 1);
                if (nums[m] > nums[h])
                    return find(m + 1, h);
                if (nums[m] < nums[h])
                    return find(l, m);
                if (nums[l] > nums[m])
                    return find(l, m);
                if (nums[l] < nums[m])
                    return find(l, m);
                return min(find(l, m - 1), find(m + 1, h));
            };
            return find(0, nums.size() - 1);
        }

        // 155. Min Stack
        // Design a stack that supports push, pop, top, and retrieving the minimum
        // element in constant time.
        // push(x) -- Push element x onto stack.
        // pop() -- Removes the element on top of the stack.
        // top() -- Get the top element.
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
            stack<int> q;
            stack<int> m;

        public:
            /** initialize your data structure here. */
            MinStack() {}
            void push(int x)
            {
                q.push(x);
                if (m.empty())
                    m.push(x);
                else
                    m.push(min(m.top(), x));
            }
            void pop()
            {
                q.pop();
                m.pop();
            }
            int top() { return q.top(); }
            int getMin() { return m.top(); }
        };

        // 160. Intersection of Two Linked Lists
        // Write a program to find the node at which the intersection of two singly
        // linked lists begins. For example, the following two linked lists: begin to
        // intersect at node c1.
        // Example 1:
        // Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5],
        // skipA = 2, skipB = 3
        // Output: Reference of the node with value = 8
        // Input Explanation: The intersected node's value is 8 (note that this must not
        // be 0 if the two lists intersect). From the head of A, it reads as
        // [4,1,8,4,5]. From the head of B, it reads as [5,0,1,8,4,5]. There are 2 nodes
        // before the intersected node in A; There are 3 nodes before the intersected
        // node in B. Example 2: Input: intersectVal = 2, listA = [0,9,1,2,4], listB =
        // [3,2,4], skipA = 3, skipB = 1 Output: Reference of the node with value = 2
        // Input Explanation: The intersected node's value is 2 (note that this must not
        // be 0 if the two lists intersect). From the head of A, it reads as
        // [0,9,1,2,4]. From the head of B, it reads as [3,2,4]. There are 3 nodes
        // before the intersected node in A; There are 1 node before the intersected
        // node in B. Example 3: Input: intersectVal = 0, listA = [2,6,4], listB =
        // [1,5], skipA = 3, skipB = 2 Output: null Input Explanation: From the head of
        // A, it reads as [2,6,4]. From the head of B, it reads as [1,5]. Since the two
        // lists do not intersect, intersectVal must be 0, while skipA and skipB can be
        // arbitrary values. Explanation: The two lists do not intersect, so return
        // null. Notes: If the two linked lists have no intersection at all, return
        // null. The linked lists must retain their original structure after the
        // function returns. You may assume there are no cycles anywhere in the entire
        // linked structure. Your code should preferably run in O(n) time and use only
        // O(1) memory.
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
        {
            ListNode *a = headA;
            ListNode *b = headB;
            while (a != nullptr && b != nullptr && a != b)
            {
                a = a->next;
                b = b->next;
                if (a == nullptr && b == nullptr)
                    break;
                if (a == nullptr)
                    a = headB;
                if (b == nullptr)
                    b = headA;
            }
            return (a == nullptr || b == nullptr) ? nullptr : a;
        }
        ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB)
        {
            ListNode *a = headA;
            ListNode *b = headB;
            while (a != nullptr && b != nullptr && a != b)
            {
                a = a->next;
                b = b->next;
                if (a == b)
                    return a;
                if (a == nullptr)
                    a = headB;
                if (b == nullptr)
                    b = headA;
            }
            return a == b ? a : nullptr;
        }
        ListNode *getIntersectionNode3(ListNode *headA, ListNode *headB)
        {
            function<int(ListNode *)> getLength = [&](ListNode *h) -> int {
                int i = 0;
                while (h != nullptr)
                {
                    i++;
                    h = h->next;
                }
                return i;
            };
            function<ListNode *(ListNode *, int)> advance = [&](ListNode *h,
                                                                int n) -> ListNode * {
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

        // 162. Find Peak Element
        // A peak element is an element that is greater than its neighbors. Given an
        // input array nums, where nums[i] != nums[i+1], find a peak element and return
        // its index. The array may contain multiple peaks, in that case return the
        // index to any one of the peaks is fine. You may imagine that
        // nums[-1] = nums[n] = -infinity.
        // Example 1:
        // Input: nums = [1,2,3,1]
        // Output: 2
        // Explanation: 3 is a peak element and your function should return the index
        // number 2. Example 2: Input: nums = [1,2,1,3,5,6,4] Output: 1 or 5
        // Explanation: Your function can return either index number 1 where the peak
        // element is 2, or index number 5 where the peak element is 6. Note: Your
        // solution should be in logarithmic complexity.
        int findPeakElement(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l <= h)
            {
                int m = l + ((h - l) >> 1);
                if (m < h)
                {
                    if (nums[m] > nums[m + 1])
                        h = m;
                    else
                        l = m + 1;
                }
                else
                {
                    return m;
                }
            }
            throw runtime_error("not found");
        }
        int findPeakElement2(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > nums[m + 1])
                    h = m;
                else
                    l = m + 1;
            }
            return l == h ? l : -1;
        }
        int findPeakElement3(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l + 1 < h)
            {
                int m = l + ((h - l) >> 1);
                if (nums[m] > nums[m + 1])
                    h = m;
                else
                    l = m;
            }
            if (l <= h)
            {
                if (nums[l] <= nums[h])
                    return h;
                else
                    return l;
            }
            throw runtime_error("not found");
        }
        int findPeakElement4(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                if (m == 0)
                {
                    if (nums[m] >= nums[m + 1])
                        return m;
                    l = m + 1;
                }
                else if (m == (int)nums.size() - 1)
                {
                    if (nums[m - 1] <= nums[m])
                        return m;
                    h = m - 1;
                }
                else if (nums[m - 1] <= nums[m] && nums[m] >= nums[m + 1])
                {
                    return m;
                }
                else if (nums[m - 1] < nums[m + 1])
                {
                    l = m + 1;
                }
                else
                {
                    h = m - 1;
                }
            }
            return l == h ? l : -1;
        }
        int findPeakElement5(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            if (nums.size() == 1)
                return 0;
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (m == 0)
                {
                    if (nums[m] >= nums[m + 1])
                        break;
                    l = m + 1;
                }
                else if (m == (int)nums.size() - 1)
                {
                    if (nums[m - 1] <= nums[m])
                        break;
                    h = m - 1;
                }
                else if (nums[m - 1] <= nums[m] && nums[m] >= nums[m + 1])
                {
                    break;
                }
                else if (nums[m - 1] < nums[m + 1])
                {
                    l = m + 1;
                }
                else
                {
                    h = m - 1;
                }
            }
            return m;
        }
        int findPeakElement6(const vector<int> &nums)
        {
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h)
            {
                m = l + ((h - l) >> 1);
                if (m == h)
                {
                    break;
                }
                else if (l == m)
                {
                    if (nums[m] <= nums[m + 1])
                        l = m + 1;
                    else
                        break;
                }
                else
                {
                    if (nums[m - 1] < nums[m] && nums[m] > nums[m + 1])
                        break;
                    else if (nums[m - 1] <= nums[m + 1])
                        l = m + 1;
                    else
                        h = m - 1;
                }
            }
            return m;
        }

        // 164. Maximum Gap
        // Given an unsorted array, find the maximum difference between the successive
        // elements in its sorted form. Return 0 if the array contains less than 2
        // elements. Example 1: Input: [3,6,9,1] Output: 3 Explanation: The sorted form
        // of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum
        // difference 3. Example 2: Input: [10] Output: 0 Explanation: The array
        // contains less than 2 elements, therefore return 0. Note: You may assume all
        // elements in the array are non-negative integers and fit in the 32-bit signed
        // integer range. Try to solve it in linear time/space. Approach 3: Buckets and
        // The Pigeonhole Principle Intuition Sorting an entire array can be costly. At
        // worst, it requires comparing each element with every other element. What if
        // we didn't need to compare all pairs of elements? That would be possible if we
        // could somehow divide the elements into representative groups, or rather,
        // buckets. Then we would only need to compare these buckets. Digression: The
        // Pigeonhole Principle The Pigeonhole Principle states that if n items are put
        // into m containers, with n > m, then at least one container must contain more
        // than one item. Suppose for each of the n elements in our array, there was a
        // bucket. Then each element would occupy one bucket. Now what if we reduced,
        // the number of buckets? Some buckets would have to accommodate more than one
        // element. Now let's talk about the gaps between the elements. Let's take the
        // best case, where all elements of the array are sorted and have a uniform gap
        // between them. This means every adjacent pair of elements differ by the same
        // constant value. So for n elements of the array, there are n − 1 gaps, each of
        // width, say, t. It is trivial to deduce that t = (max − min) / (n − 1) (where
        // max and min are the minimum and maximum elements of the array). This width is
        // the maximal width/gap between two adjacent elements in the array; precisely
        // the quantity we are looking for! One can safely argue that this value of t,
        // is in fact, the smallest value that t can ever accomplish of any array with
        // the same number of elements (i.e. n) and the same range (i.e. (max - min)).
        // To test this fact, you can start with a uniform width array (as described
        // above) and try to reduce the gap between any two adjacent elements. If you
        // reduce the gap between arr[i − 1] and arr[i] to some value t - p, then you
        // will notice that the gap between arr[i] and arr[i + 1] would have increased
        // to t + p. Hence the maximum attainable gap would have become t + p from t.
        // Thus the value of the maximum gap t can only increase. Buckets! Coming back
        // to our problem, we have already established by application of the Pigeonhole
        // Principle, that if we used buckets instead of individual elements as our base
        // for comparison, the number of comparisons would reduce if we could
        // accommodate more than one element in a single bucket. That does not
        // immediately solve the problem though. What if we had to compare elements
        // within a bucket? We would end up no better. So the current motivation
        // remains: somehow, if we only had to compare among the buckets, and not the
        // elements within the buckets, we would be good. It would also solve our
        // sorting problem: we would just distribute the elements to the right buckets.
        // Since the buckets can be already ordered, and we only compare among buckets,
        // we wouldn't have to compare all elements to sort them! But if we only had
        // buckets to compare, we would have to ensure, that the gap between the buckets
        // itself represent the maximal gap in the input array. How do we go about doing
        // that? We could do that just by setting the buckets to be smaller than t =
        // (max - min) / (n - 1) (as described above). Since the gaps (between elements)
        // within the same bucket would only be <=t, we could deduce that the maximal
        // gap would indeed occur only between two adjacent buckets. Hence by setting
        // bucket size b to be 1 < b <= (max − min) / (n − 1), we can ensure that at
        // least one of the gaps between adjacent buckets would serve as the maximal
        // gap. Clarifications A few clarifications are in order: Would the buckets be
        // of uniform size? Yes. Each of them would be of the same size b. But, then
        // wouldn't the gap between them be uniform/constant as well? Yes it would be.
        // The gap between them would be 1 integer unit wide. That means a two adjacent
        // buckets of size 3 could hold integers with values, say, 3 - 6 and 7 - 9. We
        // avoid overlapping buckets. Then what are you talking about when you say the
        // gap between two adjacent buckets could be the maximal gap? When we are
        // talking about the size of a bucket, we are talking about its holding
        // capacity. That is the range of values the bucket can represent (or hold).
        // However the actual extent of the bucket are determined by the values of the
        // maximum and minimum element a bucket holds. For example a bucket of size 5
        // could have a capacity to hold values between 6 - 10. However, if it only
        // holds the elements 7,8 and 9, then its actual extent is only (9 - 7) + 1 = 3
        // which is not the same as the capacity of the bucket. Then how do you compare
        // adjacent buckets? We do that by comparing their extents. Thus we compare the
        // minimum element of the next bucket to the maximum element of the current
        // bucket. For example: if we have two buckets of size 5 each, holding elements
        // [1, 2, 3] and [9, 10] respectively, then the gap between the buckets would
        // essentially refer to the value 9 - 3 = 6 (which is larger than the size of
        // either bucket).
        // But then aren't we comparing elements again?! We are, yes! But only compare
        // about twice the elements as the number of buckets (i.e. the minimum and
        // maximum elements of each bucket). If you followed the above, you would
        // realize that this amount is certainly less than the actual number of elements
        // in the array, given a suitable bucket size was chosen. Algorithm We choose a
        // bucket size b such that 1 < b <= (max − min) / (n − 1). Let's just choose b
        // = floor((max − min) / (n − 1)). Thus all the n elements would be divided
        // among k = ceil((max − min) / b) buckets. Hence the i-th bucket would hold the
        // range of values: [min + (i − 1) ∗ b, min + i ∗ b) (1-based indexing). It is
        // trivial to calculate the index of the bucket to which a particular element
        // belongs. That is given by floor((num - min) / b) (0-based indexing) where
        // num is the element in question. Once all n elements have been
        // distributed, we compare k − 1 adjacent bucket pairs to find the maximum gap.
        // Complexity Analysis
        // Time complexity: O(n + b) ~= O(n).
        // Distributing the elements of the array takes one linear pass (i.e. O(n)
        // complexity). Finding the maximum gap among the buckets takes a linear pass
        // over the bucket storage (i.e. O(b) complexity). Hence overall process takes
        // linear runtime. Space complexity: O(2 * b) ~= O(b) extra space. Each bucket
        // stores a maximum and a minimum element. Hence extra space linear to the
        // number of buckets is required.
        int maximumGap(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            pair<vector<int>::const_iterator, vector<int>::const_iterator> p =
                minmax_element(nums.cbegin(), nums.cend());
            int l = *p.first;
            int h = *p.second;
            int bucketSize = max(1, (h - l) / ((int)nums.size() - 1));
            int bucketNum = (h - l) / bucketSize + 1;
            vector<pair<int, int>> buckets(bucketNum, make_pair(-1, -1));
            for (int n : nums)
            {
                int i = (n - l) / bucketSize;
                buckets[i].first =
                    buckets[i].first == -1 ? n : min(buckets[i].first, n);
                buckets[i].second =
                    buckets[i].second == -1 ? n : max(buckets[i].second, n);
            }
            int preMax = l;
            int gap = 0;
            for (const auto &p : buckets)
            {
                if (p.first == -1)
                    continue;
                gap = max(gap, p.first - preMax);
                preMax = p.second;
            }
            return gap;
        }
        int maximumGap2(const vector<int> &nums)
        {
            if (nums.size() < 2)
                return 0;
            vector<int> v(nums);
            sort(v.begin(), v.end());
            int gap = 0;
            for (size_t i = 1; i < v.size(); i++)
            {
                if (v[i - 1] + 1 < v[i])
                    gap = max(gap, v[i] - v[i - 1]);
            }
            return gap;
        }

        // 165. Compare Version Numbers
        // Compare two version numbers version1 and version2. If version1 > version2
        // return 1; if version1 < version2 return -1; otherwise return 0. You may assume
        // that the version strings are non-empty and contain only digits and the .
        // character. The . character does not represent a decimal point and is used to
        // separate number sequences. For instance, 2.5 is not "two and a half" or "half
        // way to version three", it is the fifth second-level revision of the second
        // first-level revision. You may assume the default revision number for each
        // level of a version number to be 0. For example, version number 3.4 has a
        // revision number of 3 and 4 for its first and second level revision number.
        // Its third and fourth level revision number are both 0. Example 1: Input:
        // version1 = "0.1", version2 = "1.1" Output: -1 Example 2: Input: version1 =
        // "1.0.1", version2 = "1" Output: 1 Example 3: Input: version1 = "7.5.2.4",
        // version2 = "7.5.3" Output: -1 Example 4: Input: version1 = "1.01", version2 =
        // "1.001" Output: 0 Explanation: Ignoring leading zeroes, both “01” and “001"
        // represent the same number “1” Example 5: Input: version1 = "1.0", version2 =
        // "1.0.0" Output: 0 Explanation: The first version number does not have a third
        // level revision number, which means its third level revision number is default
        // to "0" Note: Version strings are composed of numeric strings separated by
        // dots . and this numeric strings may have leading zeroes. Version strings do
        // not start or end with dots, and they will not be two consecutive dots.
        int compareVersion(const string &version1, const string &version2)
        {
            function<int(const string &, int)> nextDot = [&](const string &s,
                                                             int i) -> int {
                while (i < (int)s.size() && s[i] != '.')
                    i++;
                return i;
            };
            function<int(int, int, int, int)> comp = [&](int i1, int i2, int j1,
                                                         int j2) -> int {
                while (i1 < i2 && version1[i1] == '0')
                    i1++;
                while (j1 < j2 && version2[j1] == '0')
                    j1++;
                if (i2 - i1 > j2 - j1)
                    return 1;
                if (i2 - i1 < j2 - j1)
                    return -1;
                while (i1 <= i2 && j1 <= j2)
                {
                    if (version1[i1] > version2[j1])
                        return 1;
                    if (version1[i1] < version2[j1])
                        return -1;
                    i1++;
                    j1++;
                }
                return 0;
            };
            function<bool(const string &, int)> allZeros = [&](const string &s,
                                                               int i) -> bool {
                while (i < (int)s.size())
                {
                    if (s[i] != '0' && s[i] != '.')
                        return false;
                    i++;
                }
                return true;
            };
            int i1 = 0;
            int j1 = 0;
            while (i1 < (int)version1.size() && j1 < (int)version2.size())
            {
                int i2 = nextDot(version1, i1);
                int j2 = nextDot(version2, j1);
                int c = comp(i1, i2 - 1, j1, j2 - 1);
                if (c != 0)
                    return c;
                i1 = i2 + 1;
                j1 = j2 + 1;
            }
            if (i1 >= (int)version1.size())
                return allZeros(version2, j1) ? 0 : -1;
            if (j1 >= (int)version2.size())
                return allZeros(version1, i1) ? 0 : 1;
            return 0;
        }
        int compareVersion2(const string &version1, const string &version2)
        {
            function<int(const string &, size_t &)> version = [&](const string &str,
                                                                  size_t &i) -> int {
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

        // 166. Fraction to Recurring Decimal
        // Given two integers representing the numerator and denominator of a fraction,
        // return the fraction in string format. If the fractional part is repeating,
        // enclose the repeating part in parentheses.
        // Example 1:
        // Input: numerator = 1, denominator = 2
        // Output: "0.5"
        // Example 2:
        // Input: numerator = 2, denominator = 1
        // Output: "2"
        // Example 3:
        // Input: numerator = 2, denominator = 3
        // Output: "0.(6)"
        string fractionToDecimal(int numerator, int denominator)
        {
            string integer;
            string fraction;
            long long n = numerator;
            long long d = denominator;
            bool negative = false;
            if (n < 0)
            {
                negative = !negative;
                n = -n;
            }
            if (d < 0)
            {
                negative = !negative;
                d = -d;
            }
            long long i = n / d;
            n = n % d;
            if (i == 0)
            {
                integer = "0";
            }
            else
            {
                while (i > 0)
                {
                    long long c = i % 10;
                    i = i / 10;
                    integer.insert(0, 1, '0' + c);
                }
            }
            map<long long, int> visited;
            while (n != 0 && visited.find(n) == visited.end())
            {
                visited[n] = (int)fraction.size();
                n *= 10;
                long long c = n / d;
                n %= d;
                fraction.append(1, '0' + c);
            }
            if (visited.find(n) != visited.end())
            {
                fraction.insert(visited[n], 1, '(');
                fraction.append(1, ')');
            }
            string decimal;
            if (fraction.empty() && integer.compare("0") == 0)
                decimal.append(1, '0');
            else
            {
                if (negative)
                    decimal.append(1, '-');
                decimal.append(integer);
                if (!fraction.empty())
                {
                    decimal.append(1, '.');
                    decimal.append(fraction);
                }
            }
            return decimal;
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
        vector<int> twoSum(const vector<int> &numbers, int target)
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

        // 168. Excel Sheet Column Title
        // Given a positive integer, return its corresponding column title as appear in
        // an Excel sheet. For example:
        //     1 -> A
        //     2 -> B
        //     3 -> C
        //     ...
        //     26 -> Z
        //     27 -> AA
        //     28 -> AB
        //     ...
        // Example 1:
        // Input: 1
        // Output: "A"
        // Example 2:
        // Input: 28
        // Output: "AB"
        // Example 3:
        // Input: 701
        // Output: "ZY"
        string convertToTitle(int n)
        {
            string s;
            while (n > 0)
            {
                int c = n % 26;
                n /= 26;
                if (c == 0)
                {
                    c = 26;
                    n--;
                }
                s.insert(0, 1, 'A' + c - 1);
            }
            return s;
        }

        // 169. Majority Element
        // Given an array of size n, find the majority element. The majority element is
        // the element that appears more than floor(n/2) times. You may assume that the
        // array is non-empty and the majority element always exist in the array.
        // Example 1:
        // Input: [3,2,3]
        // Output: 3
        // Example 2:
        // Input: [2,2,1,1,1,2,2]
        // Output: 2
        // Approach 6: Boyer-Moore Voting Algorithm
        // Intuition
        // If we had some way of counting instances of the majority element as +1 and
        // instances of any other element as −1, summing them would make it obvious that
        // the majority element is indeed the majority element.
        // Algorithm
        // Essentially, what Boyer-Moore does is look for a suffix suf of nums where
        // suf[0] is the majority element in that suffix. To do this, we maintain a
        // count, which is incremented whenever we see an instance of our current
        // candidate for majority element and decremented whenever we see anything else.
        // Whenever count equals 0, we effectively forget about everything in nums up to
        // the current index and consider the current number as the candidate for
        // majority element. It is not immediately obvious why we can get away with
        // forgetting prefixes of nums - consider the following examples (pipes are
        // inserted to separate runs of nonzero count). [7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5,
        // 7, 7 | 7, 7, 7, 7] Here, the 7 at index 0 is selected to be the first
        // candidate for majority element. count will eventually reach 0 after index 5
        // is processed, so the 5 at index 6 will be the next candidate. In this case, 7
        // is the true majority element, so by disregarding this prefix, we are ignoring
        // an equal number of majority and minority elements - therefore, 7 will still
        // be the majority element in the suffix formed by throwing away the first
        // prefix. [7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5, 7, 7 | 5, 5, 5, 5] Now, the majority
        // element is 5 (we changed the last run of the array from 7s to 5s), but our
        // first candidate is still 7. In this case, our candidate is not the true
        // majority element, but we still cannot discard more majority elements than
        // minority elements (this would imply that count could reach -1 before we
        // reassign candidate, which is obviously false). Therefore, given that it is
        // impossible (in both cases) to discard more majority elements than minority
        // elements, we are safe in discarding the prefix and attempting to recursively
        // solve the majority element problem for the suffix. Eventually, a suffix will
        // be found for which count does not hit 0, and the majority element of that
        // suffix will necessarily be the same as the majority element of the overall
        // array. Complexity Analysis Time complexity : O(n) Boyer-Moore performs
        // constant work exactly n times, so the algorithm runs in linear time. Space
        // complexity : O(1) Boyer-Moore allocates only constant additional memory.
        int majorityElement(const vector<int> &nums)
        {
            int m;
            int c = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (c == 0)
                {
                    m = nums[i];
                    c++;
                }
                else if (nums[i] == m)
                {
                    c++;
                }
                else
                {
                    c--;
                }
            }
            return m;
        }
        int majorityElement2(const vector<int> &nums)
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

        // 171. Excel Sheet Column Number
        // Given a column title as appear in an Excel sheet, return its corresponding
        // column number. For example:
        //     A -> 1
        //     B -> 2
        //     C -> 3
        //     ...
        //     Z -> 26
        //     AA -> 27
        //     AB -> 28
        //     ...
        // Example 1:
        // Input: "A"
        // Output: 1
        // Example 2:
        // Input: "AB"
        // Output: 28
        // Example 3:
        // Input: "ZY"
        // Output: 701
        int titleToNumber(const string &s)
        {
            long long r = 0;
            for (size_t i = 0; i < s.size(); i++)
                r = r * 26 + s[i] - 'A' + 1;
            return (int)r;
        }

        // 172. Factorial Trailing Zeroes
        // Given an integer n, return the number of trailing zeroes in n!.
        // Example 1:
        // Input: 3
        // Output: 0
        // Explanation: 3! = 6, no trailing zero.
        // Example 2:
        // Input: 5
        // Output: 1
        // Explanation: 5! = 120, one trailing zero.
        // Note: Your solution should be in logarithmic time complexity.
        // n! = 1 * 2 * 3 * 4 * 5 * ... * 10 * ... * 15 * ... * n
        //    = 2^x * 5^y * z
        // Usually x >= y. So just need to count occurrence of 5.
        //   n:      1, 2, 3, 4, 5, 6, ..., 2*5, ..., 3*5, ..., n1*5, ..., n
        // n/5 = n1:             1,    ..., 2,   ..., 3,   ..., n2*5, ..., n1
        // n1/5 = n2:                                   1, ..., n3*5, ..., n2
        // n2/5 = n3: ...
        // ...
        int trailingZeroes(int n)
        {
            int c = 0;
            while (n >= 5)
            {
                n /= 5;
                c += n;
            }
            return c;
        }

        // 173. Binary Search Tree Iterator
        // Implement an iterator over a binary search tree (BST). Your iterator will be
        // initialized with the root node of a BST.
        // Calling next() will return the next smallest number in the BST.
        // Example:
        // BSTIterator iterator = new BSTIterator(root);
        // iterator.next();    // return 3
        // iterator.next();    // return 7
        // iterator.hasNext(); // return true
        // iterator.next();    // return 9
        // iterator.hasNext(); // return true
        // iterator.next();    // return 15
        // iterator.hasNext(); // return true
        // iterator.next();    // return 20
        // iterator.hasNext(); // return false
        // Note:
        // next() and hasNext() should run in average O(1) time and uses O(h) memory,
        // where h is the height of the tree. You may assume that next() call will
        // always be valid, that is, there will be at least a next smallest number in
        // the BST when next() is called.
        class BSTIterator
        {
        private:
            TreeNode *_node;
            stack<TreeNode *> _s;

        public:
            BSTIterator(TreeNode *root) { _node = root; }
            /** @return the next smallest number */
            int next()
            {
                int v;
                while (!_s.empty() || _node != nullptr)
                {
                    if (_node != nullptr)
                    {
                        _s.push(_node);
                        _node = _node->left;
                    }
                    else
                    {
                        v = _s.top()->val;
                        _node = _s.top()->right;
                        _s.pop();
                        break;
                    }
                }
                return v;
            }
            int next2()
            {
                while (_node != nullptr)
                {
                    _s.push(_node);
                    _node = _node->left;
                }
                TreeNode *t = _s.top();
                _s.pop();
                _node = t->right;
                return t->val;
            }

            /** @return whether we have a next smallest number */
            bool hasNext() { return !_s.empty() || _node != nullptr; }
        };

        // 174. Dungeon Game
        // The demons had captured the princess (P) and imprisoned her in the
        // bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid
        // out in a 2D grid. Our valiant knight (K) was initially positioned in the
        // top-left room and must fight his way through the dungeon to rescue the
        // princess. The knight has an initial health point represented by a positive
        // integer. If at any point his health point drops to 0 or below, he dies
        // immediately. Some of the rooms are guarded by demons, so the knight loses
        // health (negative integers) upon entering these rooms; other rooms are either
        // empty (0's) or contain magic orbs that increase the knight's health (positive
        // integers). In order to reach the princess as quickly as possible, the knight
        // decides to move only rightward or downward in each step. Write a function to
        // determine the knight's minimum initial health so that he is able to rescue
        // the princess. For example, given the dungeon below, the initial health of the
        // knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT ->
        // DOWN -> DOWN. -2 (K) 	-3 	3 -5 	-10 	1 10 	30 	-5 (P)
        // Note: The knight's health has no upper bound. Any room can contain threats or
        // power-ups, even the first room the knight enters and the bottom-right room
        // where the princess is imprisoned.
        int calculateMinimumHP(const vector<vector<int>> &dungeon)
        {
            int m = dungeon.size();
            int n = dungeon[0].size();
            vector<int> health(n, 0);
            for (int i = m - 1; i >= 0; i--)
            {
                for (int j = n - 1; j >= 0; j--)
                {
                    if (i == m - 1)
                    {
                        if (j == n - 1)
                            health[j] = 1 + (dungeon[i][j] >= 0 ? 0 : -dungeon[i][j]);
                        else
                            health[j] = dungeon[i][j] >= health[j + 1]
                                            ? 1
                                            : health[j + 1] - dungeon[i][j];
                    }
                    else
                    {
                        if (j == n - 1)
                            health[j] = dungeon[i][j] >= health[j]
                                            ? 1
                                            : health[j] - dungeon[i][j];
                        else
                        {
                            int m = min(health[j], health[j + 1]);
                            health[j] = dungeon[i][j] > m ? 1 : m - dungeon[i][j];
                        }
                    }
                }
                // for (int j = 0; j < n; j++) {
                //     cout << "  " << health[j];
                // }
                // cout << endl;
            }
            return health[0];
        }

        // 175. Combine Two Tables
        // SQL Schema
        // Table: Person
        // +-------------+---------+
        // | Column Name | Type    |
        // +-------------+---------+
        // | PersonId    | int     |
        // | FirstName   | varchar |
        // | LastName    | varchar |
        // +-------------+---------+
        // PersonId is the primary key column for this table.
        // Table: Address
        // +-------------+---------+
        // | Column Name | Type    |
        // +-------------+---------+
        // | AddressId   | int     |
        // | PersonId    | int     |
        // | City        | varchar |
        // | State       | varchar |
        // +-------------+---------+
        // AddressId is the primary key column for this table.
        // Write a SQL query for a report that provides the following information for
        // each person in the Person table, regardless if there is an address for each
        // of those people:
        // FirstName, LastName, City, State
        // # Write your MySQL query statement below
        // SELECT FirstName, LastName, City, State
        // FROM Person LEFT JOIN Address ON Person.PersonId = Address.PersonId

        // 179. Largest Number
        // Given a list of non negative integers, arrange them such that they form the
        // largest number. Example 1: Input: [10,2] Output: "210" Example 2: Input:
        // [3,30,34,5,9] Output: "9534330" Note: The result may be very large, so you
        // need to return a string instead of an integer.
        string largestNumber(const vector<int> &nums)
        {
            vector<string> s;
            s.resize(nums.size());
            transform(nums.begin(), nums.end(), s.begin(),
                      [&](int i) { return std::to_string(i); });
            sort(s.begin(), s.end(), [&](const string &a, const string &b) -> bool {
                string ab = a + b;
                string ba = b + a;
                for (size_t i = 0; i < ab.size(); i++)
                {
                    if (ab[i] > ba[i])
                        return true;
                    else if (ab[i] < ba[i])
                        return false;
                }
                return false;
            });
            if (s[0] == "0")
                return "0";
            ostringstream ss;
            for_each(s.cbegin(), s.cend(), [&](const string &i) { ss << i; });
            return ss.str();
        }
        string largestNumber2(const vector<int> &nums)
        {
            vector<string> strs;
            strs.resize(nums.size());
            transform(nums.begin(), nums.end(), strs.begin(), [&](int i) {
                ostringstream oss;
                oss << i;
                return oss.str();
            });
            sort(strs.begin(), strs.end(), [&](const string &str1, const string &str2) {
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
                for_each(strs.begin(), strs.end(),
                         [&](const string &str) { result.append(str); });
            }
            return result;
        }

        // 187. Repeated DNA Sequences
        // All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
        // for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to
        // identify repeated sequences within the DNA. Write a function to find all the
        // 10-letter-long sequences (substrings) that occur more than once in a DNA
        // molecule. Example: Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT" Output:
        // ["AAAAACCCCC", "CCCCCAAAAA"]
        // A is 0x41 = 01000001,
        // C is 0x43 = 01000011,
        // G is 0x47 = 01000111,
        // T is 0x54 = 01000100.
        // Using bit 3 and 2 to encode each one
        vector<string> findRepeatedDnaSequences(const string &s)
        {
            vector<string> result;
            map<int, int> m;
            int t = 0;
            for (size_t i = 0; i < s.size(); i++)
            {
                t = ((t << 2) | (s[i] >> 1 & 0x3)) & 0xFFFFF;
                if (i >= 9)
                {
                    if (m.find(t) == m.end())
                        m[t] = 1;
                    else
                    {
                        if (m[t] == 1)
                            result.push_back(s.substr(i - 9, 10));
                        m[t]++;
                    }
                }
            }
            return result;
        }
        vector<string> findRepeatedDnaSequences2(const string &s)
        {
            vector<string> result;
            for (size_t i = 0; i + 10 < s.size(); i++)
            {
                string t = s.substr(i, 10);
                if (find(result.cbegin(), result.cend(), t) == result.cend())
                {
                    size_t j = i + 1;
                    int stop = false;
                    while (!stop && j + 10 <= s.size())
                    {
                        if (s[i] == s[j])
                        {
                            size_t k = 1;
                            while (k < 10 && s[i + k] == s[j + k])
                                k++;
                            if (k == 10)
                            {
                                result.push_back(s.substr(i, k));
                                stop = true;
                            }
                        }
                        j++;
                    }
                }
            }
            return result;
        }

        // 188. Best Time to Buy and Sell Stock IV
        // Say you have an array for which the i-th element is the price of a given
        // stock on day i. Design an algorithm to find the maximum profit. You may
        // complete at most k transactions. Note: You may not engage in multiple
        // transactions at the same time (ie, you must sell the stock before you buy
        // again). Example 1: Input: [2,4,1], k = 2 Output: 2 Explanation: Buy on day 1
        // (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2. Example 2:
        // Input: [3,2,6,5,0,3], k = 2
        // Output: 7
        // Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit =
        // 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit
        // = 3-0 = 3. Let p[i] be the price on day i Let P(i,k) be the max profit with k
        // transactions on day i
        //            k               1                         2                   3
        //            ......      k-1                          k
        // i     p[i]
        // 0     p[0]     -p[0]
        // 1     p[1]     -p[1]   P(1,1)     -p[1]+P(1,1)
        // 2     p[2]     -p[2]   P(2,1)     -p[2]+P(2,1)   P(2,2) -p[2]+P(2,2)
        // 3     p[3]     -p[3]   P(3,1)     -p[3]+P(3,1)   P(3,2) -p[3]+P(3,2) P(3,3)
        // 4     p[4]     -p[4]   P(4,1)     -p[4]+P(4,1)   P(4,2) -p[4]+P(4,2) P(4,3)
        // ......
        // k-1 p[k-1]   -p[k-1] P(k-1,1) -p[k-1]+P(k-1,1) P(k-1,2) ......
        // -p[k-1]+P(k-1,k-2) P(k-1,k-1) -p[k-1]+P(k-1,k-1) k     p[k]     -p[k] P(k,1)
        // -p[k]+P(k,1)   P(k,2) ......     -p[k]+P(k,k-2)   P(k,k-1)     -p[k]+P(k,k-1)
        // P(k,k) k+1 p[k+1]   -p[k+1] P(k+1,1) -p[k+1]+P[k+1,1] P(k+1,2) ......
        // -p[k+1]+P(k+1,k-2) P(k+1,k-1) -p[k+1]+P(k+1,k-1) P(k+1,k)
        // ......
        // i-1 p[i-1]   -p[i-1] P(i-1,1) -p[i-1]+P(i-1,1) P(i-1,2) ......
        // -p[i-1]+P(i-1,k-2) P(i-1,k-1) -p[i-1]+P(i-1,k-1) P(i-1,k) i     p[i] P(i,1)
        // P(i,2) ......                      P(i,k-1)                      P(i,k)

        // P(i,1) = max(P(i-1,1),
        //              p[i] + max{-p[i-1],
        //                         -p[i-2],
        //                         ......
        //                         -p[2],
        //                         -p[1],
        //                         -p[0]}
        // P(i,2) = max{P(i-1, 2),
        //              p[i] + max{-p[i-1] + P(i-1, 1),
        //                         -p[i-2] + P(i-2, 1),
        //                         ......
        //                         -p[2] + P(2, 1),
        //                         -p[1] + P(1, 1)}}
        // P(i,3) = max{P(i-1, 3),
        //              p[i] + max{-p[i-1] + P(i-1, 2),
        //                         -p[i-2] + P(i-2, 2),
        //                         ......
        //                         -p[3] + P(3, 2),
        //                         -p[2] + P(2, 2)}}
        // ......
        // P(i,k-1) = max{P(i-1, k-1),
        //              p[i] + max{-p[i-1] + P(i-1, k-2),
        //                         -p[i-2] + P(i-2, k-2),
        //                         ......
        //                         -p[k-1] + P(k-1, k-2),
        //                         -p[k-2] + P(k-2, k-2)}}
        // P(i,k) = max{P(i-1, k),
        //              p[i] + max{-p[i-1] + P(i-1, k-1),
        //                         -p[i-2] + P(i-2, k-1),
        //                         ......
        //                         -p[k] + P(k, k-1),
        //                         -p[k-1] + P(k-1, k-1)}}
        int maxProfit(int k, const vector<int> &prices)
        {
            k = min(k, (int)prices.size() - 1);
            if (k <= 0)
                return 0;
            vector<int> c(k, 0);
            vector<int> p(k, 0);
            for (int i = 1; i < (int)prices.size(); i++)
            {
                for (int j = min(i, k); j > 0; j--)
                {
                    if (j == i)
                    {
                        if (j == 1)
                            c[j - 1] = -prices[i - 1];
                        else
                            c[j - 1] = -prices[i - 1] + p[j - 2];
                        p[j - 1] = prices[i] + c[j - 1];
                    }
                    else
                    {
                        if (j == 1)
                            c[j - 1] = max(c[j - 1], -prices[i - 1]);
                        else
                            c[j - 1] = max(c[j - 1], -prices[i - 1] + p[j - 2]);
                        p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                    }
                }
            }
            int m = p[0];
            for (size_t i = 1; i < p.size(); i++)
                m = max(m, p[i]);
            return m > 0 ? m : 0;
        }
        int maxProfit2(int k, const vector<int> &prices)
        {
            k = min(k, (int)prices.size() - 1);
            if (k <= 0)
                return 0;
            vector<int> c(k, 0);
            vector<int> p(k, 0);
            for (int i = 1; i < (int)prices.size(); i++)
            {
                for (int j = min(i, k); j > 0; j--)
                {
                    if (j == 1)
                    {
                        if (j == i)
                        {
                            c[j - 1] = -prices[i - 1];
                            p[j - 1] = prices[i] + c[j - 1];
                        }
                        else
                        {
                            c[j - 1] = max(c[j - 1], -prices[i - 1]);
                            p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                        }
                    }
                    else
                    {
                        if (j == i)
                        {
                            c[j - 1] = -prices[i - 1] + p[j - 2];
                            p[j - 1] = prices[i] + c[j - 1];
                        }
                        else
                        {
                            c[j - 1] = max(c[j - 1], -prices[i - 1] + p[j - 2]);
                            p[j - 1] = max(p[j - 1], prices[i] + c[j - 1]);
                        }
                    }
                }
            }
            int m = p[0];
            for (size_t i = 1; i < p.size(); i++)
                m = max(m, p[i]);
            return m > 0 ? m : 0;
        }

        // 189. Rotate Array
        // Given an array, rotate the array to the right by k steps, where k is
        // non-negative. Example 1: Input: [1,2,3,4,5,6,7] and k = 3 Output:
        // [5,6,7,1,2,3,4] Explanation: rotate 1 steps to the right: [7,1,2,3,4,5,6]
        // rotate 2 steps to the right: [6,7,1,2,3,4,5]
        // rotate 3 steps to the right: [5,6,7,1,2,3,4]
        // Example 2:
        // Input: [-1,-100,3,99] and k = 2
        // Output: [3,99,-1,-100]
        // Explanation:
        // rotate 1 steps to the right: [99,-1,-100,3]
        // rotate 2 steps to the right: [3,99,-1,-100]
        // Note: Try to come up as many solutions as you can, there are at least 3
        // different ways to solve this problem. Could you do it in-place with O(1)
        // extra space?
        void rotate(vector<int> &nums, int k)
        {
            k = k % nums.size();
            if (k == 0)
                return;
            function<void(int, int)> Swap = [&](int i, int j) {
                while (i < j)
                {
                    swap(nums[i], nums[j]);
                    i++;
                    j--;
                }
            };
            Swap(0, (int)nums.size() - 1);
            Swap(0, k - 1);
            Swap(k, (int)nums.size() - 1);
        }
        void rotate2(vector<int> &nums, int k)
        {
            k %= nums.size();
            if (k == 0)
                return;
            function<void(int, int, int)> Swap = [&](int p, int q, int n) {
                for (int m = 0; m < n; m++)
                    swap(nums[p + m], nums[q + m]);
            };
            int i = 0;
            int j = nums.size() - 1;
            int t = j - k + 1;
            // input[i..t-1] and input[t..j];
            while (i < t && t <= j)
            {
                if (t - i < j - t + 1)
                {
                    // Left range is shorter. Swap it to the right, and
                    // repeat with the rest on its left.
                    // input[i..t-1], input[t..j-(t-i)], input[j-(t-i)+1..j]
                    Swap(i, j - (t - i) + 1, t - i);
                    j = j - (t - i);
                }
                else if (t - i > j - t + 1)
                {
                    // Right range is shorter. Swap it to the left, and
                    // repeat with the rest on its right.
                    // input[i..i+(j-t)], input(i+(j-t)+1..t-1], input[t..j]
                    Swap(i, t, j - t + 1);
                    i = i + (j - t) + 1;
                }
                else
                {
                    // Both ranges have the same length
                    Swap(i, t, t - i);
                    break;
                }
            }
        }
        void rotate3(vector<int> &nums, int k)
        {
            if (nums.empty())
                return;
            int n = (int)nums.size();
            k %= n;
            if (k == 0)
                return;
            vector<int> b(k, 0);
            for (int i = 0; i < k; i++)
            {
                if (b[i] == 1)
                    continue;
                int j = i;
                int x = nums[j];
                while (true)
                {
                    int t = j + k;
                    while (t < n)
                    {
                        swap(x, nums[t]);
                        t += k;
                    }
                    t %= n;
                    swap(x, nums[t]);
                    b[t] = 1;
                    if (j == t || t == i)
                        break;
                    j = t;
                }
            }
        }
        // This one works only if n and k are co-prime
        // 0, k, 2k, 3k, ..., (n-1)k, nk
        // 0, k % n, 2k % n, 3k % n, ..., (n-1)k % n, nk % n = 0
        void rotate4(vector<int> &nums, int k)
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

        // 190. Reverse Bits
        // Reverse bits of a given 32 bits unsigned integer.
        // Example 1:
        // Input: 00000010100101000001111010011100
        // Output: 00111001011110000010100101000000
        // Explanation: The input binary string 00000010100101000001111010011100
        // represents the unsigned integer 43261596, so return 964176192 which its
        // binary representation is 00111001011110000010100101000000.
        // Example 2:
        // Input: 11111111111111111111111111111101
        // Output: 10111111111111111111111111111111
        // Explanation: The input binary string 11111111111111111111111111111101
        // represents the unsigned integer 4294967293, so return 3221225471 which
        // its binary representation is 10111111111111111111111111111111.
        // Note: Note that in some languages such as Java, there is no unsigned integer
        // type. In this case, both input and output will be given as signed integer
        // type and should not affect your implementation, as the internal binary
        // representation of the integer is the same whether it is signed or unsigned.
        // In Java, the compiler represents the signed integers using 2's complement
        // notation. Therefore, in Example 2 above the input represents the signed
        // integer -3 and the output represents the signed integer -1073741825.
        // Follow up: If this function is called many times, how would you optimize it?
        uint32_t reverseBits(uint32_t n)
        {
            n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
            n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
            n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
            n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
            n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
            return n;
        }

        // 191. Number of 1 Bits
        // Write a function that takes an unsigned integer and return the number of '1'
        // bits it has (also known as the Hamming weight).
        // Example 1:
        // Input: 00000000000000000000000000001011
        // Output: 3
        // Explanation: The input binary string 00000000000000000000000000001011 has a
        // total of three '1' bits.
        // Example 2:
        // Input: 00000000000000000000000010000000
        // Output: 1
        // Explanation: The input binary string 00000000000000000000000010000000 has a
        // total of one '1' bit.
        // Example 3:
        // Input: 11111111111111111111111111111101
        // Output: 31
        // Explanation: The input binary string 11111111111111111111111111111101 has a
        // total of thirty one '1' bits.
        // Note: Note that in some languages such as Java, there is no unsigned integer
        // type. In this case, the input will be given as signed integer type and should
        // not affect your implementation, as the internal binary representation of the
        // integer is the same whether it is signed or unsigned. In Java, the compiler
        // represents the signed integers using 2's complement notation. Therefore, in
        // Example 3 above the input represents the signed integer -3.
        // Follow up: If this function is called many times, how would you optimize it?
        int hammingWeight(uint32_t n)
        {
            int c = 0;
            while (n > 0)
            {
                n &= (n - 1);
                c++;
            }
            return c;
        }

        // 198. House Robber
        // You are a professional robber planning to rob houses along a street. Each
        // house has a certain amount of money stashed, the only constraint stopping you
        // from robbing each of them is that adjacent houses have security system
        // connected and it will automatically contact the police if two adjacent houses
        // were broken into on the same night. Given a list of non-negative integers
        // representing the amount of money of each house, determine the maximum amount
        // of money you can rob tonight without alerting the police. Example 1: Input:
        // [1,2,3,1] Output: 4 Explanation: Rob house 1 (money = 1) and then rob house 3
        // (money = 3). Total amount you can rob = 1 + 3 = 4. Example 2: Input:
        // [2,7,9,3,1] Output: 12 Explanation: Rob house 1 (money = 2), rob house 3
        // (money = 9) and rob house 5 (money = 1). Total amount you can rob = 2 + 9 + 1
        // = 12.
        // Let m[i] be the max amount for p[0..i]
        // m[i] = max{m[i - 1],
        //            p[i] + max{m[i - 2],
        //                       m[i - 1],
        //                       ......
        //                       m[2],
        //                       m[1] = max{p[1], p[0]},
        //                       m[0] = p[0]}}
        int rob(const vector<int> &nums)
        {
            if (nums.empty())
                return 0;
            if (nums.size() == 1)
                return nums[0];
            int s = nums[0];               // i = 0
            int m = max(nums[0], nums[1]); // i = 1
            for (size_t i = 2; i < nums.size(); i++)
            {
                int t = m;               // m[i-1]
                m = max(m, nums[i] + s); // m[i] = max(m[i-1], n[i] + m[i-2])
                s = max(s, t);
            }
            return m;
        }
        int rob2(const vector<int> &nums)
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

        // 199. Binary Tree Right Side View
        // Given a binary tree, imagine yourself standing on the right side of it,
        // return the values of the nodes you can see ordered from top to bottom.
        // Example:
        // Input: [1,2,3,null,5,null,4]
        // Output: [1, 3, 4]
        // Explanation:
        //    1            <---
        //  /   \
        // 2     3         <---
        //  \     \
        //   5     4       <---
        vector<int> rightSideView(TreeNode *root)
        {
            vector<int> v;
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            int d = 1;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    if (d > (int)v.size())
                        v.push_back(n->val);
                    s.push(make_pair(n, d));
                    d++;
                    n = n->right;
                }
                else
                {
                    n = s.top().first->left;
                    d = s.top().second + 1;
                    s.pop();
                }
            }
            return v;
        }
        vector<int> rightSideView2(TreeNode *root)
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
                        q[next].push(p->right);
                    if (p->left != nullptr)
                        q[next].push(p->left);
                }
                level++;
            }
            return result;
        }

        // 200. Number of Islands
        // Given a 2d grid map of '1's (land) and '0's (water), count the number of
        // islands. An island is surrounded by water and is formed by connecting
        // adjacent lands horizontally or vertically. You may assume all four edges of
        // the grid are all surrounded by water. Example 1: Input:
        // 11110
        // 11010
        // 11000
        // 00000
        // Output: 1
        // Example 2: Input:
        // 11000
        // 11000
        // 00100
        // 00011
        // Output: 3
        int numIslands(vector<vector<char>> &grid)
        {
            if (grid.empty() || grid[0].empty())
                return 0;
            int m = grid.size();
            int n = grid[0].size();
            function<void(int, int)> mark = [&](int i, int j) {
                if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1')
                    return;
                grid[i][j] = '2';
                mark(i - 1, j);
                mark(i + 1, j);
                mark(i, j - 1);
                mark(i, j + 1);
            };
            int c = 0;
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (grid[i][j] == '1')
                    {
                        c++;
                        mark(i, j);
                    }
                }
            }
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (grid[i][j] == '2')
                        grid[i][j] = '1';
                }
            }
            return c;
        }
        int numIslands2(vector<vector<char>> &grid)
        {
            if (grid.empty() || grid[0].empty())
                return 0;
            function<void(int, int)> visit = [&](int i, int j) {
                queue<pair<int, int>> q;
                pair<int, int> p = make_pair(i, j);
                q.push(p);
                while (!q.empty())
                {
                    p = q.front();
                    q.pop();
                    grid[p.first][p.second] = 'x';
                    if (p.first > 0 && grid[p.first - 1][p.second] == '1')
                        q.push(make_pair(p.first - 1, p.second));
                    if (p.second + 1 < (int)grid[p.first].size() && grid[p.first][p.second + 1] == '1')
                        q.push(make_pair(p.first, p.second + 1));
                    if (p.first + 1 < (int)grid.size() && grid[p.first + 1][p.second] == '1')
                        q.push(make_pair(p.first + 1, p.second));
                    if (p.second > 0 && grid[p.first][p.second - 1] == '1')
                        q.push(make_pair(p.first, p.second - 1));
                }
            };
            int c = 0;
            for (int i = 0; i < (int)grid.size(); i++)
            {
                for (int j = 0; j < (int)grid[i].size(); j++)
                {
                    if (grid[i][j] == '1')
                    {
                        c++;
                        visit(i, j);
                    }
                }
            }
            for (int i = 0; i < (int)grid.size(); i++)
            {
                for (int j = 0; j < (int)grid[i].size(); j++)
                {
                    if (grid[i][j] == 'x')
                        grid[i][j] = '1';
                }
            }
            return c;
        }

        // 201. Bitwise AND of Numbers Range
        // Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND
        // of all numbers in this range, inclusive.
        // Example 1:
        // Input: [5,7]
        // Output: 4
        // Example 2:
        // Input: [0,1]
        // Output: 0
        int rangeBitwiseAnd(int m, int n)
        {
            int b = 0x40000000;
            int r = 0;
            while (b > 0)
            {
                if ((b & n) == 0)
                {
                    b = b >> 1;
                    continue;
                }
                if (b <= m)
                {
                    r |= b;
                    m -= b;
                    n -= b;
                    b = b >> 1;
                }
                else
                {
                    break;
                }
            }
            return r;
        }
        int rangeBitwiseAnd2(int m, int n)
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
        int rangeBitwiseAnd3(int m, int n)
        {
            int r = m;
            for (int i = m + 1; i <= n; i++)
                r &= i;
            return r;
        }

        // 202. Happy Number
        // Write an algorithm to determine if a number is "happy". A happy number is a
        // number defined by the following process: Starting with any positive integer,
        // replace the number by the sum of the squares of its digits, and repeat the
        // process until the number equals 1 (where it will stay), or it loops endlessly
        // in a cycle which does not include 1. Those numbers for which this process
        // ends in 1 are happy numbers. Example: Input: 19 Output: true Explanation: 12
        // + 92 = 82 82 + 22 = 68 62 + 82 = 100 12 + 02 + 02 = 1
        bool isHappy(int n)
        {
            if (n <= 0)
                return false;
            set<int> s;
            while (n != 1 && s.find(n) == s.end())
            {
                if (!s.empty())
                    cout << ", ";
                cout << n;
                s.insert(n);
                int t = 0;
                while (n > 0)
                {
                    int d = n % 10;
                    n /= 10;
                    t += d * d;
                }
                n = t;
            }
            cout << (s.empty() ? "" : ", ") << n << endl;
            return n == 1;
        }
        // This is wrong. The input n may not be in the cycle, e.g.,
        // 2, 4, 16, 37, 58, 89, 145, 42, 20, 4
        bool isHappy2(int n)
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
            cout << endl;
            return x == 1;
        }

        // 203. Remove Linked List Elements
        // Remove all elements from a linked list of integers that have value val.
        // Example:
        // Input:  1->2->6->3->4->5->6, val = 6
        // Output: 1->2->3->4->5
        ListNode *removeElements(ListNode *head, int val)
        {
            ListNode *p;
            while (head != nullptr && head->val == val)
            {
                p = head->next;
                delete head;
                head = p;
            }
            if (head == nullptr)
                return head;
            p = head;
            while (p->next != nullptr)
            {
                if (p->next->val == val)
                {
                    ListNode *t = p->next;
                    p->next = t->next;
                    delete t;
                }
                else
                {
                    p = p->next;
                }
            }
            return head;
        }

        // 204. Count Primes
        // Count the number of prime numbers less than a non-negative number, n.
        // Example:
        // Input: 10
        // Output: 4
        // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
        int countPrimes(int n)
        {
            if (n <= 2)
                return 0;
            vector<int> v;
            v.push_back(2);
            for (int i = 3; i < n; i++)
            {
                bool isPrime = true;
                for (size_t j = 0; (j < v.size()) && (v[j] * v[j] <= i); j++)
                {
                    if ((i % v[j]) == 0)
                    {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                    v.push_back(i);
            }
            return (int)v.size();
        }
        int countPrimes2(int n)
        {
            if (n <= 2)
                return 0;
            const int NumBitsInt = sizeof(int) * 8;
            const int NumInts = (n / NumBitsInt) + 1;
            unique_ptr<int[]> bits(new int[NumInts]);
            memset(bits.get(), 0, NumInts * sizeof(int));
            function<void(int, int)> setbit = [&](int i, int b) {
                int j = i / NumBitsInt;
                int k = i % NumBitsInt;
                if (b == 1)
                    bits[j] |= (0x1 << k);
                else if (b == 0)
                    bits[j] &= ~(0x1 << k);
            };
            function<int(int)> getbit = [&](int i) -> int {
                int j = i / NumBitsInt;
                int k = i % NumBitsInt;
                return (bits[j] & (0x1 << k)) >> k;
            };
            int c = 0;
            for (int i = 2; i < n; i++)
            {
                if (getbit(i) == 0)
                {
                    c++;
                    for (int j = i + i; j < n; j += i)
                        setbit(j, 1);
                }
            }
            return c;
        }

        // 205. Isomorphic Strings
        // Given two strings s and t, determine if they are isomorphic. Two strings are
        // isomorphic if the characters in s can be replaced to get t. All occurrences
        // of a character must be replaced with another character while preserving the
        // order of characters. No two characters may map to the same character but a
        // character may map to itself. Example 1: Input: s = "egg", t = "add" Output:
        // true Example 2: Input: s = "foo", t = "bar" Output: false Example 3: Input: s
        // = "paper", t = "title" Output: true Note: You may assume both s and t have
        // the same length.
        bool isIsomorphic(const string &s, const string &t)
        {
            if (s.size() != t.size())
                return false;
            map<char, char> st;
            map<char, char> ts;
            for (size_t i = 0; i < s.size(); i++)
            {
                if ((st.find(s[i]) != st.end() && ts.find(t[i]) == ts.end()) ||
                    (st.find(s[i]) == st.end() && ts.find(t[i]) != ts.end()))
                    return false;
                if (st.find(s[i]) == st.end())
                {
                    st[s[i]] = t[i];
                    ts[t[i]] = s[i];
                }
                else if (st[s[i]] != t[i])
                    return false;
            }
            return true;
        }
        bool isIsomorphic2(const string &s, const string &t)
        {
            if (s.size() != s.size())
                return false;
            map<char, char> ms;
            map<char, char> mt;
            for (size_t i = 0; i < s.size(); i++)
            {
                if (ms.find(s[i]) == ms.end())
                    ms[s[i]] = t[i];
                else if (ms[s[i]] != t[i])
                    return false;
                if (mt.find(t[i]) == mt.end())
                    mt[t[i]] = s[i];
                else if (mt[t[i]] != s[i])
                    return false;
            }
            return true;
        }

        // 206. Reverse Linked List
        // Reverse a singly linked list.
        // Example:
        // Input: 1->2->3->4->5->NULL
        // Output: 5->4->3->2->1->NULL
        // Follow up: A linked list can be reversed either iteratively or recursively.
        // Could you implement both?
        ListNode *reverseList(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return head;
            ListNode *p = nullptr;
            ListNode *m = head;
            while (m != nullptr)
            {
                ListNode *n = m->next;
                m->next = p;
                p = m;
                m = n;
            }
            return p;
        }
        ListNode *reverseList2(ListNode *head)
        {
            if (head == nullptr)
                return nullptr;
            ListNode *t = head;
            while (t->next != nullptr)
            {
                ListNode *n = t->next;
                t->next = n->next;
                n->next = head;
                head = n;
            }
            return head;
        }
        ListNode *reverseList3(ListNode *head)
        {
            function<ListNode *(ListNode *)> reverse = [&](ListNode *t) -> ListNode * {
                if (t == nullptr || t->next == nullptr)
                    return t;
                ListNode *h = reverse(t->next);
                t->next->next = t;
                t->next = nullptr;
                return h;
            };
            return reverse(head);
        }
        ListNode *reverseList4(ListNode *head)
        {
            function<void(ListNode *, ListNode **, ListNode **)> reverse =
                [&](ListNode *node, ListNode **h, ListNode **t) {
                    if (node == nullptr || node->next == nullptr)
                    {
                        *h = node;
                        *t = node;
                        return;
                    }
                    reverse(node->next, h, t);
                    (*t)->next = node;
                    node->next = nullptr;
                    *t = node;
                };
            ListNode *tail = nullptr;
            reverse(head, &head, &tail);
            return head;
        }

        // 207. Course Schedule
        // There are a total of n courses you have to take, labeled from 0 to n-1.
        // Some courses may have prerequisites, for example to take course 0 you have
        // to first take course 1, which is expressed as a pair: [0,1]. Given the
        // total number of courses and a list of prerequisite pairs, is it possible
        // for you to finish all courses?
        // Example 1:
        // Input: 2, [[1,0]]
        // Output: true
        // Explanation: There are a total of 2 courses to take. To take course 1 you
        // should have finished course 0. So it is possible.
        // Example 2:
        // Input: 2, [[1,0],[0,1]]
        // Output: false
        // Explanation: There are a total of 2 courses to take. To take course 1 you
        // should have finished course 0, and to take course 0 you should also have
        // finished course 1. So it is impossible.
        // Note: The input prerequisites is a graph represented by a list of edges,
        // not adjacency matrices. Read more about how a graph is represented.
        // You may assume that there are no duplicate edges in the input prerequisites.
        bool canFinish(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            for_each(prerequisites.cbegin(), prerequisites.cend(),
                     [&](const vector<int> &e) {
                         if (g.find(e[1]) == g.end())
                             g[e[1]] = vector<int>(1, e[0]);
                         else
                             g[e[1]].push_back(e[0]);
                     });
            set<int> trees;
            function<bool(int, set<int> &)> hasCircle = [&](int i,
                                                            set<int> &visited) -> bool {
                if (g.find(i) == g.end())
                    return false;
                if (trees.find(i) != trees.end())
                    return false;
                visited.insert(i);
                for (size_t j = 0; j < g[i].size(); j++)
                {
                    if (visited.find(g[i][j]) != visited.end())
                        return true;
                    if (hasCircle(g[i][j], visited))
                        return true;
                }
                visited.erase(i);
                trees.insert(i);
                return false;
            };
            for (auto it = g.begin(); it != g.end(); it++)
            {
                set<int> v;
                if (hasCircle(it->first, v))
                    return false;
            }
            return true;
        }
        // This BFS is wrong, e.g., for inputs 3 and [[0,1],[0,2],[1,2]]
        bool canFinish2(int numCourses, const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            for_each(prerequisites.cbegin(), prerequisites.cend(),
                     [&](const vector<int> &e) {
                         if (g.find(e[1]) == g.end())
                             g[e[1]] = vector<int>(1, e[0]);
                         else
                             g[e[1]].push_back(e[0]);
                     });
            for (auto it = g.begin(); it != g.end(); it++)
            {
                set<int> visited;
                queue<int> q;
                q.push(it->first);
                visited.insert(it->first);
                while (!q.empty())
                {
                    int t = q.front();
                    q.pop();
                    if (g.find(t) == g.end())
                        continue;
                    for (size_t i = 0; i < g[t].size(); i++)
                    {
                        if (visited.find(g[t][i]) != visited.end())
                            return false;
                        q.push(g[t][i]);
                        visited.insert(g[t][i]);
                    }
                }
            }
            return true;
        }

        // 208. Implement Trie (Prefix Tree)
        // Implement a trie with insert, search, and startsWith methods.
        // Example:
        // Trie trie = new Trie();
        // trie.insert("apple");
        // trie.search("apple");   // returns true
        // trie.search("app");     // returns false
        // trie.startsWith("app"); // returns true
        // trie.insert("app");
        // trie.search("app");     // returns true
        // Note: You may assume that all inputs are consist of lowercase letters a-z.
        // All inputs are guaranteed to be non-empty strings.
        // Your Trie object will be instantiated and called as such:
        // Trie* obj = new Trie();
        // obj->insert(word);
        // bool param_2 = obj->search(word);
        // bool param_3 = obj->startsWith(prefix);
        class Trie
        {
        private:
            class Node
            {
            public:
                vector<Node *> children;
                string val;
                bool complete;
                Node(const string &w, bool c) : val(w), complete(c) {}
                Node() : Node(string(), true) {}
                // Try to match word[i..] partially or entirely
                bool Match(const string &word, size_t i, size_t &j)
                {
                    j = 0; // matched characters count
                    for (j = 0; j < val.size() && i < word.size(); j++, i++)
                    {
                        if (word[i] != val[j])
                            break;
                    }
                    return j > 0;
                }
            };

            Node *root;

            void Delete(Node *node)
            {
                if (node == nullptr)
                    return;
                for_each(node->children.begin(), node->children.end(),
                         [&](Node *n) { Delete(n); });
                node->children.clear();
            }

            // Return the deepest node matching the word partially or entirely
            // Case 1: Return the root
            //   word is empty
            //   word not match any of the children of the root
            // Case 2: Return a non-root node
            //   word matches the node entirely (i == word.size(), j is the length of
            //   the node->val) word matches the node partially (j < the length of the
            //   node->val, i <= word.size())
            Node *Search(const string &word, size_t &i, size_t &j)
            {
                i = 0; // count the prefix characters of word that are matched
                j = 0; // count the characters of the node that are matched
                if (word.empty())
                    return root;
                Node *node = root;
                bool stop = false;
                while (i < word.size() && !stop)
                {
                    stop = true;
                    for (size_t k = 0; k < node->children.size(); k++)
                    {
                        size_t l = 0;
                        if (node->children[k]->Match(word, i, l))
                        {
                            j = l;
                            i += j;
                            node = node->children[k];
                            stop = (j < node->val.size());
                            break;
                        }
                    }
                }
                return node;
            }

        public:
            Trie() { root = new Node(); }

            ~Trie()
            {
                Delete(root);
                root = nullptr;
            }

            void insert(string word)
            {
                if (word.empty())
                    return;
                size_t i = 0;
                size_t j = 0;
                Node *node = Search(word, i, j);
                if (j < node->val.size())
                {
                    // split between val[0..(j-1)] and val[j..]
                    Node *c = new Node(node->val.substr(j), node->complete);
                    c->children.insert(c->children.end(), node->children.begin(),
                                       node->children.end());
                    node->val.resize(j);
                    node->children.clear();
                    node->children.push_back(c);
                    node->complete = (i == word.size());
                }
                if (i == word.size())
                {
                    if (!node->complete)
                        node->complete = true;
                }
                else
                {
                    Node *c = new Node(word.substr(i), true);
                    node->children.push_back(c);
                }
            }

            bool search(string word)
            {
                if (word.empty())
                    return true;
                size_t i = 0;
                size_t j = 0;
                Node *node = Search(word, i, j);
                return i == word.size() && j == node->val.size() && node->complete;
            }

            // Returns if there is any word in the trie that starts with the given
            // prefix.
            bool startsWith(string prefix)
            {
                if (prefix.empty())
                    return true;
                size_t i = 0;
                size_t j = 0;
                Search(prefix, i, j);
                return i == prefix.size();
            }
        };
        class Trie2
        {
        private:
            struct Node
            {
                vector<Node *> children;
                char val;
                bool complete;

                Node(char v, bool c) : val(v), complete(c) {}

                Node() : Node((char)0, true) {}
            };

            Node *root;

            void Delete(Node *node)
            {
                if (node == nullptr)
                    return;
                for_each(node->children.begin(), node->children.end(),
                         [&](Node *n) { Delete(n); });
                node->children.clear();
            }

            Node *Search(const string &word, size_t &i)
            {
                i = 0;
                if (word.empty())
                    return root;
                Node *node = root;
                bool stop = false;
                while (i < word.size() && !stop)
                {
                    stop = true;
                    for (size_t k = 0; k < node->children.size(); k++)
                    {
                        if (word[i] == node->children[k]->val)
                        {
                            i++;
                            node = node->children[k];
                            stop = false;
                            break;
                        }
                    }
                }
                return node;
            }

        public:
            Trie2() { root = new Node(); }

            ~Trie2()
            {
                Delete(root);
                root = nullptr;
            }

            void insert(string word)
            {
                if (word.empty())
                    return;
                size_t i = 0;
                Node *node = Search(word, i);
                while (i < word.size())
                {
                    Node *c = new Node(word[i], false);
                    node->children.push_back(c);
                    node = c;
                    i++;
                }
                node->complete = true;
            }

            bool search(string word)
            {
                if (word.empty())
                    return true;
                size_t i = 0;
                Node *node = Search(word, i);
                return i == word.size() && node->complete;
            }

            // Returns if there is any word in the trie that starts with the given
            // prefix.
            bool startsWith(string prefix)
            {
                if (prefix.empty())
                    return true;
                size_t i = 0;
                Search(prefix, i);
                return i == prefix.size();
            }
        };
        class Trie3
        {
        private:
            struct Node
            {
                char val;
                map<char, Node *> children;
                bool complete;
                Node(char v)
                {
                    val = v;
                    complete = false;
                }
                ~Node()
                {
                    for (map<char, Node *>::iterator it = children.begin(); it != children.end(); it++)
                        delete it->second;
                    children.clear();
                }
            } * root;

        public:
            /** Initialize your data structure here. */
            Trie3()
                : root(new Node('\0'))
            {
            }

            ~Trie3()
            {
                delete root;
                root = nullptr;
            }

            /** Inserts a word into the trie. */
            void insert(string word)
            {
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->children.find(word[i]) == node->children.end())
                        break;
                    node = node->children[word[i++]];
                }
                while (i < word.size())
                {
                    node->children[word[i]] = new Node(word[i]);
                    node = node->children[word[i++]];
                }
                node->complete = true;
            }

            /** Returns if the word is in the trie. */
            bool search(string word)
            {
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->children.find(word[i]) == node->children.end())
                        return false;
                    node = node->children[word[i++]];
                }
                return node->complete;
            }

            /** Returns if there is any word in the trie that starts with the given prefix. */
            bool startsWith(string prefix)
            {
                Node *node = root;
                size_t i = 0;
                while (i < prefix.size())
                {
                    if (node->children.find(prefix[i]) == node->children.end())
                        return false;
                    node = node->children[prefix[i++]];
                }
                return true;
            }
        };

        // Map Sum Pairs
        // Implement a MapSum class with insert, and sum methods.
        // For the method insert, you'll be given a pair of (string, integer).
        // The string represents the key and the integer represents the value.
        // If the key already existed, then the original key-value pair will
        // be overridden to the new one. For the method sum, you'll be given a
        // string representing the prefix, and you need to return the sum of all
        // the pairs' value whose key starts with the prefix.
        // Example 1:
        // Input: insert("apple", 3), Output: Null
        // Input: sum("ap"), Output: 3
        // Input: insert("app", 2), Output: Null
        // Input: sum("ap"), Output: 5
        class MapSum
        {
        private:
            struct Node
            {
                char key;
                int val;
                bool complete;
                map<char, Node *> next;
                Node(char k, int v, bool c)
                    : key(k), val(v), complete(c)
                {
                }
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } * root;
            void search(string key, Node *&node, size_t &i)
            {
                while (i < key.size())
                {
                    if (node->next.find(key[i]) == node->next.end())
                        break;
                    node = node->next[key[i++]];
                }
            }

        public:
            MapSum()
                : root(new Node('\0', 0, true))
            {
            }
            ~MapSum()
            {
                delete root;
                root = nullptr;
            }
            void insert(string key, int val)
            {
                Node *node = root;
                size_t i = 0;
                search(key, node, i);
                while (i < key.size())
                {
                    node->next[key[i]] = new Node(key[i], 0, false);
                    node = node->next[key[i++]];
                }
                node->val = val;
                node->complete = true;
            }
            int sum(string prefix)
            {
                Node *node = root;
                size_t i = 0;
                search(prefix, node, i);
                if (i < prefix.size())
                    return 0;
                stack<Node *> s;
                int a = 0;
                s.push(node);
                while (!s.empty())
                {
                    node = s.top();
                    s.pop();
                    if (node->complete)
                        a += node->val;
                    for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        s.push(it->second);
                }
                return a;
            }
        };
        class MapSum2
        {
        private:
            struct Node
            {
                char key;
                int val;
                bool complete;
                map<char, Node *> next;
                Node(char k, int v, bool c)
                    : key(k), val(v), complete(c)
                {
                }
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } * root;
            void search(const string &key, int val, Node *&node, size_t &i, bool insert)
            {
                while (i < key.size())
                {
                    if (insert)
                        node->val += val;
                    if (node->next.find(key[i]) == node->next.end())
                        return;
                    node = node->next[key[i++]];
                }
                if (insert)
                    node->val += val;
            }

        public:
            MapSum2()
                : root(new Node('\0', 0, true))
            {
            }
            ~MapSum2()
            {
                delete root;
                root = nullptr;
            }
            void insert(const string &key, int val)
            {
                Node *node = root;
                size_t i = 0;
                search(key, val, node, i, true);
                while (i < key.size())
                {
                    node->next[key[i]] = new Node(key[i], val, false);
                    node = node->next[key[i++]];
                }
                node->complete = true;
            }
            int sum(string prefix)
            {
                Node *node = root;
                size_t i = 0;
                search(prefix, 0, node, i, false);
                if (i < prefix.size())
                    return 0;
                return node->val;
            }
        };

        // Replace Words
        // In English, we have a concept called root, which can be followed by some
        // other words to form another longer word - let's call this word successor.
        // For example, the root an, followed by other, which can form another word another.
        // Now, given a dictionary consisting of many roots and a sentence. You need
        // to replace all the successor in the sentence with the root forming it. If
        // a successor has many roots can form it, replace it with the root with the
        // shortest length. You need to output the sentence after the replacement.
        // Example 1:
        // Input: dict = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
        // Output: "the cat was rat by the bat"
        // Constraints:
        // The input will only have lower-case letters.
        // 1 <= dict.length <= 1000
        // 1 <= dict[i].length <= 100
        // 1 <= sentence words number <= 1000
        // 1 <= sentence words length <= 1000
        string replaceWords(const vector<string> &dict, string sentence)
        {
            struct Node
            {
                char val;
                bool complete;
                map<char, Node *> next;
                Node(char v, bool c) : val(v), complete(c) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } *root = new Node('\0', true);
            function<void(const string &)> insert = [&](const string &word) {
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->next.find(word[i]) == node->next.end())
                        break;
                    node = node->next[word[i++]];
                }
                while (i < word.size())
                {
                    node->next[word[i]] = new Node(word[i], false);
                    node = node->next[word[i++]];
                }
                node->complete = true;
            };
            function<size_t(size_t)> match = [&](size_t i) -> size_t {
                Node *node = root;
                size_t j = i;
                while (j < sentence.size())
                {
                    if (node->next.find(sentence[j]) == node->next.end())
                        break;
                    node = node->next[sentence[j++]];
                    if (node->complete)
                        break;
                }
                return node->complete ? j : i;
            };
            for (const string &r : dict)
                insert(r);
            size_t i = 0;
            size_t j = 0;
            while (j < sentence.size())
            {
                if (sentence[j] == ' ')
                {
                    if (i++ < j++)
                        sentence[i - 1] = sentence[j - 1];
                }
                else
                {
                    size_t k = match(j);
                    if (j < k)
                    {
                        if (i < j)
                        {
                            while (j < k)
                                sentence[i++] = sentence[j++];
                        }
                        else
                        {
                            j = k;
                            i = j;
                        }
                        while (j < sentence.size() && sentence[j] != ' ')
                            j++;
                    }
                    else
                    {
                        while (j < sentence.size() && sentence[j] != ' ')
                        {
                            if (i++ < j++)
                                sentence[i - 1] = sentence[j - 1];
                        }
                    }
                }
            }
            delete root;
            return sentence.substr(0, i);
        }

        // Add and Search Word - Data structure design
        // Design a data structure that supports the following two operations:
        // void addWord(word)
        // bool search(word)
        // search(word) can search a literal word or a regular expression string
        // containing only letters a-z or .. A . means it can represent any one letter.
        // Example:
        // addWord("bad")
        // addWord("dad")
        // addWord("mad")
        // search("pad") -> false
        // search("bad") -> true
        // search(".ad") -> true
        // search("b..") -> true
        // Note: You may assume that all words are consist of lowercase letters a-z.
        class WordDictionary2
        {
        private:
            struct Node
            {
                char val;
                bool complete;
                map<char, Node *> next;
                Node(char v, bool c) : val(v), complete(c) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            } * root;

        public:
            WordDictionary2()
            {
                root = new Node('\0', true);
            }

            ~WordDictionary2()
            {
                if (root != nullptr)
                    delete root;
            }

            void Print()
            {
                function<void(int, Node *)> print = [&](int i, Node *node) {
                    cout << string(i, ' ') << node->val << (node->complete ? "/" : " ") << endl;
                    for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        print(i + 2, it->second);
                };
                print(0, root);
            }

            void addWord(const string &word)
            {
                cout << "addWord(" << word << ")" << endl;
                Node *node = root;
                size_t i = 0;
                while (i < word.size())
                {
                    if (node->next.find(word[i]) == node->next.end())
                        break;
                    node = node->next[word[i++]];
                }
                while (i < word.size())
                {
                    node->next[word[i]] = new Node(word[i], false);
                    node = node->next[word[i++]];
                }
                node->complete = true;
                Print();
            }

            bool search(const string &word)
            {
                function<bool(Node *, size_t)> find = [&](Node *node, size_t i) -> bool {
                    if (i >= word.size())
                        return node->complete;
                    if (node->next.find(word[i]) == node->next.end())
                    {
                        if (word[i] != '.')
                            return false;
                        for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        {
                            if (find(it->second, i + 1))
                                return true;
                        }
                    }
                    else if (find(node->next[word[i]], i + 1))
                    {
                        return true;
                    }
                    return false;
                };
                bool f = find(root, 0);
                cout << "search(" << word << ") = " << f << endl;
                return f;
            }

            bool search2(const string &word)
            {
                stack<pair<Node *, size_t>> s;
                s.push(make_pair(root, 0));
                bool found = false;
                while (!s.empty())
                {
                    pair<Node *, size_t> t = s.top();
                    s.pop();
                    Node *node = t.first;
                    size_t i = t.second;
                    cout << "<'" << node->val << "', " << i << ">" << endl;
                    if (i == word.size())
                    {
                        found = node->complete;
                        if (found)
                            break;
                        else
                            continue;
                    }
                    if (node->next.empty())
                        continue;
                    if (node->next.find(word[i]) == node->next.end())
                    {
                        if (word[i] != '.')
                            continue;
                        for (map<char, Node *>::iterator it = node->next.begin(); it != node->next.end(); it++)
                        {
                            s.push(make_pair(it->second, i + 1));
                        }
                    }
                    else
                    {
                        s.push(make_pair(node->next[word[i]], i + 1));
                    }
                }
                cout << "search2(" << word << ") = " << found << endl;
                return found;
            }
        };

        // 209. Minimum Size Subarray Sum
        // Given an array of n positive integers and a positive integer s, find the
        // minimal length of a contiguous subarray of which the sum >= s. If there
        // isn't one, return 0 instead.
        // Example:
        // Input: s = 7, nums = [2,3,1,2,4,3]
        // Output: 2
        // Explanation: the subarray [4,3] has the minimal length under the problem
        // constraint. Follow up: If you have figured out the O(n) solution, try coding
        // another solution of which the time complexity is O(n log n).
        int minSubArrayLen(int s, const vector<int> &nums)
        {
            int a = 0;
            size_t i = 0;
            int m = 0;
            for (size_t j = 0; j < nums.size(); j++)
            {
                a += nums[j];
                while (a >= s)
                {
                    m = min((m == 0 ? nums.size() : m), j - i + 1);
                    a -= nums[i];
                    i++;
                }
            }
            return m;
        }
        int minSubArrayLen2(int s, const vector<int> &nums)
        {
            int l = 0;
            int c = 0;
            int i = 0;
            for (int j = 0; j < (int)nums.size(); j++)
            {
                c += nums[j];
                while (c >= s)
                {
                    l = (l == 0 ? j - i + 1 : min(l, j - i + 1));
                    c -= nums[i++];
                }
            }
            return l;
        }

        // 210. Course Schedule II
        // There are a total of n courses you have to take, labeled from 0 to n-1. Some
        // courses may have prerequisites, for example to take course 0 you have to
        // first take course 1, which is expressed as a pair: [0,1]. Given the total
        // number of courses and a list of prerequisite pairs, return the ordering of
        // courses you should take to finish all courses. There may be multiple correct
        // orders, you just need to return one of them. If it is impossible to finish
        // all courses, return an empty array. Example 1: Input: 2, [[1,0]] Output:
        // [0,1] Explanation: There are a total of 2 courses to take. To take course 1
        // you should have finished course 0. So the correct course order is [0,1] .
        // Example 2:
        // Input: 4, [[1,0],[2,0],[3,1],[3,2]]
        // Output: [0,1,2,3] or [0,2,1,3]
        // Explanation: There are a total of 4 courses to take. To take course 3 you
        // should have finished both courses 1 and 2. Both courses 1 and 2 should be
        // taken after you finished course 0. So one correct course order is [0,1,2,3].
        // Another correct ordering is [0,2,1,3] . Note: The input prerequisites is a
        // graph represented by a list of edges, not adjacency matrices. Read more about
        // how a graph is represented. You may assume that there are no duplicate edges
        // in the input prerequisites.
        vector<int> findOrder(int numCourses,
                              const vector<vector<int>> &prerequisites)
        {
            map<int, vector<int>> g;
            for_each(prerequisites.cbegin(), prerequisites.cend(),
                     [&](const vector<int> &e) {
                         if (g.find(e[0]) == g.end())
                             g[e[0]] = vector<int>();
                         g[e[0]].push_back(e[1]);
                     });
            vector<pair<int, int>> rankNodeVector;
            set<int> visited;
            set<int> path;
            bool solvable = true;
            int rank = 0;
            function<bool(int)> solve = [&](int i) -> bool {
                if (visited.find(i) != visited.end())
                    return true;
                if (g.find(i) != g.end())
                {
                    path.insert(i);
                    for (size_t j = 0; j < g[i].size(); j++)
                    {
                        if (path.find(g[i][j]) != path.end())
                        {
                            solvable = false;
                            return false;
                        }
                        solve(g[i][j]);
                    }
                    path.erase(i);
                }
                visited.insert(i);
                rankNodeVector.push_back(make_pair(rank++, i));
                return true;
            };
            for (int i = 0; i < numCourses && solvable; i++)
                solve(i);
            vector<int> result;
            if (solvable)
            {
                // sort(rankNodeVector.begin(), rankNodeVector.end());
                for_each(rankNodeVector.cbegin(), rankNodeVector.cend(),
                         [&](const pair<int, int> &p) { result.push_back(p.second); });
            }
            return result;
        }

        // 211. Add and Search Word - Data structure design
        // Design a data structure that supports the following two operations:
        // void addWord(word)
        // bool search(word)
        // search(word) can search a literal word or a regular expression string
        // containing only letters a-z or .. A . means it can represent any one letter.
        // Example:
        // addWord("bad")
        // addWord("dad")
        // addWord("mad")
        // search("pad") -> false
        // search("bad") -> true
        // search(".ad") -> true
        // search("b..") -> true
        // Note: You may assume that all words are consist of lowercase letters a-z.
        // Your WordDictionary object will be instantiated and called as such:
        // WordDictionary* obj = new WordDictionary();
        // obj->addWord(word);
        // bool param_2 = obj->search(word);
        class WordDictionary
        {
        private:
            struct Node
            {
                char val;
                vector<Node *> children;
                bool valid;
                Node(char v, bool b) : val(v), valid(b) {}
                Node() : Node(0, true) {}
            };
            Node *root;
            void Delete(Node *n)
            {
                if (n != nullptr)
                {
                    for_each(n->children.begin(), n->children.end(),
                             [&](Node *c) { Delete(c); });
                    n->children.clear();
                }
            }

        public:
            WordDictionary() { root = new Node(); }
            ~WordDictionary()
            {
                Delete(root);
                root = nullptr;
            }
            void addWord(const string &word)
            {
                size_t i = 0;
                function<Node *(Node *, size_t &)> match = [&](Node *node,
                                                               size_t &i) -> Node * {
                    if (i == word.size())
                        return node;
                    for (size_t j = 0; j < node->children.size(); j++)
                    {
                        Node *c = node->children[j];
                        if (c->val == word[i])
                        {
                            i++;
                            return match(c, i);
                        }
                    }
                    return node;
                };
                Node *node = match(root, i);
                for (; i < word.size(); i++)
                {
                    Node *c = new Node(word[i], i + 1 == word.size());
                    node->children.push_back(c);
                    node = c;
                }
            }
            bool search(const string &word)
            {
                function<bool(Node *, size_t)> match = [&](Node *node,
                                                           size_t i) -> bool {
                    if (i == word.size())
                        return node->valid;
                    for (size_t j = 0; j < node->children.size(); j++)
                    {
                        Node *c = node->children[j];
                        if (word[i] == '.' || word[i] == c->val)
                        {
                            if (match(c, i + 1))
                                return true;
                        }
                    }
                    return false;
                };
                return match(root, 0);
            }
        };

        // 212. Word Search II
        // Given a 2D board and a list of words from the dictionary, find all words in
        // the board. Each word must be constructed from letters of sequentially
        // adjacent cell, where "adjacent" cells are those horizontally or vertically
        // neighboring. The same letter cell may not be used more than once in a word.
        // Example:
        // Input:
        // board = [
        //   ['o','a','a','n'],
        //   ['e','t','a','e'],
        //   ['i','h','k','r'],
        //   ['i','f','l','v']
        // ]
        // words = ["oath","pea","eat","rain"]
        // Output: ["eat","oath"]
        // Note: All inputs are consist of lowercase letters a-z. The values of words
        // are distinct.
        vector<string> findWords(const vector<vector<char>> &board,
                                 const vector<string> &words)
        {
            vector<string> result;
            if (board.empty() || board[0].empty())
                return result;
            int m = board.size();
            int n = board[0].size();
            set<pair<int, int>> path;
            function<bool(int, int, const string &, int)> find =
                [&](int i, int j, const string &word, size_t k) -> bool {
                if (k == word.size())
                    return true;
                if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[k])
                    return false;
                pair<int, int> p = make_pair(i, j);
                if (path.find(p) != path.end())
                    return false;
                path.insert(p);
                bool found = find(i - 1, j, word, k + 1) ||
                             find(i + 1, j, word, k + 1) ||
                             find(i, j - 1, word, k + 1) || find(i, j + 1, word, k + 1);
                path.erase(p);
                return found;
            };
            for_each(words.cbegin(), words.cend(), [&](const string &w) {
                bool found = false;
                for (int i = 0; i < m && !found; i++)
                {
                    for (int j = 0; j < n && !found; j++)
                    {
                        if (find(i, j, w, 0))
                            found = true;
                    }
                }
                if (found)
                    result.push_back(w);
            });
            return result;
        }
        vector<string> findWords2(const vector<vector<char>> &board, const vector<string> &words)
        {
            struct Node
            {
                char val;
                int index;
                map<char, Node *> next;
                Node(char v, int i = -1) : val(v), index(i) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            };
            unique_ptr<Node> root(new Node('\0'));
            function<void(int)> add = [&](int i) {
                const string &w = words[i];
                Node *node = root.get();
                size_t j = 0;
                while (j < w.size() && node->next.find(w[j]) != node->next.end())
                    node = node->next[w[j++]];
                while (j < w.size())
                {
                    node->next[w[j]] = new Node(w[j]);
                    node = node->next[w[j++]];
                }
                node->index = i;
            };
            for (int i = 0; i < (int)words.size(); i++)
                add(i);
            set<string> found; // use set because a word may appear more than once in the board
            function<void(int, int, Node *, set<pair<int, int>> &)> find =
                [&](int i, int j, Node *node, set<pair<int, int>> &visited) {
                    if (i < 0 || i >= (int)board.size() || j < 0 || j >= (int)board[i].size() || node == nullptr)
                        return;
                    if (node->next.find(board[i][j]) == node->next.end())
                        return;
                    pair<int, int> p = make_pair(i, j);
                    if (visited.find(p) != visited.end())
                        return;
                    node = node->next[board[i][j]];
                    if (node->index >= 0)
                        found.insert(words[node->index]);
                    visited.insert(p);
                    find(i - 1, j, node, visited);
                    find(i, j + 1, node, visited);
                    find(i + 1, j, node, visited);
                    find(i, j - 1, node, visited);
                    visited.erase(p);
                };
            set<pair<int, int>> visited;
            for (int i = 0; i < (int)board.size(); i++)
            {
                for (int j = 0; j < (int)board[i].size(); j++)
                {
                    find(i, j, root.get(), visited);
                }
            }
            vector<string> result(found.cbegin(), found.cend());
            return result;
        }

        // Palindrome Pairs
        // Given a list of unique words, find all pairs of distinct indices (i, j)
        // in the given list, so that the concatenation of the two words, i.e.
        // words[i] + words[j] is a palindrome.
        // Example 1:
        // Input: ["abcd","dcba","lls","s","sssll"]
        // Output: [[0,1],[1,0],[3,2],[2,4]]
        // Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
        // Example 2:
        // Input: ["bat","tab","cat"]
        // Output: [[0,1],[1,0]]
        // Explanation: The palindromes are ["battab","tabbat"]
        // Example 3:
        // Input: ["a", ""]
        // Output: [[0,1],[1,0]]
        // Example 4:
        // Input: ["a","b","c","ab","ac","aa"]
        // Expected: [[3,0],[1,3],[4,0],[2,4],[5,0],[0,5]]
        vector<vector<int>> palindromePairs(const vector<string> &words)
        {
            struct Node
            {
                char val;
                vector<int> completeIndices;
                vector<int> childIndices;
                bool complete;
                map<char, Node *> next;
                Node(char v, bool c) : val(v), complete(c) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            };
            unique_ptr<Node> before(new Node('\0', false));
            unique_ptr<Node> after(new Node('\0', false));
            function<void(int)> add = [&](int j) {
                Node *node = before.get();
                int i = 0;
                const string &w = words[j];
                while (i < (int)w.size())
                {
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node->childIndices.push_back(j);
                    node = node->next[w[i++]];
                }
                while (i < (int)w.size())
                {
                    node->next[w[i]] = new Node(w[i], false);
                    node->childIndices.push_back(j);
                    node = node->next[w[i++]];
                }
                node->childIndices.push_back(j);
                node->completeIndices.push_back(j);
                node->complete = true;
                node = after.get();
                i = (int)w.size() - 1;
                while (i >= 0)
                {
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node->childIndices.push_back(j);
                    node = node->next[w[i--]];
                }
                while (i >= 0)
                {
                    node->next[w[i]] = new Node(w[i], false);
                    node->childIndices.push_back(j);
                    node = node->next[w[i--]];
                }
                node->childIndices.push_back(j);
                node->completeIndices.push_back(j);
                node->complete = true;
            };
            function<bool(const string &, int, int)> isPalindrome = [&](const string &w, int i, int j) -> bool {
                while (i < j)
                {
                    if (w[i++] != w[j--])
                        return false;
                }
                return true;
            };
            vector<vector<int>> result;
            function<void(int)> findBefore = [&](int j) {
                Node *node = before.get();
                const string &w = words[j];
                int i = (int)w.size() - 1;
                while (i >= 0)
                {
                    if (node->complete)
                    {
                        if (isPalindrome(w, 0, i))
                        {
                            for (int k : node->completeIndices)
                                result.push_back(vector<int>{k, j});
                        }
                    }
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node = node->next[w[i--]];
                }
                if (i < 0)
                {
                    for (int k : node->childIndices)
                    {
                        if (isPalindrome(words[k], (int)w.size(), (int)words[k].size() - 1))
                            result.push_back(vector<int>{k, j});
                    }
                }
            };
            function<void(int)> findAfter = [&](int j) {
                Node *node = after.get();
                const string &w = words[j];
                int i = 0;
                while (i < (int)w.size())
                {
                    if (node->complete)
                    {
                        if (isPalindrome(w, i, (int)w.size() - 1))
                        {
                            for (int k : node->completeIndices)
                                result.push_back(vector<int>{j, k});
                        }
                    }
                    if (node->next.find(w[i]) == node->next.end())
                        break;
                    node = node->next[w[i++]];
                }
                if (i >= (int)w.size())
                {
                    for (int k : node->childIndices)
                    {
                        if (isPalindrome(words[k], 0, (int)words[k].size() - (int)w.size() - 1))
                            result.push_back(vector<int>{j, k});
                    }
                }
            };
            for (int i = 0; i < (int)words.size(); i++)
            {
                findBefore(i);
                findAfter(i);
                add(i);
            }
            return result;
        }

        // 213. House Robber II
        // You are a professional robber planning to rob houses along a street. Each
        // house has a certain amount of money stashed. All houses at this place are
        // arranged in a circle. That means the first house is the neighbor of the last
        // one. Meanwhile, adjacent houses have security system connected and it will
        // automatically contact the police if two adjacent houses were broken into on
        // the same night. Given a list of non-negative integers representing the amount
        // of money of each house, determine the maximum amount of money you can rob
        // tonight without alerting the police.
        // Example 1:
        // Input: [2,3,2]
        // Output: 3
        // Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money =
        // 2), because they are adjacent houses. Example 2: Input: [1,2,3,1] Output: 4
        // Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
        // Total amount you can rob = 1 + 3 = 4.
        int robII(const vector<int> &nums)
        {
            int a1 = 0;
            int b1 = 0;
            int a2 = 0;
            int b2 = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (i == 0)
                    b1 = nums[i]; // track when starting at house 1
                if (i == 1)
                    b2 = nums[i]; // track when starting at house 2
                if (i > 0 && i + 1 < nums.size())
                { // ignore the last house
                    int c1 = max(a1 + nums[i], b1);
                    a1 = b1;
                    b1 = c1;
                }
                if (i > 1)
                {
                    int c2 = max(a2 + nums[i], b2);
                    a2 = b2;
                    b2 = c2;
                }
            }
            return max(b1, b2);
        }

        // 214. Shortest Palindrome
        // Given a string s, you are allowed to convert it to a palindrome by adding
        // characters in front of it. Find and return the shortest palindrome you can
        // find by performing this transformation.
        // Example 1:
        // Input: "aacecaaa"
        // Output: "aaacecaaa"
        // Example 2:
        // Input: "abcd"
        // Output: "dcbabcd"
        string shortestPalindrome(const string &s)
        {
            string r(s);
            reverse(r.begin(), r.end());
            // Find the prefix of s which is also a suffix of r
            string w = s + "#" + r;
            // Using KMP
            vector<int> p(w.size(), 0);
            int c = 0;
            for (int i = 1; i < (int)w.size(); i++)
            {
                while (c > 0 && w[c] != w[i])
                    c = p[c - 1];
                if (w[c] == w[i])
                    c++;
                p[i] = c;
            }
            int n = p[w.size() - 1];
            string t = s.substr(n);
            reverse(t.begin(), t.end());
            string o = t + s;
            return o;
        }
        string shortestPalindrome2(const string &s)
        {
            if (s.empty())
                return s;
            string r(s);
            reverse(r.begin(), r.end());
            string w = s + r; // eliminate the extra '#'
            vector<int> p(w.size(), 0);
            int c = 0;
            for (int i = 1; i < (int)w.size(); i++)
            {
                // Need an extra check if c exceeds the length of s
                while (c > 0 && (w[c] != w[i] || c >= (int)s.size()))
                    c = p[c - 1];
                if (w[c] == w[i])
                    c++;
                p[i] = c;
            }
            int n = p[w.size() - 1];
            string t = s.substr(n);
            reverse(t.begin(), t.end());
            string o = t + s;
            return o;
        }
        string shortestPalindrome3(const string &s)
        {
            if (s.empty())
                return s;
            int n = s.size();
            int m = n << 1; // eliminate the extra string w
            vector<int> p(m, 0);
            int c = 0;
            for (int i = 1; i < m; i++)
            {
                // map w[i] back to s[j]
                int j = i < n ? i : m - i - 1;
                while (c > 0 && (s[c] != s[j] || c >= n))
                    c = p[c - 1];
                if (s[c] == s[j])
                    c++;
                p[i] = c;
            }
            string t = s.substr(p[m - 1]);
            reverse(t.begin(), t.end());
            string o = t + s;
            return o;
        }
        string shortestPalindrome4(const string &s)
        {
            int i = (int)s.size() - 1;
            while (i >= 0)
            {
                int j = 0;
                int k = i;
                while (j <= k)
                {
                    if (s[j] != s[k])
                        break;
                    j++;
                    k--;
                }
                if (j > k)
                {
                    // s[0..i] is a palindrome
                    break;
                }
                else
                {
                    i--;
                }
            }
            string t = s.substr(i + 1);
            reverse(t.begin(), t.end());
            return t + s;
        }

        // 215. Kth Largest Element in an Array
        // Find the kth largest element in an unsorted array. Note that it is the kth
        // largest element in the sorted order, not the kth distinct element.
        // Example 1:
        // Input: [3,2,1,5,6,4] and k = 2
        // Output: 5
        // Example 2:
        // Input: [3,2,3,1,2,4,5,5,6] and k = 4
        // Output: 4
        // Note: You may assume k is always valid, 1 <= k <= array's length.
        int findKthLargest(vector<int> &nums, int k)
        {
            int b = 0;
            int e = (int)nums.size() - 1;
            while (b <= e)
            {
                int i = b;
                int j = e - 1;
                while (i <= j)
                {
                    if (nums[i] < nums[e])
                    {
                        swap(nums[i], nums[j]);
                        j--;
                    }
                    else
                    {
                        i++;
                    }
                }
                swap(nums[i], nums[e]);
                if (i - b + 1 < k)
                {
                    k -= (i - b + 1);
                    b = i + 1;
                }
                else if (i - b + 1 > k)
                {
                    e = i - 1;
                }
                else
                {
                    return nums[i];
                }
            }
            return nums[b];
        }
        int findKthLargest2(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end(), [&](int a, int b) -> bool { return a > b; });
            return nums[k - 1];
        }
        int findKthLargest3(const vector<int> &nums, int k)
        {
            priority_queue<int> q;
            for (int n : nums)
                q.push(n);
            for (int i = 0; i < k - 1; i++)
                q.pop();
            return q.top();
        }

        // 216. Combination Sum III
        // Find all possible combinations of k numbers that add up to a number n, given
        // that only numbers from 1 to 9 can be used and each combination should be a
        // unique set of numbers. Note: All numbers will be positive integers. The
        // solution set must not contain duplicate combinations.
        // Example 1:
        // Input: k = 3, n = 7
        // Output: [[1,2,4]]
        // Example 2:
        // Input: k = 3, n = 9
        // Output: [[1,2,6], [1,3,5], [2,3,4]]
        vector<vector<int>> combinationSum3(int k, int n)
        {
            vector<vector<int>> result;
            vector<int> s;
            function<void(int, int, int)> solve = [&](int i, int c, int t) {
                if (c == 0 && t == 0)
                {
                    result.push_back(s);
                    return;
                }
                for (int j = i; j <= 9 && j <= t; j++)
                {
                    s.push_back(j);
                    solve(j + 1, c - 1, t - j);
                    s.pop_back();
                }
            };
            solve(1, k, n);
            return result;
        }

        // 278. First Bad Version
        // You are a product manager and currently leading a team to develop a new
        // product. Unfortunately, the latest version of your product fails the quality
        // check. Since each version is developed based on the previous version, all the
        // versions after a bad version are also bad. Suppose you have n versions [1, 2,
        // ..., n] and you want to find out the first bad one, which causes all the
        // following ones to be bad. You are given an API bool isBadVersion(version)
        // which will return whether version is bad. Implement a function to find the
        // first bad version. You should minimize the number of calls to the API.
        // Example:
        // Given n = 5, and version = 4 is the first bad version.
        // call isBadVersion(3) -> false
        // call isBadVersion(5) -> true
        // call isBadVersion(4) -> true
        // Then 4 is the first bad version.
        bool isBadVersion(int v) { return v >= 0; }
        int firstBadVersion(int n)
        {
            int b = 1;
            int e = n;
            while (b <= e)
            {
                int m = b + ((e - b) >> 1);
                if (isBadVersion(m))
                {
                    if (b == e)
                        return m;
                    e = m;
                }
                else
                {
                    b = m + 1;
                }
            }
            throw runtime_error("not found");
        }
        int firstBadVersion2(int n)
        {
            int b = 1;
            int e = n;
            while (b < e)
            {
                int m = b + ((e - b) >> 1);
                if (isBadVersion(m))
                    e = m;
                else
                    b = m + 1;
            }
            // Assume there must be a bad version
            // e.g., when the bad version is n.
            return b;
        }
        int firstBadVersion3(int n)
        {
            int b = 1;
            int e = n;
            while (b + 1 < e)
            {
                int m = b + ((e - b) >> 1);
                if (isBadVersion(m))
                    e = m;
                else
                    b = m;
            }
            if (isBadVersion(b))
                return b;
            if (isBadVersion(e))
                return e;
            throw runtime_error("not found");
        }

        // 287. Find the Duplicate Number
        // Given an array nums containing n + 1 integers where each integer is between 1
        // and n (inclusive), prove that at least one duplicate number must exist.
        // Assume that there is only one duplicate number, find the duplicate one.
        // Example 1:
        // Input: [1,3,4,2,2]
        // Output: 2
        // Example 2:
        // Input: [3,1,3,4,2]
        // Output: 3
        // Note:
        // You must not modify the array (assume the array is read only).
        // You must use only constant, O(1) extra space.
        // Your runtime complexity should be less than O(n2).
        // There is only one duplicate number in the array, but it could be repeated
        // more than once. The first two approaches mentioned do not satisfy the
        // constraints given in the prompt, but they are solutions that you might be
        // likely to come up with during a technical interview. As an interviewer, I
        // personally would not expect someone to come up with the cycle detection
        // solution unless they have heard it before. Proof Proving that at least one
        // duplicate must exist in nums is simple application of the pigeonhole
        // principle. Here, each number in nums is a "pigeon" and each distinct number
        // that can appear in nums is a "pigeonhole". Because there are n+1 numbers are
        // nnn distinct possible numbers, the pigeonhole principle implies that at least
        // one of the numbers is duplicated. Approach #3 Floyd's Tortoise and Hare
        // (Cycle Detection) [Accepted] Intuition If we interpret nums such that for
        // each pair of index i and value v_i, the "next" value v_j​ is at index
        // v_i​, we can reduce this problem to cycle detection. See the solution to
        // Linked List Cycle II for more details. Algorithm First off, we can easily
        // show that the constraints of the problem imply that a cycle must exist.
        // Because each number in nums is between 1 and n, it will necessarily point to
        // an index that exists. Therefore, the list can be traversed infinitely, which
        // implies that there is a cycle. Additionally, because 0 cannot appear as a
        // value in nums, nums[0] cannot be part of the cycle. Therefore, traversing the
        // array in this manner from nums[0] is equivalent to traversing a cyclic linked
        // list. Given this, the problem can be solved just like Linked List Cycle II.
        int findDuplicate(const vector<int> &nums)
        {
            int i = nums[0];
            int j = nums[0];
            do
            {
                i = nums[i];
                j = nums[nums[j]];
            } while (i != j);
            i = nums[0];
            while (i != j)
            {
                i = nums[i];
                j = nums[j];
            }
            return i;
        }
        int findDuplicate2(vector<int> &nums)
        {
            for (int i = 0; i < (int)nums.size(); i++)
            {
                while (nums[i] != i + 1)
                {
                    int j = nums[i] - 1;
                    if (nums[i] == nums[j])
                        return nums[i];
                    swap(nums[i], nums[j]);
                }
            }
            throw runtime_error("Duplicate not found");
        }
        int findDuplicate3(vector<int> &nums)
        {
            while (nums[0] != nums[nums[0]])
                swap(nums[0], nums[nums[0]]);
            return nums[0];
        }
        int findDuplicate4(const vector<int> &nums)
        {
            set<int> s;
            int i = 0;
            while (s.find(nums[i]) == s.end())
            {
                s.insert(nums[i]);
                i = nums[i];
            }
            return nums[i];
        }
        int findDuplicate5(const vector<int> &nums)
        {
            set<int> s;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (s.find(nums[i]) == s.end())
                    s.insert(nums[i]);
                else
                    return nums[i];
            }
            throw runtime_error("Duplicate not found");
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
            function<void(vector<int> &, vector<int> &)> solve = [&](vector<int> &n1,
                                                                     vector<int> &n2) {
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
                [&](const vector<int> &n1, const vector<int> &n2) {
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
                [&](const vector<int> &n) -> map<int, int> {
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
                [&](const vector<int> &n1, const vector<int> &n2) {
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

        // 410. Split Array Largest Sum
        // Given an array which consists of non-negative integers and an integer m, you
        // can split the array into m non-empty continuous subarrays. Write an algorithm
        // to minimize the largest sum among these m subarrays. Note: If n is the length
        // of array, assume the following constraints are satisfied:
        // 1 <= n <= 1000
        // 1 <= m <= min(50, n)
        // Examples:
        // Input:
        // nums = [7,2,5,10,8]
        // m = 2
        // Output:
        // 18
        // Explanation:
        // There are four ways to split nums into two subarrays.
        // The best way is to split it into [7,2,5] and [10,8],
        // where the largest sum among the two subarrays is only 18.
        int splitArray(const vector<int> &nums, int m)
        {
            long long l = 0;
            long long h = 0;
            for (int n : nums)
            {
                l = max(l, (long long)n);
                h += n;
            }
            while (l < h)
            {
                long long t = l + ((h - l) >> 1);
                int c = 0;
                long long s = 0;
                for (size_t i = 0; i < nums.size(); i++)
                {
                    s += nums[i];
                    if (s > t)
                    {
                        c++;
                        s = nums[i];
                    }
                }
                if (s > 0)
                    c++;
                if (c > m)
                    l = t + 1;
                else
                    h = t;
            }
            return l;
        }

        // 658. Find K Closest Elements
        // Given a sorted array, two integers k and x, find the k closest elements to x
        // in the array. The result should also be sorted in ascending order. If there
        // is a tie, the smaller elements are always preferred. Example 1: Input:
        // [1,2,3,4,5], k=4, x=3 Output: [1,2,3,4] Example 2: Input: [1,2,3,4,5], k=4,
        // x=-1 Output: [1,2,3,4] Note: The value k is positive and will always be
        // smaller than the length of the sorted array. Length of the given array is
        // positive and will not exceed 10^4. Absolute value of elements in the array
        // and x will not exceed 10^4. UPDATE (2017/9/19): The arr parameter had been
        // changed to an array of integers (instead of a list of integers). Please
        // reload the code definition to get the latest changes. arr: [1,2,3,4,5] k: 4
        // x: -1
        vector<int> findClosestElements(const vector<int> &arr, int k, int x)
        {
            if (arr.empty())
                return {};
            if (arr.size() == 1)
                return arr;
            int b = 0;
            int e = (int)arr.size() - 1;
            int m;
            while (b + 1 < e)
            {
                m = b + ((e - b) >> 1);
                if (arr[m] < x)
                    b = m;
                else if (arr[m] > x)
                    e = m;
                else
                    break;
            }
            vector<int> result;
            if (b + 1 < e)
            {
                // Must have found x
                result.push_back(arr[m]);
                b = m - 1;
                e = m + 1;
            }
            else if (arr[b] >= x)
            {
                // b = 0, e = 1, x <= arr[b] <= arr[e]
                result.push_back(arr[b--]);
            }
            else if (arr[e] <= x)
            {
                // b = e - 1, e = arr.size - 1, arr[b] < arr[e] <= x
                result.push_back(arr[e++]);
            }
            else
            {
                // 0 < b < b + 1 == e < arr.size - 1
                // arr[b] < x << arr[e]
            }
            // b and e point to next possible candidates
            while (e - b - 1 < k)
            {
                if (b < 0)
                    result.push_back(arr[e++]);
                else if (e >= (int)arr.size())
                    result.insert(result.begin(), 1, arr[b--]);
                else if (x - arr[b] <= arr[e] - x)
                    result.insert(result.begin(), 1, arr[b--]);
                else
                    result.push_back(arr[e++]);
            }
            return result;
        }
        // This may not output the smaller ones on tie
        // arr:[0,0,1,2,3,3,4,7,7,8]
        // k: 3
        // x: 5
        // Output: [4,7,7]
        // Expected: [3,3,4]
        vector<int> findClosestElements2(vector<int> &arr, int k, int x)
        {
            vector<int> result;
            int b = 0;
            int e = (int)arr.size() - 1;
            int i = b;
            while (b <= e)
            {
                i = b;
                int j = e - 1;
                while (i <= j)
                {
                    if (abs(arr[i] - x) > abs(arr[e] - x))
                        swap(arr[i], arr[j--]);
                    else
                        i++;
                }
                swap(arr[i++], arr[e]);
                if (i - b < k)
                {
                    k -= i - b;
                    b = i;
                }
                else if (i - b > k)
                {
                    e = i - 2;
                }
                else
                {
                    break;
                }
            }
            result.insert(result.begin(), arr.begin(), arr.begin() + i);
            sort(result.begin(), result.end());
            return result;
        }

        // 719. Find K-th Smallest Pair Distance
        // Given an integer array, return the k-th smallest distance among all the
        // pairs. The distance of a pair (A, B) is defined as the absolute difference
        // between A and B. Example 1: Input: nums = [1,3,1] k = 1 Output: 0
        // Explanation:
        // Here are all the pairs:
        // (1,3) -> 2
        // (1,1) -> 0
        // (3,1) -> 2
        // Then the 1st smallest distance pair is (1,1), and its distance is 0.
        // Note:
        // 2 <= len(nums) <= 10000.
        // 0 <= nums[i] < 1000000.
        // 1 <= k <= len(nums) * (len(nums) - 1) / 2.
        // Approach #2: Binary Search + Prefix Sum [Accepted]
        // Let's binary search for the answer. It's definitely in the range [0, W],
        // where W = max(nums) - min(nums)]. Let possible(guess) be true if and only
        // if there are k or more pairs with distance less than or equal to guess.
        // We will focus on evaluating our possible function quickly.
        // Algorithm
        // Let countLessOrEqual[v] be the number of points in nums less than or equal to
        // v. Also, let countEqualOnLeft[j] be the number of points i with i < j and
        // nums[i] == nums[j]. We can record both of these with a simple linear scan.
        // Now, for every point i, the number of points j with i < j and nums[j] -
        // nums[i] <= guess is countLessOrEqual[nums[i]+guess] -
        // countLessOrEqual[nums[i]] + (countTotal[i] - countEqualOnLeft[i]), where
        // countTotal[i] is the number of ocurrences of nums[i] in nums. The sum of this
        // over all i is the number of pairs with distance <= guess. Finally, because
        // the sum of countTotal[i] - countEqualOnLeft[i] is the same as the sum of
        // countEqualOnLeft[i] when the sum is over all elements having the same value
        // nums[i], we could just replace that term with countEqualOnLeft[i] without
        // affecting the answer.
        // Approach #3: Binary Search + Sliding Window [Accepted]
        // As in Approach #2, let's binary search for the answer, and we will focus on
        // evaluating our possible function quickly.
        // Algorithm
        // We will use a sliding window approach to count the number of pairs with
        // distance <= guess. For every possible right, we maintain the loop invariant:
        // left is the smallest value such that nums[right] - nums[left] <= guess. Then,
        // the number of pairs with right as it's right-most endpoint is right - left,
        // and we add all of these up.
        int smallestDistancePair(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            int l = 0;
            int h = nums[nums.size() - 1] - nums[0];
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                int count = 0;
                int i = 0;
                for (int j = 0; j < (int)nums.size(); j++)
                {
                    while (nums[j] - nums[i] > m)
                        i++;
                    count += j - i;
                }
                if (count < k)
                    l = m + 1;
                else
                    h = m;
            }
            return l;
        }
        int smallestDistancePair2(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            int min = nums[0];
            int max = nums[nums.size() - 1];
            // let d = max - min
            //     min, min+1, ..., max-1, max
            // i = 0,   1,     ..., d-1,   d
            // countLessOrEqual[i] is the count of elements in nums whose value is
            // less than or equal to (min + i)
            vector<int> countLessOrEqual(max - min + 1, 0);
            int i = 0; // walk through nums
            for (int v = min; v <= max; v++)
            {
                // Since nums is sorted, only need to walk towards right until
                // the first element greater than v
                // Thw while loop will be skiped if v < nums[i]
                while (i < (int)nums.size() && nums[i] == v)
                    i++;
                // There are i elements <= v
                countLessOrEqual[v - min] = i;
            }
            vector<int> countEqualOnLeft(nums.size(), 0);
            for (i = 1; i < (int)nums.size(); i++)
            {
                // Since nums is sorted, just need to compare with previous one
                // to count the equal elements
                if (nums[i] == nums[i - 1])
                    countEqualOnLeft[i] = countEqualOnLeft[i - 1] + 1;
            }
            int l = 0;
            int h = max - min;
            while (l < h)
            {
                int m = l + ((h - l) >> 1);
                int count = 0;
                for (i = 0; i < (int)nums.size(); i++)
                {
                    // countLessOrEqual[guessHigh] will be elements <= nums[i] + m
                    // countLessOrEqual[guessLow] will be elements <= nums[i]
                    int guessLow = nums[i] - min;
                    int guessHigh = guessLow + m;
                    count += (guessHigh >= (int)countLessOrEqual.size()
                                  ? (int)nums.size()
                                  : countLessOrEqual[guessHigh]);
                    // This excludes all elements == nums[i], so need to compensate
                    // by adding countEqualOnLeft[i]
                    count -= countLessOrEqual[guessLow];
                    count += countEqualOnLeft[i];
                }
                if (count < k)
                    l = m + 1;
                else
                    h = m;
            }
            return l;
        }
        int smallestDistancePair3(const vector<int> &nums, int k)
        {
            priority_queue<int> q;
            for (size_t i = 0; i + 1 < nums.size(); i++)
            {
                for (size_t j = i + 1; j < nums.size(); j++)
                {
                    int d = abs(nums[j] - nums[i]);
                    if ((int)q.size() < k || d < q.top())
                        q.push(d);
                    if ((int)q.size() > k)
                        q.pop();
                }
            }
            return q.top();
        }
        int smallestDistancePair4(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            priority_queue<int> q;
            for (int i = 1; i < (int)nums.size(); i++)
            {
                for (int j = i - 1; j >= 0; j--)
                {
                    int d = abs(nums[i] - nums[j]);
                    if ((int)q.size() < k || d < q.top())
                    {
                        q.push(d);
                        if ((int)q.size() > k)
                            q.pop();
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return q.top();
        }
        // This is wrong
        int smallestDistancePair5(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            priority_queue<int> q;
            int t = 1;
            while ((int)q.size() < k && t <= (int)nums.size() - 1)
            {
                for (size_t i = 0; i + t < nums.size(); i++)
                {
                    int d = abs(nums[i + t] - nums[i]);
                    if ((int)q.size() < k || d < q.top())
                        q.push(d);
                    if ((int)q.size() > k)
                        q.pop();
                }
                t++;
            }
            return q.top();
        }

        // 744. Find Smallest Letter Greater Than Target
        // Given a list of sorted characters letters containing only lowercase letters,
        // and given a target letter target, find the smallest element in the list that
        // is larger than the given target. Letters also wrap around. For example, if
        // the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.
        // Examples:
        // Input:
        // letters = ["c", "f", "j"]
        // target = "a"
        // Output: "c"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "c"
        // Output: "f"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "d"
        // Output: "f"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "g"
        // Output: "j"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "j"
        // Output: "c"
        // Input:
        // letters = ["c", "f", "j"]
        // target = "k"
        // Output: "c"
        // Note: letters has a length in range [2, 10000]. letters consists of lowercase
        // letters, and contains at least 2 unique letters. target is a lowercase
        // letter.
        char nextGreatestLetter(const vector<char> &letters, char target)
        {
            int b = 0;
            int e = (int)letters.size() - 1;
            while (b <= e)
            {
                int m = b + ((e - b) >> 1);
                if (letters[m] <= target)
                {
                    if (m < e)
                        b = m + 1;
                    else
                        return letters[0];
                }
                else
                {
                    if (m < e)
                        e = m;
                    else
                        return letters[m];
                }
            }
            throw runtime_error("not found");
        }
        char nextGreatestLetter2(const vector<char> &letters, char target)
        {
            int b = 0;
            int e = (int)letters.size();
            while (b < e)
            {
                int m = b + ((e - b) >> 1);
                if (letters[m] <= target)
                    b = m + 1;
                else
                    e = m;
            }
            if (b == (int)letters.size())
                return letters[0];
            else
                return letters[b];
        }
        char nextGreatestLetter3(const vector<char> &letters, char target)
        {
            int b = 0;
            int e = (int)letters.size() - 1;
            while (b + 1 < e)
            {
                int m = b + ((e - b) >> 1);
                if (letters[m] <= target)
                    b = m;
                else
                    e = m;
            }
            if (target < letters[b])
                return letters[b];
            if (target < letters[e])
                return letters[e];
            return letters[0];
        }

        // Lowest Common Ancestor of a Binary Tree
        // Given a binary tree, find the lowest common ancestor (LCA) of two given nodes
        // in the tree. According to the definition of LCA on Wikipedia: “The lowest
        // common ancestor is defined between two nodes p and q as the lowest node in T
        // that has both p and q as descendants (where we allow a node to be a
        // descendant of itself).” Given the following binary tree:  root =
        // [3,5,1,6,2,0,8,null,null,7,4] Example 1: Input: root =
        // [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1 Output: 3 Explanation: The LCA of
        // nodes 5 and 1 is 3. Example 2: Input: root = [3,5,1,6,2,0,8,null,null,7,4], p
        // = 5, q = 4 Output: 5 Explanation: The LCA of nodes 5 and 4 is 5, since a node
        // can be a descendant of itself according to the LCA definition. Note: All of
        // the nodes' values will be unique. p and q are different and both values will
        // exist in the binary tree.
        TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
        {
            if (root == nullptr || p == nullptr || q == nullptr)
                return nullptr;
            TreeNode *left = lowestCommonAncestor(root->left, p, q);
            TreeNode *right = lowestCommonAncestor(root->right, p, q);
            if (left != nullptr && right != nullptr)
                return root;
            if (left != nullptr)
            {
                if (root == p || root == q)
                    return root;
                else
                    return left;
            }
            if (right != nullptr)
            {
                if (root == p || root == q)
                    return root;
                else
                    return right;
            }
            return (root == p || root == q) ? root : nullptr;
        }
        TreeNode *lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q)
        {
            stack<pair<TreeNode *, int>> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    // If found one then mark it
                    s.push(make_pair(n, (n == p || n == q) ? 1 : 0));
                    n = n->left;
                }
                else
                {
                    pair<TreeNode *, int> p = s.top();
                    if (p.first->right != nullptr && p.first->right != last)
                    {
                        n = p.first->right;
                    }
                    else
                    {
                        s.pop();
                        if (p.second == 1)
                        {
                            if (s.top().second == 1)
                            {
                                // Two nodes are found
                                return s.top().first;
                            }
                            else
                            {
                                // Only one found
                                s.top().second = 1;
                            }
                        }
                        last = p.first;
                    }
                }
            }
            return nullptr;
        }

        // Lowest Common Ancestor of a Binary Search Tree
        // Given a binary search tree (BST), find the lowest common ancestor (LCA) of
        // two given nodes in the BST. According to the definition of LCA on Wikipedia:
        // "The lowest common ancestor is defined between two nodes p and q as the lowest
        // node in T that has both p and q as descendants (where we allow a node to be
        // a descendant of itself)."
        // Given binary search tree:  root = [6,2,8,0,4,7,9,null,null,3,5]
        // Example 1:
        // Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
        // Output: 6
        // Explanation: The LCA of nodes 2 and 8 is 6.
        // Example 2:
        // Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
        // Output: 2
        // Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant
        // of itself according to the LCA definition.
        TreeNode *lowestCommonAncestorBST(TreeNode *root, TreeNode *p, TreeNode *q)
        {
            TreeNode *node = root;
            while (node != nullptr)
            {
                if (node->val > p->val && node->val > q->val)
                    node = node->left;
                else if (node->val < p->val && node->val < q->val)
                    node = node->right;
                else
                    break;
            }
            return node;
        }

        class Codec
        {
        public:
            // Serialize and Deserialize Binary Tree
            // Serialization is the process of converting a data structure or object into a
            // sequence of bits so that it can be stored in a file or memory buffer, or
            // transmitted across a network connection link to be reconstructed later in the
            // same or another computer environment. Design an algorithm to serialize and
            // deserialize a binary tree. There is no restriction on how your
            // serialization/deserialization algorithm should work. You just need to ensure
            // that a binary tree can be serialized to a string and this string can be
            // deserialized to the original tree structure. Example: You may serialize the
            // following tree:
            //     1
            //    / \
            //   2   3
            //      / \
            //     4   5
            // as "[1,2,3,null,null,4,5]"
            // Clarification: The above format is the same as how LeetCode serializes a
            // binary tree. You do not necessarily need to follow this format, so please be
            // creative and come up with different approaches yourself. Note: Do not use
            // class member/global/static variables to store states. Your serialize and
            // deserialize algorithms should be stateless. Encodes a tree to a single
            // string.
            static string serialize(TreeNode *root)
            {
                ostringstream oss;
                function<void(TreeNode *)> solve = [&](TreeNode *n) {
                    if (n == nullptr)
                    {
                        oss << "#";
                        return;
                    }
                    oss << n->val << ",";
                    solve(n->left);
                    oss << ",";
                    solve(n->right);
                };
                solve(root);
                return oss.str();
            }

            // Decodes your encoded data to tree.
            static TreeNode *deserialize(string data)
            {
                size_t i = 0;
                function<TreeNode *()> solve = [&]() -> TreeNode * {
                    size_t j = data.find(',', i);
                    string s = data.substr(i, j - i);
                    i = j + 1;
                    if (s.compare("#") == 0)
                        return nullptr;
                    int v = stoi(s);
                    TreeNode *n = new TreeNode(v);
                    n->left = solve();
                    n->right = solve();
                    return n;
                };
                return solve();
            }
        };
        class Codec2
        {
        public:
            // Encodes a tree to a single string.
            static string serialize(TreeNode *root)
            {
                ostringstream oss;
                if (root == nullptr)
                    return oss.str();
                queue<TreeNode *> q[2];
                q[0].push(root);
                int l = 0;
                bool first = true;
                while (!q[0].empty() || !q[1].empty())
                {
                    queue<TreeNode *> &current = q[l % 2];
                    queue<TreeNode *> &next = q[(l + 1) % 2];
                    bool nextAllNulls = true;
                    while (!current.empty())
                    {
                        TreeNode *n = current.front();
                        current.pop();
                        if (!first)
                            oss << ",";
                        if (n == nullptr)
                            oss << "#";
                        else
                            oss << n->val;
                        if (first)
                            first = false;
                        if (n != nullptr)
                        {
                            next.push(n->left);
                            next.push(n->right);
                            nextAllNulls &= (n->left == nullptr && n->right == nullptr);
                        }
                    }
                    if (nextAllNulls)
                        break;
                    else
                        l++;
                }
                return oss.str();
            }

            // Decodes your encoded data to tree.
            static TreeNode *deserialize(string data)
            {
                if (data.empty())
                    return nullptr;
                size_t i = 0;
                size_t j = data.find(",", i);
                TreeNode *root;
                if (j == string::npos)
                {
                    root = new TreeNode(stoi(data.substr(i)));
                    i = data.size();
                }
                else
                {
                    root = new TreeNode(stoi(data.substr(i, j - i)));
                    i = j + 1;
                }
                queue<TreeNode *> q;
                q.push(root);
                while (!q.empty() && i < data.size())
                {
                    TreeNode *n = q.front();
                    q.pop();
                    if (data[i] == '#')
                    {
                        n->left = nullptr;
                        i += 2;
                    }
                    else
                    {
                        j = data.find(",", i);
                        if (j == string::npos)
                        {
                            n->left = new TreeNode(stoi(data.substr(i)));
                            i = data.size();
                        }
                        else
                        {
                            n->left = new TreeNode(stoi(data.substr(i, j - i)));
                            i = j + 1;
                        }
                        q.push(n->left);
                    }
                    if (i >= data.size())
                        break;
                    if (data[i] == '#')
                    {
                        n->right = nullptr;
                        i += 2;
                    }
                    else
                    {
                        j = data.find(",", i);
                        if (j == string::npos)
                        {
                            n->right = new TreeNode(stoi(data.substr(i)));
                            i = data.size();
                        }
                        else
                        {
                            n->right = new TreeNode(stoi(data.substr(i, j - i)));
                            i = j + 1;
                        }
                        q.push(n->right);
                    }
                }
                return root;
            }
        };

        // Search in a Binary Search Tree
        // Given the root node of a binary search tree (BST) and a value. You need to
        // find the node in the BST that the node's value equals the given value. Return
        // the subtree rooted with that node. If such node doesn't exist, you should
        // return NULL. For example, Given the tree:
        //         4
        //        / \
        //       2   7
        //      / \
        //     1   3
        // And the value to search: 2
        // You should return this subtree:
        //       2
        //      / \   
        //     1   3
        // In the example above, if we want to search the value 5, since there is no node
        // with value 5, we should return NULL.
        TreeNode *searchBST(TreeNode *root, int val)
        {
            TreeNode *n = root;
            while (n != nullptr)
            {
                if (n->val == val)
                    break;
                if (n->val > val)
                    n = n->left;
                else
                    n = n->right;
            }
            return n;
        }
        TreeNode *searchBST2(TreeNode *root, int val)
        {
            if (root == nullptr || root->val == val)
                return root;
            return val < root->val ? searchBST2(root->left, val) : searchBST2(root->right, val);
        }

        // Insert into a Binary Search Tree
        // Given the root node of a binary search tree (BST) and a value to be inserted
        // into the tree, insert the value into the BST. Return the root node of the BST
        // after the insertion. It is guaranteed that the new value does not exist in the
        // original BST. Note that there may exist multiple valid ways for the insertion,
        // as long as the tree remains a BST after insertion. You can return any of them.
        // For example, Given the tree:
        //         4
        //        / \
        //       2   7
        //      / \
        //     1   3
        // And the value to insert: 5
        // You can return this binary search tree:
        //          4
        //        /   \
        //       2     7
        //      / \   /
        //     1   3 5
        // This tree is also valid:
        //          5
        //        /   \
        //       2     7
        //      / \   
        //     1   3
        //          \
        //           4
        TreeNode *insertIntoBST(TreeNode *root, int val)
        {
            TreeNode *p = nullptr;
            TreeNode *n = root;
            while (n != nullptr)
            {
                p = n;
                if (n->val > val)
                    n = n->left;
                else
                    n = n->right;
            }
            n = new TreeNode(val);
            if (p == nullptr)
            {
                root = n;
            }
            else
            {
                if (p->val > val)
                    p->left = n;
                else
                    p->right = n;
            }
            return root;
        }

        // Delete Node in a BST
        // Given a root node reference of a BST and a key, delete the node with the given
        // key in the BST. Return the root node reference (possibly updated) of the BST.
        // Basically, the deletion can be divided into two stages:
        // Search for a node to remove.
        // If the node is found, delete the node.
        // Note: Time complexity should be O(height of tree).
        // Example:
        // root = [5,3,6,2,4,null,7]
        // key = 3
        //     5
        //    / \
        //   3   6
        //  / \   \
        // 2   4   7
        // Given key to delete is 3. So we find the node with value 3 and delete it.
        // One valid answer is [5,4,6,2,null,null,7], shown in the following BST.
        //     5
        //    / \
        //   4   6
        //  /     \
        // 2       7
        // Another valid answer is [5,2,6,null,4,null,7].
        //     5
        //    / \
        //   2   6
        //    \   \
        //     4   7
        TreeNode *deleteNode(TreeNode *root, int key)
        {
            function<bool(TreeNode **, TreeNode **)> findNode = [&](TreeNode **parent, TreeNode **node) -> bool {
                *parent = nullptr;
                *node = root;
                while (*node != nullptr)
                {
                    if ((*node)->val == key)
                        break;
                    *parent = *node;
                    if ((*node)->val > key)
                        *node = (*node)->left;
                    else
                        *node = (*node)->right;
                }
                return (*node) != nullptr;
            };
            function<bool(TreeNode *, TreeNode **, TreeNode **)> findSuccessor =
                [&](TreeNode *node, TreeNode **parent, TreeNode **successor) -> bool {
                if (node == nullptr || node->right == nullptr)
                    return false;
                *parent = node;
                *successor = node->right;
                while ((*successor)->left != nullptr)
                {
                    *parent = *successor;
                    *successor = (*successor)->left;
                }
                return true;
            };
            TreeNode *parent = nullptr;
            TreeNode *node = nullptr;
            if (!findNode(&parent, &node))
                return root;
            TreeNode *successorParent = nullptr;
            TreeNode *successor = nullptr;
            if (!findSuccessor(node, &successorParent, &successor))
            {
                if (node == root)
                    root = node->left;
                else if (node == parent->left)
                    parent->left = node->left;
                else if (node == parent->right)
                    parent->right = node->left;
                node->left = nullptr;
                delete node;
                node = nullptr;
                return root;
            }
            TreeNode *successorChild = successor->right;
            if (successor == successorParent->left)
                successorParent->left = successorChild;
            else if (successor == successorParent->right)
                successorParent->right = successorChild;
            successor->right = nullptr;
            successor->left = node->left;
            successor->right = node->right;
            node->left = nullptr;
            node->right = nullptr;
            if (node == root)
                root = successor;
            else if (node == parent->left)
                parent->left = successor;
            else if (node == parent->right)
                parent->right = successor;
            delete node;
            node = nullptr;
            return root;
        }

        // Kth Largest Element in a Stream
        // Design a class to find the kth largest element in a stream. Note that it is
        // the kth largest element in the sorted order, not the kth distinct element.
        // Your KthLargest class will have a constructor which accepts an integer k and
        // an integer array nums, which contains initial elements from the stream. For
        // each call to the method KthLargest.add, return the element representing the
        // kth largest element in the stream.
        // Example:
        // int k = 3;
        // int[] arr = [4,5,8,2];
        // KthLargest kthLargest = new KthLargest(3, arr);
        // kthLargest.add(3);   // returns 4
        // kthLargest.add(5);   // returns 5
        // kthLargest.add(10);  // returns 5
        // kthLargest.add(9);   // returns 8
        // kthLargest.add(4);   // returns 8
        // Note: You may assume that nums' length >= k-1 and k >= 1.
        class KthLargest
        {
        private:
            struct Node
            {
                int val;
                Node *left;
                Node *right;
                int count;
                Node(int v) : val(v), left(nullptr), right(nullptr), count(1) {}
            };
            Node *_root;
            int _k;

            void insert(int v)
            {
                Node *parent = nullptr;
                Node *node = _root;
                while (node != nullptr)
                {
                    parent = node;
                    parent->count++;
                    if (node->val > v)
                        node = node->left;
                    else
                        node = node->right;
                }
                node = new Node(v);
                if (parent == nullptr)
                    _root = node;
                else if (parent->val > v)
                    parent->left = node;
                else
                    parent->right = node;
            }

            int find(int k)
            {
                Node *node = _root;
                while (node != nullptr)
                {
                    int rightCount = node->count - (node->left == nullptr ? 0 : node->left->count);
                    if (rightCount < k)
                    {
                        node = node->left;
                        k -= rightCount;
                    }
                    else if (rightCount > k)
                    {
                        node = node->right;
                    }
                    else
                    {
                        break;
                    }
                }
                if (node == nullptr)
                    throw runtime_error("Not found");
                return node->val;
            }

        public:
            KthLargest(int k, vector<int> &nums)
                : _root(nullptr), _k(k)
            {
                for (int n : nums)
                    insert(n);
            }

            int add(int val)
            {
                insert(val);
                return find(_k);
            }
        };

        // Contains Duplicate III
        // Given an array of integers, find out whether there are two distinct indices i
        // and j in the array such that the absolute difference between nums[i] and nums[j]
        // is at most t and the absolute difference between i and j is at most k.
        // Example 1:
        // Input: nums = [1,2,3,1], k = 3, t = 0
        // Output: true
        // Example 2:
        // Input: nums = [1,0,1,1], k = 1, t = 2
        // Output: true
        // Example 3:
        // Input: nums = [1,5,9,1,5,9], k = 2, t = 3
        // Output: false
        // Hint #1
        // Time complexity O(n logk) - This will give an indication that sorting is involved
        // for k elements.
        // Hide Hint #2
        // Use already existing state to evaluate next state - Like, a set of k sorted
        // numbers are only needed to be tracked. When we are processing the next number
        // in array, then we can utilize the existing sorted state and it is not necessary
        // to sort next overlapping set of k numbers again.
        class ContainsDuplicateIII
        {
        private:
            struct Node
            {
                int val;
                set<int> indices;
                Node *left;
                Node *right;
                Node(int v, int i)
                    : val(v), indices({i}), left(nullptr), right(nullptr)
                {
                }
            };

            Node *root;

            bool insert(int v, int i, int k, int t)
            {
                bool result = false;
                Node *parent = nullptr;
                Node *node = root;
                while (node != nullptr)
                {
                    parent = node;
                    if (abs((long long)node->val - (long long)v) <= (long long)t)
                    {
                        for (int j : node->indices)
                        {
                            if (abs(i - j) <= k)
                            {
                                result = true;
                                break;
                            }
                        }
                    }
                    if (node->val > v)
                    {
                        node = node->left;
                    }
                    else if (node->val < v)
                    {
                        node = node->right;
                    }
                    else
                    {
                        node->indices.insert(i);
                        return result;
                    }
                }
                node = new Node(v, i);
                if (parent == nullptr)
                    root = node;
                else if (parent->val > v)
                    parent->left = node;
                else
                    parent->right = node;
                return result;
            }

            void deleteNode(int v, int i)
            {
                Node *parent = nullptr;
                Node *node = root;
                while (node != nullptr && node->val != v)
                {
                    parent = node;
                    if (node->val > v)
                        node = node->left;
                    else
                        node = node->right;
                }
                if (node == nullptr)
                    return;
                node->indices.erase(i);
                if (!node->indices.empty())
                    return;
                if (node->right == nullptr)
                {
                    if (parent == nullptr)
                        root = node->left;
                    else if (parent->left == node)
                        parent->left = node->left;
                    else
                        parent->right = node->left;
                    node->left = nullptr;
                    delete node;
                    node = nullptr;
                    return;
                }
                Node *nextParent = node;
                Node *next = node->right;
                while (next->left != nullptr)
                {
                    nextParent = next;
                    next = next->left;
                }
                if (nextParent->right == next)
                    nextParent->right = next->right;
                else
                    nextParent->left = next->right;
                next->left = node->left;
                next->right = node->right;
                if (parent == nullptr)
                    root = next;
                else if (parent->left == node)
                    parent->left = next;
                else
                    parent->right = next;
                node->left = nullptr;
                node->right = nullptr;
                delete node;
                node = nullptr;
            }

            void deleteTree(Node *node)
            {
                if (node == nullptr)
                    return;
                deleteTree(node->left);
                node->left = nullptr;
                deleteTree(node->right);
                node->right = nullptr;
                delete node;
            }

        public:
            bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
            {
                bool result = false;
                root = nullptr;
                for (int i = 0; i < (int)nums.size(); i++)
                {
                    if (i > k)
                        deleteNode(nums[i - k - 1], i - k - 1);
                    if (insert(nums[i], i, k, t))
                    {
                        result = true;
                        break;
                    }
                }
                deleteTree(root);
                return result;
            }

            bool containsNearbyAlmostDuplicate2(vector<int> &nums, int k, int t)
            {
                map<int, int> m;
                for (int i = 0; i < (int)nums.size(); i++)
                {
                    if (m.find(nums[i]) == m.end())
                        m[nums[i]] = 1;
                    else
                        m[nums[i]]++;
                    if (i > k)
                    {
                        if (m[nums[i - k - 1]] == 1)
                            m.erase(nums[i - k - 1]);
                        else
                            m[nums[i - k - 1]]--;
                    }
                    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
                    {
                        if (it->second > 1 && t >= 0)
                            return true;
                        map<int, int>::iterator it2 = it;
                        it2++;
                        if (it2 == m.end())
                            break;
                        if ((long long)it2->first - (long long)it->first <= (long long)t)
                            return true;
                    }
                }
                return false;
            }
        };

        // Max Consecutive Ones
        // Given a binary array, find the maximum number of consecutive 1s in this array.
        // Example 1:
        // Input: [1,1,0,1,1,1]
        // Output: 3
        // Explanation: The first two digits or the last three digits are consecutive 1s.
        // The maximum number of consecutive 1s is 3. Note: The input array will only contain 0 and 1.
        // The length of input array is a positive integer and will not exceed 10,000
        int findMaxConsecutiveOnes(const vector<int> &nums)
        {
            int c = 0;
            int m = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (nums[i] == 0)
                {
                    m = max(m, c);
                    c = 0;
                }
                else
                {
                    c++;
                }
            }
            m = max(m, c);
            return m;
        }

        // Find Numbers with Even Number of Digits
        // Given an array nums of integers, return how many of them contain an even number of digits.
        // Example 1:
        // Input: nums = [12,345,2,6,7896]
        // Output: 2
        // Explanation:
        // 12 contains 2 digits (even number of digits).
        // 345 contains 3 digits (odd number of digits).
        // 2 contains 1 digit (odd number of digits).
        // 6 contains 1 digit (odd number of digits).
        // 7896 contains 4 digits (even number of digits).
        // Therefore only 12 and 7896 contain an even number of digits.
        // Example 2:
        // Input: nums = [555,901,482,1771]
        // Output: 1
        // Explanation:
        // Only 1771 contains an even number of digits.
        // Constraints:
        // 1 <= nums.length <= 500
        // 1 <= nums[i] <= 10^5
        int findNumbers(const vector<int> &nums)
        {
            int c = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                int n = nums[i];
                int d = 0;
                while (n > 0)
                {
                    d++;
                    n /= 10;
                }
                if ((d & 0x1) == 0)
                    c++;
            }
            return c;
        }

        // Squares of a Sorted Array
        // Given an array of integers A sorted in non-decreasing order, return an array
        // of the squares of each number, also in sorted non-decreasing order.
        // Example 1:
        // Input: [-4,-1,0,3,10]
        // Output: [0,1,9,16,100]
        // Example 2:
        // Input: [-7,-3,2,3,11]
        // Output: [4,9,9,49,121]
        // Note:
        // 1 <= A.length <= 10000
        // -10000 <= A[i] <= 10000
        // A is sorted in non-decreasing order.
        vector<int> sortedSquares(const vector<int> &A)
        {
            vector<int> r;
            r.resize(A.size());
            int i = 0;
            int j = (int)A.size() - 1;
            int k = j;
            while (i <= j)
            {
                int a = abs(A[i]);
                int b = abs(A[j]);
                if (a <= b)
                {
                    r[k--] = b * b;
                    j--;
                }
                else
                {
                    r[k--] = a * a;
                    i++;
                }
            }
            return r;
        }
        vector<int> sortedSquares2(const vector<int> &A)
        {
            int i = 0;
            int n = (int)A.size();
            int j = n - 1;
            int k = -1;
            while (i + 1 < j)
            {
                k = i + ((j - i) >> 1);
                if (A[k] > 0)
                    j = k;
                else if (A[k] < 0)
                    i = k;
                else
                    break;
            }
            vector<int> r;
            if (i > j)
                return r;
            r.resize(n);
            int t = 0;
            if (i == j)
            {
                r[t++] = A[i] * A[i];
                return r;
            }
            if (i + 1 < j)
            {
                r[t++] = 0;
                i = k - 1;
                j = k + 1;
            }
            while (0 <= i || j < n)
            {
                if (0 <= i && j < n)
                {
                    int a = A[i] * A[i];
                    int b = A[j] * A[j];
                    if (a <= b)
                    {
                        r[t++] = a;
                        i--;
                    }
                    else
                    {
                        r[t++] = b;
                        j++;
                    }
                }
                else if (0 <= i)
                {
                    r[t++] = A[i] * A[i];
                    i--;
                }
                else
                {
                    r[t++] = A[j] * A[j];
                    j++;
                }
            }
            return r;
        }

        // Duplicate Zeros
        // Given a fixed length array arr of integers, duplicate each occurrence of zero,
        // shifting the remaining elements to the right. Note that elements beyond the
        // length of the original array are not written. Do the above modifications to
        // the input array in place, do not return anything from your function.
        // Example 1:
        // Input: [1,0,2,3,0,4,5,0]
        // Output: null
        // Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
        // Example 2:
        // Input: [1,2,3]
        // Output: null
        // Explanation: After calling your function, the input array is modified to: [1,2,3]
        // Note:
        // 1 <= arr.length <= 10000
        // 0 <= arr[i] <= 9
        void duplicateZeros(vector<int> &arr)
        {
            int n = (int)arr.size();
            int c = 0;
            for (int i = 0; i < n; i++)
            {
                if (arr[i] == 0)
                    c++;
            }
            for (int i = n - 1; i >= 0 && c > 0; i--)
            {
                int j = i + c;
                if (j < n)
                    arr[j] = arr[i];
                if (arr[i] == 0)
                {
                    if (j - 1 < n)
                        arr[j - 1] = 0;
                    c--;
                }
            }
        }

        // Check If N and Its Double Exist
        // Given an array arr of integers, check if there exists two integers N and M
        // such that N is the double of M ( i.e. N = 2 * M). More formally check if
        // there exists two indices i and j such that :
        // i != j
        // 0 <= i, j < arr.length
        // arr[i] == 2 * arr[j]
        // Example 1:
        // Input: arr = [10,2,5,3]
        // Output: true
        // Explanation: N = 10 is the double of M = 5,that is, 10 = 2 * 5.
        // Example 2:
        // Input: arr = [7,1,14,11]
        // Output: true
        // Explanation: N = 14 is the double of M = 7,that is, 14 = 2 * 7.
        // Example 3:
        // Input: arr = [3,1,7,11]
        // Output: false
        // Explanation: In this case does not exist N and M, such that N = 2 * M.
        // Constraints:
        // 2 <= arr.length <= 500
        // -10^3 <= arr[i] <= 10^3
        bool checkIfExist(const vector<int> &arr)
        {
            set<int> s;
            for (int i : arr)
            {
                if (s.find(i) != s.end())
                    return true;
                int j;
                if (i >= 0)
                    j = i << 1;
                else
                    j = -((-i) << 1);
                if (s.find(j) == s.end())
                    s.insert(j);
                if ((i & 0x1) == 0)
                {
                    j = i >> 1;
                    if (s.find(j) == s.end())
                        s.insert(j);
                }
            }
            return false;
        }

        // Valid Mountain Array
        // Given an array A of integers, return true if and only if it is a valid
        // mountain array. Recall that A is a mountain array if and only if:
        // A.length >= 3
        // There exists some i with 0 < i < A.length - 1 such that:
        // A[0] < A[1] < ... A[i-1] < A[i]
        // A[i] > A[i+1] > ... > A[A.length - 1]
        // Example 1:
        // Input: [2,1]
        // Output: false
        // Example 2:
        // Input: [3,5,5]
        // Output: false
        // Example 3:
        // Input: [0,3,2,1]
        // Output: true
        // Note:
        // 0 <= A.length <= 10000
        // 0 <= A[i] <= 10000
        bool validMountainArray(const vector<int> &A)
        {
            size_t i = 0;
            while (i + 1 < A.size() && A[i] < A[i + 1])
                i++;
            if (i == 0 || i + 1 >= A.size() || A[i] == A[i + 1])
                return false;
            while (i + 1 < A.size() && A[i] > A[i + 1])
                i++;
            return i + 1 == A.size();
        }
        bool validMountainArray2(const vector<int> &A)
        {
            if (A.size() < 3)
                return false;
            bool up = true;
            for (size_t i = 1; i < A.size(); i++)
            {
                if (A[i - 1] == A[i])
                    return false;
                if (A[i - 1] > A[i])
                {
                    if (i == 1)
                        return false;
                    if (up)
                        up = false;
                }
                else
                {
                    if (!up)
                        return false;
                }
            }
            return !up;
        }

        // Replace Elements with Greatest Element on Right Side
        // Given an array arr, replace every element in that array with the greatest
        // element among the elements to its right, and replace the last element with -1.
        // After doing so, return the array.
        // Example 1:
        // Input: arr = [17,18,5,4,6,1]
        // Output: [18,6,6,6,1,-1]
        // Constraints:
        // 1 <= arr.length <= 10^4
        // 1 <= arr[i] <= 10^5
        vector<int> replaceElements(vector<int> &arr)
        {
            int m = -1;
            for (int i = (int)arr.size() - 1; i >= 0; i--)
            {
                int t = arr[i];
                arr[i] = m;
                m = max(m, t);
            }
            return arr;
        }

        // Move Zeroes
        // Given an array nums, write a function to move all 0's to the end of it while
        // maintaining the relative order of the non-zero elements. Example:
        // Input: [0,1,0,3,12]
        // Output: [1,3,12,0,0]
        // Note: You must do this in-place without making a copy of the array.
        // Minimize the total number of operations.
        void moveZeroes(vector<int> &nums)
        {
            int i = -1;
            for (int j = 0; j < (int)nums.size(); j++)
            {
                if (nums[j] != 0)
                {
                    if (++i < j)
                        swap(nums[i], nums[j]);
                }
            }
        }
        void moveZeroes2(vector<int> &nums)
        {
            int i = -1;
            for (int j = 0; j < (int)nums.size(); j++)
            {
                if (nums[j] != 0)
                {
                    i++;
                    if (i < j)
                        nums[i] = nums[j];
                }
            }
            for (i++; i < (int)nums.size(); i++)
                nums[i] = 0;
        }

        // Sort Array By Parity
        // Given an array A of non-negative integers, return an array consisting of all
        // the even elements of A, followed by all the odd elements of A.
        // You may return any answer array that satisfies this condition. Example 1:
        // Input: [3,1,2,4]
        // Output: [2,4,3,1]
        // The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
        // Note:
        // 1 <= A.length <= 5000
        // 0 <= A[i] <= 5000
        vector<int> sortArrayByParity(vector<int> &A)
        {
            int i = 0;
            int j = (int)A.size() - 1;
            while (i < j)
            {
                if ((A[i] & 0x1) == 0)
                    i++;
                else if ((A[j] & 0x1) == 1)
                    j--;
                else
                    swap(A[i++], A[j--]);
            }
            return A;
        }

        // Height Checker
        // Students are asked to stand in non-decreasing order of heights for an annual
        // photo. Return the minimum number of students that must move in order for all
        // students to be standing in non-decreasing order of height. Notice that when a
        // group of students is selected they can reorder in any possible way between
        // themselves and the non selected students remain on their seats.
        // Example 1:
        // Input: heights = [1,1,4,2,1,3]
        // Output: 3
        // Explanation:
        // Current array : [1,1,4,2,1,3]
        // Target array  : [1,1,1,2,3,4]
        // On index 2 (0-based) we have 4 vs 1 so we have to move this student.
        // On index 4 (0-based) we have 1 vs 3 so we have to move this student.
        // On index 5 (0-based) we have 3 vs 4 so we have to move this student.
        // Example 2:
        // Input: heights = [5,1,2,3,4]
        // Output: 5
        // Example 3:
        // Input: heights = [1,2,3,4,5]
        // Output: 0
        // Constraints:
        // 1 <= heights.length <= 100
        // 1 <= heights[i] <= 100
        int heightChecker(const vector<int> &heights)
        {
            vector<int> s(heights.begin(), heights.end());
            sort(s.begin(), s.end());
            int c = 0;
            for (size_t i = 0; i < s.size(); i++)
            {
                if (s[i] != heights[i])
                    c++;
            }
            return c;
        }

        // Third Maximum Number
        // Given a non-empty array of integers, return the third maximum number in this
        // array. If it does not exist, return the maximum number. The time complexity
        // must be in O(n).
        // Example 1:
        // Input: [3, 2, 1]
        // Output: 1
        // Explanation: The third maximum is 1.
        // Example 2:
        // Input: [1, 2]
        // Output: 2
        // Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
        // Example 3:
        // Input: [2, 2, 3, 1]
        // Output: 1
        // Explanation: Note that the third maximum here means the third maximum distinct number.
        // Both numbers with value 2 are both considered as second maximum.
        int thirdMax(const vector<int> &nums)
        {
            vector<int> m;
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (m.empty())
                {
                    m.push_back(nums[i]);
                }
                else if (m.size() == 1)
                {
                    if (m[0] < nums[i])
                        m.push_back(nums[i]);
                    else if (m[0] > nums[i])
                        m.insert(m.begin(), nums[i]);
                }
                else if (m.size() == 2)
                {
                    if (m[1] < nums[i])
                        m.push_back(nums[i]);
                    else if (m[0] < nums[i] && nums[i] < m[1])
                        m.insert(m.begin() + 1, nums[i]);
                    else if (nums[i] < m[0])
                        m.insert(m.begin(), nums[i]);
                }
                else
                {
                    if (m[2] < nums[i])
                    {
                        m[0] = m[1];
                        m[1] = m[2];
                        m[2] = nums[i];
                    }
                    else if (m[1] < nums[i] && nums[i] < m[2])
                    {
                        m[0] = m[1];
                        m[1] = nums[i];
                    }
                    else if (m[0] < nums[i] && nums[i] < m[1])
                    {
                        m[0] = nums[i];
                    }
                }
            }
            return m.size() == 3 ? m[0] : m.back();
        }

        // Find All Numbers Disappeared in an Array
        // Given an array of integers where 1 <= a[i] <= n (n = size of array), some
        // elements appear twice and others appear once. Find all the elements of
        // [1, n] inclusive that do not appear in this array. Could you do it without
        // extra space and in O(n) runtime? You may assume the returned list does not
        // count as extra space. Example:
        // Input: [4,3,2,7,8,2,3,1]
        // Output: [5,6]
        vector<int> findDisappearedNumbers(vector<int> &nums)
        {
            for (int i = 0; i < (int)nums.size(); i++)
            {
                while (nums[i] != i + 1 and nums[i] != nums[nums[i] - 1])
                {
                    int t = nums[i];
                    nums[i] = nums[t - 1];
                    nums[t - 1] = t;
                }
            }
            vector<int> r;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (nums[i] != i + 1)
                    r.push_back(i + 1);
            }
            return r;
        }

        // Design Linked List
        // Design your implementation of the linked list. You can choose to use the
        // singly linked list or the doubly linked list. A node in a singly linked list
        // should have two attributes: val and next. val is the value of the current
        // node, and next is a pointer/reference to the next node. If you want to use
        // the doubly linked list, you will need one more attribute prev to indicate the
        // previous node in the linked list. Assume all nodes in the linked list are 0-indexed.
        // Implement these functions in your linked list class:
        // get(index) : Get the value of the index-th node in the linked list. If the index
        // is invalid, return -1.
        // addAtHead(val) : Add a node of value val before the first element of the linked
        // list. After the insertion, the new node will be the first node of the linked list.
        // addAtTail(val) : Append a node of value val to the last element of the linked list.
        // addAtIndex(index, val) : Add a node of value val before the index-th node in the
        // linked list. If index equals to the length of linked list, the node will be appended
        // to the end of linked list. If index is greater than the length, the node will not be inserted.
        // deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.
        // Example:
        // Input:
        // ["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]
        // [[],[1],[3],[1,2],[1],[1],[1]]
        // Output:
        // [null,null,null,null,2,null,3]
        // Explanation:
        // MyLinkedList linkedList = new MyLinkedList(); // Initialize empty LinkedList
        // linkedList.addAtHead(1);
        // linkedList.addAtTail(3);
        // linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
        // linkedList.get(1);            // returns 2
        // linkedList.deleteAtIndex(1);  // now the linked list is 1->3
        // linkedList.get(1);            // returns 3
        // Constraints:
        // 0 <= index,val <= 1000
        // Please do not use the built-in LinkedList library.
        // At most 2000 calls will be made to get, addAtHead, addAtTail,  addAtIndex and deleteAtIndex.
        class MyLinkedList
        {
        private:
            struct Node
            {
                int val;
                Node *next;
                Node(int v) : val(v), next(nullptr) {}
            };

            Node *head;
            Node *tail;

        public:
            /** Initialize your data structure here. */
            MyLinkedList()
            {
                head = nullptr;
                tail = nullptr;
            }

            /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
            int get(int index)
            {
                Node *p = head;
                for (int i = 0; i < index && p != nullptr; i++)
                    p = p->next;
                return p == nullptr ? -1 : p->val;
            }

            /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
            void addAtHead(int val)
            {
                Node *n = new Node(val);
                n->next = head;
                head = n;
                if (tail == nullptr)
                    tail = n;
            }

            /** Append a node of value val to the last element of the linked list. */
            void addAtTail(int val)
            {
                Node *n = new Node(val);
                if (tail == nullptr)
                    head = n;
                else
                    tail->next = n;
                tail = n;
            }

            /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
            void addAtIndex(int index, int val)
            {
                if (index == 0)
                {
                    addAtHead(val);
                    return;
                }
                Node *p = head;
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index)
                {
                    Node *n = new Node(val);
                    n->next = p->next;
                    p->next = n;
                    if (n->next == nullptr)
                        tail = n;
                }
            }

            /** Delete the index-th node in the linked list, if the index is valid. */
            void deleteAtIndex(int index)
            {
                Node *p = head;
                if (index == 0)
                {
                    if (head != nullptr)
                    {
                        Node *p = head;
                        head = head->next;
                        delete p;
                        p = nullptr;
                        if (head == nullptr || head->next == nullptr)
                            tail = head;
                    }
                    return;
                }
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index && p->next != nullptr)
                {
                    Node *t = p->next;
                    if (tail == t)
                        tail = p;
                    p->next = t->next;
                    delete t;
                    t = nullptr;
                }
            }
        };
        class MyDoubleLinkedList
        {
        private:
            struct Node
            {
                int val;
                Node *prev;
                Node *next;
                Node(int v) : val(v), prev(nullptr), next(nullptr) {}
            };

            Node *head;
            Node *tail;

        public:
            /** Initialize your data structure here. */
            MyDoubleLinkedList()
            {
                head = nullptr;
                tail = nullptr;
            }

            /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
            int get(int index)
            {
                Node *p = head;
                for (int i = 0; i < index && p != nullptr; i++)
                    p = p->next;
                return p == nullptr ? -1 : p->val;
            }

            /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
            void addAtHead(int val)
            {
                Node *n = new Node(val);
                n->next = head;
                if (head != nullptr)
                    head->prev = n;
                head = n;
                if (tail == nullptr)
                    tail = n;
            }

            /** Append a node of value val to the last element of the linked list. */
            void addAtTail(int val)
            {
                Node *n = new Node(val);
                if (tail == nullptr)
                    head = n;
                else
                    tail->next = n;
                n->prev = tail;
                tail = n;
            }

            /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
            void addAtIndex(int index, int val)
            {
                if (index == 0)
                {
                    addAtHead(val);
                    return;
                }
                Node *p = head;
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index)
                {
                    Node *n = new Node(val);
                    n->next = p->next;
                    if (p->next != nullptr)
                        p->next->prev = n;
                    p->next = n;
                    n->prev = p;
                    if (n->next == nullptr)
                        tail = n;
                }
            }

            /** Delete the index-th node in the linked list, if the index is valid. */
            void deleteAtIndex(int index)
            {
                Node *p = head;
                if (index == 0)
                {
                    if (head != nullptr)
                    {
                        Node *p = head;
                        head = head->next;
                        delete p;
                        p = nullptr;
                        if (head == nullptr || head->next == nullptr)
                            tail = head;
                        else
                            head->prev = nullptr;
                    }
                    return;
                }
                int i;
                for (i = 1; i < index && p->next != nullptr; i++)
                    p = p->next;
                if (i == index && p->next != nullptr)
                {
                    Node *t = p->next;
                    if (tail == t)
                        tail = p;
                    p->next = t->next;
                    if (t->next != nullptr)
                        t->next->prev = p;
                    delete t;
                    t = nullptr;
                }
            }
        };

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

        // Palindrome Linked List
        // Given a singly linked list, determine if it is a palindrome.
        // Example 1:
        // Input: 1->2
        // Output: false
        // Example 2:
        // Input: 1->2->2->1
        // Output: true
        // Follow up: Could you do it in O(n) time and O(1) space?
        bool isPalindrome(ListNode *head)
        {
            if (head == nullptr || head->next == nullptr)
                return true;
            function<ListNode *(ListNode *)> reverse = [&](ListNode *h) -> ListNode * {
                if (h == nullptr)
                    return nullptr;
                ListNode *t = h;
                while (t->next != nullptr)
                {
                    ListNode *p = t->next;
                    t->next = p->next;
                    p->next = h;
                    h = p;
                }
                return h;
            };
            ListNode *p = head;
            ListNode *q = head;
            while (q->next != nullptr && q->next->next != nullptr)
            {
                p = p->next;
                q = q->next->next;
            }
            bool oddCount = (q->next == nullptr);
            ListNode *h2 = p->next;
            p->next = nullptr;
            head = reverse(head);
            p = oddCount ? head->next : head;
            q = h2;
            bool result = true;
            while (p != nullptr && q != nullptr)
            {
                if (p->val != q->val)
                {
                    result = false;
                    break;
                }
                p = p->next;
                q = q->next;
            }
            if (result && !(p == nullptr && q == nullptr))
                result = false;
            p = head;
            head = reverse(head);
            p->next = h2;
            return result;
        }

        class MultilevelDoubleLinkedList
        {
        public:
            struct Node
            {
                int val;
                Node *prev;
                Node *next;
                Node *child;
            };

            // Flatten a Multilevel Doubly Linked List
            // You are given a doubly linked list which in addition to the next and previous
            // pointers, it could have a child pointer, which may or may not point to a
            // separate doubly linked list. These child lists may have one or more children
            // of their own, and so on, to produce a multilevel data structure, as shown in
            // the example below.
            // Flatten the list so that all the nodes appear in a single-level, doubly linked
            // list. You are given the head of the first level of the list.
            // Example 1:
            // Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
            // Output: [1,2,3,7,8,11,12,9,10,4,5,6]
            // Explanation:
            // The multilevel linked list in the input is as follows:
            // After flattening the multilevel linked list it becomes:
            // Example 2:
            // Input: head = [1,2,null,3]
            // Output: [1,3,2]
            // Explanation:
            // The input multilevel linked list is as follows:
            //   1---2---NULL
            //   |
            //   3---NULL
            // Example 3:
            // Input: head = []
            // Output: []
            // How multilevel linked list is represented in test case:
            // We use the multilevel linked list from Example 1 above:
            //  1---2---3---4---5---6--NULL
            //          |
            //          7---8---9---10--NULL
            //              |
            //              11--12--NULL
            // The serialization of each level is as follows:
            // [1,2,3,4,5,6,null]
            // [7,8,9,10,null]
            // [11,12,null]
            // To serialize all levels together we will add nulls in each level to signify no node connects to the upper node of the previous level. The serialization becomes:
            // [1,2,3,4,5,6,null]
            // [null,null,7,8,9,10,null]
            // [null,11,12,null]
            // Merging the serialization of each level and removing trailing nulls we obtain:
            // [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
            // Constraints:
            // Number of Nodes will not exceed 1000.
            // 1 <= Node.val <= 10^5
            Node *flatten(Node *head)
            {
                if (head == nullptr)
                    return nullptr;
                function<Node *(Node *)> flat = [&](Node *h) -> Node * {
                    Node *t = h;
                    while (h != nullptr)
                    {
                        if (h->child == nullptr)
                        {
                            t = h;
                            h = h->next;
                        }
                        else
                        {
                            Node *ch = h->child;
                            Node *ct = flat(ch);
                            ct->next = h->next;
                            if (h->next != nullptr)
                                h->next->prev = ct;
                            h->next = ch;
                            ch->prev = h;
                            h->child = nullptr;
                            t = ct;
                            h = ct->next;
                        }
                    }
                    return t;
                };
                flat(head);
                return head;
            }
            Node *flatten2(Node *head)
            {
                stack<Node *> s;
                Node *n = head;
                Node *t = head;
                while (!s.empty() || n != nullptr)
                {
                    if (n != nullptr)
                    {
                        if (n->child == nullptr)
                        {
                            t = n;
                            n = n->next;
                        }
                        else
                        {
                            s.push(n);
                            n = n->child;
                            t = n;
                        }
                    }
                    else
                    {
                        n = s.top();
                        s.pop();
                        t->next = n->next;
                        if (n->next != nullptr)
                            n->next->prev = t;
                        n->next = n->child;
                        n->child->prev = n;
                        n->child = nullptr;
                        n = t->next;
                    }
                }
                return head;
            }
        };

        // Find Pivot Index
        // Given an array of integers nums, write a method that returns the "pivot"
        // index of this array. We define the pivot index as the index where the sum
        // of the numbers to the left of the index is equal to the sum of the numbers
        // to the right of the index. If no such index exists, we should return -1. If
        // there are multiple pivot indexes, you should return the left-most pivot index.
        // Example 1:
        // Input:
        // nums = [1, 7, 3, 6, 5, 6]
        // Output: 3
        // Explanation:
        // The sum of the numbers to the left of index 3 (nums[3] = 6) is equal to the
        // sum of numbers to the right of index 3. Also, 3 is the first index where this occurs.
        // Example 2:
        // Input:
        // nums = [1, 2, 3]
        // Output: -1
        // Explanation:
        // There is no index that satisfies the conditions in the problem statement.
        // Note:
        // The length of nums will be in the range [0, 10000].
        // Each element nums[i] will be an integer in the range [-1000, 1000].
        // Hide Hint #1
        // We can precompute prefix sums P[i] = nums[0] + nums[1] + ... + nums[i-1]. Then
        // for each index, the left sum is P[i], and the right sum is P[P.length - 1] - P[i] - nums[i].
        int pivotIndex(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            vector<int> p(nums.size());
            int s = 0;
            for (size_t i = 0; i < nums.size(); i++)
            {
                s += nums[i];
                p[i] = s;
            }
            if (p[nums.size() - 1] - nums[0] == 0)
                return 0;
            for (size_t i = 1; i + 1 < nums.size(); i++)
            {
                if (p[i - 1] == p[nums.size() - 1] - nums[i] - p[i - 1])
                    return i;
            }
            if (p[nums.size() - 1] - nums[nums.size() - 1] == 0)
                return nums.size() - 1;
            return -1;
        }

        // Largest Number At Least Twice of Others
        // In a given integer array nums, there is always exactly one largest element.
        // Find whether the largest element in the array is at least twice as much as
        // every other number in the array. If it is, return the index of the largest
        // element, otherwise return -1.
        // Example 1:
        // Input: nums = [3, 6, 1, 0]
        // Output: 1
        // Explanation: 6 is the largest integer, and for every other number in the array x,
        // 6 is more than twice as big as x.  The index of value 6 is 1, so we return 1.
        // Example 2:
        // Input: nums = [1, 2, 3, 4]
        // Output: -1
        // Explanation: 4 isn't at least as big as twice the value of 3, so we return -1.
        // Note:
        // nums will have a length in the range [1, 50].
        // Every nums[i] will be an integer in the range [0, 99].
        // Hide Hint #1
        // Scan through the array to find the unique largest element m, keeping track of
        // it's index maxIndex. Scan through the array again. If we find some x != m
        // with m < 2*x, we should return -1. Otherwise, we should return maxIndex.
        int dominantIndex(const vector<int> &nums)
        {
            if (nums.empty())
                return -1;
            if (nums.size() == 1)
                return 0;
            int a;
            int b;
            if (nums[0] <= nums[1])
            {
                a = 0;
                b = 1;
            }
            else
            {
                a = 1;
                b = 0;
            }
            for (size_t i = 2; i < nums.size(); i++)
            {
                if (nums[b] <= nums[i])
                {
                    a = b;
                    b = i;
                }
                else if (nums[a] <= nums[i])
                {
                    a = i;
                }
            }
            if ((nums[a] << 1) <= nums[b])
                return b;
            else
                return -1;
        }

        // Diagonal Traverse
        // Given a matrix of M x N elements (M rows, N columns), return all elements of
        // the matrix in diagonal order as shown in the below image.
        // Example:
        // Input:
        // [
        //  [ 1, 2, 3 ],
        //  [ 4, 5, 6 ],
        //  [ 7, 8, 9 ]
        // ]
        // Output:  [1,2,4,7,5,3,6,8,9]
        // The total number of elements of the given matrix will not exceed 10,000.
        vector<int> findDiagonalOrder(const vector<vector<int>> &matrix)
        {
            vector<int> o;
            if (matrix.empty() || matrix[0].empty())
                return o;
            bool up = true;
            int m = (int)matrix.size();
            int n = (int)matrix[0].size();
            for (int j = 0; j < n; j++)
            {
                if (up)
                {
                    for (int i = min(m - 1, j); i >= 0; i--)
                        o.push_back(matrix[i][j - i]);
                }
                else
                {
                    for (int i = 0; i <= min(m - 1, j); i++)
                        o.push_back(matrix[i][j - i]);
                }
                up = !up;
            }
            for (int i = 1; i < m; i++)
            {
                if (up)
                {
                    for (int j = max(0, n - m + i); j < n; j++)
                        o.push_back(matrix[n - 1 - j + i][j]);
                }
                else
                {
                    for (int j = n - 1; j >= max(0, n - m + i); j--)
                        o.push_back(matrix[n - 1 - j + i][j]);
                }
                up = !up;
            }
            return o;
        }

        // Reverse String
        // Write a function that reverses a string. The input string is given as
        // an array of characters char[]. Do not allocate extra space for another
        // array, you must do this by modifying the input array in-place with O(1)
        // extra memory. You may assume all the characters consist of printable
        // ascii characters.
        // Example 1:
        // Input: ["h","e","l","l","o"]
        // Output: ["o","l","l","e","h"]
        // Example 2:
        // Input: ["H","a","n","n","a","h"]
        // Output: ["h","a","n","n","a","H"]
        void reverseString(vector<char> &s)
        {
            int i = 0;
            int j = (int)s.size() - 1;
            while (i < j)
                swap(s[i++], s[j--]);
        }
        void reverseString2(vector<char> &s)
        {
            function<void(int, int)> reverse = [&](int i, int j) {
                if (i >= j)
                    return;
                swap(s[i], s[j]);
                reverse(i + 1, j - 1);
            };
            reverse(0, (int)s.size() - 1);
        }

        // Array Partition I
        // Given an array of 2n integers, your task is to group these integers into n
        // pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of
        // min(ai, bi) for all i from 1 to n as large as possible.
        // Example 1:
        // Input: [1,4,3,2]
        // Output: 4
        // Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
        // Note:
        // n is a positive integer, which is in the range of [1, 10000].
        // All the integers in the array will be in the range of [-10000, 10000].
        // Suppose a0 < a1 < a2 < a3, then
        // min(a0, a1) + min(a2, a3) > min(a0, a2) + min(a1, a3)
        int arrayPairSum(vector<int> &nums)
        {
            sort(nums.begin(), nums.end());
            int s = 0;
            for (size_t i = 0; i < nums.size(); i += 2)
                s += nums[i];
            return s;
        }

        // Design Circular Queue
        // Design your implementation of the circular queue. The circular queue is a
        // linear data structure in which the operations are performed based on FIFO
        // (First In First Out) principle and the last position is connected back to
        // the first position to make a circle. It is also called "Ring Buffer".
        // One of the benefits of the circular queue is that we can make use of the
        // spaces in front of the queue. In a normal queue, once the queue becomes
        // full, we cannot insert the next element even if there is a space in front
        // of the queue. But using the circular queue, we can use the space to store
        // new values. Your implementation should support following operations:
        // MyCircularQueue(k): Constructor, set the size of the queue to be k.
        // Front: Get the front item from the queue. If the queue is empty, return -1.
        // Rear: Get the last item from the queue. If the queue is empty, return -1.
        // enQueue(value): Insert an element into the circular queue. Return true if the operation is successful.
        // deQueue(): Delete an element from the circular queue. Return true if the operation is successful.
        // isEmpty(): Checks whether the circular queue is empty or not.
        // isFull(): Checks whether the circular queue is full or not.
        // Example:
        // MyCircularQueue circularQueue = new MyCircularQueue(3); // set the size to be 3
        // circularQueue.enQueue(1);  // return true
        // circularQueue.enQueue(2);  // return true
        // circularQueue.enQueue(3);  // return true
        // circularQueue.enQueue(4);  // return false, the queue is full
        // circularQueue.Rear();  // return 3
        // circularQueue.isFull();  // return true
        // circularQueue.deQueue();  // return true
        // circularQueue.enQueue(4);  // return true
        // circularQueue.Rear();  // return 4
        // Note:
        // All values will be in the range of [0, 1000].
        // The number of operations will be in the range of [1, 1000].
        // Please do not use the built-in Queue library.
        class MyCircularQueue
        {
        private:
            vector<int> que;
            int head;
            int tail;

        public:
            /** Initialize your data structure here. Set the size of the queue to be k. */
            MyCircularQueue(int k)
            {
                que.resize(k);
                head = -1;
                tail = -1;
            }

            /** Insert an element into the circular queue. Return true if the operation is successful. */
            bool enQueue(int value)
            {
                if (isFull())
                    return false;
                if (head == -1)
                {
                    head = 0;
                    tail = 0;
                }
                else
                {
                    tail = (tail + 1) % (int)que.size();
                }
                que[tail] = value;
                return true;
            }

            /** Delete an element from the circular queue. Return true if the operation is successful. */
            bool deQueue()
            {
                if (isEmpty())
                    return false;
                if (head == tail)
                {
                    head = -1;
                    tail = -1;
                }
                else
                {
                    head = (head + 1) % (int)que.size();
                }
                return true;
            }

            /** Get the front item from the queue. */
            int Front()
            {
                return isEmpty() ? -1 : que[head];
            }

            /** Get the last item from the queue. */
            int Rear()
            {
                return isEmpty() ? -1 : que[tail];
            }

            /** Checks whether the circular queue is empty or not. */
            bool isEmpty()
            {
                return head == -1;
            }

            /** Checks whether the circular queue is full or not. */
            bool isFull()
            {
                return ((tail + 1) % (int)que.size()) == head;
            }
        };

        // Open the Lock
        // You have a lock in front of you with 4 circular wheels. Each wheel has 10
        // slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can
        // rotate freely and wrap around: for example we can turn '9' to be '0', or
        // '0' to be '9'. Each move consists of turning one wheel one slot.
        // The lock initially starts at '0000', a string representing the state of the 4 wheels.
        // You are given a list of deadends dead ends, meaning if the lock displays
        // any of these codes, the wheels of the lock will stop turning and you will
        // be unable to open it. Given a target representing the value of the wheels
        // that will unlock the lock, return the minimum total number of turns required
        // to open the lock, or -1 if it is impossible.
        // Example 1:
        // Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
        // Output: 6
        // Explanation:
        // A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
        // Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
        // because the wheels of the lock become stuck after the display becomes the dead end "0102".
        // Example 2:
        // Input: deadends = ["8888"], target = "0009"
        // Output: 1
        // Explanation:
        // We can turn the last wheel in reverse to move from "0000" -> "0009".
        // Example 3:
        // Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
        // Output: -1
        // Explanation:
        // We can't reach the target without getting stuck.
        // Example 4:
        // Input: deadends = ["0000"], target = "8888"
        // Output: -1
        // Note:
        // The length of deadends will be in the range [1, 500].
        // target will not be in the list deadends.
        // Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities '0000' to '9999'.
        int openLock(const vector<string> &deadends, const string &target)
        {
            set<string> deadendset(deadends.begin(), deadends.end());
            if (deadendset.find("0000") != deadendset.end())
                return -1;
            set<string> visited;
            queue<string> currentq;
            currentq.push("0000");
            visited.insert("0000");
            queue<string> nextq;
            int c = 0;
            while (!currentq.empty())
            {
                while (!currentq.empty())
                {
                    string s = currentq.front();
                    currentq.pop();
                    if (s == target)
                        return c;
                    for (int i = 0; i < 4; i++)
                    {
                        string n = s;
                        n[i] = '0' + ((s[i] - '0' + 9) % 10);
                        if (deadendset.find(n) == deadendset.end() && visited.find(n) == visited.end())
                        {
                            nextq.push(n);
                            visited.insert(n);
                        }
                        n = s;
                        n[i] = '0' + ((s[i] - '0' + 1) % 10);
                        if (deadendset.find(n) == deadendset.end() && visited.find(n) == visited.end())
                        {
                            nextq.push(n);
                            visited.insert(n);
                        }
                    }
                }
                c++;
                currentq.swap(nextq);
            }
            return -1;
        }

        // Perfect Squares
        // Given a positive integer n, find the least number of perfect square numbers
        // (for example, 1, 4, 9, 16, ...) which sum to n.
        // Example 1:
        // Input: n = 12
        // Output: 3
        // Explanation: 12 = 4 + 4 + 4.
        // Example 2:
        // Input: n = 13
        // Output: 2
        // Explanation: 13 = 4 + 9.
        int numSquares(int n)
        {
            set<int> visited;
            queue<int> current;
            current.push(n);
            visited.insert(n);
            queue<int> next;
            int c = 0;
            while (!current.empty())
            {
                while (!current.empty())
                {
                    n = current.front();
                    current.pop();
                    int s = (int)sqrt(n);
                    for (int i = 1; i <= s; i++)
                    {
                        int i2 = i * i;
                        if (i2 == n)
                            return c + 1;
                        i2 = n - i2;
                        if (visited.find(i2) == visited.end())
                        {
                            next.push(i2);
                            visited.insert(i2);
                        }
                    }
                }
                c++;
                current.swap(next);
            }
            throw runtime_error("not found");
        }

        // Daily Temperatures
        // Given a list of daily temperatures T, return a list such that, for each day
        // in the input, tells you how many days you would have to wait until a warmer
        // temperature. If there is no future day for which this is possible, put 0 instead.
        // For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73],
        // your output should be [1, 1, 4, 2, 1, 1, 0, 0].
        // Note: The length of temperatures will be in the range [1, 30000]. Each
        // temperature will be an integer in the range [30, 100].
        vector<int> dailyTemperatures(const vector<int> &T)
        {
            vector<int> o(T.size(), 0);
            stack<int> s;
            for (int i = 0; i < (int)T.size(); i++)
            {
                while (!s.empty() && T[s.top()] < T[i])
                {
                    int j = s.top();
                    s.pop();
                    o[j] = i - j;
                }
                s.push(i);
            }
            return o;
        }
        vector<int> dailyTemperatures2(const vector<int> &T)
        {
            vector<int> o(T.size(), 0);
            stack<int> s;
            for (int i = (int)T.size() - 1; i >= 0; i--)
            {
                while (!s.empty() && T[i] >= T[s.top()])
                    s.pop();
                if (s.empty())
                    o[i] = 0;
                else
                    o[i] = s.top() - i;
                s.push(i);
            }
            return o;
        }

        // Target Sum
        // You are given a list of non-negative integers, a1, a2, ..., an, and a
        // target, S. Now you have 2 symbols + and -. For each integer, you should
        // choose one from + and - as its new symbol. Find out how many ways to
        // assign symbols to make sum of integers equal to target S.
        // Example 1:
        // Input: nums is [1, 1, 1, 1, 1], S is 3.
        // Output: 5
        // Explanation:
        // -1+1+1+1+1 = 3
        // +1-1+1+1+1 = 3
        // +1+1-1+1+1 = 3
        // +1+1+1-1+1 = 3
        // +1+1+1+1-1 = 3
        // There are 5 ways to assign symbols to make the sum of nums be target 3.
        // Note:
        // The length of the given array is positive and will not exceed 20.
        // The sum of elements in the given array will not exceed 1000.
        // Your output answer is guaranteed to be fitted in a 32-bit integer.
        int findTargetSumWays(const vector<int> &nums, int S)
        {
            map<pair<int, long long>, int> m;
            // Use long long because may overflow if it is INT_MAX
            function<int(int, long long)> count = [&](int i, long long a) -> int {
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ")" << endl;
                if (i >= (int)nums.size())
                    return a == 0 ? 1 : 0;
                pair<int, long long> p = make_pair(i, a);
                if (m.find(p) == m.end())
                    m[p] = count(i + 1, a + nums[i]) + count(i + 1, a - nums[i]);
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ") = " << m[p] << endl;
                return m[p];
            };
            return count(0, S);
        }
        int findTargetSumWays2(const vector<int> &nums, int S)
        {
            map<pair<int, long long>, int> m;
            // Use long long because may overflow if it is INT_MAX
            function<int(int, long long)> count = [&](int i, long long a) -> int {
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ")" << endl;
                if (i >= (int)nums.size())
                    return 0;
                pair<int, long long> p = make_pair(i, a);
                if (m.find(p) == m.end())
                {
                    if (i + 1 == (int)nums.size())
                        m[p] = ((a == nums[i] || -a == nums[i]) ? (a == 0 ? 2 : 1) : 0);
                    else
                        m[p] = count(i + 1, a + nums[i]) + count(i + 1, a - nums[i]);
                }
                // cout << string(i * 2, ' ') << "c(" << i << "," << a << ") = " << m[p] << endl;
                return m[p];
            };
            return count(0, S);
        }
        int findTargetSumWays3(const vector<int> &nums, int S)
        {
            int c = 0;
            function<void(int, int)> count = [&](int i, int a) {
                if (i >= (int)nums.size())
                {
                    if (a == S)
                        c++;
                    return;
                }
                count(i + 1, a - nums[i]);
                count(i + 1, a + nums[i]);
            };
            count(0, 0);
            return c;
        }

        // Implement Queue using Stacks
        // Implement the following operations of a queue using stacks.
        // push(x) -- Push element x to the back of queue.
        // pop() -- Removes the element from in front of queue.
        // peek() -- Get the front element.
        // empty() -- Return whether the queue is empty.
        // Example:
        // MyQueue queue = new MyQueue();
        // queue.push(1);
        // queue.push(2);
        // queue.peek();  // returns 1
        // queue.pop();   // returns 1
        // queue.empty(); // returns false
        class MyQueue
        {
        private:
            stack<int> back;
            stack<int> front;
            void flush()
            {
                if (front.empty())
                {
                    while (!back.empty())
                    {
                        front.push(back.top());
                        back.pop();
                    }
                }
            }

        public:
            /** Initialize your data structure here. */
            MyQueue()
            {
            }

            /** Push element x to the back of queue. */
            void push(int x)
            {
                back.push(x);
            }

            /** Removes the element from in front of queue and returns that element. */
            int pop()
            {
                flush();
                int v = front.top();
                front.pop();
                return v;
            }

            /** Get the front element. */
            int peek()
            {
                flush();
                return front.top();
            }

            /** Returns whether the queue is empty. */
            bool empty()
            {
                return front.empty() && back.empty();
            }
        };

        // Implement Stack using Queues
        // Implement the following operations of a stack using queues.
        // push(x) -- Push element x onto stack.
        // pop() -- Removes the element on top of the stack.
        // top() -- Get the top element.
        // empty() -- Return whether the stack is empty.
        // Example:
        // MyStack stack = new MyStack();
        // stack.push(1);
        // stack.push(2);
        // stack.top();   // returns 2
        // stack.pop();   // returns 2
        // stack.empty(); // returns false
        class MyStack
        {
        private:
            queue<int> q0;
            queue<int> q1;
            void flush(queue<int> &from, queue<int> &to)
            {
                while (from.size() > 1)
                {
                    to.push(from.front());
                    from.pop();
                }
            }

        public:
            /** Initialize your data structure here. */
            MyStack()
            {
            }

            /** Push element x onto stack. */
            void push(int x)
            {
                if (q1.empty())
                    q0.push(x);
                else
                    q1.push(x);
            }

            /** Removes the element on top of the stack and returns that element. */
            int pop()
            {
                int v;
                if (q1.empty())
                {
                    flush(q0, q1);
                    v = q0.front();
                    q0.pop();
                }
                else
                {
                    flush(q1, q0);
                    v = q1.front();
                    q1.pop();
                }
                return v;
            }

            /** Get the top element. */
            int top()
            {
                int v;
                if (q1.empty())
                {
                    flush(q0, q1);
                    v = q0.front();
                    q1.push(v);
                    q0.pop();
                }
                else
                {
                    flush(q1, q0);
                    v = q1.front();
                    q0.push(v);
                    q1.pop();
                }
                return v;
            }

            /** Returns whether the stack is empty. */
            bool empty()
            {
                return q0.empty() && q1.empty();
            }
        };

        // Decode String
        // Given an encoded string, return its decoded string.
        // The encoding rule is: k[encoded_string], where the encoded_string inside the
        // square brackets is being repeated exactly k times. Note that k is guaranteed
        // to be a positive integer. You may assume that the input string is always valid;
        // No extra white spaces, square brackets are well-formed, etc. Furthermore, you
        // may assume that the original data does not contain any digits and that digits
        // are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].
        // Examples:
        // s = "3[a]2[bc]", return "aaabcbc".
        // s = "3[a2[c]]", return "accaccacc".
        // s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
        string decodeString(const string &s)
        {
            function<string(size_t &)> decode = [&](size_t &i) -> string {
                if (i >= s.size())
                    return "";
                ostringstream oss;
                while (i < s.size())
                {
                    while (i < s.size() && (s[i] < '0' || s[i] > '9') && s[i] != ']')
                        oss << s[i++];
                    if (i >= s.size())
                        break;
                    if (s[i] == ']')
                    {
                        i++;
                        break;
                    }
                    int k = 0;
                    while (i < s.size() && '0' <= s[i] && s[i] <= '9')
                        k = (k * 10) + s[i++] - '0';
                    i++; // skip '['
                    string c = decode(i);
                    for (; k > 0; k--)
                        oss << c;
                }
                return oss.str();
            };
            size_t i = 0;
            return decode(i);
        }
        string decodeString2(const string &s)
        {
            stack<pair<string, int>> stk;
            string o;
            size_t i = 0;
            while (i < s.size())
            {
                if ((s[i] < '0' || s[i] > '9') && s[i] != ']')
                {
                    o.append(1, s[i++]);
                }
                else if (s[i] == ']')
                {
                    pair<string, int> p = stk.top();
                    stk.pop();
                    for (; p.second > 0; p.second--)
                        p.first.append(o);
                    o = p.first;
                    i++;
                }
                else
                {
                    int k = 0;
                    while (i < s.size() && '0' <= s[i] && s[i] <= '9')
                        k = k * 10 + s[i++] - '0';
                    i++; // skip '['
                    stk.push(make_pair(o, k));
                    o = "";
                }
            }
            return o;
        }

        // Flood Fill
        // An image is represented by a 2-D array of integers, each integer representing
        // the pixel value of the image (from 0 to 65535). Given a coordinate (sr, sc)
        // representing the starting pixel (row and column) of the flood fill, and a pixel
        // value newColor, "flood fill" the image. To perform a "flood fill", consider
        // the starting pixel, plus any pixels connected 4-directionally to the starting
        // pixel of the same color as the starting pixel, plus any pixels connected
        // 4-directionally to those pixels (also with the same color as the starting pixel),
        // and so on. Replace the color of all of the aforementioned pixels with the newColor.
        // At the end, return the modified image.
        // Example 1:
        // Input:
        // image = [[1,1,1],
        //          [1,1,0],
        //          [1,0,1]]
        // sr = 1, sc = 1, newColor = 2
        // Output: [[2,2,2],
        //          [2,2,0],
        //          [2,0,1]]
        // Explanation:
        // From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected
        // by a path of the same color as the starting pixel are colored with the new color.
        // Note the bottom corner is not colored 2, because it is not 4-directionally connected
        // to the starting pixel. Note:
        // The length of image and image[0] will be in the range [1, 50].
        // The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
        // The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
        vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
        {
            int c = image[sr][sc];
            if (c == newColor)
                return image; // no change needed
            int m = (int)image.size();
            int n = (int)image[0].size();
            function<void(int, int)> flood = [&](int i, int j) {
                if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != c)
                    return;
                image[i][j] = newColor;
                flood(i - 1, j);
                flood(i, j + 1);
                flood(i + 1, j);
                flood(i, j - 1);
            };
            flood(sr, sc);
            return image;
        }
        vector<vector<int>> floodFill2(vector<vector<int>> &image, int sr, int sc, int newColor)
        {
            int c = image[sr][sc];
            int m = (int)image.size();
            int n = (int)image[0].size();
            stack<pair<int, int>> path;
            set<pair<int, int>> visited;
            path.push(make_pair(sr, sc));
            visited.insert(path.top());
            function<void(int, int)> check = [&](int i, int j) {
                if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != c)
                    return;
                pair<int, int> p = make_pair(i, j);
                if (visited.find(p) == visited.end())
                {
                    path.push(p);
                    visited.insert(p);
                }
            };
            while (!path.empty())
            {
                pair<int, int> p = path.top();
                path.pop();
                image[p.first][p.second] = newColor;
                check(p.first - 1, p.second);
                check(p.first, p.second + 1);
                check(p.first + 1, p.second);
                check(p.first, p.second - 1);
            }
            return image;
        }
        vector<vector<int>> floodFill3(vector<vector<int>> &image, int sr, int sc, int newColor)
        {
            int c = image[sr][sc];
            int m = (int)image.size();
            int n = (int)image[0].size();
            queue<pair<int, int>> front;
            set<pair<int, int>> visited;
            front.push(make_pair(sr, sc));
            visited.insert(front.front());
            function<void(int, int)> check = [&](int i, int j) {
                if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != c)
                    return;
                pair<int, int> p = make_pair(i, j);
                if (visited.find(p) == visited.end())
                {
                    front.push(p);
                    visited.insert(p);
                }
            };
            while (!front.empty())
            {
                pair<int, int> p = front.front();
                front.pop();
                image[p.first][p.second] = newColor;
                check(p.first - 1, p.second);
                check(p.first, p.second + 1);
                check(p.first + 1, p.second);
                check(p.first, p.second - 1);
            }
            return image;
        }

        // 01 Matrix
        // Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
        // The distance between two adjacent cells is 1.
        // Example 1:
        // Input:
        // [[0,0,0],
        //  [0,1,0],
        //  [0,0,0]]
        // Output:
        // [[0,0,0],
        //  [0,1,0],
        //  [0,0,0]]
        // Example 2:
        // Input:
        // [[0,0,0],
        //  [0,1,0],
        //  [1,1,1]]
        // Output:
        // [[0,0,0],
        //  [0,1,0],
        //  [1,2,1]]
        // Note:
        // The number of elements of the given matrix will not exceed 10,000.
        // There are at least one 0 in the given matrix.
        // The cells are adjacent in only four directions: up, down, left and right.
        vector<vector<int>> updateMatrix(const vector<vector<int>> &matrix)
        {
            vector<vector<int>> d(matrix);
            int m = (int)matrix.size();
            int n = (int)matrix[0].size();
            function<void(int, int)> search = [&](int i, int j) {
                if (i < 0 || i >= m || j < 0 || j >= n)
                    return;
                queue<pair<int, int>> current;
                queue<pair<int, int>> next;
                set<pair<int, int>> visited;
                pair<int, int> p = make_pair(i, j);
                current.push(p);
                visited.insert(p);
                int l = 0;
                function<void(int, int)> check = [&](int a, int b) {
                    if (a < 0 || a >= m || b < 0 || b >= n)
                        return;
                    pair<int, int> t = make_pair(a, b);
                    if (visited.find(t) == visited.end())
                    {
                        next.push(t);
                        visited.insert(t);
                    }
                };
                while (!current.empty())
                {
                    while (!current.empty())
                    {
                        p = current.front();
                        current.pop();
                        if (matrix[p.first][p.second] == 0)
                        {
                            d[i][j] = l;
                            return;
                        }
                        check(p.first - 1, p.second);
                        check(p.first, p.second + 1);
                        check(p.first + 1, p.second);
                        check(p.first, p.second - 1);
                    }
                    l++;
                    current.swap(next);
                }
            };
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    search(i, j);
                }
            }
            return d;
        }

        // Keys and Rooms
        // There are N rooms and you start in room 0.  Each room has a distinct number
        // in 0, 1, 2, ..., N-1, and each room may have some keys to access the next room.
        // Formally, each room i has a list of keys rooms[i], and each key rooms[i][j]
        // is an integer in [0, 1, ..., N-1] where N = rooms.length.
        // A key rooms[i][j] = v opens the room with number v.
        // Initially, all the rooms start locked (except for room 0).
        // You can walk back and forth between rooms freely.
        // Return true if and only if you can enter every room.
        // Example 1:
        // Input: [[1],[2],[3],[]]
        // Output: true
        // Explanation:
        // We start in room 0, and pick up key 1.
        // We then go to room 1, and pick up key 2.
        // We then go to room 2, and pick up key 3.
        // We then go to room 3.  Since we were able to go to every room, we return true.
        // Example 2:
        // Input: [[1,3],[3,0,1],[2],[0]]
        // Output: false
        // Explanation: We can't enter the room with number 2.
        // Note:
        // 1 <= rooms.length <= 1000
        // 0 <= rooms[i].length <= 1000
        // The number of keys in all rooms combined is at most 3000.
        bool canVisitAllRooms(const vector<vector<int>> &rooms)
        {
            set<int> visited;
            stack<int> path;
            path.push(0);
            visited.insert(0);
            while (!path.empty())
            {
                int i = path.top();
                path.pop();
                for (int j = 0; j < (int)rooms[i].size(); j++)
                {
                    int r = rooms[i][j];
                    if (visited.find(r) == visited.end())
                    {
                        path.push(r);
                        visited.insert(r);
                    }
                }
            }
            return visited.size() == rooms.size();
        }
        bool canVisitAllRooms2(const vector<vector<int>> &rooms)
        {
            set<int> visited;
            function<void(int)> visit = [&](int i) {
                if (i >= (int)rooms.size())
                    return;
                visited.insert(i);
                for (int j = 0; j < (int)rooms[i].size(); j++)
                {
                    int r = rooms[i][j];
                    if (visited.find(r) == visited.end())
                        visit(r);
                }
            };
            visit(0);
            return visited.size() == rooms.size();
        }
        bool canVisitAllRooms3(const vector<vector<int>> &rooms)
        {
            set<int> visited;
            queue<int> q;
            q.push(0);
            visited.insert(0);
            while (!q.empty())
            {
                int i = q.front();
                q.pop();
                for (int j = 0; j < (int)rooms[i].size(); j++)
                {
                    int r = rooms[i][j];
                    if (visited.find(r) == visited.end())
                    {
                        q.push(r);
                        visited.insert(r);
                    }
                }
            }
            return visited.size() == rooms.size();
        }

        // Design HashSet
        // Design a HashSet without using any built-in hash table libraries.
        // To be specific, your design should include these functions:
        // add(value): Insert a value into the HashSet.
        // contains(value) : Return whether the value exists in the HashSet or not.
        // remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.
        // Example:
        // MyHashSet hashSet = new MyHashSet();
        // hashSet.add(1);
        // hashSet.add(2);
        // hashSet.contains(1);    // returns true
        // hashSet.contains(3);    // returns false (not found)
        // hashSet.add(2);
        // hashSet.contains(2);    // returns true
        // hashSet.remove(2);
        // hashSet.contains(2);    // returns false (already removed)
        // Note:
        // All values will be in the range of [0, 1000000].
        // The number of operations will be in the range of [1, 10000].
        // Please do not use the built-in HashSet library.
        class MyHashSet
        {
        private:
            vector<vector<int>> set;
            int n;

        public:
            /** Initialize your data structure here. */
            MyHashSet()
            {
                n = 10000;
                set.resize(n);
            }

            void add(int key)
            {
                int k = key % n;
                vector<int>::iterator it = set[k].begin();
                while (it != set[k].end() && (*it != key))
                    it++;
                if (it == set[k].end())
                    set[k].push_back(key);
            }

            void remove(int key)
            {
                int k = key % n;
                vector<int>::iterator it = set[k].begin();
                while (it != set[k].end())
                {
                    if (*it == key)
                    {
                        set[k].erase(it);
                        break;
                    }
                    else
                    {
                        it++;
                    }
                }
            }

            /** Returns true if this set contains the specified element */
            bool contains(int key)
            {
                int k = key % n;
                vector<int>::iterator it = set[k].begin();
                while (it != set[k].end() && (*it != key))
                    it++;
                return it != set[k].end();
            }
        };

        // Design HashMap
        // Design a HashMap without using any built-in hash table libraries.
        // To be specific, your design should include these functions:
        // put(key, value) : Insert a (key, value) pair into the HashMap.
        // If the value already exists in the HashMap, update the value.
        // get(key): Returns the value to which the specified key is mapped,
        // or -1 if this map contains no mapping for the key.
        // remove(key) : Remove the mapping for the value key if this map
        // contains the mapping for the key.
        // Example:
        // MyHashMap hashMap = new MyHashMap();
        // hashMap.put(1, 1);
        // hashMap.put(2, 2);
        // hashMap.get(1);            // returns 1
        // hashMap.get(3);            // returns -1 (not found)
        // hashMap.put(2, 1);          // update the existing value
        // hashMap.get(2);            // returns 1
        // hashMap.remove(2);          // remove the mapping for 2
        // hashMap.get(2);            // returns -1 (not found)
        // Note:
        // All keys and values will be in the range of [0, 1000000].
        // The number of operations will be in the range of [1, 10000].
        // Please do not use the built-in HashMap library.
        class MyHashMap
        {
        private:
            vector<vector<pair<int, int>>> v;
            int n;

        public:
            /** Initialize your data structure here. */
            MyHashMap()
            {
                n = 10000;
                v.resize(n);
            }

            /** value will always be non-negative. */
            void put(int key, int value)
            {
                int k = key % n;
                vector<pair<int, int>>::iterator it = v[k].begin();
                while (it != v[k].end() && it->first != key)
                    it++;
                if (it == v[k].end())
                    v[k].push_back(make_pair(key, value));
                else
                    it->second = value;
            }

            /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
            int get(int key)
            {
                int k = key % n;
                vector<pair<int, int>>::iterator it = v[k].begin();
                while (it != v[k].end() && it->first != key)
                    it++;
                return it == v[k].end() ? -1 : it->second;
            }

            /** Removes the mapping of the specified value key if this map contains a mapping for the key */
            void remove(int key)
            {
                int k = key % n;
                vector<pair<int, int>>::iterator it = v[k].begin();
                while (it != v[k].end() && it->first != key)
                    it++;
                if (it != v[k].end())
                    v[k].erase(it);
            }
        };

        // Contains Duplicate
        // Given an array of integers, find if the array contains any duplicates.
        // Your function should return true if any value appears at least twice
        // in the array, and it should return false if every element is distinct.
        // Example 1:
        // Input: [1,2,3,1]
        // Output: true
        // Example 2:
        // Input: [1,2,3,4]
        // Output: false
        // Example 3:
        // Input: [1,1,1,3,3,4,3,2,4,2]
        // Output: true
        bool containsDuplicate(const vector<int> &nums)
        {
            set<int> s;
            for (int n : nums)
            {
                if (s.find(n) != s.end())
                    return true;
                s.insert(n);
            }
            return false;
        }

        // Minimum Index Sum of Two Lists
        // Suppose Andy and Doris want to choose a restaurant for dinner, and
        // they both have a list of favorite restaurants represented by strings.
        // You need to help them find out their common interest with the least
        // list index sum. If there is a choice tie between answers, output all
        // of them with no order requirement. You could assume there always exists an answer.
        // Example 1:
        // Input:
        // ["Shogun", "Tapioca Express", "Burger King", "KFC"]
        // ["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
        // Output: ["Shogun"]
        // Explanation: The only restaurant they both like is "Shogun".
        // Example 2:
        // Input:
        // ["Shogun", "Tapioca Express", "Burger King", "KFC"]
        // ["KFC", "Shogun", "Burger King"]
        // Output: ["Shogun"]
        // Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
        // Note:
        // The length of both lists will be in the range of [1, 1000].
        // The length of strings in both lists will be in the range of [1, 30].
        // The index is starting from 0 to the list length minus 1.
        // No duplicates in both lists.
        vector<string> findRestaurant(const vector<string> &list1, const vector<string> &list2)
        {
            vector<string> o;
            function<void(const vector<string> &, const vector<string> &)> solve =
                [&](const vector<string> &l1, const vector<string> &l2) {
                    map<string, int> m;
                    int minIndex = INT_MAX;
                    for (int i = 0; i < (int)l1.size(); i++)
                        m[l1[i]] = i;
                    for (int i = 0; i < (int)l2.size(); i++)
                    {
                        if (m.find(l2[i]) != m.end())
                        {
                            int j = m[l2[i]] + i;
                            if (j < minIndex)
                            {
                                o.clear();
                                o.push_back(l2[i]);
                                minIndex = j;
                            }
                            else if (j == minIndex)
                            {
                                o.push_back(l2[i]);
                            }
                        }
                    }
                };
            if (list1.size() < list2.size())
                solve(list1, list2);
            else
                solve(list2, list1);
            return o;
        }

        // First Unique Character in a String
        // Given a string, find the first non-repeating character in it
        // and return it's index. If it doesn't exist, return -1.
        // Examples:
        // s = "leetcode"
        // return 0.
        // s = "loveleetcode",
        // return 2.
        // Note: You may assume the string contain only lowercase letters.
        int firstUniqChar(const string &s)
        {
            map<char, int> m;
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (m.find(s[i]) == m.end())
                    m[s[i]] = 1;
                else
                    m[s[i]]++;
            }
            for (int i = 0; i < (int)s.size(); i++)
            {
                if (m[s[i]] == 1)
                    return i;
            }
            return -1;
        }

        // Contains Duplicate II
        // Given an array of integers and an integer k, find out whether there are two
        // distinct indices i and j in the array such that nums[i] = nums[j] and the
        // absolute difference between i and j is at most k.
        // Example 1:
        // Input: nums = [1,2,3,1], k = 3
        // Output: true
        // Example 2:
        // Input: nums = [1,0,1,1], k = 1
        // Output: true
        // Example 3:
        // Input: nums = [1,2,3,1,2,3], k = 2
        // Output: false
        bool containsNearbyDuplicate(const vector<int> &nums, int k)
        {
            set<int> s;
            for (int i = 0; i < (int)nums.size(); i++)
            {
                if (s.find(nums[i]) == s.end())
                    s.insert(nums[i]);
                else
                    return true;
                if (i >= k)
                    s.erase(nums[i - k]);
            }
            return false;
        }

        // Find Duplicate Subtrees
        // Given a binary tree, return all duplicate subtrees. For each kind of duplicate
        // subtrees, you only need to return the root node of any one of them.
        // Two trees are duplicate if they have the same structure with same node values.
        // Example 1:
        //         1
        //        / \
        //       2   3
        //      /   / \
        //     4   2   4
        //        /
        //       4
        // The following are two duplicate subtrees:
        //       2
        //      /
        //     4
        // and
        //     4
        // Therefore, you need to return above trees' root in the form of a list.
        vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
        {
            vector<TreeNode *> dup;
            map<string, int> m;
            map<int, int> c;
            int id = 0;
            function<int(TreeNode *)> getId = [&](TreeNode *n) -> int {
                if (n == nullptr)
                    return 0;
                string k = to_string(n->val) + "," + to_string(getId(n->left)) + "," + to_string(getId(n->right));
                if (m.find(k) == m.end())
                    m[k] = (++id);
                if (c.find(m[k]) == c.end())
                    c[m[k]] = 1;
                else
                    c[m[k]]++;
                if (c[m[k]] == 2) // c[m[k]] can be greater than 2, but we only count it once
                    dup.push_back(n);
                return m[k];
            };
            getId(root);
            return dup;
        }
        vector<TreeNode *> findDuplicateSubtrees2(TreeNode *root)
        {
            vector<TreeNode *> dup;
            map<TreeNode *, string> m;
            map<string, int> mid;
            map<int, int> c;
            int id = 0;
            stack<TreeNode *> s;
            TreeNode *n = root;
            TreeNode *last = nullptr;
            while (!s.empty() || n != nullptr)
            {
                if (n != nullptr)
                {
                    s.push(n);
                    n = n->left;
                }
                else
                {
                    TreeNode *t = s.top();
                    if (t->right != nullptr && t->right != last)
                    {
                        n = t->right;
                    }
                    else
                    {
                        string k = to_string(t->val) + "," + (t->left == nullptr ? "" : to_string(mid[m[t->left]])) + "," + (t->right == nullptr ? "" : to_string(mid[m[t->right]]));
                        m[t] = k;
                        if (mid.find(k) == mid.end())
                            mid[k] = (++id);
                        if (c.find(mid[k]) == c.end())
                            c[mid[k]] = 1;
                        else
                            c[mid[k]]++;
                        if (c[mid[k]] == 2)
                            dup.push_back(t);
                        s.pop();
                        last = t;
                    }
                }
            }
            // cout << "{" << endl;
            // for (auto it = m.begin(); it != m.end(); it++)
            // {
            //     cout << it->first << ":" << it->first->val << ":" << it->second << endl;
            // }
            // cout << "}" << endl;
            // cout << "{" << endl;
            // for (auto it = mid.begin(); it != mid.end(); it++)
            // {
            //     cout << it->first << ":" << it->second << endl;
            // }
            // cout << "}" << endl;
            // cout << "{" << endl;
            // for (auto it = c.begin(); it != c.end(); it++)
            // {
            //     cout << it->first << ":" << it->second << endl;
            // }
            // cout << "}" << endl;

            return dup;
        }

        // Jewels and Stones
        // You're given strings J representing the types of stones that are jewels,
        // and S representing the stones you have.  Each character in S is a type of
        // stone you have.  You want to know how many of the stones you have are also jewels.
        // The letters in J are guaranteed distinct, and all characters in J and S
        // are letters. Letters are case sensitive, so "a" is considered a different type of stone from "A".
        // Example 1:
        // Input: J = "aA", S = "aAAbbbb"
        // Output: 3
        // Example 2:
        // Input: J = "z", S = "ZZ"
        // Output: 0
        // Note:
        // S and J will consist of letters and have length at most 50.
        // The characters in J are distinct.
        int numJewelsInStones(const string &J, const string &S)
        {
            set<char> j(J.cbegin(), J.cend());
            return accumulate(S.cbegin(), S.cend(), 0, [&](int c, char s) { return c + (j.find(s) == j.end() ? 0 : 1); });
        }

        // Top K Frequent Elements
        // Given a non-empty array of integers, return the k most frequent elements.
        // Example 1:
        // Input: nums = [1,1,1,2,2,3], k = 2
        // Output: [1,2]
        // Example 2:
        // Input: nums = [1], k = 1
        // Output: [1]
        // Note:
        // You may assume k is always valid, 1 <= k <= number of unique elements.
        // Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
        // It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
        // You can return the answer in any order.
        vector<int> topKFrequent(const vector<int> &nums, int k)
        {
            map<int, int> m;
            vector<int> h;
            function<bool(int, int)> less = [&](int i, int j) -> bool {
                return m[i] > m[j];
            };
            for (int n : nums)
            {
                if (m.find(n) == m.end())
                    m[n] = 1;
                else
                    m[n]++;
            }
            for (const auto &it : m)
            {
                if ((int)h.size() < k)
                {
                    h.push_back(it.first);
                }
                else if (it.second > m[h[0]])
                {
                    pop_heap(h.begin(), h.end(), less);
                    h[k - 1] = it.first;
                }
                push_heap(h.begin(), h.end(), less);
            }
            return h;
        }
        vector<int> topKFrequent2(vector<int> &nums, int k)
        {
            map<int, int> m;
            vector<int> h;
            function<bool(int, int)> less = [&](int i, int j) -> bool {
                return m[i] > m[j];
            };
            for (int n : nums)
            {
                if (m.find(n) == m.end())
                {
                    m[n] = 1;
                    h.push_back(n);
                }
                else
                {
                    m[n]++;
                }
            }
            sort(h.begin(), h.end(), less);
            h.resize(k);
            return h;
        }

        // Insert Delete GetRandom O(1)
        // Design a data structure that supports all following operations in average O(1) time.
        // insert(val): Inserts an item val to the set if not already present.
        // remove(val): Removes an item val from the set if present.
        // getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
        // Example:
        // // Init an empty set.
        // RandomizedSet randomSet = new RandomizedSet();
        // // Inserts 1 to the set. Returns true as 1 was inserted successfully.
        // randomSet.insert(1);
        // // Returns false as 2 does not exist in the set.
        // randomSet.remove(2);
        // // Inserts 2 to the set, returns true. Set now contains [1,2].
        // randomSet.insert(2);
        // // getRandom should return either 1 or 2 randomly.
        // randomSet.getRandom();
        // // Removes 1 from the set, returns true. Set now contains [2].
        // randomSet.remove(1);
        // // 2 was already in the set, so return false.
        // randomSet.insert(2);
        // // Since 2 is the only number in the set, getRandom always return 2.
        // randomSet.getRandom();
        class RandomizedSet
        {
        private:
            vector<vector<int>> v;
            map<int, int> m;
            int k;

        public:
            /** Initialize your data structure here. */
            RandomizedSet()
            {
                k = 1000;
            }

            /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
            bool insert(int val)
            {
                int i = val % k;
                if (m.find(i) == m.end())
                {
                    v.push_back({val});
                    m[i] = (int)v.size() - 1;
                    return true;
                }
                else
                {
                    int j = m[i];
                    vector<int>::iterator it = v[j].begin();
                    while (it != v[j].end() && *it != val)
                        it++;
                    if (it == v[j].end())
                    {
                        v[j].push_back(val);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            /** Removes a value from the set. Returns true if the set contained the specified element. */
            bool remove(int val)
            {
                int i = val % k;
                if (m.find(i) == m.end())
                {
                    return false;
                }
                else
                {
                    int j = m[i];
                    vector<int>::iterator it = v[j].begin();
                    while (it != v[j].end() && *it != val)
                        it++;
                    if (it == v[j].end())
                    {
                        return false;
                    }
                    else
                    {
                        v[j].erase(it);
                        if (v[j].empty())
                            m.erase(i);
                        return true;
                    }
                }
            }

            /** Get a random element from the set. */
            int getRandom()
            {
                int i = rand() % m.size();
                map<int, int>::iterator it = m.begin();
                while (i > 0)
                {
                    it++;
                    i--;
                }
                int j = it->second;
                int t = rand() % v[j].size();
                return v[j][t];
            }
        };

        // Maximum XOR of Two Numbers in an Array
        // Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 <= ai < 2^31.
        // Find the maximum result of ai XOR aj, where 0 <= i, j < n.
        // Could you do this in O(n) runtime?
        // Example:
        // Input: [3, 10, 5, 25, 2, 8]
        // Output: 28
        // Explanation: The maximum result is 5 ^ 25 = 28.
        int findMaximumXOR(vector<int> &nums)
        {
            int m = 0;
            for (size_t i = 0; i + 1 < nums.size(); i++)
            {
                for (size_t j = i + 1; j < nums.size(); j++)
                    m = max(m, (nums[i] ^ nums[j]));
            }
            return m;
        }
        int findMaximumXOR2(vector<int> &nums)
        {
            struct Node
            {
                char bit;
                map<char, Node *> next;
                Node(char b) : bit(b) {}
                ~Node()
                {
                    for (map<char, Node *>::iterator it = next.begin(); it != next.end(); it++)
                        delete it->second;
                    next.clear();
                }
            };
            unique_ptr<Node> root(new Node('\0'));
            function<char(int, int)> getBit = [&](int n, int p) -> char {
                return (char)((n >> p) & 0x1);
            };
            function<void(int)> add = [&](int n) {
                Node *node = root.get();
                int i = 0;
                while (i < 32)
                {
                    char b = getBit(n, 31 - i);
                    if (node->next.find(b) == node->next.end())
                        node->next[b] = new Node(b);
                    node = node->next[b];
                    i++;
                }
            };
            for (int n : nums)
                add(n);
            int m = 0;
            function<void(Node *, Node *, int)> find = [&](Node *n0, Node *n1, int x) {
                if (n0->next.empty() || n1->next.empty())
                {
                    m = max(m, x);
                    return;
                }
                if (n0->next.size() == 1 && n1->next.size() == 1 && n0->next.cbegin()->first == n1->next.cbegin()->first)
                {
                    find(n0->next.cbegin()->second, n1->next.cbegin()->second, (x << 1));
                }
                else
                {
                    if (n0->next.find(0) != n0->next.end() && n1->next.find(1) != n1->next.end())
                    {
                        find(n0->next[0], n1->next[1], ((x << 1) ^ 0x1));
                    }
                    if (n0->next.find(1) != n0->next.end() && n1->next.find(0) != n1->next.end())
                    {
                        find(n0->next[1], n1->next[0], ((x << 1) ^ 0x1));
                    }
                }
            };
            find(root.get(), root.get(), 0);
            return m;
        }
        int findMaximumXOR3(vector<int> &nums)
        {
            sort(nums.begin(), nums.end());
            function<void(int, int, int, int &, int &, int &, int &)> getBitRange =
                [&](int b, int e, int i, int &b0, int &e0, int &b1, int &e1) {
                    b0 = -1;
                    e0 = -1;
                    b1 = -1;
                    e1 = -1;
                    int x = 0x1 << i;
                    for (int j = b; j <= e; j++)
                    {
                        switch ((nums[j] & x) >> i)
                        {
                        case 0:
                            if (b0 == -1)
                                b0 = j;
                            e0 = j;
                            break;
                        case 1:
                            if (b1 == -1)
                                b1 = j;
                            e1 = j;
                            break;
                        }
                    }
                };
            int m = 0;
            function<void(int, int, int, int, int, int)> find =
                [&](int b0, int e0, int b1, int e1, int i, int x) {
                    if (i < 0)
                    {
                        m = max(m, x);
                        return;
                    }
                    int b00, e00, b01, e01, b10, e10, b11, e11;
                    getBitRange(b0, e0, i, b00, e00, b01, e01);
                    getBitRange(b1, e1, i, b10, e10, b11, e11);
                    if ((b00 == -1 && b10 == -1) || (b01 == -1 && b11 == -1))
                    {
                        find(b0, e0, b1, e1, i - 1, x << 1);
                    }
                    else
                    {
                        if (b00 != -1 && b11 != -1)
                            find(b00, e00, b11, e11, i - 1, ((x << 1) ^ 0x1));
                        if (b01 != -1 && b10 != -1)
                            find(b01, e01, b10, e10, i - 1, ((x << 1) ^ 0x1));
                    }
                };
            find(0, (int)nums.size() - 1, 0, (int)nums.size() - 1, 31, 0);
            return m;
        }

        class NaryTree
        {
        public:
            class Node
            {
            public:
                int val;
                vector<Node *> children;

                Node() {}

                Node(int _val)
                {
                    val = _val;
                }

                Node(int _val, vector<Node *> _children)
                {
                    val = _val;
                    children = _children;
                }
            };
            vector<int> preorder(Node *root)
            {
                vector<int> result;
                if (root == nullptr)
                    return result;
                stack<Node *> s;
                s.push(root);
                while (!s.empty())
                {
                    Node *node = s.top();
                    s.pop();
                    result.push_back(node->val);
                    for (int i = (int)node->children.size() - 1; i >= 0; i--)
                    {
                        if (node->children[i] != nullptr)
                            s.push(node->children[i]);
                    }
                }
                return result;
            }
            vector<int> postorder(Node *root)
            {
                vector<int> result;
                if (root == nullptr)
                    return result;
                stack<Node *> s;
                s.push(root);
                set<Node *> visited;
                while (!s.empty())
                {
                    Node *node = s.top();
                    if (node->children.empty() || visited.find(node->children[0]) != visited.end())
                    {
                        result.push_back(node->val);
                        visited.insert(node);
                        s.pop();
                    }
                    else
                    {
                        for (int i = (int)node->children.size() - 1; i >= 0; i--)
                            s.push(node->children[i]);
                    }
                }
                return result;
            }
            vector<vector<int>> levelOrder(Node *root)
            {
                vector<vector<int>> result;
                if (root == nullptr)
                    return result;
                vector<Node *> current;
                vector<Node *> next;
                current.push_back(root);
                while (!current.empty())
                {
                    vector<int> level;
                    for (Node *node : current)
                    {
                        level.push_back(node->val);
                        for (Node *child : node->children)
                        {
                            if (child != nullptr)
                                next.push_back(child);
                        }
                    }
                    result.push_back(level);
                    current.clear();
                    current.swap(next);
                }
                return result;
            }
            int maxDepth(Node *root)
            {
                function<int(Node *)> depth = [&](Node *node) -> int {
                    if (node == nullptr)
                        return 0;
                    if (node->children.empty())
                        return 1;
                    int m = 0;
                    for (Node *child : node->children)
                    {
                        m = max(m, depth(child));
                    }
                    return m + 1;
                };
                return depth(root);
            }
        };

        // Fibonacci Number
        // The Fibonacci numbers, commonly denoted F(n) form a sequence, called the
        // Fibonacci sequence, such that each number is the sum of the two preceding
        // ones, starting from 0 and 1. That is,
        // F(0) = 0,   F(1) = 1
        // F(N) = F(N - 1) + F(N - 2), for N > 1.
        // Given N, calculate F(N).
        // Example 1:
        // Input: 2
        // Output: 1
        // Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
        // Example 2:
        // Input: 3
        // Output: 2
        // Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
        // Example 3:
        // Input: 4
        // Output: 3
        // Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
        // Note:
        // 0 <= N <= 30.
        int fib(int N)
        {
            map<int, int> m;
            function<int(int)> f = [&](int n) -> int {
                if (n < 0)
                    return 0;
                if (n == 1 || n == 0)
                    return n;
                if (m.find(n - 2) == m.end())
                    m[n - 2] = f(n - 2);
                if (m.find(n - 1) == m.end())
                    m[n - 1] = f(n - 1);
                return m[n - 1] + m[n - 2];
            };
            return f(N);
        }

        // K-th Symbol in Grammar
        // On the first row, we write a 0. Now in every subsequent row, we look at
        // the previous row and replace each occurrence of 0 with 01, and each
        // occurrence of 1 with 10. Given row N and index K, return the K-th indexed
        // symbol in row N. (The values of K are 1-indexed.) (1 indexed).
        // Examples:
        // Input: N = 1, K = 1
        // Output: 0
        // Input: N = 2, K = 1
        // Output: 0
        // Input: N = 2, K = 2
        // Output: 1
        // Input: N = 4, K = 5
        // Output: 1
        // Explanation:
        // row 1: 0
        // row 2: 01
        // row 3: 0110
        // row 4: 01101001
        // Note:
        // N will be an integer in the range [1, 30].
        // K will be an integer in the range [1, 2^(N-1)].
        // N:   1   2   3   4   ... K-1             K       K+1             ... 2^(N-1)
        // N+1: 1 2 3 4 5 6 7 8 ... 2(K-1)-1 2(K-1) 2K-1 2K 2(K+1)-1 2(K+1) ... 2^N-1 2^N
        int kthGrammar(int N, int K)
        {
            function<int(int, int)> g = [&](int n, int k) -> int {
                if (n == 1)
                    return 0;
                int b = g(n - 1, (k + 1) >> 1);
                return ((k & 0x1) == 1) ? b : 1 - b;
            };
            return g(N, K);
        }

        // Sort an Array
        // Given an array of integers nums, sort the array in ascending order.
        // Example 1:
        // Input: nums = [5,2,3,1]
        // Output: [1,2,3,5]
        // Example 2:
        // Input: nums = [5,1,1,2,0,0]
        // Output: [0,0,1,1,2,5]
        // Constraints:
        // 1 <= nums.length <= 50000
        // -50000 <= nums[i] <= 50000
        // Bottom-up merge sort
        vector<int> sortArray(vector<int> &nums)
        {
            int n = (int)nums.size();
            int l = 1;
            while (l < n)
            {
                for (int i = 0; i + l < n; i += (l + l))
                {
                    int j = i;
                    int k = i + l;
                    while (j < k && k < i + l + l && k < n)
                    {
                        if (nums[j] <= nums[k])
                        {
                            j++;
                        }
                        else
                        {
                            int t = nums[k];
                            for (int p = k; p > j; p--)
                            {
                                nums[p] = nums[p - 1];
                            }
                            nums[j] = t;
                            j++;
                            k++;
                        }
                    }
                }
                l = l << 1;
            }
            return nums;
        }
        // Bottom-up merge sort
        vector<int> sortArray2(vector<int> &nums)
        {
            int n = (int)nums.size();
            int l = 1;
            while (l < n)
            {
                // make a copy of nums. If some elements at the end of nums are
                // not participating the sorting in the for-loop, they are kept
                // in temp and thus not lost.
                vector<int> temp(nums);
                for (int i = 0; i + l < n; i += (l + l))
                {
                    int j = i;
                    int k = i + l;
                    int q = i;
                    while (j < i + l && k < i + l + l && k < n)
                    {
                        if (nums[j] <= nums[k])
                            temp[q++] = nums[j++];
                        else
                            temp[q++] = nums[k++];
                    }
                    while (j < i + l)
                        temp[q++] = nums[j++];
                    while (k < i + l + l && k < n)
                        temp[q++] = nums[k++];
                }
                l = l << 1;
                temp.swap(nums);
            }
            return nums;
        }

        // The Skyline Problem
        // A city's skyline is the outer contour of the silhouette formed by all the
        // buildings in that city when viewed from a distance. Now suppose you are
        // given the locations and height of all the buildings as shown on a cityscape
        // photo (Figure A), write a program to output the skyline formed by these
        // buildings collectively (Figure B). The geometric information of each building
        // is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the
        // x coordinates of the left and right edge of the ith building, respectively,
        // and Hi is its height. It is guaranteed that 0 <= Li, Ri <= INT_MAX, 0 < Hi <= INT_MAX,
        // and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded
        // on an absolutely flat surface at height 0. For instance, the dimensions of
        // all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12],
        // [15 20 10], [19 24 8] ]. The output is a list of "key points" (red dots in
        // Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely
        // defines a skyline. A key point is the left endpoint of a horizontal line
        // segment. Note that the last key point, where the rightmost building ends,
        // is merely used to mark the termination of the skyline, and always has zero
        // height. Also, the ground in between any two adjacent buildings should be
        // considered part of the skyline contour. For instance, the skyline in Figure
        // B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].
        // Notes: he number of buildings in any input list is guaranteed to be in the
        // range [0, 10000]. The input list is already sorted in ascending order by the
        // left x position Li. The output list must be sorted by the x position. There
        // must be no consecutive horizontal lines of equal height in the output skyline.
        // For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable;
        // the three lines of height 5 should be merged into one in the final output as
        // such: [...[2 3], [4 5], [12 7], ...]
        vector<vector<int>> getSkyline(const vector<vector<int>> &buildings)
        {
            // First compute up boundaries
            vector<vector<int>> up;
            vector<vector<int>> begins(buildings); // already sorted by up boundaries
            vector<vector<int>>::iterator it = begins.begin();
            while (it != begins.end())
            {
                // For all the ranges with the same up boundary,
                // compute the max height at the boundary.
                int b = it->operator[](0);
                int h = it->operator[](2);
                while (it + 1 != begins.end() && (it + 1)->operator[](0) == b)
                {
                    ++it;
                    h = max(h, it->operator[](2));
                }
                // Current up boundary is valid if it is higher than all the previous heights
                bool valid = true;
                it = begins.begin();
                while (it != begins.end() && it->operator[](0) <= b)
                {
                    if (it->operator[](1) < b)
                    {
                        // The range is not covering b
                        it = begins.erase(it);
                    }
                    else
                    {
                        if (it->operator[](2) > h || (it->operator[](0) < b && it->operator[](2) == h))
                        {
                            // Current up boundary not valid since a previous range
                            // is higher
                            valid = false;
                        }
                        ++it;
                    }
                }
                if (valid)
                {
                    up.push_back({b, h});
                }
            }
            // Compute the down boundaries
            vector<vector<int>> down;
            vector<vector<int>> ends(buildings);
            // Sort down boundaries in reverse order so that we can apply similar logic
            // of computing up boundaries
            sort(ends.begin(), ends.end(), [&](const vector<int> &x, const vector<int> &y) -> bool {
                if (x[1] > y[1])
                    return true;
                if (x[1] == y[1] && x[0] > y[0])
                    return true;
                if (x[1] == y[1] && x[0] == y[0] && x[2] > y[2])
                    return true;
                return false;
            });
            it = ends.begin();
            while (it != ends.end())
            {
                // For all the ranges with the same down boundary,
                // compute the max height at the down boundary.
                int e = it->operator[](1);
                int h = it->operator[](2);
                while ((it + 1) != ends.end() && (it + 1)->operator[](1) == e)
                {
                    ++it;
                    h = max(h, it->operator[](2));
                }
                // Compute the max height among all the ranges before e
                it = ends.begin();
                int m = 0;
                while (it != ends.end() && it->operator[](1) >= e)
                {
                    if (it->operator[](0) > e)
                    {
                        // The range is not covering e
                        it = ends.erase(it);
                    }
                    else
                    {
                        if (it->operator[](1) > e)
                            m = max(m, it->operator[](2));
                        ++it;
                    }
                }
                if (m < h)
                {
                    down.insert(down.begin(), {e, m});
                }
            }
            vector<vector<int>> skyline;
            size_t i = 0;
            size_t j = 0;
            while (i < up.size() || j < down.size())
            {
                if (i < up.size() && j < down.size())
                {
                    if (up[i][0] < down[j][0])
                    {
                        skyline.push_back(up[i++]);
                    }
                    else
                    {
                        skyline.push_back(down[j++]);
                    }
                }
                else if (i < up.size())
                {
                    skyline.push_back(up[i++]);
                }
                else
                {
                    skyline.push_back(down[j++]);
                }
            }
            return skyline;
        }
        vector<vector<int>> getSkyline2(const vector<vector<int>> &buildings)
        {
            function<vector<vector<int>>(const vector<vector<int>> &, const vector<vector<int>> &)>
                merge = [&](const vector<vector<int>> &a, const vector<vector<int>> &b) -> vector<vector<int>> {
                if (a.empty())
                    return b;
                if (b.empty())
                    return a;
                vector<vector<int>> c;
                int ha = 0;
                int hb = 0;
                size_t i = 0;
                size_t j = 0;
                int h;
                while (i < a.size() || j < b.size())
                {
                    if (i < a.size() && j < b.size())
                    {
                        if (a[i][0] < b[j][0])
                        {
                            h = max(a[i][1], hb);
                            if (c.empty() || c.back()[1] != h)
                                c.push_back(vector<int>{a[i][0], h});
                            ha = a[i++][1];
                        }
                        else if (a[i][0] > b[j][0])
                        {
                            h = max(ha, b[j][1]);
                            if (c.empty() || c.back()[1] != h)
                                c.push_back(vector<int>{b[j][0], h});
                            hb = b[j++][1];
                        }
                        else
                        {
                            h = max(a[i][1], b[j][1]);
                            if (c.empty() || c.back()[1] != h)
                                c.push_back(vector<int>{a[i][0], h});
                            ha = a[i++][1];
                            hb = b[j++][1];
                        }
                    }
                    else if (i < a.size())
                    {
                        c.push_back(a[i++]);
                    }
                    else
                    {
                        c.push_back(b[j++]);
                    }
                };
                return c;
            };
            function<vector<vector<int>>(int, int)> solve =
                [&](int b, int e) -> vector<vector<int>> {
                if (b > e)
                    return {};
                if (b == e)
                    return vector<vector<int>>{
                        {buildings[b][0], buildings[b][2]},
                        {buildings[b][1], 0}};
                int m = b + ((e - b) >> 1);
                vector<vector<int>> v1 = solve(b, m);
                vector<vector<int>> v2 = solve(m + 1, e);
                vector<vector<int>> v = merge(v1, v2);
                return v;
            };
            return solve(0, (int)buildings.size() - 1);
        }

    } // namespace LeetCode

    namespace sql
    {

        // 176. Second Highest Salary
        // SQL Schema
        // Write a SQL query to get the second highest salary from the Employee table.
        // +----+--------+
        // | Id | Salary |
        // +----+--------+
        // | 1  | 100    |
        // | 2  | 200    |
        // | 3  | 300    |
        // +----+--------+
        // For example, given the above Employee table, the query should return 200 as the second highest salary. If there is no second highest salary, then the query should return null.
        // +---------------------+
        // | SecondHighestSalary |
        // +---------------------+
        // | 200                 |
        // +---------------------+
        //
        // SELECT IFNULL((SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC LIMIT 1, 1), NULL) AS SecondHighestSalary;
    } // namespace sql
} // namespace Test

#endif
