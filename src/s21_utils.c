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

int s21_strcmp(const char *str1, const char *str2) {
  int rtn = 0;
  for (; *str1 && *str1 == *str2; str1++, str2++)
    ;
  int result = *str1 - *str2;
  if (result > 0)
    rtn = 1;
  else if (result < 0)
    rtn = -1;
  else
    rtn = 0;
  return rtn;
}

char *s21_strcpy(char *dest, const char *src) {
  if (src != S21_NULL) {
    for (int i = 0; (dest[i] = src[i]) != '\0'; i++) {
    }
  }
  return dest;
}

char *s21_strcat(char *destination, const char *append) {
  int len = 0;
  for (; destination[len] != '\0'; len++) {
  }
  for (; *append; append++, len++) {
    destination[len] = *append;
  }
  return destination;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  // Приводим указатели к типу unsigned char для побайтового копирования
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;
  // Если dest и src указывают на одну и ту же область памяти, ничего не делаем
  if (d == s) {
    return dest;
  }
  // Если dest находится после src и перекрывается с ним, копируем с конца
  if (d > s && d < s + n) {
    for (size_t i = n; i > 0; i--) {
      d[i - 1] = s[i - 1];
    }
  }
  // В остальных случаях копируем с начала
  else {
    for (size_t i = 0; i < n; i++) {
      d[i] = s[i];
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
  if ((*(format) == '+' || *(format) == '-' || *(format) == ' ' ||
       *(format) == '#' || *(format) == '0')) {
    st_spec->flag = *(format);
    DEBUG_PRINT(" FLAGS=%c\n", st_spec->flag);
    format++;
  }
  if (*(format) == '*' || is_digit(*(format))) {
    if (*(format) == '*') {
      st_spec->flag = *(format);
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
    if (*(format) == '*')
      st_spec->precision = -1;
    else {
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
  DEBUG_PRINT("RESULT: parse_specifiers()=%ld Specifier=%c, Length=%c, "
              "Precision=%i,  Width=%d, Flags=%c\n",
              format - fmt, st_spec->specifier, st_spec->length,
              st_spec->precision, st_spec->width, st_spec->flag);
  DEBUG_PRINT(" fmt_length=%ld, format_length=%ld\n", s21_strlen(fmt),
              s21_strlen(format));
  return format - fmt;
}

int is_digit(char c) { return (c >= '0' && c <= '9'); }
int is_octa(char c) { return (c >= '0' && c <= '7'); }
int is_hex(char c) {
  return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
}

int is_alpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
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
    while (y < 0) {
      result = 1 / s21_pow(x, y * -1);
      y++;
    }
  } else {
    while (y > 0) {
      result = result * x;
      y--;
    }
  }
  return result;
}