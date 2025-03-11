#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

START_TEST(test_s21_sscanf_f) {
  const char str[] = "12345";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_zero) {
  const char str[] = "0";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_max) {
  const char str[] = "3.402823466E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_overflow) {
  const char str[] = "3.402823467E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_negative) {
  const char str[] = "-12345";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width) {
  const char str[] = "12345";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_zero) {
  const char str[] = "0";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_max) {
  const char str[] = "3.402823466E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_overflow) {
  const char str[] = "3.402823467E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_max) {
  const char str[] = "3.402823466E+38";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_overflow) {
  const char str[] = "3.402823467E+38";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

TCase *create_s21_sscanf_f_tests(void) {
  TCase *tc_core_f;
  tc_core_f = tcase_create("Specifier= %f");

  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_negative);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_overflow);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_max);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_zero);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_negative);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_overflow);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_max);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_zero);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_negative);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_overflow);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_max);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_zero);
  tcase_add_test(tc_core_f, test_s21_sscanf_f);

  return tc_core_f;
}