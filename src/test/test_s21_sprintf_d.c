#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_d_int_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};

  s21_sprintf(buffer, "Number: %d", 42);
  sprintf(original_buffer, "Number: %d", 42);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_d_int) {
  char buffer[100];
  char buffer_s21[100];
  const char *fmt = "Number: %d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_d_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Number: %-5d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_hd_short_int_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};

  short int short_value = 32767; // Максимальное значение для short
  s21_sprintf(buffer, "Short Number: %hd", short_value);
  sprintf(original_buffer, "Short Number: %hd", short_value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_ld_long_int_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};

  long int long_value = 2147483647L; // Максимальное значение для long
  s21_sprintf(buffer, "Long Number: %ld", long_value);
  sprintf(original_buffer, "Long Number: %ld", long_value);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_negative_hd_short_int_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};

  short int negative_short = -32767;
  s21_sprintf(buffer, "Negative Short: %hd", negative_short);
  sprintf(original_buffer, "Negative Short: %hd", negative_short);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_negative_ld_long_int_format) {
  char buffer[1024] = {0};
  char original_buffer[1024] = {0};

  long int negative_long = -2147483647L;
  s21_sprintf(buffer, "Negative Long: %ld", negative_long);
  sprintf(original_buffer, "Negative Long: %ld", negative_long);
  ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_d_width_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Number: %5d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST
START_TEST(test_s21_sprintf_d_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Number: %05d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ld_long_int) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Int: %ld";
  long int long_value = 2147483647L; // Максимальное значение для long int
  int ret = sprintf(buffer, fmt, long_value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, long_value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST


TCase *tcase_s21_sprintf_d(void) {
  TCase *tc_core_d = tcase_create("Spec %d");

tcase_add_test(tc_core_d, test_s21_sprintf_d_int_format);
tcase_add_test(tc_core_d, test_s21_sprintf_d_int);
tcase_add_test(tc_core_d, test_s21_sprintf_d_left_alignment);
tcase_add_test(tc_core_d, test_s21_sprintf_d_width_flag);
tcase_add_test(tc_core_d, test_s21_sprintf_d_zero_padding);
tcase_add_test(tc_core_d, test_s21_sprintf_ld_long_int_format);
tcase_add_test(tc_core_d, test_s21_sprintf_negative_hd_short_int_format);
tcase_add_test(tc_core_d, test_s21_sprintf_hd_short_int_format);
tcase_add_test(tc_core_d, test_s21_sprintf_ld_long_int);
tcase_add_test(tc_core_d, test_s21_sprintf_negative_ld_long_int_format);

  return tc_core_d;
}