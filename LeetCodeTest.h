#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "Test.h"
#include "Util.h"
#include <math.h>

using namespace std;
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

    Add("24. Swap Nodes in Pairs", [&]() {
        auto checkPair = [&](ListNode *l) -> bool {
            while (l != nullptr && l->next != nullptr) {
                if (l->val != l->next->val + 1)
                    return false;
                l = l->next->next;
            }
            return true;
        };
        auto check = [&](const vector<int> &v) {
            Logger().WriteInformation("Swap pairs:\n");
            ListNode *l = ToList(v);
            ListNode *l2 = DuplicateList(l);
            Print(l);
            l = swapPairs(l);
            Print(l);
            l2 = swapPairs(l2);
            Print(l2);
            bool r = checkPair(l);
            bool r2 = checkPair(l2);
            int c = CompareLists(l, l2);
            DeleteList(l);
            DeleteList(l2);
            ASSERT1(r);
            ASSERT1(r2);
            ASSERT1(c == 0);
        };
        check(vector<int>{1, 2});
        check(vector<int>{1, 2, 3});
        check(vector<int>{1, 2, 3, 4});
        check(vector<int>{1, 2, 3, 4, 5});
        check(vector<int>{1, 2, 3, 4, 5, 6});
    });

    Add("26. Remove Duplicates from Sorted Array", [&]() {
        auto check = [&](vector<int> &v) {
            Logger() << v;
            set<int> s;
            for (size_t i = 0; i < v.size(); i++) {
                s.insert(v[i]);
            }
            vector<int> v2(v);
            size_t len = removeDuplicates(v);
            Logger() << v;
            size_t len2 = removeDuplicates2(v2);
            Logger() << v2;
            ASSERT1(len == s.size());
            ASSERT1(len2 == s.size());
            for (size_t i = 0; i < len; i++) {
                ASSERT1(v[i] == *s.begin());
                ASSERT1(v2[i] == *s.begin());
                s.erase(s.begin());
            }
        };
        {
            vector<int> v = {0, 1, 2, 3, 4, 5};
            check(v);
        }
        {
            vector<int> v = {0, 0, 0};
            check(v);
        }
        {
            for (int i = 0; i < 20; i++) {
                vector<int> input = Random::Vector(Random::Int(50, 1), 10, -10);
                sort(input.begin(), input.end());
                int length = (int)input.size();
                Logger().WriteInformation("Run %d: %d elements\n", i, length);
                check(input);
            }
        }
    });

    Add("27. Remove Element", [&]() {
        auto check = [&](vector<int> &v, int e) {
            Logger() << v << "Removing " << e << endl;
            vector<int> s;
            for (size_t i = 0; i < v.size(); i++) {
                if (v[i] != e)
                    s.push_back(v[i]);
            }
            vector<int> v2(v);
            vector<int> v3(v);
            int len = removeElement(v, e);
            Logger() << v << "Length " << len << endl;
            int len2 = removeElement2(v2, e);
            Logger() << v2 << "Length " << len2 << endl;
            int len3 = removeElement3(v3, e);
            Logger() << v3 << "Length " << len3 << endl;
            ASSERT1(len == (int)s.size());
            ASSERT1(len2 == (int)s.size());
            ASSERT1(len3 == (int)s.size());
            sort(v.begin(), v.begin() + len);
            sort(v2.begin(), v2.begin() + len2);
            sort(v3.begin(), v3.begin() + len2);
            sort(s.begin(), s.end());
            for (int i = 0; i < len; i++) {
                ASSERT1(v[i] == s[i]);
                ASSERT1(v2[i] == s[i]);
                ASSERT1(v3[i] == s[i]);
            }
        };
        {
            vector<int> v = {0, 1, 2, 3, 4, 5};
            check(v, 0);
        }
        {
            vector<int> v = {0, 0, 0};
            check(v, 0);
        }
        for (int i = 0; i < 20; i++) {
            vector<int> input = Random::Vector(Random::Int(50, 1), 10, -10);
            int length = (int)input.size();
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            check(input, Random::Int(10, -10));
        }
    });

    Add("28. Implement strStr()", [&]() {
        auto check = [&](const char *input1, const char *input2, int index) {
            Logger().WriteInformation("\nInput1:\t%s\n", input1);
            Logger().WriteInformation("Input2:\t%s\n", input2);
            int i = strStr(input1, input2);
            int i2 = strStr2(input1, input2);
            const char *p3 = strStr3(input1, input2);
            int i3 = (int)(p3 == nullptr ? -1 : p3 - input1);
            const char *p4 = strStr4(input1, input2);
            int i4 = (int)(p4 == nullptr ? -1 : p4 - input1);
            const char *p5 = strStr5(input1, input2);
            int i5 = (int)(p5 == nullptr ? -1 : p5 - input1);
            const char *p6 = strstr(input1, input2);
            int i6 = (int)(p6 == nullptr ? -1 : p6 - input1);
            Logger().WriteInformation("Index:\t%d\t%d\t%d\t%d\t%d\t%d\n", i, i2,
                                      i3, i4, i5, i6);
            if (index >= -1) {
                ASSERT1(i == index);
                ASSERT1(i2 == index);
                ASSERT1(i3 == index);
                ASSERT1(i4 == index);
                ASSERT1(i5 == index);
                ASSERT1(i6 == index);
            } else {
                ASSERT1(i2 == i);
                ASSERT1(i3 == i);
                ASSERT1(i4 == i);
                ASSERT1(i5 == i);
                ASSERT1(i6 == i);
            }
        };
        check("", "", 0);
        check("", "a", -1);
        check("a", "", 0);
        check("a", "a", 0);
        check("a", "b", -1);
        check("a", "aa", -1);
        check("aa", "a", 0);
        check("aa", "b", -1);
        check("aa", "aa", 0);
        check("aa", "aaa", -1);
        check("ab", "a", 0);
        check("ab", "b", 1);
        check("ab", "c", -1);
        check("ab", "ab", 0);
        check("abc", "a", 0);
        check("abc", "b", 1);
        check("abc", "c", 2);
        check("abc", "d", -1);
        check("abc", "ab", 0);
        check("abc", "bc", 1);
        check("abc", "abc", 0);
        check("ababa", "ab", 0);
        check("ababa", "ba", 1);
        check("ababa", "aba", 0);
        check("ababa", "bab", 1);
        check("ababa", "ababa", 0);
        check("abcabcab", "abc", 0);
        check("abcabcab", "bca", 1);
        check("abcabcab", "cab", 2);
        check("abdabcab", "abc", 3);
        check("abdabcab", "bca", 4);
        check("abdabcab", "cab", 5);
        for (int i = 0; i < 100; i++) {
            string haystack = Random::String<char>(Random::Int(100), "abc");
            string needle = Random::String<char>(Random::Int(5), "ab");
            check(haystack.c_str(), needle.c_str(), -2);
        }
    });

    Add("29. Divide Two Integers", [&]() {
        auto check = [&](int e, int r) {
            int s = divide(e, r);
            int s2 = divide2(e, r);
            int s3 = divide3(e, r);
            int s4 = divide4(e, r);
            int s5 = (e == INT_MIN && r == -1) ? INT_MAX
                                               : (long long)e / (long long)r;
            Logger().WriteInformation(" %d / %d = %d, %d, %d, %d, %d\n", e, r,
                                      s, s2, s3, s4, s5);
            ASSERT1(s == s5);
            ASSERT1(s2 == s5);
            ASSERT1(s3 == s5);
            ASSERT1(s4 == s5);
        };
        check(5, 2);
        check(-5, 2);
        check(5, -2);
        check(-5, -2);
        check(7, 3);
        check(-7, 3);
        check(7, -3);
        check(-7, -3);
        check(1, 3);
        check(-1, 3);
        check(1, -3);
        check(-1, -3);
        check(INT_MAX, 1);
        check(INT_MIN, 1);
        check(INT_MAX, 2);
        check(INT_MIN, 2);
        check(INT_MAX, 3);
        check(INT_MIN, 3);
        check(INT_MAX, 4);
        check(INT_MIN, 4);
        check(INT_MAX, -1);
        check(INT_MIN, -1);
        check(INT_MAX, -2);
        check(INT_MIN, -2);
        check(INT_MAX, -3);
        check(INT_MIN, -3);
        check(INT_MAX, -4);
        check(INT_MIN, -4);
        check(INT_MIN, INT_MIN);
        check(INT_MAX, INT_MIN);
        check(INT_MIN, INT_MAX);
        check(INT_MAX, INT_MAX);
        for (int i = 0; i < 1000; i++) {
            int e;
            int r;
            switch (i % 3) {
            case 0:
                e = rand();
                if (e == 0)
                    e = 1;
                r = rand();
                if (r == 0)
                    r = 1;
                break;
            case 1:
                e = INT_MIN;
                r = rand();
                if (r == 0)
                    r = 1;
                break;
            case 2:
                e = INT_MAX;
                r = rand();
                if (r == 0)
                    r = 1;
                break;
            }
            if (e > 0 && e < r)
                swap(e, r);
            check(e, r);
        }
    });

    Add("31. Next Permutation", [&]() {
        auto check = [&](vector<int> &v) {
            sort(v.begin(), v.end());
            Logger() << v;
            vector<int> v2(v);
            vector<int> v3(v);
            while (std::next_permutation(v.begin(), v.end())) {
                nextPermutation(v2);
                nextPermutation2(v3);
                Logger() << v2;
                Logger() << v3;
                for (size_t i = 0; i < v.size(); i++) {
                    ASSERT1(v[i] == v2[i]);
                    ASSERT1(v[i] == v3[i]);
                }
            }
            nextPermutation(v2);
            nextPermutation2(v3);
            Logger() << v2;
            Logger() << v3;
            for (size_t i = 0; i < v.size(); i++) {
                ASSERT1(v[i] == v2[i]);
                ASSERT1(v[i] == v3[i]);
            }
        };
        for (int i = 0; i < 10; i++) {
            vector<int> input = Random::Vector(Random::Int(6, 1), 6);
            int length = (int)input.size();
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            check(input);
        }
        for (int i = 0; i < 100; i++) {
            vector<int> v = Random::Vector(Random::Int(10, 1), 10);
            int length = (int)v.size();
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            Logger() << v;
            vector<int> v2(v);
            vector<int> v3(v);
            std::next_permutation(v.begin(), v.end());
            nextPermutation(v2);
            nextPermutation2(v3);
            Logger() << v2;
            Logger() << v3;
            for (size_t i = 0; i < v.size(); i++) {
                ASSERT1(v[i] == v2[i]);
                ASSERT1(v[i] == v3[i]);
            }
        }
    });

    Add("32. Longest Valid Parentheses", [&]() {
        auto check = [&](const string &s) {
            int l = longestValidParentheses(s);
            int l2 = longestValidParentheses2(s);
            int l3 = longestValidParentheses3(s);
            Logger().WriteInformation("%s: %d, %d, %d\n", s.c_str(), l, l2, l3);
            ASSERT1(l == l2);
            ASSERT1(l == l3);
        };
        check("()");
        check("()()");
        check("(())");
        check("(()())");
        check("(()())((()())(()()))");
        for (int i = 0; i < 10; i++) {
            size_t n = Random::Int(50, 2);
            string s = Random::String(n, string("()"));
            check(s);
        }
    });

    Add("33. Search in Rotated Sorted Array", [&]() {
        auto check = [&](const vector<int> v, int t, int e,
                         bool ignoreE = false) {
            int i = search(v, t);
            int i2 = search2(v, t);
            if (ignoreE) {
                Logger() << v << t << ", " << i << ", " << i2 << endl;
                ASSERT1(i == i2);
            } else {
                Logger() << v << t << ", " << i << ", " << i2 << ", " << e
                         << endl;
                ASSERT1(i == e);
                ASSERT1(i2 == e);
            }
        };
        check({4, 5, 6, 7, 0, 1, 2}, 0, 4);
        check({4, 5, 6, 7, 0, 1, 2}, 3, -1);
        check({1, 3}, 1, 0);
        check({1, 3}, 3, 1);
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            int d = (i % 10) == 0 ? 0 : Random::Int(n);
            Util::RotateLeft(v, d);
            check(v, Random::Int(n * 2), -2, true);
        }
    });

    Add("34. Find First and Last Position of Element in Sorted Array", [&]() {
        auto check = [&](const vector<int> &v, int e) {
            Logger() << v;
            Logger() << "Range " << e << ": ";
            vector<int> p = searchRange(v, e);
            vector<int> p2 = searchRange2(v, e);
            vector<int> p3 = searchRange3(v, e);
            Logger() << p << p2 << p3;
            ASSERT1(p[0] == p2[0]);
            ASSERT1(p[1] == p2[1]);
            ASSERT1(p[0] == p3[0]);
            ASSERT1(p[1] == p3[1]);
            if (p[0] > 0) {
                ASSERT1(v[p[0] - 1] < v[p[0]]);
                ASSERT1(v[p[0]] == e);
            }
            if (0 <= p[1] && p[1] < (int)v.size() - 1) {
                ASSERT1(v[p[1]] < v[p[1] + 1]);
                ASSERT1(v[p[1]] == e);
            }
        };
        {
            vector<int> v = {0};
            check(v, 0);
            check(v, 1);
        }
        {
            vector<int> v = {1, 1};
            check(v, 1);
            check(v, 2);
        }
        {
            vector<int> v = {2, 3};
            check(v, 1);
            check(v, 2);
            check(v, 3);
            check(v, 4);
        }
        for (int i = 0; i < 100; i++) {
            vector<int> input = Random::Vector(Random::Int(100, 1), 5, -5);
            sort(input.begin(), input.end());
            check(input, Random::Int(6, -6));
        }
    });

    Add("35. Search Insert Position", [&]() {
        auto check = [&](const vector<int> &v, int t) {
            Logger() << v << t << endl;
            int i = searchInsert(v, t);
            int i2 = searchInsert2(v, t);
            Logger() << i << ", " << i2 << endl;
            ASSERT1(i == i2);
            if (i < (int)v.size())
                ASSERT1(t <= v[i]);
            else
                ASSERT1(i == (int)v.size());
            if (0 < i)
                ASSERT1(v[i - 1] <= t);
            else
                ASSERT1(i == 0);
        };
        check({1, 3, 5, 6}, 5);
        check({1, 3, 5, 6}, 2);
        check({1, 3, 5, 6}, 7);
        check({1, 3, 5, 6}, 0);
        for (int i = 0; i < 100; i++) {
            vector<int> input = Random::Vector(Random::Int(100, 1), 100);
            sort(input.begin(), input.end());
            check(input, Random::Int(200, -100));
        }
    });

    Add("37. Sudoku Solver", [&]() {
        auto check = [&](const vector<vector<char>> &board) {
            Logger().WriteInformation("Sudoku:\n");
            Logger() << board;
            vector<vector<char>> b(board);
            solveSudoku(b);
            vector<vector<char>> b2(board);
            solveSudoku(b2);
            Logger() << b << b2;
            bool r = isValidSudoku(b);
            bool r2 = isValidSudoku2(b);
            bool r3 = isValidSudoku3(b);
            ASSERT1(r == true);
            ASSERT1(r2 == true);
            ASSERT1(r3 == true);
            bool s = isValidSudoku(b2);
            bool s2 = isValidSudoku2(b2);
            bool s3 = isValidSudoku3(b2);
            ASSERT1(s == true);
            ASSERT1(s2 == true);
            ASSERT1(s3 == true);
        };
        {
            vector<vector<char>> b = {
                {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
            check(b);
        }
    });

    Add("38. Count and Say", [&]() {
        auto check = [&](int n, const string &e, bool ignoreE = false) {
            string s = countAndSay(n);
            string s2 = countAndSay2(n);
            if (ignoreE) {
                Logger() << n << ", " << s << ", " << s2 << endl;
                ASSERT1(s == s2);
            } else {
                Logger() << n << ", " << s << ", " << s2 << ", " << e << endl;
                ASSERT1(s == e);
                ASSERT1(s2 == e);
            }
        };
        check(1, "1");
        check(2, "11");
        check(3, "21");
        check(4, "1211");
        check(5, "111221");
        check(6, "312211");
        check(7, "13112221");
        check(8, "1113213211");
        for (int i = 9; i <= 20; i++) {
            check(i, "", true);
        }
    });

    Add("39. Combination Sum", [&]() {
        auto check = [&](const vector<int> &v, int t) {
            Logger() << v << "Target " << t << endl;
            vector<int> v1(v);
            vector<int> v2(v);
            vector<int> v3(v);
            vector<int> v4(v);
            auto c = combinationSum(v1, t);
            auto c2 = combinationSum_2(v2, t);
            auto c3 = combinationSum_3(v3, t);
            auto c4 = combinationSum_4(v4, t);
            Util::SortGrid(c);
            Util::SortGrid(c2);
            Util::SortGrid(c3);
            Util::SortGrid(c4);
            Logger() << c;
            ASSERT1(0 == Util::Compare(c, c2));
            ASSERT1(0 == Util::Compare(c, c3));
            ASSERT1(0 == Util::Compare(c, c4));
        };
        for (int i = 0; i < 20; i++) {
            vector<int> input = Util::IncreasingVector(Random::Int(10, 1), 2);
            Util::Shuffle(input);
            int t = 0;
            int c = 1 + (input.size() >> 2);
            for (int j = 0; j < c; j++) {
                t += input[Random::Int(input.size() - 1)];
            }
            check(input, t);
        }
        {
            vector<int> v = {6, 7, 5};
            check(v, 24);
        }
        {
            vector<int> v = {7, 10};
            check(v, 24);
        }
        {
            vector<int> v = {6, 11, 5, 3, 2, 8, 7, 4, 10, 9};
            check(v, 24);
        }
    });

    Add("40. Combination Sum II", [&]() {
        auto check = [&](const vector<int> &v, int t) {
            Logger() << v << "Target " << t << endl;
            vector<int> v1(v);
            vector<int> v2(v);
            vector<int> v3(v);
            auto c1 = combinationSum2(v1, t);
            auto c2 = combinationSum2_2(v2, t);
            auto c3 = combinationSum2_2(v3, t);
            Util::SortGrid(c1);
            Util::SortGrid(c2);
            Util::SortGrid(c3);
            Logger() << c1 << c2 << c3;
            ASSERT1(0 == Util::Compare(c1, c2));
            ASSERT1(0 == Util::Compare(c1, c3));
        };
        {
            vector<int> v = {10, 1, 2, 7, 6, 1, 5};
            check(v, 8);
        }
        for (int i = 0; i < 20; i++) {
            vector<int> input = Random::Vector(Random::Int(20, 1), 20, 1);
            Util::Shuffle(input);
            int t = 0;
            int c = 1 + (input.size() >> 2);
            for (int j = 0; j < c; j++) {
                t += input[Random::Int(input.size() - 1)];
            }
            check(input, t);
        }
    });

    Add("41. First Missing Positive", [&]() {
        auto check = [&](const vector<int> &v, int e, bool ignoreE = false) {
            Logger() << v;
            vector<int> v1(v);
            int i = firstMissingPositive(v1);
            vector<int> v2(v);
            int i2 = firstMissingPositive2(v2);
            if (ignoreE) {
                Logger() << i << ", " << i2 << endl;
                ASSERT1(i == i2);
            } else {
                Logger() << i << ", " << i2 << ", " << e << endl;
                ASSERT1(i == e);
                ASSERT1(i2 == e);
            }
        };
        check({1, 2, 0}, 3);
        check({3, 4, -1, 1}, 2);
        check({7, 8, 9, 11, 12}, 1);
        check({0, 2, 2, 1, 1}, 3);
        for (int i = 0; i < 100; i++) {
            vector<int> v = Random::Vector(Random::Int(50), 20, -10);
            check(v, 0, true);
        }
    });

    Add("42. Trapping Rain Water", [&]() {
        auto check = [&](const vector<int> &a) {
            Logger() << a;
            int s = trap(a);
            int s2 = trap2(a);
            Logger().WriteInformation("  Trapped water: %d, %d\n", s, s2);
            ASSERT1(s == s2);
        };
        check({1});
        check({1, 2});
        check({2, 1});
        check({1, 2, 3});
        check({3, 2, 1});
        check({2, 1, 3});
        check({3, 1, 2});
        check({2, 0, 2, 1, 3});
        check({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});
        check({5, 2, 1, 2, 1, 5});
        for (int i = 0; i < 100; i++) {
            vector<int> v = Random::Vector(Random::Int(50), 100);
            check(v);
        }
    });

    Add("43. Multiply Strings", [&]() {
        auto toString = [&](unsigned long long u) -> string {
            ostringstream o;
            o << u;
            return o.str();
        };
        auto check = [&](unsigned long long u1, unsigned long long u2) {
            string s1 = toString(u1);
            string s2 = toString(u2);
            string o = multiply(s1, s2);
            string o2 = multiply2(s1, s2);
            unsigned long long u = u1 * u2;
            string o3 = toString(u);
            Logger().WriteInformation("%s X %s = %s, %s, %s\n", s1.c_str(),
                                      s2.c_str(), o.c_str(), o2.c_str(),
                                      o3.c_str());
            ASSERT1(o == o3);
            ASSERT1(o2 == o3);
        };
        check(0, 0);
        check(1, 1);
        check(2, 2);
        check(5, 5);
        check(10, 5);
        check(11, 11);
        check(222, 11);
        check(1111, 22222);
        for (int i = 0; i < 100; i++)
            check(Random::Int(), Random::Int());
    });

    Add("44. Wildcard Matching", [&]() {
        auto check = [&](const string &s, const string &p) {
            // bool e = isMatch(s, p);
            bool e2 = isMatch2(s, p);
            bool e3 = isMatch3(s, p);
            bool e4 = isMatch(s.c_str(), p.c_str());
            Logger() << s << ", " << p << ", " << e2 << ", " << e3 << ", " << e4
                     << endl;
            ASSERT1(e2 == e3);
            ASSERT1(e2 == e4);
        };
        check("aa", "a");
        check("aa", "aa");
        check("aaa", "aa");
        check("aa", "*");
        check("aa", "a*");
        check("ab", "?*");
        check("aab", "c*a*b");
        check("abbbaaaaaaaabbbabaaabbabbbaabaabbbbaabaabbabaabbabbaabbbaabaabba"
              "baabaabbbbaabbbaabaaababbbbabaaababbaaa",
              "ab**b*bb*ab**ab***b*abaa**b*a*aaa**bba*aa*a*abb*a*a");
        check("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababa"
              "abbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbb"
              "aaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaab"
              "aaababaaaabb",
              "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**"
              "aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb");
    });

    Add("45. Jump Game II", [&]() {
        auto check = [&](const vector<int> &a) {
            Logger() << a;
            int c = jump(a);
            int c2 = jump2(a);
            int c3 = jump3(a);
            int c4 = jump4(a);
            Logger() << c << ", " << c2 << ", " << c3 << ", " << c4 << endl;
            ASSERT1(c == c2);
            ASSERT1(c == c3);
            ASSERT1(c == c4);
        };
        check({0});
        check({2, 3, 1, 1, 4});
        check({1, 1, 1, 1, 1});
    });

    Add("46. Permutations", [&]() {
        auto check = [&](vector<int> &v) {
            Logger() << v;
            vector<vector<int>> p = {v};
            while (std::next_permutation(v.begin(), v.end()))
                p.push_back(vector<int>(v));
            Logger() << p;
            Util::Sort(p);
            vector<int> v1(v);
            vector<vector<int>> p1 = permute(v1);
            Logger() << p1;
            Util::Sort(p1);
            vector<int> v2(v);
            vector<vector<int>> p2 = permute2(v2);
            Logger() << p2;
            Util::Sort(p2);
            vector<int> v3(v);
            vector<vector<int>> p3 = permute3(v3);
            Logger() << p3;
            Util::Sort(p3);
            vector<int> v4(v);
            vector<vector<int>> p4 = permuteUnique(v4);
            Logger() << p4;
            Util::Sort(p4);
            vector<int> v5(v);
            vector<vector<int>> p5 = permuteUnique2(v5);
            Logger() << p5;
            Util::Sort(p5);
            ASSERT1(0 == Util::Compare(p1, p));
            ASSERT1(0 == Util::Compare(p2, p));
            ASSERT1(0 == Util::Compare(p3, p));
            ASSERT1(0 == Util::Compare(p4, p));
            ASSERT1(0 == Util::Compare(p5, p));
        };
        {
            vector<int> v = {3};
            check(v);
        }
        {
            vector<int> v = {0, 1, 2, 3, 4};
            check(v);
        }
        {
            vector<int> v = {1, 2, 3, 4};
            check(v);
        }
    });
    Add("47. Permutations II", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            vector<int> v1(v);
            sort(v1.begin(), v1.end());
            set<vector<int>, Util::VectorLess<int>> s = {v1};
            vector<vector<int>> p = {v1};
            while (std::next_permutation(v1.begin(), v1.end())) {
                if (s.find(v1) == s.end()) {
                    p.push_back(vector<int>(v1));
                    s.insert(v1);
                }
            }
            Logger() << p;
            Util::Sort(p);
            vector<int> v2(v);
            vector<vector<int>> p2 = permuteUnique(v2);
            Logger() << p2;
            Util::Sort(p2);
            vector<int> v3(v);
            vector<vector<int>> p3 = permuteUnique2(v3);
            Logger() << p3;
            Util::Sort(p3);
            ASSERT1(0 == Util::Compare(p2, p));
            ASSERT1(0 == Util::Compare(p3, p));
        };
        check({2, 2});
        check({3, 3, 3});
        check({1, 1, 2});
        check({1, 2, 1});
        check({2, 1, 1});
        check({1, 2, 2});
        check({2, 1, 2});
        check({2, 2, 1});
    });

    Add("48. Rotate Image", [&]() {
        auto check = [&](const vector<vector<int>> w) {
            Logger() << w;
            vector<vector<int>> v(w);
            rotate(v);
            Logger() << v;
            vector<vector<int>> v2(w);
            rotate2(v2);
            Logger() << v2;
            ASSERT1(Util::Compare(v, v2) == 0);
        };
        for (int i = 1; i <= 10; i++)
            check(Random::Grid(i, i));
    });

    Add("49. Group Anagrams", [&]() {
        auto check = [&](const vector<string> &strs) {
            Logger() << strs;
            vector<vector<string>> g = groupAnagrams(strs);
            Logger() << g;
            Util::SortGrid(g);
            Logger() << g;
            vector<vector<string>> g2 = groupAnagrams2(strs);
            Logger() << g2;
            Util::SortGrid(g2);
            Logger() << g2;
            ASSERT1(0 == Util::Compare(g, g2));
        };
        check({"eat", "tea", "tan", "ate", "nat", "bat"});
    });

    Add("50. Pow(x, n)", [&]() {
        auto check = [&](double x, int n) {
            double p = myPow(x, n);
            double p2 = myPow2(x, n);
            double p3 = myPow3(x, n);
            double p4 = myPow4(x, n);
            double p5 = myPow5(x, n);
            double e = pow(x, n);
            Logger().WriteInformation("%f^%s%d%s = %f, %f, %f, %f, %f, %f\n", x,
                                      n < 0 ? "(" : "", n, n < 0 ? ")" : "", p,
                                      p2, p3, p4, p5, e);
            ASSERT1(p == e);
            ASSERT1(p2 == e);
            ASSERT1(p3 == e);
            ASSERT1(p4 == e);
            ASSERT1(p5 == e);
        };
        for (int i = -10; i <= 10; i++) {
            check(2, i);
        }
        check(-1, INT_MIN);
        check(-1, INT_MAX);
        check(-0.5, INT_MIN);
        check(-0.5, INT_MAX);
        check(0.5, INT_MIN);
        check(0.5, INT_MAX);
        check(1, INT_MIN);
        check(1, INT_MAX);
    });

    Add("51. N-Queens", [&]() {
        auto print = [&](const vector<vector<string>> &solutions) {
            for (size_t i = 0; i < solutions.size(); i++) {
                Logger().WriteInformation("  Solution %d:\n", i);
                for (size_t j = 0; j < solutions[i].size(); j++) {
                    Logger().WriteInformation("\t");
                    for (size_t k = 0; k < solutions[i][j].length(); k++) {
                        Logger().WriteInformation(" %c", solutions[i][j][k]);
                    }
                    Logger().WriteInformation("\n");
                }
            }
        };
        auto check = [&](int n) {
            Logger().WriteInformation("Solutions of %d-Queens problem:\n", n);
            vector<vector<string>> solutions = solveNQueens(n);
            vector<vector<string>> solutions2 = solveNQueens2(n);
            int count = totalNQueens(n);
            int count2 = totalNQueens2(n);
            Util::Sort(solutions);
            Util::Sort(solutions2);
            print(solutions);
            print(solutions2);
            ASSERT1(Util::Compare(solutions, solutions2) == 0);
            ASSERT1(count == count2);
            ASSERT1((int)solutions.size() == count);
            ASSERT1((int)solutions2.size() == count);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
    });

    Add("53. Maximum Subarray", [&]() {
        auto check = [&](const vector<int> &a, int el, int er, int es,
                         bool ignoreE = false) -> void {
            Logger() << a;
            int sum = LeetCode::maxSubArray(a);
            int sum2 = LeetCode::maxSubArray2(a);
            Logger() << sum << ", " << sum2 << endl;
            int l3, r3;
            int sum3 = LeetCode::maxSubArray2(a, l3, r3);
            Logger().WriteInformation("a[%d..%d] = %d\n", l3, r3, sum3);
            int l4, r4;
            int sum4 = LeetCode::maxSubArray3(a, l4, r4);
            Logger().WriteInformation("a[%d..%d] = %d\n", l4, r4, sum4);
            if (ignoreE) {
                ASSERT1(sum == sum2);
                ASSERT1(sum == sum3);
                ASSERT1(sum == sum4);
            } else {
                ASSERT1(es == sum);
                ASSERT1(es == sum2);
                ASSERT1(el == l3);
                ASSERT1(er == r3);
                ASSERT1(es == sum3);
                ASSERT1(el == l4);
                ASSERT1(er == r4);
                ASSERT1(es == sum4);
            }
        };
        {
            vector<int> A = {13, -3, -25, 20, -3,  -16, -23, 18,
                             20, -7, 12,  -5, -22, 15,  -4,  7};
            check(A, 7, 10, 43);
        }
        {
            vector<int> A = {13};
            check(A, 0, 0, 13);
        }
        {
            vector<int> A = {13, -3};
            check(A, 0, 0, 13);
        }
        {
            vector<int> A = {13, -3, -25};
            check(A, 0, 0, 13);
        }
        {
            vector<int> A = {13, -3, -25, 20};
            check(A, 3, 3, 20);
        }
        {
            vector<int> A = {13, -3, -25, 20, -3};
            check(A, 3, 3, 20);
        }
        {
            vector<int> A = {13, -3, -25, 20, -3, -16, -23, 18};
            check(A, 3, 3, 20);
        }
        {
            vector<int> A = {13, 3, 25, 20, 3,  16, 23, 18,
                             20, 7, 12, 5,  22, 15, 4,  7};
            check(A, 0, (int)A.size() - 1, 213);
        }
        {
            vector<int> A = {13, 3};
            check(A, 0, 1, 16);
        }
        {
            vector<int> A = {13, 3, 25};
            check(A, 0, 2, 41);
        }
        {
            vector<int> A = {-13, -3, -25, -20, -3,  -16, -23, -18,
                             -20, -7, -12, -5,  -22, -15, -4,  -7};
            check(A, 1, 1, -3);
        }
        {
            vector<int> A = {-13};
            check(A, 0, 0, -13);
        }
        {
            vector<int> A = {-13, -3};
            check(A, 1, 1, -3);
        }
        {
            vector<int> A = {0,   0,  -25, -20, -3,  -16, -23, -18,
                             -20, -7, -12, -5,  -22, -15, -4,  -7};
            check(A, 0, 0, 0);
        }
        {
            vector<int> A = {0};
            check(A, 0, 0, 0);
        }
        {
            vector<int> A = {0,  0, 25, 20, 3,  16, 23, 18,
                             20, 7, 12, 5,  22, 15, 0,  0};
            check(A, 2, 13, 186);
        }
        {
            vector<int> A = {-25, -20, -3,  0,  0,   -16, -23, -18,
                             -20, -7,  -12, -5, -22, -15, -4,  -7};
            check(A, 3, 3, 0);
        }
        {
            vector<int> A = {-25, -20, -3, 0, 0};
            check(A, 3, 3, 0);
        }
        {
            vector<int> A = {1,   1,  1,   -1, -1,  -1,  -1, -18,
                             -20, -7, -12, -5, -22, -15, -4, -7};
            check(A, 0, 2, 3);
        }
        {
            vector<int> A = {1, 1, 1, -1, -1, -1};
            check(A, 0, 2, 3);
        }
        {
            vector<int> A = {1,   1,  1,   -1, -1,  -1,  -1, -18,
                             -20, -7, -12, -5, -22, -15, -4, 7};
            check(A, (int)A.size() - 1, (int)A.size() - 1, 7);
        }
        {
            vector<int> A = {
                -226810937, 607950954,   640895092,  884005970,  -649503488,
                -353856437, 576018669,   -477225174, 115899598,  -48539461,
                276748204,  -290373133,  28778236,   971155940,  893772103,
                291438717,  466641603,   -769652651, 229713913,  -1038736612,
                -552146455, -779039256,  653214606,  -737276041, -212720293,
                -795018961, -840076700,  1071432244, -605038688, 27772106,
                728237979,  241892199,   -438018765, 295391246,  52156344,
                -13780430,  1015276633,  -445566812, 582736219,  57434406,
                579635550,  -214257402,  840803096,  -465328039, -316843286,
                660833375,  899852501,   -923943508, 964922547,  55824590,
                -888938297, -660965732,  350527157,  838018133,  -324499950,
                -935934961, -1030742653, -90834827,  -938244542, -562039518,
                1010679102, 863735261,   753594504,  -501081487, 85384682,
                -267990977, 558879906,   26919490,   360184034,  67874301,
                -989387928, -133922241,  927358722,  925156991,  474491544,
                -463226389, 512248541,   300602220,  -313428073, 403429264,
                -717315015, -128624547,  816205355,  706953965};
            long long s = 0;
            for (size_t i = 27; i <= 83; i++) {
                s += A[i];
            }
            Logger() << "Actual sum[27..83] = " << s << ", " << (int)s << endl;
            check(A, 27, 83, 1391522844);
        }
        {
            int d = RAND_MAX >> 1;
            for (int i = 0; i < 1000; i++) {
                vector<int> input;
                int length = 1 + (rand() % 100);
                for (int j = 0; j < length; j++) {
                    input.push_back(rand() - d);
                }
                check(input, -1, -1, -1, true);
            }
        }
        {
            for (int i = 0; i < 1000; i++) {
                vector<int> input;
                int length = 1 + (rand() % 100);
                for (int j = 0; j < length; j++) {
                    input.push_back(rand() % 20 - 10);
                }
                Logger() << input;
                check(input, -1, -1, -1, true);
            }
        }
    });

    Add("54. Spiral Matrix", [&]() {
        auto check = [&](const vector<vector<int>> &m) {
            Logger() << m;
            vector<int> o = LeetCode::spiralOrder(m);
            vector<int> o2 = LeetCode::spiralOrder2(m);
            vector<int> o3 = LeetCode::spiralOrder3(m);
            Logger() << o << o2 << o3;
            ASSERT1(Util::Compare(o, o2) == 0);
            ASSERT1(Util::Compare(o, o3) == 0);
        };
        check({{0}});
        check({{0, 1}});
        check({{0, 1, 2}});
        check({{0}, {1}});
        check({{0}, {1}, {2}});
        check({{0, 1}, {3, 2}});
        check({{0, 1, 2}, {5, 4, 3}});
        check({{0, 1}, {5, 2}, {4, 3}});
        check({{0, 1, 2}, {7, 8, 3}, {6, 5, 4}});
        check({{0, 1, 2, 3}, {9, 10, 11, 4}, {8, 7, 6, 5}});
        check({{0, 1, 2}, {9, 10, 3}, {8, 11, 4}, {7, 6, 5}});
        check({{0, 1, 2, 3}, {11, 12, 13, 4}, {10, 15, 14, 5}, {9, 8, 7, 6}});
        for (int i = 0; i < 100; i++) {
            vector<vector<int>> m =
                Random::Grid(Random::Int(50, 1), Random::Int(50, 1));
            Logger() << m;
            check(m);
        }
        auto check2 = [&](int n) {
            Logger() << "Generating spiral matrix of order " << n << ":"
                     << endl;
            vector<vector<int>> m = generateMatrix(n);
            vector<vector<int>> m2 = generateMatrix2(n);
            Logger() << m << m2;
            ASSERT1(0 == Util::Compare(m, m2));
            vector<int> v = Util::IncreasingVector(n * n, 1);
            vector<int> o = spiralOrder(m);
            vector<int> o2 = spiralOrder2(m);
            vector<int> o3 = spiralOrder3(m);
            ASSERT1(Util::Compare(v, o) == 0);
            ASSERT1(Util::Compare(v, o2) == 0);
            ASSERT1(Util::Compare(v, o3) == 0);
        };
        for (int i = 1; i <= 10; i++)
            check2(i);
    });

    Add("55. Jump Game", [&]() {
        auto check = [&](const vector<int> a) {
            Logger() << a;
            bool c = LeetCode::canJump(a);
            bool c2 = LeetCode::canJump2(a);
            Logger().WriteInformation("Can %sjump\n", c ? "" : "not ");
            Logger().WriteInformation("Can %sjump\n", c2 ? "" : "not ");
            ASSERT1(c == c2);
        };
        check({0});
        check({1});
        check({2});
        check({0, 1});
        check({2, 3, 1, 1, 4});
        check({3, 2, 1, 0, 4});
        for (int i = 0; i < 100; i++) {
            vector<int> a = Random::Vector(Random::Int(100, 1), 10);
            check(a);
        }
    });

    Add("56. Merge Intervals", [&]() {
        auto print = [&](vector<Interval> it) {
            for_each(it.begin(), it.end(), [&](const Interval &i) {
                Logger().WriteInformation(" [%d,%d]", i.start, i.end);
            });
            Logger().WriteInformation("\n");
        };
        auto check = [&](vector<Interval> it) {
            Logger().WriteInformation("Input: ");
            print(it);
            vector<vector<int>> v;
            for_each(it.begin(), it.end(), [&](const Interval &i) {
                v.push_back(vector<int>{i.start, i.end});
            });
            vector<vector<int>> o = merge(v);
            vector<Interval> o2 = merge(it);
            vector<Interval> o3 = merge2(it);
            Logger().WriteInformation("Output:");
            Logger() << o;
            print(o2);
            print(o3);
            ASSERT1(o.size() == o2.size());
            ASSERT1(o.size() == o3.size());
            for (size_t i = 0; i < o.size(); i++) {
                ASSERT1(o2[i].start == o[i][0]);
                ASSERT1(o2[i].end == o[i][1]);
                ASSERT1(o3[i].start == o[i][0]);
                ASSERT1(o3[i].end == o[i][1]);
            }
        };
        {
            vector<Interval> it = {
                Interval(74, 78), Interval(61, 63), Interval(46, 50),
                Interval(51, 54), Interval(50, 50), Interval(60, 64),
                Interval(39, 42), Interval(25, 27), Interval(91, 95)};
            check(it);
        }
    });

    Add("57. Insert Interval", [&]() {
        auto print = [&](const vector<Interval> &it) {
            for_each(it.begin(), it.end(), [&](const Interval &i) {
                Logger().WriteInformation(" [%d,%d]", i.start, i.end);
            });
            Logger().WriteInformation("\n");
        };
        auto check = [&](const vector<vector<int>> &it, const vector<int> &n) {
            Logger().WriteInformation("Input: ");
            Logger() << it << n;
            vector<Interval> v;
            for_each(it.begin(), it.end(), [&](const vector<int> &i) {
                v.push_back(Interval(i[0], i[1]));
            });
            vector<vector<int>> o = insert(it, n);
            vector<Interval> o2 =
                InsertMergeSortedInterval(v, Interval(n[0], n[1]));
            Logger().WriteInformation("Output:");
            Logger() << o;
            print(o2);
            ASSERT1(o.size() == o2.size());
            for (size_t i = 0; i < o.size(); i++) {
                ASSERT1(o2[i].start == o[i][0]);
                ASSERT1(o2[i].end == o[i][1]);
            }
        };
        check({}, {2, 3});
        check({{1, 2}}, {4, 5});
        check({{3, 5}}, {1, 2});
        check({{4, 6}}, {4, 5});
        check({{2, 6}}, {4, 6});
        check({{1, 6}}, {4, 5});
        check({{1, 3}, {6, 9}}, {2, 5});
        check({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8});
    });

    Add("58. Length of Last Word", [&]() {
        auto check = [&](const string &s, int el = -1) {
            Logger() << "\"" << s << "\"" << endl;
            int l = lengthOfLastWord(s);
            int l2 = lengthOfLastWord2(s);
            int l3 = lengthOfLastWord3(s.c_str());
            int l4 = lengthOfLastWord4(s);
            Logger() << "LengthOfLastWord: " << l << ", " << l2 << ", " << l3
                     << ", " << l4 << endl;
            if (el == -1) {
                ASSERT1(l == l2);
                ASSERT1(l == l3);
                ASSERT1(l == l4);
            } else {
                ASSERT1(l == el);
                ASSERT1(l2 == el);
                ASSERT1(l3 == el);
                ASSERT1(l4 == el);
            }
        };
        check("", 0);
        check("a", 1);
        check(" ", 0);
        check("  ", 0);
        check("ababa", 5);
        check("a a", 1);
        check("a  a", 1);
        check("a    a", 1);
        check("a a sv", 2);
        check("aa asfd", 4);
        check("   aa", 2);
        check("  a", 1);
        check(" aas", 3);
        for (int i = 0; i < 100; i++) {
            string s = Random::String(Random::Int(100, 0));
            check(s);
        }
    });

    Add("60. Permutation Sequence", [&]() {
        auto check = [&](int n) {
            string s;
            for (int i = 1; i <= n; i++)
                s.append(1, '0' + i);
            int k = 0;
            do {
                k++;
                string p = getPermutation(n, k);
                string p2 = getPermutation2(n, k);
                Logger() << "permute(" << n << ", " << k << ") = " << s << ", "
                         << p << ", " << p2 << endl;
                ASSERT1(p.compare(s) == 0);
                ASSERT1(p2.compare(s) == 0);
            } while (std::next_permutation(s.begin(), s.end()));
        };
        for (int i = 1; i < 10; i++)
            check(i);
    });

    Add("61. Rotate List", [&]() {
        auto check = [&](const vector<int> &v, int k) {
            Logger().WriteInformation("Right rotate list by %d\n", k);
            ListNode *l = ToList(v);
            Print(l);
            l = rotateRight(l, k);
            Print(l);
            vector<int> w = ToVector(l);
            DeleteList(l);
            ListNode *l2 = ToList(v);
            Print(l2);
            l2 = rotateRight2(l2, k);
            Print(l2);
            vector<int> w2 = ToVector(l2);
            DeleteList(l2);
            ListNode *l3 = ToList(v);
            Print(l3);
            l3 = rotateRight(l3, k);
            Print(l3);
            vector<int> w3 = ToVector(l3);
            DeleteList(l3);
            ASSERT1(0 == Util::Compare(w, w2));
            ASSERT1(0 == Util::Compare(w, w3));
        };
        {
            vector<int> v = {0};
            check(v, 0);
            check(v, 1);
            check(v, 2);
        }
        {
            vector<int> v = {0, 1};
            check(v, 0);
            check(v, 1);
            check(v, 2);
            check(v, 3);
            check(v, 4);
            check(v, 5);
        }
        {
            vector<int> v = {0, 1, 2};
            check(v, 0);
            check(v, 1);
            check(v, 2);
            check(v, 3);
            check(v, 4);
            check(v, 5);
            check(v, 6);
            check(v, 7);
            check(v, 8);
        }
        for (int i = 0; i < 100; i++) {
            vector<int> v = Random::Vector(Random::Int(20, 1), 20);
            int k = Random::Int(40);
            check(v, k);
        }
    });

    Add("62. Unique Paths", [&]() {
        for (int m = 1; m <= 10; m++) {
            for (int n = 1; n <= 10; n++) {
                Logger() << "UniquePaths(" << m << ", " << n << ") = ";
                int v = uniquePaths(m, n);
                int v2 = uniquePaths2(m, n);
                Logger() << v << ", " << v2 << endl;
                ASSERT1(v == v2);
            }
        }
    });

    Add("63. Unique Paths II", [&]() {
        auto check = [&](const vector<vector<int>> &grid, int expected) {
            int count = uniquePathsWithObstacles(grid);
            int count2 = uniquePathsWithObstacles2(grid);
            Logger() << grid << "Unique paths: " << count << ", " << count2
                     << endl;
            if (expected < 0) {
                ASSERT1(count == count2);
            } else {
                ASSERT1(count == expected);
                ASSERT1(count2 == expected);
            }
        };
        vector<vector<int>> grid = {{0, 0}, {0, 0}};
        check(grid, 2);
        for (int i = 0; i < 10; i++) {
            int m = Random::Int(20, 1);
            int n = Random::Int(20, 1);
            vector<vector<int>> v(m, vector<int>(n, 0));
            for (int j = 0; j < m; j++) {
                int p = Random::Int(m - 1);
                int q = Random::Int(n - 1);
                v[p][q] = 1;
            }
            check(v, -1);
        }
    });

    Add("64. Minimum Path Sum", [&]() {
        auto check = [&](const vector<vector<int>> &grid) {
            Logger() << grid;
            int s = minPathSum(grid);
            int s2 = minPathSum2(grid);
            Logger() << "MinPathSum = " << s << ", " << s2 << endl;
            ASSERT1(s == s2);
        };
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                check(Random::Grid(i, j, Random::Int(100)));
            }
        }
    });

    Add("65. Valid Number", [&]() {
        auto check = [&](const string &s, bool e) {
            Logger() << s;
            bool a = isNumber(s);
            bool a2 = isNumber(s.c_str());
            Logger() << " is a number: " << a << ", " << a2 << endl;
            ASSERT1(a == e);
            ASSERT1(a2 == e);
        };
        check("  00  ", true);
        Logger() << "\t00 = " << 00 << endl;
        check("  +00  ", true);
        Logger() << "\t+00 = " << +00 << endl;
        check("  01  ", true);
        Logger() << "\t01 = " << 01 << endl;
        check("  -01  ", true);
        Logger() << "\t-01 = " << -01 << endl;
        check("  00.0  ", true);
        Logger() << "\t00.0 = " << 00.0 << endl;
        check("  +00.0  ", true);
        Logger() << "\t+00.0 = " << +00.0 << endl;
        check("  00.  ", true);
        Logger() << "\t00. = " << 00. << endl;
        check("  -00.  ", true);
        Logger() << "\t-00. = " << -00. << endl;
        check("  1.  ", true);
        Logger() << "\t1. = " << 1. << endl;
        check("  +1.  ", true);
        Logger() << "\t+1. = " << +1. << endl;
        check("  .1  ", true);
        Logger() << "\t.1 = " << .1 << endl;
        check("  -.1  ", true);
        Logger() << "\t-.1 = " << -.1 << endl;
        check("  .1e010  ", true);
        Logger() << "\t.1e010 = " << .1e010 << endl;
        check("  +.1e010  ", true);
        Logger() << "\t+.1e010 = " << +.1e010 << endl;
        check("  .1e-010  ", true);
        Logger() << "\t.1e-010 = " << .1e-010 << endl;
        check("  -.1e-010  ", true);
        Logger() << "\t-.1e-010 = " << -.1e-010 << endl;
        check("  .1e+02  ", true);
        Logger() << "\t.1e+02 = " << .1e+02 << endl;
        check("  +.1e+02  ", true);
        Logger() << "\t+.1e+02 = " << +.1e+02 << endl;
        check("  .1e-02  ", true);
        Logger() << "\t.1e-02 = " << .1e-02 << endl;
        check("  -.1e-02  ", true);
        Logger() << "\t-.1e-02 = " << -.1e-02 << endl;
        check("2e0", true);
        Logger() << "\t2e0 = " << 2e0 << endl;
        check("2.e01", true);
        Logger() << "\t2.e01 = " << 2.e01 << endl;
        check(".", false);
        check("-.", false);
        check("0e", false);
        check("e+02", false);
        check(".e+02", false);
        check("+e+02", false);
        check(".1e.1", false);
        check(".1e0.1", false);
        check("0", true);
        check(" 0.1 ", true);
        check("abc", false);
        check("1 a", false);
        check("2e10", true);
        check(" -90e3  ", true);
        check(" 1e", false);
        check("e3", false);
        check(" 6e-1", true);
        check(" 99e2.5", false);
        check("53.5e93", true);
        check(" --6 ", false);
        check("-+3", false);
        check("95a54e53", false);
    });

    Add("66. Plus One", [&]() {
        auto number = [&](const vector<int> &digits) -> int {
            int s = 0;
            for_each(digits.begin(), digits.end(),
                     [&](int n) { s = 10 * s + n; });
            return s;
        };
        auto check = [&](const vector<int> &digits) {
            int a = number(digits);
            Logger().WriteInformation("%d + 1 = ", a);
            vector<int> output = plusOne(digits);
            int b = number(output);
            vector<int> output2 = plusOne(digits);
            int b2 = number(output2);
            Logger().WriteInformation("%d, %d\n", b, b2);
            ASSERT1(a + 1 == b);
            ASSERT1(a + 1 == b2);
        };
        check(vector<int>{0});
        check(vector<int>{9});
        check(vector<int>{1, 0});
        check(vector<int>{1, 9});
        check(vector<int>{9, 9});
        check(vector<int>{1, 0, 0});
        check(vector<int>{1, 0, 9});
        check(vector<int>{1, 9, 0});
        check(vector<int>{1, 9, 9});
        check(vector<int>{9, 9, 9});
    });

    Add("67. Add Binary", [&]() {
        auto check = [&](const string &a, const string &b, const string &e) {
            int width = 1 + max(a.length(), b.length());
            Logger().WriteInformation("\n   %s%s\n",
                                      string(width - a.length(), ' ').c_str(),
                                      a.c_str());
            Logger().WriteInformation(" + %s%s\n",
                                      string(width - b.length(), ' ').c_str(),
                                      b.c_str());
            string c = addBinary(a, b);
            Logger().WriteInformation(" = %s%s\n",
                                      string(width - c.length(), ' ').c_str(),
                                      c.c_str());
            string c2 = addBinary2(a, b);
            Logger().WriteInformation(" = %s%s\n",
                                      string(width - c2.length(), ' ').c_str(),
                                      c2.c_str());
            string c3 = addBinary3(a, b);
            Logger().WriteInformation(" = %s%s\n",
                                      string(width - c3.length(), ' ').c_str(),
                                      c3.c_str());
            ASSERT1(c == e);
            ASSERT1(c2 == e);
            ASSERT1(c3 == e);
        };
        check("0", "0", "0");
        check("0", "1", "1");
        check("1", "0", "1");
        check("1", "1", "10");
        check("00", "00", "00");
        check("01", "01", "10");
        check("01", "10", "11");
        check("00", "11", "11");
        check("11", "01", "100");
        check("11", "10", "101");
        check("11", "11", "110");
        check("11", "1", "100");
        check("1110", "10", "10000");
        check("101", "11101", "100010");
    });

    Add("68. Text Justification", [&]() {
        auto check = [&](const vector<string> words, int l) {
            vector<string> text = fullJustify(words, l);
            vector<string> text2 = fullJustify2(words, l);
            Logger().WriteInformation("Format with width %d:\n", l);
            for_each(text.begin(), text.end(), [&](const string &w) {
                Logger().WriteInformation("  \"%s\"\n", w.c_str());
            });
            Logger().WriteInformation("\n");
            for_each(text2.begin(), text2.end(), [&](const string &w) {
                Logger().WriteInformation("  \"%s\"\n", w.c_str());
            });
            Logger().WriteInformation("\n");
            ASSERT1(0 == Util::Compare(text, text2));
        };
        {
            vector<string> w = {"This"};
            Logger() << w;
            check(w, 4);
            check(w, 5);
            check(w, 6);
        }
        {
            vector<string> w = {"This", "is"};
            Logger() << w;
            for (int i = 4; i < 10; i++) {
                check(w, i);
            }
        }
        {
            vector<string> w = {"This", "is", "an"};
            Logger() << w;
            for (int i = 4; i < 12; i++) {
                check(w, i);
            }
        }
        {
            vector<string> w = {
                "This", "is", "an", "example", "of", "text", "justification."};
            Logger() << w;
            for (int i = 14; i < 60; i++) {
                check(w, i);
            }
        }
    });

    Add("69. Sqrt(x)", [&]() {
        auto check = [&](int x) {
            Logger().WriteInformation("sqrt(%d) = ", x);
            int a = mySqrt(x);
            int a2 = mySqrt2(x);
            int a3 = mySqrt3(x);
            int b = (int)sqrt(x);
            Logger().WriteInformation("%d, %d, %d, %d\n", a, a2, a3, b);
            ASSERT1(a == b);
            ASSERT1(a2 == b);
            ASSERT1(a3 == b);
        };
        check(0);
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        check(INT_MAX - 9);
        check(INT_MAX - 8);
        check(INT_MAX - 7);
        check(INT_MAX - 6);
        check(INT_MAX - 5);
        check(INT_MAX - 4);
        check(INT_MAX - 3);
        check(INT_MAX - 2);
        check(INT_MAX - 1);
        check(INT_MAX);
        for (int i = 0; i < 100; i++) {
            int v = Random::Int();
            check(v);
        }
    });

    Add("71. Simplify Path", [&]() {
        auto check = [&](const string &p, const string &e,
                         bool ignoreE = false) {
            Logger().WriteInformation("Input:  %s\n", p.c_str());
            string a = simplifyPath(string(p));
            string a2 = simplifyPath2(string(p));
            string a3 = simplifyPath3(string(p));
            if (ignoreE) {
                Logger().WriteInformation("Output:\n\t%s\n\t%s\n\t%s\n",
                                          a.c_str(), a2.c_str(), a3.c_str());
                ASSERT1(a == a2);
                ASSERT1(a == a3);
            } else {
                Logger().WriteInformation("Output: %s, %s, %s, %s\n", a.c_str(),
                                          a2.c_str(), a3.c_str(), e.c_str());
                ASSERT1(a == e);
                ASSERT1(a2 == e);
                ASSERT1(a3 == e);
            }
        };
        check("", "");
        check("/", "/");
        check(".", "/");
        check("a", "/a");
        check("//", "/");
        check("..", "/");
        check("ab", "/ab");
        check("/.", "/");
        check("./", "/");
        check("/a", "/a");
        check("a/", "/a");
        check(".a", "/.a");
        check("a.", "/a.");
        check("///", "/");
        check("...", "/...");
        check("abc", "/abc");
        check("/..", "/");
        check("../", "/");
        check("./.", "/");
        check(".//", "/");
        check("/./", "/");
        check("//.", "/");
        check("/ab", "/ab");
        check("a/b", "/a/b");
        check("ab/", "/ab");
        check("a//", "/a");
        check("/a/", "/a");
        check("//a", "/a");
        check("/a.", "/a.");
        check("/.a", "/.a");
        check("./a", "/a");
        check(".a/", "/.a");
        check("a/.", "/a");
        check("a./", "/a.");
        check(".ab", "/.ab");
        check("a.b", "/a.b");
        check("ab.", "/ab.");
        check("a..", "/a..");
        check(".a.", "/.a.");
        check("..a", "/..a");
        check("////", "/");
        check("....", "/....");
        check("abcd", "/abcd");
        check(".///", "/");
        check("/.//", "/");
        check("//./", "/");
        check("///.", "/");
        check("..//", "/");
        check("././", "/");
        check(".//.", "/");
        check("/../", "/");
        check("/./.", "/");
        check("//..", "/");
        check("/...", "/...");
        check("./..", "/");
        check("../.", "/");
        check(".../", "/...");
        check("./a/", "/a");
        check(".//a", "/a");
        check(".a//", "/.a");
        check("/.a/", "/.a");
        check("/./a", "/a");
        check("/a./", "/a.");
        check("/a/.", "/a");
        check("//.a", "/.a");
        check("//a.", "/a.");
        check("a.//", "/a.");
        check("a/./", "/a");
        check("a//.", "/a");
        check("../a", "/a");
        check("..a/", "/..a");
        check("./.a", "/.a");
        check("./a.", "/a.");
        check(".a/.", "/.a");
        check(".a./", "/.a.");
        check("/a..", "/a..");
        check("/.a.", "/.a.");
        check("/..a", "/..a");
        check("a/..", "/");
        check("a./.", "/a.");
        check("a../", "/a..");
        check("//ab", "/ab");
        check("/a/b", "/a/b");
        check("/ab/", "/ab");
        check("./ab", "/ab");
        check(".a/b", "/.a/b");
        check(".ab/", "/.ab");
        check("/.ab", "/.ab");
        check("/a.b", "/a.b");
        check("/ab.", "/ab.");
        check("a./b", "/a./b");
        check("a.b/", "/a.b");
        check("a/.b", "/a/.b");
        check("a/b.", "/a/b.");
        check("ab./", "/ab.");
        check("ab/.", "/ab");
        check("..ab", "/..ab");
        check(".a.b", "/.a.b");
        check(".ab.", "/.ab.");
        check("a..b", "/a..b");
        check("a.b.", "/a.b.");
        check("ab..", "/ab..");
        check(".abc", "/.abc");
        check("a.bc", "/a.bc");
        check("ab.c", "/ab.c");
        check("abc.", "/abc.");
        check("/abc", "/abc");
        check("a/bc", "/a/bc");
        check("ab/c", "/ab/c");
        check("abc/", "/abc");
        check("/....", "/....");
        check("./...", "/...");
        check("../..", "/");
        check(".../.", "/...");
        check("..../", "/....");
        check("//...", "/...");
        check("/./..", "/");
        check("/../.", "/");
        check("/.../", "/...");
        check("/a/b/c", "/a/b/c");
        check("//ab/c", "/ab/c");
        check("///abc", "/abc");
        check("/a/./..", "/");
        check("/a/b/..", "/a");
        check("/a/../b", "/b");
        check("/../a/./b", "/a/b");
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100);
            string s = Random::String<char>(n, "ab/.");
            check(s, "", true);
        }
    });

    Add("72. Edit Distance", [&]() {
        auto check = [&](const string &w1, const string &w2, int e,
                         bool ignoreE = false) {
            Logger().WriteInformation("Source:   %s\n", w1.c_str());
            Logger().WriteInformation("Target:   %s\n", w2.c_str());
            int a = minDistance(w1, w2);
            int b = minDistance2(w1, w2);
            int c = minDistance3(w1, w2);
            if (ignoreE) {
                Logger().WriteInformation("Distance: %d, %d, %d\n", a, b, c);
                ASSERT1(a == b);
                ASSERT1(b == c);
            } else {
                Logger().WriteInformation("Distance: %d, %d, %d, %d\n", a, b, c,
                                          e);
                ASSERT1(a == e);
                ASSERT1(b == e);
                ASSERT1(c == e);
            }
        };
        check("", "", 0);
        check("a", "", 1);
        check("ab", "", 2);
        check("", "b", 1);
        check("", "bc", 2);
        check("a", "a", 0);
        check("a", "b", 1);
        check("aa", "a", 1);
        check("aa", "b", 2);
        check("a", "bb", 2);
        check("b", "bb", 1);
        check("aa", "bb", 2);
        check("aa", "ab", 1);
        check("aa", "ba", 1);
        check("ab", "bb", 1);
        check("ba", "bb", 1);
        check("bb", "bb", 0);
        check("aaa", "a", 2);
        check("aaa", "b", 3);
        check("aaa", "aa", 1);
        check("aaa", "ab", 2);
        check("aaa", "ba", 2);
        check("aaa", "bc", 3);
        check("aaa", "abc", 2);
        check("aaa", "bac", 2);
        check("aaa", "bca", 2);
        check("aaa", "aab", 1);
        check("aaa", "aba", 1);
        check("aaa", "baa", 1);
        check("aaa", "bcd", 3);
        check("aaa", "aaa", 0);
        check("a", "aaa", 2);
        check("b", "aaa", 3);
        check("aa", "aaa", 1);
        check("ab", "aaa", 2);
        check("ba", "aaa", 2);
        check("bc", "aaa", 3);
        check("abc", "aaa", 2);
        check("bac", "aaa", 2);
        check("bca", "aaa", 2);
        check("aab", "aaa", 1);
        check("aba", "aaa", 1);
        check("baa", "aaa", 1);
        check("bcd", "aaa", 3);
        check("aaa", "aaa", 0);
        check("e", "dhwjmfxritzebjkoqvtm", 19);
        for (int i = 0; i < 100; i++) {
            int len1 = Random::Int(100, 1);
            string w1 = Random::String(len1);
            int len2 = Random::Int(100);
            string w2 = Random::String(len2);
            check(w1, w2, 0, true);
        }
    });

    Add("73. Set Matrix Zeroes", [&]() {
        auto test = [&](vector<vector<int>> &m) {
            vector<vector<int>> m2(m);
            setZeroes(m);
            setZeroes2(m2);
            ASSERT1(0 == Util::Compare(m, m2));
        };
        vector<vector<int>> m = {{0, 1}};
        test(m);
    });

    Add("74. Search a 2D Matrix", [&]() {
        auto check = [&](const vector<vector<int>> &m, int t, bool e) {
            bool a = searchMatrix(m, t);
            bool a2 = searchMatrix2(m, t);
            Logger().WriteInformation("Search %d, %d, %d\n", t, a, a2);
            ASSERT1(a == e);
            ASSERT1(a2 == e);
        };
        {
            vector<vector<int>> m = {
                {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
            Logger() << m;
            check(m, 1, true);
            check(m, 2, false);
            check(m, 3, true);
            check(m, 4, false);
            check(m, 5, true);
            check(m, 6, false);
            check(m, 7, true);
            check(m, 8, false);
            check(m, 10, true);
            check(m, 11, true);
            check(m, 12, false);
            check(m, 16, true);
            check(m, 18, false);
            check(m, 20, true);
            check(m, 21, false);
            check(m, 23, true);
            check(m, 25, false);
            check(m, 30, true);
            check(m, 32, false);
            check(m, 34, true);
            check(m, 40, false);
            check(m, 50, true);
            check(m, 60, false);
        }
    });

    Add("75. Sort Colors", [&]() {
        auto check = [&](vector<int> &a) {
            Logger().WriteInformation("Input:  ");
            Logger() << a;
            vector<int> a2(a);
            vector<int> a3(a);
            sortColors(a);
            sortColors2(a2);
            sortColors3(a3);
            Logger().WriteInformation("Output: ");
            Logger() << a << a2 << a3;
            ASSERT1(0 == Util::Compare(a, a2));
            ASSERT1(0 == Util::Compare(a, a3));
            for (size_t i = 1; i < a.size(); i++) {
                ASSERT1(a[i] >= a[i - 1]);
                ASSERT1(a2[i] >= a2[i - 1]);
                ASSERT1(a3[i] >= a3[i - 1]);
            }
        };
        {
            vector<int> a = {1};
            check(a);
        }
        {
            vector<int> a = {0, 0};
            check(a);
        }
        {
            vector<int> a = {0, 1};
            check(a);
        }
        {
            vector<int> a = {0, 2};
            check(a);
        }
        {
            vector<int> a = {1, 0};
            check(a);
        }
        {
            vector<int> a = {1, 1};
            check(a);
        }
        {
            vector<int> a = {1, 2};
            check(a);
        }
        {
            vector<int> a = {2, 0};
            check(a);
        }
        {
            vector<int> a = {2, 1};
            check(a);
        }
        {
            vector<int> a = {2, 2};
            check(a);
        }
        {
            vector<int> a = {0, 0, 0};
            check(a);
        }
        {
            vector<int> a = {0, 0, 1};
            check(a);
        }
        {
            vector<int> a = {0, 0, 2};
            check(a);
        }
        {
            vector<int> a = {0, 1, 0};
            check(a);
        }
        {
            vector<int> a = {0, 1, 1};
            check(a);
        }
        {
            vector<int> a = {0, 1, 2};
            check(a);
        }
        {
            vector<int> a = {0, 2, 0};
            check(a);
        }
        {
            vector<int> a = {0, 2, 1};
            check(a);
        }
        {
            vector<int> a = {0, 2, 2};
            check(a);
        }
        {
            vector<int> a = {1, 0, 0};
            check(a);
        }
        {
            vector<int> a = {1, 0, 1};
            check(a);
        }
        {
            vector<int> a = {1, 0, 2};
            check(a);
        }
        {
            vector<int> a = {1, 1, 0};
            check(a);
        }
        {
            vector<int> a = {1, 1, 1};
            check(a);
        }
        {
            vector<int> a = {1, 1, 2};
            check(a);
        }
        {
            vector<int> a = {1, 2, 0};
            check(a);
        }
        {
            vector<int> a = {1, 2, 1};
            check(a);
        }
        {
            vector<int> a = {1, 2, 2};
            check(a);
        }
        {
            vector<int> a = {2, 0, 0};
            check(a);
        }
        {
            vector<int> a = {2, 0, 1};
            check(a);
        }
        {
            vector<int> a = {2, 0, 2};
            check(a);
        }
        {
            vector<int> a = {2, 1, 0};
            check(a);
        }
        {
            vector<int> a = {2, 1, 1};
            check(a);
        }
        {
            vector<int> a = {2, 1, 2};
            check(a);
        }
        {
            vector<int> a = {2, 2, 0};
            check(a);
        }
        {
            vector<int> a = {2, 2, 1};
            check(a);
        }
        {
            vector<int> a = {2, 2, 2};
            check(a);
        }
        {
            for (int i = 0; i < 100; i++) {
                int len = Random::Int(50, 1);
                vector<int> v = Random::Vector(len, 2, 0);
                check(v);
            }
        }
    });

    Add("76. Minimum Window Substring", [&]() {
        auto check = [&](const string &s, const string &t, const string &e,
                         bool ignoreE = false) {
            Logger().WriteInformation("Source: %s\n", s.c_str());
            Logger().WriteInformation("Target: %s\n", t.c_str());
            string u = minWindow(s, t);
            string u2 = minWindow2(s, t);
            string u3 = minWindow3(s, t);
            if (ignoreE) {
                Logger().WriteInformation("Substring: %s %s %s\n", u.c_str(),
                                          u2.c_str(), u3.c_str());
                ASSERT1(u == u2);
                ASSERT1(u == u3);
            } else {
                Logger().WriteInformation("Substring: %s %s %s %s\n", u.c_str(),
                                          u2.c_str(), u3.c_str(), e.c_str());
                ASSERT1(u == e);
                ASSERT1(u2 == e);
                ASSERT1(u3 == e);
            }
        };
        check("", "", "");
        check("", "A", "");
        check("A", "", "");
        check("AA", "A", "A");
        check("AA", "AA", "AA");
        check("AB", "A", "A");
        check("AB", "B", "B");
        check("AB", "BA", "AB");
        check("AB", "AB", "AB");
        check("ACCCCCBCCCACCACB", "ABA", "ACCACB");
        check("ACCCCCBCCCACCACB", "ABD", "");
        check("ADOBECODEBANC", "ABC", "BANC");
        for (int i = 0; i < 100; i++) {
            int n1 = Random::Int(100);
            string s1 = Random::String<char>(n1, "abcdefg");
            int n2 = Random::Int(20);
            string s2 = Random::String<char>(n2, "abcdefgh");
            check(s1, s2, "", true);
        }
    });

    Add("77. Combinations", [&]() {
        auto check = [&](int n, int k) {
            Logger() << "Combine(" << n << ", " << k << ") =" << endl;
            vector<vector<int>> c = combine(n, k);
            vector<vector<int>> c2 = combine2(n, k);
            vector<vector<int>> c3 = combine3(n, k);
            vector<vector<int>> c4 = combine4(n, k);
            vector<vector<int>> c5 = combine5(n, k);
            vector<vector<int>> c6 = combine6(n, k);
            Util::SortGrid(c);
            Util::SortGrid(c2);
            Util::SortGrid(c3);
            Util::SortGrid(c4);
            Util::SortGrid(c5);
            Util::SortGrid(c6);
            Logger() << c;
            ASSERT1(0 == Util::Compare(c, c2));
            ASSERT1(0 == Util::Compare(c, c3));
            ASSERT1(0 == Util::Compare(c, c4));
            ASSERT1(0 == Util::Compare(c, c5));
            ASSERT1(0 == Util::Compare(c, c6));
        };
        for (int n = 1; n <= 10; n++) {
            for (int k = 1; k <= n; k++) {
                check(n, k);
            }
        }
    });

    Add("78. Subsets", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            vector<vector<int>> s = subsets(v);
            vector<vector<int>> s2 = subsets2(v);
            vector<int> v2(v);
            vector<vector<int>> s3 = subsetsWithDup(v2);
            vector<int> v3(v);
            vector<vector<int>> s4 = subsetsWithDup2(v3);
            Util::SortGrid(s);
            Util::SortGrid(s2);
            Util::SortGrid(s3);
            Util::SortGrid(s4);
            Logger() << s;
            ASSERT1(0 == Util::Compare(s, s2));
            ASSERT1(0 == Util::Compare(s, s3));
            ASSERT1(0 == Util::Compare(s, s4));
        };
        for (int i = 0; i <= 10; i++) {
            vector<int> v = Util::IncreasingVector(i);
            check(v);
        }
    });

    Add("79. Word Search", [&]() {
        auto print = [&](const vector<vector<char>> &board) {
            Logger().WriteInformation("Board:\n");
            for_each(board.begin(), board.end(), [&](const vector<char> &row) {
                for_each(row.begin(), row.end(),
                         [&](char c) { Logger().WriteInformation(" %c", c); });
                Logger().WriteInformation("\n");
            });
        };
        auto check = [&](const vector<vector<char>> &board, const string &word,
                         bool expect) {
            bool a = exist(board, word);
            bool a2 = exist2(board, word);
            Logger().WriteInformation("Search %s: %d, %d\n", word.c_str(), a,
                                      a2);
            ASSERT1(a == expect);
            ASSERT1(a2 == expect);
        };
        {
            vector<vector<char>> b = {{'A'}};
            print(b);
            check(b, "A", true);
            check(b, "B", false);
            check(b, "AA", false);
            check(b, "AB", false);
        }
        {
            vector<vector<char>> b = {{'A', 'B'}, {'B', 'A'}};
            print(b);
            check(b, "A", true);
            check(b, "B", true);
            check(b, "AA", false);
            check(b, "AB", true);
            check(b, "ABA", true);
            check(b, "BAB", true);
            check(b, "ABAB", true);
            check(b, "ABBA", false);
            check(b, "BAAB", false);
            check(b, "BABA", true);
        }
        {
            vector<vector<char>> b = {{'A', 'A'}, {'A', 'A'}};
            print(b);
            check(b, "A", true);
            check(b, "B", false);
            check(b, "AA", true);
            check(b, "AAA", true);
            check(b, "AAAA", true);
            check(b, "AAAAA", false);
        }
        {
            vector<vector<char>> b = {{'A', 'B', 'C', 'E'},
                                      {'S', 'F', 'C', 'S'},
                                      {'A', 'D', 'E', 'E'}};
            print(b);
            check(b, "ABCCED", true);
            check(b, "SEE", true);
            check(b, "ABCB", false);
        }
        {
            vector<vector<char>> b = {{'A', 'B', 'C', 'E'},
                                      {'S', 'F', 'E', 'S'},
                                      {'A', 'D', 'E', 'E'}};
            print(b);
            check(b, "ABCEFSADEESE", true);
        }
    });

    Add("80. Remove Duplicates from Sorted Array II", [&]() {
        auto check = [&](const vector<int> &v, int e, bool ignoreE = false) {
            Logger().WriteInformation("Input: ");
            Logger() << v;
            map<int, int> mv = Util::Count<int>(v);
            Logger() << mv;
            vector<int> w(v);
            int n = removeDuplicatesII(w);
            map<int, int> mw = Util::Count<int>(w, 0, n - 1);
            vector<int> w2(v);
            int n2 = removeDuplicatesII2(w2);
            map<int, int> mw2 = Util::Count<int>(w2, 0, n2 - 1);
            vector<int> w3(v);
            int n3 = removeDuplicatesII3(w3);
            map<int, int> mw3 = Util::Count<int>(w3, 0, n3 - 1);
            Logger().WriteInformation("Output:");
            Logger() << w;
            Logger() << mw;
            if (ignoreE) {
                ASSERT1(n == n2);
                ASSERT1(n == n3);
            } else {
                ASSERT1(n == e);
                ASSERT1(n2 == e);
                ASSERT1(n3 == e);
            }
            ASSERT1(Util::Contain<int>(mv, mw));
            ASSERT1(Util::Contain<int>(mv, mw2));
            ASSERT1(Util::Contain<int>(mv, mw3));
            ASSERT1(Util::Equal<int>(mw, mw2));
            ASSERT1(Util::Equal<int>(mw, mw3));
            for (auto it = mw.cbegin(); it != mw.cend(); it++) {
                ASSERT1(it->second <= 2);
            }
        };
        check({1}, 1);
        check({1, 1}, 2);
        check({1, 2}, 2);
        check({1, 1, 2}, 3);
        check({1, 1, 1}, 2);
        check({1, 2, 2}, 3);
        check({1, 2, 3}, 3);
        check({1, 2, 3, 4}, 4);
        check({1, 1, 3, 4}, 4);
        check({1, 1, 1, 4}, 3);
        check({1, 1, 1, 1}, 2);
        check({1, 2, 2, 4}, 4);
        check({1, 2, 2, 2}, 3);
        check({1, 2, 3, 3}, 4);
        check({1, 1, 3, 3}, 4);
        check({1, 2, 3, 4, 5}, 5);
        check({1, 1, 2, 2, 5}, 5);
        check({1, 1, 3, 4, 5}, 5);
        check({1, 1, 1, 4, 4}, 4);
        check({1, 1, 1, 1, 5}, 3);
        check({1, 1, 1, 1, 1}, 2);
        check({1, 1, 3, 3, 3}, 4);
        check({1, 3, 3, 3, 3}, 3);
        check({1, 3, 3, 3, 4}, 4);
    });

    Add("81. Search in Rotated Sorted Array II", [&]() {
        auto check = [&](const vector<int> &a, int t, int e) {
            bool b = searchII(a, t);
            bool b2 = searchII2(a, t);
            Logger().WriteInformation("  %d is found: %d, %d\n", t, b, b2);
            if (e == -1) {
                ASSERT1(!b);
                ASSERT1(!b2);
            } else {
                ASSERT1(b);
                ASSERT1(b2);
            }
        };
        {
            vector<int> a = {2, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 2, 1);
            check(a, 3, -1);
        }
        {
            vector<int> a = {1, 2, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, 1);
            check(a, 3, -1);
        }
        {
            vector<int> a = {2, 1, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, 2);
            check(a, 3, -1);
        }
        {
            vector<int> a = {2, 2, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 2);
            check(a, 2, 1);
            check(a, 3, -1);
        }
        {
            vector<int> a = {1, 1, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, 2);
            check(a, 3, -1);
        }
        {
            vector<int> a = {2, 1, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, 0);
            check(a, 3, -1);
        }
        {
            vector<int> a = {1, 2, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 2);
            check(a, 2, 1);
            check(a, 3, -1);
        }
        {
            vector<int> a = {2, 2, 2};
            Logger() << a;
            check(a, 1, -1);
            check(a, 2, 2);
            check(a, 3, -1);
        }
        {
            vector<int> a = {1, 1, 3, 4};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, -1);
            check(a, 3, 2);
            check(a, 4, 3);
            check(a, 5, -1);
        }
        {
            vector<int> a = {4, 1, 1, 3};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, -1);
            check(a, 3, 3);
            check(a, 4, 0);
            check(a, 5, -1);
        }
        {
            vector<int> a = {3, 4, 1, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 2);
            check(a, 2, -1);
            check(a, 3, 0);
            check(a, 4, 1);
            check(a, 5, -1);
        }
        {
            vector<int> a = {1, 3, 4, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, -1);
            check(a, 3, 1);
            check(a, 4, 2);
            check(a, 5, -1);
        }
        {
            vector<int> a = {1, 1, 1, 4};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, -1);
            check(a, 4, 3);
            check(a, 5, -1);
        }
        {
            vector<int> a = {4, 1, 1, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, -1);
            check(a, 4, 0);
            check(a, 5, -1);
        }
        {
            vector<int> a = {1, 4, 1, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, -1);
            check(a, 4, 1);
            check(a, 5, -1);
        }
        {
            vector<int> a = {1, 1, 4, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, -1);
            check(a, 4, 2);
            check(a, 5, -1);
        }
        {
            vector<int> a = {1, 1, 1, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, -1);
            check(a, 4, -1);
        }
        {
            vector<int> a = {1, 2, 2, 4};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, 1);
            check(a, 3, -1);
            check(a, 4, 3);
            check(a, 5, -1);
        }
        {
            vector<int> a = {4, 1, 2, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, 2);
            check(a, 3, -1);
            check(a, 4, 0);
            check(a, 5, -1);
        }
        {
            vector<int> a = {2, 4, 1, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 2);
            check(a, 2, 0);
            check(a, 3, -1);
            check(a, 4, 1);
            check(a, 5, -1);
        }
        {
            vector<int> a = {2, 2, 4, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 3);
            check(a, 2, 0);
            check(a, 3, -1);
            check(a, 4, 2);
            check(a, 5, -1);
        }
        {
            vector<int> a = {1, 2, 2, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, 1);
            check(a, 3, -1);
            check(a, 4, -1);
        }
        {
            vector<int> a = {2, 1, 2, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, 0);
            check(a, 3, -1);
            check(a, 4, -1);
        }
        {
            vector<int> a = {2, 2, 1, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 2);
            check(a, 2, 0);
            check(a, 3, -1);
            check(a, 4, -1);
        }
        {
            vector<int> a = {2, 2, 2, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 3);
            check(a, 2, 0);
            check(a, 3, -1);
            check(a, 4, -1);
        }
        {
            vector<int> a = {1, 2, 4, 4};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
            check(a, 2, 1);
            check(a, 3, -1);
            check(a, 4, 2);
        }
        {
            vector<int> a = {4, 1, 2, 4};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 1);
            check(a, 2, 2);
            check(a, 3, -1);
            check(a, 4, 0);
        }
        {
            vector<int> a = {4, 4, 1, 2};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 2);
            check(a, 2, 3);
            check(a, 3, -1);
            check(a, 4, 0);
        }
        {
            vector<int> a = {2, 4, 4, 1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 3);
            check(a, 2, 0);
            check(a, 3, -1);
            check(a, 4, 1);
        }
        {
            vector<int> a = {1};
            Logger() << a;
            check(a, 0, -1);
            check(a, 1, 0);
        }
    });

    Add("82. Remove Duplicates from Sorted List II", [&]() {
        auto check = [&](const vector<int> &nums) {
            ListNode *list = ToList(nums);
            Logger().WriteInformation("List:  ");
            Print(list);
            list = deleteDuplicatesII(list);
            Logger().WriteInformation("Dedup: ");
            if (list == nullptr)
                Logger().WriteInformation("\n");
            else {
                Print(list);
                int v = list->val;
                ListNode *p = list->next;
                bool foundDup = false;
                while (p != nullptr) {
                    if (p->val == v)
                        foundDup = true;
                    v = p->val;
                    p = p->next;
                }
                DeleteList(list);
                ASSERT1(foundDup == false);
            }
            ListNode *list2 = ToList(nums);
            Logger().WriteInformation("List:  ");
            Print(list2);
            list2 = deleteDuplicatesII2(list2);
            Logger().WriteInformation("Dedup: ");
            if (list2 == nullptr)
                Logger().WriteInformation("\n");
            else {
                Print(list2);
                int v = list2->val;
                ListNode *p = list2->next;
                bool foundDup = false;
                while (p != nullptr) {
                    if (p->val == v)
                        foundDup = true;
                    v = p->val;
                    p = p->next;
                }
                DeleteList(list2);
                ASSERT1(foundDup == false);
            }
            ListNode *list3 = ToList(nums);
            Logger().WriteInformation("List:  ");
            Print(list3);
            list3 = deleteDuplicatesII3(list3);
            Logger().WriteInformation("Dedup: ");
            if (list3 == nullptr)
                Logger().WriteInformation("\n");
            else {
                Print(list3);
                int v = list3->val;
                ListNode *p = list3->next;
                bool foundDup = false;
                while (p != nullptr) {
                    if (p->val == v)
                        foundDup = true;
                    v = p->val;
                    p = p->next;
                }
                DeleteList(list3);
                ASSERT1(foundDup == false);
            }
        };
        check(vector<int>{1});
        check(vector<int>{1, 1});
        check(vector<int>{1, 2});
        check(vector<int>{1, 1, 2});
        check(vector<int>{1, 2, 2});
        check(vector<int>{1, 1, 1});
        check(vector<int>{1, 2, 3});
        check(vector<int>{1, 1, 2, 2});
        check(vector<int>{1, 1, 1, 2});
        check(vector<int>{1, 2, 2, 2});
        check(vector<int>{1, 1, 1, 1});
        check(vector<int>{1, 2, 2, 3});
        check(vector<int>{1, 2, 3, 4});
    });

    Add("83. Remove Duplicates from Sorted List", [&]() {
        auto check = [&](const vector<int> &nums) {
            ListNode *list = ToList(nums);
            Logger().WriteInformation("List:  ");
            Print(list);
            list = deleteDuplicates(list);
            Logger().WriteInformation("Dedup: ");
            if (list == nullptr)
                Logger().WriteInformation("\n");
            else {
                Print(list);
                int v = list->val;
                ListNode *p = list->next;
                bool foundDup = false;
                while (p != nullptr) {
                    if (p->val == v)
                        foundDup = true;
                    v = p->val;
                    p = p->next;
                }
                DeleteList(list);
                ASSERT1(foundDup == false);
            }
            ListNode *list2 = ToList(nums);
            Logger().WriteInformation("List:  ");
            Print(list2);
            list2 = deleteDuplicates2(list2);
            Logger().WriteInformation("Dedup: ");
            if (list2 == nullptr)
                Logger().WriteInformation("\n");
            else {
                Print(list2);
                int v = list2->val;
                ListNode *p = list2->next;
                bool foundDup = false;
                while (p != nullptr) {
                    if (p->val == v)
                        foundDup = true;
                    v = p->val;
                    p = p->next;
                }
                DeleteList(list2);
                ASSERT1(foundDup == false);
            }
        };
        check(vector<int>{1});
        check(vector<int>{1, 1});
        check(vector<int>{1, 2});
        check(vector<int>{1, 1, 2});
        check(vector<int>{1, 2, 2});
        check(vector<int>{1, 1, 1});
        check(vector<int>{1, 2, 3});
        check(vector<int>{1, 1, 2, 2});
        check(vector<int>{1, 1, 1, 2});
        check(vector<int>{1, 2, 2, 2});
        check(vector<int>{1, 1, 1, 1});
        check(vector<int>{1, 2, 2, 3});
        check(vector<int>{1, 2, 3, 4});
    });

    Add("84. Largest Rectangle in Histogram", [&]() {
        auto check = [&](const vector<int> &h, int e) {
            Logger().WriteInformation("Histogram:");
            Logger() << h;
            int a = largestRectangleArea(h);
            int b = largestRectangleArea2(h);
            int c = largestRectangleArea3(h);
            Logger().WriteInformation(" max area: %d, %d, %d\n", a, b, c);
            if (e >= 0) {
                ASSERT1(a == e);
                ASSERT1(b == e);
                ASSERT1(c == e);
            } else {
                ASSERT1(a == b);
                ASSERT1(a == c);
            }
        };
        check(vector<int>{2, 1, 10, 9, 8, 10}, 32);
        check(vector<int>{1}, 1);
        check(vector<int>{2}, 2);
        check(vector<int>{1, 1}, 2);
        check(vector<int>{1, 2}, 2);
        check(vector<int>{1, 3}, 3);
        check(vector<int>{2, 3}, 4);
        check(vector<int>{0, 1}, 1);
        check(vector<int>{0, 2}, 2);
        check(vector<int>{0, 0}, 0);
        check(vector<int>{1, 0}, 1);
        check(vector<int>{2, 0}, 2);
        check(vector<int>{2, 1}, 2);
        check(vector<int>{3, 1}, 3);
        check(vector<int>{3, 2}, 4);
        check(vector<int>{0, 0, 0}, 0);
        check(vector<int>{1, 0, 0}, 1);
        check(vector<int>{0, 1, 0}, 1);
        check(vector<int>{0, 0, 1}, 1);
        check(vector<int>{1, 1, 0}, 2);
        check(vector<int>{1, 0, 1}, 1);
        check(vector<int>{0, 1, 1}, 2);
        check(vector<int>{1, 1, 1}, 3);
        check(vector<int>{2, 1, 1}, 3);
        check(vector<int>{1, 2, 1}, 3);
        check(vector<int>{1, 1, 2}, 3);
        check(vector<int>{3, 1, 1}, 3);
        check(vector<int>{1, 3, 1}, 3);
        check(vector<int>{1, 1, 3}, 3);
        check(vector<int>{4, 1, 1}, 4);
        check(vector<int>{1, 4, 1}, 4);
        check(vector<int>{1, 1, 4}, 4);
        check(vector<int>{1, 2, 2}, 4);
        check(vector<int>{2, 1, 2}, 3);
        check(vector<int>{2, 2, 1}, 4);
        check(vector<int>{1, 2, 3}, 4);
        check(vector<int>{1, 3, 2}, 4);
        check(vector<int>{2, 1, 3}, 3);
        check(vector<int>{2, 3, 1}, 4);
        check(vector<int>{3, 1, 2}, 3);
        check(vector<int>{3, 2, 1}, 4);
        check(vector<int>{1, 2, 5}, 5);
        check(vector<int>{1, 5, 2}, 5);
        check(vector<int>{5, 2, 1}, 5);
        check(vector<int>{5, 1, 2}, 5);
        check(vector<int>{1, 3, 4}, 6);
        check(vector<int>{3, 1, 4}, 4);
        check(vector<int>{1, 2, 3, 4}, 6);
        check(vector<int>{2, 1, 3, 4}, 6);
        check(vector<int>{2, 3, 1, 4}, 4);
        check(vector<int>{4, 2, 1, 3}, 4);
        check(vector<int>{4, 2, 3, 1}, 6);
        check(vector<int>{1, 2, 3, 4, 5}, 9);
        check(vector<int>{5, 4, 3, 2, 1}, 9);
        check(vector<int>{2, 1, 5, 6, 2, 3}, 10);
        for (int i = 0; i < 100; i++) {
            int len = 1 + (rand() % 100);
            vector<int> hist;
            for (int j = 0; j < len; j++) {
                int v = (rand() % 100);
                hist.push_back(v);
            }
            check(hist, -1);
        }
    });

    Add("85. Maximal Rectangle", [&]() {
        auto check = [&](const vector<vector<char>> &matrix, int expect) {
            Logger() << matrix;
            int area = maximalRectangle(matrix);
            int area2 = maximalRectangle2(matrix);
            Logger().WriteInformation(" Area: %d, %d\n", area, area2);
            if (expect < 0) {
                ASSERT1(area == area2);
            } else {
                ASSERT1(area == expect);
                ASSERT1(area2 == expect);
            }
        };
        {
            vector<vector<char>> m = {{'0'}};
            check(m, 0);
        }
        {
            vector<vector<char>> m = {{'1'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'0', '0'}};
            check(m, 0);
        }
        {
            vector<vector<char>> m = {{'0', '1'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'1', '0'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'1', '1'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'0'}, {'0'}};
            check(m, 0);
        }
        {
            vector<vector<char>> m = {{'1'}, {'0'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'0'}, {'1'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'1'}, {'1'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'0', '0'}, {'0', '0'}};
            check(m, 0);
        }
        {
            vector<vector<char>> m = {{'1', '0'}, {'0', '0'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'0', '1'}, {'0', '0'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'0', '0'}, {'1', '0'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'0', '0'}, {'0', '1'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'1', '1'}, {'0', '0'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'1', '0'}, {'1', '0'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'1', '0'}, {'0', '1'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'0', '1'}, {'1', '0'}};
            check(m, 1);
        }
        {
            vector<vector<char>> m = {{'0', '1'}, {'0', '1'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'0', '0'}, {'1', '1'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'1', '1'}, {'1', '0'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'1', '1'}, {'0', '1'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'1', '0'}, {'1', '1'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'0', '1'}, {'1', '1'}};
            check(m, 2);
        }
        {
            vector<vector<char>> m = {{'1', '1'}, {'1', '1'}};
            check(m, 4);
        }
        {
            vector<vector<char>> m = {{'1', '1', '1'}, {'1', '0', '0'}};
            check(m, 3);
        }
        {
            vector<vector<char>> m = {{'1', '1', '1'}, {'1', '1', '0'}};
            check(m, 4);
        }
        {
            vector<vector<char>> m = {{'1', '1', '1'}, {'1', '1', '1'}};
            check(m, 6);
        }
        {
            vector<vector<char>> m = {
                {'0', '0', '1', '0'}, {'1', '1', '1', '1'},
                {'1', '1', '1', '1'}, {'1', '1', '1', '0'},
                {'1', '1', '0', '0'}, {'1', '1', '1', '1'},
                {'1', '1', '1', '0'},
            };
            check(m, 12);
        }
        for (int i = 0; i < 100; i++) {
            int m = Random::Int(100, 1);
            int n = Random::Int(100, 1);
            vector<vector<char>> g = Random::Grid(m, n, '1', '0');
            check(g, -1);
        }
    });

    Add("86. Partition List", [&]() {
        auto check = [&](const vector<int> &nums, int x) {
            Logger().WriteInformation("Partition by %d:\n", x);
            ListNode *l = ToList(nums);
            Print(l);
            l = partition(l, x);
            Print(l);
            vector<int> v = ToVector(l);
            DeleteList(l);
            ListNode *l2 = ToList(nums);
            l2 = partition2(l2, x);
            Print(l2);
            vector<int> v2 = ToVector(l2);
            DeleteList(l2);
            ListNode *l3 = ToList(nums);
            l3 = partition3(l3, x);
            Print(l3);
            vector<int> v3 = ToVector(l3);
            DeleteList(l3);
            ASSERT1(0 == Util::Compare(v, v2));
            ASSERT1(0 == Util::Compare(v, v3));
            bool lessThanX = true;
            for (size_t i = 0; i < v.size(); i++) {
                if (v[i] < x) {
                    ASSERT1(lessThanX);
                } else {
                    if (lessThanX)
                        lessThanX = false;
                    ASSERT1(!lessThanX);
                }
                ASSERT1(v2[i] == v[i]);
                ASSERT1(v3[i] == v[i]);
            }
        };
        check({1}, 3);
        check({5}, 3);
        check({2, 1}, 3);
        check({5, 3}, 3);
        check({2, 4}, 3);
        check({5, 1}, 3);
        check({1, 4, 3, 2, 5, 2}, 3);
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v, Random::Int(150, -50));
        }
    });

    Add("87. Scramble String", [&]() {
        auto check = [&](const string &s1, const string &s2) {
            bool r = isScramble(s1, s2);
            bool r2 = isScramble2(s1, s2);
            bool r3 = isScramble3(s1, s2);
            Logger().WriteInformation("IsScramble(%s, %s) = %d, %d, %d\n",
                                      s1.c_str(), s2.c_str(), r, r2, r3);
            ASSERT1(r == r2);
            ASSERT1(r == r3);
        };
        check("", "");
        check("a", "b");
        check("a", "a");
        check("ab", "ab");
        check("ab", "ba");
        check("ab", "ac");
        check("ab", "ca");
        check("aaa", "aaa");
        check("abcd", "acbd");
        check("abcd", "adbc");
        check("abcd", "badc");
        check("abcd", "bdac");
        check("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aaaaaaaaaaaaaaa",
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aaaaaaaaaaaaaaa");

        for (int i = 0; i < 100; i++) {
            int len = Random::Int(10, 1);
            string s1 = Random::String<char>(len, "abcdefg");
            for (int j = 0; j < 10; j++) {
                string s2(s1);
                random_shuffle(s2.begin(), s2.end());
                check(s1, s2);
            }
        }
    });

    Add("88. Merge Sorted Array", [&]() {
        auto check = [&](vector<int> &v, int m, vector<int> &w, int n) {
            Logger().WriteInformation("Merge:\n");
            Logger() << v << w;
            vector<int> v2(v), v3(v), v4(v), w2(w), w3(w), w4(w);
            merge(v, m, w, n);
            merge2(v2, m, w2, n);
            merge3(v3, m, w3, n);
            merge4(v4, m, w4, n);
            Logger().WriteInformation("  to:\n");
            Logger() << v2 << v3 << v4;
            ASSERT1(is_sorted(v.begin(), v.end()));
            ASSERT1(is_sorted(v2.begin(), v2.end()));
            ASSERT1(is_sorted(v3.begin(), v3.end()));
            ASSERT1(is_sorted(v4.begin(), v4.end()));
            ASSERT1(0 == Util::Compare(v, v2));
            ASSERT1(0 == Util::Compare(v, v3));
            ASSERT1(0 == Util::Compare(v, v4));
        };
        {
            vector<int> v(1, 0);
            vector<int> w = {1};
            check(v, 0, w, 1);
        }
        {
            vector<int> v = {1};
            vector<int> w = {};
            check(v, 1, w, 0);
        }
        {
            vector<int> v = {1, 0};
            vector<int> w = {2};
            check(v, 1, w, 1);
        }
        {
            vector<int> v = {1, 0};
            vector<int> w = {0};
            check(v, 1, w, 1);
        }
        {
            vector<int> v = {1, 1, 0};
            vector<int> w = {2};
            check(v, 2, w, 1);
        }
        {
            vector<int> v = {1, 2, 0};
            vector<int> w = {2};
            check(v, 2, w, 1);
        }
        {
            vector<int> v = {1, 3, 0};
            vector<int> w = {2};
            check(v, 2, w, 1);
        }
        {
            vector<int> v = {1, 1, 0};
            vector<int> w = {0};
            check(v, 2, w, 1);
        }
        for (int i = 0; i < 100; i++) {
            int m = Random::Int(100);
            vector<int> v = Random::Vector(m, 100);
            sort(v.begin(), v.end());
            int n = Random::Int(100);
            vector<int> w = Random::Vector(n, 100);
            sort(w.begin(), w.end());
            v.resize(m + n, 0);
            check(v, m, w, n);
        }
    });

    Add("89. Gray Code", [&]() {
        auto check = [&](int n) {
            vector<int> codes = grayCode(n);
            vector<int> codes2 = grayCode2(n);
            Logger().WriteInformation("%d-bit gray codes:\n", n);
            ASSERT1(codes.size() == codes2.size());
            for (size_t i = 0; i < codes.size(); i++) {
                Logger().WriteInformation("  ");
                for (int j = n - 1; j >= 0; j--) {
                    Logger().WriteInformation("%d", (codes[i] >> j) & 0x1);
                }
                Logger().WriteInformation(
                    " %s %d\n", codes[i] == codes2[i] ? "==" : "!=", codes2[i]);
                ASSERT1(codes[i] == codes2[i]);
            }
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
    });

    Add("90. Subsets II", [&]() {
        auto check = [&](const vector<int> &nums) {
            Logger() << nums;
            vector<vector<int>> v = subsets(vector<int>(nums));
            set<vector<int>> s;
            for_each(v.begin(), v.end(), [&](vector<int> &i) {
                sort(i.begin(), i.end());
                s.insert(i);
            });
            Logger() << s;
            vector<int> n(nums);
            vector<vector<int>> w = subsetsWithDup(n);
            vector<int> n2(nums);
            vector<vector<int>> w2 = subsetsWithDup2(n2);
            ASSERT1(s.size() == w.size());
            ASSERT1(s.size() == w2.size());
            for (size_t i = 0; i < w.size(); i++) {
                ASSERT1(s.find(w[i]) != s.end());
                ASSERT1(s.find(w2[i]) != s.end());
            }
        };
        check({1, 2, 2});
        check({1, 1});
        check({2, 2, 2});
        check({1, 1, 2, 2, 3, 3});
        for (int i = 0; i < 20; i++) {
            int n = Random::Int(10, 1);
            vector<int> v = Random::Vector(n, 5);
            check(v);
        }
    });

    Add("91. Decode Ways", [&]() {
        auto check = [&](const string &s) {
            int c = numDecodings(s);
            int c2 = numDecodings2(s);
            int c3 = numDecodings3(s);
            Logger().WriteInformation("Ways to decode %s: %d, %d, %d\n",
                                      s.c_str(), c, c2, c3);
            ASSERT1(c == c2);
            ASSERT1(c == c3);
        };
        check("0");
        check("1");
        check("12");
        check("123");
        check("1234");
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(20);
            string s = Random::String<char>(n, "01112223456789");
            check(s);
        }
    });

    Add("92. Reverse Linked List II", [&]() {
        auto check = [&](const vector<int> &v, int m, int n) {
            ListNode *l = ToList(v);
            Logger() << "Input:" << endl;
            Print(l);
            Logger() << "Reverse between " << m << " and " << n << endl;
            l = reverseBetween(l, m, n);
            Print(l);
            vector<int> w = ToVector(l);
            DeleteList(l);
            ListNode *l2 = ToList(v);
            l2 = reverseBetween(l2, m, n);
            Print(l2);
            vector<int> w2 = ToVector(l2);
            DeleteList(l2);
            ListNode *l3 = ToList(v);
            l3 = reverseBetween(l3, m, n);
            Print(l3);
            vector<int> w3 = ToVector(l3);
            DeleteList(l3);
            ASSERT1(0 == Util::Compare(w, w2));
            ASSERT1(0 == Util::Compare(w, w3));
        };
        check({1}, 1, 1);
        check({1, 2}, 1, 1);
        check({1, 2}, 2, 2);
        check({1, 2}, 1, 2);
        check({1, 2, 3}, 1, 1);
        check({1, 2, 3}, 2, 2);
        check({1, 2, 3}, 3, 3);
        check({1, 2, 3}, 1, 2);
        check({1, 2, 3}, 2, 3);
        check({1, 2, 3}, 1, 3);
        for (int i = 3; i < 10; i++) {
            vector<int> v = Util::IncreasingVector(i + 1);
            for (int m = 1; m <= (int)v.size(); m++) {
                for (int n = m; n <= (int)v.size(); n++)
                    check(v, m, n);
            }
        }
    });

    Add("93. Restore IP Addresses", [&]() {
        auto check = [&](const string &s) {
            Logger().WriteInformation("%s\n", s.c_str());
            vector<string> ips = restoreIpAddresses(s);
            vector<string> ips2 = restoreIpAddresses2(s);
            vector<string> ips3 = restoreIpAddresses3(s);
            Util::Sort(ips);
            Util::Sort(ips2);
            Util::Sort(ips3);
            for_each(ips.begin(), ips.end(), [&](string &i) {
                Logger().WriteInformation("\t%s\n", i.c_str());
            });
            ASSERT1(0 == Util::Compare(ips, ips2));
            ASSERT1(0 == Util::Compare(ips, ips3));
        };
        check("25525511135");
        check("0000");
        check("1234");
        check("255255255255");
        check("010010");
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(12, 4);
            string s = Random::String<char>(n, "0123456789");
            check(s);
        }
    });

    Add("PreOrderTraversal", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << "Input: " << v;
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<int> w = preorderTraversal(t);
            vector<int> w2 = preorderTraversal2(t);
            DeleteTree(t);
            Logger() << w << w2;
            ASSERT1(0 == Util::Compare(w, w2));
            ASSERT1(v.size() == w.size());
            vector<int> v1(v);
            sort(v1.begin(), v1.end());
            sort(w.begin(), w.end());
            ASSERT1(0 == Util::Compare(v1, w));
        };
        check({});
        check({1});
        check({1, 2});
        check({1, 2, 3});
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("94. Binary Tree Inorder Traversal", [&]() {
        auto check = [&](const vector<int> &v) {
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<int> w = inorderTraversal(t);
            vector<int> w2 = inorderTraversal2(t);
            vector<int> w3 = inorderTraversal3(t);
            DeleteTree(t);
            Logger() << w;
            ASSERT1(0 == Util::Compare(w, w2));
            ASSERT1(0 == Util::Compare(w, w3));
            ASSERT1(v.size() == w.size());
            vector<int> v1(v);
            sort(v1.begin(), v1.end());
            sort(w.begin(), w.end());
            ASSERT1(0 == Util::Compare(v1, w));
        };
        check({});
        check({1});
        check({1, 2});
        check({1, 2, 3});
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("PostOrderTraversal", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << "Input: " << v;
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<int> w = postorderTraversal(t);
            vector<int> w2 = postorderTraversal2(t);
            DeleteTree(t);
            Logger() << w << w2;
            ASSERT1(0 == Util::Compare(w, w2));
            ASSERT1(v.size() == w.size());
            vector<int> v1(v);
            sort(v1.begin(), v1.end());
            sort(w.begin(), w.end());
            ASSERT1(0 == Util::Compare(v1, w));
        };
        check({});
        check({1});
        check({1, 2});
        check({1, 2, 3});
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("95. Unique Binary Search Trees II", [&]() {
        auto check = [&](int n) {
            vector<TreeNode *> trees = generateTrees(n);
            vector<TreeNode *> trees2 = generateTrees2(n);
            vector<vector<int>> m;
            for (size_t i = 0; i < trees.size(); i++) {
                Logger() << "Tree " << i << "\n";
                Print(trees[i]);
                m.push_back(inorderTraversal(trees[i]));
                DeleteTree(trees[i]);
            }
            vector<vector<int>> m2;
            for (size_t i = 0; i < trees2.size(); i++) {
                m2.push_back(inorderTraversal(trees2[i]));
                DeleteTree(trees2[i]);
            }
            Util::Sort(m);
            Util::Sort(m2);
            ASSERT1(0 == Util::Compare(m, m2));
            int c = numTrees(n);
            int c2 = numTrees2(n);
            int c3 = numTrees3(n);
            ASSERT1((int)m.size() == c);
            ASSERT1((int)m.size() == c2);
            ASSERT1((int)m.size() == c3);
        };
        for (int i = 0; i < 10; i++)
            check(i + 1);
    });

    Add("97. Interleaving String", [&]() {
        auto check = [&](const string &s1, const string &s2, const string &s3,
                         bool expect) {
            Logger().WriteInformation("s1: %s\n", s1.c_str());
            Logger().WriteInformation("s2: %s\n", s2.c_str());
            Logger().WriteInformation("s3: %s\n", s3.c_str());
            bool r = isInterleave(s1, s2, s3);
            bool r2 = isInterleave2(s1, s2, s3);
            Logger().WriteInformation("is interleave: %d, %d\n", r, r2);
            ASSERT1(r == expect);
            ASSERT1(r2 == expect);
        };
        check("", "", "", true);
        check("a", "", "a", true);
        check("a", "", "b", false);
        check("", "a", "a", true);
        check("", "a", "b", false);
        check("a", "a", "aa", true);
        check("a", "a", "ab", false);
        check("a", "a", "ba", false);
        check("a", "b", "ab", true);
        check("a", "b", "ba", true);
        check("ab", "ac", "abac", true);
        check("ab", "ac", "acab", true);
        check("ab", "ac", "aabc", true);
        check("ab", "ac", "aacb", true);
        check("ab", "ac", "acba", false);
        check("ab", "ac", "caab", false);
        check("ab", "ac", "bcaa", false);
        check("aabcc", "dbbca", "aadbbcbcac", true);
        check("aabcc", "dbbca", "aadbbbaccc", false);
    });

    Add("98. Validate Binary Search Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            TreeNode *t = RandomTreeFromInOrder(v);
            Print(t);
            bool r = isValidBST(t);
            bool r2 = isValidBST2(t);
            bool r3 = isValidBST3(t);
            bool r4 = isValidBST4(t);
            DeleteTree(t);
            Logger() << "is valid BST: " << r << ", " << r2 << ", " << r3
                     << ", " << r4 << endl;
            ASSERT1(r == r2);
            ASSERT1(r == r3);
            ASSERT1(r == r4);
        };
        check({});
        check({1});
        check({1, 2});
        check({1, 2, 3});
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(50);
            vector<int> v = Random::Vector(n);
            check(v);
            sort(v.begin(), v.end());
            check(v);
        }
    });

    Add("99. Recover Binary Search Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            TreeNode *t = RandomTreeFromInOrder(v);
            Print(t);
            TreeNode *t2 = Clone(t);
            bool r = isValidBST(t);
            bool r2 = isValidBST(t2);
            recoverTree(t);
            recoverTree2(t2);
            bool s = isValidBST(t);
            bool s2 = isValidBST(t2);
            Print(t);
            DeleteTree(t);
            DeleteTree(t2);
            ASSERT1(r == false);
            ASSERT1(r2 == false);
            ASSERT1(s == true);
            ASSERT1(s2 == true);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(40, 2);
            vector<int> v = Util::IncreasingVector(n);
            int a = Random::Int(n - 1);
            int b = Random::Int(n - 1);
            if (b == a)
                b = a < n - 1 ? a + 1 : a - 1;
            Logger() << v;
            Logger() << "Swap " << v[a] << " and " << v[b] << endl;
            swap(v[a], v[b]);
            check(v);
        }
    });

    Add("100. Same Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            TreeNode *t = RandomTree(v);
            TreeNode *t2 = RandomTree(v);
            Print(t);
            Print(t2);
            bool r = isSameTree(t, t2);
            Logger() << "isSameTree " << r << endl;
            DeleteTree(t);
            DeleteTree(t2);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(40, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("101. Symmetric Tree", [&]() {
        auto check = [&](const vector<int> &v,
                         bool createSymmetricTree = false) {
            Logger() << v;
            TreeNode *t;
            if (createSymmetricTree)
                t = RandomSymmetricTree(v);
            else
                t = RandomTree(v);
            Print(t);
            bool r = isSymmetric(t);
            bool r2 = isSymmetric2(t);
            Logger() << "isSymmetric: " << r << ", " << r2 << endl;
            DeleteTree(t);
            ASSERT1(r == r2);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(20, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
            check(v, true);
        }
    });

    Add("102. Binary Tree Level Order Traversal", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<vector<int>> r = levelOrder(t);
            vector<vector<int>> r2 = levelOrder2(t);
            Logger() << "levelOrder: " << r << endl;
            DeleteTree(t);
            ASSERT1(0 == Util::Compare(r, r2));
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("103. Binary Tree Zigzag Level Order Traversal", [&]() {
        auto checkTree = [&](TreeNode *t) {
            Print(t);
            vector<vector<int>> r = zigzagLevelOrder(t);
            vector<vector<int>> r2 = zigzagLevelOrder2(t);
            Logger() << r;
            DeleteTree(t);
            ASSERT1(0 == Util::Compare(r, r2));
        };
        auto checkVector = [&](const vector<int> &v) {
            TreeNode *t = RandomTree(v);
            checkTree(t);
        };
        {
            TreeNode *t = new TreeNode(3);
            t->left = new TreeNode(9);
            t->right = new TreeNode(20);
            t->right->left = new TreeNode(15);
            t->right->right = new TreeNode(7);
            checkTree(t);
        }
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            checkVector(v);
        }
    });

    Add("104. Maximum Depth of Binary Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            TreeNode *t = RandomTree(v);
            Print(t);
            int d = maxDepth(t);
            int d2 = maxDepth2(t);
            Logger() << "maxDepth: " << d << ", " << d2 << endl;
            DeleteTree(t);
            ASSERT1(d == d2);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("105. Construct Binary Tree from Preorder and Inorder Traversal",
        [&]() {
            auto check = [&](const vector<int> &v) {
                TreeNode *t = RandomTree(v);
                Print(t);
                vector<int> pre = preorderTraversal(t);
                Logger() << "PreOrder: " << pre;
                vector<int> in = inorderTraversal(t);
                Logger() << "InOrder:  " << in;
                TreeNode *t2 = buildTree(pre, in);
                Print(t2);
                bool r = isSameTree(t, t2);
                TreeNode *t3 = buildTree2(pre, in);
                Print(t3);
                bool r2 = isSameTree(t, t3);
                TreeNode *t4 = buildTree3(pre, in);
                Print(t4);
                bool r3 = isSameTree(t, t4);
                Logger() << "isSame: " << r << ", " << r2 << ", " << r3 << endl;
                DeleteTree(t);
                DeleteTree(t2);
                DeleteTree(t3);
                DeleteTree(t4);
                ASSERT1(r == true);
                ASSERT1(r2 == true);
                ASSERT1(r3 == true);
            };
            for (int i = 0; i < 100; i++) {
                int n = Random::Int(100, 1);
                vector<int> v = Util::IncreasingVector(n);
                check(v);
            }
        });

    Add("106. Construct Binary Tree from Inorder and Postorder Traversal",
        [&]() {
            auto check = [&](const vector<int> &v) {
                TreeNode *t = RandomTree(v);
                Print(t);
                vector<int> in = inorderTraversal(t);
                Logger() << "InOrder:   " << in;
                vector<int> post = postorderTraversal(t);
                Logger() << "PostOrder: " << post;
                TreeNode *t2 = buildTreeInOrderPostOrder(in, post);
                Print(t2);
                bool r = isSameTree(t, t2);
                TreeNode *t3 = buildTreeInOrderPostOrder2(in, post);
                Print(t3);
                bool r2 = isSameTree(t, t3);
                TreeNode *t4 = buildTreeInOrderPostOrder3(in, post);
                Print(t4);
                bool r3 = isSameTree(t, t4);
                Logger() << "isSame: " << r << ", " << r2 << ", " << r3 << endl;
                DeleteTree(t);
                DeleteTree(t2);
                DeleteTree(t3);
                DeleteTree(t4);
                ASSERT1(r == true);
                ASSERT1(r2 == true);
                ASSERT1(r3 == true);
            };
            for (int i = 0; i < 100; i++) {
                int n = Random::Int(100, 1);
                vector<int> v = Util::IncreasingVector(n);
                check(v);
            }
        });

    Add("107. Binary Tree Level Order Traversal II", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << v;
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<vector<int>> r = levelOrderBottom(t);
            vector<vector<int>> r2 = levelOrderBottom2(t);
            Logger() << "levelOrderBottom: " << r << endl;
            DeleteTree(t);
            ASSERT1(0 == Util::Compare(r, r2));
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Random::Vector(n, 100);
            check(v);
        }
    });

    Add("108. Convert Sorted Array to Binary Search Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            Logger() << "Convert to balanced BST:" << v;
            TreeNode *t = sortedArrayToBST(v);
            Print(t);
            TreeNode *t2 = sortedArrayToBST2(v);
            Print(t2);
            bool r = isSameTree(t, t2);
            Logger() << "isSameTree: " << r << endl;
            DeleteTree(t);
            DeleteTree(t2);
            ASSERT1(r == true);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("109. Convert Sorted List to Binary Search Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            ListNode *l = ToList(v);
            Logger() << "Convert to balanced BST:";
            Print(l);
            TreeNode *t = sortedListToBST(l);
            Print(t);
            TreeNode *t2 = sortedListToBST2(l);
            Print(t2);
            TreeNode *t3 = sortedListToBST3(l);
            Print(t3);
            bool b = isBalanced(t);
            bool b2 = isBalanced(t2);
            bool b3 = isBalanced(t3);
            Logger() << "isBalanced: " << b << ", " << b2 << ", " << b3 << endl;
            bool r = isSameTree(t, t2);
            bool r2 = isSameTree(t, t3);
            Logger() << "isSameTree: " << r << ", " << r2 << endl;
            DeleteTree(t);
            DeleteTree(t2);
            DeleteTree(t3);
            DeleteList(l);
            ASSERT1(b == true);
            ASSERT1(b2 == true);
            ASSERT1(b3 == true);
            // ASSERT1(r == true); sortedListToBST2 is a bit different
            ASSERT1(r2 == true);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("111. Minimum Depth of Binary Tree", [&]() {
        auto check = [&](const vector<int> &v) {
            TreeNode *t = RandomTree(v);
            Print(t);
            int d = minDepth(t);
            int d2 = minDepth2(t);
            int d3 = minDepth3(t);
            DeleteTree(t);
            Logger() << "minDepth: " << d << ", " << d2 << ", " << d3 << endl;
            ASSERT1(d == d2);
            ASSERT1(d == d3);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v);
        }
    });

    Add("112. Path Sum", [&]() {
        auto check = [&](const vector<int> &v, int sum) {
            TreeNode *t = RandomTree(v);
            Print(t);
            int r = hasPathSum(t, sum);
            int r2 = hasPathSum2(t, sum);
            int s = pickPathSum(t);
            int b = hasPathSum(t, s);
            int b2 = hasPathSum2(t, s);
            DeleteTree(t);
            Logger() << "hasPathSum(" << sum << "): " << r << ", " << r2
                     << endl;
            Logger() << "hasPathSum(" << s << "): " << b << ", " << b2 << endl;
            ASSERT1(r == r2);
            ASSERT1(b == true);
            ASSERT1(b2 == true);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v, Random::Int(200));
        }
    });

    Add("113. Path Sum II", [&]() {
        auto check = [&](const vector<int> &v, int sum) {
            TreeNode *t = RandomTree(v);
            Print(t);
            vector<vector<int>> r = pathSum(t, sum);
            vector<vector<int>> r2 = pathSum2(t, sum);
            Logger() << "pathSum(" << sum << "):" << endl;
            Util::Sort(r);
            Util::Sort(r2);
            Logger() << r;
            setPathSum(t, sum);
            Print(t);
            vector<vector<int>> b = pathSum(t, sum);
            vector<vector<int>> b2 = pathSum2(t, sum);
            DeleteTree(t);
            Util::Sort(b);
            Util::Sort(b2);
            Logger() << "pathSum(" << sum << "):" << endl;
            Logger() << b;
            ASSERT1(0 == Util::Compare(r, r2));
            ASSERT1(0 == Util::Compare(b, b2));
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            vector<int> v = Util::IncreasingVector(n);
            check(v, Random::Int(200));
        }
    });

    Add("114. Flatten Binary Tree to Linked List", [&]() {
        auto check = [&](int n) {
            TreeNode *t = RandomTree(n);
            Print(t);
            TreeNode *t2 = Clone(t);
            flatten(t);
            Print(t);
            flatten(t2);
            Print(t2);
            vector<int> v = preorderTraversal(t);
            vector<int> v2 = preorderTraversal(t2);
            DeleteTree(t);
            DeleteTree(t2);
            ASSERT1(Util::IsIncreasing(v));
            ASSERT1(Util::IsIncreasing(v2));
            ASSERT1(0 == Util::Compare(v, v2));
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 1);
            check(n);
        }
    });

    Add("115. Distinct Subsequences", [&]() {
        auto check = [&](const string &s, const string &t) {
            int c = numDistinct(s, t);
            int c2 = numDistinct2(s, t);
            Logger() << "numDistinct(" << endl;
            Logger() << "s: " << s << endl;
            Logger() << "t: " << t << endl;
            Logger() << ") = " << c << ", " << c2 << endl;
            ASSERT1(c == c2);
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100, 2);
            int m = Random::Int(10, 1);
            string s = Random::String<char>(n, "abcdefg");
            string t = Random::String<char>(m, "abcd");
            check(s, t);
        }
    });

    Add("123. Best Time to Buy and Sell Stock III", [&]() {
        auto check = [&](const vector<int> &p) {
            Logger() << p;
            int m = maxProfitIII(p);
            int m2 = maxProfitIII2(p);
            int m3 = maxProfitIII3(p);
            int m4 = maxProfitIII4(p);
            Logger() << "maxProfitIII: " << m << ", " << m2 << ", " << m3
                     << ", " << m4 << endl;
            ASSERT1(m == m2);
            ASSERT1(m == m3);
            ASSERT1(m == m4);
        };
        check({1});
        check({1, 2});
        check({2, 2});
        check({1, 2, 3});
        check({1, 2, 2});
        check({2, 2, 2});
        check({1, 2, 3, 4});
        check({2, 7, 1, 6});
        check({3, 7, 1, 6});
        check({9, 7, 10, 9, 5, 8, 3, 7, 2, 1, 5, 3});
        check({6, 1, 3, 2, 4, 7});
        for (int i = 0; i < 100; i++) {
            int len = Random::Int(100, 1);
            vector<int> v = Random::Vector(len, 100);
            check(v);
        }
    });

    Add("124. Binary Tree Maximum Path Sum", [&]() {
        auto check = [&](TreeNode *node, long long expect) {
            Print(node);
            long long sum = maxPathSum(node);
            Logger().WriteInformation("Sum %lld %s %lld\n", sum,
                                      sum == expect ? "==" : "!=", expect);
            ASSERT1(sum == expect);
        };
        {
            TreeNode n1(1);
            check(&n1, 1);
        }
        {
            TreeNode n1(-1);
            check(&n1, -1);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            n1.left = &n2;
            check(&n1, 3);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(2);
            n1.left = &n2;
            check(&n1, 2);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            n1.left = &n2;
            check(&n1, 1);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(-2);
            n1.left = &n2;
            check(&n1, -1);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            n1.right = &n2;
            check(&n1, 3);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(2);
            n1.right = &n2;
            check(&n1, 2);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            n1.right = &n2;
            check(&n1, 1);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(-2);
            n1.right = &n2;
            check(&n1, -1);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 6);
        }
        {
            TreeNode n1(-1);
            TreeNode n2(2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 4);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 4);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 3);
        }
        {
            TreeNode n1(-2);
            TreeNode n2(2);
            TreeNode n3(3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 3);
        }
        {
            TreeNode n1(-2);
            TreeNode n2(3);
            TreeNode n3(2);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 3);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, 1);
        }
        {
            TreeNode n1(-4);
            TreeNode n2(-2);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, -2);
        }
        {
            TreeNode n1(-4);
            TreeNode n2(-4);
            TreeNode n3(-3);
            n1.left = &n2;
            n1.right = &n3;
            check(&n1, -3);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 10);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-2);
            TreeNode n3(3);
            TreeNode n4(4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 6);
        }
        {
            TreeNode n1(1);
            TreeNode n2(-4);
            TreeNode n3(3);
            TreeNode n4(4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 4);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(-4);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            check(&n1, 6);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(3);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            check(&n1, 10);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(5);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            check(&n1, 11);
        }
        {
            TreeNode n1(1);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(5);
            TreeNode n6(6);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            n3.left = &n6;
            check(&n1, 17);
        }
        {
            TreeNode n1(-10);
            TreeNode n2(2);
            TreeNode n3(3);
            TreeNode n4(4);
            TreeNode n5(5);
            TreeNode n6(6);
            n1.left = &n2;
            n1.right = &n3;
            n2.left = &n4;
            n2.right = &n5;
            n3.left = &n6;
            check(&n1, 11);
        }
    });

    Add("125. Valid Palindrome", [&]() {
        auto check = [&](const string &s, bool e) {
            bool r = isPalindrome(s);
            bool r2 = isPalindrome2(s);
            bool r3 = isPalindrome3(s);
            Logger().WriteInformation("\"%s\" is palindrome: %d, %d, %d\n",
                                      s.c_str(), r, r2, r3);
            ASSERT1(r == e);
            ASSERT1(r2 == e);
            ASSERT1(r3 == e);
        };
        check("", true);
        check("1", true);
        check("a", true);
        check(",", true);
        check("22", true);
        check("23", false);
        check("ab", false);
        check("a1", false);
        check(":3", true);
        check("a;", true);
        check("?b", true);
        check("# #4**", true);
        check("# c**", true);
        check("a, b&*() A;", true);
        check("A man, a plan, a canal: Panama", true);
        check("race a car", false);
        check("^%(&*%$%(", true);
        check("A^%(&*%$%(a", true);
        check("^%9(&*%$9%(", true);
    });

    Add("126. Word Ladder II", [&]() {
        auto check = [&](const string &begin, const string &end,
                         const vector<string> &dic) {
            Logger() << dic;
            Logger() << "Search path: " << begin << " -> " << end << endl;
            vector<vector<string>> results = findLadders(begin, end, dic);
            vector<vector<string>> results2 = findLadders2(begin, end, dic);
            Util::Sort(results);
            Util::Sort(results2);
            Logger() << "Results = " << results;
            ASSERT1(0 == Util::Compare(results, results2));
        };
        check("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"});
    });

    Add("127. Word Ladder", [&]() {
        auto check = [&](const string &start, const string &end,
                         const vector<string> &dict, int expect) {
            Logger() << "Dictionary:" << dict;
            Logger().WriteInformation("    Start:   %s\n", start.c_str());
            Logger().WriteInformation("    End:     %s\n", end.c_str());
            int length = ladderLength(start, end, dict);
            int length2 = ladderLength2(start, end, dict);
            int length3 = ladderLength3(start, end, dict);
            int length4 = ladderLength4(start, end, dict);
            int length5 = ladderLength5(start, end, dict);
            Logger().WriteInformation("    Length:  %d, %d, %d, %d, %d, %d\n",
                                      length, length2, length3, length4,
                                      length5, expect);
            ASSERT1(length == expect);
            ASSERT1(length2 == expect);
            ASSERT1(length3 == expect);
            ASSERT1(length4 == expect);
            ASSERT1(length5 == expect);
        };
        check("hit", "cog", {"hot"}, 0);
        check("hit", "cog", {"hot", "dot", "dog", "lot", "log"}, 0);
        check("hit", "cog", {"hot", "dot", "dog", "cog", "lot", "log"}, 5);
        check("red", "tax",
              {"ted", "tex", "reb", "tax", "tad", "den", "rex", "pee"}, 4);
        check("d", "c", vector<string>{"a", "b", "c"}, 2);
        check("qa", "sq",
              vector<string>{"si", "go", "se", "cm", "so", "ph", "mt", "db",
                             "mb", "sb", "kr", "ln", "tm", "le", "av", "sm",
                             "ar"},
              0);
    });

    Add("128. Longest Consecutive Sequence", [&]() {
        auto check = [&](const vector<int> &input, int expectLength,
                         bool ignoreE = false) {
            Logger() << input;
            int length = longestConsecutive(input);
            int length2 = longestConsecutive2(input);
            int length3 = longestConsecutive3(input);
            if (ignoreE) {
                Logger().WriteInformation("  Length: %d, %d, %d\n", length,
                                          length2, length3);
                ASSERT1(length == length2);
                ASSERT1(length == length3);
            } else {
                Logger().WriteInformation("  Length: %d, %d, %d, %d\n", length,
                                          length2, length3, expectLength);
                ASSERT1(length == expectLength);
                ASSERT1(length2 == expectLength);
                ASSERT1(length3 == expectLength);
            }
        };
        check({0}, 1);
        check({0, 0}, 1);
        check({0, 1}, 2);
        check({1, 0}, 2);
        check({0, 2}, 1);
        check({0, 1, 2}, 3);
        check({0, 1, 3}, 2);
        check({-1, 1, 2}, 2);
        check({0, -1, 2}, 2);
        check({3, 1, 2}, 3);
        check({0, 1, 1}, 2);
        check({1, 0, 1, 1}, 2);
        check({1, 0, 1, 0}, 2);
        check({1, 0, -1}, 3);
        check({0, 1, 2, 1}, 3);
        check({-7, -1, 3, -9, -4, 7, -3, 2, 4, 9, 4, -9, 8, -7, 5, -1, -7}, 4);
        check({-6, 8, -5, 7, -9, -1, -7, -6, -9, -7, 5, 7, -1, -8, -8, -2, 0},
              5);
        check({1, 2, 3, 4, 5, 3, 2, 1}, 5);
        check({2, 1, 3, -1, 0, -2, 1}, 6);
        check({6, 5, 3, 4, 2, 5, 3, 4, 6}, 5);
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(200);
            vector<int> input = Random::Vector(n, 50, -50);
            check(input, 0, true);
        }
    });
}
#endif