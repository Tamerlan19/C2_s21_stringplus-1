#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

  
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

TCase *create_s21_sscanf_p_tests(void) {
    TCase *tc_core_p;
    tc_core_p = tcase_create("Specifier= %p");

    tcase_add_test(tc_core_p, test_s21_sscanf_p_simple);
    tcase_add_test(tc_core_p, test_s21_sscanf_p);
    tcase_add_test(tc_core_p, test_s21_sscanf_p_suppress);
    tcase_add_test(tc_core_p, test_s21_sscanf_p_combination);

  return tc_core_p;
}