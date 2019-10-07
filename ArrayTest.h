#ifndef _ARRAYTEST_H_
#define _ARRAYTEST_H_

#include "Array.h"
#include "Random.h"
#include "Test.h"

using namespace Test;

class ArrayTest : public TestClass
{
  public:
    ArrayTest(Log &log) : TestClass(log) {}
    ~ArrayTest(void) {}
    void Init(void);
};

void ArrayTest::Init(void)
{
	Add("Rotate", [&]() {
		auto check = [&](int length) {
			unique_ptr<int[]> input(new int[length]);
			Random::Array(input.get(), length);
			unique_ptr<int[]> input2(new int[length]);
            memcpy(input2.get(), input.get(), length * sizeof(int));
			for (int i = 0; i <= 2 * length; i++) {
				RotateLeft(input.get(), length, i);
				RotateLeft2(input2.get(), length, i);
				Logger().Print(input.get(), length);
				Logger().Print(input2.get(), length);
				ASSERT1(true == Equal(input.get(), input2.get(), length));
				RotateRight(input.get(), length, i);
				RotateRight2(input2.get(), length, i);
				Logger().Print(input.get(), length);
				Logger().Print(input2.get(), length);
				ASSERT1(true == Equal(input.get(), input2.get(), length));
			}
		};
		for (int i = 1; i < 20; i++) {
			check(i);
		}
	});

	Add("Transpose", [&]() {
		auto check = [&](int length, int columns) {
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Sequential(A.get(), length);
			Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			Transpose(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = j * rows + i;
					ASSERT1(A[s] == B[t]);
				}
			}
			Transpose<int>(B.get(), length, rows);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		};
		check(1, 1);
		check(5, 5);
		check(5, 1);
		check(15, 5);
		check(60, 6);
		check(64, 8);
	});

	Add("RowsColumns", [&](){
		{
			int length = 64;
			int columns = 8;
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Sequential(A.get(), length);
			Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			TransposeRowsToColumns<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = j * rows + i;
					ASSERT1(A[s] == B[t]);
				}
			}
			TransposeColumnsToRows<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		}
		{
			int length = 16;
			int columns = 8;
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Sequential(A.get(), length);
			Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			TransposeRowsToColumns<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			// Transpose element (m,n) to ((n % M), (k(m-1) + n/M)) means the index i = Nm + n is mapped to j = (n % M)N + k(m-1) + n/M
			int k = columns / rows;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = (j % rows) * columns + k * i + j / rows;
					ASSERT1(A[s] == B[t]);
				}
			}
			TransposeColumnsToRows<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		}
		{
			int length = 27;
			int columns = 3;
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Sequential(A.get(), length);
			Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			TransposeRowsToColumns<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			// Transpose element (m,n) to ((m%k)N + n, m/k)) means the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
			int k = rows / columns;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = (i % k) * columns * columns + j * columns + i / k;
					ASSERT1(A[s] == B[t]);
				}
			}
			TransposeColumnsToRows<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		}
	});
}
#endif