#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>



START_TEST(test_s21_sscanf_o_simple) {
  const char *input = "01237";
  unsigned x = 10, xr = 10;
  const char *fmt = "%o";

  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);

  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST



START_TEST(test_s21_sscanf_o) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_max) {
  const char str[] = "37777777777";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_overflow) {
  const char str[] = "37777777778";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_negative) {
  const char str[] = "-12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_max) {
  const char str[] = "37777777777";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_overflow) {
  const char str[] = "37777777778";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_negative) {
  const char str[] = "-12345";
  unsigned res4 = 111, res_s21 = 111;

  const char *fmt = "%5o";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res4);

  ck_assert_int_eq(res4, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_max) {
  const char str[] = "37777777777";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_overflow) {
  const char str[] = "37777777778";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST


TCase *create_s21_sscanf_o_tests(void) {
    TCase *tc_core_o;
    tc_core_o = tcase_create("Specifier= %o");
    tcase_add_test(tc_core_o, test_s21_sscanf_o_simple);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_negative);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_overflow);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_max);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_zero);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_negative);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_overflow);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_max);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width_zero);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_width);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_negative);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_overflow);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_max);
    tcase_add_test(tc_core_o, test_s21_sscanf_o_zero);
    tcase_add_test(tc_core_o, test_s21_sscanf_o);


  return tc_core_o;
}