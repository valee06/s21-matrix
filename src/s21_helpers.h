#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

enum result { OK, INCORRECT_MATRIX_ERROR, CALCULATION_ERROR };

static inline int s21_incorrect_rows_cols(int rows, int cols) {
  return rows <= 0 || cols <= 0;
}

static inline int s21_not_equal_size(s21_matrix* A, s21_matrix* B) {
  return ((A->rows != B->rows) || (A->columns != B->columns));
}

static inline int s21_bad_matrix(s21_matrix* A) {
  return (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0);
}

static inline int s21_bad_matrixes(s21_matrix* A, s21_matrix* B) {
  return (s21_bad_matrix(A) || s21_bad_matrix(B));
}

static inline int s21_square_matrix(s21_matrix* A) {
  return (A->rows == A->columns) ? OK : CALCULATION_ERROR;
}

void s21_free_matrix(s21_matrix* A);
void s21_comparison(s21_matrix* A, s21_matrix* B, int* finish);
int s21_both_good_matrix(s21_matrix* A, s21_matrix* B);
int s21_sum_sub(s21_matrix* A, s21_matrix* B, s21_matrix* result, int sign);
int s21_isnan_or_isinf_el_in_matrix(s21_matrix* A);
int s21_good_for_mult(s21_matrix* A, s21_matrix* B);
double s21_mult_el_matrix(s21_matrix* A, s21_matrix* B, int row, int col);
int s21_get_minor(s21_matrix* A, int skip_row, int skip_col, s21_matrix* minor);
int s21_get_complements(s21_matrix* A, s21_matrix* result);
int s21_inversion(s21_matrix* A, double det, s21_matrix* result);
#endif