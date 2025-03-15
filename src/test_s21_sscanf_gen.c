#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "s21_string.h"

#define TEST_COUNT 5000
#define TEST_VAR 3
#define SPEC_COUNTS 15
#define MAX_BUFFER_SIZE 1024

typedef struct {
  char spec[50];
  char type[50];
  char init[50];
  char input[1024];
} spec_type;

// Функция для создания тестов
// const char *get_input(int t) {
//   const char *inputs[20] = {
//       "123 456789 3.14159",      // для %hd %ld %Lf
//       "12345 ignore X",          // для %5d %*s %c
//       "12.34 255 FF",            // для %5.2f %hhu %x
//       "hello Z 77 9999",         // для %s %c %o %u
//       "1.23E4 3.14G 0.00001 %",  // для %E %G %g %%
//       "0x123abc 9F 2.71e-3",     // для %p %X %e
//       "-128 4294967295 2.71828", // для %hhd %lu %Lf
//       "longword X FF",           // для %10s %*c %X
//       "77 8888 1A2B hello",      // для %o %u %x %s
//       "12.345 1.2E5 255"         // для %5.3g %LE %hhu
//       "123 456789 3.14159",      // для %hd %ld %Lf
//       "12345 ignore X",          // для %5d %*s %c
//       "12.34 255 FF",            // для %5.2f %hhu %x
//       "hello Z 77 9999",         // для %s %c %o %u
//       "1.23E4 3.14G 0.00001 %",  // для %E %G %g %%
//       "0x123abc 9F 2.71e-3",     // для %p %X %e
//       "-128 4294967295 2.71828", // для %hhd %lu %Lf
//       "longword X FF",           // для %10s %*c %X
//       "77 8888 1A2B hello",      // для %o %u %x %s
//       "12.345 1.2E5 255"         // для %5.3g %LE %hhu
//   };
//   return inputs[t];
// }

// int set_input_for_specs(const spec_type *spec, int t, char *str) { //
// 2025-02-25 19:43:22 @morrigem: fix style: neve used

//   int res = 0;
//   for (int i = 0; i < t; i++) {
//     // DEBUG_PRINT("Add string into inpuit=%s",spec[i].input);
//     strcat(str, spec[i].input);
//   }
//   return res;
// }

int set_input_str(spec_type *spec) {
  int res = 0;
  char inputs[100][MAX_BUFFER_SIZE];
  // srand(time(NULL));

  if (strchr(spec->spec, 's') != NULL || strchr(spec->spec, 'c') != NULL) {
    const char *test_str[83] = {
        "123",
        "456789",
        "3.14159",
        "12345",
        "ignore",
        "X",
        "12.34",
        "255",
        "FF",
        "hello",
        "Z",
        "77",
        "9999",
        "1.23E4",
        "3.14G",
        "0.00001",
        "%%",
        "0x123abc",
        "9F",
        "2.71e-3",
        "-128",
        "4294967295",
        "2.71828",
        "longword",
        "X",
        "FF",
        "77",
        "8888",
        "1A2B",
        "hello",
        "12.345",
        "1.2E5",
        "255"
        "123",
        "456789",
        "3.14159",
        "12345",
        "ignore",
        "X",
        "12.34",
        "255",
        "FF",
        "hello",
        "Z",
        "77",
        "9999",
        "1.23E4",
        "3.14G",
        "0.00001",
        "%",
        "-128",
        "4294967295",
        "2.71828",
        "0x123abc",
        "9F",
        "2.71e-3",
        "12.345",
        "1.2E5",
        "255"
        "-128",
        "4294967295",
        "2.71828",
        "longword",
        "X",
        "FF",
        "77",
        "8888",
        "1A2B",
        "hello",
    };

    for (int i = 0; i < 100; i++) {
      int c = rand() % 66;
      strncpy(inputs[i], test_str[c], 99);
      inputs[i][strlen(test_str[c])] = '\0';
    }

  } else if (strchr(spec->spec, 'G') != NULL ||
             strchr(spec->spec, 'g') != NULL ||
             strchr(spec->spec, 'e') != NULL ||
             strchr(spec->spec, 'E') != NULL ||
             strchr(spec->spec, 'f') != NULL) {
    const char *test_str[50] = {
        "123",    "456789",     "3.14159", "12.34",   "255",         "9.45",
        "1.23E4", "3.14",       "0.00001", "-128",    "4294,967295", "2.71828",
        "12.345", "1.2E5",      "255",     "4.723e6", "456789",      "3.14159",
        "12.34",  "255",        "9.8e-3",  "1.23E4",  "314",         "0.00001",
        "-128",   "4294967295", "2.71828", "12.345",  "1.2E5",       "255"};
    for (int i = 0; i < 100; i++) {
      int c = rand() % 30;
      strncpy(inputs[i], test_str[c], 99);
      inputs[i][strlen(test_str[c])] = '\0';
    }

  } else {
    const char *test_str[50] = {
        "123",    "456789",     "3.14159", "12.34",  "255",         "9.45",
        "1.234",  "314",        "0.00001", "-128",   "4294,967295", "2.71828",
        "12.345", "1.2",        "255",     "4.723",  "456789",      "3.14159",
        "12.34",  "255",        "98",      "1.23",   "3.14",        "0",
        "-128",   "4294967295", "2.71828", "12.345", "1.2",         "255"};
    for (int i = 0; i < 100; i++) {
      int c = rand() % 30;
      strncpy(inputs[i], test_str[c], 99);
      inputs[i][strlen(test_str[c])] = '\0';
    }
  }
  strcpy(spec->input, inputs[rand() % 100]);
  // DEBUG_PRINT("Set inputs =|%s| for spec=%s\n", spec->input,spec->spec);
  return res;
}

//`%[*][ширина][длина]спецификатор`

/**
 * @brief Get the format specifier type based on the given index.
 *
 * This function takes an integer index `t` and returns the corresponding format
 * specifier type. If the index is out of range, it adjusts the index to be
 * within the valid range. The function initializes an array of `spec_type`
 * structures with various format specifiers and their corresponding types. It
 * sets the input string and format flags for the selected specifier and returns
 * the selected specifier.
 *
 * @param t The index of the format specifier to retrieve.
 * @return The selected format specifier type.
 */
int set_fmt_flags(spec_type *fmt) {
  int res = 0;
  char res_fmt[10] = "%";
  const char *spec = fmt->spec;

  int random_width = rand() % 20;
  if (strpbrk(fmt->spec, "np%") == NULL) {
    const char *width[] = {"", "0", "1", "2", "",  "3",  "4",  "",   "5", "6",
                           "", "7", "",  "8", "9", "10", "15", "20", "",  "50"};
    strcat(res_fmt, width[random_width]);
    // printf("DEBUG: res_fmt=%s. Add width=%s\n", res_fmt,
    // width[random_width]);
  }
  // sprintf(res_fmt, "%d", width[random_number]);
  if (strlen(fmt->type) > 1) {
    if (strpbrk(spec, "sc") != NULL) {
      const char *length[3] = {"", "l"};
      int random_len = rand() % 2;
      if (strpbrk(length[random_len], "l") != NULL) {
        const char tmp[20] = "wchar_t ";
        memset(fmt->type, '\0', strlen(fmt->type));
        // strcat(tmp,fmt->type);
        memmove(fmt->type, tmp, strlen(tmp));
      }
      strcat(res_fmt, length[random_len]);
    } else if (strpbrk(spec, "feEgG") != NULL) {
      int random_len = rand() % 2;
      const char *length[3] = {"", "L"};
      if (strpbrk(length[random_len], "L") != NULL) {
        char tmp[50] = "long double ";
        memmove(fmt->type, tmp, strlen(tmp));
      }
      strcat(res_fmt, length[random_len]);
    } else if (strpbrk(spec, "%") != NULL) {
      int random_len = rand() % 2;
      const char *length[3] = {"", "L"};
      if (strpbrk(length[random_len], "L") != NULL) {
        char tmp[50] = "long ";
        // strcat(tmp,fmt->type);
        memmove(fmt->type, tmp, strlen(tmp));
      }
      strcat(res_fmt, length[random_len]);
    }
  }
  // printf("DEBUG: after add legth flags: res_fmt=%s\n", res_fmt);

  strcat(res_fmt, spec); // add specifiers

  memmove(fmt->spec, res_fmt, strlen(res_fmt));
  // printf("DEBUG: spec=%s\n", fmt->spec);

  return res;
}
spec_type get_fmt(int t) {
  if (t >= SPEC_COUNTS) {
    t = SPEC_COUNTS - t;
  } else if (t < 0) {
    t = SPEC_COUNTS + t;
  }

  spec_type spec[SPEC_COUNTS] = {
      {"d", "int ", "555", ""},
      {"u", "unsigned int ", "123", ""},
      {"f", "float ", "1.123", ""},
      {"c", "char ", "\"A\"", ""},
      {"s", "char ", "\"ABC\"", ""},
      {"x", "unsigned int ", "123", ""},
      {"X", "unsigned int ", "123", ""},
      {"o", "unsigned int ", "123", ""},
      {"i", "int ", "-123", ""},
      {"e", "float ", "1.123", ""},
      {"E", "float ", "1.123", ""},
      {"g", "float ", "1.123", ""},
      {"G", "float ", "1.123", ""},
      {"%", "", "", ""}
      // {"p", "unsigned int ", "0x123ABC"},
  };
  if (t <= SPEC_COUNTS) {

    set_input_str(&spec[t]);
    set_fmt_flags(&spec[t]);
  }
  // memcpy(spec->spec, s, strlen(s));
  return spec[t];
}
int add_checks(spec_type fmt, char *checks, int i) {
  // char checks[100] = {0};
  int res = 0;
  char ch_var[1000] = {0};
  // sprintf(ch_var, "var%d, var%d_s21);\n", i, i);
  sprintf(ch_var, "var%d, var%d_s21", i + 1, i + 1);
  if (strpbrk(fmt.spec, "sc") != NULL) {
    // strcat(checks, "  ck_assert_str_eq(");
    if (strpbrk(fmt.spec, "l") != NULL) {
      strcat(checks, "  ck_assert(compare_wstrings(");
      strcat(ch_var, ")");
    } else {
      strcat(checks, "  ck_assert_str_eq(");
    }
  } else if (strpbrk(fmt.spec, "feEgG") != NULL) {
    strcat(checks, "  ck_assert_double_eq_tol(");
    strcat(ch_var, ",10-6");
  } else {
    strcat(checks, "  ck_assert_int_eq(");
  }
  strcat(ch_var, ");\n");
  strcat(checks, ch_var);
  return res;
}

int get_var(spec_type fmt[TEST_VAR], char *vars, char *args_sscanf,
            char *args_sscanf_s21, char *args_fmt, char *checks,
            char **fmt_spr) {
  int res = 0;
  int i = 0;
  while (i < TEST_VAR) {
    if (strlen(fmt[i].type) > 1) {
      char tmp[1000] = {0};
      if (strpbrk(fmt[i].spec, "s") != NULL ||
          (strpbrk(fmt[i].spec, "c") != NULL)) {
        if (strchr(fmt[i].spec, 'l') != NULL) {
          sprintf(tmp, "  %svar%d[1024]=L%s,var%d_s21[1024]=L%s;\n",
                  fmt[i].type, i + 1, fmt[i].init, i + 1, fmt[i].init);
        } else
          sprintf(tmp, "  %svar%d[1024]=%s,var%d_s21[1024]=%s;\n", fmt[i].type,
                  i + 1, fmt[i].init, i + 1, fmt[i].init);
      } else if ((strlen(fmt[i].init) > 1)) {
        sprintf(tmp, "  %svar%d=%s,var%d_s21=%s;\n", fmt[i].type, i + 1,
                fmt[i].init, i + 1, fmt[i].init);
      }

      strcat(vars, tmp);
      char var[30] = {0}, var_s21[30] = {0};
      if (strchr(fmt[i].spec, 'c') != NULL ||
          strchr(fmt[i].spec, 's') != NULL) {
        sprintf(var, ", var%d", i + 1);
        sprintf(var_s21, ", var%d_s21", i + 1);
      } else {
        sprintf(var, ",&var%d", i + 1);
        sprintf(var_s21, ",&var%d_s21", i + 1);
      }

      strcat(args_sscanf, var);
      strcat(args_sscanf_s21, var_s21);
      strcat(args_fmt, fmt[i].spec);
      strcat(args_fmt, fmt_spr[i]);

      add_checks(fmt[i], checks, i);
    }

    i++;
  }
  return res;
}

const char *get_separator(int i) {
  const char *spr[15] = {"",    " ", ",", ".", ":",   "%%",  "_", "  ",
                         "   ", "!", ",", "$", "\\n", "\\t", "A"};
  return spr[i];
}

void insert_header(FILE *file) {
  fprintf(file, "#include \"s21_string.h\"\n#include <check.h>\n#include "
                "<stdio.h>\n#include <wchar.h>\n#include <locale.h>\n\n");
}

void insert_cmp_wstrings(FILE *file) {
  fprintf(file,
          "static int compare_wstrings(const wchar_t *a, const wchar_t *b) {\n\
    setlocale(LC_ALL, \"en_US.utf8\");\n\
    if (a == NULL && b == NULL)\n\
      return 1;\n\
    if (a == NULL || b == NULL)\n\
      return 0;\n\
    return wcscmp(a, b) == 0;\n}\n");
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
  int insert_wide = 0;
  insert_header(file);
  // insert_cmp_wstrings(file);
  int stop = 0;
  for (int i = 0; n < TEST_COUNT && !(stop); i++) { // specifiers
    spec_type fmt_arr[50];
    char test_name[50];
    sprintf(test_name, "test_s21_sscanf_cmpx_%04d", n + 1);
    char args_sscanf[1000] = {0};
    char args_sscanf_s21[1000] = {0};
    char args_fmt[1000] = {0};
    char vars[1000] = {0};
    char checks[1000] = {0};
    char input[MAX_BUFFER_SIZE] = {0};
    char *fmt_spr[50];

    int max_var = TEST_VAR;
    for (int vrs = 0, i = 0; i < max_var; i++) {
      int random_number = rand() % SPEC_COUNTS;
      int s = rand() % 15; // separator
      const char *spr = get_separator(s);
      fmt_spr[i] = malloc(11);
      strncpy(fmt_spr[i], spr, strlen(spr));
      fmt_spr[i][strlen(spr)] = '\0';
      // printf("DEBUG: i=%d, random_number=%d\n", i, random_number);
      fmt_arr[i] = get_fmt(random_number);
      strcat(input, fmt_arr[i].input);
      strcat(input, fmt_spr[i]);
      if (strpbrk(fmt_arr[i].spec, "sc") != NULL) {
        if (strpbrk(fmt_arr[i].spec, "l") != NULL && insert_wide == 0) {
          insert_wide = 1;
        }
      }

      if (strlen(fmt_arr[i].init) > 0) {
        // printf("DEBUG: %c\n", fmt_arr[i].spec[i]);
        vrs++;
      }
      if (i == TEST_VAR - 1 && vrs == 0) {
        printf("Addddddddddddddd variable\n");
        max_var++;
        i--;
      }
      // free(fmt_spr[i]);
    }
    if (insert_wide == 1) {
      insert_cmp_wstrings(file);
      insert_wide++;
    }

    get_var(fmt_arr, vars, args_sscanf, args_sscanf_s21, args_fmt, checks,
            fmt_spr);

    fprintf(file, "\nSTART_TEST(%s) {\n\
  const char *input=\"%s\";\n\
%s\
  const char *fmt=\"%s\";\n\n\
  int ret = sscanf(input,fmt%s);\n\
  int ret_s21 = s21_sscanf(input,fmt %s);\n\n\
  DEBUG_PRINT(\"ret=%%d,ret_s21=%%d\\n\",ret,ret_s21);\n\
%s\
  ck_assert_int_eq(ret, ret_s21);\n\
DEBUG_PRINT(\"Test %s is passed.\\n\");\n\
}\n\
END_TEST \n\
",
            test_name, input, vars, args_fmt, args_sscanf, args_sscanf_s21,
            checks, test_name);
    n++;
    if (n == TEST_COUNT) {
      stop = 1;
    }
  }

  fprintf(file, "\nSuite *s21_sscanf_gen_suite(void) {\n\
  Suite *s;\n\
  TCase *tc_core;\n\
  s = suite_create(\"s21_sscanf_gen\");\n\
  tc_core = tcase_create(\"Core\");\n");
  for (int r = 0; r < n; r++) {
    fprintf(file, "\ttcase_add_test(tc_core, test_s21_sscanf_cmpx_%04d);\n",
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