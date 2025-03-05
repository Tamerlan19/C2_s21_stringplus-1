// [ ] Удалить импорт библиотеки, использовалась для отладки кода
#include "s21_string.h"
#include "s21_utils.h"
#include <stdio.h>
#include <wchar.h>
#include <limits.h>
#include <stdint.h>

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

// int parse_specifiers_length(const char *format) {
//     int len = 0;
//     while (format[len] && (format[len] != ' ' || format[len] != '%')) {
//       len++;
//     }
//     // if (is_alpha(format[len])) {
//     //   len++; // Учитываем спецификатор
//     // }
//     DEBUG_PRINT("len = %d, format= = %s\n", len, format);
//     return len;
//   }

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *buffer = str;
  const char *ptr = format;
  DEBUG_PRINT("ptr = %s\n", ptr);
  DEBUG_PRINT("format = %s\n", format);
  while (*ptr) {
    if (*ptr == '%') {
      // ptr++;
      Specifiers flags = {'*', -10, -1, '*', '*'};
      // int t = parse_specifiers(ptr, &flags);
      ptr += parse_specifiers(ptr, &flags);
      // DEBUG_PRINT("Spec string_length = %s\n", t);
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
      } else if (flags.specifier == 'o') { // Добавляем обработку '%o'
        handle_octal(&buffer, flags, args);
      } else if (flags.specifier == 'p') { // Добавляем обработку '%p'
        handle_pointer(&buffer, flags, args);
      }else if (flags.specifier == '%') {
        handle_percent(&buffer, flags);
      } else if (flags.specifier == 'e' || flags.specifier == 'E') {
        handle_exp(&buffer, flags, args);
        DEBUG_PRINT("HANDLE_EXP: buffer=|%s|\n", buffer);
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
  if (flags.specifier == 'h') {
    d = (short int)va_arg(args, int);
  } else if (flags.specifier == 'l') {
    d = va_arg(args, long int);
  } else {
    d = (int)va_arg(args, int);
  }

  char tmp[300] = {0};
  int is_negative = (d < 0);
  long int num = (is_negative) ? -d : d; // Работаем с положительным числом
  int len = 0;

  if (num == 0) {
    tmp[len++] = '0';
  } else {
    while (num > 0) {
      tmp[len++] = '0' + (num % 10); // Получаем цифру и добавляем её в массив
      num /= 10;
    }
  }

  // Если число отрицательное, добавляем минус
  if (is_negative) {
    tmp[len++] = '-';
  }

  // Если задана точность, дополняем нулями слева
  if (flags.precision >= 0 && len < flags.precision) {
    int padding = flags.precision - len;
    for (int i = len - 1; i >= 0; i--) {
      tmp[i + padding] = tmp[i]; // Сдвигаем символы вправо
    }
    for (int i = 0; i < padding; i++) {
      tmp[i] = '0'; // Добавляем нули
    }
    len += padding;
  }

  // Разворачиваем строку, так как мы записывали цифры в обратном порядке
  for (int i = 0, j = len - 1; i < j; i++, j--) {
    char temp = tmp[i];
    tmp[i] = tmp[j];
    tmp[j] = temp;
  }

  // Определяем общую длину с учетом ширины
  int total_width = flags.width > 0 ? flags.width : 0;
  int padding = total_width > len ? total_width - len : 0;
  DEBUG_PRINT("padding= %d, total_width=%d\n", padding, total_width);

  // Копируем результат в буфер с учетом ширины
  if (flags.flag == '-') { // Левое выравнивание
    // Сначала копируем число
    for (int i = 0; i < len; i++) {
      *(*buffer + i) = tmp[i];
    }
    *buffer += len;

    // Затем добавляем пробелы справа
    for (int i = 0; i < padding; i++) {
      *(*buffer) = ' ';
      *buffer += 1;
    }
  } else { // Правое выравнивание
    char fill_char = (flags.flag == '0' && !is_negative)
                         ? '0'
                         : ' '; // Определяем символ заполнения
    // Сначала добавляем символы заполнения
    for (int i = 0; i < padding; i++) {
      *(*buffer) = fill_char;
      *buffer += 1;
    }
    // Затем копируем число
    for (int i = 0; i < len; i++) {
      *(*buffer + i) = tmp[i];
    }
    *buffer += len;
  }

  // Добавляем завершающий нулевой символ, если необходимо
  *(*buffer) = '\0';
}

void handle_float(char **buffer, Specifiers flags, va_list args) {
  char tmp[200] = {0};
  int len = 0;

  // Определяем тип числа в зависимости от модификатора длины
  double f;
  if (flags.length == 'l') {
    // Для 'l' используем double (по умолчанию)
    f = va_arg(args, double);
  } else {
    // Без модификатора длины также используем double
    f = va_arg(args, double);
  }
  // Преобразуем число в строку вручную
  if (flags.precision >= 0) {
    // Используем массив для хранения целой части и дробной части
    long int_part = (long)f;
    double frac_part = f - int_part;

    // Преобразуем целую часть
    if (int_part == 0) {
      tmp[len++] = '0';
    } else {
      int int_len = 0;
      if (int_part < 0) {
        tmp[len++] = '-';
        int_part = -int_part;
      }
      long n = int_part;
      while (n > 0) {
        tmp[int_len++] = '0' + (n % 10);
        n /= 10;
      }
      for (int i = 0; i < int_len / 2; i++) {
        char temp = tmp[i];
        tmp[i] = tmp[int_len - i - 1];
        tmp[int_len - i - 1] = temp;
      }
      len += int_len;
    }

    // Добавляем точку
    tmp[len++] = '.';

    // Преобразуем дробную часть
    for (int i = 0; i < flags.precision; i++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      if (i == flags.precision - 1 &&
          (frac_part - digit) * 10 >=
              5.0) { // 2025-02-26 01:24:15 @morrigem: add round
        digit = (int)frac_part + 1;
      }
      tmp[len++] = '0' + digit;
      frac_part -= digit;
    }
  } else {
    // Если точность не указана, используем значение по умолчанию
    sprintf(tmp, "%f", f); // Можно заменить на ручную реализацию
    len = s21_strlen(tmp);
  }

  // Добавляем '+' только если флаг установлен
  if (flags.flag == '+' && f > 0) {
    s21_memmove(tmp + 1, tmp, len);
    tmp[0] = '+';
    len++;
  }

  // Обработка ширины и выравнивания
  int total_width = flags.width > 0 ? flags.width : 0;
  int padding = total_width > len ? total_width - len : 0;

  if (flags.flag == '-') { // Левое выравнивание
    s21_memcpy(*buffer, tmp, len);
    *buffer += len;
    s21_memset(*buffer, ' ', padding);
    *buffer += padding;
  } else { // Правое выравнивание
    char fill_char = (flags.flag == '0') ? '0' : ' ';
    s21_memset(*buffer, fill_char, padding);
    *buffer += padding;
    s21_memcpy(*buffer, tmp, len);
    *buffer += len;
  }

  **buffer = '\0';
}

void handle_string(char **buffer, Specifiers flags, va_list args) {
    const char *s = NULL;
    wchar_t *ws = NULL;
    int len = 0;
    char tmp[MAX_BUF_SIZE] = {0}; // Объявляем временный буфер для преобразования широких строк

    // Проверяем длину
    if (flags.length == 'l') {
        // Обрабатываем широкую строку
        ws = va_arg(args, wchar_t*);
        if (ws == NULL) {
            s = "(null)";
        } else {
            // Преобразуем широкую строку в обычную (если нужно)
            // Используем wcstombs для преобразования
            wcstombs(tmp, ws, MAX_BUF_SIZE); // Преобразуем широкую строку в многобайтовую
            s = tmp; // Используем tmp как источник данных
        }
    } else {
        // Обрабатываем обычную строку
        s = va_arg(args, const char*);
        if (s == NULL) {
            s = "(null)";
        }
    }

    // Вычисляем длину строки
    len = s21_strlen(s);

    // Применяем точность (precision), если она указана
    if (flags.precision >= 0 && len > flags.precision) {
        len = flags.precision;
    }

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    // Выравнивание
    if (flags.flag == '-') { // Левое выравнивание
        s21_memcpy(*buffer, s, len); // Копируем строку
        *buffer += len;
        s21_memset(*buffer, ' ', padding); // Добавляем пробелы справа
        *buffer += padding;
    } else { // Правое выравнивание
        s21_memset(*buffer, ' ', padding); // Добавляем пробелы слева
        *buffer += padding;
        s21_memcpy(*buffer, s, len); // Копируем строку
        *buffer += len;
    }

    // Завершающий нулевой символ
    **buffer = '\0';
}

void handle_unsigned(char **buffer, Specifiers flags, va_list args) {
    unsigned long num; // Используем unsigned long для поддержки 'l'
    char tmp[MAX_BUF_SIZE] = {0}; // Буфер для временного хранения числа
    int len = 0; // Длина числа в строковом представлении

    // Получаем число из va_list с учетом длины
    if (flags.length == 'l') {
        num = va_arg(args, unsigned long); // Для 'l' используем unsigned long
    } else if (flags.length == 'h') {
        num = (unsigned short)va_arg(args, unsigned int); // Для 'h' используем unsigned short
    } else {
        num = va_arg(args, unsigned int); // По умолчанию unsigned int
    }

    // Преобразуем число в строку
    char *ptr = tmp + sizeof(tmp) - 1; // Начинаем с конца массива
    *ptr = '\0'; // Завершающий нулевой символ
    if (num == 0 && flags.precision == 0) {
        // Если число равно 0 и точность равна 0, результат должен быть пустой строкой
        len = 0;
    } else {
        do {
            *--ptr = '0' + (num % 10); // Преобразуем цифру в символ
            num /= 10;
            len++;
        } while (num > 0);

        // Применяем точность (precision)
        if (flags.precision >= 0 && len < flags.precision) {
            int pad = flags.precision - len;
            s21_memmove(ptr + pad, ptr, len); // Сдвигаем число вправо
            s21_memset(ptr, '0', pad); // Дополняем нулями слева
            len += pad;
        }
    }

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    // Выравнивание
    if (flags.flag == '-') { // Левое выравнивание
        s21_memcpy(*buffer, ptr, len);
        *buffer += len;
        s21_memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag == '0' && flags.precision < 0) ? '0' : ' ';
        s21_memset(*buffer, fill_char, padding);
        *buffer += padding;
        s21_memcpy(*buffer, ptr, len);
        *buffer += len;
    }

    // Завершающий нулевой символ
    **buffer = '\0';
}

void handle_char(char **buffer, Specifiers flags, va_list args) {
    char tmp[MB_LEN_MAX] = {0}; // Временный буфер для многобайтового символа
    int len = 1; // Длина символа (по умолчанию 1)

    // Проверяем длину
    if (flags.length == 'l') {
        // Обрабатываем широкий символ
        wchar_t wc = va_arg(args, wchar_t); // Извлекаем широкий символ
        len = wctomb(tmp, wc); // Преобразуем широкий символ в многобайтовый
        if (len == -1) {
            // Если преобразование не удалось, используем замену
            tmp[0] = '?';
            len = 1;
        }
    } else {
        // Обрабатываем обычный символ
        char c = (char)va_arg(args, int); // Извлекаем обычный символ
        tmp[0] = c;
    }

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    // Выравнивание
    if (flags.flag == '-') { // Левое выравнивание
        s21_memcpy(*buffer, tmp, len); // Копируем символ
        *buffer += len;
        s21_memset(*buffer, ' ', padding); // Добавляем пробелы справа
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag == '0') ? '0' : ' ';
        s21_memset(*buffer, fill_char, padding); // Добавляем символы заполнения слева
        *buffer += padding;
        s21_memcpy(*buffer, tmp, len); // Копируем символ
        *buffer += len;
    }

    // Завершающий нулевой символ
    **buffer = '\0';
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
    long n = int_part;
    while (n > 0) {
      // *(tmp++) = '0' + (n % 10);
      // n /= 10;
      // int_len++;
      int digit = n % base;
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
  // DEBUG_PRINT("Set exp_int=|%s|\n", (str-1));
  // DEBUG_PRINT("Set exp_int=|%s|\n", (str-2));
  // DEBUG_PRINT("Set exp_int=|%s|\n", (str-3));
  DEBUG_PRINT("Set exp_int=|%s|\n", (str - len));
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
  // int res = 0;
  char *start = dst;
  DEBUG_PRINT("Start process add_exp(|%s|,|%d|)\n", dst, exp);
  if (flags.specifier == 'g' || flags.specifier == 'e') {
    *(dst++) = 'e';
  } else {
    *(dst++) = 'E';
  }
  if (exp < 0) {
    *(dst++) = '-';
    exp *= -1;
  } else if (exp < 10) {
    *(dst++) = '+';
    *(dst++) = '0';
  } else if (exp < 10) {
    *(dst++) = '+';
  }
  dst += proc_int_to_str(dst, exp, 10);

  DEBUG_PRINT("add exp=|%s|\n", (dst - 3));
  return dst - start;
}

void proc_width_pading(char **buffer, char *src, Specifiers flags, int len) {
  DEBUG_PRINT("proc_width_pading(%s,%s,%d)\n", *buffer, src, len);
  int total_width = flags.width > 0 ? flags.width : 0;
  int padding = total_width > len ? total_width - len : 0;
  if (*src == '-' && flags.flag == '0') {
    *(*buffer)++ = *src++;
    len--;
  }
  if (flags.flag == '-') { // Left align
    DEBUG_PRINT("Left align\n");
    s21_memcpy(*buffer, src, len);
    *buffer += len;
    s21_memset(*buffer, ' ', padding);
    *buffer += padding;
  } else { // Rgiht align 
    DEBUG_PRINT("Right align\n");
    char fill_char = (flags.flag == '0') ? '0' : ' ';
    s21_memset(*buffer, fill_char, padding);
    *buffer += padding;
    s21_memcpy(*buffer, src, len);
    *buffer += len;
  }
}

void handle_exp(char **buffer, Specifiers flags, va_list args) {
  DEBUG_PRINT("Start process void handle_ex()\n");
  long double ch;
  // char *tmp = malloc(sizeof(char) * 100);
  char tmp_arr[MAX_BUF_SIZE] = {0};
  char *tmp = tmp_arr;
  // s21_memset(tmp, '\0', 100);
  char *tmp_ptr = tmp;
  int exp = 0;
  int int_part = 0;
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
  ch *= s21_pow(10, flags.precision);
  div_part = (int)ch;
  if (ch - div_part >= 0.5) {
    div_part++;
  }
  DEBUG_PRINT("div_part = |%Lf|, int_div=|%ld|\n", ch, div_part);
  tmp += proc_int_to_str(tmp, div_part, 10);
  tmp += add_exp(tmp, exp, flags);
  proc_width_pading(buffer, tmp_ptr, flags, tmp - tmp_ptr);
}
void handle_general(char **buffer, Specifiers flags, va_list args) {
  va_list args_orig;
  va_copy(args_orig, args);
  float ch = va_arg(args, double);
  if (flags.precision < 0) {
    flags.precision = 6;
  }
  args = args_orig;
  if ((ch / 10000) < 1) {
    handle_float(buffer, flags, args);
  } else {
    handle_exp(buffer, flags, args);
  }
}
void handle_hex(char **buffer, Specifiers flags, va_list args) {
    unsigned long num; // Используем unsigned long для поддержки 'l'
    char tmp[MAX_BUF_SIZE] = {0}; // Временный буфер для хранения числа
    int len = 0; // Длина числа в строковом представлении

    // Получаем число из va_list с учетом длины
    if (flags.length == 'l') {
        num = va_arg(args, unsigned long); // Для 'l' используем unsigned long
    } else if (flags.length == 'h') {
        num = (unsigned short)va_arg(args, unsigned int); // Для 'h' используем unsigned short
    } else {
        num = va_arg(args, unsigned int); // По умолчанию unsigned int
    }

    // Преобразуем число в шестнадцатеричную строку
    char *ptr = tmp + sizeof(tmp) - 1; // Начинаем с конца буфера
    *ptr = '\0'; // Завершающий нулевой символ

    if (num == 0) {
        *--ptr = '0'; // Если число равно 0, просто записываем '0'
        len = 1;
    } else {
        while (num > 0) {
            int digit = num % 16;
            char c;
            if (digit < 10) {
                c = '0' + digit;
            } else {
                // Для спецификатора 'x' используем буквы в нижнем регистре, для 'X' — в верхнем
                c = (flags.specifier == 'x') ? ('a' + digit - 10) : ('A' + digit - 10);
            }
            *--ptr = c; // Записываем символ в буфер
            num /= 16;
            len++;
        }
    }

    // Добавляем префикс "0x" или "0X", если установлен флаг '#'
    if (flags.flag == '#') {
        *--ptr = (flags.specifier == 'x') ? 'x' : 'X';
        *--ptr = '0';
        len += 2;
    }

    // Применяем точность (precision)
    if (flags.precision >= 0 && len < flags.precision) {
        int pad = flags.precision - len;
        s21_memmove(ptr + pad, ptr, len); // Сдвигаем число вправо
        s21_memset(ptr, '0', pad); // Дополняем нулями слева
        len += pad;
    }

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    // Выравнивание
    if (flags.flag == '-') { // Левое выравнивание
        s21_memcpy(*buffer, ptr, len);
        *buffer += len;
        s21_memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag == '0' && flags.precision < 0) ? '0' : ' ';
        s21_memset(*buffer, fill_char, padding);
        *buffer += padding;
        s21_memcpy(*buffer, ptr, len);
        *buffer += len;
    }

    // Завершающий нулевой символ
    **buffer = '\0';
}
void handle_octal(char **buffer, Specifiers flags, va_list args) {
    unsigned long num; // Используем unsigned long для поддержки 'l'
    char tmp[MAX_BUF_SIZE] = {0}; // Временный буфер для хранения числа
    int len = 0; // Длина числа в строковом представлении

    // Получаем число из va_list с учетом длины
    if (flags.length == 'l') {
        num = va_arg(args, unsigned long); // Для 'l' используем unsigned long
    } else if (flags.length == 'h') {
        num = (unsigned short)va_arg(args, unsigned int); // Для 'h' используем unsigned short
    } else {
        num = va_arg(args, unsigned int); // По умолчанию unsigned int
    }

    // Преобразуем число в восьмеричную строку
    char *ptr = tmp + sizeof(tmp) - 1; // Начинаем с конца массива
    *ptr = '\0'; // Завершающий нулевой символ

    if (num == 0 && flags.precision == 0) {
        // Если число равно 0 и точность равна 0, результат должен быть пустой строкой
        len = 0;
    } else {
        do {
            *--ptr = '0' + (num % 8); // Преобразуем цифру в символ
            num /= 8;
            len++;
        } while (num > 0);

        // Применяем точность (precision)
        if (flags.precision >= 0 && len < flags.precision) {
            int pad = flags.precision - len;
            s21_memmove(ptr + pad, ptr, len); // Сдвигаем число вправо
            s21_memset(ptr, '0', pad); // Дополняем нулями слева
            len += pad;
        }
    }

    // Добавляем префикс "0", если установлен флаг '#'
    if (flags.flag == '#' && len > 0) {
        *--ptr = '0';
        len++;
    }

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    // Выравнивание
    if (flags.flag == '-') { // Левое выравнивание
        s21_memcpy(*buffer, ptr, len);
        *buffer += len;
        s21_memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag == '0' && flags.precision < 0) ? '0' : ' ';
        s21_memset(*buffer, fill_char, padding);
        *buffer += padding;
        s21_memcpy(*buffer, ptr, len);
        *buffer += len;
    }

    // Завершающий нулевой символ
    **buffer = '\0';
}
void handle_pointer(char **buffer, Specifiers flags, va_list args) {
    void *ptr = va_arg(args, void *); // Извлекаем указатель из списка аргументов
    uintptr_t num = (uintptr_t)ptr;   // Преобразуем указатель в целое число

    // Инициализируем временный буфер для хранения результата
    char tmp[MAX_BUF_SIZE] = {0};
    char *tmp_ptr = tmp + sizeof(tmp) - 1; // Начинаем с конца буфера
    *tmp_ptr = '\0'; // Завершающий нулевой символ

    // Преобразуем число в шестнадцатеричную строку
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

    // Добавляем префикс "0x"
    *--tmp_ptr = 'x';
    *--tmp_ptr = '0';

    // Вычисляем длину строки
    int len = (int)(tmp + sizeof(tmp) - 1 - tmp_ptr);

    // Применяем точность (precision)
    if (flags.precision >= 0 && len - 2 < flags.precision) { // Учитываем длину "0x"
        int pad = flags.precision - (len - 2);
        s21_memmove(tmp_ptr + pad, tmp_ptr + 2, len - 2); // Сдвигаем число вправо
        s21_memset(tmp_ptr + 2, '0', pad);               // Дополняем нулями слева
        len += pad;
    }

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    // Выравнивание
    if (flags.flag == '-') { // Левое выравнивание
        s21_memcpy(*buffer, tmp_ptr, len);
        *buffer += len;
        s21_memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag == '0' && flags.precision < 0) ? '0' : ' ';
        s21_memset(*buffer, fill_char, padding);
        *buffer += padding;
        s21_memcpy(*buffer, tmp_ptr, len);
        *buffer += len;
    }

    // Завершающий нулевой символ
    **buffer = '\0';
}
