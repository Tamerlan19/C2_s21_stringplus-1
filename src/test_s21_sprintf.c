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
  char buffer[1024] = {0};
  s21_sprintf(buffer, "Number: %d", 42);
  ck_assert_str_eq(buffer, "Number: 42");
}
END_TEST

START_TEST(test_width_flag) {
  // DEBUG_PRINT("\ntest_width_flag\n");
  char buffer[1024];
  s21_sprintf(buffer, "Number: %5d", 42);
  DEBUG_PRINT("buffer = |%s|\n", buffer);
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

START_TEST(test_s21_sprintf_basic) {
    char buffer[100];
    s21_sprintf(buffer, "Hello, %s!", "world");
    ck_assert_str_eq(buffer, "Hello, world!");
}
END_TEST

START_TEST(test_s21_sprintf_int) {
    char buffer[100];
    s21_sprintf(buffer, "Number: %d", 42);
    ck_assert_str_eq(buffer, "Number: 42");
}
END_TEST

START_TEST(test_s21_sprintf_float) {
    char buffer[100];
    s21_sprintf(buffer, "Float: %.2f", 3.14159);
    ck_assert_str_eq(buffer, "Float: 3.14");
}
END_TEST

START_TEST(test_s21_sprintf_precision) {
    char buffer[100];
    s21_sprintf(buffer, "%.3s", "testing");
    ck_assert_str_eq(buffer, "tes");
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_basic_string);
  tcase_add_test(tc_core, test_int_format);

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

  tcase_add_test(tc_core, test_s21_sprintf_basic);
  tcase_add_test(tc_core, test_s21_sprintf_int);
  tcase_add_test(tc_core, test_s21_sprintf_float);
  tcase_add_test(tc_core, test_s21_sprintf_width);
  tcase_add_test(tc_core, test_s21_sprintf_precision);

  suite_add_tcase(s, tc_core);

  return s;
}
