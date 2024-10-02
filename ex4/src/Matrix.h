// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cmath>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;

#define ARRAY_2D_ACCESS(arr, numCols, i, j) arr[(i) * (numCols) + (j)]

#define ZERO 0
#define FIRST 1
#define ERROR_OUT_OF_RANGE_MESSAGE "the index out of the range"
#define ERROR_LEGNTH_INVALID_MESSAGE "the legth of the element is invalid"
#define LOWER_LIM_PROBABILITY 0.1
#define ERRPR_RUNTIME_MESSAGE "error: problem with the input or the file"
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

class Matrix
{
 private:
  int _rows,_cols;
  float *_matrix;


 public:

  /**
   * constructor to matrix class
   * @param rows the number of rows
   * @param cols the number of columns
   */
  Matrix (int rows, int cols);

  /**
   * default constructor
   */
  Matrix () : _rows (FIRST), _cols (FIRST)
  {
    _matrix = new float[FIRST];
    _matrix[ZERO] = 0;
  }

  /**
   * copy constructor to matrix class
   * @param m matrix to copy
   */
  Matrix (const Matrix &m);

  /**
   * destructor to matrix class
   */
  ~Matrix ()
  {
    delete[] _matrix;
  }

  /**
   * funciton that get the number of rows
   * @return the number of rows
   */
  int get_rows () const
  { return _rows; }

  /**
   * funciton that get the number of columns
   * @return the number of columns
   */
  int get_cols () const
  { return _cols; }

  /**
   * funciton that transposes the matrix
   * @return the transposed matrix
   */
  Matrix &transpose ();

  /**
   * function that transposes the matrix into a column vector
   * @return the transposed column vector
   */
  Matrix &vectorize ();

  /**
   * function that print the matrix elements
   */
  void plain_print () const;

  /**
   * function that multiplication of two matrices with (Hadamard product)
   * @param matrix the second matrix (the first matrix is the "this" matrix)
   * @return the result of the multiplication
   */
  Matrix dot (const Matrix &matrix) const;

  /**
   * function that calculate the Frobenius norm of the given matrix
   * @return the Frobenius norm of the given matrix
   */
  float norm()const;

  /**
   * function that returns new matrix that is the reduced row echelon form of
   * the given matrix
   * @return matrix after reducing row echelon form
   */

  /**
   * function that return the index of the max argument of the given matrix
   * @return the index of the max argument of the given matrix
   */
  int argmax()const ;

  /**
   * function that return the sum of all the elements in the matrix
   * @return the sum
   */
  float sum() const;


  /**
   * function that sum 2 matrix
   * @param lhs the left hand side matrix
   * @param rhs the right hand side matrix
   * @return matrix that is the sum of the two matrices
   */
  Matrix operator+(const Matrix &rhs)const;

  /**
   * assignment operator to matrix class
   * @param rhs the right hand side matrix
   * @return the matrix rhs
   */
  Matrix& operator=(const Matrix &rhs);

  /**
   * function that multiplication of two matrices
   * @param rhs the second matrix (the first matrix is the "this" matrix)
   * @return the result of the multiplication
   */
  Matrix operator *(const Matrix &rhs) const;

  /**
   * function that multiply in scalar (on the right)
   * @param c the scalar
   * @return matrix after the multiplication
   */
  Matrix operator *(const float c)const;

  /**
   * function that multiply in scalar (on the left)
   * @param c the scalar
   * @return matrix after the multiplication
   */
  friend Matrix operator *(const float c, const Matrix& mat);

  /**
   * function that get i,j index in matrix and return the element cell in (i,j)
   * @param i row index
   * @param j column index
   * @return float the element cell
   */
  float operator() (int i, int j) const;


  /**
   * function that get i,j index in matrix and return the element cell in (i,j)
   * @param i row index
   * @param j column index
   * @return float the element cell
   */
  float& operator() (int i, int j);

  /**
   * function that return the value of the cells k'th in the matrix
   * @param k the index of the cell
   * @return float (the value of the cell
   */
  const float& operator[] (int k) const;


  /**
   * function that return the value of the cells k'th in the matrix
   * @param k the index of the cell
   * @return float (the value of the cell
   */
  float& operator[](int k);


  /**
   * operator += add matrix m to this
   * @param m the second matrix
   * @return updated matrix
   */
  Matrix& operator+=(const Matrix& m);

  /**
   * function that print to output stram
   * @param os the outputstream
   * @param m matrix
   * @return the output steam
   */
  friend std::ostream& operator<< (std::ostream &os,const Matrix& m);

  /**
   * function that input to matrix
   * @param is the inputsteam
   * @param m matrix
   * @return istream&
   */
  friend std::istream& operator>> (std::istream& is, Matrix& m);
};

#endif //MATRIX_H