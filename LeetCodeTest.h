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

    Add("Roman", [&]() {
        auto check = [&](int n, const string &e, bool ignoreE = false) {
            string r = intToRoman(n);
            string r2 = intToRoman2(n);
            int m = romanToInt(r);
            int m2 = romanToInt(r2);
            if (ignoreE) {
                Logger() << n << ", " << r << ", " << r2 << ", " << m << ", "
                         << m2 << endl;
                ASSERT1(r == r2);
            } else {
                Logger() << n << ", " << r << ", " << r2 << ", " << e << ", "
                         << m << ", " << m2 << endl;
                ASSERT1(r == e);
                ASSERT1(r2 == e);
            }
            ASSERT1(n == m);
            ASSERT1(n == m2);
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

    Add("14. Longest Common Prefix", [&]() {
        auto check = [&](const vector<string> &strs, const string &e,
                         bool ignoreE = false) {
            Logger() << strs;
            string s = longestCommonPrefix(strs);
            string s2 = longestCommonPrefix2(strs);
            string s3 = longestCommonPrefix3(strs);
            if (ignoreE) {
                Logger() << s << ", " << s2 << ", " << s3 << endl;
                ASSERT1(s == s2);
                ASSERT1(s == s3);
            } else {
                Logger() << s << ", " << s2 << ", " << s3 << ", " << e << endl;
                ASSERT1(s == e);
                ASSERT1(s2 == e);
                ASSERT1(s3 == e);
            }
        };
        check({}, "");
        check({""}, "");
        check({"a", "", "adb"}, "");
        check({"a", "ac", "adb"}, "a");
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(5, 0);
            int l = Random::Int(10);
            Logger() << "Generating " << n << " strings, max string length "
                     << l << endl;
            vector<string> strs = Random::Strings<char>(n, l, "ab");
            check(strs, "", true);
        }
    });

    Add("15. 3Sum", [&]() {
        auto check = [&](const vector<int> &n) {
            Logger() << n;
            vector<int> m(n);
            vector<vector<int>> o = threeSum(m);
            vector<int> m2(n);
            vector<vector<int>> o2 = threeSum2(m2);
            vector<int> m3(n);
            vector<vector<int>> o3 = threeSum3(m3);
            Util::SortGrid(o);
            Util::SortGrid(o2);
            Util::SortGrid(o3);
            Logger() << o;
            Logger() << o2;
            Logger() << o3;
            ASSERT1(0 == Util::Compare(o, o2));
            ASSERT1(0 == Util::Compare(o, o3));
        };
        check(vector<int>{-1, 0, 1, 0, -1, 1});
        check(vector<int>{1, 0, -1, 0, -2, 2});
        check(vector<int>{1, 1, 1, 1, 1, 1});
        {
            vector<int> v = {
                -463, -428, -392, -386, -348, -312, -280, -248, -247, -244,
                -224, -216, -198, -195, -195, -189, -175, -173, -167, -155,
                -111, -96,  -36,  -28,  -3,   10,   15,   22,   25,   44,
                44,   49,   50,   68,   84,   88,   104,  107,  111,  116,
                171,  208,  233,  304,  309,  313,  318,  323,  330,  331,
                331,  358,  364,  365,  388,  396,  403,  425,  449};
            check(v);
        }
        for (int i = 0; i < 100; i++) {
            vector<int> v = Random::Vector(Random::Int(100, 3), 1000, -1000);
            check(v);
        }
    });

    Add("16. 3Sum Closest", [&]() {
        auto check = [&](const vector<int> &n, int t) {
            Logger() << n;
            vector<int> m(n);
            int o = threeSumClosest(m, t);
            vector<int> m2(n);
            int o2 = threeSumClosest2(m2, t);
            Logger() << t << ", " << o << ", " << o2 << endl;
            ASSERT1(o == o2);
        };
        for (int i = 0; i < 100; i++) {
            vector<int> v = Random::Vector(Random::Int(100, 3), 1000, -1000);
            check(v, Random::Int(1000, -1000));
        }
    });

    Add("18. 4Sum", [&]() {
        auto check = [&](const vector<int> &n, int t) {
            Logger() << n;
            Logger().WriteInformation("Target: %d\n", t);
            vector<int> m(n);
            vector<vector<int>> o = fourSum(m, t);
            vector<int> m2(n);
            vector<vector<int>> o2 = fourSum2(m2, t);
            vector<int> m3(n);
            vector<vector<int>> o3 = fourSum3(m3, t);
            vector<int> m4(n);
            vector<vector<int>> o4 = fourSum4(m4, t);
            Util::SortGrid(o);
            Logger() << o;
            Util::SortGrid(o2);
            Logger() << o2;
            Util::SortGrid(o3);
            Logger() << o3;
            Util::SortGrid(o4);
            Logger() << o4;
            ASSERT1(0 == Util::Compare(o, o2));
            ASSERT1(0 == Util::Compare(o, o3));
            ASSERT1(0 == Util::Compare(o, o4));
        };
        check(vector<int>{633, -649, -975, 409, -678, 624, -976, -460, -102,
                          -983, 120, 202, 75, 826, -339, -709, 620, 204},
              -666);
        check(vector<int>{1, 0, -1, 0, -2, 2}, 0);
        check(vector<int>{1, 1, 1, 1, 1, 1}, 4);
        {
            vector<int> v = {
                -463, -428, -392, -386, -348, -312, -280, -248, -247, -244,
                -224, -216, -198, -195, -195, -189, -175, -173, -167, -155,
                -111, -96,  -36,  -28,  -3,   10,   15,   22,   25,   44,
                44,   49,   50,   68,   84,   88,   104,  107,  111,  116,
                171,  208,  233,  304,  309,  313,  318,  323,  330,  331,
                331,  358,  364,  365,  388,  396,  403,  425,  449};
            check(v, 2110);
            check(v, 1284);
        }
        for (int i = 0; i < 100; i++) {
            vector<int> v = Random::Vector(Random::Int(100, 3), 1000, -1000);
            check(v, Random::Int(1000, -1000));
        }
    });

    Add("19. Remove Nth Node From End of List", [&]() {
        auto check = [&](ListNode *l, int n) {
            Print(l);
            ListNode *l2 = DuplicateList(l);
            Print(l2);
            l = removeNthFromEnd(l, n);
            l2 = removeNthFromEnd(l2, n);
            Print(l);
            Print(l2);
            ASSERT1(0 == CompareLists(l, l2));
            DeleteList(l);
            DeleteList(l2);
        };
        check(ToList(Util::IncreasingVector(1)), 1);
        check(ToList(Util::IncreasingVector(2)), 1);
        check(ToList(Util::IncreasingVector(2)), 2);
        check(ToList(Util::IncreasingVector(3)), 1);
        check(ToList(Util::IncreasingVector(3)), 2);
        check(ToList(Util::IncreasingVector(3)), 3);
        for (int i = 4; i <= 10; i++) {
            for (int j = 1; j <= i; j++)
                check(ToList(Util::IncreasingVector(i)), j);
        }
    });

    Add("20. Valid Parentheses", [&]() {
        auto check = [&](const string &s, bool e) {
            bool r = isValid(s);
            Logger() << s << ", " << r << ", " << e << endl;
            ASSERT1(r == e);
        };
        check("", true);
        check("(", false);
        check("]", false);
        check("[]", true);
        check(")(", false);
        check("()[]{}", true);
        check("(]", false);
        check("([)]", false);
        check("([{}])", true);
    });

    Add("21. Merge Two Sorted Lists", [&]() {
        auto check = [&](const vector<int> &v1, const vector<int> &v2) {
            ListNode *l1 = ToList(v1);
            ListNode *l2 = ToList(v2);
            Print(l1);
            Print(l2);
            ListNode *l = mergeTwoLists(l1, l2);
            Print(l);
            bool r = IsSorted(l);
            DeleteList(l);
            ASSERT1(r);
        };
        check({}, {});
        check({}, {1});
        check({1}, {});
        check({1}, {1});
        check({2}, {1});
        check({1, 3}, {2, 4});
        check({1, 4, 6}, {2, 3, 5});
        for (int i = 0; i < 100; i++) {
            vector<int> v1 = Random::Vector(Random::Int(100));
            vector<int> v2 = Random::Vector(Random::Int(100));
            sort(v1.begin(), v1.end());
            sort(v2.begin(), v2.end());
            check(v1, v2);
        }
    });

    Add("22. Generate Parentheses", [&]() {
        auto check = [&](int n) {
            Logger().WriteInformation("%d pairs of parentheses:\n", n);
            vector<string> pa = generateParenthesis(n);
            vector<string> pa2 = generateParenthesis2(n);
            vector<string> pa3 = generateParenthesis3(n);
            vector<string> pa5 = generateParenthesis5(n);
            sort(pa.begin(), pa.end());
            Logger() << pa;
            sort(pa2.begin(), pa2.end());
            Logger() << pa2;
            sort(pa3.begin(), pa3.end());
            Logger() << pa3;
            sort(pa5.begin(), pa5.end());
            Logger() << pa5;
            ASSERT1(0 == Util::Compare(pa, pa2));
            ASSERT1(0 == Util::Compare(pa, pa3));
            ASSERT1(0 == Util::Compare(pa, pa5));
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
    });
}
#endif