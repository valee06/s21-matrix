#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_mult_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  int finish = s21_good_for_mult(A, B);
  if (finish != 0) {
    return finish;
  }
  if ((finish = s21_create_matrix(A->rows, B->columns, result)) == 0) {
    for (int row = 0; row < A->rows; row++) {
      for (int col = 0; col < B->columns; col++) {
        result->matrix[row][col] = s21_mult_el_matrix(A, B, row, col);
      }
    }
  }
  return finish;
}