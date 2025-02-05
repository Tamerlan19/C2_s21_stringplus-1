#include "s21_string.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(test_s21_strchr_found) {
  const char *str = "Hello, World!";
  int ch = 'o';
  char *result = s21_strchr(str, ch);
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_str_eq(result,
                   "o, World!"); // Проверяем, что найдено правильное вхождение
}
END_TEST

START_TEST(test_s21_strchr_not_found) {
  const char *str = "Hello, World!";
  int ch = 'z';
  const char *result = s21_strchr(str, ch);
  ck_assert_ptr_null(result); // Ожидаем NULL, так как символ не найден
}
END_TEST

START_TEST(test_s21_strchr_null_terminator) {
  const char *str = "Hello, World!";
  int ch = '\0';
  const char *result = s21_strchr(str, ch);
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_str_eq(result,
                   ""); // Проверяем, что найдено вхождение нулевого символа
}
END_TEST

START_TEST(test_s21_strchr_empty_string) {
  const char *str = "";
  int ch = 'a';
  const char *result = s21_strchr(str, ch);
  ck_assert_ptr_null(result); // Ожидаем NULL, так как строка пуста
}
END_TEST

START_TEST(test_s21_strchr_first_char) {
  const char *str = "Hello, World!";
  int ch = 'H';
  const char *result = s21_strchr(str, ch);
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_str_eq(result,
                   "Hello, World!"); // Проверяем, что найдено первое вхождение
}
END_TEST

START_TEST(test_s21_strchr_last_char) {
  const char *str = "Hello, World!";
  int ch = '!';
  const char *result = s21_strchr(str, ch);
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_str_eq(result, "!"); // Проверяем, что найдено последнее вхождение
}
END_TEST

START_TEST(test_s21_strlen) {
  ck_assert_int_eq(s21_strlen("Hello"), 5);
  ck_assert_int_eq(s21_strlen(""), 0);
  ck_assert_int_eq(s21_strlen("0987654321"), 10);
  ck_assert_int_eq(s21_strlen("\n"), strlen("\n"));
  ck_assert_int_eq(s21_strlen("\0"), strlen("\0"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(
      s21_strlen(
          "                                                              "),
      strlen("                                                              "));
  const char *str;

  str = "";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));

  str = "Hello, World!";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));

  str = "A";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));

  str = "   ";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));

  str = "\t\n\r";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));

  str = "Hello\0World";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));

  // Very long string with many characters.";
  unsigned int size = 42949672;       // 4294967295
  char *l_str = (char *)malloc(size); // Выделяем память в куче
  if (l_str == NULL) {
    perror("Failed to allocate memory");
  } else {
    memset(l_str, 'A', size - 1); // Заполняем буфер символами 'A'
    l_str[size - 1] = '\0'; // Добавляем завершающий нулевой символ
    ck_assert_uint_eq(s21_strlen(l_str), strlen(l_str));
    free(l_str);
  }
}
END_TEST

START_TEST(test_s21_strncmp) {
  // Сценарий 1: Сравнение одинаковых строк
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));

  str1 = "Hello";
  str2 = "World";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));

  str1 = "World";
  str2 = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));

  str1 = "Hello";
  str2 = "Hell";
  ck_assert_int_eq(s21_strncmp(str1, str2, 4), strncmp(str1, str2, 4));

  str1 = "Hello";
  str2 = "World";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));

  str1 = "Hello";
  str2 = "Hell";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));

  str1 = "";
  str2 = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));

  str1 = "hello";
  str2 = "HELLO";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_s21_strcmp) {
  ck_assert_int_eq(s21_strcmp("Hello world", "Hello world"),
                   strcmp("Hello world", "Hello world"));
  ck_assert_int_eq(s21_strcmp("", "123"), strcmp("", "123"));
  ck_assert_int_eq(s21_strcmp("123", ""), strcmp("123", ""));
  ck_assert_int_eq(s21_strcmp("\n", "\r"), strcmp("\n", "\r"));
  ck_assert_int_eq(s21_strcmp("", ""), strcmp("", ""));
  ck_assert_int_eq(s21_strcmp("", "NULL"), strcmp("", "NULL"));
  ck_assert_int_eq(s21_strcmp("\n", "\n"), strcmp("\n", "\n"));
}
END_TEST

START_TEST(test_s21_sprintf_c) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  int x6 = 12345;
  char *format_string3 = "%+.*d\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string3, 8, 4, x6),
                   sprintf(buff, format_string3, 8, 4, x6));
  ck_assert_str_eq(buff, s21_buff);

  short x7 = -32768;
  char *format_string4 = "%hd\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string4, x7),
                   sprintf(buff, format_string4, x7));
  ck_assert_str_eq(buff, s21_buff);

  float x8 = 123.456;
  char *format_string5 = "% 010.2f\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string5, x8),
                   sprintf(buff, format_string5, x8));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_sprintf;

  s = suite_create("s21_string");
  tc_core = tcase_create("Core");
  tc_sprintf = tcase_create("sprintf");
  // tc_sscanf = tcase_create("sscanf");

  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strcmp);
  tcase_add_test(tc_core, test_s21_strchr_found);
  tcase_add_test(tc_core, test_s21_strchr_not_found);
  tcase_add_test(tc_core, test_s21_strchr_null_terminator);
  tcase_add_test(tc_core, test_s21_strchr_empty_string);
  tcase_add_test(tc_core, test_s21_strchr_first_char);
  tcase_add_test(tc_core, test_s21_strchr_last_char);

  tcase_add_test(tc_sprintf, test_s21_sprintf_c);

  suite_add_tcase(s, tc_core);
  // suite_add_tcase(s, tc_sprintf);
  // suite_add_tcase(s, tc_sscanf);

  return s;
}
