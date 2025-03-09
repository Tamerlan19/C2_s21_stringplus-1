#include "../s21_string.h"
#include <check.h>
#include <stdio.h>
START_TEST(test_s21_sprintf_u_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %u";
  unsigned int value = 12345;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %10u";
  unsigned int value = 789;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %.5u";
  unsigned int value = 45;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_width_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %10.5u";
  unsigned int value = 678;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %-10u";
  unsigned int value = 123;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %010u";
  unsigned int value = 456;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %.5u";
  unsigned int value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_large_number) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %u";
  unsigned int value = 4294967295; // Максимальное значение для unsigned int
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_exceed_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %5u";
  unsigned int value = 123456789;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_hu_short_unsigned) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Unsigned: %hu";
  unsigned short int short_uvalue =
      65535; // Максимальное значение для unsigned short
  int ret = sprintf(buffer, fmt, short_uvalue);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, short_uvalue);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lu_long_unsigned) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Unsigned: %lu";
  unsigned long int long_uvalue =
      4294967295UL; // Максимальное значение для unsigned long
  int ret = sprintf(buffer, fmt, long_uvalue);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, long_uvalue);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

TCase *tcase_s21_sprintf_u(void) {
  TCase *tc_core_u = tcase_create("Spec %u");
  tcase_add_test(tc_core_u, test_s21_sprintf_u_basic);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_width);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_precision);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_left_alignment);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_zero_padding);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_zero_value);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_large_number);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_exceed_width);
  tcase_add_test(tc_core_u, test_s21_sprintf_u_width_precision);
  tcase_add_test(tc_core_u, test_s21_sprintf_hu_short_unsigned);
  tcase_add_test(tc_core_u, test_s21_sprintf_lu_long_unsigned);
  return tc_core_u;
}