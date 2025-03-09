#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_basic_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Hello, World!";

  int ret = sprintf(buffer, "%s", fmt);
  int ret_s21 = s21_sprintf(buffer_s21, "%s", fmt);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %.3s";
  const char *str = "testing";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %10s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %10.3s";
  const char *str = "testing";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %-10s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_empty_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = "";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_null_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = NULL;
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_long_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %.10s";
  const char *str = "This is a very long string";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %010s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_exceed_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %5s";
  const char *str = "LongerString";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

TCase *tcase_s21_sprintf_d(void) {
  TCase *tc_core_s = tcase_create("Spec %s");
  
  tcase_add_test(tc_core_s, test_s21_sprintf_basic_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_basic);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_precision);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_width);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_width_precision);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_left_alignment);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_empty_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_null_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_long_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_zero_padding);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_exceed_width);

  
  return tc_core_s;
}