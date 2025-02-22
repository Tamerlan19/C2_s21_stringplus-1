#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_COUNT 10
#define TEST_VAR 3

typedef struct {
  char spec[10];
  char type[50];
  char init[50];
} spec_type;

// Функция для создания тестов
char *get_input(int t) {
  char *inputs[TEST_COUNT] = {
      "123 456789 3.14159",      // для %hd %ld %Lf
      "12345 ignore X",          // для %5d %*s %c
      "12.34 255 FF",            // для %5.2f %hhu %x
      "hello Z 77 9999",         // для %s %c %o %u
      "1.23E4 3.14G 0.00001 %",  // для %E %G %g %%
      "0x123abc 9F 2.71e-3",     // для %p %X %e
      "-128 4294967295 2.71828", // для %hhd %lu %Lf
      "longword X FF",           // для %10s %*c %X
      "77 8888 1A2B hello",      // для %o %u %x %s
      "12.345 1.2E5 255"         // для %5.3g %LE %hhu
  };
  return inputs[t];
}
spec_type get_fmt(int t) {
  if (t > TEST_COUNT || t < 0) {
    t = TEST_COUNT - t;
  }
  spec_type spec[50] = {
      {"%d", "int ", "=555"}, // Целое число (int)
      {"%u", "unsigned int ", "=123"}, // Беззнаковое целое число (unsigned int)
      {"%f", "float ", "=1.123"}, // Вещественное число (float)
      {"%c", "char ", "='A'"},    // Символ (char)
      {"%s", "char [1024]", "=\"ABC\""},    // Строка (char *)
      {"%p", "unsigned int ", "=0x123ABC"}, // Указатель (void *)
      {"%x", "unsigned int ", "=123"}, // Шестнадцатеричное целое число (int)
      {"%X", "unsigned int ",
       "=123"}, // Шестнадцатеричное целое число (int, заглавные буквы)
      {"%o", "unsigned int ", "=123"}, // Восьмеричное целое число (int)
      {"%i", "int ",
       "=-123"}, // Целое число (автоматическое определение системы счисления)
      {"%e", "float ",
       "=1.123"}, // Вещественное число в научной нотации (float)
      {"%E", "float ", "=1.123"}, // Вещественное число в научной нотации
                                  // (float, заглавные буквы)
      {"%g", "float ", "=1.123"}, // Вещественное число в кратчайшей форме
                                  // (float или scientific)
      {"%G", "float ", "=1.123"}, // Вещественное число в кратчайшей форме
                                  // (float или scientific, заглавные буквы)
      {"%%", "", ""} // Символ процента (%)
  };

  return spec[t];
}
int add_checks(spec_type fmt, char *checks, int i) {
  // char checks[100] = {0};
  int res = 0;
  char ch_var[1000] = {0};
  sprintf(ch_var, "var%d, var%d_s21);\n", i, i);
  if (strpbrk(fmt.spec, "s") != NULL) {
    strcat(checks, "  ck_assert_str_eq(");
  } else if (strpbrk(fmt.spec, "feEgG") != NULL) {
    strcat(checks, "  ck_assert_double_eq(");
  } else {
    strcat(checks, "  ck_assert_int_eq(");
  }
  strcat(checks, ch_var);
  return res;
}

int get_var(spec_type fmt[TEST_VAR], char *vars, char *args_sscanf,
            char *args_sscanf_s21, char *args_fmt, char *checks,
            const char *fmt_spr) {
  int res = 0;
  int i = 0;
  while (i < TEST_VAR) {
    if (strlen(fmt[i].type) > 1) {
      char tmp[1000] = {0};

      sprintf(tmp, "  %svar%d%s,var%d_s21%s;\n", fmt[i].type, i, fmt[i].init, i,
              fmt[i].init);
      strcat(vars, tmp);
      char var[10] = {0}, var_s21[10] = {0};
      sprintf(var, "var%d", i);
      sprintf(var_s21, "var%d_s21", i);
      if (strlen(args_sscanf) > 1) {
        if (strchr(fmt[i].spec, 's') == NULL) {
          strcat(args_sscanf, ",&");
          strcat(args_sscanf_s21, ",&");
        } else {
          strcat(args_sscanf, ",");
          strcat(args_sscanf_s21, ",");
        }
      } else {
        if (strchr(fmt[i].spec, 's') == NULL) {
          strcat(args_sscanf, "&");
          strcat(args_sscanf_s21, "&");
        }
      }
      strcat(args_sscanf, var);
      strcat(args_sscanf_s21, var_s21);
      strcat(args_fmt, fmt[i].spec);
      strcat(args_fmt, fmt_spr);

      add_checks(fmt[i], checks, i);
    }

    i++;
  }
  return res;
}

char *get_separator(int i) {
  char *spr[10] = {"", " ", ",", ".", ":", "%", "_", "  ", "   ", "!"};

  return spr[i];
}

int main(void) {
  int res = 0;

  const char *flname = "test_gen_s21_sscanf.c";
  FILE *file = fopen(flname, "w");
  if (file == NULL) {
    perror("Failed to open file for writing");
    return EXIT_FAILURE;
  }
  int n = 0;
  fprintf(file, "#include \"s21_string.h\"\n#include <check.h>\n");

  for (int j = 0; j < TEST_COUNT; j++) { // TEST_STRING
    char *input = get_input(j);

    for (int s = 0; s < 10; s++) { // separator
      char *fmt_spr = get_separator(s);

      for (int i = 0; i < TEST_COUNT; i++) {

        spec_type fmt_arr[50];
        char test_name[50];
        sprintf(test_name, "test_s21_sscanf_cmpx_%03d", n + 1);

        char args_sscanf[1000] = {0};
        char args_sscanf_s21[1000] = {0};
        char args_fmt[1000] = {0};
        char vars[1000] = {0};
        char checks[1000] = {0};

        for (int i = 0; i < TEST_VAR; i++) {
          fmt_arr[i] = get_fmt(i);
        }

        get_var(fmt_arr, vars, args_sscanf, args_sscanf_s21, args_fmt, checks,
                fmt_spr);
        fprintf(file, "\nSTART_TEST(%s) {\n\
  const char *input=\"%s\";\n\
%s\
  const char *fmt=\"%s\";\n\n\
  int ret = sscanf(input,fmt,%s);\n\
  int ret_s21 = s21_sscanf(input,fmt,%s);\n\n\
%s\
  ck_assert_int_eq(ret, ret_s21);\n\
  }\n\
  END_TEST \n\
  ",
                test_name, input, vars, args_fmt, args_sscanf, args_sscanf_s21,
                checks);
        n++;
      }
    }
  }

  if (file == NULL) {
    perror("Failed to open file for writing");
    return EXIT_FAILURE;
  }

  fprintf(file, "\nSuite *s21_sscanf_gen_suite(void) {\n\
  Suite *s;\n\
  TCase *tc_core;\n\
  s = suite_create(\"s21_sscanf_gen\");\n\
  tc_core = tcase_create(\"Core\");\n");
  for (int r = 0; r < n; r++) {
    fprintf(file, "\ttcase_add_test(tc_core, test_s21_sscanf_cmpx_%03d);\n",
            r + 1);
  }

  fprintf(file, "\n  suite_add_tcase(s, tc_core);\n\
  return s;\n}");

  fprintf(file, "\n\n\nint main(void) {\n\
  SRunner *sr;\n\
  sr = srunner_create(s21_sscanf_gen_suite());\n\
  srunner_run_all(sr, CK_NORMAL);\n\
  srunner_free(sr);\n\
  return 0;\n}");

  fclose(file);
  return res;
}