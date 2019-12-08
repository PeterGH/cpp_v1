#ifndef _STRINGTEST_H_
#define _STRINGTEST_H_

#include "String.h"
#include "Test.h"
#include <string.h>

using namespace Test;

class StringTest : public TestClass {
  public:
    StringTest(Log &log) : TestClass(log) {}
    ~StringTest(void) {}
    void Init(void);
};

void StringTest::Init(void) {
    Add("Empty<char>", [&]() {
        string e = String::Empty<char>();
        cout << e << " len: " << e.length() << endl;
        ASSERT1(e == "");
        string s;
        ASSERT1(e == s);
    });

    Add("Empty<wchar_t>", [&]() {
        wstring e = String::Empty<wchar_t>();
        wcout << e << L" len: " << e.length() << endl;
        ASSERT1(e == L"");
        wstring s;
        ASSERT1(e == s);
    });

    Add("ToLower<char>", [&]() {
        string i = "AFf34z df  g3zds^(%98FSDSFE";
        char *pi = (char *)i.c_str();
        cout << i << ": len " << strlen(pi) << endl;
        string o = String::ToLower(i);
        cout << o << ": len " << o.length() << endl;
        ASSERT2(0 == o.compare("aff34z df  g3zds^(%98fsdsfe"),
                String::Format("o = %s", o));
    });

    Add("ToLower<wchar_t>", [&]() {
        wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
        wchar_t *pi = (wchar_t *)i.c_str();
        wcout << i << L": len " << wcslen(pi) << endl;
        wstring o = String::ToLower(i);
        wcout << o << L": len " << o.length() << endl;
        ASSERT2(0 == o.compare(L"aff34z df  g3zds^(%98fsdsfe"),
                String::ToString(String::Format(L"o = %s", o)));
    });

    Add("ToWString(char *)", [&]() {
        string i = "AFf34z df  g3zds^(%98FSDSFE";
        char *pi = (char *)i.c_str();
        cout << i << ": len " << strlen(pi) << endl;
        wstring o = String::ToWString(pi);
        pi = (char *)o.c_str();
        wcout << o << ": len " << o.size() << ": clen " << strlen(pi) << endl;
        ASSERT2(0 == o.compare(L"AFf34z df  g3zds^(%98FSDSFE"),
                String::Format("o = %s", o));
    });

    Add("ToString(wchar_t *)", [&]() {
        wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
        wchar_t *pi = (wchar_t *)i.c_str();
        wcout << i << ": len " << wcslen(pi) << endl;
        string o = String::ToString(pi);
        char *p = (char *)o.c_str();
        cout << o << ": len " << strlen(p) << endl;
        ASSERT2(0 == o.compare("AFf34z df  g3zds^(%98FSDSFE"),
                String::Format("o = %s", o));
    });

    Add("ToString(wstring)", [&]() {
        wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
        string o = String::ToString(i);
        ASSERT2(o == "AFf34z df  g3zds^(%98FSDSFE",
                String::Format("o = %s", o));
    });

    Add("ToWString(string)", [&]() {
        string i = "AFf34z df  g3zds^(%98FSDSFE";
        wstring o = String::ToWString(i);
        ASSERT2(o == L"AFf34z df  g3zds^(%98FSDSFE",
                String::Format("o = %s", String::ToString(o)));
    });

    Add("Format(char *)", [&]() {
        string s = String::Format("Hello World!");
        cout << s << endl;
        ASSERT2(s == "Hello World!", String::Format("s = %s", s));
        s = String::Format("Hello %s!", "Peter");
        cout << s << endl;
        ASSERT2(s == "Hello Peter!", String::Format("s = %s", s));
        s = String::Format("Hello %s! You are %d years old.", "Peter", 18);
        cout << s << endl;
        ASSERT2(s == "Hello Peter! You are 18 years old.",
                String::Format("s = %s", s));
    });

    Add("Format(wchar_t *)", [&]() {
        wstring s = String::Format(L"Hello World!");
        wcout << s << endl;
        ASSERT2(s == L"Hello World!",
                String::Format("s = %s", String::ToString(s)));
        s = String::Format(L"Hello %s!", L"Peter");
        wcout << s << endl;
        ASSERT2(s == L"Hello Peter!",
                String::Format("s = %s", String::ToString(s)));
        s = String::Format(L"Hello %s! You are %d years old.", L"Peter", 18);
        wcout << s << endl;
        ASSERT2(s == L"Hello Peter! You are 18 years old.",
                String::Format("s = %s", String::ToString(s)));
    });

    Add("StartsWith<char>", [&]() {
        string s1 = "Hello World!";
        string s2 = "Hello";
        ASSERT1(String::StartsWith(s1, s2));
        s2 = "hello w";
        ASSERT1(String::StartsWith(s1, s2));
        s2 = "World";
        ASSERT1(!String::StartsWith(s1, s2));
        s2 = "Hellow World! Great!";
        ASSERT1(!String::StartsWith(s1, s2));
        s2 = "";
        ASSERT1(String::StartsWith(s1, s2));
        s1 = "";
        s2 = "Hello";
        ASSERT1(!String::StartsWith(s1, s2));
    });

    Add("StartsWith<wchar_t>", [&]() {
        wstring s1 = L"Hello World!";
        wstring s2 = L"Hello";
        ASSERT1(String::StartsWith(s1, s2));
        s2 = L"hello w";
        ASSERT1(String::StartsWith(s1, s2));
        s2 = L"World";
        ASSERT1(!String::StartsWith(s1, s2));
        s2 = L"Hellow World! Great!";
        ASSERT1(!String::StartsWith(s1, s2));
        s2 = L"";
        ASSERT1(String::StartsWith(s1, s2));
        s1 = L"";
        s2 = L"Hello";
        ASSERT1(!String::StartsWith(s1, s2));
    });

    Add("EndsWith<char>", [&]() {
        string s1 = "Hello World!";
        string s2 = "Hello";
        ASSERT1(!String::EndsWith(s1, s2));
        s2 = "!";
        ASSERT1(String::EndsWith(s1, s2));
        s2 = "world!";
        ASSERT1(String::EndsWith(s1, s2));
        s2 = "Hellow World! Great!";
        ASSERT1(!String::EndsWith(s1, s2));
        s2 = "";
        ASSERT1(String::EndsWith(s1, s2));
        s1 = "";
        s2 = "Hello";
        ASSERT1(!String::EndsWith(s1, s2));
    });

    Add("EndsWith<wchar_t>", [&]() {
        wstring s1 = L"Hello World!";
        wstring s2 = L"Hello";
        ASSERT1(!String::EndsWith(s1, s2));
        s2 = L"!";
        ASSERT1(String::EndsWith(s1, s2));
        s2 = L"world!";
        ASSERT1(String::EndsWith(s1, s2));
        s2 = L"Hellow World! Great!";
        ASSERT1(!String::EndsWith(s1, s2));
        s2 = L"";
        ASSERT1(String::EndsWith(s1, s2));
        s1 = L"";
        s2 = L"Hello";
        ASSERT1(!String::EndsWith(s1, s2));
    });

    Add("Contains<char>", [&]() {
        string s1 = "Hello World!";
        ASSERT1(String::Contains(s1, s1));
        string s2 = "Hello";
        ASSERT1(String::Contains(s1, s2));
        s2 = "ello w";
        ASSERT1(String::Contains(s1, s2));
        s2 = "World";
        ASSERT1(String::Contains(s1, s2));
        s2 = "Hellow World! Great!";
        ASSERT1(!String::Contains(s1, s2));
        s2 = " ";
        ASSERT1(String::Contains(s1, s2));
        s2 = "";
        ASSERT1(String::Contains(s1, s2));
        s2 = "  ";
        ASSERT1(!String::Contains(s1, s2));
    });

    Add("Contains<wchar_t>", [&]() {
        wstring s1 = L"Hello World!";
        ASSERT1(String::Contains(s1, s1));
        wstring s2 = L"Hello";
        ASSERT1(String::Contains(s1, s2));
        s2 = L"ello w";
        ASSERT1(String::Contains(s1, s2));
        s2 = L"World";
        ASSERT1(String::Contains(s1, s2));
        s2 = L"Hellow World! Great!";
        ASSERT1(!String::Contains(s1, s2));
        s2 = L" ";
        ASSERT1(String::Contains(s1, s2));
        s2 = L"";
        ASSERT1(String::Contains(s1, s2));
        s2 = L"  ";
        ASSERT1(!String::Contains(s1, s2));
    });

    Add("TrimStart<wchar_t>", [&]() {
        wstring s1 = L"  Hello World!*X&&**";
        wstring s2 = String::TrimStart(s1, L" ");
        wcout << s2 << endl;
        ASSERT1(s2 == L"Hello World!*X&&**");
        wstring s3 = String::TrimStart(s2, L" ");
        wcout << s3 << endl;
        ASSERT1(s3 == s2);
        wstring s4 = String::TrimStart(s3, L"Hello ");
        wcout << s4 << endl;
        ASSERT1(s4 == L"World!*X&&**");
        wstring s5 = String::TrimStart<wchar_t>(L"", L"H");
        ASSERT1(s5 == L"");
    });

    Add("TrimStart<char>", [&]() {
        string s1 = "  Hello World!*X&&**";
        string s2 = String::TrimStart(s1, " ");
        cout << s2 << endl;
        ASSERT1(s2 == "Hello World!*X&&**");
        string s3 = String::TrimStart(s2, " ");
        cout << s3 << endl;
        ASSERT1(s3 == s2);
        string s4 = String::TrimStart(s3, "Hello ");
        cout << s4 << endl;
        ASSERT1(s4 == "World!*X&&**");
        string s5 = String::TrimStart<char>("", "H");
        ASSERT1(s5 == "");
    });

    Add("TrimEnd<wchar_t>", [&]() {
        wstring s1 = L"  Hello World!*X&&**";
        wstring s2 = String::TrimEnd(s1, L" ");
        wcout << s2 << endl;
        ASSERT1(s2 == s1);
        wstring s3 = String::TrimEnd(s2, L"*&");
        wcout << s3 << endl;
        ASSERT1(s3 == L"  Hello World!*X");
        wstring s4 = String::TrimEnd(s3, L" World!*X");
        wcout << s4 << endl;
        ASSERT1(s4 == L"  He");
        wstring s5 = String::TrimEnd<wchar_t>(L"", L"*");
        ASSERT1(s5 == L"");
    });

    Add("TrimEnd<char>", [&]() {
        string s1 = "  Hello World!*X&&**";
        string s2 = String::TrimEnd(s1, " ");
        cout << s2 << endl;
        ASSERT1(s2 == s1);
        string s3 = String::TrimEnd(s2, "*&");
        cout << s3 << endl;
        ASSERT1(s3 == "  Hello World!*X");
        string s4 = String::TrimEnd(s3, " World!*X");
        cout << s4 << endl;
        ASSERT1(s4 == "  He");
        string s5 = String::TrimEnd<char>("", "*");
        ASSERT1(s5 == "");
    });

    Add("Trim<wchar_t>", [&]() {
        wstring s1 = L"  Hello World!*X&&**";
        wstring s2 = String::Trim(s1, L" ");
        wcout << s2 << endl;
        ASSERT1(s2 == L"Hello World!*X&&**");
        wstring s3 = String::Trim(s2, L" ");
        wcout << s3 << endl;
        ASSERT1(s3 == s2);
        wstring s4 = String::Trim(s3, L"*&H");
        wcout << s4 << endl;
        ASSERT1(s4 == L"ello World!*X");
        wstring s5 = String::Trim<wchar_t>(L"", L" *");
        ASSERT1(s5 == L"");
    });

    Add("Trim<char>", [&]() {
        string s1 = "  Hello World!*X&&**";
        string s2 = String::Trim(s1, " ");
        cout << s2 << endl;
        ASSERT1(s2 == "Hello World!*X&&**");
        string s3 = String::Trim(s2, " ");
        cout << s3 << endl;
        ASSERT1(s3 == s2);
        string s4 = String::Trim(s3, "*&H");
        cout << s4 << endl;
        ASSERT1(s4 == "ello World!*X");
        string s5 = String::Trim<char>("", " *");
        ASSERT1(s5 == "");
    });

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