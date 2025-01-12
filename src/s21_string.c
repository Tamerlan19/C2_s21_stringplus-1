// #include <stdio.h>
#include "s21_string.h"
#include <stdarg.h>

#include <stdio.h>
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
 - [ ] void *s21_memchr(const void *str, int c, size_t n)	Searches for the
first occurrence of the character c (an unsigned char) in the first n bytes of
the string pointed to, by the argument str.
 - [ ] int s21_memcmp(const void *str1, const void *str2, size_t n)	Compares
the first n bytes of str1 and str2.
 - [ ] void *s21_memcpy(void *dest, const void *src, size_t n)	Copies n
characters from src to dest.
 - [ ] void *s21_memset(void *str, int c, size_t n)	Copies the character c
(an unsigned char) to the first n characters of the string pointed to, by the
argument str.
 - [ ] char *s21_strncat(char *dest, const char *src, size_t n)	Appends the
string pointed to, by src to the end of the string pointed to, by dest up to n
characters long.
 - [ ] char *s21_strchr(const char *str, int c)	Searches for the first
occurrence of the character c (an unsigned char) in the string pointed to, by
the argument str.
 - [x] int s21_strncmp(const char *str1, const char *str2, size_t n)	Compares
at most the first n bytes of str1 and str2.
 - [ ] char *s21_strncpy(char *dest, const char *src, size_t n)	Copies up to n
characters from the string pointed to, by src to dest.
 - [ ] size_t s21_strcspn(const char *str1, const char *str2)	Calculates the
length of the initial segment of str1 which consists entirely of characters not
in str2.
 - [ ] 	char *s21_strerror(int errnum)	Searches an internal array for the error
number errnum and returns a pointer to an error message string. You need to
declare macros containing arrays of error messages for mac and linux operating
systems. Error descriptions are available in the original library. Checking the
current OS is carried out using directives.
 - [x] 	size_t s21_strlen(const char *str)	Computes the length of the
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
- [ ] sprintf()
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

/**
TODO: Part 4. Дополнительно. Реализация функции sscanf
Необязательное задание на дополнительные баллы: реализуй функцию sscanf из
библиотеки stdio.h:

Функция должна быть размещена в библиотеке s21_string.h;
На реализацию функции накладываются все требования, изложенные в первой части.
Должно поддерживаться полное форматирование (с учетом флагов, ширины, точности,
модификаторов и типов преобразования).
*/

size_t s21_strlen(const char *str){
  size_t len = 0;
  for (; *(str + len); len++)
    ;
  return len;
}

int s21_strncmp(const char *str1, const char *str2, size_t n)
{
    int rtn = 0;
    int is_diff = 0;
    for (size_t i=0; i < n && !is_diff; i++){
      if (str1[i] != str2[i] || str1[i]=='\0'|| str2[i]=='\0') {
        is_diff++;
        rtn = (unsigned char)str1[i] - (unsigned char)str2[i];
    }
    }
  return rtn;
}

// int s21_strncmp(const char *str1, const char *str2, size_t n){
//     int rtn = 0;
//   for (int i=0; *str1 && *str1 == *str2 && i<n; str1++, str2++, i++)
//     ;
//   return (*str1 - *str2);
// }

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
  if (src != NULL) {
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

char *s21_strchr(char *str, int ch) {
  char *rtn = NULL;
  if (str != NULL) {
    for (; *str && *str != ch; str++) {
    }
    if (*str != '\0')
      rtn = str;
  }
  return rtn;
}

int s21_sprintf(char *str, const char *format, ...) {
  char *start = str;
  va_list ap;
  va_start(ap, format);
  int i = 0;
  while (*format) {
    if (*format != '%') {
  //     i += s21_putchar(start, *format);
      start++;
      format++;
    } else {
  //     flags_t flags = parseFlags((char *)format, &ap);
  //     if (flags.flagSize) format += flags.flagSize;
      format++;
  //     int b = checkFormat(start, *format, &ap, flags);
      // i += b;
      // start += b;
      format++;
    }
  }
  va_end(ap);
  str[i] = '\0';
  return i;
}
