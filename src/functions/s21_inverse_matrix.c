#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_inverse_matrix(s21_matrix* A, s21_matrix* result) {
  if (result == NULL) {
    return INCORRECT_MATRIX_ERROR;
  }
  int finish;
  double det;
  if ((finish = s21_determinant(A, &det)) == OK) {
    if (det != 0.0) {
      finish = s21_inversion(A, det, result);
    } else {
      finish = CALCULATION_ERROR;
    }
  }
  return finish;
}