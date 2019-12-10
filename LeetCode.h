#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include <algorithm>
#include <bitset>
#include <functional>
#include <limits.h>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
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
} // namespace LeetCode
} // namespace Test

#endif
