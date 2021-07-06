#ifndef _LEETCODETEST_H_
#define _LEETCODETEST_H_

#include "LeetCode.h"
#include "LeetCode0.h"
#include "LeetCode1.h"
#include "LeetCode2.h"
#include "LeetCode3.h"
#include "LeetCode4.h"
#include "LeetCode6.h"
#include "LeetCode7.h"
#include "Test.h"
#include "Util.h"
#include <math.h>

using namespace std;
using namespace Test;
using namespace Test::LeetCode;

class LeetCodeTest : public TestClass
{
public:
    LeetCodeTest(Log &log) : TestClass(log) {}
    ~LeetCodeTest(void) {}
    void Init(void);
    void Init0(void);
    void Init1(void);
    void Init2(void);
    void Init3(void);
    void Init6(void);
    void Init7(void);
};

void LeetCodeTest::Init(void)
{
    Init0();
    Init1();
    Init2();
    Init3();
    Init6();
    Init7();
}
#endif