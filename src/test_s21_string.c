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

int compare_memory(const void *a, const void *b, s21_size_t n) {
    return memcmp(a, b, n) == 0;
}

// Тестовый случай 1: Заполнение нулями
START_TEST(test_s21_memset_zero_fill) {
    char buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    s21_memset(buffer, 0, 10);

    char expected[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ck_assert(s21_memcmp(buffer, expected, 10) == 1);
}
END_TEST

// Тестовый случай 2: Частичное заполнение
START_TEST(test_s21_memset_partial_fill) {
    char buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    s21_memset(buffer, 'A', 5);

    char expected[10] = {'A', 'A', 'A', 'A', 'A', 6, 7, 8, 9, 10};
    ck_assert(compare_memory(buffer, expected, 10) == 1);
}
END_TEST

// Тестовый случай 3: Заполнение символом
START_TEST(test_s21_memset_char_fill) {
    char buffer[10];
    s21_memset(buffer, 'X', 10);

    char expected[10] = {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};
    ck_assert(compare_memory(buffer, expected, 10) == 1);
}
END_TEST

// Тестовый случай 4: Нулевая длина
START_TEST(test_s21_memset_zero_length) {
    char buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    s21_memset(buffer, 'A', 0);

    char expected[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ck_assert(compare_memory(buffer, expected, 10) == 1);
}
END_TEST

// Тестовый случай 5: NULL-указатель
START_TEST(test_s21_memset_null_pointer) {
    char *buffer = NULL;
    s21_memset(buffer, 'A', 10); // Функция должна безопасно обрабатывать NULL

    // Проверяем, что программа не завершилась с ошибкой
    ck_assert_ptr_eq(buffer, NULL);
}
END_TEST


// Test Case 1: Identical memory blocks
START_TEST(test_s21_memcmp_identical_blocks) {
    char buffer1[] = "abcdef";
    char buffer2[] = "abcdef";
    s21_size_t n = 6;

    int result = s21_memcmp(buffer1, buffer2, n);
    ck_assert_int_eq(result, 0); // Expected result is 0 (equal)
}
END_TEST

// Test Case 2: Different memory blocks
START_TEST(test_s21_memcmp_different_blocks) {
    char buffer1[] = "abcde";
    char buffer2[] = "abcdz";
    s21_size_t n = 5;

    int result = s21_memcmp(buffer1, buffer2, n);
    ck_assert_int_lt(result, 0); // 'e' < 'z', so result should be negative
}
END_TEST

// Test Case 3: Partial comparison with identical bytes
START_TEST(test_s21_memcmp_partial_identical) {
    char buffer1[] = "abcdefgh";
    char buffer2[] = "abcdefxy";
    s21_size_t n = 6;

    int result = s21_memcmp(buffer1, buffer2, n);
    ck_assert_int_eq(result, 0); // First 6 bytes are identical
}
END_TEST

// Test Case 4: Partial comparison with different bytes
START_TEST(test_s21_memcmp_partial_different) {
    char buffer1[] = "abcdefg";
    char buffer2[] = "abcdefh";
    s21_size_t n = 7;

    int result = s21_memcmp(buffer1, buffer2, n);
    ck_assert_int_lt(result, 0); // 'g' < 'h', so result should be negative
}
END_TEST

// Test Case 5: Comparison with n = 0
START_TEST(test_s21_memcmp_zero_length) {
    char buffer1[] = "abcdef";
    char buffer2[] = "ABCDEF";
    s21_size_t n = 0;

    int result = s21_memcmp(buffer1, buffer2, n);
    ck_assert_int_eq(result, 0); // If n == 0, result should always be 0
}
END_TEST

// Test Case 6: NULL pointers
START_TEST(test_s21_memcmp_null_pointers) {
    char buffer1[] = "abcdef";
    const void *null_ptr = NULL;
    s21_size_t n = 6;

    int result = s21_memcmp(null_ptr, buffer1, n);
    ck_assert_int_eq(result, 0); // Function should handle NULL safely
}
END_TEST

START_TEST(test_s21_strncpy_short_src) {
    char dest[50] = "Original";
    const char *src = "Short";
    s21_size_t n = 10;

    s21_strncpy(dest, src, n);

    // Сравниваем результат с ожидаемым значением
    char expected[50] = "Short\0\0\0\0\0"; // Ожидаемая строка
    ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncpy_long_src) {
    char dest[50] = "";
    const char *src = "ThisIsALongString";
    s21_size_t n = 5;

    s21_strncpy(dest, src, n);

    // Сравниваем результат с ожидаемым значением
    char expected[50] = "ThisI"; // Ожидаемая строка (без завершающего \0)
    ck_assert_str_eq(dest, expected); // Проверяем первые n символов
}
END_TEST

// Тест: копирование с n = 0 (ничего не должно измениться)
START_TEST(test_s21_strncpy_n_zero) {
    char dest[50] = "Test";
    const char *src = "New";
    s21_size_t n = 0;

    s21_strncpy(dest, src, n);
    ck_assert_str_eq(dest, "Test");
}
END_TEST

// Тест: копирование пустой строки
START_TEST(test_s21_strncpy_empty_src) {
    char dest[50] = "Original";
    const char *src = "";
    s21_size_t n = 5;

    s21_strncpy(dest, src, n);
    ck_assert_str_eq(dest, "\0\0\0\0\0iginal");
}
END_TEST

// Тест: проверка NULL-указателей
START_TEST(test_s21_strncpy_null_pointers) {
    char dest[50] = "Original";
    const char *src = NULL;
    s21_size_t n = 5;

    s21_strncpy(dest, src, n); // Функция должна вернуть dest без изменений
    ck_assert_str_eq(dest, "Original");
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_string");
  tc_core = tcase_create("Core");
  // tc_sprintf = tcase_create("sprintf");
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

  tcase_add_test(tc_core, test_s21_memset_zero_fill);
  tcase_add_test(tc_core, test_s21_memset_partial_fill);
  tcase_add_test(tc_core, test_s21_memset_char_fill);
  tcase_add_test(tc_core, test_s21_memset_zero_length);
  tcase_add_test(tc_core, test_s21_memset_null_pointer);

  tcase_add_test(tc_core, test_s21_memcmp_identical_blocks);
  tcase_add_test(tc_core, test_s21_memcmp_different_blocks);
  tcase_add_test(tc_core, test_s21_memcmp_partial_identical);
  tcase_add_test(tc_core, test_s21_memcmp_partial_different);
  tcase_add_test(tc_core, test_s21_memcmp_zero_length);
  tcase_add_test(tc_core, test_s21_memcmp_null_pointers);
  tcase_add_test(tc_core, test_s21_strncpy_short_src);
  tcase_add_test(tc_core, test_s21_strncpy_long_src);
  tcase_add_test(tc_core, test_s21_strncpy_n_zero);
  tcase_add_test(tc_core, test_s21_strncpy_empty_src);
  tcase_add_test(tc_core, test_s21_strncpy_null_pointers);
  // tcase_add_test(tc_sprintf, test_s21_sprintf_c);

  suite_add_tcase(s, tc_core);

  return s;
}
