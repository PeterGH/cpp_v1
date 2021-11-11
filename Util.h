#ifndef _UTIL_H_
#define _UTIL_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

namespace Random
{
static int Int(int max = RAND_MAX, int min = 0)
{
    return min +
           (rand() % ((long long)max - (long long)min + 1)); // may overflow if INT_MAX or INT_MIN
}

static void Array(int *array, int length, int max = RAND_MAX, int min = 0)
{
    if (array == nullptr)
        throw invalid_argument("array is nullptr");
    if (length <= 0)
        throw invalid_argument("invalid length");
    for (int i = 0; i < length; i++)
    {
        array[i] = Int(max, min);
    }
}

static vector<int> Vector(size_t n, int max = RAND_MAX, int min = 0)
{
    vector<int> result(n);
    std::generate(result.begin(), result.end(),
                  [&]() { return Int(max, min); });
    return result;
}

static vector<vector<int>> Grid(size_t m, size_t n, int max = RAND_MAX,
                                int min = 0)
{
    vector<vector<int>> result(m, vector<int>(n));
    for (size_t i = 0; i < m; i++)
    {
        std::generate(result[i].begin(), result[i].end(),
                      [&]() { return Int(max, min); });
    }
    return result;
}

static vector<vector<char>> Grid(size_t m, size_t n, char max, char min)
{
    vector<vector<char>> result(m, vector<char>(n));
    for (size_t i = 0; i < m; i++)
    {
        std::generate(result[i].begin(), result[i].end(),
                      [&]() { return char(Int(max, min)); });
    }
    return result;
}

template <class T>
static basic_string<T> String(size_t length, const basic_string<T> &alphabet)
{
    basic_string<T> output;
    size_t len = alphabet.length();
    if (len == 0)
        return output;
    for (size_t i = 0; i < length; i++)
    {
        T c = alphabet[rand() % len];
        output.append(1, c);
    }
    return output;
}

static string String(size_t length)
{
    static string alphabet =
        "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return String(length, alphabet);
}

template <class T>
static vector<basic_string<T>> Strings(size_t count, size_t maxStringlength,
                                       const basic_string<T> &alphabet)
{
    vector<basic_string<T>> result(count);
    std::generate(result.begin(), result.end(), [&]() {
        return maxStringlength == 0
                   ? Test::String::Empty<T>()
                   : String(rand() % maxStringlength, alphabet);
    });
    return result;
}

} // namespace Random

namespace Util
{
template <class T>
static int Compare(const vector<T> &lhs, const vector<T> &rhs)
{
    if (lhs.empty() && rhs.empty())
        return 0;
    if (lhs.empty())
        return -1;
    if (rhs.empty())
        return 1;
    size_t n = min(lhs.size(), rhs.size());
    for (size_t i = 0; i < n; i++)
    {
        if (lhs[i] < rhs[i])
            return -1;
        else if (lhs[i] > rhs[i])
            return 1;
    }
    if (lhs.size() < rhs.size())
        return -1;
    else if (lhs.size() > rhs.size())
        return 1;
    else
        return 0;
}

static int Compare(const vector<string> &lhs, const vector<string> &rhs)
{
    if (lhs.empty() && rhs.empty())
        return 0;
    if (lhs.empty())
        return -1;
    if (rhs.empty())
        return 1;
    size_t n = min(lhs.size(), rhs.size());
    for (size_t i = 0; i < n; i++)
    {
        int c = lhs[i].compare(rhs[i]);
        if (c != 0)
            return c;
    }
    if (lhs.size() < rhs.size())
        return -1;
    else if (lhs.size() > rhs.size())
        return 1;
    else
        return 0;
}

template <class T>
static int Compare(const vector<vector<T>> &lhs, const vector<vector<T>> &rhs)
{
    if (lhs.empty() && rhs.empty())
        return 0;
    if (lhs.empty())
        return -1;
    if (rhs.empty())
        return 1;
    size_t n = min(lhs.size(), rhs.size());
    for (size_t i = 0; i < n; i++)
    {
        int r = Compare(lhs[i], rhs[i]);
        if (r != 0)
            return r;
    }
    if (lhs.size() < rhs.size())
        return -1;
    else if (lhs.size() > rhs.size())
        return 1;
    else
        return 0;
}

template <class T>
static bool Contain(const map<T, int> &m1, const map<T, int> &m2)
{
    for (auto it = m2.cbegin(); it != m2.cend(); it++)
    {
        if (m1.find(it->first) == m1.end())
            return false;
        if (m1.at(it->first) < it->second)
            return false;
    }
    return true;
}

template <class T>
static bool Equal(const map<T, int> &m1, const map<T, int> &m2)
{
    if (m1.size() != m2.size())
        return false;
    for (auto it = m2.cbegin(); it != m2.cend(); it++)
    {
        if (m1.find(it->first) == m1.end())
            return false;
        if (m1.at(it->first) != it->second)
            return false;
    }
    return true;
}

static bool Equal(const map<int, vector<int>> &m1,
                  const map<int, vector<int>> &m2)
{
    if (m1.size() != m2.size())
        return false;
    for (auto it = m2.cbegin(); it != m2.cend(); it++)
    {
        if (m1.find(it->first) == m1.end())
            return false;
        if (0 != Compare(m1.at(it->first), it->second))
            return false;
    }
    return true;
}

template <class T>
struct VectorLess : std::less<T>
{
    bool operator()(const vector<T> &v1, const vector<T> &v2) const
    {
        return Compare(v1, v2) == -1;
    }
};

static vector<int> IncreasingVector(size_t n, int init = 0)
{
    vector<int> result(n);
    std::generate(result.begin(), result.end(), [&]() { return init++; });
    return result;
}

static bool IsIncreasing(const vector<int> &v)
{
    for (size_t i = 1; i < v.size(); i++)
    {
        if (v[i - 1] > v[i])
            return false;
    }
    return true;
}

template <class T>
static void RotateLeft(vector<T> &input, size_t distance)
{
    if (input.empty())
        return;
    distance = distance % input.size();
    if (distance == 0)
        return;
    int i = 0;
    int j = input.size() - 1;
    int k = distance;
    // input[i..k-1] and input[k..j]
    while (i < k && k <= j)
    {
        if (k - i < j - k + 1)
        {
            // Left range is shorter. Swap it to the right, and
            // repeat with the rest on its left.
            // input[i..k-1], input[k..j-(k-i)], input[j-(k-i)+1..j]
            for (int n = 0; n < k - i; n++)
                swap(input[i + n], input[j - (k - i) + 1 + n]);
            j = j - (k - i);
        }
        else if (k - i > j - k + 1)
        {
            // Right range is shorter. Swap it to the left, and
            // repeat with the rest on its right.
            // input[i..i+(j-k)], input[i+(j-k)+1..k-1], input[k..j]
            for (int n = 0; n < j - k + 1; n++)
                swap(input[i + n], input[k + n]);
            i = i + (j - k) + 1;
        }
        else
        {
            // Both ranges have the same length
            for (int n = 0; n < k - i; n++)
                swap(input[i + n], input[k + n]);
            break;
        }
    }
}

static void Shuffle(vector<int> &input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        size_t j = rand() % input.size();
        swap(input[i], input[j]);
    }
}

// Sort a vector of vectors. Each vector element is not sorted.
static void Sort(vector<vector<int>> &grid)
{
    sort(grid.begin(), grid.end(),
         [&](vector<int> &lhs, vector<int> &rhs) -> bool {
             if (lhs.empty() && rhs.empty())
                 return false;
             if (lhs.empty())
                 return true;
             size_t n = min(lhs.size(), rhs.size());
             for (size_t i = 0; i < n; i++)
             {
                 if (lhs[i] < rhs[i])
                     return true;
                 else if (lhs[i] > rhs[i])
                     return false;
             }
             return lhs.size() < rhs.size();
         });
}

// Sort a vector of vectors. Each vector element is not sorted.
static void Sort(vector<vector<string>> &grid)
{
    sort(grid.begin(), grid.end(),
         [&](vector<string> &lhs, vector<string> &rhs) -> bool {
             if (lhs.empty() && rhs.empty())
                 return false;
             if (lhs.empty())
                 return true;
             size_t n = min(lhs.size(), rhs.size());
             for (size_t i = 0; i < n; i++)
             {
                 int c = lhs[i].compare(rhs[i]);
                 if (c < 0)
                     return true;
                 else if (c > 0)
                     return false;
             }
             return lhs.size() < rhs.size();
         });
}

// Sort a grid. First sort each row, then sort the vector of rows.
static void SortGrid(vector<vector<int>> &grid)
{
    for_each(grid.begin(), grid.end(),
             [&](vector<int> &v) { sort(v.begin(), v.end()); });
    sort(grid.begin(), grid.end(),
         [&](vector<int> &lhs, vector<int> &rhs) -> bool {
             if (lhs.empty() && rhs.empty())
                 return false;
             if (lhs.empty())
                 return true;
             size_t n = min(lhs.size(), rhs.size());
             for (size_t i = 0; i < n; i++)
             {
                 if (lhs[i] < rhs[i])
                     return true;
                 else if (lhs[i] > rhs[i])
                     return false;
             }
             return lhs.size() < rhs.size();
         });
}

static void Sort(vector<string> &v)
{
    sort(v.begin(), v.end(), [&](const string &l, const string &r) -> bool {
        return l.compare(r) < 0;
    });
}

// Sort a grid. First sort each row, then sort the vector of rows.
static void SortGrid(vector<vector<string>> &grid)
{
    for_each(grid.begin(), grid.end(), [&](vector<string> &v) { Sort(v); });
    sort(grid.begin(), grid.end(),
         [&](vector<string> &lhs, vector<string> &rhs) -> bool {
             if (lhs.empty() && rhs.empty())
                 return false;
             if (lhs.empty())
                 return true;
             size_t n = min(lhs.size(), rhs.size());
             for (size_t i = 0; i < n; i++)
             {
                 int c = lhs[i].compare(rhs[i]);
                 if (c < 0)
                     return true;
                 else if (c > 0)
                     return false;
             }
             return lhs.size() < rhs.size();
         });
}

static void Sort(map<int, vector<int>> &m)
{
    for (auto it = m.begin(); it != m.end(); it++)
    {
        sort(it->second.begin(), it->second.end());
    }
}

template <class T>
static map<T, int> Count(const vector<T> &v, size_t begin, size_t end)
{
    if (begin >= v.size())
        throw invalid_argument("begin");
    if (end >= v.size())
        throw invalid_argument("end");
    if (begin > end)
        throw invalid_argument("begin > end");
    map<T, int> m;
    for (size_t i = begin; i <= end; i++)
    {
        if (m.find(v[i]) == m.end())
            m[v[i]] = 1;
        else
            m[v[i]]++;
    }
    return m;
}

template <class T>
static map<T, int> Count(const vector<T> &v)
{
    if (v.empty())
        return map<T, int>();
    return Count(v, 0, v.size() - 1);
}

} // namespace Util

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "{";
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i > 0)
            os << ", ";
        os << v[i];
    }
    os << "}" << endl;
    return os;
}

#endif