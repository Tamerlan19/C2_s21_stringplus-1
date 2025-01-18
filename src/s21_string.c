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
 - [x] char *s21_strchr(const char *str, int c)	Searches for the first
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

size_t s21_strlen(const char *str) {
  size_t len = 0;
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
int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int rtn = 0;
  int is_diff = 0;
  for (size_t i = 0; i < n && !is_diff; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
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

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * @param str The string to search.
 * @param ch The character to find.
 * @return A pointer to the first occurrence of the character in the string, or
 * NULL if the character is not found.
 */
char *s21_strchr(const char *str, int ch) {
  char *rtn = NULL;
  if (str != NULL) {
    for (; *str != '\0' && *str != ch; str++) {
    }
    if (*str == ch)
      rtn = (char *)str;
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

struct Specifiers parse_specifiers(const char *format) {
  struct Specifiers st_spec = {'*', -10, 0, '*', '*'};
  format++;
  // Flags
  if ((*(format) == '+' || *(format) == '-' || *(format) == ' ' ||
       *(format) == '#' || *(format) == '0')) {
    st_spec.flag = *(format);
    printf("DEBUG: FLAGS=%c\n", st_spec.flag);
    format++;
  }
  if ( *(format) == '*' || is_digit(*(format))) {
    st_spec.width = 0;
    if (*(format) == '*')
      st_spec.width = -1;
    else {
      while (is_digit(*(format))) {
        st_spec.width = st_spec.width * 10 + *(format) - '0';
        format++;
      }
    }
    // format++;
    printf("DEBUG: Width=%i\n", st_spec.width);
  }
  // Precision
  if (*(format) == '.') {
    format++;
    st_spec.precision = 0;
    if (*(format) == '*')
      st_spec.precision = -1;
    else {
      while (is_digit(*(format))) {
        st_spec.precision = st_spec.precision * 10 + *(format) - '0';
        format++;
      }
    }
    printf("DEBUG: Precision=%i\n", st_spec.precision);
  }

  // Length
  if (*(format) == 'h' || *(format) == 'l' || *(format) == 'L') {
    st_spec.length = *(format);
    format++;
    printf("DEBUG: Length=%c\n", st_spec.length);
  }

  // Specifiers
  if (*format == 'c' || *format == 'd' || *format == 'i' || *format == 'f' ||
      *format == 's' || *format == 'u' || *format == '%' || *format == 'g' ||
      *format == 'G' || *format == 'e' || *format == 'E' || *format == 'x' ||
      *format == 'X' || *format == 'o' || *format == 'p') {
    st_spec.specifier = *format;
    format++;
    printf("DEBUG: Specifier=%c\n", st_spec.specifier);
  } else {
    st_spec.specifier = '0';
  }
  format++;
  return st_spec;
}

int is_digit(char c) { return (c >= '0' && c <= '9'); }

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

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  struct Specifiers st_spec;
  const char *p = str; // Указатель на входную строку
  const char *fmt = format; // Указатель на строку формата
  //%[*][ширина][длина]спецификатор.
  int res = 0;

  while (*fmt) {
    if (*fmt == '%') {
      printf("\nDEBUG: Format string:%s\n",fmt);
      st_spec = parse_specifiers(fmt);
      printf("DEBUG: str=%s\n", str);
      printf("DEBUG: !!! Flag=%c, Width=%i, Length=%c, Precision=%i, Specifiers=%c\n",
             st_spec.flag, st_spec.width, st_spec.length, st_spec.precision,
             st_spec.specifier);
      if (st_spec.specifier == 'c') {
        printf("DEBUG: Char=%c\n", *p);
        char *ch = va_arg(args, char *);
        *ch = *p;
        p++;

      } else if (st_spec.specifier == 'd') {
        int znak = 1, i = 0, width=st_spec.width;
        long int  result = 0;
        if(width<0 && width!=asterisk){
            width = s21_strlen(str);
        }
        while (is_space(*p)) {
          p++;
        }
        if (*p == '-') {
          znak = -1;
          p++;
        }
        while (is_digit(*p) && i <width) {
          result = result * 10 + *p - '0';
          printf("DEBUG: Width=%d result=%ld.\n", width,result);
          p++;
          i++;
        }
        if (i > 0 && st_spec.width != asterisk) {
            result = result * znak;
            if(st_spec.length == 'h'){
            short int *ch = va_arg(args, short int *);
            *ch = result;
            } else if (st_spec.length == 'l'){
            long int *ch = va_arg(args, long int *);
            *ch = result;
            }else{
              int *ch = va_arg(args, int *);
              *ch = result;
            }
          p++;
          res++;
        //   printf("DEBUG: Digit=%ld\n", result);
        } else {
          if (*p=='\0' && st_spec.width!=asterisk) {
            res = -1;
          }
          p++;
        }

      } else if (st_spec.specifier == 'f') {
        int znak = 1;
        int i = 0;
        float result = 0;
        if (*p == '-') {
          znak = -1;
          p++;
        }
        while (is_digit(*p)) {
          result = result * 10 + *p - '0';
          p++;
          i++;
        }
        if (*p == '.') {
          p++;
          float ost = 1;
          while (is_digit(*p)) {
            ost = ost * 0.1f;
            result = result + (*p - '0') * ost;
            p++;
            i++;
          }
        }
        if (i > 0) {
          float *ch = va_arg(args, float *);
          result = result * znak;
          *ch = result;
          p++;
          res++;
          printf("DEBUG: Digit=%f\n", result);
        }
      } else if (st_spec.specifier == 's') {
        int i = 0;
        printf("Size=%ld\n", s21_strlen(str));
        while (is_space(*p))
          p++;
        int width = st_spec.width;
        if (width < -1) {
          width = s21_strlen(str);
        }
        if (width == asterisk) {
          for (; *p != ' ' && i <= width; i++, p++)
            ;
        } else {
          if ((st_spec.length == 'L' || st_spec.length == 'l')) {
            wchar_t *ch = va_arg(args, wchar_t *);
            while (*p && !is_space(*p) && i <= (width)) {
              size_t res = mbrtowc(ch, p, MB_CUR_MAX, NULL);
              p += res;
              ch++;
              i++;
            }
            *ch = L'\0';
            res++;
            wprintf(L"DEBUG: wide String=%ls\n", ch);
            printf("DEBUG: 11111111111\n");
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
            printf("DEBUG: String=%s\n", ch);
          }
        }

      } else if (st_spec.specifier == '%') {
        printf("DEBUG: Char=%c\n", *p);
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
          printf("DEBUG: octal number\n");
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
        printf("DEBUG: Digit=%d\n", result);
      }
    }

    fmt++;
  }
  return res;
}
