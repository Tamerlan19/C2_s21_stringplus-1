#include "s21_string.h"
#include <locale.h>
#include <stdarg.h>

// Specifiers parse_specifiers(const char *format);
// char *s21_strcpy(char *dest, const char *src);
// char *s21_strcat(char *destination, const char *append);

typedef struct {
  int errnum;
  const char *message;
} S21_Error;

#ifdef __APPLE__ // macOS
static const S21_Error S21_ERROR_MESSAGES[] = {
    {0, "Undefined error: 0"},
    {1, "Operation not permitted"},
    {2, "No such file or directory"},
    {3, "No such process"},
    {4, "Interrupted system call"},
    {5, "Input/output error"},
    {6, "Device not configured"},
    {7, "Argument list too long"},
    {8, "Exec format error"},
    {9, "Bad file descriptor"},
    {10, "No child processes"},
    {11, "Resource deadlock avoided"},
    {12, "Cannot allocate memory"},
    {13, "Permission denied"},
    {14, "Bad address"},
    {15, "Block device required"},
    {16, "Resource busy"},
    {17, "File exists"},
    {18, "Cross-device link"},
    {19, "Operation not supported by device"},
    {20, "Not a directory"},
    {21, "Is a directory"},
    {22, "Invalid argument"},
    {23, "Too many open files in system"},
    {24, "Too many open files"},
    {25, "Inappropriate ioctl for device"},
    {26, "Text file busy"},
    {27, "File too large"},
    {28, "No space left on device"},
    {29, "Illegal seek"},
    {30, "Read-only file system"},
    {31, "Too many links"},
    {32, "Broken pipe"},
    {33, "Numerical argument out of domain"},
    {34, "Result too large"},
    {35, "Resource temporarily unavailable"},
    {36, "Operation now in progress"},
    {37, "Operation already in progress"},
    {38, "Socket operation on non-socket"}};

#elif defined(__linux__) // Linux
S21_Error error_list[] = {
    {0, "Success"},
    {1, "Operation not permitted"},
    {2, "No such file or directory"},
    {3, "No such process"},
    {4, "Interrupted system call"},
    {5, "Input/output error"},
    {6, "No such device or address"},
    {7, "Argument list too long"},
    {8, "Exec format error"},
    {9, "Bad file descriptor"},
    {10, "No child processes"},
    {11, "Resource temporarily unavailable"},
    {12, "Cannot allocate memory"},
    {13, "Permission denied"},
    {14, "Bad address"},
    {15, "Block device required"},
    {16, "Device or resource busy"},
    {17, "File exists"},
    {18, "Invalid cross-device link"},
    {19, "No such device"},
    {20, "Not a directory"},
    {21, "Is a directory"},
    {22, "Invalid argument"},
    {23, "Too many open files in system"},
    {24, "Too many open files"},
    {25, "Inappropriate ioctl for device"},
    {26, "Text file busy"},
    {27, "File too large"},
    {28, "No space left on device"},
    {29, "Illegal seek"},
    {30, "Read-only file system"},
    {31, "Too many links"},
    {32, "Broken pipe"},
    {33, "Numerical argument out of domain"},
    {34, "Numerical result out of range"},
    {35, "Resource deadlock avoided"},
    {36, "File name too long"},
    {37, "No locks available"},
    {38, "Function not implemented"},
    {39, "Directory not empty"},
    {40, "Too many levels of symbolic links"},
    {41, "Unknown error 41"},
    {42, "No message of desired type"},
    {43, "Identifier removed"},
    {44, "Channel number out of range"},
    {45, "Level 2 not synchronized"},
    {46, "Level 3 halted"},
    {47, "Level 3 reset"},
    {48, "Link number out of range"},
    {49, "Protocol driver not attached"},
    {50, "No CSI structure available"},
    {51, "Level 2 halted"},
    {52, "Invalid exchange"},
    {53, "Invalid request descriptor"},
    {54, "Exchange full"},
    {55, "No anode"},
    {56, "Invalid request code"},
    {57, "Invalid slot"},
    {58, "Unknown error 58"},
    {59, "Bad font file format"},
    {60, "Device not a stream"},
    {61, "No data available"},
    {62, "Timer expired"},
    {63, "Out of streams resources"},
    {64, "Machine is not on the network"},
    {65, "Package not installed"},
    {66, "Object is remote"},
    {67, "Link has been severed"},
    {68, "Advertise error"},
    {69, "Srmount error"},
    {70, "Communication error on send"},
    {71, "Protocol error"},
    {72, "Multihop attempted"},
    {73, "RFS specific error"},
    {74, "Bad message"},
    {75, "Value too large for defined data type"},
    {76, "Name not unique on network"},
    {77, "File descriptor in bad state"},
    {78, "Remote address changed"},
    {79, "Can not access a needed shared library"},
    {80, "Accessing a corrupted shared library"},
    {81, ".lib section in a.out corrupted"},
    {82, "Attempting to link in too many shared libraries"},
    {83, "Cannot exec a shared library directly"},
    {84, "Invalid or incomplete multibyte or wide character"},
    {85, "Interrupted system call should be restarted"},
    {86, "Streams pipe error"},
    {87, "Too many users"},
    {88, "Socket operation on non-socket"},
    {89, "Destination address required"},
    {90, "Message too long"},
    {91, "Protocol wrong type for socket"},
    {92, "Protocol not available"},
    {93, "Protocol not supported"},
    {94, "Socket type not supported"},
    {95, "Operation not supported"},
    {96, "Protocol family not supported"},
    {97, "Address family not supported by protocol"},
    {98, "Address already in use"},
    {99, "Cannot assign requested address"},
    {100, "Network is down"},
    {101, "Network is unreachable"},
    {102, "Network dropped connection on reset"},
    {103, "Software caused connection abort"},
    {104, "Connection reset by peer"},
    {105, "No buffer space available"},
    {106, "Transport endpoint is already connected"},
    {107, "Transport endpoint is not connected"},
    {108, "Cannot send after transport endpoint shutdown"},
    {109, "Too many references: cannot splice"},
    {110, "Connection timed out"},
    {111, "Connection refused"},
    {112, "Host is down"},
    {113, "No route to host"},
    {114, "Operation already in progress"},
    {115, "Operation now in progress"},
    {116, "Stale file handle"},
    {117, "Structure needs cleaning"},
    {118, "Not a XENIX named type file"},
    {119, "No XENIX semaphores available"},
    {120, "Is a named type file"},
    {121, "Remote I/O error"},
    {122, "Disk quota exceeded"},
    {123, "No medium found"},
    {124, "Wrong medium type"},
    {125, "Operation canceled"},
    {126, "Required key not available"},
    {127, "Key has expired"},
    {128, "Key has been revoked"},
    {129, "Key was rejected by service"},
    {130, "Owner died"},
    {131, "State not recoverable"},
    {132, "Operation not possible due to RF-kill"},
    {133, "Memory page has hardware error"}};

#define ERROR_LIST_SIZE (sizeof(error_list) / sizeof(error_list[0]))
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr[i] == (unsigned char)c) {
      return (void *)(ptr + i);
    }
  }
  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
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

void *s21_memset(void *str, int c, s21_size_t n) {
  if (str) { // Проверяем, что указатель не NULL
    unsigned char *ptr =
        (unsigned char *)str; // Преобразуем указатель к типу unsigned char*
    unsigned char value =
        (unsigned char)c; // Преобразуем значение c к unsigned char

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

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int rtn = 0;
  int is_diff = 0;
  for (s21_size_t i = 0; i < n && !is_diff; i++) {
    // if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
    // //2025-02-25 18:49 Condition 'str2[i]=='\0'' is always false
    if (str1[i] != str2[i] || str1[i] == '\0') {
      is_diff++;
      rtn = (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return rtn;
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

char *s21_strerror(int errnum) {
  char *res = malloc(sizeof(char) * 50);
  s21_memset(res, '\0', 50);
  if (res != NULL) {
    for (int i = 0; i < (int)ERROR_LIST_SIZE; i++) {
      if (error_list[i].errnum == errnum) {
        s21_strncpy(res, error_list[i].message,
                    s21_strlen(error_list[i].message));
        res[s21_strlen(error_list[i].message)] = '\0';
      }
    }
    if (s21_strlen(res) == 0) {
      s21_strncpy(res, "Unknown error ", 14);
      char num[5] = {0};
      int_to_str(errnum, num, 10);
      s21_strncat(res, num, s21_strlen(num));
    }
  }
  return res;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; *(str + len); len++)
    ;
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  for (s21_size_t i = 0; str1[i] != '\0'; i++) {
    for (s21_size_t j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return (char *)&str1[i];
      }
    }
  }
  return S21_NULL;
}

// [ ] Необходимо проверить корректность работы функции
/**
 * @brief Find the last occurrence of a character in a string.
 *
 * This function searches for the last occurrence of the character `c` in the
 * string `str`. If the character is found, it returns a pointer to the last
 * occurrence of the character. If the character is not found or if the string
 * is empty, it returns `S21_NULL`.
 *
 * @param str The string to search in.
 * @param c The character to find.
 * @return A pointer to the last occurrence of the character, or `S21_NULL` if
 * not found.
 */
char *s21_strrchr(const char *str, int c) {
  const char *rtn = S21_NULL;
  if (str != S21_NULL) {
    const char *p = str + s21_strlen(str);
    for (; p >= str; p--) {
      if (*p == (char)c) {
        rtn = p;
        break;
      }
    }
  }
  return (char *)rtn;
}

void *s21_to_upper(const char *str) {

  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t length = s21_strlen(str);
  char *result = (char *)malloc(length + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      result[i] = str[i] - 32;
    } else {
      result[i] = str[i];
    }
  }

  result[length] = '\0';
  return (void *)result;
};

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  size_t length = s21_strlen(str);
  char *result = (char *)malloc(length + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }

  result[length] = '\0';
  return (void *)result;
};

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  /* Возвращает новую строку, в которой указанная строка (str) вставлена
  в указанную позицию (start_index) в данной строке (src).
  В случае какой-либо ошибки следует вернуть значение S21_NULL.
  */

  // Проверяем, что переданные массивы не равны NULL
  if (src == S21_NULL || str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t src_length = s21_strlen(src);
  s21_size_t str_length = s21_strlen(str);

  // Корректируем условие проверки индекса:
  // Разрешаем вставку в начало (start_index == 0) и в конец (start_index == src_length)
  if (start_index <= src_length) {
    s21_size_t result_length = src_length + str_length;
    char *result = (char *)malloc(result_length + 1); // Выделяем память под новый массив
    if (result == S21_NULL) {
      return S21_NULL; // Если память не выделена, возвращаем NULL
    }

    // Копируем часть строки до start_index
    s21_memcpy(result, src, start_index);

    // Копируем строку str после start_index
    s21_memcpy(result + start_index, str, str_length);

    // Копируем оставшуюся часть исходной строки
    s21_memcpy(result + start_index + str_length, src + start_index,
               src_length - start_index);

    result[result_length] = '\0'; // Добавляем завершающий ноль

    return (void *)result;
  } else {
    return S21_NULL; // Некорректный индекс
  }
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL ||
      trim_chars == S21_NULL) // проверяю на корректность переданной строки
  {
    return S21_NULL;
  }
  s21_size_t src_length = s21_strlen(src);
  s21_size_t trim_length = s21_strlen(trim_chars); // длины строк

  if (trim_length == 0) {
    trim_chars = " \t\n\r";
    // trim_length = s21_strlen(trim_chars);
  }

  s21_size_t start = 0; // определяю начало
  while (start < src_length && s21_strchr(trim_chars, src[start]) != S21_NULL) {
    start++;
  }

  s21_size_t end = src_length; // определяю конец, пропускаю символы из trim
  while (end > start && s21_strchr(trim_chars, src[end - 1]) != S21_NULL) {
    end--;
  }

  s21_size_t result_length = end - start; // память под строку
  char *result = (char *)malloc(result_length + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }

  s21_memcpy(result, src + start, result_length);
  result[result_length] = '\0';

  return (void *)result;
};
