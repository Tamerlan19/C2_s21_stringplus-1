#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_o_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Octal: %o";
  unsigned int value = 64; // Восьмеричное представление: 100
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
  unsigned int value = 64; // Восьмеричное представление: 100
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
  unsigned int value = 64; // Восьмеричное представление: 100
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
  unsigned int value = 64; // Восьмеричное представление: 100
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
  unsigned int value = 64; // Восьмеричное представление: 100
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
  unsigned int value = 64; // Восьмеричное представление: 100
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
  unsigned int value = 0; // Нулевое значение
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
  unsigned int value = 0; // Нулевое значение
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
  unsigned int value = 10; // Восьмеричное представление: 12
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
  unsigned int value = 4294967295; // Максимальное значение для unsigned int (восьмеричное: 37777777777)
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
  unsigned int value = 0; // Максимальное значение для unsigned int (восьмеричное: 37777777777)
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
  unsigned int value = 0; // Максимальное значение для unsigned int (восьмеричное: 37777777777)
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
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



  return tc_core_o;
}