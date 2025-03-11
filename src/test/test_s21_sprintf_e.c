#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_e_simple) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %e";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  
    // ck_assert_str_eq(fmt, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_e_width_precision_negative) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %14.3e";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_e_width_precision) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.3e";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_e_left_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %-14.3e";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_e_positive) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.3e";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  START_TEST(test_s21_sprintf_e_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %014.3e";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_E_simple) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %E";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  
    // ck_assert_str_eq(fmt, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_E_width_precision_negative) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %14.3E";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_E_width_precision) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.3E";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_E_left_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %-14.3E";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_E_positive) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.3E";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  START_TEST(test_s21_sprintf_E_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %014.3E";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST

  START_TEST(test_s21_sprintf_E_minimal_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 0.0002324456;
    const char *fmt = "Number: %014.3E";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST

  START_TEST(test_s21_sprintf_LE_large_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    long double value = 1.7976931348623157e+308L;
    const char *fmt = "Number: %014.3LE";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  

TCase *tcase_s21_sprintf_e(void) {
  TCase *tc_core_e = tcase_create("Spec %e|%E");

  tcase_add_test(tc_core_e, test_s21_sprintf_e_simple);
  tcase_add_test(tc_core_e, test_s21_sprintf_e_left_padding);
  tcase_add_test(tc_core_e, test_s21_sprintf_e_width_precision);
  tcase_add_test(tc_core_e, test_s21_sprintf_e_width_precision_negative);
  tcase_add_test(tc_core_e, test_s21_sprintf_e_positive);
  tcase_add_test(tc_core_e, test_s21_sprintf_e_zero_padding);
  tcase_add_test(tc_core_e, test_s21_sprintf_E_minimal_zero_padding);
  tcase_add_test(tc_core_e, test_s21_sprintf_LE_large_zero_padding);
  tcase_add_test(tc_core_e, test_s21_sprintf_E_zero_padding);
  tcase_add_test(tc_core_e, test_s21_sprintf_E_positive);
  tcase_add_test(tc_core_e, test_s21_sprintf_E_left_padding);
  tcase_add_test(tc_core_e, test_s21_sprintf_E_width_precision);
  tcase_add_test(tc_core_e, test_s21_sprintf_E_width_precision_negative);
  tcase_add_test(tc_core_e, test_s21_sprintf_E_simple);
  return tc_core_e;
}