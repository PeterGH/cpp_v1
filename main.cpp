#include <iostream>
#include "Argument.h"
#include "Log.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Test::Argument<char> arg(argc, argv);

    Test::Log log;
    log << arg.ToString() << endl;
    log.WriteError("haha %d\n", 1);
    log << "Another one" << endl
        << "Third" << endl;

    const wchar_t *wargv[6] = { L"-key1", L"value1", L"-key2", L"-key3", L"value3", L"value4"};

    Test::Argument<wchar_t> warg(6, wargv);

    wcout << warg.ToString() << endl;
    return 0;
}