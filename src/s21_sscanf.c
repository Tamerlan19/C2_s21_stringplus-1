#include "s21_string.h"
#include "s21_utils.c"

float s21_pow(int x, int y);
int get_number(const char *p, long int *res);
int proc_spec_s(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_d(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_s(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_f(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_c(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_u(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_n(long int result, va_list args, const Specifiers st_spec);
int proc_spec_i(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_o(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_x(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_p(const char *str, va_list args, const Specifiers st_spec);
int is_alpha(char c);
int is_digit(char c);
int is_space(char c);

int str_to_int(const char *p, long int *res, int base);

void proc_str(const char **p, int step, Specifiers st_spec, int *res) {
  DEBUG_PRINT("next_val(): step=%d, res =%d \n", step, *res);
  if (step > 0) {
    *p = *p + step;
    if (st_spec.flag != '*') {
      *res = *res + 1;
    }
  } else if (step < 0 && *res == 0) {
    *res = -1;
  }
  DEBUG_PRINT("next_val(): step=%d, res =%d \n", step, *res);
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  // Specifiers st_spec = {'*', -10, -1, '*', '*'};
  const char *p = str; // Указатель на входную строку
  const char *fmt = format; // Указатель на строку формата
  //%[*/ширина][длина]спецификатор.
  // int s=0;
  int res = 0;
  int stop = 0;
  if (p != S21_NULL && fmt != S21_NULL) {
    DEBUG_PRINT("String and Format is not NULL\n");
    while (*p && *fmt && !stop) {
      DEBUG_PRINT("Start cycle (while (*p && *fmt && !stop))!\n");
      // Skip separator in format string for non char types
      while ((*fmt == *p || *fmt == '%') && !stop) {
        if (*fmt == '%') {
          Specifiers st_spec = {' ', -10, -1, '*', '*'};
          DEBUG_PRINT("\n");
          DEBUG_PRINT(" str=%s\n", p);
          DEBUG_PRINT(" format=%s\n", fmt);
          fmt += parse_specifiers(fmt, &st_spec);
          DEBUG_PRINT("format after parse =%s\n", fmt);
          int step = 0;
          if (st_spec.specifier == 'c') {
            step = proc_spec_c(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT(" after process Char Result=%d\n", res);

          } else if (st_spec.specifier == 'd') {
            while ((is_space(*p)) && *p != '-') {
              DEBUG_PRINT("Noop symbol:|%c|\n", *p);
              p++;
            }
            step = proc_spec_d(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT(" after process %%d Result=%d\n", res);
            DEBUG_PRINT(" FINISH *String position=%s\n", p);

          } else if (st_spec.specifier == 'f') {
            while ((is_space(*p)) && *p != '-') {
              DEBUG_PRINT("Noop symbol:|%c|\n", *p);
              p++;
            }
            step = proc_spec_f(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT(" after process %%f Result=%d\n", res);
            DEBUG_PRINT(" FINISH *String position=%s\n", p);

          } else if (st_spec.specifier == 's') {
            step = proc_spec_s(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT("Incriment *p +step=%d\n", step);
            DEBUG_PRINT(" after process string Result=%d\n", res);
            DEBUG_PRINT(" p=|%s|\n", p);
            DEBUG_PRINT(" fmt=|%s|\n", fmt);
          } else if (st_spec.specifier == 'u') {
            DEBUG_PRINT("Start process %%u specificator...");
            step = proc_spec_u(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT("Incriment *p +step=%d\n", step);
            DEBUG_PRINT(" after process string Result=%d\n", res);
            DEBUG_PRINT(" p=|%s|\n", p);
            DEBUG_PRINT(" fmt=|%s|\n", fmt);

          } else if (st_spec.specifier == 'n') {
            DEBUG_PRINT("/nStart process %%n specificator...\n");
            long int r = p - str;
            proc_spec_n(r, args, st_spec);
          } else if (st_spec.specifier == 'i') {
            DEBUG_PRINT("/nStart process %%i (percent) specificator...\n");
            while ((is_space(*p)) && *p != '-') {
              DEBUG_PRINT("Noop symbol:|%c|\n", *p);
              p++;
            }
            step = proc_spec_i(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT(" after process %%n Result=%d\n", res);
            DEBUG_PRINT(" FINISH *String position=%s\n", p);
          } else if (st_spec.specifier == 'o') {
            while ((is_space(*p)) && *p != '-') {
              DEBUG_PRINT("Noop symbol:|%c|\n", *p);
              p++;
            }
            step = proc_spec_o(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT(" after process %%d Result=%d\n", res);
            DEBUG_PRINT(" FINISH *String position=%s\n", p);

          } else if (st_spec.specifier == 'x' || st_spec.specifier == 'X') {
            while ((is_space(*p)) && *p != '-') {
              DEBUG_PRINT("Noop symbol:|%c|\n", *p);
              p++;
            }
            step = proc_spec_x(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT(" after process %%d Result=%d\n", res);
            DEBUG_PRINT(" FINISH *String position=%s\n", p);

          } else if (st_spec.specifier == 'p') {
            while ((is_space(*p)) && *p != '-') {
              DEBUG_PRINT("Noop symbol:|%c|\n", *p);
              p++;
            }
            step = proc_spec_p(p, args, st_spec);
            proc_str(&p, step, st_spec, &res);
            DEBUG_PRINT(" after process %%p Result=%d\n", res);
            DEBUG_PRINT(" FINISH *String position=%s\n", p);

          } else if (st_spec.specifier == '%') {
            DEBUG_PRINT("/nStart process %% (percent) specificator...\n");
            if (*(p) == '%') {
              p++;
            } else
              stop = 1;

            step = 0;
          }

          noop_space(&fmt);
          noop_space(&p);
        } else if (*fmt == *p) {
          DEBUG_PRINT("Equal char: *fmt=%c is eq *p=%c\n", *fmt, *p);
          DEBUG_PRINT("Equal char: str=%s\n", p);
          DEBUG_PRINT("Equal char: format=%s\n", fmt);
          fmt++;
          p++;
        } else {
          stop = 1;
        }
      }
      stop = 1;
    }
  } else {
    DEBUG_PRINT("Format or Input is NULL\n");
    res = -1;
  }
  if (stop == 0) {
    res = -1;
  }
  DEBUG_PRINT(" FINISH result=%d\n", res);
  va_end(args);

  return res;
}

/**
 * @brief Reads a wide character from a multibyte string.
 *
 * @param p A pointer to the multibyte string.
 * @param wch A pointer to a wide character where the read character will be
 * stored.
 * @return The number of bytes read, or -1 if an error occurred.
 */
int read_wchar(const char **p, wchar_t *wch) {
  int res = 0;
  int bytes_read = mbtowc(wch, *p, MB_CUR_MAX);
  DEBUG_PRINT(" wide Char wch=%x p=%s\n", *wch, *p);
  if (bytes_read <= 0) {
    res = -1;
  } else {
    *p += bytes_read;
  }
  DEBUG_PRINT(" result read_wchar=%d\n", res);
  return res;
}

/**
 * @brief Parses a number from a string.
 *
 * @param p The string to parse.
 * @param res A pointer to a long int where the parsed number will be stored.
 * @return The number of characters parsed.
 */
int get_number(const char *p, long int *res) {
  *res = 0;
  int i = 0;
  int znak = 1;
  if (*p == '-' && is_digit(*(p + 1))) {
    znak = -1;
    p++;
    i++;
  }
  while (is_digit(*p)) {
    *res = *res * 10 + (*p - '0');
    p++;
    i++;
  }
  *res *= znak;
  return i;
}

int str_to_int(const char *p, long int *res, int base) {
  *res = 0;
  int i = 0;
  int znak = 1;
  if (*p == '-' && is_digit(*(p + 1))) {
    znak = -1;
    p++;
    i++;
  }
  if (base == 8) {
    while (is_octa(*p)) {
      *res = *res * base + (*p - '0');
      p++;
      i++;
    }
  } else if (base == 16) {
    if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X')) {
      p += 2;
    }
    p = s21_to_upper(p);
    while (is_hex(*p)) {
      if (is_digit(*p)) {
        *res = *res * base + (*p - '0');
      } else
        *res = *res * base + (*p - '0' - 7);

      p++;
      i++;
    }
  } else {

    while (is_digit(*p)) {
      *res = *res * base + (*p - '0');
      p++;
      i++;
    }
  }
  *res *= znak;
  return i;
}

int proc_spec_c(const char *str, va_list args, const Specifiers st_spec) {

  size_t max_len = s21_strlen(str);
  const char *p = str;
  DEBUG_PRINT(": String for decode=|%s|\n", str);
  int width = st_spec.width > 0 ? st_spec.width : 1;
  if (st_spec.flag == '*') {
    if (st_spec.length == 'l') {
      wchar_t dummy;
      for (int i = 0; i < width && *p; i++) {
        if (read_wchar(&p, &dummy) != 0)
          break;
      }
    } else {
      p += width > 0 ? width : 1;
    }
  } else {
    if ((st_spec.length == 'l')) {
      width = (width > (int)max_len) ? (int)max_len : width;
      wchar_t *wch = va_arg(args, wchar_t *);
      for (int i = 0; i < width; i++) {
        DEBUG_PRINT(" wide Char=%x\n", L'Ω');
        int bytes_read = read_wchar(&p, &wch[i]);
        p += bytes_read;
        if (bytes_read == -1) {
          wch[i] = L'\0';
          DEBUG_PRINT(" read char symbol=%d\n", i);
          break;
        }
        DEBUG_PRINT(" wide Char=%x\n", (wchar_t)wch[i]);
      }
    } else {
      char *ch = va_arg(args, char *);
      size_t copy_size = (size_t)width > max_len ? max_len : (size_t)width;
      s21_memcpy(ch, p, copy_size);
      ch[copy_size] = '\0';
      p += copy_size;
      DEBUG_PRINT(" ordinary Char=%c\n", *ch);
    }
  }
  return p - str;
}

int proc_spec_f(const char *str, va_list args, const Specifiers st_spec) {
  char arg_str[s21_strlen(str) + 1];
  int width = st_spec.width > 0 ? st_spec.width : (int)s21_strlen(str);
  if (width >= 0) {
    s21_memcpy(arg_str, str, width);
    arg_str[width] = '\0';
  } else {
    s21_memcpy(arg_str, str, width);
  }
  const char *p = arg_str; // Указатель на входную строку
  DEBUG_PRINT(" String=%s\n", p);
  long int res = 0;
  int i = 0;
  long double result = 0.0;
  p += get_number(p, &res);
  result += res;
  DEBUG_PRINT(" RES_CELOE=%Lf\n", result);
  if (*p == '.') {
    p++;
    i++;
    int ost_div = get_number(p, &res);
    DEBUG_PRINT(" Ostatoc_div=%d\n", ost_div);
    result = result + res * (1 / s21_pow(10, ost_div));
    p += ost_div;
    DEBUG_PRINT(" String after get float=%s\n", p);
    DEBUG_PRINT(" RES_frac=%Lf\n", result);
  }
  if (*p == 'e' || *p == 'E') {
    p++;
    p += get_number(p, &res);
    DEBUG_PRINT(" exp=%ld\n", res);
    result = result * s21_pow(10, (res));
  }
  if (p - arg_str > 0 && st_spec.flag != '*') {
    float *ch = va_arg(args, float *);
    *ch = result;
    p++;
    i++;
    DEBUG_PRINT(" Float=%Lf\n", result);
  }
  // DEBUG_PRINT(" value Length=%ld\n", arg_str - p);
  return p - arg_str;
}
int proc_spec_s(const char *str, va_list args, const Specifiers st_spec) {
  DEBUG_PRINT("Call proc_spec_s()\n");
  int width = st_spec.width >= 0 ? st_spec.width : (int)s21_strlen(str);
  DEBUG_PRINT("width=%d\n", width);
  const char *p = str;
  int res = 0;
  int i = 0;
  DEBUG_PRINT("proc_spec_s(): String length=%ld\n", s21_strlen(p));
  noop_space(&p);

  if (st_spec.flag == '*') {
    if ((st_spec.length == 'l')) {
      DEBUG_PRINT("Start procesing and noop wide String\n");
      wchar_t ch[10];
      while (*p && !is_space(*p) && i < width) {
        s21_size_t mbr_res = mbrtowc(ch, p, MB_CUR_MAX, NULL);
        if (mbr_res == (size_t)-1 || mbr_res == (size_t)-2) {
          DEBUG_PRINT("Error: Invalid multibyte sequence.\n");
          break; // Прерываем цикл при ошибке
        }
        DEBUG_PRINT("mbr_res=%ld\n", mbr_res);
        p += mbr_res; // Перемещаем указатель на следующий символ
        // ch++;         // Перемещаем указатель на следующий широкий символ
        i++; // Увеличиваем счётчик прочитанных символов
      }
    } else {
      for (; !(is_space(*p)) && i < width; i++, p++)
        ;
    }
    res = 0;
  } else {
    if ((st_spec.length == 'l')) {
      DEBUG_PRINT("Start procesing wide String\n");
      wchar_t *ch = va_arg(args, wchar_t *);
      wchar_t *start = ch;
      while (*p && !is_space(*p) && i < width) {
        s21_size_t mbr_res = mbrtowc(ch, p, MB_CUR_MAX, NULL);
        if (mbr_res == (s21_size_t)-1 || mbr_res == (s21_size_t)-2) {
          DEBUG_PRINT("Error: Invalid multibyte sequence.\n");
          break; // Прерываем цикл при ошибке
        }
        p += mbr_res;
        ch++;
        i++;
      }
      *ch = L'\0';
      if (i > 0) {
        res++; // Увеличиваем счётчик успешных преобразований
        DEBUG_PRINT("Wide string=%ls\n", start); // Выводим строку с начала
      } else {
        DEBUG_PRINT("Warning: No valid characters read.\n");
      }
      res++;
    } else {
      DEBUG_PRINT("proc_spec_s(process string)\n");
      char *ch = va_arg(args, char *);
      if (ch != NULL) {
        DEBUG_PRINT("String write to args=|%s|, strlen=%ld, width=%d\n", p,
                    s21_strlen(p), width);
        while (*p && !is_space(*p) && i < width) {
          *ch++ = *p++;
          DEBUG_PRINT("i=%d, symbol=%c\n", i, *(ch)); // Отладочный вывод
          i++;
        }
        *ch = '\0';

        if (i > 0) {
          res++;
        } else {
          DEBUG_PRINT("Warning: No valid characters read.\n");
        }
      } else
        DEBUG_PRINT("ERRRRRROOR");
      DEBUG_PRINT("proc_spec_s()=%d\n", res);
      DEBUG_PRINT("String=%s\n", ch - i);
    }
  }
  if (i == 0) {
    res = -1;
  } else
    res = p - str;
  DEBUG_PRINT(" value Step=%ld\n", p - str);
  return res;
}

int proc_spec_d(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  s21_size_t i = 0;
  int width = st_spec.width >= 0 ? st_spec.width : (int)s21_strlen(str);
  long int result = 0;
  char arg_str[s21_strlen(str) + 1];
  if (st_spec.width > 0) {
    s21_memcpy(arg_str, str, width);
    arg_str[width] = '\0';
  } else {
    s21_memcpy(arg_str, str, s21_strlen(str));
  }
  arg_str[s21_strlen(str)] = '\0';
  const char *p = arg_str;
  noop_space(&p);
  DEBUG_PRINT(" String str=|%s|\n", str);
  DEBUG_PRINT(" String arg_str=|%s|\n", arg_str);
  DEBUG_PRINT(" String copy with Width=%s\n", p);
  DEBUG_PRINT(" Input string for convert to int=|%s|\n", p);
  int step = 0;
  step = str_to_int(p, &result, 10);
  p += step;
  DEBUG_PRINT(" Width=%d result=%ld step=%d.\n", width, result, step);
  i++;
  DEBUG_PRINT("Accept result into int=|%ld|\n", result);
  if (step > 0) {
    if (st_spec.flag != '*') {
      if (st_spec.length == 'h') {
        short int *ch = va_arg(args, short int *);
        *ch = (short int)result;
      } else if (st_spec.length == 'l') {
        long int *ch = va_arg(args, long int *);
        *ch = result;
      } else {
        int *ch = va_arg(args, int *);
        *ch = (int)result;
      }
    }
    res = p - arg_str;
  } else if (*p == '\0' && st_spec.flag != '*') {
    res = -1;
  } else {
    res = 0;
    va_arg(args, short int *);
  }

  return res;
}

int proc_spec_u(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  // s21_size_t i = 0;
  int width = st_spec.width >= 0 ? st_spec.width : (int)s21_strlen(str);
  long int result = 0;
  char arg_str[s21_strlen(str) + 1];
  if (st_spec.width > 0) {
    s21_memcpy(arg_str, str, width);
    arg_str[st_spec.width] = '\0';
  } else {
    s21_memcpy(arg_str, str, s21_strlen(str));
  }
  arg_str[s21_strlen(str)] = '\0';
  const char *p = arg_str; // Указатель на входную строку
  noop_space(&p);
  DEBUG_PRINT(" Input string for convert to int=|%s|\n", p);
  int step = 0;
  step = get_number(p, &result);
  p += step;
  DEBUG_PRINT(" Width=%d result=%ld step=%d.\n", width, result, step);
  // i++;
  if (step > 0) {
    if (st_spec.flag != '*') {
      if (st_spec.length == 'h') {
        short unsigned int *ch = va_arg(args, short unsigned int *);
        *ch = (short unsigned int)result;
      } else if (st_spec.length == 'l') {
        long unsigned int *ch = va_arg(args, long unsigned int *);
        *ch = (long unsigned int)result;
      } else {
        unsigned int *ch = va_arg(args, unsigned int *);
        *ch = (unsigned int)result;
      }
    }
    res = p - arg_str;
  } else if (*p == '\0' && st_spec.flag != '*') {
    res = -1;
  }
  return res;
}

int proc_spec_n(long int result, va_list args, const Specifiers st_spec) {
  int res = 0;
  DEBUG_PRINT(" Input string for convert to result=|%ld|\n", result);
  if (st_spec.length == 'h') {
    short int *ch = va_arg(args, short int *);
    if (ch != S21_NULL) {
      *ch = (short int)result;
    } else
      res = -1;
  } else if (st_spec.length == 'l') {
    long int *ch = va_arg(args, long int *);
    if (ch != S21_NULL) {
      *ch = result;
    } else
      res = -1;
  } else {
    int *ch = va_arg(args, int *);
    if (ch != S21_NULL) {
      *ch = (int)result;
    } else
      res = -1;
  }
  return res;
}

int proc_spec_i(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  const char *p = str;
  if (*p == '0') {
    if (*(p + 1) == 'x' || *(p + 1) == 'X') {
      res = proc_spec_x(str, args, st_spec);
    } else {
      res = proc_spec_o(str, args, st_spec);
    }
  } else {
    res = proc_spec_d(str, args, st_spec);
  }
  return res;
}

int proc_spec_o(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  s21_size_t i = 0;
  int width = st_spec.width >= 0 ? st_spec.width : (int)s21_strlen(str);
  long int result = 0;
  char arg_str[s21_strlen(str) + 1];
  if (st_spec.width > 0) {
    s21_memcpy(arg_str, str, width);
    arg_str[width] = '\0';
  } else {
    s21_memcpy(arg_str, str, s21_strlen(str));
  }
  arg_str[s21_strlen(str)] = '\0';
  const char *p = arg_str;
  noop_space(&p);
  DEBUG_PRINT(" String str=|%s|\n", str);
  DEBUG_PRINT(" String arg_str=|%s|\n", arg_str);
  DEBUG_PRINT(" String copy with Width=%s\n", p);
  DEBUG_PRINT(" Input string for convert to int=|%s|\n", p);
  int step = 0;
  step = str_to_int(p, &result, 8);
  p += step;
  DEBUG_PRINT(" Width=%d result=%ld step=%d.\n", width, result, step);
  i++;
  DEBUG_PRINT("Accept result into int=|%ld|\n", result);
  if (step > 0) {
    if (st_spec.flag != '*') {
      if (st_spec.length == 'h') {
        short int *ch = va_arg(args, short int *);
        *ch = (short int)result;
      } else if (st_spec.length == 'l') {
        long int *ch = va_arg(args, long int *);
        *ch = result;
      } else {
        int *ch = va_arg(args, int *);
        *ch = (int)result;
      }
    }
    // p++;
    res = p - arg_str;
  } else if (*p == '\0' && st_spec.flag != '*') {
    // p++;
    res = -1;
  } else {
    res = 0;
    va_arg(args, short int *);
  }

  return res;
}

int proc_spec_x(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  s21_size_t i = 0;
  int width = st_spec.width >= 0 ? st_spec.width : (int)s21_strlen(str);
  long int result = 0;
  char arg_str[s21_strlen(str) + 1];
  if (st_spec.width > 0) {
    s21_memcpy(arg_str, str, width);
    arg_str[width] = '\0';
  } else {
    s21_memcpy(arg_str, str, s21_strlen(str));
  }
  arg_str[s21_strlen(str)] = '\0';
  const char *p = arg_str;
  noop_space(&p);
  DEBUG_PRINT(" String str=|%s|\n", str);
  DEBUG_PRINT(" String arg_str=|%s|\n", arg_str);
  DEBUG_PRINT(" String copy with Width=%s\n", p);
  DEBUG_PRINT(" Input string for convert to hex=|%s|\n", p);
  int t1 = (int)'A' - '0';
  int t2 = (int)'a' - '0';
  DEBUG_PRINT("Code fo A=%d, code for a=%d\n", t1, t2);
  int step = 0;
  step = str_to_int(p, &result, 16);
  p += step;
  DEBUG_PRINT(" Width=%d result=%ld step=%d.\n", width, result, step);
  i++;
  DEBUG_PRINT("Accept result into int=|%ld|\n", result);
  if (step > 0) {
    if (st_spec.flag != '*') {
      if (st_spec.length == 'h') {
        short int *ch = va_arg(args, short int *);
        *ch = (short int)result;
      } else if (st_spec.length == 'l') {
        long int *ch = va_arg(args, long int *);
        *ch = result;
      } else {
        int *ch = va_arg(args, int *);
        *ch = (int)result;
      }
    }
    // p++;
    res = p - arg_str;
  } else if (*p == '\0' && st_spec.flag != '*') {
    // p++;
    res = -1;
  } else {
    res = 0;
    va_arg(args, short int *);
  }

  return res;
}

int proc_spec_p(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  DEBUG_PRINT("pointer String=%s\n", str);
  if (str != NULL) {
    const char *p = str;
    if (st_spec.flag != '*') {
      void **ch = va_arg(args, void **);
      if (ch != S21_NULL) {
        // Проверяем, что строка начинается с "0x" и содержит шестнадцатеричные
        // символы
        if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X')) {
          p += 2;
          long int address;
          int conv = 0;
          conv = str_to_int(p, &address, 16);
          if (conv != 0 && address > 0) {
            *ch = (void *)address;
            p += conv;
            res = p - str;
            DEBUG_PRINT("pointer assign=%p, res =%d\n", *ch,
                        res); // Выводим адрес
          } else {
            res = -1;
          }
        } else {
          res = -1;
        }
      } else {
        res = -1;
      }
    } else {
      if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X')) {
        p += 2;
        long int address;
        int conv = 0;
        conv = str_to_int(p, &address, 16);
        if (conv != 0 && address > 0) {
          p += conv;
          res = p - str;
          DEBUG_PRINT("SKIP: pointer not assig, res =%d\n", res); // Выводим адрес
        } else {
          res = -1;
        }
      }
    }
  }else {
      res = -1;
    }

    return res;
  }