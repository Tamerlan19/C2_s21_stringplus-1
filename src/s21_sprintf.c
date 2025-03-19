#include "s21_string.h"
#include "s21_utils.h"
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <wchar.h>
// [ ] Удалить импорт библиотеки, использовалась для отладки кода
// #include <stdio.h>

#define MAX_BUF_SIZE 1024

void handle_char(char **buffer, Specifiers flags, va_list args);
void handle_int(char **buffer, Specifiers flags, va_list argc);
void handle_float(char **buffer, Specifiers flags, va_list argc);
void handle_string(char **buffer, Specifiers flags, va_list argc);
void handle_unsigned(char **buffer, Specifiers flags, va_list args);
void handle_percent(char **buffer, Specifiers flags);

void handle_exp(char **buffer, Specifiers flags, va_list args);
void handle_hex(char **buffer, Specifiers flags, va_list args);
void handle_octal(char **buffer, Specifiers flags, va_list args);
void handle_pointer(char **buffer, Specifiers flags, va_list args);
void handle_general(char **buffer, Specifiers flags, va_list args);

void set_width_pading(char **buffer, char *src, Specifiers flags, int len);
void set_width_pading_sign(char **buffer, char *src, Specifiers flags, int len,
                           char sign);
int set_flag_sign(char **buffer, Specifiers flags, int is_negative, int len);
int add_sign(char *buffer, Specifiers flags, int is_positive);

int get_exp(long double ch);

void set_width_argv(Specifiers *flags, va_list args) {
  if (flags->width == -1) {
    int w = va_arg(args, int);
    flags->width = w;
  }
}
void set_precission_argv(Specifiers *flags, va_list args) {
  if (flags->precision == -1) {
    int p = va_arg(args, int);
    flags->precision = p;
  }
}
int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *buffer = str;
  const char *ptr = format;
  DEBUG_PRINT("\n\n\nptr = %s\nformat = %s\n", ptr, format);
  while (*ptr) {
    if (*ptr == '%') {
      Specifiers flags = {'a', '+', ' ', -10, -10, '*', '*'};
      ptr += parse_specifiers(ptr, &flags, 1);
      set_width_argv(&flags, args);
      set_precission_argv(&flags, args);
      DEBUG_PRINT("RESULT: Specifier=%c, Length=%c, Precision=%i,  Width=%d, "
                  "Flags=%c\n",
                  flags.specifier, flags.length, flags.precision, flags.width,
                  flags.flag);
      char spec = *ptr;
      if (flags.specifier == 'c') {
        handle_char(&buffer, flags, args);
      } else if (flags.specifier == 'd') {
        handle_int(&buffer, flags, args);
      } else if (flags.specifier == 'f') {
        handle_float(&buffer, flags, args);
      } else if (flags.specifier == 's') {
        handle_string(&buffer, flags, args);
      } else if (flags.specifier == 'u') {
        handle_unsigned(&buffer, flags, args);
      } else if (flags.specifier == 'x' || flags.specifier == 'X') {
        handle_hex(&buffer, flags, args);
      } else if (flags.specifier == 'o') {
        handle_octal(&buffer, flags, args);
      } else if (flags.specifier == 'p') {
        handle_pointer(&buffer, flags, args);
      } else if (flags.specifier == '%') {
        handle_percent(&buffer, flags);
      } else if (flags.specifier == 'e' || flags.specifier == 'E') {
        handle_exp(&buffer, flags, args);
      } else if (flags.specifier == 'g' || flags.specifier == 'G') {
        handle_general(&buffer, flags, args);
      } else
        *buffer++ = spec;
    } else {
      *buffer++ = *ptr++;
    }
  }
  *buffer = '\0';
  va_end(args);
  return (int)s21_strlen(str);
}

void reverse_string(char *tmp, int len) {
  for (int i = 0, j = len - 1; i < j; i++, j--) {
    char temp = tmp[i];
    tmp[i] = tmp[j];
    tmp[j] = temp;
  }
}

int set_flag_sign(char **buffer, Specifiers flags, int is_positive, int len) {
  int res = 0;
  *buffer -= len;
  DEBUG_PRINT("set_flag_sign()=%s\n", *(buffer));
  if ((flags.flag == ' ' && is_positive) ||
      (flags.flag == '+' && is_positive)) {
    s21_memmove(*buffer + 1, *buffer, len);
    (*buffer)[0] = flags.flag;
    res++;
  } else if (!is_positive) {
    s21_memmove(*buffer + 1, *buffer, len);
    (*buffer)[0] = '-';
    res++;
  }
  DEBUG_PRINT("STR=%s", *buffer);

  return res;
}

/**
 * @brief Handles the formatting of an integer according to the specified flags.
 *
 * @param buffer A pointer to the buffer where the formatted string will be
 * stored.
 * @param flags The flags specifying the formatting options.
 * @param d The integer to be formatted.
 */
void handle_int(char **buffer, Specifiers flags, va_list args) {
  long int d;
  if (flags.length == 'h') {
    d = (short int)va_arg(args, int);
  } else if (flags.length == 'l') {
    d = va_arg(args, long int);
  } else {
    d = (int)va_arg(args, int);
  }

  char sign = '\0';
  char tmp[300] = {0};
  int is_negative = (d < 0);
  long int num = (is_negative) ? -d : d;
  int len = 0;

  if (num == 0) {
    tmp[len++] = '0';
  } else {
    while (num > 0) {
      tmp[len++] = '0' + (num % 10);
      num /= 10;
    }
  }
  if (is_negative) {
    sign = '-';
  } else if (flags.flag == ' ' || flags.flag == '+') {
    sign = flags.flag;
  }

  reverse_string(tmp, len);

  if (flags.precision >= 0 && len < flags.precision) {
    int padding = flags.precision - len;
    for (int i = len; i >= 0; i--) {
      tmp[i + padding] = tmp[i];
    }
    for (int i = 0; i < padding; i++) {
      tmp[i] = '0';
    }

    len += padding;
  }
  set_width_pading_sign(buffer, tmp, flags, len, sign);
}

int add_sign(char *buffer, Specifiers flags, int is_positive) {
  int res = 0;
  size_t len = s21_strlen(buffer);

  if ((flags.flag == '+' && is_positive) ||
      (flags.flag == ' ' && is_positive)) {
    s21_memmove(buffer + 1, buffer, len + 1);
    buffer[0] = (flags.flag == '+') ? '+' : ' ';
    res = 1;
  } else if (!is_positive) {
    s21_memmove(buffer + 1, buffer, len + 1);
    buffer[0] = '-';
    res = 1;
  }

  return res;
}

int double_int_to_string(char *tmp, long double int_part) {
  int int_len = 0;
  if (int_part < 0) {
    DEBUG_PRINT("int_part is negative. tmp=%s\n", tmp);
    int_part *= -1;
  }

  int exp = get_exp(int_part);
  DEBUG_PRINT("exp=%d\n", exp);
  if (exp < 19) {
    while (int_part > 0) {
      int digit = (int)fmodl(int_part, 10);
      tmp[int_len++] = '0' + digit;
      int_part = floorl(int_part / 10);
    }
  } else if (exp <= 38) {
    DEBUG_PRINT("Process in bigint...\n");
    __int128_t big_int = (__int128_t)int_part;
    while (big_int > 0) {
      tmp[int_len++] = '0' + (big_int % 10);
      big_int /= 10;
    }
  } else {
    DEBUG_PRINT("Process Extra long double...\n");
    BigNumber num = convert_long_double_to_big_number(int_part);
    for (int i = 0; i < num.count; i++) {
      DEBUG_PRINT("num[%d]=%ld\n", i, num.parts[i]);
      long int_part = (long)num.parts[i];
      while (int_part > 0) {
        int digit = int_part % 10;
        tmp[int_len++] = '0' + digit;
        DEBUG_PRINT("Add digit=|%d| in positin=%d\n", digit, int_len)
        int_part /= 10;
      }
    }
  }
  reverse_string(tmp, int_len);
  return int_len;
}

void handle_float(char **buffer, Specifiers flags, va_list args) {
  char tmp[MAX_BUF_SIZE] = {0};
  int len = 0;
  long double f;
  if (flags.length == 'L') {
    f = va_arg(args, long double);
  } else {
    f = va_arg(args, double);
  }
  if (flags.precision < 0) {
    flags.precision = 6; // default value for %f
  }

  long double int_part;
  long double frac_part = modfl(f, &int_part);
  DEBUG_PRINT("int_part= %Lf, frac_part= %Lf, f=|%Lf|\n", int_part, frac_part,
              (long double)f);
  if (int_part == 0) {
    tmp[len++] = '0';
  } else {
    if (int_part < 0) {
      DEBUG_PRINT("int_part is negative. tmp=%s\n", tmp);
      int_part *= -1;
    }
    len += double_int_to_string(tmp, int_part);
  }

  DEBUG_PRINT("tmp=%s\n", tmp);
  (frac_part < 0) ? (frac_part *= -1) : (frac_part *= 1);
  DEBUG_PRINT("frac_part= %Lf\n", frac_part);
  if (flags.specifier == 'g' || flags.specifier == 'G') {
    if (frac_part * s21_pow(10, flags.precision) > 1) {
      flags.precision = flags.precision - len;
    } else {
      while (frac_part * s21_pow(10, flags.precision - 2) < 1) {
        flags.precision++;
      }
    }
  }
  if (flags.precision > 0) {
    tmp[len++] = '.';
    for (int i = 0; i < flags.precision; i++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      if (i == flags.precision - 1 && (frac_part - digit) * 10 >= 5.0) {
        digit = (int)frac_part + 1;
      }
      tmp[len++] = '0' + digit;
      DEBUG_PRINT("tmp in cycle = |%s|,digit=%i\n", tmp, digit);
      frac_part -= digit;
    }
  }
  len += add_sign(tmp, flags, f >= 0);
  set_width_pading(buffer, tmp, flags, len);
}

void handle_string(char **buffer, Specifiers flags, va_list args) {
  char *s = NULL;
  wchar_t *ws = NULL;
  int len = 0;
  char tmp[MAX_BUF_SIZE] = {
      0}; // Объявляем временный буфер для преобразования широких строк

  if (flags.length == 'l') {
    ws = va_arg(args, wchar_t *);
    if (ws == S21_NULL) {
      s = "(null)";
    } else {
      wcstombs(tmp, ws,
               MAX_BUF_SIZE); // Преобразуем широкую строку в многобайтовую
      s = tmp; // Используем tmp как источник данных
    }
  } else {
    s = va_arg(args, char *);
    if (s == S21_NULL) {
      s = "(null)";
    }
  }

  len = s21_strlen(s);

  if (flags.precision >= 0 && len > flags.precision) {
    len = flags.precision;
  }

  flags.flag_fill = ' ';
  set_width_pading(buffer, s, flags, len);
}

void handle_unsigned(char **buffer, Specifiers flags, va_list args) {
  unsigned long num;
  char tmp[MAX_BUF_SIZE] = {0};
  int len = 0;

  if (flags.length == 'l') {
    num = va_arg(args, unsigned long);
  } else if (flags.length == 'h') {
    num = (unsigned short)va_arg(args, unsigned int);
  } else {
    num = va_arg(args, unsigned int);
  }
  int f = num;
  char *ptr = tmp + sizeof(tmp) - 1;
  *ptr = '\0';
  if (num == 0 && flags.precision == 0) {
    len = 0;
  } else {
    do {
      *--ptr = '0' + (num % 10);
      num /= 10;
      len++;
    } while (num > 0);

    if (flags.precision >= 0 && len < flags.precision) {
      int pad = flags.precision - len;
      s21_memmove(ptr + pad, ptr, len);
      s21_memset(ptr, '0', pad);
      len += pad;
    }
  }

  if (flags.flag == ' ' || (flags.flag == '+' && f > 0)) {
    s21_memmove(tmp + 1, tmp, len);
    tmp[0] = flags.flag;
    len++;
  } else if (f < 0) {
    s21_memmove(tmp + 1, tmp, len);
    tmp[0] = '-';
    len++;
  }

  set_width_pading(buffer, ptr, flags, len);
}

void handle_char(char **buffer, Specifiers flags, va_list args) {
  char tmp[MB_LEN_MAX] = {0};
  int len = 1;

  if (flags.length == 'l') {
    wchar_t wc = va_arg(args, wchar_t);
    len = wctomb(tmp, wc);
    if (len == -1) {
      tmp[0] = '?';
      len = 1;
    }
  } else {
    char c = (char)va_arg(args, int);
    tmp[0] = c;
  }

  flags.flag_fill = ' ';
  set_width_pading(buffer, tmp, flags, len);
}

void handle_percent(char **buffer, Specifiers flags) {
  if (flags.specifier == '%') {

    *(*buffer)++ = '%';
    **buffer = '\0';
  }
}

int proc_int_to_str(char *str, int int_part, int base) {
  DEBUG_PRINT("Star process handle_exp_int(|%s|,|%d|)\n", str - 3, int_part);
  char *tmp = str;
  int len = 0;
  if (int_part == 0) {
    *(tmp++) = '0';
  } else {
    int int_len = 0;
    long unsigned n = int_part;
    while (n > 0) {
      long unsigned digit = n % base;
      *(tmp++) = (digit < 10) ? '0' + digit : 'A' + digit - 10;
      int_len++;
      n /= base;
    }
    char *t = str;
    tmp--;
    while (tmp - str >= 0) {
      char temp = *tmp;
      *tmp = *str;
      *str = temp;
      DEBUG_PRINT("Inser char into str=%c\n", *tmp);
      str++;
      tmp--;
    }
    str = t + int_len;
    len += int_len;
  }
  *(str) = '\0';
  DEBUG_PRINT("Result stro to int conversation=|%s|\n", (str - len));
  return len;
}

int set_znak(char *tmp, Specifiers flags, long double *ch) {
  int res = 0;
  DEBUG_PRINT("Start process set_znak(|%s|,|%Lf|)\n", tmp, *ch);
  if (*ch < 0) {
    *tmp++ = '-';
    *ch *= -1;
    res++;
  } else if (flags.flag == '+') {
    *tmp++ = '+';
    res++;
  }
  DEBUG_PRINT("Set znak=|%s|\n", tmp - res);
  return res;
}

int add_exp(char *dst, int exp, Specifiers flags) {
  char *start = dst;
  DEBUG_PRINT("Start process add_exp(|%s|,|%d|)\n", dst, exp);
  if (flags.specifier == 'g' || flags.specifier == 'e') {
    *(dst++) = 'e';
  } else {
    *(dst++) = 'E';
  }
  if (exp < 0) {
    *(dst++) = '-';
    if (exp > -10) {
      *(dst++) = '0';
    }
    exp *= -1;
  } else {
    *(dst++) = '+';
    if (exp < 10) {
      *(dst++) = '0';
    }
  }
  dst += proc_int_to_str(dst, exp, 10);
  DEBUG_PRINT("add exp=|%s|\n", (dst - 3));
  return dst - start;
}

void set_width_pading_sign(char **buffer, char *src, Specifiers flags, int len,
                           char sign) {
  DEBUG_PRINT("proc_width_pading(%s,%s,%d,%c)\n", *buffer, src, len, sign);
  DEBUG_PRINT("Flags=|%c|, flag_Align=|%c|, flag_fill=|%c|\n", flags.flag,
              flags.flag_align, flags.flag_fill);
  int total_width = flags.width > 0 ? flags.width : 0;
  int padding = total_width > len ? total_width - len : 0;

  if (flags.flag_align == '-') { // Left align
    DEBUG_PRINT("Left align\n");
    if (sign) {
      *(*buffer)++ = sign;
      if (padding > 0) {
        padding--;
      }
    }
    s21_memcpy(*buffer, src, len);
    *buffer += len;
    s21_memset(*buffer, flags.flag_fill, padding);
    *buffer += padding;
  } else { // Rgiht align
    DEBUG_PRINT("Right align\n");
    if (flags.flag_fill != ' ') {
      DEBUG_PRINT("Insert sign=%c\n", sign);
      if (sign) {
        *(*buffer)++ = sign;
        if (padding > 0) {
          padding--;
        }
      }
      s21_memset(*buffer, flags.flag_fill, padding);
      *buffer += padding;
      s21_memcpy(*buffer, src, len);
    } else {
      s21_memset(*buffer, flags.flag_fill, padding);
      *buffer += padding;
      if (sign) {
        if (padding > 0) {
          *buffer -= 1;
        }
        *(*buffer)++ = sign;
      }
      s21_memcpy(*buffer, src, len);
    }
    *buffer += len;
  }
  *(*buffer) = '\0';
}

void set_width_pading(char **buffer, char *src, Specifiers flags, int len) {
  DEBUG_PRINT("proc_width_pading(%s,%s,%d)\n", *buffer, src, len);
  DEBUG_PRINT("Flags=%c", flags.flag);
  int total_width = flags.width > 0 ? flags.width : 0;
  int padding = total_width > len ? total_width - len : 0;
  DEBUG_PRINT("total_width=%d, padding= %d\n", total_width, padding);

  if (flags.flag_align == '-') { // Left align
    DEBUG_PRINT("Left align\n");
    s21_memcpy(*buffer, src, len);
    *buffer += len;
    s21_memset(*buffer, ' ', padding);
    *buffer += padding;
  } else { // Rgiht align
    DEBUG_PRINT("Right align\n");
    // char fill_char = (flags.flag == '0') ? '0' : ' ';
    s21_memset(*buffer, flags.flag_fill, padding);
    *buffer += padding;
    s21_memcpy(*buffer, src, len);
    *buffer += len;
  }

  *(*buffer) = '\0';
}

void handle_exp(char **buffer, Specifiers flags, va_list args) {
  DEBUG_PRINT("Start process void handle_ex()\n");
  long double ch;
  char tmp_arr[MAX_BUF_SIZE] = {0};
  char *tmp = tmp_arr;
  char *tmp_ptr = tmp;
  int exp = 0;
  long int_part = 0;
  int len = 0;
  if (flags.length == 'L') {
    ch = va_arg(args, long double);
  } else {
    ch = va_arg(args, double);
  }
  DEBUG_PRINT("Get args=|%Lf|\n", ch);
  len += set_znak(tmp, flags, &ch);
  tmp += len;
  DEBUG_PRINT("Set znak=|%s|\n", (tmp - 1));
  if (ch < 1) {
    while (ch < 1) {
      ch *= 10;
      exp--;
    }
  } else if (ch >= 10) {
    while (ch >= 10) {
      ch /= 10;
      exp++;
    }
  }
  int_part = (long)ch;
  tmp += proc_int_to_str(tmp, int_part, 10);
  *(tmp++) = '.';

  ch = ch - int_part;
  long int div_part = 0;
  if (flags.precision < 0) {
    flags.precision = 6;
  }
  len = tmp - tmp_ptr;
  DEBUG_PRINT("handle_exp: div_part=%Lf, flags.precision=%d\n", ch,
              flags.precision);
  if (flags.specifier == 'g' || flags.specifier == 'G') {
    if (int_part != 0 && ch * s21_pow(10, flags.precision - 1) > 1) {
      flags.precision--;
    } else {
      while (ch * s21_pow(10, flags.precision + 1) < 1) {
        flags.precision++;
      }
    }
  }

  ch *= s21_pow(10, flags.precision);
  DEBUG_PRINT("handle_exp: div_part=%Lf, flags.precision=%d\n", ch,
              flags.precision);
  div_part = (int)ch;
  if (ch - div_part >= 0.5) {
    div_part++;
  }
  if ((flags.specifier == 'g' || flags.specifier == 'G') &&
      div_part % 10 == 0) {
    div_part = div_part / 10;
  }

  DEBUG_PRINT("div_part = |%Lf|, int_div=|%ld|\n", ch, div_part);
  tmp += proc_int_to_str(tmp, div_part, 10);
  tmp += add_exp(tmp, exp, flags);
  set_width_pading(buffer, tmp_ptr, flags, tmp - tmp_ptr);
}

void handle_hex(char **buffer, Specifiers flags, va_list args) {
  DEBUG_PRINT("Start process void handle_hex()\n");
  long unsigned ch;
  char tmp_arr[MAX_BUF_SIZE] = {0};
  char *tmp = tmp_arr;
  char *tmp_ptr = tmp;
  if (flags.length == 'l') {
    ch = va_arg(args, long unsigned);
  } else {
    ch = va_arg(args, unsigned);
  }
  DEBUG_PRINT("Get args=|%lu|\n", (long unsigned)ch);

  tmp += proc_int_to_str(tmp, ch, 16);
  DEBUG_PRINT("strlen *tmp=|%d|\n", (int)s21_strlen(tmp_ptr));

  int len = tmp - tmp_ptr;
  if (flags.precision > len) {
    s21_memmove(tmp_ptr + flags.precision - len, tmp_ptr, len);
    s21_memset(tmp_ptr, '0', flags.precision - len);
    tmp += flags.precision - len;
  }
  if (flags.specifier == 'x') {
    char *r = (char *)s21_to_lower(tmp_ptr);
    s21_memcpy(tmp_ptr, r, tmp - tmp_ptr);
  } else {
    char *r = (char *)s21_to_upper(tmp_ptr);
    s21_memcpy(tmp_ptr, r, tmp - tmp_ptr);
  }
  set_width_pading(buffer, tmp_ptr, flags, tmp - tmp_ptr);
}

int get_exp(long double ch) {
  int res = 0;
  if (ch < 0) {
    ch *= -1;
  }
  if (ch > 1) {
    while (ch > 1) {
      ch /= 10;
      res++;
    }
  } else {
    while (ch < 1) {
      ch *= 10;
      res--;
    }
  }
  return res;
}

int proc_precission_g(double *ch, Specifiers flags) {
  int res = 0;
  int i = 0;
  int val = 0;
  if (*ch < 1) {
    while (val <= flags.precision) {
      int digit = (long)*ch * 10;
      *ch *= 10;
      if (digit != 0) {
        val++;
      }
      i++;
    }
  }
  *ch = *ch * ((double)s21_pow(10, val));
  DEBUG_PRINT("Number with precidsion=|%f|\n", *ch);

  return res;
}

void handle_general(char **buffer, Specifiers flags, va_list args) {
  va_list args_orig;
  va_copy(args_orig, args);
  double ch = va_arg(args, double);
  int exp = get_exp(ch);
  DEBUG_PRINT("Spec g: exp =|%d|\n", exp);
  proc_precission_g(&ch, flags);
  args = args_orig;
  if (exp < -4 || (exp >= flags.precision + 1 && !(flags.precision < 0))) {
    handle_exp(buffer, flags, args);
  } else {
    handle_float(buffer, flags, args);
  }
}

void handle_octal(char **buffer, Specifiers flags, va_list args) {
  unsigned long num, ch;
  char tmp[MAX_BUF_SIZE] = {0};
  int len = 0;

  if (flags.length == 'l') {
    num = va_arg(args, unsigned long);
  } else if (flags.length == 'h') {
    num = (unsigned short)va_arg(args, unsigned int);
  } else {
    num = va_arg(args, unsigned int);
  }
  ch = num;

  char *ptr = tmp + sizeof(tmp) - 1;
  *ptr = '\0';

  if (num == 0 && flags.precision == 0) {
    len = 0;
  } else {
    do {
      *--ptr = '0' + (num % 8);
      num /= 8;
      len++;
    } while (num > 0);
    DEBUG_PRINT("spec:%%o, len:%d, num=%ld\n", len, num);

    if (flags.precision >= 0 && len < flags.precision) {
      int pad = flags.precision - len;
      s21_memmove(ptr + pad, ptr, len); // Сдвигаем число вправо
      s21_memset(ptr, '0', pad); // Дополняем нулями слева
      len += pad;
    }
  }

  DEBUG_PRINT("spec:%%o, flag:#, len:%d, num=%ld\n", len, num);
  if (flags.flag == '#' && len > 0) {
    DEBUG_PRINT("ADD 0!\n")
    if (ch != 0) {
      *--ptr = '0';
    }
    len++;
  }

  set_width_pading(buffer, ptr, flags, len);
}
void handle_pointer(char **buffer, Specifiers flags, va_list args) {
  DEBUG_PRINT("Process handle_pointer()\n");
  void *ptr = va_arg(args, void *);
  if (ptr != S21_NULL) {
    uintptr_t num = (uintptr_t)ptr;

    char tmp[MAX_BUF_SIZE] = {0};
    char *tmp_ptr = tmp + sizeof(tmp) - 1;
    *tmp_ptr = '\0';

    if (num == 0) {
      *--tmp_ptr = '0';
    } else {
      while (num > 0) {
        int digit = num % 16;
        char c = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        *--tmp_ptr = c;
        num /= 16;
      }
    }

    *--tmp_ptr = 'x';
    *--tmp_ptr = '0';

    int len = (int)(tmp + sizeof(tmp) - 1 - tmp_ptr);

    DEBUG_PRINT("tmp_ptr=%s\n", tmp_ptr);
    if (flags.precision >= 0 && len - 2 < flags.precision) {
      int pad = flags.precision - (len - 2);
      DEBUG_PRINT("pad=%d\n", pad);
      s21_memmove(tmp_ptr + pad, tmp_ptr, len + 1);
      s21_memset(tmp_ptr + 2, '0', pad);
      len += pad;
    }
    DEBUG_PRINT("tmp_ptr=%s\n", tmp_ptr);

    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;
    if (flags.flag_align == '-') {
      s21_memcpy(*buffer, tmp_ptr, len);
      *buffer += len;
      s21_memset(*buffer, ' ', padding);
      *buffer += padding;
    } else {
      if (flags.flag_fill == '0' && flags.precision < 0) {
        s21_memcpy(*buffer, tmp_ptr, 2); // Копируем "0x"
        *buffer += 2;
        s21_memset(*buffer, '0', padding); // Заполняем нулями
        *buffer += padding;
        DEBUG_PRINT("tmp_ptr=%s\n", tmp_ptr);
        s21_memcpy(*buffer, tmp_ptr + 2, len - 2); // Копируем остальную часть
        *buffer += len - 2;
      } else {
        s21_memset(*buffer, ' ', padding);
        *buffer += padding;
        s21_memcpy(*buffer, tmp_ptr, len);
        *buffer += len;
      }
    }
    // set_width_pading(buffer, ptr, flags, len);

  } else {
    s21_memcpy(*buffer, "(nil)", 5);
    *buffer += 5;
  }
  **buffer = '\0';
}
