#ifndef _ALGORITHMTEST_H_
#define _ALGORITHMTEST_H_

#include "Algorithm.h"
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
}

#endif