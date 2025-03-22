#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_s21_sscanf_i) {
  const char str[] = "12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_zero) {
  const char str[] = "0";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_max) {
  const char str[] = "2147483647";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_overflow) {
  const char str[] = "2147483648";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_negative) {
  const char str[] = "-12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width) {
  const char str[] = "12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_zero) {
  const char str[] = "0";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_max) {
  const char str[] = "2147483647";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_overflow) {
  const char str[] = "2147483648";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_negative) {
  const char str[] = "-12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_max) {
  const char str[] = "2147483647";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_overflow) {
  const char str[] = "2147483648";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

TCase *create_s21_sscanf_i_tests(void) {
  TCase *tc_core_i;
  tc_core_i = tcase_create("Specifier= %i");

  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_negative);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_overflow);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_max);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_zero);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_negative);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_overflow);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_max);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_zero);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_negative);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_overflow);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_max);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_zero);
  tcase_add_test(tc_core_i, test_s21_sscanf_i);

  return tc_core_i;
}