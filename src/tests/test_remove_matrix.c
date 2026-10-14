#include <check.h>

#include "../s21_matrix.h"

START_TEST(remove_valid_matrix) {
  s21_matrix m;
  s21_create_matrix(3, 3, &m);
  s21_remove_matrix(&m);
  ck_assert_ptr_null(m.matrix);
  ck_assert_int_eq(m.rows, 0);
  ck_assert_int_eq(m.columns, 0);
}
END_TEST

START_TEST(remove_null_pointer_no_crash) {
  s21_remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(remove_1x1_matrix) {
  s21_matrix m;
  s21_create_matrix(1, 1, &m);
  m.matrix[0][0] = 42.0;
  s21_remove_matrix(&m);
  ck_assert_ptr_null(m.matrix);
}
END_TEST

Suite* s21_remove_matrix_test(void) {
  Suite* suite = suite_create("s21_remove_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, remove_valid_matrix);
  tcase_add_test(tc, remove_null_pointer_no_crash);
  tcase_add_test(tc, remove_1x1_matrix);
  suite_add_tcase(suite, tc);

  return suite;
}
