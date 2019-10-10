#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <functional>
#include <stdexcept>
#include <string.h>
#include "String.h"

using namespace std;

namespace Test
{

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

// http://leetcode.com/2011/02/coins-in-line.html
// Two players take turn to select a coin from one end of a line of coins.
// Compute the maximum value of coins the first palyer can get.
namespace CoinSelect
{
// Given the value matrix, return the indices the first player wants to choose
static void GetIndices(Matrix<int> &v, int length, vector<int> &indices)
{
    int i = 0;
    int j = length - 1;
    while (i + 2 <= j)
    {
        if (v(i + 1, j) <= v(i, j - 1))
        {
            // A select input[i] and leave B input[i+1..j]
            indices.push_back(i);
            if (v(i + 2, j) <= v(i + 1, j - 1))
            {
                // B select input[i+1] and leave A input[i+2..j]
                i = i + 2;
            }
            else
            {
                // B select input[j] and leave A input[i+1..j-1]
                i++;
                j--;
            }
        }
        else
        {
            // A select input[j] and leave B input[i..j-1]
            indices.push_back(j);
            if (v(i + 1, j - 1) <= v(i, j - 2))
            {
                // B select input[i] and leave A input[i+1..j-1]
                i++;
                j--;
            }
            else
            {
                // B select input[j-1] and leave A input[i..j-2]
                j = j - 2;
            }
        };
    }

    if (i + 1 == j)
    {
        if (v(i, i) > v(j, j))
        {
            indices.push_back(i);
        }
        else
        {
            indices.push_back(j);
        }
    }
    else if (i == j)
    {
        indices.push_back(i);
    }
}

// Let V[i,j] be the maximum value from input[i..j]
// Let S[i,j] be the sum of input[i..j]
// V[i,j] = S[i,j] - min { V[i+1,j], V[i,j-1] }
static int MaxSelection(const int *input, int length, vector<int> &indices)
{
    Matrix<int> v(length, length);
    Matrix<int> s(length, length);

    // S[i,i] = input[i]
    // V[i,i] = input[i]
    for (int i = 0; i < length; i++)
    {
        s(i, i) = input[i];
        v(i, i) = input[i];
    }

    // S[i,j] = S[i,j-1] + input[j]
    // V[i,j] = S[i,j] - min { V[i+1,j], V[i,j-1] }
    for (int l = 1; l < length; l++)
    {
        for (int i = 0; i < length - l; i++)
        {
            s(i, i + l) = s(i, i + l - 1) + input[i + l];
            v(i, i + l) = s(i, i + l) - min(v(i + 1, i + l), v(i, i + l - 1));
        }
    }

    GetIndices(v, length, indices);
    return v(0, length - 1);
}

// Let V[i,j] be the maximum value from input[i..j]
// V[i,j] = max { input[i] + min { V[i+2,j], V[i+1,j-1] },
//                input[j] + min { V[i+1,j-1], V[i,j-2] } }
static int MaxSelection2(const int *input, int length, vector<int> &indices)
{
    Matrix<int> v(length, length);

    // V[i,i] = input[i]
    for (int i = 0; i < length; i++)
    {
        v(i, i) = input[i];
    }

    // V[i,i+1] = max { V[i,i], V[i+1,i+1] }
    for (int i = 0; i < length - 1; i++)
    {
        v(i, i + 1) = max(v(i, i), v(i + 1, i + 1));
    }

    // V[i,j] = max { input[i] + min { V[i+2,j], V[i+1,j-1] },
    //                input[j] + min { V[i+1,j-1], V[i,j-2] } }
    for (int l = 2; l < length; l++)
    {
        for (int i = 0; i < length - l; i++)
        {
            v(i, i + l) = max(
                input[i] + min(v(i + 2, i + l), v(i + 1, i + l - 1)),
                input[i + l] + min(v(i + 1, i + l - 1), v(i, i + l - 2)));
        }
    }

    GetIndices(v, length, indices);
    return v(0, length - 1);
}
} // namespace CoinSelect

} // namespace Test

#endif