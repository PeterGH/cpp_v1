#include "Argument.h"
#include "Log.h"
#include <iostream>
//#include "AlgorithmTest.h"
#include "ArgumentTest.h"
//#include "ArrayTest.h"
#include "CppTest.h"
#include "LeetCodeTest.h"
#include "LogTest.h"
#include "StringTest.h"
//#include "StructureTest.h"

using namespace std;

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        cout << argv[0] << " -l" << endl;
        cout << "\tList all tests." << endl;
        cout << argv[0] << " test -l" << endl;
        cout << "\tList all test methods of a test." << endl;
        cout << argv[0] << " -a" << endl;
        cout << "\tRun all tests." << endl;
        cout << argv[0] << " test" << endl;
        cout << "\tRun all test methods of a test." << endl;
        cout << argv[0] << " test method" << endl;
        cout << "\tRun a specific method of a test." << endl;
        return -1;
    }

    Argument<char> arg(argc, argv);

    Log log(cout, arg.Has("v") ? Log::Level::Verbose : Log::Level::Warning);
    TestSuite suite(log);
    // suite.Add(new AlgorithmTest(log));
    suite.Add(new ArgumentTest(log));
    // suite.Add(new ArrayTest(log));
    suite.Add(new CppTest(log));
    suite.Add(new LeetCodeTest(log));
    suite.Add(new LogTest(log));
    suite.Add(new StringTest(log));
    // suite.Add(new StructureTest(log));

    if (arg.Has("l")) {
        if (arg.IndexedArgCount() <= 1) {
            cout << "Available tests are:" << endl;
            suite.List();
        } else {
            for (size_t i = 1; i < arg.IndexedArgCount(); i++) {
                suite.List(arg[i]);
            }
        }
    } else if (arg.Has("a")) {
        suite.Run();
        suite.Report();
    } else if (arg.IndexedArgCount() > 1) {
        if (arg.IndexedArgCount() == 2)
            suite.Run(arg[1]);
        else
            suite.Run(arg[1], arg[2]);
        suite.Report();
    }
    return 0;
}