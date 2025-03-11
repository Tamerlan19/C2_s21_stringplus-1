#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_g_simple) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %g";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  
    // ck_assert_str_eq(fmt, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_g_width_precision_negative) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %14.3g";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_g_width_precision) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.2g";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_g_left_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.4564;
    const char *fmt = "Number: %-14.4g";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_g_positive) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.3g";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  START_TEST(test_s21_sprintf_g_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %014.3g";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_G_simple) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %G";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  
    // ck_assert_str_eq(fmt, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_G_width_precision_negative) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %14.3G";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_G_width_precision) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.3G";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_G_left_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = -123.456;
    const char *fmt = "Number: %-14.3G";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  
  START_TEST(test_s21_sprintf_G_positive) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %+14.3G";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  START_TEST(test_s21_sprintf_G_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    const char *fmt = "Number: %014.3G";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST

  START_TEST(test_s21_sprintf_G_minimal_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 0.0002324456;
    const char *fmt = "Number: %14.3G";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST

  //[ ]: не работает тест. Нужно починить.
  START_TEST(test_s21_sprintf_LG_large_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    long double value = 1.7976931348623157e+308L;
    const char *fmt = "Number: %014.3LG";
    s21_sprintf(buffer, fmt, value);
    sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
  }
  END_TEST
  

  TCase *tcase_s21_sprintf_g(void) {
    TCase *tc_core_g = tcase_create("Spec %g|%G");

    tcase_add_test(tc_core_g, test_s21_sprintf_g_simple);
    tcase_add_test(tc_core_g, test_s21_sprintf_g_left_padding);
    tcase_add_test(tc_core_g, test_s21_sprintf_g_width_precision);
    tcase_add_test(tc_core_g, test_s21_sprintf_g_width_precision_negative);
    tcase_add_test(tc_core_g, test_s21_sprintf_g_positive);
    tcase_add_test(tc_core_g, test_s21_sprintf_g_zero_padding);
    tcase_add_test(tc_core_g, test_s21_sprintf_G_simple);
    tcase_add_test(tc_core_g, test_s21_sprintf_G_left_padding);
    tcase_add_test(tc_core_g, test_s21_sprintf_G_width_precision);
    tcase_add_test(tc_core_g, test_s21_sprintf_G_width_precision_negative);
    tcase_add_test(tc_core_g, test_s21_sprintf_G_positive);
    tcase_add_test(tc_core_g, test_s21_sprintf_G_zero_padding);
    tcase_add_test(tc_core_g, test_s21_sprintf_G_minimal_zero_padding);
    tcase_add_test(tc_core_g, test_s21_sprintf_LG_large_zero_padding);
    return tc_core_g;
  }