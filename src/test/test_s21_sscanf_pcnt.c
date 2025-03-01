#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

  
START_TEST(test_s21_sscanf_percent) {
  const char str[] = "12345%54321";
  const char *fmt = "%d%%%d";
  int res1 = 0, res2 = 0;
  int res1_s21 = 0, res2_s21 = 0;

  int ret_s21 = s21_sscanf(str, fmt, &res1_s21, &res2_s21);
  int ret = sscanf(str, fmt, &res1, &res2);

  ck_assert_int_eq(res1, res1_s21);
  ck_assert_int_eq(res2, res2_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space) {
  const char str[] = "12345 % 54321";
  const char *fmt = "%d %% %d";
  int res1 = 0, res2 = 0;
  int res1_s21 = 0, res2_s21 = 0;

  int ret_s21 = s21_sscanf(str, fmt, &res1_s21, &res2_s21);
  int ret = sscanf(str, fmt, &res1, &res2);

  ck_assert_int_eq(res1, res1_s21);
  ck_assert_int_eq(res2, res2_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space_s) {
  const char str[] = "12345%54321";
  const char *fmt = "%s %% %s";
  char str1[20] = {0}, str2[20] = {0}, str1r[20] = {0}, str2r[20] = {0};

  int ret_s21 = s21_sscanf(str, fmt, str1, str2);
  int ret = sscanf(str, fmt, str1r, str2r);

  ck_assert_str_eq(str1, str1r);
  ck_assert_str_eq(str2, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space_2) {
  const char str[] = "Use %triple space in format string";

  const char *fmt = "%s%% %s";
  char str1_s21[20] = {0}, str2_s21[20] = "TEST", str1r[20] = {0},
       str2r[20] = "TEST";

  int ret_s21 = s21_sscanf(str, fmt, str1_s21, str2_s21);
  int ret = sscanf(str, fmt, str1r, str2r);

  ck_assert_str_eq(str1_s21, str1r);
  ck_assert_str_eq(str2_s21, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space_triple) {
  const char str[] = "Use%triple space in format string";
  const char *fmt = "%s%%% %s";
  char str1[20] = {0}, str2[20] = "TEST", str1r[20] = {0}, str2r[20] = "TEST";

  int ret_s21 = s21_sscanf(str, fmt, str1, str2);
  int ret = sscanf(str, fmt, str1r, str2r);

  ck_assert_str_eq(str1, str1r);
  ck_assert_str_eq(str2, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST


TCase *create_s21_sscanf_pcnt_tests(void) {
    TCase *tc_core_pcnt;
    tc_core_pcnt = tcase_create("Specifier= %%");

    tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent);
    tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space);
    tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space_2);
    tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space_s);
    tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space_triple);

  return tc_core_pcnt;
}