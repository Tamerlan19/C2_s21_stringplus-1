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

START_TEST(test_s21_sprintf_Lf_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %Lf";
  long double value = 3.141592653589793238L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %.10Lf";
  long double value = 3.141592653589793238L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %20Lf";
  long double value = 2.718281828459045235L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %-20Lf";
  long double value = 2.718281828459045235L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_plus_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %+Lf";
  long double value = 2.718281828459045235L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %015Lf";
  long double value = 1.618033988749894848L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_scientific_notation) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %Le";
  long double value = 123456789.0123456789L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_width_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %15.5Lf";
  long double value = -1.414213562373095048L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_str_eq(buffer, buffer_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_large_number) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %Lf";
  long double value = 1.7976931348623157e+37L; // Очень большое число
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_str_eq(buffer, buffer_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_negative_number) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %Lf";
  long double value = -0.0000000000000000000000000000001L;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_dynamic_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %.*Lf";
  long double value = 3.141592653589793238L;
  int precision = 10;
  int ret = sprintf(buffer, fmt, precision, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, precision, value);
  ck_assert_str_eq(buffer, buffer_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sprintf_Lf_dynamic_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Double: %*Lf";
  long double value = 2.718281828459045235L;
  int width = 20;
  int ret = sprintf(buffer, fmt, width, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, width, value);
  ck_assert_str_eq(buffer, buffer_s21);
  ck_assert_int_eq(ret, ret_s21);
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

  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_basic);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_precision);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_width);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_left_alignment);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_plus_flag);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_zero_padding);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_scientific_notation);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_width_precision);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_large_number);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_negative_number);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_dynamic_precision);
  tcase_add_test(tc_core_f, test_s21_sprintf_Lf_dynamic_width);

  return tc_core_f;
}