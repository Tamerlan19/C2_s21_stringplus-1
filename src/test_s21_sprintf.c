#include "s21_string.h"
#include <check.h>
#include <stdio.h>
#include <string.h>

START_TEST(test_s21_sprintf_basic_string) {
  char buffer[1024];
  s21_sprintf(buffer, "Hello, World!");
  ck_assert_str_eq(buffer, "Hello, World!");
}
END_TEST

START_TEST(test_s21_sprintf_d_int_format) {
  char buffer[1024] = {0};
  s21_sprintf(buffer, "Number: %d", 42);
  ck_assert_str_eq(buffer, "Number: 42");
}
END_TEST

START_TEST(test_s21_sprintf_d_width_flag) {
  char buffer[1024];
  s21_sprintf(buffer, "Number: %5d", 42);
  ck_assert_str_eq(buffer, "Number:    42");
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_flag) {
  char buffer[1024];
  s21_sprintf(buffer, "Float: %.2f", 3.14159);
  ck_assert_str_eq(buffer, "Float: 3.14");
}
END_TEST

START_TEST(test_s21_sprintf_d_zero_padding) {
  char buffer[1024];
  s21_sprintf(buffer, "Number: %05d", 42);
  ck_assert_str_eq(buffer, "Number: 00042");
}
END_TEST

START_TEST(test_s21_sprintf_d_left_alignment) {
  char buffer[1024];
  s21_sprintf(buffer, "Number: %-5d", 42);
  ck_assert_str_eq(buffer, "Number: 42   ");
}
START_TEST(test_s21_sprintf_simple_char) {
  char buffer[256] = {0};
  s21_sprintf(buffer, "%c", 'A'); // Передаем буфер явно
  ck_assert_str_eq(buffer, "A");
}
END_TEST

// Тест 2: Ширина больше одного символа
START_TEST(test_s21_sprintf_width) {
  char buffer[256] = {0};
  s21_sprintf(buffer, "%5c", 'B'); // Передаем буфер явно
  ck_assert_str_eq(buffer, "    B");
}
END_TEST

// Тест 3: Левое выравнивание
START_TEST(test_s21_sprintf_left_align) {
  char buffer[256] = {0};
  s21_sprintf(buffer, "%-5c", 'C'); // Передаем буфер явно
  ck_assert_str_eq(buffer, "C    ");
}
END_TEST

// Тест 4: Заполнение нулями
START_TEST(test_s21_sprintf_zero_padding) {
  char buffer[256] = {0};
  s21_sprintf(buffer, "%05c", 'D'); // Передаем буфер явно
  ck_assert_str_eq(buffer, "0000D");
}
END_TEST

// Тест 5: Минимальная ширина равна единице
START_TEST(test_s21_sprintf_min_width_one) {
  char buffer[256] = {0};
  s21_sprintf(buffer, "%1c", 'E'); // Передаем буфер явно
  ck_assert_str_eq(buffer, "E");
}
END_TEST

// Тест 6: Отрицательная ширина (должна игнорироваться)
START_TEST(test_s21_sprintf_negative_width) {
  char buffer[256] = {0};
  s21_sprintf(buffer, "%-5c", 'F'); // Передаем буфер явно
  ck_assert_str_eq(buffer, "F    ");
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

tcase_add_test(tc_core, test_s21_sprintf_basic_string);
tcase_add_test(tc_core, test_s21_sprintf_d_int_format);
tcase_add_test(tc_core, test_s21_sprintf_d_int);
tcase_add_test(tc_core, test_s21_sprintf_d_left_alignment);
tcase_add_test(tc_core, test_s21_sprintf_d_width_flag);
tcase_add_test(tc_core,test_s21_sprintf_d_zero_padding);

tcase_add_test(tc_core, test_s21_sprintf_c_zero_padding);
tcase_add_test(tc_core, test_s21_sprintf_c_simple_char);
tcase_add_test(tc_core, test_s21_sprintf_c_width);
tcase_add_test(tc_core, test_s21_sprintf_c_left_align);
tcase_add_test(tc_core, test_s21_sprintf_c_zero_padding);
tcase_add_test(tc_core, test_s21_sprintf_c_min_width_one);
tcase_add_test(tc_core, test_s21_sprintf_c_negative_width);
tcase_add_test(tc_core, test_s21_sprintf_c_width);

tcase_add_test(tc_core, test_s21_sprintf_f_float);
tcase_add_test(tc_core, test_s21_sprintf_f_precision_flag);

tcase_add_test(tc_core, test_s21_sprintf_s_precision);
tcase_add_test(tc_core, test_s21_sprintf_s_basic);

tcase_add_test(tc_core, test_s21_sprintf_u_simple_number);
tcase_add_test(tc_core, test_s21_sprintf_u_with_width);
tcase_add_test(tc_core, test_s21_sprintf_u_with_precision);
tcase_add_test(tc_core, test_s21_sprintf_u_left_alignment);
tcase_add_test(tc_core, test_s21_sprintf_u_zero_padding);
tcase_add_test(tc_core, test_s21_sprintf_u_zero_with_zero_precision);
tcase_add_test(tc_core, test_s21_sprintf_u_complex_case);

  tcase_add_test(tc_core, test_precision_flag);
  tcase_add_test(tc_core, test_zero_padding);
  tcase_add_test(tc_core, test_left_alignment);
  tcase_add_test(tc_core, test_width_flag);
  tcase_add_test(tc_core, test_s21_sprintf_simple_char);
  tcase_add_test(tc_core, test_s21_sprintf_width);
  tcase_add_test(tc_core, test_s21_sprintf_left_align);
  tcase_add_test(tc_core, test_s21_sprintf_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_min_width_one);
  tcase_add_test(tc_core, test_s21_sprintf_negative_width);

  suite_add_tcase(s, tc_core);

  return s;
}
