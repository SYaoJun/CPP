#pragma once

#include <memory>

namespace  startup{


/*
 * The base class defining a Matrix
 */
template <typename T>
class Matrix {
 protected:
  // r*c
  Matrix(int r, int c) : rows{r}, cols{c}, linear{new T[r * c]} {}

  // number of rows in the matrix
  int rows;
  // number of columns in the matrix
  int cols;
  // Flattened array containing the elements of the matrix
  T *linear;

 public:
  // Return the # of rows in the matrix
  virtual int GetRows() = 0;

  // Return the # of columns in the matrix
  virtual int GetColumns() = 0;

  // Return the (i,j)th  matrix element
  virtual T GetElem(int i, int j) = 0;

  // Sets the (i,j)th  matrix element to val
  virtual void SetElem(int i, int j, T val) = 0;

  // Sets the matrix elements based on the array arr
  virtual void MatImport(T *arr) = 0;

  virtual ~Matrix() { delete[] linear; }
};

template <typename T>
class RowMatrix : public Matrix<T> {
 public:
  RowMatrix(int r, int c) : Matrix<T>(r, c) {
    data_ = new T *[r];
    for (auto i = 0; i < r; i++) {
      data_[i] = &this->linear[i * c];
    }
  }

  int GetRows() override { return this->rows; }

  int GetColumns() override { return this->cols; }

  T GetElem(int i, int j) override { return data_[i][j]; }

  void SetElem(int i, int j, T val) override { data_[i][j] = val; }

  void MatImport(T *arr) override {
    for (auto i = 0; i < this->rows; i++) {
      data_[i] = &arr[i * this->cols];
    }
  }

  // TODO(P0): Add implementation
  ~RowMatrix() override { delete[] data_; }

 private:
  T **data_;
};

template <typename T>
class RowMatrixOperations {
 public:
  // Compute (mat1 + mat2) and return the result.
  // Return nullptr if dimensions mismatch for input matrices.
  static std::unique_ptr<RowMatrix<T>> AddMatrices(std::unique_ptr<RowMatrix<T>> mat1,
                                                   std::unique_ptr<RowMatrix<T>> mat2) {
    if (!mat1 || !mat2 || mat1->GetRows() != mat2->GetRows() || mat1->GetColumns() != mat2->GetColumns()) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }

    std::unique_ptr<RowMatrix<T>> res_ptr{new RowMatrix<T>(mat1->GetRows(), mat1->GetColumns())};
    for (auto i = 0; i < res_ptr->GetRows(); i++) {
      for (auto j = 0; j < res_ptr->GetColumns(); j++) {
        res_ptr->SetElem(i, j, mat1->GetElem(i, j) + mat2->GetElem(i, j));
      }
    }
    return res_ptr;
  }

  // Compute matrix multiplication (mat1 * mat2) and return the result.
  // Return nullptr if dimensions mismatch for input matrices.
  static std::unique_ptr<RowMatrix<T>> MultiplyMatrices(std::unique_ptr<RowMatrix<T>> mat1,
                                                        std::unique_ptr<RowMatrix<T>> mat2) {
    if (!mat1 || !mat2 || mat1->GetColumns() != mat2->GetRows()) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }

    std::unique_ptr<RowMatrix<T>> res_ptr{new RowMatrix<T>(mat1->GetRows(), mat2->GetColumns())};
    for (auto i = 0; i < res_ptr->GetRows(); i++) {
      for (auto j = 0; j < res_ptr->GetColumns(); j++) {
        T sum{};
        for (auto k = 0; k < mat1->GetColumns(); k++) {
          sum += (mat1->GetElem(i, k) * mat2->GetElem(k, j));
        }
        res_ptr->SetElem(i, j, sum);
      }
    }
    return res_ptr;
  }

  // Simplified GEMM (general matrix multiply) operation
  // Compute (matA * matB + matC). Return nullptr if dimensions mismatch for input matrices
  static std::unique_ptr<RowMatrix<T>> GemmMatrices(std::unique_ptr<RowMatrix<T>> matA,
                                                    std::unique_ptr<RowMatrix<T>> matB,
                                                    std::unique_ptr<RowMatrix<T>> matC) {
    return AddMatrices(MultiplyMatrices(move(matA), move(matB)), move(matC));
  }
};
}  // namespace startup