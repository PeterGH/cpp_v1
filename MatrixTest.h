#ifndef _MATRIXTEST_H_
#define _MATRIXTEST_H_

#include "Matrix.h"
#include "Test.h"

using namespace Test;

class MatrixTest : public TestClass
{
public:
    MatrixTest(Log &log) : TestClass(log) {}
    ~MatrixTest(void) {}
    void Init(void);
};

void MatrixTest::Init()
{
    Add("Matrix", [&]() {
        Matrix<int> B(3, 4);
        Logger().Print(B);
        B(1, 2) = 101;
        Logger().Print(B, "%d", "\t");
        int v = B(1, 2);
        ASSERT1(101 == v);
        B(2, 3) = 202;
        auto p = [&](Log &l, int &x) { l.WriteInformation("%d", x); };
        Logger().Print<int>(B, p, "\t");
        v = B(2, 3);
        ASSERT1(202 == v);
        const int w = B(2, 3);
        ASSERT1(202 == w);
        v = 203;
        Logger().Print(B, "%d", "\t");
        ASSERT1(202 == B(2, 3));
        int &x = B(2, 3);
        x = 204;
        Logger().Print(B, "%d", "\t");
        ASSERT1(204 == B(2, 3));
    });

    Add("LowerTriangularMatrix", [&]() {
        LowerTriangularMatrix<int> B(4, 3);
        Logger().Print(B);
        B(2, 1) = 101;
        Logger().Print(B, "%d", "\t");
        int v = B(2, 1);
        ASSERT1(101 == v);
        B(3, 2) = 202;
        auto p = [&](Log &l, int x) { l.WriteInformation("%d", x); };
        Logger().Print<int>(B, p, "\t");
        v = B(3, 2);
        ASSERT1(202 == v);
        const int w = B(3, 2);
        ASSERT1(202 == w);
        ASSERTERROR(B(0, 1) = 0, invalid_argument);
        const LowerTriangularMatrix<int> A(4, 3);
        ASSERT1(A(0, 1) == 0);
        LowerTriangularMatrix<int> C(4, 5);
        Logger().Print(C);
        C(2, 1) = 101;
        Logger().Print(C, "%d", "\t");
        v = C(2, 1);
        ASSERT1(101 == v);
        C(3, 2) = 202;
        Logger().Print<int>(C, p, "\t");
        v = C(3, 2);
        ASSERT1(202 == v);
        const int y = C(3, 2);
        ASSERT1(202 == y);
        ASSERTERROR(C(0, 1) = 0, invalid_argument);
        const LowerTriangularMatrix<int> D(4, 5);
        ASSERT1(D(0, 1) == 0);
    });

    Add("UpperTriangularMatrix", [&]() {
        UpperTriangularMatrix<int> B(3, 4);
        Logger().Print(B);
        B(1, 2) = 101;
        Logger().Print(B, "%d", "\t");
        int v = B(1, 2);
        ASSERT1(101 == v);
        B(2, 3) = 202;
        auto p = [&](Log &l, int x) { l.WriteInformation("%d", x); };
        Logger().Print<int>(B, p, "\t");
        v = B(2, 3);
        ASSERT1(202 == v);
        const int w = B(2, 3);
        ASSERT1(202 == w);
        ASSERTERROR(B(1, 0) = 0, invalid_argument);
        const UpperTriangularMatrix<int> A(3, 4);
        ASSERT1(A(1, 0) == 0);
        UpperTriangularMatrix<int> C(5, 4);
        Logger().Print(C);
        C(1, 2) = 101;
        Logger().Print(C, "%d", "\t");
        v = C(1, 2);
        ASSERT1(101 == v);
        C(2, 3) = 202;
        Logger().Print<int>(C, p, "\t");
        v = C(2, 3);
        ASSERT1(202 == v);
        const int y = C(2, 3);
        ASSERT1(202 == y);
        ASSERTERROR(C(1, 0) = 0, invalid_argument);
        const UpperTriangularMatrix<int> D(5, 4);
        ASSERT1(D(1, 0) == 0);
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
}

#endif