#ifndef _ALGORITHMTEST_H_
#define _ALGORITHMTEST_H_

#include <limits.h>
#include "Algorithm.h"
#include "Array.h"
#include "Random.h"
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

    Add("LongestCommonSubsequence", [&]() {
        string x = "ABCBDAB";
        string y = "BDCABA";
        LongestCommonSubsequence::PrintLCS(x, y);

        x = "ABCBDABJOHBFUOBLNJIPIOHUGOYO";
        y = "BDCABATIOFTYFIBLOILUIIGGOBLOBIP";
        LongestCommonSubsequence::PrintLCS(x, y);
    });

    Add("LongestIncreasingSubsequence", [&]() {
        {
            int I[] = {1};
            LongestIncreasingSubsequence::PrintSolution(I, 1);
        }
        {
            int I1[] = {1, 2};
            LongestIncreasingSubsequence::PrintSolution(I1, 2);

            int I2[] = {2, 1};
            LongestIncreasingSubsequence::PrintSolution(I2, 2);
        }
        {
            int I1[] = {1, 2, 3};
            LongestIncreasingSubsequence::PrintSolution(I1, 3);

            int I2[] = {1, 3, 2};
            LongestIncreasingSubsequence::PrintSolution(I2, 3);

            int I3[] = {2, 1, 3};
            LongestIncreasingSubsequence::PrintSolution(I3, 3);

            int I4[] = {2, 3, 1};
            LongestIncreasingSubsequence::PrintSolution(I4, 3);

            int I5[] = {3, 1, 2};
            LongestIncreasingSubsequence::PrintSolution(I5, 3);

            int I6[] = {3, 2, 1};
            LongestIncreasingSubsequence::PrintSolution(I6, 3);
        }
        {
            int I1[] = {1, 2, 3, 4};
            LongestIncreasingSubsequence::PrintSolution(I1, 4);

            int I2[] = {1, 2, 4, 3};
            LongestIncreasingSubsequence::PrintSolution(I2, 4);

            int I3[] = {1, 3, 2, 4};
            LongestIncreasingSubsequence::PrintSolution(I3, 4);

            int I4[] = {1, 3, 4, 2};
            LongestIncreasingSubsequence::PrintSolution(I4, 4);

            int I5[] = {1, 4, 2, 3};
            LongestIncreasingSubsequence::PrintSolution(I5, 4);

            int I6[] = {1, 4, 3, 2};
            LongestIncreasingSubsequence::PrintSolution(I6, 4);

            int I7[] = {2, 1, 3, 4};
            LongestIncreasingSubsequence::PrintSolution(I7, 4);

            int I8[] = {2, 1, 4, 3};
            LongestIncreasingSubsequence::PrintSolution(I8, 4);

            int I9[] = {2, 3, 1, 4};
            LongestIncreasingSubsequence::PrintSolution(I9, 4);

            int I10[] = {2, 3, 4, 1};
            LongestIncreasingSubsequence::PrintSolution(I10, 4);

            int I11[] = {2, 4, 1, 3};
            LongestIncreasingSubsequence::PrintSolution(I11, 4);

            int I12[] = {2, 4, 3, 1};
            LongestIncreasingSubsequence::PrintSolution(I12, 4);

            int I13[] = {3, 1, 2, 4};
            LongestIncreasingSubsequence::PrintSolution(I13, 4);

            int I14[] = {3, 1, 4, 2};
            LongestIncreasingSubsequence::PrintSolution(I14, 4);

            int I15[] = {3, 2, 1, 4};
            LongestIncreasingSubsequence::PrintSolution(I15, 4);

            int I16[] = {3, 2, 4, 1};
            LongestIncreasingSubsequence::PrintSolution(I16, 4);

            int I17[] = {3, 4, 1, 2};
            LongestIncreasingSubsequence::PrintSolution(I17, 4);

            int I18[] = {3, 4, 2, 1};
            LongestIncreasingSubsequence::PrintSolution(I18, 4);

            int I19[] = {4, 1, 2, 3};
            LongestIncreasingSubsequence::PrintSolution(I19, 4);

            int I20[] = {4, 1, 3, 2};
            LongestIncreasingSubsequence::PrintSolution(I20, 4);

            int I21[] = {4, 2, 1, 3};
            LongestIncreasingSubsequence::PrintSolution(I21, 4);

            int I22[] = {4, 2, 3, 1};
            LongestIncreasingSubsequence::PrintSolution(I22, 4);

            int I23[] = {4, 3, 1, 2};
            LongestIncreasingSubsequence::PrintSolution(I23, 4);

            int I24[] = {4, 3, 2, 1};
            LongestIncreasingSubsequence::PrintSolution(I24, 4);
        }
    });

    Add("MatrixChain", [&]() {
        int dimension[7] = {30, 35, 15, 5, 10, 20, 25};
        int count = 7;
        int cost[6][6];
        int split[6][6];

        memset(cost, 0, 36 * sizeof(int));
        memset(split, 0, 36 * sizeof(int));

        MatrixChain::ComputeCostTable(dimension, count, &cost[0][0], &split[0][0]);

        for (int i = 0; i < 6; i++)
        {
            cout << "\t" << dimension[i] << "x" << dimension[i + 1];
        }

        cout << endl;

        for (int i = 0; i < 6; i++)
        {
            cout << "\t" << i;
        }

        cout << endl;

        for (int i = 0; i < 6; i++)
        {
            cout << i;
            for (int j = 0; j < 6; j++)
            {
                cout << "\t";
                if (j >= i)
                    cout << cost[i][j];
            }

            cout << endl;
        }

        cout << endl;

        for (int i = 0; i < 6; i++)
        {
            cout << i;
            for (int j = 0; j < 6; j++)
            {
                cout << "\t";
                if (j >= i)
                    cout << split[i][j];
            }

            cout << endl;
        }

        MatrixChain::PrintSolution(dimension, count);
    });

    Add("MazeUniquePaths", [&]() {
        auto check = [&](int rows, int cols) {
            Logger().WriteInformation("Maze %d x %d:", rows, cols);
            Matrix<double> count(rows, cols);
            Matrix<double> count2(rows, cols);
            Maze::CountUniquePaths(rows, cols, count);
            Maze::CountUniquePaths2(rows, cols, count2);
            Logger().WriteInformation(" unique paths (%f, %f)\n", count(0, 0), count2(0, 0));
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    ASSERT1(count(i, j) == count2(i, j));
                }
            }
        };

        // overflow may happen if the maze is too large
        for (int i = 1; i <= 15; i++)
        {
            for (int j = 1; j <= 15; j++)
            {
                check(i, j);
            }
        }
    });

    Add("MinMaxPartitionSum", [&]() {
        auto check = [&](int *input, int length, int partitions, int expectedSum) {
            Logger().WriteInformation("\nInput:");
            for (int i = 0; i < length; i++)
            {
                Logger().WriteInformation(" %d", input[i]);
            }
            Logger().WriteInformation("\n%d partitions\n", partitions);

            unique_ptr<int[]> indices(new int[partitions]);
            unique_ptr<int[]> indices2(new int[partitions]);
            int sum = MinMaxPartitionSum::Solve(input, length, indices.get(), partitions);
            int sum2 = MinMaxPartitionSum::Solve2(input, length, indices2.get(), partitions);

            auto print = [&](unique_ptr<int[]> &indicesArray) {
                for (int j = 0; j < partitions; j++)
                {
                    int b = indicesArray[j];
                    int e = j == partitions - 1 ? length - 1 : indicesArray[j + 1] - 1;
                    int s = 0;
                    for (int i = b; i <= e; i++)
                    {
                        s += input[i];
                    }
                    Logger().WriteInformation("  %d = sum{A[%d..%d]} = ", s, b, e);
                    for (int i = b; i <= e; i++)
                    {
                        Logger().WriteInformation("%s%d", i == b ? "" : " + ", input[i]);
                    }
                    Logger().WriteInformation("\n");
                }
            };

            Logger().WriteInformation("\nSolution using dynamic programming: %d\n", sum);
            print(indices);
            Logger().WriteInformation("\nSolution using binary search: %d\n", sum2);
            print(indices2);
            ASSERT1(sum == expectedSum);
            ASSERT1(sum2 == expectedSum);
            for (int i = 0; i < partitions; i++)
            {
                ASSERT1(indices[i] == indices2[i]);
            }
        };

        int A1[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
        check(A1, 9, 3, 1700);

        int A2[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};
        check(A2, 9, 9, 900);

        int A3[] = {900, 800, 700, 600, 500, 400, 300, 200, 100};
        check(A3, 9, 3, 1700);

        int A4[] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
        check(A4, 9, 3, 300);

        int A5[] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
        check(A5, 9, 2, 500);

        int A6[] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
        check(A6, 9, 9, 100);

        int A7[] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
        check(A7, 9, 4, 300);

        int A8[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
        check(A8, 12, 5, 300);
    });

    Add("FiniteAutomationInvalidPattern", [&]() {
        ASSERTERROR(FiniteAutomation fa(nullptr), invalid_argument);
        ASSERTERROR(FiniteAutomation fa(""), invalid_argument);
        ASSERTERROR(FiniteAutomation fa("test"), invalid_argument);
    });

    Add("FiniteAutomationInvalidInput", [&]() {
        FiniteAutomation fa("a");
        vector<int> i = fa.SearchString("", 0);
        ASSERT1(i.size() == 0);
    });

    Add("FiniteAutomation1", [&]() {
        FiniteAutomation fa("a");
        fa.Print();

        vector<int> indices = fa.SearchString("b", 1);
        ASSERT1(indices.size() == 0);

        indices = fa.SearchString("a", 1);
        ASSERT1(indices.size() == 1);
        ASSERT1(indices[0] == 0);

        indices = fa.SearchString("ba", 2);
        ASSERT1(indices.size() == 1);
        ASSERT1(indices[0] == 1);

        indices = fa.SearchString("ab", 1);
        ASSERT1(indices.size() == 1);
        ASSERT1(indices[0] == 0);

        indices = fa.SearchString("bb", 2);
        ASSERT1(indices.size() == 0);

        indices = fa.SearchString("aa", 2);
        ASSERT1(indices.size() == 2);
        ASSERT1(indices[0] == 0);
        ASSERT1(indices[1] == 1);

        indices = fa.SearchString("baa", 3);
        ASSERT1(indices.size() == 2);
        ASSERT1(indices[0] == 1);
        ASSERT1(indices[1] == 2);

        indices = fa.SearchString("aba", 3);
        ASSERT1(indices.size() == 2);
        ASSERT1(indices[0] == 0);
        ASSERT1(indices[1] == 2);

        indices = fa.SearchString("bba", 3);
        ASSERT1(indices.size() == 1);
        ASSERT1(indices[0] == 2);
    });

    Add("FiniteAutomation2", [&]() {
        FiniteAutomation fa("aa");
        fa.Print();

        vector<int> indices = fa.SearchString("b", 1);
        ASSERT1(indices.size() == 0);

        indices = fa.SearchString("a", 1);
        ASSERT1(indices.size() == 0);

        indices = fa.SearchString("aa", 2);
        ASSERT1(indices.size() == 1);
        ASSERT1(indices[0] == 0);

        indices = fa.SearchString("ba", 2);
        ASSERT1(indices.size() == 0);

        indices = fa.SearchString("baa", 3);
        ASSERT1(indices.size() == 1);
        ASSERT1(indices[0] == 1);

        indices = fa.SearchString("bab", 3);
        ASSERT1(indices.size() == 0);

        indices = fa.SearchString("aab", 3);
        ASSERT1(indices.size() == 1);
        ASSERT1(indices[0] == 0);

        indices = fa.SearchString("aaa", 3);
        ASSERT1(indices.size() == 2);
        ASSERT1(indices[0] == 0);
        ASSERT1(indices[1] == 1);
    });

    Add("KMP", [&]() {
        for (int i = 0; i < 50; i++)
        {
            Logger().WriteInformation("Run %d\n", i);
            string pattern = Random::String(1 + rand() % 5, string("abcdefg"));
            string input = Random::String(1 + rand() % 1000, string("abcdefg"));
            KMP kmp(pattern.c_str());
            // kmp.Print();
            vector<int> indices = kmp.SearchString(input.c_str(), strlen(input.c_str()));
            printf("Pattern: %s\n", pattern.c_str());
            printf("Input: %s\n", input.c_str());
            for_each(indices.begin(), indices.end(), [](int i) {
                printf("Found a match at index %d\n", i);
            });
        }
    });

    Add("GCD", [&]() {
        auto check = [&](int n0, int n1, int e) {
            int r = Math::GreatestCommonDivisor<int>(n0, n1);
            Logger().WriteInformation("GCD(%d, %d) = %d\n", n0, n1, r);
            ASSERT1(r == e);
        };
        check(1, 0, 1);
        check(0, 1, 1);
        check(-1, 0, 1);
        check(1, 2, 1);
        check(2, 3, 1);
        check(2, 4, 2);
        check(3, 21, 3);
        check(42, 6, 6);
        check(56, 21, 7);
        check(57, 21, 3);
        check(77, 9, 1);
        check(1, -2, 1);
        check(-2, 3, 1);
        check(-2, -4, 2);
        check(-3, 21, 3);
        check(-42, 6, 6);
        check(-56, -21, 7);
        check(-57, -21, 3);
        check(77, -9, 1);
    });

    Add("AddBits", [&]() {
        auto toArray = [&](int n, size_t l, int *a) {
            for (size_t i = 0; i < l; i++)
            {
                a[i] = n & 0x1;
                n = n >> 1;
            }
        };
        auto toNum = [&](int *a, size_t l) -> int {
            int n = 0;
            for (size_t i = 0; i < l; i++)
            {
                if (a[i] == 1)
                    n = n + (0x1 << i);
            }
            return n;
        };
        auto check = [&](int n0, int n1, int e) {
            size_t l0 = Math::CountBits(n0);
            unique_ptr<int[]> b0(new int[l0]);
            toArray(n0, l0, b0.get());
            size_t l1 = Math::CountBits(n1);
            unique_ptr<int[]> b1(new int[l1]);
            toArray(n1, l1, b1.get());
            size_t l2 = 1 + max(l0, l1);
            unique_ptr<int[]> b2(new int[l2]);
            Math::AddBits(b0.get(), l0, b1.get(), l1, b2.get());
            int a = toNum(b2.get(), l2);
            Logger().WriteInformation("%d + %d = %d\n", n0, n1, a);
            ASSERT1(a == e);
        };
        check(2, 1, 3);
        check(3, 1, 4);
        check(3, 2, 5);
        for (int i = 0; i < 10; i++)
        {
            int n0 = 1 + rand();
            int n1 = 1 + rand();
            check(n0, n1, n0 + n1);
        }
    });

    Add("Excel", [&]() {
        auto check = [&](const string &input, unsigned long long expect) {
            Logger().WriteInformation("%s = ", input.c_str());
            unsigned long long r = Math::DecodeExcel(input);
            string e = Math::EncodeExcel(r);
            Logger().WriteInformation("%llu = %s\n", r, e.c_str());
            ASSERT1(r == expect);
            ASSERT1(e == input);
        };
        check("A", 0);
        check("B", 1);
        check("C", 2);
        check("X", 23);
        check("Y", 24);
        check("Z", 25);
        check("AA", 26);
        check("AB", 27);
        check("AY", 50);
        check("AZ", 51);
        check("BA", 52);
        check("BB", 53);
        check("BZ", 77);
        check("CA", 78);
        check("ZA", 676);
        check("ZY", 700);
        check("ZZ", 701);
        check("AAA", 702);
        check("AAB", 703);
        check("AAZ", 727);
        for (unsigned long long i = 0; i < 1000; i++)
        {
            string code = Math::EncodeExcel(i);
            unsigned long long decode = Math::DecodeExcel(code);
            Logger().WriteInformation("%llu, %s, %llu\n", i, code.c_str(), decode);
            ASSERT1(decode == i);
        }
        for (unsigned int i = 0; i < 1000; i++)
        {
            unsigned long long n = rand();
            string code = Math::EncodeExcel(n);
            unsigned long long decode = Math::DecodeExcel(code);
            Logger().WriteInformation("%llu, %s, %llu\n", n, code.c_str(), decode);
            ASSERT1(decode == n);
        }
    });

    Add("ExclusiveMultiplication", [&]() {
        auto check = [&](int *input, int length, long long *output, long long *expect) {
            Math::ExclusiveMultiplication(input, length, output);
            Logger().WriteInformation("Input:  ");
            Logger().Print<int>(input, length, "%4d", " ");
            Logger().WriteInformation("Output: ");
            Logger().Print<long long>(output, length, "%4ld", " ");
            for (int i = 0; i < length; i++)
            {
                ASSERT1(output[i] == expect[i]);
            }
        };
        {
            int A[] = {4, 3, 2, 1, 2};
            long long B[5];
            long long C[] = {12, 16, 24, 48, 24};
            check(A, 5, B, C);
        }
        {
            int A[] = {4, 3, 2, 1, 2, 3};
            long long B[6];
            long long C[] = {36, 48, 72, 144, 72, 48};
            check(A, 6, B, C);
        }
    });

    Add("ReversePolishNotation", [&]() {
        auto check = [&](vector<string> &tokens, int expect) {
            Logger().WriteInformation("Expression:");
            for_each(tokens.begin(), tokens.end(), [&](string &t) {
                Logger().WriteInformation(" %s", t.c_str());
            });
            Logger().WriteInformation("\n");
            int r = Math::EvalReversePolishNotation(tokens);
            Logger().WriteInformation("Result:     %d\n", r);
            ASSERT1(r == expect);
        };
        vector<string> t = {"2", "1", "+", "3", "*"};
        check(t, 9);
        t = {"4", "13", "5", "/", "+"};
        check(t, 6);
        t = {"-1", "-22", "+"};
        check(t, -23);
        t = {"1", "-22", "-"};
        check(t, 23);
        t = {"-2", "-3", "*"};
        check(t, 6);
        t = {"-22", "-2", "/"};
        check(t, 11);
    });

    Add("SingleNumber", [&]() {
        auto check = [&](int input[], int length, int expect) {
            int r1 = SingleNumber::FindOutOfThree(input, length);
            int r2 = SingleNumber::FindOutOfThree(input, length);
            int r3 = SingleNumber::FindOutOfThree(input, length);
            int r4 = SingleNumber::FindLOutOfK(input, length, 3, 1);
            int r5 = SingleNumber::FindLOutOfK2(input, length, 3, 1);
            Logger().WriteInformation("Single number: %d, %d, %d, %d, %d\n", r1, r2, r3, r4, r5);
            ASSERT1(r1 == expect);
            ASSERT1(r2 == expect);
            ASSERT1(r3 == expect);
            ASSERT1(r4 == expect);
            ASSERT1(r5 == expect);
        };
        {
            int A[] = {0, 1, 0, 0};
            check(A, 4, 1);
        }
        {
            int a = 0xFFFFFFFF;
            int A[] = {a, 3, a, a};
            check(A, 4, 3);
        }
        {
            int A[] = {1, 2, 3, 1, 2, 3, 4, 1, 2, 3};
            check(A, 10, 4);
        }
        {
            int A[] = {0, 1, 0, 1, 0, 1, 99};
            check(A, 7, 99);
        }
        {
            for (int j = 0; j < 100; j++)
            {
                int k = 2 + rand() % 10;
                int l = 1 + rand() % (k - 1);
                vector<int> n;
                int c;
                for (int i = 0; i < 10; i++)
                {
                    c = 1 + rand() % INT_MAX;
                    n.insert(n.end(), k, c);
                }
                c = 1 + rand() % INT_MAX;
                n.insert(n.end(), l, c);
                random_shuffle(n.begin(), n.end());
                Logger() << n;
                unique_ptr<int[]> input(new int[n.size()]);
                ToArray(n, input.get());
                int r = SingleNumber::FindLOutOfK(input.get(), n.size(), k, l);
                int r2 = SingleNumber::FindLOutOfK2(input.get(), n.size(), k, l);
                Logger().WriteInformation("Run %d: Single (%d, %d out of %d): %d, %d\n", j, c, l, k, r, r2);
                ASSERT1(r == c);
                ASSERT1(r2 == c);
            }
        }
    });

    Add("CountInversions", [&]() {
        auto check = [&](int *A, int L, int expected) -> void {
            int count = CountInversions<int>(A, L);
            ASSERT1(expected == count);
        };

        int I1[] = {0};
        check(I1, 1, 0);

        int I2[] = {0, 1};
        check(I2, 2, 0);

        int I3[] = {1, 0};
        check(I3, 2, 1);

        int I4[] = {0, 1, 2};
        check(I4, 3, 0);

        int I5[] = {1, 0, 2};
        check(I5, 3, 1);

        int I6[] = {2, 0, 1};
        check(I6, 3, 2);

        int I7[] = {2, 1, 0};
        check(I7, 3, 3);

        int I8[] = {0, 2, 1};
        check(I8, 3, 1);

        int I9[] = {1, 2, 0};
        check(I9, 3, 2);

        int I10[] = {3, 2, 1, 0};
        check(I10, 4, 6);

        int I11[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        int L = sizeof(I11) / sizeof(I11[0]);
        check(I11, L, 45);
    });

    Add("Range", [&]() {
        auto check = [&](double b1, double e1, double b2, double e2, bool o) {
            OverLap::Range r1 = make_pair(b1, e1);
            OverLap::Range r2 = make_pair(b2, e2);
            bool r = OverLap::IsOverlap(r1, r2);
            Logger().WriteInformation("(%.2f, %.2f) and (%.2f, %.2f) %s overlap\n", b1, e1, b2, e2, r ? "" : "not");
            ASSERT1(r == o);
        };

        check(0.0, 1.0, 2.0, 3.0, false);
        check(0.0, 2.0, 1.5, 3.0, true);
        check(0.0, 4.0, 2.0, 3.0, true);
    });

    Add("Rectangle", [&]() {
        auto check = [&](
                         double b1, double e1, double b2, double e2,
                         double b3, double e3, double b4, double e4,
                         bool o) {
            OverLap::Rectangle r1 = make_pair(make_pair(b1, e1), make_pair(b2, e2));
            OverLap::Rectangle r2 = make_pair(make_pair(b3, e3), make_pair(b4, e4));
            bool r = OverLap::IsOverlap(r1, r2);
            Logger().WriteInformation(
                "((%.2f, %.2f), (%.2f, %.2f)) and ((%.2f, %.2f), (%.2f, %.2f)) %s overlap\n",
                b1, e1, b2, e2, b3, e3, b4, e4, r ? "" : "not");
            ASSERT1(r == o);
        };

        check(0, 6, 2, 5, 3, 4, 5, 3, false);
        check(1, 6, 3, 5, 3, 4, 5, 3, false);
        check(2, 6, 4, 5, 3, 4, 5, 3, false);
        check(3, 6, 5, 5, 3, 4, 5, 3, false);
        check(4, 6, 6, 5, 3, 4, 5, 3, false);
        check(5, 6, 7, 5, 3, 4, 5, 3, false);
        check(6, 6, 8, 5, 3, 4, 5, 3, false);

        check(0, 4.5, 2, 3.5, 3, 4, 5, 3, false);
        check(1, 4.5, 3, 3.5, 3, 4, 5, 3, false);
        check(2, 4.5, 4, 3.5, 3, 4, 5, 3, true);
        check(3, 4.5, 5, 3.5, 3, 4, 5, 3, true);
        check(4, 4.5, 6, 3.5, 3, 4, 5, 3, true);
        check(5, 4.5, 7, 3.5, 3, 4, 5, 3, false);
        check(6, 4.5, 8, 3.5, 3, 4, 5, 3, false);

        check(0, 4, 2, 3, 3, 4, 5, 3, false);
        check(1, 4, 3, 3, 3, 4, 5, 3, false);
        check(2, 4, 4, 3, 3, 4, 5, 3, true);
        check(3, 4, 5, 3, 3, 4, 5, 3, true);
        check(4, 4, 6, 3, 3, 4, 5, 3, true);
        check(5, 4, 7, 3, 3, 4, 5, 3, false);
        check(6, 4, 8, 3, 3, 4, 5, 3, false);

        check(0, 3.5, 2, 2.5, 3, 4, 5, 3, false);
        check(1, 3.5, 3, 2.5, 3, 4, 5, 3, false);
        check(2, 3.5, 4, 2.5, 3, 4, 5, 3, true);
        check(3, 3.5, 5, 2.5, 3, 4, 5, 3, true);
        check(4, 3.5, 6, 2.5, 3, 4, 5, 3, true);
        check(5, 3.5, 7, 2.5, 3, 4, 5, 3, false);
        check(6, 3.5, 8, 2.5, 3, 4, 5, 3, false);

        check(0, 2, 2, 1, 3, 4, 5, 3, false);
        check(1, 2, 3, 1, 3, 4, 5, 3, false);
        check(2, 2, 4, 1, 3, 4, 5, 3, false);
        check(3, 2, 5, 1, 3, 4, 5, 3, false);
        check(4, 2, 6, 1, 3, 4, 5, 3, false);
        check(5, 2, 7, 1, 3, 4, 5, 3, false);
        check(6, 2, 8, 1, 3, 4, 5, 3, false);
    });

    Add("IntPoint", [&]() {
        vector<PointsOnALine::IntPoint> points = {
            PointsOnALine::IntPoint{3, 1},
            PointsOnALine::IntPoint{3, 1},
            PointsOnALine::IntPoint{0, 2},
            PointsOnALine::IntPoint{0, 1},
            PointsOnALine::IntPoint{-1, 0},
            PointsOnALine::IntPoint{0, 0}};
        sort(points.begin(), points.end());
        for_each(points.begin(), points.end(), [&](PointsOnALine::IntPoint &p) {
            Logger().WriteInformation("  (%d, %d)", p.x, p.y);
        });
        Logger().WriteInformation("\n");
        PointsOnALine::IntPoint p0(-1, 0);
        ASSERT1(points[0] == p0);
        PointsOnALine::IntPoint p1(0, 0);
        ASSERT1(points[1] == p1);
        PointsOnALine::IntPoint p2(0, 1);
        ASSERT1(points[2] == p2);
        PointsOnALine::IntPoint p3(0, 2);
        ASSERT1(points[3] == p3);
        PointsOnALine::IntPoint p4(3, 1);
        ASSERT1(points[4] == p4);
        PointsOnALine::IntPoint p5(3, 1);
        ASSERT1(points[5] == p5);
    });

    Add("MaxPointsOnLine", [&]() {
        auto check = [&](vector<PointsOnALine::IntPoint> &points, int expect) {
            Logger().WriteInformation("Input %d points:\n", points.size());
            for_each(points.begin(), points.end(), [&](const PointsOnALine::IntPoint &p) {
                Logger().WriteInformation("  (%d, %d)", p.x, p.y);
            });
            Logger().WriteInformation("\n");
            set<PointsOnALine::IntPoint> output;
            int count = PointsOnALine::MaxPointsOnALine(points, output);
            Logger().WriteInformation("Max points on a line: %d\n", count);
            for_each(output.begin(), output.end(), [&](const PointsOnALine::IntPoint &p) {
                Logger().WriteInformation("  (%d, %d)", p.x, p.y);
            });
            Logger().WriteInformation("\n");
            ASSERT1(count == expect);
        };
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{1, 1}};
            check(points, 1);
        }
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{1, 1},
                PointsOnALine::IntPoint{1, 2}};
            check(points, 2);
        }
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{1, 1},
                PointsOnALine::IntPoint{2, 1}};
            check(points, 2);
        }
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{2, 3},
                PointsOnALine::IntPoint{4, 5}};
            check(points, 2);
        }
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{1, 2},
                PointsOnALine::IntPoint{2, 2},
                PointsOnALine::IntPoint{1, 1},
                PointsOnALine::IntPoint{2, 1}};
            check(points, 2);
        }
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{1, 2},
                PointsOnALine::IntPoint{2, 2},
                PointsOnALine::IntPoint{1, 1},
                PointsOnALine::IntPoint{2, 1},
                PointsOnALine::IntPoint{3, 1}};
            check(points, 3);
        }
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{2, 3},
                PointsOnALine::IntPoint{1, 2},
                PointsOnALine::IntPoint{2, 2},
                PointsOnALine::IntPoint{1, 1},
                PointsOnALine::IntPoint{2, 1}};
            check(points, 3);
        }
        {
            vector<PointsOnALine::IntPoint> points = {
                PointsOnALine::IntPoint{1, 4},
                PointsOnALine::IntPoint{1, 3},
                PointsOnALine::IntPoint{2, 3},
                PointsOnALine::IntPoint{1, 2},
                PointsOnALine::IntPoint{2, 2},
                PointsOnALine::IntPoint{3, 2},
                PointsOnALine::IntPoint{2, 1},
                PointsOnALine::IntPoint{3, 1},
                PointsOnALine::IntPoint{4, 1}};
            check(points, 4);
        }
    });

    Add("CointSelect", [&]() {
        auto check = [&](int *input, int length) {
            Logger().WriteInformation("Input:");
            Logger().Print(input, length);

            auto print = [&](int value, vector<int> &indices) {
                Logger().WriteInformation("\tMax value:\t  %d\n", value);
                Logger().WriteInformation("\tIndices:\t");
                Logger() << indices;
                Logger().WriteInformation("\tItems:\t");
                Logger().Print<int>(indices, [&](Log &l, int i) {
                    l.WriteInformation("%d", input[i]);
                });
            };

            vector<int> indices;
            vector<int> indices2;
            int v = CoinSelect::MaxSelection(input, length, indices);
            Logger().WriteInformation("Solution 1\n");
            print(v, indices);
            int v2 = CoinSelect::MaxSelection2(input, length, indices2);
            Logger().WriteInformation("Solution 2\n");
            print(v2, indices2);

            ASSERT1(v == v2);
            ASSERT1(indices.size() == indices2.size());
            for (unsigned int i = 0; i < indices.size(); i++)
            {
                ASSERT1(indices[i] == indices2[i]);
            }
        };

        int c[] = {3, 2, 2, 3, 1, 2};
        int l = sizeof(c) / sizeof(c[0]);
        check(c, l);

        int c2[] = {3, 2, 2, 3, 1, 2, 1};
        int l2 = sizeof(c2) / sizeof(c2[0]);
        check(c2, l2);

        for (int i = 0; i < 100; i++)
        {
            int length = 1 + rand() % 100;
            unique_ptr<int[]> input(new int[length]);
            Random::Array(input.get(), length);
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            check(input.get(), length);
        }
    });

    Add("SearchWord", [&]() {
        auto check = [&](const vector<vector<char>> &m, const string &w, bool e) {
            Logger().Print(m, "%c", " ");
            Logger().WriteInformation("%s\n", w.c_str());
            bool r = SearchWord::Existed(m, w);
            bool r2 = SearchWord::Existed2(m, w);
            ASSERT1(r == e);
            ASSERT1(r2 == e);
        };
        {
            vector<vector<char>> m =
                {
                    {'x', 'x', 'x'},
                    {'x', 'h', 'e'},
                    {'o', 'l', 'x'},
                    {'x', 'l', 'x'}};
            check(m, "hello", true);
        }
        {
            vector<vector<char>> m =
                {
                    {'x', 'x', 'x'},
                    {'x', 'h', 'e'},
                    {'o', 'l', 'x'},
                    {'x', 'l', 'x'}};
            check(m, "hillo", false);
        }
        {
            // This will fail
            vector<vector<char>> m =
                {
                    {'x', 'w', 'h', 'b'},
                    {'u', 'k', 'o', 'm'},
                    {'z', 'w', 'v', 'a'},
                    {'t', 'd', 'k', 'n'}};
            // check(m, "owuxwhm", true);
        }
        {
            vector<vector<char>> m =
                {
                    {'w', 'x', 'x'},
                    {'x', 'w', 'x'},
                    {'x', 'x', 'x'}};
            check(m, "www", true);
        }
        {
            vector<vector<char>> m =
                {
                    {'w', 'y', 'x'},
                    {'x', 'w', 'x'},
                    {'x', 'x', 'x'}};
            check(m, "wwwy", true);
        }
        {
            vector<vector<char>> m =
                {
                    {'x', 'x', 'x'},
                    {'w', 'y', 'x'},
                    {'x', 'w', 'x'}};
            check(m, "wwwy", true);
        }
        {
            vector<vector<char>> m =
                {
                    {'y', 'x', 'x'},
                    {'w', 'x', 'x'},
                    {'x', 'w', 'x'}};
            check(m, "wwwy", true);
        }
        /*
		{
			for (int i = 0; i < 10; i++) {
				string word = String::Random(string("abcdefghijklmnopqrstuvwxyz"), 1 + (rand() % 10));
				vector<vector<char>> matrix = MatrixProblem::Generator::RandomWithoutWord(word);
				check(matrix, word, false);
			}
		}
		{
			for (int i = 0; i < 10; i++) {
				string word = String::Random(string("abcdefghijklmnopqrstuvwxyz"), 1 + (rand() % 10));
				vector<vector<char>> matrix = MatrixProblem::Generator::RandomWithWord(word);
				check(matrix, word, true);
			}
		}
		*/
    });

    Add("SurroundedRegion", [&]() {
        auto verify = [&](vector<vector<char>> &board) {
            int height = board.size();
            int width = board[0].size();
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (board[i][j] == 'O')
                    {
                        bool boundary = i == 0 || i == height - 1 || j == 0 || j == width - 1;
                        pair<int, int> p = make_pair(i, j);
                        set<pair<int, int>> region;
                        queue<pair<int, int>> q;
                        region.insert(p);
                        q.push(p);
                        while (!q.empty())
                        {
                            p = q.front();
                            q.pop();
                            pair<int, int> n;
                            if (p.first > 0 && board[p.first - 1][p.second] == 'O')
                            {
                                if (p.first - 1 == 0)
                                    boundary = true;
                                n = make_pair(p.first - 1, p.second);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.second > 0 && board[p.first][p.second - 1] == 'O')
                            {
                                if (p.second - 1 == 0)
                                    boundary = true;
                                n = make_pair(p.first, p.second - 1);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.second < width - 1 && board[p.first][p.second + 1] == 'O')
                            {
                                if (p.second + 1 == width - 1)
                                    boundary = true;
                                n = make_pair(p.first, p.second + 1);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                            if (p.first < height - 1 && board[p.first + 1][p.second] == 'O')
                            {
                                if (p.first + 1 == height - 1)
                                    boundary = true;
                                n = make_pair(p.first + 1, p.second);
                                if (region.find(n) == region.end())
                                {
                                    region.insert(n);
                                    q.push(n);
                                }
                            }
                        }

                        ASSERT1(boundary);
                    }
                }
            }
        };

        auto check = [&](vector<vector<char>> &board, vector<vector<char>> &board2) {
            Logger().WriteInformation("Input:\n");
            Logger().Print(board, "%c");
            SurroundedRegion::Capture(board);
            Logger().WriteInformation("Output1:\n");
            Logger().Print(board, "%c");
            ;
            verify(board);
            SurroundedRegion::Capture2(board2);
            Logger().WriteInformation("Output2:\n");
            Logger().Print(board2, "%c");
            verify(board2);
            int height = board.size();
            int width = board[0].size();
            int height2 = board.size();
            int width2 = board[0].size();
            ASSERT1(height == height2);
            ASSERT1(width == width2);
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    ASSERT1(board[i][j] == board2[i][j]);
                }
            }
        };
        {
            vector<vector<char>> board = {{'X'}};
            vector<vector<char>> board2 = {{'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O'}};
            vector<vector<char>> board2 = {{'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}};
            vector<vector<char>> board2 = {{'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}};
            vector<vector<char>> board2 = {{'X', 'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}};
            vector<vector<char>> board2 = {{'O', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'O'}};
            vector<vector<char>> board2 = {{'O', 'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X'}, {'X'}};
            vector<vector<char>> board2 = {{'X'}, {'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X'}, {'O'}};
            vector<vector<char>> board2 = {{'X'}, {'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O'}, {'X'}};
            vector<vector<char>> board2 = {{'O'}, {'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O'}, {'O'}};
            vector<vector<char>> board2 = {{'O'}, {'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'X', 'X'}};
            vector<vector<char>> board2 = {{'X', 'X'}, {'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}, {'X', 'X'}};
            vector<vector<char>> board2 = {{'O', 'X'}, {'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}, {'X', 'X'}};
            vector<vector<char>> board2 = {{'X', 'O'}, {'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'O', 'X'}};
            vector<vector<char>> board2 = {{'X', 'X'}, {'O', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'X', 'O'}};
            vector<vector<char>> board2 = {{'X', 'X'}, {'X', 'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'O'}, {'X', 'X'}};
            vector<vector<char>> board2 = {{'O', 'O'}, {'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'X'}, {'O', 'O'}};
            vector<vector<char>> board2 = {{'X', 'X'}, {'O', 'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}, {'O', 'X'}};
            vector<vector<char>> board2 = {{'O', 'X'}, {'O', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}, {'X', 'O'}};
            vector<vector<char>> board2 = {{'X', 'O'}, {'X', 'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'X'}, {'X', 'O'}};
            vector<vector<char>> board2 = {{'O', 'X'}, {'X', 'O'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'O'}, {'O', 'X'}};
            vector<vector<char>> board2 = {{'X', 'O'}, {'O', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'X', 'X'}, {'X', 'X', 'X'}, {'X', 'X', 'X'}};
            vector<vector<char>> board2 = {{'X', 'X', 'X'}, {'X', 'X', 'X'}, {'X', 'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'X', 'X'}, {'X', 'X', 'X'}, {'X', 'X', 'X'}};
            vector<vector<char>> board2 = {{'O', 'X', 'X'}, {'X', 'X', 'X'}, {'X', 'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'O', 'X', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
            vector<vector<char>> board2 = {{'O', 'X', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
            check(board, board2);
        }
        {
            vector<vector<char>> board = {{'X', 'O', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
            vector<vector<char>> board2 = {{'X', 'O', 'X'}, {'X', 'O', 'X'}, {'X', 'X', 'X'}};
            check(board, board2);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int height = 1 + rand() % 100;
                int width = 1 + rand() % 100;
                Logger().WriteInformation("Run %d, %d X %d\n", i, height, width);
                vector<vector<char>> board;
                vector<vector<char>> board2;
                for (int j = 0; j < height; j++)
                {
                    vector<char> row;
                    for (int k = 0; k < width; k++)
                    {
                        int v = rand();
                        if ((v & 0x1) == 1)
                        {
                            row.push_back('X');
                        }
                        else
                        {
                            row.push_back('O');
                        }
                    }
                    board.push_back(row);
                    board2.push_back(row);
                }
                check(board, board2);
            }
        }
    });
}

#endif