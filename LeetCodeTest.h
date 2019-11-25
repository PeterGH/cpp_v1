#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "Test.h"
#include "Util.h"

using namespace Test;
using namespace Test::LeetCode;

class LeetCodeTest : public TestClass
{
public:
    LeetCodeTest(Log &log) : TestClass(log) {}
    ~LeetCodeTest(void) {}
    void Init(void);
};

void LeetCodeTest::Init(void)
{
    Add("3. Longest Substring Without Repeating Characters", [&]() {
        auto check = [&](const string &s, int el) {
            int l = lengthOfLongestSubstring(s);
            int l2 = lengthOfLongestSubstring2(s);
            int l3 = lengthOfLongestSubstring3(s);
            Logger().WriteInformation(
                "%s, %d%s%d, %d%s%d, %d%s%d\n",
                s.c_str(),
                l,
                l == el ? "==" : "!=",
                el,
                l2,
                l2 == el ? "==" : "!=",
                el,
                l3,
                l3 == el ? "==" : "!=",
                el);
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
        for (int i = 0; i < 100; i++)
        {
            size_t len = 1 + (rand() % 100);
            string s = Random::String(len);
            int l = lengthOfLongestSubstring(s);
            int l2 = lengthOfLongestSubstring2(s);
            int l3 = lengthOfLongestSubstring3(s);
            Logger().WriteInformation(
                "%s, %d%s%d, %d%s%d, %d%s%d\n",
                s.c_str(),
                l,
                l == l2 ? "==" : "!=",
                l2,
                l2,
                l2 == l3 ? "==" : "!=",
                l3,
                l3,
                l3 == l ? "==" : "!=",
                l);
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
            Logger() << s << ", '" << p << "', '" << p2 << "', '" << p3 << "', '" << p4 << "'" << endl;
            if (es.empty())
            {
                ASSERT1(p == p2);
                ASSERT1(p == p3);
                ASSERT1(p == p4);
            }
            else
            {
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
        for (int i = 0; i < 100; i++)
        {
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
            if (es.empty())
            {
                ASSERT1(z == z2);
            }
            else
            {
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
        for (int i = 0; i < 100; i++)
        {
            size_t len = 1 + (rand() % 50);
            string s = Random::String(len);
            for (int r = 1; r <= (int)s.size(); r++)
            {
                check(s, r);
            }
        }
    });
}
#endif