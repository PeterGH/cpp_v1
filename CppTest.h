#ifndef _CPPTEST_H_
#define _CPPTEST_H_

#include "Test.h"

using namespace Test;

class CppTest : public TestClass
{
public:
    CppTest(Log &log) : TestClass(log) {}
    ~CppTest(void) {}
    void Init(void);
};

void CppTest::Init(void)
{
    Add("ComparePair", [&]() {
        auto check = [&](pair<int, int> p0, pair<int, int> p1, char expect) {
            char e;
            if (p0 < p1)
                e = '<';
            else if (p0 == p1)
                e = '=';
            else
                e = '>';
            Logger().WriteInformation("<%d,%d> %c <%d,%d>\n", p0.first, p0.second, e, p1.first, p1.second);
            ASSERT1(e == expect);
        };
        check(make_pair(-1, -1), make_pair(-1, -1), '=');
        check(make_pair(-1, -2), make_pair(-1, -3), '>');
        check(make_pair(-1, -4), make_pair(-1, -2), '<');
        check(make_pair(-2, -1), make_pair(-1, -1), '<');
        check(make_pair(-1, -1), make_pair(-2, -1), '>');
        check(make_pair(0, 0), make_pair(0, 0), '=');
        check(make_pair(0, -1), make_pair(0, 1), '<');
        check(make_pair(0, 1), make_pair(0, -1), '>');
        check(make_pair(1, 0), make_pair(-1, 0), '>');
        check(make_pair(-1, 0), make_pair(1, 0), '<');
    });
}

#endif
