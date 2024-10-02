
#include "Activation.h"

using std::exp;

// See full documentation in header file
Matrix activation::relu (const Matrix &matrix)
{
  Matrix new_matrix = Matrix (matrix.get_rows (), matrix.get_cols ());
  int size_of_matrix = matrix.get_rows () * matrix.get_cols ();
  for (int i = 0; i < size_of_matrix; i++)
  {
    new_matrix[i] = (matrix[i] > 0) ? matrix[i] : 0;
  }
  return new_matrix;
}

// See full documentation in header file
Matrix activation::softmax (const Matrix &matrix)
{
  float sum = 0;
  Matrix matrix_d = Matrix (matrix.get_rows (), matrix.get_cols ());
  int size_of_matrix = matrix.get_rows () * matrix.get_cols ();
  for (int i = 0; i < size_of_matrix; i++)
  {
    sum += exp(matrix[i]);
  }
  for (int i = 0; i < size_of_matrix; i++)
  {
    matrix_d[i] = exp(matrix[i])/sum;
  }
  return matrix_d;
}




