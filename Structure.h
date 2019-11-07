#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <vector>
#include "String.h"

using namespace std;

namespace Test
{
// Standard C++ Library contains a class bitset<N> to manipulate a set of
// bits. The difference is bitset<N> requires N to be set explicitly during
// compile time while BitSet can be defined during runtime. Like bitset,
// every method of BitSet manipulating a bit takes an input parameter
// representing a zero-based position.
class BitSet
{
private:
    static const int IntBits = 8 * sizeof(int);
    int _lenBit; // Number of bits managed by this class
    int _y;      // _lenBit % IntBits
    int _lenInt; // Length of int array to store bits
    int *_ints;  // Int array storing the managed bits

    // Logical shift to the left with a distance
    void LeftShiftInternal(size_t distance)
    {
        if (distance == 0)
            return;
        int x, y;
        x = distance / IntBits;
        y = distance % IntBits;
        if (y == 0)
        {
            // LSB                                             MSB
            // +----+----+----+----+----+----+----+----+----+----+
            // 0    1         x-1  x         L-x            L-1
            // |<------- x ------->|         |<------- x ------->|
            for (int i = _lenInt - 1; i >= x; i--)
            {
                _ints[i] = _ints[i - x];
            }
        }
        else
        {
            // LSB                                                                                     MSB
            // +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
            // 0        1                 x                                   L-x               L-1
            // |<----------- x ---------->|<-y->|                       |<-y->|<----------- x ---------->|
            unsigned int mask = (0x1 << y) - 1;
            for (int i = _lenInt - 1; i > x; i--)
            {
                _ints[i] = ((_ints[i - x] << y) & ~mask) + ((_ints[i - x - 1] >> (IntBits - y)) & mask);
            }
            _ints[x] = (_ints[0] << y) & ~mask;
        }
        if (x > 0)
        {
            memset(_ints, 0, x * sizeof(int));
        }
    }

    // Given a zero-based bit position, calculate the index x of integer
    // and the index y of bit in the integer.
    // Assume n = 8 * sizeof(int), then the int array represents a bit map like:
    //     | 0 1 ... (n-1) | n (n+1) ... (2n-1) | 2n  ... (3n-1) | 3n ...
    // x = | 0             | 1                  | 2              | 3  ...
    // y = | 0 1 ... (n-1) | 0 1     ... (n-1)  | 0 1 ... (n-1)  | 0  ...
    // position = x*n + y
    void Position(int position, int *x, int *y) const
    {
        if (position < 0 || position >= _lenBit)
            throw invalid_argument(String::Format("Invalid bit position [%d] (not in [0, %d])", position, _lenBit - 1));
        *x = position / IntBits;
        *y = position % IntBits;
    }

public:
    // Create a BitSet object to manage bits upto maxBits.
    BitSet(int maxBits)
    {
        if (maxBits <= 0)
            throw invalid_argument(String::Format("Invalid argument [%d]", maxBits));
        _lenBit = maxBits;
        _lenInt = _lenBit / IntBits;
        _y = _lenBit % IntBits;
        if (_y > 0)
            _lenInt++;
        _ints = new int[_lenInt];
        memset(_ints, 0, _lenInt * sizeof(int));
    }

    BitSet(const BitSet &bitset)
    {
        _lenBit = bitset._lenBit;
        _lenInt = bitset._lenInt;
        _y = bitset._y;
        _ints = new int[bitset._lenInt];
        memcpy(_ints, bitset._ints, bitset._lenInt * sizeof(int));
    }

    BitSet &operator=(const BitSet &bitset)
    {
        if (this != &bitset)
        {
            if (_ints != nullptr)
            {
                delete[] _ints;
                _ints = nullptr;
            }
            _lenBit = bitset._lenBit;
            _lenInt = bitset._lenInt;
            _y = bitset._y;
            _ints = new int[bitset._lenInt];
            memcpy(_ints, bitset._ints, bitset._lenInt * sizeof(int));
        }
        return *this;
    }

    BitSet(BitSet &&bitset)
    {
        _lenBit = bitset._lenBit;
        _lenInt = bitset._lenInt;
        _y = bitset._y;
        _ints = bitset._ints;
        bitset._lenBit = 0;
        bitset._lenInt = 0;
        bitset._y = 0;
        bitset._ints = nullptr;
    }

    BitSet &operator=(BitSet &&bitset)
    {
        if (this != &bitset)
        {
            if (_ints != nullptr)
            {
                delete[] _ints;
                _ints = nullptr;
            }
            _lenBit = bitset._lenBit;
            _lenInt = bitset._lenInt;
            _y = bitset._y;
            _ints = bitset._ints;
            bitset._lenBit = 0;
            bitset._lenInt = 0;
            bitset._y = 0;
            bitset._ints = nullptr;
        }
        return *this;
    }

    ~BitSet(void)
    {
        if (nullptr != _ints)
        {
            delete[] _ints;
            _ints = nullptr;
        }
    }

    // Test if all bits are set
    bool All(void) const
    {
        for (int i = 0; i < (_y == 0 ? _lenInt : _lenInt - 1); i++)
        {
            if (_ints[i] != (int)0xFFFFFFFF)
                return false;
        }
        // Test if the lower _y bits of the last integer are all ones
        if (_y > 0 && (((0x1 << _y) - 1) ^ _ints[_lenInt - 1]) != 0)
            return false;
        return true;
    }

    // Test if any bit is set
    bool Any(void) const
    {
        for (int i = 0; i < (_y == 0 ? _lenInt : _lenInt - 1); i++)
        {
            if (_ints[i] != 0)
                return true;
        }
        // Test if the lower y bits of the last integer are all zeros
        if (_y > 0 && ((((0x1 << _y) - 1) & _ints[_lenInt - 1]) != 0))
            return true;
        return false;
    }

    // Count the bits have been set
    size_t Count(void) const
    {
        // http://leetcode.com/2010/09/number-of-1-bits.html
        auto countInt = [&](int n) -> size_t {
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

        size_t count = 0;
        for (int i = 0; i < (_y == 0 ? _lenInt : _lenInt - 1); i++)
        {
            count += countInt(_ints[i]);
        }
        if (_y > 0)
        {
            int last = _ints[_lenInt - 1] & ((0x1 << _y) - 1);
            count += countInt(last);
        }
        return count;
    }

    // Flip all bits
    void Flip(void)
    {
        for (int i = 0; i < _lenInt; i++)
        {
            _ints[i] ^= 0xFFFFFFFF;
        }

        // The bits of the last integer have already been flipped.
        // Just reset its higher non-used bits to zero.
        if (_y > 0)
            _ints[_lenInt - 1] &= (0x1 << _y) - 1;
    }

    // Flip one bit position
    void Flip(size_t position)
    {
        int x, y;
        Position(position, &x, &y);
        _ints[x] ^= 0x1 << y;
    }

    // Test if the bit set represent an integer of power of 2
    bool IsPower2(void)
    {
        return 1 == Count();
    }

    // Logical shift to the left with a distance
    void LeftShift(size_t distance)
    {
        LeftShiftInternal(distance);
        // Reset the bits out of range
        if (_y > 0)
            _ints[_lenInt - 1] &= (0x1 << _y) - 1;
    }

    // Reset all bits to zero
    void Reset(void)
    {
        memset(_ints, 0, _lenInt * sizeof(int));
    }

    // Reset one bit position to zero
    void Reset(size_t position)
    {
        int x, y;
        Position(position, &x, &y);
        _ints[x] &= ~(0x1 << y);
    }

    // Reverse bits of an unsigned integer
    static void Reverse(unsigned int &bits)
    {
        bits = ((bits & 0x55555555) << 1) | ((bits & 0xAAAAAAAA) >> 1);
        bits = ((bits & 0x33333333) << 2) | ((bits & 0xCCCCCCCC) >> 2);
        bits = ((bits & 0x0F0F0F0F) << 4) | ((bits & 0xF0F0F0F0) >> 4);
        bits = ((bits & 0x00FF00FF) << 8) | ((bits & 0xFF00FF00) >> 8);
        bits = ((bits & 0x0000FFFF) << 16) | ((bits & 0xFFFF0000) >> 16);
    }

    // Reverse bits
    void Reverse(void)
    {
        size_t d = _lenInt * IntBits - _lenBit;
        // 0YXXXXXXX
        // YXXXXXXX0
        LeftShiftInternal(d);
        int i = 0;
        int j = _lenInt - 1;
        while (j > i)
        {
            unsigned int u = _ints[i];
            unsigned int v = _ints[j];
            Reverse(u);
            Reverse(v);
            _ints[i] = v;
            _ints[j] = u;
            i++;
            j--;
        }

        if (j == i)
        {
            unsigned int t = _ints[i];
            Reverse(t);
            _ints[i] = t;
        }
    }

    // Set all bits to one
    void Set(void)
    {
        memset(_ints, 0xFF, _lenInt * sizeof(int));
        // The bits of the last integer have already been flipped.
        // Just reset its higher non-used bits to zero.
        if (_y > 0)
            _ints[_lenInt - 1] &= (0x1 << _y) - 1;
    }

    // Set one bit position to one
    void Set(size_t position)
    {
        int x, y;
        Position(position, &x, &y);
        _ints[x] |= 0x1 << y;
    }

    // Test if one bit position is set
    bool Test(size_t position) const
    {
        int x, y;
        Position(position, &x, &y);
        return 0x1 & (_ints[x] >> y);
    }

    string ToString(void)
    {
        ostringstream oss;

        if (nullptr != _ints)
        {
            bool skip = true;
            for (int j = 28; j >= 0; j -= 4)
            {
                unsigned int c = 0xF & (_ints[_lenInt - 1] >> j);
                if (skip && _y > 0 && j >= _y && c == 0)
                    continue;
                skip = false;
                oss << hex << c;
            }
            for (int i = _lenInt - 2; i >= 0; i--)
            {
                for (int j = 28; j >= 0; j -= 4)
                {
                    oss << hex << (0xF & (_ints[i] >> j));
                }
            }
        }

        return oss.str();
    }
};

// This implementation uses a vector as the container and the methods
// from <algorithm> to manipulate it. The default template parameter
// Compare is less<T>, which creates a maximum heap. If Compare is
// greater<T>, then it creates a minimum heap. To track top n numbers
// in a set, create a min heap of size n, enumerate each number and
// push it into the heap if it is greater than the root of heap.
// To track bottom n numbers in a set, create a max heap of size n,
// enumerate each number and push it into the heap if it is smaller
// than the root of heap.
template <class T, class Compare = less<T>>
class Heap
{
private:
    vector<T> _elements;
    Compare _compare;
    unsigned long _capacity;

    // Initialize the heap using a given vector
    // If the number of elements in the vector is greater than the
    // heap capacity, then only top (for min heap) or botton elements
    // (for max heap) will be pushed into the heap.
    void Init(const vector<T> &input)
    {
        unsigned long l = min<unsigned long>(_capacity, input.size());
        for (unsigned long i = 0; i < l; i++)
        {
            _elements.push_back(input[i]);
        }

        make_heap(_elements.begin(), _elements.end(), _compare);

        for (unsigned long i = l; i < input.size() - 1; i++)
        {
            if (_compare(input[i], Top()))
            {
                Pop();
                Push(input[i]);
            }
        }
    }

public:
    // Create a heap that can contain upto ULONG_MAX elements
    Heap(void) : _capacity(ULONG_MAX) {}

    // Create a heap of specified capacity
    Heap(unsigned long cap) : _capacity(cap) {}

    // Create a heap using an existing container
    Heap(const vector<T> &input)
    {
        _capacity = ULONG_MAX;
        Init(input);
    }

    // Create a heap of specified capacity using an existing container
    Heap(const vector<T> &input, unsigned long cap)
    {
        _capacity = cap;
        Init(input);
    }

    ~Heap(void) {}

    // Return true if this is really a heap
    bool IsHeap(void)
    {
        return is_heap(_elements.begin(), _elements.end(), _compare);
    }

    // Pop the top of heap
    T Pop(void)
    {
        if (_elements.size() == 0)
            throw runtime_error("Heap is empty.");

        // pop_heap moves the top to the end of container
        pop_heap(_elements.begin(), _elements.end(), _compare);

        // Get a reference to the popped top element
        T &value = _elements.back();

        // Remvoe the popped to element from the heap
        _elements.pop_back();

        return value;
    }

    // Try to push an element into the heap
    // Return true if an element is pushed into the heap successfully.
    // Return false if the heap is at capacity and the element does
    // not fit into the heap.
    bool Push(const T &e)
    {
        while (_elements.size() >= _capacity)
        {
            // Check against the top element since it is the gate to the heap
            if (_compare(e, Top()))
            {
                // Pop the top to make a room for the element
                Pop();
            }
            else
            {
                // The element does not fit in the heap
                return false;
            }
        }

        // Add the element to the end of vector
        _elements.push_back(e);

        // push_heap moves the end of vector into the heap
        push_heap(_elements.begin(), _elements.end(), _compare);

        return true;
    }

    // Get the number of elements in the heap
    size_t Size(void) { return _elements.size(); }

    // Get a reference to the top of heap
    const T &Top(void) { return _elements.front(); }
};

template <class Compare = std::less<>>
class YoungTableau
{
    // A Young tableau is an m x n matrix such that the entries of
    // each row are in sorted order from left to right and the entries
    // of each column are in sorted order from top to bottom. A Young
    // tableau is like a heap and can be used to implement a priority queue.

    // comp is a binary function returning a boolean value.
    // If comp(first, second) returns true, then the first input should be
    // to the right or the bottom of the second input.
    // Default comp is std::less, which forms a max heap.

private:
    static Compare s_comp;

    // Determine whether lhs is lower than rhs
    static bool lower(int lhs, int rhs) { return s_comp(lhs, rhs); }

    // Determine whether lhs is equal to rhs
    static bool equal(int lhs, int rhs) { return !s_comp(lhs, rhs) && !s_comp(rhs, lhs); }

    // Determine whether lhs is higher than rhs
    static bool higher(int lhs, int rhs) { return s_comp(rhs, lhs); }

public:
    static void PushUp(vector<vector<int>> &tableau, size_t i, size_t j)
    {
        while (true)
        {
            size_t mi = i;
            size_t mj = j;
            int m = tableau[mi][mj];

            // Check against the upper
            if (i > 0 && lower(tableau[i - 1][j], m))
            {
                mi = i - 1;
                mj = j;
                m = tableau[mi][mj];
            }

            // Check against the left
            if (j > 0 && lower(tableau[i][j - 1], m))
            {
                mi = i;
                mj = j - 1;
                m = tableau[mi][mj];
            }

            if (mi == i && mj == j)
                break;

            swap(tableau[i][j], tableau[mi][mj]);
            i = mi;
            j = mj;
        }
    }

    static void PushDown(vector<vector<int>> &tableau, size_t i, size_t j)
    {
        while (true)
        {
            size_t mi = i;
            size_t mj = j;
            int m = tableau[mi][mj];

            // Check against the below
            if (i + 1 < tableau.size() && lower(m, tableau[i + 1][j]))
            {
                mi = i + 1;
                mj = j;
                m = tableau[mi][mj];
            }

            // Check against the right
            if (j + 1 < tableau[i].size() && lower(m, tableau[i][j + 1]))
            {
                mi = i;
                mj = j + 1;
                m = tableau[mi][mj];
            }

            if (mi == i && mj == j)
                break;

            swap(tableau[i][j], tableau[mi][mj]);
            i = mi;
            j = mj;
        }
    }

    static void Create(vector<vector<int>> &tableau)
    {
        // Complexity is sum(i + j) for i in [0, m - 1] and j in [0, n - 1],
        // which is O(mn(m+n))
        for (size_t i = 0; i < tableau.size(); i++)
        {
            for (size_t j = 0; j < tableau[i].size(); j++)
            {
                PushUp(tableau, i, j);
            }
        }
    }

    static void Create2(vector<vector<int>> &tableau)
    {
        // Complecity is m * lg(n) + n * lg(m)

        for (size_t i = 0; i < tableau.size(); i++)
        {
            sort(tableau[i].begin(), tableau[i].end(), higher);
        }

        for (size_t i = 0; i < tableau[0].size(); i++)
        {
            // Sort column i
            MergeSort(tableau, i, higher);
        }
    }

    static bool Verify(vector<vector<int>> &tableau)
    {
        for (size_t i = 0; i < tableau.size(); i++)
        {
            for (size_t j = 0; j < tableau[i].size(); j++)
            {
                if (j + 1 < tableau[i].size() && lower(tableau[i][j], tableau[i][j + 1]))
                {
                    return false;
                }

                if (i + 1 < tableau.size() && j < tableau[i + 1].size() && lower(tableau[i][j], tableau[i + 1][j]))
                {
                    return false;
                }
            }
        }

        return true;
    }

    static pair<int, int> Search(vector<vector<int>> &tableau, const int &value)
    {
        // Complexit is O(m + n)
        int i = 0;
        int j = tableau[0].size() - 1;

        while (i < (int)tableau.size() && j >= 0)
        {
            if (lower(value, tableau[i][j]))
                i++;
            else if (lower(tableau[i][j], value))
                j--;
            else
                return make_pair(i, j);
        }

        return make_pair(-1, -1);
    }

    static pair<int, int> Search2(vector<vector<int>> &tableau, const int &value)
    {
        function<pair<int, int>(int, int, int, int)>
            search = [&](int i0, int j0, int i1, int j1) -> pair<int, int> {
            if (i0 == i1)
            {
                int j = BinarySearch(tableau[i0], value, j0, j1, true, higher);
                if (j != -1)
                    return make_pair(i0, j);
            }
            else if (j0 == j1)
            {
                // Search column j0
                int i = BinarySearch(tableau, j0, value, i0, i1, true, higher);
                if (i != -1)
                    return make_pair(i, j0);
            }
            else
            {
                int i = (i0 + i1) >> 1;

                // Find the first j such that value should be to the left of tableau[i][j]
                int j = FindInsertPoint(tableau[i], value, j0, j1, true, higher);

                if (j <= j1 && equal(tableau[i][j], value))
                    return make_pair(i, j);

                if (j <= j1 && i0 < i)
                {
                    // search top-right area
                    auto p = search(i0, j, i - 1, j1);
                    if (p.first != -1 && p.second != -1)
                        return p;
                }

                if (j0 < j && i < i1)
                {
                    // search bottom-left area
                    return search(i + 1, j0, i1, j - 1);
                }
            }
            return make_pair(-1, -1);
        };

        return search(0, 0, tableau.size() - 1, tableau[tableau.size() - 1].size() - 1);
    }

    // Count elements are to the top-left area of the input value.
    static unsigned long CountHigherThan(vector<vector<int>> &tableau, const int &value)
    {
        function<unsigned long(size_t, size_t, size_t, size_t)>
            count = [&](size_t i0, size_t j0, size_t i1, size_t j1) -> unsigned long {
            size_t i = FindInsertPoint(
                value,
                i0,
                i0 + min(i1 - i0, j1 - j0),
                [&](size_t k) -> int { return tableau[k][j0 + k - i0]; },
                true,
                higher);
            size_t j = j0 + i - i0;

            if (i == i0 && j == j0)
                return 0;

            unsigned long c = (i - i0) * (j - j0);

            if (j <= j1)
                c += count(i0, j, i - 1, j1);

            if (i <= i1)
                c += count(i, j0, i1, j - 1);

            return c;
        };

        return count(0, 0, tableau.size() - 1, tableau[0].size() - 1);
    }

    // Count elements are to the top-left area of the input value.
    static unsigned long CountHigherThan2(vector<vector<int>> &tableau, const int &value)
    {
        unsigned long c = 0;
        int last = -1;
        for (size_t i = 0; i < tableau.size(); i++)
        {
            if (last == -1)
                last = tableau[i].size();
            if (last == 0)
                break;
            last = FindInsertPoint(tableau[i], value, 0, last - 1, true, higher);
            c += last;
        }
        return c;
    }

    // Count elements are to the top-left area of the input value.
    static unsigned long CountHigherThan3(vector<vector<int>> &tableau, const int &value)
    {
        unsigned long c = 0;
        int rows = tableau.size();
        int cols = tableau[0].size();

        for (int j = 0; j < min(rows, cols); j++)
        {
            unsigned int t = 0;
            for (int i = 0; i <= j; i++)
            {
                if (lower(value, tableau[i][j - i]))
                    t++;
            }
            if (t == 0)
                return c;
            else
                c += t;
        }

        if (rows <= cols)
        {
            //  +---------+
            //  | /      /|
            //  |/      / |
            //  +---------+
            for (int j = rows; j < cols; j++)
            {
                unsigned int t = 0;
                for (int i = 0; i < rows; i++)
                {
                    if (lower(value, tableau[i][j - i]))
                        t++;
                }
                if (t == 0)
                    return c;
                else
                    c += t;
            }

            for (int j = cols; j < cols + rows - 1; j++)
            {
                unsigned int t = 0;
                for (int i = j - cols + 1; i < rows; i++)
                {
                    if (lower(value, tableau[i][j - i]))
                        t++;
                }
                if (t == 0)
                    return c;
                else
                    c += t;
            }
        }
        else
        {
            //  +---+
            //  |  /|
            //  | / |
            //  |/ /|
            //  | / |
            //  |/  |
            //  +---+
            for (int i = cols; i < rows; i++)
            {
                unsigned int t = 0;
                for (int j = 0; j < cols; j++)
                {
                    if (lower(value, tableau[i - j][j]))
                        t++;
                }
                if (t == 0)
                    return c;
                else
                    c += t;
            }

            for (int i = rows; i < rows + cols - 1; i++)
            {
                unsigned int t = 0;
                for (int j = i - rows + 1; j < cols; j++)
                {
                    if (lower(value, tableau[i - j][j]))
                        t++;
                }
                if (t == 0)
                    return c;
                else
                    c += t;
            }
        }

        return c;
    }

    // Count elements are to the top-left area of the input value.
    static unsigned long CountHigherThan4(vector<vector<int>> &tableau, const int &value)
    {
        unsigned long c = 0;
        size_t rows = tableau.size();
        size_t cols = tableau[0].size();
        size_t topLefti = 0;
        size_t topLeftj = 0;
        size_t bottomRighti = 0;
        size_t bottomRightj = 0;

        while (topLefti < rows)
        {
            unsigned int t = 0;
            for (size_t i = topLefti; i <= bottomRighti; i++)
            {
                if (lower(value, tableau[i][topLeftj - i + topLefti]))
                    t++;
            }
            if (t == 0)
                return c;
            else
                c += t;
            topLefti = topLeftj + 1 < cols ? topLefti : topLefti + 1;
            topLeftj = topLeftj + 1 < cols ? topLeftj + 1 : topLeftj;
            bottomRightj = bottomRighti + 1 < rows ? bottomRightj : bottomRightj + 1;
            bottomRighti = bottomRighti + 1 < rows ? bottomRighti + 1 : bottomRighti;
        }

        return c;
    }

    // Find the i-th number in it.
    static int SearchByOrder(const vector<vector<int>> &tableau, int i)
    {
        // Option 1: Heap extract-max i times
        // Option 2: Use CountHigherThan with BinarySearch
        return -1;
    }
};

class LRUCache
{
private:
    int _capacity;

    struct Item
    {
        int key;
        int value;
        struct Item *prev;
        struct Item *next;
        Item(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    } * head, *tail;

    map<int, struct Item *> keys;

    void MoveFront(struct Item *p)
    {
        if (p == this->head)
            return;
        if (p == this->tail)
        {
            this->tail = p->prev;
            this->tail->next = nullptr;
        }
        else
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        p->next = this->head;
        this->head->prev = p;
        p->prev = nullptr;
        this->head = p;
    }

public:
    LRUCache(int capacity)
        : _capacity(capacity), head(nullptr), tail(nullptr)
    {
    }

    ~LRUCache(void)
    {
        while (this->head != nullptr)
        {
            struct Item *p = this->head;
            this->head = this->head->next;
            delete p;
        }
    }

    int Get(int key)
    {
        if (this->keys.find(key) == this->keys.end())
        {
            return -1;
        }
        else
        {
            struct Item *p = this->keys[key];
            MoveFront(p);
            return p->value;
        }
    }

    void Set(int key, int value)
    {
        struct Item *p;
        if (this->keys.find(key) == this->keys.end())
        {
            if ((int)this->keys.size() == this->_capacity)
            {
                int k = this->tail->key;
                if (this->head == this->tail)
                {
                    delete this->head;
                    this->head = nullptr;
                    this->tail = nullptr;
                }
                else
                {
                    p = this->tail;
                    this->tail = p->prev;
                    this->tail->next = nullptr;
                    delete p;
                }
                this->keys.erase(k);
            }
            p = new struct Item(key, value);
            if (this->head == nullptr)
            {
                this->head = p;
                this->tail = p;
            }
            else
            {
                p->next = this->head;
                this->head->prev = p;
                this->head = p;
            }
            this->keys[key] = p;
        }
        else
        {
            // Whether or not to change the value,
            // it counts as an access.
            p = this->keys[key];
            p->value = value;
            MoveFront(p);
        }
    }
};

template <class T>
class Array1D
{
private:
    T *_array;
    size_t _length;
    void Check(unsigned int index)
    {
        if (!(0 <= index && index < _length))
        {
            throw invalid_argument(String::Format("Invalid indices [%d]", index));
        }
        if (_array == nullptr)
        {
            throw logic_error(String::Format("Array uninitialized"));
        }
    }

public:
    Array1D(size_t length)
    {
        if (0 < length)
        {
            _length = length;
            //size_t cb = _length * sizeof(T);
            //_array = (T *)malloc(cb);
            //memset(_array, 0, cb);

            // If T is a primitive type, e.g. int, the memory may not be initialized.
            // If T is an object, then the constructor handles initialization.
            _array = new T[_length];
        }
        else
        {
            _length = 0;
            _array = nullptr;
        }
    }

    ~Array1D(void)
    {
        if (_array != nullptr)
        {
            //free(_array);
            delete[] _array;
            _array = nullptr;
            _length = 0;
        }
    }

    const size_t Length(void) const { return _length; }

    T &operator[](unsigned int index)
    {
        Check(index);
        T &value = _array[index];
        return value;
    }

    const T &GetValue(unsigned int index)
    {
        Check(index);
        T &value = _array[index];
        return value;
    }

    void SetValue(unsigned int index, T value)
    {
        Check(index);
        _array[index] = value;
    }

    void Print(void) const
    {
        for (size_t i = 0; i < _length; i++)
        {
            cout << "\t" << i;
        }
        cout << endl;
        for (size_t i = 0; i < _length; i++)
        {
            cout << "\t" << _array[i];
        }
        cout << endl;
    }
};

template <class T>
class Array2D
{
private:
    T *_array;
    size_t _rows;
    size_t _cols;
    void Check(unsigned int row, unsigned int col)
    {
        if (!(0 <= row && row < _rows && 0 <= col && col < _cols))
        {
            throw invalid_argument(String::Format("Invalid indices [%d][%d]", row, col));
        }
        if (_array == nullptr)
        {
            throw logic_error(String::Format("Array uninitialized"));
        }
    }

public:
    Array2D(size_t rows, size_t cols)
    {
        if ((0 < rows) && (0 < cols))
        {
            _rows = rows;
            _cols = cols;
            //size_t cb = _rows * _cols * sizeof(T);
            //_array = (T *)malloc(cb);
            //memset(_array, 0, cb);

            // If T is a primitive type, e.g. int, the memory may not be initialized.
            // If T is an object, then the constructor handles initialization.
            _array = new T[_rows * _cols];
        }
        else
        {
            _rows = 0;
            _cols = 0;
            _array = nullptr;
        }
    }

    ~Array2D(void)
    {
        if (_array != nullptr)
        {
            //free(_array);
            delete[] _array;
            _array = nullptr;
            _rows = 0;
            _cols = 0;
        }
    }

    const size_t CountRows(void) const { return _rows; }

    const size_t CountCols(void) const { return _cols; }

    const T &GetValue(unsigned int row, unsigned int col)
    {
        Check(row, col);
        T &value = *(_array + row * _cols + col);
        return value;
    }

    void SetValue(unsigned int row, unsigned int col, T value)
    {
        Check(row, col);
        *(_array + row * _cols + col) = value;
    }

    T &Element(unsigned int row, unsigned int col)
    {
        Check(row, col);
        T &value = *(_array + row * _cols + col);
        return value;
    }

    void Print(void) const
    {
        for (size_t i = 0; i < _cols; i++)
        {
            cout << "\t" << i;
        }
        cout << endl;
        for (size_t i = 0; i < _rows; i++)
        {
            cout << i;
            for (size_t j = 0; j < _cols; j++)
            {
                cout << "\t" << *(_array + i * _cols + j);
            }
            cout << endl;
        }
        cout << endl;
    }
};

#if NULL

template <class T>
class ArrayMD
{
private:
    T *_array;          // _array[D_0][D_1][D_2]...[D_(n-1)]
    size_t _dimensions; // = n
    size_t *_sizes;     // = {D_0,       D_1,       D_2,       ..., D_(n-2),     D_(n-1)}
    size_t *_volumes;   // = {M(1, n-1), M(2, n-1), M(3, n-1), ..., M(n-1, n-1), 1}, where M(i, j) = D_i * D_(i+1) *...*D_j
    size_t _size;       // = M(0, n-1) = D_0 *...* D_(n-1)
    void Check(size_t dimension);

public:
    ArrayMD(size_t _dimensions, ...);
    ~ArrayMD(void);
    const size_t Size(size_t dimension) const
    {
        Check(dimension);
        return _sizes[dimension];
    }
    T *Element(size_t _dimensions, ...);
    void Print(void) const;
};

template <class T>
void ArrayMD<T>::Check(size_t dimension)
{
    if (dimension > _dimensions)
    {
        throw invalid_argument(String::Format("Invalid dimension %d", dimension));
    }
    if (_array == NULL)
    {
        throw logic_error(String::Format("Array uninitialized"));
    }
}

template <class T>
ArrayMD<T>::ArrayMD(size_t dimensions, ...)
{
    _dimensions = dimensions;
    _sizes = new size_t[_dimensions];
    _size = 1;
    va_list args;
    va_start(args, _dimensions);
    for (size_t i = 0; i < _dimensions; i++)
    {
        int t = va_arg(args, int); // This fails to get the value. Don't know why
        cout << t << " ";
        _sizes[i] = t;
        _size *= _sizes[i];
    }
    va_end(args);
    if (_size > 0)
    {
        _array = new T[_size];
        _volumes = new size_t[_dimensions];
        _volumes[_dimensions - 1] = 1;
        for (int i = _dimensions - 2; i >= 0; i--)
        {
            _volumes[i] = _sizes[i + 1] * _volumes[i + 1];
        }
    }
    else
    {
        _array = NULL;
        delete[] _sizes;
        _sizes = NULL;
    }
}

template <class T>
ArrayMD<T>::~ArrayMD(void)
{
    if (_array != NULL)
    {
        delete[] _array;
        _array = NULL;
    }
    if (_sizes != NULL)
    {
        delete[] _sizes;
        _sizes = NULL;
    }
    if (_volumes != NULL)
    {
        delete[] _volumes;
        _volumes = NULL;
    }
}

template <class T>
T *ArrayMD<T>::Element(size_t dimensions, ...)
{
    Check(dimensions);
    T *p = _array;
    va_list args;
    va_start(args, dimensions);
    for (size_t i = 0; i < _dimensions; i++)
    {
        p += (i * _volumes[i]);
    }
    va_end(args);
    return p;
}

template <class T>
void ArrayMD<T>::Print(void) const
{
    for (size_t i = 0; i < _dimensions; i++)
    {
        cout << "\t" << i;
    }
    cout << endl;
    for (size_t i = 0; i < _dimensions; i++)
    {
        cout << "\t" << _sizes[i];
    }
    cout << endl;
    for (size_t i = 0; i < _dimensions; i++)
    {
        cout << "\t" << _volumes[i];
    }
    cout << endl;
}
#endif

template <class T>
class Matrix
{
protected:
    size_t rows;
    size_t cols;
    T *buffer;
    // Default constructor for inheritance
    Matrix(void) : rows(0), cols(0), buffer(nullptr) {}

public:
    Matrix(size_t rows, size_t cols)
    {
        if (rows == 0)
            throw invalid_argument(String::Format("Invalid rows %d", rows));
        if (cols == 0)
            throw invalid_argument(String::Format("Invalid cols %d", cols));
        this->rows = rows;
        this->cols = cols;
        size_t c = rows * cols;
        this->buffer = new T[c];
        memset(this->buffer, 0, c * sizeof(T));
    }

    Matrix(const Matrix &matrix)
    {
        this->rows = matrix.rows;
        this->cols = matrix.cols;
        size_t c = this->rows * this->cols;
        this->buffer = new T[c];
        memcpy(this->buffer, matrix.buffer, c * sizeof(T));
    }

    Matrix &operator=(const Matrix &matrix)
    {
        if (this != &matrix)
        {
            if (this->buffer != nullptr)
            {
                delete[] this->buffer;
                this->buffer = nullptr;
            }
            this->rows = matrix.rows;
            this->cols = matrix.cols;
            size_t c = this->rows * this->cols;
            this->buffer = new T[c];
            memcpy(this->buffer, matrix.buffer, c * sizeof(T));
        }
        return *this;
    }

    Matrix(Matrix &&matrix)
    {
        this->rows = matrix.rows;
        this->cols = matrix.cols;
        this->buffer = matrix.buffer;
        matrix.rows = 0;
        matrix.cols = 0;
        matrix.buffer = nullptr;
    }

    Matrix &operator=(Matrix &&matrix)
    {
        if (this != &matrix)
        {
            if (this->buffer != nullptr)
            {
                delete[] this->buffer;
                this->buffer = nullptr;
            }
            this->rows = matrix.rows;
            this->cols = matrix.cols;
            this->buffer = matrix.buffer;
            matrix.rows = 0;
            matrix.cols = 0;
            matrix.buffer = nullptr;
        }
        return *this;
    }

    virtual ~Matrix(void)
    {
        if (this->buffer != nullptr)
        {
            delete[] this->buffer;
            this->buffer = nullptr;
            this->rows = 0;
            this->cols = 0;
        }
    }

    virtual T &operator()(size_t r, size_t c)
    {
        if (r >= this->rows)
            throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
        if (c >= this->cols)
            throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
        T &value = *(this->buffer + r * this->cols + c);
        return value;
    }

    virtual T operator()(size_t r, size_t c) const { return this->operator()(r, c); }

    const size_t Rows(void) const { return this->rows; }
    const size_t Cols(void) const { return this->cols; }
};

template <class T>
class LowerTriangularMatrix : public Matrix<T>
{
public:
    LowerTriangularMatrix(size_t rows, size_t cols)
        : Matrix<T>()
    {
        if (rows == 0)
            throw invalid_argument(String::Format("Invalid rows %d", rows));
        if (cols == 0)
            throw invalid_argument(String::Format("Invalid cols %d", cols));
        this->rows = rows;
        this->cols = cols;
        // if rows <= cols
        //   rows + ... + 2 + 1 = (rows + 1) * rows / 2
        // if rows > cols
        //   rows + (rows - 1) + ... + (rows - (cols - 1)) = rows * cols - (cols - 1) * cols / 2
        size_t c;
        if (rows <= cols)
            c = ((rows + 1) * rows) >> 1;
        else
            c = rows * cols - (((cols - 1) * cols) >> 1);
        this->buffer = new T[c];
        memset(this->buffer, 0, c * sizeof(T));
    }

    LowerTriangularMatrix(const LowerTriangularMatrix &other)
    {
        this->rows = other.rows;
        this->cols = other.cols;
        size_t c;
        if (this->rows <= this->cols)
            c = ((this->rows + 1) * this->rows) >> 1;
        else
            c = this->rows * this->cols - (((this->cols - 1) * this->cols) >> 1);
        this->buffer = new T[c];
        memcpy(this->buffer, other.buffer, c * sizeof(T));
    }

    LowerTriangularMatrix &operator=(LowerTriangularMatrix &other)
    {
        if (this != &other)
        {
            if (this->buffer != nullptr)
            {
                delete[] this->buffer;
                this->buffer = nullptr;
            }
            this->rows = other.rows;
            this->cols = other.cols;
            size_t c;
            if (this->rows <= this->cols)
                c = ((this->rows + 1) * this->rows) >> 1;
            else
                c = this->rows * this->cols - (((this->cols - 1) * this->cols) >> 1);
            this->buffer = new T[c];
            memcpy(this->buffer, other.buffer, c * sizeof(T));
        }
        return *this;
    }

    LowerTriangularMatrix(LowerTriangularMatrix &&other)
    {
        this->rows = other.rows;
        this->cols = other.cols;
        this->buffer = other.buffer;
        other.rows = 0;
        other.cols = 0;
        other.buffer = nullptr;
    }

    LowerTriangularMatrix &operator=(LowerTriangularMatrix &&other)
    {
        if (this != &other)
        {
            if (this->buffer != nullptr)
            {
                delete[] this->buffer;
                this->buffer = nullptr;
            }
            this->rows = other.rows;
            this->cols = other.cols;
            this->buffer = other.buffer;
            other.rows = 0;
            other.cols = 0;
            other.buffer = nullptr;
        }
        return *this;
    }

    ~LowerTriangularMatrix(void) {}

    T &operator()(size_t r, size_t c)
    {
        if (r >= this->rows)
            throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
        if (c >= this->cols)
            throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
        if (r < c)
            throw invalid_argument(String::Format("r %d is smaller than c %d", r, c));
        // if rows <= cols
        //   1 + 2 + ... + i + j = (i + 1) * i / 2 + j
        // if rows > cols
        //   if i <= cols - 1
        //     1 + 2 + ... + i + j = (i + 1) * i / 2 + j
        //   if cols <= i <= rows - 1
        //     1 + 2 + ... + cols + ((i - 1) - (cols - 1)) * cols  + j = (cols + 1) * cols / 2 + (i - cols) * cols + j
        int index;
        if (this->cols <= r && r < this->rows)
            index = (((this->cols + 1) * this->cols) >> 1) + (r - this->cols) * this->cols + c;
        else
            index = (((r + 1) * r) >> 1) + c;
        T &value = *(this->buffer + index);
        return value;
    }

    T operator()(size_t r, size_t c) const
    {
        if (r >= this->rows)
            throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
        if (c >= this->cols)
            throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
        if (r < c)
        {
            T d;
            memset(&d, 0, sizeof(T));
            return d;
        }
        return this->operator()(r, c);
    }
};

template <class T>
class UpperTriangularMatrix : public Matrix<T>
{
public:
    UpperTriangularMatrix(size_t rows, size_t cols)
        : Matrix<T>()
    {
        if (rows == 0)
            throw invalid_argument(String::Format("Invalid rows %d", rows));
        if (cols == 0)
            throw invalid_argument(String::Format("Invalid cols %d", cols));
        this->rows = rows;
        this->cols = cols;

        // if rows <= cols
        //   cols + (cols - 1) + ... + (cols - (rows - 1))) = cols * rows - (rows - 1) * rows / 2
        // if rows > cols
        //   cols + (cols - 1) + ... + 2 + 1 = (cols + 1) * cols / 2
        size_t c;
        if (rows > cols)
            c = ((cols + 1) * cols) >> 1;
        else
            c = cols * rows - (((rows - 1) * rows) >> 1);
        this->buffer = new T[c];
        memset(this->buffer, 0, c * sizeof(T));
    }

    UpperTriangularMatrix(const UpperTriangularMatrix &other)
    {
        this->rows = other.rows;
        this->cols = other.cols;
        size_t c;
        if (this->rows > this->cols)
            c = ((this->cols + 1) * this->cols) >> 1;
        else
            c = this->cols * this->rows - (((this->rows - 1) * this->rows) >> 1);
        this->buffer = new T[c];
        memcpy(this->buffer, other.buffer, c * sizeof(T));
    }

    UpperTriangularMatrix &operator=(UpperTriangularMatrix &other)
    {
        if (this != &other)
        {
            if (this->buffer != nullptr)
            {
                delete[] this->buffer;
                this->buffer = nullptr;
            }
            this->rows = other.rows;
            this->cols = other.cols;
            size_t c;
            if (this->rows > this->cols)
                c = ((this->cols + 1) * this->cols) >> 1;
            else
                c = this->cols * this->rows - (((this->rows - 1) * this->rows) >> 1);
            this->buffer = new T[c];
            memcpy(this->buffer, other.buffer, c * sizeof(T));
        }
        return *this;
    }

    UpperTriangularMatrix(UpperTriangularMatrix &&other)
    {
        this->rows = other.rows;
        this->cols = other.cols;
        this->buffer = other.buffer;
        other.rows = 0;
        other.cols = 0;
        other.buffer = nullptr;
    }

    UpperTriangularMatrix &operator=(UpperTriangularMatrix &&other)
    {
        if (this != &other)
        {
            if (this->buffer != nullptr)
            {
                delete[] this->buffer;
                this->buffer = nullptr;
            }
            this->rows = other.rows;
            this->cols = other.cols;
            this->buffer = other.buffer;
            other.rows = 0;
            other.cols = 0;
            other.buffer = nullptr;
        }
        return *this;
    }

    ~UpperTriangularMatrix(void) {}

    T &operator()(size_t r, size_t c)
    {
        if (r >= this->rows)
            throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
        if (c >= this->cols)
            throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
        if (r > c)
            throw invalid_argument(String::Format("r %d is larger than c %d", r, c));
        // cols + (cols - 1) + ... + (cols - (i - 1)) + j - i
        // = cols * i - (i - 1) * i / 2 + j - i
        int index = this->cols * r - (((r - 1) * r) >> 1) + c - r;
        T &value = *(this->buffer + index);
        return value;
    }

    T operator()(size_t r, size_t c) const
    {
        if (r >= this->rows)
            throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
        if (c >= this->cols)
            throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
        if (r > c)
        {
            T d;
            memset(&d, 0, sizeof(T));
            return d;
        }
        return this->operator()(r, c);
    }
};

// Multi-Radix Integer
// Digits:
//    d_{n-1} d_{n-2} ...... d_i ...... d_2 d_1 d_0
// Bases:
//    b_{n-1} b_{n-2} ...... b_i ...... b_2 b_1 b_0
// 0 <= d_i < b_i
class MRInteger
{
private:
    unsigned int *_bases;
    // 0 <= _digits[i] < _bases[i]
    unsigned int *_digits;
    // Number of digits
    unsigned int _length;
    // maximum number of integers can be represented
    unsigned long _max;
    // position: n-1, n-2, ..., 3, 2, 1, 0
    // Add one to the sub MRInteger containing digits from position to 0.
    // Return 1 if need to increase the digit at position+1 by 1,
    // and 0 otherwise.
    unsigned int AddOne(unsigned int position)
    {
        if (0 == position)
        {
            _digits[position] = (1 + _digits[position]) % _bases[position];
            return (0 == _digits[position]) ? 1 : 0;
        }
        else
        {
            if (1 == AddOne(position - 1))
            {
                _digits[position] = (1 + _digits[position]) % _bases[position];
                return (0 == _digits[position]) ? 1 : 0;
            }
            else
            {
                return 0;
            }
        }
    }

public:
    MRInteger(const unsigned int *bases, unsigned int length)
        : _bases(nullptr), _digits(nullptr), _length(0), _max(0)
    {
        if (bases == nullptr)
            throw invalid_argument("bases is nullptr");
        if (length <= 0)
            throw invalid_argument(String::Format("length %d is invalid", length));
        for (unsigned int i = 0; i < length; i++)
        {
            if (bases[i] <= 0)
            {
                throw invalid_argument(String::Format("bases[%d] %d is invalid", i, bases[i]));
            }
        }

        _bases = new unsigned int[length];
        _digits = new unsigned int[length];
        _length = length;
        _max = 1;
        for (unsigned int i = 0; i < length; i++)
        {
            _bases[i] = bases[i];
            _digits[i] = 0;
            _max = _max * bases[i];
        }
    }

    MRInteger(const unsigned int *bases, const unsigned int *digits, unsigned int length)
        : _bases(nullptr), _digits(nullptr), _length(0), _max(0)
    {
        if (bases == nullptr)
            throw invalid_argument("bases is nullptr");
        if (digits == nullptr)
            throw invalid_argument("digits is nullptr");
        if (length <= 0)
            throw invalid_argument(String::Format("length %d is invalid", length));
        for (unsigned int i = 0; i < length; i++)
        {
            if (bases[i] <= 0)
            {
                throw invalid_argument(String::Format("bases[%d] %d is invalid", i, bases[i]));
            }
        }

        _bases = new unsigned int[length];
        _digits = new unsigned int[length];
        _length = length;
        _max = 1;
        for (unsigned int i = 0; i < length; i++)
        {
            _bases[i] = bases[i];
            _digits[i] = digits[i] % _bases[i];
            _max = _max * bases[i];
        }
    }

    // Copy constructor
    MRInteger(const MRInteger &mrint)
        : _bases(nullptr), _digits(nullptr), _length(0), _max(0)
    {
        if (_bases != nullptr)
        {
            delete[] _bases;
            _bases = nullptr;
        }

        if (_digits != nullptr)
        {
            delete[] _digits;
            _digits = nullptr;
        }

        _bases = new unsigned int[mrint._length];
        _digits = new unsigned int[mrint._length];
        _length = mrint._length;
        _max = mrint._max;
        for (unsigned int i = 0; i < _length; i++)
        {
            _bases[i] = mrint._bases[i];
            _digits[i] = mrint._digits[i];
        }
    }

    // Move constructor
    MRInteger(MRInteger &&mrint)
        : _bases(nullptr), _digits(nullptr), _length(0), _max(0)
    {
        _bases = mrint._bases;
        mrint._bases = nullptr;
        _digits = mrint._digits;
        mrint._digits = nullptr;
        _length = mrint._length;
        mrint._length = 0;
        _max = mrint._max;
        mrint._max = 0;
    }

    ~MRInteger(void)
    {
        if (_bases != nullptr)
        {
            delete[] _bases;
            _bases = nullptr;
        }

        if (_digits != nullptr)
        {
            delete[] _digits;
            _digits = nullptr;
        }

        _length = 0;
        _max = 0;
    }

    // Set this MRInteger using the given digits array.
    void Set(const unsigned int *digits, unsigned int length)
    {
        // The number of elements to use from the digits array
        // is the minimum of the length and the MRInteger length.
        unsigned int l = length < this->_length ? length : this->_length;

        for (unsigned int i = 0; i < l; i++)
        {
            _digits[i] = digits[i] % _bases[i];
        }

        for (unsigned int i = l; i < this->_length; i++)
        {
            _digits[i] = 0;
        }
    }

    void Reset(void)
    {
        for (unsigned int i = 0; i < _length; i++)
        {
            _digits[i] = 0;
        }
    }

    // Copy asignment
    const MRInteger &operator=(const MRInteger &mrint)
    {
        if (this != &mrint)
        {
            delete[] _bases;
            _bases = new unsigned int[mrint._length];
            delete[] _digits;
            _digits = new unsigned int[mrint._length];
            _length = mrint._length;
            _max = mrint._max;
            for (unsigned int i = 0; i < _length; i++)
            {
                _bases[i] = mrint._bases[i];
                _digits[i] = mrint._digits[i];
            }
        }

        return *this;
    }

    // Move assignment
    const MRInteger &operator=(MRInteger &&mrint)
    {
        if (this != &mrint)
        {
            delete[] _bases;
            _bases = mrint._bases;
            mrint._bases = nullptr;
            delete[] _digits;
            _digits = mrint._digits;
            mrint._digits = nullptr;
            _length = mrint._length;
            mrint._length = 0;
            _max = mrint._max;
            mrint._max = 0;
        }

        return *this;
    }

    // ++ MRInteger
    const MRInteger &operator++(void)
    {
        AddOne(_length - 1);
        return *this;
    }

    // MRInteger ++
    const MRInteger operator++(int)
    {
        MRInteger mrint(*this);
        ++*this;
        return mrint;
    }

    bool operator==(const MRInteger &mrint) const
    {
        int minLength = (int)this->_length;
        if (this->_length > mrint._length)
        {
            minLength = mrint._length;
            for (int i = (int)this->_length - 1; i >= (int)mrint._length; i--)
            {
                if (this->_digits[i] != 0)
                {
                    // this has more digits and one of them is not zero
                    return false;
                }
            }
        }
        else if (this->_length < mrint._length)
        {
            for (int i = (int)mrint._length - 1; i >= (int)this->_length; i--)
            {
                if (mrint._digits[i] != 0)
                {
                    // mrint has more digits and one of them is not zero
                    return false;
                }
            }
        }

        // Now this and mrint either have the same length,
        // or have different lengh but the extra digits are zeros.
        for (int i = minLength - 1; i >= 0; i--)
        {
            if (this->_digits[i] != mrint._digits[i])
            {
                // this != mrint
                return false;
            }
        }

        return true;
    }

    bool operator!=(const MRInteger &mrint) const { return !((*this) == mrint); }

    bool operator<(const MRInteger &mrint) const
    {
        int minLength = (int)this->_length;
        if (this->_length > mrint._length)
        {
            minLength = mrint._length;
            for (int i = (int)this->_length - 1; i >= (int)mrint._length; i--)
            {
                if (this->_digits[i] > 0)
                {
                    // this has more digits and one of them is greater than zero
                    return false;
                }
            }
        }
        else if (this->_length < mrint._length)
        {
            for (int i = (int)mrint._length - 1; i >= (int)this->_length; i--)
            {
                if (mrint._digits[i] > 0)
                {
                    // mrint has more digits and one of them is greater than zero
                    return true;
                }
            }
        }

        for (int i = minLength - 1; i >= 0; i--)
        {
            if (this->_digits[i] > mrint._digits[i])
            {
                // this > mrint
                return false;
            }
            else if (this->_digits[i] < mrint._digits[i])
            {
                // this < mrint
                return true;
            }
        }

        // this == mrint
        return false;
    }

    bool operator>=(const MRInteger &mrint) const { return !((*this) < mrint); }

    bool operator>(const MRInteger &mrint) const
    {
        int minLength = (int)this->_length;
        if (this->_length > mrint._length)
        {
            minLength = mrint._length;
            for (int i = (int)this->_length - 1; i >= (int)mrint._length; i--)
            {
                if (this->_digits[i] > 0)
                {
                    // this has more digits and one of them is greater than zero
                    return true;
                }
            }
        }
        else if (this->_length < mrint._length)
        {
            for (int i = (int)mrint._length - 1; i >= (int)this->_length; i--)
            {
                if (mrint._digits[i] > 0)
                {
                    // mrint has more digits and one of them is greater than zero
                    return false;
                }
            }
        }

        for (int i = minLength - 1; i >= 0; i--)
        {
            if (this->_digits[i] < mrint._digits[i])
            {
                // this < mrint
                return false;
            }
            else if (this->_digits[i] > mrint._digits[i])
            {
                // this > mrint
                return true;
            }
        }

        // this == mrint
        return false;
    }

    bool operator<=(const MRInteger &mrint) const { return !((*this) > mrint); }

    // maximum number of integers can be represented
    const unsigned long Max(void) const { return _max; }

    const unsigned int Length(void) const { return _length; }

    const unsigned int operator[](unsigned int index) const
    {
        return _digits[index];
    }

    void Random(void)
    {
        for (unsigned int i = 0; i < this->_length; i++)
        {
            this->_digits[i] = rand() % this->_bases[i];
        }
    }
};

class PermutationGenerator
{
private:
    unsigned int _length;
    unsigned long long _totalCount;
    // Internal counter to track the permutation state.
    // It is a multiple-radix integer, where the base
    // of position i is i + 1.
    // 0 <= _counter[i] < i + 1
    unique_ptr<unsigned int[]> _counter;

    void IncreaseCounter(void)
    {
        for (unsigned int i = 0; i < _length; i++)
        {
            _counter[i] = (_counter[i] + 1) % (i + 1);
            if (_counter[i] != 0)
            {
                // Current position does not round off (i + 1).
                // No need to continue.
                break;
            }
        }
    }

public:
    PermutationGenerator(unsigned int length)
    {
        assert(length > 0);
        _length = length;
        _counter = unique_ptr<unsigned int[]>(new unsigned int[length]);
        memset(_counter.get(), 0, length * sizeof(unsigned int));
        _totalCount = Factorial(length);
    }

    ~PermutationGenerator(void) {}

    // Total number of permutations
    const unsigned long long TotalCount(void) const
    {
        return _totalCount;
    }

    // Current counter value at position index
    const unsigned int operator[](unsigned int index) const
    {
        assert(index < _length);
        return _counter[index];
    }

    // Get next permutation in-place
    template <class T>
    void Next(vector<T> &input)
    {
        int len = (int)min((unsigned int)input.size(), _length);
        for (int i = len - 1; i >= 0; i--)
        {
            if (_counter[i] > 0)
                swap(input[i], input[i - _counter[i]]);
        }

        // Prepare for the next permutation
        IncreaseCounter();
    }
};

template <class T>
class Queue
{
private:
    stack<T> in, out;

    static void Flush(stack<T> &from, stack<T> &to)
    {
        while (!from.empty())
        {
            T v = from.top();
            from.pop();
            to.push(v);
        }
    }

public:
    Queue(void) {}
    ~Queue(void) {}

    T &Back(void)
    {
        if (in.empty())
        {
            if (out.empty())
                throw runtime_error("Queue is empty");
            Flush(out, in);
        }

        return in.top();
    }

    bool Empty(void) const
    {
        return out.empty() && in.empty();
    }

    T &Front(void)
    {
        if (out.empty())
            Flush(in, out);
        if (out.empty())
            throw runtime_error("Queue is empty");
        return out.top();
    }

    void Pop(void)
    {
        if (out.empty())
            Flush(in, out);
        if (out.empty())
            throw runtime_error("Queue is empty");
        out.pop();
    }

    void Push(const T &value)
    {
        in.push(value);
    }

    size_t Size(void) const
    {
        return out.size() + in.size();
    }
};

template <class T>
class Stack
{
private:
    queue<T> queue0, queue1;

    static void Flush(queue<T> &nonempty, queue<T> &empty, size_t count)
    {
        while (count > 0)
        {
            T v = nonempty.front();
            nonempty.pop();
            empty.push(v);
            count--;
        }
    }

public:
    Stack(void) {}
    ~Stack(void) {}

    bool Empty(void) const
    {
        return queue0.empty() && queue1.empty();
    }

    void Pop(void)
    {
        if (queue0.empty() && queue1.empty())
            throw runtime_error("Stack is empty");
        else if (!queue0.empty())
        {
            Flush(queue0, queue1, queue0.size() - 1);
            queue0.pop();
        }
        else if (!queue1.empty())
        {
            Flush(queue1, queue0, queue1.size() - 1);
            queue1.pop();
        }
    }

    void Push(const T &value)
    {
        if (!queue0.empty())
            queue0.push(value);
        else if (!queue1.empty())
            queue1.push(value);
        else
            queue0.push(value);
    }

    size_t Size(void) const
    {
        return queue0.size() + queue1.size();
    }

    T &Top(void)
    {
        if (queue0.empty() && queue1.empty())
            throw runtime_error("Stack is empty");
        else if (!queue0.empty())
            return queue0.back();
        else
            return queue1.back();
    }
};

template <class T>
class SingleLinkList
{
    // The overloaded operator << is a template
    // Another valid form is: friend ostream& operator<<<>(ostream &, SingleLinkList<T> &);
    friend ostream &operator<<<T>(ostream &, SingleLinkList<T> &);

private:
    class Node
    {
    public:
        T data;
        Node *next;
        Node(T &d, Node *n) : data(d), next(n) {}
        Node(T &d) : data(d), next(nullptr) {}
        ~Node(void) { next = nullptr; }
    } * _head, *_tail;

public:
    SingleLinkList(void) : _head(nullptr), _tail(nullptr) {}

    ~SingleLinkList(void)
    {
        Node *p;
        while (nullptr != _head)
        {
            p = _head;
            _head = p->next;
            delete p;
        }
    }

    void Insert(T &data)
    {
        Node *node = new Node(data);
        if (nullptr == _head)
        {
            // the list is empty, so initialize the list with the node.
            _head = node;
            _tail = node;
        }
        else
        {
            // the list is not empty, so add the node to the end.
            _tail->next = node;
            _tail = node;
        }
    }

    void Reverse(void)
    {
        Node *p, *n;

        // The list is empty or contains only one node.
        if (nullptr == _head || nullptr == _head->next)
            return;

        // Initialize the variables.

        //  ( )->( )->( )->......( )->NULL
        //   ^                    ^
        //   |                    |
        // _head                _tail

        // p to previous node.
        p = _head;

        //  ( )->( )->( )->......( )->NULL
        //   ^                    ^
        //   |                    |
        // _head=p              _tail

        // header to the middle node.
        _head = p->next;

        //  ( )->( )->( )->......( )->NULL
        //   ^    ^               ^
        //   |    |               |
        //   p  _head           _tail

        // n to the next node.
        n = _head->next;

        //  ( )->( )->( )->......( )->NULL
        //   ^    ^    ^          ^
        //   |    |    |          |
        //   p  _head  n        _tail

        // tail points to the last node of the reversed list.
        _tail = p;

        //  ( )->( )->( )->......( )->NULL
        //   ^    ^    ^
        //   |    |    |
        //   p  _head  n
        //  =_tail

        // The last node of the reversed list should point to nothing.
        _tail->next = nullptr;

        // NULL<-( )  ( )->( )->......( )->NULL
        //        ^    ^    ^
        //        |    |    |
        //        p  _head  n
        //     =_tail

        while (nullptr != n)
        {
            // Reverse the link between the previous node and the middle node.
            _head->next = p;

            // NULL<-( )<-( )  ( )->......( )->NULL
            //        ^    ^    ^
            //        |    |    |
            //        p  _head  n
            //     =_tail

            // Move forward.
            p = _head;

            // NULL<-( )<-( )  ( )->......( )->NULL
            //        ^    ^    ^
            //        |    |    |
            //      _tail  p    n
            //           =_head

            _head = n;

            // NULL<-( )<-( )  ( )->......( )->NULL
            //        ^    ^    ^
            //        |    |    |
            //      _tail  p    n
            //                =_head

            n = _head->next;

            // NULL<-( )<-( )  ( )->( )......( )->NULL
            //        ^    ^    ^    ^
            //        |    |    |    |
            //      _tail  p  _head  n
        }

        // NULL<-( )<-( )......( )  ( )->NULL
        //        ^             ^    ^    ^
        //        |             |    |    |
        //      _tail           p  _head  n

        // n is NULL, header points to the last node of the original list.
        // Reverse the last link.
        _head->next = p;

        // NULL<-( )<-( )......( )<-( ) NULL
        //        ^             ^    ^    ^
        //        |             |    |    |
        //      _tail           p  _head  n
    }

    // The middle node is the n-th (1-based) node, no matter if
    // the list contain (2n-1) nodes or 2n nodes.
    // So returns the median or the lower median.
    const T &Middle(void) const
    {
        Node *middle, *p;

        // The list is empty.
        if (nullptr == _head)
            throw invalid_argument("Empty list");

        // Start from the first node.
        middle = _head;
        p = _head;

        while (nullptr != p->next && nullptr != p->next->next)
        {
            // p visits the (2n-1)-th node.
            p = p->next->next;
            // middle visits the n-th node.
            middle = middle->next;
        }
        return middle->data;
    }

    void Print(ostream &os = cout) const
    {
        Node *p = _head;
        os << "Head->";
        while (nullptr != p)
        {
            os << p->data << "->";
            p = p->next;
        }
        os << "NULL" << endl;
    }

    const T &operator[](unsigned int index) const
    {
        unsigned int i = 0;
        Node *p = _head;
        while (i < index && p != nullptr)
        {
            p = p->next;
            i++;
        }
        if (p != nullptr)
        {
            // i == index
            return p->data;
        }

        throw invalid_argument(String::Format("Invalid index [%d]", index));
    }

    class iterator;
    friend class iterator;
    class iterator
    {
    private:
        unsigned int _index;
        Node *_pointer;
        void Check(void) const
        {
            if (_pointer == nullptr)
                throw invalid_argument(String::Format("SingleLinkList<%s>::iterator is not initialized", typeid(T).name()));
        }

    public:
        iterator(const SingleLinkList<T> &list) : _index(0), _pointer(list._head) {}
        iterator(const iterator &it) : _index(it._index), _pointer(it._pointer) {}
        iterator(void) : _index(0), _pointer(nullptr) {}

        const unsigned int index(void) const { return _index; }

        bool operator++()
        {
            Check();
            if (_pointer->next != nullptr)
            {
                _index++;
                _pointer = _pointer->next;
            }
            else
            {
                _index = 0;
                _pointer = nullptr;
            }
            return _pointer != nullptr;
        }

        bool operator++(int) { return operator++(); }

        const T &current() const
        {
            Check();
            T &d = _pointer->data;
            return d;
        }

        // Return a pointer so that dereference is on the return type
        const Node *operator->()
        {
            Check();
            return _pointer;
        }

        const T &operator*() const { return current(); }

        // Note: There is no return value
        operator bool() const { return _pointer != nullptr; }

        bool operator==(const iterator &it) const { return _pointer == it._pointer; }
        bool operator!=(const iterator &it) const { return _pointer != it._pointer; }
    };

    iterator begin() const { return iterator(*this); }
    iterator end() const { return iterator(); }
};

template <class T>
ostream &operator<<(ostream &os, SingleLinkList<T> &list)
{
    list.Print(os);
    return os;
}

template <class T>
class BinarySearchTree
{
public:
    class Node
    {
    private:
        T _data;
        Node *_parent;
        Node *_left;
        Node *_right;

    public:
        Node(const T &data)
            : _data(data),
              _parent(nullptr),
              _left(nullptr),
              _right(nullptr)
        {
        }

        ~Node(void)
        {
            auto f = [](Node *p) { if (p != nullptr) { p = nullptr; } };
            f(_left);
            f(_right);
            f(_parent);
        }

        void Print(void) { cout << _data << " "; }

        static void PreOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            f(node);
            PreOrderWalk(node->_left, f);
            PreOrderWalk(node->_right, f);
        }

        void PreOrderWalk(function<void(Node *)> f) { Node::PreOrderWalk(this, f); }

        static void InOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            InOrderWalk(node->_left, f);
            f(node);
            InOrderWalk(node->_right, f);
        }

        void InOrderWalk(function<void(Node *)> f) { Node::InOrderWalk(this, f); }

        static void PostOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            PostOrderWalk(node->_left, f);
            PostOrderWalk(node->_right, f);
            f(node);
        }

        void PostOrderWalk(function<void(Node *)> f) { Node::PostOrderWalk(this, f); }

        static Node *Search(Node *node, T data)
        {
            if (node == nullptr || node->_data == data)
                return node;
            if (data < node->_data)
                return Search(node->_left, data);
            else
                return Search(node->_right, data);
        }

        Node *Search(T data) { return Node::Search(this, data); }

        static Node *Min(Node *node)
        {
            if (node == nullptr)
                return node;
            while (node->_left != nullptr)
                node = node->_left;
            return node;
        }

        Node *Min() { return Node::Min(this); }

        static Node *Max(Node *node)
        {
            if (node == nullptr)
                return node;
            while (node->_right != nullptr)
                node = node->_right;
            return node;
        }

        Node *Max() { return Node::Max(this); }

        static Node *Insert(Node *node, T data)
        {
            Node *newNode = new Node(data);
            Node *parent = node;
            Node *current = node;
            while (current != nullptr)
            {
                parent = current;
                if (newNode->_data < current->_data)
                {
                    current = current->_left;
                }
                else
                { // newNode->_data >= current->_data
                    current = current->_right;
                }
            }
            newNode->_parent = parent;
            if (parent == nullptr)
            {
                // This means node is NULL, i.e. it is an empty tree.
                // Return the new node as it is the first node of a tree.
                return newNode;
            }
            else if (newNode->_data < parent->_data)
            {
                parent->_left = newNode;
            }
            else
            {
                parent->_right = newNode;
            }
            // The root of tree.
            return node;
        }

        void Insert(T data) { Node::Insert(this, data); }

        static Node *Successor(Node *node)
        {
            if (node == nullptr)
                return nullptr;
            //  (A)
            //  / \
	        // () (B)
            // The successor of A is the minimum node of subtree B
            if (node->_right != nullptr)
                return Min(node->_right);
            //    (B)
            //   /
            // (C)
            //   \
	        //    ()
            //      \
	        //      (A)
            //      / \
        	//     () NULL
            // The successor of A is the lowest ancestor B whose
            // left child C contains A in its right substree
            Node *parent = node->_parent;
            while (parent != nullptr && node == parent->_right)
            {
                node = parent;
                parent = parent->_parent;
            }
            // parent could be NULL if node is the maximum node of tree, i.e.,
            //
            //  (A)
            //  / \
	        // () NULL
            //
            // or
            //
            // ()
            //   \
	        //   (A)
            //   / \
	        //  () NULL
            return parent;
        }

        Node *Successor() { return Node::Successor(this); }

        static Node *Predecessor(Node *node)
        {
            if (node == nullptr)
                return nullptr;
            //   (A)
            //   /
            // (B)
            // The predecessor of A is the maximum node of subtree B
            if (node->_left != nullptr)
                return Max(node->_left);
            //     (B)
            //       \
	        //       (C)
            //       /
            //      ()
            //     /
            //   (A)
            //   / \
	        // NULL ()
            // The predecessor of A is the lowest ancestor B whose
            // right child C contains A in its left substree
            Node *parent = node->_parent;
            while (parent != nullptr && node == parent->_left)
            {
                node = parent;
                parent = parent->_parent;
            }
            // parent could be NULL if node is the minimum node of tree, i.e.,
            //
            //   (A)
            //   / \
	        // NULL ()
            //
            // or
            //
            //      ()
            //     /
            //   (A)
            //   / \
	        // NULL ()
            return parent;
        }

        Node *Predecessor() { return Node::Predecessor(this); }

        // Remove left and right subtrees at node
        static void Empty(Node *node)
        {
            PostOrderWalk(node->_left, [](Node *x) { delete x; });
            PostOrderWalk(node->_right, [](Node *x) { delete x; });
            node->_left = nullptr;
            node->_right = nullptr;
        }

        void Empty() { Empty(this); }

        // Replace dst with src. Return dst.
        static Node *Transplant(Node *dst, Node *src)
        {
            if (dst == nullptr)
                return nullptr;

            if (dst->_parent == nullptr)
            {
                // src becomes the new root
                if (src != nullptr)
                    src->_parent = nullptr;
                return dst;
            }

            // Link dst->_parent to src
            if (dst == dst->_parent->_left)
            {
                dst->_parent->_left = src;
            }
            else
            {
                dst->_parent->_right = src;
            }

            // Link src->_parent to dst->_parent
            if (src != nullptr)
                src->_parent = dst->_parent;

            // dst->_parent is not changed. The children of dst are not changed.
            // It is possible src is still a child of dst, though src->_parent
            // is now pointing outside of dst tree.
            return dst;
        }
    };

    static void Delete(Node *node)
    {
        if (node == nullptr)
            return;

        if (node->_left == nullptr)
        {
            //   ()
            //    |
            //   (A)
            //   /  \
		    // NULL (B)
            Transplant(node, node->_right);
            delete node;
            return;
        }

        if (node->_right == nullptr)
        {
            //   ()
            //    |
            //   (A)
            //   /  \
		    // (B) NULL
            Transplant(node, node->_left);
            delete node;
            return;
        }

        Node *successor = Min(node->_right);

        if (successor->_parent != node)
        {
            //     ()
            //     |
            //    (A)
            //    / \
		    //   ()  (D)
            //        \
		    //         ()
            //        /
            //      (B)
            //      / \
	        //    NULL (C)
            Transplant(successor, successor->_right);
            //     ()
            //     |
            //    (A)
            //    / \
		    //   () (D)
            //        \
		    //         ()
            //        /
            //      (C)           (B)
            successor->_right = node->_right;
            successor->_right->_parent = successor;
            //     ()
            //     |
            //    (A)
            //    /
            //   ()
            //       (B)
            //         \
		    //         (D)
            //           \
		    //            ()
            //           /
            //         (C)
        }

        Transplant(node, successor);
        successor->_left = node->_left;
        successor->_left->_parent = successor;
        delete node;
    }

private:
    Node *_root;

public:
    BinarySearchTree(void) { _root = nullptr; }

    ~BinarySearchTree(void) { Empty(); }

    void Insert(T data) { _root = Node::Insert(_root, data); }

    void PreOrderWalk(function<void(Node *)> f) { Node::PreOrderWalk(_root, f); };
    void InOrderWalk(function<void(Node *)> f) { Node::InOrderWalk(_root, f); };
    void PostOrderWalk(function<void(Node *)> f) { Node::PostOrderWalk(_root, f); };

    void Empty(void)
    {
        Node::PostOrderWalk(_root, [](Node *x) { delete x; });
        _root = nullptr;
    }

    Node *Search(T data) { return Node::Search(_root, data); }
    Node *Min(void) { return Node::Min(_root); }
    Node *Max(void) { return Node::Max(_root); }

    void Print()
    {
        auto f = [](Node *x) { x->Print(); };
        PostOrderWalk(f);
    }
};

template <class T>
class AVLTree
{
private:
    class Node
    {
        template <class T>
        friend class AVLTree;

    private:
        T content;
        Node *parent;
        Node *left;
        Node *right;
        int height;

    public:
        Node(const T &c) : content(c), parent(nullptr), left(nullptr), right(nullptr), height(1) {}
        // Not delete its children
        ~Node(void)
        {
            auto f = [](Node *&p) { if (p != nullptr) { p = nullptr; } };
            f(this->left);
            f(this->right);
            f(this->parent);
        }

        static Node *Search(Node *node, const T &content)
        {
            if (node == nullptr || node->content == content)
                return node;
            while (node != nullptr && content != node->content)
            {
                if (content < node->content)
                    node = node->left;
                else
                    node = node->right;
            }

            return node;
        }

        static Node *Min(Node *node)
        {
            if (node == nullptr)
                return node;
            while (node->left != nullptr)
                node = node->left;
            return node;
        }

        static void PostOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            PostOrderWalk(node->left, f);
            PostOrderWalk(node->right, f);
            f(node);
        }

        static void Empty(Node *node)
        {
            PostOrderWalk(node->left, [](Node *x) { delete x; });
            PostOrderWalk(node->right, [](Node *x) { delete x; });
            node->left = nullptr;
            node->right = nullptr;
        }

        static bool Verify(Node *node)
        {
            if (node == nullptr)
                return true;
            if (node->left == nullptr && node->right == nullptr)
            {
                if (node->height != 1)
                    return false;
            }

            if (node->left == nullptr && node->right != nullptr)
            {
                if (node->right->height != 1)
                    return false;
                if (node->height != 2)
                    return false;
            }

            if (node->left != nullptr && node->right == nullptr)
            {
                if (node->left->height != 1)
                    return false;
                if (node->height != 2)
                    return false;
            }

            if (node->left != nullptr && node->right != nullptr)
            {
                if (node->left->height - node->right->height > 1)
                    return false;
                if (node->right->height - node->left->height > 1)
                    return false;
                if (node->height != 1 + std::max(node->left->height, node->right->height))
                    return false;
            }

            if (node->left != nullptr && !Verify(node->left))
                return false;

            if (node->right != nullptr && !Verify(node->right))
                return false;

            return true;
        }

        static stringstream &ToString(stringstream &ss, Node *node, int x, vector<int> &y)
        {
            static string link = "____";
            string c = String::Format("%d:%d", node->height, node->content);
            ss << c;
            x += c.length();

            if (node->right != nullptr)
            {
                // Record current x coordinate,
                // so it can be used to draw '|'
                y.push_back(x);
            }

            if (node->left != nullptr)
            {
                ss << link;
                ToString(ss, node->left, x + link.length(), y);
            }

            if (node->right != nullptr)
            {
                ss << endl;

                for (size_t i = 0; i < y.size(); i++)
                {
                    int len = i == 0 ? y[i] : y[i] - y[i - 1];
                    string blank(len - 1, ' ');
                    ss << blank << '|';
                }

                ss << link;

                // The right child is ready to print
                // Remove its coordinate because it is not needed any more
                y.pop_back();

                ToString(ss, node->right, x + link.length(), y);
            }

            return ss;
        }

        void Print(void)
        {
            stringstream ss;
            vector<int> y;
            ToString(ss, this, 0, y);
            ss << endl;
            cout << ss.str();
        }

    } * root;

    //        y               x
    //       / \             / \
	//      x       <====       y
    //     / \                 / \
	//        z               z
    //
    // Rotate at x
    Node *LeftRotate(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        Node *y = node->right;
        if (y == nullptr)
            return nullptr;

        node->right = y->left;
        if (y->left != nullptr)
            y->left->parent = node;

        y->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = y;
        }
        else
        {
            if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
        }

        y->left = node;
        node->parent = y;
        return y;
    }

    //        x               y
    //       / \             / \
	//      y       ====>       x
    //     / \                 / \
	//        z               z
    //
    // Rotate at x
    Node *RightRotate(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        Node *y = node->left;
        if (y == nullptr)
            return nullptr;

        node->left = y->right;
        if (y->right != nullptr)
            y->right->parent = node;

        y->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = y;
        }
        else
        {
            if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
        }

        y->right = node;
        node->parent = y;
        return y;
    }

    // Replace the subtree at dst with the subtree at src
    // Update root if dst is the original root
    // src may be NULL, then dst is removed from its parent but not deleted.
    void Transplant(Node *dst, Node *src)
    {
        if (dst == nullptr)
            return;
        if (dst->parent == nullptr)
        {
            // src becomes the new root
            this->root = src;
        }
        else if (dst == dst->parent->left)
        {
            dst->parent->left = src;
        }
        else
        {
            dst->parent->right = src;
        }

        if (src != nullptr)
            src->parent = dst->parent;
    }

    //        z                 x
    //       / \               / \
	//      x   y     <====       y
    //     / \ / \               / \
	//                          z
    //                         / \
	// Transplant at x
    Node *LeftTransplant(Node *node)
    {
        if (node == nullptr)
            return nullptr;

        Node *y = node->right;
        if (y == nullptr)
            return nullptr;

        Node *z = y->left;
        if (z == nullptr)
            return nullptr;

        y->left = z->right;
        if (z->right != nullptr)
            z->right->parent = y;

        node->right = z->left;
        if (z->left != nullptr)
            z->left->parent = node;

        z->right = y;
        y->parent = z;

        z->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = z;
        }
        else
        {
            if (node == node->parent->left)
                node->parent->left = z;
            else
                node->parent->right = z;
        }

        z->left = node;
        node->parent = z;

        return z;
    }

    //        x                 z
    //       / \               / \
	//      y       ====>     y   x
    //     / \               / \ / \
	//        z
    //       / \
	// Transplant at x
    Node *RightTransplant(Node *node)
    {
        if (node == nullptr)
            return nullptr;

        Node *y = node->left;
        if (y == nullptr)
            return nullptr;

        Node *z = y->right;
        if (z == nullptr)
            return nullptr;

        y->right = z->left;
        if (z->left != nullptr)
            z->left->parent = y;

        node->left = z->right;
        if (z->right != nullptr)
            z->right->parent = node;

        z->left = y;
        y->parent = z;

        z->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = z;
        }
        else
        {
            if (node == node->parent->left)
                node->parent->left = z;
            else
                node->parent->right = z;
        }

        z->right = node;
        node->parent = z;

        return z;
    }

    // Case 1
    //        ( )
    //        / \
	//     N(h) ( )
    //     / \  / \
	//
    // Case 2
    //     ( )
    //     / \
	//   ( ) N(h)
    //   / \ / \
	//
    // The subtree at node is a valid AVL tree.
    // Need to fix the height of node's ancestors and siblings.
    void InsertFix(Node *node)
    {
        if (node == nullptr)
            return;
        while (node->parent != nullptr)
        {
            Node *parent = node->parent;
            if (parent->height == node->height + 1)
            {
                //       P(h+1)       P(h+1)
                //       /   \        /   \
				//     N(h)  (h)    (h)   N(h)
                //     / \   / \    / \   / \
				//
                break;
            }

            // Now parent->height == node->height

            if (node == parent->left)
            {
                if (parent->right == nullptr)
                {
                    if (parent->height == 1)
                    {
                        //       P(1)
                        //       /
                        //     N(1)
                        //
                        if (parent->parent == nullptr)
                        {
                            parent->height++;
                            break;
                        }

                        if (parent == parent->parent->right)
                        {
                            //     (2)
                            //     / \
							//       P(1)
                            //       /
                            //     N(1)
                            //
                            RightRotate(parent);
                            //     (2)
                            //     / \
							//       N(1)
                            //         \
							//         P(1)
                            //
                            node->height++;
                            //     (2)
                            //     / \
							//       N(2)
                            //         \
							//         P(1)
                            //
                            continue;
                        }
                        else
                        {
                            //         (2)
                            //         / \
							//       P(1)
                            //       /
                            //     N(1)
                            //
                            parent->height++;
                            node = parent;
                            //         (2)
                            //         / \
							//       N(2)
                            //       /
                            //     (1)
                            //
                            continue;
                        }
                    }

                    //       P(2)
                    //       /
                    //     N(2)
                    //     / \
					//
                    if (node->left == nullptr)
                    {
                        //       P(2)
                        //       /
                        //     N(2)
                        //       \
						//       (1)
                        LeftRotate(node);
                        //       P(2)
                        //       /
                        //     (1)
                        //     /
                        //   N(2)
                        node->height--;
                        node = node->parent;
                        node->height++;
                        //       P(2)
                        //       /
                        //     N(2)
                        //     /
                        //   (1)
                    }

                    if (node->right == nullptr)
                    {
                        //       P(2)
                        //       /
                        //     N(2)
                        //     /
                        //   (1)
                        RightRotate(parent);
                        //     N(2)
                        //     /  \
						//   (1)  P(2)
                        parent->height = node->height - 1;
                        //     N(2)
                        //     /  \
						//   (1)  P(1)
                        break;
                    }
                    else
                    {
                        //       P(2)
                        //       /
                        //     N(2)
                        //     /  \
						//   (1)  (1)
                        RightRotate(parent);
                        //     N(2)
                        //     /  \
						//   (1)  P(2)
                        //        /
                        //      (1)
                        node->height++;
                        //     N(3)
                        //     /  \
						//   (1)  P(2)
                        //        /
                        //      (1)
                        continue;
                    }
                }
                else if (parent->right != nullptr)
                {
                    if (parent->right->height == node->height - 1)
                    {
                        //       P(h)
                        //       /   \
						//     N(h) (h-1)
                        //     / \   / \
						//
                        if (parent->parent == nullptr)
                        {
                            parent->height++;
                            break;
                        }

                        if (parent == parent->parent->left)
                        {
                            //         ( )
                            //         /
                            //       P(h)
                            //       /   \
							//     N(h) (h-1)
                            //     / \   / \
							//
                            parent->height++;
                            node = parent;
                            //         ( )
                            //         /
                            //       N(h+1)
                            //       /   \
							//     (h)  (h-1)
                            //     / \   / \
							//
                            continue;
                        }
                        else
                        {
                            //      ( )
                            //        \
							//       P(h)
                            //       /   \
							//     N(h) (h-1)
                            //     / \   / \
							//
                            RightRotate(parent);
                            //      ( )
                            //        \
							//       N(h)
                            //       /   \
							//           P(h)
                            //           / \
							//             (h-1)
                            node->height++;
                            //      ( )
                            //        \
							//       N(h+1)
                            //       /   \
							//           P(h)
                            //           / \
							//             (h-1)
                            continue;
                        }
                    }

                    // Now parent->right->height == node->height - 2

                    //       P(h)              P(h)              P(h)
                    //       /   \            /    \            /    \
					//     N(h) (h-2)       N(h)   (h-2)      N(h)   (h-2)
                    //     /     / \       /  \     / \      /  \     /  \
					//                  (h-1)(h-2)        (h-1)(h-1)
                    //
                    RightRotate(parent);
                    //       N(h)             N(h)                N(h)
                    //       /   \            /   \               /   \
					//          P(h)       (h-1)  P(h)         (h-1)  P(h)
                    //           / \             /   \               /    \
					//            (h-2)       (h-2)  (h-2)         (h-1) (h-2)
                    //
                    if (parent->left != nullptr && parent->height == parent->left->height + 1)
                    {
                        node = parent;
                        continue;
                    }
                    else
                    {
                        parent->height--;
                        break;
                    }
                    //       N(h)             N(h)                  (h)
                    //       /   \            /   \               /   \
					//          P(h-1)     (h-1) P(h-1)         (h-1) N(h)
                    //           / \             /   \               /    \
					//            (h-2)       (h-2)  (h-2)         (h-1) (h-2)
                    //
                }
            }
            else if (node == parent->right)
            {
                if (parent->left == nullptr)
                {
                    if (parent->height == 1)
                    {
                        //       P(1)
                        //         \
						//        N(1)
                        //
                        if (parent->parent == nullptr)
                        {
                            parent->height++;
                            break;
                        }

                        if (parent == parent->parent->left)
                        {
                            //     (2)
                            //     / \
							//   P(1)
                            //     \
							//     N(1)
                            //
                            LeftRotate(parent);
                            //     (2)
                            //     / \
							//   N(1)
                            //   /
                            // P(1)
                            //
                            node->height++;
                            //     (2)
                            //     / \
							//   N(2)
                            //   /
                            // P(1)
                            //
                            continue;
                        }
                        else
                        {
                            //    (2)
                            //    / \
							//      P(1)
                            //        \
							//        N(1)
                            //
                            parent->height++;
                            node = parent;
                            //    (2)
                            //    / \
							//      N(2)
                            //        \
							//        (1)
                            //
                            continue;
                        }
                    }

                    //       P(2)
                    //          \
					//          N(2)
                    //           / \
					//
                    if (node->right == nullptr)
                    {
                        //       P(2)
                        //          \
						//          N(2)
                        //           /
                        //         (1)
                        RightRotate(node);
                        //       P(2)
                        //          \
						//          (1)
                        //            \
						//           N(2)
                        node->height--;
                        node = node->parent;
                        node->height++;
                        //       P(2)
                        //          \
						//          N(2)
                        //            \
						//            (1)
                    }

                    if (node->left == nullptr)
                    {
                        //       P(2)
                        //          \
						//          N(2)
                        //            \
						//            (1)
                        LeftRotate(parent);
                        //       N(2)
                        //       /   \
						//     P(2)  (1)
                        parent->height = node->height - 1;
                        //       N(2)
                        //       /   \
						//     P(1)  (1)
                        break;
                    }
                    else
                    {
                        //       P(2)
                        //          \
						//          N(2)
                        //          /  \
						//         (1) (1)
                        LeftRotate(parent);
                        //       N(2)
                        //       /   \
						//     P(2)  (1)
                        //        \
						//        (1)
                        node->height++;
                        //       N(3)
                        //       /   \
						//     P(2)  (1)
                        //        \
						//        (1)
                        continue;
                    }
                }
                else if (parent->left != nullptr)
                {
                    if (parent->left->height == node->height - 1)
                    {
                        //       P(h)
                        //       /   \
						//    (h-1) N(h)
                        //     / \   / \
						//
                        if (parent->parent == nullptr)
                        {
                            parent->height++;
                            break;
                        }

                        if (parent == parent->parent->right)
                        {
                            //     ( )
                            //       \
							//       P(h)
                            //       /   \
							//    (h-1) N(h)
                            //     / \   / \
							//
                            parent->height++;
                            node = parent;
                            //     ( )
                            //       \
							//       N(h+1)
                            //       /   \
							//    (h-1)  (h)
                            //     / \   / \
							//
                            continue;
                        }
                        else
                        {
                            //         ( )
                            //         /
                            //       P(h)
                            //       /   \
							//    (h-1) N(h)
                            //     / \   / \
							//
                            LeftRotate(parent);
                            //         ( )
                            //         /
                            //       N(h)
                            //       /   \
							//     P(h)
                            //     / \
							//  (h-1)
                            node->height++;
                            //         ( )
                            //         /
                            //       N(h+1)
                            //       /   \
							//     P(h)
                            //     / \
							//  (h-1)
                            continue;
                        }
                    }

                    // Now parent->left->height == node->height - 2

                    //		 P(h)              P(h)              P(h)
                    //       /   \            /    \            /    \
					//    (h-2)  N(h)      (h-2)   N(h)      (h-2)   N(h)
                    //     / \     \       /  \     / \      /  \     /  \
					//                           (h-2)(h-1)        (h-1) (h-1)
                    //
                    LeftRotate(parent);
                    //       N(h)             N(h)                N(h)
                    //       /   \            /   \               /   \
					//     P(h)            P(h)  (h-1)          P(h) (h-1)
                    //     / \             /   \               /    \
					//  (h-2)           (h-2)  (h-2)         (h-2) (h-1)
                    //
                    if (parent->right != nullptr && parent->height == parent->right->height + 1)
                    {
                        node = parent;
                        continue;
                    }
                    else
                    {
                        parent->height--;
                        break;
                    }
                    //       N(h)             N(h)                 (h)
                    //       /   \            /   \               /   \
					//    P(h-1)          P(h-1) (h-1)           N(h) (h-1)
                    //     / \             /   \               /    \
					//  (h-2)           (h-2)  (h-2)         (h-2) (h-1)
                    //
                }
            }
        }
    }

    // Node height is one less than its original value.
    // Need to fix it way up.
    void DeleteFix(Node *node)
    {
        if (node == nullptr || node->parent == nullptr)
            return;

        while (node->parent != nullptr)
        {
            Node *parent = node->parent;

            if (node == parent->left)
            {
                //      P( )
                //      /   \
				//   N(h)   ( )
                Node *sibling = parent->right;

                if (sibling->height == node->height)
                {
                    //      P(h+2)
                    //      /   \
					//   N(h)   S(h)
                    parent->height = node->height + 1;
                    node = parent;
                    //      N(h+1)
                    //      /   \
					//    (h)   S(h)
                    continue;
                }

                if (sibling->height == node->height + 1)
                {
                    //      P(h+2)
                    //      /   \
					//   N(h)   S(h+1)
                    break;
                }

                if (sibling->height == node->height + 2)
                {
                    //      P(h+3)
                    //      /   \
					//   N(h)   S(h+2)
                    //           /  \
					//
                    if (sibling->right->height == node->height)
                    {
                        //      P(h+3)
                        //      /   \
						//   N(h)   S(h+2)
                        //           /  \
						//        (h+1) (h)
                        //         / \
						//
                        LeftTransplant(parent);
                        //         (h+1)
                        //         /    \
						//      P(h+3)  S(h+2)
                        //      /   \    /  \
						//   N(h)           (h)
                        parent->height = node->height + 1;
                        sibling->height = node->height + 1;
                        sibling->parent->height = node->height + 2;
                        node = sibling->parent;
                        //         N(h+2)
                        //         /    \
						//      P(h+1)  S(h+1)
                        //      /   \    /  \
						//    (h)           (h)
                        continue;
                    }

                    if (sibling->left->height == node->height)
                    {
                        //      P(h+3)
                        //      /   \
						//   N(h)   S(h+2)
                        //           /  \
						//         (h) (h+1)
                        LeftRotate(parent);
                        //         S(h+2)
                        //         /    \
						//      P(h+3)  (h+1)
                        //      /   \
						//   N(h)   (h)
                        parent->height = node->height + 1;
                        node = sibling;
                        //         N(h+2)
                        //         /    \
						//      P(h+1)  (h+1)
                        //      /   \
						//    (h)   (h)
                        continue;
                    }

                    if (sibling->left->height == node->height + 1)
                    {
                        //      P(h+3)
                        //      /   \
						//   N(h)   S(h+2)
                        //           /  \
						//        (h+1) (h+1)
                        LeftRotate(parent);
                        //         S(h+2)
                        //         /    \
						//      P(h+3)  (h+1)
                        //      /   \
						//   N(h)   (h+1)
                        parent->height = node->height + 2;
                        sibling->height = node->height + 3;
                        //         S(h+3)
                        //         /    \
						//      P(h+2)  ( )
                        //      /   \
						//   N(h)   (h+1)
                        break;
                    }
                }
            }

            if (node == parent->right)
            {
                //      P( )
                //      /   \
				//    ( )  N(h)
                Node *sibling = parent->left;

                if (sibling->height == node->height)
                {
                    //      P(h+2)
                    //      /   \
					//   S(h)   N(h)
                    parent->height = node->height + 1;
                    node = parent;
                    //      N(h+1)
                    //      /   \
					//    S(h)   (h)
                    continue;
                }

                if (sibling->height == node->height + 1)
                {
                    //      P(h+2)
                    //      /   \
					//  S(h+1)  N(h)
                    break;
                }

                if (sibling->height == node->height + 2)
                {
                    //      P(h+3)
                    //      /   \
					//  S(h+2)   N(h)
                    //   /  \
					//
                    if (sibling->left->height == node->height)
                    {
                        //      P(h+3)
                        //      /   \
						//  S(h+2)   N(h)
                        //   /  \
						// (h)  (h+1)
                        RightTransplant(parent);
                        //         (h+1)
                        //         /    \
						//      S(h+2)  P(h+3)
                        //      /   \    /  \
						//    (h)           N(h)
                        parent->height = node->height + 1;
                        sibling->height = node->height + 1;
                        sibling->parent->height = node->height + 2;
                        node = sibling->parent;
                        //         N(h+2)
                        //         /    \
						//      S(h+1)  P(h+1)
                        //      /   \    /  \
						//    (h)           (h)
                        continue;
                    }

                    if (sibling->right->height == node->height)
                    {
                        //      P(h+3)
                        //      /   \
						//  S(h+2)   N(h)
                        //   /  \
						// (h+1) (h)
                        RightRotate(parent);
                        //         S(h+2)
                        //         /    \
						//      (h+1)  P(h+3)
                        //              /   \
						//            (h)   N(h)
                        parent->height = node->height + 1;
                        node = sibling;
                        //         N(h+2)
                        //         /    \
						//      (h+1) P(h+1)
                        //              /   \
						//            (h)   (h)
                        continue;
                    }

                    if (sibling->right->height == node->height + 1)
                    {
                        //      P(h+3)
                        //      /   \
						//  S(h+2)   N(h)
                        //   /  \
						//(h+1) (h+1)
                        RightRotate(parent);
                        //         S(h+2)
                        //         /    \
						//      (h+1) P(h+3)
                        //              /   \
						//           (h+1)   N(h)
                        parent->height = node->height + 2;
                        sibling->height = node->height + 3;
                        //         S(h+3)
                        //         /    \
						//      (h+1)  P(h+2)
                        //              /   \
						//           (h+1)   N(h)
                        break;
                    }
                }
            }
        }
    }

    //     N( )
    //     /
    //
    //     N( )
    //        \
	// Node has one leaf child deleted.
    // Need to fix the node tree.
    void DeleteFixLeafTree(Node *node)
    {
        if (node == nullptr)
            return;
        if (node->left == nullptr && node->right == nullptr)
        {
            if (node->height != 1)
            {
                node->height = 1;
                DeleteFix(node);
            }

            return;
        }

        if (node->left != nullptr && node->right != nullptr)
        {
            // Should not be a valid input,
            // but handle it anyway.
            int h = 1 + node->left->height > node->right->height ? node->left->height : node->right->height;
            if (node->height != h)
            {
                node->height = h;
                DeleteFix(node);
            }

            return;
        }

        if (node->left != nullptr)
        {
            if (node->left->height == 1)
            {
                //     N(2)
                //     /
                //	 (1)
                return;
            }
            else
            {
                Node *left = node->left;
                if (left->right == nullptr)
                {
                    //     N(3)
                    //     /
                    //	 L(2)
                    //   /
                    // (1)
                    RightRotate(node);
                    //	 L(2)
                    //   /  \
					// (1) N(3)
                    node->height = 1;
                    //	 L(2)
                    //   /  \
					// (1) N(1)
                    DeleteFix(left);
                    return;
                }
                else
                {
                    //     N(3)
                    //     /
                    //	 L(2)
                    //   / \
					//     (1)
                    RightTransplant(node);
                    //      (1)
                    //     /  \
					//	 L(2) N(3)
                    //   /
                    //
                    if (left->left == nullptr)
                    {
                        //      (1)
                        //     /  \
						//	 L(2) N(3)
                        left->height = 1;
                        left->parent->height = 2;
                        node->height = 1;
                        //      (2)
                        //     /  \
						//	 L(1) N(1)
                        DeleteFix(left->parent);
                        return;
                    }
                    else
                    {
                        //      (1)
                        //     /  \
						//	 L(2) N(3)
                        //   /
                        // (1)
                        left->parent->height = 3;
                        node->height = 1;
                        //      (3)
                        //     /  \
						//	 L(2) N(1)
                        //   /
                        // (1)
                        return;
                    }
                }
            }
        }

        if (node->right != nullptr)
        {
            if (node->right->height == 1)
            {
                //     N(2)
                //        \
				//	      (1)
                return;
            }
            else
            {
                Node *right = node->right;
                if (right->left == nullptr)
                {
                    //     N(3)
                    //        \
					//	      R(2)
                    //          \
					//          (1)
                    LeftRotate(node);
                    //	     R(2)
                    //       /  \
					//     N(3) (1)
                    node->height = 1;
                    //	     R(2)
                    //       /  \
					//     N(1) (1)
                    DeleteFix(right);
                    return;
                }
                else
                {
                    //     N(3)
                    //        \
					//	      R(2)
                    //        /  \
					//      (1)
                    LeftTransplant(node);
                    //      (1)
                    //     /   \
					//	 N(3) R(2)
                    //           \
					//
                    if (right->right == nullptr)
                    {
                        //      (1)
                        //     /   \
						//	 N(3) R(2)
                        right->height = 1;
                        right->parent->height = 2;
                        node->height = 1;
                        //      (2)
                        //     /   \
						//	 N(1) R(1)
                        DeleteFix(right->parent);
                        return;
                    }
                    else
                    {
                        //      (1)
                        //     /   \
						//	 N(3) R(2)
                        //           \
						//           (1)
                        right->parent->height = 3;
                        node->height = 1;
                        //      (3)
                        //     /   \
						//	 N(1) R(2)
                        //           \
						//           (1)
                        return;
                    }
                }
            }
        }
    }

public:
    AVLTree(void) : root(nullptr) {}

    ~AVLTree()
    {
        if (this->root != nullptr)
        {
            Node::Empty(this->root);
            delete this->root;
            this->root = nullptr;
        }
    }

    void Insert(const T &content)
    {
        Node *newNode = new Node(content);

        if (this->root == nullptr)
        {
            // The new node becomes the root.
            this->root = newNode;
            return;
        }

        Node *parent = this->root;
        Node *current = this->root;
        while (current != nullptr)
        {
            parent = current;
            if (newNode->content < current->content)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = parent;
        if (newNode->content < parent->content)
        {
            parent->left = newNode;
        }
        else
        {
            parent->right = newNode;
        }

        InsertFix(newNode);
    }

    void Delete(const T &content)
    {
        Node *node = Node::Search(this->root, content);
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
        {
            if (node->parent == nullptr)
            {
                this->root = nullptr;
                delete node;
                return;
            }

            Node *parent = node->parent;
            if (node == parent->left)
                parent->left = nullptr;
            else if (node == parent->right)
                parent->right = nullptr;
            delete node;
            DeleteFixLeafTree(parent);
            return;
        }

        if (node->left == nullptr)
        {
            //    N(2)
            //       \
			//       (1)
            Node *right = node->right;
            Transplant(node, right);
            delete node;
            //    (1)
            if (right->parent != nullptr)
                DeleteFix(right);
            return;
        }

        if (node->right == nullptr)
        {
            //    N(2)
            //    /
            //  (1)
            Node *left = node->left;
            Transplant(node, left);
            delete node;
            //    (1)
            if (left->parent != nullptr)
                DeleteFix(left);
            return;
        }

        // Now node->left and node-right exist

        //    N( )
        //    /  \
		//  ( )  ( )

        Node *successor = Node::Min(node->right);

        if (successor == node->right && successor->right == nullptr)
        {
            //    N( )
            //    /  \
			//  ( )  S(1)
            //  / \
			//
            Transplant(node, successor);
            successor->height = node->height;
            successor->left = node->left;
            node->left->parent = successor;
            delete node;
            //    S( )
            //    /
            //  ( )
            //  / \
			//
            DeleteFixLeafTree(successor);
            return;
        }

        if (successor == node->right && successor->right != nullptr)
        {
            //    N( )
            //    /  \
			//  ( )  S(2)
            //  / \     \
			//          (1)
            Transplant(node, successor);
            successor->height = node->height;
            successor->left = node->left;
            node->left->parent = successor;
            delete node;
            //    S( )
            //    /  \
			//  ( )  (1)
            //  / \
			//
            DeleteFix(successor->right);
            return;
        }

        // Now successor != node->right
        //     N( )
        //    /   \
		//  ( )   ( )
        //  / \   /  \
		//      ( )
        //      / \
		//    S( )
        //       \

        if (successor->right != nullptr)
        {
            //     N( )
            //    /   \
			//  ( )   ( )
            //  / \   /  \
			//      ( )
            //      / \
			//    S(2)
            //       \
			//       (1)
            Node *right = successor->right;
            Transplant(successor, right);
            successor->right = node->right;
            node->right->parent = successor;
            //     N( )
            //    /   \
			//  ( )
            //  / \   S(2)
            //           \
			//           ( )
            //          /  \
			//        ( )
            //        / \
			//      R(1)
            //
            Transplant(node, successor);
            successor->height = node->height;
            successor->left = node->left;
            node->left->parent = successor;
            delete node;
            //     S( )
            //    /   \
			//  ( )   ( )
            //  / \   /  \
			//      ( )
            //      / \
			//    R(1)
            DeleteFix(right);
            return;
        }

        if (successor->right == nullptr)
        {
            //     N( )
            //    /   \
			//  ( )   ( )
            //  / \   /  \
			//      ( )
            //      / \
			//    S(1)
            Node *parent = successor->parent;
            parent->left = nullptr;
            successor->right = node->right;
            node->right->parent = successor;
            //     N( )
            //    /   \
			//  ( )
            //  / \   S(1)
            //           \
			//           ( )
            //          /  \
			//        P( )
            //           \
			//
            Transplant(node, successor);
            successor->height = node->height;
            successor->left = node->left;
            node->left->parent = successor;
            delete node;
            //     S( )
            //    /   \
			//  ( )   ( )
            //  / \   /  \
			//      P( )
            //         \
			//
            DeleteFixLeafTree(parent);
            return;
        }
    }

    bool Verify(void)
    {
        return Node::Verify(this->root);
    }

    void Print(void)
    {
        if (this->root != nullptr)
            this->root->Print();
    }
};
} // namespace Test

#endif