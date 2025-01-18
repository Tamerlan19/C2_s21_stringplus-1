#include "s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_n) {
  const char *fmt = "The result=%n";
  char output[100];
  char output_res[100];
  int x = 5;
  ck_assert_int_eq(s21_sprintf(output, fmt, x), sprintf(output_res, fmt, x));
  //   ck_assert_int_eq(x, xr);
}

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sprintf_n);

  suite_add_tcase(s, tc_core);

  return s;
}
