#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST_COUNT 20
#define TEST_VAR 3
#define SPEC_COUNTS 15

typedef struct {
  char spec[50];
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


//`%[*][ширина][длина]спецификатор`

int set_fmt_flags(spec_type *fmt) {
  int res = 0;
  char res_fmt[10]="%";
  char *spec=fmt->spec;


  int random_width = rand() % 20;
  char *width[20] = {"","0","1","2","","3","4","","5","6","","7","","8","9","10","15","20","","50"};
  if (strpbrk(fmt->spec, "np%") == NULL) {  
    strcat(res_fmt,width[random_width]);
    printf("DEBUG: res_fmt=%s. Add width=%s\n", res_fmt, width[random_width]);
  }
    // sprintf(res_fmt, "%d", width[random_number]);
    
    if (strpbrk(spec, "sc") != NULL) {
      char *length[3] = {"","l"};
      int random_len = rand() % 2;
        if (strpbrk(length[random_len],"l") !=NULL) {
          char tmp[20]="wchar_t ";
          memset(fmt->type,'\0',strlen(fmt->type));
          // strcat(tmp,fmt->type);
          memmove(fmt->type, tmp, strlen(tmp));
        }
        strcat(res_fmt,length[random_len]);
    } else if (strpbrk(spec, "feEgG") != NULL) {
      int random_len = rand() % 2;
      char *length[3] = {"","L"};
        char tmp[50]="long double ";
        memmove(fmt->type, tmp, strlen(tmp));
      strcat(res_fmt,length[random_len]);
    } else {
      int random_len = rand() % 2;
      char *length[3] = {"","L"};
        char tmp[50]="long ";
        strcat(tmp,fmt->type);
        memmove(fmt->type, tmp, strlen(tmp));
      strcat(res_fmt,length[random_len]);
    }
    printf("DEBUG: after add legth flags: res_fmt=%s\n", res_fmt);
    
    strcat(res_fmt, spec); //add specifiers

  memmove(fmt->spec, res_fmt, strlen(res_fmt));
  printf("DEBUG: spec=%s\n", fmt->spec);

  return res;
}
spec_type get_fmt(int t) {
  if (t > SPEC_COUNTS || t < 0) {
    t = SPEC_COUNTS - t;
  }
  spec_type spec[SPEC_COUNTS] = {
      {"d", "int ", "=555"}, 
      {"u", "unsigned int ", "=123"}, 
      {"f", "float ", "=1.123"}, 
      {"c", "char ", "='A'"},    
      {"s", "char [1024]", "=\"ABC\""},    
      {"p", "unsigned int ", "=0x123ABC"}, 
      {"x", "unsigned int ", "=123"}, 
      {"X", "unsigned int ", "=123"}, 
      {"o", "unsigned int ", "=123"},
      {"i", "int ",       "=-123"}, 
      {"e", "float ",       "=1.123"}, 
      {"E", "float ", "=1.123"},                                   
      {"g", "float ", "=1.123"},                                   
      {"G", "float ", "=1.123"},                                  
      {"%", "", ""}
      // {"hd", "int ", "=555"}, 
      // {"hu", "unsigned int ", "=123"}, 
      // {"Lf", "float ", "=1.123"}, 
      // {"lc", "char ", "='A'"},    
      // {"ls", "char [1024]", "=\"ABC\""},    
      // {"hp", "unsigned int ", "=0x123ABC"}, 
      // {"hx", "unsigned int ", "=123"}, 
      // {"hX", "unsigned int ", "=123"}, 
      // {"ho", "unsigned int ", "=123"},
      // {"hi", "int ",       "=-123"}, 
      // {"Le", "float ",       "=1.123"}, 
      // {"LE", "float ", "=1.123"},                                   
      // {"Lg", "float ", "=1.123"},                                   
      // {"LG", "float ", "=1.123"}                                 
  };

  set_fmt_flags(&spec[t]);
  // memcpy(spec->spec, s, strlen(s));
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
  srand(time(NULL));
  const char *flname = "test_gen_s21_sscanf.c";
  FILE *file = fopen(flname, "w");
  if (file == NULL) {
    perror("Failed to open file for writing");
    return EXIT_FAILURE;
  }
  int n = 0;
  fprintf(file, "#include \"s21_string.h\"\n#include <check.h>\n");

  for (int j = 0; j < TEST_COUNT && n < 2; j++) { // TEST_STRING
    char *input = get_input(j);

    for (int s = 0; s < 10; s++) { // separator
      char *fmt_spr = get_separator(s);

      for (int i = 0; i < TEST_COUNT; i++) { //specifiers

        spec_type fmt_arr[50];
        char test_name[50];
        sprintf(test_name, "test_s21_sscanf_cmpx_%03d", n + 1);

        char args_sscanf[1000] = {0};
        char args_sscanf_s21[1000] = {0};
        char args_fmt[1000] = {0};
        char vars[1000] = {0};
        char checks[1000] = {0};

        for (int i = 0; i < TEST_VAR; i++) {

          int random_number = rand() % SPEC_COUNTS;
          printf("DEBUG: i=%d, random_number=%d\n", i, random_number);
          fmt_arr[i] = get_fmt(random_number);
        }
        n++;

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