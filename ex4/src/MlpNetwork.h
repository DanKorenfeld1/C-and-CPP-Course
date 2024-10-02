//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "MlpNetwork.h"
#include "Dense.h"
#include "Matrix.h"
#include "Activation.h"

#define MLP_SIZE 4
#define NUMBER_OF_LAYERS 4
/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

class MlpNetwork
{
  private:
    Dense _layer[NUMBER_OF_LAYERS];

  /**
   * helper funciton that check if the sizes of the matrices ok and after
   * build the Dense class
   * @param weights array of matrices, every matrix for specific layer
   * @param bias array of matrices, every matrix for specific layer
   * @param w_dims the size of the weight matrix that need in the layer
   * @param b_dims the size of the bias matrix that need in the layer
   * @param func the Activation Fuction
   * @return Dense class
   */
    Dense check_and_create_layer(const Matrix& weights, const Matrix& bias,
                                 const matrix_dims& w_dims,
                                 const matrix_dims& b_dims,
                                 ActivationFuction func);
  //todo: why need static??

 public:
  /**
   * Constructor to MlpNetwork class
   * @param weights array of matrices, every matrix for specific layer
   * @param biases array of matrices, every matrix for specific layer
   */
  MlpNetwork(const Matrix weights[NUMBER_OF_LAYERS],const Matrix
  biases[NUMBER_OF_LAYERS]);

  /**
   * funciton that applies the entire network on input. return a digit
   * atruct type.
   * @param img
   * @return
   */
  digit operator() (const Matrix& img)const;
};

#endif // MLPNETWORK_H
