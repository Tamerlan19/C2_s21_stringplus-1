#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_c_simple_char) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%c";

  int ret = sprintf(buffer, fmt, 'A');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'A');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_width) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%5c";

  int ret = sprintf(buffer, fmt, 'B');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'B');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_left_align) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%-5c";

  int ret = sprintf(buffer, fmt, 'C');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'C');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_zero_padding) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%5c";
  int ret = sprintf(buffer, fmt, 'D');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'D');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_min_width_one) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%1c";

  int ret = sprintf(buffer, fmt, 'E');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'E');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_negative_width) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%-5c";

  int ret = sprintf(buffer, fmt, 'F');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'F');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

TCase *tcase_s21_sprintf_c(void) {
  TCase *tc_core_c = tcase_create("Spec %c");

  tcase_add_test(tc_core_c, test_s21_sprintf_c_zero_padding);
  tcase_add_test(tc_core_c, test_s21_sprintf_c_simple_char);
  tcase_add_test(tc_core_c, test_s21_sprintf_c_width);
  tcase_add_test(tc_core_c, test_s21_sprintf_c_left_align);
  tcase_add_test(tc_core_c, test_s21_sprintf_c_zero_padding);
  tcase_add_test(tc_core_c, test_s21_sprintf_c_min_width_one);
  tcase_add_test(tc_core_c, test_s21_sprintf_c_negative_width);
  tcase_add_test(tc_core_c, test_s21_sprintf_c_width);
  return tc_core_c;
}