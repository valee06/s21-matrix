#include <check.h>

#include "../s21_matrix.h"

START_TEST(transpose_2x3_to_3x2) {
  s21_matrix a, res;
  s21_create_matrix(2, 3, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[0][2] = 3.0;
  a.matrix[1][0] = 4.0;
  a.matrix[1][1] = 5.0;
  a.matrix[1][2] = 6.0;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_int_eq(res.rows, 3);
  ck_assert_int_eq(res.columns, 2);
  ck_assert_double_eq(res.matrix[0][0], 1.0);
  ck_assert_double_eq(res.matrix[0][1], 4.0);
  ck_assert_double_eq(res.matrix[1][0], 2.0);
  ck_assert_double_eq(res.matrix[1][1], 5.0);
  ck_assert_double_eq(res.matrix[2][0], 3.0);
  ck_assert_double_eq(res.matrix[2][1], 6.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(transpose_square_symmetric) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 1.0);
  ck_assert_double_eq(res.matrix[0][1], 3.0);
  ck_assert_double_eq(res.matrix[1][0], 2.0);
  ck_assert_double_eq(res.matrix[1][1], 4.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(transpose_1x1) {
  s21_matrix a, res;
  s21_create_matrix(1, 1, &a);
  a.matrix[0][0] = 42.0;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 42.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(transpose_null_returns_error) {
  s21_matrix res;
  ck_assert_int_eq(s21_transpose(NULL, &res), 1);
}
END_TEST

START_TEST(transpose_1xn_to_nx1) {
  s21_matrix a, res;
  s21_create_matrix(1, 3, &a);
  a.matrix[0][0] = 10.0;
  a.matrix[0][1] = 20.0;
  a.matrix[0][2] = 30.0;
  ck_assert_int_eq(s21_transpose(&a, &res), 0);
  ck_assert_int_eq(res.rows, 3);
  ck_assert_int_eq(res.columns, 1);
  ck_assert_double_eq(res.matrix[0][0], 10.0);
  ck_assert_double_eq(res.matrix[1][0], 20.0);
  ck_assert_double_eq(res.matrix[2][0], 30.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

Suite* s21_transpose_test(void) {
  Suite* suite = suite_create("s21_transpose");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, transpose_2x3_to_3x2);
  tcase_add_test(tc, transpose_square_symmetric);
  tcase_add_test(tc, transpose_1x1);
  tcase_add_test(tc, transpose_null_returns_error);
  tcase_add_test(tc, transpose_1xn_to_nx1);
  suite_add_tcase(suite, tc);

  return suite;
}
