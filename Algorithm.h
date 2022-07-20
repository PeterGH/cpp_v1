#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "String.h"
#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <memory>
#include <stack>
#include <string.h>
#include <unordered_map>
#include <vector>

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
    static int BinarySearch(const Value &value, int begin, int end,
                            function<const Value &(int)> get, bool first = true,
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
    static int BinarySearch(const vector<int> &input, int value, size_t begin,
                            size_t end, bool first = true,
                            Compare comp = std::less<>())
    {
        return BinarySearch(
            value, (int)begin, (int)end,
            [&](int i) -> const int &
            { return input[i]; },
            first, comp);
    }

    // Search a value in a column
    template <class Compare = std::less<>>
    static int BinarySearch(const vector<vector<int>> &input, size_t col, int value,
                            size_t begin, size_t end, bool first = true,
                            Compare comp = std::less<>())
    {
        return BinarySearch(
            value, (int)begin, (int)end,
            [&](int i) -> const int &
            { return input[i][col]; },
            first, comp);
    }

    // Assume the input is sorted.
    // Cases:
    // 1. empty input
    // 2. target is the first
    // 3. target is the last
    // 4. target is in the middle
    // 5. target is less than everyone
    // 6. target is greater than everyone
    // 7. target does not exists and is neither less than nor greater than everyone
    int BinarySearch(const vector<int> &input, int target)
    {
        int b = 0;
        int e = (int)input.size() - 1;
        // [b..e] contain possible answers
        while (b <= e)
        {
            int m = b + ((e - b) >> 1); // b <= m <= e
            if (input[m] < target)
                b = m + 1;
            else if (input[m] > target)
                e = m - 1;
            else
                return m;
        }
        return -1;
    }
    int BinarySearch2(const vector<int> &input, int target)
    {
        int b = 0;
        int e = (int)input.size(); // b <= e
        // [b..e) contain possible answers
        while (b < e)
        {
            int m = b + ((e - b) >> 1); // b <= m < e
            if (input[m] < target)
                b = m + 1;
            else if (input[m] > target)
                e = m;
            else
                return m;
        }
        // Post-processing: End Condition: b == e
        if (b != (int)input.size() && input[b] == target)
            return b;
        return -1;
    }
    int BinarySearch2_2(const vector<int> &input, int target)
    {
        int b = 0;
        int e = (int)input.size() - 1; // b > e if input is empty
        // [b..e) contain possible answers
        while (b < e)
        {
            int m = b + ((e - b) >> 1); // b <= m < e
            if (input[m] < target)
                b = m + 1;
            else if (input[m] > target)
                e = m;
            else
                return m;
        }
        // Post-processing: End Condition: b == e
        if (b == e && input[b] == target)
            return b;
        return -1;
    }
    int BinarySearch3(const vector<int> &input, int target)
    {
        if (input.empty())
            return -1;
        int b = 0;
        int e = input.size() - 1;
        // (b..e) contain possible answers
        while (b + 1 < e)
        {
            int m = b + ((e - b) >> 1); // b < m < e
            if (input[m] == target)
                return m;
            else if (input[m] < target)
                b = m;
            else
                e = m;
        }
        // Post-processing: End Condition: b + 1 == e
        if (input[b] == target)
            return b;
        if (input[e] == target)
            return e;
        return -1;
    }

    // comp is a binary function returning a boolean value.
    // If comp(first, second) returns true, then the first input
    // should go before the second input. Default comp is std::less,
    // which forms a non-decreasing sequence. Return i in [begin, end]
    // if should insert value to position i. Return end + 1 if should
    // append value.
    template <class Value, class Compare = std::less<Value>>
    static size_t FindInsertPoint(const Value &value, int begin, int end,
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
    static size_t FindInsertPoint(vector<int> &input, int value, size_t begin,
                                  size_t end, bool first = true,
                                  Compare comp = std::less<>())
    {
        return FindInsertPoint(
            value, (int)begin, (int)end, [&](int i) -> int
            { return input[i]; },
            first, comp);
    }

    // find insert point for a value in a column
    template <class Compare = std::less<>>
    static size_t FindInsertPoint(vector<vector<int>> &input, size_t col, int value,
                                  size_t begin, size_t end, bool first = true,
                                  Compare comp = std::less<>())
    {
        return FindInsertPoint(
            value, (int)begin, (int)end,
            [&](int i) -> int
            { return input[i][col]; },
            first, comp);
    }

    // Find a number closest to a target from a sorted array
    int FindClosest(const vector<int> &input, int target)
    {
        if (input.empty())
            return -1;
        int b = 0;
        int e = (int)input.size() - 1;
        while (b + 1 < e)
        {
            int m = b + ((e - b) >> 1);
            if (input[m] < target)
                b = m;
            else if (input[m] > target)
                e = m;
            else
                return m;
        }
        if (target <= input[b])
            return b;
        else if (input[e] <= target)
            return e;
        else if (target - input[b] <= input[e] - target)
            return b;
        else
            return e;
    }
    int FindClosest2(const vector<int> &input, int target)
    {
        int index = -1;
        long long delta = LLONG_MAX;
        for (int i = 0; i < (int)input.size(); i++)
        {
            long long d = abs(input[i] - target);
            if (d < delta)
            {
                delta = d;
                index = i;
            }
        }
        return index;
    }

    // Find the median of a sorted array.
    // If the array length is odd, then the median is unique.
    // If the array length is even, then return the lower median.
    // Lower median or single median is (L - 1) / 2
    // Higher median or single median is L / 2
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
    // If the two arrays contain even number of elements, then return the lower
    // median.
    template <class T>
    static T FindMedian(const T *input1, int length1, const T *input2,
                        int length2)
    {
        if (input1 == nullptr)
            throw invalid_argument("input1 is a nullptr");
        if (length1 <= 0)
            throw invalid_argument(
                String::Format("length1 %d is invalid", length1));
        if (input2 == nullptr)
            throw invalid_argument("input2 is a nullptr");
        if (length2 <= 0)
            throw invalid_argument(
                String::Format("length2 %d is invalid", length2));

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
                // +---------------------------------------+
                // +---------------------------------------+
                // 0 s-1 0 l-1
                // s = l
                // m = s - 1 = l - 1
                return shortArray[medianIndex];
            }
            else
            {
                // +---------------------------------------+
                // +-----+------------------------------------------+
                // 0 s-1 0 m-s l-1
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
            // +---------------------------------------+---------+
            // +---------------------------------------+
            // 0 m l-1 0 s-1
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
        // Median =
        // S[m] if L[n] < S[m] <= L[n+1], i.e. S[m] is the lower median and
        //      L[n+1] is the higher median
        // L[n] if S[m] < L[n] <= S[m+1], i.e. L[m] is the lower median and
        //      S[n+1] is the higher median
        // S[m] if S[m] == L[n], i.e. S[m] or L[n] is the lower median and
        //      min(S[m+1], L[n+1]) is the higher median
        // max(S[m-1], L[n+1]) if S[m] > L[n+1]
        // max(S[m+1], L[n-1]) if L[n] > S[m+1]

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
    static T FindKthOrder(int k, const T *input1, int length1, const T *input2,
                          int length2)
    {
        if (input1 == nullptr)
            throw invalid_argument("input1 is a nullptr");
        if (length1 <= 0)
            throw invalid_argument(
                String::Format("length1 %d is invalid", length1));
        if (input2 == nullptr)
            throw invalid_argument("input2 is a nullptr");
        if (length2 <= 0)
            throw invalid_argument(
                String::Format("length2 %d is invalid", length2));
        if (k <= 0)
            throw invalid_argument(String::Format("k %d is invalid", k));
        if (k > length1 + length2)
            throw invalid_argument(
                String::Format("k(%d) is greater than length1(%d) + length2(%d)", k,
                               length1, length2));

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
                // +-----------------------+---------------+
                // +---------------------------------------+
                // 0 k-1 s-1 0 l-1
                return shortArray[k - 1];
            }
            else
            {
                // +---------------------------------------+
                // +-----+------------------------------------------+
                // 0 s-1 0 k-s-1 l-1
                return longArray[k - shortLength - 1];
            }
        }
        else if (longArray[longLength - 1] <= shortArray[0])
        {
            if (k <= longLength)
            {
                // +---------------------------------------+---------+
                // +---------------------------------------+
                // 0 k-1 l-1 0 s-1
                return longArray[k - 1];
            }
            else
            {
                // +-------------------------------------------------+
                // +--------+------------------------------+
                // 0 l-1 0 k-l-1 s-1
                return shortArray[k - longLength - 1];
            }
        }
        if (k == 1)
        {
            return std::min<T>(shortArray[0], longArray[0]);
        }
        if (k == shortLength + longLength)
        {
            return std::max<T>(shortArray[shortLength - 1],
                               longArray[longLength - 1]);
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

        throw runtime_error(
            String::Format("Unable to find %d-th smallest element", k));
    }
    template <class T>
    static T FindKthOrder2(int k, const T *input1, int length1, const T *input2,
                           int length2)
    {
        if (input1 == nullptr)
            throw invalid_argument("input1 is a nullptr");
        if (length1 <= 0)
            throw invalid_argument(
                String::Format("length1 %d is invalid", length1));
        if (input2 == nullptr)
            throw invalid_argument("input2 is a nullptr");
        if (length2 <= 0)
            throw invalid_argument(
                String::Format("length2 %d is invalid", length2));
        if (k <= 0)
            throw invalid_argument(String::Format("k %d is invalid", k));
        if (k > length1 + length2)
            throw invalid_argument(
                String::Format("k(%d) is greater than length1(%d) + length2(%d)", k,
                               length1, length2));

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
            throw runtime_error(
                String::Format("Unable to find %d-th smallest element", k));
        }
    }

    // Find all pairs of elements each of which is summed up to a given value
    // Return the indices using a vector
    // The elements of input will be rearranged so the indices returned are not the
    // original ones
    template <class T>
    static void FindPairsBySum(T *input, int length, const T sum,
                               vector<pair<int, int>> &indices)
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
            // 0                          i1                    i2 length-1
            //           < sum/2                  = sum/2                > sum/2

            // Partition input so that input[0..i1] <= half - 1 <
            // input[i1+1..length-1]
            int i1 =
                Partition::PartitionArrayByValue(input, 0, length - 1, half - 1);
            if (i1 == length - 1)
            {
                // All elements are less than sum/2 - 1, no matter whether sum is
                // positive or negative.
                return;
            }

            // Partition input once more so that input[i1+1..i2] = half <
            // input[i2+1..length-1]
            int i2 =
                Partition::PartitionArrayByValue(input, i1 + 1, length - 1, half);
            if (i2 == -1)
            {
                // All elements are greater than sum/2, no matter whether sum is
                // positive or negative.
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
            // 0                                     i1 length-1
            //                 <= sum/2                             >= sum/2 + 1

            // Partition input so that input[0..i1] <= half < input[i1+1..length-1]
            int i1 = Partition::PartitionArrayByValue(input, 0, length - 1, half);

            if (i1 == -1)
            {
                // All elements are greater than sum/2, no matter whether sum is
                // positive or negative.
                return;
            }

            if (i1 == length - 1)
            {
                // All elements are less than or equal to sum/2, no matter whether
                // sum is positive or negative.
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
            int j =
                Search::BinarySearch<T>(v, &input[shortRangeBegin],
                                        shortRangeEnd - shortRangeBegin + 1, true);
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
    // The elements of input will be rearranged so the indices returned are not the
    // original ones
    template <class T>
    static void FindPairsBySum2(T *input, int length, const T sum,
                                vector<pair<int, int>> &indices)
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
    // Return a pair of indices of found element. If not found, then return a pair
    // (-1, -1)
    template <class T>
    static pair<int, int> FindIntersection(const T *input1, int length1,
                                           const T *input2, int length2)
    {
        if (input1 == nullptr)
            throw invalid_argument("input1 is a nullptr");
        if (length1 <= 0)
            throw invalid_argument(
                String::Format("length1 %d is invalid", length1));
        if (input2 == nullptr)
            throw invalid_argument("input2 is a nullptr");
        if (length2 <= 0)
            throw invalid_argument(
                String::Format("length2 %d is invalid", length2));

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
    static pair<int, int> FindIntersection2(const T *input1, int length1,
                                            const T *input2, int length2)
    {
        if (input1 == nullptr)
            throw invalid_argument("input1 is a nullptr");
        if (length1 <= 0)
            throw invalid_argument(
                String::Format("length1 %d is invalid", length1));
        if (input2 == nullptr)
            throw invalid_argument("input2 is a nullptr");
        if (length2 <= 0)
            throw invalid_argument(
                String::Format("length2 %d is invalid", length2));

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

    class KMP
    {
    private:
        unique_ptr<char[]> pattern;
        unique_ptr<int[]> prefix;
        int length;

    public:
        KMP(const char *pattern)
        {
            if (pattern == nullptr)
                throw invalid_argument("pattern is nullptr");
            this->length = (int)strlen(pattern);
            if (this->length <= 0)
                throw invalid_argument(
                    String::Format("length %d <= 0", this->length));
            this->pattern.reset(new char[this->length + 1]);
            strcpy(this->pattern.get(), pattern);
            this->prefix.reset(new int[this->length]);
            memset(this->prefix.get(), 0, this->length * sizeof(int));
            // Maintain prefix[i] = k, update prefix[i+1] by checking pattern[i+1]
            // vs pattern[k+1]. The goal is for each input i, find k such that
            // pattern[0..k] is suffix of input[0..i].
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
                // 1. there is a k such that pattern[0..(k+1)] is a suffix of
                // pattern[0..i], or
                // 2. k = -1 (i.e., pattern[0] != pattern[i])
                if (this->pattern[k + 1] == this->pattern[i])
                {
                    // One more match
                    k = k + 1;
                }
                else
                {
                    // k = -1
                }
                this->prefix[i] = k;
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
                    k = this->prefix[k];
                if (this->pattern[k + 1] == input[i])
                    k = k + 1;
                if (k == this->length - 1)
                {
                    indices.push_back(i - k);
                    k = this->prefix[k];
                }
            }
            return indices;
        }
    };

    class Monge
    {
    public:
        static vector<vector<int>> Random(size_t m, size_t n, int max = RAND_MAX, int min = 0)
        {
            vector<vector<int>> result(m, vector<int>(n));
            auto rnd = [&]() -> int
            { return min + (rand() % (max - min)); };
            int l = 0;
            for (int j = 0; j < (int)n; j++)
            {
                for (int i = 0; i <= j && i < (int)m; i++)
                {
                    int k = j - i;
                    if (i == 0 || i == j)
                        result[i][k] = rnd();
                    else
                        result[i][k] = std::min(
                            rnd(),
                            result[i][k - 1] + result[i - 1][k] - result[i - 1][k - 1]);
                    l = std::min(l, result[i][k]);
                }
            }
            for (int i = 1; i < (int)m; i++)
            {
                for (int j = (int)n - 1; j >= 0 && j >= (int)n - (int)m + i; j--)
                {
                    int k = i + (int)n - 1 - j;
                    if (j == 0)
                        result[k][j] = rnd();
                    else
                        result[k][j] = std::min(
                            rnd(),
                            result[k][j - 1] + result[k - 1][j] - result[k - 1][j - 1]);
                    l = std::min(l, result[k][j]);
                }
            }
            if (l < 0)
            {
                for (int i = 0; i < (int)m; i++)
                {
                    for (int j = 0; j < (int)n; j++)
                        result[i][j] -= l;
                }
            }
            return result;
        }
        static vector<vector<int>> Random2(size_t m, size_t n, int max = RAND_MAX, int min = 0)
        {
            vector<vector<int>> result(m, vector<int>(n));
            auto rnd = [&]() -> int
            { return min + (rand() % (max - min)); };
            for (size_t j = 0; j < n; j++)
                result[0][j] = rnd();
            for (size_t i = 1; i < m; i++)
            {
                result[i][0] = rnd();
                for (size_t j = 1; j < n; j++)
                {
                    result[i][j] = std::min(rnd(),
                                            result[i - 1][j] + result[i][j - 1] - result[i - 1][j - 1]);
                    if (j < n - 1)
                    {
                        int d = result[i - 1][j] - result[i - 1][j + 1] - result[i][j];
                        if (d > 0)
                        {
                            d += (rnd() >> 1);
                            for (size_t k = 0; k <= j; k++)
                                result[i][k] += d;
                        }
                    }
                }
            }
            return result;
        }

        static bool IsMonge(const vector<vector<int>> &grid)
        {
            if (grid.size() <= 1 || grid[0].size() <= 1)
                return false;
            for (size_t i = 0; i < grid.size() - 1; i++)
            {
                for (size_t j = 0; j < grid[i].size() - 1; j++)
                {
                    if (grid[i][j] + grid[i + 1][j + 1] > grid[i][j + 1] + grid[i + 1][j])
                        return false;
                }
            }
            return true;
        }
    };

    // Given Random(0, 1) = 0 or 1 at 1/2 probability each, implement Random(a, b)
    // to ouput a random integer in [a, b].
    // Solution 1 (wrong):
    // Compute Random(0, 1) for (b - a + 1) times, sum the results and add to a.
    // This is wrong because the distribution of the sum is not uniform.
    // Solution 2:
    // Obvious we need to compute Random(0, 1) for k times, where k is to be determined.
    // So we have a sequence b = {b_0, b_1, ..., b_(k-1)}, where b_i = Random(0, 1) for the i-th time.
    // For range [a, b], k must satisfy 2^k >= (b - a + 1) so that we can map the
    // sequence b to an output.
    // b_0 * 2^0 + b_1 * 2^1 + ... + b(k-1) * 2^(k-1)
    int RandomInt(int a, int b)
    {
        function<int()> bit = [&]() -> int
        {
            return rand() & 0x1;
        };
        int r = b - a + 1; // [1, 2, ..., r]
        int k = 0;
        int d = 1;
        while (d < r)
        {
            k++;
            d = d << 1;
        }
        int s = 0;
        while (true)
        {
            // Need to run bit() for k times
            int i = 0;
            d = 1;
            s = 0;
            while (i < k)
            {
                if (bit() > 0)
                {
                    s += d;
                }
                i++;
                d = d << 1;
            }
            if (s < r)
                break;
        }
        return a + s;
    }
    int RandomInt2(int a, int b)
    {
        function<int()> bit = [&]() -> int
        {
            return rand() & 0x1;
        };
        int r = b - a; // [0, 1, ..., r]
        int k = 0;
        int d = 1;
        int s = 0;
        while (s < r)
        {
            s += d;
            k++;
            d = d << 1;
        }
        while (true)
        {
            // Need to run bit() for k times
            int i = 0;
            d = 1;
            s = 0;
            while (i < k)
            {
                if (bit() > 0)
                {
                    s += d;
                }
                i++;
                d = d << 1;
            }
            if (s <= r)
                break;
        }
        return a + s;
    }
} // namespace Test
#endif