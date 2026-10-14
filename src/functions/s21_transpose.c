#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_transpose(s21_matrix* A, s21_matrix* result) {
  if (s21_bad_matrix(A)) {
    return INCORRECT_MATRIX_ERROR;
  }
  int finish;
  if ((finish = s21_create_matrix(A->columns, A->rows, result)) == 0) {
    for (int row = 0; row < A->columns; row++) {
      for (int col = 0; col < A->rows; col++) {
        result->matrix[row][col] = A->matrix[col][row];
      }
    }
  }
  return finish;
}