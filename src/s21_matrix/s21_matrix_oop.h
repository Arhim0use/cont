#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <math.h>

#include <iostream>


class S21Matrix {
 public:
  S21Matrix();

  S21Matrix(int rows, int cols);

  S21Matrix(const S21Matrix& other);

  S21Matrix(S21Matrix&& other);

  ~S21Matrix();

  S21Matrix operator=(const S21Matrix& other) noexcept;

  S21Matrix& operator=(S21Matrix&& other) noexcept;

  bool operator==(const S21Matrix& other) const noexcept;

  bool operator!=(const S21Matrix& other) const noexcept;

  bool EqMatrix(const S21Matrix& other) const noexcept;

 private:
  int rows_, cols_;
  double** matrix_;

  void AllocMatrix();

  void CpyMatrix(const S21Matrix& other);

  // void print_matr();
};


#endif  // __S21MATRIX_H__