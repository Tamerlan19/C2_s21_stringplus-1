#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include "../s21_string.h"

static int compare_wstrings(const wchar_t *a, const wchar_t *b) {
  setlocale(LC_ALL, "en_US.utf8");
  wprintf(L"a=|%ls| b=|%ls|\n", a, b);
  if (a == NULL && b == NULL) return 1;
  if (a == NULL || b == NULL) return 0;
  return wcscmp(a, b) == 0;
}

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

  ck_assert_int_eq(var1, var1_s21);
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
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

  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2388) {
  const char *input = "2559994967295 A456789   ";
  unsigned var1 = 123, var1_s21 = 123;
  wchar_t var2[1024] = L"A", var2_s21[1024] = L"A";
  long double var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%0x%lcA%8Le   ";

  int ret = sscanf(input, fmt, &var1, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21, &var3_s21);

  ck_assert_int_eq(var1, var1_s21);
  ck_assert(compare_wstrings(var2, var2_s21));
  ck_assert_double_eq_tol(var3, var3_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
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

  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2733) {
  const char *input = "1.23E4255e2:0x123abc  ";
  long double var1 = 1.123, var1_s21 = 1.123;
  float var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%6Le%G:%4c  ";

  int ret = sscanf(input, fmt, &var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, var3_s21);

  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_3234) {
  const char *input = "255\n1.23E4 longword!";
  long double var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%LG %7c!";

  int ret = sscanf(input, fmt, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var2_s21, var3_s21);

  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_4106) {
  const char *input = "314\t4294,967295 1A2B  ";
  float var1 = 1.123, var1_s21 = 1.123;
  float var2 = 1.123, var2_s21 = 1.123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%1E\t%e %3c  ";

  int ret = sscanf(input, fmt, &var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21, var3_s21);

  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_6148) {
  const char *input = "9.8e-3\t3.14159_98$";
  long double var1 = 1.123, var1_s21 = 1.123;
  unsigned int var2 = 123, var2_s21 = 123;
  const char *fmt = "%5LE\t%x_";

  int ret = sscanf(input, fmt, &var1, &var2);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21);

  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_int_eq(var2, var2_s21);
  ck_assert_int_eq(ret, ret_s21);
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

  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_6523) {
  const char *input = "98  11111295 A4294967295";
  unsigned var1 = 123, var1_s21 = 123;
  unsigned var2 = 123, var2_s21 = 123;
  float var3 = 1.123, var3_s21 = 1.123;
  const char *fmt = "%5u  %17xA%f";

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
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0032) {
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
  ck_assert(compare_wstrings(var2, var2_s21));
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_8369 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0112) {
  const char *input = "128   -128 1.23\n";
  unsigned int var1 = 123, var1_s21 = 123;
  float var2 = 1.123, var2_s21 = 1.123;
  const char *fmt = "%u   %1E ";

  int ret = sscanf(input, fmt, &var1, &var2);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, &var2_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_double_eq_tol(var2, var2_s21, 10 - 6);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0112 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_2389) {
  const char *input = "255429496729 5A456789   ";
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

START_TEST(test_s21_sscanf_cmpx_4081) {
  const char *input = "-128\n0:3.14159";
  char var1[1024] = "A", var1_s21[1024] = "A";
  char var3[1024] = "ABC", var3_s21[1024] = "ABC";
  const char *fmt = "%50c\n%15s";

  int ret = sscanf(input, fmt, var1, var3);
  int ret_s21 = s21_sscanf(input, fmt, var1_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_str_eq(var1, var1_s21);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_4081 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0623) {
  const char *input = "9.45FF-128!";
  unsigned int var1 = 123, var1_s21 = 123;
  char var2[1024] = "ABCs", var2_s21[1024] = "ABC";
  const char *fmt = "%9x%s!";

  int ret = sscanf(input, fmt, &var1, var2);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0623 is passed.\n");
}
END_TEST
START_TEST(test_s21_sscanf_cmpx_4745) {
  const char *input = "%1.2\n255\t";
  char var1[1024] = "ABC", var1_s21[1024] = "ABC";
  int var2 = 555, var2_s21 = 555;
  int var3 = -123, var3_s21 = -123;
  const char *fmt = "%7s%5d\n%i\t";

  int ret = sscanf(input, fmt, var1, &var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, var1_s21, &var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_str_eq(var1, var1_s21);
  ck_assert_int_eq(var2, var2_s21);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_4745 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_4802) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "0.00001 longword   1A2B ";
  float var1 = 1.123, var1_s21 = 1.123;
  wchar_t var2[1024] = L"A", var2_s21[1024] = L"A";
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%f %50lc   %c ";

  int ret = sscanf(input, fmt, &var1, var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert(compare_wstrings(var2, var2_s21));
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_4802 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_1127) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "9999\t4.723$hello_";
  wchar_t var1[1024] = L"A", var1_s21[1024] = L"A";
  unsigned int var2 = 123, var2_s21 = 123;
  char var3[1024] = "A", var3_s21[1024] = "A";
  const char *fmt = "%20lc\t%9x$%2c_";

  int ret = sscanf(input, fmt, var1, &var2, var3);
  int ret_s21 = s21_sscanf(input, fmt, var1_s21, &var2_s21, var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert(compare_wstrings(var1, var1_s21));
  ck_assert_int_eq(var2, var2_s21);
  ck_assert_str_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_1127 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_0005) {
  setlocale(LC_ALL, "en_US.utf8");
  const char *input = "-128$1.23E4\t12.345\n";
  long double var1 = 1.123, var1_s21 = 1.123;
  char var2[1024] = "A", var2_s21[1024] = "A";
  int var3 = -123, var3_s21 = -123;
  const char *fmt = "%20Lg$%20c\t%i\n";

  int ret = sscanf(input, fmt, &var1, var2, &var3);
  int ret_s21 = s21_sscanf(input, fmt, &var1_s21, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_double_eq_tol(var1, var1_s21, 10 - 6);
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_0005 is passed.\n");
}
END_TEST

START_TEST(test_s21_sscanf_cmpx_1686) {
  const char *input = "2.71828.8888  4294,967295:";
  unsigned int var1 = 123, var1_s21 = 123;
  char var2[1024] = "A", var2_s21[1024] = "A";
  unsigned int var3 = 123, var3_s21 = 123;

  int ret = sscanf(input, "%o.%50c  %10u:", &var1, var2, &var3);
  int ret_s21 =
      s21_sscanf(input, "%o.%50c  %10u:", &var1_s21, var2_s21, &var3_s21);

  DEBUG_PRINT("ret=%d,ret_s21=%d\n", ret, ret_s21);
  ck_assert_int_eq(var1, var1_s21);
  ck_assert_str_eq(var2, var2_s21);
  ck_assert_int_eq(var3, var3_s21);
  ck_assert_int_eq(ret, ret_s21);
  DEBUG_PRINT("Test test_s21_sscanf_cmpx_1686 is passed.\n");
}
END_TEST

TCase *create_s21_sscanf_complex_tests(void) {
  TCase *tc;
  tc = tcase_create("complex test:");

  tcase_add_test(tc, test_s21_sscanf_cmpx_0320);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0495);
  tcase_add_test(tc, test_s21_sscanf_cmpx_007);
  tcase_add_test(tc, test_s21_sscanf_cmpx_008);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0041);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0045);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0213);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0420);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0850);
  tcase_add_test(tc, test_s21_sscanf_cmpx_2214);
  tcase_add_test(tc, test_s21_sscanf_cmpx_2388);
  tcase_add_test(tc, test_s21_sscanf_cmpx_2506);
  tcase_add_test(tc, test_s21_sscanf_cmpx_2733);
  tcase_add_test(tc, test_s21_sscanf_cmpx_3234);
  tcase_add_test(tc, test_s21_sscanf_cmpx_6148);
  tcase_add_test(tc, test_s21_sscanf_cmpx_6203);
  tcase_add_test(tc, test_s21_sscanf_cmpx_7445);
  tcase_add_test(tc, test_s21_sscanf_cmpx_9721);
  tcase_add_test(tc, test_s21_sscanf_complex);
  tcase_add_test(tc, test_s21_sscanf_cmpx_7092);
  tcase_add_test(tc, test_s21_sscanf_cmpx_4106);
  tcase_add_test(tc, test_s21_sscanf_cmpx_9707);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0252);
  tcase_add_test(tc, test_s21_sscanf_cmpx_6523);
  tcase_add_test(tc, test_s21_sscanf_cmpx_2446);
  tcase_add_test(tc, test_s21_sscanf_cmpx_8369);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0032);
  tcase_add_test(tc, test_s21_sscanf_cmpx_2388);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0112);
  tcase_add_test(tc, test_s21_sscanf_cmpx_2389);
  tcase_add_test(tc, test_s21_sscanf_cmpx_4081);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0623);
  tcase_add_test(tc, test_s21_sscanf_cmpx_4745);
  tcase_add_test(tc, test_s21_sscanf_cmpx_4802);
  tcase_add_test(tc, test_s21_sscanf_cmpx_1127);
  tcase_add_test(tc, test_s21_sscanf_cmpx_0005);
  tcase_add_test(tc, test_s21_sscanf_cmpx_1686);

  return tc;
}