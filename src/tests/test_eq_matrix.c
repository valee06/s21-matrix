#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

START_TEST(eq_identical_matrices) {
  s21_matrix a, b;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  b.matrix[0][0] = 1.0;
  b.matrix[0][1] = 2.0;
  b.matrix[1][0] = 3.0;
  b.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_different_values) {
  s21_matrix a, b;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 1.0;
  b.matrix[0][0] = 2.0;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_different_sizes) {
  s21_matrix a, b;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 3, &b);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_null_matrix_returns_failure) {
  s21_matrix a;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_eq_matrix(&a, NULL), 0);
  ck_assert_int_eq(s21_eq_matrix(NULL, &a), 0);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(eq_within_epsilon) {
  s21_matrix a, b;
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &b);
  a.matrix[0][0] = 1.0;
  b.matrix[0][0] = 1.0 + 1e-8;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_outside_epsilon) {
  s21_matrix a, b;
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &b);
  a.matrix[0][0] = 1.0;
  b.matrix[0][0] = 1.0 + 1e-6;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

Suite* s21_eq_matrix_test(void) {
  Suite* suite = suite_create("s21_eq_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, eq_identical_matrices);
  tcase_add_test(tc, eq_different_values);
  tcase_add_test(tc, eq_different_sizes);
  tcase_add_test(tc, eq_null_matrix_returns_failure);
  tcase_add_test(tc, eq_within_epsilon);
  tcase_add_test(tc, eq_outside_epsilon);
  suite_add_tcase(suite, tc);

  return suite;
}
