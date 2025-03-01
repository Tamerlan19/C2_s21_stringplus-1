#include "s21_string.h"
#include "s21_utils.c"
#include <limits.h>

long double s21_pow(int x, int y);
int get_number(const char *p, long int *res);
int proc_spec_s(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_d(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_f(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_c(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_u(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_n(long int result, va_list args, const Specifiers st_spec);
int proc_spec_i(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_o(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_x(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_p(const char *str, va_list args, const Specifiers st_spec);

int str_to_int(const char *p, long int *res, int base);

void proc_str(const char **p, int step, Specifiers st_spec, int *res,
              int *stop) {
  DEBUG_PRINT("next_val(): step=%d, res =%d \n", step, *res);
  if (step > 0) {
    *p = *p + step;
    if (st_spec.flag != '*') {
      *res = *res + 1;
    }
  } else if (step == -1) {
    *stop = 1;
    if (*res == 0 && **p == '\0') {
      *res = -1;
    }
  } else if (step < -1) {
    *stop = 1;
    *res = -1;
  } else if ((st_spec.specifier != 'n' &&
              st_spec.specifier !=
                  '%')) { 
    DEBUG_PRINT("Specifiers.flag=%c\n", st_spec.flag);
    *stop = 1;
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  int res = 0;
  if(*format){

  
  va_list args;
  va_start(args, format);
  const char *p = str; 
  const char *fmt = format; 
  int stop = 0;
  if (p != S21_NULL && fmt != S21_NULL) {
    while (*p && *fmt && !stop) {
      while ((*fmt) && !stop) {
        if (*fmt == '%') {
          Specifiers st_spec = {' ', -10, -1, '*', '*'};
          fmt += parse_specifiers(fmt, &st_spec);
          int step = 0;
          if (!(st_spec.specifier == 'c')) {
            noop_space(&p);
          }
          if (st_spec.specifier == 'c') {
            step = proc_spec_c(p, args, st_spec);
          } else if (st_spec.specifier == 'd') {
            step = proc_spec_d(p, args, st_spec);
          } else if (st_spec.specifier == 'f' || st_spec.specifier == 'g' ||
                     st_spec.specifier == 'G' || st_spec.specifier == 'e' ||
                     st_spec.specifier == 'E') {
            step = proc_spec_f(p, args, st_spec);
          } else if (st_spec.specifier == 's') {
            step = proc_spec_s(p, args, st_spec);
          } else if (st_spec.specifier == 'u') {
            step = proc_spec_u(p, args, st_spec);
          } else if (st_spec.specifier == 'n') {
            long int r = p - str;
            proc_spec_n(r, args, st_spec);
          } else if (st_spec.specifier == 'i') {
            step = proc_spec_i(p, args, st_spec);
          } else if (st_spec.specifier == 'o') {
            step = proc_spec_o(p, args, st_spec);
          } else if (st_spec.specifier == 'x' || st_spec.specifier == 'X') {
            step = proc_spec_x(p, args, st_spec);
          } else if (st_spec.specifier == 'p') {
            step = proc_spec_p(p, args, st_spec);
          } else if (st_spec.specifier == '%') {
            // if (is_space(*p)) { // 2025-03-01 11:28:25 @morrigem: comment 2025-03-01 11:28
            //   noop_space(&p);
            // }
            if (*(p) == '%') {
              p++;
            } else
              stop = 1;
            step = 0;
          }
          proc_str(&p, step, st_spec, &res, &stop);
        } else if (*fmt == *p) {
          fmt++;
          p++;
        } else if (is_space(*fmt)) {
          noop_space(&fmt);
          noop_space(&p);
        } else {
          stop = 1;
        }
      }
      stop = 1;
      if (is_space(*fmt)) {
        noop_space(&fmt);
        noop_space(&p);
      }
    }
  // } else { // 2025-03-01 11:29:06 @morrigem: comment 2025-03-01 11:29
  //   res = -1;
  }
  if (stop == 0) {
    res = -1;
  }
  va_end(args);
}

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
  if (*p == '-' && (is_digit(*(p + 1)) || (*(p-1)=='e') || (*(p-1)=='E'))) {
    znak = -1;
    p++;
    i++;
  } else if (*p == '+') {
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

char *get_arg_width(const char *str, int width) {
  char *arg_str = malloc(sizeof(char) * width + 1);
  if (*str != '\0') {
    s21_strncpy(arg_str, str, width);
    arg_str[width] = '\0';
  }
  return arg_str;
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
  p = s21_to_upper(p);
  long int temp = 0;
  while (*p) {
    int digit = -1;

    if (is_digit(*p))
      digit = *p - '0'; 
    else if (is_hex(*p))
      digit = (*p - 'A' + 10); 

    if (digit < 0 || digit >= base)
      break;

    if (temp > (LONG_MAX - digit) / base) {
      *res = (znak == 1) ? LONG_MAX : LONG_MIN;
    }
    temp = (temp * base + digit);
    p++;
    i++;
  }   
  *res = temp * znak;
  return i;
}


int str_to_luint(const char *p, long unsigned *res, int base) {
  *res = 0;
  int i = 0;
  int znak = 1;
  if (*p == '-' && is_digit(*(p + 1))) {
    znak = -1;
    p++;
    i++;
  }
  p = s21_to_upper(p);
  long int temp = 0;
  while (*p) {
    int digit = -1;

    if (is_digit(*p))
      digit = *p - '0'; 
    else if (is_hex(*p))
      digit = (*p - 'A' + 10); 

    if (digit < 0 || digit >= base)
      break;

    if (temp > (LONG_MAX - digit) / base) {
      *res = (znak == 1) ? LONG_MAX : LONG_MIN;
    }
    temp = (temp * base + digit);
    p++;
    i++;
  }   
  *res = temp * znak;
  return i;
}

int proc_spec_c(const char *str, va_list args, const Specifiers st_spec) {
  int error = 0;
  size_t max_len = s21_strlen(str);
  const char *p = str;
  if (max_len>0){ 
  int width = st_spec.width > 0 ? get_width(str, st_spec) : 1;
  DEBUG_PRINT("Start procesing Char. width=%d\n", (int)max_len);
  if (width > 0) {
    if (st_spec.flag == '*') {
      if (st_spec.length == 'l') {
        wchar_t dummy;
        for (int i = 0; i < width && *p; i++) {
          if (read_wchar(&p, &dummy) != 0)
            break;
        }
      } else {
        p += width; 
      }
    } else {
      if ((st_spec.length == 'l')) {
        width = (width > (int)max_len) ? (int)max_len : width;
        wchar_t *wch = va_arg(args, wchar_t *);
        for (int i = 0; i < width; i++) {
          int bytes_read = read_wchar(&p, &wch[i]);
          p += bytes_read;
          if (bytes_read == -1) {
            wch[i] = L'\0';
            error = 1;
            break;
          }
        }
      } else {
        char *ch = va_arg(args, char *);
        size_t copy_size = (size_t)width > max_len ? max_len : (size_t)width;
        s21_memcpy(ch, p, copy_size);
        ch[copy_size] = '\0';
        p += copy_size;
      }
    }
  }
}
  return p - str - error;
}

int proc_spec_wchar(const char **p, wchar_t *ch) {
  int res = 0;
  DEBUG_PRINT("Start procesing and noop wide String\n");
  while (**p && !is_space(**p)) {
    s21_size_t mbr_res = mbrtowc(ch, *p, MB_CUR_MAX, NULL);
    if (mbr_res == (size_t)-1 || mbr_res == (size_t)-2) {
      DEBUG_PRINT("Error: Invalid multibyte sequence.\n");
      break;
    }
    DEBUG_PRINT("mbr_res=%lu, char=|%lc| \n", (unsigned long)mbr_res, *(ch));
    *p += mbr_res;
    ch++; 
    res += mbr_res;
  }
  *ch = L'\0';
  DEBUG_PRINT("End procesing wide String. number chars=%d\n", res);
  return res;
}

int proc_spec_f(const char *str, va_list args, const Specifiers st_spec) {
  int r = 0;
  int width = get_width(str, st_spec);
  char *arg_str = get_arg_width(str, width);
  const char *p = arg_str;
  noop_space(&p);

  
  long int res = 0;
  int init = 0;
  long double result = 0.0;
  if (get_number(p, &res) > 0) {
    p += get_number(p, &res);
    init++;
  }
  result += res;
  if (*p == '.' && is_digit(*(p + 1)) && *(p + 1) != '\0') {
    long int div = 0;
    p++;
    int ost_div = get_number(p, &div);
    // if (result < 0) { // 2025-03-01 11:30:57 @morrigem: delete in next commit
    //   div = div * -1;
    // }
    result = result + div * (1 / s21_pow(10, ost_div));
    p += ost_div;
    init++;
  } else if (*p == '.' && p - arg_str > 0) {
    p++;
  }
  
  if (init && (*p == 'e' || *p == 'E')) {
    p++;
    p += get_number(p, &res);
    result = result * s21_pow(10, (res));
    DEBUG_PRINT("number=%ld, init=%d\n", res, init);
  }

  if (p - arg_str > 0 && st_spec.flag != '*') {
    if (st_spec.length == 'L') {
      long double *ch = va_arg(args, long double *);
      *ch = result;
    } else {
      float *ch = va_arg(args, float *);
      *ch = (float)result;
    }
    r = p - arg_str;
  } else if (st_spec.flag == '*') {
    r = p - arg_str;
  } else {
    r = -1;
  }
  free(arg_str);
  return r;
}
int proc_spec_s(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0, i = 0;
  int width = get_width(str, st_spec);
  if(width>0){

  
  char *arg_str = get_arg_width(str, width);
  const char *p = arg_str;
  noop_space(&p);
  if (*p) {
    if (st_spec.flag == '*') {
      if ((st_spec.length == 'l')) {
        wchar_t ch[sizeof(char) * s21_strlen(p)];
        i += proc_spec_wchar(&p, ch);

      } else {
        for (; *p && !(is_space(*p)); i++, p++)
          ;
      }
      res = 0;
    } else {
      if ((st_spec.length == 'l')) {
        wchar_t *ch = va_arg(args, wchar_t *);
        if (ch != S21_NULL) {
          i += proc_spec_wchar(&p, ch);
        }
      } else {
        char *ch = va_arg(args, char *);
        if (ch != NULL) {
          for (; *p && !(is_space(*p)); i++) {
            *ch++ = *p++;
          }
          *ch = '\0';
        }
      }
      if (i > 0) {
        res++;
      }
    }
  }
  if (i == 0 && res == 0) {
    res = -1;
  } else
    res = p - arg_str;
  free(arg_str);
}
  return res;
}

int proc_spec_d(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  int width = get_width(str, st_spec);
  long int result = 0;
  char *arg_str = get_arg_width(str, width);
  const char *p = arg_str;
  noop_space(&p);
  int step = 0;
  step = str_to_int(p, &result, 10);
  p += step;
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
        if (ch != S21_NULL) {
          *ch = (int)result;
        }
      }
    }
    res = p - arg_str;
  } else if (*p == '\0' && st_spec.flag != '*') {
    res = -1;
  } else {
    res = 0;

    va_arg(args, short int *);
  }
  free(arg_str);
  return res;
}

int proc_spec_u(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  int width = get_width(str, st_spec);
  // long int result = 0;
  long unsigned result = 0;
  char *arg_str = get_arg_width(str, width);
  const char *p = arg_str;
  noop_space(&p);
  int step = 0;
  // step = get_number(p, &result);
  step = str_to_luint(p, &result,10);
  p += step;
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
  } else if (st_spec.flag != '*') {
    res = -1;
  }
  free(arg_str);
  return res;
}

int proc_spec_n(long int result, va_list args, const Specifiers st_spec) {
  int res = 0;
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
  int width = get_width(str, st_spec);
  long int result = 0;
  char *arg_str = get_arg_width(str, width);
  const char *p = arg_str;
  noop_space(&p);
  int step = 0;
  step = str_to_int(p, &result, 8);
  p += step;
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
  } else if (st_spec.flag != '*') {
    res = -1;
  } else {
    res = 0;
    va_arg(args, short int *);
  }
  free(arg_str);
  return res;
}

int proc_spec_x(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  int width = get_width(str, st_spec);
  long unsigned result = 0;
  char *arg_str = get_arg_width(str, width);
  const char *p = arg_str;
  noop_space(&p);
  int step = 0;
  if (*p == '0' && *(p + 1) == 'x') {
    p += 2;
  }
  step = str_to_luint(p, &result, 16);
  p += step;
  if (step > 0) {
    if (st_spec.flag != '*') {
      if (st_spec.length == 'h') {
        short unsigned int *ch = va_arg(args, short unsigned int *);
        *ch = (short int)result;
      } else if (st_spec.length == 'l') {
        long unsigned int *ch = va_arg(args, long unsigned int *);
        *ch = result;
      } else {
        unsigned int *ch = va_arg(args, unsigned int *);
        if (result > 4294967295) {
            *ch = ((unsigned) result) % 4294967296;
            // *ch = 4294967295;
            // *ch = (unsigned) result;
        } else {
          *ch = (unsigned)result;
        }
      }
    }
    res = p - arg_str;
  } else if (st_spec.flag != '*') {
    res = -1;
  } else {
    res = 0;
    va_arg(args, short int *);
  }
  free(arg_str);
  return res;
}

int proc_spec_p(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  if (str != NULL) {
    const char *p = str;
    if (st_spec.flag != '*') {
      void **ch = va_arg(args, void **);
      if (ch != S21_NULL) {
        if (*p == '0' && (*(p + 1) == 'x' || *(p + 1) == 'X')) {
          p += 2;
          long unsigned address;
          int conv = 0;
          conv = str_to_luint(p, &address, 16);
          DEBUG_PRINT("Converted %d chars to pointer.\n",conv);
          if (conv != 0 ) {
            *ch = (void *)address;
            p += conv;
            res = p - str;
          } else {
            res = -1;
          }
        } else {
          long int address;
          int conv = 0;
          conv = str_to_int(p, &address, 16);
          if (conv != 0 ) {
            *ch = (void *)address;
            res = 0;
          } else {
            res = -1;
          }
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
        } else {
          res = -1;
        }
      }
    }
  } else {
    res = -1;
  }
  return res;
}