#include "s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_basic_string) {
    char buffer[1024];
    s21_sprintf(buffer, "Hello, World!");
    ck_assert_str_eq(buffer, "Hello, World!");
}
END_TEST

START_TEST(test_int_format) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %d", 42);
    ck_assert_str_eq(buffer, "Number: 42");
}
END_TEST

START_TEST(test_width_flag) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %5d", 42);
    ck_assert_str_eq(buffer, "Number:    42");
}
END_TEST

START_TEST(test_precision_flag) {
    char buffer[1024];
    s21_sprintf(buffer, "Float: %.2f", 3.14159);
    ck_assert_str_eq(buffer, "Float: 3.14");
}
END_TEST

START_TEST(test_zero_padding) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %05d", 42);
    ck_assert_str_eq(buffer, "Number: 00042");
}
END_TEST

START_TEST(test_left_alignment) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %-5d", 42);
    ck_assert_str_eq(buffer, "Number: 42   ");
}
END_TEST


Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_basic_string);
    tcase_add_test(tc_core, test_int_format);
    tcase_add_test(tc_core, test_width_flag);
    tcase_add_test(tc_core, test_precision_flag);
    tcase_add_test(tc_core, test_zero_padding);
    tcase_add_test(tc_core, test_left_alignment);

  suite_add_tcase(s, tc_core);

  return s;
}
