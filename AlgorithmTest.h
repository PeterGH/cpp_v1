#ifndef _ALGORITHMTEST_H_
#define _ALGORITHMTEST_H_

#include "Algorithm.h"
#include "Test.h"
#include "Util.h"
#include <limits.h>

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
    Add("BinarySearch", [&]()
        {
            auto check = [&](const vector<int> &v, int t) {
                Logger() << "Search " << t << " in " << v;
                int i = BinarySearch(v, t);
                int i2 = BinarySearch2(v, t);
                int i2_2 = BinarySearch2_2(v, t);
                int i3 = BinarySearch3(v, t);
                Logger() << "at " << i << ", " << i2 << ", " << i2_2 << ", " << i3
                         << endl;
                if (i == -1)
                {
                    ASSERT1(i2 == -1);
                    ASSERT1(i2_2 == -1);
                    ASSERT1(i3 == -1);
                }
                else
                {
                    ASSERT1(v[i] == t);
                    ASSERT1(v[i2] == t);
                    ASSERT1(v[i2_2] == t);
                    ASSERT1(v[i3] == t);
                }
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100);
                vector<int> v = Random::Vector(n, 50);
                sort(v.begin(), v.end());
                check(v, -10);
                set<int> s;
                for (int e : v)
                {
                    if (s.find(e) == s.end())
                    {
                        check(v, e);
                        s.insert(e);
                    }
                }
                check(v, 100);
            } });

    Add("FindInsertPoint", [&]()
        {
            {
                for (int n = 1; n < 10; n++) {
                    vector<int> input(n, n);
                    size_t i = FindInsertPoint(input, n, 0, input.size() - 1);
                    Logger() << input;
                    Logger() << "First " << n << " should be inserted at " << i << endl;
                    ASSERT1(i == 0);
                }
            }
            {
                for (int n = 1; n < 10; n++) {
                    vector<int> input(n, n);
                    size_t i = FindInsertPoint(input, n - 1, 0, input.size() - 1);
                    Logger() << input;
                    Logger() << "First " << n - 1 << " should be inserted at " << i << endl;
                    ASSERT1(i == 0);
                }
            }
            {
                for (int n = 1; n < 10; n++) {
                    vector<int> input(n, n);
                    size_t i =
                        FindInsertPoint(input, n, 0, input.size() - 1, false);
                    Logger() << input;
                    Logger() << "Last " << n << " should be inserted at " << i << endl;
                    ASSERT1(i == input.size());
                }
            }
            {
                for (int n = 1; n < 10; n++) {
                    vector<int> input(n, n);
                    size_t i =
                        FindInsertPoint(input, n + 1, 0, input.size() - 1, false);
                    Logger() << input;
                    Logger() << "Last " << n + 1 << " should be inserted at " << i << endl;
                    ASSERT1(i == input.size());
                }
            }
            {
                int max = 50;
                for (int i = 0; i < 100; i++) {
                    vector<int> input =
                        Random::Vector(Random::Int(1000, 1), max);
                    sort(input.begin(), input.end());
                    Logger() << input;
                    for (int j = 0; j < 100; j++) {
                        int e = Random::Int(max + 10, -10);
                        size_t i = FindInsertPoint(input, e, 0, input.size() - 1);
                        Logger() << "First " << e << " should be inserted at " << i << endl;
                        ASSERT1(i >= 0);
                        ASSERT1(i <= input.size());
                        if (i < input.size())
                            ASSERT1(e <= input[i]);
                        if (i > 0)
                            ASSERT1(input[i - 1] < e);
                    }
                }
            }
            {
                int max = 50;
                for (int i = 0; i < 100; i++) {
                    vector<int> input =
                        Random::Vector(Random::Int(1000, 1), max);
                    sort(input.begin(), input.end());
                    Logger() << input;
                    for (int j = 0; j < 100; j++) {
                        int e = Random::Int(max + 10, -10);
                        size_t i =
                            FindInsertPoint(input, e, 0, input.size() - 1, false);
                        Logger() << "Last " << e << " should be inserted at " << i << endl;
                        ASSERT1(i >= 0);
                        ASSERT1(i <= input.size());
                        if (i < input.size())
                            ASSERT1(e < input[i]);
                        if (i > 0)
                            ASSERT1(input[i - 1] <= e);
                    }
                }
            } });

    Add("FindClosest", [&]()
        {
            auto check = [&](const vector<int> &v, int t) {
                Logger() << "Search " << t << " in " << v;
                int i = FindClosest(v, t);
                int i2 = FindClosest2(v, t);
                Logger() << "at " << i << ", " << i2 << endl;
                if (i == -1 || i2 == -1)
                    ASSERT1(i == i2);
                else
                    ASSERT1(v[i] == v[i2]);
            };
            for (int i = 0; i < 100; i++)
            {
                int n = Random::Int(100);
                vector<int> v = Random::Vector(n, 5000, -5000);
                sort(v.begin(), v.end());
                for (int i = 0; i < 1000; i++)
                {
                    int t = Random::Int(5000, -5000);
                    check(v, t);
                }
            } });

    Add("FindMedian", [&]()
        {
            {
                int I[] = {1,  1,  3,  3,   7,    8,    34,      35,
                           42, 43, 64, 445, 3556, 8769, 96656532};
                ASSERT1(1 == Test::FindMedian(I, 1));
                ASSERT1(1 == Test::FindMedian(I, 2));
                ASSERT1(1 == Test::FindMedian(I, 3));
                ASSERT1(1 == Test::FindMedian(I, 4));
                ASSERT1(3 == Test::FindMedian(I, 5));
                ASSERT1(3 == Test::FindMedian(I, 6));
                ASSERT1(3 == Test::FindMedian(I, 7));
                ASSERT1(3 == Test::FindMedian(I, 8));
                ASSERT1(7 == Test::FindMedian(I, 9));
                ASSERT1(7 == Test::FindMedian(I, 10));
                ASSERT1(8 == Test::FindMedian(I, 11));
                ASSERT1(8 == Test::FindMedian(I, 12));
            }
            {
                int A1[] = {0};
                int B1[] = {0};
                int m = Test::FindMedian<int>(A1, 1, B1, 1);
                ASSERT1(m == 0);
                int A2[] = {0};
                int B2[] = {1};
                m = Test::FindMedian<int>(A2, 1, B2, 1);
                ASSERT1(m == 0);
                int A3[] = {1};
                int B3[] = {0};
                m = Test::FindMedian<int>(A3, 1, B3, 1);
                ASSERT1(m == 0);
                int A4[] = {0};
                int B4[] = {0, 1};
                m = Test::FindMedian<int>(A4, 1, B4, 2);
                ASSERT1(m == 0);
                int A5[] = {1};
                int B5[] = {0, 1};
                m = Test::FindMedian<int>(A5, 1, B5, 2);
                ASSERT1(m == 1);
                int A6[] = {-1};
                int B6[] = {0, 1};
                m = Test::FindMedian<int>(A6, 1, B6, 2);
                ASSERT1(m == 0);
                int A7[] = {0};
                int B7[] = {-1, 1};
                m = Test::FindMedian<int>(A7, 1, B7, 2);
                ASSERT1(m == 0);
                int A8[] = {1};
                int B8[] = {-1, 0};
                m = Test::FindMedian<int>(A8, 1, B8, 2);
                ASSERT1(m == 0);
                int A9[] = {-1};
                int B9[] = {0, 1, 2};
                m = Test::FindMedian<int>(A9, 1, B9, 3);
                ASSERT1(m == 0);
                int A10[] = {0};
                int B10[] = {0, 1, 2};
                m = Test::FindMedian<int>(A10, 1, B10, 3);
                ASSERT1(m == 0);
                int A11[] = {1};
                int B11[] = {0, 1, 2};
                m = Test::FindMedian<int>(A11, 1, B11, 3);
                ASSERT1(m == 1);
                int A12[] = {2};
                int B12[] = {0, 1, 2};
                m = Test::FindMedian<int>(A12, 1, B12, 3);
                ASSERT1(m == 1);
                int A13[] = {3};
                int B13[] = {0, 1, 2};
                m = Test::FindMedian<int>(A13, 1, B13, 3);
                ASSERT1(m == 1);
                int A14[] = {-1};
                int B14[] = {0, 1, 2, 3};
                m = Test::FindMedian<int>(A14, 1, B14, 4);
                ASSERT1(m == 1);
                int A15[] = {0};
                int B15[] = {0, 1, 2, 3};
                m = Test::FindMedian<int>(A15, 1, B15, 4);
                ASSERT1(m == 1);
                int A16[] = {1};
                int B16[] = {0, 1, 2, 3};
                m = Test::FindMedian<int>(A16, 1, B16, 4);
                ASSERT1(m == 1);
                int A17[] = {2};
                int B17[] = {0, 1, 2, 3};
                m = Test::FindMedian<int>(A17, 1, B17, 4);
                ASSERT1(m == 2);
                int A18[] = {3};
                int B18[] = {0, 1, 2, 3};
                m = Test::FindMedian<int>(A18, 1, B18, 4);
                ASSERT1(m == 2);
                int A19[] = {4};
                int B19[] = {0, 1, 2, 3};
                m = Test::FindMedian<int>(A19, 1, B19, 4);
                ASSERT1(m == 2);
            }
            {
                int A1[] = {-3, -1};
                int B1[] = {1, 3};
                int m = Test::FindMedian<int>(A1, 2, B1, 2);
                ASSERT1(m == -1);
                int A2[] = {-3, 1};
                int B2[] = {1, 3};
                m = Test::FindMedian<int>(A2, 2, B2, 2);
                ASSERT1(m == 1);
                int A3[] = {-3, 2};
                int B3[] = {1, 3};
                m = Test::FindMedian<int>(A3, 2, B3, 2);
                ASSERT1(m == 1);
                int A4[] = {-3, 3};
                int B4[] = {1, 3};
                m = Test::FindMedian<int>(A4, 2, B4, 2);
                ASSERT1(m == 1);
                int A5[] = {-3, 4};
                int B5[] = {1, 3};
                m = Test::FindMedian<int>(A5, 2, B5, 2);
                ASSERT1(m == 1);
                int A6[] = {1, 2};
                int B6[] = {1, 3};
                m = Test::FindMedian<int>(A6, 2, B6, 2);
                ASSERT1(m == 1);
                int A7[] = {2, 2};
                int B7[] = {1, 3};
                m = Test::FindMedian<int>(A7, 2, B7, 2);
                ASSERT1(m == 2);
                int A8[] = {1, 3};
                int B8[] = {1, 3};
                m = Test::FindMedian<int>(A8, 2, B8, 2);
                ASSERT1(m == 1);
                int A9[] = {2, 3};
                int B9[] = {1, 3};
                m = Test::FindMedian<int>(A9, 2, B9, 2);
                ASSERT1(m == 2);
                int A10[] = {3, 3};
                int B10[] = {1, 3};
                m = Test::FindMedian<int>(A10, 2, B10, 2);
                ASSERT1(m == 3);
                int A11[] = {3, 4};
                int B11[] = {1, 3};
                m = Test::FindMedian<int>(A11, 2, B11, 2);
                ASSERT1(m == 3);
                int A12[] = {4, 5};
                int B12[] = {1, 3};
                m = Test::FindMedian<int>(A12, 2, B12, 2);
                ASSERT1(m == 3);
                int A13[] = {-3, -1};
                int B13[] = {1, 3, 5};
                m = Test::FindMedian<int>(A13, 2, B13, 3);
                ASSERT1(m == 1);
                int A14[] = {-3, 1};
                int B14[] = {1, 3, 5};
                m = Test::FindMedian<int>(A14, 2, B14, 3);
                ASSERT1(m == 1);
                int A15[] = {-3, 2};
                int B15[] = {1, 3, 5};
                m = Test::FindMedian<int>(A15, 2, B15, 3);
                ASSERT1(m == 2);
                int A16[] = {1, 2};
                int B16[] = {1, 3, 5};
                m = Test::FindMedian<int>(A16, 2, B16, 3);
                ASSERT1(m == 2);
                int A17[] = {2, 2};
                int B17[] = {1, 3, 5};
                m = Test::FindMedian<int>(A17, 2, B17, 3);
                ASSERT1(m == 2);
                int A18[] = {-3, 3};
                int B18[] = {1, 3, 5};
                m = Test::FindMedian<int>(A18, 2, B18, 3);
                ASSERT1(m == 3);
                int A19[] = {1, 3};
                int B19[] = {1, 3, 5};
                m = Test::FindMedian<int>(A19, 2, B19, 3);
                ASSERT1(m == 3);
                int A20[] = {2, 3};
                int B20[] = {1, 3, 5};
                m = Test::FindMedian<int>(A20, 2, B20, 3);
                ASSERT1(m == 3);
                int A21[] = {3, 3};
                int B21[] = {1, 3, 5};
                m = Test::FindMedian<int>(A21, 2, B21, 3);
                ASSERT1(m == 3);
                int A22[] = {-3, 4};
                int B22[] = {1, 3, 5};
                m = Test::FindMedian<int>(A22, 2, B22, 3);
                ASSERT1(m == 3);
                int A23[] = {1, 4};
                int B23[] = {1, 3, 5};
                m = Test::FindMedian<int>(A23, 2, B23, 3);
                ASSERT1(m == 3);
                int A24[] = {2, 4};
                int B24[] = {1, 3, 5};
                m = Test::FindMedian<int>(A24, 2, B24, 3);
                ASSERT1(m == 3);
                int A25[] = {3, 4};
                int B25[] = {1, 3, 5};
                m = Test::FindMedian<int>(A25, 2, B25, 3);
                ASSERT1(m == 3);
                int A26[] = {4, 4};
                int B26[] = {1, 3, 5};
                m = Test::FindMedian<int>(A26, 2, B26, 3);
                ASSERT1(m == 4);
                int A27[] = {-3, 5};
                int B27[] = {1, 3, 5};
                m = Test::FindMedian<int>(A27, 2, B27, 3);
                ASSERT1(m == 3);
                int A28[] = {1, 5};
                int B28[] = {1, 3, 5};
                m = Test::FindMedian<int>(A28, 2, B28, 3);
                ASSERT1(m == 3);
                int A29[] = {2, 5};
                int B29[] = {1, 3, 5};
                m = Test::FindMedian<int>(A29, 2, B29, 3);
                ASSERT1(m == 3);
                int A30[] = {3, 5};
                int B30[] = {1, 3, 5};
                m = Test::FindMedian<int>(A30, 2, B30, 3);
                ASSERT1(m == 3);
                int A31[] = {4, 5};
                int B31[] = {1, 3, 5};
                m = Test::FindMedian<int>(A31, 2, B31, 3);
                ASSERT1(m == 4);
                int A32[] = {5, 5};
                int B32[] = {1, 3, 5};
                m = Test::FindMedian<int>(A32, 2, B32, 3);
                ASSERT1(m == 5);
                int A33[] = {-3, 7};
                int B33[] = {1, 3, 5};
                m = Test::FindMedian<int>(A33, 2, B33, 3);
                ASSERT1(m == 3);
                int A34[] = {1, 7};
                int B34[] = {1, 3, 5};
                m = Test::FindMedian<int>(A34, 2, B34, 3);
                ASSERT1(m == 3);
                int A35[] = {2, 7};
                int B35[] = {1, 3, 5};
                m = Test::FindMedian<int>(A35, 2, B35, 3);
                ASSERT1(m == 3);
                int A36[] = {3, 7};
                int B36[] = {1, 3, 5};
                m = Test::FindMedian<int>(A36, 2, B36, 3);
                ASSERT1(m == 3);
                int A37[] = {4, 7};
                int B37[] = {1, 3, 5};
                m = Test::FindMedian<int>(A37, 2, B37, 3);
                ASSERT1(m == 4);
                int A38[] = {5, 7};
                int B38[] = {1, 3, 5};
                m = Test::FindMedian<int>(A38, 2, B38, 3);
                ASSERT1(m == 5);
                int A39[] = {6, 7};
                int B39[] = {1, 3, 5};
                m = Test::FindMedian<int>(A39, 2, B39, 3);
                ASSERT1(m == 5);
            }
            {
                int A1[] = {1, 4, 7};
                int B1[] = {10, 30, 50};
                int m = Test::FindMedian<int>(A1, 3, B1, 3);
                ASSERT1(m == 7);
                int A2[] = {1, 4, 10};
                int B2[] = {10, 30, 50};
                m = Test::FindMedian<int>(A2, 3, B2, 3);
                ASSERT1(m == 10);
                int A3[] = {1, 4, 17};
                int B3[] = {10, 30, 50};
                m = Test::FindMedian<int>(A3, 3, B3, 3);
                ASSERT1(m == 10);
                int A4[] = {1, 10, 17};
                int B4[] = {10, 30, 50};
                m = Test::FindMedian<int>(A4, 3, B4, 3);
                ASSERT1(m == 10);
                int A5[] = {1, 14, 17};
                int B5[] = {10, 30, 50};
                m = Test::FindMedian<int>(A5, 3, B5, 3);
                ASSERT1(m == 14);
                int A6[] = {10, 14, 17};
                int B6[] = {10, 30, 50};
                m = Test::FindMedian<int>(A6, 3, B6, 3);
                ASSERT1(m == 14);
                int A7[] = {11, 14, 17};
                int B7[] = {10, 30, 50};
                m = Test::FindMedian<int>(A7, 3, B7, 3);
                ASSERT1(m == 14);
                int A8[] = {14, 14, 17};
                int B8[] = {10, 30, 50};
                m = Test::FindMedian<int>(A8, 3, B8, 3);
                ASSERT1(m == 14);
                int A9[] = {14, 17, 17};
                int B9[] = {10, 30, 50};
                m = Test::FindMedian<int>(A9, 3, B9, 3);
                ASSERT1(m == 17);
                int A10[] = {17, 17, 17};
                int B10[] = {10, 30, 50};
                m = Test::FindMedian<int>(A10, 3, B10, 3);
                ASSERT1(m == 17);
                int A11[] = {1, 4, 30};
                int B11[] = {10, 30, 50};
                m = Test::FindMedian<int>(A11, 3, B11, 3);
                ASSERT1(m == 10);
                int A12[] = {1, 10, 30};
                int B12[] = {10, 30, 50};
                m = Test::FindMedian<int>(A12, 3, B12, 3);
                ASSERT1(m == 10);
                int A13[] = {1, 14, 30};
                int B13[] = {10, 30, 50};
                m = Test::FindMedian<int>(A13, 3, B13, 3);
                ASSERT1(m == 14);
                int A14[] = {10, 14, 30};
                int B14[] = {10, 30, 50};
                m = Test::FindMedian<int>(A14, 3, B14, 3);
                ASSERT1(m == 14);
                int A15[] = {11, 14, 30};
                int B15[] = {10, 30, 50};
                m = Test::FindMedian<int>(A15, 3, B15, 3);
                ASSERT1(m == 14);
                int A16[] = {14, 14, 30};
                int B16[] = {10, 30, 50};
                m = Test::FindMedian<int>(A16, 3, B16, 3);
                ASSERT1(m == 14);
                int A17[] = {14, 30, 30};
                int B17[] = {10, 30, 50};
                m = Test::FindMedian<int>(A17, 3, B17, 3);
                ASSERT1(m == 30);
                int A18[] = {30, 30, 30};
                int B18[] = {10, 30, 50};
                m = Test::FindMedian<int>(A18, 3, B18, 3);
                ASSERT1(m == 30);
                int A19[] = {1, 4, 37};
                int B19[] = {10, 30, 50};
                m = Test::FindMedian<int>(A19, 3, B19, 3);
                ASSERT1(m == 10);
                int A20[] = {1, 10, 37};
                int B20[] = {10, 30, 50};
                m = Test::FindMedian<int>(A20, 3, B20, 3);
                ASSERT1(m == 10);
                int A21[] = {10, 10, 37};
                int B21[] = {10, 30, 50};
                m = Test::FindMedian<int>(A21, 3, B21, 3);
                ASSERT1(m == 10);
                int A22[] = {1, 14, 37};
                int B22[] = {10, 30, 50};
                m = Test::FindMedian<int>(A22, 3, B22, 3);
                ASSERT1(m == 14);
                int A23[] = {10, 14, 37};
                int B23[] = {10, 30, 50};
                m = Test::FindMedian<int>(A23, 3, B23, 3);
                ASSERT1(m == 14);
                int A24[] = {11, 14, 37};
                int B24[] = {10, 30, 50};
                m = Test::FindMedian<int>(A24, 3, B24, 3);
                ASSERT1(m == 14);
                int A25[] = {1, 30, 37};
                int B25[] = {10, 30, 50};
                m = Test::FindMedian<int>(A25, 3, B25, 3);
                ASSERT1(m == 30);
                int A26[] = {10, 30, 37};
                int B26[] = {10, 30, 50};
                m = Test::FindMedian<int>(A26, 3, B26, 3);
                ASSERT1(m == 30);
                int A27[] = {11, 30, 37};
                int B27[] = {10, 30, 50};
                m = Test::FindMedian<int>(A27, 3, B27, 3);
                ASSERT1(m == 30);
                int A28[] = {30, 30, 37};
                int B28[] = {10, 30, 50};
                m = Test::FindMedian<int>(A28, 3, B28, 3);
                ASSERT1(m == 30);
                int A29[] = {1, 34, 37};
                int B29[] = {10, 30, 50};
                m = Test::FindMedian<int>(A29, 3, B29, 3);
                ASSERT1(m == 30);
                int A30[] = {10, 34, 37};
                int B30[] = {10, 30, 50};
                m = Test::FindMedian<int>(A30, 3, B30, 3);
                ASSERT1(m == 30);
                int A31[] = {11, 34, 37};
                int B31[] = {10, 30, 50};
                m = Test::FindMedian<int>(A31, 3, B31, 3);
                ASSERT1(m == 30);
                int A32[] = {30, 34, 37};
                int B32[] = {10, 30, 50};
                m = Test::FindMedian<int>(A32, 3, B32, 3);
                ASSERT1(m == 30);
                int A33[] = {31, 34, 37};
                int B33[] = {10, 30, 50};
                m = Test::FindMedian<int>(A33, 3, B33, 3);
                ASSERT1(m == 31);
                int A34[] = {1, 4, 57};
                int B34[] = {10, 30, 50};
                m = Test::FindMedian<int>(A34, 3, B34, 3);
                ASSERT1(m == 10);
                int A35[] = {1, 10, 57};
                int B35[] = {10, 30, 50};
                m = Test::FindMedian<int>(A35, 3, B35, 3);
                ASSERT1(m == 10);
                int A36[] = {10, 10, 57};
                int B36[] = {10, 30, 50};
                m = Test::FindMedian<int>(A36, 3, B36, 3);
                ASSERT1(m == 10);
                int A37[] = {1, 14, 57};
                int B37[] = {10, 30, 50};
                m = Test::FindMedian<int>(A37, 3, B37, 3);
                ASSERT1(m == 14);
                int A38[] = {10, 14, 57};
                int B38[] = {10, 30, 50};
                m = Test::FindMedian<int>(A38, 3, B38, 3);
                ASSERT1(m == 14);
                int A39[] = {11, 14, 57};
                int B39[] = {10, 30, 50};
                m = Test::FindMedian<int>(A39, 3, B39, 3);
                ASSERT1(m == 14);
                int A40[] = {14, 14, 57};
                int B40[] = {10, 30, 50};
                m = Test::FindMedian<int>(A40, 3, B40, 3);
                ASSERT1(m == 14);
                int A41[] = {1, 30, 57};
                int B41[] = {10, 30, 50};
                m = Test::FindMedian<int>(A41, 3, B41, 3);
                ASSERT1(m == 30);
                int A42[] = {10, 30, 57};
                int B42[] = {10, 30, 50};
                m = Test::FindMedian<int>(A42, 3, B42, 3);
                ASSERT1(m == 30);
                int A43[] = {11, 30, 57};
                int B43[] = {10, 30, 50};
                m = Test::FindMedian<int>(A43, 3, B43, 3);
                ASSERT1(m == 30);
                int A44[] = {30, 30, 57};
                int B44[] = {10, 30, 50};
                m = Test::FindMedian<int>(A44, 3, B44, 3);
                ASSERT1(m == 30);
                int A45[] = {1, 34, 57};
                int B45[] = {10, 30, 50};
                m = Test::FindMedian<int>(A45, 3, B45, 3);
                ASSERT1(m == 30);
                int A46[] = {10, 34, 57};
                int B46[] = {10, 30, 50};
                m = Test::FindMedian<int>(A46, 3, B46, 3);
                ASSERT1(m == 30);
                int A47[] = {11, 34, 57};
                int B47[] = {10, 30, 50};
                m = Test::FindMedian<int>(A47, 3, B47, 3);
                ASSERT1(m == 30);
                int A48[] = {30, 34, 57};
                int B48[] = {10, 30, 50};
                m = Test::FindMedian<int>(A48, 3, B48, 3);
                ASSERT1(m == 30);
                int A49[] = {31, 34, 57};
                int B49[] = {10, 30, 50};
                m = Test::FindMedian<int>(A49, 3, B49, 3);
                ASSERT1(m == 31);
                int A50[] = {34, 34, 57};
                int B50[] = {10, 30, 50};
                m = Test::FindMedian<int>(A50, 3, B50, 3);
                ASSERT1(m == 34);
                int A51[] = {1, 50, 57};
                int B51[] = {10, 30, 50};
                m = Test::FindMedian<int>(A51, 3, B51, 3);
                ASSERT1(m == 30);
                int A52[] = {10, 50, 57};
                int B52[] = {10, 30, 50};
                m = Test::FindMedian<int>(A52, 3, B52, 3);
                ASSERT1(m == 30);
                int A53[] = {11, 50, 57};
                int B53[] = {10, 30, 50};
                m = Test::FindMedian<int>(A53, 3, B53, 3);
                ASSERT1(m == 30);
                int A54[] = {30, 50, 57};
                int B54[] = {10, 30, 50};
                m = Test::FindMedian<int>(A54, 3, B54, 3);
                ASSERT1(m == 30);
                int A55[] = {31, 50, 57};
                int B55[] = {10, 30, 50};
                m = Test::FindMedian<int>(A55, 3, B55, 3);
                ASSERT1(m == 31);
                int A56[] = {50, 50, 57};
                int B56[] = {10, 30, 50};
                m = Test::FindMedian<int>(A56, 3, B56, 3);
                ASSERT1(m == 50);
                int A57[] = {1, 54, 57};
                int B57[] = {10, 30, 50};
                m = Test::FindMedian<int>(A57, 3, B57, 3);
                ASSERT1(m == 30);
                int A58[] = {10, 54, 57};
                int B58[] = {10, 30, 50};
                m = Test::FindMedian<int>(A58, 3, B58, 3);
                ASSERT1(m == 30);
                int A59[] = {11, 54, 57};
                int B59[] = {10, 30, 50};
                m = Test::FindMedian<int>(A59, 3, B59, 3);
                ASSERT1(m == 30);
                int A60[] = {30, 54, 57};
                int B60[] = {10, 30, 50};
                m = Test::FindMedian<int>(A60, 3, B60, 3);
                ASSERT1(m == 30);
                int A61[] = {31, 54, 57};
                int B61[] = {10, 30, 50};
                m = Test::FindMedian<int>(A61, 3, B61, 3);
                ASSERT1(m == 31);
                int A62[] = {50, 54, 57};
                int B62[] = {10, 30, 50};
                m = Test::FindMedian<int>(A62, 3, B62, 3);
                ASSERT1(m == 50);
                int A63[] = {51, 54, 57};
                int B63[] = {10, 30, 50};
                m = Test::FindMedian<int>(A63, 3, B63, 3);
                ASSERT1(m == 50);
            }
            {
                int A1[] = {716334471};
                int B1[] = {470591100, 1001089438, 1025533459, 1152645729, 2039723618};
                int m = Test::FindMedian<int>(A1, 1, B1, 5);
                ASSERT1(m == 1001089438);
            }
            {
                for (int i = 0; i < 1000; i++) {
                    int length = 1 + Random::Int(100, 1);
                    unique_ptr<int[]> input(new int[length]);
                    for (int j = 0; j < length; j++) {
                        input[j] = Random::Int();
                    }
                    int len0 = 1 + Random::Int(length - 2);
                    Logger().WriteInformation("Run %d: %d and %d elements\n", i, len0,
                                              length - len0);
                    std::sort(input.get(), input.get() + len0);
                    std::sort(input.get() + len0, input.get() + length);
                    Logger().Print(input.get(), len0);
                    Logger().Print(input.get() + len0, length - len0);
                    int median = Test::FindMedian<int>(
                        input.get(), len0, (input.get() + len0), length - len0);
                    int median2 = Test::FindMedian2<int>(
                        input.get(), len0, (input.get() + len0), length - len0);
                    std::sort(input.get(), input.get() + length);
                    Logger().Print(input.get(), length);
                    int median3 =
                        Test::FindMedian<int>(input.get(), length);
                    Logger() << "Medians: " << median << ", " << median2 << ", " << median3 << endl;
                    ASSERT1(median == median2);
                    ASSERT1(median == median3);
                }
            } });

    Add("FindKthOrder", [&]()
        {
            {
                auto check = [&](int e, int k, int *input1, int length1, int *input2,
                                 int length2)
                {
                    Logger().Print(input1, length1);
                    Logger().Print(input2, length2);
                    int v = Test::FindKthOrder<int>(k, input1, length1,
                                                    input2, length2);
                    int v2 = Test::FindKthOrder2<int>(k, input1, length1,
                                                      input2, length2);
                    int v3 = Test::FindKthOrder3<int>(k, input1, length1,
                                                      input2, length2);
                    Logger().WriteInformation("%d-th order: %d, %d, %d, %d\n", k, v, v2, v3, e);
                    ASSERT1(v == e);
                    ASSERT1(v2 == e);
                    ASSERT1(v3 == e);
                };

                int A0[] = {1};
                int B0[] = {2};
                check(1, 1, A0, 1, B0, 1);
                check(2, 2, A0, 1, B0, 1);

                int A1[] = {1};
                int B1[] = {1};
                check(1, 1, A1, 1, B1, 1);
                check(1, 2, A1, 1, B1, 1);

                int A2[] = {1, 2};
                int B2[] = {2};
                check(1, 1, A2, 2, B2, 1);
                check(2, 2, A2, 2, B2, 1);
                check(2, 3, A2, 2, B2, 1);

                int A3[] = {1, 2};
                int B3[] = {1};
                check(1, 1, A3, 2, B3, 1);
                check(1, 2, A3, 2, B3, 1);
                check(2, 3, A3, 2, B3, 1);

                int A4[] = {1, 1};
                int B4[] = {2};
                check(1, 1, A4, 2, B4, 1);
                check(1, 2, A4, 2, B4, 1);
                check(2, 3, A4, 2, B4, 1);

                int A5[] = {2, 2};
                int B5[] = {1};
                check(1, 1, A5, 2, B5, 1);
                check(2, 2, A5, 2, B5, 1);
                check(2, 3, A5, 2, B5, 1);

                int A6[] = {1, 2};
                int B6[] = {3};
                check(1, 1, A6, 2, B6, 1);
                check(2, 2, A6, 2, B6, 1);
                check(3, 3, A6, 2, B6, 1);

                int A7[] = {1, 3};
                int B7[] = {2};
                check(1, 1, A7, 2, B7, 1);
                check(2, 2, A7, 2, B7, 1);
                check(3, 3, A7, 2, B7, 1);

                int A8[] = {2, 3};
                int B8[] = {1};
                check(1, 1, A8, 2, B8, 1);
                check(2, 2, A8, 2, B8, 1);
                check(3, 3, A8, 2, B8, 1);

                int A9[] = {1, 2};
                int B9[] = {3, 4};
                check(1, 1, A9, 2, B9, 2);
                check(2, 2, A9, 2, B9, 2);
                check(3, 3, A9, 2, B9, 2);
                check(4, 4, A9, 2, B9, 2);

                int A10[] = {1, 3};
                int B10[] = {2, 4};
                check(1, 1, A10, 2, B10, 2);
                check(2, 2, A10, 2, B10, 2);
                check(3, 3, A10, 2, B10, 2);
                check(4, 4, A10, 2, B10, 2);

                int A11[] = {1, 4};
                int B11[] = {2, 3};
                check(1, 1, A11, 2, B11, 2);
                check(2, 2, A11, 2, B11, 2);
                check(3, 3, A11, 2, B11, 2);
                check(4, 4, A11, 2, B11, 2);

                int A12[] = {1, 2};
                int B12[] = {2, 3};
                check(1, 1, A12, 2, B12, 2);
                check(2, 2, A12, 2, B12, 2);
                check(2, 3, A12, 2, B12, 2);
                check(3, 4, A12, 2, B12, 2);

                int A13[] = {1, 3};
                int B13[] = {2, 2};
                check(1, 1, A13, 2, B13, 2);
                check(2, 2, A13, 2, B13, 2);
                check(2, 3, A13, 2, B13, 2);
                check(3, 4, A13, 2, B13, 2);

                int A13_1[] = {1, 1};
                int B13_1[] = {2, 3};
                check(1, 1, A13_1, 2, B13_1, 2);
                check(1, 2, A13_1, 2, B13_1, 2);
                check(2, 3, A13_1, 2, B13_1, 2);
                check(3, 4, A13_1, 2, B13_1, 2);

                int A14[] = {1, 2};
                int B14[] = {1, 3};
                check(1, 1, A14, 2, B14, 2);
                check(1, 2, A14, 2, B14, 2);
                check(2, 3, A14, 2, B14, 2);
                check(3, 4, A14, 2, B14, 2);

                int A15[] = {1, 2};
                int B15[] = {3, 3};
                check(1, 1, A15, 2, B15, 2);
                check(2, 2, A15, 2, B15, 2);
                check(3, 3, A15, 2, B15, 2);
                check(3, 4, A15, 2, B15, 2);

                int A16[] = {1, 3};
                int B16[] = {2, 3};
                check(1, 1, A16, 2, B16, 2);
                check(2, 2, A16, 2, B16, 2);
                check(3, 3, A16, 2, B16, 2);
                check(3, 4, A16, 2, B16, 2);

                int A17[] = {1, 1};
                int B17[] = {1, 2};
                check(1, 1, A17, 2, B17, 2);
                check(1, 2, A17, 2, B17, 2);
                check(1, 3, A17, 2, B17, 2);
                check(2, 4, A17, 2, B17, 2);

                int A18[] = {1, 2};
                int B18[] = {2, 2};
                check(1, 1, A18, 2, B18, 2);
                check(2, 2, A18, 2, B18, 2);
                check(2, 3, A18, 2, B18, 2);
                check(2, 4, A18, 2, B18, 2);

                int A19[] = {1, 1};
                int B19[] = {1, 1};
                check(1, 1, A19, 2, B19, 2);
                check(1, 2, A19, 2, B19, 2);
                check(1, 3, A19, 2, B19, 2);
                check(1, 4, A19, 2, B19, 2);

                int A20[] = {1, 2, 3};
                int B20[] = {4, 5};
                check(1, 1, A20, 3, B20, 2);
                check(2, 2, A20, 3, B20, 2);
                check(3, 3, A20, 3, B20, 2);
                check(4, 4, A20, 3, B20, 2);
                check(5, 5, A20, 3, B20, 2);

                int A21[] = {1, 2, 4};
                int B21[] = {3, 5};
                check(1, 1, A21, 3, B21, 2);
                check(2, 2, A21, 3, B21, 2);
                check(3, 3, A21, 3, B21, 2);
                check(4, 4, A21, 3, B21, 2);
                check(5, 5, A21, 3, B21, 2);

                int A22[] = {1, 2, 5};
                int B22[] = {3, 4};
                check(1, 1, A22, 3, B22, 2);
                check(2, 2, A22, 3, B22, 2);
                check(3, 3, A22, 3, B22, 2);
                check(4, 4, A22, 3, B22, 2);
                check(5, 5, A22, 3, B22, 2);

                int A23[] = {1, 3, 4};
                int B23[] = {2, 5};
                check(1, 1, A23, 3, B23, 2);
                check(2, 2, A23, 3, B23, 2);
                check(3, 3, A23, 3, B23, 2);
                check(4, 4, A23, 3, B23, 2);
                check(5, 5, A23, 3, B23, 2);

                int A24[] = {1, 3, 5};
                int B24[] = {2, 4};
                check(1, 1, A24, 3, B24, 2);
                check(2, 2, A24, 3, B24, 2);
                check(3, 3, A24, 3, B24, 2);
                check(4, 4, A24, 3, B24, 2);
                check(5, 5, A24, 3, B24, 2);

                int A25[] = {2, 3, 4};
                int B25[] = {1, 5};
                check(1, 1, A25, 3, B25, 2);
                check(2, 2, A25, 3, B25, 2);
                check(3, 3, A25, 3, B25, 2);
                check(4, 4, A25, 3, B25, 2);
                check(5, 5, A25, 3, B25, 2);

                int A26[] = {1, 4, 5};
                int B26[] = {2, 3};
                check(1, 1, A26, 3, B26, 2);
                check(2, 2, A26, 3, B26, 2);
                check(3, 3, A26, 3, B26, 2);
                check(4, 4, A26, 3, B26, 2);
                check(5, 5, A26, 3, B26, 2);

                int A27[] = {2, 3, 5};
                int B27[] = {1, 4};
                check(1, 1, A27, 3, B27, 2);
                check(2, 2, A27, 3, B27, 2);
                check(3, 3, A27, 3, B27, 2);
                check(4, 4, A27, 3, B27, 2);
                check(5, 5, A27, 3, B27, 2);

                int A28[] = {2, 4, 5};
                int B28[] = {1, 3};
                check(1, 1, A28, 3, B28, 2);
                check(2, 2, A28, 3, B28, 2);
                check(3, 3, A28, 3, B28, 2);
                check(4, 4, A28, 3, B28, 2);
                check(5, 5, A28, 3, B28, 2);

                int A29[] = {3, 4, 5};
                int B29[] = {1, 2};
                check(1, 1, A29, 3, B29, 2);
                check(2, 2, A29, 3, B29, 2);
                check(3, 3, A29, 3, B29, 2);
                check(4, 4, A29, 3, B29, 2);
                check(5, 5, A29, 3, B29, 2);
            }
            {

                auto check = [&](int k, int *input1, int length1, int *input2,
                                 int length2)
                {
                    Logger().Print(input1, length1);
                    Logger().Print(input2, length2);
                    int v = Test::FindKthOrder<int>(k, input1, length1,
                                                    input2, length2);
                    int v2 = Test::FindKthOrder2<int>(k, input1, length1,
                                                      input2, length2);
                    int v3 = Test::FindKthOrder3<int>(k, input1, length1,
                                                      input2, length2);
                    Logger().WriteInformation("%d-th order: %d, %d, %d\n", k, v, v2, v3);
                    ASSERT1(v == v2);
                    ASSERT1(v == v3);
                };
                for (int i = 0; i < 500; i++)
                {
                    int length = 1 + Random::Int(100, 1);
                    int length1 = 1 + Random::Int(length - 2);
                    int length2 = length - length1;
                    unique_ptr<int[]> input(new int[length]);
                    for (int j = 0; j < length; j++)
                    {
                        input[j] = Random::Int();
                    }
                    for (int k = 1; k <= length; k++)
                    {
                        Logger().WriteInformation(
                            "Run %d: %d-th order statics from %d and %d elements\n", i,
                            k, length1, length2);
                        std::sort(input.get(), input.get() + length1);
                        std::sort(input.get() + length1, input.get() + length);
                        check(k, input.get(), length1, (input.get() + length1),
                              length2);
                    }
                }
            } });

    Add("PartitionArrayByValue", [&]()
        {
            auto check = [&](int* a, int l, int v)
            {
                Logger().Print(a, l);
                Logger() << "Partiton by " << v << endl;
                int m = PartitionArrayByValue(a, 0, l - 1, v);
                Logger().Print(a, l);
                Logger() << "at index " << m << endl;
                for (int i = 0; i <= m; i++)
                {
                    ASSERT1(a[i] <= v);
                }
                for (int i = m + 1; i < l; i++)
                {
                    ASSERT1(a[i] > v);
                }
            };
            for (int i = 0; i < 100; i++)
            {
                int length = 1 + Random::Int(100);
                std::unique_ptr<int[]> input(new int[length]);
                Random::Array(input.get(), length, 100);
                check(input.get(), length, -10);
                check(input.get(), length, Random::Int(100));
                check(input.get(), length, 110);
            } });

    Add("FindIntersection", [&]()
        {
        auto check = [&](int *input1, int length1, int *input2, int length2) {
            Logger().Print(input1, length1);
            Logger().Print(input2, length2);
            pair<int, int> indices = FindIntersection<int>(
                input1, length1, input2, length2);
            pair<int, int> indices2 = FindIntersection2<int>(
                input1, length1, input2, length2);
            if (indices.first != -1 && indices.second != -1) {
                Logger().WriteInformation("input1[%d] = %d, input2[%d] = %d\n",
                                          indices.first, input1[indices.first],
                                          indices.second,
                                          input2[indices.second]);
            } else {
                Logger().WriteInformation("input1[%d], input2[%d]\n",
                                          indices.first, indices.second);
            }
            if (indices2.first != -1 && indices2.second != -1) {
                Logger().WriteInformation(
                    "input1[%d] = %d, input2[%d] = %d\n", indices2.first,
                    input1[indices2.first], indices2.second,
                    input2[indices2.second]);
            } else {
                Logger().WriteInformation("input1[%d], input2[%d]\n",
                                          indices2.first, indices2.second);
            }
            ASSERT1(indices.first == indices2.first);
            ASSERT1(indices.second == indices2.second);
            if (indices.first != -1 && indices2.second != -1) {
                ASSERT1(input1[indices.first] == input2[indices.second]);
            }
        };
        {
            int A[] = {0};
            int B[] = {0};
            check(A, 1, B, 1);
        }
        {
            int A[] = {0};
            int B[] = {1};
            check(A, 1, B, 1);
        }
        {
            int A[] = {0, 1};
            int B[] = {1, 2};
            check(A, 2, B, 2);
        }
        {
            int A[] = {0, 2};
            int B[] = {1, 2, 2};
            check(A, 2, B, 3);
        }
        {
            int A[] = {0, 1, 2};
            int B[] = {2, 2};
            check(A, 3, B, 2);
        }

        for (int i = 0; i < 100; i++) {
            int length = 1 + Random::Int(100, 2);
            int length1 = 1 + Random::Int(length - 2);
            int length2 = length - length1;

            unique_ptr<int[]> input(new int[length]);
            for (int j = 0; j < length; j++) {
                input[j] = Random::Int(100);
            }

            Logger().WriteInformation(
                "\nRun %d: intersection from %d and %d elements\n", i, length1,
                length2);
            std::sort(input.get(), input.get() + length1);
            std::sort(input.get() + length1, input.get() + length);
            check(input.get(), length1, (input.get() + length1), length2);
        } });

    Add("FindShiftPoint", [&]()
        {
            auto check = [&](const vector<int> v, size_t d) {
                Logger() << v;
                size_t s = FindShiftPoint(v);
                Logger() << "shifted by " << d << ", " << s << endl;
                ASSERT1(s == d);
            };
            {
                vector<int> v = {0};
                check(v, 0);
            }
            {
                vector<int> v = {1, 2};
                check(v, 0);
            }
            {
                vector<int> v = {2, 1};
                check(v, 1);
            }
            {
                vector<int> v = {3, 4, 5};
                check(v, 0);
            }
            {
                vector<int> v = {5, 3, 4};
                check(v, 1);
            }
            {
                vector<int> v = {4, 5, 3};
                check(v, 2);
            }
            {
                for (int i = 0; i < 100; i++) {
                    size_t n = Random::Int(100, 1);
                    size_t s = Random::Int(100) % n;
                    vector<int> input = Util::IncreasingVector(n);
                    Util::RotateLeft(input, s);
                    check(input, ((n - s) % n));
                    ASSERT1(input[(n - s) % n] == 0);
                }
            } });
    /*
            Add("KMP", [&]()
                {
                for (int i = 0; i < 50; i++)
                {
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
                } });

            Add("Monge", [&]()
                {
                for (int i = 0; i < 10; i++)
                {
                    int m = Random::Int(20, 2);
                    int n = Random::Int(20, 2);
                    int h = Random::Int(100);
                    vector<vector<int>> grid = Monge::Random(m, n, h);
                    vector<vector<int>> grid2 = Monge::Random2(m, n, h);
                    bool r = Monge::IsMonge(grid);
                    bool r2 = Monge::IsMonge(grid2);
                    Logger() << grid << grid2;
                    Logger() << "IsMonge = " << r << ", " << r2 << endl;
                    ASSERT1(r);
                    ASSERT1(r2);
                } });

            Add("RandomInt", [&]()
                {
                auto check = [&](int a, int b) {
                    map<int, int> m;
                    int n = 100 * (b - a + 1);
                    for (int i = 0; i < n; i++)
                    {
                        int j = RandomInt(a, b);
                        if (m.find(j) == m.end())
                            m[j] = 1;
                        else
                            m[j]++;
                    }
                    Logger() << "RandomInt(" << a << ", " << b << ") distribution:" << endl;
                    Logger() << m;
                    ASSERT1((int)m.size() == b - a + 1);
                    for (int i = a; i <= b; i++)
                        ASSERT1(m.find(i) != m.end());
                };
                for (int i = 0; i < 10; i++)
                {
                    check(0, i);
                } });
        */
}

#endif