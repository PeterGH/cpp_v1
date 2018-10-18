#ifndef _ARGUMENTTEST_H_
#define _ARGUMENTTEST_H_

#include "Argument.h"
#include "Test.h"

using namespace Test;

class ArgumentTest : public TestClass
{
  public:
    ArgumentTest(Log &log) : TestClass(log) {}
    ~ArgumentTest(void) {}
    void Init(void);
};

void ArgumentTest::Init(void)
{
    Add("wchar_t", [&]() {
        const wchar_t *wargv[6] = { L"-key1", L"value1", L"-key2", L"-key3", L"value3", L"value4"};
        Argument<wchar_t> warg(6, wargv);
        wstring str = warg.ToString();
        ASSERT1(0 == str.compare(L"-key1 value1 -key2  -key3 value3 value4"));
    });
}
#endif