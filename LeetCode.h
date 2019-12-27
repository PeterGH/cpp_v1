#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include "Util.h"
#include <algorithm>
#include <bitset>
#include <functional>
#include <limits.h>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace Test {
namespace LeetCode {

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
int lengthOfLongestSubstring(const string &s) {
    map<char, int> m;
    int l = 0;
    int i = 0;
    int j = 0;
    for (j = 0; j < (int)s.size(); j++) {
        if (m.find(s[j]) != m.end()) {
            l = max(l, j - i);
            while (i <= m[s[j]]) {
                m.erase(s[i]);
                i++;
            }
        }
        m[s[j]] = j;
    }
    l = max(l, j - i);
    return l;
}
int lengthOfLongestSubstring2(const string &s) {
    set<char> chars;
    int i = 0;
    int l = 0;
    int j = 0;
    for (j = 0; j < (int)s.size(); j++) {
        if (chars.find(s[j]) == chars.end())
            chars.insert(s[j]);
        else {
            l = max(l, j - i);
            while (s[i] != s[j]) {
                chars.erase(s[i]);
                i++;
            }
            i++;
        }
    }
    l = max(l, j - i);
    return l;
}
int lengthOfLongestSubstring3(const string &s) {
    if (s.empty())
        return 0;
    bitset<256> m;
    int i = 0;
    m.set(s[0]);
    int l = 1;
    int j;
    for (j = 1; j < (int)s.size(); j++) {
        if (m.test(s[j])) {
            if (j - i > l)
                l = j - i;
            while (s[i] != s[j]) {
                m.reset(s[i]);
                i++;
            }
            i++;
        } else {
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
string longestPalindrome(const string &s) {
    if (s.empty())
        return string();
    function<int(int, int)> expand = [&](int i, int j) -> int {
        while (0 <= i && j < (int)s.size() && s[i] == s[j]) {
            i--;
            j++;
        }
        // s[(i + 1) .. (j - 1)] is a palindrome
        return j - i - 1;
    };
    int m = 1;
    int b = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int n;
        if (i + 1 < (int)s.size())
            n = max(expand(i, i), expand(i, i + 1));
        else
            n = expand(i, i);
        if (n > m) {
            // If n is odd, b + (n - 1) / 2 = i
            // If n is even, b + n / 2 - 1 = i
            b = i - ((n - 1) >> 1);
            m = n;
        }
    }
    return s.substr(b, m);
}
string longestPalindrome2(const string &s) {
    function<pair<int, int>(int, int)> expand = [&](int l,
                                                    int r) -> pair<int, int> {
        while (0 <= l && r < (int)s.size() && s[l] == s[r]) {
            l--;
            r++;
        }
        return make_pair(l + 1, r - 1);
    };
    int begin = 0, end = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        auto p = expand(i, i);
        if (p.second - p.first > end - begin) {
            begin = p.first;
            end = p.second;
        }
        if (i < (int)s.size() - 1) {
            p = expand(i, i + 1);
            if (p.second - p.first > end - begin) {
                begin = p.first;
                end = p.second;
            }
        }
    }
    return s.substr(begin, end - begin + 1);
}
string longestPalindrome3(const string &s) {
    vector<vector<int>> len(2, vector<int>(s.size(), 1));
    int begin = 0, end = 0;
    for (size_t i = 0; i + 1 < s.size(); i++) {
        if (s[i] == s[i + 1]) {
            len[1][i] = 2;
            if (2 > end - begin + 1) {
                begin = i;
                end = i + 1;
            }
        }
    }
    for (int l = 3; l <= (int)s.size(); l++) {
        int v = ((l & 0x1) == 1 ? 0 : 1);
        for (size_t i = 0; i + l - 1 < s.size(); i++) {
            if (s[i] == s[i + l - 1] && len[v][i + 1] == l - 2) {
                // s[i..(i + l - 1)] is a palindrome of length l, if
                // (1) s[i] == s[i + l - 1], and
                // (2) s[(i + 1)..(i + l - 2)] is a palindrome (of length (l -
                // 2))
                len[v][i] = l;
                if (l > end - begin + 1) {
                    begin = i;
                    end = i + l - 1;
                }
            }
        }
    }
    return s.substr(begin, end - begin + 1);
}
string longestPalindrome4(const string &s) {
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
        while (true) {
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
    while (i < n) {
        if (i < r) {
            int j = (c << 1) - i;
            l[i] = min(l[j], r - i);
            if (i + l[i] < r) {
                i++;
                continue;
            }
        }
        expand(i, l[i]);
        if (i + l[i] >= r) {
            c = i;
            r = i + l[i];
        }
        if (l[i] > ml) {
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
string convert(const string &s, int numRows) {
    if (numRows <= 1)
        return s;
    ostringstream ss;
    int d = (numRows << 1) - 2;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < (int)s.size(); j += d) {
            if (j + i < (int)s.size())
                ss << s[j + i];
            if (0 < i && i + 1 < numRows && 0 <= j + d - i &&
                j + d - i < (int)s.size())
                ss << s[j + d - i];
        }
    }
    return ss.str();
}
string convert2(const string &s, int numRows) {
    string output;
    int len = s.size();
    int delta = numRows == 1 ? 1 : (numRows << 1) - 2;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < len; j += delta) {
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
int reverse(int x) {
    long long y = x;
    bool isNegative = false;
    if (y < 0) {
        isNegative = true;
        y = -y;
    }
    long long z = 0;
    while (y > 0) {
        z = z * 10 + (y % 10);
        if (isNegative && -z < INT_MIN)
            return 0;
        else if (z > INT_MAX)
            return 0;
        y = y / 10;
    }
    return isNegative ? -z : z;
}
int reverse2(int x) {
    int minh = -214748364; // INT_MIN / 10 = 18284266;
    int mind = -8;         // INT_MIN % 10 = -8;
    int maxh = 214748364;  // INT_MAX / 10 = 214748364;
    int maxd = 7;          // INT_MAX % 10 = 7;
    int y = 0;
    while (x != 0) {
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
int myAtoi(string str) {
    bool foundStart = false;
    bool isNegative = false;
    int r = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            if (foundStart)
                break;
        } else if (str[i] == '+') {
            if (foundStart)
                break;
            foundStart = true;
        } else if (str[i] == '-') {
            if (foundStart)
                break;
            foundStart = true;
            isNegative = true;
        } else if (str[i] < '0' || str[i] > '9') {
            if (foundStart)
                break;
            return 0;
        } else {
            if (!foundStart)
                foundStart = true;
            if (isNegative &&
                (r < -214748364 || (r == -214748364 && str[i] > '8'))) {
                return INT_MIN;
            }
            if (!isNegative &&
                (r > 214748364 || (r == 214748364 && str[i] > '7'))) {
                return INT_MAX;
            }
            r = r * 10 + (isNegative ? ('0' - str[i]) : (str[i] - '0'));
        }
    }
    return r;
}
int myAtoi2(string str) {
    long r = 0;
    bool negative = false;
    bool foundStart = false;
    size_t i = 0;
    while (i < str.length()) {
        char c = str[i++];
        if (c == '+' || c == '-') {
            if (foundStart)
                break;
            foundStart = true;
            negative = (c == '-');
        } else if ('0' <= c && c <= '9') {
            if (!foundStart)
                foundStart = true;
            r = r * 10 + c - '0';
            if (negative && -r <= INT_MIN)
                return INT_MIN;
            else if (!negative && r >= INT_MAX)
                return INT_MAX;
        } else if (c == ' ') {
            if (foundStart)
                break;
        } else
            break;
    }
    return negative ? -r : r;
}
int myAtoi3(string str) {
    size_t i = 0;
    while (i < str.length() && str[i] == ' ')
        i++;
    if (i == str.length())
        return 0;
    bool negative = false;
    if (str[i] == '+' || str[i] == '-') {
        negative = (str[i++] == '-');
    }
    if (i == str.length() || str[i] < '0' || str[i] > '9')
        return 0;
    long r = 0;
    while (i < str.length() && '0' <= str[i] && str[i] <= '9') {
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
bool isPalindrome(int x) {
    if (x < 0)
        return false;
    int d = 1;
    // 10 * d will overflow if d is too large, e.g. when x = 1000000001
    // while (10 * d <= x)
    //     d *= 10;
    int y = x;
    while (y >= 10) {
        d *= 10;
        y /= 10;
    }
    while (x > 0) {
        int l = x % 10;
        int h = x / d;
        if (h != l)
            return false;
        x = (x % d) / 10;
        d /= 100;
    }
    return true;
}
bool isPalindrome2(int x) {
    if (x < 0)
        return false;
    long long y = x;
    long long d = 1;
    while (y >= 10 * d)
        d *= 10;
    int l = 0;
    int r = 0;
    while (y > 0) {
        l = y >= d ? (y / d) : 0; // what if just l = y / d ?
        r = y % 10;
        if (l != r)
            return false;
        y = (y % d) / 10;
        d /= 100;
    }
    return true;
}
bool isPalindrome3(unsigned int number) {
    if (number < 10)
        return true;
    unsigned int base = 1;
    while ((number / base) >= 10)
        base *= 10;
    // Compare the most significant digit (MSD) and
    // the least significant digit (LSD)
    while (number >= 10) {
        if ((number / base) != (number % 10)) {
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
// Output: 49 (between a[1] and a[8])
int maxArea(const vector<int> &height) {
    size_t i = 0;
    size_t j = height.size() - 1;
    int m = 0;
    while (i < j) {
        int a = 0;
        if (height[i] <= height[j]) {
            a = height[i] * (j - i);
            i++;
        } else {
            a = height[j] * (j - i);
            j--;
        }
        m = std::max(m, a);
    }
    return m;
}
int maxArea2(const vector<int> &height) {
    int n = height.size();
    if (n <= 1)
        return 0;
    vector<int> begin = {0};
    for (int i = 1; i < n; i++) {
        if (height[i] > height[begin.back()])
            begin.push_back(i);
    }
    // begin contains increasing elements
    vector<int> end = {n - 1};
    for (int i = n - 2; i >= 0; i--) {
        if (height[i] > height[end.front()])
            end.insert(end.begin(), i);
    }
    // end contains decreasing elements
    int a = 0;
    for (int j = 0; j < (int)end.size(); j++) {
        int i = 0;
        while (i < (int)begin.size() && begin[i] < end[j]) {
            int b = (end[j] - begin[i]) * min(height[begin[i]], height[end[j]]);
            if (b > a)
                a = b;
            i++;
        }
    }
    return a;
}
int maxArea3(const vector<int> &height) {
    int m = 0;
    for (int i = 0; i < (int)height.size() - 1; i++) {
        for (int j = i + 1; j < (int)height.size(); j++) {
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
string intToRoman(int num) {
    string r;
    if (num >= 1000) {
        r.append(num / 1000, 'M');
        num %= 1000;
    }
    if (num >= 900) {
        r.append("CM");
        num -= 900;
    }
    if (num >= 500) {
        r.append(1, 'D');
        num -= 500;
    }
    if (num >= 400) {
        r.append("CD");
        num -= 400;
    }
    if (num >= 100) {
        r.append(num / 100, 'C');
        num %= 100;
    }
    if (num >= 90) {
        r.append("XC");
        num -= 90;
    }
    if (num >= 50) {
        r.append(1, 'L');
        num -= 50;
    }
    if (num >= 40) {
        r.append("XL");
        num -= 40;
    }
    if (num >= 10) {
        r.append(num / 10, 'X');
        num %= 10;
    }
    if (num == 9) {
        r.append("IX");
        num -= 9;
    }
    if (num >= 5) {
        r.append(1, 'V');
        num -= 5;
    }
    if (num == 4) {
        r.append("IV");
        num -= 4;
    }
    if (num >= 1) {
        r.append(num, 'I');
    }
    return r;
}
string intToRoman2(int num) {
    string s;
    if (num <= 0)
        return s;
    int d = num / 1000;
    if (d > 0)
        s.append(d, 'M');
    num = num % 1000;
    if (num == 0)
        return s;
    if (num >= 900) {
        s.append(1, 'C');
        s.append(1, 'M');
        num -= 900;
    } else if (num >= 500) {
        s.append(1, 'D');
        num -= 500;
        if (num == 0)
            return s;
        d = num / 100;
        if (d > 0)
            s.append(d, 'C');
        num = num % 100;
    } else if (num >= 400) {
        s.append(1, 'C');
        s.append(1, 'D');
        num -= 400;
    } else {
        d = num / 100;
        if (d > 0)
            s.append(d, 'C');
        num = num % 100;
    }
    // Now 0 <= num < 100
    if (num == 0)
        return s;
    if (num >= 90) {
        s.append(1, 'X');
        s.append(1, 'C');
        num -= 90;
    } else if (num >= 50) {
        s.append(1, 'L');
        num -= 50;
        if (num == 0)
            return s;
        d = num / 10;
        if (d > 0)
            s.append(d, 'X');
        num = num % 10;
    } else if (num >= 40) {
        s.append(1, 'X');
        s.append(1, 'L');
        num -= 40;
    } else {
        d = num / 10;
        if (d > 0)
            s.append(d, 'X');
        num = num % 10;
    }
    // Now 0 <= num < 10
    if (num == 0)
        return s;
    if (num == 9) {
        s.append(1, 'I');
        s.append(1, 'X');
    } else if (num >= 5) {
        s.append(1, 'V');
        num -= 5;
        s.append(num, 'I');
    } else if (num == 4) {
        s.append(1, 'I');
        s.append(1, 'V');
    } else {
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
int romanToInt(const string &s) {
    int r = 0;
    size_t i = 0;
    while (i < s.size()) {
        switch (s[i]) {
        case 'I':
            if (i + 1 < s.size() && s[i + 1] == 'V') {
                r += 4;
                i += 2;
            } else if (i + 1 < s.size() && s[i + 1] == 'X') {
                r += 9;
                i += 2;
            } else {
                r += 1;
                i++;
            }
            break;
        case 'V':
            r += 5;
            i++;
            break;
        case 'X':
            if (i + 1 < s.size() && s[i + 1] == 'L') {
                r += 40;
                i += 2;
            } else if (i + 1 < s.size() && s[i + 1] == 'C') {
                r += 90;
                i += 2;
            } else {
                r += 10;
                i++;
            }
            break;
        case 'L':
            r += 50;
            i++;
            break;
        case 'C':
            if (i + 1 < s.size() && s[i + 1] == 'D') {
                r += 400;
                i += 2;
            } else if (i + 1 < s.size() && s[i + 1] == 'M') {
                r += 900;
                i += 2;
            } else {
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
string longestCommonPrefix(const vector<string> &strs) {
    if (strs.empty())
        return "";
    if (strs.size() == 1)
        return strs[0];
    size_t i = 0;
    while (i < strs[0].size()) {
        for (size_t j = 1; j < strs.size(); j++) {
            if (i == strs[j].size() || strs[0][i] != strs[j][i])
                return strs[0].substr(0, i);
        }
        i++;
    }
    return strs[0];
}
string longestCommonPrefix2(const vector<string> &strs) {
    string p;
    int n = strs.size();
    if (n == 0)
        return p;
    int i = 0;
    while (i < (int)strs[0].size()) {
        char c = strs[0][i];
        for (int j = 1; j < n; j++) {
            if (i == (int)strs[j].length() || strs[j][i] != c)
                return p;
        }
        p.append(1, c);
        i++;
    }
    return p;
}
string longestCommonPrefix3(const vector<string> &strs) {
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
    for (size_t i = 1; i < strs.size(); i++) {
        k = prefix(k, i);
        if (k == 0)
            break;
    }
    return strs[0].substr(0, k);
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
vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> result;
    set<tuple<int, int>> m;
    for (size_t i = 0; i + 2 < nums.size(); i++) {
        set<int> s;
        for (size_t j = i + 1; j < nums.size(); j++) {
            if (s.find(-nums[i] - nums[j]) != s.end()) {
                vector<int> r = {nums[i], -nums[i] - nums[j], nums[j]};
                sort(r.begin(), r.end());
                tuple<int, int> t = make_tuple(r[0], r[1]);
                if (m.find(t) == m.end()) {
                    result.push_back(r);
                    m.insert(t);
                }
            }
            s.insert(nums[j]);
        }
    }
    return result;
}
vector<vector<int>> threeSum2(vector<int> &nums) {
    vector<vector<int>> ans;
    int n = nums.size();
    if (n < 3)
        return ans;
    sort(nums.begin(), nums.end());
    if (nums[0] > 0 || nums[n - 1] < 0)
        return ans;
    int i = 0;
    while (i <= n - 3) {
        if (nums[i] > 0)
            break;
        int j = i + 1;
        int k = n - 1;
        while (j < k) {
            int s = nums[j] + nums[k];
            if (s == -nums[i])
                ans.push_back(vector<int>{nums[i], nums[j], nums[k]});
            if (s <= -nums[i]) {
                while (j + 1 < k && nums[j + 1] == nums[j])
                    j++;
                j++;
            }
            if (s >= -nums[i]) {
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
vector<vector<int>> threeSum3(vector<int> &nums) {
    vector<vector<int>> ans;
    int n = nums.size();
    if (n < 3)
        return ans;
    sort(nums.begin(), nums.end());
    if (nums[0] > 0 || nums[n - 1] < 0)
        return ans;
    int i = 0;
    while (i <= n - 3) {
        if (nums[i] > 0)
            break;
        int j = i + 1;
        while (j <= n - 2) {
            int s = nums[i] + nums[j];
            if (s > 0)
                break;
            int t = -s;
            int l = j + 1;
            int h = n - 1;
            int m;
            while (l <= h) {
                m = l + ((h - l) >> 1);
                if (t < nums[m]) {
                    if (l == m)
                        break;
                    h = m - 1;
                } else if (nums[m] < t) {
                    if (m == h)
                        break;
                    l = m + 1;
                } else {
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
int threeSumClosest(vector<int> &nums, int target) {
    sort(nums.begin(), nums.end());
    size_t i = 0;
    int r = 0;
    int d = INT_MAX;
    while (i + 2 < nums.size()) {
        int j = i + 1;
        int k = nums.size() - 1;
        while (j < k) {
            int s = nums[i] + nums[j] + nums[k];
            if (abs(target - s) < d) {
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
int threeSumClosest2(vector<int> &nums, int target) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int i = 0;
    int d = INT_MAX;
    int t = target;
    while (i <= n - 3) {
        int j = i + 1;
        int k = n - 1;
        while (j < k) {
            int s = nums[i] + nums[j] + nums[k];
            if (s < target) {
                if (target - s <= d) {
                    d = target - s;
                    t = s;
                }
                while (j + 1 < k && nums[j + 1] == nums[j])
                    j++;
                j++;
            } else if (s > target) {
                if (s - target <= d) {
                    d = s - target;
                    t = s;
                }
                while (j < k - 1 && nums[k - 1] == nums[k])
                    k--;
                k--;
            } else {
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
vector<string> letterCombinations(const string &digits) {
    map<char, vector<char>> m = {
        {'2', {'a', 'b', 'c'}}, {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}}, {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}}, {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}}, {'9', {'w', 'x', 'y', 'z'}}};
    vector<string> result;
    function<void(const string &, size_t)> combine = [&](const string &s,
                                                         size_t i) {
        if (i == digits.size()) {
            if (!s.empty())
                result.push_back(s);
            return;
        }
        if (m.find(digits[i]) == m.end()) {
            combine(s, i + 1);
            return;
        }
        for (size_t j = 0; j < m[digits[i]].size(); j++) {
            string s1(s);
            s1.append(1, m[digits[i]][j]);
            combine(s1, i + 1);
        }
    };
    combine("", 0);
    return result;
}
vector<string> letterCombinations2(const string &digits) {
    if (digits.length() == 0)
        return vector<string>{};
    function<void(const string &, int, const string &,
                  map<char, vector<char>> &, vector<string> &)>
        combine = [&](const string &s, int i, const string &r,
                      map<char, vector<char>> &m, vector<string> &o) {
            if (i == (int)s.length()) {
                o.push_back(r);
                return;
            }
            if (m.find(s[i]) == m.end()) {
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
vector<vector<int>> fourSum(vector<int> &nums, int target) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    size_t i = 0;
    while (i + 3 < nums.size()) {
        size_t j = i + 1;
        while (j + 2 < nums.size()) {
            int t = target - nums[i] - nums[j];
            int m = j + 1;
            int n = nums.size() - 1;
            while (m < n) {
                int s = nums[m] + nums[n];
                if (s == t)
                    result.push_back(
                        vector<int>{nums[i], nums[j], nums[m], nums[n]});
                if (s <= t) {
                    while (m + 1 < n && nums[m] == nums[m + 1])
                        m++;
                    m++;
                }
                if (s >= t) {
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
vector<vector<int>> fourSum2(vector<int> &num, int target) {
    if (num.size() < 4)
        return vector<vector<int>>{};
    sort(num.begin(), num.end());
    unordered_map<int, set<pair<int, int>>> twosum;
    set<vector<int>> ans;
    for (int i = 0; i < (int)num.size() - 1; i++) {
        for (int j = i + 1; j < (int)num.size(); j++) {
            int s = num[i] + num[j];
            int t = target - s;
            if (twosum.find(t) != twosum.end()) {
                for_each(
                    twosum[t].begin(), twosum[t].end(), [&](pair<int, int> p) {
                        vector<int> a = {p.first, p.second, num[i], num[j]};
                        ans.insert(a);
                    });
            }
        }
        for (int j = 0; j < i; j++) {
            int s = num[j] + num[i];
            if (twosum.find(s) == twosum.end()) {
                twosum[s] = set<pair<int, int>>{};
            }
            twosum[s].insert(make_pair(num[j], num[i]));
        }
    }
    return vector<vector<int>>(ans.begin(), ans.end());
}
// [TODO] Generalize to X-Sum
vector<vector<int>> fourSum3(vector<int> &num, int target) {
    if (num.size() < 4)
        return vector<vector<int>>{};
    sort(num.begin(), num.end());
    function<void(vector<int> &, int, int, const vector<int> &,
                  vector<vector<int>> &)>
        solve = [&](vector<int> &n, int i, int t, const vector<int> &s,
                    vector<vector<int>> &o) {
            if (s.size() == 3) {
                int l = i;
                int h = n.size() - 1;
                int m;
                while (l <= h) {
                    m = l + ((h - l) >> 1);
                    if (t < n[m]) {
                        if (l == m)
                            break;
                        h = m - 1;
                    } else if (n[m] < t) {
                        if (m == h)
                            break;
                        l = m + 1;
                    } else {
                        vector<int> v(s);
                        v.push_back(n[m]);
                        o.push_back(v);
                        break;
                    }
                }
                return;
            }
            // while (i <= (int)n.size() - 4 + (int)s.size() && n[i] <= t) {
            while (i <= (int)n.size() - 4 + (int)s.size()) {
                int j = i;
                while (j + 1 < (int)n.size() && n[j + 1] == n[j])
                    j++;
                int k = i;
                int u = n[k];
                vector<int> v(s);
                while (k <= j) {
                    v.push_back(n[k]);
                    if (v.size() == 4) {
                        if (u == t)
                            o.push_back(v);
                        break;
                    } else {
                        solve(n, j + 1, t - u, v, o);
                    }
                    k++;
                    u += n[k];
                }
                i = j + 1;
            }
        };
    vector<vector<int>> o;
    solve(num, 0, target, vector<int>{}, o);
    return o;
}
// [TODO] Generalize to X-Sum
vector<vector<int>> fourSum4(vector<int> &num, int target) {
    if (num.size() < 4)
        return vector<vector<int>>{};
    sort(num.begin(), num.end());
    function<void(vector<int> &, int, int, int, const vector<int> &,
                  vector<vector<int>> &)>
        solve = [&](vector<int> &n, int i, int r, int t, const vector<int> &s,
                    vector<vector<int>> &o) {
            // Search n[i..] for remaining r numbers whose sum is t
            // while (r > 0 && i <= (int)n.size() - r && n[i] <= t) {
            while (r > 0 && i <= (int)n.size() - r) {
                int j = i;
                while (j + 1 < (int)n.size() && n[j + 1] == n[j])
                    j++;
                // Range num[i..j] contains the same number
                int k = i;
                int u = 0; // n[k];
                int c = 0; // 1;
                vector<int> v(s);
                // while (k <= j && u <= t && c <= r) {
                while (k <= j && c <= r) {
                    v.push_back(n[k]);
                    u += n[k];
                    c++;
                    if (c == r) {
                        if (u == t)
                            o.push_back(v);
                        break;
                    } else {
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void Print(ListNode *node) {
    if (node == nullptr)
        return;
    while (node != nullptr) {
        cout << node->val << "->";
        node = node->next;
    }
    cout << "null" << endl;
}

void DeleteList(ListNode *node) {
    if (node == nullptr)
        return;
    ListNode *p = node;
    while (p != nullptr) {
        node = p->next;
        delete p;
        p = node;
    }
}

ListNode *ToList(const vector<int> &numbers) {
    ListNode *list = nullptr;
    if (numbers.empty())
        return list;
    list = new ListNode(numbers[0]);
    ListNode *n = list;
    for (size_t i = 1; i < numbers.size(); i++) {
        n->next = new ListNode(numbers[i]);
        n = n->next;
    }
    return list;
}

ListNode *DuplicateList(ListNode *node) {
    ListNode *list = nullptr;
    ListNode *node2 = nullptr;
    while (node != nullptr) {
        if (list == nullptr) {
            list = new ListNode(node->val);
            node2 = list;
        } else {
            node2->next = new ListNode(node->val);
            node2 = node2->next;
        }
        node = node->next;
    }
    return list;
}

int CompareLists(ListNode *node1, ListNode *node2) {
    while (node1 != nullptr && node2 != nullptr) {
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

bool IsSorted(ListNode *node) {
    while (node != nullptr && node->next != nullptr) {
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
ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *q = head;
    for (int i = 0; i < n - 1; i++)
        q = q->next;
    ListNode *p = head;
    if (q->next == nullptr) {
        head = p->next;
        p->next = nullptr;
        delete p;
        return head;
    }
    q = q->next;
    while (q->next != nullptr) {
        q = q->next;
        p = p->next;
    }
    q = p->next;
    p->next = q->next;
    q->next = nullptr;
    delete q;
    return head;
}
ListNode *removeNthFromEnd2(ListNode *head, int n) {
    if (head == nullptr || n <= 0)
        return head;
    ListNode *q = head;
    int i = 0;
    while (i < n && q->next != nullptr) {
        q = q->next;
        i++;
    }
    if (i < n - 1) // only i + 1 (less than n) nodes in the list
        return head;
    ListNode *p = head;
    if (i == n - 1) {
        // Exact i + 1 (= n) nodes in the list
        head = p->next;
        delete p;
        return head;
    }
    // i = n
    // q is the (i+1)-th, i.e. (n+1)-th, node
    // p is the 1-st node
    while (q->next != nullptr) {
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
bool isValid(const string &s) {
    stack<char> a;
    for (size_t i = 0; i < s.size(); i++) {
        switch (s[i]) {
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
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr)
        return l2;
    if (l2 == nullptr)
        return l1;
    ListNode *l = nullptr;
    if (l1->val < l2->val) {
        l = l1;
        l1 = l1->next;
    } else {
        l = l2;
        l2 = l2->next;
    }
    ListNode *n = l;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val < l2->val) {
            n->next = l1;
            n = n->next;
            l1 = l1->next;
        } else {
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
vector<string> generateParenthesis(int n) {
    vector<string> result;
    function<void(int, int, const string &)> gen = [&](int l, int r,
                                                       const string &s) {
        if (l == n && r == n) {
            result.push_back(s);
            return;
        }
        if (l < n) {
            string s1(s);
            s1.append(1, '(');
            gen(l + 1, r, s1);
        }
        if (r < n && l > r) {
            string s2(s);
            s2.append(1, ')');
            gen(l, r + 1, s2);
        }
    };
    gen(0, 0, "");
    return result;
}
vector<string> generateParenthesis2(int n) {
    if (n <= 0)
        return vector<string>{};

    function<void(int, int, map<pair<int, int>, vector<string>> &)> solve =
        [&](
            // l <= r
            int l, // count '(' needed
            int r, // count ')' needed
            map<pair<int, int>, vector<string>> &m) {
            pair<int, int> p = make_pair(l, r);
            m[p] = vector<string>{};
            string s;
            for (int i = 1; i < l; i++) {
                s.append(1, '(');
                string t(s);
                for (int j = 1; j <= r - l + i; j++) {
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
vector<string> generateParenthesis3(int n) {
    if (n <= 0)
        return vector<string>{};
    if (n == 1)
        return vector<string>{"()"};

    function<void(string, int, int, int, vector<string> &)> solve =
        [&](string s,
            int l, // count '(' in s
            int r, // count ')' in s
            int n, vector<string> &o) {
            for (int i = 1; i < n - l; i++) {
                s.append(1, '(');
                string t(s);
                for (int j = 1; j <= l - r + i; j++) {
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
vector<string> generateParenthesis4(int n) {
    vector<string> result;
    if (n <= 0)
        return result;
    result.push_back("()");
    if (n == 1)
        return result;
    for (int i = 2; i <= n; i++) {
        int j = result.size();
        for (int k = 0; k < j; k++) {
            string s = result.front();
            result.erase(result.begin());
            string o = s;
            o.append("()");
            result.push_back(o);
            bool symmetric = true;
            int a = 0;
            int b = o.length() - 1;
            while (a < b) {
                if (o[a] == o[b]) {
                    symmetric = false;
                    break;
                }
                a++;
                b--;
            }
            if (!symmetric) {
                o = "()";
                o.append(s);
                result.push_back(o);
            }
            o = "(";
            o.append(s);
            o.append(")");
            result.push_back(o);
        }
    }
    return result;
}
vector<string> generateParenthesis5(int n) {
    if (n <= 0)
        return vector<string>{};
    if (n == 1)
        return vector<string>{"()"};

    function<void(string, int, int, int, vector<string> &)> solve =
        [&](string s,
            int l, // count '(' in s
            int r, // count ')' in s
            int n, vector<string> &o) {
            if (l == n) {
                s.append(n - r, ')');
                o.push_back(s);
                return;
            }

            string tl(s);
            tl.append(1, '(');
            solve(tl, l + 1, r, n, o);
            if (l > r) {
                string tr(s);
                tr.append(1, ')');
                solve(tr, l, r + 1, n, o);
            }
        };

    vector<string> result;
    string s;
    solve(s, 0, 0, n, result);
    return result;
}

// 24. Swap Nodes in Pairs
// Given a linked list, swap every two adjacent nodes and return its head.
// You may not modify the values in the list's nodes, only nodes itself may
// be changed. Example:
// Given 1->2->3->4, you should return the list as 2->1->4->3.
ListNode *swapPairs(ListNode *head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    // swap first two nodes
    ListNode *p = head;
    head = p->next;
    p->next = head->next;
    head->next = p;
    // Swap the two nodes after p
    // i.e. p->next->next
    while (p->next != nullptr && p->next->next != nullptr) {
        ListNode *q = p->next->next;
        p->next->next = q->next;
        q->next = p->next;
        p->next = q;
        p = p->next->next;
    }
    return head;
}
ListNode *swapPairs2(ListNode *head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    // swap f->s
    ListNode *f = head;
    ListNode *s = f->next;
    f->next = s->next;
    s->next = f;
    head = s;
    ListNode *p = f;
    f = f->next;
    // two nodes after p
    // p->f->s
    while (f != nullptr) {
        s = f->next;
        if (s == nullptr)
            break;
        f->next = s->next;
        s->next = f;
        p->next = s;
        p = f;
        f = f->next;
    }
    return head;
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
int removeDuplicates(vector<int> &nums) {
    if (nums.empty())
        return 0;
    size_t i = 0;
    for (size_t j = 1; j < nums.size(); j++) {
        if (nums[j - 1] != nums[j]) {
            if (i + 1 != j)
                nums[i + 1] = nums[j];
            i++;
        }
    }
    return i + 1;
}
int removeDuplicates2(vector<int> &nums) {
    if (nums.empty())
        return 0;
    size_t i = 0;
    for (size_t j = 1; j < nums.size(); j++) {
        // i increases only when j should be kept
        if (nums[j - 1] != nums[j] && (++i) != j)
            nums[i] = nums[j];
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
int removeElement(vector<int> &nums, int val) {
    int i = -1;
    for (int j = 0; j < (int)nums.size(); j++) {
        if (nums[j] != val) {
            if (i + 1 != j)
                nums[i + 1] = nums[j];
            i++;
        }
    }
    return i + 1;
}
int removeElement2(vector<int> &nums, int val) {
    int i = -1;
    for (int j = 0; j < (int)nums.size(); j++) {
        // i increases only when j should be kept
        if (nums[j] != val && (++i) != j)
            nums[i] = nums[j];
    }
    return i + 1;
}
// Remove by swaping to end, not stable
int removeElement3(vector<int> &nums, int val) {
    int i = 0;
    int n = nums.size();
    while (i < n) {
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
int strStr(string haystack, string needle) {
    if (needle.empty())
        return 0;
    if (haystack.size() < needle.size())
        return -1;
    size_t i = 0;
    while (i <= haystack.size() - needle.size()) {
        if (haystack[i] == needle[0]) {
            size_t j = i;
            size_t k = 0;
            while (j < haystack.size() && k < needle.size() &&
                   haystack[j] == needle[k]) {
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
int strStr2(string haystack, string needle) {
    if (needle.empty())
        return 0;
    size_t i = 0;
    while (i + needle.size() <= haystack.size()) {
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
const char *strStr3(const char *haystack, const char *needle) {
    if (*needle == '\0')
        return haystack;
    if (*haystack == '\0')
        return nullptr;
    int lh = 0;
    const char *h = haystack;
    while (*h != '\0') {
        lh++;
        h++;
    }
    int ln = 0;
    const char *n = needle;
    while (*n != '\0') {
        ln++;
        n++;
    }
    if (lh < ln)
        return nullptr;
    for (int i = 0; i <= lh - ln; i++, haystack++) {
        if (*haystack == *needle) {
            h = haystack;
            n = needle;
            while (*h != '\0' && *n != '\0' && *n == *h) {
                h++;
                n++;
            }
            if (*n == '\0')
                return haystack;
        }
    }
    return nullptr;
}
const char *strStr4(const char *input1, const char *input2) {
    if (input1 == nullptr || input2 == nullptr)
        return nullptr;
    if (*input2 == '\0')
        return input1;
    const char *q = input1;
    const char *p = input2;
    while (*(q + 1) != '\0' && *(p + 1) != '\0') {
        q++;
        p++;
    }
    if (*(q + 1) == '\0' && *(p + 1) != '\0') {
        return nullptr; // input2 is longer than input1
    }
    // now input1 is not shorter than input2
    // set p to the beginning of input1
    p = input1;
    // Hop p and q at same step until q reaches the end of input1
    while (*q != '\0') {
        if (*p == *input2) {
            const char *r = p;
            const char *s = input2;
            while (*s != '\0' && *r == *s) {
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
const char *strStr5(const char *input1, const char *input2) {
    if (input1 == nullptr || input2 == nullptr)
        return nullptr;
    const char *p = input1;
    while (*p != '\0') {
        if (*p == *input2) {
            const char *r = p;
            const char *s = input2;
            while (*r != '\0' && *s != '\0' && *r == *s) {
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
int divide(int dividend, int divisor) {
    if (divisor == 1)
        return dividend;
    if (divisor == -1)
        return dividend == INT_MIN ? INT_MAX : -dividend;
    if (divisor == INT_MIN)
        return dividend == INT_MIN ? 1 : 0;
    bool negative = false;
    if (divisor < 0) {
        if (dividend < 0) {
            if (divisor < dividend)
                return 0;
            dividend -= divisor;
            dividend = -dividend;
        } else {
            if (dividend < -divisor)
                return 0;
            dividend += divisor;
            negative = true;
        }
        divisor = -divisor;
    } else {
        if (dividend < 0) {
            if (-divisor < dividend)
                return 0;
            dividend += divisor;
            negative = true;
            dividend = -dividend;
        } else {
            if (dividend < divisor)
                return 0;
            dividend -= divisor;
        }
    }
    int q = 1; // already subtract one divisor from dividend
    int n = 1;
    int d = divisor;
    while (dividend >= divisor) {
        if (dividend - d < 0) {
            d = d >> 1;
            n = n >> 1;
        } else if (dividend - d >= d) {
            d = d << 1;
            n = n << 1;
        } else {
            dividend -= d;
            q += n;
        }
    }
    return negative ? -q : q;
}
int divide2(int dividend, int divisor) {
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
    if (longDividend < 0) {
        longDividend = -longDividend;
        if (longDivisor < 0)
            longDivisor = -longDivisor;
        else
            negative = true;
    } else if (longDivisor < 0) {
        longDivisor = -longDivisor;
        negative = true;
    }
    int quotient = 0;
    // use long in case of overflow when left shift by 1
    long d = longDivisor;
    int m = 1;
    while (longDividend >= longDivisor) {
        if (d <= longDividend && longDividend < d << 1) {
            quotient += m;
            longDividend -= d;
        } else if (longDividend < d) {
            d = d >> 1;
            m = m >> 1;
        } else { // d << 1 <= longDividend
            d = d << 1;
            m = m << 1;
        }
    }
    return negative ? -quotient : quotient;
}
int divide3(int dividend, int divisor) {
    if (divisor == 1)
        return dividend;
    if (divisor == -1)
        return dividend == INT_MIN ? INT_MAX : -dividend;
    if (divisor == INT_MIN)
        return dividend == INT_MIN ? 1 : 0;
    long long de = dividend;
    long long ds = divisor;
    bool negative = false;
    if (de > 0 && ds < 0) {
        negative = true;
        ds = -ds;
    } else if (de < 0 && ds > 0) {
        negative = true;
        de = -de;
    } else if (de < 0 && ds < 0) {
        de = -de;
        ds = -ds;
    }
    long long r = 0;
    while (de >= ds) {
        long long d = ds;
        long long i = 1;
        while (de >= d) {
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
int divide4(int dividend, int divisor) {
    if (divisor == 1)
        return dividend;
    if (divisor == -1)
        return dividend == INT_MIN ? INT_MAX : -dividend;
    if (divisor == INT_MIN)
        return dividend == INT_MIN ? 1 : 0;
    long long de = dividend;
    long long ds = divisor;
    bool negative = false;
    if (de > 0 && ds < 0) {
        negative = true;
        ds = -ds;
    } else if (de < 0 && ds > 0) {
        negative = true;
        de = -de;
    } else if (de < 0 && ds < 0) {
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
    while (de >= d) {
        d = d << 1;
        i = i << 1;
        v.push_back(d);
    }
    d = d >> 1;
    i = i >> 1;
    de -= d;
    v.pop_back();
    r += i;
    while (de >= ds) {
        int j = 0;
        int k = v.size() - 1;
        while (j <= k) {
            int m = j + ((k - j) >> 1);
            if (de < v[m]) {
                if (j == m) {
                    if (m > 0) {
                        r += (long long)(1 << (m - 1));
                        de -= v[m - 1];
                    }
                    while ((int)v.size() > m)
                        v.pop_back();
                    break;
                }
                k = m - 1;
            } else if (v[m] < de) {
                if (m == k) {
                    r += (long long)(1 << m);
                    de -= v[m];
                    while ((int)v.size() > m + 1)
                        v.pop_back();
                    break;
                }
                j = m + 1;
            } else {
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
int divide5(int dividend, int divisor) {
    bool negative = false;
    if (dividend < 0) {
        if (divisor > 0) {
            negative = true;
            divisor = -divisor;
        } else {
            if (dividend == INT_MIN && divisor == -1)
                return INT_MAX;
        }
    } else {
        if (divisor < 0) {
            negative = true;
            divisor = -divisor;
        }
    }
    int q = 0;
    int n = 1;
    int d = divisor;
    if (dividend < 0) {
        while (dividend <= divisor) {
            if (dividend - d > 0) {
                d = d >> 1;
                n = n >> 1;
            } else if (dividend - d <= d) {
                d = d << 1; // runtime error: left shift of negative value -1
                            // when dividing -1 by 1
                n = n << 1;
            } else {
                dividend += d; // BUG, shoud be subtraction
                q += n;
            }
        }

    } else {
        while (dividend >= divisor) {
            if (dividend - d < 0) {
                d = d >> 1;
                n = n >> 1;
            } else if (dividend - d >= d) {
                d = d << 1;
                n = n << 1;
            } else {
                dividend -= d;
                q += n;
            }
        }
    }
    return negative ? -q : q;
}
int divide6(int dividend, int divisor) {
    bool negative = false;
    if (dividend < 0) {
        if (divisor > 0) {
            if (dividend == INT_MIN && divisor == 1)
                return INT_MIN;
            negative = true;
            divisor = -divisor;
        } else {
            if (dividend == INT_MIN && divisor == -1)
                return INT_MAX;
        }
    } else {
        if (divisor < 0) {
            negative = true;
            divisor = -divisor;
        }
    }
    int q = 0;
    int n = 1;
    int d = divisor;
    if (dividend < 0) {
        while (dividend <= divisor) {
            if (dividend - d > 0) {
                d = (d & (0x7FFFFFFF) >> 1) & 0x80000000;
                n = n >> 1;
            } else if (dividend - d <= d) {
                d = d + d;
                n = n << 1; // runtime error: left shift of negative value
                            // -2147483648 when divided by -3
            } else {
                dividend -= d;
                q += n;
            }
        }
    } else {
        while (dividend >= divisor) {
            if (dividend - d < 0) {
                d = d >> 1;
                n = n >> 1;
            } else if (dividend - d >= d) {
                d = d << 1;
                n = n << 1;
            } else {
                dividend -= d;
                q += n;
            }
        }
    }
    return negative ? -q : q;
}
int divide7(int dividend, int divisor) {
    if (dividend == INT_MIN) {
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
    while (udividend >= udivisor) {
        if (udividend < d) {
            d = d >> 1;
            n = n >> 1;
        } else if (udividend - d >= d) {
            d = d << 1;
            n = n << 1;
        } else {
            udividend -= d;
            q += n;
        }
    }
    return negative ? -q : q;
}

// 31. Next Permutation
// Implement next permutation, which rearranges numbers into the
// lexicographically next greater permutation of numbers. If such arrangement is
// not possible, it must rearrange it as the lowest possible order (ie, sorted
// in ascending order). The replacement must be in-place and use only constant
// extra memory. Here are some examples. Inputs are in the left-hand column and
// its corresponding outputs are in the right-hand column. 1,2,3 -> 1,3,2 3,2,1
// -> 1,2,3 1,1,5 -> 1,5,1
void nextPermutation(vector<int> &nums) {
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
    while (j <= k) {
        int m = j + ((k - j) >> 1);
        if (nums[i] < nums[m]) {
            if (0 <= m - 1 && nums[m - 1] <= nums[i]) {
                swap(nums[i], nums[m]);
                break;
            }
            k = m - 1;
        } else {
            if (m + 1 < (int)nums.size() && nums[i] < nums[m + 1]) {
                swap(nums[i], nums[m + 1]);
                break;
            }
            j = m + 1;
        }
    }
}
void nextPermutation2(vector<int> &nums) {
    if (nums.size() < 2)
        return;
    size_t i = nums.size() - 1;
    while (1 <= i && nums[i - 1] >= nums[i])
        i--;
    size_t j = i;
    size_t k = nums.size() - 1;
    while (j < k)
        swap(nums[j++], nums[k--]);
    if (1 <= i) {
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
int longestValidParentheses(const string &s) {
    size_t m = 0;
    stack<size_t> p;
    for (size_t i = 0; i < s.size(); i++) {
        if (!p.empty() && s[i] == ')' && s[p.top()] == '(') {
            p.pop();
            m = max(m, p.empty() ? i + 1 : i - p.top());
        } else {
            p.push(i);
        }
    }
    return (int)m;
}
int longestValidParentheses2(const string &s) {
    int len = s.length();
    if (len == 0)
        return 0;
    vector<pair<int, int>> p;
    int i = 0;
    while (i + 1 < len) {
        if (s[i] == '(' && s[i + 1] == ')') {
            int j = i;
            int k = i + 1;
            while (j >= 0 && k < len && s[j] == '(' && s[k] == ')') {
                j--;
                k++;
            }
            p.push_back(make_pair(j + 1, k - 1));
            i = k;
        } else
            i++;
    }
    if (p.size() == 0)
        return 0;
    vector<pair<int, int>>::iterator it = p.begin();
    while (it + 1 != p.end()) {
        if (it->second + 1 == (it + 1)->first) {
            it->second = (it + 1)->second;
            p.erase(it + 1);
        } else {
            it++;
        }
    }
    bool stop = false;
    while (!stop) {
        stop = true;
        for (int j = 0; j < (int)p.size(); j++) {
            int l = p[j].first - 1;
            int r = p[j].second + 1;
            while (l >= 0 && r < len && s[l] == '(' && s[r] == ')') {
                stop = false;
                p[j].first = l;
                p[j].second = r;
                l--;
                r++;
            }
        }
        it = p.begin();
        while (it + 1 != p.end()) {
            if (it->second + 1 == (it + 1)->first) {
                stop = false;
                it->second = (it + 1)->second;
                p.erase(it + 1);
            } else {
                it++;
            }
        }
    }
    int m = 0;
    for (int j = 0; j < (int)p.size(); j++) {
        if (p[j].second - p[j].first + 1 > m) {
            m = p[j].second - p[j].first + 1;
        }
    }
    return m;
}
int longestValidParentheses3(const string &s) {
    int len = s.length();
    if (len == 0)
        return 0;
    function<bool(int &, int &)> expand = [&](int &j, int &k) -> bool {
        bool e = false;
        while (j - 1 >= 0 && k + 1 < len && s[j - 1] == '(' &&
               s[k + 1] == ')') {
            e = true;
            j--;
            k++;
        }
        return e;
    };
    int m = 0;
    stack<pair<int, int>> p;
    int i = 0;
    while (i + 1 < len) {
        if (s[i] == '(' && s[i + 1] == ')') {
            int j = i;
            int k = i + 1;
            expand(j, k);
            while (!p.empty() && p.top().second + 1 == j) {
                j = p.top().first;
                p.pop();
                if (!expand(j, k))
                    break;
            }
            if (k - j + 1 > m)
                m = k - j + 1;
            p.push(make_pair(j, k));
            i = k + 1;
        } else {
            i++;
        }
    }
    return m;
}
// This is wrong. e.g. "((()())((" return 0 but the answer should be 6
int longestValidParentheses4(const string &s) {
    int len = s.length();
    if (len == 0)
        return 0;
    int i = -1;
    int n = -1;
    int m = 0;
    for (int j = 0; j < len; j++) {
        if (s[j] == '(') {
            if (n < 0) {
                n = 1;
                i = j;
            } else {
                n++;
            }
        } else if (s[j] == ')') {
            if (n == 0) {
                m = std::max(m, j - i);
            }
            n--;
        }
    }
    if (n == 0) {
        m = std::max(m, len - i);
    }
    return m;
}
// This is wrong. e.g. "()()" return 2 but the answer should be 4
int longestValidParentheses5(const string &s) {
    int m = 0;
    stack<int> p;
    for (int i = 0; i < (int)s.length(); i++) {
        switch (s[i]) {
        case '(':
            p.push(i);
            break;
        case ')':
            if (!p.empty()) {
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
int search(const vector<int> &nums, int target) {
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h) {
        int m = l + ((h - l) >> 1);
        if (target < nums[m]) {
            if (nums[0] <= nums[m]) {
                if (nums[0] <= target) {
                    if (l == m)
                        break;
                    h = m - 1;
                } else {
                    if (m == h)
                        break;
                    l = m + 1;
                }
            } else {
                if (l == m)
                    break;
                h = m - 1;
            }
        } else if (nums[m] < target) {
            if (nums[0] <= nums[m]) {
                if (m == h)
                    break;
                l = m + 1;
            } else {
                if (nums[0] <= target) {
                    if (l == m)
                        break;
                    h = m - 1;
                } else {
                    if (m == h)
                        break;
                    l = m + 1;
                }
            }
        } else {
            return m;
        }
    }
    return -1;
}
int search2(const vector<int> &nums, int target) {
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (nums[m] == target)
            return m;
        else if (nums[m] < target) {
            if (nums[0] < nums[m])
                l = m + 1;
            else if (target <= nums[r])
                l = m + 1;
            else
                r = m - 1;
        } else {
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

// 34. Find First and Last Position of Element in Sorted Array
// Given an array of integers nums sorted in ascending order, find the starting
// and ending position of a given target value. Your algorithm's runtime
// complexity must be in the order of O(log n). If the target is not found in
// the array, return [-1, -1]. Example 1: Input: nums = [5,7,7,8,8,10], target =
// 8 Output: [3,4] Example 2: Input: nums = [5,7,7,8,8,10], target = 6 Output:
// [-1,-1]
vector<int> searchRange(const vector<int> &nums, int target) {
    int l = 0;
    int h = (int)nums.size() - 1;
    int first = -1;
    int second = -1;
    bool foundFirst = false;
    while (l <= h) {
        int m = l + ((h - l) >> 1);
        if (target < nums[m]) {
            if (l == m)
                break;
            h = m - 1;
        } else if (nums[m] < target) {
            if (m == h)
                break;
            l = m + 1;
        } else {
            if (!foundFirst) {
                if (l == m || nums[m - 1] < target) {
                    foundFirst = true;
                    first = m;
                    l = m;
                    h = (int)nums.size() - 1;
                } else {
                    h = m - 1;
                }
            } else {
                if (m == h || target < nums[m + 1]) {
                    second = m;
                    break;
                } else {
                    l = m + 1;
                }
            }
        }
    }
    return vector<int>{first, second};
}
vector<int> searchRange2(const vector<int> &nums, int target) {
    if (nums.empty())
        return vector<int>{-1, -1};
    int l = 0;
    int r = nums.size() - 1;
    int m = -1;
    while (l <= r) {
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
    if (l < m) {
        n = m - 1;
        while (l <= n) {
            b = l + ((n - l) >> 1);
            if (nums[b] == target) {
                if (b == 0 || nums[b - 1] < target)
                    break;
                else
                    n = b - 1;
            } else {
                if (nums[b + 1] == target) {
                    b++;
                    break;
                } else
                    l = b + 1;
            }
        }
        if (l > n)
            b = -1;
    }
    int e = m;
    if (m < r) {
        n = m + 1;
        while (n <= r) {
            e = n + ((r - n) >> 1);
            if (nums[e] == target) {
                if (e == (int)nums.size() - 1 || nums[e + 1] > target)
                    break;
                else
                    n = e + 1;
            } else {
                if (nums[e - 1] == target) {
                    e--;
                    break;
                } else
                    r = e - 1;
            }
        }
        if (n > r)
            e = -1;
    }
    return vector<int>{b, e};
}
vector<int> searchRange3(const vector<int> &nums, int target) {
    int b = -1;
    int e = -1;
    bool foundBegin = false;
    bool foundEnd = false;
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (nums[m] < target)
            l = m + 1;
        else if (target < nums[m])
            r = m - 1;
        else if (!foundBegin) {
            if (l == m) {
                foundBegin = true;
                b = m;
                l = b;
                r = nums.size() - 1;
            } else
                r = m;
        } else if (!foundEnd) {
            if (l < m)
                l = m;
            else {
                foundEnd = true;
                e = m == r ? m : (nums[r] == target ? r : m);
            }
        } else {
            break;
        }
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
int searchInsert(const vector<int> &nums, int target) {
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h) {
        int m = l + ((h - l) >> 1);
        if (target < nums[m]) {
            if (l == m)
                return m;
            h = m - 1;
        } else if (nums[m] < target) {
            if (m == h)
                return m + 1;
            l = m + 1;
        } else {
            return m;
        }
    }
    return 0;
}
int searchInsert2(const vector<int> &nums, int target) {
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (nums[m] == target)
            return m;
        if (nums[m] < target) {
            if (m == r || nums[m + 1] > target)
                return m + 1;
            else
                l = m + 1;
        } else {
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
bool isValidSudoku(const vector<vector<char>> &board) {
    map<size_t, set<char>> row;
    map<size_t, set<char>> col;
    map<size_t, set<char>> cell;
    for (size_t i = 0; i < board.size(); i++) {
        row[i] = set<char>{};
        for (size_t j = 0; j < board[0].size(); j++) {
            if (i == 0)
                col[j] = set<char>{};
            int k = (i / 3) * 3 + (j / 3);
            if (cell.find(k) == cell.end())
                cell[k] = set<char>{};
            if (board[i][j] != '.') {
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
bool isValidSudoku2(const vector<vector<char>> &board) {
    map<size_t, set<char>> rows;
    map<size_t, set<char>> cols;
    map<size_t, set<char>> grids;
    for (size_t i = 0; i < board.size(); i++) {
        if (rows.find(i) == rows.end())
            rows[i] = set<char>{};
        for (size_t j = 0; j < board[i].size(); j++) {
            if (i == 0 && cols.find(j) == cols.end())
                cols[j] = set<char>();
            if (i % 3 == 0 && j % 3 == 0 &&
                grids.find(i * 3 + j) == grids.end()) {
                grids[i * 3 + j] = set<char>{};
            }
            if (board[i][j] != '.') { // A real check may be against '0'-'9'
                if (rows[i].find(board[i][j]) != rows[i].end())
                    return false;
                rows[i].insert(board[i][j]);
                if (cols[j].find(board[i][j]) != cols[j].end())
                    return false;
                cols[j].insert(board[i][j]);
                auto k = (i / 3) * 3 + (j / 3);
                if (grids[k].find(board[i][j]) != grids[k].end())
                    return false;
                grids[k].insert(board[i][j]);
            }
        }
    }
    return true;
}
bool isValidSudoku3(const vector<vector<char>> &board) {
    map<char, set<size_t>> row;
    map<char, set<size_t>> col;
    map<char, set<size_t>> cell;
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[0].size(); j++) {
            char c = board[i][j];
            if (c != '.') {
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
void solveSudoku(vector<vector<char>> &board) {
    function<bool(size_t, size_t, vector<vector<char>> &)> solve =
        [&](size_t i, size_t j, vector<vector<char>> &b) -> bool {
        if (i == 9 && j == 0)
            return true;
        if (b[i][j] != '.')
            return solve(j < 8 ? i : i + 1, j < 8 ? j + 1 : 0, b);
        for (char c = '1'; c <= '9'; c++) {
            bool isCandidate = true;
            for (size_t k = 0; k < 9; k++) {
                if (b[i][k] == c) {
                    isCandidate = false;
                    break;
                }
            }
            if (!isCandidate)
                continue;
            for (size_t k = 0; k < 9; k++) {
                if (b[k][j] == c) {
                    isCandidate = false;
                    break;
                }
            }
            if (!isCandidate)
                continue;
            size_t m = (i / 3) * 3;
            size_t n = (j / 3) * 3;
            for (size_t p = m; p < m + 3; p++) {
                for (size_t q = n; q < n + 3; q++) {
                    if (b[p][q] == c) {
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
void solveSudoku2(vector<vector<char>> &board) {
    function<void(int &, int, int &, int)> oneStep = [&](int &i, int r, int &j,
                                                         int c) {
        j++;
        j = j % c;
        if (j == 0) {
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
        while (i != (int)b.size() - 1 || j != (int)b[i].size() - 1) {
            if (b[i][j] == '.')
                break;
            oneStep(i, (int)b.size(), j, (int)b[i].size());
        }
        // Now (i, j) is either empty or it is the bottom-right element of b
        if (b[i][j] != '.')
            return true;
        pair<int, int> p = make_pair(i, j);
        for (set<char>::iterator it = m[p].begin(); it != m[p].end(); it++) {
            char c = *it;
            if (row[i].find(c) == row[i].end() &&
                col[j].find(c) == col[j].end() &&
                cell[i / 3][j / 3].find(c) == cell[i / 3][j / 3].end()) {
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
    for (int i = 0; i < (int)board.size(); i++) {
        for (int j = 0; j < (int)board[i].size(); j++) {
            if (board[i][j] != '.') {
                row[i].insert(board[i][j]);
                col[j].insert(board[i][j]);
                cell[i / 3][j / 3].insert(board[i][j]);
            }
        }
    }
    map<pair<int, int>, set<char>> m;
    for (int i = 0; i < (int)board.size(); i++) {
        for (int j = 0; j < (int)board[i].size(); j++) {
            if (board[i][j] == '.') {
                pair<int, int> p = make_pair(i, j);
                m[p] = set<char>{};
                for (char c = '1'; c <= '9'; c++) {
                    if (row[i].find(c) == row[i].end() &&
                        col[j].find(c) == col[j].end() &&
                        cell[i / 3][j / 3].find(c) ==
                            cell[i / 3][j / 3].end()) {
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
string countAndSay(int n) {
    string s = "1";
    for (int i = 2; i <= n; i++) {
        size_t j = 0;
        stringstream ss;
        while (j < s.size()) {
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
string countAndSay2(int n) {
    if (n <= 0)
        return "";
    string s = "1";
    for (int i = 0; i < n - 1; i++) {
        int j = 0;
        string o;
        while (j < (int)s.length()) {
            int k = j;
            while (k + 1 < (int)s.length() && s[k + 1] == s[k])
                k++;
            int c = k - j + 1;
            int m = o.length();
            while (c > 0) {
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
vector<vector<int>> combinationSum(const vector<int> &candidates, int target) {
    vector<vector<int>> result;
    function<void(size_t, int, vector<int> &)> solve = [&](size_t i, int t,
                                                           vector<int> &v) {
        if (i >= candidates.size())
            return;
        if (candidates[i] <= t) {
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
                                     int target) {
    vector<vector<int>> result;
    function<void(size_t, int, vector<int> &)> solve = [&](size_t i, int t,
                                                           vector<int> &v) {
        if (i >= candidates.size())
            return;
        if (candidates[i] <= t) {
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
vector<vector<int>> combinationSum_3(vector<int> &candidates, int target) {
    vector<vector<int>> result = vector<vector<int>>{};
    sort(candidates.begin(), candidates.end());
    function<void(int, int, vector<int> &)> solve = [&](int i, int t,
                                                        vector<int> &s) {
        for (int j = i; j < (int)candidates.size(); j++) {
            if (candidates[j] > t)
                break;
            vector<int> r(s);
            r.push_back(candidates[j]);
            if (candidates[j] == t) {
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
vector<vector<int>> combinationSum_4(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    map<pair<int, int>, vector<vector<int>>> m;
    function<void(int, int)> solve = [&](int i, int t) {
        pair<int, int> p = make_pair(i, t);
        if (m.find(p) != m.end())
            return;
        m[p] = vector<vector<int>>{};
        for (int j = i; j < (int)candidates.size(); j++) {
            if (candidates[j] > t)
                break;
            if (candidates[j] == t) {
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
vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
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
        for (size_t k = i; k <= j; k++) {
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
vector<vector<int>> combinationSum2_2(vector<int> &candidates, int target) {
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
        if (candidates[i] == t) {
            result.push_back(c1);
            return;
        }
        solve(i + 1, t - candidates[i], c1);
        while (i + 1 < candidates.size() &&
               candidates[i] == candidates[i + 1]) {
            // This is needed to eliminate duplicate solutions
            i++;
        }
        solve(i + 1, t, c);
    };
    vector<int> s;
    solve(0, target, s);
    return result;
}
vector<vector<int>> combinationSum2_3(vector<int> &candidates, int target) {
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
        for (size_t k = i; k <= j; k++) {
            s += candidates[k];
            if (s > t)
                break;
            vector<int> c1(c);
            c1.insert(c1.end(), k - i + 1, candidates[i]);
            if (s == t) {
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
int firstMissingPositive(vector<int> &nums) {
    if (nums.empty())
        return 1;
    int m = INT_MAX;
    for (size_t i = 0; i < nums.size(); i++) {
        if (nums[i] > 0 && m > nums[i])
            m = nums[i];
    }
    if (m > 1)
        return 1;
    for (int i = 0; i < (int)nums.size(); i++) {
        while (nums[i] > 0 && nums[i] != i + 1) {
            int j = nums[i] - 1;
            if (j >= (int)nums.size() || nums[j] == nums[i])
                break;
            swap(nums[i], nums[j]);
        }
    }
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] != i + 1)
            return i + 1;
    }
    return nums.size() + 1;
}
int firstMissingPositive2(vector<int> &nums) {
    if (nums.empty())
        return 1;
    set<int> s;
    for (size_t i = 0; i < nums.size(); i++) {
        if (nums[i] > 0)
            s.insert(nums[i]);
    }
    int j = 1;
    for (auto it = s.cbegin(); it != s.cend(); it++) {
        if (*it != j)
            break;
        j++;
    }
    return j;
}
// This is wrong. For [0,2,2,1,1], expect 3 but get 2
int firstMissingPositive3(vector<int> &nums) {
    if (nums.empty())
        return 1;
    sort(nums.begin(), nums.end());
    size_t i = 0;
    while (i < nums.size() && nums[i] <= 0)
        i++;
    int j = 1;
    while (i < nums.size() && nums[i] == j) {
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
// Input: [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
int trap(const vector<int> &height) {
    int v = 0;
    int i = 0;
    while (i < (int)height.size()) {
        int j = i;
        while (j + 1 < (int)height.size() && height[i] > height[j + 1])
            j++;
        if (j + 1 == (int)height.size())
            break;
        for (int k = i + 1; k <= j; k++) {
            v += (height[i] - height[k]);
        }
        i = j + 1;
    }
    int h = i; // The peak
    if (h < (int)height.size() - 1) {
        i = (int)height.size() - 1;
        while (h <= i) {
            int j = i;
            while (h <= j - 1 && height[j - 1] < height[i])
                j--;
            if (j == h)
                break;
            for (int k = i - 1; k >= j; k--) {
                v += (height[i] - height[k]);
            }
            i = j - 1;
        }
    }
    return v;
}
int trap2(const vector<int> &height) {
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
    for (int j = 1; j < (int)height.size(); j++) {
        while (!tips.empty() && height[tips.top()] < height[j]) {
            i = tips.top();
            tips.pop();
        }
        if (tips.empty()) {
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
    while (!tips.empty()) {
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
int TrapWater2(int A[], int n) {
    if (A == nullptr || n <= 2)
        return 0;
    stack<int> tips;
    if (A[0] > A[1])
        tips.push(0);
    for (int i = 1; i < n; i++) {
        if (A[i - 1] < A[i] && (i == n - 1 || A[i] >= A[i + 1])) {
            // This loop is wrong because tips[0] can be the lowest tip
            // e.g., [1, 0, 2, 0, 3]
            while (tips.size() > 1 && A[tips.top()] < A[i]) {
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
    while (!tips.empty()) {
        int i = tips.top();
        if (j - i > 1) {
            int m = min(A[i], A[j]);
            for (int k = i + 1; k < j; k++) {
                if (A[k] < m) {
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
string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0")
        return "0";
    function<string(const string &, char)> mul = [&](const string &s,
                                                     char d) -> string {
        string r;
        char c = '0';
        int i = s.size() - 1;
        while (0 <= i || c != '0') {
            int t = c - '0';
            if (0 <= i)
                t += (s[i--] - '0') * (d - '0');
            if (t >= 10) {
                c = '0' + t / 10;
                t %= 10;
            } else {
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
        while (0 <= i || 0 <= j || c != '0') {
            int t = c - '0';
            if (0 <= i)
                t += (s1[i--] - '0');
            if (0 <= j)
                t += (s2[j--] - '0');
            if (t >= 10) {
                c = '1';
                t -= 10;
            } else {
                c = '0';
            }
            r.insert(r.begin(), '0' + t);
        }
        return r;
    };
    string result = "0";
    for (int i = num2.size() - 1; i >= 0; i--) {
        string m = mul(num1, num2[i]);
        result = add(result, m);
        num1.append(1, '0');
    }
    return result;
}
string multiply2(string num1, string num2) {
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
        while (0 <= i) {
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
        while (0 <= i || 0 <= j) {
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
    while (0 <= i) {
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
bool isMatch(string s, string p) {
    function<bool(size_t, size_t)> match = [&](size_t i, size_t j) -> bool {
        if (i == s.size() && j == p.size())
            return true;
        if (j == p.size())
            return false;
        if (i < s.size() && (s[i] == p[j] || p[j] == '?'))
            return match(i + 1, j + 1);
        if (p[j] == '*') {
            while (j < p.size() && p[j] == '*')
                j++;
            size_t k = i;
            while (k <= s.size()) {
                if (match(k, j))
                    return true;
                k++;
            }
        }
        return false;
    };
    return match(0, 0);
}
bool isMatch2(string s, string p) {
    map<pair<size_t, size_t>, bool> m;
    function<bool(size_t, size_t)> match = [&](size_t i, size_t j) -> bool {
        pair<size_t, size_t> v = make_pair(i, j);
        if (m.find(v) != m.end())
            return m[v];
        if (i == s.size() && j == p.size()) {
            m[v] = true;
            return true;
        }
        if (j == p.size()) {
            m[v] = false;
            return false;
        }
        if (i < s.size() && (s[i] == p[j] || p[j] == '?'))
            return match(i + 1, j + 1);
        if (p[j] == '*') {
            while (j < p.size() && p[j] == '*')
                j++;
            size_t k = i;
            while (k <= s.size()) {
                if (match(k, j)) {
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
bool isMatch3(string s, string p) {
    int lastStartIndex = -1;
    int currentIndex = 0;
    int i = 0;
    int j = 0;
    while (i < (int)s.size()) {
        if (j < (int)p.size() && (s[i] == p[j] || p[j] == '?')) {
            i++;
            j++;
            continue;
        }
        if (j < (int)p.size() && p[j] == '*') {
            lastStartIndex = j++;
            currentIndex = i;
            continue;
        }
        if (lastStartIndex != -1) {
            j = lastStartIndex + 1;
            i = ++currentIndex;
            continue;
        }
        return false;
    }
    while (j < (int)p.size() && p[j] == '*')
        j++;
    return j == (int)p.size();
}
bool isMatch(const char *s, const char *p) {
    function<int(const char *)> length = [&](const char *c) -> int {
        // Count characters in c that is not '*'
        int i = 0;
        while (*c != '\0') {
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
        while (*s != '\0' && *p != '\0' && (*s == *p || *p == '?')) {
            ++s;
            ++p;
        }
        // Now *s == '\0' || *p == '\0' || (*s != *p && *p != '?')
        if (*s == '\0' && *p == '\0') {
            m[c] = true;
            return true;
        }
        if (*p == '\0' || *p != '*')
            return false;
        // Now *p == '*'
        while (*p == '*')
            p++;
        // Now *p == '\0' || *p == '?' || *p != '*'
        while (*s != '\0' && i >= j) {
            if ((*s == *p || *p == '?') && isMatchInternal(s + 1, p + 1, m)) {
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
int jump(const vector<int> &nums) {
    size_t i = 0;
    int s = 0;
    size_t j = i + nums[i];
    while (i + 1 < nums.size()) {
        size_t t = j;
        for (size_t k = i + 1; k <= j && k < nums.size(); k++)
            t = max(t, k + nums[k]);
        s++;
        i = j;
        j = t;
    }
    return s;
}
int jump2(const vector<int> &nums) {
    if (nums.size() < 2)
        return 0;
    vector<int> steps(nums.size(), nums.size());
    for (int i = (int)nums.size() - 2; i >= 0; i--) {
        int j = i + nums[i];
        if (j >= (int)nums.size() - 1)
            steps[i] = 1;
        else {
            int m = steps[j];
            for (int k = j - 1; k > i; k--) {
                if (steps[k] < m)
                    m = steps[k];
            }
            steps[i] = 1 + m;
        }
    }
    return steps[0];
}
int jump3(const vector<int> &nums) {
    if (nums.size() < 2)
        return 0;
    map<int, int> step; // Key is the number of steps, value is the index where
                        // to take the steps
    map<int, int>::iterator it;
    step[0] = nums.size() - 1;
    for (int i = (int)nums.size() - 2; i >= 0; i--) {
        int j = i + nums[i];
        for (it = step.begin(); it != step.end(); it++) {
            if (j >= it->second) {
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
int jump4(const vector<int> &nums) {
    if (nums.size() < 2)
        return 0;
    int currentIndex = nums[0];   // max distance current step can reach
    int nextIndex = currentIndex; // max distance next step can reach
    int step = 1;
    int i = 1;
    while (currentIndex < (int)nums.size() - 1 && i <= currentIndex) {
        if (i + nums[i] > nextIndex)
            nextIndex = i + nums[i];
        i++;
        if (i > currentIndex) {
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
vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> result;
    function<void(size_t)> solve = [&](size_t i) {
        if (i + 1 == nums.size()) {
            result.push_back(nums);
            return;
        }
        for (size_t j = i; j < nums.size(); j++) {
            swap(nums[i], nums[j]);
            solve(i + 1);
            swap(nums[i], nums[j]);
        }
    };
    solve(0);
    return result;
}
vector<vector<int>> permute2(vector<int> &nums) {
    vector<vector<int>> result = vector<vector<int>>{};
    function<void(size_t, vector<int> &)> solve = [&](size_t i,
                                                      vector<int> &n) {
        if (i == nums.size()) {
            result.push_back(n);
            return;
        }
        for (size_t j = i; j < nums.size(); j++) {
            vector<int> n1(n);
            swap(n1[i], n1[j]);
            solve(i + 1, n1);
        }
    };
    solve(0, nums);
    return result;
}
vector<vector<int>> permute3(vector<int> &nums) {
    vector<vector<int>> result = vector<vector<int>>{};
    function<void(size_t, vector<int> &)> solve = [&](size_t i,
                                                      vector<int> &n) {
        if (i == nums.size()) {
            result.push_back(n);
            return;
        }
        for (size_t j = i; j < nums.size(); j++) {
            vector<int> n1(n);
            if (j > i) {
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
vector<vector<int>> permuteUnique(vector<int> &nums) {
    vector<vector<int>> result;
    function<void(size_t)> solve = [&](size_t i) {
        if (i + 1 == nums.size()) {
            result.push_back(nums);
            return;
        }
        set<int> visited;
        for (size_t j = i; j < nums.size(); j++) {
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
vector<vector<int>> permuteUnique2(vector<int> &nums) {
    vector<vector<int>> result = vector<vector<int>>{};
    function<void(size_t, vector<int> &)> solve = [&](size_t i,
                                                      vector<int> &n) {
        if (i == nums.size()) {
            result.push_back(n);
            return;
        }
        set<int> visited = {};
        for (size_t j = i; j < nums.size(); j++) {
            if (visited.find(n[j]) == visited.end()) {
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
void rotate(vector<vector<int>> &matrix) {
    // Swap up-right with bottom-left
    for (size_t i = 1; i < matrix.size(); i++) {
        for (size_t j = 0; j < i; j++)
            swap(matrix[i][j], matrix[j][i]);
    }
    size_t n = matrix[0].size();
    size_t c = n >> 1;
    // Swap left with right
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < c; j++) {
            swap(matrix[i][j], matrix[i][n - 1 - j]);
        }
    }
}
void rotate2(vector<vector<int>> &matrix) {
    int d = matrix.size();
    // Swap up-left with bottom-right
    for (int i = 0; i < d - 1; i++) {
        for (int j = 0; j < d - i - 1; j++) {
            swap(matrix[i][j], matrix[d - j - 1][d - i - 1]);
        }
    }
    // Swap up with bottom
    for (int i = 0; i < (d >> 1); i++) {
        for (int j = 0; j < d; j++) {
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
vector<vector<string>> groupAnagrams(const vector<string> &strs) {
    map<string, vector<size_t>> m;
    for (size_t i = 0; i < strs.size(); i++) {
        string s(strs[i]);
        sort(s.begin(), s.end());
        if (m.find(s) == m.end())
            m[s] = {i};
        else
            m[s].push_back(i);
    }
    vector<vector<string>> result;
    for (auto it = m.begin(); it != m.end(); it++) {
        vector<string> v;
        for (size_t i = 0; i < it->second.size(); i++)
            v.push_back(strs[it->second[i]]);
        result.push_back(v);
    }
    return result;
}
vector<vector<string>> groupAnagrams2(const vector<string> &strs) {
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
         it++) {
        result.push_back(it->second);
    }
    return result;
}

// 50. Pow(x, n)
// Implement pow(x, n), which calculates x raised to the power n (xn).
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
double myPow(double x, int n) {
    double y = 1;
    bool negative = false;
    if (n < 0) {
        negative = true;
        if (n == INT_MIN) {
            y = x;
            n = -(n + 1);
        } else {
            n = -n;
        }
    }
    while (n > 0) {
        if ((n & 0x1) > 0) {
            y *= x;
        }
        n = n >> 1;
        x *= x;
    }
    return negative ? 1 / y : y;
}
double myPow2(double x, int n) {
    // Use long long to avoid overflow when flip the sign.
    long long n1 = n;
    bool inverse = false;
    if (n1 < 0) {
        inverse = true;
        n1 = -n1;
    }
    // Use long long to avoid overflow when left-shift the bits.
    long long d;
    double y;
    double z = 1;
    while (n1 > 0) {
        d = 1;
        y = x; // = x^d
        // loop x^2, x^4, x^8, ...
        while ((d << 1) <= n1) {
            y *= y;
            d = d << 1;
        }
        z *= y;
        n1 -= d;
    }
    return inverse ? 1 / z : z;
}
// Keep dividing n by 2 and get the remainder r (0 or 1)
// then there is a sequence:
// n n_1 n_2 n_3 n_4 ...... n_k (= 0)
//   r_1 r_2 r_3 r_4 ...... r_k (= 0)
// x^n = x^{r_1} * (x^2)^{n_1}
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{n_2}
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{n_3}
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{r_4} * (x^16)^{n_4}
//     ......
//     = x^{r_1} * (x^2)^{r_2} * (x^4)^{r_3} * (x^8)^{r_4} * (x^16)^{n_4} ......
//     * (x^{2^(k-1)})^{r_(k-1)} * (x^{2^k})^{n_k}
double myPow3(double x, int n) {
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
    while (n1 > 0) {
        m = m * m;
        if ((n1 & 0x1) == 1) {
            p = p * m;
        }
        n1 = n1 >> 1;
    }
    if (negative)
        p = 1 / p;
    return p;
}
double myPow4(double x, int n) {
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
    while (n1 > 0) {
        if ((n1 & 0x1) == 1) {
            p = p * m;
        }
        m = m * m;
        n1 = n1 >> 1;
    }
    if (negative)
        p = 1 / p;
    return p;
}
double myPow5(double x, int n) {
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
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    function<void(int, vector<string> &)> solve = [&](int i,
                                                      vector<string> &b) {
        if (i == n) {
            result.push_back(b);
            return;
        }
        for (int j = 0; j < n; j++) {
            bool ok = true;
            for (int k = i - 1; k >= 0; k--) {
                if (j - (i - k) >= 0 && b[k][j - (i - k)] == 'Q') {
                    ok = false;
                    break;
                }
                if (b[k][j] == 'Q') {
                    ok = false;
                    break;
                }
                if (j + (i - k) < n && b[k][j + (i - k)] == 'Q') {
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
vector<vector<string>> solveNQueens2(int n) {
    if (n <= 0)
        return vector<vector<string>>{};
    function<void(vector<string> &, int, vector<vector<string>> &)> solve =
        [&](vector<string> &board, size_t line,
            vector<vector<string>> &solutions) {
            for (size_t i = 0; i < board[line].size(); i++) {
                if (board[line][i] == '.') {
                    vector<string> next(board);
                    next[line][i] = 'Q';
                    if (line == board.size() - 1) {
                        for_each(next.begin(), next.end(), [&](string &l) {
                            for (size_t j = 0; j < l.length(); j++) {
                                if (l[j] == 'X')
                                    l[j] = '.';
                            }
                        });
                        solutions.push_back(next);
                    } else {
                        int a = i;
                        int b = i;
                        for (size_t j = line + 1; j < board.size(); j++) {
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
int totalNQueens(int n) {
    if (n <= 0)
        return 0;
    int count = 0;
    vector<int> b(n, 0);
    function<void(int)> solve = [&](int i) {
        if (i == n) {
            count++;
            return;
        }
        for (int j = 0; j < n; j++) {
            bool ok = true;
            for (int k = i - 1; k >= 0; k--) {
                if ((j - (i - k) >= 0 && b[k] == (j - (i - k))) || b[k] == j ||
                    (j + (i - k) < n && b[k] == (j + (i - k)))) {
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
int totalNQueens2(int n) {
    if (n <= 0)
        return 0;
    function<int(vector<vector<bool>> &, int)> count =
        [&](vector<vector<bool>> &board, int line) -> int {
        int c = 0;
        for (size_t i = 0; i < board[line].size(); i++) {
            if (board[line][i] == true) {
                if (line == (int)board.size() - 1)
                    c++;
                else {
                    vector<vector<bool>> next(board);
                    next[line][i] = false;
                    int a = i;
                    int b = i;
                    bool proceed = false;
                    for (size_t j = line + 1; j < board.size(); j++) {
                        a--;
                        if (a >= 0)
                            next[j][a] = false;
                        next[j][i] = false;
                        b++;
                        if (b < (int)next[j].size())
                            next[j][b] = false;
                        proceed = false;
                        for (size_t k = 0; k < next[j].size(); k++) {
                            if (next[j][k] == true) {
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
int maxSubArray(const vector<int> &nums) {
    long long maxSubSum = INT_MIN;
    long long minSum = 0;
    long long sum = 0;
    for (size_t i = 0; i < nums.size(); i++) {
        sum += nums[i];
        maxSubSum = max(maxSubSum, sum - minSum);
        minSum = min(minSum, sum);
    }
    return (int)maxSubSum; // may overflow
}
int maxSubArray2(const vector<int> &nums) {
    // Another option could be to init minSum and sum to nums[0]
    // and loop start at 1. (No, this does not work, e.g. {1, 2})
    long long minSum = 0;
    long long sum = 0;
    long long delta = INT_MIN;
    for (size_t i = 0; i < nums.size(); i++) {
        sum += nums[i];
        if (sum - minSum >= delta)
            delta = sum - minSum;
        if (sum < minSum)
            minSum = sum;
    }
    return (int)delta; // may overflow
}
int maxSubArray2(const vector<int> &nums, int &begin, int &end) {
    begin = -1;
    end = -1;
    long long delta = INT_MIN;
    int minIndex = -1;
    long long minSum = 0; // sum[0..minIndex]
    long long sum = 0;    // sum[0..i]
    for (size_t i = 0; i < nums.size(); i++) {
        sum += nums[i];
        long long d = sum - minSum;
        if (d > delta) {
            delta = d;
            begin = minIndex + 1;
            end = i;
        }
        if (d <= 0) {
            minSum = sum;
            minIndex = i;
        }
    }
    return (int)delta; // may overflow
}
int maxSubArray3(const vector<int> &nums, int &begin, int &end) {
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
    for (int i = 0; i < (int)nums.size(); i++) {
        c += nums[i];
        if (c > delta) {
            // Current element is positive and the current sum is larger than
            // the last one. Update the last seen maximum sum
            begin = l;
            end = i;
            delta = c;
        } else if (c <= 0) {
            // Current element is negative and everything cancel out
            // Reset and start from the next element
            l = i + 1;
            c = 0;
        }
        // Record the max element so far
        if (nums[i] > nums[max])
            max = i;
    }
    if (delta <= 0) {
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
vector<int> spiralOrder(const vector<vector<int>> &matrix) {
    vector<int> result;
    int d = 0;
    int r = matrix.size();
    int c = matrix.empty() ? 0 : matrix[0].size();
    int i = 0;
    int j = -1;
    while (r > 0 && c > 0) {
        if (d == 0) {
            for (int k = 1; k <= c; k++)
                result.push_back(matrix[i][j + k]);
            j += c;
            r--;
        } else if (d == 1) {
            for (int k = 1; k <= r; k++)
                result.push_back(matrix[i + k][j]);
            i += r;
            c--;
        } else if (d == 2) {
            for (int k = 1; k <= c; k++)
                result.push_back(matrix[i][j - k]);
            j -= c;
            r--;
        } else {
            for (int k = 1; k <= r; k++)
                result.push_back(matrix[i - k][j]);
            i -= r;
            c--;
        }
        d = (d + 1) % 4;
    }
    return result;
}
vector<int> spiralOrder2(const vector<vector<int>> &matrix) {
    vector<int> result = vector<int>{};
    if (matrix.empty() || matrix[0].empty())
        return result;
    int h = matrix[0].size();
    int v = matrix.size();
    int i = 0;
    int j = -1;
    int k;
    while (h > 0 && v > 0) {
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
vector<int> spiralOrder3(const vector<vector<int>> &matrix) {
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
    while (m > 0 && n > 0) {
        solve(i, j, m, n);
        i++;
        j++;
        m -= 2;
        n -= 2;
    }
    return result;
}

} // namespace LeetCode
} // namespace Test
#endif
