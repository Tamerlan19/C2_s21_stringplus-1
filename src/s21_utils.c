#include "s21_utils.h"
#include "s21_string.h"

int contains_char(const char *str, char ch) {
  while (*str) {
    if (*str == ch) {
      return 1; // Найден символ
    }
    str++;
  }
  return 0;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  if (d != s) {
    if (d > s && d < s + n) {
      for (size_t i = n; i > 0; i--) {
        d[i - 1] = s[i - 1];
      }
    } else {
      for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
      }
    }
  }
  return dest;
}

/**
 * @brief Parses the format string and extracts the specifiers.
 *
 * @param fmt The format string to parse.
 * @param st_spec A pointer to a Specifiers struct to store the parsed
 * specifiers.
 * @return The number of characters parsed.
 */
int parse_specifiers(const char *fmt, Specifiers *st_spec) {
  const char *format = fmt;
  format++;
  DEBUG_PRINT("format=%s\n", format);
  if (*(format) == '+' || *(format) == '#') {
    st_spec->flag = *(format);
    DEBUG_PRINT(" FLAGS=%c\n", st_spec->flag);
    format++;
  }
  if (*(format) == ' ' || *(format) == '0') {
    st_spec->flag_fill = *(format);
    DEBUG_PRINT(" FLAGS=%c\n", st_spec->flag_fill);
    format++;
  }
  if ( *(format) == '-' ) {
    st_spec->flag_align = *(format);
    DEBUG_PRINT(" FLAGS=%c\n", st_spec->flag_align);
    format++;
  }
  // Width
  if (*(format) == '*' || is_digit(*(format))) {
    if (*(format) == '*') {
      // st_spec->flag = *(format); // 2025-03-16 22:51:32 @morrigem:fix get width from argv
      st_spec->width = -1; // 2025-03-16 22:51:32 @morrigem:fix get width from argv
      format++;
    }
    if (is_digit(*(format))) {
      st_spec->width = 0;
      while (is_digit(*(format))) {
        st_spec->width = st_spec->width * 10 + *(format) - '0';
        format++;
      }
    }
    DEBUG_PRINT("Width=%i\n", st_spec->width);
  }
  // Precision
  if (*(format) == '.') {
    format++;
    st_spec->precision = 0;
    if (*(format) == '*') {
      st_spec->precision = -1;
      format++;
    } else {
      while (is_digit(*(format))) {
        st_spec->precision = st_spec->precision * 10 + *(format) - '0';
        format++;
      }
    }
    DEBUG_PRINT(" Precision=%i\n", st_spec->precision);
  }

  // Length
  if (*(format) == 'h' || *(format) == 'l' || *(format) == 'L') {
    st_spec->length = *(format);
    format++;
    DEBUG_PRINT(" Length=%c\n", st_spec->length);
  }

  // Specifiers
  if (*format == 'c' || *format == 'd' || *format == 'i' || *format == 'f' ||
      *format == 's' || *format == 'u' || *format == '%' || *format == 'g' ||
      *format == 'G' || *format == 'e' || *format == 'E' || *format == 'x' ||
      *format == 'X' || *format == 'o' || *format == 'p' || *format == 'n') {
    st_spec->specifier = *format;
    format++;
    DEBUG_PRINT("Specifier=%c\n", st_spec->specifier);
  } else {
    st_spec->specifier = '0';
  }
  DEBUG_PRINT("RESULT: parse_specifiers()=%td Specifier=%c, Length=%c, "
              "Precision=%i,  Width=%d, Flags=%c\n",
              format - fmt, st_spec->specifier, st_spec->length,
              st_spec->precision, st_spec->width, st_spec->flag);
  DEBUG_PRINT(" fmt_length=%lu, format_length=%lu\n",
              (unsigned long)s21_strlen(fmt),
              (unsigned long)s21_strlen(format));
  return format - fmt;
}

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_hex(char c) {
  return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
}

void int_to_str(int num, char *str, int base) {
  int i = 0;
  int is_negative = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0 && base == 10) {
    is_negative = 1;
    num = -num;
  }

  while (num > 0) {
    int digit = num % base;
    str[i++] = (digit > 9) ? (digit - 10) + 'A' : digit + '0';
    num /= base;
  }

  if (is_negative) {
    str[i++] = '-';
  }

  str[i] = '\0';

  int start = 0, end = i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

int is_space(char c) { return (c == ' ' || c == '\t' || c == '\n'); }

void noop_space(const char **str) {
  if (*str != S21_NULL) {
    while ((is_space(**str))) {
      DEBUG_PRINT("Noop space.\n");
      (*str)++;
    }
  }
}

long double s21_pow(int x, int y) {
  long double result = 1.0;
  if (y < 0) {
    result = result / s21_pow(x, y * -1);
  } else {
    while (y > 0) {
      result = result * x;
      y--;
    }
  }
  return result;
}

int get_width(const char *str, const Specifiers st_spec) {
  int width = 0;
  if (st_spec.width >= 0 && st_spec.width < (int)s21_strlen(str)) {
    width = st_spec.width;
  } else {
    width = (int)s21_strlen(str);
  }

  return width;
}