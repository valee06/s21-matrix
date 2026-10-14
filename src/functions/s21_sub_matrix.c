#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_sub_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  return s21_sum_sub(A, B, result, -1);
}