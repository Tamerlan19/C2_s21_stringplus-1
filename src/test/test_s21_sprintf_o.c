#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

START_TEST(test_s21_sprintf_o_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %o";
  unsigned int value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_hash_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %#o";
  unsigned int value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %5o";
  unsigned int value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %05o";
  unsigned int value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_dynamic_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %*o";
  unsigned int value = 64;
  int width = 5;
  int ret = sprintf(buffer, fmt, width, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, width, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_dynamic_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %.*o";
  unsigned int value = 64;
  int precision = 5;
  int ret = sprintf(buffer, fmt, precision, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, precision, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %o";
  unsigned int value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_hash_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %#o";
  unsigned int value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_width_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %05o";
  unsigned int value = 10;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_large_number) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %o";
  unsigned int value = 4294967295;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_precision_nul) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %.0o";
  unsigned int value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_precision_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %-.5o";
  unsigned int value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %lo";
  unsigned long value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_hash_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %#lo";
  unsigned long value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %5lo";
  unsigned long value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %05lo";
  unsigned long value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %-5lo";
  unsigned long value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_hash_with_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %#5lo";
  unsigned long value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %lo";
  unsigned long value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_hash_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %#lo";
  unsigned long value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_large_number) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %lo";
  unsigned long value = 4294967295UL;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %.5lo";
  unsigned long value = 10;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_dynamic_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %*lo";
  unsigned long value = 64;
  int width = 10;
  int ret = sprintf(buffer, fmt, width, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, width, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lo_dynamic_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Octal: %.*lo";
  unsigned long value = 10;
  int precision = 5;
  int ret = sprintf(buffer, fmt, precision, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, precision, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %ho";
  unsigned short value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_hash_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %#ho";
  unsigned short value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %5ho";
  unsigned short value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %05ho";
  unsigned short value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %-5ho";
  unsigned short value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_hash_with_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %#5ho";
  unsigned short value = 64;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %ho";
  unsigned short value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_hash_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %#ho";
  unsigned short value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_large_number) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %ho";
  unsigned short value = 65535;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %.5ho";
  unsigned short value = 10;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_dynamic_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %*ho";
  unsigned short value = 64;
  int width = 10;
  int ret = sprintf(buffer, fmt, width, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, width, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ho_dynamic_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Octal: %.*ho";
  unsigned short value = 10;
  int precision = 5;
  int ret = sprintf(buffer, fmt, precision, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, precision, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

TCase *tcase_s21_sprintf_o(void) {
  TCase *tc_core_o = tcase_create("Spec %o");

  tcase_add_test(tc_core_o, test_s21_sprintf_o_basic);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_hash_flag);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_zero_padding);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_dynamic_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_dynamic_precision);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_zero_value);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_hash_zero_value);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_width_zero_padding);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_large_number);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_precision_nul);
  tcase_add_test(tc_core_o, test_s21_sprintf_o_precision_padding);

  tcase_add_test(tc_core_o, test_s21_sprintf_lo_basic);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_hash_flag);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_zero_padding);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_left_alignment);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_hash_with_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_zero_value);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_hash_zero_value);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_large_number);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_precision);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_dynamic_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_lo_dynamic_precision);

  tcase_add_test(tc_core_o, test_s21_sprintf_ho_basic);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_hash_flag);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_zero_padding);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_left_alignment);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_hash_with_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_zero_value);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_hash_zero_value);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_large_number);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_precision);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_dynamic_width);
  tcase_add_test(tc_core_o, test_s21_sprintf_ho_dynamic_precision);

  return tc_core_o;
}