#include <check.h>

#include "test_suites.h"

int main(void) {
  Suite* suites[] = {
      s21_create_matrix_test(),    s21_remove_matrix_test(),
      s21_eq_matrix_test(),        s21_sum_matrix_test(),
      s21_sub_matrix_test(),       s21_mult_number_test(),
      s21_mult_matrix_test(),      s21_transpose_test(),
      s21_calc_complements_test(), s21_determinant_test(),
      s21_inverse_matrix_test(),
  };

  SRunner* runner = srunner_create(suites[0]);
  for (unsigned long i = 1; i < sizeof(suites) / sizeof(suites[0]); ++i) {
    srunner_add_suite(runner, suites[i]);
  }

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed == 0 ? 0 : 1;
}
