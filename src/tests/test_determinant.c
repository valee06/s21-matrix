#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

START_TEST(det_1x1) {
  s21_matrix a;
  double res;
  s21_create_matrix(1, 1, &a);
  a.matrix[0][0] = 7.0;
  ck_assert_int_eq(s21_determinant(&a, &res), 0);
  ck_assert_double_eq(res, 7.0);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(det_2x2) {
  s21_matrix a;
  double res;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_determinant(&a, &res), 0);
  ck_assert_double_eq_tol(res, -2.0, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(det_3x3_singular) {
  s21_matrix a;
  double res;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[0][2] = 3.0;
  a.matrix[1][0] = 4.0;
  a.matrix[1][1] = 5.0;
  a.matrix[1][2] = 6.0;
  a.matrix[2][0] = 7.0;
  a.matrix[2][1] = 8.0;
  a.matrix[2][2] = 9.0;
  ck_assert_int_eq(s21_determinant(&a, &res), 0);
  ck_assert_double_eq(res, 0.0);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(det_3x3_nonzero) {
  s21_matrix a;
  double res;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 2.0;
  a.matrix[0][1] = 1.0;
  a.matrix[0][2] = 3.0;
  a.matrix[1][0] = 1.0;
  a.matrix[1][1] = 4.0;
  a.matrix[1][2] = 2.0;
  a.matrix[2][0] = 3.0;
  a.matrix[2][1] = 2.0;
  a.matrix[2][2] = 1.0;
  ck_assert_int_eq(s21_determinant(&a, &res), 0);
  ck_assert_double_eq_tol(res, -25.0, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(det_non_square_returns_error) {
  s21_matrix a;
  double res;
  s21_create_matrix(2, 3, &a);
  ck_assert_int_eq(s21_determinant(&a, &res), 2);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(det_null_matrix_returns_error) {
  double res;
  ck_assert_int_eq(s21_determinant(NULL, &res), 1);
}
END_TEST

START_TEST(det_null_result_returns_error) {
  s21_matrix a;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_determinant(&a, NULL), 1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(det_identity_3x3) {
  s21_matrix a;
  double res;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1.0;
  a.matrix[1][1] = 1.0;
  a.matrix[2][2] = 1.0;
  ck_assert_int_eq(s21_determinant(&a, &res), 0);
  ck_assert_double_eq_tol(res, 1.0, 1e-7);
  s21_remove_matrix(&a);
}
END_TEST

Suite* s21_determinant_test(void) {
  Suite* suite = suite_create("s21_determinant");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, det_1x1);
  tcase_add_test(tc, det_2x2);
  tcase_add_test(tc, det_3x3_singular);
  tcase_add_test(tc, det_3x3_nonzero);
  tcase_add_test(tc, det_non_square_returns_error);
  tcase_add_test(tc, det_null_matrix_returns_error);
  tcase_add_test(tc, det_null_result_returns_error);
  tcase_add_test(tc, det_identity_3x3);
  suite_add_tcase(suite, tc);

  return suite;
}
