
#include "Matrix.h"



#define ONE_COL_IS_VECTORIZE 1
using std::ifstream;

// See full documentation in header file
Matrix::Matrix (int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }
    _rows = rows;
    _cols = cols;
    _matrix = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; i++)
    {
        _matrix[i] = ZERO;
    }
}

// See full documentation in header file
Matrix::Matrix (const Matrix &m)
{
    _rows = m._rows;
    _cols = m._cols;
    _matrix = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; i++)
    {
        _matrix[i] = m._matrix[i];
    }
}

// See full documentation in header file
Matrix &Matrix::transpose ()
{
    if (_cols != ONE_COL_IS_VECTORIZE)
    {
        Matrix temp (_cols, _rows);
        for (int i = 0; i < _rows; i++)
        {
            for (int j = 0; j < _cols; j++)
            {
//        temp(j,i)=(*this)(i,j);
                ARRAY_2D_ACCESS(temp, temp._cols, j, i) = ARRAY_2D_ACCESS(_matrix,
                                                                          _cols,
                                                                          i, j);
            }
        }
        *this = temp;
    }
    else
    {
        int tempp = _rows;
        _rows = _cols;
        _cols = tempp;
    }
    return *this;

}

// See full documentation in header file
Matrix &Matrix::vectorize ()
{
    float *new_matrix = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; i++)
    {
        new_matrix[i] = _matrix[i];
    }
    delete[] _matrix;
    _matrix = new_matrix;
    _rows = _cols * _rows;
    _cols = ONE_COL_IS_VECTORIZE;
    return *this;
}

// See full documentation in header file
void Matrix::plain_print () const
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            cout << ARRAY_2D_ACCESS(_matrix, _cols, i, j) << " ";
        }
        cout << endl;
    }
}

// See full documentation in header file
Matrix Matrix::dot (const Matrix &matrix) const
{
    if (matrix._rows != this->_rows || matrix._cols != this->_cols)
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }

    Matrix result = Matrix (*this);
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            ARRAY_2D_ACCESS(result._matrix, _rows, i, j) = ARRAY_2D_ACCESS
                                                           (_matrix, _rows, i, j)
                                                           * ARRAY_2D_ACCESS(matrix._matrix, _rows, i, j);
        }
    }
    return result;
}

// See full documentation in header file
float Matrix::norm () const
{
    float number_norm = 0;
    for (int i = 0; i < _rows * _cols; i++)
    {
        number_norm += _matrix[i] * _matrix[i];
    }
    return (float) sqrt (number_norm);
}

// See full documentation in header file
int Matrix::argmax () const
{
    float max_value = _matrix[0];
    int max_index = 0;
    for (int i = 0; i < _rows * _cols; i++)
    {
        if (_matrix[i] > max_value)
        {
            max_value = _matrix[i];
            max_index = i;
        }
    }
    return max_index;
}

// See full documentation in header file
Matrix Matrix::operator+ (const Matrix &rhs) const
{
    if (rhs._rows != _rows || rhs._cols != _cols)
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }
    Matrix result = Matrix (*this);
    for (int i = 0; i < _rows * _cols; i++)
    {
        result._matrix[i] += rhs._matrix[i];
    }
    return result;
}

// See full documentation in header file
Matrix &Matrix::operator= (const Matrix &rhs)
{
    if (this != &rhs)
    {
        _rows = rhs._rows;
        _cols = rhs._cols;
        delete[] _matrix;
        // the copy (end of the function)
        _matrix = new float[rhs._rows * rhs._cols];
        for (int i = 0; i < rhs._rows * rhs._cols; i++)
        {
            _matrix[i] = rhs._matrix[i];
        }
    }
    return *this;
}

// See full documentation in header file
Matrix Matrix::operator* (const Matrix &rhs) const
{
    if (this->_cols != rhs._rows)
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }
    Matrix result = Matrix (this->_rows, rhs._cols);
    for (int i = 0; i < result._rows; i++)
    {
        for (int j = 0; j < result._cols; j++)
        {
            float cell = 0;
            for (int k = 0; k < this->_cols; k++)
            {
                cell += ARRAY_2D_ACCESS(_matrix, this->_cols, i, k) *
                        ARRAY_2D_ACCESS(rhs._matrix, rhs._cols, k, j);
            }
            ARRAY_2D_ACCESS(result._matrix, result._cols, i, j) = cell;
        }
    }
    return result;
}

// See full documentation in header file
Matrix Matrix::operator* (const float c) const
{
    Matrix temp (*this);
    for (int i = 0; i < _rows * _cols; i++)
    {
        temp._matrix[i] *= c;
    }
    return temp;
}

// See full documentation in header file
Matrix operator* (const float c, const Matrix &mat)
{
    Matrix temp (mat);
    for (int i = 0; i < temp.get_rows () * temp.get_cols (); i++)
    {
        temp._matrix[i] *= c;
    }
    return temp;
}

// See full documentation in header file
float Matrix::operator() (int i, int j) const
{
    if (i >= _rows || _rows < 0 || _cols < 0 || j >= _cols)
    {
        throw std::out_of_range (ERROR_OUT_OF_RANGE_MESSAGE);
    }
    return ARRAY_2D_ACCESS(_matrix, _cols, i, j);
}

// See full documentation in header file
float &Matrix::operator() (int i, int j)
{
    if (i >= _rows || _rows < 0 || _cols < 0 || j >= _cols)
    {
        throw std::out_of_range (ERROR_OUT_OF_RANGE_MESSAGE);
    }
    return ARRAY_2D_ACCESS(_matrix, _cols, i, j);
}

// See full documentation in header file
const float &Matrix::operator[] (int k) const
{
    if (k >= _cols * _rows || k < 0)
    {
        throw std::out_of_range (ERROR_OUT_OF_RANGE_MESSAGE);
    }
    return _matrix[k];
}

// See full documentation in header file
float &Matrix::operator[] (int k)
{
    if (k >= _cols * _rows || k < 0)
    {
        throw std::out_of_range (ERROR_OUT_OF_RANGE_MESSAGE);
    }
    return _matrix[k];
}

// See full documentation in header file
std::ostream &operator<< (std::ostream &os, const Matrix &m)
{
    for (int i = 0; i < m._rows; i++)
    {
        for (int j = 0; j < m._cols; j++)
        {
            if (m (i, j) > LOWER_LIM_PROBABILITY)
            {
                os << "**";
            }
            else
            {
                os << "  ";
            }
        }
        os << endl;
    }
    return os;
}

// See full documentation in header file
float Matrix::sum () const
{
    float sum = 0;
    for (int i = 0; i < _rows * _cols; i++)
    {
        sum += _matrix[i];
    }
    return sum;
}

// See full documentation in header file
Matrix &Matrix::operator+= (const Matrix &m)
{
    if (m._rows != this->_rows || m._cols != this->_cols)
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }
    for (int i = 0; i < _rows * _cols; i++)
    {
        _matrix[i] += m._matrix[i];
    }
    return *this;
}

// See full documentation in header file
std::istream &operator>> (std::istream &is, Matrix &matrix)
{
    if (!is.good ())
    {
        throw std::runtime_error (ERRPR_RUNTIME_MESSAGE);
    }
    long len_from_start = is.gcount ();
    is.seekg (0, std::istream::end);
    long length = is.tellg () - len_from_start;
    is.seekg (len_from_start, std::istream::beg);
    int size = matrix.get_cols () * matrix.get_rows ();
    if ((long unsigned int) length < size * sizeof (float))
    {
        throw std::runtime_error (ERRPR_RUNTIME_MESSAGE);
    }
    if (!is.read ((char *) matrix._matrix, sizeof (float) * size))
    {
        throw std::runtime_error (ERRPR_RUNTIME_MESSAGE);
    }
    if (is.gcount () != (long int) size * sizeof (float))
    {
        throw std::runtime_error (ERRPR_RUNTIME_MESSAGE);
    }
    return is;
}














