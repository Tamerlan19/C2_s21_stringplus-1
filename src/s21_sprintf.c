// [ ] Удалить импорт библиотеки, использовалась для отладки кода
#include "s21_string.h"
#include "s21_utils.h"
#include <stdio.h>

void handle_char(char **buffer, Specifiers flags, int c);
void handle_int(char **buffer, Specifiers flags, va_list argc);
void handle_float(char **buffer, Specifiers flags, va_list argc);
void handle_string(char **buffer, Specifiers flags, const char *s);
void handle_unsigned(char **buffer, Specifiers flags, unsigned int u);
void handle_percent(char **buffer, Specifiers flags);

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
        int c = va_arg(args, int);
        handle_char(&buffer, flags, c);
      } else if (flags.specifier == 'd') {
        handle_int(&buffer, flags, args);
      } else if (flags.specifier == 'f') {

        handle_float(&buffer, flags, args);
      } else if (flags.specifier == 's') {
        const char *s = va_arg(args, const char *);
        handle_string(&buffer, flags, s);
      } else if (flags.specifier == 'u') {
        unsigned int u = va_arg(args, unsigned int);
        handle_unsigned(&buffer, flags, u);
      } else if (flags.specifier == '%') {
        handle_percent(&buffer, flags);
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
      tmp[len++] = '0' + digit;
      frac_part -= digit;
    }
  } else {
    // Если точность не указана, используем значение по умолчанию
    sprintf(tmp, "%f", f); // Можно заменить на ручную реализацию
    len = s21_strlen(tmp);
  }

  // Добавляем '+' только если флаг установлен
  if (flags.flag == '+') {
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
void handle_string(char **buffer, Specifiers flags, const char *s) {
  if (s == NULL) {
    s = "(null)";
  }
  int len = s21_strlen(s);
  DEBUG_PRINT("len = %d\n", len);
  // Применяем точность, если она указана
  if (flags.precision >= 0 && len > flags.precision) {
    len = flags.precision;
  }
  // Определяем общую длину с учетом ширины
  int total_width = flags.width > 0 ? flags.width : 0;
  int padding = total_width > len ? total_width - len : 0;
  DEBUG_PRINT("TEST. len = %d, padding = %d, string= %s\n", len, padding, s);
  if (flags.flag == '-') { // Левое выравнивание
    s21_memcpy(*buffer, s, len);
    *buffer += len;
    s21_memset(*buffer, ' ', padding);
    *buffer += padding;
  } else { // Правое выравнивание

    s21_memset(*buffer, ' ', padding);
    *buffer += padding;
    DEBUG_PRINT("Right padding\n");
    s21_memcpy(*buffer, s, len);
    *buffer += len;
  }

  **buffer = '\0';
}

void handle_unsigned(char **buffer, Specifiers flags, unsigned int u) {
  char tmp[100] = {0}; // Буфер для временного хранения числа
  int len = 0; // Длина числа в строковом представлении

  // Шаг 1: Преобразуем число в строку
  char *ptr = tmp + sizeof(tmp) - 1; // Начинаем с конца массива
  *ptr = '\0'; // Завершающий нулевой символ
  if (u == 0 && flags.precision == 0) {
    // Если число равно 0 и точность равна 0, результат должен быть пустой
    // строкой
    len = 0;
  } else {
    unsigned int num = u;
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

  // Шаг 2: Определяем общую длину с учетом ширины
  int total_width = flags.width > 0 ? flags.width : 0;
  int padding = total_width > len ? total_width - len : 0;

  // Шаг 3: Выравнивание
  if (flags.flag == '-') { // Левое выравнивание
    s21_memcpy(*buffer, ptr, len);
    *buffer += len;
    s21_memset(*buffer, ' ', padding);
    *buffer += padding;
  } else { // Правое выравнивание
    char fill_char = (flags.flag == '0') && !(flags.flag == '-') ? '0' : ' ';
    s21_memset(*buffer, fill_char, padding);
    *buffer += padding;
    s21_memcpy(*buffer, ptr, len);
    *buffer += len;
  }

  // Шаг 4: Завершающий нулевой символ
  **buffer = '\0';
}
void handle_char(char **buffer, Specifiers flags, int c) {
  char tmp[2] = {(char)c, '\0'};
  int len = 1;

  // Определяем общую длину с учетом ширины
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
void handle_percent(char **buffer, Specifiers flags) {
  if (flags.specifier == '%') {

    *(*buffer)++ = '%';
    **buffer = '\0';
  }
}
