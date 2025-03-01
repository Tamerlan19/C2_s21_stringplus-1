#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

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

TCase *create_s21_sscanf_n_tests(void) {
  TCase *tc_core_n;
  tc_core_n = tcase_create("Specifier= %n");

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

  return tc_core_n;
}