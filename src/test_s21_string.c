#include "s21_string.h"
#include <check.h>
#include <string.h>
#include <stdio.h>

START_TEST(test_s21_strlen) {
  ck_assert_int_eq(s21_strlen("Hello"), 5);
  ck_assert_int_eq(s21_strlen(""), 0);
  ck_assert_int_eq(s21_strlen("0987654321"), 10);
  ck_assert_int_eq(s21_strlen("\n"), strlen("\n"));
  ck_assert_int_eq(s21_strlen("\0"), strlen("\0"));
  ck_assert_int_eq(
      s21_strlen(
          "                                                              "),
      strlen("                                                              "));
}
END_TEST

START_TEST(test_s21_strcmp) {
  ck_assert_int_eq(s21_strcmp("Hello world", "Hello world"),
                   strcmp("Hello world", "Hello world"));
  ck_assert_int_eq(s21_strcmp("", "123"), strcmp("", "123"));
  ck_assert_int_eq(s21_strcmp("123", ""), strcmp("123", ""));
  ck_assert_int_eq(s21_strcmp("\n", "\r"), strcmp("\n", "\r"));
  ck_assert_int_eq(s21_strcmp("", ""), strcmp("", ""));
  ck_assert_int_eq(s21_strcmp("", "NULL"), strcmp("", "NULL"));
  ck_assert_int_eq(s21_strcmp("\n", "\n"), strcmp("\n", "\n"));
}
END_TEST

START_TEST(test_s21_sprintf_с) {
  char buff[70] = {0};
  char s21_buff[70] = {0};

  int x6 = 12345;
  char *format_string3 = "%+.*d\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string3, 8, 4, x6),
                   sprintf(buff, format_string3, 8, 4, x6));
  ck_assert_str_eq(buff, s21_buff);

  short x7 = -32768;
  char *format_string4 = "%hd\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string4, x7),
                   sprintf(buff, format_string4, x7));
  ck_assert_str_eq(buff, s21_buff);

  float x8 = 123.456;
  char *format_string5 = "% 010.2f\n";
  ck_assert_int_eq(s21_sprintf(s21_buff, format_string5, x8),
                   sprintf(buff, format_string5, x8));
  ck_assert_str_eq(buff, s21_buff);
}
END_TEST


Suite *s21_string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_string");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strcmp);

  tcase_add_test(tc_core, test_s21_sprintf_с);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}


