#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_determinant(s21_matrix* A, double* result) {
  if (s21_bad_matrix(A) || result == NULL) {
    return INCORRECT_MATRIX_ERROR;
  } else if (s21_square_matrix(A) != OK ||
             s21_isnan_or_isinf_el_in_matrix(A) != OK) {
    return CALCULATION_ERROR;
  }
  int finish = OK;
  int sign = 1;
  *result = 0.0;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    for (int col = 0; col < A->columns; col++) {
      s21_matrix minor;
      if ((finish = s21_get_minor(A, 0, col, &minor)) == OK) {
        double minor_det;
        s21_determinant(&minor, &minor_det);
        *result += minor_det * A->matrix[0][col] * sign;
        sign *= -1;
        s21_remove_matrix(&minor);
      }
    }
  }
  if (fabs(*result) <= 1e-7) {
    *result = 0.0;
  }
  return finish;
}