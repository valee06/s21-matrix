#include <check.h>

#include "../s21_matrix.h"
#include "alloc_mock.h"

START_TEST(create_valid_3x3) {
  s21_matrix m;
  ck_assert_int_eq(s21_create_matrix(3, 3, &m), 0);
  ck_assert_int_eq(m.rows, 3);
  ck_assert_int_eq(m.columns, 3);
  ck_assert_ptr_nonnull(m.matrix);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_valid_1x1) {
  s21_matrix m;
  ck_assert_int_eq(s21_create_matrix(1, 1, &m), 0);
  ck_assert_int_eq(m.rows, 1);
  ck_assert_int_eq(m.columns, 1);
  ck_assert_double_eq(m.matrix[0][0], 0.0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_zeroed_elements) {
  s21_matrix m;
  s21_create_matrix(2, 2, &m);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ck_assert_double_eq(m.matrix[i][j], 0.0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_zero_rows_returns_error) {
  s21_matrix m;
  ck_assert_int_eq(s21_create_matrix(0, 3, &m), 1);
}
END_TEST

START_TEST(create_zero_cols_returns_error) {
  s21_matrix m;
  ck_assert_int_eq(s21_create_matrix(3, 0, &m), 1);
}
END_TEST

START_TEST(create_negative_rows_returns_error) {
  s21_matrix m;
  ck_assert_int_eq(s21_create_matrix(-1, 3, &m), 1);
}
END_TEST

START_TEST(create_null_result_returns_error) {
  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), 1);
}
END_TEST

START_TEST(create_non_square) {
  s21_matrix m;
  ck_assert_int_eq(s21_create_matrix(2, 5, &m), 0);
  ck_assert_int_eq(m.rows, 2);
  ck_assert_int_eq(m.columns, 5);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_first_calloc_fails) {
  s21_matrix m;
  s21_enable_calloc_mock(1);
  int ret = s21_create_matrix(10, 10, &m);
  s21_disable_calloc_mock();
  if (ret == 0) s21_remove_matrix(&m);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(create_matrix_second_calloc_fails) {
  s21_matrix m;
  s21_enable_calloc_mock(2);
  int ret = s21_create_matrix(10, 10, &m);
  s21_disable_calloc_mock();
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(create_matrix_third_calloc_fails) {
  s21_matrix m;
  s21_enable_calloc_mock(3);
  int ret = s21_create_matrix(10, 10, &m);
  s21_disable_calloc_mock();
  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite* s21_create_matrix_test(void) {
  Suite* suite = suite_create("s21_create_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, create_valid_3x3);
  tcase_add_test(tc, create_valid_1x1);
  tcase_add_test(tc, create_zeroed_elements);
  tcase_add_test(tc, create_zero_rows_returns_error);
  tcase_add_test(tc, create_zero_cols_returns_error);
  tcase_add_test(tc, create_negative_rows_returns_error);
  tcase_add_test(tc, create_null_result_returns_error);
  tcase_add_test(tc, create_non_square);
  tcase_add_test(tc, create_matrix_first_calloc_fails);
  tcase_add_test(tc, create_matrix_second_calloc_fails);
  tcase_add_test(tc, create_matrix_third_calloc_fails);
  suite_add_tcase(suite, tc);

  return suite;
}
