#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

START_TEST(mult_number_simple) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_mult_number(&a, 3.0, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 3.0);
  ck_assert_double_eq(res.matrix[0][1], 6.0);
  ck_assert_double_eq(res.matrix[1][0], 9.0);
  ck_assert_double_eq(res.matrix[1][1], 12.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_number_by_zero) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 5.0;
  a.matrix[1][1] = 9.0;
  ck_assert_int_eq(s21_mult_number(&a, 0.0, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 0.0);
  ck_assert_double_eq(res.matrix[1][1], 0.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_number_by_negative) {
  s21_matrix a, res;
  s21_create_matrix(1, 2, &a);
  a.matrix[0][0] = 4.0;
  a.matrix[0][1] = -2.0;
  ck_assert_int_eq(s21_mult_number(&a, -1.0, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], -4.0);
  ck_assert_double_eq(res.matrix[0][1], 2.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_number_null_matrix_returns_error) {
  s21_matrix res;
  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &res), 1);
}
END_TEST

START_TEST(mult_number_nan_scalar_returns_error) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_mult_number(&a, __builtin_nan(""), &res), 2);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(mult_number_inf_scalar_returns_error) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_mult_number(&a, __builtin_inf(), &res), 2);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(mult_number_nan_element_returns_error) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  a.matrix[1][0] = __builtin_nan("");
  ck_assert_int_eq(s21_mult_number(&a, 2.0, &res), 2);
  s21_remove_matrix(&a);
}
END_TEST

Suite* s21_mult_number_test(void) {
  Suite* suite = suite_create("s21_mult_number");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, mult_number_simple);
  tcase_add_test(tc, mult_number_by_zero);
  tcase_add_test(tc, mult_number_by_negative);
  tcase_add_test(tc, mult_number_null_matrix_returns_error);
  tcase_add_test(tc, mult_number_nan_scalar_returns_error);
  tcase_add_test(tc, mult_number_inf_scalar_returns_error);
  tcase_add_test(tc, mult_number_nan_element_returns_error);
  suite_add_tcase(suite, tc);

  return suite;
}
