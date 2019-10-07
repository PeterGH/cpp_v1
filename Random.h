#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <algorithm>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace Test
{
class Random
{
public:
    static int Int(int max = RAND_MAX, int min = 0)
    {
        return min + (rand() % (max - min + 1));
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
        std::generate(result.begin(), result.end(), [&]() { return Int(max, min); });
        return result;
    }

    static vector<vector<int>> Grid(size_t m, size_t n, int max = RAND_MAX, int min = 0)
    {
        vector<vector<int>> result(m, vector<int>(n));
        for (size_t i = 0; i < m; i++)
        {
            std::generate(result[i].begin(), result[i].end(), [&]() { return Int(max, min); });
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
        static string alphabet = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return String(length, alphabet);
    }
};
} // namespace Test

#endif