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

    Add("RemoveDuplicateChar", [&]() {
        auto check = [&](char *c, int length, char *e, int el) {
            Logger().WriteInformation("%s\t", c);
            int l = RemoveDuplicateChars(c, length);
            Logger().WriteInformation("%s\n", c);
            ASSERT1(0 == strcmp(c, e));
            ASSERT1(l == el);
        };
        {
            char *c;
            c = nullptr;
            int l = RemoveDuplicateChars(c, 0);
            ASSERT1(l == -1);
        }
        {
            char c[] = "Test";
            char e[] = "Test";
            check(c, 4, e, 4);
        }
        {
            char c[] = "TTeesstt";
            char e[] = "Test";
            check(c, 8, e, 4);
        }
        {
            char c[] = "TestTest";
            char e[] = "Test";
            check(c, 8, e, 4);
        }
        {
            char c[] = "";
            char e[] = "";
            check(c, 0, e, 0);
        }
        {
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            for (int i = 0; i < 100; i++)
            {
                size_t length = 1 + (rand() % 100);
                string s1 = String::Random(alphabet, length);
                Logger().WriteInformation("Run %d: %s\n", i, s1.c_str());
                unique_ptr<char[]> s2(new char[length + 1]);
                memcpy(s2.get(), s1.c_str(), length);
                s2[length] = '\0';
                set<char> ss1 = String::UniqueChars(s1);
                Logger().Print(ss1, "%c");
                int ls2 = RemoveDuplicateChars(s2.get(), (int)length);
                Logger().Print(s2.get(), (size_t)ls2, "%c");
                ASSERT1((int)ss1.size() == ls2);
                for (int j = 0; j < ls2; j++)
                {
                    ASSERT2(ss1.find(s2[j]) != ss1.end(), String::Format("%c is not found in set\n", s2[j]));
                }
            }
        }
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

    Add("PalindromeLongestSubsequence", [&]() {
        string s = "character";
        string t;
        string a;
        cout << "Input: " << s << endl;
        Palindrome::LongestSubsequenceByTable(s, t);
        cout << "Table: " << t << endl;
        Palindrome::LongestSubsequenceByArray(s, a);
        cout << "Array: " << a << endl;
        cout << endl;
        ASSERT1(0 == t.compare(a));

        s = "racecar";
        t = "";
        a = "";
        cout << "Input: " << s << endl;
        Palindrome::LongestSubsequenceByTable(s, t);
        cout << "Table: " << t << endl;
        Palindrome::LongestSubsequenceByArray(s, a);
        cout << "Array: " << a << endl;
        cout << endl;
        ASSERT1(0 == t.compare(a));

        s = "raceecar";
        t = "";
        a = "";
        cout << "Input: " << s << endl;
        Palindrome::LongestSubsequenceByTable(s, t);
        cout << "Table: " << t << endl;
        Palindrome::LongestSubsequenceByArray(s, a);
        cout << "Array: " << a << endl;
        cout << endl;
        ASSERT1(0 == t.compare(a));

        s = "racefcar";
        t = "";
        a = "";
        cout << "Input: " << s << endl;
        Palindrome::LongestSubsequenceByTable(s, t);
        cout << "Table: " << t << endl;
        Palindrome::LongestSubsequenceByArray(s, a);
        cout << "Array: " << a << endl;
        cout << endl;
        ASSERT1(0 == t.compare(a));

        s = "ra";
        t = "";
        a = "";
        cout << "Input: " << s << endl;
        Palindrome::LongestSubsequenceByTable(s, t);
        cout << "Table: " << t << endl;
        Palindrome::LongestSubsequenceByArray(s, a);
        cout << "Array: " << a << endl;
        cout << endl;
        ASSERT1(0 == t.compare(a));

        s = "rac";
        t = "";
        a = "";
        cout << "Input: " << s << endl;
        Palindrome::LongestSubsequenceByTable(s, t);
        cout << "Table: " << t << endl;
        Palindrome::LongestSubsequenceByArray(s, a);
        cout << "Array: " << a << endl;
        cout << endl;
        ASSERT1(0 == t.compare(a));
    });

    Add("PalindromeNumber", [&]() {
        auto check = [&](unsigned int n, bool e) {
            bool r = Palindrome::IsPalindrom(n);
            Logger().WriteInformation("%d is %s palindrome\n", n, r ? "" : "not");
            ASSERT1(r == e);
        };

        check(3, true);
        check(33, true);
        check(23, false);
        check(232, true);
        check(1231, false);
        check(12344321, true);
        check(123454321, true);
        check(1234567, false);
    });

    Add("PalindromeString", [&]() {
        auto check = [&](const string &s, bool e) {
            bool r = Palindrome::IsPalindrom(s);
            Logger().WriteInformation("\"%s\" is %s palindrome\n", s.c_str(), r ? "" : "not");
            ASSERT1(r == e);
        };

        check("", true);
        check("1", true);
        check("a", true);
        check(",", true);
        check("22", true);
        check("23", false);
        check("ab", false);
        check("a1", false);
        check(":3", true);
        check("a;", true);
        check("?b", true);
        check("# #4**", true);
        check("# c**", true);
        check("a, b&*() A;", true);
        check("A man, a plan, a canal: Panama", true);
        check("race a car", false);
        check("^%(&*%$%(", true);
        check("A^%(&*%$%(a", true);
        check("^%9(&*%$9%(", true);
    });

    Add("PalindromeSubstring1", [&]() {
        string i = "babcbabcbaccba";
        string o;
        Logger().WriteInformation("%s\n", i.c_str());
        Palindrome::LongestSubstring(i, o);
        Logger().WriteInformation("%s\n", o.c_str());
        ASSERT1(o == "abcbabcba");
    });

    Add("PalindromeSubstring2", [&]() {
        string i = "xabcbabcbayzaw";
        string o1;
        Logger().WriteInformation("%s\n", i.c_str());
        Palindrome::LongestSubstring(i, o1);
        Logger().WriteInformation("%s\n", o1.c_str());
        string o2;
        Palindrome::LongestSubsequenceByTable(i, o2);
        Logger().WriteInformation("%s\n", o2.c_str());
        string o3;
        Palindrome::LongestSubsequenceByArray(i, o3);
        Logger().WriteInformation("%s\n", o3.c_str());
        ASSERT1(o1 == "abcbabcba");
        ASSERT1(o2 == o1);
        ASSERT1(o3 == o1);
    });

    Add("PalindromeSubstring3", [&]() {
        string i = "xabcbabcbayztw";
        string o1;
        Logger().WriteInformation("%s\n", i.c_str());
        Palindrome::LongestSubstring(i, o1);
        Logger().WriteInformation("%s\n", o1.c_str());
        string o2;
        Palindrome::LongestSubsequenceByTable(i, o2);
        Logger().WriteInformation("%s\n", o2.c_str());
        string o3;
        Palindrome::LongestSubsequenceByArray(i, o3);
        Logger().WriteInformation("%s\n", o3.c_str());
        ASSERT1(o1 == "abcbabcba");
        ASSERT1(o2 == o1);
        ASSERT1(o3 == o1);
    });

    Add("PalindromePartition", [&]() {
        auto check = [&](const string &input) {
            Logger().WriteInformation("Input: %s\n", input.c_str());
            vector<vector<string>> partitions = Palindrome::Partition(input);
            vector<string> mincut = Palindrome::MinCutPartition(input);
            size_t mincutSize2 = (size_t)Palindrome::MinCutPartition2(input);
            Logger().WriteInformation("    %d partitions:\n", partitions.size());
            size_t mincutSize = input.length();
            for_each(partitions.begin(), partitions.end(), [&](vector<string> &partition) {
                if (partition.size() < mincutSize)
                    mincutSize = partition.size();
                Logger().WriteInformation("      [");
                for (size_t i = 0; i < partition.size(); i++)
                {
                    if (i != 0)
                    {
                        Logger().WriteInformation(", ");
                    }
                    Logger().WriteInformation("%s", partition[i].c_str());
                }
                Logger().WriteInformation("]\n");
            });
            Logger().WriteInformation("    Min cuts: %d, %d\n", mincut.size() - 1, mincutSize2);
            Logger().WriteInformation("      [");
            for (size_t i = 0; i < mincut.size(); i++)
            {
                if (i != 0)
                {
                    Logger().WriteInformation(", ");
                }
                Logger().WriteInformation("%s", mincut[i].c_str());
            }
            Logger().WriteInformation("]\n");
            ASSERT1(mincut.size() == mincutSize);
            ASSERT1(mincut.size() == mincutSize2 + 1);
        };

        check("a");
        check("aa");
        check("ab");
        check("aaa");
        check("aab");
        check("abb");
        check("aba");
        check("aaaa");
        check("aaab");
        check("aaba");
        check("abaa");
        check("baaa");
        check("aabb");
        check("abab");
        check("baab");
        check(string(10, 'a'));
    });

    Add("PartitionArrayByOrders", [&]() {
        {
            int A[] = {1};
            int I[] = {0};
            Partition::PartitionArrayByOrders(A, 0, 0, I, 0, 0);
            ASSERT1(A[0] == 1);
        }
        {
            int A[] = {1, 2};
            int I1[] = {0};
            Partition::PartitionArrayByOrders(A, 0, 1, I1, 0, 0);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);

            int I2[] = {1};
            Partition::PartitionArrayByOrders(A, 0, 1, I2, 0, 0);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);

            int I3[] = {0, 1};
            Partition::PartitionArrayByOrders(A, 0, 1, I3, 0, 1);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);

            int B1[] = {2, 1};
            Partition::PartitionArrayByOrders(B1, 0, 1, I1, 0, 0);
            ASSERT1(B1[0] == 1);
            ASSERT1(B1[1] == 2);

            int B2[] = {2, 1};
            Partition::PartitionArrayByOrders(B2, 0, 1, I2, 0, 0);
            ASSERT1(B2[0] == 1);
            ASSERT1(B2[1] == 2);

            int B3[] = {2, 1};
            Partition::PartitionArrayByOrders(B3, 0, 1, I3, 0, 1);
            ASSERT1(B3[0] == 1);
            ASSERT1(B3[1] == 2);
        }
        {
            int A[] = {1, 2, 3};
            int I1[] = {0};
            Partition::PartitionArrayByOrders(A, 0, 2, I1, 0, 0);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);
            ASSERT1(A[2] == 3);

            int I2[] = {1};
            Partition::PartitionArrayByOrders(A, 0, 2, I2, 0, 0);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);
            ASSERT1(A[2] == 3);

            int I3[] = {2};
            Partition::PartitionArrayByOrders(A, 0, 2, I3, 0, 0);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);
            ASSERT1(A[2] == 3);

            int I4[] = {0, 1};
            Partition::PartitionArrayByOrders(A, 0, 2, I4, 0, 1);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);
            ASSERT1(A[2] == 3);

            int I5[] = {0, 2};
            Partition::PartitionArrayByOrders(A, 0, 2, I5, 0, 1);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);
            ASSERT1(A[2] == 3);

            int I6[] = {1, 2};
            Partition::PartitionArrayByOrders(A, 0, 2, I6, 0, 1);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);
            ASSERT1(A[2] == 3);

            int I7[] = {0, 1, 2};
            Partition::PartitionArrayByOrders(A, 0, 2, I7, 0, 2);
            ASSERT1(A[0] == 1);
            ASSERT1(A[1] == 2);
            ASSERT1(A[2] == 3);

            int B1[] = {2, 1, 3};
            Partition::PartitionArrayByOrders(B1, 0, 2, I1, 0, 0);
            ASSERT1(B1[0] == 1);
            ASSERT1(B1[1] > B1[0]);
            ASSERT1(B1[2] > B1[0]);

            int B2[] = {2, 3, 1};
            Partition::PartitionArrayByOrders(B2, 0, 2, I1, 0, 0);
            ASSERT1(B2[0] == 1);
            ASSERT1(B2[1] > B2[0]);
            ASSERT1(B2[2] > B2[0]);

            int B3[] = {3, 1, 2};
            Partition::PartitionArrayByOrders(B3, 0, 2, I1, 0, 0);
            ASSERT1(B3[0] == 1);
            ASSERT1(B3[1] > B3[0]);
            ASSERT1(B3[2] > B3[0]);

            int B4[] = {3, 2, 1};
            Partition::PartitionArrayByOrders(B4, 0, 2, I1, 0, 0);
            ASSERT1(B4[0] == 1);
            ASSERT1(B4[1] > B4[0]);
            ASSERT1(B4[2] > B4[0]);

            int B5[] = {2, 1, 3};
            Partition::PartitionArrayByOrders(B5, 0, 2, I2, 0, 0);
            ASSERT1(B5[0] == 1);
            ASSERT1(B5[1] == 2);
            ASSERT1(B5[2] == 3);

            int B6[] = {2, 3, 1};
            Partition::PartitionArrayByOrders(B6, 0, 2, I2, 0, 0);
            ASSERT1(B6[0] == 1);
            ASSERT1(B6[1] == 2);
            ASSERT1(B6[2] == 3);

            int B7[] = {3, 1, 2};
            Partition::PartitionArrayByOrders(B7, 0, 2, I2, 0, 0);
            ASSERT1(B7[0] == 1);
            ASSERT1(B7[1] == 2);
            ASSERT1(B7[2] == 3);

            int B8[] = {3, 2, 1};
            Partition::PartitionArrayByOrders(B8, 0, 2, I2, 0, 0);
            ASSERT1(B8[0] == 1);
            ASSERT1(B8[1] == 2);
            ASSERT1(B8[2] == 3);

            int B9[] = {2, 1, 3};
            Partition::PartitionArrayByOrders(B9, 0, 2, I3, 0, 0);
            ASSERT1(B9[0] < B9[2]);
            ASSERT1(B9[1] < B9[2]);
            ASSERT1(B9[2] == 3);

            int B10[] = {2, 3, 1};
            Partition::PartitionArrayByOrders(B10, 0, 2, I3, 0, 0);
            ASSERT1(B10[0] < B10[2]);
            ASSERT1(B10[1] < B10[2]);
            ASSERT1(B10[2] == 3);

            int B11[] = {3, 1, 2};
            Partition::PartitionArrayByOrders(B11, 0, 2, I3, 0, 0);
            ASSERT1(B11[0] < B11[2]);
            ASSERT1(B11[1] < B11[2]);
            ASSERT1(B11[2] == 3);

            int B12[] = {3, 2, 1};
            Partition::PartitionArrayByOrders(B12, 0, 2, I3, 0, 0);
            ASSERT1(B12[0] < B12[2]);
            ASSERT1(B12[1] < B12[2]);
            ASSERT1(B12[2] == 3);

            int B13[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                Partition::PartitionArrayByOrders(B13[i], 0, 2, I4, 0, 1);
                ASSERT1(B13[i][0] == 1);
                ASSERT1(B13[i][1] == 2);
                ASSERT1(B13[i][2] == 3);
            }

            int B14[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                Partition::PartitionArrayByOrders(B14[i], 0, 2, I5, 0, 1);
                ASSERT1(B14[i][0] == 1);
                ASSERT1(B14[i][1] == 2);
                ASSERT1(B14[i][2] == 3);
            }

            int B15[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                Partition::PartitionArrayByOrders(B15[i], 0, 2, I6, 0, 1);
                ASSERT1(B15[i][0] == 1);
                ASSERT1(B15[i][1] == 2);
                ASSERT1(B15[i][2] == 3);
            }

            int B16[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                Partition::PartitionArrayByOrders(B16[i], 0, 2, I7, 0, 2);
                ASSERT1(B16[i][0] == 1);
                ASSERT1(B16[i][1] == 2);
                ASSERT1(B16[i][2] == 3);
            }
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int length = 1 + rand();
                int len = 1 + (rand() % (length - 1));

                Logger().WriteInformation("Run %d: %d elements %d indices\n", i, length, len);

                unique_ptr<int[]> input(new int[length]);
                for (int j = 0; j < length; j++)
                {
                    input[j] = rand();
                }

                int delta = length / len;
                unique_ptr<int[]> indices(new int[len]);
                indices[0] = rand() % (delta + 1);
                for (int j = 1; j < len; j++)
                {
                    indices[j] = indices[j - 1] + 1 + (rand() % delta);
                }

                ASSERT1(indices[len - 1] < length);

                Partition::PartitionArrayByOrders((int *)input.get(), 0, length - 1, (int *)indices.get(), 0, len - 1);

                int index = 0;
                for (int j = 0; j < length; j++)
                {
                    if (j == indices[index])
                    {
                        index++;
                    }

                    if (index < len)
                        ASSERT1(input[j] <= input[indices[index]]);

                    if (index > 0)
                        ASSERT1(input[j] >= input[indices[index - 1]]);
                }
            }
        }
    });

    Add("PartitionArrayByQuantiles", [&]() {
        {
            int A[] = {1};
            int I[1];
            Partition::PartitionArrayByQuantiles(A, 1, I, 1);
            ASSERT1(A[0] == 1);
        }
        {
            int A1[] = {1, 2};
            int I1[1];
            Partition::PartitionArrayByQuantiles(A1, 2, I1, 2);
            ASSERT1(A1[0] == 1);
            ASSERT1(A1[1] == 2);
            ASSERT1(I1[0] == 1);

            int A2[] = {2, 1};
            int I2[1];
            Partition::PartitionArrayByQuantiles(A2, 2, I2, 2);
            ASSERT1(A2[0] == 1);
            ASSERT1(A2[1] == 2);
            ASSERT1(I2[0] == 1);
        }
        {
            int A1[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                int I[1];
                Partition::PartitionArrayByQuantiles(A1[i], 3, I, 2);
                ASSERT1(A1[i][0] == 1);
                ASSERT1(A1[i][1] == 2);
                ASSERT1(A1[i][2] == 3);
                ASSERT1(I[0] == 1);
            }

            int A2[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                int I[2];
                Partition::PartitionArrayByQuantiles(A2[i], 3, I, 3);
                ASSERT1(A2[i][0] == 1);
                ASSERT1(A2[i][1] == 2);
                ASSERT1(A2[i][2] == 3);
                ASSERT1(I[0] == 1);
                ASSERT1(I[1] == 2);
            }
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int length = 1 + rand();
                int len = 1 + (rand() % length);

                Logger().WriteInformation("Run %d: %d elements %d indices\n", i, length, len - 1);

                unique_ptr<int[]> input(new int[length]);
                for (int j = 0; j < length; j++)
                {
                    input[j] = rand();
                }

                unique_ptr<int[]> indices(new int[len - 1]);

                Partition::PartitionArrayByQuantiles((int *)input.get(), length, (int *)indices.get(), len);

                for (int i = 0; i < len - 3; i++)
                {
                    int d1 = indices[i + 1] - indices[i];
                    int d2 = indices[i + 2] - indices[i + 1];
                    ASSERT1(abs(d1 - d2) <= 1);
                }

                int index = 0;
                for (int j = 0; j < length; j++)
                {
                    if (j == indices[index])
                    {
                        index++;
                    }

                    if (index < len - 1)
                        ASSERT1(input[j] <= input[indices[index]]);

                    if (index > 0)
                        ASSERT1(input[j] >= input[indices[index - 1]]);
                }
            }
        }
    });

    Add("FindMedian", [&]() {
        {
            int A1[] = {0};
            int B1[] = {0};
            int m = FindMedian<int>(A1, 1, B1, 1);
            ASSERT1(m == 0);

            int A2[] = {0};
            int B2[] = {1};
            m = FindMedian<int>(A2, 1, B2, 1);
            ASSERT1(m == 0);

            int A3[] = {1};
            int B3[] = {0};
            m = FindMedian<int>(A3, 1, B3, 1);
            ASSERT1(m == 0);

            int A4[] = {0};
            int B4[] = {0, 1};
            m = FindMedian<int>(A4, 1, B4, 2);
            ASSERT1(m == 0);

            int A5[] = {1};
            int B5[] = {0, 1};
            m = FindMedian<int>(A5, 1, B5, 2);
            ASSERT1(m == 1);

            int A6[] = {-1};
            int B6[] = {0, 1};
            m = FindMedian<int>(A6, 1, B6, 2);
            ASSERT1(m == 0);

            int A7[] = {0};
            int B7[] = {-1, 1};
            m = FindMedian<int>(A7, 1, B7, 2);
            ASSERT1(m == 0);

            int A8[] = {1};
            int B8[] = {-1, 0};
            m = FindMedian<int>(A8, 1, B8, 2);
            ASSERT1(m == 0);

            int A9[] = {-1};
            int B9[] = {0, 1, 2};
            m = FindMedian<int>(A9, 1, B9, 3);
            ASSERT1(m == 0);

            int A10[] = {0};
            int B10[] = {0, 1, 2};
            m = FindMedian<int>(A10, 1, B10, 3);
            ASSERT1(m == 0);

            int A11[] = {1};
            int B11[] = {0, 1, 2};
            m = FindMedian<int>(A11, 1, B11, 3);
            ASSERT1(m == 1);

            int A12[] = {2};
            int B12[] = {0, 1, 2};
            m = FindMedian<int>(A12, 1, B12, 3);
            ASSERT1(m == 1);

            int A13[] = {3};
            int B13[] = {0, 1, 2};
            m = FindMedian<int>(A13, 1, B13, 3);
            ASSERT1(m == 1);

            int A14[] = {-1};
            int B14[] = {0, 1, 2, 3};
            m = FindMedian<int>(A14, 1, B14, 4);
            ASSERT1(m == 1);

            int A15[] = {0};
            int B15[] = {0, 1, 2, 3};
            m = FindMedian<int>(A15, 1, B15, 4);
            ASSERT1(m == 1);

            int A16[] = {1};
            int B16[] = {0, 1, 2, 3};
            m = FindMedian<int>(A16, 1, B16, 4);
            ASSERT1(m == 1);

            int A17[] = {2};
            int B17[] = {0, 1, 2, 3};
            m = FindMedian<int>(A17, 1, B17, 4);
            ASSERT1(m == 2);

            int A18[] = {3};
            int B18[] = {0, 1, 2, 3};
            m = FindMedian<int>(A18, 1, B18, 4);
            ASSERT1(m == 2);

            int A19[] = {4};
            int B19[] = {0, 1, 2, 3};
            m = FindMedian<int>(A19, 1, B19, 4);
            ASSERT1(m == 2);
        }
        {
            int A1[] = {-3, -1};
            int B1[] = {1, 3};
            int m = FindMedian<int>(A1, 2, B1, 2);
            ASSERT1(m == -1);

            int A2[] = {-3, 1};
            int B2[] = {1, 3};
            m = FindMedian<int>(A2, 2, B2, 2);
            ASSERT1(m == 1);

            int A3[] = {-3, 2};
            int B3[] = {1, 3};
            m = FindMedian<int>(A3, 2, B3, 2);
            ASSERT1(m == 1);

            int A4[] = {-3, 3};
            int B4[] = {1, 3};
            m = FindMedian<int>(A4, 2, B4, 2);
            ASSERT1(m == 1);

            int A5[] = {-3, 4};
            int B5[] = {1, 3};
            m = FindMedian<int>(A5, 2, B5, 2);
            ASSERT1(m == 1);

            int A6[] = {1, 2};
            int B6[] = {1, 3};
            m = FindMedian<int>(A6, 2, B6, 2);
            ASSERT1(m == 1);

            int A7[] = {2, 2};
            int B7[] = {1, 3};
            m = FindMedian<int>(A7, 2, B7, 2);
            ASSERT1(m == 2);

            int A8[] = {1, 3};
            int B8[] = {1, 3};
            m = FindMedian<int>(A8, 2, B8, 2);
            ASSERT1(m == 1);

            int A9[] = {2, 3};
            int B9[] = {1, 3};
            m = FindMedian<int>(A9, 2, B9, 2);
            ASSERT1(m == 2);

            int A10[] = {3, 3};
            int B10[] = {1, 3};
            m = FindMedian<int>(A10, 2, B10, 2);
            ASSERT1(m == 3);

            int A11[] = {3, 4};
            int B11[] = {1, 3};
            m = FindMedian<int>(A11, 2, B11, 2);
            ASSERT1(m == 3);

            int A12[] = {4, 5};
            int B12[] = {1, 3};
            m = FindMedian<int>(A12, 2, B12, 2);
            ASSERT1(m == 3);

            int A13[] = {-3, -1};
            int B13[] = {1, 3, 5};
            m = FindMedian<int>(A13, 2, B13, 3);
            ASSERT1(m == 1);

            int A14[] = {-3, 1};
            int B14[] = {1, 3, 5};
            m = FindMedian<int>(A14, 2, B14, 3);
            ASSERT1(m == 1);

            int A15[] = {-3, 2};
            int B15[] = {1, 3, 5};
            m = FindMedian<int>(A15, 2, B15, 3);
            ASSERT1(m == 2);

            int A16[] = {1, 2};
            int B16[] = {1, 3, 5};
            m = FindMedian<int>(A16, 2, B16, 3);
            ASSERT1(m == 2);

            int A17[] = {2, 2};
            int B17[] = {1, 3, 5};
            m = FindMedian<int>(A17, 2, B17, 3);
            ASSERT1(m == 2);

            int A18[] = {-3, 3};
            int B18[] = {1, 3, 5};
            m = FindMedian<int>(A18, 2, B18, 3);
            ASSERT1(m == 3);

            int A19[] = {1, 3};
            int B19[] = {1, 3, 5};
            m = FindMedian<int>(A19, 2, B19, 3);
            ASSERT1(m == 3);

            int A20[] = {2, 3};
            int B20[] = {1, 3, 5};
            m = FindMedian<int>(A20, 2, B20, 3);
            ASSERT1(m == 3);

            int A21[] = {3, 3};
            int B21[] = {1, 3, 5};
            m = FindMedian<int>(A21, 2, B21, 3);
            ASSERT1(m == 3);

            int A22[] = {-3, 4};
            int B22[] = {1, 3, 5};
            m = FindMedian<int>(A22, 2, B22, 3);
            ASSERT1(m == 3);

            int A23[] = {1, 4};
            int B23[] = {1, 3, 5};
            m = FindMedian<int>(A23, 2, B23, 3);
            ASSERT1(m == 3);

            int A24[] = {2, 4};
            int B24[] = {1, 3, 5};
            m = FindMedian<int>(A24, 2, B24, 3);
            ASSERT1(m == 3);

            int A25[] = {3, 4};
            int B25[] = {1, 3, 5};
            m = FindMedian<int>(A25, 2, B25, 3);
            ASSERT1(m == 3);

            int A26[] = {4, 4};
            int B26[] = {1, 3, 5};
            m = FindMedian<int>(A26, 2, B26, 3);
            ASSERT1(m == 4);

            int A27[] = {-3, 5};
            int B27[] = {1, 3, 5};
            m = FindMedian<int>(A27, 2, B27, 3);
            ASSERT1(m == 3);

            int A28[] = {1, 5};
            int B28[] = {1, 3, 5};
            m = FindMedian<int>(A28, 2, B28, 3);
            ASSERT1(m == 3);

            int A29[] = {2, 5};
            int B29[] = {1, 3, 5};
            m = FindMedian<int>(A29, 2, B29, 3);
            ASSERT1(m == 3);

            int A30[] = {3, 5};
            int B30[] = {1, 3, 5};
            m = FindMedian<int>(A30, 2, B30, 3);
            ASSERT1(m == 3);

            int A31[] = {4, 5};
            int B31[] = {1, 3, 5};
            m = FindMedian<int>(A31, 2, B31, 3);
            ASSERT1(m == 4);

            int A32[] = {5, 5};
            int B32[] = {1, 3, 5};
            m = FindMedian<int>(A32, 2, B32, 3);
            ASSERT1(m == 5);

            int A33[] = {-3, 7};
            int B33[] = {1, 3, 5};
            m = FindMedian<int>(A33, 2, B33, 3);
            ASSERT1(m == 3);

            int A34[] = {1, 7};
            int B34[] = {1, 3, 5};
            m = FindMedian<int>(A34, 2, B34, 3);
            ASSERT1(m == 3);

            int A35[] = {2, 7};
            int B35[] = {1, 3, 5};
            m = FindMedian<int>(A35, 2, B35, 3);
            ASSERT1(m == 3);

            int A36[] = {3, 7};
            int B36[] = {1, 3, 5};
            m = FindMedian<int>(A36, 2, B36, 3);
            ASSERT1(m == 3);

            int A37[] = {4, 7};
            int B37[] = {1, 3, 5};
            m = FindMedian<int>(A37, 2, B37, 3);
            ASSERT1(m == 4);

            int A38[] = {5, 7};
            int B38[] = {1, 3, 5};
            m = FindMedian<int>(A38, 2, B38, 3);
            ASSERT1(m == 5);

            int A39[] = {6, 7};
            int B39[] = {1, 3, 5};
            m = FindMedian<int>(A39, 2, B39, 3);
            ASSERT1(m == 5);
        }
        {
            int A1[] = {1, 4, 7};
            int B1[] = {10, 30, 50};
            int m = FindMedian<int>(A1, 3, B1, 3);
            ASSERT1(m == 7);

            int A2[] = {1, 4, 10};
            int B2[] = {10, 30, 50};
            m = FindMedian<int>(A2, 3, B2, 3);
            ASSERT1(m == 10);

            int A3[] = {1, 4, 17};
            int B3[] = {10, 30, 50};
            m = FindMedian<int>(A3, 3, B3, 3);
            ASSERT1(m == 10);

            int A4[] = {1, 10, 17};
            int B4[] = {10, 30, 50};
            m = FindMedian<int>(A4, 3, B4, 3);
            ASSERT1(m == 10);

            int A5[] = {1, 14, 17};
            int B5[] = {10, 30, 50};
            m = FindMedian<int>(A5, 3, B5, 3);
            ASSERT1(m == 14);

            int A6[] = {10, 14, 17};
            int B6[] = {10, 30, 50};
            m = FindMedian<int>(A6, 3, B6, 3);
            ASSERT1(m == 14);

            int A7[] = {11, 14, 17};
            int B7[] = {10, 30, 50};
            m = FindMedian<int>(A7, 3, B7, 3);
            ASSERT1(m == 14);

            int A8[] = {14, 14, 17};
            int B8[] = {10, 30, 50};
            m = FindMedian<int>(A8, 3, B8, 3);
            ASSERT1(m == 14);

            int A9[] = {14, 17, 17};
            int B9[] = {10, 30, 50};
            m = FindMedian<int>(A9, 3, B9, 3);
            ASSERT1(m == 17);

            int A10[] = {17, 17, 17};
            int B10[] = {10, 30, 50};
            m = FindMedian<int>(A10, 3, B10, 3);
            ASSERT1(m == 17);

            int A11[] = {1, 4, 30};
            int B11[] = {10, 30, 50};
            m = FindMedian<int>(A11, 3, B11, 3);
            ASSERT1(m == 10);

            int A12[] = {1, 10, 30};
            int B12[] = {10, 30, 50};
            m = FindMedian<int>(A12, 3, B12, 3);
            ASSERT1(m == 10);

            int A13[] = {1, 14, 30};
            int B13[] = {10, 30, 50};
            m = FindMedian<int>(A13, 3, B13, 3);
            ASSERT1(m == 14);

            int A14[] = {10, 14, 30};
            int B14[] = {10, 30, 50};
            m = FindMedian<int>(A14, 3, B14, 3);
            ASSERT1(m == 14);

            int A15[] = {11, 14, 30};
            int B15[] = {10, 30, 50};
            m = FindMedian<int>(A15, 3, B15, 3);
            ASSERT1(m == 14);

            int A16[] = {14, 14, 30};
            int B16[] = {10, 30, 50};
            m = FindMedian<int>(A16, 3, B16, 3);
            ASSERT1(m == 14);

            int A17[] = {14, 30, 30};
            int B17[] = {10, 30, 50};
            m = FindMedian<int>(A17, 3, B17, 3);
            ASSERT1(m == 30);

            int A18[] = {30, 30, 30};
            int B18[] = {10, 30, 50};
            m = FindMedian<int>(A18, 3, B18, 3);
            ASSERT1(m == 30);

            int A19[] = {1, 4, 37};
            int B19[] = {10, 30, 50};
            m = FindMedian<int>(A19, 3, B19, 3);
            ASSERT1(m == 10);

            int A20[] = {1, 10, 37};
            int B20[] = {10, 30, 50};
            m = FindMedian<int>(A20, 3, B20, 3);
            ASSERT1(m == 10);

            int A21[] = {10, 10, 37};
            int B21[] = {10, 30, 50};
            m = FindMedian<int>(A21, 3, B21, 3);
            ASSERT1(m == 10);

            int A22[] = {1, 14, 37};
            int B22[] = {10, 30, 50};
            m = FindMedian<int>(A22, 3, B22, 3);
            ASSERT1(m == 14);

            int A23[] = {10, 14, 37};
            int B23[] = {10, 30, 50};
            m = FindMedian<int>(A23, 3, B23, 3);
            ASSERT1(m == 14);

            int A24[] = {11, 14, 37};
            int B24[] = {10, 30, 50};
            m = FindMedian<int>(A24, 3, B24, 3);
            ASSERT1(m == 14);

            int A25[] = {1, 30, 37};
            int B25[] = {10, 30, 50};
            m = FindMedian<int>(A25, 3, B25, 3);
            ASSERT1(m == 30);

            int A26[] = {10, 30, 37};
            int B26[] = {10, 30, 50};
            m = FindMedian<int>(A26, 3, B26, 3);
            ASSERT1(m == 30);

            int A27[] = {11, 30, 37};
            int B27[] = {10, 30, 50};
            m = FindMedian<int>(A27, 3, B27, 3);
            ASSERT1(m == 30);

            int A28[] = {30, 30, 37};
            int B28[] = {10, 30, 50};
            m = FindMedian<int>(A28, 3, B28, 3);
            ASSERT1(m == 30);

            int A29[] = {1, 34, 37};
            int B29[] = {10, 30, 50};
            m = FindMedian<int>(A29, 3, B29, 3);
            ASSERT1(m == 30);

            int A30[] = {10, 34, 37};
            int B30[] = {10, 30, 50};
            m = FindMedian<int>(A30, 3, B30, 3);
            ASSERT1(m == 30);

            int A31[] = {11, 34, 37};
            int B31[] = {10, 30, 50};
            m = FindMedian<int>(A31, 3, B31, 3);
            ASSERT1(m == 30);

            int A32[] = {30, 34, 37};
            int B32[] = {10, 30, 50};
            m = FindMedian<int>(A32, 3, B32, 3);
            ASSERT1(m == 30);

            int A33[] = {31, 34, 37};
            int B33[] = {10, 30, 50};
            m = FindMedian<int>(A33, 3, B33, 3);
            ASSERT1(m == 31);

            int A34[] = {1, 4, 57};
            int B34[] = {10, 30, 50};
            m = FindMedian<int>(A34, 3, B34, 3);
            ASSERT1(m == 10);

            int A35[] = {1, 10, 57};
            int B35[] = {10, 30, 50};
            m = FindMedian<int>(A35, 3, B35, 3);
            ASSERT1(m == 10);

            int A36[] = {10, 10, 57};
            int B36[] = {10, 30, 50};
            m = FindMedian<int>(A36, 3, B36, 3);
            ASSERT1(m == 10);

            int A37[] = {1, 14, 57};
            int B37[] = {10, 30, 50};
            m = FindMedian<int>(A37, 3, B37, 3);
            ASSERT1(m == 14);

            int A38[] = {10, 14, 57};
            int B38[] = {10, 30, 50};
            m = FindMedian<int>(A38, 3, B38, 3);
            ASSERT1(m == 14);

            int A39[] = {11, 14, 57};
            int B39[] = {10, 30, 50};
            m = FindMedian<int>(A39, 3, B39, 3);
            ASSERT1(m == 14);

            int A40[] = {14, 14, 57};
            int B40[] = {10, 30, 50};
            m = FindMedian<int>(A40, 3, B40, 3);
            ASSERT1(m == 14);

            int A41[] = {1, 30, 57};
            int B41[] = {10, 30, 50};
            m = FindMedian<int>(A41, 3, B41, 3);
            ASSERT1(m == 30);

            int A42[] = {10, 30, 57};
            int B42[] = {10, 30, 50};
            m = FindMedian<int>(A42, 3, B42, 3);
            ASSERT1(m == 30);

            int A43[] = {11, 30, 57};
            int B43[] = {10, 30, 50};
            m = FindMedian<int>(A43, 3, B43, 3);
            ASSERT1(m == 30);

            int A44[] = {30, 30, 57};
            int B44[] = {10, 30, 50};
            m = FindMedian<int>(A44, 3, B44, 3);
            ASSERT1(m == 30);

            int A45[] = {1, 34, 57};
            int B45[] = {10, 30, 50};
            m = FindMedian<int>(A45, 3, B45, 3);
            ASSERT1(m == 30);

            int A46[] = {10, 34, 57};
            int B46[] = {10, 30, 50};
            m = FindMedian<int>(A46, 3, B46, 3);
            ASSERT1(m == 30);

            int A47[] = {11, 34, 57};
            int B47[] = {10, 30, 50};
            m = FindMedian<int>(A47, 3, B47, 3);
            ASSERT1(m == 30);

            int A48[] = {30, 34, 57};
            int B48[] = {10, 30, 50};
            m = FindMedian<int>(A48, 3, B48, 3);
            ASSERT1(m == 30);

            int A49[] = {31, 34, 57};
            int B49[] = {10, 30, 50};
            m = FindMedian<int>(A49, 3, B49, 3);
            ASSERT1(m == 31);

            int A50[] = {34, 34, 57};
            int B50[] = {10, 30, 50};
            m = FindMedian<int>(A50, 3, B50, 3);
            ASSERT1(m == 34);

            int A51[] = {1, 50, 57};
            int B51[] = {10, 30, 50};
            m = FindMedian<int>(A51, 3, B51, 3);
            ASSERT1(m == 30);

            int A52[] = {10, 50, 57};
            int B52[] = {10, 30, 50};
            m = FindMedian<int>(A52, 3, B52, 3);
            ASSERT1(m == 30);

            int A53[] = {11, 50, 57};
            int B53[] = {10, 30, 50};
            m = FindMedian<int>(A53, 3, B53, 3);
            ASSERT1(m == 30);

            int A54[] = {30, 50, 57};
            int B54[] = {10, 30, 50};
            m = FindMedian<int>(A54, 3, B54, 3);
            ASSERT1(m == 30);

            int A55[] = {31, 50, 57};
            int B55[] = {10, 30, 50};
            m = FindMedian<int>(A55, 3, B55, 3);
            ASSERT1(m == 31);

            int A56[] = {50, 50, 57};
            int B56[] = {10, 30, 50};
            m = FindMedian<int>(A56, 3, B56, 3);
            ASSERT1(m == 50);

            int A57[] = {1, 54, 57};
            int B57[] = {10, 30, 50};
            m = FindMedian<int>(A57, 3, B57, 3);
            ASSERT1(m == 30);

            int A58[] = {10, 54, 57};
            int B58[] = {10, 30, 50};
            m = FindMedian<int>(A58, 3, B58, 3);
            ASSERT1(m == 30);

            int A59[] = {11, 54, 57};
            int B59[] = {10, 30, 50};
            m = FindMedian<int>(A59, 3, B59, 3);
            ASSERT1(m == 30);

            int A60[] = {30, 54, 57};
            int B60[] = {10, 30, 50};
            m = FindMedian<int>(A60, 3, B60, 3);
            ASSERT1(m == 30);

            int A61[] = {31, 54, 57};
            int B61[] = {10, 30, 50};
            m = FindMedian<int>(A61, 3, B61, 3);
            ASSERT1(m == 31);

            int A62[] = {50, 54, 57};
            int B62[] = {10, 30, 50};
            m = FindMedian<int>(A62, 3, B62, 3);
            ASSERT1(m == 50);

            int A63[] = {51, 54, 57};
            int B63[] = {10, 30, 50};
            m = FindMedian<int>(A63, 3, B63, 3);
            ASSERT1(m == 50);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                vector<int> input0 = Random::Vector(100);
                int len0 = (int)input0.size();
                vector<int> input1 = Random::Vector(100);
                int len1 = (int)input1.size();

                Logger().WriteInformation("Run %d: %d and %d elements\n", i, len0, len1);

                sort(input0.begin(), input0.end());
                unique_ptr<int[]> array0(new int[len0]);
                ToArray(input0, array0.get());

                sort(input1.begin(), input1.end());
                unique_ptr<int[]> array1(new int[len1]);
                ToArray(input1, array1.get());

                int median = FindMedian<int>(array0.get(), len0, array1.get(), len1);

                vector<int> input(input0.begin(), input0.end());
                input.insert(input.end(), input1.begin(), input1.end());
                sort(input.begin(), input.end());

                int median2 = Math::LowerMedian(0, input.size() - 1);

                ASSERT1(median == input[median2]);
            }
        }
    });

    Add("SelectClosetNeighbors", [&]() {
        {
            int A1[] = {1, 2};
            SelectClosestNeighbors(A1, 2, 0, 1);
            ASSERT1(A1[0] == 1);
            ASSERT1(A1[1] == 2);

            SelectClosestNeighbors(A1, 2, 1, 1);
            ASSERT1(A1[0] == 2);
            ASSERT1(A1[1] == 1);

            SelectClosestNeighbors(A1, 2, 0, 1);
            ASSERT1(A1[0] == 1);
            ASSERT1(A1[1] == 2);

            SelectClosestNeighbors(A1, 2, 1, 1);
            ASSERT1(A1[0] == 2);
            ASSERT1(A1[1] == 1);

            SelectClosestNeighbors(A1, 2, 0, 0);
            ASSERT1(A1[0] == 1);
            ASSERT1(A1[1] == 2);

            SelectClosestNeighbors(A1, 2, 1, 0);
            ASSERT1(A1[0] == 2);
            ASSERT1(A1[1] == 1);
        }
        {
            int A1[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                SelectClosestNeighbors(A1[i], 3, 0, 0);
                ASSERT1(A1[i][0] == 1);
            }

            int A2[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                SelectClosestNeighbors(A2[i], 3, 0, 1);
                ASSERT1(A2[i][0] == 1);
                ASSERT1(A2[i][1] == 2);
            }

            int A3[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                SelectClosestNeighbors(A3[i], 3, 1, 0);
                ASSERT1(A3[i][0] == 2);
            }

            int A4[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                SelectClosestNeighbors(A4[i], 3, 2, 0);
                ASSERT1(A4[i][0] == 3);
            }

            int A5[6][3] = {
                {1, 2, 3},
                {1, 3, 2},
                {2, 1, 3},
                {2, 3, 1},
                {3, 1, 2},
                {3, 2, 1}};

            for (int i = 0; i < 6; i++)
            {
                SelectClosestNeighbors(A5[i], 3, 2, 1);
                ASSERT1(A5[i][0] == 3);
                ASSERT1(A5[i][1] == 2);
            }
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int length = 1 + rand();
                int pivotIndex = rand() % length;
                int countNeighbors = rand() % length;

                Logger().WriteInformation("Run %d: %d elements, select %d elements closest to pivotIndex %d\n", i, length, countNeighbors, pivotIndex);

                unique_ptr<int[]> input(new int[length]);
                for (int j = 0; j < length; j++)
                {
                    input[j] = rand();
                }

                int pivot = SelectClosestNeighbors((int *)input.get(), length, pivotIndex, countNeighbors);

                int maxDistance = 0;
                for (int i = 0; i <= countNeighbors; i++)
                {
                    int d = abs(input[i] - pivot);
                    if (d > maxDistance)
                        maxDistance = d;
                }

                for (int i = countNeighbors + 1; i < length; i++)
                {
                    int d = abs(input[i] - pivot);
                    ASSERT1(d >= maxDistance);
                }
            }
        }
    });

    Add("KthOrder", [&]() {
        {
            auto check = [&](int e, int k, int *input1, int length1, int *input2, int length2) {
                Logger().WriteInformation("\n");
                Logger().WriteInformation("Input1:");
                Logger().Print(input1, length1);
                Logger().WriteInformation("Input2:");
                Logger().Print(input2, length2);
                int v = KthOrder::Solve<int>(k, input1, length1, input2, length2);
                int v2 = KthOrder::Solve2<int>(k, input1, length1, input2, length2);
                Logger().WriteInformation("%d-th order: %d %s %d, %d %s %d\n", k, v, v == e ? "==" : "!=", e, v2, v2 == e ? "==" : "!=", e);
                ASSERT1(v == e);
                ASSERT1(v2 == e);
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
            auto check = [&](int k, int *input1, int length1, int *input2, int length2) {
                int v = KthOrder::Solve<int>(k, input1, length1, input2, length2);
                int v2 = KthOrder::Solve2<int>(k, input1, length1, input2, length2);
                Logger().WriteInformation("%d-th order: %d %s %d\n", k, v, v == v2 ? "==" : "!=", v2);
                ASSERT1(v == v2);
            };

            for (int i = 0; i < 100; i++)
            {
                vector<int> v0 = Random::Vector(100); // Array::RandomSorted();
                vector<int> v1 = Random::Vector(100); // Array::RandomSorted();
                unique_ptr<int[]> input0(new int[v0.size()]);
                unique_ptr<int[]> input1(new int[v1.size()]);
                ToArray(v0, input0.get());
                ToArray(v1, input1.get());
                int k = 1;
                int length = v0.size() + v1.size();
                do
                {
                    Logger().WriteInformation("Run %d: %d-th order statics from %d and %d elements\n", i, k, v0.size(), v1.size());
                    check(k, input0.get(), v0.size(), input1.get(), v1.size());

                    if (k >= length - 100 && k < length)
                    {
                        k = length;
                    }
                    else
                    {
                        k += (1 + (rand() % 99));
                    }
                } while (k <= length);
            }
        }
    });

    Add("Intersection", [&]() {
        auto check = [&](int *input1, int length1, int *input2, int length2) {
            pair<int, int> indices = Intersection::Solve<int>(input1, length1, input2, length2);
            pair<int, int> indices2 = Intersection::Solve<int>(input1, length1, input2, length2);
            if (indices.first != -1 && indices.second != -1)
            {
                Logger().WriteInformation("input1[%d] = %d, input2[%d] = %d\n",
                                          indices.first, input1[indices.first], indices.second, input2[indices.second]);
            }
            else
            {
                Logger().WriteInformation("input1[%d], input2[%d]\n", indices.first, indices.second);
            }
            if (indices2.first != -1 && indices2.second != -1)
            {
                Logger().WriteInformation("input1[%d] = %d, input2[%d] = %d\n",
                                          indices2.first, input1[indices2.first], indices2.second, input2[indices2.second]);
            }
            else
            {
                Logger().WriteInformation("input1[%d], input2[%d]\n", indices2.first, indices2.second);
            }
            ASSERT1(indices == indices2);
            if (indices.first != -1 && indices2.second != -1)
            {
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

        for (int i = 0; i < 100; i++)
        {
            int length = 1 + rand();
            int length1 = 1 + (rand() % (length - 2));
            int length2 = length - length1;
            unique_ptr<int[]> input(new int[length]);
            Random::Array(input.get(), length);
            Logger().WriteInformation("\nRun %d: intersection from %d and %d elements\n", i, length1, length2);
            // Sort::MergeSort::Sort<int>(input.get(), 0, length1 - 1);
            // Sort::MergeSort::Sort<int>(input.get(), length1, length - 1);
            check(input.get(), length1, (input.get() + length1), length2);
        }
    });

    Add("RowSort", [&]() {
        {
            const int rows = 3;
            const int columns = 18;
            const int length = rows * columns;
            int A[length];
            for (int i = 0; i < length; i++)
            {
                A[i] = length - i;
            }

            RowSort::Sort<int>(A, length, columns);
            ASSERT1(RowSort::IsSorted(A, length, columns));
        }
        {
            for (int i = 0; i < 10; i++)
            {
                // srand((unsigned)time(NULL));
                const int rows = rand() % 100 + 1;
                const int columns = 2 * rows * rows;
                const int length = rows * columns;
                Logger().WriteInformation("Run %d: %d X %d\n", i, rows, columns);

                unique_ptr<int[]> A(new int[length]);
                Random::Array(A.get(), length);
                unique_ptr<int[]> B(new int[length]);
                memcpy_s(B.get(), length * sizeof(int), A.get(), length * sizeof(int));

                long tick = GetTickCount();
                bool sortedA = RowSort::IsSorted(A.get(), length, columns);
                Logger().WriteInformation("Serialized: %ssorted, %d ticks\n", sortedA ? "" : "not ", GetTickCount() - tick);
                tick = GetTickCount();
                RowSort::Sort<int>(A.get(), length, columns);
                Logger().WriteInformation("Serialized: sort took %d ticks\n", GetTickCount() - tick);
                tick = GetTickCount();
                sortedA = RowSort::IsSorted(A.get(), length, columns);
                Logger().WriteInformation("Serialized: %ssorted, %d ticks\n", sortedA ? "" : "not ", GetTickCount() - tick);

                tick = GetTickCount();
                bool sortedB = RowSort::ParallelIsSorted(B.get(), length, columns);
                Logger().WriteInformation("Parallel: %ssorted, %d ticks\n", sortedB ? "" : "not ", GetTickCount() - tick);
                tick = GetTickCount();
                RowSort::ParallelSort<int>(B.get(), length, columns);
                Logger().WriteInformation("Parallel: sort took %d ticks\n", GetTickCount() - tick);
                tick = GetTickCount();
                sortedB = RowSort::IsSorted(B.get(), length, columns);
                Logger().WriteInformation("Parallel: %ssorted, %d ticks\n", sortedB ? "" : "not ", GetTickCount() - tick);

                bool equal = Equal(A.get(), B.get(), length);
                ASSERT1(sortedA == true);
                ASSERT1(sortedB == true);
                ASSERT1(equal == true);
            }
        }
    });

    Add("CountingSort", [&]() {
        {
            int A[] = {2, 5, 3, 0, 2, 3, 0, 3};
            int L = sizeof(A) / sizeof(A[0]);
            int B[8];
            CountingSort::Sort(A, L, B);
            Logger().WriteInformation("A:\t");
            Logger().Print(A, L);
            Logger().WriteInformation("B:\t");
            Logger().Print(B, L);
            ASSERT1(IsSorted(B, L));
            CountingSort::Sort(A, L);
            Logger().WriteInformation("A:\t");
            Logger().Print(A, L);
            ASSERT1(IsSorted(A, L));
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int size = 1 + rand() % 1000;
                int range = rand() % 100;
                Logger().WriteInformation("Run %d %d elements in [-%d, %d]\n", i, size, range, range);
                unique_ptr<int[]> A(new int[size]);
                Random::Array(A.get(), size, -range, range);
                CountingSort::Sort(A.get(), size);
                ASSERT1(IsSorted(A.get(), size));
            }
        }
    });

    Add("WordLadder", [&]() {
        auto check = [&](const string &start, const string &end, const unordered_set<string> &dict, int expect) {
            Logger().WriteInformation("Dictionary: [");
            int i = 0;
            for_each(dict.begin(), dict.end(), [&](string w) {
                if (i != 0)
                {
                    Logger().WriteInformation(" ");
                }
                Logger().WriteInformation("%s", w.c_str());
                i++;
            });
            Logger().WriteInformation("]\n");
            Logger().WriteInformation("    Start:   %s\n", start.c_str());
            Logger().WriteInformation("    End:     %s\n", end.c_str());
            int length = WordLadder::Solve(start, end, dict);
            int length2 = WordLadder::Solve2(start, end, dict);
            int length3 = WordLadder::Solve3(start, end, dict);
            vector<vector<string>> ladders = WordLadder::WordLadders(start, end, dict);
            Logger().WriteInformation("    Length:  %d %s %d\n", length, length == expect ? "==" : "!=", expect);
            Logger().WriteInformation("    Length2: %d %s %d\n", length2, length2 == expect ? "==" : "!=", expect);
            Logger().WriteInformation("    Length3: %d %s %d\n", length3, length3 == expect ? "==" : "!=", expect);
            Logger().WriteInformation("    Ladders:\n");
            for_each(ladders.begin(), ladders.end(), [&](vector<string> &l) {
                Logger().WriteInformation("            [");
                int i = 0;
                for_each(l.begin(), l.end(), [&](string w) {
                    if (i != 0)
                    {
                        Logger().WriteInformation(" ");
                    }
                    Logger().WriteInformation("%s", w.c_str());
                    i++;
                });
                Logger().WriteInformation("]\n");
            });
            ASSERT1(length == expect);
            ASSERT1(length2 == expect);
            ASSERT1(length3 == expect);
        };
        {
            unordered_set<string> dict = {"hot"};
            check("hit", "cog", dict, 0);
        }
        {
            unordered_set<string> dict = {"hot", "dot", "dog", "lot", "log"};
            check("hit", "cog", dict, 5);
        }
        {
            unordered_set<string> dict = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
            check("red", "tax", dict, 4);
        }
    });

    Add("MatchSubsequence", [&]() {
        auto check = [&](const string &input, const string &pattern, int expect) {
            Logger().WriteInformation("Input:   %s\n", input.c_str());
            Logger().WriteInformation("Pattern: %s\n", pattern.c_str());
            int count2 = MatchSubsequence::Count2(input, pattern);
            Logger().WriteInformation("Matches: %d %s %d\n", count2, count2 == expect ? "==" : "!=", expect);
            int count = MatchSubsequence::Count(input, pattern);
            Logger().WriteInformation("Matches: %d %s %d\n", count, count == expect ? "==" : "!=", expect);
            ASSERT1(count == expect);
            ASSERT1(count2 == expect);
        };
        check("r", "r", 1);
        check("s", "r", 0);
        check("rr", "r", 2);
        check("rb", "r", 1);
        check("br", "r", 1);
        check("vb", "r", 0);
        check("rabbbit", "rabbit", 3);
        check("rrrr", "rr", 6);
        check("rrrrr", "rr", 10);
        check("rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr", "rr", 861);
        check("rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr", "rr", 5151);
        check("aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe", "bddabdcae", 10582116);
    });

    Add("BreakString", [&]() {
        int positions[] = {0, 2, 8, 10, 20};
        Matrix<pair<int, int>> cost(5, 5);
        BreakString::ComputeCostTable(positions, 5, cost);
        Logger().Print(positions, 5);
        auto print = [&](Log &l, pair<int, int> &p) {
            l.WriteInformation("(%d, %d)", p.first, p.second);
        };
        Logger().Print<pair<int, int>>(cost, print);

        vector<int> breaks;
        int totalCost = BreakString::ComputeBreaks(positions, 5, breaks);
        Logger().WriteInformation("Cost: %d\n", totalCost);
        Logger().WriteInformation("Breaks: ");
        Logger().Print(breaks);
    });

    Add("MinPathSum", [&]() {
        auto check = [&](vector<vector<int>> &triangle, int expect) {
            for_each(triangle.begin(), triangle.end(), [&](vector<int> &r) {
                for_each(r.begin(), r.end(), [&](int i) {
                    Logger().WriteInformation(" %d", i);
                });
                Logger().WriteInformation("\n");
            });
            int sum = MinPathSum::Solve(triangle);
            Logger().WriteInformation("Sum: %d %s %d\n", sum, sum == expect ? "==" : "!=", expect);
            ASSERT1(sum == expect);
        };
        {
            vector<vector<int>> t = {{-10}};
            check(t, -10);
        }
        {
            vector<vector<int>> t = {
                {-10},
                {1, 2}};
            check(t, -9);
        }
        {
            vector<vector<int>> t = {
                {2},
                {3, 4},
                {6, 5, 7},
                {4, 1, 8, 3}};
            check(t, 11);
        }
    });

    Add("IsMatch", [&]() {
        auto check = [&](char *s, char *p, bool e) {
            bool m1 = IsMatch1(s, p);
            bool m2 = IsMatch2(s, p);
            Logger().WriteInformation("IsMatch:\t%s %s %s\n", s, m1 ? "==" : "!=", p);
            Logger().WriteInformation("IsMatch2:\t%s %s %s\n", s, m2 ? "==" : "!=", p);
            ASSERT1(m1 == e);
            ASSERT1(m2 == e);
        };
        check("", "", true);
        check("a", "", false);
        check("", "a", false);
        check("", "*", true);
        check("", ".*", true);
        check("aa", "a", false);
        check("aa", ".", false);
        check("aa", "aa", true);
        check("aa", "..", true);
        check("aa", "*aa", true);
        check("aaa", "aa", false);
        check("aaa", "*aa", false);
        check("aaa", "aa*", true);
        check("aaa", "aa**", true);
        check("aaa", "a*a", true);
        check("aaa", "...", true);
        check("aaa", ".*.", true);
        check("aa", "a*", true);
        check("aa", ".*", true);
        check("ab", ".*", true);
        check("ab", "..", true);
        check("aab", "c*a*b", true);
        check("aab", "c***a**b", true);
        check("abbbc", "ab*c", true);
        check("ac", "ab*c", true);
        check("abbc", "ab*bbc", true);
        check("abcbcd", "a.*c.*d", true);
        const string ab1 = "ab";
        const string ab2 = "ab.*";
        for (int i = 0; i < 100; i++)
        {
            size_t len1 = 1 + rand() % 5;
            string input = Random::String(len1, ab1);
            size_t len2 = 1 + rand() % 5;
            string pattern = Random::String(len2, ab2);
            bool m1 = IsMatch1(input.c_str(), pattern.c_str());
            bool m2 = IsMatch2(input.c_str(), pattern.c_str());
            Logger().WriteInformation("IsMatch1:\t%s %s %s\n", input.c_str(), m1 ? "==" : "!=", pattern.c_str());
            Logger().WriteInformation("IsMatch2:\t%s %s %s\n", input.c_str(), m2 ? "==" : "!=", pattern.c_str());
            ASSERT1(m1 == m2);
        }
    });

    Add("LongestSubStringWithUniqueChars", [&]() {
        auto check = [&](char *s, int i, int l) {
            string ss(s);
            size_t ai1, al1;
            LongestSubStringWithUniqueChars1(ss, ai1, al1);
            size_t ai2, al2;
            LongestSubStringWithUniqueChars1(ss, ai2, al2);
            Logger().WriteInformation(
                "%s, (%d%s%d, %d%s%d), %s\n",
                ss.c_str(),
                ai1,
                ai1 == i ? "==" : "!=",
                i,
                al1,
                al1 == l ? "==" : "!=",
                l,
                ss.substr(ai1, al1).c_str());
            Logger().WriteInformation(
                "%s, (%d%s%d, %d%s%d), %s\n",
                ss.c_str(),
                ai2,
                ai2 == i ? "==" : "!=",
                i,
                al2,
                al2 == l ? "==" : "!=",
                l,
                ss.substr(ai2, al2).c_str());
            ASSERT1(ai1 == i);
            ASSERT1(al1 == l);
            ASSERT1(ai2 == i);
            ASSERT1(al2 == l);
        };
        check("a", 0, 1);
        check("aa", 0, 1);
        check("ab", 0, 2);
        check("aaa", 0, 1);
        check("aba", 0, 2);
        check("aab", 1, 2);
        check("abc", 0, 3);
        check("abab", 0, 2);
        check("abba", 0, 2);
        check("abca", 0, 3);
        check("aabc", 1, 3);
        check("abac", 1, 3);
        check("abcd", 0, 4);
        check("abcabc", 0, 3);
        check("abcad", 1, 4);
        check("aaabcd", 2, 4);
        check("abcabcbb", 0, 3);
        for (int i = 0; i < 100; i++)
        {
            size_t len = 1 + (rand() % 100);
            string ss = Random::String(len);
            size_t ai1, al1;
            LongestSubStringWithUniqueChars1(ss, ai1, al1);
            size_t ai2, al2;
            LongestSubStringWithUniqueChars1(ss, ai2, al2);
            Logger().WriteInformation(
                "%s, (%d, %d), %s\n",
                ss.c_str(),
                ai1,
                al1,
                ss.substr(ai1, al1).c_str());
            Logger().WriteInformation(
                "%s, (%d, %d), %s\n",
                ss.c_str(),
                ai2,
                al2,
                ss.substr(ai2, al2).c_str());
            ASSERT1(ai1 == ai2);
            ASSERT1(al1 == al2);
        }
    });

    Add("ShortestSubStringContainingGivenChars", [&]() {
        {
            auto check = [&](const string &input, const string &chars, const string &expect) {
                int index1;
                int length1;
                ShortestSubStringContainingGivenChars::Solve1(chars, input, index1, length1);
                string match1 = index1 == -1 ? "" : input.substr(index1, length1);
                int index2;
                int length2;
                ShortestSubStringContainingGivenChars::Solve2(chars, input, index2, length2);
                string match2 = index2 == -1 ? "" : input.substr(index2, length2);
                int index3;
                int length3;
                ShortestSubStringContainingGivenChars::SolveGivenUniqueChars1(chars, input, index3, length3);
                string match3 = index3 == -1 ? "" : input.substr(index3, length3);
                int index4;
                int length4;
                ShortestSubStringContainingGivenChars::SolveGivenUniqueChars2(chars, input, index4, length4);
                string match4 = index4 == -1 ? "" : input.substr(index4, length4);
                Logger().WriteInformation("Input: %s\n", input.c_str());
                Logger().WriteInformation("Chars: %s\n", chars.c_str());
                Logger().WriteInformation("Match1: %s %s %s\n", match1.c_str(), match1 == expect ? "==" : "!=", expect.c_str());
                Logger().WriteInformation("Match2: %s %s %s\n", match2.c_str(), match2 == expect ? "==" : "!=", expect.c_str());
                Logger().WriteInformation("Match3: %s %s %s\n", match3.c_str(), match3 == expect ? "==" : "!=", expect.c_str());
                Logger().WriteInformation("Match4: %s %s %s\n", match4.c_str(), match4 == expect ? "==" : "!=", expect.c_str());
                ASSERT1(match1 == expect);
                ASSERT1(match2 == expect);
                ASSERT1(match3 == expect);
                ASSERT1(match4 == expect);
            };

            check("aaaaa", "a", "a");
            check("aaaaa", "b", "");
            check("aaaaa", "ab", "");
            check("abaa", "ab", "ab");
            check("abaa", "ba", "ab");
            check("ccab", "ab", "ab");
            check("ccab", "ba", "ab");
            check("aabaa", "ab", "ab");
            check("aabaa", "ba", "ab");
            check("ccaba", "ab", "ab");
            check("ccaba", "ba", "ab");
            check("aacbddaa", "ba", "acb");
            check("aacdbddbeaa", "ab", "bea");
            check("ADOBECODEBANC", "ABC", "BANC");
            check("aabbbccaa", "abc", "bcca");
            check("aabbbccbaa", "abc", "cba");
            check("bcdfdefdcfeecgfacecdeagadcb", "dcgab", "gadcb");
            check("cfegdgbddacafeaccceccedgagfcbagcfbcdfdefdcfeecgfacecdeagadcbeddcacadebafcdcga", "dcgab", "gadcb");
        }
        {
            auto check = [&](const string &input, const string &chars, const string &expect) {
                int index1;
                int length1;
                ShortestSubStringContainingGivenChars::Solve1(chars, input, index1, length1);
                string match1 = index1 == -1 ? "" : input.substr(index1, length1);
                int index2;
                int length2;
                ShortestSubStringContainingGivenChars::Solve2(chars, input, index2, length2);
                string match2 = index2 == -1 ? "" : input.substr(index2, length2);
                Logger().WriteInformation("Input: %s\n", input.c_str());
                Logger().WriteInformation("Chars: %s\n", chars.c_str());
                Logger().WriteInformation("Match1: %s %s %s\n", match1.c_str(), match1 == expect ? "==" : "!=", expect.c_str());
                Logger().WriteInformation("Match2: %s %s %s\n", match2.c_str(), match2 == expect ? "==" : "!=", expect.c_str());
                ASSERT1(match1 == expect);
                ASSERT1(match2 == expect);
            };

            check("aaaaa", "aa", "aa");
            check("aaaaa", "bb", "");
            check("aaaaa", "aba", "");
            check("abaa", "aab", "aba");
            check("abaa", "aba", "aba");
            check("ccab", "ccab", "ccab");
            check("ccab", "cba", "cab");
            check("aabaa", "aaab", "aaba");
            check("aabaa", "baa", "aab");
            check("ccaba", "aab", "aba");
            check("ccaba", "aba", "aba");
            check("aacbddaa", "aba", "aacb");
            check("aacdbddbeaa", "aabb", "bddbeaa");
            check("ADOBECODEBANC", "ABCC", "CODEBANC");
            check("aabbbccaa", "abbc", "abbbc");
            check("aabbbccbaa", "aabcc", "ccbaa");
        }
        {
            auto length = [&](int max) -> int {
                return 1 + rand() % max;
            };
            string alphabet = "abcdefg";
            auto random = [&](int len) -> string {
                string output = Random::String(len, alphabet);
                return output;
            };
            for (int i = 0; i < 1000; i++)
            {
                string chars = random(length(10));
                string input = random(length(100));
                int index1;
                int length1;
                ShortestSubStringContainingGivenChars::Solve1(chars, input, index1, length1);
                string match1 = index1 == -1 ? "" : input.substr(index1, length1);
                int index2;
                int length2;
                ShortestSubStringContainingGivenChars::Solve2(chars, input, index2, length2);
                string match2 = index2 == -1 ? "" : input.substr(index2, length2);
                Logger().WriteInformation("Input: %s\n", input.c_str());
                Logger().WriteInformation("Chars: %s\n", chars.c_str());
                Logger().WriteInformation("%s %s %s\n", match1.c_str(), match1 == match2 ? "==" : "!=", match2.c_str());
                ASSERT1(match1 == match2);
                if (ContainsUniqueChars(chars))
                {
                    int index3;
                    int length3;
                    ShortestSubStringContainingGivenChars::SolveGivenUniqueChars1(chars, input, index3, length3);
                    string match3 = index3 == -1 ? "" : input.substr(index3, length3);
                    Logger().WriteInformation("%s %s %s\n", match1.c_str(), match1 == match3 ? "==" : "!=", match3.c_str());
                    int index4;
                    int length4;
                    ShortestSubStringContainingGivenChars::SolveGivenUniqueChars2(chars, input, index4, length4);
                    string match4 = index4 == -1 ? "" : input.substr(index4, length4);
                    Logger().WriteInformation("%s %s %s\n", match1.c_str(), match1 == match4 ? "==" : "!=", match4.c_str());
                    ASSERT1(match1 == match4);
                }
            }
        }
    });

    Add("ReplaceWithShorterString", [&]() {
        auto check = [&](char *input, char *pattern, char *shorter, char *expect) {
            Logger().WriteInformation("\nInput:   %s\n", input);
            Logger().WriteInformation("Pattern: %s\n", pattern);
            Logger().WriteInformation("Shorter: %s\n", shorter);
            ReplaceWithShorterString(input, pattern, shorter);
            Logger().WriteInformation("Output:  %s\n", input);
            while (*input != '\0')
            {
                ASSERT1(*input++ == *expect++);
            }
        };
        char A[][4][256] = {
            {"a", "a", "X", "X"},
            {"aa", "aa", "X", "X"},
            {"aa", "a", "X", "X"},
            {"aa", "aaa", "X", "aa"},
            {"abc", "abc", "X", "X"},
            {"abcabc", "abc", "X", "X"},
            {"abcabcabc", "abc", "X", "X"},
            {"abcaabcaabc", "abc", "X", "XaXaX"},
            {"abcaaabcaaabca", "abc", "X", "XaaXaaXa"},
            {"abcabcabababcabc", "abc", "X", "XababX"},
            {"abcabcabababcabcab", "abc", "X", "XababXab"},
            {"aabbaabbaaabbbaabb", "aabb", "X", "XaXbX"},
            {"aabbaabbaaabbbaabb", "aaabb", "X", "aabbaabbXbaabb"},
            {"aabbaabbaaabbbaaabb", "aaabb", "X", "aabbaabbXbX"},
            {"aabbaabbaaabbbaaabc", "aaabb", "X", "aabbaabbXbaaabc"},
            {"abcdeffdfegabcabc", "abc", "X", "XdeffdfegX"},
            {"abcdeffdfegabcabc", "ab", "X", "XcdeffdfegXcXc"},
            {"abcdeffdfegabcabc", "a", "X", "XbcdeffdfegXbcXbc"},
            {"abcdeffdfegabcab", "abc", "X", "XdeffdfegXab"},
            {"abcdeffdfegabcabcab", "abc", "X", "XdeffdfegXab"},
            {"abcdeffdfegabcaabcab", "abc", "X", "XdeffdfegXaXab"},
            {"abcdeffdfegabcaaaabcab", "abc", "X", "XdeffdfegXaaaXab"},
            {"aaaaaa", "a", "X", "X"},
            {"aaaaaa", "aa", "X", "X"},
            {"aaaaaa", "aaaaaa", "X", "X"},
            {"aaaaaa", "aaaaaaa", "X", "aaaaaa"},
            {"aabaababaaab", "a", "X", "XbXbXbXb"},
            {"aabaababaaa", "a", "X", "XbXbXbX"},
            {"aaaab", "a", "X", "Xb"},
            {"baaa", "a", "X", "bX"},
            {"aabaaabaab", "aaa", "X", "aabXbaab"},
            {"aabaaabaab", "aa", "X", "XbXabXb"},
            {"aabaaabaa", "aa", "X", "XbXabX"},
            {"aa", "aa", "XY", "XY"},
            {"aa", "aaa", "XY", "aa"},
            {"abc", "abc", "XY", "XY"},
            {"abcabc", "abc", "XY", "XY"},
            {"abcabcabc", "abc", "XY", "XY"},
            {"abcaabcaabc", "abc", "XY", "XYaXYaXY"},
            {"abcaaabcaaabca", "abc", "XY", "XYaaXYaaXYa"},
            {"abcabcabababcabc", "abc", "XY", "XYababXY"},
            {"abcabcabababcabcab", "abc", "XY", "XYababXYab"},
            {"aabbaabbaaabbbaabb", "aabb", "XY", "XYaXYbXY"},
            {"aabbaabbaaabbbaabb", "aaabb", "XY", "aabbaabbXYbaabb"},
            {"aabbaabbaaabbbaaabb", "aaabb", "XY", "aabbaabbXYbXY"},
            {"aabbaabbaaabbbaaabc", "aaabb", "XY", "aabbaabbXYbaaabc"},
            {"abcdeffdfegabcabc", "abc", "XY", "XYdeffdfegXY"},
            {"abcdeffdfegabcabc", "ab", "XY", "XYcdeffdfegXYcXYc"},
            {"abcdeffdfegabcab", "abc", "XY", "XYdeffdfegXYab"},
            {"abcdeffdfegabcabcab", "abc", "XY", "XYdeffdfegXYab"},
            {"abcdeffdfegabcaabcab", "abc", "XY", "XYdeffdfegXYaXYab"},
            {"abcdeffdfegabcaaaabcab", "abc", "XY", "XYdeffdfegXYaaaXYab"},
            {"aaaaaa", "aa", "XY", "XY"},
            {"aaaaaa", "aaaaaa", "XY", "XY"},
            {"aaaaaa", "aaaaaaa", "XY", "aaaaaa"},
            {"aabaaabaab", "aaa", "XY", "aabXYbaab"},
            {"aabaaabaab", "aa", "XY", "XYbXYabXYb"},
            {"aabaaabaa", "aa", "XY", "XYbXYabXY"}};
        int len = sizeof(A) / sizeof(A[0]);
        for (int i = 0; i < len; i++)
        {
            check(A[i][0], A[i][1], A[i][2], A[i][3]);
        }
    });

    Add("RemoveExtraSpaces", [&]() {
        auto check = [&](char *input, char *expect) {
            Logger().WriteInformation("\"%s\"", input);
            RemoveExtraSpaces(input);
            Logger().WriteInformation("\t=>\t\"%s\"\n", input);
            ASSERT1(0 == strcmp(input, expect));
        };
        {
            char a[] = "";
            char b[] = "";
            check(a, b);
        }
        {
            char a[] = "   ";
            char b[] = "";
            check(a, b);
        }
        {
            char a[] = "ABCDEFG";
            char b[] = "ABCDEFG";
            check(a, b);
        }
        {
            char a[] = "A B C D E F G";
            char b[] = "A B C D E F G";
            check(a, b);
        }
        {
            char a[] = "AB CD EFG";
            char b[] = "AB CD EFG";
            check(a, b);
        }
        {
            char a[] = "AB   CD  EFG";
            char b[] = "AB CD EFG";
            check(a, b);
        }
        {
            char a[] = "ABCD     EFG";
            char b[] = "ABCD EFG";
            check(a, b);
        }
        {
            char a[] = " ABCDEFG ";
            char b[] = "ABCDEFG";
            check(a, b);
        }
        {
            char a[] = "    ABCDEFG    ";
            char b[] = "ABCDEFG";
            check(a, b);
        }
        {
            char a[] = "    A B C D E F G    ";
            char b[] = "A B C D E F G";
            check(a, b);
        }
        {
            char a[] = "    A B  C   D    E   F  G    ";
            char b[] = "A B C D E F G";
            check(a, b);
        }
        {
            char a[] = "    AB CD EF G    ";
            char b[] = "AB CD EF G";
            check(a, b);
        }
        {
            char a[] = "    AB CD  EF   GHI  JK L    ";
            char b[] = "AB CD EF GHI JK L";
            check(a, b);
        }
    });

    Add("ReverseWords", [&]() {
        auto check = [&](const char *input, const string &expect) {
            Logger().WriteInformation("\nInput:  %s\n", input);
            string input1(input);
            size_t len = strlen(input);
            unique_ptr<char[]> input2(new char[len + 1]);
            strcpy_s(input2.get(), len + 1, input);
            ReverseWords(input1);
            ReverseWords(input2.get());
            Logger().WriteInformation("Output: %s\n", input1.c_str());
            Logger().WriteInformation("Output: %s\n", input2.get());
            string input3(input2.get());
            ASSERT1(input1 == expect);
            ASSERT1(input3 == expect);
        };
        check("a", "a");
        check("", "");
        check(" ", "");
        check("  ", "");
        check("ab", "ab");
        check("a b", "b a");
        check("a  b", "b a");
        check(" a b ", "b a");
        check("  a  b  ", "b a");
        check("  ab  cd  ", "cd ab");
        check("   This is a test!   ", "test! a is This");
    });

    Add("StrStr", [&]() {
        auto check = [&](char *input1, char *input2, int index) {
            Logger().WriteInformation("\nInput1:\t%s\n", input1);
            Logger().WriteInformation("Input2:\t%s\n", input2);
            const char *p1 = StrStr1(input1, input2);
            int i1 = (int)(p1 == nullptr ? -1 : p1 - input1);
            const char *p2 = StrStr2(input1, input2);
            int i2 = (int)(p2 == nullptr ? -1 : p2 - input1);
            const char *p3 = strstr(input1, input2);
            int i3 = (int)(p3 == nullptr ? -1 : p3 - input1);
            Logger().WriteInformation("Index:\t%d\t%d\t%d\n", i1, i2, i3);
            ASSERT1(i1 == index);
            ASSERT1(i2 == index);
            ASSERT1(i3 == index);
        };
        check("", "", 0);
        check("", "a", -1);
        check("a", "", 0);
        check("a", "a", 0);
        check("a", "b", -1);
        check("a", "aa", -1);
        check("aa", "a", 0);
        check("aa", "b", -1);
        check("aa", "aa", 0);
        check("aa", "aaa", -1);
        check("ab", "a", 0);
        check("ab", "b", 1);
        check("ab", "c", -1);
        check("ab", "ab", 0);
        check("abc", "a", 0);
        check("abc", "b", 1);
        check("abc", "c", 2);
        check("abc", "d", -1);
        check("abc", "ab", 0);
        check("abc", "bc", 1);
        check("abc", "abc", 0);
        check("ababa", "ab", 0);
        check("ababa", "ba", 1);
        check("ababa", "aba", 0);
        check("ababa", "bab", 1);
        check("ababa", "ababa", 0);
        check("abcabcab", "abc", 0);
        check("abcabcab", "bca", 1);
        check("abcabcab", "cab", 2);
        check("abdabcab", "abc", 3);
        check("abdabcab", "bca", 4);
        check("abdabcab", "cab", 5);
    });

    Add("BreakWord", [&]() {
        function<void(Log &, const string &)>
            print = [&](Log &l, const string &s) {
                l.WriteInformation("%s", s.c_str());
            };

        auto check = [&](string s, unordered_set<string> &dict) {
            Logger().WriteInformation("Input: %s\n", s.c_str());
            Logger().WriteInformation("Dictionary: ");
            Logger().Print(dict, print, " ");
            bool breakable = BreakWords::Solvable(s, dict);
            if (breakable)
                Logger().WriteInformation("breakable\n");
            else
                Logger().WriteInformation("unbreakable\n");
            vector<string> sentences1 = BreakWords::Solve1(s, dict);
            vector<string> sentences2 = BreakWords::Solve2(s, dict);
            Logger().WriteInformation("Output1:\n");
            Logger().Print(sentences1, print, "\n");
            Logger().WriteInformation("Output2:\n");
            Logger().Print(sentences2, print, "\n");
            ASSERT1(sentences1.size() == sentences2.size());
            sort(sentences1.begin(), sentences1.end());
            sort(sentences2.begin(), sentences2.end());
            for (size_t i = 0; i < sentences1.size(); i++)
            {
                ASSERT1(sentences1[i] == sentences2[i]);
            }
        };
        {
            string s = "catsanddog";
            unordered_set<string> dict = {"cat", "cats", "and", "sand", "dog"};
            check(s, dict);
        }
        {
            string s;
            unordered_set<string> dict = {"cat", "cats", "and", "sand", "dog"};
            check(s, dict);
        }
        {
            string s = "aaaaaaa";
            unordered_set<string> dict = {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa"};
            check(s, dict);
        }
        {
            string s = "dogs";
            unordered_set<string> dict = {"dog", "s", "gs"};
            check(s, dict);
        }
    });

    Add("LongestConsecutiveSequence", [&]() {
        auto check = [&](vector<int> &input, int expectBegin, int expectLength) {
            Logger().WriteInformation("Input: ");
            Logger().Print(input);
            int begin1;
            size_t length1;
            LongestConsecutiveSequence1(input, begin1, length1);
            Logger().WriteInformation("  Begin:  %d %s %d\n", begin1, begin1 == expectBegin ? "==" : "!=", expectBegin);
            Logger().WriteInformation("  Length: %d %s %d\n", length1, length1 == expectLength ? "==" : "!=", expectLength);
            int begin2;
            size_t length2;
            LongestConsecutiveSequence2(input, begin2, length2);
            Logger().WriteInformation("  Begin2:  %d %s %d\n", begin2, begin2 == expectBegin ? "==" : "!=", expectBegin);
            Logger().WriteInformation("  Length2: %d %s %d\n", length2, length2 == expectLength ? "==" : "!=", expectLength);
            ASSERT1(begin1 == expectBegin);
            ASSERT1(length1 == expectLength);
            ASSERT1(begin2 == expectBegin);
            ASSERT1(length2 == expectLength);
        };
        {
            vector<int> input = {0};
            check(input, 0, 1);
        }
        {
            vector<int> input = {0, 0};
            check(input, 0, 1);
        }
        {
            vector<int> input = {0, 1};
            check(input, 0, 2);
        }
        {
            vector<int> input = {1, 0};
            check(input, 0, 2);
        }
        {
            vector<int> input = {0, 2};
            check(input, 0, 1);
        }
        {
            vector<int> input = {0, 1, 2};
            check(input, 0, 3);
        }
        {
            vector<int> input = {0, 1, 3};
            check(input, 0, 2);
        }
        {
            vector<int> input = {-1, 1, 2};
            check(input, 1, 2);
        }
        {
            vector<int> input = {0, -1, 2};
            check(input, -1, 2);
        }
        {
            vector<int> input = {3, 1, 2};
            check(input, 1, 3);
        }
        {
            vector<int> input = {0, 1, 1};
            check(input, 0, 2);
        }
        {
            vector<int> input = {1, 0, 1, 1};
            check(input, 0, 2);
        }
        {
            vector<int> input = {1, 0, 1, 0};
            check(input, 0, 2);
        }
        {
            vector<int> input = {1, 0, -1};
            check(input, -1, 3);
        }
        {
            vector<int> input = {0, 1, 2, 1};
            check(input, 0, 3);
        }
        {
            vector<int> input = {-7, -1, 3, -9, -4, 7, -3, 2, 4, 9, 4, -9, 8, -7, 5, -1, -7};
            check(input, 2, 4);
        }
        {
            vector<int> input = {-6, 8, -5, 7, -9, -1, -7, -6, -9, -7, 5, 7, -1, -8, -8, -2, 0};
            check(input, -9, 5);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                vector<int> input;
                Random(input);
                Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
                if (input.size() == 0)
                    continue;
                int begin1;
                size_t length1;
                LongestConsecutiveSequence1(input, begin1, length1);
                int begin2;
                size_t length2;
                LongestConsecutiveSequence1(input, begin2, length2);
                Logger().WriteInformation("  Begin:  %d %s %d\n", begin1, begin1 == begin2 ? "==" : "!=", begin2);
                Logger().WriteInformation("  Length: %d %s %d\n", length1, length1 == length2 ? "==" : "!=", length2);
                ASSERT1(begin1 == begin2);
                ASSERT1(length1 == length2);
            }
        }
    });

    Add("Partition", [&]() {
        {
            vector<int> I = {3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64};
            int L = (int)I.size();

            int i = PartitionByValue(I, 0, 0, 3);
            ASSERT1(i == 0);

            i = PartitionByValue(I, L - 1, L - 1, 64);
            ASSERT1(i == L - 1);

            i = PartitionByValue(I, 0, 1, 43);
            ASSERT1(i == 1);
            ASSERT1(I[0] == 3);
            ASSERT1(I[1] == 43);

            i = PartitionByValue(I, 2, 3, 1);
            ASSERT1(i == 2);
            ASSERT1(I[2] == 1);
            ASSERT1(I[3] == 42);

            i = PartitionByValue(I, 0, L - 1, 64);
            ASSERT1(i >= 0);
            ASSERT1(i <= L - 1);
            for (int j = 0; j < L - 1; j++)
            {
                if (j < i)
                    ASSERT1(I[j] <= I[i]);
                else if (j > i)
                    ASSERT1(I[j] >= I[i]);
            }

            for (int k = 0; k < 10; k++)
            {
                Random(I, 100);
                L = (int)I.size();
                Logger().Print(I);
                i = PartitionRandomly(I, 0, L - 1);
                Logger().WriteInformation("Partition by %d at index %d:\n", I[i], i);
                Logger().Print(I);
                ASSERT1(i >= 0);
                ASSERT1(i <= L - 1);
                for (int j = 0; j < L - 1; j++)
                    if (j < i)
                        ASSERT1(I[j] <= I[i]);
                    else if (j > i)
                        ASSERT1(I[j] > I[i]);
                Logger().WriteInformation("\n");
            }
        }
        {
            vector<int> I = {3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64};
            int L = (int)I.size();

            int i = PartitionByOrder(I, 0, 0, 0);
            ASSERT1(i == 3);

            i = PartitionByOrder(I, L - 1, L - 1, 0);
            ASSERT1(i == 64);

            i = PartitionByOrder(I, 0, 1, 0);
            ASSERT1(i == 3);
            ASSERT1(I[0] == 3);
            ASSERT1(I[1] == 43);

            i = PartitionByOrder(I, 0, 1, 1);
            ASSERT1(i == 43);
            ASSERT1(I[0] == 3);
            ASSERT1(I[1] == 43);

            i = PartitionByOrder(I, 2, 3, 0);
            ASSERT1(i == 1);
            ASSERT1(I[2] == 1);
            ASSERT1(I[3] == 42);

            i = PartitionByOrder(I, 2, 3, 1);
            ASSERT1(i == 42);
            ASSERT1(I[2] == 1);
            ASSERT1(I[3] == 42);

            for (int p = 0; p < 100; p++)
            {
                Random(I, 100);
                L = (int)I.size();
                Logger().Print(I);
                int j = rand() % L;
                i = PartitionByOrder(I, 0, L - 1, j);
                Logger().WriteInformation("Partition by %d at index %d:\n", I[j], j);
                Logger().Print(I);
                ASSERT1(i == I[j]);
                for (int k = 0; k < L - 1; k++)
                    if (k < j)
                        ASSERT1(I[k] <= I[j]);
                    else if (k > j)
                        ASSERT1(I[k] >= I[j]);
                Logger().WriteInformation("\n");
            }
        }
    });

    Add("QuickSort", [&]() {
        {
            vector<int> I = {1};
            QuickSort(I);
            ASSERT1(I[0] == 1);
        }
        {
            vector<int> I = {2, 1};

            QuickSort(I);
            ASSERT1(I[0] == 1);
            ASSERT1(I[1] == 2);

            QuickSort(I);
            ASSERT1(I[0] == 1);
            ASSERT1(I[1] == 2);

            I[1] = I[0];
            QuickSort(I);
            ASSERT1(I[0] == 1);
            ASSERT1(I[1] == 1);
        }
        {
            vector<int> I = {3, 2, 1};

            QuickSort(I);
            ASSERT1(I[0] == 1);
            ASSERT1(I[1] == 2);
            ASSERT1(I[2] == 3);

            QuickSort(I);
            ASSERT1(I[0] == 1);
            ASSERT1(I[1] == 2);
            ASSERT1(I[2] == 3);

            I[1] = I[0];
            I[2] = I[0];
            QuickSort(I);
            ASSERT1(I[0] == 1);
            ASSERT1(I[1] == 1);
            ASSERT1(I[2] == 1);
        }
        {
            vector<int> V = {3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64};
            vector<int> I1, I2, I3;
            Duplicate(V, I1);
            Duplicate(V, I2);
            Duplicate(V, I3);

            QuickSort(I1);
            QuickSortInParallel(I2);
            QuickSortRandomly(I3);

            std::sort(V.begin(), V.end());

            for (int i = 0; i < V.size(); i++)
            {
                ASSERT1(V[i] == I1[i]);
                ASSERT1(V[i] == I2[i]);
                ASSERT1(V[i] == I3[i]);
            }
        }
        {
            vector<int> V = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
            vector<int> I;
            Duplicate(V, I);

            QuickSort(I);
            std::sort(V.begin(), V.end());

            for (int i = 0; i < V.size(); i++)
            {
                ASSERT1(V[i] == I[i]);
            }
        }
        {
            vector<int> V = {0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2};
            vector<int> I;
            Duplicate(V, I);

            QuickSort(I);
            std::sort(V.begin(), V.end());

            for (int i = 0; i < V.size(); i++)
            {
                ASSERT1(V[i] == I[i]);
            }
        }
        {
            for (int i = 0; i < 100; i++)
            {
                vector<int> v;
                Random(v);
                Logger().WriteInformation("Run %d: %d elements\n", i, v.size());

                vector<int> i1, i2, i3;
                Duplicate(v, i1);
                Duplicate(v, i2);
                Duplicate(v, i3);

                QuickSort(i1);
                QuickSortInParallel(i2);
                QuickSortRandomly(i3);

                std::sort(v.begin(), v.end());

                for (int i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == i1[i]);
                    ASSERT1(v[i] == i2[i]);
                    ASSERT1(v[i] == i3[i]);
                }
            }
        }
    });

    Add("RadixSort", [&]() {
        {
            auto check = [&](vector<vector<int>> v) -> bool {
                for (int i = 1; i < (int)v.size(); i++)
                {
                    for (int j = (int)v[0].size() - 1; j >= 0; j--)
                    {
                        if (v[i - 1][j] < v[i][j])
                            return true;
                        if (v[i - 1][j] > v[i][j])
                            return false;
                    }
                }
                return true;
            };

            for (int i = 0; i < 100; i++)
            {
                Logger().WriteInformation("Run %d:\n", i);
                vector<vector<int>> v;
                Random(v, 50, 50, 20);
                Logger().WriteInformation("Input:\n");
                Logger().Print(v, "%2d");
                RadixSort(v);
                Logger().WriteInformation("Sorted:\n");
                Logger().Print(v, "%2d");
                ASSERT1(true == check(v));
            }
        }
    });

    Add("PositionToInsert", [&]() {
        {
            int e = 2;
            int n = 100;
            vector<int> input(n, e);
            int i = PositionToInsert(e, input);
            ASSERT1(-1 == i);
            i = PositionToInsert(e, input, false);
            ASSERT1(n - 1 == i);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                vector<int> input;
                Random(input, 200, 200);
                Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
                sort(input.begin(), input.end());
                Logger().Print(input);
                for (int j = 0; j < 10; j++)
                {
                    int e1 = rand() % 50;
                    int e2 = input[rand() % input.size()];
                    Logger().WriteInformation("Found %d", e1);
                    int i1 = PositionToInsert(e1, input);
                    Logger().WriteInformation(" at %d\n", i1);
                    Logger().WriteInformation("Found %d", e2);
                    int i2 = PositionToInsert(e2, input);
                    Logger().WriteInformation(" at %d\n", i2);
                    if (i1 >= 0)
                        ASSERT1(input[i1] < e1);
                    if (i1 < (int)input.size() - 1)
                        ASSERT1(e1 <= input[i1 + 1]);
                    if (i2 >= 0)
                        ASSERT1(input[i2] < e2);
                    if (i2 < (int)input.size() - 1)
                        ASSERT1(e2 <= input[i2 + 1]);
                }
            }
        }
        {
            for (int i = 0; i < 100; i++)
            {
                vector<int> input;
                Random(input, 200, 200);
                Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
                sort(input.begin(), input.end());
                Logger().Print(input);
                for (int j = 0; j < 10; j++)
                {
                    int e1 = rand() % 50;
                    int e2 = input[rand() % input.size()];
                    Logger().WriteInformation("Found %d", e1);
                    int i1 = PositionToInsert(e1, input, false);
                    Logger().WriteInformation(" at %d\n", i1);
                    Logger().WriteInformation("Found %d", e2);
                    int i2 = PositionToInsert(e2, input, false);
                    Logger().WriteInformation(" at %d\n", i2);
                    if (i1 >= 0)
                        ASSERT1(input[i1] <= e1);
                    if (i1 < (int)input.size() - 1)
                        ASSERT1(e1 < input[i1 + 1]);
                    if (i2 >= 0)
                        ASSERT1(input[i2] <= e2);
                    if (i2 < (int)input.size() - 1)
                        ASSERT1(e2 < input[i2 + 1]);
                }
            }
        }
    });

    Add("Sort", [&]() {
        auto check = [&](vector<int> &input) {
            Logger().WriteInformation("Input:  ");
            Logger().Print(input);
            size_t count = 11;
            vector<vector<int>> inputs(count, vector<int>{});
            for_each(inputs.begin(), inputs.end(), [&](vector<int> &v) {
                Duplicate(input, v);
            });

            sort(input.begin(), input.end());
            Logger().WriteInformation("Sorted: ");
            Logger().Print(input);

            QuickSort(inputs[0]);
            QuickSortInParallel(inputs[1]);
            QuickSortRandomly(inputs[2]);
            InsertSort(inputs[3]);
            InsertSortRecursively(inputs[4], inputs[4].size());
            SelectSort(inputs[5]);
            MergeSort(inputs[6]);
            HeapSort(inputs[7]);
            HeapSortInParallel(inputs[8]);
            HeapSort(inputs[9], 3);
            HeapSortInParallel(inputs[10], 3);
            for (size_t i = 0; i < input.size(); i++)
            {
                for (size_t j = 0; j < count; j++)
                {
                    ASSERT2(
                        inputs[j][i] == input[i],
                        String::Format("inputs[%d][%d] = %d != %d\n", j, i, inputs[j][i], input[i]));
                }
            }
        };
        {
            vector<int> i = {1};
            check(i);
        }
        {
            vector<int> i = {1, 2};
            check(i);
        }
        {
            vector<int> i = {2, 1};
            check(i);
        }
        {
            vector<int> i = {2, 2};
            check(i);
        }
        {
            vector<int> i = {1, 2, 3};
            check(i);
        }
        {
            vector<int> i = {2, 1, 3};
            check(i);
        }
        {
            vector<int> i = {3, 1, 2};
            check(i);
        }
        {
            vector<int> i = {2, 2, 3};
            check(i);
        }
        {
            vector<int> i = {2, 3, 2};
            check(i);
        }
        {
            vector<int> i = {3, 2, 2};
            check(i);
        }
        {
            vector<int> i = {3, 3, 3};
            check(i);
        }
        {
            for (int i = 0; i < 1000; i++)
            {
                vector<int> input;
                Random(input, 200, 200);
                Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
                check(input);
            }
        }
    });

    Add("MergeSort", [&]() {
        {
            vector<vector<int>> inputs = {
                {0, 5, 9, 11},
                {0, 1, 2, 3, 5, 6},
                {6, 7, 8}};

            Logger().Print(inputs);

            vector<int> output;

            MergeSort(inputs, output);

            ASSERT1(is_sorted(output.begin(), output.end()));
            ASSERT1(output.size() == 13);

            Logger().Print(output);
            Logger().WriteInformation("\n");
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int count = 1 + rand() % 10;
                vector<vector<int>> inputs(count, vector<int>{});
                size_t size = 0;
                for (int j = 0; j < count; j++)
                {
                    Random(inputs[j], 10, 100);
                    size += inputs[j].size();
                    sort(inputs[j].begin(), inputs[j].end());
                }
                Logger().WriteInformation("Run %d: %d elements\n", i, size);
                Logger().Print(inputs);
                vector<int> output;
                MergeSort(inputs, output);
                Logger().Print(output);
                ASSERT1(is_sorted(output.begin(), output.end()));
                ASSERT1(output.size() == size);
            }
        }
    });

    Add("HeapSort", [&]() {
        {
            for (int j = 0; j < 100; j++)
            {
                vector<int> i1;
                Random(i1);
                Logger().WriteInformation("Run %d, %d elements\n", j, i1.size());
                vector<int> i2;
                Duplicate(i1, i2);

                Heapify(i1);
                HeapifyInParallel(i2);

                for (size_t i = 0; i < i1.size(); i++)
                {
                    ASSERT2(i1[i] == i2[i], String::Format("i1[%d] %d != i2[%d] %d", i, i1[i], i, i2[i]));
                }
            }
        }
        {
            for (int j = 0; j < 100; j++)
            {
                vector<int> a, v;
                Random(a);
                Duplicate(a, v);
                unsigned int dimension = 2 + (rand() % 100);
                Logger().WriteInformation("Run %d, %d elements, %d-heap\n", j, a.size(), dimension);

                HeapSort(a, dimension);
                std::make_heap(v.begin(), v.end());
                std::sort_heap(v.begin(), v.end());

                for (size_t i = 0; i < a.size(); i++)
                {
                    ASSERT2(a[i] == v[i], String::Format("i[%d] %d != v[%d] %d", i, a[i], i, v[i]));
                }
            }
        }
        {
            for (int j = 0; j < 100; j++)
            {
                vector<int> i1, i2;
                Random(i1);
                Duplicate(i1, i2);
                unsigned int dimension = 2 + (rand() % 100);
                Logger().WriteInformation("Run %d, %d elements, %d-heap\n", j, i1.size(), dimension);

                Heapify(i1, dimension);
                HeapifyInParallel(i2, dimension);

                for (size_t i = 0; i < i1.size(); i++)
                {
                    ASSERT2(i1[i] == i2[i], String::Format("i1[%d] %d != i2[%d] %d", i, i1[i], i, i2[i]));
                }
            }
        }
    });
}

#endif