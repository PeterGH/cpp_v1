#ifndef _LEETCODETEST4_H_
#define _LEETCODETEST4_H_

#include "LeetCodeTest.h"

void LeetCodeTest::Init4(void)
{
    Add("407. Trapping Rain Water II", [&]()
        { auto check = [&](const vector<vector<int>> &map, int expected)
          {
              Logger() << map;
              int volume = trapRainWater(map);
              int volume2 = trapRainWater2(map);
              int volume3 = trapRainWater3(map);
              Logger() << "volume = " << volume << ", " << volume2 << ", " << volume3 << ", " << expected << endl;
              if (expected < 0)
              {
                  ASSERT1(volume == volume2);
                  ASSERT1(volume == volume3);
              }
              else
              {
                  ASSERT1(volume == expected);
                  ASSERT1(volume2 == expected);
                  ASSERT1(volume3 == expected);
              };
          };
          check({{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}}, 4); });
}
#endif