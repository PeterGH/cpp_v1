#ifndef _UTIL_H_
#define _UTIL_H_

#include <algorithm>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

namespace Random {
static int Int(int max = RAND_MAX, int min = 0) {
    return min +
           (rand() % (max - min + 1)); // may overflow if INT_MAX or INT_MIN
}

static void Array(int *array, int length, int max = RAND_MAX, int min = 0) {
    if (array == nullptr)
        throw invalid_argument("array is nullptr");
    if (length <= 0)
        throw invalid_argument("invalid length");
    for (int i = 0; i < length; i++) {
        array[i] = Int(max, min);
    }
}

static vector<int> Vector(size_t n, int max = RAND_MAX, int min = 0) {
    vector<int> result(n);
    std::generate(result.begin(), result.end(),
                  [&]() { return Int(max, min); });
    return result;
}

static vector<vector<int>> Grid(size_t m, size_t n, int max = RAND_MAX,
                                int min = 0) {
    vector<vector<int>> result(m, vector<int>(n));
    for (size_t i = 0; i < m; i++) {
        std::generate(result[i].begin(), result[i].end(),
                      [&]() { return Int(max, min); });
    }
    return result;
}

template <class T>
static basic_string<T> String(size_t length, const basic_string<T> &alphabet) {
    basic_string<T> output;
    size_t len = alphabet.length();
    if (len == 0)
        return output;
    for (size_t i = 0; i < length; i++) {
        T c = alphabet[rand() % len];
        output.append(1, c);
    }
    return output;
}

static string String(size_t length) {
    static string alphabet =
        "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return String(length, alphabet);
}

template <class T>
static vector<basic_string<T>> Strings(size_t count, size_t maxStringlength,
                                       const basic_string<T> &alphabet) {
    vector<basic_string<T>> result(count);
    std::generate(result.begin(), result.end(), [&]() {
        return maxStringlength == 0
                   ? String::Empty<T>()
                   : String(rand() % maxStringlength, alphabet);
    });
    return result;
}

} // namespace Random

namespace Util {
static int Compare(const vector<int> &lhs, const vector<int> &rhs) {
    if (lhs.empty() && rhs.empty())
        return 0;
    if (lhs.empty())
        return -1;
    if (rhs.empty())
        return 1;
    size_t n = min(lhs.size(), rhs.size());
    for (size_t i = 0; i < n; i++) {
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

static int Compare(const vector<vector<int>> &lhs,
                   const vector<vector<int>> &rhs) {
    if (lhs.empty() && rhs.empty())
        return 0;
    if (lhs.empty())
        return -1;
    if (rhs.empty())
        return 1;
    size_t n = min(lhs.size(), rhs.size());
    for (size_t i = 0; i < n; i++) {
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

static vector<int> IncreasingVector(size_t n, int init = 0) {
    vector<int> result(n);
    std::generate(result.begin(), result.end(), [&]() { return init++; });
    return result;
}

static void Shuffle(vector<int> &input) {
    for (size_t i = 0; i < input.size(); i++) {
        size_t j = rand() % input.size();
        swap(input[i], input[j]);
    }
}

static void Sort(vector<vector<int>> &grid) {
    sort(grid.begin(), grid.end(),
         [&](vector<int> &lhs, vector<int> &rhs) -> bool {
             if (lhs.empty() && rhs.empty())
                 return false;
             if (lhs.empty())
                 return true;
             size_t n = min(lhs.size(), rhs.size());
             for (size_t i = 0; i < n; i++) {
                 if (lhs[i] < rhs[i])
                     return true;
                 else if (lhs[i] > rhs[i])
                     return false;
             }
             return lhs.size() < rhs.size();
         });
}

static void SortGrid(vector<vector<int>> &grid) {
    for_each(grid.begin(), grid.end(),
             [&](vector<int> &v) { sort(v.begin(), v.end()); });
    sort(grid.begin(), grid.end(),
         [&](vector<int> &lhs, vector<int> &rhs) -> bool {
             if (lhs.empty() && rhs.empty())
                 return false;
             if (lhs.empty())
                 return true;
             size_t n = min(lhs.size(), rhs.size());
             for (size_t i = 0; i < n; i++) {
                 if (lhs[i] < rhs[i])
                     return true;
                 else if (lhs[i] > rhs[i])
                     return false;
             }
             return lhs.size() < rhs.size();
         });
}
} // namespace Util
#endif