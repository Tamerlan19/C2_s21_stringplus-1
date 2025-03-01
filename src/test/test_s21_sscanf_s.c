#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>



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


  
TCase *create_s21_sscanf_s_tests(void) {
    TCase *tc;
    tc = tcase_create("Specifier= %s");

    tcase_add_test(tc, test_s21_sscanf_s_separators_comp);
    tcase_add_test(tc, test_s21_sscanf_s_simple);
    tcase_add_test(tc, test_s21_sscanf_s_space);
    tcase_add_test(tc, test_s21_sscanf_s_width);
    tcase_add_test(tc, test_s21_sscanf_s_multiple);
    tcase_add_test(tc, test_s21_sscanf_s_empty);
    tcase_add_test(tc, test_s21_sscanf_s_wrong_fmt);
    tcase_add_test(tc, test_s21_sscanf_s_width_wrong_fmt);
    tcase_add_test(tc, test_s21_sscanf_s_separators);
    tcase_add_test(tc, test_s21_sscanf_s_width_separators);
    tcase_add_test(tc, test_s21_sscanf_s_add_spaces);
    tcase_add_test(tc, test_s21_sscanf_s_skip_assignment);
    tcase_add_test(tc, test_s21_sscanf_ls_simple);
    tcase_add_test(tc, test_s21_sscanf_ls_space);
    tcase_add_test(tc, test_s21_sscanf_ls_width);
    tcase_add_test(tc, test_s21_sscanf_ls_multiple);
    tcase_add_test(tc, test_s21_sscanf_ls_empty);
    tcase_add_test(tc, test_s21_sscanf_ls_wrong_fmt);
    tcase_add_test(tc, test_s21_sscanf_ls_width_separators);
    tcase_add_test(tc, test_s21_sscanf_ls_skip_assignment);
    tcase_add_test(tc, test_s21_sscanf_ls_separators);

  return tc;
}