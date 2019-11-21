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

// 1. Assume the input array is not sorted.
// 2. The input array may contain duplicate elements.
// 3. The return value is the index of the first occurrence
// of the value to search in the input array if found, otherwise -1.
template <class T>
int LinearSearch(T e, const T *A, int L)
{
    if (A == nullptr || L <= 0)
        return -1;
    for (int i = 0; i < L; i++)
    {
        if (e == A[i])
            return i;
    }
    return -1;
}

// comp is a binary function returning a boolean value.
// If comp(first, second) returns true, then the first input
// should go before the second input. Default comp is std::less,
// which forms a non-decreasing sequence. Return -1 if not found.
template <class Value, class Compare = std::less<Value>>
static int BinarySearch(
    const Value &value,
    int begin,
    int end,
    function<const Value &(int)> get,
    bool first = true,
    Compare comp = std::less<Value>())
{
    while (begin <= end)
    {
        // (1) b < m < e
        // (2) b == m < e == b + 1
        // (3) b == m == e
        int middle = begin + ((end - begin) >> 1);
        const Value &middleValue = get(middle);
        if (comp(value, middleValue))
            end = middle - 1;
        else if (comp(middleValue, value))
            begin = middle + 1;
        else
        {
            if (first)
            {
                if (begin == middle)
                    return middle; // case (2) or (3)
                else
                    end = middle; // case (1)
            }
            else
            {
                if (middle == end)
                    return middle; // case (3)
                else if (begin < middle)
                    begin = middle; // case (1)
                else if (comp(value, get(end)))
                    return middle; // case (2), m is the last
                else
                    return end; // case (2), e is the last
            }
        }
    }
    return -1;
}

template <class Compare = std::less<>>
static int BinarySearch(
    const vector<int> &input,
    int value,
    size_t begin,
    size_t end,
    bool first = true,
    Compare comp = std::less<>())
{
    return BinarySearch(
        value,
        (int)begin,
        (int)end,
        [&](int i) -> const int & { return input[i]; },
        first,
        comp);
}

template <class Compare = std::less<>>
static int BinarySearch(
    const vector<vector<int>> &input,
    size_t col,
    int value,
    size_t begin,
    size_t end,
    bool first = true,
    Compare comp = std::less<>())
{
    return BinarySearch(
        value,
        (int)begin,
        (int)end,
        [&](int i) -> const int & { return input[i][col]; },
        first,
        comp);
}

// 1. Assume the input array is already sorted.
//    We do not want to apply sorting in the implementation of
//    binary search to enforce the assumption. Instead, sorting
//    should be the responsibility of the caller of binary search.
// 2. The input array may contain duplicate elements.
// 3. The return value is the index of the first occurrence of
//    the value to search in the sorted input array if found, otherwise -1.
template <class T>
int BinarySearch(T e, const T *A, int L)
{
    if (A == nullptr || L <= 0)
        return -1;
    int low = 0;
    int high = L - 1;
    while (low <= high)
    {
        int middle = (low + high) >> 1;
        if (e < A[middle])
            high = middle - 1;
        else if (e > A[middle])
            low = middle + 1;
        else
        {
            // The input array may contain duplicate elements.
            // The index found so far may not be the first occurrence of the value to search.
            // So search forward to find the first occurrence.
            while (middle > 0 && e == A[middle - 1])
                middle--;
            return middle;
        }
    }
    return -1;
}

// 1. Assume the input array is already sorted.
//    We do not want to apply sorting in the implementation of binary search to enforce the assumption.
//    Instead, sorting should be the responsibility of the caller of binary search.
// 2. The input array may contain duplicate elements.
// 3. The return value is the index of the first occurrence of the value to search in the sorted input array if found, otherwise -1.
template <class T>
int BinarySearchRecursively(T e, const T *A, int l, int h)
{
    if (A == nullptr || l < 0 || h < 0 || h < l)
        return -1;
    int middle = (l + h) >> 1;
    if (e < A[middle])
        return BinarySearchRecursively(e, A, l, middle - 1);
    else if (e > A[middle])
        return BinarySearchRecursively(e, A, middle + 1, h);
    else
    {
        // The input array may contain duplicate elements.
        // The index found so far may not be the first occurrence of the value to search.
        // So search forward to find the first occurrence.
        while (middle > 0 && e == A[middle - 1])
        {
            middle--;
        }
        return middle;
    }
}

// comp is a binary function returning a boolean value.
// If comp(first, second) returns true, then the first input
// should go before the second input. Default comp is std::less,
// which forms a non-decreasing sequence. Return i in [begin, end]
// if should insert value to position i. Return end + 1 if should
// append value.
template <class Value, class Compare = std::less<Value>>
static size_t FindInsertPoint(
    const Value &value,
    int begin,
    int end,
    function<const Value &(int)> get,
    bool first = true,
    Compare comp = std::less<Value>())
{
    while (begin <= end)
    {
        // (1) b < m < e
        // (2) b == m < e == b + 1
        // (3) b == m == e
        int middle = begin + ((end - begin) >> 1);
        int middleValue = get(middle);
        if (comp(value, middleValue))
        {
            if (begin == middle)
                return middle; // case (2) or (3)
            else
                end = middle - 1; // case (1)
        }
        else if (comp(middleValue, value))
        {
            if (middle == end)
                return end + 1; // case (3)
            else
                begin = middle + 1; // case (1) or (2)
        }
        else
        {
            if (first)
            {
                if (begin == middle)
                    return middle; // case (2) or (3)
                else
                    end = middle; // case (1)
            }
            else
            {
                if (middle == end)
                    return middle; // case (3)
                else if (begin < middle)
                    begin = middle; // case (1)
                else if (comp(value, get(end)))
                    return middle; // case (2), m is the last
                else
                    return end; // case (2), e is the last
            }
        }
    }
    throw runtime_error("Unreachable code");
}

template <class Compare = std::less<>>
static size_t FindInsertPoint(
    vector<int> &input,
    int value,
    size_t begin,
    size_t end,
    bool first = true,
    Compare comp = std::less<>())
{
    return FindInsertPoint(
        value,
        (int)begin,
        (int)end,
        [&](int i) -> int { return input[i]; },
        first,
        comp);
}

template <class Compare = std::less<>>
static size_t FindInsertPoint(
    vector<vector<int>> &input,
    size_t col,
    int value,
    size_t begin,
    size_t end,
    bool first = true,
    Compare comp = std::less<>())
{
    return FindInsertPoint(
        value,
        (int)begin,
        (int)end,
        [&](int i) -> int { return input[i][col]; },
        first,
        comp);
}

// Assume array A[0..(L-1)] is already sorted and it can contain duplicate elements.
// Return -1 if e < A[0]
// Return (L-1) if A[L-1] <= e
// Return i if A[i] <= e < A[i+1].
template <class T>
int PositionToInsert(T e, const T *A, int L)
{
    if (A == nullptr || L <= 0)
        return -2;
    int low = 0;
    int high = L - 1;
    // The loop ensures A[0..(low-1)] < e < A[(high+1)..(L-1)]
    while (low <= high)
    {
        // low <= middle <= high.
        // The case middle == high could happen when low == high.
        int middle = (low + high) >> 1;
        if (e < A[middle])
        {
            if (middle == low)
                return low - 1;
            else
                high = middle - 1;
        }
        else if (e > A[middle])
        {
            if (middle == high)
                return high;
            else
                low = middle + 1;
        }
        else
        {
            // The input array may contain duplicate elements.
            // The index found so far may not be the last occurrence of the value to search.
            // So search backward to find the last occurrence.
            while (middle < L - 1 && e == A[middle + 1])
            {
                middle++;
            }
            return middle;
        }
    }
    // We should not hit this line.
    throw runtime_error("Cannot find position");
}

namespace BinarySearch
{
// Find the median of a sorted array.
// If the array length is odd, then the median is unique.
// If the array length is even, then return the lower median.
template <class T>
static T FindMedian(const T *input, int length)
{
    if (input == nullptr)
        throw invalid_argument("input is a nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));

    // If l = 2m
    // +----------------+  +------------------+
    // 0               m-1 m                 2m-1
    // The median index is m-1 = (l - 1) / 2, rounding to the lower boundary
    //
    // If l = 2m-1
    // +----------------+   +   +------------------+
    // 0               m-2 m-1  m                 2m-2
    // The median index is m-1 = (l - 1) / 2

    int medianIndex = (length - 1) >> 1;
    return input[medianIndex];
}

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
    // m + n = medianIndex - 1
    // Median = S[m] if L[n] < S[m] <= L[n+1], i.e. S[m] is the lower median and L[n+1] is the higher median
    //          L[n] if S[m] < L[n] <= S[m+1], i.e. L[m] is the lower median and S[n+1] is the higher median
    //          S[m] if S[m] == L[n], i.e. S[m] or L[n] is the lower median and min(S[m+1], L[n+1]) is the higher median
    //          max(S[m-1], L[n+1]) if S[m] > L[n+1]
    //          max(S[m+1], L[n-1]) if L[n] > S[m+1]

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

// Find the k-th order statistic (smallest element) from two sorted arrays.
// k = 1, 2, ...
template <class T>
static T FindKthOrder(int k, const T *input1, int length1, const T *input2, int length2)
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
            // 0								      k-1       l-1 0                                      s-1
            return longArray[k - 1];
        }
        else
        {
            // +-------------------------------------------------+  +--------+------------------------------+
            // 0								                l-1 0      k-l-1                           s-1
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
    // m + n = k - 2
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
static T FindKthOrder2(int k, const T *input1, int length1, const T *input2, int length2)
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

// Find all pairs of elements each of which is summed up to a given value
// Return the indices using a vector
// The elements of input will be rearranged so the indices returned are not the original ones
template <class T>
static void FindPairsBySum(T *input, int length, const T sum, vector<pair<int, int>> &indices)
{
    if (input == nullptr)
        throw invalid_argument("input is a nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));

    if (length == 1)
        return;

    T half = sum >> 1;

    // input may contain positive and negative values

    int shortRangeBegin;
    int shortRangeEnd;
    int longRangeBegin;
    int longRangeEnd;

    if ((sum & 0x1) == 0)
    {
        //
        // sum is even
        // +--------------------------+---------------------+------------------------------+
        // 0                          i1                    i2                          length-1
        //           < sum/2                  = sum/2                > sum/2

        // Partition input so that input[0..i1] <= half - 1 < input[i1+1..length-1]
        int i1 = Partition::PartitionArrayByValue(input, 0, length - 1, half - 1);
        if (i1 == length - 1)
        {
            // All elements are less than sum/2 - 1, no matter whether sum is positive or negative.
            return;
        }

        // Partition input once more so that input[i1+1..i2] = half < input[i2+1..length-1]
        int i2 = Partition::PartitionArrayByValue(input, i1 + 1, length - 1, half);
        if (i2 == -1)
        {
            // All elements are greater than sum/2, no matter whether sum is positive or negative.
            return;
        }

        // Now input[i1+1..i2] == sum/2
        for (int i = i1 + 1; i < i2; i++)
        {
            for (int j = i + 1; j <= i2; j++)
            {
                indices.push_back(make_pair(i, j));
            }
        }

        if (i1 == -1 || i2 == length - 1)
        {
            return;
        }

        if (i1 + 1 >= length - 1 - i2)
        {
            shortRangeBegin = i2 + 1;
            shortRangeEnd = length - 1;
            longRangeBegin = 0;
            longRangeEnd = i1;
        }
        else
        {
            shortRangeBegin = 0;
            shortRangeEnd = i1;
            longRangeBegin = i2 + 1;
            longRangeEnd = length - 1;
        }
    }
    else
    {
        //
        // sum is odd
        // +-------------------------------------+-----------------------------------------+
        // 0                                     i1                                     length-1
        //                 <= sum/2                             >= sum/2 + 1

        // Partition input so that input[0..i1] <= half < input[i1+1..length-1]
        int i1 = Partition::PartitionArrayByValue(input, 0, length - 1, half);

        if (i1 == -1)
        {
            // All elements are greater than sum/2, no matter whether sum is positive or negative.
            return;
        }

        if (i1 == length - 1)
        {
            // All elements are less than or equal to sum/2, no matter whether sum is positive or negative.
            return;
        }

        if (i1 + 1 >= length - 1 - i1)
        {
            shortRangeBegin = i1 + 1;
            shortRangeEnd = length - 1;
            longRangeBegin = 0;
            longRangeEnd = i1;
        }
        else
        {
            shortRangeBegin = 0;
            shortRangeEnd = i1;
            longRangeBegin = i1 + 1;
            longRangeEnd = length - 1;
        }
    }

    Sort::Merge::Sort<T>(input, shortRangeBegin, shortRangeEnd);

    for (int i = longRangeBegin; i <= longRangeEnd; i++)
    {
        T v = sum - input[i];
        int j = Search::BinarySearch<T>(v, &input[shortRangeBegin], shortRangeEnd - shortRangeBegin + 1, true);
        if (j == -1)
        {
            // No element == sum - input[i]
            continue;
        }

        j = shortRangeBegin + j;

        do
        {
            indices.push_back(make_pair(i, j));
            j++;
        } while (j <= shortRangeEnd && input[j] == v);
    }
}

// Find all pairs of elements each of which is summed up to a given value
// Return the indices using a vector
// The elements of input will be rearranged so the indices returned are not the original ones
template <class T>
static void FindPairsBySum2(T *input, int length, const T sum, vector<pair<int, int>> &indices)
{
    if (input == nullptr)
        throw invalid_argument("input is a nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));

    if (length == 1)
        return;

    Sort::Merge::Sort<T>(input, length);

    for (int i = 0; i < length - 1; i++)
    {
        T v = sum - input[i];
        int j = Search::BinarySearch<T>(v, &input[i + 1], length - 1 - i, true);
        if (j == -1)
        {
            // No element == sum - input[i]
            continue;
        }

        j = i + 1 + j;

        do
        {
            indices.push_back(make_pair(i, j));
            j++;
        } while (j < length && input[j] == v);
    }
}

// http://leetcode.com/2010/03/here-is-phone-screening-question-from.html
// Find the first common element of two sorted arrays
// Return a pair of indices of found element. If not found, then return a pair (-1, -1)
template <class T>
static pair<int, int> FindIntersection(const T *input1, int length1, const T *input2, int length2)
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
        int j = Search::BinarySearch<T>(shortArray[i], longArray, longLength);
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
static pair<int, int> FindIntersection2(const T *input1, int length1, const T *input2, int length2)
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
} // namespace BinarySearch

// A sorted array is rotated. Find the index of the minimal
// element, i.e., the shift distance.
// Assume no duplicates in the array.
static size_t FindShiftPoint(const vector<int> &input)
{
    // Check if no shift
    if (*input.begin() < *(input.end() - 1))
        return 0;
    // Now the shift > 0
    int b = 0;
    int e = input.size() - 1;
    while (b <= e)
    {
        int m = b + ((e - b) >> 1);
        if (input[b] < input[m])
            b = m;
        else if (input[b] > input[m])
            e = m;
        else
            return b == e ? b : e;
    }
    throw runtime_error("Unreachable code");
}

namespace Search
{
// Find a subarray of contiguous elements whose sum is maximized
// If array contains both positive and negative numbers, return the maximum subarray
// If array contains positive numbers, return entire array A
// If array contains non-positive numbers, return the maximum number
// Parameter sum is the summation of the returned subarray
// Parameters start and end are the start and end indices of the returned subarray
template <class T>
static void MaxSum(const T *input, int length, int &start, int &end, T &sum)
{
    start = -1;
    end = -1;
    sum = INT_MIN;

    if (input == nullptr || length <= 0)
        return;

    // Track the last maximum sum so far
    start = 0;
    end = 0;
    sum = 0;

    // Track the current streak
    int l = 0;   // Beginning
    T c = 0;     // Cumulative sum up to current element
    int max = 0; // The index of the maximum element seen so far

    for (int i = 0; i < length; i++)
    {
        c += input[i];

        if (c > sum)
        {
            // Current element is positive and the current sum is larger than the last one.
            // Update the last seen maximum sum
            start = l;
            end = i;
            sum = c;
        }
        else if (c <= 0)
        {
            // Current element is negative and everything cancel out
            // Reset and start from the next element
            l = i + 1;
            c = 0;
        }

        // Record the max element so far
        if (input[i] >= input[max])
            max = i;
    }

    if (sum <= 0)
    {
        // All elements are zero or negative
        // Return the maximum element
        start = max;
        end = max;
        sum = input[max];
    }
}

template <class T>
static void MaxSum2(const T *input, int length, int &start, int &end, T &sum)
{
    start = -1;
    end = -1;
    sum = INT_MIN;

    if (input == nullptr || length <= 0)
        return;

    int minIndex = -1;
    int minSum = 0; // sum[0..minIndex]
    int s = 0;      // sum[0..i]
    for (int i = 0; i < length; i++)
    {
        s += input[i];
        int d = s - minSum;
        if (d >= sum)
        {
            start = minIndex + 1;
            if (d != sum || input[i] != 0 || sum == 0)
                end = i;
            sum = d;
        }
        if (s <= minSum)
        {
            minSum = s;
            minIndex = i;
        }
    }
}

} // namespace Search

// This is similar to standard c++ function partial_sum in <numeric>
static vector<int> PartialSum(const vector<int> &input)
{
    vector<int> output;
    int sum = 0;
    for (unsigned int i = 0; i < input.size(); i++)
    {
        sum += input[i];
        output.push_back(sum);
    }

    return output;
}

// For each input[i] compute the sum of range elements before input[i], inclusively.
static vector<int> PartialSum(const vector<int> &input, unsigned int range)
{
    range = range > input.size() ? input.size() : range;
    vector<int> output(input);
    for (int i = 1; i < (int)range; i++)
    {
        for (int j = (int)input.size() - 1; j >= i; j--)
        {
            output[j] += input[j - i];
        }
    }

    return output;
}
static vector<int> PartialSum2(const vector<int> &input, unsigned int range)
{
    range = range > input.size() ? input.size() : range;
    vector<int> output;
    int sum = 0;
    for (unsigned int i = 0; i < input.size(); i++)
    {
        sum += input[i];
        if (i >= range)
        {
            sum -= input[i - range];
        }

        output.push_back(sum);
    }

    return output;
}
static void PartialSum3(vector<int> &input, unsigned int range)
{
    range = range > input.size() ? input.size() : range;

    // sum A[n-k .. n-1]
    int sum = 0;
    for (int i = input.size() - 1; i >= (int)(input.size() - range); i--)
    {
        sum += input[i];
    }

    int last = 0;
    for (int i = input.size() - range - 1; i >= 0; i--)
    {
        last = sum;
        sum -= input[i + range];
        input[i + range] = last;
        sum += input[i];
    }

    // Now sum = A[0 .. k-1]

    for (int i = range - 1; i >= 0; i--)
    {
        last = sum;
        sum -= input[i];
        input[i] = last;
    }
}

// comp is a binary function returning a boolean value.
// If comp(first, second) returns true, then the first
// input should go before the second input. Default comp
// is std::less, which forms a non-decreasing sequence.
template <class Compare = std::less<>>
static void MergeSort(vector<vector<int>> &input, size_t col, Compare comp = std::less<>())
{
    function<void(size_t, size_t, size_t)> merge =
        [&](size_t head1, size_t head2, size_t tail2) {
            // merge input[head1..(head2 - 1)] with input[head2..tail2]
            while (head1 < head2 && head2 <= tail2)
            {
                if (comp(input[head2][col], input[head1][col]))
                {
                    // input[head1][col] > input[head2][col]
                    int t = input[head2][col];
                    for (size_t i = head2; i > head1; i--)
                    {
                        input[i][col] = input[i - 1][col];
                    }
                    input[head1][col] = t;
                    head2++;
                }
                head1++;
            }
        };

    function<void(size_t, size_t)> sort =
        [&](size_t head, size_t tail) {
            if (head >= tail)
                return;
            // midlle is the medium or higher medium
            size_t middle = head + ((tail - head + 1) >> 1);
            sort(head, middle - 1);
            sort(middle, tail);
            merge(head, middle, tail);
        };

    sort(0, input.size() - 1);
}

namespace Count
{
// An inversion is a pair {input[i], input[j]} such that input[i] > input[j] when i < j.
// We can extend the concept to two sub arrays of input, and the set of inversions
// contains every inversion whose elements each falls into different sub arrays, e.g.,
// input[i] is in the first sub array while input[j] is in the second.
// Sorting the two sub arrays separately does not change the count of inversions
// between the two sub arrays.
// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
// count inversions between input[head..(middle-1)] and input[middle..tail] by merging
// them into a sorted array input[head..tail].
template <class T>
static int Inversions(T *input, size_t length)
{
    if (input == nullptr || length <= 1)
        return 0;

    // Count inversions between a[h..(m-1)] and a[m..t], assuming both subarrays are sorted
    function<int(T *, int, int, int)> merge = [&](T *a, int h, int m, int t) -> int {
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
} // namespace Count

namespace InsertionSort
{
// Insertion sort is in-place, stable.
template <class T>
static void Sort(T *A, int L)
{
    if (A == nullptr || L <= 0)
        return;
    // Cannot compute the length of A by sizeof(A) / sizeof(A[0])
    // Have to use an additional parameter L
    for (int i = 1; i < L; i++)
    {
        // Record the current value to insert into A[0..(i-1)]
        T key = A[i];
        // Shift any values in A[0..(i-1)] greater than the current value,
        // so that the right position for the current value is vacant.
        int j = i - 1;
        // Note the comparison is strict,
        // so the multiple instances of the same value preserve their
        // orignial orders, i.e., the sorting is stable.
        while (j >= 0 && A[j] > key)
        {
            // Right shift A[j] to A[j+1],
            // so that A[j+1] is vacant for insertion
            A[j + 1] = A[j];
            j--;
        }
        // Insert the current value
        A[j + 1] = key;
    }
}

// Recursively sort A[0..(L-1)] by insertion
// Use binary search to find the position to insert an element
template <class T>
static void RecursiveSort(T *A, int L)
{
    // Invalid input
    if (A == nullptr || L <= 0)
        return;
    // Only one element. no need to recurse
    if (L == 1)
        return;
    // Recursively sort A[0..(L-2)]
    RecursiveSort(A, L - 1);
    // Record the current value to insert into A[0..(L-2)]
    T key = A[L - 1];
    // Find the position after which the current value should be inserted
    // -1 <= i <= (L-2)
    int i = BinarySearch<T>::FindPositionToInsert(key, A, L - 1);
    // Shift A[(i+1)..(L-2)] so that the position (i+1) for the current value is vacant.
    for (int j = L - 2; j > i; j--)
    {
        A[j + 1] = A[j];
    }
    // Insert the current value
    A[i + 1] = key;
}
} // namespace InsertionSort

// minIndex will be the index of the minimum value (first index if there are more than on minimum value
// maxIndex will be the index of the maximum value (last index if there are more than on maximum value
template <class T>
void GetMinMax<T>(const T *input, int length, int &minIndex, int &maxIndex)
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
    Array::MinMax(input, length, minIndex, maxIndex);
    if (minIndex < 0 || maxIndex < 0 || minIndex >= length || maxIndex >= length)
    {
        range = -1;
        return;
    }

    minValue = input[minIndex];
    int maxValue = input[maxIndex];
    range = maxValue - minValue + 1;
}

// Sort input and return the result in output
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

class FiniteAutomationWithWildChar
{
public:
    FiniteAutomationWithWildChar(char *pattern, int length)
    {
        if (pattern == nullptr)
            return;
        if (length <= 0)
            return;

        int i = 0;
        for (int j = 0; j < length; j++)
        {
            if (pattern[j] != FiniteAutomationWithWildChar::WildChar)
            {
                if (j > 0 && pattern[j - 1] == FiniteAutomationWithWildChar::WildChar)
                {
                    i = j;
                }

                if (j == length - 1)
                {
                    this->patterns.push_back(unique_ptr<FiniteAutomation>(new FiniteAutomation(&pattern[i], j - i + 1)));
                }
            }
            else
            {
                if (j > 0 && pattern[j - 1] != FiniteAutomationWithWildChar::WildChar)
                {
                    this->patterns.push_back(unique_ptr<FiniteAutomation>(new FiniteAutomation(&pattern[i], j - i)));
                }
            }
        }
    }

    ~FiniteAutomationWithWildChar(void) {}
    void Print(void)
    {
        for_each(this->patterns.begin(), this->patterns.end(), [&](unique_ptr<FiniteAutomation> &it) {
            it->Print();
        });
    }

    multimap<int, int> SearchString(char *input, int length)
    {
        multimap<int, int> indices;

        vector<unique_ptr<FiniteAutomation>>::iterator it = this->patterns.begin();

        vector<int> found = (*it)->SearchString(input, length);
        int patternLength = (*it)->PatternLength();
        vector<unique_ptr<FiniteAutomation>>::iterator next = it;
        next++;
        if (next == this->patterns.end())
        {
            for_each(found.begin(), found.end(), [&](int p) {
                indices.insert(pair<int, int>(p, (p + patternLength - 1)));
            });
        }
        else
        {
            for_each(found.begin(), found.end(), [&](int p) {
                SearchString(next, input, p + patternLength, length - p - patternLength, p, indices);
            });
        }

        return indices;
    }

private:
    void SearchString(const vector<unique_ptr<FiniteAutomation>>::iterator &it, char *input, int start, int length, int first, multimap<int, int> &indices)
    {
        vector<int> found = (*it)->SearchString(&input[start], length);
        int patternLength = (*it)->PatternLength();
        vector<unique_ptr<FiniteAutomation>>::iterator next = it;
        next++;
        if (next == this->patterns.end())
        {
            for_each(found.begin(), found.end(), [&](int p) {
                indices.insert(pair<int, int>(first, (start + p + patternLength - 1)));
            });
        }
        else
        {
            for_each(found.begin(), found.end(), [&](int p) {
                SearchString(next, input, start + p + patternLength, length - p - patternLength, first, indices);
            });
        }
    }
    static const char WildChar = '*';
    vector<unique_ptr<FiniteAutomation>> patterns;
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
// Refer to leetcode "Minimum Window Substring"

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

// http://leetcode.com/2010/11/microsoft-string-replacement-problem.html
// Replace a pattern with a shorter string in place.
// Continous occurrences of the pattern should be replaced with one shorter string.
static void ReplaceWithShorterString(char *input, const char *pattern, const char *shorter)
{
    if (input == nullptr || pattern == nullptr || shorter == nullptr || *input == '\0' || *pattern == '\0' || *shorter == '\0')
        return;
    char *i = input; // Next insert position
    char *j = input; // Next check position
    const char *s = shorter;
    const char *p = pattern;
    while (*j != '\0')
    {
        bool found = false;
        while (*j == *p)
        {
            char *k = j;
            while (*k != '\0' && *p != '\0' && *k == *p)
            {
                // Do not use *k++ == *p++ in the while condition statement,
                // because k and p will advance even if *k and *p are different.
                k++;
                p++;
            }
            if (*p == '\0')
            {
                // Found one pattern, skip it and
                // check for next continous pattern
                found = true;
                j = k;
                p = pattern;
            }
            else
            {
                // Input is done or not match
                p = pattern;
                break;
            }
        }
        if (found)
        {
            while (*s != '\0')
                *i++ = *s++;
            s = shorter;
        }
        if (*j != '\0')
        {
            // j may reach the end if the input ends with the pattern
            *i++ = *j++;
        }
    }
    *i = '\0';
}

// An input string may contains leading and ending spaces, and
// may contain contiguous spaces in the middle. Remove the leading
// and ending spaces, and nomalize each group of contiguous spaces
// in the middle into one space.
static void RemoveExtraSpaces(char *input)
{
    if (input == nullptr)
        return;
    char *i = input - 1; // Track the end of the last word seen so far
    char *j = input;     // Track the next char in input
    while (*j != '\0')
    {
        while (*j == ' ')
            j++;
        if (*j == '\0')
            break;
        if (i + 1 != input)
        {
            i++;
            *i = ' ';
        }
        while (*j != ' ' && *j != '\0')
        {
            i++;
            if (i < j)
                *i = *j;
            j++;
        }
    }
    i++;
    *i = '\0';
}

// input is a sentence of words separated by spaces.
// There can be multiple spaces between two words.
// Reverse the order of words, and condense multiple spaces between
// two words into one.
static void ReverseWords(string &input)
{
    size_t len = input.length();
    size_t i = 0;
    while (i < len && input[i] == ' ')
        i++;
    if (i == len)
    {
        input.clear();
        return;
    }
    while (i < len)
    {
        size_t j = input.find_first_of(" ", i);
        if (j == string::npos)
            j = len;
        input.insert(len, input, i, j - i);
        input.insert(len, 1, ' ');
        while (j < len && input[j] == ' ')
            j++;
        i = j;
    }
    input = input.substr(i + 1);
}
// input is a sentence of words separated by spaces.
// There can be multiple spaces between two words.
// Reverse the order of words, and condense multiple spaces between
// two words into one.
static void ReverseWords(char *input)
{
    if (input == nullptr)
        return;
    RemoveExtraSpaces(input);
    auto reverse = [&](char *s, char *t) {
        while (s < t)
        {
            char v = *s;
            *s++ = *t;
            *t-- = v;
        }
    };
    char *s = input;
    char *t = s;
    while (*s != '\0')
    {
        if (*s == ' ')
            s++;
        t = s;
        while (*t != '\0' && *t != ' ')
            t++;
        t--;
        reverse(s, t);
        s = ++t;
    }
    reverse(input, --s);
}

// Return a pointer to the first occurrence of input2 in input1, or nullptr
static const char *StrStr1(const char *input1, const char *input2)
{
    if (input1 == nullptr || input2 == nullptr)
        return nullptr;
    if (*input2 == '\0')
        return input1;
    const char *q = input1;
    const char *p = input2;
    while (*(q + 1) != '\0' && *(p + 1) != '\0')
    {
        q++;
        p++;
    }
    if (*(q + 1) == '\0' && *(p + 1) != '\0')
    {
        return nullptr; // input2 is longer than input1
    }
    // now input1 is not shorter than input2
    // set p to the beginning of input1
    p = input1;
    // Hop p and q at same step until q reaches the end of input1
    while (*q != '\0')
    {
        if (*p == *input2)
        {
            const char *r = p;
            const char *s = input2;
            while (*s != '\0' && *r == *s)
            {
                r++;
                s++;
            }
            if (*s == '\0')
                return p;
        }
        p++;
        q++;
    }
    return nullptr;
}
// Return a pointer to the first occurrence of input2 in input1, or nullptr
static const char *StrStr2(const char *input1, const char *input2)
{
    if (input1 == nullptr || input2 == nullptr)
        return nullptr;
    const char *p = input1;
    while (*p != '\0')
    {
        if (*p == *input2)
        {
            const char *r = p;
            const char *s = input2;
            while (*r != '\0' && *s != '\0' && *r == *s)
            {
                r++;
                s++;
            }
            if (*s == '\0')
                return p;
        }
        p++;
    }
    return *input2 == '\0' ? input1 : nullptr;
}

namespace BreakWords
{
// leetcode "Word Break"
static bool StartWith(const string &s1, const string &s2)
{
    if (s1.length() < s2.length())
        return false;
    for (size_t i = 0; i < s2.length(); i++)
    {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

// Given a input string, break it by inserting spaces so that each word
// is in a given dictionary. Return all possible sentences by breaking the string.
static vector<string> Solve1(const string &input, unordered_set<string> &dictionary)
{
    function<void(const string &, unordered_set<string> &, const string &, vector<string> &)>
        breakWord = [&](
                        const string &s,
                        unordered_set<string> &dict,
                        const string &sentence,
                        vector<string> &results) {
            size_t len = s.length();
            for_each(dict.begin(), dict.end(), [&](string w) {
                size_t wlen = w.length();
                if (StartWith(s, w))
                {
                    string sen(sentence);
                    if (sen.length() > 0)
                        sen.append(1, ' ');
                    sen.append(w);
                    if (len == wlen)
                        results.push_back(sen);
                    else
                        breakWord(s.substr(wlen), dict, sen, results);
                }
            });
        };
    vector<string> sentences;
    breakWord(input, dictionary, string(), sentences);
    return sentences;
}

// Given a input string, break it by inserting spaces so that each word
// is in a given dictionary. Return all possible sentences by breaking the string.
static vector<string> Solve2(const string &input, unordered_set<string> &dictionary)
{
    function<void(const string &, size_t, unordered_set<string> &, map<size_t, vector<string>> &)>
        breakWord = [&](
                        const string &s,
                        size_t index,
                        unordered_set<string> &dict,
                        map<size_t, vector<string>> &results) {
            if (results.find(index) == results.end())
                results[index] = vector<string>{};
            size_t len = s.length() - index;
            for_each(dict.begin(), dict.end(), [&](string w) {
                size_t wlen = w.length();
                if (StartWith(s.substr(index), w))
                {
                    size_t wi = index + wlen;
                    if (wi == s.length())
                        results[index].push_back(w);
                    else
                    {
                        if (results.find(wi) == results.end())
                            breakWord(s, wi, dict, results);
                        for_each(results[wi].begin(), results[wi].end(), [&](string r) {
                            string rs(w);
                            rs.append(1, ' ');
                            rs.append(r);
                            results[index].push_back(rs);
                        });
                    }
                }
            });
        };
    map<size_t, vector<string>> sentences;
    breakWord(input, 0, dictionary, sentences);
    return sentences[0];
}

static bool Solvable(const string &input, unordered_set<string> &dictionary)
{
    function<void(const string &, size_t, unordered_set<string> &, map<size_t, bool> &)>
        breakWord = [&](
                        const string &s,
                        size_t index,
                        unordered_set<string> &dict,
                        map<size_t, bool> &results) {
            if (results.find(index) == results.end())
                results[index] = false;
            size_t len = s.length() - index;
            for_each(dict.begin(), dict.end(), [&](string w) {
                size_t wlen = w.length();
                if (StartWith(s.substr(index), w))
                {
                    size_t wi = index + wlen;
                    if (wi == s.length())
                    {
                        results[index] = true;
                        return;
                    }
                    else
                    {
                        if (results.find(wi) == results.end())
                            breakWord(s, wi, dict, results);
                        if (results[wi])
                        {
                            results[index] = true;
                            return;
                        }
                    }
                }
            });
        };
    map<size_t, bool> sentences;
    breakWord(input, 0, dictionary, sentences);
    return sentences[0];
}
} // namespace BreakWords

// Find the elements forming the longest contiguous sequence.
// Given [100, 4, 200, 1, 3, 2], The longest consecutive elements sequence is [1, 2, 3, 4].
// Return: first = 1, length = 4.
static void LongestConsecutiveSequence1(const vector<int> &input, int &first, size_t &length)
{
    if (input.size() == 0)
    {
        length = 0;
        return;
    }
    first = input[0];
    length = 1;
    // Given a open range (begin, end), track the begin and end using two hash tables.
    unordered_map<int, int> end;   // (begin, end)
    unordered_map<int, int> begin; // (end, begin)
    for_each(input.begin(), input.end(), [&](int i) {
        // i must fall into one of cases:
        // 1. i begins one range and ends another range.
        // 2. i begins one range or ends one range.
        // 3. i is inside one range.
        // 4. i is outside of any range.
        bool iBegin = end.find(i) != end.end();   // (i, end[i])
        bool iEnd = begin.find(i) != begin.end(); // (begin[i], i)
        if (iEnd && iBegin)
        {
            // merge (begin[i], i) with (i, end[i])
            if (end[i] - begin[i] - 1 > length)
            {
                length = end[i] - begin[i] - 1;
                first = begin[i] + 1;
            }
            end[begin[i]] = end[i];
            begin[end[i]] = begin[i];
            end.erase(i);
            begin.erase(i);
        }
        else if (iBegin)
        {
            // expand (i, end[i]) to (i-1, end[i])
            if (end[i] - i > length)
            {
                length = end[i] - i;
                first = i;
            }
            // if (i-1, end[i-1]) exists, then should not change it,
            // because (i, end[i]) must be inside (i-1, end[i-1]).
            if (end.find(i - 1) == end.end())
            {
                end[i - 1] = end[i];
                begin[end[i]] = i - 1;
                end.erase(i);
            }
        }
        else if (iEnd)
        {
            // expand (begin[i], i) to (begin[i], i+1)
            if (i - begin[i] > length)
            {
                length = i - begin[i];
                first = begin[i] + 1;
            }
            // if (begin[i+1], i+1) exists, then should not change it,
            // because (begin[i], i) must be inside (begin[i+1], i+1).
            if (begin.find(i + 1) == begin.end())
            {
                begin[i + 1] = begin[i];
                end[begin[i]] = i + 1;
                begin.erase(i);
            }
        }
        else
        {
            // add new range (i-1, i+1) and (i+1, i-1)
            // the new range may already be covered in existing range, e.g.
            // { 0, 1, 2, 1}, when the second 1 occurrs, a new range (0,2) is added,
            // but the first three numbers already generate range (-1, 3).
            if (1 > length)
            {
                length = 1;
                first = i;
            }
            if (end.find(i - 1) == end.end() && begin.find(i + 1) == begin.end())
            {
                end[i - 1] = i + 1;
                begin[i + 1] = i - 1;
            }
        }
    });
}
static void LongestConsecutiveSequence2(vector<int> &input, int &first, size_t &length)
{
    if (input.size() == 0)
    {
        length = 0;
        return;
    }
    first = input[0];
    length = 1;
    sort(input.begin(), input.end());
    int f = input[0];
    int l = 1;
    for (size_t i = 1; i < input.size(); i++)
    {
        if (input[i] == input[i - 1])
            continue;
        else if (input[i] == input[i - 1] + 1)
            l++;
        else
        { // input[i] > input[i - 1] + 1
            if (l > length)
            {
                first = f;
                length = l;
            }
            f = input[i];
            l = 1;
        }
    }
    if (l > length)
    {
        first = f;
        length = l;
    }
}

// Get a random permutation in-place
template <class T>
static void RandomPermutation(vector<T> &input)
{
    int len = (int)input.size() - 1;
    for (int i = len; i >= 0; i--)
    {
        // The rand function returns a pseudorandom integer
        // in the range 0 (inclusive) to RAND_MAX (32767).
        // We need r in [0, i]
        int r = rand() % (i + 1);
        swap(input[i], input[i - r]);
    }
}

// The set {1, 2, 3, ..., n} contains a total of n! unique
// permutations. By listing and labeling all of the permutations
// in order, We get the following sequence (ie, for n = 3):
// 1. "123"
// 2. "132"
// 3. "213"
// 4. "231"
// 5. "312"
// 6. "321"
// Given n and k, return the k-th permutation sequence.
// Note: Given n will be between 1 and 9 inclusive.
static string KthPermutation(int n, int k)
{
    assert(n > 0);
    assert(n < 10);
    if (n <= 0 || k <= 0)
        return string();

    int i = 1; // Count number of digits to permute
    int m = 1; // Count number of permutations of i digits, i.e. i!

    while (m < k && i < n)
    {
        i++;
        m *= i;
    }

    if (m < k)
        return string(); // k > n!

    // Now m = i!, and (i-1)! < k <= i!

    // 1 2 3 ...... n-i n-i+1 n-i+2 ...... n-1 n
    // ~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~
    //     not permute         permute i digits

    string output;

    // append {1, 2, 3, ..., n-i}
    for (int j = 1; j <= n - i; j++)
    {
        output.append(1, '0' + j);
    }

    // Permute the last i digits
    vector<int> permute;

    // Initialize with {n-i+1, ..., n}
    for (int j = n - i + 1; j <= n; j++)
    {
        permute.push_back(j);
    }

    while (i > 0)
    {
        // For each loop, the variables are defined as:
        //   i, number of digits to permute
        //   m, number of permutations of i digits
        //   k, index (1-based) of target in m permutations

        /*
			if (i == 1) {
			// k = 1 since k <= m = i! = 1
			output.append(1, '0' + permute[permute.size() - 1]);
			break;
			} else if (i == 2) {
			if (k == 1) {
			output.append(1, '0' + permute[permute.size() - 2]);
			output.append(1, '0' + permute[permute.size() - 1]);
			} else { // k = 2
			output.append(1, '0' + permute[permute.size() - 1]);
			output.append(1, '0' + permute[permute.size() - 2]);
			}
			break;
			}
			*/

        // Permute 1 2 3 4 5 ...... i-1 i, will get i ranges
        // determined by the first digit
        //   1 ......
        //   1 ......
        //   2 ......
        //   2 ......
        //   ......
        //   ......
        //   i-1 ......
        //   i-1 ......
        //   i ......
        //   i ......

        m = m / i; // Count permutations per range

        int j = (k - 1) / m + 1; // Get the range index (1-based)
                                 // which k falls into

        // 1 2 3 4 5 ... j-1 j   j+1 ... i-1 i
        // j 1 2 3 4 5 ...   j-1 j+1 ... i-1 i
        int t = permute[j - 1];
        permute.erase(permute.begin() + j - 1);
        output.append(1, '0' + t);

        i--;                   // Move on to the rest i - 1 digits
        k = ((k - 1) % m) + 1; // Get the index in the j-th range
    }

    return output;
}

class Permutation
{

private:
    // Keep the permutation state
    MRInteger *_counter;
    template <class T>
    static void Swap(T *buffer, unsigned int position1, unsigned int position2)
    {
        if (position1 != position2)
        {
            T t = buffer[position1];
            buffer[position1] = buffer[position2];
            buffer[position2] = t;
        }
    }

public:
    Permutation(unsigned int length)
    {
        std::unique_ptr<unsigned int[]> bases(new unsigned int[length]);
        for (unsigned int i = 0; i < length; i++)
        {
            bases[i] = i + 1;
        }

        _counter = new MRInteger(bases.get(), length);
    }

    ~Permutation(void)
    {
        delete _counter;
    }

    // Permutation the buffer.
    template <class T>
    void Next(T *buffer, int length)
    {
        int len = min(length, (int)_counter->Length());
        for (int i = len - 1; i >= 0; i--)
        {
            Swap(buffer, i, i - (*_counter)[i]);
        }

        // Prepare for the next permutation
        (*_counter)++;
    }

    template <class T>
    void Next(T *input, T *output, int length)
    {
        memcpy(output, input, length * sizeof(T));
        Next(output, length);
    }

    template <class T>
    static void Random(T *buffer, int length)
    {
        for (int i = length - 1; i >= 0; i--)
        {
            // The rand function returns a pseudorandom integer
            // in the range 0 (inclusive) to RAND_MAX (32767).
            // We need r in [0, i]
            int r = Random::Next(i);
            Swap(buffer, i, i - r);
        }
    }

    template <class T>
    static void Random(T *input, T *output, int length)
    {
        memcpy(output, input, length * sizeof(T));
        Random(output, length);
    }

    // Current counter value at position index
    const unsigned int operator[](unsigned int index) const { return (*_counter)[index]; }
    // maximum number of permutations
    const unsigned long Max(void) const { return _counter->Max(); }

    // Given a collection of numbers, return all possible permutations. For example,
    // [1,2,3] have the following permutations:
    // [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
    template <class T>
    static vector<vector<T>> All(vector<T> &input)
    {
        if (input.size() == 0)
            return vector<vector<T>>{};

        // Compute all permutations starting at index i
        function<void(vector<T> &, size_t, vector<vector<T>> &)>
            permute = [&](vector<T> &n, size_t i, vector<vector<T>> &o) {
                if (i == n.size() - 1)
                {
                    o.push_back(n);
                    return;
                }
                for (size_t j = i; j < n.size(); j++)
                {
                    vector<T> m(n);
                    if (j != i)
                    {
                        // Should just swap m[i] and m[j]
                        // But we erase and insert, which effectively push m[i] one more positin to the right.
                        // This way keeps the lexicographical order
                        T t = m[j];
                        m.erase(m.begin() + j);
                        m.insert(m.begin() + i, t);
                    }
                    permute(m, i + 1, o);
                }
            };

        vector<vector<T>> output;
        permute(input, 0, output);
        return output;
    }

    // Given a collection of numbers that might contain duplicates,
    // return all possible unique permutations. For example,
    // [1,1,2] have the following unique permutations:
    // [1,1,2], [1,2,1], and [2,1,1].
    template <class T>
    static vector<vector<T>> Unique(vector<T> &input)
    {
        if (input.size() == 0)
            return vector<vector<T>>{};

        function<void(vector<T> &, size_t, vector<vector<T>> &)>
            permute = [&](vector<T> &n, size_t i, vector<vector<T>> &o) {
                if (i == n.size() - 1)
                {
                    o.push_back(n);
                    return;
                }
                unordered_set<T> swapped;
                swapped.insert(n[i]);
                for (size_t j = i; j < n.size(); j++)
                {
                    if (j != i && swapped.find(n[j]) != swapped.end())
                    {
                        continue;
                    }
                    swapped.insert(n[j]);
                    vector<T> m(n);
                    if (j != i)
                    {
                        T t = m[j];
                        m.erase(m.begin() + j);
                        m.insert(m.begin() + i, t);
                    }
                    permute(m, i + 1, o);
                }
            };

        vector<vector<T>> output;
        permute(input, 0, output);
        return output;
    }

    // The set {1, 2, 3, ..., n} contains a total of n! unique permutations.
    // By listing and labeling all of the permutations in order,
    // We get the following sequence (ie, for n = 3):
    // 1. "123"
    // 2. "132"
    // 3. "213"
    // 4. "231"
    // 5. "312"
    // 6. "321"
    // Given n and k, return the k-th permutation sequence.
    // Note: Given n will be between 1 and 9 inclusive.
    static string GetPermutation(int n, int k)
    {
        if (n <= 0 || k <= 0)
            return string();

        int i = 1; // Count number of digits to permute
        int m = 1; // Count number of permutations of i digits, i.e. i!

        while (m < k && i < n)
        {
            i++;
            m *= i;
        }

        if (m < k)
            return string(); // k > n!

        // Now m = i!, and (i-1)! < k <= i!

        // 1 2 3 ...... n-i n-i+1 n-i+2 ...... n-1 n
        // ~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~
        //     not permute         permute i digits

        string output;

        // append {1, 2, 3, ..., n-i}
        for (int j = 1; j <= n - i; j++)
        {
            output.append(1, '0' + j);
        }

        // Permute the last i digits
        vector<int> permute;

        // Initialize with {n-i+1, ..., n}
        for (int j = n - i + 1; j <= n; j++)
        {
            permute.push_back(j);
        }

        while (i > 0)
        {
            // For each loop, the variables are defined as:
            //   i, number of digits to permute
            //   m, number of permutations of i digits
            //   k, index (1-based) of target in m permutations

            if (i == 1)
            {
                // k = 1 since k <= m = i! = 1
                output.append(1, '0' + permute[permute.size() - 1]);
                break;
            }
            else if (i == 2)
            {
                if (k == 1)
                {
                    output.append(1, '0' + permute[permute.size() - 2]);
                    output.append(1, '0' + permute[permute.size() - 1]);
                }
                else
                { // k = 2
                    output.append(1, '0' + permute[permute.size() - 1]);
                    output.append(1, '0' + permute[permute.size() - 2]);
                }
                break;
            }

            // Permute 1 2 3 4 5 ...... i-1 i, will get i ranges determined by the first digit
            //   1 ......
            //   1 ......
            //   2 ......
            //   2 ......
            //   ......
            //   ......
            //   i-1 ......
            //   i-1 ......
            //   i ......
            //   i ......

            m = m / i; // Count permutations per range

            int j = (k - 1) / m + 1; // Get the range index (1-based) which k falls into

            // 1 2 3 4 5 ... j-1 j   j+1 ... i-1 i
            // j 1 2 3 4 5 ...   j-1 j+1 ... i-1 i
            int t = permute[j - 1];
            permute.erase(permute.begin() + j - 1);
            output.append(1, '0' + t);

            i--;                   // Move on to the rest i - 1 digits
            k = ((k - 1) % m) + 1; // Get the index in the j-th range
        }

        return output;
    }
};

namespace PowerSet
{
// The powerset of any set S is the set of all subsets of S, including the empty set and S itself.

template <class T>
static vector<vector<T>> ComputeRecursively(typename vector<T>::iterator &begin, typename vector<T>::iterator &end)
{
    if (begin == end)
    {
        // Create an empty element
        vector<T> empty;
        // Note the return vector contains one element, which is an empty vector.
        return vector<vector<T>>(1, empty);
    }

    T first = *begin;

    begin++;
    // Compute the powerset using the elements excluding the first one
    vector<vector<T>> s = ComputeRecursively(begin, end);

    vector<vector<T>> ps(s.begin(), s.end());

    for_each(s.begin(), s.end(), [&](vector<T> &v) -> void {
        v.push_back(first);
        ps.push_back(v);
    });

    return ps;
}

template <class T>
static vector<vector<T>> Compute(vector<T> &set)
{
    return ComputeRecursively(set.begin(), set.end());
}
} // namespace PowerSet

// Partition input into two ranges input[begin..i] and input[(i+1)..end], such that
// transform(input[begin..i]) < value <= transform(input[(i+1)..end]).
// Invariant: given j, divide the input into three ranges input[begin..i],
// input[(i+1)..(j-1)] and input[j..end] using value,
// such that transform(input[begin..i]) < value <= transform(input[(i+1)..(j-1)]).
// Return the index i+1
// If all elements are less than value, then return index end+1
// If all elements are greater than or equal to value, then return begin
template <class T, class C, class Compare = std::less<C>>
static size_t PartitionByValue(
    vector<T> &input,
    const C &value,
    size_t begin,
    size_t end,
    Compare comp = std::less<C>(),
    function<C(T)> transform = [&](T v) -> C { return v; })
{
    size_t i = begin;
    for (size_t j = begin; j <= end; j++)
    {
        if (comp(transform(input[j]), value))
        {
            if (i++ != j)
                swap(input[i - 1], input[j]);
        }
    }
    return i;
}

// Partition input into two ranges input[low..i] and input[(i+1)..high],
// such that transform(input[low..i]) <= transform(value) < transform(input[(i+1)..high]).
// Invariant: given j, divide the input into three ranges input[low..i],
// input[(i+1)..(j-1)] and input[j..high] using value, such that
// transform(input[low..i]) <= transform(value) < transform(input[(i+1)..(j-1)]).
// Return the index i, i.e. the last element less than or equal to value
// If all elements are less than value, then return index high
// If all elements are greater than value, then return low-1
template <class T, class C>
static int PartitionByValue(
    vector<T> &input,
    int low,
    int high,
    const T &value,
    function<C(T)> transform = [&](T v) -> C { return v; })
{
    assert(low >= 0);
    assert(high < input.size());
    assert(low <= high);
    int i = low - 1;
    C v = transform(value);
    for (int j = low; j <= high; j++)
    {
        if (transform(input[j]) <= v)
        {
            // The check can be <.
            // The difference is:
            // 1. <= incurs more swaps, but it is stable because all elements equal to value
            //    are still in their original order. The return value is the last index of
            //    elements less than or equal to value.
            // 2. < incurs less swaps, but it is unstable. The return value is the last
            //    index of elements less than value.
            i++;
            if (i != j)
                swap(input[i], input[j]);
        }
    }
    // Now input[low..i] <= value < input[(i+1)..high]
    // Note not necessarily input[i] is the maximum in input[low..i],
    // i.e., it may not be true input[i] == value
    return i;
}

template <class T>
static int PartitionByValue(vector<T> &input, int low, int high, const T &value)
{
    return PartitionByValue<T, T>(input, low, high, value);
}

// Randomly select an element to partition the input.
// Return the new index of selected element
template <class T, class C>
static int PartitionRandomly(
    vector<T> &input,
    int low,
    int high,
    function<C(T)> transform = [&](T v) -> C { return v; })
{
    assert(low >= 0);
    assert(high < input.size());
    assert(low <= high);
    int i = low + rand() % (high - low + 1);
    // move element input[i] to input[high], so on return the return index
    // points to the element
    swap(input[i], input[high]);
    return PartitionByValue<T, C>(input, low, high, input[high], transform);
}

template <class T>
static int PartitionRandomly(vector<T> &input, int low, int high)
{
    return PartitionRandomly<T, T>(input, low, high);
}

// Reorder input[low..high] such that it is partioned by the i-th order element,
// i.e., input[low..(low+i-1)] <= input[low+i] <= input[low+i+1..high]
// The order is zero-based, i.e., 0 <= i <= high - low
// Return the i-th order element
template <class T, class C>
static T &PartitionByOrder(
    vector<T> &input,
    int low,
    int high,
    int i,
    function<C(T)> transform = [&](T v) -> C { return v; })
{
    assert(low >= 0);
    assert(high < input.size());
    assert(low <= high);
    assert(i <= high - low);
    if (low == high)
        return input[low];
    int m = PartitionRandomly(input, low, high, transform);
    int k = m - low;
    if (i == k)
    {
        // low ......... m ......... high
        // 0   ......... k
        // 0   ......... i
        return input[m];
    }
    else if (i < k)
    {
        // low ............ m ...... high
        // 0   ............ k
        // 0   ...... i
        return PartitionByOrder(input, low, m - 1, i, transform);
    }
    else
    {
        // low ...... m ............ high
        // 0   ...... k
        // 0   ............ i
        return PartitionByOrder(input, m + 1, high, i - k - 1, transform);
    }
}

template <class T>
static T &PartitionByOrder(vector<T> &input, int low, int high, int i)
{
    return PartitionByOrder<T, T>(input, low, high, i);
}

template <class T>
static void QuickSort(vector<T> &input)
{
    int size = (int)input.size();
    if (size <= 1)
        return;

    function<void(int, int)>
        sort = [&](int low, int high) {
            // Use input[high] as the gate, so it will be moved to input[middle]
            int middle = PartitionByValue<T, T>(input, low, high, input[high]);
            // Ignore input[middle] in following sort
            if (low < middle)
                sort(low, middle - 1);
            if (middle < high)
                sort(middle + 1, high);
        };

    sort(0, size - 1);
}

template <class T>
static void QuickSortInParallel(vector<T> &input)
{
    int size = (int)input.size();
    if (size <= 1)
        return;

    function<void(int, int)>
        sort = [&](int low, int high) {
            // Use input[high] as the gate, so it will be moved to input[middle]
            int middle = PartitionByValue<T, T>(input, low, high, input[high]);
            // Ignore input[middle] in following sort
            parallel_invoke(
                [&, low, middle] { if (low < middle) sort(low, middle - 1); },
                [&, middle, high] { if (middle < high) sort(middle + 1, high); });
        };

    sort(0, size - 1);
}

template <class T>
static void QuickSortRandomly(vector<T> &input)
{
    int size = (int)input.size();
    if (size <= 1)
        return;

    function<void(int, int)>
        sort = [&](int low, int high) {
            int middle = PartitionRandomly<T, T>(input, low, high);
            // Ignore input[middle] in following sort, because
            // it is guaranteed input[middle] is the maximum in input[low..middle],
            // and the minimum in input[middle..high]
            if (low < middle)
                sort(low, middle - 1);
            if (middle < high)
                sort(middle + 1, high);
        };

    sort(0, size - 1);
}

template <class T>
static void RadixSort(vector<vector<T>> &input)
{
    if (input.size() == 0)
        return;
    if (input[0].size() == 0)
        return;

    function<function<bool(const vector<T> &, const vector<T> &)>(size_t)>
        compare = [&](size_t radix) {
            function<bool(const vector<T> &, const vector<T> &)>
                c = [=](const vector<T> &left, const vector<T> &right) {
                    return left[radix] < right[radix];
                };

            return c;
        };

    size_t len = input[0].size();
    for (size_t i = 0; i < len; i++)
    {
        function<bool(const vector<T> &, const vector<T> &)> c = compare(i);
        stable_sort(input.begin(), input.end(), c);
    }
}

template <class T>
static void InsertSort(
    vector<T> &input,
    function<bool(const T &, const T &)> greater = [&](const T &x, const T &y) -> bool { return x > y; })
{
    for (int i = 1; i < (int)input.size(); i++)
    {
        // Record the current key value to insert into input[0..(i-1)]
        T key = input[i];
        int j = i - 1;
        // Shift any values in input[0..(i-1)] greater than the current key to the right,
        // so that the insert position for the current key is vacant.
        // Note the default greater is strict,
        // so the multiple instances of the same value preserve their
        // orignial orders, i.e., the sorting is stable.
        while (j >= 0 && greater(input[j], key))
        {
            input[j + 1] = input[j];
            j--;
        }
        input[j + 1] = key;
    }
}

// Recursively sort input[0..(length-1)] by insertion
// Use binary search to find the position to insert an element
template <class T>
static void InsertSortRecursively(vector<T> &input, size_t length)
{
    if (input.size() <= 1 || length <= 1)
        return;

    // Recursively sort input[0..(length-2)]
    InsertSortRecursively(input, length - 1);

    // Record the current value to insert into input[0..(length-2)]
    T key = input[length - 1];

    // Find the last position after which the current value should be inserted.
    // -1 <= i <= (length-2)
    int i = PositionToInsert(key, input, 0, (int)length - 2, false);

    // Shift input[(i+1)..(length-2)] so that the position (i+1) for the current value is vacant.
    for (int j = (int)length - 2; j > i; j--)
    {
        input[j + 1] = input[j];
    }

    // Insert the current value
    input[i + 1] = key;
}

template <class T>
static void SelectSort(
    vector<T> &input,
    function<bool(const T &, const T &)> greater = [&](const T &x, const T &y) -> bool { return x > y; })
{
    if (input.size() <= 1)
        return;
    for (size_t i = 0; i < input.size() - 1; i++)
    {
        size_t min = i;
        for (size_t j = i + 1; j < input.size(); j++)
        {
            if (greater(input[min], input[j]))
            {
                min = j;
            }
        }
        swap(input[i], input[min]);
    }
}

// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
// rearrange elements every step so that input[head..tail] is sorted.
// In-place and stable.
template <class T>
static void Merge(vector<T> &input, int head, int middle, int tail, int step = 1)
{
    if (input.size() <= 1 || head < 0 || middle <= 0 || tail < middle || tail <= head || step <= 0)
        return;
    // head and middle point to the heads of two sub sorted arrays.
    while (head < middle && middle <= tail)
    {
        if (input[head] <= input[middle])
        {
            head += step;
        }
        else
        {
            T t = input[middle];
            // Shift input[head..(middle-step)] to input[(head+step)..middle]
            for (int i = middle; i > head; i -= step)
            {
                input[i] = input[i - step];
            }
            input[head] = t;
            // Move to the next pair of elements
            head += step;
            middle += step;
        }
    }
}

template <class T>
static void MergeSort(vector<T> &input, int head, int tail, int step = 1)
{
    if (input.size() <= 1 || head < 0 || tail < 0 || tail < head || step <= 0)
        return;
    if (head < tail)
    {
        int middle = head + (((tail - head) / step) >> 1) * step + step;
        parallel_invoke(
            [&input, head, middle, step] { MergeSort(input, head, middle - step, step); },
            [&input, middle, tail, step] { MergeSort(input, middle, tail, step); });
        Merge(input, head, middle, tail, step);
    }
}

template <class T>
static void MergeSort(vector<T> &input, int step = 1)
{
    MergeSort(input, 0, (int)input.size() - 1, step);
}

// A comparator betweeb two Element<T> instances
template <class T>
struct Greater
    : public binary_function<
          const pair<vector<T>, size_t> &,
          const pair<vector<T>, size_t> &,
          bool>
{
    bool operator()(const pair<vector<T>, size_t> &left, const pair<vector<T>, size_t> &right) const
    {
        return left.first[left.second] > right.first[right.second];
    }
};

// Implementation of merge-sort multiple sorted arrays
template <class T>
void MergeSort(vector<vector<T>> &inputs, vector<T> &output)
{
    if (inputs.size() == 0)
        return;

    // A minimum heap
    Heap<pair<vector<T>, size_t>, Greater<T>> heap((unsigned long)inputs.size());

    for (size_t i = 0; i < inputs.size(); i++)
    {
        if (inputs[i].size() > 0)
        {
            // Initialize the heap with the first element in each sorted array
            heap.Push(make_pair(inputs[i], 0));
        }
    }

    while (heap.Size() > 0)
    {
        // Extract the minimum element from the heap
        pair<vector<T>, size_t> min = heap.Pop();

        // append the minum element into the output vector
        output.push_back(min.first[min.second]);

        // Move to the next element in the same array
        min.second++;

        if (min.second < min.first.size())
        {
            // The array still has elements.
            // Push the next element into the heap.
            heap.Push(min);
        }
    }
}

namespace Heap
{
// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
// The assumption is the subtrees rooted at i are already heapified.
template <class T>
static void HeapifyElement(T *input, unsigned int i, unsigned int length)
{
    if (i >= length)
        return;
    unsigned int max = i;
    unsigned int l = Math::Tree::Left(i);
    if (l < length && input[l] > input[max])
    {
        max = l;
    }

    unsigned int r = Math::Tree::Right(i);
    if (r < length && input[r] > input[max])
    {
        max = r;
    }

    if (max != i)
    {
        Array::Swap(input, i, max);
        HeapifyElement(input, max, length);
    }
}
// Construct the array into a max heap from bottom up
template <class T>
static void Heapify(T *input, unsigned int length)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));

    unsigned int height = Math::Tree::Height(length);

    // The elements at bottom are indexed in [2^(height - 1) - 1, 2^height - 2]
    // We only need to heapify elements above them
    for (long i = ((1 << (height - 1)) - 2); i >= 0; i--)
    {
        HeapifyElement(input, (unsigned int)i, length);
    }
}

template <class T>
static void ParallelHeapify(T *input, unsigned int length)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));

    unsigned height = Math::Tree::Height(length);

    for (long long h = (height - 1); h > 0; h--)
    {
        // For h, the index is in [((1 << (h-1)) - 1), ((1 << h) - 2)]
        parallel_for(
            unsigned int((1 << (h - 1)) - 1),
            unsigned int((1 << h) - 1),
            [&](unsigned int i) { HeapifyElement(input, (unsigned int)i, length); });
    }
}

template <class T>
static void Sort(T *input, unsigned int length)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));

    // Make a heap
    Heapify(input, length);

    // Sort
    for (long long i = length - 1; i >= 0; i--)
    {
        // Swap the current maximum value, which is at position 0, to position i.
        // The range [i, length - 1] is sorted.
        Array::Swap(input, 0, (unsigned int)i);
        // Rearrange [0, i - 1] so that it is a heap
        HeapifyElement(input, 0, (unsigned int)i);
    }
}

// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
// The assumption is the subtrees rooted at i are already heapified.
template <class T>
static void HeapifyElement(T *input, unsigned int i, unsigned int length, unsigned int d)
{
    if (i >= length)
        return;
    unsigned int max = i;

    for (unsigned int j = 0; j < d; j++)
    {
        unsigned int c = Math::Tree::Child(i, j, d);
        if (c < length && input[c] > input[max])
        {
            max = c;
        }
    }

    if (max != i)
    {
        Array::Swap(input, i, max);
        HeapifyElement(input, max, length, d);
    }
}

// Construct the array into a max d-ary heap from bottom up
template <class T>
static void Heapify(T *input, unsigned int length, unsigned int d)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));
    if (d <= 1)
        throw invalid_argument(String::Format("d %d is invalid", d));

    unsigned int height = Math::Tree::Height(length, d);
    long long index = ((long long)pow(d, height - 1) - 1) / (d - 1) - 1;
    for (long long i = index; i >= 0; i--)
    {
        HeapifyElement(input, (unsigned int)i, length, d);
    }
}

template <class T>
static void ParallelHeapify(T *input, unsigned int length, unsigned int d)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));
    if (d <= 1)
        throw invalid_argument(String::Format("d %d is invalid", d));

    unsigned int height = Math::Tree::Height(length, d);

    for (long long h = height - 1; h > 0; h--)
    {
        // For h, the index is in [(d ^ (h - 1) - 1) / (d - 1), (d^h - 1) / (d - 1) - 1]
        parallel_for(
            unsigned int((pow(d, h - 1) - 1) / (d - 1)),
            unsigned int((pow(d, h) - 1) / (d - 1)),
            [&](unsigned int i) { HeapifyElement(input, (unsigned int)i, length, d); });
    }
}

template <class T>
static void Sort(T *input, unsigned int length, unsigned int d)
{
    if (input == nullptr)
        throw invalid_argument("input is nullptr");
    if (length <= 0)
        throw invalid_argument(String::Format("length %d is invalid", length));
    if (d <= 1)
        throw invalid_argument(String::Format("d %d is invalid", d));

    // Make A a heap
    Heapify(input, length, d);

    // Sort
    for (long i = length - 1; i >= 0; i--)
    {
        // Swap the current maximum value, which is at position 0, to position i.
        // The range [i, length - 1] is sorted.
        Array::Swap(input, 0, (unsigned int)i);
        // Rearrange [0, i - 1] so that it is a heap
        HeapifyElement(input, 0, (unsigned int)i, d);
    }
}
} // namespace Heap

// HeapSort use a max heap

// Rearrange [begin, end] so that it is a heap.
// The assumption is the subtrees rooted at begin are already heapified.
// Just need to push down begin if necessary
template <class T>
static void HeapifyElement(vector<T> &input, size_t begin, size_t end)
{
    assert(input.size() > 0);
    assert(begin < input.size());
    assert(end < input.size());

    while (begin < end)
    {
        size_t max = begin;
        size_t l = (begin << 1) + 1;
        if (l <= end && input[l] > input[max])
            max = l;

        size_t r = (begin << 1) + 2;
        if (r <= end && input[r] > input[max])
            max = r;

        if (max == begin)
            break;

        swap(input[begin], input[max]);
        begin = max;
    }
}

// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
// The assumption is the subtrees rooted at i are already heapified.
template <class T>
static void HeapifyElement(vector<T> &input, size_t begin, size_t end, size_t d)
{
    assert(input.size() > 0);
    assert(begin < input.size());
    assert(end < input.size());
    assert(d >= 2);

    while (begin < end)
    {
        size_t max = begin;

        for (size_t j = 0; j < d; j++)
        {
            size_t c = begin * d + j + 1;
            if (c <= end && input[c] > input[max])
                max = c;
        }

        if (max == begin)
            break;

        swap(input[begin], input[max]);
        begin = max;
    }
}

// Construct the array into a max heap from bottom up
template <class T>
static void Heapify(vector<T> &input)
{
    if (input.size() <= 1)
        return;

    //         0
    //    1          2
    //  3   4     5     6
    // 7 8 9 10 11 12 13 14
    // 2^(height - 1) - 1 < count <= 2^height - 1
    size_t height = 0;
    size_t count = input.size();
    while (count > 0)
    {
        count = count >> 1;
        height++;
    }

    // The elements at bottom are indexed in [2^(height - 1) - 1, 2^height - 2]
    // We only need to heapify elements above them
    // Do not define i as unsigned int, otherwise the for loop will continue forever
    // because i is unsigned and thus i is always non-negative.
    // When i = 0, (i --) becomes 4294967295
    for (long long i = ((1 << (height - 1)) - 2); i >= 0; i--)
        HeapifyElement(input, (size_t)i, input.size() - 1);
}

// d-ary
//                                                  0
//                   1                              2                    ...          d
// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
// (d^2+d+1) (d^2+d+2) ...
// ......
// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]
//
// (d^(h-1)-1)/(d-1) < count <= (d^h-1)/(d-1)
// d^(h-1) - 1 < count * (d-1) <= d^h - 1
// There are h d-bits and the pattern is between:
//  1    0    0    ...  0    0    0
// (d-1)(d-1)(d-1) ... (d-1)(d-1)(d-1)
template <class T>
static void Heapify(vector<T> &input, size_t d)
{
    if (input.size() <= 1)
        return;

    assert(d >= 2);

    size_t height = 0;
    size_t count = input.size() * (d - 1);
    while (count > 0)
    {
        count = count / d;
        height++;
    }

    long long index = ((long long)pow(d, height - 1) - 1) / (d - 1) - 1;
    for (long long i = index; i >= 0; i--)
        HeapifyElement(input, (size_t)i, input.size() - 1, d);
}

template <class T>
static void HeapifyInParallel(vector<T> &input)
{
    if (input.size() <= 1)
        return;

    size_t height = 0;
    size_t count = input.size();
    while (count > 0)
    {
        count = count >> 1;
        height++;
    }

    for (long long h = (height - 1); h > 0; h--)
    {
        // For h, the index is in [((1 << (h-1)) - 1), ((1 << h) - 2)]
        parallel_for(
            size_t((1 << (h - 1)) - 1),
            size_t((1 << h) - 1),
            [&](size_t i) { HeapifyElement(input, i, input.size() - 1); });
    }
}

template <class T>
static void HeapifyInParallel(vector<T> &input, size_t d)
{
    if (input.size() <= 1)
        return;

    assert(d >= 2);

    size_t height = 0;
    size_t count = input.size() * (d - 1);
    while (count > 0)
    {
        count = count / d;
        height++;
    }

    for (long long h = height - 1; h > 0; h--)
    {
        // For h, the index is in [(d ^ (h - 1) - 1) / (d - 1), (d^h - 1) / (d - 1) - 1]
        parallel_for(
            size_t((pow(d, h - 1) - 1) / (d - 1)),
            size_t((pow(d, h) - 1) / (d - 1)),
            [&](size_t i) { HeapifyElement(input, i, input.size() - 1, d); });
    }
}

template <class T>
static void HeapSort(vector<T> &input)
{
    if (input.size() <= 1)
        return;

    // Make a heap
    Heapify(input);

    // Sort
    for (long long i = input.size() - 1; i > 0; i--)
    {
        // Swap the current maximum value, which is at position 0, to position i.
        // The range [i, length - 1] is sorted.
        swap(input[0], input[i]);
        // Rearrange [0, i - 1] so that it is a heap
        HeapifyElement(input, 0, (size_t)i - 1);
    }
}

template <class T>
static void HeapSort(vector<T> &input, size_t d)
{
    if (input.size() <= 1)
        return;

    // Make a heap
    Heapify(input, d);

    // Sort
    for (long long i = input.size() - 1; i > 0; i--)
    {
        // Swap the current maximum value, which is at position 0, to position i.
        // The range [i, length - 1] is sorted.
        swap(input[0], input[i]);
        // Rearrange [0, i - 1] so that it is a heap
        HeapifyElement(input, 0, (size_t)i - 1, d);
    }
}

template <class T>
static void HeapSortInParallel(vector<T> &input)
{
    if (input.size() <= 1)
        return;

    // Make a heap
    HeapifyInParallel(input);

    // Sort
    for (long long i = input.size() - 1; i > 0; i--)
    {
        // Swap the current maximum value, which is at position 0, to position i.
        // The range [i, length - 1] is sorted.
        swap(input[0], input[i]);
        // Rearrange [0, i - 1] so that it is a heap
        HeapifyElement(input, 0, (size_t)i - 1);
    }
}

template <class T>
static void HeapSortInParallel(vector<T> &input, size_t d)
{
    if (input.size() <= 1)
        return;

    // Make a heap
    HeapifyInParallel(input, d);

    // Sort
    for (long long i = input.size() - 1; i > 0; i--)
    {
        // Swap the current maximum value, which is at position 0, to position i.
        // The range [i, length - 1] is sorted.
        swap(input[0], input[i]);
        // Rearrange [0, i - 1] so that it is a heap
        HeapifyElement(input, 0, (size_t)i - 1, d);
    }
}

namespace BitonicSort
{
template <class T>
static void Compare(T *items, int i, int j, bool dir)
{
    cout << "Compare(" << i << "," << j << ")=>";
    cout << "(" << items[i] << "," << items[j] << ")";
    if (dir == (items[i] > items[j]))
    {
        swap(items[i], items[j]);
        cout << "=>(" << items[i] << "," << items[j] << ")";
    }
}

template <class T>
static void Merge(T *items, int index, int count, bool dir)
{
    cout << "Merge(" << index << "," << count << ")=>";
    if (count > 1)
    {
        int m = count >> 1;
        for (int i = index; i < index + m; ++i)
        {
            Compare(items, i, i + m, dir);
        }
        Merge(items, index, m, dir);
        Merge(items, index + m, count - m, dir);
    }
    Print(items, index, count);
}

template <class T>
static void Sort(T *items, int index, int count, bool dir)
{
    cout << "Sort(" << index << "," << count << ")=>";
    if (count > 1)
    {
        // Divide the array into two partitions and then sort
        // the partitions in different directions.
        int m = count >> 1;

        Sort(items, index, m, true);
        Sort(items, index + m, count - m, false);

        // Merge the results.
        Merge(items, index, count, dir);
    }
    Print(items, index, count);
}

template <class T>
static void Sort(T *items, int size)
{
    Print(items, 0, size);
    Sort(items, 0, size, true);
    Print(items, 0, size);
}

template <class T>
static void Print(T *items, int index, int count)
{
    for (int i = index; i < (index + count); i++)
    {
        cout << items[i] << " ";
    }
    cout << endl;
}
}; // namespace BitonicSort

} // namespace Test

namespace RodCutting
{
// i = 0   1   2   3   ... i   ... n
// u = u_0 u_1 u_2 u_3 ... u_i ... u_n
// m = m_0 m_1 m_2 m_3 ... m_i ... m_n
// u_i is the utility of length i
// u0 < u_1 < u2 < ... < u_(n-1) < u_n
// m_i is the max utility fo cutting rod of length i
// m_0 = u_0
// m_1 = max((u_0 + m_0), u_1)
// m_2 = max((u_0 + m_1), (u_1 + m_0), u_2)
// ...
// m_i = max((u_0 + m_(i-1)), (u_1 + m_(i-2)), (u_2 + m_(i-3)), ... (u_(i-1) + m_0), u_i)
void ComputeFirstCut(vector<double> &utility, vector<double> &maxUtility, vector<int> &firstCut)
{
    maxUtility[0] = utility[0];
    firstCut[0] = 0;

    for (unsigned int i = 1; i < utility.size(); i++)
    {
        maxUtility[i] = -1;
        for (unsigned int j = 0; j < i; j++)
        {
            double current = utility[j] + maxUtility[i - j - 1];
            if (maxUtility[i] < current)
            {
                maxUtility[i] = current;
                firstCut[i] = j;
            }
        }
        if (maxUtility[i] < utility[i])
        {
            maxUtility[i] = utility[i];
            firstCut[i] = i;
        }
    }
}

// i = 0   1   2   3   ... i   ... n
// f = f_0 f_1 f_2 f_3 ... f_i ... f_n
// index    cut    left
// n        f_n    n-f_n-1
// n-f_n-1
void PrintResult(vector<double> &utility)
{
    int i = (int)utility.size();

    vector<double> maxUtility(i);
    vector<int> firstCut(i);

    ComputeFirstCut(utility, maxUtility, firstCut);

    i--;
    while (i >= 0)
    {
        cout << firstCut[i] << " ";
        i = i - firstCut[i] - 1;
    }
    cout << endl;
}
} // namespace RodCutting

// Give a matrix, a seam is a path from one side to the other such that
// successiv elements are adjacent vertically or diagnoally. The sum of
// elements of a seam is of interesting, and people usually wants to find
// a seam with minimum sum. This is useful in many image processing applications.
namespace SeamCarving
{
template <class T>
static void ComputeSeams(Matrix<T> &input, Matrix<T> &seams)
{
    int rows = input.Rows();
    int cols = input.Cols();
    for (int i = 0; i < cols; i++)
    {
        seams(0, i) = input(0, i);
    }

    T min;
    for (int i = 1; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j - 1 >= 0)
            {
                min = seams(i - 1, j - 1);
                if (seams(i - 1, j) < min)
                    min = seams(i - 1, j);
            }
            else
            {
                min = seams(i - 1, j);
            }

            if (j + 1 < cols && input(i - 1, j + 1) < min)
                min = seams(i - 1, j + 1);

            seams(i, j) = input(i, j) + min;
        }
    }
}
template <class T>
static void MinSeam(Matrix<T> &input, vector<pair<size_t, size_t>> &seam)
{
    int rows = input.Rows();
    int cols = input.Cols();
    Matrix<T> seams(rows, cols);
    ComputeSeams(input, seams);
    int j = 0;
    T min = seams(rows - 1, 0);
    for (int i = 1; i < cols; i++)
    {
        if (seams(rows - 1, i) < min)
        {
            min = seams(rows - 1, i);
            j = i;
        }
    }

    seam.insert(seam.begin(), make_pair(rows - 1, j));

    int k = j;
    for (int i = rows - 2; i >= 0; i--)
    {
        if (j - 1 >= 0)
        {
            min = seams(i, j - 1);
            k = j - 1;
            if (seams(i, j) < min)
            {
                min = seams(i, j);
                k = j;
            }
        }
        else
        {
            min = seams(i, j);
            k = j;
        }

        if (j + 1 < cols && seams(i, j + 1) < min)
        {
            k = j + 1;
        }

        seam.insert(seam.begin(), make_pair(i, k));
        j = k;
    }
}
} // namespace SeamCarving

namespace Tree
{
//         0
//    1          2
//  3   4     5     6
// 7 8 9 10 11 12 13 14
// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
static unsigned int Parent(unsigned int i) { return (i - 1) >> 1; }
static unsigned int Left(unsigned int i) { return (i << 1) + 1; }
static unsigned int Right(unsigned int i) { return (i << 1) + 2; }

// Get the height of binary tree given count of nodes
//         0
//    1          2
//  3   4     5     6
// 7 8 9 10 11 12 13 14
// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
//
// 2^(H - 1) <= count <= 2^H - 1
// There are H bits and the pattern is between:
// 10000 ... 000
// 11111 ... 111
static unsigned int Height(unsigned int count)
{
    unsigned int h = 0;
    while (count > 0)
    {
        count = count >> 1;
        h++;
    }
    return h;
}

// d-ary heap
//                                                  0
//                   1                              2                    ...          d
// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
// (d^2+d+1) (d^2+d+2) ...
// ......
// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]
// Return the index of the parent of node i
static unsigned int Parent(unsigned int i, unsigned int d) { return (i - 1) / d; }
// Return the index of the j-th child of node i. j is zero based.
static unsigned int Child(unsigned int i, unsigned int j, unsigned int d) { return i * d + j + 1; }
// Get the height of d-ary tree given count of nodes
// d-ary
//                                                  0
//                   1                              2                    ...          d
// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
// (d^2+d+1) (d^2+d+2) ...
// ......
// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]
//
// (d^(h-1)-1)/(d-1) < count <= (d^h-1)/(d-1)
// d^(h-1) - 1 < count * (d-1) <= d^h - 1
// There are h d-bits and the pattern is between:
//  1    0    0    ...  0    0    0
// (d-1)(d-1)(d-1) ... (d-1)(d-1)(d-1)
static unsigned int Height(unsigned int count, unsigned int d)
{
    count = count * (d - 1);
    unsigned int h = 0;
    while (count > 0)
    {
        count = count / d;
        h++;
    }
    return h;
}
} // namespace Tree

namespace UnitTimeTaskScheduler
{
// Separate a set of tasks with <deadline, weight> into a subset of ontime
// and a subset of late, so that the tasks of ontime can be scheduled before
// their deadlines and the total sum of weights is maximized.
// Each deadline is greater than 0 and less or equal to the count of tasks.
// This is discussed in MIT Introduction to Algorithms 3rd edition, Chapter 16.
// It is solved using the greedy algorithm over a matroid.
static void Schedule(vector<pair<int, int>> &tasks, vector<pair<int, int>> &ontime, vector<pair<int, int>> &late)
{
    function<bool(const pair<int, int> &, const pair<int, int> &)> greaterWeight =
        [&](const pair<int, int> &first, const pair<int, int> &second) -> bool {
        return first.second > second.second;
    };

    // Sort tasks by weights decreasingly
    stable_sort(tasks.begin(), tasks.end(), greaterWeight);

    // Count number of tasks in set whose deadline is no late than a given value.
    function<int(const vector<pair<int, int>> &, int)> count =
        [&](const vector<pair<int, int>> &set, int deadline) -> int {
        int c = 0;
        for_each(set.begin(), set.end(), [&](const pair<int, int> &t) {
            if (t.first <= deadline)
                c++;
        });

        return c;
    };

    while (!tasks.empty())
    {
        pair<int, int> t = tasks.front();
        tasks.erase(tasks.begin());
        bool isLate = false;
        for (int i = 0; i <= (int)ontime.size(); i++)
        {
            int c = count(ontime, i);
            if (c == i && t.first <= i)
            {
                // The first i time slots have already been filled.
                // Task t cannot fit in. Put it in the late set.
                isLate = true;
                late.push_back(t);
                break;
            }
        }

        if (!isLate)
            ontime.push_back(t);
    };

    function<bool(const pair<int, int> &, const pair<int, int> &)> earlier =
        [&](const pair<int, int> &first, const pair<int, int> &second) -> bool {
        return first.first < second.first;
    };

    stable_sort(ontime.begin(), ontime.end(), earlier);
    stable_sort(late.begin(), late.end(), earlier);
}
} // namespace UnitTimeTaskScheduler
#endif