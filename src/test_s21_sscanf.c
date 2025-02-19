#include "s21_string.h"
#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <limits.h>

START_TEST(test_s21_sscanf_d_simple) {
  const char *input = "123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_neg) {
  const char *input = "-123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_neg_twice) {
  const char *input = "--123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_some) {
  const char *input = "123 -456 789";
  int x = 0, y = 0, z = 0, xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x, &y, &z),
                   sscanf(input, fmt, &xr, &yr, &zr));
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(zr, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_space_bef) {
  const char *input = "  123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_space_aft) {
  const char *input = "123   ";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_merge_string_end) {
  const char *input = "123Hello Worrld!!!";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_merge_string_start) {
  const char *input = "qwerty123";
  int x = 1, xr = 1; // var is not change value
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_empty) {
  const char *input = "";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_max) {
  const char *input = "2147483647"; // INT_MAX
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_min) {
  const char *input = "-2147483648"; // INT_MIN
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_max_over) {
  const char *input = "2147483657"; // INT_MAX +10. Oveflow: Result
                                    // s21_scanf=-2147483639, sscanf=-2147483639
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_miss) {
  const char *input = "9903456";
  int x = -5, xr = -5;
  const char *fmt = "%*d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_width) {
  const char *input = "123456";
  int x = 0, xr = 0;
  const char *fmt = "%3d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_wrong_fmt) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_wrong_fmt_width) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%2d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_some_fmt_wrong) {
  const char *input = "123 -456 abc";
  int x = 0, y = 0, z = 0, xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x, &y, &z),
                   sscanf(input, fmt, &xr, &yr, &zr));
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(zr, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_some_sep) {
  const char *input = " \t\n123 \t\n456 \t\n";
  int x = 0, y = 0, xr = 0, yr = 0;
  const char *fmt = "%d %d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x, &y),
                   sscanf(input, fmt, &xr, &yr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_zero) {
  const char *input = "0";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_skip_assignment) {
  const char *input = "";
  int x = 10, xr = 10;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_d_zero_start) {
  const char *input = "00789";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
END_TEST

START_TEST(test_s21_sscanf_ld_skip_assignment) {
  const char *input = "12345";
  long value = 0;
  int result = s21_sscanf(input, "%*ld");
  ck_assert_int_eq(result, 0); // Значение прочитано, но не присвоено
  ck_assert_int_eq(value, 0); // Значение не должно измениться
}
END_TEST

START_TEST(test_s21_sscanf_hd) {
  const char *input = "12345";
  short value = 0;
  int result = s21_sscanf(input, "%hd", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 12345);
}
END_TEST

// Тест 7: Чтение числа с модификатором `l` (long)
START_TEST(test_s21_sscanf_ld) {
  const char *input = "21474836480"; // Значение больше INT_MAX
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 21474836480L);
}
END_TEST

// Тест 19: Чтение числа с модификатором длины и указанием ширины
START_TEST(test_s21_sscanf_ld_width) {
  const char *input = "123456";
  long value = 0;
  int result = s21_sscanf(input, "%3ld", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 123); // Только первые 3 символа
}
END_TEST

// Тест 20: Чтение числа с модификатором длины и неверным форматом
START_TEST(test_s21_sscanf_ld_invalid) {
  const char *input = "abc";
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, 0); // Ничего не прочитано
  ck_assert_int_eq(value, 0); // Значение не должно измениться
}
END_TEST

// Тест 21: Чтение числа с модификатором длины и пустой строкой
START_TEST(test_s21_sscanf_ld_empty) {
  const char *input = "";
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, -1); // Ошибка или конец строки
  ck_assert_int_eq(value, 0); // Значение не должно измениться
}
END_TEST

START_TEST(test_s21_sscanf_complex) {
  int i, j;
  float x, y;
  char str1[10], str2[4];
  wchar_t warr[2];
  setlocale(LC_ALL, "en_US.utf8");
  char input[] = "25 54.32E-1 Thompson    56789 0123 56ß水";
  int ret = s21_sscanf(input, "%d%f%9s%2d%f %*d %2s %2lc", &i, &x, str1, &j, &y,
                       str2, warr);
  ck_assert_int_eq(i, 25);
  ck_assert_float_eq(x, 5.432);
  ck_assert_str_eq(str1, "Thompson");
  ck_assert_int_eq(j, 56);
  ck_assert_float_eq(y, 789.000000);
  ck_assert_str_eq(str2, "56");
  ck_assert_msg(warr[0] == 0x00DF,
                "Символы не совпадают: ожидалось U+00DF (ß), получено %lc (%x)",
                warr[0], warr[0]);
  ck_assert_int_eq(warr[0], 0x00DF);
  ck_assert_msg(
      warr[1] == 0x6C34,
      "Символы не совпадают: ожидалось U+6C34 (水), получено %lc (%x)", warr[1],
      warr[1]);
  ck_assert_int_eq(warr[1], 0x6C34);
  ck_assert_int_eq(ret, 7);
}
END_TEST

START_TEST(test_s21_sscanf_c) {
  // 1. Базовое чтение
  char c;
  int count = s21_sscanf("A", "%c", &c);
  ck_assert_int_eq(count, 1);
  ck_assert_int_eq(c, 'A');

  // 2. Чтение с шириной
  char str[5];
  count = s21_sscanf("World", "%4c", str);
  ck_assert_int_eq(count, 1);
  ck_assert_str_eq(str, "Worl");

  // 3. Подавление присваивания
  count = s21_sscanf("X", "%*c");
  ck_assert_int_eq(count, 0);

  count = s21_sscanf("XYZ", "%*c%*c%c", &c);
  ck_assert_int_eq(count, 1);
  ck_assert_int_eq(c, 'Z');
}
END_TEST

START_TEST(test_s21_sscanf_lc) {
  setlocale(LC_ALL, "en_US.utf8");
  // 1. Базовое чтение
  wchar_t wc;
  int count = s21_sscanf("Ω", "%lc", &wc);
  ck_assert_int_eq(count, 1);
  ck_assert_int_eq(wc, L'Ω');

  // 2. Чтение с шириной
  wchar_t wstr[5];
  count = s21_sscanf("Δέλτα", "%4lc", wstr);
  ck_assert_int_eq(count, 1);
  ck_assert(wmemcmp(wstr, L"Δέλ", 3) == 0);

  // 3. Специальные символы
  count = s21_sscanf("\t\n", "%2lc", wstr);
  ck_assert_int_eq(count, 1);
  ck_assert_int_eq(wstr[0], L'\t');
}
END_TEST

START_TEST(test_s21_sscanf_c_error) {
  setlocale(LC_ALL, "en_US.utf8");
  char c;
  char ca[3];
  int count = s21_sscanf("", "%c", &c);
  ck_assert_int_eq(count, EOF);

  count = s21_sscanf("\n\t\0", "%3c", ca);
  ck_assert_int_eq(count, 1);
  ck_assert_int_eq(ca[0], '\n');
  ck_assert_int_eq(ca[1], '\t');
  ck_assert_int_eq(ca[2], '\0');

  wchar_t wstr[3];
  count = s21_sscanf("abc", "%2lc", wstr);
  ck_assert_int_eq(count, 1);
  ck_assert(wmemcmp(wstr, L"ab", 2) == 0);
}
END_TEST

START_TEST(test_s21_sscanf_c_edge) {
  setlocale(LC_ALL, "en_US.utf8");
  // 1. Чтение символа с шириной 0
  char c = 'd', cr = 'd';
  char *fmt = "%0c";
  int count = s21_sscanf("A", fmt, &c);
  int countr = sscanf("A", fmt, &cr);
  ck_assert_int_eq(count, countr);
  ck_assert_int_eq(c, cr);

  // 2. Чтение символа с шириной больше длины строки
  char str[10] = {0};
  count = s21_sscanf("Hi", "%5c", str);
  ck_assert_int_eq(count, 1);
  ck_assert_str_eq(str, "Hi");

  // 3. Чтение символа с шириной и подавлением присваивания
  char t = ' ';
  count = s21_sscanf("Hello", "%*3c%c", &t);
  ck_assert_int_eq(t, 'l');
  ck_assert_int_eq(count, 1);

  // 4. Чтение символа с шириной и невалидными данными
  wchar_t wc;
  count = s21_sscanf("\xFF", "%1lc", &wc); // Невалидный UTF-8
  ck_assert_int_eq(count, EOF);
}
END_TEST

// Тест 1: Простой случай чтения строки
START_TEST(test_s21_sscanf_s_simple) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr);
}
END_TEST

START_TEST(test_s21_sscanf_s_space) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr); // Должно быть "Hello"
}
END_TEST

// Тест 3: Чтение строки с указанием ширины
START_TEST(test_s21_sscanf_s_width) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%5s"; // Чтение только 5 символов
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr); // Должно быть "Hello"
}
END_TEST

// Тест 4: Чтение строки с пропуском присваивания
START_TEST(test_s21_sscanf_s_skip_assignment) {
  const char *input = "Hello World";
  char str[20] = {0};
  const char *fmt = "%*s"; // Пропуск первой строки
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, str));
}
END_TEST

// Тест 5: Чтение нескольких строк
START_TEST(test_s21_sscanf_s_multiple) {
  const char *input = "Hello World 123";
  char str1[20] = {0}, str2[20] = {0}, str1r[20] = {0}, str2r[20] = {0};
  const char *fmt = "%s %s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str1, str2),
                   sscanf(input, fmt, str1r, str2r));
  ck_assert_str_eq(str1, str1r); // Должно быть "Hello"
  ck_assert_str_eq(str2, str2r); // Должно быть "World"
}
END_TEST

// Тест: Чтение wide-строки с разделителями
START_TEST(test_s21_sscanf_s_separators_comp) {
  // const char *input = "Hello , Wide : World!";
  const char *input = "Hello, , Wide : World!";
  char wstr1_s21[50] = {0}, wstr2_s21[50] = {0}, wstr3_s21[50] = {0};
  char wstr1_sscanf[50] = {0}, wstr2_sscanf[50] = {0}, wstr3_sscanf[50] = {0};
  char *fmt = "%s , %s : %s"; // Форматная строка
  // char *fmt = ""; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  printf("TEST: wstr1_sscanf=|%s|, wstr2_sscanf=|%s|, wstr3_sscanf=|%s|\n",
         wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);
  printf("TEST: wstr1_s21=|%s|, wstr2_s21=|%s|, wstr3_s21=|%s|\n", wstr1_s21,
         wstr2_s21, wstr3_s21);
  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert_str_eq(wstr1_s21, wstr1_sscanf);
  ck_assert_str_eq(wstr2_s21, wstr2_sscanf);
  ck_assert_str_eq(wstr3_s21, wstr3_sscanf);
  printf("Test test_s21_sscanf_s_separators passed.\n");
}
END_TEST

// Тест 6: Чтение строки с пустым вводом
START_TEST(test_s21_sscanf_s_empty) {
  const char *input = "";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr); // Должно быть пустая строка
}
END_TEST

// Тест 7: Чтение строки с неверным форматом
START_TEST(test_s21_sscanf_s_wrong_fmt) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%d"; // Неверный формат для строки
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr); // Должно быть пустая строка
}
END_TEST

// Тест 8: Чтение строки с модификатором ширины и неверным форматом
START_TEST(test_s21_sscanf_s_width_wrong_fmt) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%5d"; // Неверный формат для строки
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr); // Должно быть пустая строка
}
END_TEST

// Тест 9: Чтение строки с разделителями (пробелы, табуляция, новая строка)
START_TEST(test_s21_sscanf_s_separators) {
  const char *input = " \t\nHello \t\nWorld \t\n";
  char str1[20] = {0}, str2[20] = {0}, str1r[20] = {0}, str2r[20] = {0};
  const char *fmt = "%s %s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str1, str2),
                   sscanf(input, fmt, str1r, str2r));
  ck_assert_str_eq(str1, str1r); // Должно быть "Hello"
  ck_assert_str_eq(str2, str2r); // Должно быть "World"
}
END_TEST

// Тест 10: Чтение строки с модификатором ширины и разделителями
START_TEST(test_s21_sscanf_s_width_separators) {
  const char *input = " \t\nHello \t\nWorld \t\n";
  char str1[20] = {0}, str2[20] = {0}, str1r[20] = {0}, str2r[20] = {0};
  const char *fmt = "%3s %3s"; // Чтение только 3 символов
  ck_assert_int_eq(s21_sscanf(input, fmt, str1, str2),
                   sscanf(input, fmt, str1r, str2r));
  ck_assert_str_eq(str1, str1r); // Должно быть "Hel"
  ck_assert_str_eq(str2, str2r); // Должно быть "Wor"
}
END_TEST

START_TEST(test_s21_sscanf_s_add_spaces) {
  const char *input = "  Hello    World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = " %d "; // Неверный формат для строки
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr); // Должно быть пустая строка
}
END_TEST

// Тест: Чтение одного символа без модификаторов
START_TEST(s21_test_sscanf_c_single_char) {
  const char *input = "abc";
  char c;
  int result = s21_sscanf(input, "%c", &c);
  ck_assert_int_eq(result, 1); // Успешно прочитан один символ
  ck_assert_int_eq(c, 'a'); // Проверяем значение символа
  printf("Test s21_test_sscanf_c_single_char passed.\n");
}
END_TEST

// Тест: Чтение четырех символов без модификаторов
START_TEST(s21_test_sscanf_c_four_chars) {
  const char *input = "abcd";
  char c1, c2, c3, c4;
  char c1_r, c2_r, c3_r, c4_r;

  int result = s21_sscanf(input, "%c%c%c%c", &c1, &c2, &c3, &c4);
  int result_r = sscanf(input, "%c%c%c%c", &c1_r, &c2_r, &c3_r, &c4_r);
  // ck_assert_int_eq(result, 4); // Успешно прочитано четыре символа
  ck_assert_int_eq(c1, c1_r);
  ck_assert_int_eq(c2, c2_r);
  ck_assert_int_eq(c3, c3_r);
  ck_assert_int_eq(c4, c4_r);
  ck_assert_int_eq(result, result_r);
  printf("Test s21_test_sscanf_c_four_chars passed.\n");
}
END_TEST

// Тест: Пропуск символов с помощью ширины '*'
START_TEST(s21_test_sscanf_c_skip_with_width) {
  const char *input = "abcde";
  char c1, c2;

  int result = s21_sscanf(input, "%*c%c%*c%c", &c1, &c2);
  ck_assert_int_eq(result, 2); // Успешно прочитано два символа
  ck_assert_int_eq(c1, 'b');
  ck_assert_int_eq(c2, 'd');
  printf("Test s21_test_sscanf_c_skip_with_width passed.\n");
}
END_TEST

// Тест: Чтение wide-символа с модификатором 'l'
START_TEST(s21_test_sscanf_c_wide_char) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Ωβγ"; // UTF-8 представление 'Ω', 'β', 'γ'
  wchar_t wc;

  int result = s21_sscanf(input, "%lc", &wc);
  ck_assert_int_eq(result, 1); // Успешно прочитан один wide-символ
  ck_assert_int_eq(wc, L'Ω'); // Проверяем значение wide-символа
  printf("Test s21_test_sscanf_c_wide_char passed.\n");
}
END_TEST

// Тест: Чтение нескольких wide-символов с ограничением по ширине
START_TEST(s21_test_sscanf_c_wide_chars_with_width) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Ωβγδ"; // UTF-8 представление 'Ω', 'β', 'γ', 'δ'
  wchar_t wc[2];

  int result = s21_sscanf(input, "%2lc", wc);
  ck_assert_int_eq(result, 1); // Успешно прочитан один wide-символ
  ck_assert_int_eq(wc[0], L'Ω'); // Проверяем значение первого wide-символа
  printf("Test s21_test_sscanf_c_wide_chars_with_width passed.\n");
}
END_TEST

// Тест: Чтение символов с игнорированием флага '*'
START_TEST(s21_test_sscanf_c_ignore_flag) {
  const char *input = "abc";
  char c;

  int result = s21_sscanf(input, "%*c%c", &c);
  ck_assert_int_eq(result, 1); // Успешно прочитан один символ
  ck_assert_int_eq(c, 'b'); // Первый символ проигнорирован
  printf("Test s21_test_sscanf_c_ignore_flag passed.\n");
}
END_TEST

static int compare_wstrings(const wchar_t *a, const wchar_t *b) {
  setlocale(LC_ALL, "en_US.utf8");
  wprintf(L"a=|%ls| b=|%ls|\n", a, b);
  if (a == NULL && b == NULL)
    return 1;
  if (a == NULL || b == NULL)
    return 0;
  return wcscmp(a, b) == 0;
}

// Тест: Простое чтение wide-строки
START_TEST(test_s21_sscanf_ls_simple) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello Wide World";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  char *fmt = "%ls"; // Форматная строка

  // Проверяем s21_sscanf
  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  // Проверяем sscanf
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(
      result_s21, result_sscanf); // Сравниваем количество прочитанных элементов
  ck_assert(
      compare_wstrings(wstr_s21, wstr_sscanf)); // Сравниваем значения строк
  printf("Test test_s21_sscanf_ls_simple passed.\n");
}
END_TEST

// Тест: Чтение wide-строки с пробелами
START_TEST(test_s21_sscanf_ls_space) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "   Hello   ";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  char *fmt = "%ls"; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  printf("Test test_s21_sscanf_ls_space passed.\n");
}
END_TEST

// Тест: Чтение wide-строки с ограничением по ширине
START_TEST(test_s21_sscanf_ls_width) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "HelloWideWorld";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  char *fmt = "%4ls"; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  printf("Test test_s21_sscanf_ls_width passed.\n");
}
END_TEST

// Тест: Чтение нескольких wide-строк
START_TEST(test_s21_sscanf_ls_multiple) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello Wide World";
  wchar_t wstr1_s21[50], wstr2_s21[50], wstr3_s21[50];
  wchar_t wstr1_sscanf[50], wstr2_sscanf[50], wstr3_sscanf[50];
  char *fmt = "%ls %ls %ls"; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr1_s21, wstr1_sscanf));
  ck_assert(compare_wstrings(wstr2_s21, wstr2_sscanf));
  ck_assert(compare_wstrings(wstr3_s21, wstr3_sscanf));
  printf("Test test_s21_sscanf_ls_multiple passed.\n");
}
END_TEST

// Тест: Чтение пустой строки
START_TEST(test_s21_sscanf_ls_empty) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "";
  wchar_t wstr_s21[50] = {0}, wstr_sscanf[50] = {0};
  char *fmt = "%ls"; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  // ck_assert_(wstr_s21, wstr_sscanf);
  printf("Test test_s21_sscanf_ls_empty passed.\n");
}
END_TEST

// Тест: Неверный формат строки
START_TEST(test_s21_sscanf_ls_wrong_fmt) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  char *fmt = "%l"; // Неверный формат

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  printf("Test test_s21_sscanf_ls_wrong_fmt passed.\n");
}
END_TEST

// Тест: Чтение wide-строки с разделителями
START_TEST(test_s21_sscanf_ls_separators) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello, Wide: World!";
  wchar_t wstr1_s21[50] = {0}, wstr2_s21[50] = {0}, wstr3_s21[50] = {0};
  wchar_t wstr1_sscanf[50] = {0}, wstr2_sscanf[50] = {0},
          wstr3_sscanf[50] = {0};
  char *fmt = "%ls , %ls : %ls"; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr1_s21, wstr1_sscanf));
  ck_assert(compare_wstrings(wstr2_s21, wstr2_sscanf));
  ck_assert(compare_wstrings(wstr3_s21, wstr3_sscanf));
  printf("Test test_s21_sscanf_ls_separators passed.\n");
}
END_TEST

// Тест: Чтение wide-строки с шириной и разделителями
START_TEST(test_s21_sscanf_ls_width_separators) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello , Wide : World!";
  wchar_t wstr1_s21[50] = {0}, wstr2_s21[50] = {0}, wstr3_s21[50] = {0};
  wchar_t wstr1_sscanf[50] = {0}, wstr2_sscanf[50] = {0},
          wstr3_sscanf[50] = {0};
  char *fmt = "%4ls, %3ls %5ls"; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr1_s21, wstr1_sscanf));
  ck_assert(compare_wstrings(wstr2_s21, wstr2_sscanf));
  ck_assert(compare_wstrings(wstr3_s21, wstr3_sscanf));
  printf("Test test_s21_sscanf_ls_width_separators passed.\n");
}
END_TEST

// Тест: Пропуск присваивания (%*ls)
START_TEST(test_s21_sscanf_ls_skip_assignment) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello Wide World";
  wchar_t wstr_s21[50] = {0}, wstr_sscanf[50] = {0};
  char *fmt = "%*ls %ls"; // Форматная строка

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  printf("Test test_s21_sscanf_ls_skip_assignment passed.\n");
}
END_TEST

// Тест 1: Чтение чисел, разделённых пробелами
START_TEST(test_s21_sscanf_d_separator_space) {
  const char *input = "123 456 789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr); // Ожидается 3 (успешное чтение трёх чисел)
  ck_assert_int_eq(x, xr); // Ожидается 123
  ck_assert_int_eq(y, yr); // Ожидается 456
  ck_assert_int_eq(z, zr); // Ожидается 789
}
END_TEST

// Тест 2: Чтение чисел, разделённых табуляцией
START_TEST(test_s21_sscanf_d_separator_tab) {
  const char *input = "123\t456\t789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%d%d"; // Формат без явных разделителей

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr); // Ожидается 3 (успешное чтение трёх чисел)
  ck_assert_int_eq(x, xr); // Ожидается 123
  ck_assert_int_eq(y, yr); // Ожидается 456
  ck_assert_int_eq(z, zr); // Ожидается 789
}
END_TEST

// Тест 3: Чтение чисел, разделённых запятыми
START_TEST(test_s21_sscanf_d_separator_comma) {
  const char *input = "123,456,789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d,%d,%d"; // Явное указание запятых как разделителей

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr); // Ожидается 3 (успешное чтение трёх чисел)
  ck_assert_int_eq(x, xr); // Ожидается 123
  ck_assert_int_eq(y, yr); // Ожидается 456
  ck_assert_int_eq(z, zr); // Ожидается 789
}
END_TEST

// Тест 4: Чтение чисел, разделённых смешанными разделителями (пробелы и
// запятые)
START_TEST(test_s21_sscanf_d_separator_mixed) {
  const char *input = "123, 456, 789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d, %d, %d"; // Явное указание разделителей

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr); // Ожидается 3 (успешное чтение трёх чисел)
  ck_assert_int_eq(x, xr); // Ожидается 123
  ck_assert_int_eq(y, yr); // Ожидается 456
  ck_assert_int_eq(z, zr); // Ожидается 789
}
END_TEST

// Тест 5: Чтение чисел, разделённых новыми строками
START_TEST(test_s21_sscanf_d_separator_newline) {
  const char *input = "123\n456\n789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%d%d"; // Формат без явных разделителей

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr); // Ожидается 3 (успешное чтение трёх чисел)
  ck_assert_int_eq(x, xr); // Ожидается 123
  ck_assert_int_eq(y, yr); // Ожидается 456
  ck_assert_int_eq(z, zr); // Ожидается 789
}
END_TEST

// Тест 6: Чтение чисел с нестандартными разделителями (например, точка с
// запятой)
START_TEST(test_s21_sscanf_d_separator_semicolon) {
  const char *input = "123;456;789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d;%d;%d"; // Явное указание разделителей

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr); // Ожидается 3 (успешное чтение трёх чисел)
  ck_assert_int_eq(x, xr); // Ожидается 123
  ck_assert_int_eq(y, yr); // Ожидается 456
  ck_assert_int_eq(z, zr); // Ожидается 789
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_skip) {
  const char *input = "123abc456def789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%*c%d%*c%d"; // Пропуск одного символа между числами

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr); // Ожидается 3 (успешное чтение трёх чисел)
  ck_assert_int_eq(x, xr); // Ожидается 123
  ck_assert_int_eq(y, yr); // Ожидается 456
  ck_assert_int_eq(z, zr); // Ожидается 789
}
END_TEST

START_TEST(test_s21_sscanf_u)
{
   char str[] = "12345";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%u", &res1);
   int ret2 = sscanf(str, "%u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_zero)
{
   char str[] = "0";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%u", &res1);
   int ret2 = sscanf(str, "%u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_max)
{
   char str[] = "4294967295";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%u", &res1);
   int ret2 = sscanf(str, "%u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_overflow)
{
   char str[] = "4294967296";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%u", &res1);
   int ret2 = sscanf(str, "%u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_negative)
{
   char str[] = "-12345";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%u", &res1);
   int ret2 = sscanf(str, "%u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST


START_TEST(test_s21_sscanf_u_width)
{
   char str[] = "12345";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%5u", &res1);
   int ret2 = sscanf(str, "%5u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_zero)
{
   char str[] = "0";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%5u", &res1);
   int ret2 = sscanf(str, "%5u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_max)
{
   char str[] = "4294967295";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%5u", &res1);
   int ret2 = sscanf(str, "%5u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_overflow)
{
   char str[] = "4294967296";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%5u", &res1);
   int ret2 = sscanf(str, "%5u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_negative)
{
   char str[] = "-12345";
   unsigned int res1, res2;

   int ret1 = s21_sscanf(str, "%5u", &res1);
   int ret2 = sscanf(str, "%5u", &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST


START_TEST(test_s21_sscanf_u_width_star)
{
   char str[] = "12345";
   unsigned int res1=1, res2=2;
   char *fmt="%*3u%u";

   int ret1 = s21_sscanf(str, fmt, &res1);
   int ret2 = sscanf(str, fmt, &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_zero)
{
   char str[] = "0";
   unsigned int res1={0}, res2={0};
   char *fmt="%*5u%u";

   int ret1 = s21_sscanf(str, fmt, &res1);
   int ret2 = sscanf(str, fmt, &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_max)
{
   char str[] = "4294967295";
   unsigned int res1={0}, res2={0};
   char *fmt="%*5u";

   int ret1 = s21_sscanf(str, fmt, &res1);
   int ret2 = sscanf(str, fmt, &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_overflow)
{
   char str[] = "4294967296";
   unsigned int res1={0}, res2={0};
   char *fmt="%*5u";

   int ret1 = s21_sscanf(str, fmt, &res1);
   int ret2 = sscanf(str, fmt, &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_negative)
{
   char str[] = "-12345";
   unsigned int res1=0, res2=0;
   char *fmt="%*5u";

   int ret1 = s21_sscanf(str, fmt, &res1);
   int ret2 = sscanf(str, fmt, &res2);

   ck_assert_int_eq(res1, res2);
   ck_assert_int_eq(ret1, ret2);
  }
  END_TEST

  START_TEST(test_s21_sscanf_hu_simple) {
    const char *input = "12345";
    unsigned short hu = 0;

    int result_s21 = s21_sscanf(input, "%hu", &hu);
    int result_std = sscanf(input, "%hu", &hu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, 12345);            // Проверяем значение
}
END_TEST

START_TEST(test_s21_sscanf_hu_width) {
    const char *input = "123456789";
    unsigned short hu = 0;

    int result_s21 = s21_sscanf(input, "%4hu", &hu);
    int result_std = sscanf(input, "%4hu", &hu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, 1234);             // Проверяем значение с ограничением по ширине
}
END_TEST

START_TEST(test_s21_sscanf_hu_flag_star) {
    const char *input = "12345";
    unsigned short hu = 0;
    char * fmt= "%*hu %hu";
    int result_s21 = s21_sscanf(input, fmt, &hu);
    int result_std = sscanf(input, fmt, &hu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, 0);                // Значение не должно быть прочитано из-за флага '*'
}
END_TEST

START_TEST(test_s21_sscanf_hu_overflow) {
    const char *input = "65536"; // Значение больше, чем может вместить unsigned short
    unsigned short hu = 0;

    int result_s21 = s21_sscanf(input, "%hu", &hu);
    int result_std = sscanf(input, "%hu", &hu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, 0);                // При переполнении результат зависит от реализации, но часто это 0
}
END_TEST

START_TEST(test_s21_sscanf_lu_simple) {
    const char *input = "1234567890";
    unsigned long lu = 0;

    int result_s21 = s21_sscanf(input, "%lu", &lu);
    int result_std = sscanf(input, "%lu", &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(lu, 1234567890);       // Проверяем значение
}
END_TEST

START_TEST(test_s21_sscanf_lu_width) {
    const char *input = "123456789012345";
    unsigned long lu = 0;

    int result_s21 = s21_sscanf(input, "%10lu", &lu);
    int result_std = sscanf(input, "%10lu", &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(lu, 1234567890);       // Проверяем значение с ограничением по ширине
}
END_TEST

START_TEST(test_s21_sscanf_lu_flag_star) {
    const char *input = "1234567890";
    unsigned long lu = 0;
    char *fmt= "%*lu %lu";

    int result_s21 = s21_sscanf(input, fmt, &lu);
    int result_std = sscanf(input, fmt, &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(lu, 0);                // Значение не должно быть прочитано из-за флага '*'
}
END_TEST

START_TEST(test_s21_sscanf_lu_overflow) {
    const char *input = "18446744073709551616"; // Значение больше, чем может вместить unsigned long
    unsigned long lu = 0;

    int result_s21 = s21_sscanf(input, "%lu", &lu);
    int result_std = sscanf(input, "%lu", &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(lu, ULONG_MAX);         // Результат зависит от платформы, но обычно это максимальное значение unsigned long
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_combination) {
    const char *input = "12345 67890";
    unsigned short hu = 0;
    unsigned long lu = 0;

    int result_s21 = s21_sscanf(input, "%hu %lu", &hu, &lu);
    int result_std = sscanf(input, "%hu %lu", &hu, &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, 12345);            // Проверяем первое значение
    ck_assert_uint_eq(lu, 67890);            // Проверяем второе значение
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_with_width) {
    const char *input = "1234567890 9876543210";
    unsigned short hu = 0,hu_std = 0;
    unsigned long lu = 0,lu_std = 0;

    int result_s21 = s21_sscanf(input, "%4hu %5lu", &hu, &lu);
    int result_std = sscanf(input, "%4hu %5lu", &hu_std, &lu_std);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, hu_std);             // Первое значение с ограничением по ширине
    ck_assert_uint_eq(lu, lu_std);            // Второе значение с ограничением по ширине
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_with_star_flag) {
    const char *input = "12345 67890";
    unsigned long lu = 0;
    char *fmt="%*hu %lu";

    int result_s21 = s21_sscanf(input, fmt, &lu);
    int result_std = sscanf(input, fmt, &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(lu, 67890);            // Первое значение должно быть пропущено
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_with_spaces) {
    const char *input = "  12345   67890";
    unsigned short hu = 0;
    unsigned long lu = 0;

    int result_s21 = s21_sscanf(input, "%hu%lu", &hu, &lu);
    int result_std = sscanf(input, "%hu%lu", &hu, &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, 12345);            // Пробелы должны быть проигнорированы
    ck_assert_uint_eq(lu, 67890);            // Пробелы должны быть проигнорированы
}
END_TEST

START_TEST(test_s21_sscanf_hu_with_zero_flag) {
    const char *input = "012345";
    unsigned short hu = 0;

    int result_s21 = s21_sscanf(input, "%hu", &hu);
    int result_std = sscanf(input, "%hu", &hu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, 12345);            // Префикс '0' должен быть проигнорирован
}
END_TEST

START_TEST(test_s21_sscanf_lu_with_zero_flag) {
    const char *input = "01234567890";
    unsigned long lu = 0;

    int result_s21 = s21_sscanf(input, "%lu", &lu);
    int result_std = sscanf(input, "%lu", &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(lu, 1234567890);       // Префикс '0' должен быть проигнорирован
}
END_TEST

START_TEST(test_s21_sscanf_hu_with_large_width) {
    const char *input = "1234567890";
    unsigned short hu = 0,hu_s21 = 0;

    int result_s21 = s21_sscanf(input, "%10hu", &hu_s21);
    int result_std = sscanf(input, "%10hu", &hu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(hu, hu_s21);            // Ширина больше, чем может вместить unsigned short
}
END_TEST

START_TEST(test_s21_sscanf_lu_with_large_width) {
    const char *input = "12345678901234567890";
    unsigned long lu = 0,lu_s21 = 0;

    int result_s21 = s21_sscanf(input, "%20lu", &lu_s21);
    int result_std = sscanf(input, "%20lu", &lu);

    ck_assert_int_eq(result_s21, result_std); // Сравниваем коды завершения
    ck_assert_uint_eq(lu, lu_s21); // Ширина больше, чем длина числа
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *suite;
  TCase *tc_core_d, *tc_core_c, *tc_core_s, *tc_core_u, *tc_debug;

  suite = suite_create("s21_sscanf");
  // tc_core = tcase_create("Core");
  tc_core_d = tcase_create("Spec %d");
  tc_core_c = tcase_create("Spec %c");
  tc_core_s = tcase_create("Spec %s");
  tc_core_u = tcase_create("Spec %u");
  tc_debug = tcase_create("Debug");


  tcase_add_test(tc_core_d, test_s21_sscanf_d_simple);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_neg);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_neg_twice);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_space_bef);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_space_aft);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_some);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_merge_string_end);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_merge_string_start);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_empty);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_max);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_min);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_max_over);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_miss);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_width);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_some_fmt_wrong);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_wrong_fmt);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_wrong_fmt_width);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_some_sep);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_zero);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_zero_start);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_skip_assignment);
  tcase_add_test(tc_core_d, test_s21_sscanf_hd);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_skip_assignment);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_width);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_invalid);
  tcase_add_test(tc_core_d, test_s21_sscanf_ld_empty);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_space);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_tab);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_comma);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_mixed);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_newline);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_skip);
  tcase_add_test(tc_core_d, test_s21_sscanf_d_separator_semicolon);

  tcase_add_test(tc_core_c, test_s21_sscanf_c);
  tcase_add_test(tc_core_c, test_s21_sscanf_lc);
  tcase_add_test(tc_core_c, test_s21_sscanf_c_error);
  tcase_add_test(tc_core_c, test_s21_sscanf_complex);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_single_char);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_skip_with_width);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_wide_char);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_wide_chars_with_width);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_ignore_flag);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_four_chars);
  tcase_add_test(tc_core_c, test_s21_sscanf_c_edge);

  tcase_add_test(tc_core_s, test_s21_sscanf_s_separators_comp);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_simple);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_space);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_width);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_multiple);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_empty);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_wrong_fmt);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_width_wrong_fmt);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_separators);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_width_separators);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_add_spaces);
  tcase_add_test(tc_core_s, test_s21_sscanf_s_skip_assignment);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_simple);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_space);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_width);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_multiple);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_empty);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_wrong_fmt);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_width_separators);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_skip_assignment);
  tcase_add_test(tc_core_s, test_s21_sscanf_ls_separators);

  
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_star_negative);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_star_overflow);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_star_max);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_star_zero);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_star);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_negative);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_overflow);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_max);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width_zero);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_width);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_negative);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_overflow);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_max);
    tcase_add_test(tc_core_u, test_s21_sscanf_u_zero);
    tcase_add_test(tc_core_u, test_s21_sscanf_u);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_simple);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_width);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_flag_star);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_overflow);
    tcase_add_test(tc_core_u, test_s21_sscanf_lu_simple);
    tcase_add_test(tc_core_u, test_s21_sscanf_lu_width);
    tcase_add_test(tc_core_u, test_s21_sscanf_lu_flag_star);
    tcase_add_test(tc_core_u, test_s21_sscanf_lu_overflow);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_and_lu_combination);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_and_lu_with_width);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_and_lu_with_star_flag);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_and_lu_with_spaces);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_with_zero_flag);
    tcase_add_test(tc_core_u, test_s21_sscanf_lu_with_zero_flag);
    tcase_add_test(tc_core_u, test_s21_sscanf_hu_with_large_width);
    tcase_add_test(tc_core_u, test_s21_sscanf_lu_with_large_width);


  tcase_add_test(tc_debug, test_s21_sscanf_hu_and_lu_with_spaces);

  //[ ] Uncomment additional test case
  // suite_add_tcase(s, tc_core);
  // suite_add_tcase(suite, tc_core_c);
  // suite_add_tcase(suite, tc_core_d);
  // suite_add_tcase(suite, tc_core_s);
  suite_add_tcase(suite, tc_core_u);

  suite_add_tcase(suite, tc_debug);

  return suite;
}
