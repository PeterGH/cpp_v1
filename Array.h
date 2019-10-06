#ifndef _ARRAY_H_
#define _ARRAY_H_

namespace Test
{
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

} // namespace Test
#endif