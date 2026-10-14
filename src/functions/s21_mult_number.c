#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_mult_number(s21_matrix* A, double number, s21_matrix* result) {
  if (s21_bad_matrix(A)) {
    return INCORRECT_MATRIX_ERROR;
  }
  int res_matrix = s21_isnan_or_isinf_el_in_matrix(A);
  if (res_matrix != 0 || isnan(number) || isinf(number)) {
    return CALCULATION_ERROR;
  }
  int finish;
  if ((finish = s21_create_matrix(A->rows, A->columns, result)) == 0) {
    for (int row = 0; row < A->rows; row++) {
      for (int col = 0; col < A->columns; col++) {
        result->matrix[row][col] = number * A->matrix[row][col];
      }
    }
  }
  return finish;
}