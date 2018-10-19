#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <algorithm>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace Test
{
class Random
{
  public:
    static int Int(int max = RAND_MAX, int min = 0)
    {
        return min + (rand() % (max - min + 1));
    }

    static vector<int> Vector(size_t n, int max = RAND_MAX, int min = 0)
    {
        vector<int> result(n);
        std::generate(result.begin(), result.end(), [&]() { return Int(max, min); });
        return result;
    }
};
} // namespace Test

#endif