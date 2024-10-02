
#include "Dense.h"

Matrix Dense::operator() (const Matrix &matrix) const
{
    return _func ((_weights * matrix) + _bias);
}
Dense::Dense (const Matrix &weights, const Matrix &bias,
              ActivationFuction func)
{
    if (bias.get_cols () != VECTOR_COL_SIZE)
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }
    if (bias.get_rows () != weights.get_rows ())
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }
    _weights = weights;
    _bias = bias;
    _func = func;
}
