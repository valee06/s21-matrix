#include "../s21_helpers.h"
#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, s21_matrix* result) {
  if (result == NULL || (s21_incorrect_rows_cols(rows, columns))) {
    return INCORRECT_MATRIX_ERROR;
  }

  int finish = OK;

  result->matrix = (double**)calloc(rows, sizeof(double*));
  if (result->matrix == NULL) {
    finish = INCORRECT_MATRIX_ERROR;
  }

  for (int ptr = 0; ptr < rows && !finish; ptr++) {
    result->matrix[ptr] = (double*)calloc(columns, sizeof(double));
    if (result->matrix[ptr] == NULL) {
      finish = INCORRECT_MATRIX_ERROR;
      for (int ptr_1 = 0; ptr_1 < ptr; ptr_1++) {
        free(result->matrix[ptr_1]);
      }
      free(result->matrix);
    }
  }

  if (!finish) {
    result->rows = rows;
    result->columns = columns;
  }
  return finish;
}