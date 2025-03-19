#include "../s21_string.h"
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>

TCase *create_s21_sscanf_d_tests(void);
TCase *create_s21_sscanf_c_tests(void);
TCase *create_s21_sscanf_s_tests(void);
TCase *create_s21_sscanf_u_tests(void);
TCase *create_s21_sscanf_n_tests(void);
TCase *create_s21_sscanf_i_tests(void);
TCase *create_s21_sscanf_o_tests(void);
TCase *create_s21_sscanf_x_tests(void);
TCase *create_s21_sscanf_p_tests(void);
TCase *create_s21_sscanf_g_tests(void);
TCase *create_s21_sscanf_f_tests(void);
TCase *create_s21_sscanf_pcnt_tests(void);
TCase *create_s21_sscanf_complex_tests(void);

START_TEST(test_s21_sscanf_cmpx_6523) {
  const char *input = "98  11111295A 4294967295";
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

Suite *s21_sscanf_suite(void) {
  Suite *suite;

  suite = suite_create("s21_sscanf");

  TCase *tc_core_d = create_s21_sscanf_d_tests();
  suite_add_tcase(suite, tc_core_d);
  TCase *tc_core_c = create_s21_sscanf_c_tests();
  suite_add_tcase(suite, tc_core_c);
  TCase *tc_core_u = create_s21_sscanf_u_tests();
  suite_add_tcase(suite, tc_core_u);
  TCase *tc_core_n = create_s21_sscanf_n_tests();
  suite_add_tcase(suite, tc_core_n);
  TCase *tc_core_i = create_s21_sscanf_i_tests();
  suite_add_tcase(suite, tc_core_i);
  TCase *tc_core_s = create_s21_sscanf_s_tests();
  suite_add_tcase(suite, tc_core_s);
  TCase *tc_core_o = create_s21_sscanf_o_tests();
  suite_add_tcase(suite, tc_core_o);
  TCase *tc_core_x = create_s21_sscanf_x_tests();
  suite_add_tcase(suite, tc_core_x);
  TCase *tc_core_p = create_s21_sscanf_p_tests();
  suite_add_tcase(suite, tc_core_p);
  TCase *tc_core_g = create_s21_sscanf_g_tests();
  suite_add_tcase(suite, tc_core_g);
  TCase *tc_core_f = create_s21_sscanf_f_tests();
  suite_add_tcase(suite, tc_core_f);
  TCase *tc_core_pcnt = create_s21_sscanf_pcnt_tests();
  suite_add_tcase(suite, tc_core_pcnt);
  TCase *tc_core_cmpx = create_s21_sscanf_complex_tests();
  suite_add_tcase(suite, tc_core_cmpx);

  //[ ] Delete debug case
  TCase *tc_debug;
  tc_debug = tcase_create("Debug");
  tcase_add_test(tc_debug, test_s21_sscanf_cmpx_6523);
  suite_add_tcase(suite, tc_debug);

  return suite;
}
