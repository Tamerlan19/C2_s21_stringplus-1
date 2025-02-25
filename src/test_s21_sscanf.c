#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include "s21_string.h"


START_TEST(test_s21_sscanf_d_simple) {
  const char *input = "123";
  int x = 0, xr = 0;
  // const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, "%d", &x);
  int ret = sscanf(input, "%d", &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_neg) {
  const char *input = "-123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_neg_twice) {
  const char *input = "--123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_some) {
  const char *input = "123 -456 789";
  int x = 0, y = 0, z = 0, xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";
  int ret_s21 = s21_sscanf(input, fmt, &x, &y, &z);
  int ret = sscanf(input, fmt, &xr, &yr, &zr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(zr, zr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_space_bef) {
  const char *input = "  123";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_space_aft) {
  const char *input = "123   ";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_merge_string_end) {
  const char *input = "123Hello Worrld!!!";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_merge_string_start) {
  const char *input = "qwerty123";
  int x = 1, xr = 1; // var is not change value
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_empty) {
  const char *input = "";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_max) {
  const char *input = "2147483647"; // INT_MAX
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_min) {
  const char *input = " -2147483648"; // INT_MIN
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_max_over) {
  const char *input = "2147483657"; // INT_MAX +10. Oveflow: Result
                                    // s21_scanf=-2147483639, sscanf=-2147483639
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_miss) {
  const char *input = "9903456";
  int ret_s21 = s21_sscanf(input, "%*d");
  int ret = sscanf(input, "%*d");
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_width) {
  const char *input = "123456";
  int x = 0, xr = 0;
  const char *fmt = "%3d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_wrong_fmt) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_wrong_fmt_width) {
  const char *input = "qwerty";
  int x = 0, xr = 0;
  const char *fmt = "%2d";
  int ret_s21 = s21_sscanf(input, fmt, &x);
  int ret = sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_some_fmt_wrong) {
  const char *input = "123 -456 abc";
  int x = 0, y = 0, z = 0, xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";
  int ret_s21 = s21_sscanf(input, fmt, &x, &y, &z);
  int ret = sscanf(input, fmt, &xr, &yr, &zr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(zr, zr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_some_sep) {
  const char *input = " \t\n123 \t\n456 \t\n";
  int x = 0, y = 0, xr = 0, yr = 0;
  const char *fmt = "%d %d";
  int ret_s21 = s21_sscanf(input, fmt, &x, &y);
  int ret = sscanf(input, fmt, &xr, &yr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d_zero) {
  const char *input = "0";
  int x = 111, xr = 111;
  const char *fmt = "%d";
  int ret = sscanf(input, fmt, &xr);
  int ret_s21 = s21_sscanf(input, fmt, &x);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(ret, ret_s21);
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
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(value, 0);
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

START_TEST(test_s21_sscanf_ld) {
  const char *input = "21474836480"; // Значение больше INT_MAX
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 21474836480L);
}
END_TEST

START_TEST(test_s21_sscanf_ld_width) {
  const char *input = "123456";
  long value = 0;
  int result = s21_sscanf(input, "%3ld", &value);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(value, 123);
}
END_TEST

START_TEST(test_s21_sscanf_ld_invalid) {
  const char *input = "abc";
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(value, 0);
}
END_TEST

START_TEST(test_s21_sscanf_ld_empty) {
  const char *input = "";
  long value = 0;
  int result = s21_sscanf(input, "%ld", &value);
  ck_assert_int_eq(result, -1);
  ck_assert_int_eq(value, 0);
}
END_TEST

START_TEST(test_s21_sscanf_complex) {
  int i = 0, j = 0, i_s21 = 0, j_s21 = 0;
  float x = 0.0, y = 0.0;
  float x_s21 = 0.0, y_s21 = 0.0;
  const char str1[10], str2[4];
  const char str1_s21[10], str2_s21[4];
  wchar_t warr[2];
  wchar_t warr_s21[2];
  setlocale(LC_ALL, "en_US.utf8");
  const char input[] = "25 54.32E-1 Thompson    56789 0123 56 ß水";
  int ret = s21_sscanf(input, "%d%f%9s%2d%f %*d %2s %2lc", &i, &x, str1, &j, &y,
                       str2, warr);
  int ret_s21 = s21_sscanf(input, "%d%f%9s%2d%f %*d %2s %2lc", &i_s21, &x_s21,
                           str1_s21, &j_s21, &y_s21, str2_s21, warr_s21);
  ck_assert_int_eq(i, i_s21);
  ck_assert_float_eq(x, x_s21);
  ck_assert_str_eq(str1, str1_s21);
  ck_assert_int_eq(j, j_s21);
  ck_assert_float_eq(y, y_s21);
  ck_assert_str_eq(str2, str2_s21);
  ck_assert_msg(warr[0] == warr_s21[0],
                "Символы не совпадают: ожидалось U+00DF (ß), получено %lc (%x)",
                warr_s21[0], warr_s21[0]);
  ck_assert_int_eq(warr[0], warr_s21[0]);
  ck_assert_msg(
      warr[1] == warr_s21[1],
      "Символы не совпадают: ожидалось U+6C34 (水), получено %lc (%x)", warr[1],
      warr[1]);
  ck_assert_int_eq(warr[1], warr_s21[1]);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_c) {

  char c;
  int count = s21_sscanf("A", "%c", &c);
  ck_assert_int_eq(count, 1);
  ck_assert_int_eq(c, 'A');

  const char str[5];
  count = s21_sscanf("World", "%4c", str);
  ck_assert_int_eq(count, 1);
  ck_assert_str_eq(str, "Worl");

  count = s21_sscanf("X", "%*c");
  ck_assert_int_eq(count, 0);

  count = s21_sscanf("XYZ", "%*c%*c%c", &c);
  ck_assert_int_eq(count, 1);
  ck_assert_int_eq(c, 'Z');
}
END_TEST

START_TEST(test_s21_sscanf_lc) {
  setlocale(LC_ALL, "en_US.utf8");

  wchar_t wc, wc_s21;
  int count = sscanf("Ω", "%lc", &wc);
  int count_s21 = s21_sscanf("Ω", "%lc", &wc_s21);
  ck_assert_int_eq(count, count_s21);
  ck_assert_int_eq(wc, wc_s21);

  wchar_t wstr[5], wstr_s21[5];
  count_s21 = s21_sscanf("Δέλτα", "%4lc", wstr_s21);
  count = sscanf("Δέλτα", "%4lc", wstr);
  ck_assert_int_eq(count, count_s21);
  ck_assert(wmemcmp(wstr, wstr_s21, 3) == 0);

  count = sscanf("\t\n", "%2lc", wstr);
  count_s21 = s21_sscanf("\t\n", "%2lc", wstr_s21);
  ck_assert_int_eq(count, count_s21);
  ck_assert_int_eq(wstr[0], wstr_s21[0]);
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

  char c = 'd', cr = 'd';
  const char *fmt = "%0c";
  int count = s21_sscanf("A", fmt, &c);
  int countr = sscanf("A", fmt, &cr);
  ck_assert_int_eq(count, countr);
  ck_assert_int_eq(c, cr);

  const char str[10] = {0};
  count = s21_sscanf("Hi", "%5c", str);
  ck_assert_int_eq(count, 1);
  ck_assert_str_eq(str, "Hi");

  char t = ' ';
  count = s21_sscanf("Hello", "%*3c%c", &t);
  ck_assert_int_eq(t, 'l');
  ck_assert_int_eq(count, 1);

  wchar_t wc;
  count = s21_sscanf("\xFF", "%1lc", &wc); // Невалидный UTF-8
  ck_assert_int_eq(count, EOF);
}
END_TEST

START_TEST(test_s21_sscanf_s_simple) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%s";
  int ret_s21 = s21_sscanf(input, fmt, str);
  int ret = sscanf(input, fmt, strr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(str, strr);
}
END_TEST

START_TEST(test_s21_sscanf_s_space) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%s";
  int ret_s21 = s21_sscanf(input, fmt, str);
  int ret = sscanf(input, fmt, strr);
  ck_assert_str_eq(str, strr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_s_width) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%5s";
  int ret_s21 = s21_sscanf(input, fmt, str);
  int ret = sscanf(input, fmt, strr);
  ck_assert_str_eq(str, strr);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_s_skip_assignment) {
  const char *input = "Hello World";
  int ret_s21 = s21_sscanf(input, "%*s");
  int ret = sscanf(input, "%*s");
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_s_multiple) {
  const char *input = "Hello World 123";
  char str1[20] = {0}, str2[20] = {0}, str1r[20] = {0}, str2r[20] = {0};
  const char *fmt = "%s %s";
  int ret_s21 = s21_sscanf(input, fmt, str1, str2);
  int ret = sscanf(input, fmt, str1r, str2r);
  ck_assert_str_eq(str1, str1r);
  ck_assert_str_eq(str2, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_s_separators_comp) {
  // const char *input = "Hello , Wide : World!";
  const char *input = "Hello, , Wide : World!";
  char wstr1_s21[50] = {0}, wstr2_s21[50] = {0}, wstr3_s21[50] = {0};
  char wstr1_sscanf[50] = {0}, wstr2_sscanf[50] = {0}, wstr3_sscanf[50] = {0};
  const char *fmt = "%s , %s : %s";

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  DEBUG_PRINT("TEST: wstr1_sscanf=|%s|, wstr2_sscanf=|%s|, wstr3_sscanf=|%s|\n",
              wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);
  DEBUG_PRINT("TEST: wstr1_s21=|%s|, wstr2_s21=|%s|, wstr3_s21=|%s|\n",
              wstr1_s21, wstr2_s21, wstr3_s21);
  ck_assert_str_eq(wstr1_s21, wstr1_sscanf);
  ck_assert_str_eq(wstr2_s21, wstr2_sscanf);
  ck_assert_str_eq(wstr3_s21, wstr3_sscanf);
  ck_assert_int_eq(result_s21, result_sscanf);
  DEBUG_PRINT("Test test_s21_sscanf_s_separators passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_s_empty) {
  const char *input = "";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr);
}
END_TEST

START_TEST(test_s21_sscanf_s_wrong_fmt) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr);
}
END_TEST

START_TEST(test_s21_sscanf_s_width_wrong_fmt) {
  const char *input = "Hello World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = "%5s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str), sscanf(input, fmt, strr));
  ck_assert_str_eq(str, strr);
}
END_TEST

START_TEST(test_s21_sscanf_s_separators) {
  const char *input = " \t\nHello \t\nWorld \t\n";
  char str1[20] = {0}, str2[20] = {0}, str1r[20] = {0}, str2r[20] = {0};
  const char *fmt = "%s %s";
  ck_assert_int_eq(s21_sscanf(input, fmt, str1, str2),
                   sscanf(input, fmt, str1r, str2r));
  ck_assert_str_eq(str1, str1r);
  ck_assert_str_eq(str2, str2r);
}
END_TEST

START_TEST(test_s21_sscanf_s_width_separators) {
  const char *input = " \t\nHello \t\nWorld \t\n";
  char str1[20] = {2}, str2[20] = {2}, str1r[20] = {2}, str2r[20] = {2};
  const char *fmt = "%3s %3s";
  int ret_s21 = s21_sscanf(input, fmt, str1, str2);
  int ret = sscanf(input, fmt, str1r, str2r);
  ck_assert_str_eq(str1, str1r);
  ck_assert_str_eq(str2, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_s_add_spaces) {
  const char *input = "  Hello    World";
  char str[20] = {0}, strr[20] = {0};
  const char *fmt = " %s ";
  int ret_s21 = s21_sscanf(input, fmt, str);
  int ret = sscanf(input, fmt, strr);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(str, strr);
}
END_TEST

START_TEST(s21_test_sscanf_c_single_char) {
  const char *input = "abc";
  char c;
  int result = s21_sscanf(input, "%c", &c);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(c, 'a');
  DEBUG_PRINT("Test s21_test_sscanf_c_single_char passed.\n");
}
END_TEST

START_TEST(s21_test_sscanf_c_four_chars) {
  const char *input = "abcd";
  char c1, c2, c3, c4;
  char c1_r, c2_r, c3_r, c4_r;

  int result = s21_sscanf(input, "%c%c%c%c", &c1, &c2, &c3, &c4);
  int result_r = sscanf(input, "%c%c%c%c", &c1_r, &c2_r, &c3_r, &c4_r);
  // ck_assert_int_eq(result, 4);
  ck_assert_int_eq(c1, c1_r);
  ck_assert_int_eq(c2, c2_r);
  ck_assert_int_eq(c3, c3_r);
  ck_assert_int_eq(c4, c4_r);
  ck_assert_int_eq(result, result_r);
  DEBUG_PRINT("Test s21_test_sscanf_c_four_chars passed.\n");
}
END_TEST

START_TEST(s21_test_sscanf_c_skip_with_width) {
  const char *input = "abcde";
  char c1, c2;

  int result = s21_sscanf(input, "%*c%c%*c%c", &c1, &c2);
  ck_assert_int_eq(result, 2);
  ck_assert_int_eq(c1, 'b');
  ck_assert_int_eq(c2, 'd');
  DEBUG_PRINT("Test s21_test_sscanf_c_skip_with_width passed.\n");
}
END_TEST

START_TEST(s21_test_sscanf_c_wide_char) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Ωβγ"; // UTF-8 представление 'Ω', 'β', 'γ'
  wchar_t wc;

  int result = s21_sscanf(input, "%lc", &wc);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(wc, L'Ω');
  DEBUG_PRINT("Test s21_test_sscanf_c_wide_char passed.\n");
}
END_TEST

START_TEST(s21_test_sscanf_c_wide_chars_with_width) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Ωβγδ"; // UTF-8 представление 'Ω', 'β', 'γ', 'δ'
  wchar_t wc[2];

  int result = s21_sscanf(input, "%2lc", wc);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(wc[0], L'Ω');
  DEBUG_PRINT("Test s21_test_sscanf_c_wide_chars_with_width passed.\n");
}
END_TEST

START_TEST(s21_test_sscanf_c_ignore_flag) {
  const char *input = "abc";
  char c;

  int result = s21_sscanf(input, "%*c%c", &c);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(c, 'b');
  DEBUG_PRINT("Test s21_test_sscanf_c_ignore_flag passed.\n");
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

START_TEST(test_s21_sscanf_ls_simple) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello Wide World";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  const char *fmt = "%ls";

  // Проверяем s21_sscanf
  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  DEBUG_PRINT("Test test_s21_sscanf_ls_simple passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_space) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "   Hello   ";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  const char *fmt = "%ls";

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  DEBUG_PRINT("Test test_s21_sscanf_ls_space passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_width) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "HelloWideWorld";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  const char *fmt = "%4ls";

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  DEBUG_PRINT("Test test_s21_sscanf_ls_width passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_multiple) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello Wide World";
  wchar_t wstr1_s21[50], wstr2_s21[50], wstr3_s21[50];
  wchar_t wstr1_sscanf[50], wstr2_sscanf[50], wstr3_sscanf[50];
  const char *fmt = "%ls %ls %ls";

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr1_s21, wstr1_sscanf));
  ck_assert(compare_wstrings(wstr2_s21, wstr2_sscanf));
  ck_assert(compare_wstrings(wstr3_s21, wstr3_sscanf));
  DEBUG_PRINT("Test test_s21_sscanf_ls_multiple passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_empty) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "";
  wchar_t wstr_s21[50] = {0}, wstr_sscanf[50] = {0};
  const char *fmt = "%ls";

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  // ck_assert_(wstr_s21, wstr_sscanf);
  DEBUG_PRINT("Test test_s21_sscanf_ls_empty passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_wrong_fmt) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello";
  wchar_t wstr_s21[50], wstr_sscanf[50];
  const char *fmt = "%l";

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  DEBUG_PRINT("Test test_s21_sscanf_ls_wrong_fmt passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_separators) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello, Wide: World!";
  wchar_t wstr1_s21[50] = {0}, wstr2_s21[50] = {0}, wstr3_s21[50] = {0};
  wchar_t wstr1_sscanf[50] = {0}, wstr2_sscanf[50] = {0},
          wstr3_sscanf[50] = {0};
  const char *fmt = "%ls , %ls : %ls";

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr1_s21, wstr1_sscanf));
  ck_assert(compare_wstrings(wstr2_s21, wstr2_sscanf));
  ck_assert(compare_wstrings(wstr3_s21, wstr3_sscanf));
  DEBUG_PRINT("Test test_s21_sscanf_ls_separators passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_width_separators) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello , Wide : World!";
  wchar_t wstr1_s21[50] = {0}, wstr2_s21[50] = {0}, wstr3_s21[50] = {0};
  wchar_t wstr1_sscanf[50] = {0}, wstr2_sscanf[50] = {0},
          wstr3_sscanf[50] = {0};
  const char *fmt = "%4ls, %3ls %5ls";

  int result_s21 = s21_sscanf(input, fmt, wstr1_s21, wstr2_s21, wstr3_s21);
  int result_sscanf =
      sscanf(input, fmt, wstr1_sscanf, wstr2_sscanf, wstr3_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr1_s21, wstr1_sscanf));
  ck_assert(compare_wstrings(wstr2_s21, wstr2_sscanf));
  ck_assert(compare_wstrings(wstr3_s21, wstr3_sscanf));
  DEBUG_PRINT("Test test_s21_sscanf_ls_width_separators passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_ls_skip_assignment) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Hello Wide World";
  wchar_t wstr_s21[50] = {0}, wstr_sscanf[50] = {0};
  const char *fmt = "%*ls %ls";

  int result_s21 = s21_sscanf(input, fmt, wstr_s21);
  int result_sscanf = sscanf(input, fmt, wstr_sscanf);

  ck_assert_int_eq(result_s21, result_sscanf);
  ck_assert(compare_wstrings(wstr_s21, wstr_sscanf));
  DEBUG_PRINT("Test test_s21_sscanf_ls_skip_assignment passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_space) {
  const char *input = "123 456 789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d %d %d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_tab) {
  const char *input = "123\t456\t789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%d%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_comma) {
  const char *input = "123,456,789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d,%d,%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_mixed) {
  const char *input = "123, 456, 789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d, %d, %d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_newline) {
  const char *input = "123\n456\n789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%d%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_semicolon) {
  const char *input = "123;456;789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d;%d;%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_d_separator_skip) {
  const char *input = "123abc456def789";
  int x = 0, y = 0, z = 0;
  int xr = 0, yr = 0, zr = 0;
  const char *fmt = "%d%*c%d%*c%d";

  int result = s21_sscanf(input, fmt, &x, &y, &z);
  int resultr = sscanf(input, fmt, &xr, &yr, &zr);

  ck_assert_int_eq(result, resultr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(y, yr);
  ck_assert_int_eq(z, zr);
}
END_TEST

START_TEST(test_s21_sscanf_u) {
  const char str[] = "12345";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%u", &res1);
  int ret2 = sscanf(str, "%u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_zero) {
  const char str[] = "0";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%u", &res1);
  int ret2 = sscanf(str, "%u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_max) {
  const char str[] = "4294967295";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%u", &res1);
  int ret2 = sscanf(str, "%u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_overflow) {
  const char str[] = "4294967296";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%u", &res1);
  int ret2 = sscanf(str, "%u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_negative) {
  const char str[] = "-12345";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%u", &res1);
  int ret2 = sscanf(str, "%u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width) {
  const char str[] = "12345";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%5u", &res1);
  int ret2 = sscanf(str, "%5u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_zero) {
  const char str[] = "0";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%5u", &res1);
  int ret2 = sscanf(str, "%5u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_max) {
  const char str[] = "4294967295";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%5u", &res1);
  int ret2 = sscanf(str, "%5u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_overflow) {
  const char str[] = "4294967296";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%5u", &res1);
  int ret2 = sscanf(str, "%5u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_negative) {
  const char str[] = "-12345";
  unsigned int res1, res2;

  int ret1 = s21_sscanf(str, "%5u", &res1);
  int ret2 = sscanf(str, "%5u", &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star) {
  const char str[] = "12345";
  unsigned int res1 = 1, res2 = 2;
  const char *fmt = "%*3u%u";

  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_zero) {
  const char str[] = "0";
  unsigned int res1 = {0}, res2 = {0};
  const char *fmt = "%*5u%u";

  int ret_s21 = s21_sscanf(str, fmt, &res1);
  int ret = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret_s21, ret);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_max) {
  const char str[] = "4294967295";

  int ret1 = s21_sscanf(str, "%*5u");
  int ret2 = sscanf(str, "%*5u");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_overflow) {
  const char str[] = "4294967296";

  int ret1 = s21_sscanf(str, "%*5u");
  int ret2 = sscanf(str, "%*5u");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_u_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5u");
  int ret2 = sscanf(str, "%*5u");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_hu_simple) {
  const char *input = "12345";
  unsigned short hu = 0;

  int result_s21 = s21_sscanf(input, "%hu", &hu);
  int result_std = sscanf(input, "%hu", &hu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, 12345);
}
END_TEST

START_TEST(test_s21_sscanf_hu_width) {
  const char *input = "123456789";
  unsigned short hu = 0;

  int result_s21 = s21_sscanf(input, "%4hu", &hu);
  int result_std = sscanf(input, "%4hu", &hu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, 1234);
}
END_TEST

START_TEST(test_s21_sscanf_hu_flag_star) {
  const char *input = "12345";
  unsigned short hu = 0;
  const char *fmt = "%*hu %hu";
  int result_s21 = s21_sscanf(input, fmt, &hu);
  int result_std = sscanf(input, fmt, &hu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, 0);
}
END_TEST

START_TEST(test_s21_sscanf_hu_overflow) {
  const char *input = "65536";
  unsigned short hu = 0;

  int result_s21 = s21_sscanf(input, "%hu", &hu);
  int result_std = sscanf(input, "%hu", &hu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, 0);
}
END_TEST

START_TEST(test_s21_sscanf_lu_simple) {
  const char *input = "1234567890";
  unsigned long lu = 0;

  int result_s21 = s21_sscanf(input, "%lu", &lu);
  int result_std = sscanf(input, "%lu", &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(lu, 1234567890);
}
END_TEST

START_TEST(test_s21_sscanf_lu_width) {
  const char *input = "123456789012345";
  unsigned long lu = 0;

  int result_s21 = s21_sscanf(input, "%10lu", &lu);
  int result_std = sscanf(input, "%10lu", &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(lu, 1234567890);
}
END_TEST

START_TEST(test_s21_sscanf_lu_flag_star) {
  const char *input = "1234567890";
  unsigned long lu = 0;
  const char *fmt = "%*lu %lu";

  int result_s21 = s21_sscanf(input, fmt, &lu);
  int result_std = sscanf(input, fmt, &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(lu, 0);
}
END_TEST

START_TEST(test_s21_sscanf_lu_overflow) {
  const char *input = "18446744073709551616";

  unsigned long lu = 0;

  int result_s21 = s21_sscanf(input, "%lu", &lu);
  int result_std = sscanf(input, "%lu", &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(lu, ULONG_MAX);
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_combination) {
  const char *input = "12345 67890";
  unsigned short hu = 0;
  unsigned long lu = 0;

  int result_s21 = s21_sscanf(input, "%hu %lu", &hu, &lu);
  int result_std = sscanf(input, "%hu %lu", &hu, &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, 12345);
  ck_assert_uint_eq(lu, 67890);
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_with_width) {
  const char *input = "1234567890 9876543210";
  unsigned short hu = 0, hu_std = 0;
  unsigned long lu = 0, lu_std = 0;

  int result_s21 = s21_sscanf(input, "%4hu %5lu", &hu, &lu);
  int result_std = sscanf(input, "%4hu %5lu", &hu_std, &lu_std);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, hu_std);
  ck_assert_uint_eq(lu, lu_std);
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_with_star_flag) {
  const char *input = "12345 67890";
  unsigned long lu = 0;
  const char *fmt = "%*hu %lu";

  int result_s21 = s21_sscanf(input, fmt, &lu);
  int result_std = sscanf(input, fmt, &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(lu, 67890);
}
END_TEST

START_TEST(test_s21_sscanf_hu_and_lu_with_spaces) {
  const char *input = "  12345   67890";
  unsigned short hu = 0;
  unsigned long lu = 0;

  int result_s21 = s21_sscanf(input, "%hu%lu", &hu, &lu);
  int result_std = sscanf(input, "%hu%lu", &hu, &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, 12345);
  ck_assert_uint_eq(lu, 67890);
}
END_TEST

START_TEST(test_s21_sscanf_hu_with_zero_flag) {
  const char *input = "012345";
  unsigned short hu = 0;

  int result_s21 = s21_sscanf(input, "%hu", &hu);
  int result_std = sscanf(input, "%hu", &hu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, 12345);
}
END_TEST

START_TEST(test_s21_sscanf_lu_with_zero_flag) {
  const char *input = "01234567890";
  unsigned long lu = 0;

  int result_s21 = s21_sscanf(input, "%lu", &lu);
  int result_std = sscanf(input, "%lu", &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(lu, 1234567890);
}
END_TEST

START_TEST(test_s21_sscanf_hu_with_large_width) {
  const char *input = "1234567890";
  unsigned short hu = 0, hu_s21 = 0;

  int result_s21 = s21_sscanf(input, "%10hu", &hu_s21);
  int result_std = sscanf(input, "%10hu", &hu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(hu, hu_s21);
}
END_TEST

START_TEST(test_s21_sscanf_lu_with_large_width) {
  const char *input = "12345678901234567890";
  unsigned long lu = 0, lu_s21 = 0;

  int result_s21 = s21_sscanf(input, "%20lu", &lu_s21);
  int result_std = sscanf(input, "%20lu", &lu);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_uint_eq(lu, lu_s21);
}
END_TEST

START_TEST(test_s21_sscanf_n_simple) {
  const char *input = "HelloWorld";
  int n = 0;

  int result_s21 = s21_sscanf(input, "%n", &n);
  int result_std = sscanf(input, "%n", &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, 0);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_string) {
  const char *input = "HelloWorld";
  int n = 0;

  int result_s21 = s21_sscanf(input, "%4s%n", (char[5]){0}, &n);
  int result_std = sscanf(input, "%4s%n", (char[5]){0}, &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, 4);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_width) {
  const char *input = "1234567890";
  int n = 0;

  int result_s21 = s21_sscanf(input, "%*4d%n", &n);
  int result_std = sscanf(input, "%*4d%n", &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, 4);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_star_flag) {
  const char *input = "12345";
  int n = 0;

  int result_s21 = s21_sscanf(input, "%*d%n", &n);
  int result_std = sscanf(input, "%*d%n", &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, 5);
}
END_TEST

START_TEST(test_s21_scanf_n_with_length_modifiers) {
  const char *input = "HelloWorld";
  short int hn = 0;
  int n = 0;
  long int ln = 0;

  int result_s21 =
      s21_sscanf(input, "%4s%hn%*4s%n%ln", (char[5]){0}, &hn, &n, &ln);
  int result_std = sscanf(input, "%4s%hn%*4s%n%ln", (char[5]){0}, &hn, &n, &ln);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(hn, 4);
  ck_assert_int_eq(n, 8);
  ck_assert_int_eq(ln, 8);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_zero_width) {
  const char *input = "12345";
  int n = 0, n_s21 = 0, a = 0, a_s21 = 0;
  const char *fmt = "%0d%n";

  int result_s21 = s21_sscanf(input, fmt, &a_s21, &n_s21);
  int result_std = sscanf(input, fmt, &a, &n);
  ck_assert_int_eq(a_s21, a);
  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, n_s21);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_multiple_n) {
  const char *input = "HelloWorld";
  int n1 = 0, n2 = 0, n3 = 0;
  int n1_s21 = 0, n2_s21 = 0, n3_s21 = 0;
  char s[50] = {0}, s_s21[50] = {0}, s2[50] = {0}, s2_s21[50] = {0};
  const char *fmt = "%4s%n%*4s%n%4s%n";

  int result_s21 =
      s21_sscanf(input, fmt, s_s21, &n1_s21, &n2_s21, s2_s21, &n3_s21);
  int result_std = sscanf(input, fmt, s, &n1, &n2, s2, &n3);

  ck_assert_str_eq(s, s_s21);
  ck_assert_int_eq(n1, n1_s21);
  ck_assert_int_eq(n2, n2_s21);
  ck_assert_str_eq(s2, s2_s21);
  ck_assert_int_eq(n3, n3_s21);
  ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_spaces) {
  const char *input = "   HelloWorld";
  int n = 12345, n_s21 = 12345;

  int result_s21 = s21_sscanf(input, "   %n", &n_s21);
  int result_std = sscanf(input, "   %n", &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, n_s21);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_separator) {
  const char *input = "1234,5678";
  int n = 11, n_s21 = 11;

  int result_s21 = s21_sscanf(input, "%*4d,%n", &n_s21);
  int result_std = sscanf(input, "%*4d,%n", &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, n_s21);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_large_input) {
  const char *input = "12345678901234567890";
  int n = 0, n_s21 = 0;

  int result_s21 = s21_sscanf(input, "%*10d%n", &n_s21);
  int result_std = sscanf(input, "%*10d%n", &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, n_s21);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_no_conversion) {
  const char *input = "12345";
  int n = 0;

  int result_s21 = s21_sscanf(input, "%*d%n", &n);
  int result_std = sscanf(input, "%*d%n", &n);

  ck_assert_int_eq(result_s21, result_std);
  ck_assert_int_eq(n, 5);
}
END_TEST

START_TEST(test_s21_sscanf_n_with_length_modifiers) {
  const char *input = "HelloWorld";
  char s[50] = {0}, s_s21[50] = {0};
  char s2[50] = {0}, s2_s21[50] = {0};
  short int hn = 1111, hn_s21 = 1111;
  int n = 111, n_s21 = 111;
  int ln = 222, ln_s21 = 222;
  const char *fmt = "%4s%hn%*4s%n%4s%n";

  int result_s21 =
      s21_sscanf(input, fmt, s_s21, &hn_s21, &n_s21, s2_s21, &ln_s21);
  int result_std = sscanf(input, fmt, s, &hn, &n, s2, &ln);

  ck_assert_str_eq(s, s_s21);
  ck_assert_int_eq(n, n_s21);
  ck_assert_int_eq(ln, ln_s21);
  ck_assert_int_eq(hn, hn_s21);
  ck_assert_str_eq(s2, s2_s21);
  ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_sscanf_percent) {
  const char str[] = "12345%54321";
  const char *fmt = "%d%%%d";
  int res1 = 0, res2 = 0;
  int res1_s21 = 0, res2_s21 = 0;

  int ret_s21 = s21_sscanf(str, fmt, &res1_s21, &res2_s21);
  int ret = sscanf(str, fmt, &res1, &res2);

  ck_assert_int_eq(res1, res1_s21);
  ck_assert_int_eq(res2, res2_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space) {
  const char str[] = "12345 % 54321";
  const char *fmt = "%d %% %d";
  int res1 = 0, res2 = 0;
  int res1_s21 = 0, res2_s21 = 0;

  int ret_s21 = s21_sscanf(str, fmt, &res1_s21, &res2_s21);
  int ret = sscanf(str, fmt, &res1, &res2);

  ck_assert_int_eq(res1, res1_s21);
  ck_assert_int_eq(res2, res2_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space_s) {
  const char str[] = "12345%54321";
  const char *fmt = "%s %% %s";
  char str1[20] = {0}, str2[20] = {0}, str1r[20] = {0}, str2r[20] = {0};

  int ret_s21 = s21_sscanf(str, fmt, str1, str2);
  int ret = sscanf(str, fmt, str1r, str2r);

  ck_assert_str_eq(str1, str1r);
  ck_assert_str_eq(str2, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space_2) {
  const char str[] = "Use %triple space in format string";

   const char *fmt = "%s%% %s";
   char str1_s21[20] = {0}, str2_s21[20] = "TEST", str1r[20] = {0},
             str2r[20] = "TEST";

  int ret_s21 = s21_sscanf(str, fmt, str1_s21, str2_s21);
  int ret = sscanf(str, fmt, str1r, str2r);

  ck_assert_str_eq(str1_s21, str1r);
  ck_assert_str_eq(str2_s21, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent_space_triple) {
  const char str[] = "Use%triple space in format string";
  const char *fmt = "%s%%% %s";
  char str1[20] = {0}, str2[20] = "TEST", str1r[20] = {0},
             str2r[20] = "TEST";

  int ret_s21 = s21_sscanf(str, fmt, str1, str2);
  int ret = sscanf(str, fmt, str1r, str2r);

  ck_assert_str_eq(str1, str1r);
  ck_assert_str_eq(str2, str2r);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_i) {
  const char str[] = "12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_zero) {
  const char str[] = "0";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_max) {
  const char str[] = "2147483647";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_overflow) {
  const char str[] = "2147483648";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_negative) {
  const char str[] = "-12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width) {
  const char str[] = "12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_zero) {
  const char str[] = "0";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_max) {
  const char str[] = "2147483647";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_overflow) {
  const char str[] = "2147483648";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_negative) {
  const char str[] = "-12345";
  int res1 = 0, res2 = 0;

  const char *fmt = "%5i";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_max) {
  const char str[] = "2147483647";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_overflow) {
  const char str[] = "2147483648";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_i_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5i");
  int ret2 = sscanf(str, "%*5i");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_simple) {
  const char *input = "01237";
  unsigned x = 10, xr = 10;
  const char *fmt = "%o";

  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);

  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST

START_TEST(test_s21_sscanf_x_simple) {
  const char *input = "0xf3";
  unsigned x = 10, xr = 10;
  const char *fmt = "%x";
  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST

START_TEST(test_s21_sscanf_xh_simple) {
  const char *input = "0xf3";
  short unsigned x = 10, xr = 10;
  const char *fmt = "%hx";
  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST

START_TEST(test_s21_sscanf_o) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_max) {
  const char str[] = "37777777777";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_overflow) {
  const char str[] = "37777777778";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_negative) {
  const char str[] = "-12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_max) {
  const char str[] = "37777777777";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_overflow) {
  const char str[] = "37777777778";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5o";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_negative) {
  const char str[] = "-12345";
  unsigned res4 = 111, res_s21 = 111;

  const char *fmt = "%5o";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res4);

  ck_assert_int_eq(res4, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_max) {
  const char str[] = "37777777777";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_overflow) {
  const char str[] = "37777777778";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_o_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5o");
  int ret2 = sscanf(str, "%*5o");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_overflow) {
  const char str[] = "10000000";
  unsigned int res = 111, res_s21 = 111;

  const char *fmt = "%x";
  int ret = sscanf(str, fmt, &res);
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_x_negative) {
  const char str[] = "-12345";
  unsigned res = 111, res_s21 = 111;

  const char *fmt = "%x";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_x_width) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_overflow) {
  const char str[] = "100000000";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5x";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_negative) {
  const char str[] = "-12345";
  unsigned res = 111, res_s21 = 111;

  const char *fmt = "%5x";
  int ret = sscanf(str, fmt, &res);
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_max) {
  const char str[] = "ffffffff";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_overflow) {
  const char str[] = "100000000";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_x_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5x");
  int ret2 = sscanf(str, "%*5x");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_overflow) {
  const char str[] = "10000000";
  unsigned int res = 123, res_s21 = 123;

  const char *fmt = "%X";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_X_negative) {
  const char str[] = "-12345";
  unsigned res = 0, res_s21 = 0;

  const char *fmt = "%X";
  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res);

  ck_assert_int_eq(res, res_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_X_width) {
  const char str[] = "12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_zero) {
  const char str[] = "0";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_max) {
  const char str[] = "ffffffff";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_overflow) {
  const char str[] = "100000000";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_negative) {
  const char str[] = "-12345";
  unsigned res1 = 0, res2 = 0;

  const char *fmt = "%5X";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str,  "%*5X");
  int ret2 = sscanf(str,  "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str,  "%*5X");
  int ret2 = sscanf(str,  "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_max) {
  const char str[] = "ffffffff";

  int ret1 = s21_sscanf(str,  "%*5X");
  int ret2 = sscanf(str,  "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_overflow) {
  const char str[] = "100000000";

  int ret1 = s21_sscanf(str,  "%*5X");
  int ret2 = sscanf(str,  "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str,  "%*5X");
  int ret2 = sscanf(str,  "%*5X");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_X_simple) {
  const char *input = "0xf3";
  int x = 10, xr = 10;
  const char *fmt = "%i";
  s21_sscanf(input, fmt, &x);
  sscanf(input, fmt, &xr);
  ck_assert_int_eq(x, xr);
  ck_assert_int_eq(s21_sscanf(input, fmt, &x), sscanf(input, fmt, &xr));
}
END_TEST

START_TEST(test_s21_sscanf_p_simple) {
  int val = 44;
  void *ptr = &val;
  char ptr_address[50], ptr_address_s21[50];

  sprintf(ptr_address, "%p", ptr);
  sprintf(ptr_address_s21, "%p", ptr);
  DEBUG_PRINT("Pointer: %s\n", ptr_address);
  DEBUG_PRINT("Pointer s21: %s\n", ptr_address_s21);
  void *read_prt = NULL, *read_prt_s21 = NULL;
  int ret = sscanf(ptr_address, "%p", &read_prt);
  int ret_s21 = s21_sscanf(ptr_address_s21, "%p", &read_prt_s21);

  ck_assert_str_eq(ptr_address, ptr_address_s21);
  ck_assert_ptr_eq(ptr, read_prt);
  ck_assert_ptr_eq(ptr, read_prt_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_p) {
  const char *str = "0xABCD 0x1234";
  const char *fmt = "%p %p";
  void *ptr1 = NULL, *ptr2 = NULL;
  void *ptr3 = NULL, *ptr4 = NULL;

  int res1 = s21_sscanf(str, fmt, &ptr1, &ptr2);
  int res2 = sscanf(str, fmt, &ptr3, &ptr4);

  ck_assert_ptr_eq(ptr1, ptr3);
  ck_assert_ptr_eq(ptr2, ptr4);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sscanf_p_suppress) {
  const char *str = "0xABCD 0x1234";
  const char *fmt = "%*p %p";
  void *ptr1 = NULL;
  void *ptr2 = NULL;

  int res1 = s21_sscanf(str, fmt, &ptr1);

  int res2 = sscanf(str, fmt, &ptr2);

  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sscanf_p_combination) {
  const char *str = "0xABCD 42 0x1234";
  const char *fmt = "%p %d %p";
  void *ptr1 = NULL, *ptr2 = NULL;
  void *ptr3 = NULL, *ptr4 = NULL;
  int num1 = 0, num2 = 0;

  int res1 = s21_sscanf(str, fmt, &ptr1, &num1, &ptr2);

  int res2 = sscanf(str, fmt, &ptr3, &num2, &ptr4);

  ck_assert_ptr_eq(ptr1, ptr3);
  ck_assert_int_eq(num1, num2);
  ck_assert_ptr_eq(ptr2, ptr4);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sscanf_g) {
  const char str[] = "12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_zero) {
  const char str[] = "0";
  float res1 = 0, res2 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_max) {
  const char str1[] = "1.7976931348623157E+308";
  long double res_s21 = 0, res = 0;
  int ret = 123, ret_s21 = 123;

  const char *fmt1 = "%Lg";
  ret_s21 = s21_sscanf(str1, fmt1, &res_s21);
  ret = sscanf(str1, fmt1, &res);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_double_eq_tol(res_s21, res, 1e-9);

  long double res2_s21 = 0, res2 = 0;
  const char *fmt2 = "%Lg";
  const char str2[] = "1.7976931348623157E+308";

  int ret2_s21 = s21_sscanf(str2, fmt2, &res2_s21);
  int ret2 = sscanf(str2, fmt2, &res2);

  ck_assert_int_eq(ret2_s21, ret2);
  ck_assert_double_eq(res2_s21, res2);
}
END_TEST

START_TEST(test_s21_sscanf_g_overflow) {
  const char str[] = "1.7976931348623158E+308";
  float res = 0, res_s21 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res_s21);
  int ret2 = sscanf(str, fmt, &res);

  ck_assert_double_eq(res, res_s21);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width) {
  const char str[] = "12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_zero) {
  const char str[] = "0";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_max) {
  const char str[] = "1.7976931348623157E+308";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_overflow) {
  const char str[] = "1.7976931348623158E+308";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5g";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_double_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_max) {
  const char str[] = "1.7976931348623157E+308";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_overflow) {
  const char str[] = "1.7976931348623158E+308";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_g_width_star_negative) {
  const char str[] = "-12345";

  int ret1 = s21_sscanf(str, "%*5g");
  int ret2 = sscanf(str, "%*5g");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f) {
  const char str[] = "12345";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_zero) {
  const char str[] = "0";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_max) {
  const char str[] = "3.402823466E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_overflow) {
  const char str[] = "3.402823467E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_negative) {
  const char str[] = "-12345";
  float res1 = 555, res2 = 555;

  const char *fmt = "%f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width) {
  const char str[] = "12345";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_zero) {
  const char str[] = "0";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_max) {
  const char str[] = "3.402823466E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_overflow) {
  const char str[] = "3.402823467E+38";
  float res1 = 555, res2 = 555;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star) {
  const char str[] = "12345";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_zero) {
  const char str[] = "0";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_max) {
  const char str[] = "3.402823466E+38";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_overflow) {
  const char str[] = "3.402823467E+38";

  int ret1 = s21_sscanf(str, "%*5f");
  int ret2 = sscanf(str, "%*5f");

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_f_width_star_negative) {
  const char str[] = "-12345";
  float res1 = 0, res2 = 0;

  const char *fmt = "%5f";
  int ret1 = s21_sscanf(str, fmt, &res1);
  int ret2 = sscanf(str, fmt, &res2);

  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_007) {
  const char *input = "1.2E51.2E5\n1.2E5%%";
  float var1 = 1.123, var1_s21 = 1.123;
  long double var2 = 1.123, var2_s21 = 1.123;
  long double var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%1G%Lf\n%15Lg%%";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0023 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_008) {
  const char *input = "1.23E4  456789   2.71828  ";
  float var1 = 1.123, var1_s21 = 1.123;
  float var2 = 1.123, var2_s21 = 1.123;
  int var3 = 555, var3_s21 = 555;
  const char *fmt = "%2f  %7G   %10d  ";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0463 is passed.\n");
}

END_TEST

START_TEST(test_s21_sscanf_cmpx_0320) {
  const char *input = "12.345.-128.1.2A";
  int var1 = -123, var1_s21 = -123;
  long double var2 = 1.123, var2_s21 = 1.123;
  unsigned int var3 = 123, var3_s21 = 123;
  const char *fmt = "%10i.%9Lf.%2xA";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0320 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0495) {
  const char *input = "4.723e6  255   3.14159:";
  long double var1 = 1.123, var1_s21 = 1.123;
  float var2 = 1.123, var2_s21 = 1.123;
  float var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%5LE  %e   %2E:";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0495 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0045) {
  const char *input = "4.723.-128A255 ";
  unsigned int var1 = 123, var1_s21 = 123;
  float var2 = 1.123, var2_s21 = 1.123;
  float var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%20o.%15gA%f ";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0045 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0041) {
  const char *input = "1.2E5 4.723e6   1A2BA";
  wchar_t var1[1024] = L"ABC", var1_s21[1024] = L"ABC";
  long double var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%3ls %9Lg   %cA";

  int ret = sscanf(input, fmt, var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, var1_s21, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert(compare_wstrings(var1, var1_s21));
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0041 is passed.\n");
}

START_TEST(test_s21_sscanf_cmpx_0213) {
  const char *input = "1.234 0.00001\n1.2E5!";
  unsigned int var1 = 123, var1_s21 = 123;
  long double var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%x %6Lg\n%c!";

  int ret = sscanf(input, fmt, &var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0213 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0420) {
  const char *input = "255 0123abc\n3.14159,";
  char var2[1024] = "ABC", var2_s21[1024] = "ABC";
  long double var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%s\n%LG,";

  int ret = sscanf(input, fmt, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0420 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0850) {
  const char *input = "3.14159\t 023abc\t123";
  int var1 = -123, var1_s21 = -123;
  char var2[1024] = "ABC", var2_s21[1024] = "ABC";
  float var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%7i\t%6s\t%20E";

  int ret = sscanf(input, fmt, &var1, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0850 is passed.\n");
  // Assertion 'fabsl(var3_s21 - var3) < 10-6' failed: var3 == 1.19468e+06,
  // var3_s21 == 0, 10-6 == 4
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2214) {
  const char *input = "3.14\n4.723e6  12.34 ";
  int var1 = -123, var1_s21 = -123;
  float var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%8i\n%50g  %0c ";

  int ret = sscanf(input, fmt, &var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_2214 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2388) {
  const char *input = "2554294967295A456789   ";
  unsigned var1 = 123, var1_s21 = 123;
  wchar_t var2[1024] = L"A", var2_s21[1024] = L"A";
  long double var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%0x%lcA%8Le   ";

  int ret = sscanf(input, fmt, &var1, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert(compare_wstrings(var2, var2_s21));
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_2388 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2506) {
  const char *input = "3.14159  0.00001\n-128_";
  unsigned int var1 = 123, var1_s21 = 123;
  float var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%8X  %15e\n%15c_";

  int ret = sscanf(input, fmt, &var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_2506 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2733) {
  const char *input = "1.23E4255:0x123abc  ";
  long double var1 = 1.123, var1_s21 = 1.123;
  float var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%4Le%G:%4c  ";

  int ret = sscanf(input, fmt, &var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_2733 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_3234) {
  const char *input = "255\n1.23E4 longword!";
  long double var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%LG %7c!";

  int ret = sscanf(input, fmt, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_3234 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_4106) {
  const char *input = "314\t4294,967295 1A2B  ";
  float var1 = 1.123, var1_s21 = 1.123;
  float var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%1E\t%e %3c  ";

  /*
    const char *input="255  456789 3.14159A";
  unsigned int var2=123,var2_s21=123;
  char var3[1024]="A",var3_s21[1024]="A";
  const char *fmt="%3x%6cA";
*/

  int ret = sscanf(input, fmt, &var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_4106 is passed.\n");
  // test_s21_sscanf.c:3034:F:Debug:test_s21_sscanf_cmpx_4106:0: Assertion 'var3
  // == var3_s21' failed: var3 == "429", var3_s21 == "   42"
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_6148) {
  const char *input = "9.8e-3\t3.14159_98$";
  long double var1 = 1.123, var1_s21 = 1.123;
  unsigned int var2 = 123, var2_s21 = 123;
  const char *fmt = "%5LE\t%x_";

  int ret = sscanf(input, fmt, &var1, &var2);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_int_eq(var2, var2_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_6148 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_6203) {
  const char *input = "1.2E5\n4294967295   0.00001$";
  long double var1 = 1.123, var1_s21 = 1.123;
  long double var2 = 1.123, var2_s21 = 1.123;
  unsigned int var3 = 123, var3_s21 = 123;
  const char *fmt = "%3Lg\n%Le   %5u$";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_6203 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_6523) {
  // const char *input="98  4294967295A4294967295";
  const char *input = "98  11111295A4294967295";
  unsigned  var1 = 123, var1_s21 = 123;
  unsigned  var2 = 123, var2_s21 = 123;
  float var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%5u  %50xA%f";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_int_eq(var2, var2_s21);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_6523 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_7092) {
  const char *input = "255  456789 3.14159A";
  unsigned int var2 = 123, var2_s21 = 123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%3x%6cA";

  int ret = sscanf(input, fmt, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var2, var2_s21);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_7092 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_7445) {
  const char *input = "1.2E5 40.723e6  456789 ";
  float var1 = 1.123, var1_s21 = 1.123;
  float var2 = 9.123, var2_s21 = 9.123;
  int var3 = -123, var3_s21 = -123;
  const char *fmt = "%3f %E  %2i ";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_7445 is passed.\n");
  // test_s21_sscanf.c:3120:F:Debug:test_s21_sscanf_cmpx_7445:0: Assertion 'var3
  // == var3_s21' failed: var3 == -123, var3_s21 == 4
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_9707) {
  const char *input = "4294967295\n1A2B:4294967295 ";
  wchar_t var1[1024] = L"A", var1_s21[1024] = L"A";
  char var2[1024] = "A", var2_s21[1024] = "A";
  float var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%50lc\n%5c:%4G ";

  int ret = sscanf(input, fmt, var1, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, var1_s21, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  DEBUG_PRINT("var1=|%ls|,\nvar_s21=|%ls|\n", var1, var1_s21);
  ck_assert(compare_wstrings(var1, var1_s21));
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_9707 is passed.\n");
  // test_s21_sscanf.c:3138:F:Debug:test_s21_sscanf_cmpx_9707:0: Assertion 'var2
  // == var2_s21' failed: var2 == "A", var2_s21 == ""
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_9721) {
  const char *input = "9.8e-3  1.2\n255\t";
  long double var1 = 1.123, var1_s21 = 1.123;
  int var3 = 555, var3_s21 = 555;
  const char *fmt = "%5Lf  %15d\t";

  int ret = sscanf(input, fmt, &var1, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_9721 is passed.\n");
  // test_s21_sscanf.c:3154:F:Debug:test_s21_sscanf_cmpx_9721:0: Assertion 'var3
  // == var3_s21' failed: var3 == 3, var3_s21 == -3
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0032) {
  // const char *input="4294967295 3.14_1.23A";
  // unsigned int var1=123,var1_s21=123;
  // int var3=-123,var3_s21=-123;
  // const char *fmt="%X %9iA";
  const char *input = "0xFFFFFFFF 556A";
  unsigned var1 = 123, var1_s21 = 123;
  int var3 = 123, var3_s21 = 123;
  const char *fmt = "%X %9iA";

  int ret = sscanf(input, fmt, &var1, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var3_s21);

  DEBUG_PRINT("ret=%i,ret_s21=%i\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0032 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0252) {
  const char *input = "9.8e-3\n4294967295 4294967295\n";
  float var1 = 1.123, var1_s21 = 1.123;
  float var2 = 1.123, var2_s21 = 1.123;
  long unsigned var3 = 123, var3_s21 = 123;
  const char *fmt = "%f\n%f %lx\n";

  int ret = sscanf(input, fmt, &var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0252 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2446) {
  const char *input = "4294967295 % 12.345 ";
  unsigned long var1 = 123, var1_s21 = 123;
  char var2[1024] = "ABC", var2_s21[1024] = "ABC";
  unsigned var3 = 123, var3_s21 = 123;
  const char *fmt = "%lx %s\n%1x ";

  int ret = sscanf(input, fmt, &var1, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_2446 is passed.\n");
  // test_gen_s21_sscanf.c:42072:F:Core:test_s21_sscanf_cmpx_2446:0: Assertion
  // 'var1 == var1_s21' failed: var1 == 2492887701, var1_s21 == 4294967295
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_8369) {
  const char *input = "314   FF  00x4294967295$";
  unsigned int var1 = 123, var1_s21 = 123;
  wchar_t var2[1024] = L"ABC", var2_s21[1024] = L"ABC";
  unsigned int var3 = 123, var3_s21 = 123;
  const char *fmt = "%4o   %7ls  %X$";

  int ret = sscanf(input, fmt, &var1, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  // ck_assert_int_eq(var2, fmt[6]);
  ck_assert(compare_wstrings(var2, var2_s21));
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_8369 is passed.\n");
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *suite;
  TCase *tc_core_d, *tc_core_c, *tc_core_s, *tc_core_u, *tc_core_n, *tc_debug,
      *tc_core_pcnt, *tc_core_i, *tc_core_o, *tc_core_x, *tc_core_p, *tc_core_g,
      *tc_core_f;

  suite = suite_create("s21_sscanf");
  // tc_core = tcase_create("Core");
  tc_core_d = tcase_create("Specifier= %d");
  tc_core_c = tcase_create("Specifier= %c");
  tc_core_s = tcase_create("Specifier= %s");
  tc_core_u = tcase_create("Specifier= %u");
  tc_core_n = tcase_create("Specifier= %n");
  tc_core_i = tcase_create("Specifier= %i");
  tc_core_o = tcase_create("Specifier= %o");
  tc_core_x = tcase_create("Specifier= %x");
  tc_core_p = tcase_create("Specifier= %p");
  tc_core_g = tcase_create("Specifier= %g");
  tc_core_f = tcase_create("Specifier= %f");
  tc_core_pcnt = tcase_create("Specifier= %%");
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

  tcase_add_test(tc_core_n, test_s21_sscanf_n_simple);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_string);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_width);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_star_flag);
  tcase_add_test(tc_core_n, test_s21_scanf_n_with_length_modifiers);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_zero_width);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_multiple_n);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_spaces);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_separator);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_large_input);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_no_conversion);
  tcase_add_test(tc_core_n, test_s21_sscanf_n_with_length_modifiers);

  tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent);
  tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space);
  tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space_2);
  tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space_s);
  tcase_add_test(tc_core_pcnt, test_s21_sscanf_percent_space_triple);

  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_negative);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_overflow);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_max);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star_zero);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_star);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_negative);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_overflow);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_max);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width_zero);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_width);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_negative);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_overflow);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_max);
  tcase_add_test(tc_core_i, test_s21_sscanf_i_zero);
  tcase_add_test(tc_core_i, test_s21_sscanf_i);

  tcase_add_test(tc_core_o, test_s21_sscanf_o_simple);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_negative);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_overflow);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_max);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star_zero);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_star);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_negative);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_overflow);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_max);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width_zero);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_width);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_negative);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_overflow);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_max);
  tcase_add_test(tc_core_o, test_s21_sscanf_o_zero);
  tcase_add_test(tc_core_o, test_s21_sscanf_o);

  tcase_add_test(tc_core_x, test_s21_sscanf_x_simple);
  tcase_add_test(tc_core_x, test_s21_sscanf_xh_simple);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_negative);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_overflow);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_max);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star_zero);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_star);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_negative);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_overflow);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_max);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width_zero);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_width);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_negative);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_overflow);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_max);
  tcase_add_test(tc_core_x, test_s21_sscanf_x_zero);
  tcase_add_test(tc_core_x, test_s21_sscanf_x);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_simple);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_negative);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_overflow);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_max);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star_zero);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_star);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_negative);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_overflow);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_max);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width_zero);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_width);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_negative);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_overflow);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_max);
  tcase_add_test(tc_core_x, test_s21_sscanf_X_zero);
  tcase_add_test(tc_core_x, test_s21_sscanf_X);

  tcase_add_test(tc_core_p, test_s21_sscanf_p_simple);
  tcase_add_test(tc_core_p, test_s21_sscanf_p);
  tcase_add_test(tc_core_p, test_s21_sscanf_p_suppress);
  tcase_add_test(tc_core_p, test_s21_sscanf_p_combination);

  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_negative);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_overflow);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_max);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star_zero);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_star);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_negative);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_overflow);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_max);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width_zero);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_width);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_negative);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_overflow);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_max);
  tcase_add_test(tc_core_g, test_s21_sscanf_g_zero);
  tcase_add_test(tc_core_g, test_s21_sscanf_g);

  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_negative);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_overflow);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_max);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star_zero);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_star);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_negative);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_overflow);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_max);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width_zero);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_width);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_negative);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_overflow);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_max);
  tcase_add_test(tc_core_f, test_s21_sscanf_f_zero);
  tcase_add_test(tc_core_f, test_s21_sscanf_f);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_0320);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_0495);

  //[ ] Uncomment additional test case
  suite_add_tcase(suite, tc_core_c);
  suite_add_tcase(suite, tc_core_d);
  suite_add_tcase(suite, tc_core_s);
  suite_add_tcase(suite, tc_core_u);
  suite_add_tcase(suite, tc_core_n);
  suite_add_tcase(suite, tc_core_i);
  suite_add_tcase(suite, tc_core_o);
  suite_add_tcase(suite, tc_core_x);
  suite_add_tcase(suite, tc_core_p);
  suite_add_tcase(suite, tc_core_g);
  suite_add_tcase(suite, tc_core_f);
  suite_add_tcase(suite, tc_core_pcnt);

  //[ ] Delete debug suite
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_007);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_008);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_0041);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_0045);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_0213);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_0420);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_0850);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_2214);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_2388);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_2506);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_2733);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_3234);
  tcase_add_test(tc_core_c, test_s21_sscanf_cmpx_4106);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_6148);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_6203);
  tcase_add_test(tc_core_x, test_s21_sscanf_cmpx_6523);
  tcase_add_test(tc_core_c, test_s21_sscanf_cmpx_7092);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_7445);
  tcase_add_test(tc_core_c, test_s21_sscanf_cmpx_9707);
  tcase_add_test(tc_core_f, test_s21_sscanf_cmpx_9721);
  tcase_add_test(tc_core_x, test_s21_sscanf_cmpx_0252);
  tcase_add_test(tc_core_x, test_s21_sscanf_cmpx_2446);
  tcase_add_test(tc_debug, test_s21_sscanf_cmpx_8369);

  tcase_add_test(tc_debug, test_s21_sscanf_cmpx_0032);
  tcase_add_test(tc_debug, test_s21_sscanf_cmpx_2388);
  tcase_add_test(tc_debug, test_s21_sscanf_d_max);

  suite_add_tcase(suite, tc_debug);
  return suite;
}
