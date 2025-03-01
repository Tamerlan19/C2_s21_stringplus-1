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
  // TCase *tc_debug;
  // tc_debug = tcase_create("Debug");
  // suite_add_tcase(suite, tc_debug);

  return suite;
}
