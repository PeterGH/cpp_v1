#ifndef _STRINGTEST_H_
#define _STRINGTEST_H_

#include "String.h"
#include "Test.h"

using namespace Test;

class StringTest : public TestClass
{
public:
    StringTest(Log &log) : TestClass(log) {}
    ~StringTest(void) {}
    void Init(void);
};

void StringTest::Init(void)
{
    Add("Join", [&]() {
        {
            int i[] = {0, 1, 2, 3};
            string o1 = Test::String::Join(i, 4, ":");
            Logger().WriteInformation("%s\n", o1.c_str());
            ASSERT1(0 == strcmp("0:1:2:3", o1.c_str()));

            wstring o2 = Test::String::Join(i, 4, L":");
            Logger().WriteInformation("%S\n", o2.c_str());
            ASSERT1(0 == wcscmp(L"0:1:2:3", o2.c_str()));
        }
        {
            double i[] = {0.1, 1.2, 2.3, 3.4};
            string o1 = Test::String::Join(i, 4, ":");
            Logger().WriteInformation("%s\n", o1.c_str());
            ASSERT1(0 == strcmp("0.1:1.2:2.3:3.4", o1.c_str()));

            wstring o2 = Test::String::Join(i, 4, L":");
            Logger().WriteInformation("%S\n", o2.c_str());
            ASSERT1(0 == wcscmp(L"0.1:1.2:2.3:3.4", o2.c_str()));
        }
        {
            vector<int> i = {0, 1, 2, 3};
            string o1 = Test::String::Join(i, ":");
            Logger().WriteInformation("%s\n", o1.c_str());
            ASSERT1(0 == strcmp("0:1:2:3", o1.c_str()));

            wstring o2 = Test::String::Join(i, L":");
            Logger().WriteInformation("%S\n", o2.c_str());
            ASSERT1(0 == wcscmp(L"0:1:2:3", o2.c_str()));
        }
        {
            vector<double> i = {0.1, 1.2, 2.3, 3.4};
            string o1 = Test::String::Join(i, ":");
            Logger().WriteInformation("%s\n", o1.c_str());
            ASSERT1(0 == strcmp("0.1:1.2:2.3:3.4", o1.c_str()));

            wstring o2 = Test::String::Join(i, L":");
            Logger().WriteInformation("%S\n", o2.c_str());
            ASSERT1(0 == wcscmp(L"0.1:1.2:2.3:3.4", o2.c_str()));
        }
    });
}

#endif