// #include <stdio.h>
#include "s21_string.h"
#include <locale.h>
#include <stdarg.h>
// #include <stdio.h>
#include <string.h>

float s21_pow(int x, int y);
int get_number(const char *p, long int *res);
int proc_spec_s(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_d(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_s(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_f(const char *str, va_list args, const Specifiers st_spec);
int proc_spec_c(const char *str, va_list args, const Specifiers st_spec);
int is_alpha(char c);
int is_digit(char c);
int is_space(char c);
// Specifiers parse_specifiers(const char *format);
int parse_specifiers(const char *format, Specifiers *st_spec);

void monster_flags(const char *format, Specifiers *flags);
void handle_char(char **buffer, Specifiers flags, int c);
void handle_int(char **buffer, Specifiers flags, int d);
void handle_float(char **buffer, Specifiers flags, double f);
void handle_string(char **buffer, Specifiers flags, const char *s);
void handle_unsigned(char **buffer, Specifiers flags, unsigned int u);
void handle_percent(char **buffer, Specifiers flags);

/**
 TODO: Part 1. string.h Functions
 - Оформи решение как статическую библиотеку с названием s21_string.a (с
заголовочным файлом s21_string.h).
 - Библиотека должна быть разработана в соответствии с принципами структурного
программирования, обязательно исключи дублирование в коде.
 - Подготовь полное покрытие unit-тестами функций библиотеки c помощью
библиотеки Check.
 - Unit-тесты должны проверять результаты работы твоей реализации путём
сравнения ее с реализацией стандартной библиотеки string.h.
 - Unit-тесты должны покрывать не менее 80% каждой функции.
 - Предусмотри Makefile для сборки библиотеки и тестов (с целями all, clean,
test, s21_string.a, gcov_report).
 - В цели gcov_report должен формироваться отчёт gcov в виде html страницы. Для
этого unit-тесты должны запускаться с флагами gcov.
 - Перед каждой функцией используй префикс s21_.
No.	Function	Description
 - [ ] void *s21_memchr(const void *str, int c, s21_size_t n)	Searches for the
first occurrence of the character c (an unsigned char) in the first n bytes of
the string pointed to, by the argument str.
 - [ ] int s21_memcmp(const void *str1, const void *str2, s21_size_t n)	Compares
the first n bytes of str1 and str2.
 - [x] void *s21_memcpy(void *dest, const void *src, s21_size_t n)	Copies n
characters from src to dest.
 - [x] void *s21_memset(void *str, int c, s21_size_t n)	Copies the character c
(an unsigned char) to the first n characters of the string pointed to, by the
argument str.
 - [x] char *s21_strncat(char *dest, const char *src, s21_size_t n)	Appends
the string pointed to, by src to the end of the string pointed to, by dest up to
n characters long.
 - [x] char *s21_strchr(const char *str, int c)	Searches for the first
occurrence of the character c (an unsigned char) in the string pointed to, by
the argument str.
 - [x] int s21_strncmp(const char *str1, const char *str2, s21_size_t n)
Compares at most the first n bytes of str1 and str2.
 - [x] char *s21_strncpy(char *dest, const char *src, s21_size_t n)	Copies
up to n characters from the string pointed to, by src to dest.
 - [x] s21_size_t s21_strcspn(const char *str1, const char *str2)
Calculates the length of the initial segment of str1 which consists entirely of
characters not in str2.
 - [ ] 	char *s21_strerror(int errnum)	Searches an internal array for the error
number errnum and returns a pointer to an error message string. You need to
declare macros containing arrays of error messages for mac and linux operating
systems. Error descriptions are available in the original library. Checking the
current OS is carried out using directives.
 - [x] 	s21_size_t s21_strlen(const char *str)	Computes the length of the
string str up to but not including the terminating null character.
 - [ ] 	char *s21_strpbrk(const char *str1, const char *str2)	Finds the first
character in the string str1 that matches any character specified in str2.
 - [ ] 	char *s21_strrchr(const char *str, int c)	Searches for the last
occurrence of the character c (an unsigned char) in the string pointed to by the
argument str.
 - [ ] 	char *s21_strstr(const char *haystack, const char *needle)	Finds
the first occurrence of the entire string needle (not including the terminating
null character) which appears in the string haystack.
 - [ ] 	char *s21_strtok(char *str, const char *delim)	Breaks string str into a
series of tokens separated by delim.
 */

/**
TODO: Part 2. Частичная реализация функции sprintf
Тебе необходимо реализовать функцию sprintf из библиотеки stdio.h:
- [ ] sprintf(): %[флаги][ширина][.точность][длина]спецификатор
- [ ] обработка форматной строки и заполнение параметров вывода (Структура?)
Функция должна быть размещена в библиотеке s21_string.h.
На реализацию функции накладываются все требования, изложенные в первой части.
Должно поддерживаться частичное форматирование:
Спецификаторы: c, d, f, s, u, %
Флаги: -, +, (пробел)
Ширина: (число)
Точность: .(число)
Длина: h, l
 */

/**
TODO: Part 3. Дополнительно. Реализация некоторых модификаторов формата функции
- [ ] sprintf Необязательное задание на дополнительные баллы: реализуй некоторые
модификаторы формата функции sprintf из библиотеки stdio.h:

Функция должна быть размещена в библиотеке s21_string.h.
На реализацию функции накладываются все требования, изложенные в первой части.
Должны поддерживаться следующие дополнительные модификаторы формата:
Спецификаторы: g, G, e, E, x, X, o, p
Флаги: #, 0
Ширина: *
Точность: .*
Длина: L
*/
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    if (str1 && str2) { // Проверяем, что оба указателя не NULL
        const unsigned char *s1 = (const unsigned char *)str1;
        const unsigned char *s2 = (const unsigned char *)str2;

        for (s21_size_t i = 0; i < n; i++) {
            if (s1[i] != s2[i]) { // Сравниваем байты
                return (int)(s1[i] - s2[i]); // Возвращаем разницу между байтами
            }
        }
    }

    return 0; // Если все байты совпадают или n == 0, возвращаем 0
}

void *s21_memset(void *str, int c, s21_size_t n) {
    if (str) { // Проверяем, что указатель не NULL
        unsigned char *ptr = (unsigned char *)str; // Преобразуем указатель к типу unsigned char*
        unsigned char value = (unsigned char)c;    // Преобразуем значение c к unsigned char

        for (s21_size_t i = 0; i < n; i++) {
            ptr[i] = value; // Записываем значение в каждый байт
        }
    }

    return str; // Возвращаем исходный указатель
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    if (dest && src) { // Проверяем, что обе строки не NULL
        char *dest_end = dest;

        // Находим конец строки dest
        while (*dest_end) {
            dest_end++;
        }

        // Копируем символы из src в dest, пока не достигнем n или '\0'
        for (s21_size_t i = 0; i < n && *src; i++, src++, dest_end++) {
            *dest_end = *src;
        }

        // Добавляем завершающий нулевой символ
        *dest_end = '\0';
    }

    return dest; // Возвращаем указатель на dest
}

int contains_char(const char *str, char ch) {
    while (*str) {
        if (*str == ch) {
            return 1; // Найден символ
        }
        str++;
    }
    return 0; 
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t count = 0;

    if (str1 && str2) { // Проверяем, что обе строки не NULL
        while (*str1 && !contains_char(str2, *str1)) {
            count++;
            str1++;
        }
    }

    return count;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest; 
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; *(str + len); len++)
    ;
  return len;
}

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * @param str The string to search.
 * @param ch The character to find.
 * @return A pointer to the first occurrence of the character in the string, or
 * NULL if the character is not found.
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int rtn = 0;
  int is_diff = 0;
  for (s21_size_t i = 0; i < n && !is_diff; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
      is_diff++;
      rtn = (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return rtn;
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

/**
 * @brief Copies the string pointed to by src to the buffer pointed to by dest.
 *
 * @param dest The destination buffer.
 * @param src The source string.
 * @return A pointer to the destination buffer.
 */
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

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * @param str The string to search.
 * @param ch The character to find.
 * @return A pointer to the first occurrence of the character in the string, or
 * NULL if the character is not found.
 */
char *s21_strchr(const char *str, int ch) {
  char *rtn = S21_NULL;
  if (str != S21_NULL) {
    for (; *str != '\0' && *str != ch; str++) {
    }
    if (*str == ch)
      rtn = (char *)str;
  }
  return rtn;
}

/**
 * @brief Copies n bytes from the memory area src to the memory area dest.
 *
 * @param dest The destination memory area.
 * @param src The source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination memory area.
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  // Приводим указатели к типу char* для побайтового копирования
  char *d = (char *)dest;
  const char *s = (const char *)src;

  // Копируем n байт из src в dest
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  // Возвращаем указатель на dest
  return dest;
}

int parse_specifiers_length(const char *format) {
  int len = 0;
  while (format[len] && (format[len]!=' ' || format[len] != '%')) {
    len++;
  }
  // if (is_alpha(format[len])) {
  //   len++; // Учитываем спецификатор
  // }
  DEBUG_PRINT("len = %d, format= = %s\n", len, format);
  return len;
}

void int_to_str(int num, char *str, int base) {
  int i = 0;
  int is_negative = 0;

  // Обрабатываем 0 отдельно
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  // Обрабатываем отрицательные числа для десятичной системы
  if (num < 0 && base == 10) {
    is_negative = 1;
    num = -num; // Преобразуем в положительное
  }

  // Преобразуем число в строку (обратный порядок)
  while (num > 0) {
    int digit = num % base;
    str[i++] = (digit > 9) ? (digit - 10) + 'A' : digit + '0';
    num /= base;
  }

  // Добавляем знак минус для десятичной системы
  if (is_negative) {
    str[i++] = '-';
  }

  str[i] = '\0'; // Завершаем строку

  // Переворачиваем строку
  int start = 0, end = i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}


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
            Specifiers flags  = {'*', -10, -1, '*', '*'};
            // int t = parse_specifiers(ptr, &flags);
            ptr += parse_specifiers(ptr, &flags);
            // DEBUG_PRINT("Spec string_length = %s\n", t);
            DEBUG_PRINT("RESULT: Specifier=%c, Length=%c, Precision=%i,  Width=%d, Flags=%c\n", flags.specifier,flags.length,flags.precision,flags.width,flags.flag);
            char spec = *ptr;
                if (flags.specifier== 'c') {
                    int c = va_arg(args, int);
                    handle_char(&buffer, flags, c);
                } else if (flags.specifier== 'd') {
                    int d = va_arg(args, int);
                    handle_int(&buffer, flags, d);
                } else if (flags.specifier == 'f') {
                    double f = va_arg(args, double);
                    handle_float(&buffer, flags, f);
                } else if (flags.specifier == 's') {
                    const char *s = va_arg(args, const char *);
                    handle_string(&buffer, flags, s);
                } else if (flags.specifier == 'u') {
                    unsigned int u = va_arg(args, unsigned int);
                    handle_unsigned(&buffer, flags, u);
                } else if (flags.specifier == '%') {
                    handle_percent(&buffer, flags);
                }else
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
* @param buffer A pointer to the buffer where the formatted string will be stored.
* @param flags The flags specifying the formatting options.
* @param d The integer to be formatted.
*/
void handle_int(char **buffer, Specifiers flags, int d) {
    char tmp[300] = {0};
    int is_negative = (d < 0);
    int num = (is_negative) ? -d : d; // Работаем с положительным числом
    int len = 0;

    // Преобразуем число в строку вручную
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
    if (flags.flag=='-' ) { // Левое выравнивание
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
        char fill_char = (flags.flag=='0' && !is_negative) ? '0' : ' '; // Определяем символ заполнения
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


void handle_float(char **buffer, Specifiers flags, double f) {
    char tmp[200] = {0};
    int len = 0;

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
        len = strlen(tmp);
    }

    // Добавляем '+' только если флаг установлен
    if (flags.flag == '+') {
        memmove(tmp + 1, tmp, len);
        tmp[0] = '+';
        len++;
    }

    // Обработка ширины и выравнивания
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    if (flags.flag == '-') { // Левое выравнивание
        memcpy(*buffer, tmp, len);
        *buffer += len;
        memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag == '0') ? '0' : ' ';
        memset(*buffer, fill_char, padding);
        *buffer += padding;
        memcpy(*buffer, tmp, len);
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
        memcpy(*buffer, s, len);
        *buffer += len;
        memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание

        memset(*buffer, ' ', padding);
        *buffer += padding;
    DEBUG_PRINT("Right padding\n");
        // memset(*buffer, '1', 2);
        // *buffer += 2;        
        memcpy(*buffer, s, len);
        *buffer += len;
    }

    **buffer = '\0';
}

void handle_unsigned(char **buffer, Specifiers flags, unsigned int u) {
    char tmp[100] = {0};
    if (flags.precision >= 0) {
        char fmt[20] = {0};
        sprintf(fmt, "%%.%du", flags.precision);
        sprintf(tmp, fmt, u);
    } else {
        sprintf(tmp, "%u", u);
    }

    int len = strlen(tmp);

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    if (flags.flag & '-') { // Левое выравнивание
        memcpy(*buffer, tmp, len);
        *buffer += len;
        memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag & '0') ? '0' : ' ';
        memset(*buffer, fill_char, padding);
        *buffer += padding;
        memcpy(*buffer, tmp, len);
        *buffer += len;
    }

    **buffer = '\0';
}
void handle_char(char **buffer, Specifiers flags, int c) {
    char tmp[2] = {(char)c, '\0'};
    int len = 1;

    // Определяем общую длину с учетом ширины
    int total_width = flags.width > 0 ? flags.width : 0;
    int padding = total_width > len ? total_width - len : 0;

    if (flags.flag == '-') { // Левое выравнивание
        memcpy(*buffer, tmp, len);
        *buffer += len;
        memset(*buffer, ' ', padding);
        *buffer += padding;
    } else { // Правое выравнивание
        char fill_char = (flags.flag == '0') ? '0' : ' ';
        memset(*buffer, fill_char, padding);
        *buffer += padding;
        memcpy(*buffer, tmp, len);
        *buffer += len;
    }

    **buffer = '\0';
}
void handle_percent(char **buffer, Specifiers flags) {
  if (flags.specifier=='%'){

    *(*buffer)++ = '%';
    **buffer = '\0';
  }
}


/**
* @brief Parses the format string and extracts the specifiers.
*
* @param fmt The format string to parse.
* @param st_spec A pointer to a Specifiers struct to store the parsed specifiers.
* @return The number of characters parsed.
*/
int parse_specifiers(const char *fmt, Specifiers *st_spec) {
  // Specifiers st_spec = {'*', -10, 0, '*', '*'};
  const char *format = fmt;
  format++;
  DEBUG_PRINT("format=%s\n", format);
  // Flags
  if ((*(format) == '+' || *(format) == '-' || *(format) == ' ' ||
       *(format) == '#' || *(format) == '0')) {
    st_spec->flag = *(format);
    DEBUG_PRINT(" FLAGS=%c\n", st_spec->flag);
    format++;
  }
  if (*(format) == '*' || is_digit(*(format))) {
    st_spec->width = 0;
    if (*(format) == '*') {

      st_spec->width = -1;
      format++;
    } else {
      while (is_digit(*(format))) {
        st_spec->width = st_spec->width * 10 + *(format) - '0';
        format++;
      }
    }
    // format++;
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
    DEBUG_PRINT("format=%s\n", format);
  if (*format == 'c' || *format == 'd' || *format == 'i' || *format == 'f' ||
      *format == 's' || *format == 'u' || *format == '%' || *format == 'g' ||
      *format == 'G' || *format == 'e' || *format == 'E' || *format == 'x' ||
      *format == 'X' || *format == 'o' || *format == 'p') {
    st_spec->specifier = *format;
    format++;
    DEBUG_PRINT("Specifier=%c\n", st_spec->specifier);
  } else {
    st_spec->specifier = '0';
  }
  // format++;
  DEBUG_PRINT("RESULT: Specifier=%c, Length=%c, Precision=%i,  Width=%d, Flags=%c\n", st_spec->specifier,st_spec->length,st_spec->precision,st_spec->width,st_spec->flag);
  return format-fmt;
}

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_alpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_space(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/*TODO: Flags
 - [ ] #    При использовании со спецификаторами o, x или X перед числом
 вставляется 0, 0x или 0X соответственно (для значений, отличных от нуля). При
 использовании с e, E и f «заставляет» записанный вывод содержать десятичную
 точку, даже если за ней не последует никаких цифр. По умолчанию, если не
 следует никаких цифр, десятичная точка не записывается. При использовании с g
 или G результат такой же, как и с e или E, но конечные нули не удаляются.
 - [ ] 0    Заполняет число слева нулями (0) вместо пробелов, где указан
 спецификатор ширины (см. подспецификатор ширины).
*/

/*TODO: Width
 - [ ] (число)  Минимальное количество печатаемых символов. Если выводимое
 значение короче этого числа, результат дополняется пробелами. Значение не
 усекается, даже если результат больше.
 - [ ] *    В sprintf знак * значит, что ширина указывается не в строке формата,
 а в качестве дополнительного аргумента целочисленного значения, предшествующего
 аргументу, который необходимо отформатировать. В sscanf знак *, помещенный
 после % и перед спецификатором формата, считывает данные указанного типа, но
 подавляет их присваивание.
 */

/*TODO: Длина
 - [ ] h    Аргумент интерпретируется как короткое int или короткое int без
 знака (применяется только к целочисленным спецификаторам: i, d, o, u, x и X).
 - [ ] l    Аргумент интерпретируется как длинное int или длинное int без знака
 для целочисленных спецификаторов (i, d, o, u, x и X) и как широкий символ или
 строка широких символов для спецификаторов c и s.
 - [ ] L    Аргумент интерпретируется как длинный double (применяется только к
 спецификаторам с плавающей точкой — e, E, f, g и G).
*/

/**
TODO: Part 4. Дополнительно. Реализация функции sscanf
Необязательное задание на дополнительные баллы: реализуй функцию sscanf из
библиотеки stdio.h:
%[*][ширина][длина]спецификатор
Функция должна быть размещена в библиотеке s21_string.h;
На реализацию функции накладываются все требования, изложенные в первой части.
Должно поддерживаться полное форматирование (с учетом флагов, ширины, точности,
модификаторов и типов преобразования).
[ ] Спецификаторы: c, d, f, s, u, %, i
 - Ширина: (число)
 - Длина: h, l
[ ] Спецификаторы: g, G, e, E, x, X, o, p
 - Ширина: *
 - Длина: L
[x] %[*|ширина][длина]c.
[x] %[*|ширина][длина]d.
[x] %[*|ширина][длина]f.
[ ] %[*|ширина][длина]s.
[ ] %[*|ширина][длина]u.
[ ] %[*|ширина][длина]%
[ ] %[*|ширина][длина]g.
[ ] %[*|ширина][длина]G.
[ ] %[*|ширина][длина]e.
[ ] %[*|ширина][длина]E.
[ ] %[*|ширина][длина]x.
[ ] %[*|ширина][длина]X.
[ ] %[*|ширина][длина]o.
[ ] %[*|ширина][длина]p.
*/

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  Specifiers st_spec;
  const char *p = str; // Указатель на входную строку
  const char *fmt = format; // Указатель на строку формата
  //%[*/ширина][длина]спецификатор.
  int res = 0;

  while (*fmt) {
    if (*fmt == '%') {
      DEBUG_PRINT("\n");
      parse_specifiers(fmt, &st_spec);
      // st_spec = parse_specifiers(fmt);
      if (st_spec.width < -1) {
        st_spec.width = s21_strlen(p);
      }
      // DEBUG_PRINT("\nFormat string:%s\n", fmt);
      DEBUG_PRINT(" result=%d\n", res);
      DEBUG_PRINT(" str=%s\n", p);
      DEBUG_PRINT(" format=%s\n", fmt);
      DEBUG_PRINT(" !!! Flag=%c, Width=%i, Length=%c, Precision=%i, "
                  "Specifiers=%c\n",
                  st_spec.flag, st_spec.width, st_spec.length,
                  st_spec.precision, st_spec.specifier);
      if (st_spec.specifier == 'c') {
        int step = 0;
        step = proc_spec_c(p, args, st_spec);
        if (step > 0) {
          p = p + step;
          if (st_spec.width != asterisk) {
            res++;
          }
        } else if (step <= 0) {
          res--;
        }
        DEBUG_PRINT(" after process Char Result=%d\n", res);

      } else if (st_spec.specifier == 'd') {
        while ((is_space(*p)) && *p != '-') {
          DEBUG_PRINT("Noop symbol:|%c|\n", *p);
          p++;
        }
        int step = 0;
        step = proc_spec_d(p, args, st_spec);
        if (step > 0) {
          p = p + step;
          if (st_spec.width != asterisk) {
            res++;
          }
        } else if (step < 0) {
          res--;
        }
        DEBUG_PRINT(" FINISH position=%s\n", p);

      } else if (st_spec.specifier == 'f') {
        while ((is_space(*p)) && *p != '-') {
          DEBUG_PRINT("Noop symbol:|%c|\n", *p);
          p++;
        }
        int step = 0;
        step = proc_spec_f(p, args, st_spec);
        if (step > 0) {
          p = p + step;
          if (st_spec.width != asterisk) {
            res++;
          }
        } else if (step < 0) {
          res--;
        }
      } else if (st_spec.specifier == 's') {
        while ((is_space(*p)) && *p != '-') {
          DEBUG_PRINT("Noop symbol:|%c|\n", *p);
          p++;
        }
        int step = 0;
        step = proc_spec_s(p, args, st_spec);
        if (step > 0) {
          p = p + step;
          if (st_spec.width != asterisk) {
            res++;
          }
        } else if (step < 0) {
          res--;
        }
        DEBUG_PRINT(" after process string Result=%d\n", res);
      } else if (st_spec.specifier == '%') {
        DEBUG_PRINT(" Char=%c\n", *p);
        p++;
        fmt++;
      }
    } else if (st_spec.specifier == 'i') {
      int znak = 1;
      int i = 0;
      int result = 0;
      if (*p == '-') {
        znak = -1;
        p++;
      }
      if (*p == '0') {
        p++;
        if (*p == 'x' || *p == 'X') {
          p++;
        } else {
          DEBUG_PRINT(" octal number\n");
          while ((*p >= '0' && *p <= '8')) {
            result = result * 8 + *p - '0';
            p++;
            i++;
          }
        }
      }
      while (is_digit(*p)) {
        result = result * 10 + *p - '0';
        p++;
        i++;
      }
      if (i > 0) {
        int *ch = va_arg(args, int *);
        result = result * znak;
        *ch = result;
        p++;
        res++;
        DEBUG_PRINT(" Digit=%d\n", result);
      }
    }

    fmt++;
  }
  DEBUG_PRINT(" FINISH result=%d\n", res);
  return res;
}

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

float s21_pow(int x, int y) {
  float result = 1.0;
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

int proc_spec_c(const char *str, va_list args, const Specifiers st_spec) {
  size_t max_len = s21_strlen(str);
  const char *p = str;
  DEBUG_PRINT(" String for decode=|%s|\n", str);
  if (st_spec.width == asterisk) {
    if (st_spec.length == 'l') {
      wchar_t dummy;
      for (int i = 0; i < st_spec.width && *p; i++) {
        if (read_wchar(&p, &dummy) != 0)
          break;
      }
    } else {
      p += st_spec.width > 0 ? st_spec.width : 1;
    }
  } else {
    int width = st_spec.width > 0 ? st_spec.width : 1;
    if ((st_spec.length == 'l')) {
      width = (width > (int)max_len) ? (int)max_len : width;
      wchar_t *wch = va_arg(args, wchar_t *);
      for (int i = 0; i < width; i++) {
        DEBUG_PRINT(" wide Char=%x\n", L'Ω');
        if (read_wchar(&p, &wch[i]) != 0) {
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
  if (st_spec.width >= 0) {
    s21_memcpy(arg_str, str, st_spec.width);
    arg_str[st_spec.width] = '\0';
  } else {
    s21_memcpy(arg_str, str, st_spec.width);
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
  if (p - arg_str > 0 && st_spec.width != asterisk) {
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
  // const char *p = str; // Указатель на входную строку
  char arg_str[s21_strlen(str)];
  if (st_spec.width >= 0) {
    s21_memcpy(arg_str, str, st_spec.width);
    arg_str[st_spec.width] = '\0';
    // } else {
    //   s21_memcpy(arg_str, str, st_spec.width);
  }

  const char *p = arg_str;
  int res = 0;
  int i = 0;
  DEBUG_PRINT("Size=%ld\n", s21_strlen(p));
  while (is_space(*p))
    p++;
  int width = st_spec.width;
  if (width < -1) {
    width = s21_strlen(p);
  }
  if (width == asterisk) {
    for (; !(is_space(*p)) && i <= width; i++, p++)
      ;
    res = 0;
  } else {
    if ((st_spec.length == 'l')) {
      wchar_t *ch = va_arg(args, wchar_t *);
      while (*p && !is_space(*p) && i <= (width)) {
        s21_size_t res = mbrtowc(ch, p, MB_CUR_MAX, S21_NULL);
        p += res;
        ch++;
        i++;
      }
      *ch = L'\0';
      res++;
      wprintf(L"wide String=%ls\n", ch);
    } else {
      char *ch = va_arg(args, char *);
      while (*p && !is_space(*p) && i <= (width)) {
        *ch = *p;
        p++;
        ch++;
        i++;
      }
      *ch = '\0';
      res++;
      DEBUG_PRINT(" String=%s\n", p);
    }
    if (i == 0) {
      res = -1;
    } else
      res = p - arg_str;
  }
  DEBUG_PRINT(" value Step=%ld\n", p - arg_str);
  return res;
}
int proc_spec_d(const char *str, va_list args, const Specifiers st_spec) {
  int res = 0;
  s21_size_t i = 0;
  int width = st_spec.width;
  long int result = 0;
  char arg_str[s21_strlen(str) + 1];
  if (st_spec.width > 0) {
    s21_memcpy(arg_str, str, st_spec.width);
    arg_str[st_spec.width] = '\0';
  } else {
    s21_memcpy(arg_str, str, s21_strlen(str));
  }
  arg_str[s21_strlen(str)] = '\0';
  const char *p = arg_str; // Указатель на входную строку
  // while (i <= s21_strlen(p) && (is_space(*p)) && *p != '-') {
  //   printf("Noop symbol:|%c|\n", *p);
  //   p++;
  // }
  // DEBUG_PRINT(" String str=|%s|\n", str);
  // DEBUG_PRINT(" String arg_str=|%s|\n", arg_str);
  // DEBUG_PRINT(" String copy with Width=%s\n", p);
  DEBUG_PRINT(" Input string for convert to int=|%s|\n", p);
  int step = 0;
  step = get_number(p, &result);
  p += step;
  DEBUG_PRINT(" Width=%d result=%ld step=%d.\n", width, result, step);
  i++;
  if (step > 0) {
    if (st_spec.width != asterisk) {
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
  } else if (*p == '\0' && st_spec.width != asterisk) {
    // p++;
    res = -1;
  }

  return res;
}
