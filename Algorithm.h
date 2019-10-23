#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>
#include "Structure.h"

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

class KMP
{
public:
    KMP(const char *pattern)
    {
        this->prefix = nullptr;
        this->pattern = nullptr;
        if (pattern == nullptr)
            throw invalid_argument("pattern is nullptr");
        this->length = (int)strlen(pattern);
        if (this->length <= 0)
            throw invalid_argument(String::Format("length %d <= 0", this->length));

        this->pattern = new char[this->length + 1];
        strcpy(this->pattern, pattern);
        this->prefix = new int[this->length];
        memset(this->prefix, 0, this->length * sizeof(int));

        // Maintain prefix[i] = k, update prefix[i+1] by checking pattern[i+1] vs pattern[k+1].
        // The goal is for each input i, find k such that pattern[0..k] is suffix of input[0..i].

        int k = -1;
        this->prefix[0] = k;
        for (int i = 1; i < this->length; i++)
        {
            while (k > -1 && this->pattern[k + 1] != this->pattern[i])
            {
                // Keep searching backward for minimum k
                // such that pattern[0..k)] is a suffix of pattern[0..(i-1)]
                k = this->prefix[k];
            }

            // The while loop terminates when
            // 1. there is a k such that pattern[0..(k+1)] is a suffix of pattern[0..i], or
            // 2. k = -1

            if (this->pattern[k + 1] == this->pattern[i])
            {
                // One more match
                k = k + 1;
            }

            this->prefix[i] = k;
        }
    }

    ~KMP(void)
    {
        if (this->prefix != nullptr)
        {
            delete[] this->prefix;
            this->prefix = nullptr;
        }

        if (this->pattern != nullptr)
        {
            delete[] this->pattern;
            this->pattern = nullptr;
        }
    }

    void Print(void)
    {
        for (int i = 0; i < this->length; i++)
        {
            printf("\t%d", i);
        }

        printf("\n");

        for (int i = 0; i < this->length; i++)
        {
            printf("\t%d", this->prefix[i]);
        }

        printf("\n");
    }

    vector<int> SearchString(const char *input, int length)
    {
        vector<int> indices;
        if (input == nullptr || input[0] == '\0' || length <= 0)
            return indices;

        int k = -1;
        for (int i = 0; i < length; i++)
        {
            while (k > -1 && this->pattern[k + 1] != input[i])
            {
                k = this->prefix[k];
            }

            if (this->pattern[k + 1] == input[i])
            {
                k = k + 1;
            }

            if (k == this->length - 1)
            {
                indices.push_back(i - k);
                k = this->prefix[k];
            }
        }

        return indices;
    }

private:
    char *pattern;
    int *prefix;
    int length;
};

namespace Math
{
static size_t CountBits(unsigned int n)
{
    int c = 0;
    while (n != 0)
    {
        n = n >> 1;
        c++;
    }
    return c;
};

static size_t CountBitOnes(unsigned int n)
{
    int c = 0;
    while (n != 0)
    {
        // erase one bit from the lower end
        // 0x####0100 & 0x####00FF = 0x####0000
        n = n & (n - 1);
        c++;
    }
    return c;
};

static int LowerMedian(int b, int e)
{
    // If e - b + 1 = 2m
    // +----------------+    +------------------+
    // b               b+m-1 b+m             e = b+2m-1
    // The median index is b+m-1 = b + (e - b) / 2, rounding to the lower boundary
    //
    // If e - b + 1 = 2m-1
    // +----------------+    +     +------------------+
    // b               b+m-2 b+m-1 b+m+1             e = b+2m-2
    // The median index is b+m-1 = b + (e - b) / 2
    return b + ((e - b) >> 1);
}

static int HigherMedian(int b, int e)
{
    // If e - b + 1 = 2m
    // +----------------+    +------------------+
    // b               b+m-1 b+m             e = b+2m-1
    // The median index is b+m = b + (e - b + 1) / 2, rounding to the lower boundary
    //
    // If e - b + 1 = 2m-1
    // +----------------+    +     +------------------+
    // b               b+m-2 b+m-1 b+m+1             e = b+2m-2
    // The median index is b+m-1 = b + (e - b + 1) / 2
    return b + ((e - b + 1) >> 1);
}

static long long ToInteger(const string &input)
{
    if (input.length() == 0)
        throw invalid_argument("input is empty");
    long long s = 0;
    bool negative = input[0] == '-';
    for (size_t i = negative ? 1 : 0; i < input.length(); i++)
    {
        if (input[i] < '0' || input[i] > '9')
            throw invalid_argument("input is not an integer");
        s = s * 10 + input[i] - '0';
    }
    return negative ? -s : s;
}

template <class T>
static T GreatestCommonDivisor(T n0, T n1)
{
    if (n0 == 0 && n1 == 0)
        throw invalid_argument("(0, 0) has no greatest common divisor");
    if (n0 < 0)
        n0 = -n0;
    if (n1 < 0)
        n1 = -n1;
    if (n0 == 0)
        return n1;
    if (n1 == 0)
        return n0;
    if (n1 > n0)
        swap(n0, n1);
    T r = n0 % n1;
    while (r != 0)
    {
        n0 = n1;
        n1 = r;
        r = n0 % n1;
    }
    return n1;
}

// Add two bit arrays, n2 = n0 + n1. Assume bit-0 is the LSB.
static void AddBits(const int *n0, size_t l0, const int *n1, size_t l1, int *n2)
{
    if (n0 == nullptr || n1 == nullptr)
        return;
    if (l0 == 0 || l1 == 0)
        return;
    if (n2 == nullptr)
        return;
    if (l0 > l1)
    { // adjust so that n0 is shorter than n1
        swap(n0, n1);
        swap(l0, l1);
    }
    memset(n2, 0, (l1 + 1) * sizeof(int));
    memcpy(n2, n0, l0 * sizeof(int));
    int c = 0;
    size_t i = 0;
    for (i = 0; i < l1; i++)
    {
        int s = n2[i] + n1[i] + c;
        switch (s)
        {
        case 0:
        case 1:
            n2[i] = s;
            c = 0;
            break;
        case 2:
        case 3:
            n2[i] = s & 0x1;
            c = 1;
            break;
        default:
            break;
        }
    }
    if (c == 1)
        n2[i] = 1;
}

// Convert Excel column number to integer:
//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
//     0, 1, ..., 25, 26, 27, ..., 51, 52, 53, ..., 701, 702, 703, ...
// If we encode [A-Z] to [1 - 26], then
//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
//     1, 2, ..., 26, 27, 28, ..., 52, 53, 54, ..., 702, 703, 704, ...
// The output is merely one less.
// input  I[0..n-1]
// output I[0] * 26^(n-1) + I[1] * 26^(n-2) + ... + I[i] * 26^(n-1-i) + ... + I[n-2] * 26^1 + I[n-1]
static unsigned long long DecodeExcel(const string &input)
{
    unsigned long long s = 0;
    for (unsigned int i = 0; i < input.length(); i++)
    {
        s = s * 26 + (input[i] - 'A' + 1);
    }
    return s - 1;
}

// Convert integer tp Excel column number:
//     0, 1, ..., 25, 26, 27, ..., 51, 52, 53, ..., 701, 702, 703, ...
//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
// If we encode [A-Z] to [1 - 26], then
//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
//     1, 2, ..., 26, 27, 28, ..., 52, 53, 54, ..., 702, 703, 704, ...
static string EncodeExcel(unsigned long long input)
{
    string code;
    unsigned int r;
    input++;
    while (input > 0)
    {
        r = input % 26;
        input /= 26;
        if (r == 0)
        {
            // make sure r is in [1, 26]
            // so if r = 0, then borrow one from next higher position
            input--;
            r = 26;
        }
        code.insert(0, 1, r - 1 + 'A');
    }
    return code;
}

// http://leetcode.com/2010/04/multiplication-of-numbers.html
// There is an array A[N] of N numbers. You have to compose an array
// Output[N] such that Output[i] will be equal to multiplication of all
// the elements of A[N] except A[i]. Solve it without division operator
// and in O(n). For example Output[0] will be multiplication of A[1]
// to A[N-1] and Output[1] will be multiplication of A[0] and from A[2]
// to A[N-1]. Example:
// A: {4, 3, 2, 1, 2}
// OUTPUT: {12, 16, 24, 48, 24}
// Let M[i..j] = I[i] * I[i+1] * ... * I[j]
// I[i]  I[0]      I[1]      I[2]      ...... I[i]        ...... I[n-1]
// L[i]  1         M[0..0]   M[0..1]   ...... M[0..i-1]   ...... M[0..n-2]
// R[i]  M[1..n-1] M[2..n-1] M[3..n-1] ...... M[i+1..n-1] ...... 1
// O[i] = L[i] * R[i]
static void ExclusiveMultiplication(const int *input, int length, long long *output)
{
    for (int i = 0; i < length; i++)
        output[i] = 1;
    long long left = 1;
    long long right = 1;
    for (int i = 0; i < length; i++)
    {
        // At loop i, output[i] *= left (= multiplication of input[0..i-1])
        // At loop length - 1 - i, output[i] *= right (= multiplication of input[i+1..length-1])
        output[i] *= left;
        output[length - 1 - i] *= right;
        left *= input[i];
        right *= input[length - 1 - i];
    }
}

// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
static int EvalReversePolishNotation(vector<string> &tokens)
{
    if (tokens.size() == 0)
        throw invalid_argument("No token is provided");
    stack<int> args;
    int first;
    int second;
    int s;
    for_each(tokens.begin(), tokens.end(), [&](string &t) {
        if (t != "+" && t != "-" && t != "*" && t != "/")
        {
            if (t.length() == 0)
                throw invalid_argument("Token is empty");
            s = (int)Math::ToInteger(t);
            args.push(s);
        }
        else
        {
            if (args.empty())
                throw invalid_argument("Not enough tokens");
            second = args.top();
            args.pop();
            if (args.empty())
                throw invalid_argument("Not enough tokens");
            first = args.top();
            args.pop();
            if (t == "+")
                s = first + second;
            else if (t == "-")
                s = first - second;
            else if (t == "*")
                s = first * second;
            else if (t == "/")
            {
                if (second == 0)
                    throw runtime_error("Divided by zero");
                s = first / second;
            }
            args.push(s);
        }
    });
    return args.top();
}

} // namespace Math

namespace SingleNumber
{
// An array contain numbers duplicated by three times, except
// one single number. Find the single number.
// Count number of bit 1 per position and modulo 3.
static int FindOutOfThree(int input[], int length)
{
    if (length % 3 != 1)
        throw invalid_argument("The count of numbers is not 3n+1");
    int n = 0;
    int bits = 8 * sizeof(int);
    for (int i = 0; i < bits; i++)
    {
        int count = 0;
        for (int j = 0; j < length; j++)
            count += ((input[j] >> i) & 0x1);
        n |= ((count % 3) << i);
    }
    return n;
}
static int FindOutOfThree2(int input[], int length)
{
    if (length % 3 != 1)
        throw invalid_argument("The count of numbers is not 3n+1");
    int o0 = ~0; // positions that bit 1 occurred 0 or 3 times
    int o1 = 0;  // positions that bit 1 occurred 1 time
    int o2 = 0;  // positions that bit 1 occurred 2 times
    int t = 0;
    for (int i = 0; i < length; i++)
    {
        // keep o2 temporarily to calculate o0 later
        t = o2;
        // Update the positions that bit 1 occurred the second time due to input[i], and
        // keep the positions that bit 1 already occurred two times and not affected by input[i]
        o2 = (o1 & input[i]) | (o2 & ~input[i]);
        // Update the positions that bit 1 occurred the first time due to input[i], and
        // keep the positions that bit 1 already occurred one time and not affected by input[i]
        o1 = (o0 & input[i]) | (o1 & ~input[i]);
        // Update the positions that bit 1 occurred the third time due to input[i], and
        // keep the positions that bit 1 already occurred zero or three times and not affected by input[i]
        o0 = (t & input[i]) | (o0 & ~input[i]);
    }
    return o1;
}
static int FindOutOfThree3(int input[], int length)
{
    if (length % 3 != 1)
        throw invalid_argument("The count of numbers is not 3n+1");
    int o1 = 0; // positions that bit 1 occurred 0 or 3 times
    int o2 = 0; // positions that bit 1 occurred 1 time
    int o3 = 0; // positions that bit 1 occurred 2 times
    for (int i = 0; i < length; i++)
    {
        o2 |= o1 & input[i];
        o1 ^= input[i];
        o3 = o1 & o2;
        o1 &= ~o3;
        o2 &= ~o3;
    }
    return o1;
}

// An array contain numbers duplicated by k times, except
// one single number occurring l times.
// Find the single number.
static int FindLOutOfK(int input[], int length, int k, int l)
{
    if (length % k != l)
        throw invalid_argument("The count of numbers is not kn+l");
    int bits = 8 * sizeof(int);
    int r = 0;
    for (int i = 0; i < bits; i++)
    {
        int c = 0;
        for (int j = 0; j < length; j++)
            c += ((input[j] >> i) & 0x1);
        c %= k;
        if (c > 0)
            r |= (0x1 << i);
    }
    return r;
}
static int FindLOutOfK2(int input[], int length, int k, int l)
{
    if (length % k != l)
        throw invalid_argument("The count of numbers is not kn+l");
    unique_ptr<int[]> o(new int[k]);
    memset(o.get(), 0, k * sizeof(int));
    o[0] = ~0;
    for (int i = 0; i < length; i++)
    {
        int t = o[k - 1];
        for (int j = k - 1; j > 0; j--)
            o[j] = (o[j - 1] & input[i]) | (o[j] & ~input[i]);
        o[0] = (t & input[i]) | (o[0] & ~input[i]);
    }
    return o[l];
}
} // namespace SingleNumber

template <class T>
static int CountInversions(T *input, size_t length)
{
    if (input == nullptr || length <= 1)
        return 0;

    // Count inversions between a[h..(m-1)] and a[m..t],
    // assuming both subarrays are sorted
    function<int(T *, int, int, int)>
        merge = [&](T *a, int h, int m, int t) -> int {
        int c = 0;
        // head and middle point to the heads of two sub sorted arrays.
        while (h < m && m <= t)
        {
            if (a[h] <= a[m])
            {
                h++;
            }
            else
            {
                T x = a[m];
                for (int i = m; i > (int)h; i--)
                {
                    a[i] = a[i - 1];
                }
                a[h] = x;
                // There (m - h) elements moved.
                // Each of them paired with a[m] is an inversion.
                c += (m - h);
                // Move to the next pair of elements
                h++;
                m++;
            }
        }
        return c;
    };

    function<int(T *, int, int)> count = [&](T *a, int h, int t) -> int {
        if (a == nullptr || h >= t)
            return 0;
        int c = 0;
        if (h < t)
        {
            int m = h + ((t - h) >> 1) + 1;
            c += count(a, h, m - 1);
            c += count(a, m, t);
            c += merge(a, h, m, t);
        }
        return c;
    };

    return count(input, 0, length - 1);
}

namespace OverLap
{
// [pair.first, pair.second]
typedef pair<double, double> Range;

static bool IsOverlap(const Range &r1, const Range &r2)
{
    // Non-overlap r1.second <= r2.first || r2.second <= r1.first;
    return r1.first < r2.second && r2.first < r1.second;
}

// (Point.x, Point.y) = (pair.first, pair.second)
typedef pair<double, double> Point;

// The sides of Rectangle are in parallel with x-axis or y-axis
// Top-Left Point = pair.first
// Bottom-Right Point = pair.second
typedef pair<Point, Point> Rectangle;

static bool IsOverlap(const Rectangle &r1, const Rectangle &r2)
{
    // r1 and r2 overlaps if their projections onto x-axis and y-axis overlap
    // [r1.first.first, r1.second.first] and [r2.first.first, r2.second.first] overlaps.
    // [r1.second.second, r1.first.second] and [r2.second.second, r2.first.second] overlaps.
    return r1.first.first < r2.second.first && r2.first.first < r1.second.first && r1.second.second < r2.first.second && r2.second.second < r1.first.second;
}
} // namespace OverLap

namespace PointsOnALine
{
struct IntPoint
{
    int x;
    int y;
    IntPoint() : x(0), y(0) {}
    IntPoint(int a, int b) : x(a), y(b) {}
    bool operator==(const IntPoint &other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator<(const IntPoint &other) const
    {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }
};

// slope = (p1.y - p0.y) / (p1.x - p0.x)
// Reduce the slope so that the numerator and denominator are co-prime
// Return a pair <deltaX, deltaY> after reduction
static pair<int, int> NomalizeSlope(const IntPoint &p0, const IntPoint &p1)
{
    int dX = p1.x - p0.x;
    int dY = p1.y - p0.y;
    int gcd = Math::GreatestCommonDivisor(dX, dY);
    dX = dX / gcd;
    dY = dY / gcd;
    return make_pair(dX, dY);
}

// Find a line containing maximum number of points
static int MaxPointsOnALine(vector<IntPoint> &points, set<IntPoint> &output)
{
    if (points.size() <= 1)
    {
        output.clear();
        output.insert(points.begin(), points.end());
        return points.size();
    }

    // Group pairs of points by slopes. The points with the same slope
    // are potentially on the same lines.

    // Use comparer of IntPoint
    sort(points.begin(), points.end());
    map<pair<int, int>, vector<pair<IntPoint, IntPoint>>> slopes;
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        for (size_t j = i + 1; j < points.size(); j++)
        {
            if (points[i] == points[j])
            {
                // Ignore duplication
                continue;
            }

            pair<int, int> slope = NomalizeSlope(points[i], points[j]);

            // Treat vertical line specially
            if (slope.first == 0)
                slope.second = 1;
            // Treat horizontal line specially
            if (slope.second == 0)
                slope.first = 1;

            if (slopes.find(slope) == slopes.end())
            {
                slopes[slope] = vector<pair<IntPoint, IntPoint>>{};
            }

            slopes[slope].push_back(make_pair(points[i], points[j]));
        }
    }

    size_t max = 0;

    for (map<pair<int, int>, vector<pair<IntPoint, IntPoint>>>::iterator slope = slopes.begin();
         slope != slopes.end();
         slope++)
    {
        // lines of the same slope
        vector<set<IntPoint>> lines;
        for_each(slope->second.begin(), slope->second.end(), [&](pair<IntPoint, IntPoint> &s) {
            // s is a line segament ending with two points.
            // Check and assign the points into the set of points on the same line.

            // first is the line containing the first point of segament s
            vector<set<IntPoint>>::iterator first = lines.end();
            // second is the line containing the second point of segament s
            vector<set<IntPoint>>::iterator second = lines.end();

            for (vector<set<IntPoint>>::iterator it = lines.begin(); it != lines.end(); it++)
            {
                // it refers to the set of points on the same line
                if (it->find(s.first) != it->end())
                {
                    first = it;
                }
                if (it->find(s.second) != it->end())
                {
                    second = it;
                }
            }

            if (first == lines.end() && second == lines.end())
            {
                // Segament s is a new line
                set<IntPoint> line;
                line.insert(s.first);
                line.insert(s.second);
                lines.push_back(line);
            }
            else if (first == lines.end())
            {
                // The second point of segament s is already on a line.
                // Just add the first point.
                second->insert(s.first);
            }
            else if (second == lines.end())
            {
                // The first point of segament s is already on a line.
                // Just add the second point.
                first->insert(s.second);
            }
            else if (first == second)
            {
                // The segament is already on a line
                ;
            }
            else
            {
                // The segament joins two lines into one
                set<IntPoint> line;
                line.insert(first->begin(), first->end());
                line.insert(second->begin(), second->end());
                lines.erase(first);
                lines.erase(second);
                lines.push_back(line);
            }
        });

        for_each(lines.begin(), lines.end(), [&](set<IntPoint> &l) {
            if (l.size() > max)
            {
                max = l.size();
                output.clear();
                output.insert(l.begin(), l.end());
            }
        });
    }

    return max;
}
} // namespace PointsOnALine

// http://leetcode.com/2011/02/coins-in-line.html
// Two players take turn to select a coin from one end of a line of coins.
// Compute the maximum value of coins the first palyer can get.
namespace CoinSelect
{
// Given the value matrix, return the indices the first player wants to choose
static void GetIndices(Matrix<int> &v, int length, vector<int> &indices)
{
    int i = 0;
    int j = length - 1;
    while (i + 2 <= j)
    {
        if (v(i + 1, j) <= v(i, j - 1))
        {
            // A select input[i] and leave B input[i+1..j]
            indices.push_back(i);
            if (v(i + 2, j) <= v(i + 1, j - 1))
            {
                // B select input[i+1] and leave A input[i+2..j]
                i = i + 2;
            }
            else
            {
                // B select input[j] and leave A input[i+1..j-1]
                i++;
                j--;
            }
        }
        else
        {
            // A select input[j] and leave B input[i..j-1]
            indices.push_back(j);
            if (v(i + 1, j - 1) <= v(i, j - 2))
            {
                // B select input[i] and leave A input[i+1..j-1]
                i++;
                j--;
            }
            else
            {
                // B select input[j-1] and leave A input[i..j-2]
                j = j - 2;
            }
        };
    }

    if (i + 1 == j)
    {
        if (v(i, i) > v(j, j))
        {
            indices.push_back(i);
        }
        else
        {
            indices.push_back(j);
        }
    }
    else if (i == j)
    {
        indices.push_back(i);
    }
}

// Let V[i,j] be the maximum value from input[i..j]
// Let S[i,j] be the sum of input[i..j]
// V[i,j] = S[i,j] - min { V[i+1,j], V[i,j-1] }
static int MaxSelection(const int *input, int length, vector<int> &indices)
{
    Matrix<int> v(length, length);
    Matrix<int> s(length, length);

    // S[i,i] = input[i]
    // V[i,i] = input[i]
    for (int i = 0; i < length; i++)
    {
        s(i, i) = input[i];
        v(i, i) = input[i];
    }

    // S[i,j] = S[i,j-1] + input[j]
    // V[i,j] = S[i,j] - min { V[i+1,j], V[i,j-1] }
    for (int l = 1; l < length; l++)
    {
        for (int i = 0; i < length - l; i++)
        {
            s(i, i + l) = s(i, i + l - 1) + input[i + l];
            v(i, i + l) = s(i, i + l) - min(v(i + 1, i + l), v(i, i + l - 1));
        }
    }

    GetIndices(v, length, indices);
    return v(0, length - 1);
}

// Let V[i,j] be the maximum value from input[i..j]
// V[i,j] = max { input[i] + min { V[i+2,j], V[i+1,j-1] },
//                input[j] + min { V[i+1,j-1], V[i,j-2] } }
static int MaxSelection2(const int *input, int length, vector<int> &indices)
{
    Matrix<int> v(length, length);

    // V[i,i] = input[i]
    for (int i = 0; i < length; i++)
    {
        v(i, i) = input[i];
    }

    // V[i,i+1] = max { V[i,i], V[i+1,i+1] }
    for (int i = 0; i < length - 1; i++)
    {
        v(i, i + 1) = max(v(i, i), v(i + 1, i + 1));
    }

    // V[i,j] = max { input[i] + min { V[i+2,j], V[i+1,j-1] },
    //                input[j] + min { V[i+1,j-1], V[i,j-2] } }
    for (int l = 2; l < length; l++)
    {
        for (int i = 0; i < length - l; i++)
        {
            v(i, i + l) = max(
                input[i] + min(v(i + 2, i + l), v(i + 1, i + l - 1)),
                input[i + l] + min(v(i + 1, i + l - 1), v(i, i + l - 2)));
        }
    }

    GetIndices(v, length, indices);
    return v(0, length - 1);
}
} // namespace CoinSelect

// Given a cell in a grid, get all its neighors (horizontal, vertical and diagonal)
static vector<pair<int, int>> GetNeighbors(const pair<int, int> &cell, int rows, int cols)
{
    vector<pair<int, int>> r;
    for (int i = cell.first - 1; i <= cell.first + 1; i++)
    {
        for (int j = cell.second - 1; j <= cell.second + 1; j++)
        {
            if (0 <= i && i < rows && 0 <= j && j < cols && (i != cell.first || j != cell.second))
                r.push_back(make_pair(i, j));
        }
    }
    return r;
};

// Given a cell in a grid, get one of its neighbors randomly (horizontal, vertical or diagonal)
static pair<int, int> RandomNeighbor(const pair<int, int> &cell, int rows, int cols)
{
    vector<pair<int, int>> n = GetNeighbors(cell, rows, cols);
    return n[rand() % n.size()];
};

namespace MatrixGenerator
{
static char RandomChar()
{
    return 'a' + (rand() % 26);
}

static vector<vector<char>> RandomWithoutWord(const string &word)
{
    set<char> unique = String::UniqueChars(word);
    vector<vector<char>> matrix;
    size_t len = max(((int)word.size() + 1) >> 1, 2);
    for (size_t i = 0; i < len; i++)
    {
        vector<char> r;
        for (size_t j = 0; j < len; j++)
        {
            char c;
            while (true)
            {
                c = RandomChar();
                if (unique.find(c) == unique.end())
                    break;
            }
            r.push_back(c);
        }
        matrix.push_back(r);
    }
    return matrix;
}

static vector<vector<char>> RandomWithWord(const string &word)
{
    vector<vector<char>> matrix = RandomWithoutWord(word);
    if (word.length() == 0)
        return matrix;
    int rows = matrix.size();
    int cols = matrix[0].size();
    int i = rand() % rows;
    int j = rand() % cols;
    size_t l = 0;
    matrix[i][j] = word[l];
    pair<int, int> c = make_pair(i, j);
    set<pair<int, int>> visited;
    visited.insert(c);
    for (l = 1; l < word.length(); l++)
    {
        while (true)
        {
            pair<int, int> n = RandomNeighbor(c, rows, cols);
            if (visited.find(n) == visited.end())
            {
                visited.insert(n);
                c = n;
                break;
            }
        }
        matrix[c.first][c.second] = word[l];
    }
    return matrix;
}
} // namespace MatrixGenerator

namespace SearchWord
{
// Allow one cell to be used twice
static bool Existed(const vector<vector<char>> &matrix, const string &word)
{
    if (word.length() == 0 || matrix.size() == 0 || matrix[0].size() == 0)
        return false;

    function<bool(const pair<int, int> &, const string &)>
        search = [&](const pair<int, int> &cell, const string &w) -> bool {
        if (matrix[cell.first][cell.second] != w[0])
            return false;
        if (w.length() == 1)
            return true;
        vector<pair<int, int>> neighbors = GetNeighbors(cell, (int)matrix.size(), (int)matrix[0].size());
        for (size_t i = 0; i < neighbors.size(); i++)
        {
            if (search(neighbors[i], w.substr(1)))
                return true;
        }
        return false;
    };

    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[0].size(); j++)
        {
            auto p = make_pair(i, j);
            if (search(p, word))
                return true;
        }
    }
    return false;
}

// This is buggy
static bool Existed2(const vector<vector<char>> &matrix, const string &word)
{
    if (word.length() == 0 || matrix.size() == 0 || matrix[0].size() == 0)
        return false;

    function<bool(const pair<int, int> &)>
        search = [&](const pair<int, int> &cell) -> bool {
        if (matrix[cell.first][cell.second] != word[0])
            return false;
        if (word.length() == 1)
            return true;
        // unordered_map<pair<int, int>, vector<pair<int, int>>> neighbors;
        map<pair<int, int>, vector<pair<int, int>>> neighbors;
        stack<pair<int, int>> path;
        path.push(cell);
        neighbors[cell] = GetNeighbors(cell, (int)matrix.size(), (int)matrix[0].size());
        while (!path.empty())
        {
            pair<int, int> c = path.top();
            if (neighbors.find(c) == neighbors.end())
                neighbors[c] = GetNeighbors(c, (int)matrix.size(), (int)matrix[0].size());
            while (neighbors[c].size() > 0)
            {
                pair<int, int> n = neighbors[c][0];
                // This has a problem. If c is visited again, then we might miss some options
                // because some of its neighbors have already been erased.
                // Look at the tests for failures.
                // What f we do not allow to reuse a cell? Will this work?
                neighbors[c].erase(neighbors[c].begin());
                if (matrix[n.first][n.second] == word[path.size()])
                {
                    if (path.size() == word.length() - 1)
                        return true;
                    path.push(n);
                    break;
                }
            }
            if (c == path.top())
                path.pop();
        }
        return false;
    };

    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[0].size(); j++)
        {
            auto p = make_pair(i, j);
            if (search(p))
                return true;
        }
    }
    return false;
}
} // namespace SearchWord

// Given a chess board containing 'X' and 'O'.
// Capture the regions of 'o's and flip 'o's to 'x's.
// Ignore the regions on the board boundary.
// X X X X          X X X X
// X O O X    =>    X X X X
// X X O X          X X X X
// X O X X          X O X X
namespace SurroundedRegion
{
static void Capture(vector<vector<char>> &board)
{
    int height = board.size();
    if (height == 0)
        return;
    int width = board[0].size();
    set<pair<int, int>> nocapture;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j] == 'O')
            {
                pair<int, int> p = make_pair(i, j);
                if (nocapture.find(p) != nocapture.end())
                {
                    continue;
                }
                bool boundary = i == 0 || i == height - 1 || j == 0 || j == width - 1;
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

                if (boundary)
                {
                    nocapture.insert(region.begin(), region.end());
                }
                else
                {
                    for_each(region.begin(), region.end(), [&](pair<int, int> p) {
                        board[p.first][p.second] = 'X';
                    });
                }
            }
        }
    }
}

static void Capture2(vector<vector<char>> &board)
{
    int height = board.size();
    if (height == 0)
        return;
    int width = board[0].size();

    auto search = [&](int i, int j) {
        if (board[i][j] == 'O')
        {
            board[i][j] = 'C';
            pair<int, int> p = make_pair(i, j);
            queue<pair<int, int>> q;
            q.push(p);
            while (!q.empty())
            {
                p = q.front();
                q.pop();
                pair<int, int> n;
                if (p.first > 0 && board[p.first - 1][p.second] == 'O')
                {
                    board[p.first - 1][p.second] = 'C';
                    n = make_pair(p.first - 1, p.second);
                    q.push(n);
                }
                if (p.second > 0 && board[p.first][p.second - 1] == 'O')
                {
                    board[p.first][p.second - 1] = 'C';
                    n = make_pair(p.first, p.second - 1);
                    q.push(n);
                }
                if (p.second < width - 1 && board[p.first][p.second + 1] == 'O')
                {
                    board[p.first][p.second + 1] = 'C';
                    n = make_pair(p.first, p.second + 1);
                    q.push(n);
                }
                if (p.first < height - 1 && board[p.first + 1][p.second] == 'O')
                {
                    board[p.first + 1][p.second] = 'C';
                    n = make_pair(p.first + 1, p.second);
                    q.push(n);
                }
            }
        }
    };

    for (int i = 0; i < height; i++)
    {
        search(i, 0);
        search(i, width - 1);
    }

    for (int i = 0; i < width; i++)
    {
        search(0, i);
        search(height - 1, i);
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j] == 'O')
            {
                board[i][j] = 'X';
            }
            else if (board[i][j] == 'C')
            {
                board[i][j] = 'O';
            }
        }
    }
}
} // namespace SurroundedRegion

namespace Palindrome
{
// input: c_0, c_1, c_2, ..., c_i, ..., c_j, ..., c_(n-1)
// Let L_(i, j) be the length of the longest palindrome
// subsequence of input c[i..j]
// L_(i, j) = 1,                             if i == j
//            2,                             if i+1 == j, c_i == c_j
//            1,                             if i+1 == j, c_i != c_j
//            2 + L_(i+1, j-1),              if c_i == c_j, i+1 < j
//            max(L_(i, j-1), L_(i+1, j),    if c_i != c_j, i+1 < j
//
//	       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
// 0(c)    1       1       1       1       3       5       5       5       5
// 1(h)    0       1       1       1       3       3       3       3       3
// 2(a)    0       0       1       1       3       3       3       3       3
// 3(r)    0       0       0       1       1       1       1       1       3
// 4(a)    0       0       0       0       1       1       1       1       1
// 5(c)    0       0       0       0       0       1       1       1       1
// 6(t)    0       0       0       0       0       0       1       1       1
// 7(e)    0       0       0       0       0       0       0       1       1
// 8(r)    0       0       0       0       0       0       0       0       1
static void LengthTable(string &input, Matrix<size_t> &length)
{
    for (size_t i = 0; i < input.length(); i++)
    {
        // Set L_(i, i)
        length(i, i) = 1;

        // Set L_(i, i+1)
        if (i + 1 < input.length())
        {
            if (input[i] == input[i + 1])
            {
                length(i, i + 1) = 2;
            }
            else
            {
                length(i, i + 1) = 1;
            }
        }
    }

    for (size_t j = 2; j < input.length(); j++)
    {
        for (size_t i = 0; i + j < input.length(); i++)
        {
            // Set L_(i, i+j)
            if (input[i] == input[i + j])
            {
                length(i, i + j) = 2 + length(i + 1, i + j - 1);
            }
            else
            {
                length(i, i + j) = max(length(i, i + j - 1), length(i + 1, i + j));
            }
        }
    }
}

static void LongestSubsequenceByTable(string &input, string &output)
{
    Matrix<size_t> length(input.length(), input.length());

    // Compute the length table
    LengthTable(input, length);

    size_t i = 0;
    size_t j = input.length() - 1;

    if (length(i, j) == 1)
    {
        // no Parlindrome found, return the last char
        output.append(&input[j], 1);
        return;
    }

    size_t k = 0;

    while ((j - i) > 1)
    {
        while (length(i, j - 1) == length(i, j))
        {
            j--;
        }

        // The while loop stop when L_(i, j-1) != L_(i, j)
        // Now input[j] must be in the palindrome
        char c = input[j];
        j--;

        // Output a pair of c.
        // k will be the next insertion place.
        output.insert(k++, 1, c);
        output.insert(k, 1, c);

        while (input[i] != c)
        {
            i++;
        }

        i++;
    }

    // j = i or j = i+1
    output.insert(k, 1, input[j]);
    if (i + 1 == j && input[i] == input[j])
    {
        // The palindrome is of form xxxccxxxx
        output.insert(k, 1, input[j]);
    }
}

// k       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
// 0       1       1       1       1       1       1       1       1       1
// 1       1       1       1       1       1       1       1       1       1
// 2       1       1       1       1       3       1       1       1       1
// 3       1       1       1       1       3       3       1       1       1
// 4       1       1       1       1       3       3       3       1       1
// 5       1       1       1       1       3       5       3       3       1
// 6       1       1       1       1       3       5       5       3       3
// 7       1       1       1       1       3       5       5       5       3
// 8       1       1       1       1       3       5       5       5       5
// At step k, length[i] is the length of the longest palindrome
// subsequence from input[i-k] to input[i]
static void LengthArray(string &input, size_t length[])
{
    unique_ptr<size_t[]> len2(new size_t[input.length()]);
    unique_ptr<size_t[]> len1(new size_t[input.length()]);

    // Compute all length=1 substrings
    for (int i = input.length() - 1; i >= 0; i--)
    {
        length[i] = 1;
        len2[i] = length[i];
    }

    // Compute all length=2 substrings
    for (int i = input.length() - 1; i >= 1; i--)
    {
        if (input[i - 1] == input[i])
        {
            length[i] = 2;
        }
        len1[i] = length[i];
    }

    // Compute all length=(k+1) substrings
    for (int k = 2; k < (int)input.length(); k++)
    {
        for (int i = input.length() - 1; i >= k; i--)
        {
            if (input[i - k] == input[i])
            {
                length[i] = 2 + len2[i - 1];
            }
            else
            {
                length[i] = max(len1[i - 1], len1[i]);
            }
        }

        memcpy(len2.get(), len1.get(), input.length() * sizeof(size_t));
        memcpy(len1.get(), length, input.length() * sizeof(size_t));
    }
}

static void LongestSubsequenceByArray(string &input, string &output)
{
    unique_ptr<size_t[]> length(new size_t[input.length()]);
    LengthArray(input, length.get());

    int i = 0;
    int j = (int)input.length() - 1;

    if (length[j] == 1)
    {
        // no Parlindrome found, return the last char
        output.append(&input[j], 1);
        return;
    }

    int k = 0;

    while ((j - i + 1) > max((int)length[j], 2))
    {
        while (length[j - 1] == length[j])
            j--;
        char c = input[j];
        j--;
        output.insert(k++, 1, c);
        output.insert(k, 1, c);
        while (input[i] != c)
            i++;
        i++;
    }

    if (j == i + 1 && input[i] != input[j])
    {
        output.insert(k, 1, input[j]);
    }
    else
    {
        // input[i..j] is a palindrome of length[j]
        for (int p = j; p >= i; p--)
        {
            output.insert(k, 1, input[p]);
        }
    }
}

// Manacher Algorithm
// Discussed at http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
// Find the longest substring (contiguous characters) which is a palindrome
void LongestSubstring(string &input, string &output)
{
    int length = 1 + 2 * input.size();
    unique_ptr<int[]> p(new int[length]);

    // #  b  #  a  #  b  #  c  #  b  #  a  #  b  #  c  #  b  #  a  #  c  #  c  #  b  #  a  #
    // Original characters are at the odd positions
    auto getChar = [&](int i) -> char {
        if (i % 2 == 1)
        {
            return input[i >> 1];
        }
        else
        {
            return '#';
        }
    };

    // Given current index c and its palindrome length p[c],
    // try to expand it as far as possible.
    // p[c] is updated.
    auto expand = [&](int c) -> int {
        while (true)
        {
            int m = c - p[c] - 1;
            if (m < 0)
                break;
            int n = c + p[c] + 1;
            if (n >= length)
                break;
            if (getChar(m) != getChar(n))
                break;
            p[c]++;
        }

        return p[c];
    };
    /*
    auto printi = [&]() {
        printf("\t");
        for (int i = 0; i < length; i++)
        {
            printf("  %c", getChar(i));
        }
        printf("\n");
    };

    auto printp = [&](int i) {
        printf("%d\t", i);
        for (int j = 0; j <= i; j++)
        {
            printf("  %d", p[j]);
        }
        printf("\n");
    };
*/
    int maxLength = 0;
    int maxIndex = 0;
    p[0] = 0;
    int c = 0; // The center of current range
    int r = 0; // The right-most boundary of current range, i.e., c + p[c]
    for (int i = 1; i < length; i++)
    {
        // p[i] should be the same of its mirror about the current center but also bounded by the current range
        int j = 2 * c - i;
        if (i < r && p[j] < r - i)
        {
            // p[i] does not exceed the right-most boundary
            p[i] = p[j];
        }
        else
        {
            // p[i] exceeds the right-most boundary
            p[i] = i >= r ? 0 : r - i;

            // Expand as much as possible
            expand(i);

            // Update range
            if (i + p[i] > r)
            {
                c = i;
                r = c + p[c];
            }

            // Update maximum
            if (p[i] > maxLength)
            {
                maxLength = p[i];
                maxIndex = i;
            }
        }

        // printi();
        // printp(i);
    }

    int i = maxIndex - maxLength + 1;
    string::iterator b = output.begin();
    int j = 0;
    while (i < maxIndex)
    {
        char c = getChar(i);
        output.insert(b + j++, c);
        output.insert(b + j, c);
        i += 2;
    }

    if (i == maxIndex)
    {
        output.insert(b + j, getChar(i));
    }
}

bool IsPalindrom(unsigned int number)
{
    if (number < 10)
        return true;

    unsigned int base = 1;
    while ((number / base) >= 10)
    {
        base *= 10;
    }

    // Compare the most significant digit (MSD) and the least significant digit (LSD)
    while (number >= 10)
    {
        if ((number / base) != (number % 10))
        {
            // MSD is different from LSD
            return false;
        }

        // Peel off MSD and LSD
        number = (number % base) / 10;
        base /= 100;
    }

    return true;
}

// Determine if a string is palindrome.
// 1. Consider alphanumeric characters only. Ignore others.
// 2. Ignore case
static bool IsPalindrom(const string &input)
{
    if (input.size() == 0)
        return true;

    auto isAlphaNumeric = [&](char c) -> bool {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    };

    auto equal = [&](char a, char b) -> bool {
        if (a >= 'a' && a <= 'z' && ((b - 'a' == a - 'a') || (b - 'A' == a - 'a')))
            return true;
        else if (a >= 'A' && a <= 'Z' && ((b - 'a' == a - 'A') || (b - 'A' == a - 'A')))
            return true;
        else if (a >= '0' && a <= '9' && b == a)
            return true;
        return false;
    };

    int i = 0;
    int j = input.size() - 1;
    while (i <= j)
    {
        while (i <= j && !isAlphaNumeric(input[i]))
            i++;
        while (i <= j && !isAlphaNumeric(input[j]))
            j--;
        if (i > j)
            return true;
        if (!equal(input[i], input[j]))
            return false;
        i++;
        j--;
    }
    return true;
}

// Partition input into a set of palindrom substrings.
// Return all possible sets.
static vector<vector<string>> Partition(const string &input)
{
    function<void(const string &, size_t, map<size_t, vector<vector<string>>> &)>
        partition = [&](
                        const string &s,
                        size_t index,
                        map<size_t, vector<vector<string>>> &sets) {
            if (sets.find(index) == sets.end())
            {
                sets[index] = vector<vector<string>>{};
            }

            for (size_t k = index; k < s.length(); k++)
            {
                int i = index;
                int j = k;
                while (i <= j)
                {
                    if (s[i] != s[j])
                        break;
                    i++;
                    j--;
                }
                if (i > j)
                {
                    // s[index..k] is a palindrom
                    if (k == s.length() - 1)
                    {
                        sets[index].push_back(vector<string>{s.substr(index, k - index + 1)});
                    }
                    else
                    {
                        if (sets.find(k + 1) == sets.end())
                        {
                            partition(s, k + 1, sets);
                        }
                        for_each(sets[k + 1].begin(), sets[k + 1].end(), [&](vector<string> &r) {
                            vector<string> set = {s.substr(index, k - index + 1)};
                            set.insert(set.end(), r.begin(), r.end());
                            sets[index].push_back(set);
                        });
                    }
                }
            }
        };

    map<size_t, vector<vector<string>>> partitions;
    partition(input, 0, partitions);
    return partitions[0];
}

// Partition input into a set of palindrom substrings.
// Return the partion with minimum cut, i.e., the count of
// palindrome substrings is as less as possible.
static vector<string> MinCutPartition(const string &input)
{
    function<void(const string &, size_t, map<size_t, vector<string>> &)>
        partition = [&](
                        const string &s,
                        size_t index,
                        map<size_t, vector<string>> &set) {
            if (set.find(index) == set.end())
            {
                set[index] = vector<string>{};
            }

            size_t minIndex = index;
            size_t minCuts = s.length();
            for (size_t k = index; k < s.length(); k++)
            {
                int i = index;
                int j = k;
                while (i <= j)
                {
                    if (s[i] != s[j])
                        break;
                    i++;
                    j--;
                }
                if (i > j)
                {
                    // s[index..k] is a palindrom
                    if (k == s.length() - 1)
                    {
                        set[index].push_back(s.substr(index, k - index + 1));
                        return;
                    }
                    else
                    {
                        if (set.find(k + 1) == set.end())
                        {
                            partition(s, k + 1, set);
                        }
                        if (set[k + 1].size() < minCuts)
                        {
                            minCuts = set[k + 1].size();
                            minIndex = k + 1;
                        }
                    }
                }
            }

            set[index].push_back(s.substr(index, minIndex - index));
            set[index].insert(set[index].end(), set[minIndex].begin(), set[minIndex].end());
        };

    map<size_t, vector<string>> mincut;
    partition(input, 0, mincut);
    return mincut[0];
}

// Partition input into a set of palindrom substrings.
// Return the partion with minimum cut, i.e., the count of
// palindrome substrings is as less as possible.
static int MinCutPartition2(const string &input)
{
    unique_ptr<int[]> mincut(new int[input.length()]);
    vector<vector<bool>> palindrome(input.size(), vector<bool>(input.size(), false));
    for (int i = input.length() - 1; i >= 0; i--)
    {
        mincut[i] = input.length() - i - 1;
        for (int j = i; j < (int)input.length(); j++)
        {
            if (input[i] == input[j])
            {
                if (j - i <= 1)
                {
                    palindrome[i][j] = true;
                }
                else
                {
                    palindrome[i][j] = palindrome[i + 1][j - 1];
                }
            }
            else
            {
                palindrome[i][j] = false;
            }
            if (palindrome[i][j])
            {
                // input[i..j] is a palindrome
                if (j == (int)input.length() - 1)
                {
                    mincut[i] = 0;
                    break;
                }
                else
                {
                    if (mincut[j + 1] + 1 < mincut[i])
                    {
                        mincut[i] = mincut[j + 1] + 1;
                    }
                }
            }
        }
    }
    return mincut[0];
}
} // namespace Palindrome

namespace Partition
{
// Reorder input[low..high] such that it is partioned at the indices
// provided through an array. Parameter low and high give the range of
// elements in input. Parameter first and last give the range of indices
// used to partion input. The elements of indices are sorted and are valid
// indices of input array.
// TODO: Missing code
template <class T>
static void PartitionArrayByOrders(T *input, int low, int high, int *indices, int first, int last)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (low < 0)
        throw invalid_argument(String::Format("low %d is less than zero", low));
    if (high < low)
        throw invalid_argument(String::Format("low %d is greater than high %d", low, high));
    if (indices == nullptr)
        throw invalid_argument("indices is nullptr");
    if (first < 0)
        throw invalid_argument(String::Format("first %d is less than zero", first));
    if (last < first)
        throw invalid_argument(String::Format("first %d is greater than last %d", first, last));
    if (last - first > high - low)
        throw invalid_argument(String::Format("There are %d indices but only %d elements", last - first, high - low));
    if (low > indices[first])
        throw invalid_argument(String::Format("low %d is greater than indices[%d] %d", low, first, indices[first]));
    if (high < indices[last])
        throw invalid_argument(String::Format("high %d is less than indices[%d] %d", high, last, indices[last]));
    if (low == high)
        return;

    if (first == last)
    {
        if (low <= indices[first] && indices[first] <= high)
        {
            // TODO: PartitionArrayByOrder(input, low, high, indices[first] - low);
        }

        return;
    }

    int m = 0; // TODO: PartitionArrayRandomly(input, low, high);

    // Find the last element index in indices less than m
    int k = first; // TODO: + BinarySearch::PositionToInsert<int>(m, &indices[first], last - first + 1);

    // low ................................ m ............................... high
    //        indices[fist] .... indices[k]   indices[k+1] .... indices[last]
    // first <= k < last, if indices[first] < m < indices[last]
    //
    // low .. m ............................................................. high
    //      k   indices[fist] ................................. indices[last]
    // k < first, if m <= indices[first]
    //
    // low ............................................................... m .... high
    //       indices[fist] ................................. indices[last]   k
    // last <= k, if indices[last] < m

    if (first <= k && k < last)
    {
        // indices[k] < m <= indices[k+1]
        if (m == indices[k + 1])
        {
            PartitionArrayByOrders(input, low, m - 1, indices, first, k);
            if (k + 1 < last)
                PartitionArrayByOrders(input, m + 1, high, indices, k + 2, last);
        }
        else
        {
            PartitionArrayByOrders(input, low, m - 1, indices, first, k);
            PartitionArrayByOrders(input, m + 1, high, indices, k + 1, last);
        }
    }
    else if (k < first)
    {
        // m <= indices[first]
        if (m == indices[first])
            PartitionArrayByOrders(input, m + 1, high, indices, first + 1, last);
        else
            PartitionArrayByOrders(input, m + 1, high, indices, first, last);
    }
    else if (last <= k)
    {
        PartitionArrayByOrders(input, low, m - 1, indices, first, last);
    }
}

// The k-th quantiles of an array with length are k-1 elements evenly
// dividing the array so that the set of subarrays is sorted, i.e., each
// element of a subarray is not less than each element of its preceeding subarray,
// and not greater than each element of its succeeding subarray.
// This method partition the input array and return the indices of the k-1 elements
// forming the quantiles. Parameter order defines the order of quantiles,
// i.e., array indices will be used to return order-1 indices.
template <class T>
static void PartitionArrayByQuantiles(T *input, int length, int *indices, int order)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
    if (indices == nullptr)
        throw invalid_argument("indices is nullptr");
    if (order < 1)
        throw invalid_argument(String::Format("order %d is less than 1", order));
    if (order > length)
        throw invalid_argument(String::Format("order %d is greater than length %d", order, length));

    if (order == 1)
        return;

    int step = length / order;
    int remainder = length % order;

    // 0                                                                                                         L-1
    // +----------+----------+----------+----------+----------+----------+----------+----------+----------+-------+
    // 0         step       2*step             (R-1)*step   R*step                         (O-1)*step   O*step  O*step+R-1
    //            0          1                    R-2        R-1         R                    O-2

    int s = 0;
    if (step > 1)
    {
        for (int i = 0; i < remainder; i++)
        {
            indices[i] = s + step;
            s = indices[i];
        }

        for (int i = remainder; i < order - 1; i++)
        {
            indices[i] = s + step - 1;
            s = indices[i];
        }
    }
    else
    {
        for (int i = 0; i < order - 1; i++)
        {
            indices[i] = s + step;
            s = indices[i];
        }
    }

    PartitionArrayByOrders(input, 0, length - 1, indices, 0, order - 2);
}

} // namespace Partition

// Find the median from two sorted arrays.
// If the two arrays contain odd number of elements, then the median is unique.
// If the two arrays contain even number of elements, then return the lower median.
template <class T>
static T FindMedian(const T *input1, int length1, const T *input2, int length2)
{
    if (input1 == nullptr)
        throw invalid_argument("input1 is a nullptr");
    if (length1 <= 0)
        throw invalid_argument(String::Format("length1 %d is invalid", length1));
    if (input2 == nullptr)
        throw invalid_argument("input2 is a nullptr");
    if (length2 <= 0)
        throw invalid_argument(String::Format("length2 %d is invalid", length2));

    const T *shortArray;
    int shortLength;
    const T *longArray;
    int longLength;

    if (length1 <= length2)
    {
        shortLength = length1;
        shortArray = input1;
        longLength = length2;
        longArray = input2;
    }
    else
    {
        shortLength = length2;
        shortArray = input2;
        longLength = length1;
        longArray = input1;
    }

    int medianIndex = (shortLength + longLength - 1) / 2;
    if (shortArray[shortLength - 1] <= longArray[0])
    {
        if (medianIndex == shortLength - 1)
        {
            // +---------------------------------------+  +---------------------------------------+
            // 0                                      s-1 0                                      l-1
            // s = l
            // m = s - 1 = l - 1
            return shortArray[medianIndex];
        }
        else
        {
            // +---------------------------------------+  +-----+------------------------------------------+
            // 0                                      s-1 0    m-s                                        l-1
            // s < l
            // m = (s + l - 1) / 2
            //   = k - 1    if (s + l) = 2k
            //     k - 1    if (s + l) = 2k - 1
            // s - 1 < m < l - 1
            return longArray[medianIndex - shortLength];
        }
    }
    else if (longArray[longLength - 1] <= shortArray[0])
    {
        // +---------------------------------------+---------+  +---------------------------------------+
        // 0                                       m        l-1 0                                      s-1
        // s <= l
        // m = (s + l - 1) / 2
        //   = k - 1    if (s + l) = 2k
        //     k - 1    if (s + l) = 2k - 1
        // s - 1 <= m <= l - 1
        return longArray[medianIndex];
    }

    // +---------------------------------------+
    // 0             m-1 m m+1                s-1
    // +-----------------------------------------------+
    // 0             n-1 n n+1                        l-1
    //
    // From (m + 1) + (n + 1) = medianIndex + 1
    // get: m + n = medianIndex - 1
    // Median = S[m] if L[n] < S[m] <= L[n+1], i.e. S[m] is the lower median and L[n+1] is the higher median
    //          L[n] if S[m] < L[n] <= S[m+1], i.e. L[n] is the lower median and S[m+1] is the higher median
    //          S[m] if S[m] == L[n], i.e. S[m] or L[n] is the lower median and min(S[m+1], L[n+1]) is the higher median
    //          max(S[m-1], L[n+1]) if S[m] > L[n+1], and S[m] is the higher median
    //          max(S[m+1], L[n-1]) if L[n] > S[m+1], and L[n] is the higher median

    int low = 0;
    int high = shortLength - 1;
    while (true)
    {
        // (1) If low < high - 1, then low < m < high
        // (2) If low = high - 1, then low = m < high
        // (3) If low = high, then low = m = high
        int m = (low + high) >> 1;
        int n = medianIndex - m - 1;
        if (shortArray[m] > longArray[n])
        {
            if (shortArray[m] <= longArray[n + 1])
            {
                return shortArray[m];
            }
            else
            {
                if (m < high)
                {
                    // Case (1) or (2)
                    high = m;
                }
                else
                {
                    // Case (3)
                    // s[m] > l[n] and s[m] > l[n+1]
                    // Compare s[m-1] and l[n+1] as one of them is the median
                    if (m - 1 >= 0 && shortArray[m - 1] > longArray[n + 1])
                        return shortArray[m - 1];
                    else
                        return longArray[n + 1];
                }
            }
        }
        else if (longArray[n] > shortArray[m])
        {
            if (longArray[n] <= shortArray[m + 1])
            {
                return longArray[n];
            }
            else
            {
                if (low < m)
                {
                    // Case (1)
                    low = m;
                }
                else
                {
                    // Case (2) or (3)
                    // l[n] > s[m] and l[n] > s[m+1]
                    // Compare l[n-1] and s[m+1]
                    if (n - 1 >= 0 && longArray[n - 1] > shortArray[m + 1])
                        return longArray[n - 1];
                    else
                        return shortArray[m + 1];
                }
            }
        }
        else
        {
            return shortArray[m];
        }
    }
}

// Find k closest neighbors to the i-th order element.
// Parameter pivotIndex is the order of the input element.
// When the method finishes, the first 1 + countNeighbors elements are the pivot element and its closest neighbors.
template <class T>
static T SelectClosestNeighbors(T *input, int length, int pivotIndex, int countNeighbors)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
    if (pivotIndex < 0 || pivotIndex >= length)
        throw invalid_argument(String::Format("pivotIndex %d is not in [0, %d]", pivotIndex, length - 1));
    if (countNeighbors < 0 || countNeighbors >= length)
        throw invalid_argument(String::Format("countNeighbors %d is not in [0, %d]", countNeighbors, length - 1));
    // TODO: Partition::PartitionArrayByOrder(input, 0, length - 1, pivotIndex);
    T pivot = input[pivotIndex];
    // TODO: Partition::PartitionArrayByOrder<T, int>(input, 0, length - 1, countNeighbors, [&pivot](T v) -> int { return abs(v - pivot); });
    return pivot;
}

namespace KthOrder
{
// Find the k-th order statistic (smallest element) from two sorted arrays.
// k = 1, 2, ...
template <class T>
static T Solve(int k, const T *input1, int length1, const T *input2, int length2)
{
    if (input1 == nullptr)
        throw invalid_argument("input1 is a nullptr");
    if (length1 <= 0)
        throw invalid_argument(String::Format("length1 %d is invalid", length1));
    if (input2 == nullptr)
        throw invalid_argument("input2 is a nullptr");
    if (length2 <= 0)
        throw invalid_argument(String::Format("length2 %d is invalid", length2));
    if (k <= 0)
        throw invalid_argument(String::Format("k %d is invalid", k));
    if (k > length1 + length2)
        throw invalid_argument(String::Format("k(%d) is greater than length1(%d) + length2(%d)", k, length1, length2));

    const T *shortArray;
    int shortLength;
    const T *longArray;
    int longLength;

    if (length1 <= length2)
    {
        shortLength = length1;
        shortArray = input1;
        longLength = length2;
        longArray = input2;
    }
    else
    {
        shortLength = length2;
        shortArray = input2;
        longLength = length1;
        longArray = input1;
    }

    if (shortArray[shortLength - 1] <= longArray[0])
    {
        if (k <= shortLength)
        {
            // +-----------------------+---------------+  +---------------------------------------+
            // 0                      k-1             s-1 0                                      l-1
            return shortArray[k - 1];
        }
        else
        {
            // +---------------------------------------+  +-----+------------------------------------------+
            // 0                                      s-1 0   k-s-1                                       l-1
            return longArray[k - shortLength - 1];
        }
    }
    else if (longArray[longLength - 1] <= shortArray[0])
    {
        if (k <= longLength)
        {
            // +---------------------------------------+---------+  +---------------------------------------+
            // 0                                      k-1       l-1 0                                      s-1
            return longArray[k - 1];
        }
        else
        {
            // +-------------------------------------------------+  +--------+------------------------------+
            // 0                                                l-1 0      k-l-1                           s-1
            return shortArray[k - longLength - 1];
        }
    }

    if (k == 1)
    {
        return std::min<T>(shortArray[0], longArray[0]);
    }

    if (k == shortLength + longLength)
    {
        return std::max<T>(shortArray[shortLength - 1], longArray[longLength - 1]);
    }

    // +---------------------------------------+
    // 0             m-1 m m+1                s-1
    // +-----------------------------------------------+
    // 0             n-1 n n+1                        l-1
    //
    // From (m+1) + (n+1) = k
    // get: m + n = k - 2
    // k-th = S[m] if L[n] < S[m] <= L[n+1]
    //        L[n] if S[m] < L[n] <= S[m+1]
    //        S[m] if S[m] == L[n]
    //        max(S[m-1], L[n+1]) if S[m] > L[n+1]
    //        max(S[m+1], L[n-1]) if L[n] > S[m+1]

    int low = 0;
    int high = std::min<int>(k - 1, shortLength - 1);
    while (low <= high)
    {
        // (1) If low < high - 1, then low < m < high
        // (2) If low = high - 1, then low = m < high
        // (3) If low = high, then low = m = high
        int m = (low + high) >> 1;
        int n = k - m - 2;
        if (n >= longLength)
        {
            // this may happen if k > m + longLength + 1
            low = low < m ? m : m + 1;
        }
        else if (shortArray[m] > longArray[n])
        {
            if (n == longLength - 1 || shortArray[m] <= longArray[n + 1])
            {
                return shortArray[m];
            }
            else
            {
                if (m < high)
                {
                    // Case (1) or (2)
                    high = m;
                }
                else
                {
                    // Case (3)
                    // s[m] > l[n] and s[m] > l[n+1]
                    // Compare s[m-1] and l[n+1] as one of them is the k-th
                    if (m - 1 >= 0 && shortArray[m - 1] > longArray[n + 1])
                        return shortArray[m - 1];
                    else
                        return longArray[n + 1];
                }
            }
        }
        else if (longArray[n] > shortArray[m])
        {
            if (m == shortLength - 1 || longArray[n] <= shortArray[m + 1])
            {
                return longArray[n];
            }
            else
            {
                if (low < m)
                {
                    // Case (1)
                    low = m;
                }
                else
                {
                    // Case (2) or (3)
                    // l[n] > s[m] and l[n] > s[m+1]
                    // Compare l[n-1] and s[m+1] as one of them is the k-th
                    if (n - 1 >= 0 && longArray[n - 1] > shortArray[m + 1])
                        return longArray[n - 1];
                    else
                        return shortArray[m + 1];
                }
            }
        }
        else
        {
            return shortArray[m];
        }
    }

    throw runtime_error(String::Format("Unable to find %d-th smallest element", k));
}

template <class T>
static T Solve2(int k, const T *input1, int length1, const T *input2, int length2)
{
    if (input1 == nullptr)
        throw invalid_argument("input1 is a nullptr");
    if (length1 <= 0)
        throw invalid_argument(String::Format("length1 %d is invalid", length1));
    if (input2 == nullptr)
        throw invalid_argument("input2 is a nullptr");
    if (length2 <= 0)
        throw invalid_argument(String::Format("length2 %d is invalid", length2));
    if (k <= 0)
        throw invalid_argument(String::Format("k %d is invalid", k));
    if (k > length1 + length2)
        throw invalid_argument(String::Format("k(%d) is greater than length1(%d) + length2(%d)", k, length1, length2));

    if (k == 1)
    {
        return std::min<T>(input1[0], input2[0]);
    }

    // +-----------------------------------+
    // 0             m m+1                s-1
    // +-------------------------------------------+
    // 0             n n+1                        l-1
    //
    // find m + n = k - 2
    // k-th = S[m] if L[n] < S[m]
    //        L[n] if S[m] < L[n]
    //        S[m] if S[m] == L[n]

    int m = -1;
    int n = -1;
    while (m + n < k - 2)
    {
        if (m < length1 - 1 && n < length2 - 1)
        {
            if (input1[m + 1] <= input2[n + 1])
            {
                m++;
            }
            else
            {
                n++;
            }
        }
        else if (m < length1 - 1 && n == length2 - 1)
        {
            m++;
        }
        else if (m == length1 - 1 && n < length2 - 1)
        {
            n++;
        }
        else
        {
            break;
        }
    }

    if (m + n == k - 2)
    {
        if (n == -1)
        {
            return input1[m];
        }
        else if (m == -1)
        {
            return input2[n];
        }
        else
        {
            return std::max<T>(input1[m], input2[n]);
        }
    }
    else
    {
        throw runtime_error(String::Format("Unable to find %d-th smallest element", k));
    }
}
} // namespace KthOrder

namespace Intersection
{
// Find the first common element of two sorted arrays
// Return a pair of indices of found element. If not found, then return a pair (-1, -1)
// http://leetcode.com/2010/03/here-is-phone-screening-question-from.html
template <class T>
static pair<int, int> Solve(const T *input1, int length1, const T *input2, int length2)
{
    if (input1 == nullptr)
        throw invalid_argument("input1 is a nullptr");
    if (length1 <= 0)
        throw invalid_argument(String::Format("length1 %d is invalid", length1));
    if (input2 == nullptr)
        throw invalid_argument("input2 is a nullptr");
    if (length2 <= 0)
        throw invalid_argument(String::Format("length2 %d is invalid", length2));

    const T *shortArray;
    int shortLength;
    const T *longArray;
    int longLength;

    if (length1 <= length2)
    {
        shortLength = length1;
        shortArray = input1;
        longLength = length2;
        longArray = input2;
    }
    else
    {
        shortLength = length2;
        shortArray = input2;
        longLength = length1;
        longArray = input1;
    }

    for (int i = 0; i < shortLength; i++)
    {
        int j = longArray[longLength - 1]; // TODO: BinarySearch::Search<T>(shortArray[i], longArray, longLength, true);
        if (j != -1)
        {
            if (shortArray == input1)
            {
                return make_pair(i, j);
            }
            else
            {
                return make_pair(j, i);
            }
        }
    }

    return make_pair(-1, -1);
}

template <class T>
static pair<int, int> Solve2(const T *input1, int length1, const T *input2, int length2)
{
    if (input1 == nullptr)
        throw invalid_argument("input1 is a nullptr");
    if (length1 <= 0)
        throw invalid_argument(String::Format("length1 %d is invalid", length1));
    if (input2 == nullptr)
        throw invalid_argument("input2 is a nullptr");
    if (length2 <= 0)
        throw invalid_argument(String::Format("length2 %d is invalid", length2));

    int i = 0;
    int j = 0;
    while (i < length1 && j < length2)
    {
        if (input1[i] < input2[j])
        {
            i++;
        }
        else if (input1[i] > input2[j])
        {
            j++;
        }
        else
        {
            return make_pair(i, j);
        }
    }

    return make_pair(-1, -1);
}
} // namespace Intersection

namespace RowSort
{
// ColumnSort is described in MIT Introduction to Algorithms
// 3rd edition Chapter 8 problem 8-7.
// Sort an array of r rows and s columns such that
// 1. r must be even
// 2. s must be a divisor of r
// 3. r >= 2s^2
//
// The steps are
// 0. Given an array
//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
//                             ......
//                             ......
//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
// 1. Sort each column
// 2. Transpose the array. Turn the leftmost column into top r/s rows in order,
//    and then do the same for the rest of columns in order
//     (0,0)     (1,0)       (2,0)       ...... (s-2,0)    (s-1,0)
//     (s,0)     (s+1,0)     (s+2,0)     ...... (2s-2,0)   (2s-1,0)
//                                       ......
//     (r-s,0)   (r-s+1,0)   (r-s+2,0)   ...... (r-2,0)    (r-1,0)
//     (0,1)     (1,1)       (2,1)       ...... (s-2,1)    (s-1,1)
//     (s,1)     (s+1,1)     (s+2,1)     ...... (2s-2,1)   (2s-1,1)
//                                       ......
//     (r-s,1)   (r-s+1,1)   (r-s+2,1)   ...... (r-2,1)    (r-1,1)
//                                       ......
//                                       ......
//     (0,s-1)   (1,s-1)     (2,s-1)     ...... (s-2,s-1)  (s-1,s-1)
//     (s,s-1)   (s+1,s-1)   (s+2,s-1)   ...... (2s-2,s-1) (2s-1,s-1)
//                                       ......
//     (r-s,s-1) (r-s+1,s-1) (r-s+2,s-1) ...... (r-2,s-1)  (r-1,s-1)
// 3. Sort each column
// 4. Revert step 2
//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
//                             ......
//                             ......
//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
// 5. Sort each column
// 6. Shift leftmost column down by r/2 and into the top of its right next column.
//    Do the same for the rest of columns in order
//               (r/2,0)   (r/2,1)   (r/2,2)   ...... (r/2,s-3)   (r/2,s-2)   (r/2,s-1)
//               (r/2+1,0) (r/2+1,1) (r/2+1,2) ...... (r/2+1,s-3) (r/2+1,s-2) (r/2+1,s-1)
//               (r/2+2,0) (r/2+2,1) (r/2+2,2) ...... (r/2+2,s-3) (r/2+2,s-2) (r/2+2,s-1)
//                                             ......
//                                             ......
//               (r-1,0)   (r-1,1)   (r-1,2)   ...... (r-1,s-3)   (r-1,s-2)   (r-1,s-1)
//     (0,0)     (0,1)     (0,2)     ......           (0,s-2)     (0,s-1)
//     (1,0)     (1,1)     (1,2)     ......           (1,s-2)     (1,s-1)
//     (2,0)     (2,1)     (2,2)     ......           (2,s-2)     (2,s-1)
//                                   ......
//                                   ......
//     (r/2-2,0) (r/2-2,1) (r/2-2,2) ......           (r/2-2,s-2) (r/2-2,s-1)
//     (r/2-1,0) (r/2-1,1) (r/2-1,2) ......           (r/2-1,s-2) (r/2-1,s-1)
// 7. Sort each column
// 8. Revert step 6
//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
//                             ......
//                             ......
//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
//
// When step 8 completes, the matrix is sorted in column-major order:
// Reading down the leftmost column and continuing with the rest of columns,
// the elements are in sorted order.
//
// This implementation use a row-based variant, a.k.a. RowSort,
// to sort a two-dimensional matrix stored in an array.
// Sort an array of s rows and r columns such that
// 1. r must be even
// 2. s must be a divisor of r
// 3. r >= 2s^2
//
// The steps are
// 0. Given an array
//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
//                             ......
//                             ......
//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
// 1. Sort each row
// 2. Transpose the array. Turn the topmost row into left r/s columns in order,
//    and then do the same for the rest of rows in order
//     (0,0)   (0,s)    ...... (0,r-s)   (1,0)   (1,s)    ...... (1,r-s)   ...... (s-1,0)   (s-1,s)    ...... (s-1,r-s)
//     (0,1)   (0,s+1)  ...... (0,r-s+1) (1,1)   (1,s+1)  ...... (1,r-s+1) ...... (s-1,1)   (s-1,s+1)  ...... (s-1,r-s+1)
//     (0,2)   (0,s+2)  ...... (0,r-s+2) (1,2)   (1,s+2)  ...... (1,r-s+2) ...... (s-1,2)   (s-1,s+2)  ...... (s-1,r-s+2)
//                      ......                            ......           ......                      ......
//                      ......                            ......           ......                      ......
//     (0,s-2) (0,2s-2) ...... (0,r-2)   (1,s-2) (1,2s-2) ...... (1,r-2)   ...... (s-1,s-2) (s-1,2s-2) ...... (s-1,r-2)
//     (0,s-1) (0,2s-1) ...... (0,r-1)   (1,s-1) (1,2s-1) ...... (1,r-1)   ...... (s-1,s-1) (s-1,2s-1) ...... (s-1,r-1)
// 3. Sort each row
// 4. Revert step 2
//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
//                             ......
//                             ......
//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
// 5. Sort each row
// 6. Shift topmost row right by r/2 and into the left of its down next row.
//    Do the same for the rest of rows in order
//                                                                  (0,0)   (0,1)   (0,2)   ...... (0,r/2-2)   (0,r/2-1)
//     (0,r/2)   (0,r/2+1)   (0,r/2+2)   ...... (0,r-2)   (0,r-1)   (1,0)   (1,1)   (1,2)   ...... (1,r/2-2)   (1,r/2-1)
//     (1,r/2)   (1,r/2+1)   (1,r/2+2)   ...... (1,r-2)   (1,r-1)   (2,0)   (2,1)   (2,2)   ...... (2,r/2-2)   (2,r/2-1)
//                                       ......                                             ......
//                                       ......                                             ......
//     (s-3,r/2) (s-3,r/2+1) (s-3,r/2+2) ...... (s-3,r-2) (s-3,r-1) (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r/2-2) (s-2,r/2-1)
//     (s-2,r/2) (s-2,r/2+1) (s-2,r/2+2) ...... (s-2,r-2) (s-2,r-1) (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r/2-2) (s-1,r/2-1)
//     (s-1,r/2) (s-1,r/2+1) (s-1,r/2+2) ...... (s-1,r-2) (s-1,r-1)
// 7. Sort each row
// 8. Revert step 6
//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
//                             ......
//                             ......
//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
//
// When step 8 completes, the matrix is sorted in row-major order:
// Reading right the topmost row and continuing with the rest of rows,
// the elements are in sorted order.

template <class T>
static void check(T *input, const int length, const int columns)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive.", length));
    if (columns <= 0)
        throw invalid_argument(String::Format("columns %d is not positive.", columns));
}

// Check if each column is sorted
template <class T>
static bool IsColumnsSorted(T *input, const int length, const int columns)
{
    check(input, length, columns);
    if (length <= columns)
        return true; // Only one row

    // 0      ... c-1
    // c      ... 2c-1
    //        ...
    // (r-1)c ... rc-1
    // rc ... l-1
    int rows = length / columns;
    for (int i = 0; i < columns; i++)
    {
        int end = i + rows * columns;
        if (end >= length)
            end -= columns;
        for (int j = i; j < end; j += columns)
        {
            if (input[j] > input[j + columns])
                return false;
        }
    }

    return true;
}

// Check if each row is sorted
template <class T>
static bool IsRowsSorted(T *input, const int length, const int columns)
{
    check(input, length, columns);
    if (columns == 1)
        return true; // Only one column

    // 0      ... c-1
    // c      ... 2c-1
    //        ...
    // (r-2)c ... rc-1
    // (r-1)c ... l-1
    int rows = length / columns;
    if (length % columns > 0)
        rows++;
    int begin = 0;
    for (int i = 0; i < rows; i++)
    {
        int end = begin + columns - 1;
        if (end >= length)
            end = length - 1;
        for (int j = begin; j < end; j++)
        {
            if (input[j] > input[j + 1])
                return false;
        }

        begin += columns;
    }

    return true;
}

// Check if input is sorted in row-major order
template <class T>
static bool IsSorted(T *input, const int length, const int columns)
{
    check(input, length, columns);

    // 0      ... c-1
    // c      ... 2c-1
    //        ...
    // (r-2)c ... rc-1
    // (r-1)c ... l-1
    int rows = length / columns;
    if (length % columns > 0)
        rows++;
    int begin = 0;
    for (int i = 0; i < rows; i++)
    {
        int end = begin + columns - 1;
        if (end >= length - 1)
            end = length - 2;
        for (int j = begin; j <= end; j++)
        {
            // When j = end, j+1 is the begin of next row
            if (input[j] > input[j + 1])
                return false;
        }

        begin += columns;
    }

    return true;
}

// Sort each row
template <class T>
static void SortRows(T *input, const int length, const int columns)
{
    check(input, length, columns);

    int rows = length / columns;
    if (length % columns > 0)
        rows++;
    int begin = 0;
    for (int i = 0; i < rows; i++)
    {
        int end = begin + columns - 1;
        if (end >= length)
            end = length - 1;
        MergeSort::Sort(input, begin, end);
        begin += columns;
    }
}

// Sort a matrix so that each row is sorted and each column is sorted
template <class T>
static void Sort(T *input, const int length, const int columns)
{
    check(input, length, columns);
    if (columns % 2 != 0)
        throw invalid_argument(String::Format("columns %d is not even.", columns));
    if (length % columns > 0)
        throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));
    int rows = length / columns;
    if (columns % rows > 0)
        throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));
    if (columns < 2 * rows * rows)
        throw invalid_argument(String::Format("columns %d is less than 2 * %d * %d.", columns, rows, rows));

    SortRows(input, length, columns);
    Array::TransposeRowsToColumns<T>(input, length, columns);
    SortRows(input, length, columns);
    Array::TransposeColumnsToRows<T>(input, length, columns);
    SortRows(input, length, columns);
    Array::RotateRight<T>(input, length, columns >> 1);
    SortRows(&input[columns], length - columns, columns);
    Array::RotateLeft<T>(input, length, columns >> 1);
}

// Parallel check if each column is sorted
template <class T>
static bool ParallelIsColumnsSorted(T *input, const int length, const int columns)
{
    check(input, length, columns);
    if (length <= columns)
        return true; // Only one row

    // 0      ... c-1
    // c      ... 2c-1
    //        ...
    // (r-1)c ... rc-1
    // rc ... l-1
    int rows = length / columns;
    bool sorted = true;
    cancellation_token_source tokenSource;
    run_with_cancellation_token([&]() {
        parallel_for(int(0), columns, [&](int i) {
            int end = i + rows * columns;
            if (end >= length)
                end -= columns;
            for (int j = i; j < end; j += columns)
            {
                if (input[j] > input[j + columns])
                {
                    sorted = false;
                    tokenSource.cancel();
                }
            }
        });
    },
                                tokenSource.get_token());

    return sorted;
}

// Parallel check if each row is sorted
template <class T>
static bool ParallelIsRowsSorted(T *input, const int length, const int columns)
{
    check(input, length, columns);
    if (columns == 1)
        return true; // Only one column

    // 0      ... c-1
    // c      ... 2c-1
    //        ...
    // (r-2)c ... rc-1
    // (r-1)c ... l-1
    int rows = length / columns;
    if (length % columns > 0)
        rows++;
    bool sorted = true;
    cancellation_token_source tokenSource;
    run_with_cancellation_token([&]() {
        parallel_for(int(0), rows, [&](int i) {
            int begin = i * columns;
            int end = begin + columns - 1;
            if (end >= length)
                end = length - 1;
            for (int j = begin; j < end; j++)
            {
                if (input[j] > input[j + 1])
                {
                    sorted = false;
                    tokenSource.cancel();
                }
            }
        });
    },
                                tokenSource.get_token());

    return sorted;
}

// Parallel check if each row is sorted and if each column is sorted
template <class T>
static bool ParallelIsSorted(T *input, const int length, const int columns)
{
    check(input, length, columns);

    // 0      ... c-1
    // c      ... 2c-1
    //        ...
    // (r-2)c ... rc-1
    // (r-1)c ... l-1
    int rows = length / columns;
    if (length % columns > 0)
        rows++;
    bool sorted = true;
    cancellation_token_source tokenSource;
    run_with_cancellation_token([&]() {
        parallel_for(int(0), rows, [&](int i) {
            int begin = i * columns;
            int end = begin + columns - 1;
            if (end >= length - 1)
                end = length - 2;
            for (int j = begin; j <= end; j++)
            {
                if (input[j] > input[j + 1])
                {
                    // When j = end, j+1 is the begin of next row
                    sorted = false;
                    tokenSource.cancel();
                }
            }
        });
    },
                                tokenSource.get_token());

    return sorted;
}

// Parallel sort each row
template <class T>
static void ParallelSortRows(T *input, const int length, const int columns)
{
    check(input, length, columns);

    int rows = length / columns;
    if (length % columns > 0)
        rows++;
    parallel_for(int(0), rows, [&](int i) {
        int begin = i * columns;
        int end = begin + columns - 1;
        if (end >= length)
            end = length - 1;
        MergeSort::Sort<T>(input, begin, end);
    });
}

// Parallel sort a matrix so that each row is sorted and each column is sorted
template <class T>
static void ParallelSort(T *input, const int length, const int columns)
{
    check(input, length, columns);
    if (columns % 2 != 0)
        throw invalid_argument(String::Format("columns %d is not even.", columns));
    if (length % columns > 0)
        throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));
    int rows = length / columns;
    if (columns % rows > 0)
        throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));
    if (columns < 2 * rows * rows)
        throw invalid_argument(String::Format("columns %d is less than 2 * %d * %d.", columns, rows, rows));

    ParallelSortRows(input, length, columns);
    Array::TransposeRowsToColumns<T>(input, length, columns);
    ParallelSortRows(input, length, columns);
    Array::TransposeColumnsToRows<T>(input, length, columns);
    ParallelSortRows(input, length, columns);
    Array::RotateRight<T>(input, length, columns >> 1);
    ParallelSortRows(&input[columns], length - columns, columns);
    Array::RotateLeft<T>(input, length, columns >> 1);
}
} // namespace RowSort

namespace CountingSort
{
static void GetRange(const int *input, int length, int &minValue, int &range)
{
    if (input == nullptr || length <= 0)
    {
        range = -1;
        return;
    }

    int minIndex;
    int maxIndex;
    MinMax(input, length, minIndex, maxIndex);
    if (minIndex < 0 || maxIndex < 0 || minIndex >= length || maxIndex >= length)
    {
        range = -1;
        return;
    }

    minValue = input[minIndex];
    int maxValue = input[maxIndex];
    range = maxValue - minValue + 1;
}

// Sort input and return the result in output.
// Not in-place. Stable.
static void Sort(const int *input, int length, int *output)
{
    if (input == nullptr || length <= 0 || output == nullptr)
        return;

    int minValue;
    int range = -1;
    GetRange(input, length, minValue, range);
    if (range == -1)
        return;

    unique_ptr<int[]> count(new int[range]);
    memset(count.get(), 0, range * sizeof(int));

    for (int i = 0; i < length; i++)
    {
        int delta = input[i] - minValue;
        count[delta]++;
    }

    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = length - 1; i >= 0; i--)
    {
        int delta = input[i] - minValue;
        output[count[delta] - 1] = input[i];
        count[delta]--;
    }
}

// Sort in place
// In-place sort. Not stable.
static void Sort(int *input, int length)
{
    if (input == nullptr || length <= 0)
        return;

    int minValue;
    int range = -1;
    GetRange(input, length, minValue, range);
    if (range == -1)
        return;

    unique_ptr<int[]> count(new int[range]);
    memset(count.get(), 0, range * sizeof(int));

    for (int i = 0; i < length; i++)
    {
        int delta = input[i] - minValue;
        count[delta]++;
    }

    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    BitSet bits(length);
    for (int i = length - 1; i >= 0; i--)
    {
        if (bits.Test(i))
            continue;
        while (true)
        {
            // Use input[i] as a temporay place to store the next value to be placed.
            int delta = input[i] - minValue;
            int currentIndex = count[delta] - 1;
            count[delta]--;
            bits.Set(currentIndex);
            if (currentIndex == i)
                break;
            int nextValue = input[currentIndex];
            input[currentIndex] = input[i];
            input[i] = nextValue;
        }
    }
}
} // namespace CountingSort

namespace WordLadder
{
// Find the length of shortest transformation sequence from a start string
// to a end string, such that
// 1. only one character can be changed at each step
// 2. each intermediate word must exist in a dictionary
// Notes:
// 1. all words are in the lower case
// 2. start and end may not be in the dictionary
static int Solve(const string &start, const string &end, const unordered_set<string> &dictionary)
{
    if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0)
        return 0;
    unordered_set<string> dict;
    dict.insert(dictionary.begin(), dictionary.end());
    if (dict.find(start) == dict.end())
        dict.insert(start);
    if (dict.find(end) == dict.end())
        dict.insert(end);

    // For each word find the set of words having only one different character from it
    map<string, vector<string>> graph;
    for_each(dict.begin(), dict.end(), [&](string word) {
        graph[word] = vector<string>{};
    });

    for_each(dict.begin(), dict.end(), [&](string word) {
        int wordLen = word.length();
        for (map<string, vector<string>>::iterator it = graph.begin(); it != graph.end(); it++)
        {
            if (wordLen == it->first.length())
            {
                int diff = 0;
                for (int i = 0; i < wordLen; i++)
                {
                    if (word[i] != it->first[i])
                        diff++;
                    if (diff > 1)
                        break;
                }
                if (diff == 1)
                    it->second.push_back(word);
            }
        }
    });

    bool found = false;
    unordered_set<string> visited;
    queue<string> q[2];
    int step = 0;
    q[0].push(start);
    visited.insert(start);
    while (!q[0].empty() || !q[1].empty())
    {
        queue<string> &current = q[step & 0x1];
        queue<string> &next = q[(step + 1) & 0x1];
        while (!current.empty())
        {
            string word = current.front();
            current.pop();
            for (size_t i = 0; i < graph[word].size(); i++)
            {
                if (graph[word][i] == end)
                {
                    found = true;
                    break;
                }
                if (visited.find(graph[word][i]) == visited.end())
                {
                    visited.insert(graph[word][i]);
                    next.push(graph[word][i]);
                }
            }
            if (found)
                return step + 2;
        }
        step++;
    }
    return 0;
}

static int Solve2(const string &start, const string &end, const unordered_set<string> &dictionary)
{
    if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0)
        return 0;
    unordered_set<string> dict;
    dict.insert(dictionary.begin(), dictionary.end());

    auto diff1 = [&](const string &first, const string &second) -> bool {
        if (first.size() != second.size())
            return false;
        int diff = 0;
        for (size_t i = 0; i < first.length(); i++)
        {
            if (first[i] != second[i])
                diff++;
            if (diff > 1)
                return false;
        }
        return diff == 1;
    };

    vector<string> q[2];
    int step = 0;
    q[0].push_back(start);
    while (!q[0].empty() || !q[1].empty())
    {
        vector<string> &current = q[step & 0x1];
        vector<string> &next = q[(step + 1) & 0x1];
        while (!current.empty())
        {
            string word = current.front();
            current.erase(current.begin());
            for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++)
            {
                if (diff1(word, *it))
                {
                    if (diff1(*it, end))
                        return step + 3;
                    else
                        next.push_back(*it);
                }
            }
        }
        for_each(next.begin(), next.end(), [&](string &s) {
            dict.erase(s);
        });
        step++;
    }
    return 0;
}

static int Solve3(const string &start, const string &end, const unordered_set<string> &dictionary)
{
    if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0)
        return 0;

    unordered_set<string> visited;
    queue<string> q[2];
    int step = 0;
    q[0].push(start);
    visited.insert(start);
    while (!q[0].empty() || !q[1].empty())
    {
        queue<string> &current = q[step & 0x1];
        queue<string> &next = q[(step + 1) & 0x1];
        while (!current.empty())
        {
            string word = current.front();
            current.pop();
            int wordLen = word.size();
            string temp;
            for (int i = 0; i < wordLen; i++)
            {
                temp = word;
                for (char j = 'a'; j <= 'z'; j++)
                {
                    temp[i] = j;
                    if (temp == end)
                        return step + 2;
                    if (dictionary.find(temp) != dictionary.end() && visited.find(temp) == visited.end())
                    {
                        visited.insert(temp);
                        next.push(temp);
                    }
                }
            }
        }
        step++;
    }
    return 0;
}

// Find all shortest transformation sequences from a start string to a end string, such that
// 1. only one character can be changed at each step
// 2. each intermediate word must exist in a dictionary
// Notes:
// 1. all words are in the lower case
// 2. start and end may not be in the dictionary
static vector<vector<string>> WordLadders(const string &start, const string &end, const unordered_set<string> &dictionary)
{
    vector<vector<string>> ladders = {};
    if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0)
        return ladders;

    unordered_map<string, vector<vector<string>>> path; // Record paths ending at a word
    unordered_map<string, int> level;
    queue<string> q[2];
    int step = 0;
    bool stop = false;
    q[0].push(start);
    level[start] = step;
    path[start] = vector<vector<string>>{};
    path[start].push_back(vector<string>{start});
    while (!q[0].empty() || !q[1].empty())
    {
        queue<string> &current = q[step & 0x1];
        queue<string> &next = q[(step + 1) & 0x1];
        while (!current.empty())
        {
            string word = current.front();
            current.pop();
            string temp;
            for (size_t i = 0; i < word.size(); i++)
            {
                temp = word;
                for (char j = 'a'; j <= 'z'; j++)
                {
                    temp[i] = j;
                    if (temp == end)
                    {
                        for_each(path[word].begin(), path[word].end(), [&](vector<string> &p) {
                            vector<string> r(p);
                            r.push_back(temp);
                            ladders.push_back(r);
                        });
                        stop = true;
                    }
                    else if (dictionary.find(temp) != dictionary.end())
                    {
                        if (level.find(temp) == level.end())
                        {
                            level[temp] = step + 1;
                            next.push(temp);
                            path[temp] = vector<vector<string>>{};
                        }
                        if (level[temp] > step)
                        {
                            for_each(path[word].begin(), path[word].end(), [&](vector<string> &p) {
                                vector<string> r(p);
                                r.push_back(temp);
                                path[temp].push_back(r);
                            });
                        }
                    }
                }
            }
        }
        if (stop)
            break; // Found the shortest paths. If need to find all, then do not stop.
        step++;
    }
    return ladders;
}
} // namespace WordLadder

namespace MatchSubsequence
{
// Find all subsequences of input string that match a pattern.
// Return the total count.
// A subsequence may not be a substring (i.e., contiguous)
static int Count(const string &input, const string &pattern)
{
    if (input.length() < pattern.length() || pattern.length() == 0)
        return 0;
    if (input.length() == pattern.length())
        return input == pattern ? 1 : 0;
    int count = 0;
    for (size_t i = 0; i <= input.length() - pattern.length(); i++)
    {
        if (input[i] == pattern[0])
        {
            if (pattern.length() == 1)
                count++;
            else
                count += Count(input.substr(i + 1), pattern.substr(1));
        }
    }
    return count;
}

static int Count2(const string &input, const string &pattern)
{
    if (input.length() < pattern.length() || pattern.length() == 0)
        return 0;

    map<pair<size_t, size_t>, int> count;
    function<int(size_t, size_t)>
        search = [&](size_t i, size_t j) -> int {
        if (input.length() - i == pattern.length() - j)
            return input.substr(i) == pattern.substr(j) ? 1 : 0;
        int c = 0;
        for (size_t k = i; k <= input.length() - pattern.length() + j; k++)
        {
            if (input[k] == pattern[j])
            {
                pair<size_t, size_t> p = make_pair(k, j);
                if (count.find(p) == count.end())
                {
                    if (j == pattern.length() - 1)
                        count[p] = 1;
                    else
                        count[p] = search(k + 1, j + 1);
                }
                c += count[p];
            }
        }
        return c;
    };

    return search(0, 0);
}
} // namespace MatchSubsequence

// Given a string of length n, we want to break it at some predetermined positions.
// We can start at any one of the positions to break the string into two parts,
// and continue with each substring and the rest of positions. For each position
// there is a cost of splitting depending on the length of substring to break.
// We want to find a sequence of positions to break the string with minimum cost.
//     0    1    2    3    ......    i    ......    n-2    n-1
// p   p[0] p[1] p[2] p[3]           p[i]           p[n-2] p[n-1]
//     0 = p[0] < p[1] < p[2] < ... < p[i] < ... < p[n-2] < p[n-1] = string length
// Define c[i,j] as the cost of breaking a substring starting at position p[i]
// and ending at position p[j].
// c[i,j] = 0,     if i == j || i+1 == j    (no split between p[i] and p[j])
//          p[j] - p[i] + 1 + min {
//                  c[i,i+1] + c[i+1,j],
//                  c[i,i+2] + c[i+2,j],
//                  ......
//                  c[i,j-2] + c[j-2,j],
//                  c[i,j-1] + c[j-1,j]},    if i+1 < j
namespace BreakString
{
// cost[i,j] has two properties. The selected position to break substring from
// position i to j. The second is the cost to break substring from position i to j.
static void ComputeCostTable(int *positions, int length, Matrix<pair<int, int>> &cost)
{
    if (positions == nullptr)
        throw invalid_argument("positions is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("Invalid length %d", length));
    int rows = cost.Rows();
    if (rows != length)
        throw invalid_argument(String::Format("rows %d != length %d", rows, length));
    int cols = cost.Cols();
    if (cols != length)
        throw invalid_argument(String::Format("cols %d != length %d", cols, length));

    for (int i = 0; i < length; i++)
    {
        cost(i, i).first = i;
        cost(i, i).second = 0;
        if (i < length - 1)
        {
            cost(i, i + 1).first = i;
            cost(i, i + 1).second = 0;
        }
    }

    for (int l = 2; l < length; l++)
    {
        for (int i = 0; i < length - l; i++)
        {
            // Compute cost(i, i+l)
            int c = 0x7FFFFFFF;
            int k = i;
            for (int j = i + 1; j < i + l; j++)
            {
                int t = cost(i, j).second + cost(j, i + l).second;
                if (t < c)
                {
                    c = t;
                    k = j;
                }
            }

            cost(i, i + l).first = k;
            cost(i, i + l).second = c + positions[i + l] - positions[i];
        }
    }
}

static int ComputeBreaks(int *positions, int length, vector<int> &breaks)
{
    if (positions == nullptr)
        throw invalid_argument("positions is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("Invalid length %d", length));
    Matrix<pair<int, int>> cost(length, length);
    ComputeCostTable(positions, length, cost);

    vector<pair<int, int>> range;
    range.push_back(make_pair(0, length - 1));
    while (!range.empty())
    {
        pair<int, int> p = range.back();
        range.pop_back();

        int k = cost(p.first, p.second).first;
        breaks.push_back(positions[k]);

        if (k < p.second - 1)
        {
            range.push_back(make_pair(k, p.second));
        }

        if (p.first < k - 1)
        {
            range.push_back(make_pair(p.first, k));
        }
    }

    return cost(0, length - 1).second;
}
} // namespace BreakString

namespace MinPathSum
{
// Given a triangle, find the minimum path sum from top to bottom. Each step may move to only adjacent numbers on the row below.
// For example, given the following triangle
// [     [2],
//      [3,4],
//     [6,5,7],
//    [4,1,8,3]]
// The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
//
//          0
//         0 1
//        0 1 2
//       0 1 2 3
//      0 1 2 3 4
//        ......
// minSum[i] = e[i] + min { minSum[i-1], minSum[i] }
static int Solve(vector<vector<int>> &triangle)
{
    if (triangle.size() == 0)
        return 0;
    vector<int> sum;
    sum.push_back(triangle[0][0]);
    for (size_t i = 1; i < triangle.size(); i++)
    {
        vector<int> &row = triangle[i];
        sum.push_back(row[i] + sum[i - 1]);
        for (int j = i - 1; j > 0; j--)
            sum[j] = row[j] + min(sum[j - 1], sum[j]);
        sum[0] = row[0] + sum[0];
    }
    int min = sum[0];
    for (size_t i = 1; i < sum.size(); i++)
        if (sum[i] < min)
            min = sum[i];
    return min;
}
} // namespace MinPathSum

// Pattern can include:
// '.'	Any single character
// '*'  Zero or more occurrences of previous character
// Any other characters
// Return true if the entire input string match the pattern.
static bool IsMatch1(const char *input, const char *pattern)
{
    if (input == nullptr || pattern == nullptr)
        return false;
    while (*pattern == '*')
        pattern++;
    if (*input == '\0' && *pattern == '\0')
        return true;
    if (*pattern == '\0')
        return false;
    if (*(pattern + 1) != '*')
    {
        // input    a#######
        //          ""
        // pattern  b####
        //          a####
        //          .####
        return (*input == *pattern || *pattern == '.' && *input != '\0') && IsMatch1(input + 1, pattern + 1);
    }
    // input    a#######
    //          ""
    // pattern  b***####
    //          a***###
    //          .***###
    while (*input == *pattern || (*pattern == '.' && *input != '\0'))
    {
        // input    a#######
        // pattern  a***###
        //          .***###
        if (IsMatch1(input++, pattern + 2))
            return true;
    }
    // input    a#######
    //          ""
    // pattern  b***####
    return IsMatch1(input, pattern + 2);
}
static bool IsMatch2(const char *input, const char *pattern)
{
    if (input == nullptr || pattern == nullptr)
        return false;
    while (*pattern == '*')
        pattern++;
    while ((*input == *pattern || *pattern == '.') && *input != '\0' && *pattern != '\0' && *(pattern + 1) != '*')
    {
        // input    a#######
        // pattern  a####
        //          .####
        input++;
        pattern++;
    }
    if (*input == '\0' && *pattern == '\0')
        return true; // input and pattern match
    if (*pattern == '\0')
        return false; // input has more characters unmatched
    if (*(pattern + 1) != '*')
    {
        // input    a#######
        //          '\0'
        // pattern  b####
        return false;
    }
    // input    a#######
    //          '\0'
    // pattern  b***####
    //          a***###
    //          .***###
    // Now *(pattern+1) == '*'
    if (*input != *pattern && *pattern != '.')
    {
        // input    a#######
        //          '\0'
        // pattern  b*###
        return IsMatch2(input, pattern + 2);
    }
    // input    a#######
    //          '\0'
    // pattern  a*###
    //          .*###
    while (*input != '\0' && (*input == *pattern || *pattern == '.'))
    {
        if (IsMatch2(input, pattern + 2))
            return true;
        input++;
    }
    // input	'\0'
    // input    b#######
    // pattern  a*###
    return IsMatch2(input, pattern + 2);
}

static void LongestSubStringWithUniqueChars1(const string &input, size_t &index, size_t &length)
{
    index = 0;
    length = 0;
    bitset<256> visited;
    size_t i = 0;
    size_t j = 0;
    while (j < input.length())
    {
        if (visited[input[j]] == true)
        {
            if (j - i > length)
            {
                index = i;
                length = j - i;
            }
            while (input[i] != input[j])
            {
                visited[input[i]] = false;
                i++;
            }
            i++;
        }
        else
            visited[input[j]] = true;
        j++;
    }
    if (j - i > length)
    {
        index = i;
        length = j - i;
    }
}
static void LongestSubStringWithUniqueChars2(const string &input, size_t &index, size_t &length)
{
    index = 0;
    length = 0;
    map<char, size_t> position;
    size_t i = 0;
    size_t j = 0;
    while (j < input.length())
    {
        if (position.find(input[j]) != position.end() && position[input[j]] >= i)
        {
            if (j - i > length)
            {
                index = i;
                length = j - i;
            }
            i = position[input[j]] + 1;
        }
        position[input[j]] = j;
        j++;
    }
    if (j - i > length)
    {
        index = i;
        length = j - i;
    }
}

namespace ShortestSubStringContainingGivenChars
{
static void UpdateMap(map<char, int> &m, char c)
{
    if (m.find(c) == m.end())
        m[c] = 1;
    else
        m[c]++;
}

// check if m1 contains m2
static bool Contain(map<char, int> m1, map<char, int> m2)
{
    if (m1.size() < m2.size())
        return false;
    for (map<char, int>::iterator it = m2.begin(); it != m2.end(); it++)
    {
        if (m1.find(it->first) == m1.end())
            return false;
        if (m1[it->first] < it->second)
            return false;
    }
    return true;
}

// http://leetcode.com/2010/11/finding-minimum-window-in-s-which.html
// Find the shortest substring containing all the characters in a given set
// The given set may contain duplicate chars
static void Solve1(const string &chars, const string &input, int &index, int &length)
{
    index = -1;
    length = INT_MAX;

    map<char, int> charMap;
    for (unsigned int i = 0; i < chars.length(); i++)
    {
        UpdateMap(charMap, chars[i]);
    }

    map<char, int> count;
    int i = 0;
    int j = 0;
    while (j < (int)input.length() && count.size() < charMap.size() - 1)
    {
        if (charMap.find(input[j]) != charMap.end())
            UpdateMap(count, input[j]);
        j++;
    }
    while (j < (int)input.length())
    {
        if (charMap.find(input[j]) != charMap.end())
        {
            UpdateMap(count, input[j]);
            if (Contain(count, charMap))
            {
                while (Contain(count, charMap))
                {
                    if (count.find(input[i]) != count.end())
                        count[input[i]]--;
                    i++;
                }
                int l = j - i + 2; // j - (i-1) + 1
                if (l < length)
                {
                    index = i - 1;
                    length = l;
                }
            }
        }
        j++;
    }
}

static void Solve2(const string &chars, const string &input, int &index, int &length)
{
    index = -1;
    length = INT_MAX;

    map<char, int> charMap;
    for (unsigned int i = 0; i < chars.length(); i++)
    {
        UpdateMap(charMap, chars[i]);
    }

    for (unsigned int i = 0; i < input.length(); i++)
    {
        if (charMap.find(input[i]) != charMap.end())
        {
            map<char, int> count;
            unsigned int j = i;
            while (j < input.length())
            {
                if (charMap.find(input[j]) != charMap.end())
                {
                    UpdateMap(count, input[j]);
                    if (Contain(count, charMap))
                    {
                        int l = j - i + 1;
                        if (l < length)
                        {
                            index = i;
                            length = l;
                        }
                        break;
                    }
                }
                j++;
            }
        }
    }
}

// Assuming the given set does not contain duplicate characters
static void SolveGivenUniqueChars1(const string &chars, const string &input, int &index, int &length)
{
    index = -1;
    length = INT_MAX;
    map<char, int> count;
    int i = 0;
    char c;
    for (unsigned int j = 0; j < input.length(); j++)
    {
        c = input[j];
        if (chars.find(c) != string::npos)
        {
            if (count.find(c) == count.end())
                count[c] = 1;
            else
                count[c]++;
            if (count.size() == chars.length())
            {
                while (count.size() == chars.length())
                {
                    c = input[i];
                    if (count.find(c) != count.end())
                    {
                        count[c]--;
                        if (count[c] == 0)
                            count.erase(c);
                    }
                    i++;
                }
                int l = j - i + 2; // j - (i-1) + 1
                if (l < length)
                {
                    index = i - 1;
                    length = l;
                }
            }
        }
    }
}

// Assuming the given set does not contain duplicate characters
static void SolveGivenUniqueChars2(const string &chars, const string &input, int &index, int &length)
{
    index = -1;
    length = INT_MAX;
    queue<int> indices;
    map<char, int> found; // track found chars and their most recent indices
    for (unsigned int i = 0; i < input.length(); i++)
    {
        if (chars.find(input[i]) != string::npos)
        {
            indices.push(i);
            found[input[i]] = i; // insert or update with the latest index
            if (found.size() == chars.length())
            {
                // found all chars
                // pop old indices that are not the most recent
                while (indices.front() != found[input[indices.front()]])
                    indices.pop();
                int l = indices.back() - indices.front() + 1;
                if (l < length)
                {
                    // Update if the current one is shorter
                    index = indices.front();
                    length = l;
                }
                // erase the oldest char in order to start next search
                found.erase(input[indices.front()]);
                indices.pop();
            }
        }
    }
    if (index == -1)
        length = 0;
}
} // namespace ShortestSubStringContainingGivenChars

} // namespace Test

#endif