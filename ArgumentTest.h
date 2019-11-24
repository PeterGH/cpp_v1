#ifndef _ARGUMENTTEST_H_
#define _ARGUMENTTEST_H_

#include "Argument.h"
#include "String.h"
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
        const wchar_t *wargv[6] = {L"-key1", L"value1", L"-key2", L"-key3", L"value3", L"value4"};
        Argument<wchar_t> warg(6, wargv);
        wstring str = warg.ToString();
        ASSERT1(0 == str.compare(L"-key1 value1 -key2  -key3 value3 value4"));
    });

    Add("Argument_char", [&]() {
        int argc = 9;
        const char *argv[] = {"Test.exe", "I1", "I2", "-K1", "V1", "-K2", "-K3", "V3", "I3"};
        Argument<char> arg(argc, argv);
        cout << arg.ToString() << endl;
        ASSERT2(arg.NamedArgCount() == 3, String::Format("arg.NamedArgCount() = %d", arg.NamedArgCount()));
        ASSERT2(arg.IndexedArgCount() == 4, String::Format("arg.IndexedArgCount() = %d", arg.IndexedArgCount()));
        ASSERT2(arg.Count() == 7, String::Format("arg.Count() == %d", arg.Count()));
        ASSERT1(arg.Has(3));
        ASSERT2(arg[3] == "I3", String::Format("arg[s] = %s", arg[3]));
        ASSERT1(!arg.Has(4));
        ASSERTERROR(arg[4], std::invalid_argument);
        ASSERT1(arg.Has("K2"));
        ASSERT2(arg["K2"] == "", String::Format("arg[\"K2\"] = %s", arg["K2"]));
        ASSERT1(arg.Has("K3"));
        ASSERT2(arg["K3"] == "V3", String::Format("arg[\"K3\"] = %s", arg["K3"]));
        ASSERT1(!arg.Has("K4"));
        ASSERTERROR(arg["K4"], invalid_argument);
    });

    Add("Keys_char", [&]() {
        int argc = 9;
        const char *argv[9] = {"Test.exe", "I1", "I2", "-K1", "V1", "-K2", "-K3", "V3", "I3"};
        Argument<char> arg(argc, argv);
        cout << arg.ToString() << endl;
        set<string> keys = arg.Keys();
        ASSERT2(keys.size() == 3, String::Format("keys.size() = %d", keys.size()));
        set<string>::iterator it;
        string k[] = {"k1", "k2", "k3"};
        for (unsigned int i = 0; i < 3; i++)
        {
            ASSERT1(arg.Has(k[i]));
            it = keys.find(k[i]);
            ASSERT2(it != keys.end(), String::Format("%s is not found", k[i]));
        }
    });

    Add("Argument_wchar_t", [&]() {
        int argc = 9;
        const wchar_t *argv[9] = {L"Test.exe", L"I1", L"I2", L"-K1", L"V1", L"-K2", L"-K3", L"V3", L"I3"};
        Argument<wchar_t> arg(argc, argv);
        wcout << arg.ToString() << endl;
        ASSERT2(arg.NamedArgCount() == 3, String::Format("arg.NamedArgCount() = %d", arg.NamedArgCount()));
        ASSERT2(arg.IndexedArgCount() == 4, String::Format("arg.IndexedArgCount() = %d", arg.IndexedArgCount()));
        ASSERT2(arg.Count() == 7, String::Format("arg.Count() == %d", arg.Count()));
        ASSERT1(arg.Has(3));
        wcout << arg[3] << endl;
        ASSERT1(arg[3] == L"I3");
        ASSERT1(!arg.Has(4));
        ASSERTERROR(arg[4], std::invalid_argument);
        ASSERT1(arg.Has(L"K2"));
        wcout << L"arg[L\"K2\"] = " << arg[L"K2"] << endl;
        ASSERT1(arg[L"K2"] == L"");
        ASSERT1(arg.Has(L"K3"));
        wcout << L"arg[L\"K3\"] = " << arg[L"K2"] << endl;
        ASSERT1(arg[L"K3"] == L"V3");
        ASSERT1(!arg.Has(L"K4"));
        ASSERTERROR(arg[L"K4"], invalid_argument);
    });

    Add("Keys_wchar_t", [&]() {
        int argc = 9;
        const wchar_t *argv[9] = {L"Test.exe", L"I1", L"I2", L"-K1", L"V1", L"-K2", L"-K3", L"V3", L"I3"};
        Argument<wchar_t> arg(argc, argv);
        wcout << arg.ToString() << endl;
        set<wstring> keys = arg.Keys();
        ASSERT2(keys.size() == 3, String::Format("keys.size() = %d", keys.size()));
        set<wstring>::iterator it;
        wstring k[] = {L"k1", L"k2", L"k3"};
        for (unsigned int i = 0; i < 3; i++)
        {
            ASSERT1(arg.Has(k[i]));
            it = keys.find(k[i]);
            ASSERT2(it != keys.end(), String::Format("%s is not found", k[i]));
        }
    });
}
#endif