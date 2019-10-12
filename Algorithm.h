#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include "Matrix.h"

using namespace std;

namespace Test
{
// http://leetcode.com/2011/01/ctrla-ctrlc-ctrlv.html
// Produce the longest string with N keystrokes using four
// keys: A, Ctrl+A (Select), Ctrl+C (Copy), Ctrl+V (Paste)
// If we encode the keys with letters 'A', 'S', 'C', 'P' then
// the keystrokes form a sequence of these four letters.
// 1. One occurrence of (S, C, P) actually does nothing but copying
//    existing string into the clipboard. (S, C) copies existing string
//    into the clipboard, and following P just replace existing string
//    with the same string from the clipboard.
// 2. One occurrence of P pastes what is in the clipboard to the output.
//    So in order to double the length of existing string, we need four
//    keystrokes (S, C, P, P).
// 3. When the number of keystrokes is large, then the single key A is
//    useless and we need only consider the other three keys.
// 4. Given N keystrokes, the max length M(N) is:
//    M(N) = max {  N,              // when N is small, we may just type A repeatly
//                  2 * M(N-4),     // the last four keystrokes are SCPP
//                  3 * M(N-5),     // the last five keystrokes are SCPPP
//                  ......
//                  (k-2) * M(N-k), // the last k keystrokes are SC and (k-2) Ps
//                  ......
//                  (N-3) * M(1)    // the sequence starts with ASC following by (N-3) Ps
//                }
static void LongestStringWithKeystrokes(int n, unsigned long long length[])
{
    length[0] = 1;
    length[1] = 2;
    length[2] = 3;
    length[3] = 4;
    for (int i = 4; i < n; i++)
    {
        unsigned long long m = i + 1; // when all i+1 keystrokes are As
        for (int j = 4; j <= i; j++)
        {
            unsigned long long n = (j - 2) * length[i - j];
            if (n > m)
                m = n;
        }
        length[i] = m;
    }
}

namespace Knapsack
{
// Assuming items<value, weight> are sorted by weight not decreasing
// value:    v_0 v_1 v_2 v_3 ...... v_(n-1)
// weight:   w_0 w_1 w_2 w_3 ...... w_(n-1), such that w_i <= w_j for i < j
// capacity: W
// matrix:   Define m[i][j] to be the maximum value that can be attained
//           with weight less than or equal to j using items up to i
//           m[i][j] = m[i-1][j]                              if j < w_i
//           m[i][j] = max(m[i-1][j], m[i-1][j-w_i] + v_i)    if j >= w_i
//
// i=0  0 1 2 3 ...... w_0-1 w_0 w_0+1 ...... W
// v_0  0 0 0 0 ...... 0     v_0 v_0   ...... v_0
//
// i=1  0 1 2 3 ...... w_0-1 w_0 w_0+1 ...... w_1-1 w_1 w_1+1 ...... w_0+w_1-1 w_0+w_1 w_0+w_1+1 ...... W
// v_1  0 0 0 0 ...... 0     v_0 v_0   ...... v_0 ......
static void ComputeValues(vector<pair<int, int>> &items, Matrix<int> &values)
{
    int capacity = values.Cols() - 1;
    if (capacity <= 0)
        throw invalid_argument(String::Format("Invalid capacit %d", capacity));
    int countItems = items.size();
    int rows = values.Rows();
    if (countItems > rows)
        throw invalid_argument(String::Format("There are %d items but value matrix has only %d rows", countItems, rows));

    // Compute the first row of values[0][]
    // using item 0, i.e., value[0], weight[0]
    for (int j = 0; j <= capacity; j++)
    {
        if (j < items[0].second)
        {
            // item 0 is too heavy
            values(0, j) = 0;
        }
        else
        {
            // item 0 weight is less than or equal to j
            values(0, j) = items[0].first;
        }
    }

    for (int i = 1; i < countItems; i++)
    {
        // Consider item i, i.e., value[i], weight[i]
        for (int j = 0; j <= capacity; j++)
        {
            if (j < items[i].second)
            {
                values(i, j) = values(i - 1, j);
            }
            else
            {
                values(i, j) = max(
                    values(i - 1, j),
                    values(i - 1, j - items[i].second) + items[i].first);
            }
        }
    }
}

static void SelectItems(vector<pair<int, int>> &items, Matrix<int> &values, vector<pair<int, int>> &selected)
{
    ComputeValues(items, values);

    int j = values.Cols() - 1;
    for (int i = items.size() - 1; i >= 0; i--)
    {
        if (i > 0 && values(i, j) > values(i - 1, j))
        {
            // m[i][j] = m[i-1][j-w_i] + v_i,  j >= w_i
            selected.insert(selected.begin(), items[i]);
            j -= items[i].second;
        }
        else
        {
            if (j >= items[i].second && items[i].second > 0)
                // m[i][j] = m[i-1][j],  j >= w_i
                selected.insert(selected.begin(), items[i]);
        }
    }
}

static void PrintSolution(vector<pair<int, int>> &items, Matrix<int> &values)
{
    vector<pair<int, int>> selected;
    SelectItems(items, values, selected);

    int capacity = values.Cols() - 1;
    int countItems = items.size();

    cout << "\t";
    for (int j = 0; j <= capacity; j++)
    {
        cout << "\t" << j;
    }

    cout << endl;

    for (int i = 0; i < countItems; i++)
    {
        cout << items[i].first << "\t" << items[i].second;
        for (int j = 0; j <= capacity; j++)
        {
            cout << "\t" << values(i, j);
        }

        cout << endl;
    }

    cout << "Selected items:" << endl;
    for_each(selected.begin(), selected.end(), [&](pair<int, int> &item) {
        cout << "\t" << item.first << "\t" << item.second << endl;
    });
}
} // namespace Knapsack

namespace LongestCommonSubsequence
{
//         0 y_0 y_1 y_2 ... y_(n-1)
// 0       0 0   0   0       0
// x_0     0
// x_1     0
// x_2     0
// ...
// x_(m-1) 0
//
// select =
//          1    Up
//          0    Diag
//         -1    Left
static void LengthTable(string &x, string &y, int *length, int *select)
{
    if (length == nullptr)
        throw invalid_argument("length is nullptr");
    if (select == nullptr)
        throw invalid_argument("select is nullptr");

    size_t m = x.length();
    size_t n = y.length();

    function<int &(int, int)> len = [&](int i, int j) -> int & {
        return *(length + i * (1 + n) + j);
    };

    function<int &(int, int)> sel = [&](int i, int j) -> int & {
        return *(select + i * (1 + n) + j);
    };

    for (unsigned int i = 0; i <= m; i++)
    {
        len(i, 0) = 0;
    }

    for (unsigned int i = 1; i <= n; i++)
    {
        len(0, i) = 0;
    }

    for (unsigned int i = 1; i <= m; i++)
    {
        for (unsigned int j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                len(i, j) = len(i - 1, j - 1) + 1;
                sel(i, j) = 0;
            }
            else if (len(i - 1, j) >= len(i, j - 1))
            {
                len(i, j) = len(i - 1, j);
                sel(i, j) = 1;
            }
            else
            {
                len(i, j) = len(i, j - 1);
                sel(i, j) = -1;
            }
        }
    }
}

static void PrintTable(int *T, size_t m, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << "\t" << i;
    }

    cout << endl;

    for (size_t i = 0; i < m; i++)
    {
        cout << i;
        for (size_t j = 0; j < n; j++)
        {
            cout << "\t" << *(T + i * n + j);
        }

        cout << endl;
    }
}

static void PrintLCS(string &x, string &y)
{
    size_t m = x.length();
    size_t n = y.length();
    size_t s = (1 + m) * (1 + n);
    unique_ptr<int[]> length(new int[s]);
    memset(length.get(), 0, s * sizeof(int));
    unique_ptr<int[]> select(new int[s]);
    memset(select.get(), 0, s * sizeof(int));

    LengthTable(x, y, length.get(), select.get());

    PrintTable(length.get(), 1 + m, 1 + n);
    PrintTable(select.get(), 1 + m, 1 + n);

    string lcs = "";
    int i = m;
    int j = n;
    while (i > 0 && j > 0)
    {
        int s = *(select.get() + i * (1 + n) + j);
        switch (s)
        {
        case 0:
            lcs.insert(0, &x[i - 1], 1);
            i--;
            j--;
            break;
        case 1:
            i--;
            break;
        case -1:
            j--;
            break;
        }
    }

    cout << "X: " << x << endl;
    cout << "Y: " << y << endl;
    cout << "LCS: " << lcs << endl;
}
} // namespace LongestCommonSubsequence

namespace LongestIncreasingSubsequence
{
//  i    0    1    2    3    ......    i    ......    n-2    n-1
//  I    I[0] I[1] I[2] I[3]           I[i]           I[n-2] I[n-1]
//  M    M[0] M[0] M[0] M[0]           M[0]           M[0]   M[0]
//            M[1] M[1] M[1]           M[1]           M[1]   M[1]
//                 M[2] M[2]           M[2]           M[2]   M[2]
//                      M[3]           M[3]           M[3]   M[3]
//
//                                     M[i]           M[i]   M[i]
//
//                                                    M[n-2] M[n-2]
//                                                           M[n-1]
//
//  For each i, compute M[j]
//  j = 0, 1, 2, 3, ......, i
//  Compute the ending elements of all increasing subsequences of length j+1,
//  choose I[k] which is the smallest ending element,
//  and set M[j] with its position k.
//  M[j] tracks the increasing subsequence of length j+1 that is most
//  likely to be extended when scanning the rest of elements in I.
//  If L is the length of longest increasing subsequence up to I[i] (0 <= L-1 <= i), then
//  M[0] < M[1] < M[2] < ...... < M[L-1] <= i
static void PrintSolution(int *input, int length)
{
    if (input == nullptr || length <= 0)
        return;

    cout << "Input:";
    for (int i = 0; i < length; i++)
    {
        cout << " " << input[i];
    }

    cout << endl;

    unique_ptr<int[]> m(new int[length]);
    unique_ptr<int[]> p(new int[length]);

    m[0] = 0;
    p[0] = -1; // Previous element in the increasing subsequence
    int L = 1; // The length of longest increasing subsequence so far
    for (int i = 1; i < length; i++)
    {
        // Should have used binary search.
        int j = L;
        while (j > 0 && input[i] <= input[m[j - 1]])
            j--;

        if (j > 0)
        {
            // input[m[j-1]] < input[i]
            // So input[i] extends the increasing subsequence ending at m[j-1]
            p[i] = m[j - 1];
        }
        else
        {
            // input[i] does not extend any increasing subsequence so far
            p[i] = -1;
        }

        if (j == L)
        {
            // If j == L, then input[m[L-1]] < input[i]
            // input[i] is the first element to end an increasing subsequence of length L + 1
            m[j] = i;
            L++;
        }
        else if (input[i] < input[m[j]])
        {
            // j < L, and input[m[j-1]] < input[i] < input[m[j]]
            // input[i] extends the increasing subsequence of length j ending at m[j-1], and
            // it is smaller than existing ending element at m[j].
            m[j] = i;
        }
    }

    stack<int> e;
    int i = m[L - 1];
    while (i >= 0)
    {
        e.push(input[i]);
        i = p[i];
    }

    cout << "Longest increasing subsequence:";
    while (!e.empty())
    {
        cout << " " << e.top();
        e.pop();
    }

    cout << endl;
}
} // namespace LongestIncreasingSubsequence

namespace MatrixChain
{
// Matrices:    A_0,       A_1,       A_2,       ..., A_i,           ..., A_j,           ..., A_(n-2)
// Dimensions:  d_0 x d_1, d_1 x d_2, d_2 x d_3, ..., d_i x d_(i+1), ..., d_j x d_(j+1), ..., d_(n-2) x d_(n-1)
// count = n
// Costs:
//   cost[i][i] = 0, for i = 0, 1, 2, ..., (n-2)
//   cost[i][j] = min { (cost[i][i] + cost[i+1][j] + d_i x d_(i+1) x d_(j+1)),
//                      (cost[i][i+1] + cost[i+2][j] + d_i x d_(i+2) x d_(j+1)),
//                      (cost[i][i+2] + cost[i+3][j] + d_i x d_(i+3) x d_(j+1)),
//                      ...
//                      (cost[i][j-1] + cost[j][j] + d_i x d_j x d_(j+1))
//                    },
//                 for i < j,
//                     i = 0, 1, 2, ..., n-3
//                     j =    1, 2, ..., n-3, n-2
static void ComputeCostTable(int *dimension, int count, int *cost, int *split)
{
    if (dimension == nullptr || count <= 0 || cost == nullptr || split == nullptr)
        return;

    function<int &(int, int)> c = [&](int i, int j) -> int & {
        return *(cost + i * (count - 1) + j);
    };

    for (int i = 0; i < count - 1; i++)
    {
        c(i, i) = 0;
    }

    // l = 1,   cost[0][1],   cost[1][2],   cost[2][3], ..., cost[i][i+1], ..., cost[n-4][n-3], cost[n-3][n-2]
    // l = 2,   cost[0][2],   cost[1][3],   cost[2][4], ..., cost[i][i+2], ..., cost[n-4][n-2]
    // ...
    // l = n-3, cost[0][n-3], cost[1][n-2]
    // l = n-2, cost[0][n-2]
    for (int l = 1; l < count - 1; l++)
    {
        for (int i = 0; i < count - 1 - l; i++)
        {
            int j = i + l;
            c(i, j) = 0x7FFFFFFF;
            for (int k = i; k < j; k++)
            {
                // split A_i..A_k, A_(k+1)..A_j
                int min = c(i, k) + c(k + 1, j) + dimension[i] * dimension[k + 1] * dimension[j + 1];
                if (min < c(i, j))
                {
                    c(i, j) = min;
                    *(split + i * (count - 1) + j) = k;
                }
            }
        }
    }
}

static void PrintSolution(int *dimension, int count)
{
    if (dimension == nullptr || count <= 0)
        return;

    int length = (count - 1) * (count - 1);
    unique_ptr<int[]> cost(new int[length]);
    unique_ptr<int[]> split(new int[length]);

    memset(cost.get(), 0, length * sizeof(int));
    memset(split.get(), 0, length * sizeof(int));

    ComputeCostTable(dimension, count, cost.get(), split.get());

    for (int i = 0; i < count - 1; i++)
    {
        cout << "A_" << i << " : " << dimension[i] << " x " << dimension[i + 1] << endl;
    }

    function<void(int, int)> print = [&](int i, int j) {
        if (i == j)
        {
            cout << " A_" << i << " ";
        }
        else
        {
            int k = *(split.get() + i * (count - 1) + j);
            cout << "(";
            print(i, k);
            print(k + 1, j);
            cout << ")";
        }
    };

    cout << "Parenthesization : ";
    print(0, count - 2);
    cout << endl;
    cout << "Cost : " << *(cost.get() + count - 2) << endl;
}
} // namespace MatrixChain

namespace Maze
{
// http://leetcode.com/2010/11/unique-paths.html
// Given a MxN maze, count the unique paths to travel
// from the top-left cell to the bottom-right cell.
static double CountUniquePaths(int rows, int cols, Matrix<double> &count)
{
    if (rows <= 0)
        throw invalid_argument(String::Format("rows %d is invalid", rows));
    if (cols <= 0)
        throw invalid_argument(String::Format("cols %d is invalid", cols));
    if ((int)count.Rows() < rows)
        throw invalid_argument(String::Format("count rows %d is less than %d", count.Rows(), rows));
    if ((int)count.Cols() < cols)
        throw invalid_argument(String::Format("count cols %d is less than %d", count.Cols(), cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            count(i, j) = -1;
        }
    }

    function<double(int, int)> countPaths = [&](int i, int j) -> double {
        if (i >= rows || j >= cols)
        {
            return 0;
        }
        else if (i == rows - 1 && j == cols - 1)
        {
            count(i, j) = 1;
        }
        else if (i == rows - 1)
        {
            if (count(i, j + 1) == -1)
            {
                count(i, j + 1) = countPaths(i, j + 1);
            }
            count(i, j) = count(i, j + 1);
        }
        else if (j == cols - 1)
        {
            if (count(i + 1, j) == -1)
            {
                count(i + 1, j) = countPaths(i + 1, j);
            }
            count(i, j) = count(i + 1, j);
        }
        else
        {
            if (count(i + 1, j) == -1)
            {
                count(i + 1, j) = countPaths(i + 1, j);
            }
            if (count(i, j + 1) == -1)
            {
                count(i, j + 1) = countPaths(i, j + 1);
            }
            count(i, j) = count(i + 1, j) + count(i, j + 1);
        }
        return count(i, j);
    };

    return countPaths(0, 0);
}

static double CountUniquePaths2(int rows, int cols, Matrix<double> &count)
{
    if (rows <= 0)
        throw invalid_argument(String::Format("rows %d is invalid", rows));
    if (cols <= 0)
        throw invalid_argument(String::Format("cols %d is invalid", cols));
    if ((int)count.Rows() < rows)
        throw invalid_argument(String::Format("count rows %d is less than %d", count.Rows(), rows));
    if ((int)count.Cols() < cols)
        throw invalid_argument(String::Format("count cols %d is less than %d", count.Cols(), cols));

    for (int i = 0; i < rows; i++)
    {
        count(i, cols - 1) = 1;
    }

    for (int j = 0; j < cols; j++)
    {
        count(rows - 1, j) = 1;
    }

    for (int i = rows - 2; i >= 0; i--)
    {
        for (int j = cols - 2; j >= 0; j--)
        {
            count(i, j) = count(i + 1, j) + count(i, j + 1);
        }
    }

    return count(0, 0);
}
} // namespace Maze

namespace MinMaxPartitionSum
{
// http://leetcode.com/2011/04/the-painters-partition-problem.html
// Divide input into K partitions such that the maximum sum over each
// partition is minimized. The elements of input should not be moved,
// and partitions should not overlap.
// input        I_0 I_1 I_2 ...... I_i
// partitions   p_0 p_1 p_2 ...... p_j
// Let S(i, j) be the solution with input[0..i] and partitions[0..j]
// S(i, j) = min{
//                max{S(i-1, j-1), I_i},
//                max{S(i-2, j-1), I_(i-1) + I_i},
//                max{S(i-3, j-1), I_(i-2) + I_(i-1) + I_i},
//                ......
//                max{S(j, j-1),   I_(j+1) + I_(j+2) + ... + I_(i-2) + I_(i-1) + I_i},
//                max{S(j-1, j-1), I_j + I_(j+1) + ... + I_(i-2) + I_(i-1) + I_i}
//           }
//
// S(i,j)    0       1       2       3       4      ...... j-2       j-1       j
//   0      (0,0)
//   1      (1,0)   (1,1)
//   2      (2,0)   (2,1)   (2,2)
//   3      (3,0)   (3,1)   (3,2)   (3,3)
//   4      (4,0)   (4,1)   (4,2)   (4,3)   (4,4)
//           ......
//   j-1    (j-1,0) (j-1,1) (j-1,2) (j-1,3) (j-1,4) ...... (j-1,j-2) (j-1,j-1)
//   j      (j,0)   (j,1)   (j,2)   (j,3)   (j,4)   ...... (j,j-2)   (j,j-1)   (j,j)
//   j+1    (j+1,0) (j+1,1) (j+1,2) (j+1,3) (j+1,4) ...... (j+1,j-2) (j+1,j-1) (j+1,j)
//           ......
//   i-1    (i-1,0) (i-1,1) (i-1,2) (i-1,3) (i-1,4) ...... (i-1,j-2) (i-1,j-1) (i-1,j)
//   i      (i,0)   (i,1)   (i,2)   (i,3)   (i,4)   ...... (i,j-2)   (i,j-1)   (i,j)
//
template <class T>
static T Solve(const T *input, int length, int *indices, int partitions)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
    if (indices == nullptr)
        throw invalid_argument("indices is nullptr");
    if (partitions > length)
        throw invalid_argument(String::Format("length %d is less than partitions %d", length, partitions));

    Matrix<T> S(length, partitions);
    Matrix<int> I(length, partitions);

    // Initialize column 0
    S(0, 0) = input[0];
    I(0, 0) = 0;
    for (int i = 1; i < length; i++)
    {
        // input[0..i] assigned to partition[0]
        S(i, 0) = S(i - 1, 0) + input[i];
        // partition[0] starts at index 0
        I(i, 0) = 0;
    }

    for (int j = 1; j < partitions; j++)
    {
        for (int i = j; i < length; i++)
        {
            T s = input[i];
            S(i, j) = std::max(S(i - 1, j - 1), s);
            I(i, j) = i;
            for (int k = i - 2; k >= j - 1; k--)
            {
                s += input[k + 1];
                T maxS = std::max(S(k, j - 1), s);
                if (maxS <= S(i, j))
                {
                    S(i, j) = maxS;
                    I(i, j) = k + 1;

                    // Given { 100, 100, 100, 100, 100, 100, 100, 100, 100 } and 4 partitions
                    // If maxS < S(i, j), then the partions are:
                    //   300 = sum{A[0..2]} = 100 + 100 + 100
                    //   300 = sum{A[3..5]} = 100 + 100 + 100
                    //   200 = sum{A[6..7]} = 100 + 100
                    //   100 = sum{A[8..8]} = 100
                    // If maxS <= S(i, j), then the partions are:
                    //   200 = sum{A[0..1]} = 100 + 100
                    //   200 = sum{A[2..3]} = 100 + 100
                    //   200 = sum{A[4..5]} = 100 + 100
                    //   300 = sum{A[6..8]} = 100 + 100 + 100

                    // For some k1 < k2, the following two values may be the same
                    //   max{S(k1, j-1), I_(k1+1) + ... + I_i}
                    //   max{S(k2, j-1), I_(k2+1) + ... + I_i}
                    // We want to partition at k1+1 instead of k2+1 so that
                    // the last partion would not necessarily take too few load
                }
            }
        }
    }

    // S.Print();
    // I.Print();

    int i = length - 1;
    for (int j = partitions - 1; j >= 0; j--)
    {
        indices[j] = I(i, j);
        i = indices[j] - 1;
    }

    return S(length - 1, partitions - 1);
}

// This implementation has some problem getting wrong indices even though the return value can be correct.
template <class T>
static T Solve2(const T *input, int length, int *indices, int partitions)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
    if (indices == nullptr)
        throw invalid_argument("indices is nullptr");
    if (partitions > length)
        throw invalid_argument(String::Format("length %d is less than partitions %d", length, partitions));

    T min = input[0];
    T max = input[0];
    T sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += input[i];
        if (input[i] > max)
        {
            max = input[i];
        }
        if (input[i] < min)
        {
            min = input[i];
        }
    }

    if (partitions == length)
    {
        // One input item per partition
        for (int i = 0; i < partitions; i++)
        {
            indices[i] = i;
        }
        // The cost is the maximum of input items
        return max;
    }

    T cost = min;

    // Calculate partitions
    // Update indices and cost accordingly
    auto GetPartitions = [&](T m) -> int {
        // temporary sum per partition
        T s = 0;
        // maximum sum
        T c = 0;
        indices[0] = 0;
        int j = 1;
        for (int i = 0; i < length; i++)
        {
            s += input[i];
            if (s >= m && i != length - 1)
            {
                if (j < partitions)
                {
                    indices[j] = i;
                }
                j++;
                s -= input[i];
                if (s > c)
                {
                    c = s;
                }
                s = input[i];
            }
        }

        if (s > c)
        {
            c = s;
        }

        cost = c;
        return j;
    };

    T low = max;
    T high = sum;

    int lowPartitions = GetPartitions(low);

    if (lowPartitions < partitions)
    {
        low = min;
        high = max;
    }

    while (low < high)
    {
        T mid = (low + high) >> 1;
        int midPartions = GetPartitions(mid);
        cout << low << ", " << mid << ", " << high << ", " << midPartions << ", " << cost << endl;

        if (midPartions > partitions)
        {
            low = mid + 1;
        }
        else if (midPartions < partitions)
        {
            high = mid - 1;
        }
        else
        {
            // low = (low + mid) >> 1;
            // high = (mid + high) >> 1;
            return cost;
        }
    }

    if (low == high)
    {
        GetPartitions(low);
    }

    return cost;
}
} // namespace MinMaxPartitionSum

// Remove duplicate characters from string input.
// Return the new length of string input with only unique characters.
static int RemoveDuplicateChars(char *input, int length)
{
    if (input == nullptr)
        return -1;
    if (length <= 0)
        return length;
    bitset<256> mask;

    // Using i to point to the last position of a non-dup char that has been checked.
    // Next non-dup char should be copied to the position i+1.
    // 0 | 1 | ... | i | ... | j | ... | n-1
    // ~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~
    // Non-dup chars         chars to check

    int i = -1;
    for (int j = 0; j < length; j++)
    {
        if ('\0' == input[j])
            break;
        if (!mask.test(input[j]))
        {
            // The bit is zero, and it means input[j] is not a dup.
            mask.set(input[j]);
            i++;
            if (i < j)
            {
                // Have skipped some dups
                // Move current non-dup char to the front.
                input[i] = input[j];
            }
        }
    }

    input[++i] = '\0';
    // Now i equals to the new length.
    return i;
}

class FiniteAutomation
{
public:
    FiniteAutomation(const char *pattern)
    {
        if (pattern == nullptr)
            throw invalid_argument("pattern is nullptr");
        if (pattern[0] == '\0')
            throw invalid_argument("pattern is empty");
        int length = (int)strlen(pattern);
        if (length <= 0)
            throw invalid_argument(String::Format("length %d <= 0", length));

        this->ComputeTransition(pattern, length);
    }

    ~FiniteAutomation(void)
    {
        for_each(this->transition.begin(), this->transition.end(), [](pair<int, map<char, int> *> it) -> void {
            if (it.second != nullptr)
            {
                delete it.second;
                it.second = nullptr;
            }
        });
    }

    int PatternLength(void)
    {
        return this->transition.size() - 1;
    }

    void Print(void)
    {
        for_each(this->transition.begin(), this->transition.end(), [](pair<int, map<char, int> *> it) -> void {
            printf("State %d\n", it.first);
            for_each(it.second->begin(), it.second->end(), [](pair<char, int> iit) -> void {
                printf("\t%c -> %d\n", iit.first, iit.second);
            });
        });
    }

    // Find occurrences of pattern in the given input
    vector<int> SearchString(const char *input, int length)
    {
        vector<int> indices;
        if (input == nullptr || input[0] == '\0' || length <= 0)
            return indices;
        int state = -1;
        for (int i = 0; i < length; i++)
        {
            map<int, map<char, int> *>::iterator itState = this->transition.find(state);
            if (itState == this->transition.end())
            {
                state = -1;
                continue;
            }

            map<char, int>::iterator itChar = itState->second->find(input[i]);
            if (itChar == itState->second->end())
            {
                // input[i] is invalid
                state = -1;
            }
            else
            {
                state = itChar->second;
                if (state == (int)this->transition.size() - 2)
                {
                    // It is the final state
                    indices.push_back(i - state);
                }
            }
        }

        return indices;
    }

private:
    void ComputeTransition(const char *pattern, int length)
    {
        // Construct state transition given pattern
        // Valid states are -1, 0, 1, ..., (length-1)

        unique_ptr<char[]> uniquechars(new char[length + 1]);
        memcpy(uniquechars.get(), pattern, length * sizeof(char));
        uniquechars.get()[length] = '\0';
        int count = RemoveDuplicateChars(uniquechars.get(), length);

        // Initialize starting state -1
        map<char, int> *initState = new map<char, int>();
        initState->insert(pair<char, int>(pattern[0], 0));
        this->transition.insert(pair<int, map<char, int> *>(-1, initState));

        unique_ptr<char[]> buffer(new char[length + 2]);
        for (int state = 0; state < length; state++)
        {
            buffer[state] = pattern[state];
            map<char, int> *nextState = new map<char, int>();
            // Build nextState given each unique char
            for (int i = 0; i < count; i++)
            {
                char c = uniquechars[i];
                buffer[state + 1] = c;
                buffer[state + 2] = '\0';
                int index = Suffix(pattern, buffer.get());
                if (index != -1)
                {
                    nextState->insert(pair<char, int>(c, index));
                }
            }

            this->transition.insert(pair<int, map<char, int> *>(state, nextState));
        }
    }

    // Find the longest prefix substring of pattern that is also a suffix of input
    static int Suffix(const char *pattern, const char *input)
    {
        if (pattern == nullptr)
            return -1;
        if (input == nullptr)
            return -1;
        int m = (int)strlen(pattern);
        if (m <= 0)
            return -1;
        int n = (int)strlen(input);
        if (n <= 0)
            return -1;

        for (int i = min(m - 1, n - 1); i >= 0; i--)
        {
            // Start from pattern[i], move backward to pattern[0]
            int j = 0;
            while (pattern[i - j] == input[n - 1 - j] && j <= i)
            {
                j++;
            }

            if (j == i + 1)
            {
                // pattern[0..i] == input[(n-1-i)..(n-1)]
                return i;
            }
        }

        return -1;
    }

    // For current state i, given a character c determine the next state j
    map<int, map<char, int> *> transition;
};
} // namespace Test

#endif