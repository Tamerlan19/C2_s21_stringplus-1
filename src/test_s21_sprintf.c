#include "s21_string.h"
#include <check.h>
#include <stdio.h>
#include <string.h>

TCase *tcase_s21_sprintf_d(void);
TCase *tcase_s21_sprintf_c(void);
TCase *tcase_s21_sprintf_f(void);
TCase *tcase_s21_sprintf_u(void);
TCase *tcase_s21_sprintf_e(void);
TCase *tcase_s21_sprintf_x(void);
TCase *tcase_s21_sprintf_g(void);
TCase *tcase_s21_sprintf_p(void);
TCase *tcase_s21_sprintf_o(void);
TCase *tcase_s21_sprintf_s(void);
TCase *tcase_s21_sprintf_pcnt(void);

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");

  TCase *tc_core_d = tcase_s21_sprintf_d();
  suite_add_tcase(s, tc_core_d);
  TCase *tc_core_c = tcase_s21_sprintf_c();
  suite_add_tcase(s, tc_core_c);
  TCase *tc_core_f = tcase_s21_sprintf_f();
  suite_add_tcase(s, tc_core_f);
  TCase *tc_core_u = tcase_s21_sprintf_u();
  suite_add_tcase(s, tc_core_u);
  TCase *tc_core_s = tcase_s21_sprintf_s();
  suite_add_tcase(s, tc_core_s);
  TCase *tc_core_o = tcase_s21_sprintf_o();
  suite_add_tcase(s, tc_core_o);
  TCase *tc_core_p = tcase_s21_sprintf_p();
  suite_add_tcase(s, tc_core_p);

  TCase *tc_core_e = tcase_s21_sprintf_e();
  suite_add_tcase(s, tc_core_e);
  TCase *tc_core_x = tcase_s21_sprintf_x();
  suite_add_tcase(s, tc_core_x);
  TCase *tc_core_g = tcase_s21_sprintf_g();
  suite_add_tcase(s, tc_core_g);
  TCase *tc_core_pcnt = tcase_s21_sprintf_pcnt();
  suite_add_tcase(s, tc_core_pcnt);

  tc_core = tcase_create("Core");

  suite_add_tcase(s, tc_core);

  //[ ] удалить отладочные кейсы
  TCase *tc_debug;
  tc_debug = tcase_create("Debug");
  //   tcase_add_test(tc_debug, test_s21_sprintf_o_hash_flag);
  // tcase_add_test(tc_debug, test_s21_sprintf_p_width_zero_padding);
  suite_add_tcase(s, tc_debug);

  return s;
}
