#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "String.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Test
{

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
        int e = (int)input.size();
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
        int e = (int)input.size() - 1;
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
            auto rnd = [&]() -> int { return min + (rand() % (max - min)); };
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
            auto rnd = [&]() -> int { return min + (rand() % (max - min)); };
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
        function<int()> bit = [&]() -> int {
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
        function<int()> bit = [&]() -> int {
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