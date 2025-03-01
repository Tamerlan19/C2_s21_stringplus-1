#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

  

START_TEST(test_s21_sscanf_x) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_overflow) {
  const char str[] = "10000000";
  unsigned int res = 111, res_s21 = 111;

  const char *fmt = "%x";
  int ret = sscanf(str, fmt, &res);
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_x_negative) {
  const char str[] = "-12345";
  unsigned res = 111, res_s21 = 111;

  const char *fmt = "%x";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_x_width) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_overflow) {
  const char str[] = "100000000";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_negative) {
  const char str[] = "-12345";
  unsigned res = 111, res_s21 = 111;

  const char *fmt = "%5x";
  int ret = sscanf(str, fmt, &res);
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_max) {
  const char str[] = "ffffffff";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_overflow) {
  const char str[] = "100000000";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_simple) {
  const char *input = "0xf3";
  unsigned x = 10, xr = 10;
  const char *fmt = "%x";
  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST

START_TEST(test_s21_sscanf_xh_simple) {
  const char *input = "0xf3";
  short unsigned x = 10, xr = 10;
  const char *fmt = "%hx";
  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST

START_TEST(test_s21_sscanf_X) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_overflow) {
  const char str[] = "10000000";
  unsigned int res = 123, res_s21 = 123;

  const char *fmt = "%X";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_X_negative) {
  const char str[] = "-12345";
  unsigned res = 0, res_s21 = 0;

  const char *fmt = "%X";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_X_width) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_overflow) {
  const char str[] = "100000000";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_negative) {
  const char str[] = "-12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5X");
  int ret2 = sscanf(str, "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5X");
  int ret2 = sscanf(str, "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_max) {
  const char str[] = "ffffffff";

  int ret1 = s21_sscanf(str, "%*5X");
  int ret2 = sscanf(str, "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_overflow) {
  const char str[] = "100000000";

  int ret1 = s21_sscanf(str, "%*5X");
  int ret2 = sscanf(str, "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5X");
  int ret2 = sscanf(str, "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_simple) {
  const char *input = "0xf3";
  int x = 10, xr = 10;
  const char *fmt = "%i";
  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST


TCase *create_s21_sscanf_x_tests(void) {
    TCase *tc_core_x;
    tc_core_x = tcase_create("Specifier= %x");


    tcase_add_test(tc_core_x, test_s21_sscanf_x_simple);
    tcase_add_test(tc_core_x, test_s21_sscanf_xh_simple);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_negative);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_overflow);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_max);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_zero);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_negative);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_overflow);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_max);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width_zero);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_width);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_negative);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_overflow);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_max);
    tcase_add_test(tc_core_x, test_s21_sscanf_x_zero);
    tcase_add_test(tc_core_x, test_s21_sscanf_x);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_simple);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_negative);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_overflow);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_max);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_zero);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_negative);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_overflow);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_max);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width_zero);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_width);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_negative);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_overflow);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_max);
    tcase_add_test(tc_core_x, test_s21_sscanf_X_zero);
    tcase_add_test(tc_core_x, test_s21_sscanf_X);

  return tc_core_x;
}