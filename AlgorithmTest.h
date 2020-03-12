#ifndef _ALGORITHMTEST_H_
#define _ALGORITHMTEST_H_

#include "Algorithm.h"
#include "Test.h"
#include "Util.h"
#include <limits.h>

using namespace Test;

class AlgorithmTest : public TestClass {
  public:
    AlgorithmTest(Log &log) : TestClass(log) {}
    ~AlgorithmTest(void) {}
    void Init(void);
};

void AlgorithmTest::Init(void) {
    Add("KMP", [&]() {
        for (int i = 0; i < 50; i++) {
            Logger().WriteInformation("Run %d\n", i);
            string pattern = Random::String(1 + rand() % 10, string("abc"));
            string input = Random::String(1 + rand() % 1000, string("abc"));
            KMP kmp(pattern.c_str());
            kmp.Print();
            vector<int> indices =
                kmp.SearchString(input.c_str(), strlen(input.c_str()));
            printf("Pattern: %s\n", pattern.c_str());
            printf("Input: %s\n", input.c_str());
            for_each(indices.begin(), indices.end(), [&](int i) {
                printf("Found a match at index %d\n", i);
                ASSERT1(input.substr(i, pattern.size()) == pattern);
            });
        }
    });
}

#endif