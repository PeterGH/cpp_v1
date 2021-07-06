#ifndef _LEETCODETEST6_H_
#define _LEETCODETEST6_H_

#include "LeetCodeTest.h"

void LeetCodeTest::Init6(void)
{
    Add("658. Find K Closest Elements", [&]()
        {
            auto check = [&](const vector<int> &v, int k, int x)
            {
                Logger() << v;
                Logger() << "Find " << k << " closest elements of " << x << ":"
                         << endl;
                vector<int> r = findClosestElements(v, k, x);
                Logger() << r;
            };
            check({1, 2, 3, 4, 5}, 4, -1);
        });
}
#endif