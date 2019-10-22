#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <functional>
#include "Structure.h"

using namespace std;

namespace Test
{

template <class T>
static void ToArray(const vector<T> &v, T *a)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        a[i] = v[i];
    }
}

template <class T>
static bool Equal(const T *first, const T *second, int length)
{
    if (first == nullptr && second == nullptr)
        return true;
    if (first == nullptr || second == nullptr)
        return false;
    for (int i = 0; i < length; i++)
    {
        if (first[i] != second[i])
            return false;
    }
    return true;
}

static void Sequential(int *input, int length)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument("invalid length");
    for (int i = 0; i < length; i++)
    {
        input[i] = i;
    }
}

// Start at index i, find the next increasing range [j, k]
// Range [j, k] must be strictly increasing, i.e., no duplicates
template <class T>
static void NextIncreasingRange(const T *input, int length, int i, int &j, int &k)
{
    j = -1;
    k = -1;
    if (input == nullptr || length < 1 || i < 0 || i >= length)
        return;

    j = i;
    while (j + 1 < length && input[j] >= input[j + 1])
        j++;
    // input[j] is a local min (j might be length - 1)
    if (j == length - 1)
    {
        // Keep k = -1;
        // Also means input[i..j] is not increasing.
        return;
    }
    k = j;
    while (k + 1 < length && input[k] < input[k + 1])
        k++;
    // input[k] is a local max (k might be length - 1)
    // input[j..k] is increasing
}

// Find the indices of min and max elements.
// minIndex will be the index of the minimum value (first index if there are more than one minimum value).
// maxIndex will be the index of the maximum value (last index if there are more than one maximum value).
template <class T>
static void MinMax(const T *input, const int length, int &minIndex, int &maxIndex)
{
    minIndex = -1;
    maxIndex = -1;
    if (input == nullptr || length <= 0)
        return;

    int startIndex = 0;
    if (length % 2 == 1)
    {
        minIndex = 0;
        maxIndex = 0;
        startIndex = 1;
    }
    else
    {
        if (input[0] <= input[1])
        {
            minIndex = 0;
            maxIndex = 1;
        }
        else
        {
            minIndex = 1;
            maxIndex = 0;
        }
        startIndex = 2;
    }

    for (int i = startIndex; i < length; i += 2)
    {
        if (input[i] <= input[i + 1])
        {
            if (input[i] < input[minIndex])
                minIndex = i;
            if (input[i + 1] >= input[maxIndex])
                maxIndex = i + 1;
        }
        else
        {
            if (input[i + 1] < input[minIndex])
                minIndex = i + 1;
            if (input[i] >= input[maxIndex])
                maxIndex = i;
        }
    }
}

// Get the min index. Default it is the first if there are duplicates of min
template <class T>
static int Min(const T *input, const int length, bool first = true)
{
    if (input == nullptr || length <= 0)
        return -1;
    int m = 0;
    for (int i = 1; i < length; i++)
    {
        if (first && input[i] < input[m])
            m = i;
        if (!first && input[i] <= input[m])
            m = i;
    }
    return m;
}

// Get the max index. Default it is the first if there are duplicates of max
template <class T>
static int Max(const T *input, const int length, bool first = true)
{
    if (input == nullptr || length <= 0)
        return -1;
    int m = 0;
    for (int i = 1; i < length; i++)
    {
        if (first && input[i] > input[m])
            m = i;
        if (!first && input[i] >= input[m])
            m = i;
    }
    return m;
}

// Permute an array in place.
// The permute function takes two parameters: index of the element to permute, number of elements,
// and output the index of the new position of the element.
template <class T>
static void Permute(T *input, int length, function<int(int, int)> &permute)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive.", length));

    BitSet updated(length);

    // ------+------------+--------------
    //       j            k
    //       s            t
    for (int i = 0; i < length; i++)
    {
        if (updated.Test(i))
            continue;
        int j = i;
        T s = input[j];
        int k = permute(j, length);
        while (k != i && !updated.Test(k))
        {
            T t = input[k];
            input[k] = s;
            updated.Set(k);
            j = k;
            s = t;
            k = permute(j, length);
        }

        input[i] = s;
        updated.Set(i);
    }
}

// Permute a two dimensional matrix in place.
// The permute function takes three parameters: index of the element to
// permute, number of rows and number of columns, and output the index
// of the new position of the element.
template <class T>
static void Permute(T *input, int length, int columns, function<int(int, int, int)> &permute)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive.", length));
    if (columns <= 0)
        throw invalid_argument(String::Format("columns %d is not positive.", columns));
    if (length % columns > 0)
        throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

    function<int(int, int)> p = [&](int i, int len) -> int {
        int rows = len / columns;
        return permute(i, rows, columns);
    };

    Permute(input, length, p);
}

// Reverse elements in input[start..end]
template <class T>
static void Reverse(T *input, int start, int end)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (start < 0)
        throw invalid_argument(String::Format("start %d is invalid", start));
    if (end < 0)
        throw invalid_argument(String::Format("end %d is invalid", end));
    if (start > end)
        throw invalid_argument(String::Format("start %d is greater than end %d", start, end));
    while (start < end)
    {
        swap(input[start], input[end]);
        start++;
        end--;
    }
}

// Reverse subarray from input[i] to input[j]
template <class T>
static void Reverse(vector<T> &input, int i, int j)
{
    assert(i >= 0);
    assert(i <= j);
    assert(j < input.size());
    while (i < j)
    {
        swap(input[i], input[j]);
        i++;
        j--;
    }
}

// Swap two ranges. Expect the two ranges are not overlapping.
// If the two ranges overlap, swap whatever the values are
// in the overlapping range without any special treatment.
template <class T>
static void Swap(T *first, T *second, const int count)
{
    if (first == nullptr)
        throw invalid_argument("first is nullptr");
    if (second == nullptr)
        throw invalid_argument("second is nullptr");
    T t;
    for (int i = 0; i < count; i++)
    {
        t = first[i];
        first[i] = second[i];
        second[i] = t;
    }
}

// Rotate an input array to the left by a distance. The elements rotated
// out are shifted into the right. LSB (input[0]) is on the left side.
template <class T>
static void RotateLeft(T *input, const int length, int distance)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive", length));
    if (distance < 0)
        throw invalid_argument(String::Format("distance %d is negative", distance));
    distance = distance % length;
    if (distance == 0)
        return;
    int i = 0;
    int j = length - 1;
    int k = distance;
    // input[i..k-1] and input[k..j]
    while (i < k && k <= j)
    {
        if (k - i < j - k + 1)
        {
            // Left range is shorter. Swap it to the right, and
            // repeat with the rest on its left.
            // input[i..k-1], input[k..j-(k-i)], input[j-(k-i)+1..j]
            Swap(&input[i], &input[j - (k - i) + 1], k - i);
            j = j - (k - i);
        }
        else if (k - i > j - k + 1)
        {
            // Right range is shorter. Swap it to the left, and
            // repeat with the rest on its right.
            // input[i..i+(j-k)], input[i+(j-k)+1..k-1], input[k..j]
            Swap(&input[i], &input[k], j - k + 1);
            i = i + (j - k) + 1;
        }
        else
        {
            // Both ranges have the same length
            Swap(&input[i], &input[k], k - i);
            break;
        }
    }
}

// Rotate an input array to the left by a distance. The elements rotated
// out are shifted into the right. LSB (input[0]) is on the left side.
template <class T>
static void RotateLeft2(T *input, const int length, int distance)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive", length));
    if (distance < 0)
        throw invalid_argument(String::Format("distance %d is negative", distance));
    distance = distance % length;
    if (distance == 0)
        return;
    Reverse(input, 0, distance - 1);
    Reverse(input, distance, length - 1);
    Reverse(input, 0, length - 1);
}

// Rotate an input array to the right by a distance. The elements rotated
// out are shifted into the left. MSB (input[length-1]) is on the right side.
template <class T>
static void RotateRight(T *input, const int length, int distance)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive", length));
    if (distance < 0)
        throw invalid_argument(String::Format("distance %d is negative", distance));
    distance = distance % length;
    if (distance == 0)
        return;
    int i = 0;
    int j = length - 1;
    int k = j - distance + 1;
    // input[i..k-1] and input[k..j];
    while (i < k && k <= j)
    {
        if (k - i < j - k + 1)
        {
            // Left range is shorter. Swap it to the right, and
            // repeat with the rest on its left.
            // input[i..k-1], input[k..j-(k-i)], input[j-(k-i)+1..j]
            Swap(&input[i], &input[j - (k - i) + 1], k - i);
            j = j - (k - i);
        }
        else if (k - i > j - k + 1)
        {
            // Right range is shorter. Swap it to the left, and
            // repeat with the rest on its right.
            // input[i..i+(j-k)], input(i+(j-k)+1..k-1], input[k..j]
            Swap(&input[i], &input[k], j - k + 1);
            i = i + (j - k) + 1;
        }
        else
        {
            // Both ranges have the same length
            Swap(&input[i], &input[k], k - i);
            break;
        }
    }
}

// Rotate an input array to the right by a distance. The elements rotated
// out are shifted into the left. MSB (input[length-1]) is on the right side.
template <class T>
static void RotateRight2(T *input, const int length, int distance)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive", length));
    if (distance < 0)
        throw invalid_argument(String::Format("distance %d is negative", distance));
    distance = distance % length;
    if (distance == 0)
        return;
    Reverse(input, 0, length - distance - 1);
    Reverse(input, length - distance, length - 1);
    Reverse(input, 0, length - 1);
}

// Transpose a two dimensional matrix in place
// Given an MxN array
//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
//                             ......
//                             ......
//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
//
// Transpose
//     (0,0)   (1,0)   (2,0)   ...... (M-2,0)   (M-1,0)
//     (0,1)   (1,1)   (2,1)   ...... (M-2,1)   (M-1,1)
//     (0,2)   (1,2)   (2,2)   ...... (M-2,2)   (M-1,2)
//                             ......
//                             ......
//     (0,M-2) (1,M-2) (2,M-2) ...... (M-2,M-2) (M-1,M-2)
//     (0,M-1) (1,M-1) (2,M-1) ...... (M-2,M-1) (M-1,M-1)
//     (0,M)   (1,M)   (2,M)   ...... (M-2,M)   (M-1,M)
//     (0,M+1) (1,M+1) (2,M+1) ...... (M-2,M+1) (M-1,M+1)
//                             ......
//                             ......
//     (0,N-2) (1,N-2) (2,N-2) ...... (M-2,N-2) (M-1,N-2)
//     (0,N-1) (1,N-1) (2,N-1) ...... (M-2,N-1) (M-1,N-1)
//
// In-place matrix transposition (http://en.wikipedia.org/wiki/In-place_matrix_transposition)
// Transpose element (m,n) to (n,m) means the index i = Nm + n is mapped to j = Mn + m.
// The mapping is actually a permutation:
// P(i) = MN - 1            if i = MN - 1, or
//        Mi mod (MN - 1)   if 0 <= i < MN - 1
// The reason is
// P(i) = P(Nm + n)
//      = M(Nm + n) mod (MN - 1)
//      = MNm + Mn mod (MN - 1)
//      = (MN-1)m + m + Mn mod (MN - 1) = Mn + m
template <class T>
static void Transpose(T *input, int length, int columns)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive.", length));
    if (columns <= 0)
        throw invalid_argument(String::Format("columns %d is not positive.", columns));
    if (length % columns > 0)
        throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

    function<int(int, int, int)> permute = [=](int i, int r, int c) -> int {
        int l = r * c;
        if (i == (l - 1))
            return i;
        int j = (r * i) % (l - 1);
        return j;
    };

    Permute(input, length, columns, permute);
}

// Transpose rows to columns for a two dimensional matrix in place.
// Not change the dimensions. Given an MxN array, where N = kM
//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
//                             ......
//                             ......
//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
//
// Transpose rows to columns
//     (0,0)   (0,M)    ...... (0,(k-1)M)   (1,0)   (1,M)    ...... (1,(k-1)M)   ...... (M-1,0)   (M-1,M)    ...... (M-1,(k-1)M)
//     (0,1)   (0,M+1)  ...... (0,(k-1)M+1) (1,1)   (1,M+1)  ...... (1,(k-1)M+1) ...... (M-1,1)   (M-1,M+1)  ...... (M-1,(k-1)M+1)
//     (0,2)   (0,M+2)  ...... (0,(k-1)M+2) (1,2)   (1,M+2)  ...... (1,(k-1)M+2) ...... (M-1,2)   (M-1,M+2)  ...... (M-1,(k-1)M+2)
//                      ......                               ......              ......                      ......
//                      ......                               ......              ......                      ......
//     (0,M-2) (0,2M-2) ...... (0,kM-2)     (1,M-2) (1,2M-2) ...... (1,kM-2)     ...... (M-1,M-2) (M-1,2M-2) ...... (M-1,kM-2)
//     (0,M-1) (0,2M-1) ...... (0,kM-1)     (1,M-1) (1,2M-1) ...... (1,kM-1)     ...... (M-1,M-1) (M-1,2M-1) ...... (M-1,kM-1)
//
// Transpose element (m,n) to ((n % M), (km + n/M)) means
// the index i = Nm + n is mapped to j = (n % M)N + km + n/M
// The mapping is actually a permutation:
// 1. It is easy to see 0<= j <= MN-1
// 2. From i to j is a one-to-one mapping
//
// Given an MxN array, where M = kN
//     (0,0)   (0,1)   (0,2)   ...... (0,N-2)   (0,N-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,N-2)   (1,N-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,N-2)   (2,N-1)
//                             ......
//                             ......
//     (N-2,0) (N-2,1) (N-2,2) ...... (N-2,N-2) (N-2,N-1)
//     (N-1,0) (N-1,1) (N-1,2) ...... (N-1,N-2) (N-1,N-1)
//                             ......
//                             ......
//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,N-2) (M-2,N-1)
//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,N-2) (M-1,N-1)
//
// Transpose rows to columns
//     (0,0)     (k,0)      ...... ((N-1)k,0)
//     (0,1)     (k,1)      ...... ((N-1)k,1)
//     (0,2)     (k,2)      ...... ((N-1)k,2)
//                          ......
//     (0,N-2)   (k,N-2)    ...... ((N-1)k,N-2)
//     (0,N-1)   (k,N-1)    ...... ((N-1)k,N-1)
//     (1,0)     (k+1,0)    ...... ((N-1)k+1,0)
//     (1,1)     (k+1,1)    ...... ((N-1)k+1,1)
//     (1,2)     (k+1,2)    ...... ((N-1)k+1,2)
//                          ......
//     (1,N-2)   (k+1,N-2)  ...... ((N-1)k+1,N-2)
//     (1,N-1)   (k+1,N-1)  ...... ((N-1)k+1,N-1)
//                          ......
//                          ......
//     (k-1,0)   (2k-1,0)   ...... (kN-1,0)
//     (k-1,1)   (2k-1,1)   ...... (kN-1,1)
//     (k-1,2)   (2k-1,2)   ...... (kN-1,2)
//                          ......
//     (k-1,N-2) (2k-1,N-2) ...... (kN-1,N-2)
//     (k-1,N-1) (2k-1,N-1) ...... (kN-1,N-1)
//
// Transpose element (m,n) to ((m%k)N + n, m/k)) means
// the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
// The mapping is actually a permutation:
// 1. It is easy to see 0<= j <= MN-1
// 2. From i to j is a one-to-one mapping
template <class T>
static void TransposeRowsToColumns(T *input, int length, int columns)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive.", length));
    if (columns <= 0)
        throw invalid_argument(String::Format("columns %d is not positive.", columns));
    if (length % columns > 0)
        throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

    int rows = length / columns;

    if (columns >= rows && (columns % rows > 0))
        throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));

    if (rows >= columns && (rows % columns > 0))
        throw invalid_argument(String::Format("rows %d is not multiple of columns %d.", rows, columns));

    if (columns > rows)
    {
        // Transpose element (m,n) to ((n % M), (km + n/M)) means
        // the index i = Nm + n is mapped to j = (n % M)N + km + n/M
        function<int(int, int, int)> permute = [=](int i, int r, int c) -> int {
            int m = i / c;
            int n = i % c;
            int j = (n % r) * c + (c / r) * m + n / r;
            return j;
        };

        Permute(input, length, columns, permute);
    }
    else if (rows > columns)
    {
        // Transpose element (m,n) to ((m%k)N + n, m/k)) means
        // the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
        function<int(int, int, int)> permute = [=](int i, int r, int c) -> int {
            int m = i / c;
            int n = i % c;
            int k = r / c;
            int j = (m % k) * c * c + n * c + m / k;
            return j;
        };

        Permute(input, length, columns, permute);
    }
    else
    {
        Transpose(input, length, columns);
    }
}

// Transpose columns to rows for a two dimensional matrix in place.
// Not change the dimensions. Given an MxN array, where N = kM
//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
//                             ......
//                             ......
//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
//
// Transpose columns to rows
//     (0,0)    (1,0)    ...... (M-1,0)    (0,1)     (1,1)       ...... (M-1,1)      ...... (0,k-1)  (1,k-1)  ...... (M-1,k-1)
//     (0,k)    (1,k)    ...... (M-1,k)    (0,k+1)   (1,k+1)     ...... (M-1,k+1)    ...... (0,2k-1) (1,2k-1) ...... (M-1,2k-1)
//                       ......                                  ......              ......                   ......
//                       ......                                  ......              ......                   ......
//     (0,kM-M) (1,kM-M) ...... (M-1,kM-M) (0,kM-M+1) (1,kM-M+1) ...... (M-1,kM-M+1) ...... (0,kM-1) (1,kM-1) ...... (M-1,kM-1)
//
// Transpose element (m,n) to (n/k, (n%k)M+m) means
// the index i = Nm + n is mapped to j = (n/k)N + (n%k)M + m
// The mapping is actually a permutation:
// 1. It is easy to see 0<= j <= MN-1
// 2. From i to j is a one-to-one mapping
//
// Given an MxN array, where M = kN
//     (0,0)   (0,1)   (0,2)   ...... (0,N-2)   (0,N-1)
//     (1,0)   (1,1)   (1,2)   ...... (1,N-2)   (1,N-1)
//     (2,0)   (2,1)   (2,2)   ...... (2,N-2)   (2,N-1)
//                             ......
//                             ......
//     (N-2,0) (N-2,1) (N-2,2) ...... (N-2,N-2) (N-2,N-1)
//     (N-1,0) (N-1,1) (N-1,2) ...... (N-1,N-2) (N-1,N-1)
//                             ......
//                             ......
//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,N-2) (M-2,N-1)
//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,N-2) (M-1,N-1)
//
// Transpose columns to rows
//     (0,0)        (1,0)          (2,0)          ...... (N-2,0)    (N-1,0)
//     (N,0)        (N+1,0)        (N+2,0)        ...... (2N-2,0)   (2N-1,0)
//                                                ......
//     ((k-1)N,0)   ((k-1)N+1,0)   ((k-1)N+2,0)   ...... (kN-2,0)   (kN-1,0)
//     (0,1)        (1,1)          (2,1)          ...... (N-2,1)    (N-1,1)
//     (N,1)        (N+1,1)        (N+2,1)        ...... (2N-2,1)   (2N-1,1)
//                                                ......
//     ((k-1)N,1)   ((k-1)N+1,1)   ((k-1)N+2,1)   ...... (kN-2,1)   (kN-1,1)
//                                                ......
//                                                ......
//     (0,M-1)      (1,M-1)        (2,M-1)        ...... (N-2,M-1)  (N-1,M-1)
//     (N,M-1)      (N+1,M-1)      (N+2,M-1)      ...... (2N-2,M-1) (2N-1,M-1)
//                                                ......
//     ((k-1)N,M-1) ((k-1)N+1,M-1) ((k-1)N+2,M-1) ...... (kN-2,M-1) (kN-1,M-1)
//
// Transpose element (m,n) to (kn + m/N, m % N)) means
// the index i = Nm + n is mapped to j = (kn+m/N)N + m%N
// The mapping is actually a permutation:
// 1. It is easy to see 0<= j <= MN-1
// 2. From i to j is a one-to-one mapping
template <class T>
static void TransposeColumnsToRows(T *input, int length, int columns)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is not positive.", length));
    if (columns <= 0)
        throw invalid_argument(String::Format("columns %d is not positive.", columns));
    if (length % columns > 0)
        throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

    int rows = length / columns;

    if (columns >= rows && (columns % rows > 0))
        throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));

    if (rows >= columns && (rows % columns > 0))
        throw invalid_argument(String::Format("rows %d is not multiple of columns %d.", rows, columns));

    if (columns > rows)
    {
        // Transpose element (m,n) to (n/k, (n%k)M+m) means
        // the index i = Nm + n is mapped to j = (n/k)N + (n%k)M + m
        function<int(int, int, int)> permute = [=](int i, int r, int c) -> int {
            int m = i / c;
            int n = i % c;
            int k = c / r;
            int j = (n / k) * c + (n % k) * r + m;
            return j;
        };

        Permute(input, length, columns, permute);
    }
    else if (rows > columns)
    {
        // Transpose element (m,n) to (kn + m/N, m % N)) means
        // the index i = Nm + n is mapped to j = (kn+m/N)N + m%N
        function<int(int, int, int)> permute = [=](int i, int r, int c) -> int {
            int m = i / c;
            int n = i % c;
            int k = r / c;
            int j = (k * n + m / c) * c + m % c;
            return j;
        };

        Permute(input, length, columns, permute);
    }
    else
    {
        Transpose(input, length, columns);
    }
}
} // namespace Test
#endif