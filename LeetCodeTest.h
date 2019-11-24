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
}
#endif