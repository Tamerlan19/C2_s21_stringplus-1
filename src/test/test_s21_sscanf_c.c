#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include "../s21_string.h"

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
  count = s21_sscanf("\xFF", "%1lc", &wc);
  ck_assert_int_eq(count, EOF);
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
  const char *input = "Ωβγ";
  wchar_t wc;

  int result = s21_sscanf(input, "%lc", &wc);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(wc, L'Ω');
  DEBUG_PRINT("Test s21_test_sscanf_c_wide_char passed.\n");
}
END_TEST

START_TEST(s21_test_sscanf_c_wide_chars_with_width) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "Ωβγδ";
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

TCase *create_s21_sscanf_c_tests(void) {
  TCase *tc_core_c;
  tc_core_c = tcase_create("Specifier= %c");

  tcase_add_test(tc_core_c, test_s21_sscanf_c);
  tcase_add_test(tc_core_c, test_s21_sscanf_lc);
  tcase_add_test(tc_core_c, test_s21_sscanf_c_error);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_single_char);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_skip_with_width);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_wide_char);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_wide_chars_with_width);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_ignore_flag);
  tcase_add_test(tc_core_c, s21_test_sscanf_c_four_chars);
  tcase_add_test(tc_core_c, test_s21_sscanf_c_edge);

  return tc_core_c;
}