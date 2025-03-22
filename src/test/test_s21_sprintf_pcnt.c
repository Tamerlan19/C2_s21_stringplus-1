#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_sprintf_pcnt_simple) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "This is a percent sign: %%");
  int result2 = sprintf(buffer2, "This is a percent sign: %%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_multiple) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "%% %% %%");
  int result2 = sprintf(buffer2, "%% %% %%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_middle) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "Hello%%World");
  int result2 = sprintf(buffer2, "Hello%%World");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_start) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "%%Hello");
  int result2 = sprintf(buffer2, "%%Hello");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_end) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "Hello%%");
  int result2 = sprintf(buffer2, "Hello%%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_mixed) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "Hello%%World%%123%%");
  int result2 = sprintf(buffer2, "Hello%%World%%123%%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_empty) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "%%");
  int result2 = sprintf(buffer2, "%%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_spaces) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "Hello %% World %%");
  int result2 = sprintf(buffer2, "Hello %% World %%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_with_other_specifiers) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  int result1 = s21_sprintf(buffer1, "Hello %d%% World %s%%", 123, "Check");
  int result2 = sprintf(buffer2, "Hello %d%% World %s%%", 123, "Check");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_sprintf_pcnt_large) {
  char buffer1[1000] = {0};
  char buffer2[1000] = {0};

  int result1 = s21_sprintf(buffer1, "%% %% %% %% %% %% %% %% %% %%");
  int result2 = sprintf(buffer2, "%% %% %% %% %% %% %% %% %% %%");

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

TCase *tcase_s21_sprintf_pcnt(void) {
  TCase *tc_core_pcnt;
  tc_core_pcnt = tcase_create("Spec %%");

  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_simple);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_multiple);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_middle);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_start);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_end);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_mixed);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_empty);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_spaces);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_with_other_specifiers);
  tcase_add_test(tc_core_pcnt, test_s21_sprintf_pcnt_large);

  return tc_core_pcnt;
}