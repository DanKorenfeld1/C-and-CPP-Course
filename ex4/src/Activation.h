

#ifndef _ACTIVATION_H_
#define _ACTIVATION_H_


#include "Matrix.h"
#include <cmath>

namespace activation
{
    /**
     * function that go through each cell in the matrix and check: if the value
     * is positive, we will leave the comment; if the value is negative,
     * we will return the number 0. The function will return the new matrix
     * @param matrix the matrix that we check
     * @return new matrix after checking all the cells
     */
    Matrix relu(const Matrix& matrix);


    /**
     * function that accepts a vector and converts it to a distribution vector
     * @param matrix the vector
     * @returndistribution vector
     */
    Matrix softmax(const Matrix& matrix);
}

#endif //_ACTIVATION_H_
