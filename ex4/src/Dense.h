
#ifndef _DENSE_H_
#define _DENSE_H_

#include "Activation.h"
#include "Matrix.h"

#define VECTOR_COL_SIZE 1
typedef Matrix (*ActivationFuction) (const Matrix &);

class Dense
{
 private:
  Matrix _weights, _bias;
  ActivationFuction _func;
 public:
  /**
   * constructor function
   * @param weights A matrix that represents the weights of this layer.
   * @param bias A matrix that represents the bias of this layer.
   * @param func the Activation Fuction
   */
  Dense (const Matrix &weights, const Matrix &bias, ActivationFuction
  func);

  /**
   * function that get the matrix of the weights of this layer.
   * @return the matrix of the weights of this layer.
   */
  Matrix get_weights () const
  { return _weights; }

  /**
   * function that get the matrix of the bias of this layer.
   * @return the matrix of the bias of this layer.
   */
  Matrix get_bias () const
  { return _bias; }

  /**
   * function that get the Activation func of the layer.
   * @return the Activation func of the layer.
   */
  ActivationFuction get_activation () const
  { return _func; }

  /**
   * function that applies the layer on the input and returns an output
   * matrix.
   * @param matrix the input matrix
   * @return new matrix after the layer.
   */
  Matrix operator() (const Matrix &matrix) const;

};

#endif //_DENSE_H_
