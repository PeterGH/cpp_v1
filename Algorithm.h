#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <algorithm>
#include <iostream>
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

} // namespace Test

#endif