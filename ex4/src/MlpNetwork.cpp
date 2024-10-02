
#include "MlpNetwork.h"

// See full documentation in header file
MlpNetwork::MlpNetwork (const Matrix weights[NUMBER_OF_LAYERS],
                        const Matrix biases[NUMBER_OF_LAYERS]) :
    _layer{check_and_create_layer (weights[0], biases[0], weights_dims[0],
                                   bias_dims[0], activation::relu),
           check_and_create_layer (weights[1], biases[1], weights_dims[1],
                                   bias_dims[1], activation::relu),
           check_and_create_layer (weights[2], biases[2], weights_dims[2],
                                   bias_dims[2], activation::relu),
           check_and_create_layer (weights[3], biases[3], weights_dims[3],
                                   bias_dims[3], activation::softmax)}
{
}

// See full documentation in header file
digit MlpNetwork::operator() (const Matrix &img) const
{
    Matrix calculate_matrix = img;
    calculate_matrix.vectorize ();
    for (int i = 0; i < NUMBER_OF_LAYERS; i++)
    {
        calculate_matrix = _layer[i] (calculate_matrix);
    }
    int max_argument = calculate_matrix.argmax ();
    digit digit_1 = {(unsigned int) max_argument,
                     calculate_matrix[max_argument]};
    return digit_1;
}

Dense MlpNetwork::check_and_create_layer (const Matrix &weights, const
Matrix &bias, const matrix_dims &w_dims, const matrix_dims &b_dims,
                                          ActivationFuction func)
{
    if ((weights.get_rows () != w_dims.rows) ||
        (weights.get_cols () != w_dims.cols) ||
        (bias.get_rows () != b_dims.rows) ||
        (bias.get_cols () != b_dims.cols))
    {
        throw std::length_error (ERROR_LEGNTH_INVALID_MESSAGE);
    }
    return Dense (weights, bias, func);
}
