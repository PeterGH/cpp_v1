#ifndef _UTIL_H_
#define _UTIL_H_

#include <algorithm>
#include <vector>

using namespace std;

class Util
{
  public:
    static int Compare(const vector<int> &lhs, const vector<int> &rhs)
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

    static vector<int> IncreasingVector(size_t n, int init = 0)
    {
        vector<int> result(n);
        std::generate(result.begin(), result.end(), [&]() { return init++; });
        return result;
    }

    static void Shuffle(vector<int> &input)
    {
        for (size_t i = 0; i < input.size(); i++)
        {
            size_t j = rand() % input.size();
            swap(input[i], input[j]);
        }
    }

    static void Sort(vector<vector<int>> &grid)
    {
        sort(grid.begin(), grid.end(), [&](vector<int> &lhs, vector<int> &rhs) -> bool {
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

    static void SortGrid(vector<vector<int>> &grid)
    {
        for_each(grid.begin(), grid.end(), [&](vector<int> &v) {
            sort(v.begin(), v.end());
        });
        sort(grid.begin(), grid.end(), [&](vector<int> &lhs, vector<int> &rhs) -> bool {
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
};
#endif