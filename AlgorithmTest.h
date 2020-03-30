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
    Add("BinarySearch", [&]() {
        auto check = [&](const vector<int> &v, int t) {
            Logger() << "Search " << t << " in " << v;
            int i = BinarySearch(v, t);
            int i2 = BinarySearch2(v, t);
            int i2_2 = BinarySearch2_2(v, t);
            int i3 = BinarySearch3(v, t);
            Logger() << "at " << i << ", " << i2 << ", " << i2_2 << ", " << i3
                     << endl;
            if (i == -1) {
                ASSERT1(i2 == -1);
                ASSERT1(i2_2 == -1);
                ASSERT1(i3 == -1);
            } else {
                ASSERT1(v[i] == t);
                ASSERT1(v[i2] == t);
                ASSERT1(v[i2_2] == t);
                ASSERT1(v[i3] == t);
            }
        };
        for (int i = 0; i < 100; i++) {
            int n = Random::Int(100);
            vector<int> v = Random::Vector(n, 50);
            sort(v.begin(), v.end());
            check(v, -10);
            set<int> s;
            for (int e : v) {
                if (s.find(e) == s.end()) {
                    check(v, e);
                    s.insert(e);
                }
            }
            check(v, 100);
        }
    });

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