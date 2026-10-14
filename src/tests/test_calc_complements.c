#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

START_TEST(calc_complements_2x2) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_calc_complements(&a, &res), 0);
  ck_assert_double_eq_tol(res.matrix[0][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(res.matrix[0][1], -3.0, 1e-7);
  ck_assert_double_eq_tol(res.matrix[1][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(res.matrix[1][1], 1.0, 1e-7);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_complements_1x1) {
  s21_matrix a, res;
  s21_create_matrix(1, 1, &a);
  a.matrix[0][0] = 99.0;
  ck_assert_int_eq(s21_calc_complements(&a, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 1.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_complements_non_square_returns_error) {
  s21_matrix a, res;
  s21_create_matrix(2, 3, &a);
  ck_assert_int_eq(s21_calc_complements(&a, &res), 2);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(calc_complements_null_matrix_returns_error) {
  s21_matrix res;
  ck_assert_int_eq(s21_calc_complements(NULL, &res), 1);
}
END_TEST

START_TEST(calc_complements_null_result_returns_error) {
  s21_matrix a;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_calc_complements(&a, NULL), 1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(calc_complements_identity_3x3) {
  s21_matrix a, res;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[1][1] = 1.0;
  a.matrix[2][2] = 1.0;
  ck_assert_int_eq(s21_calc_complements(&a, &res), 0);
  ck_assert_double_eq_tol(res.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(res.matrix[1][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(res.matrix[2][2], 1.0, 1e-7);
  ck_assert_double_eq_tol(res.matrix[0][1], 0.0, 1e-7);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

Suite* s21_calc_complements_test(void) {
  Suite* suite = suite_create("s21_calc_complements");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, calc_complements_2x2);
  tcase_add_test(tc, calc_complements_1x1);
  tcase_add_test(tc, calc_complements_non_square_returns_error);
  tcase_add_test(tc, calc_complements_null_matrix_returns_error);
  tcase_add_test(tc, calc_complements_null_result_returns_error);
  tcase_add_test(tc, calc_complements_identity_3x3);
  suite_add_tcase(suite, tc);

  return suite;
}
