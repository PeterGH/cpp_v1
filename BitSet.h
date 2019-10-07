#ifndef _BITSET_H_
#define _BITSET_H_

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string.h>
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
} // namespace Test

#endif