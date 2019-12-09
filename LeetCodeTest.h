#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "Test.h"
#include "Util.h"

using namespace Test;
using namespace Test::LeetCode;

class LeetCodeTest : public TestClass {
  public:
    LeetCodeTest(Log &log) : TestClass(log) {}
    ~LeetCodeTest(void) {}
    void Init(void);
};

void LeetCodeTest::Init(void) {
    Add("3. Longest Substring Without Repeating Characters", [&]() {
        auto check = [&](const string &s, int el) {
            int l = lengthOfLongestSubstring(s);
            int l2 = lengthOfLongestSubstring2(s);
            int l3 = lengthOfLongestSubstring3(s);
            Logger().WriteInformation("%s, %d%s%d, %d%s%d, %d%s%d\n", s.c_str(),
                                      l, l == el ? "==" : "!=", el, l2,
                                      l2 == el ? "==" : "!=", el, l3,
                                      l3 == el ? "==" : "!=", el);
            ASSERT1(l == el);
            ASSERT1(l2 == el);
            ASSERT1(l3 == el);
        };
        check("abcabcbb", 3);
        check("a", 1);
        check("aa", 1);
        check("ab", 2);
        check("aaa", 1);
        check("aba", 2);
        check("aab", 2);
        check("abc", 3);
        check("abab", 2);
        check("abba", 2);
        check("abca", 3);
        check("aabc", 3);
        check("abac", 3);
        check("abcd", 4);
        check("abcabc", 3);
        check("abcad", 4);
        check("aaabcd", 4);
        for (int i = 0; i < 100; i++) {
            size_t len = 1 + (rand() % 100);
            string s = Random::String(len);
            int l = lengthOfLongestSubstring(s);
            int l2 = lengthOfLongestSubstring2(s);
            int l3 = lengthOfLongestSubstring3(s);
            Logger().WriteInformation("%s, %d%s%d, %d%s%d, %d%s%d\n", s.c_str(),
                                      l, l == l2 ? "==" : "!=", l2, l2,
                                      l2 == l3 ? "==" : "!=", l3, l3,
                                      l3 == l ? "==" : "!=", l);
            ASSERT1(l == l2);
            ASSERT1(l == l3);
        }
    });

    Add("5. Longest Palindromic Substring", [&]() {
        auto check = [&](const string &s, const string &es = "") {
            string p = longestPalindrome(s);
            string p2 = longestPalindrome2(s);
            string p3 = longestPalindrome3(s);
            string p4 = longestPalindrome4(s);
            Logger() << s << ", '" << p << "', '" << p2 << "', '" << p3
                     << "', '" << p4 << "'" << endl;
            if (es.empty()) {
                ASSERT1(p == p2);
                ASSERT1(p == p3);
                ASSERT1(p == p4);
            } else {
                ASSERT1(p == es);
                ASSERT1(p2 == es);
                ASSERT1(p3 == es);
                ASSERT1(p4 == es);
            }
        };

        check("babad", "bab");
        check("cbbd", "bb");
        check("a", "a");
        check("bb", "bb");
        check("ab", "a");
        check("abc", "a");
        check("aab", "aa");
        check("bcc", "cc");
        check("aba", "aba");
        check("aabb", "aa");
        check("aaab", "aaa");
        check("abbb", "bbb");
        check("abab", "aba");
        check("abba", "abba");
        for (int i = 0; i < 100; i++) {
            size_t len = 1 + (rand() % 100);
            string s = Random::String<char>(len, "abcde");
            check(s);
        }
    });

    Add("6. ZigZag Conversion", [&]() {
        auto check = [&](const string &s, int r, const string &es = "") {
            string z = convert(s, r);
            string z2 = convert2(s, r);
            Logger() << s << ", " << z << ", " << z2 << endl;
            if (es.empty()) {
                ASSERT1(z == z2);
            } else {
                ASSERT1(z == es);
                ASSERT1(z2 == es);
            }
        };
        check("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
        check("PAYPALISHIRING", 4, "PINALSIGYAHRPI");
        check("A", 1, "A");
        check("A", 2, "A");
        check("AB", 1, "AB");
        check("AB", 2, "AB");
        check("AB", 3, "AB");
        check("ABC", 2, "ACB");
        check("ABC", 3, "ABC");
        check("ABC", 4, "ABC");
        check("ABCD", 2, "ACBD");
        check("ABCD", 3, "ABDC");
        check("ABCD", 4, "ABCD");
        check("ABCDE", 4, "ABCED");
        for (int i = 0; i < 100; i++) {
            size_t len = 1 + (rand() % 50);
            string s = Random::String(len);
            for (int r = 1; r <= (int)s.size(); r++) {
                check(s, r);
            }
        }
    });

    Add("7. Reverse Integer", [&]() {
        auto check = [&](int x, int e, bool ignoreE = false) {
            int y = reverse(x);
            int y2 = reverse2(x);
            if (ignoreE) {
                Logger() << x << ", " << y << ", " << y2 << endl;
                ASSERT1(y == y2);
            } else {
                Logger() << x << ", " << y << ", " << y2 << ", " << e << endl;
                ASSERT1(y == e);
                ASSERT1(y2 == e);
            }
        };
        check(123, 321);
        check(-123, -321);
        check(120, 21);
        check(INT_MIN, 0);
        check(INT_MAX, 0);
        check(0, 0);
        for (int i = 0; i < 100; i++) {
            int r = rand();
            check(INT_MIN + r, 0, true);
            check(-r, 0, true);
            check(r, 0, true);
            check(INT_MAX - r, 0, true);
        }
    });

    Add("8. String to Integer (atoi)", [&]() {
        auto check = [&](const string &s, int e, bool ignoreE = false) {
            int r = myAtoi(s);
            int r2 = myAtoi2(s);
            int r3 = myAtoi3(s);
            if (ignoreE) {
                Logger() << "\"" << s << "\", " << r << ", " << r2 << ", " << r3
                         << endl;
                ASSERT1(r == r2);
                ASSERT1(r == r3);
            } else {
                Logger() << "\"" << s << "\", " << r << ", " << r2 << ", " << r3
                         << ", " << e << endl;
                ASSERT1(r == e);
                ASSERT1(r2 == e);
                ASSERT1(r3 == e);
            }
        };
        check("", 0);
        check(" ", 0);
        check("  ", 0);
        check("1", 1);
        check(" 2 ", 2);
        check("   33", 33);
        check("     3 4", 3);
        check(" 5w", 5);
        check("+5w", 5);
        check("-5w", -5);
        check(" + 6", 0);
        check(" -  6", 0);
        check("asd", 0);
        check("asd124", 0);
        check("-2147483647", -2147483647);
        check("-2147483648", -2147483648);
        check("-2147483649", -2147483648);
        check(" 2147483647", 2147483647);
        check(" 2147483648", 2147483647);
        for (int i = 0; i < 100; i++) {
            size_t len = Random::Int(20, 1);
            string str = Random::String<char>(len, "0123456789     abcde");
            check(str, 0, true);
        }
    });

    Add("9. Palindrome Number", [&]() {
        auto check = [&](int n, bool e, bool ignoreE = false) {
            bool r = isPalindrome(n);
            bool r2 = isPalindrome2(n);
            bool r3 = isPalindrome3(n);
            if (ignoreE) {
                Logger() << n << ", " << r << ", " << r2 << ", " << r3 << endl;
                ASSERT1(r == r2);
                ASSERT1(r == r3);
            } else {
                Logger() << n << ", " << r << ", " << r2 << ", " << r3 << ", "
                         << e << endl;
                ASSERT1(r == e);
                ASSERT1(r2 == e);
                ASSERT1(r3 == e);
            }
        };
        check(3, true);
        check(33, true);
        check(23, false);
        check(232, true);
        check(1231, false);
        check(12344321, true);
        check(123454321, true);
        check(1234567, false);
        check(INT_MIN, false);
        check(INT_MAX, false);
        check(1000000001, true);
        for (int i = 0; i < 100; i++) {
            check(rand(), false, true);
        }
    });

    Add("11. Container With Most Water", [&]() {
        auto check = [&](const vector<int> &h) {
            int a = maxArea(h);
            int a2 = maxArea2(h);
            int a3 = maxArea3(h);
            Logger() << h << ", " << a << ", " << a2 << ", " << a3 << endl;
            ASSERT1(a == a2);
            ASSERT1(a == a3);
        };
        check(vector<int>{14, 0, 12, 3, 8, 3, 13, 5, 14, 8});
        check(vector<int>{1, 8, 6, 2, 5, 4, 8, 3, 7});
        for (int i = 0; i < 100; i++) {
            int len = Random::Int(100, 2);
            vector<int> h = Random::Vector(len, 1000);
            check(h);
        }
    });

    Add("12. Integer to Roman", [&]() {
        auto check = [&](int n, const string &e, bool ignoreE = false) {
            string r = intToRoman(n);
            string r2 = intToRoman2(n);
            if (ignoreE) {
                Logger() << n << ", " << r << ", " << r2 << endl;
                ASSERT1(r == r2);
            } else {
                Logger() << n << ", " << r << ", " << r2 << ", " << e << endl;
                ASSERT1(r == e);
                ASSERT1(r2 == e);
            }
        };
        check(1, "I");
        check(3, "III");
        check(4, "IV");
        check(5, "V");
        check(7, "VII");
        check(9, "IX");
        check(10, "X");
        check(13, "XIII");
        check(58, "LVIII");
        check(1994, "MCMXCIV");
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(3999, 1);
            check(n, "", true);
        }
    });
}
#endif