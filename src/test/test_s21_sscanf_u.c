#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

  

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
  unsigned int res_s21 = {0}, res2 = {0};
  const char *fmt = "%*5u%u";

  int ret_s21 = s21_sscanf(str, fmt, &res_s21);
  int ret = sscanf(str, fmt, &res2);

  ck_assert_int_eq(res_s21, res2);
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


TCase *create_s21_sscanf_u_tests(void) {
    TCase *tc;
    tc = tcase_create("Specifier= %u");

    tcase_add_test(tc, test_s21_sscanf_hu_simple);
    tcase_add_test(tc, test_s21_sscanf_hu_width);
    tcase_add_test(tc, test_s21_sscanf_hu_flag_star);
    tcase_add_test(tc, test_s21_sscanf_hu_overflow);
    tcase_add_test(tc, test_s21_sscanf_lu_simple);
    tcase_add_test(tc, test_s21_sscanf_lu_width);
    tcase_add_test(tc, test_s21_sscanf_lu_flag_star);
    tcase_add_test(tc, test_s21_sscanf_lu_overflow);
    tcase_add_test(tc, test_s21_sscanf_hu_and_lu_combination);
    tcase_add_test(tc, test_s21_sscanf_hu_and_lu_with_width);
    tcase_add_test(tc, test_s21_sscanf_hu_and_lu_with_star_flag);
    tcase_add_test(tc, test_s21_sscanf_hu_and_lu_with_spaces);
    tcase_add_test(tc, test_s21_sscanf_hu_with_zero_flag);
    tcase_add_test(tc, test_s21_sscanf_lu_with_zero_flag);
    tcase_add_test(tc, test_s21_sscanf_hu_with_large_width);
    tcase_add_test(tc, test_s21_sscanf_lu_with_large_width);
    tcase_add_test(tc, test_s21_sscanf_u_width_star_negative);
    tcase_add_test(tc, test_s21_sscanf_u_width_star_overflow);
    tcase_add_test(tc, test_s21_sscanf_u_width_star_max);
    tcase_add_test(tc, test_s21_sscanf_u_width_star_zero);
    tcase_add_test(tc, test_s21_sscanf_u_width_star);
    tcase_add_test(tc, test_s21_sscanf_u_width_negative);
    tcase_add_test(tc, test_s21_sscanf_u_width_overflow);
    tcase_add_test(tc, test_s21_sscanf_u_width_max);
    tcase_add_test(tc, test_s21_sscanf_u_width_zero);
    tcase_add_test(tc, test_s21_sscanf_u_width);
    tcase_add_test(tc, test_s21_sscanf_u_negative);
    tcase_add_test(tc, test_s21_sscanf_u_overflow);
    tcase_add_test(tc, test_s21_sscanf_u_max);
    tcase_add_test(tc, test_s21_sscanf_u_zero);
    tcase_add_test(tc, test_s21_sscanf_u);

  return tc;
}