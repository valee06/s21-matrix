#include "../s21_helpers.h"
#include "../s21_matrix.h"

void s21_remove_matrix(s21_matrix* A) {
  if (A != NULL) {
    if (A->matrix != NULL) s21_free_matrix(A);
    A->rows = 0;
    A->columns = 0;
  }
}