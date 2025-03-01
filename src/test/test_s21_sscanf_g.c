#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

START_TEST(test_s21_sscanf_g) {
  const char str[] = "12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_zero) {
  const char str[] = "0";
  float res1 = 0, res2 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_max) {
  const char str1[] = "1.7976931348623157E+308";
  long double res_s21 = 0, res = 0;
  int ret = 123, ret_s21 = 123;

  const char *fmt1 = "%Lg";
  ret_s21 = s21_sscanf(str1, fmt1, &res_s21);
  ret = sscanf(str1, fmt1, &res);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_double_eq_tol(res_s21, res, 1e-9);

  long double res2_s21 = 0, res2 = 0;
  const char *fmt2 = "%Lg";
  const char str2[] = "1.7976931348623157E+308";

  int ret2_s21 = s21_sscanf(str2, fmt2, &res2_s21);
  int ret2 = sscanf(str2, fmt2, &res2);

  ck_assert_int_eq(ret2_s21, ret2);
  ck_assert_double_eq(res2_s21, res2);
}
END_TEST

START_TEST(test_s21_sscanf_g_overflow) {
  const char str[] = "1.7976931348623158E+308";
  float res = 0, res_s21 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res_s21);
  int ret2 = sscanf(str, fmt, &res);

  ck_assert_double_eq(res, res_s21);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width) {
  const char str[] = "12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_zero) {
  const char str[] = "0";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_max) {
  const char str[] = "1.7976931348623157E+308";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_overflow) {
  const char str[] = "1.7976931348623158E+308";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_max) {
  const char str[] = "1.7976931348623157E+308";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_overflow) {
  const char str[] = "1.7976931348623158E+308";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

TCase *create_s21_sscanf_g_tests(void) {
  TCase *tc_core_g;
  tc_core_g = tcase_create("Specifier= %g");

  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_negative);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_overflow);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_max);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_zero);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_negative);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_overflow);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_max);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_zero);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_negative);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_overflow);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_max);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_zero);
  tcase_add_test(tc_core_g, test_s21_sscanf_g);

  return tc_core_g;
}