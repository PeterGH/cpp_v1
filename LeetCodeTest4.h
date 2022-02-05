#ifndef _LEETCODETEST4_H_
#define _LEETCODETEST4_H_

#include "LeetCodeTest.h"

void LeetCodeTest::Init4(void)
{
    Add("407. Trapping Rain Water II", [&]()
        {
            auto check = [&](const vector<vector<int>> &map, int expected)
            {
                Logger() << map;
                int volume = trapRainWater(map);
                Logger() << "volume = " << volume << ", " << expected << endl;
                ASSERT1(volume == expected);
            };
            check({{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}}, 4);
        });
}
#endif