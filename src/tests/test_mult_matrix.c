#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

START_TEST(mult_matrix_2x3_by_3x2) {
  s21_matrix a, b, res;
  s21_create_matrix(2, 3, &a);
  s21_create_matrix(3, 2, &b);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[0][2] = 3.0;
  a.matrix[1][0] = 4.0;
  a.matrix[1][1] = 5.0;
  a.matrix[1][2] = 6.0;
  b.matrix[0][0] = 7.0;
  b.matrix[0][1] = 8.0;
  b.matrix[1][0] = 9.0;
  b.matrix[1][1] = 10.0;
  b.matrix[2][0] = 11.0;
  b.matrix[2][1] = 12.0;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 0);
  ck_assert_int_eq(res.rows, 2);
  ck_assert_int_eq(res.columns, 2);
  ck_assert_double_eq(res.matrix[0][0], 58.0);
  ck_assert_double_eq(res.matrix[0][1], 64.0);
  ck_assert_double_eq(res.matrix[1][0], 139.0);
  ck_assert_double_eq(res.matrix[1][1], 154.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_matrix_incompatible_sizes_returns_error) {
  s21_matrix a, b, res;
  s21_create_matrix(2, 3, &a);
  s21_create_matrix(2, 3, &b);
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(mult_matrix_null_returns_error) {
  s21_matrix a, res;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_mult_matrix(NULL, &a, &res), 1);
  ck_assert_int_eq(s21_mult_matrix(&a, NULL, &res), 1);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(mult_matrix_by_identity) {
  s21_matrix a, id, res;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &id);
  a.matrix[0][0] = 3.0;
  a.matrix[0][1] = 7.0;
  a.matrix[1][0] = -1.0;
  a.matrix[1][1] = 5.0;
  id.matrix[0][0] = 1.0;
  id.matrix[1][1] = 1.0;
  ck_assert_int_eq(s21_mult_matrix(&a, &id, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 3.0);
  ck_assert_double_eq(res.matrix[0][1], 7.0);
  ck_assert_double_eq(res.matrix[1][0], -1.0);
  ck_assert_double_eq(res.matrix[1][1], 5.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&id);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_matrix_1x1) {
  s21_matrix a, b, res;
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &b);
  a.matrix[0][0] = 6.0;
  b.matrix[0][0] = 7.0;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 42.0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

Suite* s21_mult_matrix_test(void) {
  Suite* suite = suite_create("s21_mult_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, mult_matrix_2x3_by_3x2);
  tcase_add_test(tc, mult_matrix_incompatible_sizes_returns_error);
  tcase_add_test(tc, mult_matrix_null_returns_error);
  tcase_add_test(tc, mult_matrix_by_identity);
  tcase_add_test(tc, mult_matrix_1x1);
  suite_add_tcase(suite, tc);

  return suite;
}
