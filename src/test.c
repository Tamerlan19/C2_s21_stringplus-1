#include "s21_string.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Suite *s21_string_suite(void);
Suite *s21_sprintf_suite(void);
Suite *s21_sscanf_suite(void);

int main(void) {
  int number_failed = 0, failed_sum = 0;

  SRunner *sr;

// [ ]: Uncomment test case suite
  // sr = srunner_create(s21_string_suite());
  // srunner_run_all(sr, CK_NORMAL);
  // number_failed = srunner_ntests_failed(sr);
  // srunner_free(sr);
  // if (number_failed != 0) {
  //   printf("Suite \"s21_string_suite\" failed: %d tests.\n\n", number_failed);
  // } else {
  //   printf("Suite \"s21_string_suite\" passed!\n\n");
  // }
  // failed_sum += number_failed;

  sr = srunner_create(s21_sprintf_suite());
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  if (number_failed != 0) {
    printf("Suite \"s21_printf_suite\" failed: %d tests.\n\n", number_failed);
  } else {
    printf("Suite \"s21_printf_suite\" passed!\n\n");
  }
  failed_sum += number_failed;


  // sr = srunner_create(s21_sscanf_suite());
  // srunner_run_all(sr, CK_NORMAL);
  // number_failed = srunner_ntests_failed(sr);
  // srunner_free(sr);
  // if (number_failed != 0) {
  //   printf("Suite \"s21_scanf_suite\" failed: %d tests.\n\n", number_failed);
  // } else {
  //   printf("Suite \"s21_scanf_suite\" passed!\n\n");
  // }
  // failed_sum += number_failed;

  if (failed_sum != 0) {
    printf("FAIL! %d tests is failed.\n", failed_sum);
  } else {
    printf("PASS!\n");
  }

  // [ ]: REMOVE return 0
  //   return (failed_sum == 0) ? 0 : 1;
  return 0;
}
