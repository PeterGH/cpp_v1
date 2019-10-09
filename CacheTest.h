#ifndef _CACHETEST_H_
#define _CACHETEST_H_

#include "Cache.h"
#include "Test.h"

using namespace Test;

class CacheTest : public TestClass
{
public:
    CacheTest(Log &log) : TestClass(log) {}
    ~CacheTest(void) {}
    void Init(void);
};

void CacheTest::Init(void)
{
    Add("LRUCache", [&]() {
        {
            Logger().WriteInformation("Cache(1)\n");
            LRUCache cache(1);

            int v = cache.Get(0);
            ASSERT1(v == -1);

            Logger().WriteInformation("Set(1, 1)\n");
            cache.Set(1, 1);
            v = cache.Get(0);
            ASSERT1(v == -1);
            v = cache.Get(1);
            ASSERT1(v == 1);

            Logger().WriteInformation("Set(2, 2)\n");
            cache.Set(2, 2);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 2);

            Logger().WriteInformation("Set(3, 3)\n");
            cache.Set(3, 3);
            v = cache.Get(2);
            ASSERT1(v == -1);
            v = cache.Get(3);
            ASSERT1(v == 3);

            Logger().WriteInformation("Set(3, 33)\n");
            cache.Set(3, 33);
            v = cache.Get(2);
            ASSERT1(v == -1);
            v = cache.Get(3);
            ASSERT1(v == 33);
        }
        {
            Logger().WriteInformation("Cache(2)\n");
            LRUCache cache(2);

            int v = cache.Get(0);
            ASSERT1(v == -1);

            Logger().WriteInformation("Set(1, 1)\n");
            cache.Set(1, 1);
            v = cache.Get(0);
            ASSERT1(v == -1);
            v = cache.Get(1);
            ASSERT1(v == 1);

            Logger().WriteInformation("Set(2, 2)\n");
            cache.Set(2, 2);
            v = cache.Get(0);
            ASSERT1(v == -1);
            v = cache.Get(1);
            ASSERT1(v == 1);
            v = cache.Get(2);
            ASSERT1(v == 2);

            Logger().WriteInformation("Set(3, 3)\n");
            cache.Set(3, 3);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 2);
            v = cache.Get(3);
            ASSERT1(v == 3);

            v = cache.Get(2);
            ASSERT1(v == 2);

            Logger().WriteInformation("Set(4, 4)\n");
            cache.Set(4, 4);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 2);
            v = cache.Get(3);
            ASSERT1(v == -1);
            v = cache.Get(4);
            ASSERT1(v == 4);

            Logger().WriteInformation("Set(2, 22)\n");
            cache.Set(2, 22);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 22);
            v = cache.Get(3);
            ASSERT1(v == -1);
            v = cache.Get(4);
            ASSERT1(v == 4);
        }
    });
}

#endif