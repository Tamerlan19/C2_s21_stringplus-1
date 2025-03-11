#include "../s21_string.h"
#include <check.h>
#include <stdio.h>
START_TEST(test_s21_sprintf_f_float) {
  char buffer[100];
  char buffer_s21[100];
  const char *fmt = "Float: %.2f";

  int ret = sprintf(buffer, fmt, 3.14159);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 3.14159);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ld_double_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double long_value = 123456789.987654321;
  s21_sprintf(buffer, "Long Number: %lf", long_value);
  sprintf(original_buffer, "Long Number: %lf", long_value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_negative_f_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double negative_value = -123.456;
  s21_sprintf(buffer, "Negative Number: %f", negative_value);
  sprintf(original_buffer, "Negative Number: %f", negative_value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double value = 123.456;
  s21_sprintf(buffer, "Number: %.2f", value);
  sprintf(original_buffer, "Number: %.2f", value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_width_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double value = 123.456;
  s21_sprintf(buffer, "Number: %10f", value);
  sprintf(original_buffer, "Number: %10f", value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_width_precision_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double value = 123.456;
  s21_sprintf(buffer, "Number: %10.2f", value);
  sprintf(original_buffer, "Number: %10.2f", value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_positive_sign_flag) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double value = 123.456;
  s21_sprintf(buffer, "Number: %+f", value);
  sprintf(original_buffer, "Number: %+f", value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_negative_sign_flag) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double negative_value = -123.456;
  s21_sprintf(buffer, "Number: %+f", negative_value);
  sprintf(original_buffer, "Number: %+f", negative_value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_zero_padding) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double value = 123.456;
  s21_sprintf(buffer, "Number: %010f", value);
  sprintf(original_buffer, "Number: %010f", value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_left_alignment) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double value = 123.456;
  s21_sprintf(buffer, "Number: %-10f", value);
  sprintf(original_buffer, "Number: %-10f", value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_small_number) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double small_value = 0.000123;
  s21_sprintf(buffer, "Small Number: %f", small_value);
  sprintf(original_buffer, "Small Number: %f", small_value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_large_number) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};
  double large_value = 123456789.987654321;
  s21_sprintf(buffer, "Large Number: %.6f", large_value);
  sprintf(original_buffer, "Large Number: %.6f", large_value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Float: %.2f";
  int ret = sprintf(buffer, fmt, 3.14759);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 3.14759);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

TCase *tcase_s21_sprintf_f(void) {
  TCase *tc_core_f = tcase_create("Spec %f");

  tcase_add_test(tc_core_f, test_s21_sprintf_f_large_number);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_small_number);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_left_alignment);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_zero_padding);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_negative_sign_flag);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_positive_sign_flag);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_width_precision_format);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_width_format);
  tcase_add_test(tc_core_f, test_s21_sprintf_negative_f_format);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_float);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_precision_format);
  tcase_add_test(tc_core_f, test_s21_sprintf_ld_double_format);
  tcase_add_test(tc_core_f, test_s21_sprintf_f_precision_flag);
  return tc_core_f;
}