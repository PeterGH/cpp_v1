#ifndef _LOGTEST_H_
#define _LOGTEST_H_

#include "Test.h"

using namespace Test;

class LogTest : public TestClass
{
  public:
    LogTest(Log &log) : TestClass(log) {}
    ~LogTest(void) {}
    void Init(void);
};

void LogTest::Init(void)
{
    Add("Write", [&]() {
        {
            ostringstream oss;
            Log log(oss);
            log.WriteError("Error %d", 1);
            ASSERT1(0 == oss.str().compare("Error: Error 1"));
        }
        {
            ostringstream oss;
            Log log(oss);
            log.WriteWarning("Warning %d", 2);
            ASSERT1(0 == oss.str().compare("Warning: Warning 2"));
        }
        {
            ostringstream oss;
            Log log(oss);
            log.WriteInformation("Information %d", 3);
            ASSERT1(0 == oss.str().compare("Information 3"));
        }
        {
            ostringstream oss;
            Log log(oss);
            log.WriteVerbose("Verbose %d", 4);
            ASSERT1(0 == oss.str().compare(""));
        }
        {
            ostringstream oss;
            Log log(oss, Log::Level::Verbose);
            log.WriteVerbose("Verbose %d", 5);
            ASSERT1(0 == oss.str().compare("Verbose 5"));
        }
    });

    Add("Operator", [&]() {
        Log log;
        log << "This is a line." << endl;
        log << "A pair " << make_pair("key", 123) << endl;
        log << "A vector " << vector<int>{1, 2, 3, 4, 5} << endl;
        log << "A grid " << vector<vector<int>>{{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9}}
            << endl;
        log << "A map " << map<string, vector<vector<int>>>{{"key1", {{1, 2}, {3, 4}}}, {"key2", {{5, 6}, {7, 8}}}}
            << endl;
    });
}

#endif