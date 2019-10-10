#ifndef _ALGORITHMTEST_H_
#define _ALGORITHMTEST_H_

#include "Algorithm.h"
#include "Test.h"

using namespace Test;

class AlgorithmTest : public TestClass
{
public:
    AlgorithmTest(Log &log) : TestClass(log) {}
    ~AlgorithmTest(void) {}
    void Init(void);
};

void AlgorithmTest::Init(void)
{
    Add("LongestStringWithKeystrokes", [&]() {
        unsigned long long expect[100] = {
            1, 2, 3, 4, 5, 6, 7, 9, 12, 16,
            20, 25, 30, 36, 48, 64, 80, 100, 125, 150,
            192, 256, 320, 400, 500, 625, 768, 1024, 1280, 1600,
            2000, 2500, 3125, 4096, 5120, 6400, 8000, 10000, 12500, 16384,
            20480, 25600, 32000, 40000, 50000, 65536, 81920, 102400, 128000, 160000,
            200000, 262144, 327680, 409600, 512000, 640000, 800000, 1048576, 1310720, 1638400,
            2048000, 2560000, 3200000, 4194304, 5242880, 6553600, 8192000, 10240000, 12800000, 16777216,
            20971520, 26214400, 32768000, 40960000, 51200000, 67108864, 83886080, 104857600, 131072000, 163840000,
            204800000, 268435456, 335544320, 419430400, 524288000, 655360000, 819200000, 1073741824, 1342177280, 1677721600,
            2097152000, 2621440000, 3276800000, 4294967296, 5368709120, 6710886400, 8388608000, 10485760000, 13107200000, 17179869184};
        unsigned long long actual[100];
        LongestStringWithKeystrokes(100, actual);
        for (int i = 0; i < 100; i++)
        {
            Logger().WriteInformation("%d: %llu %s %llu\n", i + 1, actual[i], actual[i] == expect[i] ? "==" : "!=", expect[i]);
            ASSERT1(actual[i] == expect[i]);
        }
    });

    Add("Knapsack", [&]() {
		{
			vector<pair<int, int>> items;
			items.push_back(make_pair(60, 2));
			items.push_back(make_pair(100, 4));
			items.push_back(make_pair(120, 6));
			Matrix<int> values(3, 11);
			Knapsack::PrintSolution(items, values);
		}
		{
			vector<pair<int, int>> items;
			items.push_back(make_pair(60, 2));
			items.push_back(make_pair(100, 2));
			items.push_back(make_pair(120, 6));
			Matrix<int> values(3, 11);
			Knapsack::ComputeValues(items, values);
			Knapsack::PrintSolution(items, values);
		}
	});

}

#endif