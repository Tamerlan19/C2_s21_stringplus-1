#include "s21_string.h"
#include <check.h>
#include <locale.h>
#include <stdio.h>

START_TEST(test_s21_sscanf_d_simple) {
  const char *input = "123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_neg) {
  const char *input = "-123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

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

START_TEST(test_s21_sscanf_d_space_bef) {
  const char *input = "  123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_space_aft) {
  const char *input = "123   ";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_merge_string_end) {
  const char *input = "123Hello Worrld!!!";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_merge_string_start) {
  const char *input = "qwerty123";
  int x = 1, xr = 1; // var is not change value
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_empty) {
  const char *input = "";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_max) {
  const char *input = "2147483647"; // INT_MAX
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_min) {
  const char *input = "-2147483648"; // INT_MIN
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_max_over) {
  const char *input = "2147483657"; // INT_MAX +10. Oveflow: Result
                                    // s21_scanf=-2147483639, sscanf=-2147483639
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}
START_TEST(test_s21_sscanf_d_miss) {
  const char *input = "123456";
  int x = 0, xr = 0;
  const char *fmt = "%*d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_width) {
  const char *input = "123456";
  int x = 0, xr = 0;
  const char *fmt = "%3d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_wrong_fmt) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_wrong_fmt_width) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%2d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

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

START_TEST(test_s21_sscanf_d_some_sep) {
  const char *input = " \t\n123 \t\n456 \t\n";
  int x = 0, y = 0, xr = 0, yr = 0;
  const char *fmt = "%d %d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x, &y),
                   sscanf(input, fmt, &xr, &yr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_zero) {
  const char *input = "0";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

START_TEST(test_s21_sscanf_d_zero_start) {
  const char *input = "00789";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
  ck_assert_int_eq(x, xr);
}

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
  char input[] = "25 54.32E-1 Thompson 56789 0123 56ß水";
  int ret = s21_sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc", &i, &x, str1, &j,
                       &y, str2, warr);
  ck_assert_int_eq(i, 25);
  ck_assert_float_eq(x, 5.432);
  ck_assert_str_eq(str1, "Thompson");
  ck_assert_int_eq(j, 56);
  ck_assert_float_eq(y, 789.000000);
  ck_assert_str_eq(str2, "56");
  ck_assert_msg(warr[0] == 0x00DF,
                "Символы не совпадают: ожидалось U+00DF (ß), получено %lc",
                warr[0]);
  // ck_assert_int_eq(warr[0], 0x00DF);
  ck_assert_msg(warr[1] == 0x6C34,
                "Символы не совпадают: ожидалось U+6C34 (水), получено %lc",
                warr[1]);
  // ck_assert_int_eq(warr[1], 0x6C34);
  ck_assert_int_eq(ret, 7);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sscanf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sscanf_d_simple);
  tcase_add_test(tc_core, test_s21_sscanf_d_some);
  tcase_add_test(tc_core, test_s21_sscanf_d_neg);
  tcase_add_test(tc_core, test_s21_sscanf_d_space_bef);
  tcase_add_test(tc_core, test_s21_sscanf_d_space_aft);
  tcase_add_test(tc_core, test_s21_sscanf_d_merge_string_end);
  tcase_add_test(tc_core, test_s21_sscanf_d_merge_string_start);
  tcase_add_test(tc_core, test_s21_sscanf_d_empty);
  tcase_add_test(tc_core, test_s21_sscanf_d_max);
  tcase_add_test(tc_core, test_s21_sscanf_d_min);
  tcase_add_test(tc_core, test_s21_sscanf_d_max_over);
  tcase_add_test(tc_core, test_s21_sscanf_d_miss);
  tcase_add_test(tc_core, test_s21_sscanf_d_width);
  tcase_add_test(tc_core, test_s21_sscanf_d_wrong_fmt);
  tcase_add_test(tc_core, test_s21_sscanf_d_wrong_fmt_width);
  tcase_add_test(tc_core, test_s21_sscanf_d_some_fmt_wrong);
  tcase_add_test(tc_core, test_s21_sscanf_d_some_sep);
  tcase_add_test(tc_core, test_s21_sscanf_d_zero);
  tcase_add_test(tc_core, test_s21_sscanf_d_zero_start);
  tcase_add_test(tc_core, test_s21_sscanf_hd);
  tcase_add_test(tc_core, test_s21_sscanf_ld);
  tcase_add_test(tc_core, test_s21_sscanf_ld_skip_assignment);
  tcase_add_test(tc_core, test_s21_sscanf_ld_width);
  tcase_add_test(tc_core, test_s21_sscanf_ld_invalid);
  tcase_add_test(tc_core, test_s21_sscanf_ld_empty);

  tcase_add_test(tc_core, test_s21_sscanf_complex);

  suite_add_tcase(s, tc_core);

  return s;
}
