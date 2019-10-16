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
// Return the partion with minimum cut, i.e., the count of palindrome substrins is as less as possible.
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
// Return the partion with minimum cut, i.e., the count of palindrome substrins is as less as possible.
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

} // namespace Test

#endif