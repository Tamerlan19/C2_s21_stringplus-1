#include "../s21_string.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_s21_sprintf_basic_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Hello, World!";

  int ret = sprintf(buffer, "%s", fmt);
  int ret_s21 = s21_sprintf(buffer_s21, "%s", fmt);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %.3s";
  const char *str = "testing";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %10s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %10.3s";
  const char *str = "testing";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %-10s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_empty_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = "";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_null_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = NULL;
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_long_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %.10s";
  const char *str = "This is a very long string";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %010s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_exceed_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %5s";
  const char *str = "LongerString";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_hs_short_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short String: %hs";
  char short_str[6] = "Hello"; // Массив char вместо строки
  int ret = sprintf(buffer, fmt, short_str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, short_str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ls_wide_string) {
    setlocale(LC_ALL, "en_US.utf8");

    wchar_t buffer[1024];
    char buffer_s21[1024];
    wchar_t buffer_s21_wide[1024]; // Буфер для преобразования buffer_s21 в wide string

    const char *fmt_narrow = "Wide String: %ls";
    wchar_t fmt_wide[1024];
    mbstowcs(fmt_wide, fmt_narrow, strlen(fmt_narrow) + 1); // Конвертируем формат в wchar_t

    wchar_t wide_str[] = L"Привет"; // Строка широких символов

    int ret = swprintf(buffer, 1024, fmt_wide, wide_str); // Форматируем wide string
    s21_sprintf(buffer_s21, fmt_narrow, wide_str); // Форматируем с помощью s21_sprintf

    // Преобразуем buffer_s21 в wide string
    size_t converted = mbstowcs(buffer_s21_wide, buffer_s21, 1024);
if (converted == (size_t)-1) {
    printf("Ошибка преобразования buffer_s21 в wide string\n");
    ck_abort(); // Аборт теста с сообщением об ошибке
}

    // Проверяем длину строки
    ck_assert_int_eq(ret, wcslen(buffer));
    // Сравниваем wide строки
    ck_assert_int_eq(wcscmp(buffer, buffer_s21_wide), 0);
}
END_TEST

TCase *tcase_s21_sprintf_s(void) {
  TCase *tc_core_s = tcase_create("Spec %s");
  
  tcase_add_test(tc_core_s, test_s21_sprintf_basic_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_basic);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_precision);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_width);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_width_precision);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_left_alignment);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_empty_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_null_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_long_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_zero_padding);
  tcase_add_test(tc_core_s, test_s21_sprintf_s_exceed_width);
  tcase_add_test(tc_core_s, test_s21_sprintf_hs_short_string);
  tcase_add_test(tc_core_s, test_s21_sprintf_ls_wide_string);

  
  return tc_core_s;
}