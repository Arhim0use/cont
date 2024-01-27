#include "s21_matrix_oop.h"


S21Matrix::S21Matrix() : rows_(0), cols_(0) { matrix_ = nullptr; }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ == 0 && cols_ == 0){
    matrix_ = nullptr;
  } else if (rows_ > 0 && cols_ > 0) {
    this->AllocMatrix();
  } else {
    throw std::invalid_argument("err: Invalid argument.");
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->AllocMatrix();
  CpyMatrix(other);
}

/// @brief Перенос матрицы (std::move())
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  if (this != &other) {
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;

    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
  }
}

S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      if (this->matrix_[i] != nullptr) {
        delete[] this->matrix_[i];
        this->matrix_[i] = nullptr;
      }
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

// --------------------OPERATOR_OWERLOAD-------------------- //

S21Matrix S21Matrix::operator=(const S21Matrix& other) noexcept {
  if (this != &other) {
    this->~S21Matrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    AllocMatrix();
    CpyMatrix(other);
  }

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
   if (this != &other){
      matrix_ = other.matrix_;
      rows_ = other.rows_;
      cols_ = other.cols_;

      other.matrix_ = nullptr;
      other.rows_ = 0;
      other.cols_ = 0;
   }

   return *this;
}
bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix& other) const noexcept {
  bool result = true;
  if (this->EqMatrix(other)) result = false;
  return result;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;

  bool result = true;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) >= 1e-7)
        result = false;
    }
  }

  return result;
}

// --------------------COMMON_FUNCTION-------------------- //

void S21Matrix::AllocMatrix() {
  int i = 0;
  try {
    matrix_ = new double*[rows_]();
    for (; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }

  } catch (const std::bad_alloc& e) {
    if (matrix_) {
      for (int j = 0; j < i; j++) {
        if (this->matrix_[j] != nullptr) {
          delete[] this->matrix_[j];
          this->matrix_[j] = nullptr;
        }
      }
      delete[] this->matrix_;
      this->matrix_ = nullptr;
      rows_ = 0;
      cols_ = 0;
    }
  }
}

void S21Matrix::CpyMatrix(const S21Matrix& other) {
  if (this->matrix_ != nullptr && other.matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}