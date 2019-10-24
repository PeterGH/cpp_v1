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

} // namespace Test

#endif