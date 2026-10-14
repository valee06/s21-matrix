#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_eq_matrix(s21_matrix* A, s21_matrix* B) {
  if (s21_bad_matrix(A) || s21_bad_matrix(B)) {
    return FAILURE;
  }

  int finish = SUCCESS;

  if (s21_not_equal_size(A, B)) {
    finish = FAILURE;
  } else {
    s21_comparison(A, B, &finish);
  }

  return finish;
}