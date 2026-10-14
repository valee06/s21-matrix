#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_calc_complements(s21_matrix* A, s21_matrix* result) {
  if (s21_bad_matrix(A) || result == NULL) {
    return INCORRECT_MATRIX_ERROR;
  } else if (s21_square_matrix(A) != OK ||
             s21_isnan_or_isinf_el_in_matrix(A) != OK) {
    return CALCULATION_ERROR;
  }
  int finish;
  if ((finish = s21_create_matrix(A->rows, A->columns, result)) != OK) {
    return finish;
  }
  if (A->rows == 1) {
    result->matrix[0][0] = 1;
  } else {
    finish = s21_get_complements(A, result);
  }
  return finish;
}