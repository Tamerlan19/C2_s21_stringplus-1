#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s21_string.h"

START_TEST(test_s21_strchr_found) {
  const char *str = "Hello, World!";
  int ch = 'o';
  char *result = s21_strchr(str, ch);
  char *expected = strchr(str, ch); // Вызов оригинальной функции
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_ptr_eq(result, expected); // Сравниваем указатели
  ck_assert_str_eq(result,
                   "o, World!"); // Проверяем, что найдено правильное вхождение
}
END_TEST

START_TEST(test_s21_strchr_not_found) {
  const char *str = "Hello, World!";
  int ch = 'z';
  const char *result = s21_strchr(str, ch);
  const char *expected = strchr(str, ch); // Вызов оригинальной функции
  ck_assert_ptr_null(result); // Ожидаем NULL, так как символ не найден
  ck_assert_ptr_eq(result, expected); // Сравниваем указатели
}
END_TEST

START_TEST(test_s21_strchr_null_terminator) {
  const char *str = "Hello, World!";
  int ch = '\0';
  const char *result = s21_strchr(str, ch);
  const char *expected = strchr(str, ch); // Вызов оригинальной функции
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_ptr_eq(result, expected); // Сравниваем указатели
  ck_assert_str_eq(result,
                   ""); // Проверяем, что найдено вхождение нулевого символа
}
END_TEST

START_TEST(test_s21_strchr_empty_string) {
  const char *str = "";
  int ch = 'a';
  const char *result = s21_strchr(str, ch);
  const char *expected = strchr(str, ch); // Вызов оригинальной функции
  ck_assert_ptr_null(result); // Ожидаем NULL, так как строка пуста
  ck_assert_ptr_null(expected); // Ожидаем NULL, так как строка пуста
}
END_TEST

START_TEST(test_s21_strchr_first_char) {
  const char *str = "Hello, World!";
  int ch = 'H';
  const char *result = s21_strchr(str, ch);
  const char *expected = strchr(str, ch); // Вызов оригинальной функции
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_ptr_eq(result, expected); // Сравниваем указатели
  ck_assert_str_eq(result,
                   "Hello, World!"); // Проверяем, что найдено первое вхождение
}
END_TEST

START_TEST(test_s21_strchr_last_char) {
  const char *str = "Hello, World!";
  int ch = '!';
  const char *result = s21_strchr(str, ch);
  const char *expected = strchr(str, ch); // Вызов оригинальной функции
  ck_assert_ptr_nonnull(result); // Убедимся, что результат не NULL
  ck_assert_ptr_eq(result, expected); // Сравниваем указатели
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

START_TEST(test_s21_strncmp2) {
  ck_assert_int_eq(s21_strncmp("Hello world", "Hello world", 10),
                   strncmp("Hello world", "Hello world", 10));
  ck_assert_int_eq(s21_strncmp("", "123", 5), strncmp("", "123", 5));
  ck_assert_int_eq(s21_strncmp("123", "", 2), strncmp("123", "", 2));
  ck_assert_int_eq(s21_strncmp("\n", "\r", 3), strncmp("\n", "\r", 3));
  ck_assert_int_eq(s21_strncmp("", "", 1), strncmp("", "", 1));
  ck_assert_int_eq(s21_strncmp("", "NULL", 10), strncmp("", "NULL", 10));
  ck_assert_int_eq(s21_strncmp("\n", "\n", 10), strncmp("\n", "\n", 10));
}
END_TEST

int compare_memory(const void *a, const void *b, s21_size_t n) {
  return memcmp(a, b, n) == 0;
}

// Тестовый случай 1: Заполнение нулями
START_TEST(test_s21_memset_zero_fill) {
  char buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  char expected[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Вызов s21_memset и оригинальной memset
  s21_memset(buffer, 0, 10);
  memset(expected, 0, 10);

  // Сравнение результатов
  ck_assert(compare_memory(buffer, expected, 10));
}
END_TEST

// Тестовый случай 2: Частичное заполнение
START_TEST(test_s21_memset_partial_fill) {
  char buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  char expected[10] = {'A', 'A', 'A', 'A', 'A', 6, 7, 8, 9, 10};

  // Вызов s21_memset и оригинальной memset
  s21_memset(buffer, 'A', 5);
  memset(expected, 'A', 5);

  // Сравнение результатов
  ck_assert(compare_memory(buffer, expected, 10));
}
END_TEST

// Тестовый случай 3: Заполнение символом
START_TEST(test_s21_memset_char_fill) {
  char buffer[10];
  char expected[10];

  // Вызов s21_memset и оригинальной memset
  s21_memset(buffer, 'X', 10);
  memset(expected, 'X', 10);

  // Сравнение результатов
  ck_assert(compare_memory(buffer, expected, 10));
}
END_TEST

// Тестовый случай 4: Нулевая длина
START_TEST(test_s21_memset_zero_length) {
  char buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  char expected[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int len = 0;

  // Вызов s21_memset и оригинальной memset
  s21_memset(buffer, 'A', len);
  memset(expected, 'A', len);

  // Сравнение результатов
  ck_assert(compare_memory(buffer, expected, 10));
}
END_TEST

START_TEST(test_s21_memset_large_block) {
  const size_t size = 1024 * 1024; // 1 МБ
  char *buffer = malloc(size);
  char *expected = malloc(size);

  // Заполняем память с помощью s21_memset и оригинальной memset
  s21_memset(buffer, 'X', size);
  memset(expected, 'X', size);

  // Сравнение результатов
  ck_assert(compare_memory(buffer, expected, size));

  free(buffer);
  free(expected);
}
END_TEST
START_TEST(test_s21_memset_negative_value) {
  char buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  char expected[10];

  // Заполняем память с помощью s21_memset и оригинальной memset
  s21_memset(buffer, -1, 10);
  memset(expected, -1, 10);

  // Сравнение результатов
  ck_assert(compare_memory(buffer, expected, 10));
}
END_TEST
START_TEST(test_s21_memset_null_pointer_zero_length) {
  char *buffer = NULL;
  int len = 0;

  // Вызов s21_memset и оригинальной memset
  s21_memset(buffer, 'A', len); // Ожидаем, что функция не упадёт
  memset(buffer, 'A', len); // Оригинальная функция также не упадёт

  // Проверяем, что программа не завершилась с ошибкой
  ck_assert_ptr_eq(buffer, NULL);
}
END_TEST
START_TEST(test_s21_memset_overlap) {
  char buffer[20] = "Hello, World!";
  char expected[20] = "Hello, World!";

  // Заполняем память с помощью s21_memset и оригинальной memset
  s21_memset(buffer + 5, 'X', 5);
  memset(expected + 5, 'X', 5);

  // Сравнение результатов
  ck_assert(compare_memory(buffer, expected, 20));
}
END_TEST

START_TEST(test_s21_memcmp_identical_blocks) {
  const char buffer1[] = "abcdef";
  const char buffer2[] = "abcdef";
  s21_size_t n = 6;

  int result = s21_memcmp(buffer1, buffer2, n);
  int expected = memcmp(buffer1, buffer2, n); // Вызов оригинальной функции
  ck_assert_int_eq(result, expected); // Ожидаем 0 (блоки идентичны)
}
END_TEST

// Тестовый случай 2: Разные блоки памяти
START_TEST(test_s21_memcmp_different_blocks) {
  const char buffer1[] = "abcde";
  const char buffer2[] = "abcdz";
  s21_size_t n = 5;

  int result = s21_memcmp(buffer1, buffer2, n);
  int expected = memcmp(buffer1, buffer2, n); // Вызов оригинальной функции
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тестовый случай 3: Частичное сравнение с идентичными байтами
START_TEST(test_s21_memcmp_partial_identical) {
  const char buffer1[] = "abcdefgh";
  const char buffer2[] = "abcdefxy";
  s21_size_t n = 6;

  int result = s21_memcmp(buffer1, buffer2, n);
  int expected = memcmp(buffer1, buffer2, n);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тестовый случай 4: Частичное сравнение с разными байтами
START_TEST(test_s21_memcmp_partial_different) {
  const char buffer1[] = "abcdefg";
  const char buffer2[] = "abcdefh";
  s21_size_t n = 7;

  int result = s21_memcmp(buffer1, buffer2, n);
  int expected = memcmp(buffer1, buffer2, n);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тестовый случай 5: Сравнение с n = 0
START_TEST(test_s21_memcmp_zero_length) {
  const char buffer1[] = "abcdef";
  const char buffer2[] = "ABCDEF";
  s21_size_t n = 0;

  int result = s21_memcmp(buffer1, buffer2, n);
  int expected = memcmp(buffer1, buffer2, n); // Вызов оригинальной функции
  ck_assert_int_eq(result, expected); // Ожидаем 0 (n == 0)
}
END_TEST

START_TEST(test_s21_memcmp_negative_values) {
  const char buffer1[] = {1, 2, -3, 4, 5};
  const char buffer2[] = {1, 2, -2, 4, 5};
  s21_size_t n = 5;

  int result = s21_memcmp(buffer1, buffer2, n);
  int expected = memcmp(buffer1, buffer2, n); // Вызов оригинальной функции
  ck_assert_int_eq(result,
                   expected); // Ожидаем отрицательное значение (-3 < -2)
}
END_TEST
START_TEST(test_s21_memcmp_overlap) {
  char buffer[] = "abcdefgh";
  s21_size_t n = 4;

  int result = s21_memcmp(buffer, buffer + 2, n);
  int expected = memcmp(buffer, buffer + 2, n); // Вызов оригинальной функции
  ck_assert_int_eq(result,
                   expected); // Ожидаем отрицательное значение ('a' < 'c')
}
END_TEST
START_TEST(test_s21_memcmp_large_blocks) {
  const size_t size = 1024 * 1024; // 1 МБ
  char *buffer1 = malloc(size);
  char *buffer2 = malloc(size);

  // Заполняем память одинаковыми значениями
  memset(buffer1, 'A', size);
  memset(buffer2, 'A', size);

  int result = s21_memcmp(buffer1, buffer2, size);
  int expected = memcmp(buffer1, buffer2, size); // Вызов оригинальной функции
  ck_assert_int_eq(result, expected); // Ожидаем 0 (блоки идентичны)

  free(buffer1);
  free(buffer2);
}
END_TEST
START_TEST(test_s21_memcmp_case_sensitive) {
  const char buffer1[] = "abcdef";
  const char buffer2[] = "ABCDEF";
  s21_size_t n = 6;

  int result = s21_memcmp(buffer1, buffer2, n);
  int expected = memcmp(buffer1, buffer2, n); // Вызов оригинальной функции
  ck_assert_int_eq(result,
                   expected); // Ожидаем положительное значение ('a' > 'A')
}
END_TEST

// Тест: конкатенация двух строк
START_TEST(test_s21_strncat_basic_concatenation) {
  char dest[50] = "Hello, ";
  const char *src = "World!";
  s21_size_t n = 6;

  // Вызываем оригинальную функцию для получения эталонного результата
  char original_dest[50] = "Hello, ";
  strncat(original_dest, src, n);

  // Вызываем свою функцию
  s21_strncat(dest, src, n);

  // Сравниваем результаты
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

// Тест: копирование части строки из src
START_TEST(test_s21_strncat_partial_concatenation) {
  char dest[50] = "Hello, ";
  const char *src = "World!";
  s21_size_t n = 5;

  // Вызываем оригинальную функцию для получения эталонного результата
  char original_dest[50] = "Hello, ";
  strncat(original_dest, src, n);

  // Вызываем свою функцию
  s21_strncat(dest, src, n);

  // Сравниваем результаты
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

// Тест: копирование пустой строки
START_TEST(test_s21_strncat_empty_src) {
  char dest[50] = "Hello, ";
  const char *src = "";
  s21_size_t n = 10;

  // Вызываем оригинальную функцию для получения эталонного результата
  char original_dest[50] = "Hello, ";
  strncat(original_dest, src, n);

  // Вызываем свою функцию
  s21_strncat(dest, src, n);

  // Сравниваем результаты
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

// Тест: копирование при n = 0
START_TEST(test_s21_strncat_n_zero) {
  char dest[50] = "Hello, ";
  const char *src = "World!";
  s21_size_t n = 0;

  // Вызываем оригинальную функцию для получения эталонного результата
  char original_dest[50] = "Hello, ";
  strncat(original_dest, src, n);

  // Вызываем свою функцию
  s21_strncat(dest, src, n);

  // Сравниваем результаты
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

// Тест: проверка NULL-указателей
START_TEST(test_s21_strncat_null_pointers) {
  char dest[50] = "Hello, ";
  const char *src = NULL;
  s21_size_t n = 5;

  // Оригинальная функция не поддерживает NULL-указатели, поэтому ожидаем, что
  // наша функция также ведет себя корректно
  if (src == NULL) {
    ck_assert_str_eq(dest, "Hello, "); // Должно остаться без изменений
  } else {
    // Если src не NULL, используем оригинальную функцию для сравнения
    char original_dest[50] = "Hello, ";
    strncat(original_dest, src, n);

    s21_strncat(dest, src, n);
    ck_assert_str_eq(dest, original_dest);
  }
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest1[100] = "Hello, ";
  char dest2[100] = "Hello, ";
  const char src[] = "World!";
  size_t n = 5;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  char dest1[100] = "";
  char dest2[100] = "";
  const char src[] = "World!";
  size_t n = 5;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_strncat_zero_n) {
  char dest1[100] = "Hello, ";
  char dest2[100] = "Hello, ";
  const char src[] = "World!";
  size_t n = 0;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_strncat_large_n) {
  char dest1[100] = "Hello, ";
  char dest2[100] = "Hello, ";
  const char src[] = "World!";
  size_t n = 100;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_strncpy_short_src) {
  char dest[50] = "Original";
  const char *src = "Short";
  s21_size_t n = 10;

  // Вызываем оригинальную функцию для получения эталонного результата
  char original_dest[50] = "Original";
  strncpy(original_dest, src, n);
  original_dest[n - 1] = '\0'; // Гарантируем завершающий нуль

  // Вызываем свою функцию
  s21_strncpy(dest, src, n);

  // Сравниваем результаты
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

// Тест: Длинный источник (src)
START_TEST(test_s21_strncpy_long_src) {
  char dest[50] = "";
  const char *src = "ThisIsALongString";
  s21_size_t n = 5;

  // Вызываем оригинальную функцию для получения эталонного результата
  char original_dest[50] = "";
  strncpy(original_dest, src, n);
  original_dest[n] = '\0'; // Гарантируем завершающий нуль

  // Вызываем свою функцию
  s21_strncpy(dest, src, n);

  // Сравниваем результаты
  ck_assert_str_eq(dest, original_dest);
}
END_TEST

// Тест: Копирование с n = 0 (ничего не должно измениться)
START_TEST(test_s21_strncpy_n_zero) {
  char dest[50] = "Test";
  const char *src = "New";
  s21_size_t n = 0;

  // Вызываем оригинальную функцию для получения эталонного результата
  char original_dest[50] = "Test";
  char *ret = strncpy(original_dest, src, n);
  char *ret_s21 = s21_strncpy(dest, src, n);

  // Сравниваем результаты
  ck_assert_str_eq(dest, original_dest);
  ck_assert_str_eq(ret, ret_s21);
}
END_TEST

// Тест: Копирование пустой строки
START_TEST(test_s21_strncpy_empty_src) {
  const char *src = "";
  s21_size_t n = 5;
  char dest[50] = "Original";
  char original_dest[50] = "Original";

  char *ret = strncpy(original_dest, src, n);
  char *ret_s21 = s21_strncpy(dest, src, n);

  original_dest[n] = '\0'; // Гарантируем завершающий нуль
  dest[n] = '\0'; // Гарантируем завершающий нуль
  
  ck_assert_str_eq(dest, original_dest);
  ck_assert_str_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_strcspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";
  s21_size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_empty_str2) {
  const char *str1 = "hello world";
  const char *str2 = "";
  s21_size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_no_match) {
  const char *str1 = "abcdef";
  const char *str2 = "xyz";
  s21_size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_partial_match) {
  const char *str1 = "hello world";
  const char *str2 = "aeiou";
  s21_size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_full_match) {
  const char *str1 = "abc";
  const char *str2 = "abcd";
  s21_size_t result = s21_strcspn(str1, str2);
  size_t expected = strcspn(str1, str2);
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_null_str1) {
  const char *str1 = NULL;
  const char *str2 = "abc";
  s21_size_t result = s21_strcspn(str1, str2);
  size_t expected =
      0; // По стандарту, если str1 == NULL, результат должен быть 0
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_null_str2) {
  const char *str1 = "hello world";
  const char *str2 = NULL;
  s21_size_t result = s21_strcspn(str1, str2);
  size_t expected =
      0; // По стандарту, если str2 == NULL, результат должен быть 0
  ck_assert_uint_eq(result, expected);
}
END_TEST

// Тест 1: Копирование строки
START_TEST(test_s21_memcpy_string) {
  const char src[] = "Hello, world!";
  char dest[50] = {0};

  s21_memcpy(dest, src, strlen(src)); // Копируем строку с нулевым байтом

  ck_assert_str_eq(dest, src); // Проверяем равенство строк
}
END_TEST

// Тест 2: Копирование нулевого количества байт
START_TEST(test_s21_memcpy_zero_bytes) {
  const char src[] = "Hello, world!";
  char dest[50] = "Original content";

  s21_memcpy(dest, src, 0); // Копируем 0 байт

  ck_assert_str_eq(dest,
                   "Original content"); // Содержимое dest не должно измениться
}
END_TEST

// Тест 3: Копирование большого объема данных
START_TEST(test_s21_memcpy_large_data) {
  size_t size = 1024;
  char *src = malloc(size);
  char *dest = malloc(size);

  for (size_t i = 0; i < size; i++) {
    src[i] = 'A' + (i % 26); // Заполняем src случайными символами
  }

  s21_memcpy(dest, src, size);

  for (size_t i = 0; i < size; i++) {
    ck_assert_int_eq(dest[i], src[i]); // Проверяем каждый байт
  }

  free(src);
  free(dest);
}
END_TEST

// Тест для s21_strpbrk (символ найден)
START_TEST(test_s21_strpbrk_found) {
    const char *str1 = "hello world";
    const char *str2 = "abcde";
    const char *result = s21_strpbrk(str1, str2);
    const char *result_r = strpbrk(str1, str2);
    ck_assert_ptr_ne(result, NULL); // Проверяем, что результат не NULL
    ck_assert_str_eq(result, result_r); // Проверяем, что строка начинается с найденного символа
}
END_TEST

// Тест для s21_strpbrk (символ не найден)
START_TEST(test_s21_strpbrk_not_found) {
    const char *str1 = "hello world";
    const char *str2 = "xyz";
    const char *result = s21_strpbrk(str1, str2);
    const char *result_r = strpbrk(str1, str2);
    ck_assert_ptr_eq(result, result_r); // Оба должны быть NULL
}
END_TEST

// Тест для s21_strrchr (символ найден)
START_TEST(test_s21_strrchr_found) {
    const char *str = "hello world";
    int c = 'o';
    const char *result = s21_strrchr(str, c);
    const char *result_r = strrchr(str, c);
    ck_assert_ptr_ne(result, NULL); // Проверяем, что результат не NULL
    ck_assert_str_eq(result, result_r); // Проверяем, что строка начинается с найденного символа
}
END_TEST

// Тест для s21_strrchr (символ не найден)
START_TEST(test_s21_strrchr_not_found) {
    const char *str = "hello world";
    int c = 'z';
    const char *result = s21_strrchr(str, c);
    const char *result_r = strrchr(str, c);
    ck_assert_ptr_eq(result, result_r); // Оба должны быть NULL
}
END_TEST

// Тест 1: Символ находится в строке
START_TEST(test_s21_memchr_found) {
    const char *str = "Hello, world!";
    int c = 'o';
    size_t n = strlen(str);
    void *result = s21_memchr(str, c, n);
    void *result_r = memchr(str, c, n);
    ck_assert_ptr_ne(result, NULL); // Проверяем, что результат не NULL
    ck_assert_ptr_eq(result, result_r); // Сравниваем с оригинальной функцией
}
END_TEST

// Тест 2: Символ не находится в строке
START_TEST(test_s21_memchr_not_found) {
    const char *str = "Hello, world!";
    int c = 'z';
    size_t n = strlen(str);
    void *result = s21_memchr(str, c, n);
    void *result_r = memchr(str, c, n);
    ck_assert_ptr_eq(result, result_r); // Оба должны быть NULL
}
END_TEST

// Тест 3: Пустая строка
START_TEST(test_s21_memchr_empty_string) {
    const char *str = "";
    int c = 'a';
    size_t n = strlen(str);
    void *result = s21_memchr(str, c, n);
    void *result_r = memchr(str, c, n);
    ck_assert_ptr_eq(result, result_r); // Оба должны быть NULL
}
END_TEST

// Тест 4: Символ находится в начале строки
START_TEST(test_s21_memchr_at_start) {
    const char *str = "abc";
    int c = 'a';
    size_t n = strlen(str);
    void *result = s21_memchr(str, c, n);
    void *result_r = memchr(str, c, n);
    ck_assert_ptr_ne(result, NULL); // Проверяем, что результат не NULL
    ck_assert_ptr_eq(result, result_r); // Сравниваем с оригинальной функцией
}
END_TEST

// Тест 5: Символ находится в конце строки
START_TEST(test_s21_memchr_at_end) {
    const char *str = "abc";
    int c = 'c';
    size_t n = strlen(str);
    void *result = s21_memchr(str, c, n);
    void *result_r = memchr(str, c, n);
    ck_assert_ptr_ne(result, NULL); // Проверяем, что результат не NULL
    ck_assert_ptr_eq(result, result_r); // Сравниваем с оригинальной функцией
}
END_TEST

// Тест 6: Длина n равна 0
START_TEST(test_s21_memchr_zero_length) {
    const char *str = "abc";
    int c = 'b';
    size_t n = 0;
    void *result = s21_memchr(str, c, n);
    void *result_r = memchr(str, c, n);
    ck_assert_ptr_eq(result, result_r); // Оба должны быть NULL
}
END_TEST

// Тест 7: Крайний случай — символ \0
START_TEST(test_s21_memchr_null_character) {
    const char *str = "abc\0def";
    int c = '\0';
    size_t n = strlen(str) + 4; // Учитываем символ \0 и часть строки после него
    void *result = s21_memchr(str, c, n);
    void *result_r = memchr(str, c, n);
    ck_assert_ptr_ne(result, NULL); // Проверяем, что результат не NULL
    ck_assert_ptr_eq(result, result_r); // Сравниваем с оригинальной функцией
}
END_TEST

// Тест 1: Обычная строка с маленькими буквами
START_TEST(test_s21_to_upper_normal_string) {
    const char *input = "hello world";
    void *result = s21_to_upper(input);
    ck_assert_ptr_nonnull(result); // Проверяем, что результат не NULL
    ck_assert_str_eq((char *)result, "HELLO WORLD"); // Сравниваем с ожидаемым результатом
    free(result); // Освобождаем выделенную память
}
END_TEST

// Тест 2: Строка с уже большими буквами
START_TEST(test_s21_to_upper_all_uppercase) {
    const char *input = "HELLO WORLD";
    void *result = s21_to_upper(input);
    ck_assert_ptr_nonnull(result); // Проверяем, что результат не NULL
    ck_assert_str_eq((char *)result, "HELLO WORLD"); // Сравниваем с ожидаемым результатом
    free(result); // Освобождаем выделенную память
}
END_TEST

// Тест 3: Смешанные регистры
START_TEST(test_s21_to_upper_mixed_case) {
    const char *input = "HeLLo WoRld";
    void *result = s21_to_upper(input);
    ck_assert_ptr_nonnull(result); // Проверяем, что результат не NULL
    ck_assert_str_eq((char *)result, "HELLO WORLD"); // Сравниваем с ожидаемым результатом
    free(result); // Освобождаем выделенную память
}
END_TEST

// Тест 4: Пустая строка
START_TEST(test_s21_to_upper_empty_string) {
    const char *input = "";
    void *result = s21_to_upper(input);
    ck_assert_ptr_nonnull(result); // Проверяем, что результат не NULL
    ck_assert_str_eq((char *)result, ""); // Сравниваем с ожидаемым результатом
    free(result); // Освобождаем выделенную память
}
END_TEST

// Тест 5: Входной параметр NULL
START_TEST(test_s21_to_upper_null_input) {
    const char *input = NULL;
    void *result = s21_to_upper(input);
    ck_assert_ptr_null(result); // Проверяем, что результат равен NULL
}
END_TEST

// Тест 6: Строка с символами, которые не являются буквами
START_TEST(test_s21_to_upper_non_alpha_characters) {
    const char *input = "123!@#abc";
    void *result = s21_to_upper(input);
    ck_assert_ptr_nonnull(result); // Проверяем, что результат не NULL
    ck_assert_str_eq((char *)result, "123!@#ABC"); // Сравниваем с ожидаемым результатом
    free(result); // Освобождаем выделенную память
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
  tcase_add_test(tc_core, test_s21_strncmp2);
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
  tcase_add_test(tc_core, test_s21_memset_large_block);
  tcase_add_test(tc_core, test_s21_memset_negative_value);
  tcase_add_test(tc_core, test_s21_memset_null_pointer_zero_length);
  tcase_add_test(tc_core, test_s21_memset_overlap);

  tcase_add_test(tc_core, test_s21_memcmp_identical_blocks);
  tcase_add_test(tc_core, test_s21_memcmp_different_blocks);
  tcase_add_test(tc_core, test_s21_memcmp_partial_identical);
  tcase_add_test(tc_core, test_s21_memcmp_partial_different);
  tcase_add_test(tc_core, test_s21_memcmp_zero_length);
  tcase_add_test(tc_core, test_s21_memcmp_negative_values);
  tcase_add_test(tc_core, test_s21_memcmp_overlap);
  tcase_add_test(tc_core, test_s21_memcmp_large_blocks);
  tcase_add_test(tc_core, test_s21_memcmp_case_sensitive);

  tcase_add_test(tc_core, test_s21_strncpy_short_src);
  tcase_add_test(tc_core, test_s21_strncpy_long_src);
  tcase_add_test(tc_core, test_s21_strncpy_n_zero);
  tcase_add_test(tc_core, test_s21_strncpy_empty_src);

  tcase_add_test(tc_core, test_s21_strncat_basic_concatenation);
  tcase_add_test(tc_core, test_s21_strncat_partial_concatenation);
  tcase_add_test(tc_core, test_s21_strncat_empty_src);
  tcase_add_test(tc_core, test_s21_strncat_n_zero);
  tcase_add_test(tc_core, test_s21_strncat_null_pointers);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strncat_empty_dest);
  tcase_add_test(tc_core, test_s21_strncat_zero_n);
  tcase_add_test(tc_core, test_s21_strncat_large_n);

  tcase_add_test(tc_core, test_s21_strcspn_empty_str1);
  tcase_add_test(tc_core, test_s21_strcspn_empty_str2);
  tcase_add_test(tc_core, test_s21_strcspn_no_match);
  tcase_add_test(tc_core, test_s21_strcspn_partial_match);
  tcase_add_test(tc_core, test_s21_strcspn_full_match);
  tcase_add_test(tc_core, test_s21_strcspn_null_str1);
  tcase_add_test(tc_core, test_s21_strcspn_null_str2);

  tcase_add_test(tc_core, test_s21_memcpy_string);
  tcase_add_test(tc_core, test_s21_memcpy_zero_bytes);
  tcase_add_test(tc_core, test_s21_memcpy_large_data);

  tcase_add_test(tc_core, test_s21_strpbrk_found);
  tcase_add_test(tc_core, test_s21_strpbrk_not_found);
  tcase_add_test(tc_core, test_s21_strrchr_found);
  tcase_add_test(tc_core, test_s21_strrchr_not_found);
   
  tcase_add_test(tc_core, test_s21_memchr_found);
  tcase_add_test(tc_core, test_s21_memchr_not_found);
  tcase_add_test(tc_core, test_s21_memchr_empty_string);
  tcase_add_test(tc_core, test_s21_memchr_at_start);
  tcase_add_test(tc_core, test_s21_memchr_at_end);
  tcase_add_test(tc_core, test_s21_memchr_zero_length);
  tcase_add_test(tc_core, test_s21_memchr_null_character);

  tcase_add_test(tc_core, test_s21_to_upper_normal_string);
  tcase_add_test(tc_core, test_s21_to_upper_all_uppercase);
  tcase_add_test(tc_core, test_s21_to_upper_mixed_case);
  tcase_add_test(tc_core, test_s21_to_upper_empty_string);
  tcase_add_test(tc_core, test_s21_to_upper_null_input);
  tcase_add_test(tc_core, test_s21_to_upper_non_alpha_characters);
  

  suite_add_tcase(s, tc_core);

  return s;
}
