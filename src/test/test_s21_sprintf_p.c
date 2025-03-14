#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_p_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %p";
  int value = 42;
  int *ptr = &value;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_null_pointer) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %p";
  void *ptr = NULL;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_hash_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %#p";
  int value = 42;
  int *ptr = &value;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_dynamic_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %*p";
  int value = 42;
  int *ptr = &value;
  int width = 20; // Динамическая ширина
  int ret = sprintf(buffer, fmt, width, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, width, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %016p";
  int value = 42;
  int *ptr = &value;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_dynamic_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %.*p";
  int value = 42;
  int *ptr = &value;
  int precision = 16; // Динамическая точность
  int ret = sprintf(buffer, fmt, precision, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, precision, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_width_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %020p";
  int value = 42;
  int *ptr = &value;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_long_address) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %p";
  long long value = 123456789012345LL;
  long long *ptr = &value;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %-20p";
  int value = 42;
  int *ptr = &value;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_zero_padding_with_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %010p";
  int value = 42;
  int *ptr = &value;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_zero_pointer) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Pointer: %p";
  // int value = 0;
  int *ptr = 0x0;
  int ret = sprintf(buffer, fmt, ptr);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

TCase *tcase_s21_sprintf_p(void) {
  TCase *tc_core_p = tcase_create("Spec %p");

  tcase_add_test(tc_core_p, test_s21_sprintf_p_basic);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_null_pointer);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_hash_flag);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_dynamic_width);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_zero_padding);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_dynamic_precision);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_width_zero_padding);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_long_address);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_left_alignment);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_zero_padding_with_width);
  tcase_add_test(tc_core_p, test_s21_sprintf_p_zero_pointer);

  return tc_core_p;
}