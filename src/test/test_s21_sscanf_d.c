#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_s21_sscanf_d_simple) {
  const char *input = "123";
  int x = 0, xr = 0;
  int ret_s21 = s21_sscanf(input, "%d", &x);
  int ret = sscanf(input, "%d", &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_neg) {
  const char *input = "-123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_neg_twice) {
  const char *input = "--123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_some) {
  const char *input = "123 -456 789";
  int x = 0, y = 0, z = 0, xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";
  int ret_s21 = s21_sscanf(input, fmt, &x, &y, &z);
  int ret = sscanf(input, fmt, &xr, &yr, &zr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(zr, zr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_space_bef) {
  const char *input = "  123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_space_aft) {
  const char *input = "123   ";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_merge_string_end) {
  const char *input = "123Hello Worrld!!!";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_merge_string_start) {
  const char *input = "qwerty123";
  int x = 1, xr = 1;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_empty) {
  const char *input = "";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_max) {
  const char *input = "2147483647";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_min) {
  const char *input = " -2147483648";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_max_over) {
  const char *input = "2147483657";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_miss) {
  const char *input = "9903456";
  int ret_s21 = s21_sscanf(input, "%*d");
  int ret = sscanf(input, "%*d");
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_width) {
  const char *input = "123456";
  int x = 0, xr = 0;
  const char *fmt = "%3d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_wrong_fmt) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_wrong_fmt_width) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%2d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_some_fmt_wrong) {
  const char *input = "123 -456 abc";
  int x = 0, y = 0, z = 0, xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";
  int ret_s21 = s21_sscanf(input, fmt, &x, &y, &z);
  int ret = sscanf(input, fmt, &xr, &yr, &zr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(zr, zr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_some_sep) {
  const char *input = " \t\n123 \t\n456 \t\n";
  int x = 0, y = 0, xr = 0, yr = 0;
  const char *fmt = "%d %d";
  int ret_s21 = s21_sscanf(input, fmt, &x, &y);
  int ret = sscanf(input, fmt, &xr, &yr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_zero) {
  const char *input = "0";
  int x = 111, xr = 111;
  const char *fmt = "%d";
  int ret = sscanf(input, fmt, &xr);
  int ret_s21 = s21_sscanf(input, fmt, &x);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_skip_assignment) {
  const char *input = "";
  int x = 10, xr = 10;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_zero_start) {
  const char *input = "00789";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_ld_skip_assignment) {
  const char *input = "12345";
  long value = 0;
  int result = s21_sscanf(input, "%*ld");
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(value, 0);
}
END_TEST

START_TEST(test_s21_sscanf_hd) {
  const char *input = "12345";
  short value = 0;
  int result = s21_sscanf(input, "%hd", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 12345);
}
END_TEST

START_TEST(test_s21_sscanf_ld) {
  const char *input = "21474836480";
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 21474836480L);
}
END_TEST

START_TEST(test_s21_sscanf_ld_width) {
  const char *input = "123456";
  long value = 0;
  int result = s21_sscanf(input, "%3ld", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 123);
}
END_TEST

START_TEST(test_s21_sscanf_ld_invalid) {
  const char *input = "abc";
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(value, 0);
}
END_TEST

START_TEST(test_s21_sscanf_ld_empty) {
  const char *input = "";
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, -1);
  ck_assert_int_eq(value, 0);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_space) {
  const char *input = "123 456 789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_tab) {
  const char *input = "123\t456\t789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%d%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_comma) {
  const char *input = "123,456,789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d,%d,%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_mixed) {
  const char *input = "123, 456, 789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d, %d, %d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_newline) {
  const char *input = "123\n456\n789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%d%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_semicolon) {
  const char *input = "123;456;789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d;%d;%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_skip) {
  const char *input = "123abc456def789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%*c%d%*c%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

TCase *create_s21_sscanf_d_tests(void) {
  TCase *tc_core_d = tcase_create("Specifier= %d");

  tcase_add_test(tc_core_d, test_s21_sscanf_d_simple);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_neg);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_neg_twice);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_space_bef);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_space_aft);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_some);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_merge_string_end);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_merge_string_start);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_empty);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_max);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_min);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_max_over);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_miss);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_width);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_some_fmt_wrong);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_wrong_fmt);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_wrong_fmt_width);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_some_sep);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_zero);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_zero_start);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_skip_assignment);
  tcase_add_test(tc_core_d, test_s21_sscanf_hd);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_skip_assignment);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_width);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_invalid);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_empty);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_space);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_tab);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_comma);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_mixed);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_newline);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_skip);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_semicolon);

  return tc_core_d;
}