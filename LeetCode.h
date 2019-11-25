#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include <algorithm>
#include <bitset>
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
// Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
static int lengthOfLongestSubstring(const string &s)
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
static int lengthOfLongestSubstring2(const string &s)
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
    if (s.empty())
        return 0;
    bitset<256> m;
    int i = 0;
    m.set(s[0]);
    int l = 1;
    int j;
    for (j = 1; j < (int)s.size(); j++)
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
    function<int(int, int)>
        expand = [&](int i, int j) -> int {
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
// Write the code that will take a string and make this conversion given a number of rows:
// Example 1:
// Input: s = "PAYPALISHIRING", numRows = 3
// Output: "PAHNAPLSIIGYIR"
// Example 2:
// Input: s = "PAYPALISHIRING", numRows = 4
// Output: "PINALSIGYAHRPI"
// Explanation:
// P     I    N
// A   L S  I G
// Y A   H R
// P     I
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
            if (0 < i && i + 1 < numRows && 0 <= j + d - i && j + d - i < (int)s.size())
                ss << s[j + d - i];
        }
    }
    return ss.str();
}
static string convert2(const string &s, int numRows)
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

} // namespace LeetCode
} // namespace Test

#endif