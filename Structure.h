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
class Random
{
private:
    Random()
    {
        // Seed the random-number generator with the current time so that
        // the numbers will be different every time we run.
        srand((unsigned)time(NULL));
    }

    ~Random() {}

public:
    // Call rand() to get a random number in [0, RAND_MAX]
    static int Next(void)
    {
        return rand();
    }

    // Return a random value in [0, max]
    static int Next(int max)
    {
        if (max < 0)
            throw invalid_argument(String::Format("%d is less than zero", max));
        if (max > RAND_MAX)
            throw invalid_argument(String::Format("%d is greater than RAND_MAX", max));

        // +--------+--------+--------+-- ........ --+--------+--------+--------+
        // 0        1        2        3             max-2    max-1    max     RAND_MAX

        double d = (double)RAND_MAX / (max + 1);
        int r = (int)(rand() / d);
        if (r > max)
            r = max;
        return r;
    }

    // Return a value in [min, max]
    static int Next(int min, int max)
    {
        if (min > max)
            throw invalid_argument(String::Format("%d is larger than %d", min, max));
        if (max - min > RAND_MAX)
            throw invalid_argument(String::Format("%d - %d is greater than RAND_MAX", max, min));
        int r = min + Next(max - min);
        return r;
    }

    // Select m samples from [0, n-1] in
    // which each m samples is equally likely.
    // The algorithm is described in exercise 5.3-7 in MIT Introduction to Algorithm, Third Edition.
    static void Sample(unsigned int n, unsigned int m, vector<unsigned int> &samples)
    {
        if (m == 0)
            return;
        if (m > n)
            throw invalid_argument(String::Format("%d is less than %d", n, m));
        Sample(n - 1, m - 1, samples);
        unsigned int i = (unsigned int)Next(n - 1);
        if (find(samples.begin(), samples.end(), i) == samples.end())
        {
            samples.push_back(i);
        }
        else
        {
            samples.push_back(n - 1);
        }
    }

    static void Sample2(unsigned int n, unsigned int m, vector<unsigned int> &samples)
    {
        if (m == 0)
            return;
        if (m > n)
            throw invalid_argument(String::Format("%d is less than %d", n, m));
        for (unsigned int j = n - m; j < n; j++)
        {
            unsigned int i = (unsigned int)Next(j);
            if (find(samples.begin(), samples.end(), i) == samples.end())
            {
                samples.push_back(i);
            }
            else
            {
                samples.push_back(j);
            }
        }
    }
};

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

template <class T>
class HeapD
{
private:
    unsigned int d;
    //                                                  0
    //                   1                              2                    ...          d
    // (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
    // (d^2+d+1) (d^2+d+2) ...
    // ......
    // Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
    // The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]

    // Return the index of the parent of node i
    unsigned int Parent(unsigned int i) { return (i - 1) / this->d; }

    // Return the index of the j-th child of node i. j is zero based.
    unsigned int Child(unsigned int i, unsigned int j)
    {
        if (j >= this->d)
            throw invalid_argument("HeapD::Child(i,j): j must be in [0, d-1].");

        return i * this->d + j + 1;
    }

    // (d^(h-1)-1)/(d-1) < length <= (d^h-1)/(d-1)
    // There are h d-bits and the pattern is between:
    // 1    0    0    0     ... 0    0    0
    // (d-1)(d-1)(d-1)(d-1) ... (d-1)(d-1)(d-1)
    unsigned int Height(unsigned int length)
    {
        unsigned int x = length * (this->d - 1);
        unsigned int h = 0;
        while (x > 0)
        {
            x = x / (this->d);
            h++;
        }

        return h;
    }

    static void Swap(T *A, unsigned int i, unsigned int j)
    {
        if (i == j)
            return;
        T temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    // Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
    // The assumption is the subtrees rooted at i are already heapified.
    void Heapify(T *A, unsigned int i, unsigned int L)
    {
        if (i >= L)
            return;
        unsigned int max = i;

        for (unsigned int j = 0; j < this->d; j++)
        {
            unsigned int c = Child(i, j);
            if (c < L && A[c] > A[max])
            {
                max = c;
            }
        }

        if (max != i)
        {
            Swap(A, i, max);
            Heapify(A, max, L);
        }
    }

public:
    HeapD(unsigned int d)
    {
        if (d == 0)
            throw invalid_argument("HeapD(d): d cannot be zero.");

        this->d = d;
    }

    // Construct the array into a heap
    void Heapify(T *A, unsigned int L)
    {
        unsigned int height = Height(L);
        long long index = ((long long)pow(this->d, height - 1) - 1) / (this->d - 1) - 1;
        // Do not define i as unsigned int, otherwise the for loop will continue forever
        for (long long i = index; i >= 0; i--)
        {
            Heapify(A, (unsigned int)i, L);
        }
    }

    void Sort(T *A, unsigned int L)
    {
        // Make A a heap
        Heapify(A, L);

        // Sort
        for (long long i = L - 1; i >= 0; i--)
        {
            // Swap the current maximum value, which is at position 0, to position i.
            // The range [i, length - 1] is sorted.
            Swap(A, 0, (unsigned int)i);
            // Rearrange [0, i - 1] so that it is a heap
            Heapify(A, 0, (unsigned int)i);
        }
    }
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

template <class T>
class Monge : public Matrix<T>
{
public:
    Monge(size_t r, size_t c) : Matrix<T>(r, c) {}
    static bool IsMonge(Matrix<T> &matrix)
    {
        if (matrix.Rows() <= 1 || matrix.Cols() <= 1)
            return false;
        for (size_t i = 0; i < matrix.Rows() - 1; i++)
        {
            for (size_t j = 0; j < matrix.Cols() - 1; j++)
            {
                if (matrix(i, j) + matrix(i + 1, j + 1) > matrix(i, j + 1) + matrix(i + 1, j))
                    return false;
            }
        }
        return true;
    }

    static void Random(Monge<T> &monge)
    {
        auto rnd = [&]() -> int { return rand() >> 2; };
        for (size_t j = 0; j < monge.Cols(); j++)
        {
            monge(0, j) = rnd();
        }
        for (size_t i = 1; i < monge.Rows(); i++)
        {
            monge(i, 0) = rnd() + monge(i - 1, 0) - monge(i - 1, 1);
            for (size_t j = 1; j < monge.Cols(); j++)
            {
                monge(i, j) = min(rnd(), monge(i - 1, j) + monge(i, j - 1) - monge(i - 1, j - 1));
                if (j < monge.Cols() - 1)
                {
                    int d = monge(i - 1, j) - monge(i - 1, j + 1) - monge(i, j);
                    if (d > 0)
                    {
                        d += (rnd() >> 1);
                        for (size_t k = 0; k <= j; k++)
                        {
                            monge(i, k) += d;
                        }
                    }
                }
            }
        }
    }

    void FindRowMins(vector<size_t> &mins)
    {
        if (mins.size() < this->Rows())
            throw invalid_argument(String::Format("mins length %d is less than %d", mins.size(), this->Rows()));

        function<void(size_t, size_t, size_t, size_t)> find = [&](size_t i1, size_t j1, size_t i2, size_t j2) {
            if (j1 == j2)
            {
                for (size_t i = i1; i <= i2; i++)
                {
                    mins[i] = j1;
                }
            }
            else
            {
                size_t i = i1 + ((i2 - i1) >> 1);
                T m = this->operator()(i, j1);
                mins[i] = j1;
                for (size_t j = j1 + 1; j <= j2; j++)
                {
                    if (this->operator()(i, j) < m)
                    {
                        m = this->operator()(i, j);
                        mins[i] = j;
                    }
                }
                if (i1 < i)
                {
                    find(i1, j1, i - 1, mins[i]);
                }
                if (i < i2)
                {
                    find(i + 1, mins[i], i2, j2);
                }
            }
        };

        find(0, 0, this->Rows() - 1, this->Cols() - 1);
    }

    void FindRowMins2(vector<size_t> &mins)
    {
        if (mins.size() < this->Rows())
            throw invalid_argument(String::Format("mins length %d is less than %d", mins.size(), this->Rows()));

        size_t k = 0;
        for (size_t i = 0; i < this->Rows(); i++)
        {
            T m = this->operator()(i, k);
            for (size_t j = k + 1; j < this->Cols(); j++)
            {
                if (this->operator()(i, j) < m)
                {
                    m = this->operator()(i, j);
                    k = j;
                }
            }
            mins[i] = k;
        }
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

    // Assume all the MRInteger instances in the vector have the same bases.
    static void Sort(std::vector<MRInteger> &numbers)
    {
        std::function<std::function<bool(const MRInteger &, const MRInteger &)>(int)> compare = [](int radix) {
            std::function<bool(const MRInteger &, const MRInteger &)> c = [=](const MRInteger &left, const MRInteger &right) -> bool {
                // It will fail if I change < to <=
                return left[radix] < right[radix];
            };

            return c;
        };

        for (unsigned int i = 0; i < numbers.front().Length(); i++)
        {
            std::function<bool(const MRInteger &, const MRInteger &)> c = compare(i);
            std::stable_sort(numbers.begin(), numbers.end(), c);
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
    template <class T>
    friend Log &operator<<(Log &, const SingleLinkList<T> &);

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

    // Return the pointer to the first instance of input data
    virtual Node *Search(const T &data) const
    {
        Node *p = _head;
        while (nullptr != p && p->data != data)
        {
            p = p->next;
        }

        // p == nullptr || p->data == data
        return p;
    }

    virtual bool Contain(const T &data) const { return nullptr != Search(data); }

    void Delete(const T &data)
    {
        if (nullptr == _head)
            return;

        Node *p = _head;
        if (p->data == data)
        {
            _head = p->next;
            delete p;
            return;
        }

        while (nullptr != p->next && p->next->data != data)
        {
            p = p->next;
        }

        if (nullptr != p->next)
        {
            Node *t = p->next;
            p->next = t->next;
            delete t;
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
Log &operator<<(Log &log, const SingleLinkList<T> &list)
{
    SingleLinkList<T>::Node *p = list.head;
    log.WriteInformation("Head->");
    while (nullptr != p)
    {
        // This is not accurate as data may not be int type.
        log.WriteInformation("%d->", p->data);
        p = p->next;
    }

    log.WriteInformation("nullptr");
    return log;
}

template <class T>
class SortedSingleLinkList : public SingleLinkList<T>
{
public:
    void Insert(const T &data)
    {
        SingleLinkList<T>::Node *node = new SingleLinkList<T>::Node(data);
        if (nullptr == head)
        {
            head = node;
            return;
        }

        if (head->data > data)
        {
            node->next = head;
            head = node;
            return;
        }

        SingleLinkList<T>::Node *p = head;
        while (nullptr != p->next && p->next->data <= data)
        {
            p = p->next;
        }

        node->next = p->next;
        p->next = node;
    }
};

template <class T>
class CircularSingleLinkList : public SingleLinkList<T>
{
    template <class T>
    friend ostream &operator<<(ostream &, const CircularSingleLinkList<T> &);
    template <class T>
    friend Log &operator<<(Log &, const CircularSingleLinkList<T> &);

protected:
    Node *Search(const T &data) const;

public:
    ~CircularSingleLinkList(void)
    {
        if (nullptr == head)
            return;
        Node *p = head;
        head = p->next;
        p->next = nullptr;
        SingleLinkList<T>::~SingleLinkList();
    }

    template <class T>
    typename SingleLinkList<T>::Node *CircularSingleLinkList<T>::Search(const T &data) const
    {
        if (nullptr == head)
            return nullptr;

        Node *p = head;
        while (p->data != data && p->next != head)
        {
            p = p->next;
        }

        if (p->data == data)
            return p;
        else
            return nullptr;
    }

    bool Contain(const T &data) const { return nullptr != Search(data); }
    void Delete(const T &data)
    {
        if (nullptr == head)
            return;

        Node *p = head;
        if (p->next == head)
        {
            if (p->data == data)
            {
                delete p;
                head = nullptr;
            }

            return;
        }

        while (p->next != head && p->next->data != data)
        {
            p = p->next;
        }

        if (p->next->data == data)
        {
            Node *t = p->next;
            p->next = t->next;
            if (t == head)
                head = t->next;
            delete t;
        }
    }

    // Insert data between head and head->next, then set head to the new node
    virtual void Insert(const T &data)
    {
        Node *node = new Node(data);
        if (nullptr == head)
        {
            head = node;
            head->next = head;
        }
        else
        {
            node->next = head->next;
            head->next = node;
            head = node;
        }
    }

    const T &operator[](unsigned int index) const
    {
        if (nullptr == head)
            throw invalid_argument("List is empty");

        unsigned int i = 0;
        Node *p = head;
        while (i < index)
        {
            p = p->next;
            i++;
        }

        return p->data;
    }
};

template <class T>
ostream &operator<<(ostream &os, const CircularSingleLinkList<T> &list)
{
    SingleLinkList<T>::Node *p = list.head;
    cout << "Head->";
    if (list.head == nullptr)
    {
        cout << "nullptr" << endl;
        return;
    }

    do
    {
        cout << p->data << "->";
        p = p->next;
    } while (p != list.head);

    cout << "Head" << endl;
    return os;
}

template <class T>
Log &operator<<(Log &log, const CircularSingleLinkList<T> &list)
{
    SingleLinkList<T>::Node *p = list.head;
    log.WriteInformation("Head->");
    if (list.head == nullptr)
    {
        log.WriteInformation("nullptr\n");
        return log;
    }

    do
    {
        log.WriteInformation("%d->", p->data);
        p = p->next;
    } while (p != list.head);

    log.WriteInformation("Head\n");
    return log;
}

template <class T>
class SortedCircularSingleLinkList : public CircularSingleLinkList<T>
{
public:
    // Insert data and update head to the smallest one
    void Insert(const T &data)
    {
        SingleLinkList<T>::Node *node = new SingleLinkList<T>::Node(data);

        if (nullptr == head)
        {
            head = node;
            node->next = head;
            return;
        }

        Node *p = head;
        Node *q = head->next;

        do
        {
            if (p->data <= node->data && node->data < q->data)
            {
                // Case: p->data < q->data, and node is in between
                p->next = node;
                node->next = q;
                return;
            }

            if (p->data > q->data && (p->data <= node->data || node->data <= q->data))
            {
                // Case: p->data > q->data, and node is in between
                p->next = node;
                node->next = q;

                if (node->data <= q->data)
                {
                    // node is the smallest one
                    head = node;
                }

                return;
            }

            p = q;
            q = p->next;
        } while (p != head);

        // Now we are back at head, and know all nodes are equal,
        // because neither p->data < q->data or p->data > q->data has happened.
        // Case: p->data == q->data
        p->next = node;
        node->next = q;
        if (node->data < q->data)
        {
            head = node;
        }
        else if (node->data > q->data)
        {
            head = q;
        }
    }
};

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
class RedBlackTree
{
public:
    typedef enum
    {
        RED,
        BLACK
    } Color;

    class Node
    {
        template <class T>
        friend class RedBlackTree;

    private:
        T content;
        Node *parent;
        Node *left;
        Node *right;
        Color color;

    public:
        Node(const T &c) : content(c), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
        // Not delete its children
        ~Node(void)
        {
            auto f = [](Node *p) { if (p != nullptr) { p = nullptr; } };
            f(this->left);
            f(this->right);
            f(this->parent);
        }

        T Content() { return this->content; }

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

        static int BlackHeight(Node *node)
        {
            if (node == nullptr)
            {
                // NULL is BLACK by definition
                return 1;
            }

            int left = BlackHeight(node->left);
            int right = BlackHeight(node->right);
            return std::max<int>(left, right) + (node->color == BLACK ? 1 : 0);
        }

        static int BlackHeight2(Node *node)
        {
            if (node == nullptr)
            {
                // NULL is BLACK by definition
                return 1;
            }

            Node *prev = node;
            int max = 0;
            int h = 0;
            while (node != nullptr)
            {
                if (prev == node->right)
                {
                    if (node->right->color == BLACK)
                        h--;
                    prev = node;
                    node = node->parent;
                }
                else if (node->left != nullptr && prev != node->left)
                {
                    if (node->color == BLACK)
                        h++;
                    prev = node;
                    node = node->left;
                }
                else
                {
                    if (node->left == nullptr)
                    {
                        if (node->color == BLACK)
                            h++;
                        if (h + 1 > max)
                            max = h + 1;
                    }
                    else if (prev == node->left)
                    {
                        if (node->left->color == BLACK)
                            h--;
                    }

                    prev = node;

                    if (node->right == nullptr)
                    {
                        if (h + 1 > max)
                            max = h + 1;
                        node = node->parent;
                    }
                    else
                    {
                        node = node->right;
                    }
                }
            }

            return max;
        }

        static bool Verify(Node *node)
        {
            if (node == nullptr)
                return true;

            if (node->parent == nullptr && node->color != BLACK)
            {
                // Root is not BLACK
                return false;
            }

            if (node->color == RED)
            {
                if ((node->left != nullptr && node->left->color == RED) || (node->right != nullptr && node->right->color == RED))
                {
                    // A RED node cannot have a RED child
                    return false;
                }
            }

            int left = BlackHeight2(node->left);
            int right = BlackHeight2(node->right);
            if (left != right)
            {
                // Both children must have the same BLACK height
                return false;
            }

            if (node->left != nullptr && !Verify(node->left))
                return false;
            if (node->right != nullptr && !Verify(node->right))
                return false;
            return true;
        }

        static void Empty(Node *node)
        {
            PostOrderWalk(node->left, [](Node *x) { delete x; });
            PostOrderWalk(node->right, [](Node *x) { delete x; });
            node->left = nullptr;
            node->right = nullptr;
        }

        void Empty(void) { Empty(this); }

        static stringstream &ToString(stringstream &ss, Node *node, int x, vector<int> &y)
        {
            static string link = "____";
            string c = String::Format("%s%d", node->color == RED ? "R" : "B", node->content);
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
	//
    // Rotate at x
    Node *LeftRotate(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        Node *right = node->right;
        if (right == nullptr)
            return nullptr;

        node->right = right->left;
        if (right->left != nullptr)
            right->left->parent = node;

        right->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = right;
        }
        else
        {
            if (node == node->parent->left)
                node->parent->left = right;
            else
                node->parent->right = right;
        }

        right->left = node;
        node->parent = right;
        return right;
    }

    //        y               x
    //       / \             / \
	//      x       ====>       y
    //     / \                 / \
	//
    // Rotate at y
    Node *RightRotate(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        Node *left = node->left;
        if (left == nullptr)
            return nullptr;

        node->left = left->right;
        if (left->right != nullptr)
            left->right->parent = node;

        left->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = left;
        }
        else
        {
            if (node == node->parent->left)
                node->parent->left = left;
            else
                node->parent->right = left;
        }

        left->right = node;
        node->parent = left;
        return left;
    }

    void InsertFixUp(Node *node)
    {
        if (node == nullptr || node->color == BLACK)
            return;

        while (node->parent != nullptr && node->parent->color == RED)
        {
            // So node and node->parent are both RED, we need to fix it.

            if (node->parent->parent == nullptr)
            {
                // node->parent is the root
                node->parent->color = BLACK;
                return;
            }

            // Now node->parent->parent exists and it is BLACK by definition of RedBlackTree.
            if (node->parent == node->parent->parent->left)
            {
                Node *uncle = node->parent->parent->right;
                if (uncle == nullptr || uncle->color == BLACK)
                {
                    if (node == node->parent->right)
                    {
                        //          (B)              (B)
                        //          / \             /   \
						//        (R)       or    (R)    (B)
                        //        / \             / \    / \
						//          N(R)            N(R)
                        //          / \             / \
						//
                        node = node->parent;
                        LeftRotate(node);
                    }
                    //          (B)              (B)
                    //          / \             /   \
					//        (R)       or    (R)   (B)
                    //        / \             / \   / \
					//      N(R)           N(R)
                    //      / \             / \
						//
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    //          (R)              (R)
                    //          / \             /   \
					//        (B)       or    (B)   (B)
                    //        / \             / \   / \
					//     N(R)            N(R)
                    //      / \             / \
					//
                    RightRotate(node->parent->parent);
                    //          (B)              (B)
                    //          / \             /   \
					//       N(R) (R)   or   N(R)   (R)
                    //        / \ / \         / \   / \
					//                                (B)
                    //                                / \
					//
                }
                else
                {
                    //           (B)
                    //          /   \
					//        (R)   (R)
                    //         |
                    //        (R)
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    //           (R)
                    //          /   \
					//        (B)   (B)
                    //         |
                    //        (R)
                    node = node->parent->parent;
                }
            }
            else if (node->parent == node->parent->parent->right)
            {
                Node *uncle = node->parent->parent->left;
                if (uncle == nullptr || uncle->color == BLACK)
                {
                    if (node == node->parent->left)
                    {
                        //          (B)              (B)
                        //          / \             /   \
						//            (R)    or   (B)   (R)
                        //            / \         / \   / \
						//         N(R)               N(R)
                        //          / \               / \
						//
                        node = node->parent;
                        RightRotate(node);
                    }
                    //          (B)              (B)
                    //          / \             /   \
					//            (R)    or   (B)   (R)
                    //            / \         / \   / \
					//              N(R)               N(R)
                    //              / \               / \
					//
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    //          (R)              (R)
                    //          / \             /   \
					//            (B)    or   (B)   (B)
                    //            / \         / \   / \
					//              N(R)              N(R)
                    //              / \               / \
					//
                    LeftRotate(node->parent->parent);
                    //          (B)              (B)
                    //          / \             /   \
					//        (R) N(R)    or   (R)  N(R)
                    //        / \ / \         / \   / \
					//                      (B)
                    //                      / \
					//
                }
                else
                {
                    //           (B)
                    //          /   \
					//        (R)   (R)
                    //               |
                    //              (R)
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    //           (R)
                    //          /   \
					//        (B)   (B)
                    //               |
                    //              (R)
                    node = node->parent->parent;
                }
            }
        }

        if (node->parent == nullptr)
        {
            // node is the root
            node->color = BLACK;
        }
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

    //      N(B)
    //     /   \
	//         (R)
    //         / \
	//
    //       N(B)
    //       /   \
	//     (R)
    //     / \
	//
    // Subtree at node has BLACK height one less than its sibling
    // Need to fix it
    void DeleteFixUp(Node *node)
    {
        if (node == nullptr)
            return;

        while (node->parent != nullptr && node->color == BLACK)
        {
            if (node == node->parent->left)
            {
                //      ( )
                //     /   \
				//   N(B)  ( )
                //
                Node *sibling = node->parent->right;

                if (sibling->color == RED)
                {
                    // sibling is RED and its children are BLACK
                    //          ( )
                    //         /   \
					//       N(B)  S(R)
                    //             / \
					//           (B) (B)
                    //
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    //          (R)
                    //         /   \
					//       N(B)  S(B)
                    //             / \
					//           (B) (B)
                    //
                    // Now node's BLACK height is two less than its sibling's
                    //
                    LeftRotate(node->parent);
                    //          S(B)
                    //         /   \
					//       (R)  (B)
                    //       / \
					//    N(B) (B)
                    //
                    sibling = node->parent->right;
                    //          (B)
                    //         /   \
					//       (R)  (B)
                    //       / \
					//    N(B) S(B)
                    //
                    // Now node's BLACK height is one less than its new sibling's
                }

                //      ( )
                //     /   \
				//   N(B) S(B)
                //
                // Now sibling is BLACK, and node's BLACK height is one less than its sibling's

                if (sibling->left != nullptr && sibling->left->color == RED || sibling->right != nullptr && sibling->right->color == RED)
                {
                    //       ( )               ( )              ( )
                    //       / \               / \              / \
					//    N(B) S(B)         N(B) S(B)        N(B) S(B)
                    //         / \               / \              / \
					//       (R) (B)           (B) (R)          (R) (R)
                    //

                    if (sibling->right != nullptr && sibling->right->color == BLACK)
                    {
                        //       ( )
                        //       / \
						//    N(B) S(B)
                        //         / \
						//       (R) (B)
                        //       / \
						//     (B) (B)
                        //
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        //       ( )
                        //       / \
						//    N(B) S(R)
                        //         / \
						//       (B) (B)
                        //       / \
						//     (B) (B)
                        //
                        RightRotate(sibling);
                        //       ( )
                        //       / \
						//    N(B) (B)
                        //         / \
						//       (B) S(R)
                        //           / \
						//         (B) (B)
                        //
                        sibling = node->parent->right;
                        //       ( )
                        //       / \
						//    N(B) S(B)
                        //         / \
						//       (B) (R)
                        //           / \
						//         (B) (B)
                        //
                        // node's BLACK height is still one less than its sibling's,
                        // and its sibling->right is RED
                    }

                    // Now sibling->right is RED and has two BLACK children
                    //       ( )
                    //       / \
					//    N(B) S(B)
                    //         / \
					//       ( ) (R)
                    //           / \
					//         (B) (B)
                    //
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    //       (B)
                    //       / \
					//    N(B) S( )
                    //          / \
					//        ( ) (B)
                    //            / \
					//          (B) (B)
                    //
                    LeftRotate(node->parent);
                    //       S( )
                    //       /   \
					//     (B)    (B)
                    //    /  \     / \
					//  N(B) ( ) (B) (B)
                    //
                    // Now node is fixed.
                    node = this->root;
                    break;
                }
                else
                {
                    // sibling must have at least one child
                    //       ( )               ( )              ( )
                    //       / \               / \              / \
					//    N(B) S(B)         N(B) S(B)        N(B) S(B)
                    //           \               /                / \
					//           (B)           (B)              (B) (B)
                    sibling->color = RED;
                    node = node->parent;
                    //      N( )              N( )             N( )
                    //       / \               / \              / \
					//     (B) S(R)          (B) S(R)         (B) S(R)
                    //           \               /                / \
					//           (B)           (B)              (B) (B)
                    // Now node children trees have the same BLACK heights.
                    // But node itself still has its BLACK height one less than its sibling's
                }
            }
            else
            {
                //      ( )
                //     /   \
				//   ( )  N(B)
                //
                Node *sibling = node->parent->left;

                if (sibling->color == RED)
                {
                    // sibling is RED and its children are BLACK
                    //          ( )
                    //         /   \
					//       S(R)  N(B)
                    //       / \
					//     (B) (B)
                    //
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    //          (R)
                    //         /   \
					//       S(B)  N(B)
                    //       / \
					//     (B) (B)
                    //
                    // Now node's BLACK height is two less than its sibling's
                    //
                    RightRotate(node->parent);
                    //          S(B)
                    //         /   \
					//       (B)   (R)
                    //             / \
					//           (B) N(B)
                    //
                    sibling = node->parent->left;
                    //          (B)
                    //         /   \
					//       (B)   (R)
                    //             / \
					//          S(B) N(B)
                    //
                    // Now node's BLACK height is one less than its new sibling's
                }

                //      ( )
                //     /   \
				//   S(B) N(B)
                //
                // Now sibling is BLACK, and node's BLACK height is one less than its sibling's

                if (sibling->left != nullptr && sibling->left->color == RED || sibling->right != nullptr && sibling->right->color == RED)
                {
                    //       ( )               ( )              ( )
                    //       / \               / \              / \
					//    S(B) N(B)         S(B) N(B)        S(B) N(B)
                    //     / \               / \              / \
					//   (R) (B)           (B) (R)          (R) (R)
                    //
                    if (sibling->left != nullptr && sibling->left->color == BLACK)
                    {
                        //       ( )
                        //       / \
						//    S(B) N(B)
                        //     / \
						//   (B) (R)
                        //       / \
						//     (B) (B)
                        //
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        //       ( )
                        //       / \
						//    S(R) N(B)
                        //     / \
						//   (B) (B)
                        //       / \
						//     (B) (B)
                        //
                        LeftRotate(sibling);
                        //       ( )
                        //       / \
						//     (B) N(B)
                        //     / \
						//   S(R) (B)
                        //   / \
						// (B) (B)
                        //
                        sibling = node->parent->left;
                        //       ( )
                        //       / \
						//     S(B) N(B)
                        //     / \
						//   (R) (B)
                        //   / \
						// (B) (B)
                        //
                        // node's BLACK height is still one less than its sibling's,
                        // and its sibling->right is RED
                    }

                    // Now sibling->left is RED and has two BLACK children
                    //       ( )
                    //       / \
					//     S(B) N(B)
                    //     / \
					//   (R) ( )
                    //   / \
					// (B) (B)
                    //
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    //       (B)
                    //       / \
					//     S( ) N(B)
                    //     / \
					//   (B) ( )
                    //   / \
					// (B) (B)
                    //
                    RightRotate(node->parent);
                    //       S( )
                    //       /   \
					//     (B)    (B)
                    //     / \    / \
					//   (B) (B) ( ) N(B)
                    //
                    // Now node is fixed.
                    node = this->root;
                    break;
                }
                else
                {
                    // sibling must have at least one child
                    //       ( )               ( )              ( )
                    //       / \               / \              / \
					//    S(B) N(B)         S(B) N(B)        S(B) N(B)
                    //     /                  \               / \
					//   (B)                  (B)           (B) (B)
                    sibling->color = RED;
                    node = node->parent;
                    //       N( )              N( )             N( )
                    //       / \               / \              / \
					//    S(R) (B)         S(R)  (B)        S(R)  (B)
                    //     /                  \               / \
					//   (B)                  (B)           (B) (B)
                    // Now node children trees have the same BLACK heights.
                    // But node itself still has its BLACK height one less than its sibling's
                }
            }
        }

        node->color = BLACK;
    }

    // Case 3
    //      P( )          P( )
    //     /   \         /   \
	//   N(B)  (B)     (B)  N(B)
    //   / \   / \     / \   / \
	//        () ()   () ()
    // where () could be NULL or (R)
    //
    // Case 4
    //      P(B)               P(B)
    //     /   \              /   \
	//   N(B)  (R)          (R)  N(B)
    //   / \   / \          / \   / \
	//       (B) (B)      (B) (B)
    //      / \   / \    / \   / \
	//     () () () ()  () () () ()
    // where () could be NULL or (R)
    //
    // node points to the BLACK node been deleted
    // Need to fix the subtree at its parent node
    void DeleteFix(Node *parent, Node *node)
    {
        Node *sibling;
        if (node == parent->left)
        {
            sibling = parent->right;
            if (sibling->color == BLACK && parent->color == RED)
            {
                //      P(R)
                //     /   \
				//   N(B)  S(B)
                //   / \   / \
				//        () ()
                // where () could be NULL or (R)
                //
                if (sibling->left == nullptr)
                {
                    //      P(R)
                    //     /   \
					//   N(B)  S(B)
                    //   / \   / \
					//           ()
                    // where () could be NULL or (R)
                    //
                    // After N(B) is deleted,
                    LeftRotate(parent);
                    //      S(B)
                    //     /   \
					//    P(R) ()
                    //    / \
					//
                    return;
                }

                if (sibling->left != nullptr)
                {
                    //      P(R)
                    //     /   \
					//   N(B)  S(B)
                    //   / \   / \
					//       (R) ()
                    // where () could be NULL or (R)
                    //
                    // After N(B) is deleted,
                    Node *c = sibling->left;
                    sibling->left = nullptr;
                    c->right = sibling;
                    sibling->parent = c;
                    // P(R)    C(R)
                    //        /   \
					//            S(B)
                    //            / \
					//              ()
                    //
                    Transplant(parent, c);
                    parent->right = nullptr;
                    c->left = parent;
                    parent->parent = c;
                    parent->color = BLACK;
                    //         C(R)
                    //        /   \
					//      P(B)   S(B)
                    //      / \   / \
					//              ()
                    //
                    return;
                }
            }

            if (sibling->color == BLACK && parent->color == BLACK)
            {
                //      P(B)
                //     /   \
				//   N(B)  S(B)
                //   / \   / \
				//        () ()
                // where () could be NULL or (R)
                //
                if (sibling->left == nullptr && sibling->right == nullptr)
                {
                    //      P(B)
                    //     /   \
					//   N(B)  S(B)
                    //   / \   / \
					//
                    // After node is deleted,
                    //      P(B)
                    //     /   \
					//         S(B)
                    //         / \
					//
                    sibling->color = RED;
                    DeleteFixUp(parent);
                    return;
                }

                if (sibling->left == nullptr && sibling->right != nullptr)
                {
                    //      P(B)
                    //     /   \
					//   N(B)  S(B)
                    //   / \   / \
					//           (R)
                    //
                    // After node is deleted,
                    LeftRotate(parent);
                    //      S(B)
                    //     /   \
					//   P(B)  (R)
                    //   / \   / \
					//
                    sibling->right->color = BLACK;
                    //      S(B)
                    //     /   \
					//   P(B)   (B)
                    //   / \   / \
					//
                    return;
                }

                if (sibling->left != nullptr && sibling->left->color == RED)
                {
                    //      P(B)
                    //     /   \
					//   N(B)  S(B)
                    //   / \   / \
					//       (R) ()
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    Node *c = sibling->left;
                    Transplant(parent, c);
                    sibling->left = nullptr;
                    c->right = sibling;
                    sibling->parent = c;
                    //  P(B)     C(R)
                    //          /   \
					//              S(B)
                    //              / \
					//                ( )
                    //
                    parent->right = nullptr;
                    c->left = parent;
                    parent->parent = c;
                    c->color = BLACK;
                    //           C(B)
                    //          /   \
					//        P(B)  S(B)
                    //        / \   / \
					//                ( )
                    //
                    return;
                }
            }

            if (sibling->color == RED)
            {
                //      P(B)
                //     /   \
				//   N(B)  (R)
                //   / \   / \
				//       (B) (B)
                //      / \   / \
				//     () () () ()
                // where () could be NULL or (R)
                //
                if (sibling->left->left == nullptr && sibling->left->right == nullptr)
                {
                    //      P(B)
                    //     /   \
					//   N(B)  S(R)
                    //   / \   / \
					//       (B) (B)
                    //      / \   / \
					//           () ()
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    sibling->left->color = RED;
                    //      P(B)
                    //     /   \
					//         S(R)
                    //         / \
					//       (R) (B)
                    //      / \   / \
					//           () ()
                    // where () could be NULL or (R)
                    //
                    LeftRotate(parent);
                    //      S(R)
                    //     /   \
					//   P(B)   (B)
                    //   / \    / \
					//     (R) () ()
                    //     / \
					//
                    sibling->color = BLACK;
                    //      S(B)
                    //     /   \
					//   P(B)   (B)
                    //   / \    / \
					//     (R) () ()
                    //     / \
					//
                    return;
                }

                if (sibling->left->right != nullptr)
                {
                    //      P(B)
                    //     /   \
					//   N(B)  S(R)
                    //   / \   / \
					//       (B) (B)
                    //      / \   / \
					//     () (R)() ()
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    sibling->left->right->color = BLACK;
                    //      P(B)
                    //     /   \
					//         S(R)
                    //         / \
					//       (B)  (B)
                    //      / \   / \
					//     () (B)() ()
                    //
                    RightRotate(sibling);
                    //      P(B)
                    //     /   \
					//         (B)
                    //         / \
					//       ()   S(R)
                    //            / \
					//          (B)  (B)
                    //               / \
					//              () ()
                    //
                    LeftRotate(parent);
                    //         (B)
                    //        /   \
					//      P(B)   S(R)
                    //      / \    /  \
					//        () (B)  (B)
                    //                / \
					//               () ()
                    //
                    return;
                }

                if (sibling->left->left != nullptr && sibling->left->right == nullptr)
                {
                    //      P(B)
                    //     /   \
					//   N(B)  S(R)
                    //   / \   / \
					//       (B) (B)
                    //      / \   / \
					//    (R)    () ()
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    Node *c = sibling->left->left;
                    Transplant(parent, c);
                    sibling->left->left = nullptr;
                    c->right = sibling;
                    sibling->parent = c;
                    // P(B)    C(R)
                    //        /   \
					//            S(R)
                    //            / \
					//          (B)  (B)
                    //         / \   / \
					//              () ()
                    //
                    parent->right = nullptr;
                    c->left = parent;
                    parent->parent = c;
                    c->color = BLACK;
                    //         C(B)
                    //        /   \
					//      P(B)  S(R)
                    //            / \
					//          (B)  (B)
                    //          / \  / \
					//              () ()
                    //
                    return;
                }
            }
        }

        if (node == parent->right)
        {
            sibling = parent->left;
            if (sibling->color == BLACK && parent->color == RED)
            {
                //       P(R)
                //       /   \
				//     S(B)  N(B)
                //     / \   / \
				//    () ()
                // where () could be NULL or (R)
                //
                if (sibling->right == nullptr)
                {
                    //       P(R)
                    //       /   \
					//     S(B)  N(B)
                    //     / \   / \
					//    ()
                    // where () could be NULL or (R)
                    //
                    // After N(B) is deleted,
                    RightRotate(parent);
                    //        S(B)
                    //       /   \
					//      ()   P(R)
                    //           / \
					//
                    return;
                }

                if (sibling->right != nullptr)
                {
                    //       P(R)
                    //       /   \
					//     S(B)  N(B)
                    //     / \   / \
					//    () (R)
                    // where () could be NULL or (R)
                    //
                    // After N(B) is deleted,
                    Node *c = sibling->right;
                    sibling->right = nullptr;
                    c->left = sibling;
                    sibling->parent = c;
                    //         C(R)      P(R)
                    //        /   \
					//      S(B)
                    //      / \
					//     ()
                    //
                    Transplant(parent, c);
                    parent->left = nullptr;
                    c->right = parent;
                    parent->parent = c;
                    parent->color = BLACK;
                    //         C(R)
                    //        /   \
					//      S(B)  P(B)
                    //      / \
					//     ()
                    //
                    return;
                }
            }

            if (sibling->color == BLACK && parent->color == BLACK)
            {
                //       P(B)
                //       /   \
				//     S(B)  N(B)
                //     / \   / \
				//    () ()
                // where () could be NULL or (R)
                //
                if (sibling->right == nullptr && sibling->left == nullptr)
                {
                    //       P(B)
                    //       /   \
					//     S(B) N(B)
                    //     / \   / \
					//
                    // After node is deleted,
                    //       P(B)
                    //       /   \
					//     S(B)
                    //     / \
					//
                    sibling->color = RED;
                    DeleteFixUp(parent);
                    return;
                }

                if (sibling->right == nullptr && sibling->left != nullptr)
                {
                    //       P(B)
                    //       /   \
					//     S(B) N(B)
                    //     / \   / \
					//   (R)
                    //
                    // After node is deleted,
                    RightRotate(parent);
                    //        S(B)
                    //       /   \
					//     (R)   P(B)
                    //     / \   / \
					//
                    sibling->left->color = BLACK;
                    //        S(B)
                    //       /   \
					//     (B)   P(B)
                    //     / \   / \
					//
                    return;
                }

                if (sibling->right != nullptr && sibling->right->color == RED)
                {
                    //       P(B)
                    //       /   \
					//     S(B)  N(B)
                    //     / \   / \
					//    () (R)
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    Node *c = sibling->right;
                    Transplant(parent, c);
                    sibling->right = nullptr;
                    c->left = sibling;
                    sibling->parent = c;
                    //         C(R)        P(B)
                    //        /   \
					//      S(B)
                    //      / \
					//    ()
                    //
                    parent->left = nullptr;
                    c->right = parent;
                    parent->parent = c;
                    c->color = BLACK;
                    //        C(B)
                    //       /   \
					//     S(B)  P(B)
                    //     / \   / \
					//    ()
                    //
                    return;
                }
            }

            if (sibling->color == RED)
            {
                //          P(B)
                //         /   \
				//       (R)  N(B)
                //       / \   / \
				//     (B) (B)
                //    / \   / \
				//   () () () ()
                // where () could be NULL or (R)
                //
                if (sibling->right->left == nullptr && sibling->right->right == nullptr)
                {
                    //          P(B)
                    //         /   \
					//       S(R)  N(B)
                    //       / \   / \
					//     (B) (B)
                    //    / \   / \
					//   () ()
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    sibling->right->color = RED;
                    //          P(B)
                    //         /   \
					//       S(R)
                    //       / \
					//     (B) (R)
                    //    / \   / \
					//   () ()
                    RightRotate(parent);
                    //           S(R)
                    //          /   \
					//        (B)   P(B)
                    //        / \   / \
					//       () () (R)
                    //             / \
					//
                    sibling->color = BLACK;
                    //           S(B)
                    //          /   \
					//        (B)   P(B)
                    //        / \   / \
					//       () () (R)
                    //             / \
					//
                    return;
                }

                if (sibling->right->left != nullptr)
                {
                    //          P(B)
                    //         /   \
					//       S(R)  N(B)
                    //       / \   / \
					//     (B) (B)
                    //    / \   / \
					//   () ()(R) ()
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    sibling->right->left->color = BLACK;
                    //          P(B)
                    //         /   \
					//       S(R)
                    //       / \
					//     (B) (B)
                    //    / \   / \
					//   () ()(B) ()
                    LeftRotate(sibling);
                    //           P(B)
                    //          /   \
					//        (B)
                    //        / \
					//      S(R) ()
                    //      / \
					//   (B)  (B)
                    //   / \
					//  () ()
                    //
                    RightRotate(parent);
                    //           (B)
                    //          /   \
					//       S(R)   P(B)
                    //       / \    / \
					//     (B) (B) ()
                    //     / \
					//    () ()
                    //
                    return;
                }

                if (sibling->right->right != nullptr && sibling->right->left == nullptr)
                {
                    //          P(B)
                    //         /   \
					//       S(R)  N(B)
                    //       / \   / \
					//     (B) (B)
                    //    / \   / \
					//   () ()    (R)
                    // where () could be NULL or (R)
                    //
                    // After node is deleted,
                    Node *c = sibling->right->right;
                    Transplant(parent, c);
                    sibling->right->right = nullptr;
                    c->left = sibling;
                    sibling->parent = c;
                    //           C(R)       P(B)
                    //          /   \
					//        S(R)
                    //        / \
					//     (B)  (B)
                    //    / \   / \
					//   () ()
                    //
                    parent->left = nullptr;
                    c->right = parent;
                    parent->parent = c;
                    c->color = BLACK;
                    //            C(B)
                    //           /   \
					//         S(R)  P(B)
                    //         / \
					//      (B)  (B)
                    //     / \   / \
					//    () ()
                    //
                    return;
                }
            }
        }
    }

    void Delete(Node *node)
    {
        if (node == nullptr)
            return;

        Color original = node->color;

        if (node->left == nullptr && node->right == nullptr)
        {
            if (node == this->root)
            {
                // Case 0
                //    N( )
                //     / \
				//
                delete node;
                this->root = nullptr;
                return;
            }

            Node *sibling = nullptr;
            if (node == node->parent->left)
            {
                sibling = node->parent->right;
                node->parent->left = nullptr;
            }
            else
            {
                sibling = node->parent->left;
                node->parent->right = nullptr;
            }

            delete node;

            if (original == RED)
            {
                // Case 1
                //      (B)         (B)
                //     /   \       /   \
				//   N(R)             N(R)
                //   / \               / \
				//
                // Case 2
                //      (B)          (B)
                //     /   \        /   \
				//   N(R)  (R)    (R)  N(R)
                //   / \   / \    / \   / \
				//
                return;
            }

            if (original == BLACK)
            {
                // Case 3
                //      ( )           ( )
                //     /   \         /   \
				//   N(B)  (B)     (B)  N(B)
                //   / \   / \     / \   / \
				//        () ()   () ()
                // where () could be NULL or (R)
                //
                // Case 4
                //      (B)                (B)
                //     /   \              /   \
				//   N(B)  (R)          (R)  N(B)
                //   / \   / \          / \   / \
				//       (B) (B)      (B) (B)
                //      / \   / \    / \   / \
				//     () () () ()  () () () ()
                // where () could be NULL or (R)
                //
                // After node is deleted, its position becomes nullptr
                DeleteFix(sibling->parent, nullptr);
                return;
            }
        }

        if (node->left == nullptr)
        {
            // Case 5
            //   ( )
            //    |
            //   N(B)
            //   /  \
			//      (R)
            //      / \
			//
            Node *right = node->right;
            right->color = BLACK;
            Transplant(node, right);
            delete node;
            //   ( )
            //    |
            //   (B)
            //   / \
			//
            return;
        }

        if (node->right == nullptr)
        {
            // Case 6
            //    ( )
            //     |
            //    N(B)
            //    /  \
			//  (R)
            //  / \
			//
            Node *left = node->left;
            left->color = BLACK;
            Transplant(node, left);
            delete node;
            //    ( )
            //     |
            //    (B)
            //    / \
			//
            return;
        }

        Node *successor = Node::Min(node->right);
        original = successor->color;

        if (successor == node->right && successor->right == nullptr)
        {
            // Case 7
            //     ( )
            //      |
            //     N( )
            //     /  \
			//  ( )    S( )
            //  / \    / \
			//
            Transplant(node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
            original = successor->color;
            successor->color = node->color;
            delete node;
            //     ( )
            //      |
            //     S( )
            //     /  \
			//  ( )
            //  / \
			//
            if (original == BLACK)
            {
                DeleteFix(successor, nullptr);
            }

            return;
        }

        if (successor == node->right && successor->right != nullptr)
        {
            // Case 8
            //     ( )
            //      |
            //     N( )
            //     /  \
			//  ( )    S(B)
            //  / \    / \
			//           (R)
            //
            Transplant(node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
            successor->color = node->color;
            successor->right->color = BLACK;
            delete node;
            //     ( )
            //      |
            //     S( )
            //     /  \
			//  ( )    (B)
            //  / \
			//
            return;
        }

        if (successor != node->right && successor->right == nullptr)
        {
            // Case 9
            //     ( )
            //      |
            //     N( )
            //     /  \
			//  ( )    ( )
            //  / \    /  \
			//		 S( ) ( )
            //       / \
			//
            Node *parent = successor->parent;
            parent->left = nullptr;
            successor->right = node->right;
            successor->right->parent = successor;
            //     ( )
            //      |
            //     N( )
            //     /  \
			//   ( )
            //   / \   S( )
            //          / \  
			//            ( )
            //            /  \
			//		         ( )
            //
            Transplant(node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
            original = successor->color;
            successor->color = node->color;
            delete node;
            if (original == BLACK)
            {
                DeleteFix(parent, nullptr);
            }

            return;
        }

        if (successor != node->right && successor->right != nullptr)
        {
            // Case 10
            //     ( )
            //      |
            //     N( )
            //     /  \
			//  ( )    ( )
            //  / \    /  \
			//		 S(B) ( )
            //       / \
			//         (R)
            //         / \
			//
            successor->right->color = BLACK;
            Transplant(successor, successor->right);
            //     ( )
            //      |
            //     N( )
            //     /  \
			//  ( )    ( )
            //  / \    /  \
			//		 (B) ( )       S(B)
            //       / \
			//
            successor->right = node->right;
            successor->right->parent = successor;
            //     ( )
            //      |
            //     N( )
            //     /  \
			//   ( )
            //   / \   S(B)
            //         / \  
			//           ( )
            //           /  \
			//         (B) ( )
            //         / \
			//
            Transplant(node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
            successor->color = node->color;
            delete node;
            return;
        }
    }

public:
    RedBlackTree(void) : root(nullptr) {}

    void Empty(void)
    {
        if (this->root != nullptr)
        {
            Node::Empty(this->root);
            delete this->root;
            this->root = nullptr;
        }
    }

    ~RedBlackTree() { Empty(); }

    void Insert(const T &content)
    {
        Node *newNode = new Node(content);

        if (this->root == nullptr)
        {
            // The new node becomes the root.
            // The root must be BLACK in a RedBlackTree.
            this->root = newNode;
            this->root->color = BLACK;
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

        if (parent->color == BLACK)
        {
            // Nothing else
            return;
        }
        else if (parent->color == RED)
        {
            // Both newNode and parent are RED
            if (parent->parent == nullptr)
            {
                // parent is root
                parent->color = BLACK;
            }
            else
            {
                // parent is not root
                InsertFixUp(newNode);
                while (this->root->parent != nullptr)
                {
                    this->root = this->root->parent;
                }
            }
        }
    }

    int BlackHeight(void)
    {
        return Node::BlackHeight(this->root);
    }

    int BlackHeight2(void)
    {
        return Node::BlackHeight2(this->root);
    }

    bool Verify(void)
    {
        return Node::Verify(this->root);
    }

    void Delete(const T &content)
    {
        Node *node = Node::Search(this->root, content);
        if (node == nullptr)
            return;
        Delete(node);
    }

    void Print(void)
    {
        if (this->root != nullptr)
            this->root->Print();
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

template <class T>
class Node
{
private:
    void Expand(size_t i)
    {
        if (i >= this->neighbor.size())
        {
            this->neighbor.insert(this->neighbor.end(), i - this->neighbor.size() + 1, nullptr);
        }
    }

protected:
    T data;
    vector<Node *> neighbor;

public:
    Node(const T &d) : data(d) {}

    Node(const T &d, size_t n) : data(d)
    {
        this->neighbor = vector<Node *>(n, nullptr);
    }

    Node(size_t n)
    {
        this->neighbor = vector<Node *>(n, nullptr);
    }

    virtual ~Node(void)
    {
        for (size_t i = 0; i < this->neighbor.size(); i++)
        {
            this->neighbor[i] = nullptr;
        }
    }

    const T &Data(void) const { return this->data; }

    T &Data(void) { return this->data; }

    void Data(const T &d) { this->data = d; }

    Node *&Neighbor(size_t i)
    {
        Expand(i);
        return (Node *&)this->neighbor[i];
    }

    void Neighbor(size_t i, Node *n)
    {
        Expand(i);
        this->neighbor[i] = n;
    }

    size_t CountNeighbors(void) { return this->neighbor.size(); }

    // Deep clone a graph at node
    static Node *Clone(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        queue<Node<T> *> q;
        map<Node<T> *, Node<T> *> cloned;
        Node<T> *nodeCopy = new Node<T>(node->Data(), node->CountNeighbors());
        q.push(node);
        cloned[node] = nodeCopy;
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            for (size_t i = 0; i < node->CountNeighbors(); i++)
            {
                Node<T> *n = node->Neighbor(i);
                if (n != nullptr)
                {
                    if (cloned.find(n) == cloned.end())
                    {
                        Node<T> *nCopy = new Node<T>(n->Data(), n->CountNeighbors());
                        cloned[n] = nCopy;
                        q.push(n);
                    }
                    cloned[node]->Neighbor(i) = cloned[n];
                }
            }
        }
        return nodeCopy;
    }

    virtual Node *Clone(void) { return Clone(this); }
};

template <class T>
class Node1 : public Node<T>
{
protected:
    Node *first;

public:
    Node1(const T &v) : Node(v), first(nullptr) {}

    virtual ~Node1(void)
    {
        if (this->first != nullptr)
        {
            this->first = nullptr;
        }
    }

    virtual Node1 *Search(const T &v)
    {
        Node1 *p = this;
        while (nullptr != p && p->value != v)
        {
            p = (Node1 *)p->first;
        }

        // p == nullptr || p->value == v
        return p;
    }
    virtual bool Contain(const T &v) { return nullptr != Search(v); }
};

template <class T>
class Node2 : public Node1<T>
{
protected:
    Node *second;

public:
    Node2(const T &v) : Node1(v), second(nullptr) {}

    virtual ~Node2(void)
    {
        if (this->second != nullptr)
        {
            this->second = nullptr;
        }
    }

    static Node2 *Clone(Node2 *node)
    {
        if (node == nullptr)
            return nullptr;
        queue<Node2<T> *> q;
        map<Node2<T> *, Node2<T> *> cloned;
        Node2<T> *nodeCopy = new Node2<T>(node->value);
        q.push(node);
        cloned[node] = nodeCopy;
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            if (node->first != nullptr)
            {
                if (cloned.find((Node2<T> *)node->first) == cloned.end())
                {
                    Node2<T> *firstCopy = new Node2<T>(((Node2<T> *)node->first)->value);
                    cloned[(Node2<T> *)node->first] = firstCopy;
                    q.push((Node2<T> *)node->first);
                }
                cloned[node]->first = cloned[(Node2<T> *)node->first];
            }
            if (node->second != nullptr)
            {
                if (cloned.find((Node2<T> *)node->second) == cloned.end())
                {
                    Node2<T> *secondCopy = new Node2<T>(((Node2<T> *)node->second)->value);
                    cloned[(Node2<T> *)node->second] = secondCopy;
                    q.push((Node2<T> *)node->second);
                }
                cloned[node]->second = cloned[(Node2<T> *)node->second];
            }
        }
        return nodeCopy;
    }
};

template <class T>
class SingleNode : public Node<T>
{
    template <class T>
    friend ostream &operator<<(ostream &, SingleNode<T> *);

public:
    SingleNode(const T &d) : Node<T>(d, 1) {}

    ~SingleNode(void) {}

    // Get the reference of next node pointer
    SingleNode *&Next(void)
    {
        return (SingleNode *&)this->Neighbor(0);
    }

    // Set the next node pointer
    void Next(SingleNode *next)
    {
        this->Neighbor(0) = next;
    }

    // Return the last node. The list may contain a cycle or not.
    static SingleNode *Tail(SingleNode *list)
    {
        if (list == nullptr)
            return nullptr;

        SingleNode *p = list;
        size_t m = 0;
        SingleNode *q = list;
        size_t n = 0;
        while (q->Next() != nullptr && q->Next()->Next() != nullptr)
        {
            p = p->Next();
            m++;
            q = q->Next()->Next();
            n += 2;
            if (p == q)
                break;
        }

        if (q->Next() == nullptr)
            return q;
        if (q->Next()->Next() == nullptr)
            return q->Next();

        // Multiple of cycle length
        m = n - m;

        p = list;
        q = list;
        for (size_t i = 0; i < m - 1; i++)
        {
            q = q->Next();
        }

        while (p != q->Next())
        {
            p = p->Next();
            q = q->Next();
        }

        return q;
    }

    // Delete the first node with value d
    void Delete(const T &d)
    {
        SingleNode *p = this;
        if (p->Data() == d)
        {
            // This node is what we are looking for, but
            // we cannot delete itself. So we copy next node value into this one,
            // which effectively "delete" this node.
            if (p->Next() == nullptr)
                throw invalid_argument("A SingleNode cannot delete itself");
            while (p->Next()->Next() != nullptr && p->Next()->Next() != this)
            {
                p->Data() = p->Next()->Data();
                p = p->Next();
            }
            p->Data() = p->Next()->Data();
            // Now p->Next() is useless and can be deleted
        }
        else
        {
            // TODO: handle the case when the list is a cycle and v is not found
            while (p->Next() != nullptr && p->Next()->Data() != d)
            {
                p = p->Next();
            }
            // Now p->Next() is what we are looking for
        }

        if (p->Next() != nullptr)
        {
            SingleNode *q = p->Next();
            p->Next() = q->Next();
            delete q;
        }
    }

    // Delete the first node with value d. This list may contain a cycle or not.
    static SingleNode *Delete(SingleNode *list, const T &d)
    {
        if (list == nullptr)
            return nullptr;
        if (list->Data() == d && (list->Next() == nullptr || list->Next() == list))
        {
            // list->v->null, or
            // list->v-|
            //      |__|
            delete list;
            return nullptr;
        }

        SingleNode *t = Tail(list);

        if (list->Data() == d)
        {
            if (t->Next() == list)
            {
                // list->v->...->t-|
                //      |__________|
                t->Next() = list->Next();
            }
            t = list->Next();
            delete list;
            return t;
        }

        SingleNode *p = list;
        while (p != t && p->Next()->Data() != d)
            p = p->Next();

        if (p == t)
        {
            // Not found
            return list;
        }

        if (p->Next() == t->Next())
        {
            if (t->Next() == t)
            {
                // list->...->p->v-|
                //              |__|
                p->Next() = nullptr;
                delete t;
            }
            else
            {
                // list->...->p->v->...->t-|
                //              |__________|
                p->Next() = t->Next()->Next();
                p = t->Next();
                t->Next() = p->Next();
                delete p;
            }
        }
        else
        {
            // list->...->p->v->...->x->...->t-|
            //                      |__________|
            // list->...->x->...->p->v->...->t-|
            //           |_____________________|
            // list->x->...->p->v-|
            //      |_____________|
            // list->x->...->p->v->null
            t = p->Next();
            p->Next() = t->Next();
            delete t;
        }
        return list;
    }

    // Delete the list rooted at the node. This list may contain a cycle or not.
    void DeleteList(void)
    {
        SingleNode<T> *p = Tail(this);
        if (p != nullptr)
        {
            // Break the cycle if there is one
            p->Next() = nullptr;
        }
        while (this->Next() != nullptr)
        {
            p = this->Next();
            this->Next() = p->Next();
            p->Next() = nullptr;
            delete p;
        }
    }

    // Delete the list. This list may contain a cycle or not.
    static void DeleteList(SingleNode *list)
    {
        if (list == nullptr)
            return;
        SingleNode<T> *p = Tail(list);
        if (p != nullptr)
        {
            // Break the cycle if there is one
            p->Next() = nullptr;
        }
        while (list != nullptr)
        {
            p = list;
            list = list->Next();
            p->Next() = nullptr;
            delete p;
        }
    }

    // Find the beginning of cycle if exists
    static SingleNode *FindCycle(SingleNode *list)
    {
        if (list == nullptr)
            return nullptr;

        SingleNode *t = Tail(list);
        if (t == nullptr)
            return nullptr;
        return t->Next();
    }

    // Determine if the list has a cycle somewhere
    static bool HasCycle(SingleNode *list)
    {
        if (list == nullptr)
            return false;

        SingleNode *p = list;
        SingleNode *q = list;
        while (q->Next() != nullptr && q->Next()->Next() != nullptr)
        {
            p = p->Next();
            q = q->Next()->Next();
            if (p == q)
                return true;
        }

        return false;
    }

    // Insert a node or a list after this one. This list may contain a cycle or not.
    void InsertAfter(SingleNode *node)
    {
        if (node == nullptr)
            throw invalid_argument("node is nullptr");

        SingleNode *p = Tail(node);
        // p->Next() == nullptr, if node contains no cycle
        // p->Next() != nullptr, if node contains a cycle
        // If node contains a cycle, it will be broken
        p->Next() = this->Next();
        this->Next() = node;
    }

    // Insert a node or a list at the end of this list. This list may contain a cycle or not.
    void InsertAtEnd(SingleNode *node)
    {
        if (node == nullptr)
            throw invalid_argument("node is nullptr");

        SingleNode *p = Tail(this);
        // p->Next() == nullptr, if this list contains no cycle
        // p->Next() != nullptr, if this list contains a cycle

        SingleNode *q = Tail(node);
        // q->Next() == nullptr, if node contains no cycle
        // q->Next() != nullptr, if node contains a cycle

        // If node contains a cycle, it will be broken
        // If this list contains a cycle, it will be maintained
        q->Next() = p->Next();
        p->Next() = node;
    }

    // Count list nodes. The list may contain a cycle or not.
    size_t Length(void)
    {
        size_t s = 1;
        SingleNode *t = Tail(this);
        SingleNode *p = this;
        while (p != t)
        {
            s++;
            p = p->Next();
        }
        return s;
    }

    // Count list nodes. The list may contain a cycle or not.
    static size_t Length(SingleNode *list)
    {
        if (list == nullptr)
            return 0;

        SingleNode *p = list;
        size_t m = 0;
        SingleNode *q = list;
        size_t n = 0;
        while (q->Next() != nullptr && q->Next()->Next() != nullptr)
        {
            p = p->Next();
            m++;
            q = q->Next()->Next();
            n += 2;
            if (p == q)
                break;
        }

        if (q->Next() == nullptr)
            return n + 1;
        if (q->Next()->Next() == nullptr)
            return n + 2;

        // Multiple of cycle length
        m = n - m;

        p = list;
        q = list;
        for (size_t i = 0; i < m - 1; i++)
        {
            q = q->Next();
        }

        n = 0;
        while (p != q->Next())
        {
            p = p->Next();
            q = q->Next();
            n++;
        }

        while (p != q)
        {
            p = p->Next();
            n++;
        }

        return n + 1;
    }

    // Return the n-th node when this list contains (2n-1) or 2n nodes.
    // The list may contain a cycle or not.
    SingleNode *Middle(void) { return Middle(this); }

    // Return the n-th node when this list contains (2n-1) or 2n nodes.
    // The list may contain a cycle or not.
    static SingleNode *Middle(SingleNode *list)
    {
        if (list == nullptr)
            return nullptr;

        SingleNode *t = Tail(list);
        if (t == nullptr)
            return nullptr;

        // Start from the first (1-th) node.
        SingleNode *middle = list;
        SingleNode *p = list;

        while (p != t && p->Next() != t)
        {
            // p visits the (2n-1)-th node.
            p = p->Next()->Next();
            // middle visits the n-th node.
            middle = middle->Next();
        }

        return middle;
    }

    // Reorder single-link list
    // (1)  0 -> 1 -> 2 -> ...... -> n-1 -> n -> n+1 -> ...... 2n-1 -> nullptr
    //      0 -> 2n-1 -> 1 -> 2n-2 -> 2 -> ...... -> n-2 -> n+1 -> n-1 -> n -> nullptr
    // (2)  0 -> 1 -> 2 -> ...... -> n-1 -> n -> n+1 -> ...... 2n-1 -> 2n nullptr
    //      0 -> 2n -> 1 -> 2n-1 -> 2 -> ...... -> n+2 -> n-1 -> n+1 -> n -> nullptr
    static void Reorder(SingleNode *node)
    {
        if (node == nullptr)
            return;

        // Find the middle node
        SingleNode *m = node;
        SingleNode *p = node;
        while (p->Next() != nullptr && p->Next()->Next() != nullptr)
        {
            m = m->Next();
            p = p->Next()->Next();
        }

        if (m == node)
        {
            // Only one node or two nodes
            return;
        }

        // m's index is (n-1) or n, depending on whether the list has 2n or 2n+1 nodes

        // Break the list at the middle
        SingleNode *second = m->Next();
        m->Next() = nullptr;

        // Reverse the second half of list
        if (second->Next() != nullptr)
        {
            p = second;
            m = p->Next();
            SingleNode *q = m->Next();
            p->Next() = nullptr;
            while (m != nullptr && q != nullptr)
            {
                m->Next() = p;
                p = m;
                m = q;
                q = m->Next();
            }
            m->Next() = p;
            second = m;
        }

        // Merge two lists
        m = node;
        while (second != nullptr)
        {
            p = second;
            second = p->Next();
            p->Next() = m->Next();
            m->Next() = p;
            m = p->Next();
        }
    }

    // Reverse this node and return the head of new list.
    // The list may be a cycle or not.
    SingleNode *Reverse(void) { return return Reverse(this); }

    // Reverse this node and return the head of new list.
    // The list may contain a cycle or not.
    static SingleNode *Reverse(SingleNode *list)
    {
        if (list == nullptr || list->Next() == nullptr)
            return list;
        SingleNode *t = Tail(list);
        if (t == nullptr)
            return list;

        SingleNode *p = list;
        SingleNode *m = list->Next();
        SingleNode *n = m->Next();
        while (m != t)
        {
            m->Next() = p;
            p = m;
            m = n;
            n = n->Next();
        }
        m->Next() = p;
        list->Next() = n == list ? m : nullptr;
        return m;
    }

    // Create a random list, no cycle
    static SingleNode *RandomList(size_t length)
    {
        if (length == 0)
            return nullptr;
        SingleNode<T> *list = new SingleNode<T>(rand());
        SingleNode<T> *p = list;
        for (size_t i = 1; i < length; i++)
        {
            p->Next() = new SingleNode<T>(rand());
            p = p->Next();
        }
        return list;
    }

    // Sort a single link list or a circular list
    static void Sort(SingleNode<T> *&list)
    {
        if (list == nullptr || list->Next() == nullptr || list->Next() == list)
            return;

        bool circular = false;
        SingleNode<T> *e = list;
        while (e->Next() != nullptr && e->Next() != list)
        {
            e = e->Next();
        }
        if (e->Next() == list)
            circular = true;

        SingleNode<T> *q = list;
        while (q->Next() != nullptr && q->Next() != list)
        {
            if (q->Next()->Value() < list->Value())
            {
                SingleNode<T> *t = q->Next();
                if (circular)
                {
                    if (t->Next() != list)
                    {
                        q->Next() = t->Next();
                        t->Next() = list;
                        e->Next() = t;
                    }
                }
                else
                {
                    q->Next() = t->Next();
                    t->Next() = list;
                }
                list = t;
            }
            else
            {
                SingleNode<T> *p = list;
                while (p != q && q->Next()->Value() >= p->Next()->Value())
                {
                    p = p->Next();
                }
                if (p == q)
                {
                    q = q->Next();
                }
                else
                {
                    SingleNode<T> *t = q->Next();
                    q->Next() = t->Next();
                    t->Next() = p->Next();
                    p->Next() = t;
                }
            }
        }
    }
};

template <class T>
ostream &operator<<(ostream &os, SingleNode<T> *list)
{
    os << "head";
    if (list == nullptr)
    {
        os << "->nullptr" << endl;
        return os;
    }

    SingleNode<T> *c = SingleNode<T>::FindCycle(list);
    SingleNode<T> *p = list;
    string s;
    int i = 4;
    while (p != c)
    {
        s = to_string(p->Value());
        os << "->" << s;
        i = i + 2 + s.length();
        p = p->Next();
    }

    if (p == nullptr)
    {
        os << "->nullptr" << endl;
        return os;
    }

    int j = i;
    do
    {
        s = to_string(p->Value());
        os << "->" << s;
        j = j + 2 + s.length();
        p = p->Next();
    } while (p != c);

    auto printChar = [&](int n, char c) {
        string chars(n, c);
        os << chars;
    };

    os << "-|" << endl;
    j++;
    printChar(i + 1, ' ');
    os << "|";
    printChar(j - i - 2, '_');
    os << "|" << endl;
    return os;
}

namespace MergeSort
{
// Merge two sorted single link lists
template <class T>
static void Merge(SingleNode<T> *&first, SingleNode<T> *second)
{
    if (second == nullptr)
        return;

    if (first == nullptr)
    {
        first = second;
        return;
    }

    SingleNode<T> *p;
    if (second->Value() < first->Value())
    {
        p = second->Next();
        second->Next() = first;
        first = second;
        second = p;
    }

    // Now first->Value() <= second->Value()

    p = first;
    while (p != nullptr && second != nullptr)
    {
        while (p->Next() != nullptr && p->Next()->Value() <= second->Value())
        {
            p = p->Next();
        }

        // Now p->Value() <= second->Value()

        if (p->Next() == nullptr)
        {
            // first list is done, append rest of second to first
            p->Next() = second;
            break;
        }
        else
        {
            // Insert second between p and p->Next()
            SingleNode<T> *q = second->Next();
            second->Next() = p->Next();
            p->Next() = second;
            p = second;
            second = q;
        }
    }
}

// Sort a single link list or a circular list
template <class T>
static void Sort(SingleNode<T> *&list)
{
    if (list == nullptr || list->Next() == nullptr || list->Next() == list)
        return;

    SingleNode<T> *m = list;
    SingleNode<T> *p = list;

    while (p->Next() != nullptr && p->Next() != list && p->Next()->Next() != nullptr && p->Next()->Next() != list)
    {
        // p visits the (2n-1)-th node.
        p = p->Next()->Next();
        // middle visits the n-th node.
        m = m->Next();
    }

    bool circular = false;
    if (p->Next() == list)
    {
        circular = true;
        p->Next() = nullptr;
    }
    else if (p->Next() != nullptr && p->Next()->Next() == list)
    {
        circular = true;
        p->Next()->Next() = nullptr;
    }

    SingleNode<T> *second = m->Next();
    m->Next() = nullptr;
    Sort(list);
    Sort(second);
    Merge(list, second);

    if (circular)
    {
        p = list;
        while (p->Next() != nullptr)
        {
            p = p->Next();
        }
        p->Next() = list;
    }
}
} // namespace MergeSort

template <class T>
class DoubleNode : public Node<T>
{
    template <class T>
    friend ostream &operator<<(ostream &, DoubleNode<T> *);

public:
    DoubleNode(const T &v) : Node<T>(v, 2) {}
    virtual ~DoubleNode(void) {}

    // Get the reference of previous node pointer
    DoubleNode *&Prev(void) { return (DoubleNode *&)this->Neighbor(0); }
    // Set the previous node pointer
    void Prev(DoubleNode *prev) { this->Neighbor(0) = prev; }

    // Get the reference of next node pointer
    DoubleNode *&Next(void) { return (DoubleNode *&)this->Neighbor(1); }
    // Set the next node pointer
    void Next(DoubleNode *next) { this->Neighbor(1) = next; }

    // Delete a double link list. The list may be a cycle or not.
    static void DeleteList(DoubleNode *node)
    {
        if (node == nullptr)
            return;
        DoubleNode *p;
        while (node->Next() != nullptr && node->Next() != node)
        {
            p = node->Next();
            node->Next() = p->Next();
            if (p->Next() != nullptr)
                p->Next()->Prev() = node;
            delete p;
            p = nullptr;
        }
        delete node;
        node = nullptr;
    }
};

template <class T>
ostream &operator<<(ostream &os, DoubleNode<T> *list)
{
    os << "head";
    if (list == nullptr)
    {
        os << "->nullptr" << endl;
        return os;
    }

    DoubleNode<T> *p = list;
    string s;
    int i = 4;
    do
    {
        s = to_string(p->Value());
        os << "->" << s;
        i = i + 2 + s.length();
        p = p->Next();
    } while (p != nullptr && p != list);

    if (p == nullptr)
    {
        os << "->nullptr" << endl;
        return os;
    }

    auto printChar = [&](int n, char c) {
        string chars(n, c);
        os << chars;
    };

    os << "-|" << endl;
    printChar(5, ' ');
    os << "|";
    printChar(i - 5, '_');
    os << "|" << endl;
    return os;
}

template <class T>
class BinaryNode : public Node<T>
{
public:
    BinaryNode(const T &v) : Node<T>(v, 2) {}
    virtual ~BinaryNode(void) {}

    // Delete a rooted binary tree
    static void DeleteTree(BinaryNode *node)
    {
        if (node == nullptr)
            return;
        DeleteTree(node->Left());
        DeleteTree(node->Right());
        delete node;
        node = nullptr;
    }

    virtual void DeleteTree(void) { DeleteTree(this); }

    // Create a random binary tree
    // Return nullptr if input is empty
    static BinaryNode *RandomTreeFromPreOrder(vector<T> &values)
    {
        if (values.empty())
            return nullptr;

        function<BinaryNode<T> *(vector<T> &, int, int)>
            create = [&](vector<T> &v, int i, int j) -> BinaryNode<T> * {
            if (i > j)
                return nullptr;
            BinaryNode<T> *n = new BinaryNode<T>(v[i]);
            int k = i + 1 + (rand() % (j - i + 1));
            n->Left() = create(v, i + 1, k - 1);
            n->Right() = create(v, k, j);
            return n;
        };

        BinaryNode<T> *node = create(values, 0, values.size() - 1);
        return node;
    }

    static BinaryNode *RandomTreeFromInOrder(vector<T> &values)
    {
        if (values.empty())
            return nullptr;

        function<BinaryNode<T> *(vector<T> &, int, int)>
            create = [&](vector<T> &v, int i, int j) -> BinaryNode<T> * {
            if (i > j)
                return nullptr;
            int k = i + (rand() % (j - i + 1));
            BinaryNode<T> *n = new BinaryNode<T>(v[k]);
            n->Left() = create(v, i, k - 1);
            n->Right() = create(v, k + 1, j);
            return n;
        };

        BinaryNode<T> *node = create(values, 0, values.size() - 1);
        return node;
    }

    static BinaryNode *RandomTreeFromPostOrder(vector<T> &values)
    {
        if (values.size() == 0)
            return nullptr;

        function<BinaryNode<T> *(vector<T> &, int, int)>
            create = [&](vector<T> &v, int i, int j) -> BinaryNode<T> * {
            if (i > j)
                return nullptr;
            BinaryNode<T> *n = new BinaryNode<T>(v[j]);
            int k = i - 1 + (rand() % (j - i + 1));
            n->Left() = create(v, i, k);
            n->Right() = create(v, k + 1, j - 1);
            return n;
        };

        BinaryNode<T> *node = create(values, 0, values.size() - 1);
        return node;
    }

    static BinaryNode *RandomTree(vector<T> &values)
    {
        if (values.empty())
            return nullptr;

        function<BinaryNode<T> *(vector<T> &, int, int)>
            create = [&](vector<T> &v, int i, int j) -> BinaryNode<T> * {
            if (i > j)
                return nullptr;
            BinaryNode<T> *n = nullptr;
            int k = rand() % 3;
            switch (k)
            {
            case 0:
                n = new BinaryNode<T>(v[i]);
                k = i + 1 + (rand() % (j - i + 1));
                n->Left() = create(v, i + 1, k - 1);
                n->Right() = create(v, k, j);
                break;
            case 1:
                k = i + (rand() % (j - i + 1));
                n = new BinaryNode<T>(v[k]);
                n->Left() = create(v, i, k - 1);
                n->Right() = create(v, k + 1, j);
                break;
            case 2:
                n = new BinaryNode<T>(v[j]);
                k = i - 1 + (rand() % (j - i + 1));
                n->Left() = create(v, i, k);
                n->Right() = create(v, k + 1, j - 1);
                break;
            }
            return n;
        };

        BinaryNode<T> *node = create(values, 0, values.size() - 1);
        return node;
    }

    // May return nullptr
    static BinaryNode *RandomTree(size_t maxSize)
    {
        vector<T> values;
        int size = rand() % (maxSize + 1);
        for (int i = 0; i < size; i++)
        {
            values.push_back(rand());
        }
        BinaryNode<T> *node = RandomTree(values);
        return node;
    }

    // Create all unique binary trees that can be built with a sequence
    static vector<BinaryNode *> UniqueTreesFromPreOrder(vector<T> &values)
    {
        function<vector<BinaryNode *>(int, int)>
            create = [&](int i, int j) -> vector<BinaryNode *> {
            vector<BinaryNode *> trees;

            if (i > j)
                return trees;

            if (i == j)
            {
                trees.push_back(new BinaryNode(values[i]));
                return trees;
            }

            vector<BinaryNode *> firstTrees = create(i + 1, j);
            for_each(firstTrees.begin(), firstTrees.end(), [&](BinaryNode *f) {
                BinaryNode *n = new BinaryNode(values[i]);
                n->Left() = Clone1(f);
                trees.push_back(n);
            });

            for_each(firstTrees.begin(), firstTrees.end(), [&](BinaryNode *f) {
                BinaryNode *n = new BinaryNode(values[i]);
                n->Right() = Clone1(f);
                trees.push_back(n);
            });

            for_each(firstTrees.begin(), firstTrees.end(), [&](BinaryNode *f) {
                DeleteTree(f);
            });

            for (int k = i + 2; k <= j; k++)
            {
                vector<BinaryNode *> leftTrees = create(i + 1, k - 1);
                vector<BinaryNode *> rightTrees = create(k, j);
                for_each(leftTrees.begin(), leftTrees.end(), [&](BinaryNode *l) {
                    for_each(rightTrees.begin(), rightTrees.end(), [&](BinaryNode *r) {
                        BinaryNode *n = new BinaryNode(values[i]);
                        n->Left() = Clone1(l);
                        n->Right() = Clone1(r);
                        trees.push_back(n);
                    });
                });

                for_each(leftTrees.begin(), leftTrees.end(), [&](BinaryNode *l) {
                    DeleteTree(l);
                });
                for_each(rightTrees.begin(), rightTrees.end(), [&](BinaryNode *r) {
                    DeleteTree(r);
                });
            }

            return trees;
        };

        return create(0, values.size() - 1);
    }

    static vector<BinaryNode *> UniqueTreesFromInOrder(vector<T> &values)
    {
        function<vector<BinaryNode *>(int, int)>
            create = [&](int i, int j) -> vector<BinaryNode *> {
            vector<BinaryNode *> trees;

            if (i > j)
                return trees;

            if (i == j)
            {
                trees.push_back(new BinaryNode(values[i]));
                return trees;
            }

            if (i + 1 == j)
            {
                BinaryNode *n = new BinaryNode(values[j]);
                n->Left() = new BinaryNode(values[i]);
                trees.push_back(n);
                n = new BinaryNode(values[i]);
                n->Right() = new BinaryNode(values[j]);
                trees.push_back(n);
                return trees;
            }

            vector<BinaryNode *> firstTrees = create(i + 1, j);
            for_each(firstTrees.begin(), firstTrees.end(), [&](BinaryNode *f) {
                BinaryNode *n = new BinaryNode(values[i]);
                n->Right() = f;
                trees.push_back(n);
            });

            vector<BinaryNode *> lastTrees = create(i, j - 1);
            for_each(lastTrees.begin(), lastTrees.end(), [&](BinaryNode *l) {
                BinaryNode *n = new BinaryNode(values[j]);
                n->Left() = l;
                trees.push_back(n);
            });

            for (int k = i + 1; k < j; k++)
            {
                vector<BinaryNode *> leftTrees = create(i, k - 1);
                vector<BinaryNode *> rightTrees = create(k + 1, j);
                for_each(leftTrees.begin(), leftTrees.end(), [&](BinaryNode *l) {
                    for_each(rightTrees.begin(), rightTrees.end(), [&](BinaryNode *r) {
                        BinaryNode *n = new BinaryNode(values[k]);
                        n->Left() = Clone1(l);
                        n->Right() = Clone1(r);
                        trees.push_back(n);
                    });
                });

                for_each(leftTrees.begin(), leftTrees.end(), [&](BinaryNode *l) {
                    DeleteTree(l);
                });
                for_each(rightTrees.begin(), rightTrees.end(), [&](BinaryNode *r) {
                    DeleteTree(r);
                });
            }

            return trees;
        };

        return create(0, values.size() - 1);
    }

    static vector<BinaryNode *> UniqueTreesFromPostOrder(vector<T> &values)
    {
        function<vector<BinaryNode *>(int, int)>
            create = [&](int i, int j) -> vector<BinaryNode *> {
            vector<BinaryNode *> trees;

            if (i > j)
                return trees;

            if (i == j)
            {
                trees.push_back(new BinaryNode(values[i]));
                return trees;
            }

            vector<BinaryNode *> firstTrees = create(i, j - 1);
            for_each(firstTrees.begin(), firstTrees.end(), [&](BinaryNode *f) {
                BinaryNode *n = new BinaryNode(values[j]);
                n->Left() = Clone1(f);
                trees.push_back(n);
            });

            for_each(firstTrees.begin(), firstTrees.end(), [&](BinaryNode *f) {
                BinaryNode *n = new BinaryNode(values[j]);
                n->Right() = Clone1(f);
                trees.push_back(n);
            });

            for_each(firstTrees.begin(), firstTrees.end(), [&](BinaryNode *f) {
                DeleteTree(f);
            });

            for (int k = i; k < j - 1; k++)
            {
                vector<BinaryNode *> leftTrees = create(i, k);
                vector<BinaryNode *> rightTrees = create(k + 1, j - 1);
                for_each(leftTrees.begin(), leftTrees.end(), [&](BinaryNode *l) {
                    for_each(rightTrees.begin(), rightTrees.end(), [&](BinaryNode *r) {
                        BinaryNode *n = new BinaryNode(values[j]);
                        n->Left() = Clone1(l);
                        n->Right() = Clone1(r);
                        trees.push_back(n);
                    });
                });

                for_each(leftTrees.begin(), leftTrees.end(), [&](BinaryNode *l) {
                    DeleteTree(l);
                });
                for_each(rightTrees.begin(), rightTrees.end(), [&](BinaryNode *r) {
                    DeleteTree(r);
                });
            }

            return trees;
        };

        return create(0, values.size() - 1);
    }

    // Given a pre-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
    // count unique binary trees that can be built with the n numbers
    // Let C[i,j] be the count of unique binary trees using numbers i to j
    // Then chose a k between i+1 and j and solve sub problems
    // C[i,j] = 2 * C[i+1, j]
    //        + C[i+1, k-1] * C[k, j]
    static unsigned long long CountUniqueTreesFromPreOrderOfSize(int n)
    {
        if (n <= 0)
            return 0;

        UpperTriangularMatrix<unsigned long long> count(n, n);

        for (int i = 0; i < n; i++)
        {
            count(i, i) = 1;
        }

        for (int l = 1; l < n; l++)
        {
            for (int i = 0; i < n - l; i++)
            {
                int j = i + l;
                count(i, j) = count(i + 1, j) << 1;
                for (int k = i + 2; k <= j; k++)
                {
                    count(i, j) += count(i + 1, k - 1) * count(k, j);
                }
            }
        }

        return count(0, n - 1);
    }

    // Given an in-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
    // count unique binary trees that can be built with the n numbers
    // Let C[i,j] be the count of unique binary trees using numbers i to j
    // Then chose a k between i and j and solve sub problems
    // C[i,j] = C[i+1, j]
    //        + C[i, j-1]
    //        + C[i, k-1] * C[k+1, j]
    static unsigned long long CountUniqueTreesFromInOrderOfSize(int n)
    {
        if (n <= 0)
            return 0;

        UpperTriangularMatrix<unsigned long long> count(n, n);

        for (int i = 0; i < n; i++)
        {
            count(i, i) = 1;
        }

        for (int l = 1; l < n; l++)
        {
            for (int i = 0; i < n - l; i++)
            {
                int j = i + l;
                count(i, j) = count(i + 1, j) + count(i, j - 1);
                for (int k = i + 1; k < j; k++)
                {
                    count(i, j) += count(i, k - 1) * count(k + 1, j);
                }
            }
        }

        return count(0, n - 1);
    }

    // Given a post-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
    // count unique binary trees that can be built with the n numbers
    // Let C[i,j] be the count of unique binary trees using numbers i to j
    // Then chose a k between i+1 and j and solve sub problems
    // C[i,j] = 2 * C[i, j-1]
    //        + C[i, k] * C[k+1, j-1]
    static unsigned long long CountUniqueTreesFromPostOrderOfSize(int n)
    {
        if (n <= 0)
            return 0;

        UpperTriangularMatrix<unsigned long long> count(n, n);

        for (int i = 0; i < n; i++)
        {
            count(i, i) = 1;
        }

        for (int l = 1; l < n; l++)
        {
            for (int i = 0; i < n - l; i++)
            {
                int j = i + l;
                count(i, j) = count(i, j - 1) << 1;
                for (int k = i; k < j - 1; k++)
                {
                    count(i, j) += count(i, k) * count(k + 1, j - 1);
                }
            }
        }

        return count(0, n - 1);
    }

    // Create a complete binary tree
    static BinaryNode *ToCompleteTree(vector<T> &values)
    {
        if (values.size() == 0)
            return nullptr;
        BinaryNode<T> *node = new BinaryNode<T>(values[0]);
        queue<BinaryNode<T> *> q;
        q.push(node);
        size_t i = 1;
        BinaryNode<T> *n;
        while (!q.empty() && i < values.size())
        {
            n = q.front();
            q.pop();
            n->Left() = new BinaryNode<T>(values[i++]);
            if (i == values.size())
                break;
            q.push(n->Left());
            n->Right() = new BinaryNode<T>(values[i++]);
            if (i == values.size())
                break;
            q.push(n->Right());
        }
        return node;
    }

    // Fill missing nodes to make a complete tree
    static BinaryNode *FillToComplete(BinaryNode *node, vector<T> &values)
    {
        if (values.size() == 0)
            return node;
        size_t i = 0;
        if (node == nullptr)
            node = new BinaryNode<T>(values[i++]);
        queue<BinaryNode<T> *> q;
        q.push(node);
        BinaryNode<T> *n;
        while (!q.empty() && i < values.size())
        {
            n = q.front();
            q.pop();
            if (n->Left() == nullptr)
            {
                n->Left() = new BinaryNode<T>(values[i++]);
                if (i == values.size())
                    break;
            }
            q.push(n->Left());
            if (n->Right() == nullptr)
            {
                n->Right() = new BinaryNode<T>(values[i++]);
                if (i == values.size())
                    break;
            }
            q.push(n->Right());
        }
        return node;
    }

    // May return nullptr
    static BinaryNode *RandomCompleteTree(size_t maxSize)
    {
        int size = rand() % (maxSize + 1);
        if (size == 0)
            return nullptr;
        BinaryNode<T> *node = new BinaryNode<T>(rand());
        queue<BinaryNode<T> *> q;
        q.push(node);
        int i = 1;
        BinaryNode<T> *n;
        while (!q.empty() && i < size)
        {
            n = q.front();
            q.pop();
            n->Left() = new BinaryNode<T>(rand());
            i++;
            if (i == size)
                break;
            q.push(n->Left());
            n->Right() = new BinaryNode<T>(rand());
            i++;
            if (i == size)
                break;
            q.push(n->Right());
        }
        return node;
    }

    static bool IsCompleteTree(BinaryNode *node)
    {
        if (node == nullptr)
            return true;
        queue<BinaryNode<T> *> q;
        q.push(node);
        bool end = false;
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            if (node->Left() == nullptr)
            {
                if (!end)
                    end = true;
            }
            else
            {
                if (end)
                    return false;
                else
                    q.push(node->Left());
            }
            if (node->Right() == nullptr)
            {
                if (!end)
                    end = true;
            }
            else
            {
                if (end)
                    return false;
                else
                    q.push(node->Right());
            }
        }
        return true;
    }

    // Insert a new value using BFS
    static BinaryNode *Insert(BinaryNode *node, T value)
    {
        if (node == nullptr)
            return new BinaryNode<T>(value);
        queue<BinaryNode<T> *> q;
        q.push(node);
        BinaryNode<T> *n;
        while (!q.empty())
        {
            n = q.front();
            q.pop();
            if (n->Left() == nullptr)
            {
                n->Left() = new BinaryNode<T>(value);
                break;
            }
            q.push(n->Left());
            if (n->Right() == nullptr)
            {
                n->Right() = new BinaryNode<T>(value);
                break;
            }
            q.push(n->Right());
        }
        return node;
    }

    // Create a balanced tree from a single link list
    static BinaryNode *ToBalancedTree(SingleNode<T> *list)
    {
        if (list == nullptr)
            return nullptr;

        function<BinaryNode<T> *(SingleNode<T> *)>
            convert = [&](SingleNode<T> *head) -> BinaryNode<T> * {
            if (head == nullptr)
                return nullptr;

            if (head->Next() == nullptr)
            {
                BinaryNode<T> *tree = new BinaryNode<T>(head->Value());
                delete head;
                return tree;
            }

            SingleNode<T> *first = head;
            SingleNode<T> *second = head->Next();
            while (second->Next() != nullptr && second->Next()->Next() != nullptr)
            {
                first = first->Next();
                second = second->Next();
                second = second->Next();
            }

            SingleNode<T> *node = first->Next();
            first->Next() = nullptr;
            first = node->Next();
            node->Next() = nullptr;

            BinaryNode<T> *tree = new BinaryNode<T>(node->Value());

            parallel_invoke(
                [&convert, &tree, head] { tree->Left() = convert(head); },
                [&convert, &tree, first] { tree->Right() = convert(first); });

            delete node;
            return tree;
        };

        return convert(list);
    }

    static BinaryNode *ToBalancedTree2(SingleNode<T> *list)
    {
        if (list == nullptr)
            return nullptr;

        function<BinaryNode<T> *(SingleNode<T> *&, int, int)>
            convert = [&](SingleNode<T> *&head, int begin, int end) -> BinaryNode<T> * {
            if (head == nullptr || begin > end)
                return nullptr;

            // Choose the median one if there are odd numbers in [begin, end]
            // Choose the upper median if there are even numbers in [begin, end]
            int middle = begin + ((1 + end - begin) >> 1);

            BinaryNode<T> *left = convert(head, begin, middle - 1);
            BinaryNode<T> *node = new BinaryNode<T>(head->Value());
            node->Left() = left;

            SingleNode<T> *p = head;
            head = head->Next();
            delete p;

            node->Right() = convert(head, middle + 1, end);

            return node;
        };

        SingleNode<T> *p = list;
        int i = 0;
        while (p != nullptr)
        {
            p = p->Next();
            i++;
        }

        return convert(list, 0, i - 1);
    }

    // Return 0 if two trees are equal
    static int Compare(BinaryNode *first, BinaryNode *second)
    {
        if (first == nullptr && second == nullptr)
            return 0;
        if (first == nullptr && second != nullptr)
            return -1;
        if (first != nullptr && second == nullptr)
            return 1;
        if (first->Value() < second->Value())
            return -1;
        if (first->Value() > second->Value())
            return 1;
        int v = Compare(first->Left(), second->Left());
        if (v == 0)
            v = Compare(first->Right(), second->Right());
        return v;
    }

    static int Compare2(BinaryNode *first, BinaryNode *second)
    {
        if (first == nullptr && second == nullptr)
            return 0;
        if (first == nullptr && second != nullptr)
            return -1;
        if (first != nullptr && second == nullptr)
            return 1;
        if (first->Value() < second->Value())
            return -1;
        if (first->Value() > second->Value())
            return 1;
        deque<BinaryNode *> q;
        q.push_front(first);
        q.push_back(second);
        while (!q.empty())
        {
            first = q.front();
            q.pop_front();
            second = q.back();
            q.pop_back();
            if (first->Right() == nullptr && second->Right() != nullptr)
                return -1;
            if (first->Right() != nullptr && second->Right() == nullptr)
                return 1;
            if (first->Right() != nullptr && second->Right() != nullptr)
            {
                if (first->Right()->Value() < second->Right()->Value())
                    return -1;
                if (first->Right()->Value() > second->Right()->Value())
                    return 1;
                q.push_front(first->Right());
                q.push_back(second->Right());
            }
            if (first->Left() == nullptr && second->Left() != nullptr)
                return -1;
            if (first->Left() != nullptr && second->Left() == nullptr)
                return 1;
            if (first->Left() != nullptr && second->Left() != nullptr)
            {
                if (first->Left()->Value() < second->Left()->Value())
                    return -1;
                if (first->Left()->Value() > second->Left()->Value())
                    return 1;
                q.push_front(first->Left());
                q.push_back(second->Left());
            }
        }
        return 0;
    }

    // Recursive
    static int Height(BinaryNode *node)
    {
        if (node == nullptr)
            return 0;
        int left = Height(node->Left());
        int right = Height(node->Right());
        return 1 + std::max<int>(left, right);
    }

    virtual int Height(void) { return Height(this); }

    // Get the reference of left child pointer
    virtual BinaryNode *&Left(void) { return (BinaryNode *&)this->Neighbor(0); }
    // Set the left child pointer
    virtual void Left(BinaryNode *left) { this->Neighbor(0) = left; }

    // Get the reference of right child pointer
    virtual BinaryNode *&Right(void) { return (BinaryNode *&)this->Neighbor(1); }
    // Set the right child pointer
    virtual void Right(BinaryNode *right) { this->Neighbor(1) = right; }

    static int Size(BinaryNode *node)
    {
        if (node == nullptr)
            return 0;
        int left = Size(node->Left());
        int right = Size(node->Right());
        return 1 + left + right;
    }

    virtual int Size(void) { return Size(this); }

    static stringstream &ToString(BinaryNode *node, stringstream &output)
    {
        function<void(BinaryNode *, int, vector<int> &)>
            toString = [&](
                           BinaryNode *n, // Current node to print
                           int x,         // Current node position
                           vector<int> &y // Positions of unprinted right branch starting points
                       ) {
                if (n == nullptr)
                    return;

                static string link = "____";
                string c = String::ToString(n->Value());
                output << " " << c;
                x += (1 + c.length());

                if (n->Right() != nullptr)
                {
                    // Record current x coordinate,
                    // so it can be used to draw '|'
                    y.push_back(x);
                }

                if (n->Left() != nullptr)
                {
                    output << link;
                    toString(n->Left(), x + link.length(), y);
                }

                if (n->Right() != nullptr)
                {
                    output << endl;

                    for (size_t i = 0; i < y.size(); i++)
                    {
                        int len = i == 0 ? y[i] : y[i] - y[i - 1];
                        string blank(len - 1, ' ');
                        output << blank << '|';
                    }

                    output << link;

                    // The right child is ready to print
                    // Remove its coordinate because it is not needed any more
                    y.pop_back();

                    toString(n->Right(), x + link.length(), y);
                }
            };

        vector<int> y;
        toString(node, 0, y);
        output << endl;
        return output;
    }

    static stringstream &ToString2(BinaryNode *node, stringstream &output)
    {
        function<void(stringstream *, int, char)>
            printChar = [&](stringstream *s, int n, char c) {
                if (n > 0)
                {
                    string chars(n, c);
                    *s << chars;
                }
            };

        function<void(BinaryNode *, unsigned int, int &, int &, vector<stringstream *> &)>
            toString = [&](
                           BinaryNode *n,             // current node to print
                           unsigned int y,            // current node level
                           int &x,                    // x-axis position of root of last printed sub tree
                           int &r,                    // x-axis position of right-most boundary of last printed sub tree
                           vector<stringstream *> &ss // output streams, one per level
                       ) {
                if (n == nullptr)
                    return;

                if (ss.size() <= y)
                {
                    ss.push_back(new stringstream());
                }

                // print left tree, update x and r accordingly
                toString(n->Left(), y + 1, x, r, ss);

                stringstream *s = ss[y];

                int l = (int)(s->str().length());
                if (l < x)
                {
                    printChar(s, x - l, ' ');
                }

                if (n->Left() != nullptr && r > x)
                {
                    *s << '/';
                    printChar(s, r - x - 1, '-');
                }

                string nc = String::ToString(n->Value());
                *s << nc;

                x = (r + (nc.length() >> 1));
                r = r + nc.length();

                int rx = r;
                int rr = r;
                toString(n->Right(), y + 1, rx, rr, ss);

                if (n->Right() != nullptr && rx >= r)
                {
                    printChar(s, rx - r - 1, '-');
                    *s << '\\';
                }

                // Update the right most boundary
                r = rr;
            };

        vector<stringstream *> streams;
        int x = 0;
        int r = 0;
        toString(node, 0, x, r, streams);

        for_each(streams.begin(), streams.end(), [&](stringstream *s) {
            output << s->str() << endl;
            delete s;
        });

        return output;
    }

    void Print(void)
    {
        stringstream ss;
        ToString(this, ss);
        cout << ss.str();
    }

    void Print2(void)
    {
        stringstream ss;
        ToString2(this, ss);
        cout << ss.str();
    }

    static void Serialize(BinaryNode *node, ostream &output)
    {
        function<void(BinaryNode<T> *)> serialize = [&](BinaryNode<T> *n) {
            if (n == nullptr)
            {
                output << '#';
            }
            else
            {
                output << n->Value() << ' ';
                serialize(n->Left());
                serialize(n->Right());
            }
        };

        serialize(node);
    }

    static BinaryNode *Deserialize(istream &input)
    {
        function<void(BinaryNode<T> *&)> deserialize = [&](BinaryNode<T> *&n) {
            char c = input.peek();
            if (c == ' ')
            {
                // Two cases: ' '#, or ' 'number
                // Skip ' ' using seekg. Using input >> c does not work
                // because the >> operator actually skips ' ' and reads
                // next charactor, which is either '#' or a digit.
                input.seekg(1, ios_base::cur);
                c = input.peek();
            }

            if (c == '#')
            {
                // Eat '#'
                input >> c;
                return;
            }

            T value;
            // The istream >> operator reads a value and leaves
            // the next ' ' character in the stream.
            input >> value;
            n = new BinaryNode<T>(value);
            deserialize(n->Left());
            deserialize(n->Right());
        };

        BinaryNode<T> *node;
        deserialize(node);
        return node;
    }

    // Recursive
    static void PreOrderWalk(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        f(node->Value());
        PreOrderWalk(node->Left(), f);
        PreOrderWalk(node->Right(), f);
    }

    void PreOrderWalk(function<void(T)> f) { PreOrderWalk(this, f); }

    // Non-recursive with stack
    static void PreOrderWalkWithStack(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        stack<BinaryNode *> path;
        while (!path.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                f(node->Value());
                path.push(node);
                node = node->Left();
            }
            else
            {
                node = path.top()->Right();
                path.pop();
            }
        }
    }

    void PreOrderWalkWithStack(function<void(T)> f) { PreOrderWalkWithStack(this, f); }

    // Non-recursive with stack
    static void PreOrderWalkWithStack2(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        stack<BinaryNode *> path;
        path.push(node);
        while (!path.empty())
        {
            BinaryNode *top = path.top();
            path.pop();
            f(top->Value());
            if (top->Right() != nullptr)
                path.push(top->Right());
            if (top->Left() != nullptr)
                path.push(top->Left());
        }
    }

    void PreOrderWalkWithStack2(function<void(T)> f) { PreOrderWalkWithStack2(this, f); }

    // Non-recursive with stack
    static void PreOrderWalkWithStack3(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        stack<BinaryNode *> path;
        path.push(node);
        BinaryNode *prev = node;
        while (!path.empty())
        {
            node = path.top();
            if (prev == node->Right())
            {
                path.pop();
            }
            else if (node->Left() != nullptr && node->Left() != prev)
            {
                f(node->Value());
                path.push(node->Left());
            }
            else
            {
                if (node->Left() != prev)
                    f(node->Value());
                if (node->Right() == nullptr)
                    path.pop();
                else
                    path.push(node->Right());
            }
            prev = node;
        }
    }

    void PreOrderWalkWithStack3(function<void(T)> f) { PreOrderWalkWithStack3(this, f); }

    // Recursive
    static void InOrderWalk(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        InOrderWalk(node->Left(), f);
        f(node->Value());
        InOrderWalk(node->Right(), f);
    }

    void InOrderWalk(function<void(T)> f) { InOrderWalk(this, f); }

    // Non-recursive with stack
    static void InOrderWalkWithStack(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        stack<BinaryNode *> path;
        while (!path.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                path.push(node);
                node = node->Left();
            }
            else
            {
                node = path.top();
                path.pop();
                f(node->Value());
                node = node->Right();
            }
        }
    }

    void InOrderWalkWithStack(function<void(T)> f) { InOrderWalkWithStack(this, f); }

    // Non-recursive with stack
    static void InOrderWalkWithStack2(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        stack<BinaryNode *> path;
        path.push(node);
        BinaryNode *prev = nullptr;
        while (!path.empty())
        {
            node = path.top();
            if (prev == node->Right())
            {
                path.pop();
            }
            else if (node->Left() != nullptr && node->Left() != prev)
            {
                path.push(node->Left());
            }
            else
            {
                f(node->Value());
                if (node->Right() == nullptr)
                    path.pop();
                else
                    path.push(node->Right());
            }
            prev = node;
        }
    }

    void InOrderWalkWithStack2(function<void(T)> f) { InOrderWalkWithStack2(this, f); }

    // Recursive
    static void PostOrderWalk(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        PostOrderWalk(node->Left(), f);
        PostOrderWalk(node->Right(), f);
        f(node->Value());
    }

    void PostOrderWalk(function<void(T)> f) { PostOrderWalk(this, f); }

    // Non-recursive with stack
    static void PostOrderWalkWithStack(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        stack<BinaryNode *> path;
        BinaryNode *prev = nullptr;
        while (!path.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                path.push(node);
                node = node->Left();
            }
            else
            {
                BinaryNode *top = path.top();
                if (top->Right() != nullptr && top->Right() != prev)
                {
                    node = top->Right();
                }
                else
                {
                    path.pop();
                    f(top->Value());
                    prev = top;
                }
            }
        }
    }

    void PostOrderWalkWithStack(function<void(T)> f) { PostOrderWalkWithStack(this, f); }

    // Non-recursive with stack
    static void PostOrderWalkWithStack2(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        stack<BinaryNode *> path;
        path.push(node);
        BinaryNode *prev = node;
        while (!path.empty())
        {
            node = path.top();
            if (prev == node->Right())
            {
                f(node->Value());
                path.pop();
            }
            else if (node->Left() != nullptr && node->Left() != prev)
            {
                path.push(node->Left());
            }
            else
            {
                if (node->Right() != nullptr)
                    path.push(node->Right());
                else
                {
                    f(node->Value());
                    path.pop();
                }
            }
            prev = node;
        }
    }

    void PostOrderWalkWithStack2(function<void(T)> f) { PostOrderWalkWithStack2(this, f); }

    static BinaryNode *BuildTreePreOrderInOrder(T *preOrder, int preLength, T *inOrder, int inLength)
    {
        if (inOrder == nullptr || preOrder == nullptr || inLength <= 0 || preLength <= 0 || inLength != preLength)
            return nullptr;

        T value = preOrder[0];

        int index = -1;
        for (int i = 0; i < inLength; i++)
        {
            if (inOrder[i] == value)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return nullptr;

        BinaryNode<T> *node = new BinaryNode<T>(value);

        node->Left() = BuildTreePreOrderInOrder(preOrder + 1, index, inOrder, index);
        node->Right() = BuildTreePreOrderInOrder(preOrder + index + 1, preLength - 1 - index, inOrder + index + 1, inLength - 1 - index);

        return node;
    }

    static BinaryNode *BuildTreePreOrderInOrder2(T *preOrder, int preLength, T *inOrder, int inLength)
    {
        if (preOrder == nullptr || preLength <= 0 || inOrder == nullptr || inLength <= 0 || preLength != inLength)
            return nullptr;

        stack<BinaryNode<T> *> path;

        int i = 0; // index current element in preOrder
        int j = 0; // index current element in inOrder
        int f = 0; // flag to insert to left or right

        // Root
        BinaryNode<T> *node = new BinaryNode<T>(preOrder[i]);
        path.push(node);

        // Current insertion point
        BinaryNode<T> *t = node;
        i++;

        while (i < preLength)
        {
            if (!path.empty() && path.top()->Value() == inOrder[j])
            {
                // Done with a left substree, start to insert the right subtree
                t = path.top();
                path.pop();
                f = 1;
                j++;
            }
            else
            {
                if (f == 0)
                {
                    t->Left() = new BinaryNode<T>(preOrder[i]);
                    t = t->Left();
                }
                else
                {
                    f = 0;
                    t->Right() = new BinaryNode<T>(preOrder[i]);
                    t = t->Right();
                }
                path.push(t);
                i++;
            }
        }

        return node;
    }

    static BinaryNode *BuildTreeInOrderPostOrder(T *inOrder, int inLength, T *postOrder, int postLength)
    {
        if (inOrder == nullptr || postOrder == nullptr || inLength <= 0 || postLength <= 0 || inLength != postLength)
            return nullptr;

        T value = postOrder[postLength - 1];

        int index = -1;
        for (int i = 0; i < inLength; i++)
        {
            if (inOrder[i] == value)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return nullptr;

        BinaryNode<T> *node = new BinaryNode<T>(value);

        node->Left() = BuildTreeInOrderPostOrder(inOrder, index, postOrder, index);
        node->Right() = BuildTreeInOrderPostOrder(inOrder + index + 1, inLength - 1 - index, postOrder + index, postLength - 1 - index);

        return node;
    }

    static BinaryNode *BuildTreeInOrderPostOrder2(T *inOrder, int inLength, T *postOrder, int postLength)
    {
        if (inOrder == nullptr || inLength <= 0 || postOrder == nullptr || postLength <= 0 || inLength != postLength)
            return nullptr;

        stack<BinaryNode<T> *> path;

        int i = postLength - 1; // index current element in postOrder
        int j = inLength - 1;   // index current element in inOrder
        int f = 0;              // flag to insert to left or right

        // Root
        BinaryNode<T> *node = new BinaryNode<T>(postOrder[i]);
        path.push(node);

        // Current insertion point
        BinaryNode<T> *t = node;
        i--;

        while (i >= 0)
        {
            if (!path.empty() && path.top()->Value() == inOrder[j])
            {
                // Done with a right subtree, start to insert the left subtree
                t = path.top();
                path.pop();
                f = 1;
                j--;
            }
            else
            {
                if (f == 0)
                {
                    t->Right() = new BinaryNode<T>(postOrder[i]);
                    t = t->Right();
                }
                else
                {
                    f = 0;
                    t->Left() = new BinaryNode<T>(postOrder[i]);
                    t = t->Left();
                }
                path.push(t);
                i--;
            }
        }

        return node;
    }

    // Visit level by level, left to right
    // Breadth-first search
    static void LevelOrderWalk(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        queue<BinaryNode *> q;
        q.push(node);
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            f(node->Value());
            if (node->Left() != nullptr)
                q.push(node->Left());
            if (node->Right() != nullptr)
                q.push(node->Right());
        }
    }

    virtual void LevelOrderWalk(function<void(T)> f) { LevelOrderWalk(this, f); }

    // Visit level by level, left to right
    // Depth-first search
    static void LevelOrderWalk2(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;

        vector<vector<T> *> levels;

        function<void(BinaryNode *, unsigned int)>
            preOrder = [&](BinaryNode *n, unsigned int l) {
                if (n == nullptr)
                    return;

                if (levels.size() <= l)
                {
                    levels.push_back(new vector<T>());
                }

                vector<T> *level = levels[l];
                level->push_back(n->Value());

                preOrder(n->Left(), l + 1);
                preOrder(n->Right(), l + 1);
            };

        preOrder(node, 0);

        for_each(levels.begin(), levels.end(), [&](vector<T> *level) {
            for_each(level->begin(), level->end(), [&](T c) {
                f(c);
            });
            delete level;
        });
    }

    virtual void LevelOrderWalk2(function<void(T)> f) { LevelOrderWalk2(this, f); }

    // Visit nodes level by level from bottom up and left to right
    static void LevelOrderWalkBottomUp(BinaryNode *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;

        vector<vector<T>> levels;
        levels.push_back(vector<T>{node->Value()});

        queue<BinaryNode *> q[2];
        q[0].push(node);

        int l = 0;
        while (!q[0].empty() || !q[1].empty())
        {
            queue<BinaryNode *> &current = q[l & 0x1];
            queue<BinaryNode *> &next = q[(1 + l) & 0x1];
            vector<T> level;
            while (!current.empty())
            {
                node = current.front();
                current.pop();
                if (node->Left() != nullptr)
                {
                    level.push_back(node->Left()->Value());
                    next.push(node->Left());
                }
                if (node->Right() != nullptr)
                {
                    level.push_back(node->Right()->Value());
                    next.push(node->Right());
                }
            }
            if (level.size() > 0)
                levels.insert(levels.begin(), level);
            l++;
        }

        for_each(levels.begin(), levels.end(), [&](vector<T> &level) {
            for_each(level.begin(), level.end(), [&](T c) {
                f(c);
            });
        });
    }

    void LevelOrderWalkBottomUp(function<void(T)> f) { LevelOrderWalkBottomUp(this, f); }

    // The boundary values include left-most nodes, leaf nodes and right-most
    // nodes. A left-most node may be the right child of its parent if its parent
    // is left-most and has no left child. Same goes to the right-most nodes.
    // TODO: try level walk
    static void GetBoundaryValues(BinaryNode *node, vector<T> &values)
    {
        if (node == nullptr)
            return;

        values.push_back(node->Value());

        function<void(BinaryNode<T> *, bool)>
            searchLeft = [&](BinaryNode<T> *n, bool include) {
                if (n == nullptr)
                    return;

                if (include || n->Left() == nullptr && n->Right() == nullptr)
                {
                    values.push_back(n->Value());
                }

                if (n->Left() != nullptr)
                    searchLeft(n->Left(), include);

                if (n->Right() != nullptr)
                {
                    // include the right child only if
                    // its parent is included and has no left child
                    searchLeft(n->Right(), include && n->Left() == nullptr);
                }
            };

        function<void(BinaryNode<T> *, bool)>
            searchRight = [&](BinaryNode<T> *n, bool include) {
                if (n == nullptr)
                    return;

                if (n->Left() != nullptr)
                {
                    // include the left child only if
                    // its parent is included and has no right child
                    searchRight(n->Left(), include && n->Right() == nullptr);
                }

                if (n->Right() != nullptr)
                    searchRight(n->Right(), include);

                if (include || n->Left() == nullptr && n->Right() == nullptr)
                {
                    values.push_back(n->Value());
                }
            };

        searchLeft(node->Left(), true);
        searchRight(node->Right(), true);
    }

    void GetBoundaryValues(vector<T> &values) { GetBoundaryValues(this, values); }

    static BinaryNode *Search(BinaryNode *node, const T &v)
    {
        if (node == nullptr || node->Value() == v)
            return node;
        BinaryNode<T> *left = Search(node->Left(), v);
        if (left != nullptr)
            return left;
        else
            return Search(node->Right(), v);
    }

    static BinaryNode *Min(BinaryNode *node)
    {
        if (node == nullptr)
            return node;
        BinaryNode<T> *left = Min(node->Left());
        BinaryNode<T> *right = Min(node->Right());
        BinaryNode<T> *min = node;
        if (left != nullptr && left->Value() < min->Value())
            min = left;
        if (right != nullptr && right->Value() < min->Value())
            min = right;
        return min;
    }

    static BinaryNode *Max(BinaryNode *node)
    {
        if (node == nullptr)
            return node;
        BinaryNode<T> *left = Max(node->Left());
        BinaryNode<T> *right = Max(node->Right());
        BinaryNode<T> *max = node;
        if (left != nullptr && left->Value() > max->Value())
            max = left;
        if (right != nullptr && right->Value() > max->Value())
            max = right;
        return max;
    }

    // TODO: PostOrder with DP
    static BinaryNode *LowestCommonAncestor(BinaryNode *node, BinaryNode *first, BinaryNode *second)
    {
        if (node == nullptr || first == nullptr || second == nullptr)
            return nullptr;
        if (node == first || node == second)
            return node;

        function<int(BinaryNode<T> *, BinaryNode<T> *, BinaryNode<T> *)>
            hits = [&](BinaryNode<T> *n, BinaryNode<T> *f, BinaryNode<T> *s) -> int {
            if (n == nullptr)
                return 0;
            int h = hits(n->Left(), f, s) + hits(n->Right(), f, s);
            if (n == f || n == s)
                return 1 + h;
            else
                return h;
        };

        int h = hits(node->Left(), first, second);
        if (h == 1)
            return node;
        else if (h == 2)
            return LowestCommonAncestor(node->Left(), first, second);
        else
            return LowestCommonAncestor(node->Right(), first, second);
    }

    static BinaryNode *LowestCommonAncestor2(BinaryNode *node, BinaryNode *first, BinaryNode *second)
    {
        if (node == nullptr || first == nullptr || second == nullptr)
            return nullptr;
        if (node == first || node == second)
            return node;
        BinaryNode<T> *left = LowestCommonAncestor2(node->Left(), first, second);
        BinaryNode<T> *right = LowestCommonAncestor2(node->Right(), first, second);
        if (left != nullptr && right != nullptr)
            return node;
        if (left != nullptr)
            return left;
        else
            return right;
    }

    // http://leetcode.com/2010/09/printing-binary-tree-in-zig-zag-level_18.html
    // Breadth-first-search using stack
    void PrintZigZag(void)
    {
        stack<BinaryNode *> level[2];
        int l = 0;
        level[0].push(this);
        while (true)
        {
            stack<BinaryNode *> &current = level[l % 2];
            stack<BinaryNode *> &next = level[(l + 1) % 2];
            while (!current.empty())
            {
                BinaryNode *p = current.top();
                current.pop();
                cout << p->Value() << ' ';
                if (l % 2 == 0)
                {
                    if (p->Left() != nullptr)
                        next.push(p->Left());
                    if (p->Right() != nullptr)
                        next.push(p->Right());
                }
                else
                {
                    if (p->Right() != nullptr)
                        next.push(p->Right());
                    if (p->Left() != nullptr)
                        next.push(p->Left());
                }
            }
            cout << endl;
            if (next.empty())
                break;
            l++;
        }
    }

    // Convert a binary tree to a linked list so that the list nodes
    // are linked by the left and right pointers and are in pre-order of original tree.
    // e.g.
    //      1
    //     / \
	//    2   5
    //   / \   \
	//  3   4   6
    // to
    //  1-2-3-4-5-6
    // This version builds a double-link list by setting node->left also.
    // If need a single-link list, just remove the statements setting node->left.
    static BinaryNode *ToPreOrderLinkList(BinaryNode *node)
    {
        if (node == nullptr)
            return node;

        function<void(BinaryNode *, BinaryNode *&)>
            convert = [&](BinaryNode *head, BinaryNode *&tail) {
                if (head == nullptr)
                {
                    tail = nullptr;
                    return;
                }

                if (head->Left() == nullptr && head->Right() == nullptr)
                {
                    tail = head;
                    return;
                }

                BinaryNode *leftTail = nullptr;
                convert(head->Left(), leftTail);

                BinaryNode *rightTail = nullptr;
                convert(head->Right(), rightTail);

                if (head->Left() != nullptr)
                {
                    head->Left()->Left() = head;
                    leftTail->Right() = head->Right();
                    head->Right() = head->Left();
                    head->Left() = nullptr;
                    if (leftTail->Right() == nullptr)
                    {
                        tail = leftTail;
                    }
                    else
                    {
                        leftTail->Right()->Left() = leftTail;
                        tail = rightTail;
                    }
                }
                else
                {
                    head->Right()->Left() = head;
                    tail = rightTail;
                }
            };

        BinaryNode *tail;
        convert(node, tail);
        return node;
    }

    // Convert a binary tree to a linked list so that the list nodes
    // are linked by the left and right pointers and are in in-order of original tree.
    // e.g.
    //      1
    //     / \
	//    2   5
    //   / \   \
	//  3   4   6
    // to
    //  3-2-4-1-5-6
    // This version builds a double-link list by setting node->left also.
    // If need a single-link list, just remove the statements setting node->left.
    static BinaryNode *ToInOrderLinkList(BinaryNode *node)
    {
        if (node == nullptr)
            return node;

        function<void(BinaryNode *, BinaryNode *&, BinaryNode *&)>
            convert = [&](BinaryNode *n, BinaryNode *&h, BinaryNode *&t) {
                h = nullptr;
                t = nullptr;
                if (n == nullptr)
                    return;

                BinaryNode *leftHead = nullptr;
                BinaryNode *leftTail = nullptr;
                convert(n->Left(), leftHead, leftTail);

                BinaryNode *rightHead = nullptr;
                BinaryNode *rightTail = nullptr;
                convert(n->Right(), rightHead, rightTail);

                if (leftTail == nullptr)
                {
                    leftHead = n;
                    leftTail = n;
                }
                else
                {
                    leftTail->Right() = n;
                    n->Left() = leftTail;
                }

                if (rightHead == nullptr)
                {
                    rightHead = n;
                    rightTail = n;
                }
                else
                {
                    rightHead->Left() = n;
                    n->Right() = rightHead;
                }

                h = leftHead;
                t = rightTail;
            };

        BinaryNode<T> *head = nullptr;
        BinaryNode<T> *tail = nullptr;
        convert(node, head, tail);
        return head;
    }

    // Convert a binary tree to a linked list so that the list nodes
    // are linked by the left and right pointers and are in post-order of original tree.
    // e.g.
    //      1
    //     / \
	//    2   5
    //   / \   \
	//  3   4   6
    // to
    //  3-4-2-6-5-1
    // This version builds a double-link list by setting node->left also.
    // If need a single-link list, just remove the statements setting node->left.
    static BinaryNode *ToPostOrderLinkList(BinaryNode *node)
    {
        if (node == nullptr)
            return node;

        function<void(BinaryNode *&, BinaryNode *)>
            convert = [&](BinaryNode *&head, BinaryNode *tail) {
                if (tail == nullptr)
                {
                    head = nullptr;
                    return;
                }

                if (tail->Left() == nullptr && tail->Right() == nullptr)
                {
                    head = tail;
                    return;
                }

                BinaryNode *leftHead = nullptr;
                convert(leftHead, tail->Left());

                BinaryNode *rightHead = nullptr;
                convert(rightHead, tail->Right());

                if (tail->Right() != nullptr)
                {
                    tail->Right()->Right() = tail;
                    rightHead->Left() = tail->Left();
                    tail->Left() = tail->Right();
                    tail->Right() = nullptr;
                    if (rightHead->Left() == nullptr)
                    {
                        head = rightHead;
                    }
                    else
                    {
                        rightHead->Left()->Right() = rightHead;
                        head = leftHead;
                    }
                }
                else
                {
                    tail->Left()->Right() = tail;
                    head = leftHead;
                }
            };

        BinaryNode *head;
        convert(head, node);
        return head;
    }

    // A tree is balanced if the heights of its left tree and right tree
    // differs no more than 1.
    static bool IsBalanced(BinaryNode *node)
    {
        if (node == nullptr)
            return true;

        function<bool(BinaryNode *, int &)>
            balanced = [&](BinaryNode *n, int &h) -> bool {
            if (n == nullptr)
            {
                h = 0;
                return true;
            }

            if (n->Left() == nullptr && n->Right() == nullptr)
            {
                h = 1;
                return true;
            }

            int lh;
            bool l = balanced(n->Left(), lh);
            if (l == false)
                return false;

            int rh;
            bool r = balanced(n->Right(), rh);
            if (r == false)
                return false;

            if (lh - rh > 1 || rh - lh > 1)
                return false;

            h = 1 + (lh >= rh ? lh : rh);
            return true;
        };

        int height;
        bool isBalanced = balanced(node, height);
        return isBalanced;
    }

    bool IsBalanced(void) { return IsBalanced(this); }

    // A tree is balanced if the heights of its left tree and right tree differs no more than 1.
    // This algorithm is wrong. A failed example is:
    //         1
    //     2       2
    //   3   3   3   3
    //  4 4 4 4 4 4
    // 5 5
    static bool IsBalanced2(BinaryNode *node)
    {
        if (node == nullptr)
            return true;

        int minDepth = INT_MAX;
        bool foundMinDepth = false;
        int depth = 0;
        queue<BinaryNode *> q[2];
        q[0].push(node);
        while (!q[0].empty() || !q[1].empty())
        {
            queue<BinaryNode *> &current = q[depth & 0x1];
            queue<BinaryNode *> &next = q[(depth + 1) & 0x1];
            while (!current.empty())
            {
                node = current.front();
                current.pop();
                if (node->Left() == nullptr && node->Right() == nullptr && !foundMinDepth)
                {
                    foundMinDepth = true;
                    minDepth = depth;
                }

                if (node->Left() != nullptr && node->Right() == nullptr)
                {
                    if (node->Left()->Left() != nullptr || node->Left()->Right() != nullptr)
                        return false;
                }

                if (node->Left() == nullptr && node->Right() != nullptr)
                {
                    if (node->Right()->Left() != nullptr || node->Right()->Right() != nullptr)
                        return false;
                }

                if (foundMinDepth && depth - minDepth > 1)
                    return false;

                if (node->Left() != nullptr)
                    next.push(node->Left());
                if (node->Right() != nullptr)
                    next.push(node->Right());
            }

            depth++;
        }
        return true;
    }

    bool IsBalanced2(void) { return IsBalanced2(this); }

    // Given a binary tree, check whether it is a mirror of itself
    // (ie, symmetric around its center).
    // For example, this binary tree is symmetric:
    //    1
    //   / \
	//  2   2
    // / \ / \
	// 3 4 4 3
    // But the following is not:
    //   1
    //  / \
	// 2   2
    //  \   \
	//   3   3
    static bool IsSymmetric(BinaryNode *node)
    {
        function<bool(BinaryNode *, BinaryNode *)>
            isSymmetric = [&](BinaryNode *left, BinaryNode *right) -> bool {
            if (left == nullptr && right == nullptr)
                return true;
            if (left != nullptr && right == nullptr || left == nullptr && right != nullptr)
                return false;
            if (left->Value() != right->Value())
                return false;
            if (!isSymmetric(left->Left(), right->Right()))
                return false;
            return isSymmetric(left->Right(), right->Left());
        };

        return isSymmetric(node, node);
    }

    bool IsSymmetric(void) { return IsSymmetric(this); }

    // Given a binary tree, check whether it is a mirror of itself
    // (ie, symmetric around its center).
    // For example, this binary tree is symmetric:
    //    1
    //   / \
	//  2   2
    // / \ / \
	// 3 4 4 3
    // But the following is not:
    //   1
    //  / \
	// 2   2
    //  \   \
	//   3   3
    static bool IsSymmetric2(BinaryNode *node)
    {
        if (node == nullptr)
            return true;
        if (node->Left() == nullptr && node->Right() == nullptr)
            return true;
        if (node->Left() != nullptr && node->Right() == nullptr || node->Left() == nullptr && node->Right() != nullptr)
            return false;
        if (node->Left()->Value() != node->Right()->Value())
            return false;
        deque<BinaryNode *> q;
        q.push_front(node->Left());
        q.push_back(node->Right());
        while (!q.empty())
        {
            BinaryNode *left = q.front();
            q.pop_front();
            BinaryNode *right = q.back();
            q.pop_back();
            if (left->Right() != nullptr && right->Left() == nullptr || left->Right() == nullptr && right->Left() != nullptr)
                return false;
            if (left->Right() != nullptr && right->Left() != nullptr)
            {
                if (left->Right()->Value() != right->Left()->Value())
                    return false;
                q.push_front(left->Right());
                q.push_back(right->Left());
            }
            if (left->Left() != nullptr && right->Right() == nullptr || left->Left() == nullptr && right->Right() != nullptr)
                return false;
            if (left->Left() != nullptr && right->Right() != nullptr)
            {
                if (left->Left()->Value() != right->Right()->Value())
                    return false;
                q.push_front(left->Left());
                q.push_back(right->Right());
            }
        }
        return true;
    }

    bool IsSymmetric2(void) { return IsSymmetric2(this); }

    // Swap values of two nodes
    static void SwapValues(BinaryNode *first, BinaryNode *second)
    {
        if (first == nullptr || second == nullptr)
            return;
        T t = first->Value();
        first->Value() = second->Value();
        second->Value() = t;
    }

    static BinaryNode *Clone1(BinaryNode *node)
    {
        if (node == nullptr)
            return nullptr;
        BinaryNode *newNode = new BinaryNode(node->Value());
        newNode->Left() = Clone1(node->Left());
        newNode->Right() = Clone1(node->Right());
        return newNode;
    }

    //
    // BinarySearchTree
    //

    // Create a random binary search tree
    // Return nullptr if input is empty
    static BinaryNode *SearchTreeRandom(vector<T> &values)
    {
        if (values.size() == 0)
            return nullptr;
        sort(values.begin(), values.end());
        BinaryNode<T> *node = RandomTreeFromInOrder(values);
        return node;
    }

    // May return nullptr
    static BinaryNode *SearchTreeRandom(size_t maxSize)
    {
        vector<T> values;
        int size = rand() % (maxSize + 1);
        for (int i = 0; i < size; i++)
        {
            values.push_back(rand());
        }
        BinaryNode<T> *node = SearchTreeRandom(values);
        return node;
    }

    // Insert a new value to binary search tree
    static BinaryNode *SearchTreeInsert(BinaryNode *node, T value)
    {
        BinaryNode<T> *newNode = new BinaryNode<T>(value);
        if (node == nullptr)
            return newNode;
        BinaryNode<T> *parent = node;
        BinaryNode<T> *current = node;
        while (current != nullptr)
        {
            parent = current;
            if (value <= current->Value())
                current = current->Left();
            else
                current = current->Right();
        }
        if (value <= parent->Value())
            parent->Left() = newNode;
        else
            parent->Right() = newNode;
        return node;
    }

    static BinaryNode *SearchTreeInsert2(BinaryNode *node, T value)
    {
        BinaryNode<T> *newNode = new BinaryNode<T>(value);
        if (node == nullptr)
            return newNode;
        BinaryNode<T> *current = node;
        while (true)
        {
            if (value <= current->Value())
            {
                if (current->Left() == null)
                {
                    current->Left() = newNode;
                    break;
                }
                else
                {
                    current = current->Left();
                }
            }
            else
            {
                if (current->Right() == null)
                {
                    current->Right() = newNode;
                    break;
                }
                else
                {
                    current = current->Right();
                }
            }
        }
        return node;
    }

    // Verify if a tree is a binary search tree
    static bool SearchTreeVerify(BinaryNode *node)
    {
        if (node == nullptr)
            return true;

        // ensure min < n->Value() <= max
        function<bool(BinaryNode<T> *, T, T)>
            between = [&](BinaryNode<T> *n, T min, T max) -> bool {
            if (n == nullptr)
                return true;
            if (n->Value() <= min || n->Value() > max)
                return false;
            return between(n->Left(), min, n->Value()) && between(n->Right(), n->Value(), max);
        };

        // ensure n->Value() <= max
        function<bool(BinaryNode<T> *, T)>
            less = [&](BinaryNode<T> *n, T max) -> bool {
            if (n == nullptr)
                return true;
            if (n->Value() > max)
                return false;
            return less(n->Left(), n->Value()) && between(n->Right(), n->Value(), max);
        };

        // ensure min < n->Value()
        function<bool(BinaryNode<T> *, T)>
            greater = [&](BinaryNode<T> *n, T min) -> bool {
            if (n == nullptr)
                return true;
            if (n->Value() <= min)
                return false;
            return greater(n->Right(), n->Value()) && between(n->Left(), min, n->Value());
        };

        return less(node->Left(), node->Value()) && greater(node->Right(), node->Value());
    }

    static bool SearchTreeVerify2(BinaryNode *node)
    {
        function<bool(BinaryNode<T> *, T &, T &)>
            verify = [&](BinaryNode<T> *n, T &min, T &max) -> bool {
            if (n == nullptr)
                return true;
            if (n->Left() == nullptr && n->Right() == nullptr)
            {
                min = n->Value();
                max = n->Value();
                return true;
            }

            if (n->Left() == nullptr)
            {
                min = n->Value();
            }
            else
            {
                T leftMin;
                T leftMax;
                if (!verify(n->Left(), leftMin, leftMax))
                    return false;
                if (leftMax > n->Value())
                    return false;
                min = leftMin;
            }

            if (n->Right() == nullptr)
            {
                max = n->Value();
            }
            else
            {
                T rightMin;
                T rightMax;
                if (!verify(n->Right(), rightMin, rightMax))
                    return false;
                if (rightMin <= n->Value())
                    return false;
                max = rightMax;
            }

            return true;
        };

        T min;
        T max;
        return verify(node, min, max);
    }

    static bool SearchTreeVerify3(BinaryNode *node)
    {
        if (node == nullptr)
            return true;
        stack<BinaryNode<T> *> path;
        path.push(node);
        BinaryNode<T> *prev = nullptr; // InOrder previous node
        BinaryNode<T> *lastVisited = nullptr;
        while (!path.empty())
        {
            node = path.top();
            if (node->Right() != nullptr && node->Right() == lastVisited)
            {
                path.pop();
            }
            else if (node->Left() != nullptr && node->Left() != lastVisited)
            {
                path.push(node->Left());
            }
            else
            {
                if (prev != nullptr)
                {
                    if (prev->Right() == node)
                    {
                        if (prev->Value() >= node->Value())
                            return false;
                    }
                    else
                    {
                        if (prev->Value() > node->Value())
                            return false;
                    }
                }
                prev = node;
                if (node->Right() == nullptr)
                    path.pop();
                else
                    path.push(node->Right());
            }
            lastVisited = node;
        }
        return true;
    }

    // Search a node in binary search tree
    static BinaryNode *SearchTreeSearch(BinaryNode *node, T value)
    {
        if (node == nullptr || node->Value() == value)
            return node;
        if (value <= node->Value())
            return SearchTreeSearch(node->Left(), value);
        else
            return SearchTreeSearch(node->Right(), value);
    }

    static BinaryNode *SearchTreeSearch2(BinaryNode *node, T value)
    {
        if (node == nullptr || node->Value() == value)
            return node;
        while (node != nullptr && node->Value() != value)
        {
            if (value <= node->Value())
                node = node->Left();
            else
                node = node->Right();
        }
        return node;
    }

    // Find the minimum node
    static BinaryNode *SearchTreeMin(BinaryNode *node)
    {
        if (node == nullptr)
            return nullptr;
        while (node->Left() != nullptr)
            node = node->Left();
        return node;
    }

    // Find the maximum node
    static BinaryNode *SearchTreeMax(BinaryNode *node)
    {
        if (node == nullptr)
            return node;
        while (node->Right() != nullptr)
            node = node->Right();
        return node;
    }

    // Assume first and second exist in the tree
    static BinaryNode *SearchTreeLowestCommonAncestor(BinaryNode *node, const T &first, const T &second)
    {
        if (node == nullptr)
            return nullptr;
        while (node != nullptr)
        {
            if (node->Value() > std::max(first, second))
                node = node->Left();
            else if (node->Value() < std::min(first, second))
                node = node->Right();
            else
                break;
        }
        return node;
    }

    // Serialize a binary search tree
    static void SearchTreeSerialize(BinaryNode *node, ostream &output)
    {
        function<void(T)> serialize = [&](T v) { output << v << ' '; };
        PreOrderWalk(node, serialize);
    }

    // Deserialize a binary search tree
    static BinaryNode *SearchTreeDeserialize(istream &input)
    {
        function<void(T, T, T &, BinaryNode<T> *&)>
            deserialize = [&](T l, T h, T &value, BinaryNode<T> *&node) {
                if (l < value && value <= h)
                {
                    T v = value;
                    node = new BinaryNode<T>(v);
                    input >> value;
                    if (input.good() && !input.eof())
                    {
                        deserialize(l, v, value, node->Left());
                        deserialize(v, h, value, node->Right());
                    }
                }
            };

        function<void(T, T &, BinaryNode<T> *&)>
            deserializeLeft = [&](T p, T &value, BinaryNode<T> *&node) {
                if (value <= p)
                {
                    T v = value;
                    node = new BinaryNode<T>(v);
                    input >> value;
                    if (input.good() && !input.eof())
                    {
                        deserializeLeft(v, value, node->Left());
                        deserialize(v, p, value, node->Right());
                    }
                }
            };

        function<void(T, T &, BinaryNode<T> *&)>
            deserializeRight = [&](T p, T &value, BinaryNode<T> *&node) {
                if (value > p)
                {
                    T v = value;
                    node = new BinaryNode<T>(v);
                    input >> value;
                    if (input.good() && !input.eof())
                    {
                        deserialize(p, v, value, node->Left());
                        deserializeRight(v, value, node->Right());
                    }
                }
            };

        BinaryNode<T> *node = nullptr;
        T value;
        input >> value;
        if (input.good() && !input.eof())
        {
            node = new BinaryNode<T>(value);
            input >> value;
            if (input.good() && !input.eof())
            {
                deserializeLeft(node->Value(), value, node->Left());
                deserializeRight(node->Value(), value, node->Right());
            }
        }
        return node;
    }

    static BinaryNode *SearchTreeDeserialize2(istream &input)
    {
        BinaryNode<T> *node = nullptr;
        T value;
        input >> value;
        while (input.good() && !input.eof())
        {
            node = SearchTreeInsert(node, value);
            input >> value;
        }
        return node;
    }

    static BinaryNode *SearchTreeDeserialize3(istream &input)
    {
        BinaryNode<T> *node = nullptr;
        T value;
        input >> value;
        if (input.good() && !input.eof())
            node = new BinaryNode<T>(value);
        else
            return node;
        stack<BinaryNode<T> *> path;
        path.push(node);
        BinaryNode<T> *prev = nullptr;
        while (true)
        {
            input >> value;
            if (!input.good() || input.eof())
                break;
            BinaryNode<T> *n = new BinaryNode<T>(value);
            if (!path.empty() && value <= path.top()->Value())
            {
                path.top()->Left() = n;
            }
            else
            {
                while (!path.empty() && path.top()->Value() < value)
                {
                    prev = path.top();
                    path.pop();
                }
                if (prev != nullptr)
                    prev->Right() = n;
            }
            path.push(n);
        }
        return node;
    }

    // Two elements of a binary search tree are swapped by mistake.
    // Recover the tree without changing its structure.
    // If we traverse a binary search tree in-order, we will get an increasing
    // sequence, e.g.,
    //    1, 2, 3, 4, 5, 6, 7, .......
    // If two neighboring elements are swapped, we will have one inversion, e.g.,
    //    1, 2, 4, 3, 5, 6, 7, .......
    // If two non-neighboring elements are swapped, we will have two inversions, e.g.,
    //    1, 2, 3, 6, 5, 4, 7, ....... , or
    //    1, 2, 6, 4, 5, 3, 7, .......
    static BinaryNode *SearchTreeRecover(BinaryNode *node)
    {
        if (node == nullptr || node->Left() == nullptr && node->Right() == nullptr)
            return node;

        // Track the first inversion
        BinaryNode *n1 = nullptr;
        BinaryNode *n2 = nullptr;
        // Track the second inversion
        BinaryNode *n3 = nullptr;
        BinaryNode *n4 = nullptr;

        stack<BinaryNode *> path;
        path.push(node);

        // Track the in-order previous and current nodes
        BinaryNode *prev = nullptr;
        BinaryNode *current = nullptr;
        // Track the last visited node
        BinaryNode *lastVisited = nullptr;

        while (!path.empty())
        {
            current = path.top();
            if (current->Right() != nullptr && current->Right() == lastVisited)
            {
                path.pop();
            }
            else if (current->Left() != nullptr && current->Left() != lastVisited)
            {
                path.push(current->Left());
            }
            else
            {
                if (prev != nullptr && prev->Value() > current->Value())
                {
                    if (n1 == nullptr && n2 == nullptr)
                    {
                        n1 = prev;
                        n2 = current;
                    }
                    else
                    {
                        n3 = prev;
                        n4 = current;
                        break;
                    }
                }
                prev = current;
                if (current->Right() == nullptr)
                    path.pop();
                else
                    path.push(current->Right());
            }
            lastVisited = current;
        }

        if (n3 == nullptr && n4 == nullptr && n1 != nullptr && n2 != nullptr)
        {
            SwapValues(n1, n2);
        }
        else if (n3 != nullptr && n4 != nullptr && n1 != nullptr && n2 != nullptr)
        {
            SwapValues(n1, n4);
        }

        return node;
    }

    static BinaryNode *SearchTreeRecover2(BinaryNode *node)
    {
        if (node == nullptr || node->Left() == nullptr && node->Right() == nullptr)
            return node;

        function<void(BinaryNode *, BinaryNode *&, BinaryNode *&, BinaryNode *&, BinaryNode *&, BinaryNode *&)>
            search = [&](
                         BinaryNode *current,
                         BinaryNode *&prev,
                         BinaryNode *&n1,
                         BinaryNode *&n2,
                         BinaryNode *&n3,
                         BinaryNode *&n4) {
                if (current == nullptr)
                    return;

                search(current->Left(), prev, n1, n2, n3, n4);

                if (prev != nullptr && prev->Value() > current->Value())
                {
                    if (n1 == nullptr && n2 == nullptr)
                    {
                        n1 = prev;
                        n2 = current;
                    }
                    else
                    {
                        n3 = prev;
                        n4 = current;
                        return;
                    }
                }

                prev = current;

                search(current->Right(), prev, n1, n2, n3, n4);
            };

        BinaryNode *prev = nullptr;
        BinaryNode *n1 = nullptr;
        BinaryNode *n2 = nullptr;
        BinaryNode *n3 = nullptr;
        BinaryNode *n4 = nullptr;
        search(node, prev, n1, n2, n3, n4);

        if (n3 == nullptr && n4 == nullptr && n1 != nullptr && n2 != nullptr)
        {
            SwapValues(n1, n2);
        }
        else if (n3 != nullptr && n4 != nullptr && n1 != nullptr && n2 != nullptr)
        {
            SwapValues(n1, n4);
        }

        return node;
    }
};

// Binary tree branch (root-to-leaf path) represents a number with each node as a digit.
// Sum all branch numbers.
// 1____2
//  |___8
// 12 + 18 = 30
static unsigned long long BinaryTreeSumBranches(BinaryNode<unsigned int> *node)
{
    if (node == nullptr)
        return 0;
    stack<BinaryNode<unsigned int> *> path;
    map<BinaryNode<unsigned int> *, unsigned long long> number;
    unsigned long long sum = 0;
    number[node] = node->Value();
    path.push(node);
    while (!path.empty())
    {
        node = path.top();
        path.pop();
        if (node->Left() == nullptr && node->Right() == nullptr)
        {
            sum += number[node];
        }
        if (node->Right() != nullptr)
        {
            number[node->Right()] = 10 * number[node] + node->Right()->Value();
            path.push(node->Right());
        }
        if (node->Left() != nullptr)
        {
            number[node->Left()] = 10 * number[node] + node->Left()->Value();
            path.push(node->Left());
        }
    }
    return sum;
}

// In a binary tree find a path where the sum of node values is maximized.
static long long BinaryTreeMaxPathSum(BinaryNode<int> *root, vector<BinaryNode<int> *> &path)
{
    if (root == nullptr)
        return 0;

    function<void(BinaryNode<int> *, long long &, vector<BinaryNode<int> *> &, long long &, vector<BinaryNode<int> *> &)>
        search = [&](
                     BinaryNode<int> *node,
                     long long &currentSum,
                     vector<BinaryNode<int> *> &currentPath,
                     long long &maxSum,
                     vector<BinaryNode<int> *> &maxPath) {
            currentSum = 0;
            currentPath.clear();
            maxSum = 0;
            maxPath.clear();
            if (node == nullptr)
                return;

            if (node->Left() == nullptr && node->Right() == nullptr)
            {
                currentSum = node->Value();
                currentPath.push_back(node);
                maxSum = node->Value();
                maxPath.push_back(node);
                return;
            }

            long long leftSum;
            vector<BinaryNode<int> *> leftPath;
            long long leftMaxSum;
            vector<BinaryNode<int> *> leftMaxPath;
            search(node->Left(), leftSum, leftPath, leftMaxSum, leftMaxPath);

            long long rightSum;
            vector<BinaryNode<int> *> rightPath;
            long long rightMaxSum;
            vector<BinaryNode<int> *> rightMaxPath;
            search(node->Right(), rightSum, rightPath, rightMaxSum, rightMaxPath);

            if (node->Left() != nullptr && node->Right() == nullptr)
            {
                maxSum = leftMaxSum;
                maxPath.insert(maxPath.begin(), leftMaxPath.begin(), leftMaxPath.end());

                if (leftSum <= 0)
                {
                    currentSum = node->Value();
                    currentPath.push_back(node);

                    if (node->Value() > maxSum)
                    {
                        maxSum = node->Value();
                        maxPath.clear();
                        maxPath.push_back(node);
                    }
                }
                else
                {
                    currentSum = leftSum + node->Value();
                    currentPath.push_back(node);
                    currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());

                    if (leftSum + node->Value() > maxSum)
                    {
                        maxSum = leftSum + node->Value();
                        maxPath.clear();
                        maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
                        maxPath.push_back(node);
                    }
                }
            }
            else if (node->Left() == nullptr && node->Right() != nullptr)
            {
                maxSum = rightMaxSum;
                maxPath.insert(maxPath.begin(), rightMaxPath.begin(), rightMaxPath.end());

                if (rightSum <= 0)
                {
                    currentSum = node->Value();
                    currentPath.push_back(node);

                    if (node->Value() > maxSum)
                    {
                        maxSum = node->Value();
                        maxPath.clear();
                        maxPath.push_back(node);
                    }
                }
                else
                {
                    currentSum = node->Value() + rightSum;
                    currentPath.push_back(node);
                    currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());

                    if (node->Value() + rightSum > maxSum)
                    {
                        maxSum = node->Value() + rightSum;
                        maxPath.clear();
                        maxPath.push_back(node);
                        maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
                    }
                }
            }
            else
            {
                if (leftMaxSum >= rightMaxSum)
                {
                    maxSum = leftMaxSum;
                    maxPath.insert(maxPath.begin(), leftMaxPath.begin(), leftMaxPath.end());
                }
                else
                {
                    maxSum = rightMaxSum;
                    maxPath.insert(maxPath.begin(), rightMaxPath.begin(), rightMaxPath.end());
                }

                if (leftSum <= 0 && rightSum <= 0)
                {
                    currentSum = node->Value();
                    currentPath.push_back(node);

                    if (node->Value() > maxSum)
                    {
                        maxSum = node->Value();
                        maxPath.clear();
                        maxPath.push_back(node);
                    }
                }
                else if (leftSum > 0 && rightSum <= 0)
                {
                    currentSum = leftSum + node->Value();
                    currentPath.push_back(node);
                    currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());

                    if (leftSum + node->Value() > maxSum)
                    {
                        maxSum = leftSum + node->Value();
                        maxPath.clear();
                        maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
                        maxPath.push_back(node);
                    }
                }
                else if (leftSum <= 0 && rightSum > 0)
                {
                    currentSum = node->Value() + rightSum;
                    currentPath.push_back(node);
                    currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());

                    if (node->Value() + rightSum > maxSum)
                    {
                        maxSum = node->Value() + rightSum;
                        maxPath.clear();
                        maxPath.push_back(node);
                        maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
                    }
                }
                else
                {
                    if (leftSum >= rightSum)
                    {
                        currentSum = leftSum + node->Value();
                        currentPath.push_back(node);
                        currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());
                    }
                    else
                    {
                        currentSum = node->Value() + rightSum;
                        currentPath.push_back(node);
                        currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());
                    }

                    if (leftSum + node->Value() + rightSum > maxSum)
                    {
                        maxSum = leftSum + node->Value() + rightSum;
                        maxPath.clear();
                        maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
                        maxPath.push_back(node);
                        maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
                    }
                }
            }
        };

    long long currentSum;
    vector<BinaryNode<int> *> currentPath;
    long long max;
    search(root, currentSum, currentPath, max, path);
    return max;
}

template <class T>
class BinaryNodeWithParent : public BinaryNode<T>
{
public:
    BinaryNodeWithParent(const T &v) : BinaryNode<T>(v)
    {
        this->Neighbor(2) = nullptr;
    }

    virtual ~BinaryNodeWithParent(void) {}

    // Get the reference of parent pointer
    BinaryNodeWithParent *&Parent(void) { return (BinaryNodeWithParent *&)this->Neighbor(2); }
    // Set the parent pointer
    virtual void Parent(BinaryNode *parent) { this->Neighbor(2) = parent; }

    // Create a random binary tree
    // Return nullptr if input is empty
    static BinaryNodeWithParent *RandomTree2(vector<T> &values)
    {
        if (values.size() == 0)
            return nullptr;

        BinaryNode<T> *n = RandomTreeFromInOrder(values);
        BinaryNodeWithParent<T> *node = Clone2(n);
        DeleteTree(n);
        return node;
    }

    // May return nullptr
    static BinaryNodeWithParent *RandomTree2(size_t maxSize)
    {
        vector<T> values;
        int size = rand() % (maxSize + 1);
        for (int i = 0; i < size; i++)
        {
            values.push_back(rand());
        }
        BinaryNodeWithParent<T> *node = RandomTree2(values);
        return node;
    }

    // Non-recursive without stack
    static void PreOrderWalkWithOutStack(BinaryNodeWithParent *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        BinaryNodeWithParent *prev = node;
        while (node != nullptr)
        {
            if (prev == node->Right())
            {
                prev = node;
                node = node->Parent();
            }
            else if (node->Left() != nullptr && node->Left() != prev)
            {
                f(node->Value());
                prev = node;
                node = (BinaryNodeWithParent<T> *)node->Left();
            }
            else
            {
                if (node->Left() == nullptr)
                    f(node->Value());
                prev = node;
                if (node->Right() == nullptr)
                    node = node->Parent();
                else
                    node = (BinaryNodeWithParent<T> *)node->Right();
            }
        }
    }

    void PreOrderWalkWithOutStack(function<void(T)> f) { PreOrderWalkWithOutStack(this, f); }

    // Non-recursive without stack
    static void InOrderWalkWithOutStack(BinaryNodeWithParent *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        BinaryNodeWithParent *prev = node;
        while (node != nullptr)
        {
            if (prev == node->Right())
            {
                prev = node;
                node = node->Parent();
            }
            else if (node->Left() != nullptr && node->Left() != prev)
            {
                prev = node;
                node = (BinaryNodeWithParent<T> *)node->Left();
            }
            else
            {
                f(node->Value());
                prev = node;
                if (node->Right() == nullptr)
                    node = node->Parent();
                else
                    node = (BinaryNodeWithParent<T> *)node->Right();
            }
        }
    }

    void InOrderWalkWithOutStack(function<void(T)> f) { InOrderWalkWithOutStack(this, f); }

    // Non-recursive without stack
    static void PostOrderWalkWithOutStack(BinaryNodeWithParent *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        BinaryNodeWithParent *prev = node;
        while (node != nullptr)
        {
            if (prev == node->Right())
            {
                f(node->Value());
                prev = node;
                node = node->Parent();
            }
            else if (node->Left() != nullptr && node->Left() != prev)
            {
                prev = node;
                node = (BinaryNodeWithParent<T> *)node->Left();
            }
            else
            {
                prev = node;
                if (node->Right() == nullptr)
                {
                    f(node->Value());
                    node = node->Parent();
                }
                else
                {
                    node = (BinaryNodeWithParent<T> *)node->Right();
                }
            }
        }
    }

    void PostOrderWalkWithOutStack(function<void(T)> f) { PostOrderWalkWithOutStack(this, f); }

    static BinaryNodeWithParent<T> *LowestCommonAncestor(BinaryNodeWithParent<T> *first, BinaryNodeWithParent<T> *second)
    {
        if (first == nullptr || second == nullptr)
            return nullptr;
        set<BinaryNodeWithParent<T> *> visited;
        pair<set<BinaryNodeWithParent<T> *>::iterator, bool> result;
        auto checkAndMoveUp = [&](BinaryNodeWithParent<T> **p) -> bool {
            if (*p != nullptr)
            {
                // set.insert returns a pair, where the second value is a bool indicating
                // whether the first value points to a new element or an existing element.
                result = visited.insert(*p);
                if (!result.second)
                {
                    // Insert failed because the same element already exists
                    return true;
                }
                *p = (*p)->Parent();
            }
            return false;
        };

        while (first != nullptr || second != nullptr)
        {
            if (checkAndMoveUp(&first))
                return first;
            if (checkAndMoveUp(&second))
                return second;
        }
        return nullptr;
    }

    static BinaryNodeWithParent<T> *LowestCommonAncestor2(BinaryNodeWithParent<T> *first, BinaryNodeWithParent<T> *second)
    {
        if (first == nullptr || second == nullptr)
            return nullptr;
        int df = first->Depth();
        int ds = second->Depth();
        int dd = df > ds ? df - ds : ds - df;
        BinaryNodeWithParent<T> *h = df < ds ? first : second;
        BinaryNodeWithParent<T> *l = df < ds ? second : first;
        for (int i = 0; i < dd; i++)
        {
            l = l->Parent();
        }
        while (h != nullptr && l != nullptr)
        {
            if (h == l)
                return h;
            h = h->Parent();
            l = l->Parent();
        }
        return nullptr;
    }

    // Count height of tree rooted at node
    // Non-recursive
    static int Height2(BinaryNodeWithParent *node)
    {
        if (node == nullptr)
            return 0;
        BinaryNodeWithParent *prev = node;
        // Track the maximum height while traversing the tree
        int max = 0;
        // Track the height of current node
        int h = 0;
        while (node != nullptr)
        {
            if (prev == node->Right())
            {
                // h is the height of right
                // Minus one to get the height of node
                h--;
                prev = node;
                node = node->Parent();
            }
            else if (node->Left() != nullptr && node->Left() != prev)
            {
                // h is the height of node
                // Plus one to get the height of left child
                h++;
                if (h > max)
                    max = h;
                prev = node;
                node = (BinaryNodeWithParent *)node->Left();
            }
            else
            {
                if (node->Left() == prev)
                {
                    // h is the height of left
                    // Minus one to get the height of node
                    h--;
                }
                else if (node->Left() == nullptr)
                {
                    // h is the height of parent
                    // Plus one to get the height of node
                    h++;
                    if (h > max)
                        max = h;
                }

                prev = node;
                if (node->Right() == nullptr)
                    node = node->Parent();
                else
                    node = (BinaryNodeWithParent *)node->Right();
            }
        }
        return max;
    }

    int Height2(void) { return Height2(this); }

    // Count the distance of node from the root
    static int Depth(BinaryNodeWithParent *node)
    {
        int d = 0;
        while (node != nullptr)
        {
            d++;
            node = node->Parent();
        }
        return d;
    }

    int Depth(void) { return Depth(this); }

    static BinaryNodeWithParent *Clone2(BinaryNode *node)
    {
        if (node == nullptr)
            return nullptr;
        BinaryNodeWithParent *newNode = new BinaryNodeWithParent(node->Value());
        BinaryNodeWithParent *left = Clone2(node->Left());
        if (left != nullptr)
        {
            newNode->Left() = left;
            left->Parent() = newNode;
        }
        BinaryNodeWithParent *right = Clone2(node->Right());
        if (right != nullptr)
        {
            newNode->Right() = right;
            right->Parent() = newNode;
        }
        return newNode;
    }

    BinaryNodeWithParent *Clone2(void) { return Clone2(this); }

    // Find the lagest binary search tree in a binary tree.
    // http://leetcode.com/2010/11/largest-binary-search-tree-bst-in_22.html
    // Bottom-up recursively to find the max search tree
    static BinaryNodeWithParent *MaxSearchTreeInBinaryTree(BinaryNode<T> *binaryTree)
    {
        // Given a binary search tree, find the first node less than or equal to a value
        function<BinaryNodeWithParent<T> *(BinaryNodeWithParent<T> *, T)>
            firstNodeLessThanOrEqual = [&](BinaryNodeWithParent<T> *n, T v) -> BinaryNodeWithParent<T> * {
            while (n != nullptr)
            {
                if (n->Value() <= v)
                {
                    // Implicitly, n is its parent's left child. Otherwise,
                    // its parent should be returned.
                    return n;
                }
                if (n->Left() != nullptr)
                    n = (BinaryNodeWithParent<T> *)n->Left();
                else
                    n = (BinaryNodeWithParent<T> *)n->Right();
            }
            return n;
        };

        // Given a binary search tree, find the first node greater than a value
        function<BinaryNodeWithParent<T> *(BinaryNodeWithParent<T> *, T)>
            firstNodeGreaterThan = [&](BinaryNodeWithParent<T> *n, T v) -> BinaryNodeWithParent<T> * {
            while (n != nullptr)
            {
                if (n->Value() > v)
                {
                    // Implicitly, n is its parent's right child. Otherwise,
                    // its parent should be returned.
                    return n;
                }
                if (n->Right() != nullptr)
                    n = (BinaryNodeWithParent<T> *)n->Right();
                else
                    n = (BinaryNodeWithParent<T> *)n->Left();
            }
            return n;
        };

        // Merge the binary search tree in left subtree with current node to form a new binary search tree
        function<void(BinaryNodeWithParent<T> *&, int &, BinaryNodeWithParent<T> *, int)>
            mergeLeft = [&](BinaryNodeWithParent<T> *&node, int &count, BinaryNodeWithParent<T> *left, int leftCount) {
                BinaryNodeWithParent<T> *clone = Clone2(left);
                BinaryNodeWithParent<T> *invalid = firstNodeGreaterThan(clone, node->Value());
                int invalidSize = invalid == nullptr ? 0 : Size(invalid);
                node->Left() = clone;
                clone->Parent() = node;
                count += (leftCount - invalidSize);
                if (invalid != nullptr)
                {
                    BinaryNodeWithParent<T> *p = invalid->Parent();
                    p->Right() = nullptr;
                    DeleteTree(invalid);
                }
            };

        // Merge the binary search tree in right subtree with current node to form a new binary search tree
        function<void(BinaryNodeWithParent<T> *&, int &, BinaryNodeWithParent<T> *, int)>
            mergeRight = [&](BinaryNodeWithParent<T> *&node, int &count, BinaryNodeWithParent<T> *right, int rightCount) {
                BinaryNodeWithParent<T> *clone = Clone2(right);
                BinaryNodeWithParent<T> *invalid = firstNodeLessThanOrEqual(clone, node->Value());
                int invalidSize = invalid == nullptr ? 0 : Size(invalid);
                node->Right() = clone;
                clone->Parent() = node;
                count += (rightCount - invalidSize);
                if (invalid != nullptr)
                {
                    BinaryNodeWithParent<T> *p = invalid->Parent();
                    p->Left() = nullptr;
                    DeleteTree(invalid);
                }
            };

        function<void(BinaryNode<T> *, BinaryNodeWithParent<T> *&, int &, BinaryNodeWithParent<T> *&, int &)>
            search = [&](
                         BinaryNode<T> *node,               // current node from input binary tree
                         BinaryNodeWithParent<T> *&current, // root of current search tree
                         int &currentCount,                 // node count of current search tree
                         BinaryNodeWithParent<T> *&last,    // root of last max search tree. can be current or different.
                         int &lastCount                     // node count of last max search tree.
                     ) {
                if (node == nullptr)
                {
                    current = nullptr;
                    currentCount = 0;
                    last = nullptr;
                    lastCount = 0;
                    return;
                }

                BinaryNodeWithParent<T> *left;
                int leftCount;
                BinaryNodeWithParent<T> *leftLast;
                int leftLastCount;
                search(node->Left(), left, leftCount, leftLast, leftLastCount);

                BinaryNodeWithParent<T> *right;
                int rightCount;
                BinaryNodeWithParent<T> *rightLast;
                int rightLastCount;
                search(node->Right(), right, rightCount, rightLast, rightLastCount);

                current = new BinaryNodeWithParent<T>(node->Value());
                currentCount = 1;

                if (left != nullptr && left->Value() <= current->Value())
                {
                    mergeLeft(current, currentCount, left, leftCount);
                }

                if (right != nullptr && right->Value() > current->Value())
                {
                    mergeRight(current, currentCount, right, rightCount);
                }

                if (leftLastCount >= rightLastCount)
                {
                    last = leftLast;
                    lastCount = leftLastCount;
                }
                else
                {
                    last = rightLast;
                    lastCount = rightLastCount;
                }

                if (currentCount >= lastCount)
                {
                    last = current;
                    lastCount = currentCount;
                }

                if (left != last)
                    DeleteTree(left);
                if (right != last)
                    DeleteTree(right);
                if (leftLast != last && leftLast != left)
                    DeleteTree(leftLast);
                if (rightLast != last && rightLast != right)
                    DeleteTree(rightLast);
            };

        BinaryNodeWithParent<T> *node;
        int count;
        BinaryNodeWithParent<T> *last;
        int lastCount;
        search(binaryTree, node, count, last, lastCount);

        if (node != last)
        {
            if (count >= lastCount)
            {
                DeleteTree(last);
                last = node;
            }
            else
            {
                DeleteTree(node);
            }
        }
        return last;
    }

    // This implementation follows http://leetcode.com/2010/11/largest-binary-search-tree-bst-in_22.html
    // However, the algorithm is wrong. The algorithm uses the node value
    // to define a range to search sub solutions in its children. But the
    // range may rule out possible solutions containing nodes outside of
    // the range. Some examples are shown in test.
    static BinaryNodeWithParent *MaxSearchTreeInBinaryTree2(BinaryNode<T> *binaryTree)
    {
        T binaryTreeMin = Min(binaryTree)->Value();
        T binaryTreeMax = Max(binaryTree)->Value();

        function<void(BinaryNode<T> *, T, T, BinaryNodeWithParent<T> *&, int &, BinaryNodeWithParent<T> *&, int &)>
            search = [&](
                         BinaryNode<T> *node,               // current node from input binary tree
                         T min,                             // lower bound of node value
                         T max,                             // upper bound of node value
                         BinaryNodeWithParent<T> *&current, // root of current search tree
                         int &currentCount,                 // node count of current search tree
                         BinaryNodeWithParent<T> *&last,    // root of last max search tree. can be current or different.
                         int &lastCount                     // node count of last max search tree.
                     ) {
                if (node == nullptr)
                {
                    current = nullptr;
                    currentCount = 0;
                    last = nullptr;
                    lastCount = 0;
                    return;
                }

                if (min < node->Value() && node->Value() <= max)
                {
                    BinaryNodeWithParent<T> *left;
                    int leftCount;
                    BinaryNodeWithParent<T> *leftLast;
                    int leftLastCount;
                    search(node->Left(), min, node->Value(), left, leftCount, leftLast, leftLastCount);

                    BinaryNodeWithParent<T> *right;
                    int rightCount;
                    BinaryNodeWithParent<T> *rightLast;
                    int rightLastCount;
                    search(node->Right(), node->Value(), max, right, rightCount, rightLast, rightLastCount);

                    current = new BinaryNodeWithParent<T>(node->Value());
                    currentCount = 1;

                    if (left != nullptr)
                    {
                        current->Left() = left;
                        left->Parent() = current;
                        currentCount += leftCount;
                    }

                    if (right != nullptr)
                    {
                        current->Right() = right;
                        right->Parent() = current;
                        currentCount += rightCount;
                    }

                    if (leftLastCount >= rightLastCount)
                    {
                        last = leftLast;
                        lastCount = leftLastCount;
                    }
                    else
                    {
                        last = rightLast;
                        lastCount = rightLastCount;
                    }

                    if (currentCount >= lastCount)
                    {
                        last = current;
                        lastCount = currentCount;
                    }

                    if (left != current->Left() && left != last)
                        DeleteTree(left);
                    if (right != current->Right() && right != last)
                        DeleteTree(right);
                    if (leftLast != last && leftLast != left)
                        DeleteTree(leftLast);
                    if (rightLast != last && rightLast != right)
                        DeleteTree(rightLast);
                }
                else
                {
                    search(node, binaryTreeMin - 1, binaryTreeMax + 1, current, currentCount, last, lastCount);
                    current = nullptr;
                    currentCount = 0;
                }
            };

        BinaryNodeWithParent<T> *node;
        int count;
        BinaryNodeWithParent<T> *last;
        int lastCount;
        search(binaryTree, binaryTreeMin - 1, binaryTreeMax + 1, node, count, last, lastCount);

        if (node != last)
        {
            if (count >= lastCount)
            {
                DeleteTree(last);
                last = node;
            }
            else
            {
                DeleteTree(node);
            }
        }
        return last;
    }

    // Find the lagest binary search sub tree in a binary tree.
    // http://leetcode.com/2010/11/largest-binary-search-tree-bst-in.html
    static BinaryNodeWithParent *MaxSubSearchTreeInBinaryTree(BinaryNode<T> *binaryTree)
    {
        function<void(BinaryNode<T> *&, BinaryNodeWithParent<T> *&, int &, T &, T &)>
            search = [&](
                         BinaryNode<T> *&node,              // current node from input binary tree. updated to the node corresponding to current.
                         BinaryNodeWithParent<T> *&current, // root of current search tree
                         int &currentCount,                 // node count of current search tree
                         T &currentMin,                     // min of current search tree
                         T &currentMax                      // max of current search tree
                     ) {
                if (node == nullptr)
                {
                    current = nullptr;
                    currentCount = 0;
                    return;
                }

                BinaryNode<T> *leftChild = node->Left();
                BinaryNodeWithParent<T> *left;
                int leftCount;
                T leftMin;
                T leftMax;
                search(leftChild, left, leftCount, leftMin, leftMax);

                BinaryNode<T> *rightChild = node->Right();
                BinaryNodeWithParent<T> *right;
                int rightCount;
                T rightMin;
                T rightMax;
                search(rightChild, right, rightCount, rightMin, rightMax);

                if ((left == nullptr || (leftChild == node->Left() && leftMax <= node->Value())) && (right == nullptr || (rightChild == node->Right() && rightMin > node->Value())))
                {
                    // Left sub search tree and right sub search tree are both children of node. Merge them.
                    current = new BinaryNodeWithParent<T>(node->Value());
                    current->Left() = left;
                    if (left != nullptr)
                        left->Parent() = current;
                    current->Right() = right;
                    if (right != nullptr)
                        right->Parent() = current;
                    currentCount = 1 + leftCount + rightCount;
                    currentMin = left == nullptr ? node->Value() : leftMin;
                    currentMax = right == nullptr ? node->Value() : rightMax;
                }
                else
                {
                    if (leftCount >= rightCount)
                    {
                        // Set node to the left sub search tree. It will be bottomed up to check if a merge at its parent is possible.
                        node = leftChild;
                        current = left;
                        currentCount = leftCount;
                        currentMin = leftMin;
                        currentMax = leftMax;
                        if (right != nullptr)
                            DeleteTree(right);
                    }
                    else
                    {
                        // Set node to the right sub search tree. It will be bottomed up to check if a merge at its parent is possible.
                        node = rightChild;
                        current = right;
                        currentCount = rightCount;
                        currentMin = rightMin;
                        currentMax = rightMax;
                        if (left != nullptr)
                            DeleteTree(left);
                    }
                }
            };

        BinaryNodeWithParent<T> *node;
        int count;
        T min;
        T max;
        search(binaryTree, node, count, min, max);
        return node;
    }

    static BinaryNodeWithParent *MaxSubSearchTreeInBinaryTree2(BinaryNode<T> *binaryTree)
    {
        // Record subtrees already verified to avoid re-verification
        map<BinaryNode<T> *, int> subtrees;

        function<bool(BinaryNode<T> *, T &, T &, int &)>
            isSearchTree = [&](BinaryNode<T> *node, T &min, T &max, int &count) -> bool {
            count = 0;
            if (node == nullptr)
                return true;
            min = node->Value();
            max = node->Value();
            if (subtrees.find(node) != subtrees.end())
            {
                count = subtrees[node];
                return count >= 0;
            }

            T leftMin;
            T leftMax;
            int leftCount;
            bool leftTrue = isSearchTree(node->Left(), leftMin, leftMax, leftCount);

            T rightMin;
            T rightMax;
            int rightCount;
            bool rightTrue = isSearchTree(node->Right(), rightMin, rightMax, rightCount);

            if (!leftTrue || !rightTrue || (node->Left() != nullptr && leftMax > node->Value()) || (node->Right() != nullptr && rightMin <= node->Value()))
            {
                subtrees[node] = -1;
                return false;
            }

            min = node->Left() == nullptr ? node->Value() : leftMin;
            max = node->Right() == nullptr ? node->Value() : rightMax;
            count += (1 + leftCount + rightCount);
            subtrees[node] = count;
            return true;
        };

        function<void(BinaryNode<T> *, BinaryNodeWithParent<T> *&, int &)>
            search = [&](
                         BinaryNode<T> *node,               // current node from input binary tree
                         BinaryNodeWithParent<T> *&current, // root of current search tree
                         int &currentCount                  // node count of current search tree
                     ) {
                if (node == nullptr)
                {
                    current = nullptr;
                    currentCount = 0;
                    return;
                }

                T min;
                T max;
                if (isSearchTree(node, min, max, currentCount))
                {
                    current = BinaryNodeWithParent<T>::Clone2(node);
                }
                else
                {
                    BinaryNodeWithParent<T> *left;
                    int leftCount;
                    search(node->Left(), left, leftCount);

                    BinaryNodeWithParent<T> *right;
                    int rightCount;
                    search(node->Right(), right, rightCount);

                    if (leftCount >= rightCount)
                    {
                        current = left;
                        currentCount = leftCount;
                        if (right != nullptr)
                            DeleteTree(right);
                    }
                    else
                    {
                        current = right;
                        currentCount = rightCount;
                        if (left != nullptr)
                            DeleteTree(left);
                    }
                }
            };

        BinaryNodeWithParent<T> *node;
        int count;
        search(binaryTree, node, count);
        return node;
    }

    //
    // Binary Search Tree
    //

    static BinaryNodeWithParent<T> *SearchTreeSuccessor(BinaryNodeWithParent<T> *node)
    {
        if (node == nullptr)
            return node;
        //  (A)
        //  / \
		// () (B)
        // The successor of A is the minimum node of subtree B
        if (node->Right() != nullptr)
            return (BinaryNodeWithParent<T> *)SearchTreeMin(node->Right());
        //    (B)
        //   /
        // (C)
        //   \
		//    ()
        //      \
		//      (A)
        //      / \
		//     () NULL
        // The successor of A is the lowest ancestor B whose left child C contains A in its right substree
        BinaryNodeWithParent<T> *parent = node->Parent();
        while (parent != nullptr && node == parent->Right())
        {
            node = parent;
            parent = parent->Parent();
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

    static BinaryNodeWithParent<T> *SearchTreePredecessor(BinaryNodeWithParent<T> *node)
    {
        if (node == nullptr)
            return nullptr;
        //   (A)
        //   /
        // (B)
        // The predecessor of A is the maximum node of subtree B
        if (node->Left() != nullptr)
            return (BinaryNodeWithParent<T> *)SearchTreeMax(node->Left());
        //     (B)
        //       \
		//       (C)
        //       /
        //      ()
        //     /
        //   (A)
        //   / \
		// NULL ()
        // The predecessor of A is the lowest ancestor B whose right child C contains A in its left substree
        BinaryNodeWithParent<T> *parent = node->Parent();
        while (parent != nullptr && node == parent->Left())
        {
            node = parent;
            parent = parent->Parent();
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

    // Delete a node from a binary search tree. Return the root of tree.
    static BinaryNodeWithParent<T> *SearchTreeDelete(BinaryNodeWithParent<T> *tree, BinaryNodeWithParent<T> *node)
    {
        if (tree == nullptr || node == nullptr)
            return tree;

        // Replace the subtree at dst with the subtree at src. Return dst.
        auto transplant = [&](BinaryNodeWithParent<T> *dst, BinaryNodeWithParent<T> *src) -> BinaryNodeWithParent<T> * {
            if (dst == nullptr)
                return dst;
            if (dst->Parent() == nullptr)
            {
                // src becomes the new root
                if (src != nullptr)
                    src->Parent() = nullptr;
                return dst;
            }
            if (dst == dst->Parent()->Left())
                dst->Parent()->Left() = src;
            else
                dst->Parent()->Right() = src;
            if (src != nullptr)
                src->Parent() = dst->Parent();
            return dst;
        };

        if (node->Left() == nullptr)
        {
            //   ()
            //    |
            //   (A)
            //   /  \
			// NULL (B)
            BinaryNodeWithParent<T> *r = (BinaryNodeWithParent<T> *)node->Right();
            transplant(node, r);
            node->Right() = nullptr;
            if (tree == node)
            {
                // r is the new root
                tree = r;
            }
            delete node;
            node = nullptr;
            return tree;
        }

        if (node->Right() == nullptr)
        {
            //   ()
            //    |
            //   (A)
            //   /  \
			// (B) NULL
            BinaryNodeWithParent<T> *l = (BinaryNodeWithParent<T> *)node->Left();
            transplant(node, l);
            node->Left() = nullptr;
            if (tree == node)
            {
                // l is the new root
                tree = l;
            }
            delete node;
            node = nullptr;
            return tree;
        }

        BinaryNodeWithParent<T> *successor = (BinaryNodeWithParent<T> *)SearchTreeMin(node->Right());

        if (successor->Parent() != node)
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
            transplant(successor, (BinaryNodeWithParent<T> *)successor->Right());
            //     ()
            //     |
            //    (A)
            //    / \
			//   () (D)
            //        \
			//         ()
            //        /
            //      (C)           (B)
            successor->Right() = node->Right();
            ((BinaryNodeWithParent<T> *)successor->Right())->Parent() = successor;
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

        transplant(node, successor);
        successor->Left() = node->Left();
        ((BinaryNodeWithParent<T> *)successor->Left())->Parent() = successor;

        if (tree == node)
        {
            // successor is the new root
            tree = successor;
        }

        node->Left() = nullptr;
        node->Right() = nullptr;
        delete node;
        node = nullptr;

        return tree;
    }
};

template <class T>
class BinaryNodeWithRightSibling : public BinaryNode<T>
{
public:
    BinaryNodeWithRightSibling(const T &v) : BinaryNode<T>(v)
    {
        this->Neighbor(2) = nullptr;
    }

    virtual ~BinaryNodeWithRightSibling(void) {}

    // Get the reference of right sibling pointer
    BinaryNodeWithRightSibling *&RightSibling(void) { return (BinaryNodeWithRightSibling *&)this->Neighbor(2); }
    // Set the right sibling pointer
    void RightSibling(BinaryNode *p) { this->Neighbor(2) = p; }

    // This works for both complete and incomplete binary trees
    static void SetRightSibling(BinaryNodeWithRightSibling *node)
    {
        if (node == nullptr)
            return;

        while (node != nullptr)
        {
            // Track nodes at current level, which is already done with rightSibling setting
            BinaryNodeWithRightSibling *current = node;
            // Track the beginning of next level, which is to set with rightSibling
            node = (BinaryNodeWithRightSibling *)current->Left();
            // Find the beginning
            while (node == nullptr && current != nullptr)
            {
                node = (BinaryNodeWithRightSibling *)current->Left();
                if (node == nullptr)
                {
                    // Current has no left child
                    node = (BinaryNodeWithRightSibling *)current->Right();
                }
                if (node == nullptr)
                {
                    // Current has no left and right children
                    current = current->RightSibling();
                }
            }

            if (node == nullptr)
            {
                // No more nodes in the next level
                return;
            }

            BinaryNodeWithRightSibling *prev = node;
            if (prev == current->Left())
            {
                if (current->Right() != nullptr)
                {
                    prev->RightSibling() = (BinaryNodeWithRightSibling *)current->Right();
                    prev = (BinaryNodeWithRightSibling *)current->Right();
                }
            }

            current = current->RightSibling();
            while (current != nullptr)
            {
                if (current->Left() != nullptr)
                {
                    prev->RightSibling() = (BinaryNodeWithRightSibling *)current->Left();
                    prev = (BinaryNodeWithRightSibling *)current->Left();
                }
                if (current->Right() != nullptr)
                {
                    prev->RightSibling() = (BinaryNodeWithRightSibling *)current->Right();
                    prev = (BinaryNodeWithRightSibling *)current->Right();
                }
                current = current->RightSibling();
            }
        }
    }

    void SetRightSibling(void) { SetRightSibling(this); }

    // DFS
    // This works for complete binary tree only
    static void SetRightSibling2(BinaryNodeWithRightSibling *node)
    {
        if (node == nullptr)
            return;

        BinaryNodeWithRightSibling *p = (BinaryNodeWithRightSibling *)node->Left();
        if (p != nullptr)
        {
            p->RightSibling() = (BinaryNodeWithRightSibling *)node->Right();
        }

        if (node->Right() != nullptr)
        {
            p = (BinaryNodeWithRightSibling *)node->Right();
        }

        if (p != nullptr)
        {
            // For incomplete binary tree, the following search will fail,
            // because not all rightSibling of nodes at current level are set yet.
            BinaryNodeWithRightSibling *current = node->RightSibling();
            while (current != nullptr)
            {
                if (current->Left() != nullptr)
                {
                    p->RightSibling() = (BinaryNodeWithRightSibling *)current->Left();
                    break;
                }
                if (current->Right() != nullptr)
                {
                    p->RightSibling() = (BinaryNodeWithRightSibling *)current->Right();
                    break;
                }
                current = current->RightSibling();
            }
        }

        SetRightSibling2((BinaryNodeWithRightSibling *)node->Left());
        SetRightSibling2((BinaryNodeWithRightSibling *)node->Right());
    }

    void SetRightSibling2(void) { SetRightSibling2(this); }

    static BinaryNodeWithRightSibling *Clone2(BinaryNode *node)
    {
        if (node == nullptr)
            return nullptr;
        BinaryNodeWithRightSibling *newNode = new BinaryNodeWithRightSibling(node->Value());
        BinaryNodeWithRightSibling *left = Clone2(node->Left());
        if (left != nullptr)
        {
            newNode->Left() = left;
        }
        BinaryNodeWithRightSibling *right = Clone2(node->Right());
        if (right != nullptr)
        {
            newNode->Right() = right;
        }

        return newNode;
    }

    BinaryNodeWithRightSibling *Clone2(void) { return Clone2(this); }

    // Visit level by level, left to right
    // Breadth-first search
    static void LevelOrderWalk3(BinaryNodeWithRightSibling *node, function<void(T)> f)
    {
        if (node == nullptr || f == nullptr)
            return;
        while (node != nullptr)
        {
            BinaryNodeWithRightSibling *p = node;
            while (p != nullptr)
            {
                f(p->Value());
                p = p->RightSibling();
            }

            while (p == nullptr && node != nullptr)
            {
                p = (BinaryNodeWithRightSibling *)node->Left();
                if (p == nullptr)
                    p = (BinaryNodeWithRightSibling *)node->Right();
                if (p == nullptr)
                    node = node->RightSibling();
            }

            node = p;
        }
    }

    virtual void LevelOrderWalk3(function<void(T)> f) { LevelOrderWalk3(this, f); }
};

template <class T, template <class T> class N>
class BinaryIterator
{
protected:
    N<T> *pointer;

    void Check(void) const
    {
        if (this->pointer == nullptr)
        {
            throw invalid_argument(
                String::Format("BinaryIterator<%s, %s>::iterator is not initialized", typeid(T).name(), typeid(N).name()));
        }
    }

public:
    BinaryIterator(N<T> *p) : pointer(p) {}
    BinaryIterator(const BinaryIterator &it) : pointer(it.pointer) {}
    BinaryIterator(void) : pointer(nullptr) {}

    // Get the value of current node
    const T &Current() const
    {
        Check();
        T &d = this->pointer->Value();
        return d;
    }

    // Return a pointer so that dereference is on the return type
    const N<T> *operator->()
    {
        Check();
        return this->pointer;
    }

    const T &operator*() const { return Current(); }

    // Note: There is no return value
    // This allows to check if an iterator is valid by using
    //     if (it) { } else { }
    operator bool() const { return this->pointer != nullptr; }

    bool operator==(const BinaryIterator &it) const { return this->pointer == it.pointer; }
    bool operator!=(const BinaryIterator &it) const { return this->pointer != it.pointer; }

    // Prefix increment
    // ++ it
    virtual bool operator++() { return false; }

    // Postfix increment
    // it ++
    virtual bool operator++(int) { return false; }
};

template <class T, template <class T> class N>
class PreOrderBinaryIterator : public BinaryIterator<T, N>
{
private:
    stack<N<T> *> path;
    N<T> *current;

public:
    PreOrderBinaryIterator(N<T> *p) : BinaryIterator(p), current(p)
    {
        this->operator++();
    }

    PreOrderBinaryIterator(const PreOrderBinaryIterator &it) : BinaryIterator(it), current(it.pointer)
    {
        this->operator++();
    }

    PreOrderBinaryIterator(void) : BinaryIterator(), current(nullptr) {}

    // Prefix increment
    // ++ it
    bool operator++()
    {
        while (!this->path.empty() || this->current != nullptr)
        {
            if (this->current != nullptr)
            {
                this->pointer = this->current;
                path.push(this->current);
                this->current = (N<T> *)this->current->Left();
                break;
            }
            else
            {
                this->current = (N<T> *)this->path.top()->Right();
                this->path.pop();
            }
        }

        if (this->path.empty() && this->current == nullptr)
        {
            this->pointer = nullptr;
        }

        return this->pointer != nullptr;
    }

    // Postfix increment
    // it ++
    bool operator++(int) { return operator++(); }
};

template <class T>
class PreOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent>
{
private:
    BinaryNodeWithParent<T> *current;
    BinaryNodeWithParent<T> *prev;

public:
    PreOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> *p) : BinaryIterator(p), current(p), prev(p)
    {
        this->operator++();
    }

    PreOrderBinaryIteratorWithOutStack(const PreOrderBinaryIteratorWithOutStack &it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
    {
        this->operator++();
    }

    PreOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

    // Prefix increment
    // ++ it
    bool operator++()
    {
        while (this->current != nullptr)
        {
            if (this->prev == this->current->Right())
            {
                this->prev = this->current;
                this->current = this->current->Parent();
            }
            else if (this->current->Left() != nullptr && this->prev != this->current->Left())
            {
                this->pointer = this->current;
                this->prev = this->current;
                this->current = (BinaryNodeWithParent<T> *)this->current->Left();
                break;
            }
            else
            {
                if (this->current->Left() == nullptr)
                {
                    this->pointer = this->current;
                }

                this->prev = this->current;
                if (this->current->Right() != nullptr)
                {
                    this->current = (BinaryNodeWithParent<T> *)this->current->Right();
                }
                else
                {
                    this->current = this->current->Parent();
                }

                if (this->pointer == this->prev)
                {
                    break;
                }
            }
        }

        if (this->current == nullptr)
        {
            this->pointer = nullptr;
        }

        return this->pointer != nullptr;
    }

    // Postfix increment
    // it ++
    bool operator++(int) { return operator++(); }
};

template <class T, template <class T> class N>
class InOrderBinaryIterator : public BinaryIterator<T, N>
{
private:
    stack<N<T> *> path;
    N<T> *current;

public:
    InOrderBinaryIterator(N<T> *p) : BinaryIterator(p), current(p)
    {
        this->operator++();
    }

    InOrderBinaryIterator(const InOrderBinaryIterator &it) : BinaryIterator(it), current(it.pointer)
    {
        this->operator++();
    }

    InOrderBinaryIterator(void) : BinaryIterator(), current(nullptr) {}

    // Prefix increment
    // ++ it
    bool operator++()
    {
        if (this->path.empty() && this->current == nullptr)
        {
            this->pointer = nullptr;
        }

        while (!this->path.empty() || this->current != nullptr)
        {
            if (this->current != nullptr)
            {
                path.push(this->current);
                this->current = (N<T> *)this->current->Left();
            }
            else
            {
                this->pointer = this->path.top();
                this->path.pop();
                this->current = (N<T> *)this->pointer->Right();
                break;
            }
        }

        return this->pointer != nullptr;
    }

    // Postfix increment
    // it ++
    bool operator++(int) { return operator++(); }
};

template <class T>
class InOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent>
{
private:
    BinaryNodeWithParent<T> *current;
    BinaryNodeWithParent<T> *prev;

public:
    InOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> *p) : BinaryIterator(p), current(p), prev(p)
    {
        this->operator++();
    }

    InOrderBinaryIteratorWithOutStack(const InOrderBinaryIteratorWithOutStack &it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
    {
        this->operator++();
    }

    InOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

    // Prefix increment
    // ++ it
    bool operator++()
    {
        while (this->current != nullptr)
        {
            if (this->prev == this->current->Right())
            {
                this->prev = this->current;
                this->current = this->current->Parent();
            }
            else if (this->current->Left() != nullptr && this->prev != this->current->Left())
            {
                this->prev = this->current;
                this->current = (BinaryNodeWithParent<T> *)this->current->Left();
            }
            else
            {
                this->pointer = this->current;
                this->prev = this->current;
                if (this->current->Right() != nullptr)
                {
                    this->current = (BinaryNodeWithParent<T> *)this->current->Right();
                }
                else
                {
                    this->current = this->current->Parent();
                }

                break;
            }
        }

        if (this->current == nullptr)
        {
            this->pointer = nullptr;
        }

        return this->pointer != nullptr;
    }

    // Postfix increment
    // it ++
    bool operator++(int) { return operator++(); }
};

template <class T, template <class T> class N>
class PostOrderBinaryIterator : public BinaryIterator<T, N>
{
private:
    stack<N<T> *> path;
    N<T> *current;
    N<T> *prev;

public:
    PostOrderBinaryIterator(N<T> *p) : BinaryIterator(p), current(p), prev(nullptr)
    {
        this->operator++();
    }

    PostOrderBinaryIterator(const PostOrderBinaryIterator &it) : BinaryIterator(it), current(it.pointer), prev(nullptr)
    {
        this->operator++();
    }

    PostOrderBinaryIterator(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

    // Prefix increment
    // ++ it
    bool operator++()
    {
        if (this->path.empty() && this->current == nullptr)
        {
            this->pointer = nullptr;
        }

        while (!this->path.empty() || this->current != nullptr)
        {
            if (this->current != nullptr)
            {
                this->path.push(this->current);
                this->current = (N<T> *)this->current->Left();
            }
            else
            {
                if (this->path.top()->Right() != nullptr && this->path.top()->Right() != this->prev)
                {
                    this->current = (N<T> *)this->path.top()->Right();
                }
                else
                {
                    this->pointer = this->path.top();
                    this->path.pop();
                    this->prev = this->pointer;
                    break;
                }
            }
        }

        return this->pointer != nullptr;
    }

    // Postfix increment
    // it ++
    bool operator++(int) { return operator++(); }
};

template <class T>
class PostOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent>
{
private:
    BinaryNodeWithParent<T> *current;
    BinaryNodeWithParent<T> *prev;

public:
    PostOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> *p) : BinaryIterator(p), current(p), prev(p)
    {
        this->operator++();
    }

    PostOrderBinaryIteratorWithOutStack(const PostOrderBinaryIteratorWithOutStack &it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
    {
        this->operator++();
    }

    PostOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

    // Prefix increment
    // ++ it
    bool operator++()
    {
        if (this->current == nullptr)
        {
            this->pointer = nullptr;
        }

        while (this->current != nullptr)
        {
            if (this->prev == this->current->Right())
            {
                this->pointer = this->current;
                this->prev = this->current;
                this->current = this->current->Parent();
                break;
            }
            else if (this->current->Left() != nullptr && this->prev != this->current->Left())
            {
                this->prev = this->current;
                this->current = (BinaryNodeWithParent<T> *)this->current->Left();
            }
            else
            {
                this->prev = this->current;
                if (this->current->Right() != nullptr)
                {
                    this->current = (BinaryNodeWithParent<T> *)this->current->Right();
                }
                else
                {
                    this->pointer = this->current;
                    this->current = this->current->Parent();
                    break;
                }
            }
        }

        return this->pointer != nullptr;
    }

    // Postfix increment
    // it ++
    bool operator++(int) { return operator++(); }
};

template <class T>
class BinaryTree
{
public:
    class Node
    {
        template <class T>
        friend class BinaryTree;

    private:
        T content;
        Node *parent;
        Node *left;
        Node *right;

    public:
        Node(const T &c) : content(c), parent(nullptr), left(nullptr), right(nullptr) {}
        // Not delete its children
        ~Node(void)
        {
            auto f = [](Node *p) { if (p != nullptr) { p = nullptr;} };
            f(this->left);
            f(this->right);
            f(this->parent);
        }
        static void PreOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            f(node);
            PreOrderWalk(node->left, f);
            PreOrderWalk(node->right, f);
        }
        void PreOrderWalk(function<void(Node *)> f) { PreOrderWalk(this, f); }
        static void InOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            InOrderWalk(node->left, f);
            f(node);
            InOrderWalk(node->right, f);
        }
        void InOrderWalk(function<void(Node *)> f) { InOrderWalk(this, f); }
        static void PostOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            PostOrderWalk(node->left, f);
            PostOrderWalk(node->right, f);
            f(node);
        }
        void PostOrderWalk(function<void(Node *)> f) { PostOrderWalk(this, f); }
        static void Empty(Node *node)
        {
            PostOrderWalk(node->left, [](Node *x) { delete x; });
            PostOrderWalk(node->right, [](Node *x) { delete x; });
            node->left = nullptr;
            node->right = nullptr;
        }
        void Empty(void) { Empty(this); }
        T Content() { return this->content; }
        void PrintContent() { cout << this->content << " "; }
        static void PrintTree(Node *node)
        {
            auto f = [](Node *x) { x->PrintContent(); };
            InOrderWalk(node, f);
        }
        void PrintTree(void) { PrintTree(this); }
    };

private:
    Node *root;
    int count;

public:
    BinaryTree(void) : root(nullptr), count(0) {}

    void Empty(void)
    {
        if (this->root != nullptr)
        {
            Node::Empty(this->root);
            delete this->root;
            this->root = nullptr;
            this->count = 0;
        }
    }

    ~BinaryTree(void) { Empty(); }

    //         0
    //    1          2
    //  3   4     5     6
    // 7 8 9 10 11 12 13 14
    // Given Height, the number of nodes are in [2^(Height - 1), 2^Height - 1]
    // The indices of nodes at Height are in [2^(Height - 1) - 1, 2^Height - 2]
    // Given node index, its children are 2*index+1 and 2*index+2
    void Insert(T content)
    {
        Node *newNode = new Node(content);
        if (this->root == nullptr)
        {
            this->root = newNode;
            this->root->parent = nullptr;
            this->count = 1;
        }
        else
        {
            // this->count equals to the index for the new node
            stack<int> branch;
            int index = this->count;
            while (index > 0)
            {
                if (index % 2 == 1)
                {
                    // index is an odd number, meaning it is the left child of its parent
                    // Encode it as 0
                    branch.push(0);
                }
                else
                {
                    // index is an even number, meaning it is the left child of its parent
                    // Encode it as 1
                    branch.push(1);
                }

                index = (index - 1) >> 1;
            }

            Node *current = this->root;
            while (branch.size() > 1)
            {
                if (branch.top() == 0 && current->left != nullptr)
                {
                    current = current->left;
                }
                else if (branch.top() == 1 && current->right != nullptr)
                {
                    current = current->right;
                }

                branch.pop();
            }

            if (branch.top() == 0 && current->left == nullptr)
            {
                current->left = newNode;
            }
            else if (branch.top() == 1 && current->right == nullptr)
            {
                current->right = newNode;
            }

            branch.pop();
            this->count++;
        }
    }

    void PreOrderWalk(function<void(T)> f)
    {
        if (this->root != nullptr)
        {
            auto fNode = [=](Node *x) { f(x->Content()); };
            Node::PreOrderWalk(this->root, fNode);
        }
    }

    void InOrderWalk(function<void(T)> f)
    {
        if (this->root != nullptr)
        {
            auto fNode = [=](Node *x) { f(x->Content()); };
            Node::InOrderWalk(this->root, fNode);
        }
    }

    void PostOrderWalk(function<void(T)> f)
    {
        if (this->root != nullptr)
        {
            auto fNode = [=](Node *x) { f(x->Content()); };
            Node::PostOrderWalk(this->root, fNode);
        }
    }

    void Print()
    {
        if (this->root != nullptr)
        {
            Node::PrintTree(this->root);
        }
    }
};

// Implement a complete unordered binary tree.
// Every level except the last one is fully filled.
template <class T, template <class T> class N>
class CompleteBinaryTree : public BinaryTree<T, N>
{
private:
    // Total number of nodes
    int count;

public:
    CompleteBinaryTree(void) : BinaryTree(), count(0) {}
    virtual ~CompleteBinaryTree(void)
    {
        this->count = 0;
    }

    //         0
    //    1          2
    //  3   4     5     6
    // 7 8 9 10 11 12 13 14
    // Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
    // The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
    // Given node index I, its children are 2*I+1 and 2*I+2
    static int Height(int index)
    {
        unsigned int c = (unsigned int)(index + 1);
        int h = 0;
        while (c > 0)
        {
            h++;
            c = c >> 1;
        }

        return h;
    }

    // Encode the link from a node to its left child as 0.
    // Encode the link from a node to its right child as 1.
    // The the path from the root to and node can be represented with a bit set.
    static BitSet BrachCode(int index)
    {
        int h = Height(index);
        BitSet branch(h);
        unsigned int c = (unsigned int)index;
        while (c > 0)
        {
            if (c % 2 == 1)
            {
                // index is an odd number, meaning it is the left child of its parent
                // Encode it as 0
                branch.Reset(h - 1);
            }
            else
            {
                // index is an even number, meaning it is the right child of its parent
                // Encode it as 1
                branch.Set(h - 1);
            }

            c = (c - 1) >> 1;
            h--;
        }

        return branch;
    }

    void Insert(T &content)
    {
        N<T> *node = new N<T>(content);
        if (this->root == nullptr)
        {
            this->root = node;
            this->count = 1;
        }
        else
        {
            // this->count equals to the index for the new node
            int height = Height(this->count);
            BitSet branch = BrachCode(this->count);

            N<T> *current = this->root;
            for (int h = 1; h < height; h++)
            {
                if (!branch.Test(h))
                {
                    if (current->Left() != nullptr)
                        current = (N<T> *)current->Left();
                    else
                        current->Left() = node;
                }
                else if (branch.Test(h))
                {
                    if (current->Right() != nullptr)
                        current = (N<T> *)current->Right();
                    else
                        current->Right() = node;
                }
            }

            this->count++;
        }
    }

    int Height(void)
    {
        return BinaryTree<T, N>::Height();
    }
};

//Breadth-First Search
//	Use a queue to track the frontier of vertices between the vertices
//  that have been explored and those have not been explored.
//
//	The first implementation works when visiting a vertex does not depend
//  on its predecessor. The queue here contains the vertices that have not
//  been visited. This means when enqueue an unvisited vertex, we need to
//  check if it is already in the queue.
//	void BreadthFirstSearch1(Graph g, Vertex v)
//	{
//		queue<Vertex> frontier;
//		frontier.enqueue(v);
//		while (!frontier.empty()) {
//			Vertex u = frontire.dequeue();
//			Visit(u);
//			u.Visited = true;
//			for_each (
//				u.AdjacentVertices.begin(),
//				u.AdjacentVertices.end(),
//				[&](Vertex & n)->void{
//					if (!n.Visited & !frontier.contains(n)) {
//						frontier.enqueue(n);
//					}
//				}
//			);
//		}
//	}
//
//	The second implementation works when visiting a vertex depends on
//  its predecessor. The queue here contains the vertices that have been
//  visited.
//	void BreadthFirstSearch2(Graph g, Vertex v)
//	{
//		queue<Vertex> frontier;
//		Visit(null, v);
//		v.Visited = true;
//		frontier.enqueue(v);
//		while (!frontier.empty()) {
//			Vertex u = frontire.dequeue();
//			for_each (
//				u.AdjacentVertices.begin(),
//				u.AdjacentVertices.end(),
//				[&](Vertex & n)->void {
//					if (!n.Visited) {
//						Visit(u, n);
//						n.Visited = true;
//						frontier.enqueue(n);
//					}
//				}
//			);
//		}
//	}

//Depth-First Search
//	Use a stack to track the path from the starting vertex to the
//  current vertex. The stack contains the vertices visited so far.
//
//	void DepthFisrtSearch1(Graph g, Vertex v)
//	{
//		Visit(v);
//		v.Visited = true;
//		for_each (
//			v.AdjacentVertices.begin(),
//			v.AdjacentVertices.end(),
//			[&](Vertex & n)->void {
//				if (!n.Visited) {
//					DepthFirstSearch1(n);
//				}
//			}
//		);
//	}
//
//	void DepthFisrtSearch2(Graph g, Vertex v)
//	{
//		stack<Vertex> path;
//		Visit(v);
//		v.Visited = true;
//		path.push(v);
//		while (!path.empty()) {
//			Vertex c = path.top();
//			Vertex n = c.AdjacentVertices.iterator.next();
//			if (n == null) {
//				path.pop();
//			} else if (!n.Visited) {
//				Visit(n);
//				n.Visited = true;
//				path.push(n);
//			}
//		}
//	}

template <class VertexValueType, class EdgeValueType>
class Graph
{
protected:
    class Vertex
    {
    public:
        unsigned int id;
        VertexValueType value;
        Vertex(unsigned int id, VertexValueType value) : id(id), value(value) {}
    };

    class Edge
    {
    public:
        unsigned int id;
        EdgeValueType value;
        unsigned int from;
        unsigned int to;
        Edge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value)
            : id(id), from(from), to(to), value(value)
        {
        }
    };

    map<unsigned int, Vertex *> vertices;
    map<unsigned int, Edge *> edges;
    bool directed;

public:
    // Default the graph is directed
    Graph(void) : directed(true) {}
    Graph(bool directed) : directed(directed) {}
    virtual ~Graph(void)
    {
        map<unsigned int, Edge *>::iterator eit;
        for (eit = this->edges.begin(); eit != this->edges.end(); eit++)
        {
            delete eit->second;
        }

        map<unsigned int, Vertex *>::iterator vit;
        for (vit = this->vertices.begin(); vit != this->vertices.end(); vit++)
        {
            delete vit->second;
        }
    }

    virtual void InsertVertex(unsigned int id, VertexValueType value = 1)
    {
        if (this->vertices.find(id) != this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d already exists", id));

        this->vertices[id] = new Vertex(id, value);
    }

    virtual void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
    {
        if (this->edges.find(id) != this->edges.end())
            throw invalid_argument(String::Format("Edge id %d already exists", id));

        if (this->vertices.find(from) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", from));

        if (this->vertices.find(to) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", to));

        this->edges[id] = new Edge(id, from, to, value);
    }

    // Enumerate all the edges to compute the out-degree
    virtual int OutDegree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Edge *>::iterator it;
        int i = 0;
        for (it = this->edges.begin(); it != this->edges.end(); it++)
        {
            if (it->second->from == id)
                i++;
        }

        return i;
    }

    // Enumerate all the edges to compute the in-degree
    virtual int InDegree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Edge *>::iterator it;
        int i = 0;
        for (it = this->edges.begin(); it != this->edges.end(); it++)
        {
            if (it->second->to == id)
                i++;
        }

        return i;
    }

    // Enumerate all the edges to compute the degree
    // degree == out-degree + in-degree.
    virtual int Degree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Edge *>::iterator it;
        int i = 0;
        for (it = this->edges.begin(); it != this->edges.end(); it++)
        {
            if (it->second->from == id)
                i++;
            if (it->second->to == id)
                i++;
        }

        return i;
    }

    void Transpose(Graph &transpose)
    {
        map<unsigned int, Vertex *>::iterator vit;
        Vertex *v;
        for (vit = this->vertices.begin(); vit != this->vertices.end(); vit++)
        {
            v = vit->second;
            transpose.InsertVertex(v->id, v->value);
        }

        map<unsigned int, Edge *>::iterator eit;
        Edge *e;
        for (eit = this->edges.begin(); eit != this->edges.end(); eit++)
        {
            e = eit->second;
            transpose.InsertEdge(e->id, e->to, e->from, e->value);
        }
    }

    // Enumerate all the edges and get the neighbors pointing from a vertex.
    virtual void OutNeighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Edge *>::iterator it;
        for (it = this->edges.begin(); it != this->edges.end(); it++)
        {
            Edge *e = it->second;
            if (e->from == id && e->to != id)
                neighbors.push_back(e->to);
        }
    }

    // Enumerate all the edges and get the neighbors being pointed to a vertex.
    virtual void InNeighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Edge *>::iterator it;
        for (it = this->edges.begin(); it != this->edges.end(); it++)
        {
            Edge *e = it->second;
            if (e->from != id && e->to == id)
                neighbors.push_back(e->from);
        }
    }

    // Enumerate all the edges to compute neighbors
    // neighbors == out-neighbors + in-neighbors.
    virtual void Neighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Edge *>::iterator it;
        for (it = this->edges.begin(); it != this->edges.end(); it++)
        {
            Edge *e = it->second;
            if (e->from == id && e->to != id)
                neighbors.push_back(e->to);
            if (e->from != id && e->to == id)
                neighbors.push_back(e->from);
        }
    }

    // BreadthFirstSearch can find the shortest path

    // Starting at a vertex id, breadth-first search through the graph.
    // For each vertex call the provided function.
    void BreadthFirstSearch(unsigned int id, function<void(unsigned int)> &visit)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        set<unsigned int> visited;
        vector<unsigned int> frontier;
        frontier.push_back(id);
        while (!frontier.empty())
        {
            unsigned int u = frontier.front();
            frontier.erase(frontier.begin());

            visit(u);
            visited.insert(u);

            vector<unsigned int> neighbors;
            if (this->directed)
                OutNeighbors(u, neighbors);
            else
                Neighbors(u, neighbors);
            for_each(neighbors.begin(), neighbors.end(), [&](unsigned int n) -> void {
                if (visited.find(n) == visited.end() && find(frontier.begin(), frontier.end(), n) == frontier.end())
                {
                    frontier.push_back(n);
                }
            });
        }
    }

    // Starting at a vertex id, breadth-first search through the graph.
    // For each vertex and its unvisited child, call the provided function.
    virtual void BreadthFirstSearch(unsigned int id, function<void(unsigned int, unsigned int)> &visit)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        set<unsigned int> visited;
        vector<unsigned int> frontier;

        visit(id, id);
        visited.insert(id);

        frontier.push_back(id);
        while (!frontier.empty())
        {
            unsigned int u = frontier.front();
            frontier.erase(frontier.begin());
            vector<unsigned int> neighbors;
            if (this->directed)
                OutNeighbors(u, neighbors);
            else
                Neighbors(u, neighbors);
            for_each(neighbors.begin(), neighbors.end(), [&](unsigned int n) -> void {
                if (visited.find(n) == visited.end())
                {

                    visit(u, n);
                    visited.insert(n);

                    frontier.push_back(n);
                }
            });
        }
    }

    // DepthFirstSearch cannot guarantee to find the shortest path

    // Starting at a vertex id, depth-first search through the graph.
    // For each vertex and its unvisited child, call the provided function.
    virtual void DepthFirstSearchInternal(unsigned int id, function<void(unsigned int)> &visit, set<unsigned int> &visited)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        visit(id);
        visited.insert(id);

        vector<unsigned int> neighbors;
        if (this->directed)
            OutNeighbors(id, neighbors);
        else
            Neighbors(id, neighbors);

        for_each(neighbors.begin(), neighbors.end(), [&](unsigned int n) -> void {
            if (visited.find(n) == visited.end())
            {
                DepthFirstSearchInternal(n, visit, visited);
            }
        });
    }

    virtual void DepthFirstSearch(unsigned int id, function<void(unsigned int)> &visit)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        set<unsigned int> visited;
        DepthFirstSearchInternal(id, visit, visited);
    }

    // Starting at a vertex id, depth-first search through the graph.
    // For each vertex and its unvisited child, call the provided function.
    virtual void DepthFirstSearch(unsigned int id, function<void(unsigned int, unsigned int)> &visit)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        set<unsigned int> visited;
        stack<unsigned int> path;
        map<unsigned int, vector<unsigned int>> children;
        map<unsigned int, vector<unsigned int>::iterator> next;
        function<void(unsigned int)> initChildren = [&](unsigned int n) {
            vector<unsigned int> neighbors;
            if (this->directed)
                OutNeighbors(n, neighbors);
            else
                Neighbors(n, neighbors);
            children[n] = neighbors;
            next[n] = children[n].begin();
        };

        visit(id, id);
        visited.insert(id);
        path.push(id);
        initChildren(id);

        while (!path.empty())
        {
            unsigned int top = path.top();
            vector<unsigned int>::iterator it = next[top];
            if (next[top] != children[top].end())
                next[top]++;
            if (it == children[top].end())
            {
                path.pop();
            }
            else if (visited.find(*it) == visited.end())
            {
                visit(top, *it);
                visited.insert(*it);
                path.push(*it);
                initChildren(*it);
            }
        }
    }

    virtual void Print(void) {}
};

template <class VertexValueType, class EdgeValueType>
class ListGraph : public Graph<VertexValueType, EdgeValueType>
{
private:
    class AdjacencyNode
    {
    public:
        AdjacencyNode *next;
        unsigned int edgeId;
        AdjacencyNode(unsigned int id) : edgeId(id), next(nullptr) {}
    };

    class AdjacencyHead
    {
    public:
        AdjacencyNode *head;
        unsigned int vertexId;
        AdjacencyHead(unsigned int id) : vertexId(id), head(nullptr) {}
    };

    // [TODO] Get rid of AdjacencyHead. Use AdjacencyNode only.
    map<unsigned int, AdjacencyHead *> list;

public:
    // Default the graph is directed
    ListGraph(void) : Graph() {}
    ListGraph(bool directed) : Graph(directed) {}
    ~ListGraph(void)
    {
        map<unsigned int, AdjacencyHead *>::iterator it;
        for (it = this->list.begin(); it != this->list.end(); it++)
        {
            AdjacencyNode *h = it->second->head;
            if (h != nullptr)
            {
                AdjacencyNode *n;
                while (h->next != nullptr)
                {
                    n = h;
                    h = n->next;
                    delete n;
                }

                delete h;
            }

            delete it->second;
        }
    }

    void InsertVertex(unsigned int id, VertexValueType value = 1)
    {
        Graph::InsertVertex(id, value);
        this->list[id] = new AdjacencyHead(id);
    }

    void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
    {
        Graph::InsertEdge(id, from, to, value);
        function<void(unsigned int)> link = [&](unsigned int f) {
            AdjacencyNode *n = this->list[f]->head;
            if (n == nullptr)
            {
                this->list[f]->head = new AdjacencyNode(id);
            }
            else
            {
                while (n->next != nullptr)
                {
                    n = n->next;
                }

                n->next = new AdjacencyNode(id);
            }
        };

        link(from);
        if (!this->directed && from != to)
        {
            // This will not be executed if
            // 1. It is a directed graph, or
            // 2. The edge is a circle

            // Note the neighboring vertex is edge->from
            link(to);
        }
    }

    int OutDegree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        AdjacencyNode *n = this->list[id]->head;
        int i = 0;
        while (n != nullptr)
        {
            // If the graph is undirected, then check if the edge is out or in.
            if (this->edges[n->edgeId]->from == id)
                i++;
            n = n->next;
        }

        return i;
    }

    int InDegree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        int i = 0;
        if (!this->directed)
        {
            AdjacencyNode *n = this->list[id]->head;
            while (n != nullptr)
            {
                if (this->edges[n->edgeId]->to == id)
                    i++;
                n = n->next;
            }
        }
        else
        {
            // Directed graph. Have to enumerate all the edges.
            i = Graph::InDegree(id);
        }

        return i;
    }

    int Degree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        int i = 0;
        if (!this->directed)
        {
            AdjacencyNode *n = this->list[id]->head;
            while (n != nullptr)
            {
                if (this->edges[n->edgeId]->from == id)
                    i++;
                if (this->edges[n->edgeId]->to == id)
                    i++;
                n = n->next;
            }
        }
        else
        {
            i = Graph::Degree(id);
        }

        return i;
    }

    void OutNeighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        AdjacencyNode *n = this->list[id]->head;
        while (n != nullptr)
        {
            Edge *e = this->edges[n->edgeId];
            // If the graph is undirected, then check if the edge is out or in.
            if (e->from == id && e->to != id)
                neighbors.push_back(e->to);
            n = n->next;
        }
    }

    void InNeighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        if (!this->directed)
        {
            AdjacencyNode *n = this->list[id]->head;
            while (n != nullptr)
            {
                Edge *e = this->edges[n->edgeId];
                // If the graph is undirected, then check if the edge is out or in.
                if (e->from != id && e->to == id)
                    neighbors.push_back(e->from);
                n = n->next;
            }
        }
        else
        {
            Graph::InNeighbors(id, neighbors);
        }
    }

    void Neighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        if (!this->directed)
        {
            AdjacencyNode *n = this->list[id]->head;
            while (n != nullptr)
            {
                Edge *e = this->edges[n->edgeId];
                // If the graph is undirected, then check if the edge is out or in.
                if (e->from == id && e->to != id)
                    neighbors.push_back(e->to);
                if (e->from != id && e->to == id)
                    neighbors.push_back(e->from);
                n = n->next;
            }
        }
        else
        {
            Graph::Neighbors(id, neighbors);
        }
    }

    void Print(void)
    {
        map<unsigned int, AdjacencyHead *>::iterator it;
        for (it = this->list.begin(); it != this->list.end(); it++)
        {
            unsigned int vid = it->second->vertexId;
            cout << vid;
            AdjacencyNode *n = it->second->head;
            while (n != nullptr)
            {
                unsigned int eid = n->edgeId;
                // Depending on if the graph is directed or not,
                // the neighboring vertex id can be edge->from or edge->to
                unsigned int tid = vid == this->edges[eid]->from ? this->edges[eid]->to : this->edges[eid]->from;
                cout << "->" << tid;
                n = n->next;
            }

            cout << endl;
        }
    }
};

template <class VertexValueType, class EdgeValueType>
class MatrixGraph : public Graph<VertexValueType, EdgeValueType>
{
private:
    struct Less : binary_function<pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>, bool>
    {
        bool operator()(const pair<unsigned int, unsigned int> &first, const pair<unsigned int, unsigned int> &second)
        {
            if (first.first < second.first)
                return true;
            if (first.first == second.first && first.second < second.second)
                return true;
            return false;
        }
    };

    map<pair<unsigned int, unsigned int>, unsigned int, Less> matrix;

public:
    // Default the graph is directed
    MatrixGraph(void) : Graph() {}
    MatrixGraph(bool directed) : Graph(directed) {}
    ~MatrixGraph(void) {}

    void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
    {
        Graph::InsertEdge(id, from, to, value);
        pair<unsigned int, unsigned int> key = make_pair(from, to);
        this->matrix[key] = id;
        if (!this->directed && from != to)
        {
            key = make_pair(to, from);
            this->matrix[key] = id;
        }
    }

    int OutDegree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Vertex *>::iterator to;
        pair<unsigned int, unsigned int> key;
        int i = 0;
        for (to = this->vertices.begin(); to != this->vertices.end(); to++)
        {
            key = make_pair(id, to->first);
            if (this->matrix.find(key) != this->matrix.end())
            {
                int edgeId = this->matrix[key];
                if (this->edges[edgeId]->from == id)
                    i++;
            }
        }

        return i;
    }

    int InDegree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Vertex *>::iterator from;
        pair<unsigned int, unsigned int> key;
        int i = 0;
        for (from = this->vertices.begin(); from != this->vertices.end(); from++)
        {
            key = make_pair(from->first, id);
            if (this->matrix.find(key) != this->matrix.end())
            {
                int edgeId = this->matrix[key];
                if (this->edges[edgeId]->to == id)
                    i++;
            }
        }

        return i;
    }

    int Degree(unsigned int id)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        int i = 0;
        if (!this->directed)
        {
            map<unsigned int, Vertex *>::iterator it;
            pair<unsigned int, unsigned int> key;
            for (it = this->vertices.begin(); it != this->vertices.end(); it++)
            {
                key = make_pair(id, it->first);
                if (this->matrix.find(key) != this->matrix.end())
                {
                    int edgeId = this->matrix[key];
                    if (this->edges[edgeId]->from == id)
                        i++;
                    if (this->edges[edgeId]->to == id)
                        i++;
                }
            }
        }
        else
        {
            i += OutDegree(id);
            i += InDegree(id);
        }

        return i;
    }

    void OutNeighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Vertex *>::iterator to;
        pair<unsigned int, unsigned int> key;
        for (to = this->vertices.begin(); to != this->vertices.end(); to++)
        {
            if (to->first == id)
                continue;
            key = make_pair(id, to->first);
            if (this->matrix.find(key) != this->matrix.end())
            {
                int edgeId = this->matrix[key];
                if (this->edges[edgeId]->from == id)
                    neighbors.push_back(this->edges[edgeId]->to);
            }
        }
    }

    void InNeighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        map<unsigned int, Vertex *>::iterator from;
        pair<unsigned int, unsigned int> key;
        for (from = this->vertices.begin(); from != this->vertices.end(); from++)
        {
            if (from->first == id)
                continue;
            key = make_pair(from->first, id);
            if (this->matrix.find(key) != this->matrix.end())
            {
                int edgeId = this->matrix[key];
                if (this->edges[edgeId]->to == id)
                    neighbors.push_back(this->edges[edgeId]->from);
            }
        }
    }

    void Neighbors(unsigned int id, vector<unsigned int> &neighbors)
    {
        if (this->vertices.find(id) == this->vertices.end())
            throw invalid_argument(String::Format("Vertex id %d does not exist", id));

        if (!this->directed)
        {
            map<unsigned int, Vertex *>::iterator it;
            pair<unsigned int, unsigned int> key;
            for (it = this->vertices.begin(); it != this->vertices.end(); it++)
            {
                if (it->first == id)
                    continue;
                key = make_pair(id, it->first);
                if (this->matrix.find(key) != this->matrix.end())
                {
                    int edgeId = this->matrix[key];
                    if (this->edges[edgeId]->from == id)
                        neighbors.push_back(this->edges[edgeId]->to);
                    if (this->edges[edgeId]->to == id)
                        neighbors.push_back(this->edges[edgeId]->from);
                }
            }
        }
        else
        {
            OutNeighbors(id, neighbors);
            InNeighbors(id, neighbors);
        }
    }

    void Print(void)
    {
        map<unsigned int, Vertex *>::iterator to;
        for (to = this->vertices.begin(); to != this->vertices.end(); to++)
        {
            cout << "\t" << to->first;
        }

        cout << endl;

        map<unsigned int, Vertex *>::iterator from;
        pair<unsigned int, unsigned int> key;
        for (from = this->vertices.begin(); from != this->vertices.end(); from++)
        {
            cout << from->first;
            for (to = this->vertices.begin(); to != this->vertices.end(); to++)
            {
                key = make_pair(from->first, to->first);
                cout << "\t";
                if (this->matrix.find(key) != this->matrix.end())
                {
                    cout << this->edges[this->matrix[key]]->value;
                }
            }

            cout << endl;
        }
    }
};

class GraphSearchTree
{
private:
    class Node
    {
    public:
        Node *parent;
        vector<Node *> children;
        unsigned int id;
        unsigned int distance;

        Node(unsigned int id, unsigned int d, Node *p) : id(id), distance(d), parent(p) {}
        Node(unsigned int id, unsigned int d) : id(id), distance(d), parent(nullptr) {}
        Node(unsigned int id) : id(id), distance(0), parent(nullptr) {}
        ~Node(void)
        {
            this->parent = nullptr;
            this->children.clear();
        }

        static void PostOrderWalk(Node *node, function<void(Node *)> f)
        {
            if (node == nullptr || f == nullptr)
                return;
            stack<Node *> path;
            map<Node *, vector<Node *>::iterator> next;
            path.push(node);
            next[node] = node->children.begin();
            while (!path.empty())
            {
                Node *top = path.top();
                vector<Node *>::iterator it = next[top];
                if (it == top->children.end())
                {
                    // Either top has no children, or
                    // all the children have been visited.
                    if (top->parent != nullptr)
                        next[top->parent]++;
                    f(top);
                    path.pop();
                }
                else
                {
                    path.push(*it);
                    next[*it] = (*it)->children.begin();
                }
            }
        }

        static Node *Search(Node *node, unsigned int id)
        {
            if (node == nullptr)
                return nullptr;
            if (node->id == id)
                return node;
            queue<Node *> q;
            q.push(node);
            while (!q.empty())
            {
                Node *n = q.front();
                q.pop();
                for (unsigned int i = 0; i < n->children.size(); i++)
                {
                    Node *c = n->children[i];
                    if (c->id == id)
                        return c;
                    q.push(c);
                }
            }

            return nullptr;
        }

        static stringstream &ToString(stringstream &ss, Node *node, int x, vector<int> &y)
        {
            static string link = "____";
            string c = String::Format(" %d:%d ", node->id, node->distance);
            ss << c;

            if (node->children.size() == 0)
                return ss;

            x += c.length();
            if (node->children.size() > 1)
            {
                // Record current x coordinate,
                // so it can be used to draw '|'
                y.push_back(x);
            }

            vector<Node *>::iterator it = node->children.begin();
            ss << link;
            ToString(ss, *it, x + link.length(), y);
            it++;
            while (it != node->children.end())
            {
                ss << endl;
                for (size_t i = 0; i < y.size(); i++)
                {
                    int len = i == 0 ? y[i] : y[i] - y[i - 1];
                    string blank(len - 1, ' ');
                    ss << blank << '|';
                }

                if (it + 1 == node->children.end())
                {
                    // The last child is ready to print
                    // Remove its coordinate because it is not needed any more
                    y.pop_back();
                }

                ss << link;
                ToString(ss, *it, x + link.length(), y);
                it++;
            }

            return ss;
        }

    } * root;

    unsigned int rootId;

public:
    GraphSearchTree(unsigned int id)
    {
        this->rootId = id;
        this->root = new Node(rootId);
    }

    ~GraphSearchTree(void)
    {
        Node::PostOrderWalk(this->root, [&](Node *n) { delete n; });
    }

    void Visit(unsigned int parentId, unsigned int childId)
    {
        if (childId == this->rootId)
            return;
        Node *p = Node::Search(this->root, parentId);
        if (p == nullptr)
            return;
        Node *c = new Node(childId, p->distance + 1, p);
        p->children.push_back(c);
    }

    template <class VertexValueType, class EdgeValueType>
    void BreadthFirstSearch(Graph<VertexValueType, EdgeValueType> &g)
    {
        function<void(unsigned int, unsigned int)> v = [&](unsigned int p, unsigned int c) {
            Visit(p, c);
        };

        g.BreadthFirstSearch(this->rootId, v);
    }

    template <class VertexValueType, class EdgeValueType>
    void DepthFirstSearch(Graph<VertexValueType, EdgeValueType> &g)
    {
        function<void(unsigned int, unsigned int)> v = [&](unsigned int p, unsigned int c) {
            Visit(p, c);
        };

        g.DepthFirstSearch(this->rootId, v);
    }

    void Print(void)
    {
        stringstream ss;
        vector<int> y;
        Node::ToString(ss, this->root, 0, y);
        ss << endl;
        cout << ss.str();
    }
};

namespace NodeGraph
{
class Node
{
public:
    Node(void) {}
    virtual ~Node(void) {}

    // Contain pointers to neighboring nodes
    vector<Node *> neighbors;

    // Get a cloned copy, not including neighbors
    virtual Node *Clone(void)
    {
        Node *n = new Node();
        return n;
    }

    // Clone the graph at node.
    // Return the pointer to the copy of input node.
    // Use map to return the mapping of graph nodes and their clones.
    static Node *CloneGraph(Node *node, map<Node *, Node *> &map)
    {
        if (node == nullptr)
            return nullptr;

        Node *copy = node->Clone();
        map[node] = copy;
        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *n = q.front();
            q.pop();

            for_each(n->neighbors.begin(), n->neighbors.end(), [&](Node *c) {
                if (map.find(c) == map.end())
                {
                    map[c] = c->Clone();
                    q.push(c);
                }

                map[n]->neighbors.push_back(map[c]);
            });
        }

        return copy;
    }
};
} // namespace NodeGraph
} // namespace Test

#endif