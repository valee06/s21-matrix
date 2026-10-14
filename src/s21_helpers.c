#include "s21_helpers.h"

#include "s21_matrix.h"

void s21_comparison(s21_matrix* A, s21_matrix* B, int* finish) {
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      if (fabs(A->matrix[row][col] - B->matrix[row][col]) > 1e-7) {
        *finish = FAILURE;
        row = A->rows;
        col = A->columns;
      }
    }
  }
}

void s21_free_matrix(s21_matrix* A) {
  for (int ptr = 0; ptr < A->rows; ptr++) {
    if (A->matrix[ptr] != NULL) {
      free(A->matrix[ptr]);
    }
  }
  free(A->matrix);
  A->matrix = NULL;
}

int s21_both_good_matrix(s21_matrix* A, s21_matrix* B) {
  int res = INCORRECT_MATRIX_ERROR;
  if (!s21_bad_matrixes(A, B)) {
    if ((A->rows == B->rows) && (A->columns == B->columns))
      res = OK;
    else
      res = CALCULATION_ERROR;
  }
  return res;
}

int s21_sum_sub(s21_matrix* A, s21_matrix* B, s21_matrix* result, int sign) {
  int res = s21_both_good_matrix(A, B);
  if (res != OK) {
    return res;
  }
  int res_matrix_1 = (s21_isnan_or_isinf_el_in_matrix(A));
  int res_matrix_2 = (s21_isnan_or_isinf_el_in_matrix(B));
  if (res_matrix_1 != 0 || res_matrix_2 != 0) {
    return CALCULATION_ERROR;
  }
  if ((res = s21_create_matrix(A->rows, A->columns, result)) == 0) {
    for (int row = 0; row < A->rows; row++) {
      for (int col = 0; col < A->columns; col++) {
        result->matrix[row][col] =
            A->matrix[row][col] + sign * B->matrix[row][col];
      }
    }
  }
  return res;
}

int s21_isnan_or_isinf_el_in_matrix(s21_matrix* A) {
  int res = OK;
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      if (isnan(A->matrix[row][col]) || isinf(A->matrix[row][col])) {
        res = CALCULATION_ERROR;
      }
    }
  }
  return res;
}

int s21_good_for_mult(s21_matrix* A, s21_matrix* B) {
  int res = INCORRECT_MATRIX_ERROR;
  if (!s21_bad_matrixes(A, B)) {
    if ((A->columns == B->rows) && !(s21_isnan_or_isinf_el_in_matrix(A) ||
                                     s21_isnan_or_isinf_el_in_matrix(B))) {
      res = OK;
    } else {
      res = CALCULATION_ERROR;
    }
  }
  return res;
}

double s21_mult_el_matrix(s21_matrix* A, s21_matrix* B, int row, int col) {
  double res = 0;
  for (int el = 0; el < A->columns; el++) {
    res += A->matrix[row][el] * B->matrix[el][col];
  }
  return res;
}

int s21_get_minor(s21_matrix* A, int skip_row, int skip_col,
                  s21_matrix* minor) {
  int finish;
  if ((finish = s21_create_matrix(A->rows - 1, A->columns - 1, minor)) != OK) {
    return finish;
  }
  int minor_row = 0;
  int minor_col = 0;
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      if (row != skip_row && col != skip_col) {
        minor->matrix[minor_row][minor_col] = A->matrix[row][col];
        minor_col++;
      }
      if (minor_col == minor->columns) {
        minor_col = 0;
        minor_row++;
      }
    }
  }
  return finish;
}

int s21_get_complements(s21_matrix* A, s21_matrix* result) {
  int finish = OK;
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      s21_matrix minor;
      double det;
      if ((finish = s21_get_minor(A, row, col, &minor)) == OK) {
        s21_determinant(&minor, &det);
        int sign = (row + col) % 2 == 0 ? 1 : -1;
        result->matrix[row][col] = det * sign;
        s21_remove_matrix(&minor);
      }
    }
  }
  return finish;
}

int s21_inversion(s21_matrix* A, double det, s21_matrix* result) {
  int finish;
  s21_matrix tmp_matrix;
  if ((finish = s21_calc_complements(A, &tmp_matrix)) == OK) {
    s21_matrix transposed_tmp_matrix;
    if ((finish = s21_transpose(&tmp_matrix, &transposed_tmp_matrix)) == OK) {
      double mult_num = 1.0 / det;
      finish = s21_mult_number(&transposed_tmp_matrix, mult_num, result);
      s21_remove_matrix(&transposed_tmp_matrix);
    }
    s21_remove_matrix(&tmp_matrix);
  }
  return finish;
}