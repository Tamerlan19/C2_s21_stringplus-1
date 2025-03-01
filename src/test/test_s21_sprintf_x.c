#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_x_simple) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned value = 12356879;
    const char *fmt = "Number: %x";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

START_TEST(test_s21_sprintf_x_width) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned value = 12356879;
    const char *fmt = "Number: %10x";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

START_TEST(test_s21_sprintf_x_width_precision) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned value = 12356879;
    const char *fmt = "Number: %10.5x";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

START_TEST(test_s21_sprintf_x_width_precision_minus) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned value = 123;
    const char *fmt = "Number: %-10.5x";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

  START_TEST(test_s21_sprintf_x_width_precision_plus) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned value = 123;
    const char *fmt = "Number: %+10.5x";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST


  START_TEST(test_s21_sprintf_x_width_precision_space) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned value = 123;
    const char *fmt = "Number: % 10.5x";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST
   
  START_TEST(test_s21_sprintf_x_width_precision_large) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned long value = 1235687999999999;
    const char *fmt = "Number: %20.5x";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST


  START_TEST(test_s21_sprintf_lx_width_precision_large) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned long value = 18446744073709551608UL;
    const char *fmt = "Number: %20.5lx";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

  START_TEST(test_s21_sprintf_lX_width_precision_large) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned long value = 18446744073709551608UL;
    const char *fmt = "Number: %20.5lX";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

  START_TEST(test_s21_sprintf_lX_width_precision_neg) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned long value = -1235;
    const char *fmt = "Number: %20.5lX";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

  START_TEST(test_s21_sprintf_lX_width_precision_zero) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned long value = 0;
    const char *fmt = "Number: %20.5lX";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

  START_TEST(test_s21_sprintf_lX_width_precision_zero2) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    unsigned long value = 0;
    const char *fmt = "Number: %20.0lX";
    int ret_s21 = s21_sprintf(buffer, fmt, value);
    int ret     = sprintf(original_buffer, fmt, value);
    ck_assert_str_eq(buffer, original_buffer);
    ck_assert_int_eq(ret_s21, ret);
  }
  END_TEST

  TCase *tcase_s21_sprintf_x(void) {
    TCase *tc_core_x = tcase_create("Spec %e|%E");

    tcase_add_test(tc_core_x, test_s21_sprintf_x_simple);
    tcase_add_test(tc_core_x, test_s21_sprintf_x_width);
    tcase_add_test(tc_core_x, test_s21_sprintf_x_width_precision);
    tcase_add_test(tc_core_x, test_s21_sprintf_x_width_precision_minus);
    tcase_add_test(tc_core_x, test_s21_sprintf_x_width_precision_plus);
    tcase_add_test(tc_core_x, test_s21_sprintf_x_width_precision_space);
    tcase_add_test(tc_core_x, test_s21_sprintf_x_width_precision_large);
    tcase_add_test(tc_core_x, test_s21_sprintf_lx_width_precision_large);
    tcase_add_test(tc_core_x, test_s21_sprintf_lX_width_precision_large);
    tcase_add_test(tc_core_x, test_s21_sprintf_lX_width_precision_neg);
    tcase_add_test(tc_core_x, test_s21_sprintf_lX_width_precision_zero);
    tcase_add_test(tc_core_x, test_s21_sprintf_lX_width_precision_zero2);


    return tc_core_x;
  }