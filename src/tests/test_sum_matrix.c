#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

START_TEST(sum_simple_2x2) {
  s21_matrix a, b, res;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  b.matrix[0][0] = 5.0;
  b.matrix[0][1] = 6.0;
  b.matrix[1][0] = 7.0;
  b.matrix[1][1] = 8.0;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 6.0);
  ck_assert_double_eq(res.matrix[0][1], 8.0);
  ck_assert_double_eq(res.matrix[1][0], 10.0);
  ck_assert_double_eq(res.matrix[1][1], 12.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_different_sizes_returns_error) {
  s21_matrix a, b, res;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 3, &b);
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sum_null_matrix_returns_error) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_sum_matrix(&a, NULL, &res), 1);
  ck_assert_int_eq(s21_sum_matrix(NULL, &a, &res), 1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(sum_with_zero_matrix) {
  s21_matrix a, b, res;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 3.5;
  a.matrix[0][1] = -1.0;
  a.matrix[1][0] = 0.0;
  a.matrix[1][1] = 7.2;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), 0);
  ck_assert_double_eq_tol(res.matrix[0][0], 3.5, 1e-7);
  ck_assert_double_eq_tol(res.matrix[0][1], -1.0, 1e-7);
  ck_assert_double_eq_tol(res.matrix[1][1], 7.2, 1e-7);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_negative_values) {
  s21_matrix a, b, res;
  s21_create_matrix(1, 2, &a);
  s21_create_matrix(1, 2, &b);
  a.matrix[0][0] = -5.0;
  a.matrix[0][1] = 3.0;
  b.matrix[0][0] = -2.0;
  b.matrix[0][1] = -3.0;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], -7.0);
  ck_assert_double_eq(res.matrix[0][1], 0.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_nan_element_returns_error) {
  s21_matrix a, b, res;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = __builtin_nan("");
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &res), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

Suite* s21_sum_matrix_test(void) {
  Suite* suite = suite_create("s21_sum_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, sum_simple_2x2);
  tcase_add_test(tc, sum_different_sizes_returns_error);
  tcase_add_test(tc, sum_null_matrix_returns_error);
  tcase_add_test(tc, sum_with_zero_matrix);
  tcase_add_test(tc, sum_negative_values);
  tcase_add_test(tc, sum_nan_element_returns_error);
  suite_add_tcase(suite, tc);

  return suite;
}
