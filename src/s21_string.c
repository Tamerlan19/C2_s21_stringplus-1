#include "s21_string.h"
#include <locale.h>
#include <stdarg.h>



// Specifiers parse_specifiers(const char *format);
// char *s21_strcpy(char *dest, const char *src);
// char *s21_strcat(char *destination, const char *append);
int contains_char(const char *str, char ch);


void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr[i] == (unsigned char)c) {
      return (void *)(ptr + i);
    }
  }
  return NULL;
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
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
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




s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; *(str + len); len++)
    ;
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  for (size_t i = 0; str1[i] != '\0'; i++) {  
      for (size_t j = 0; str2[j] != '\0'; j++) {  
          if (str1[i] == str2[j]) {  
              return (char *)&str1[i];  
          }
      }
  }
  return NULL;  
}

// [ ] Необходимо проверить корректность работы функции
char *s21_strrchr(const char *str, int c){
  char *rtn = NULL;
  if (str != NULL) {
    str+=s21_strlen(str);
    for (; *str && *str != c; str-- ) {
    // if (str[i] == c)//доделать надо
    //   rtn = str;
    //   break;
    }
  }
  return rtn;
}







void *s21_to_upper(const char *str) {

  if (str == NULL) {
    return NULL;
  }

  size_t length = s21_strlen(str);
  char *result = (char *)malloc(length + 1);
  if (result == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < length; i++) {
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
  if (str == NULL) {
    return NULL;
  }

  size_t length = s21_strlen(str);
  char *result = (char *)malloc(length + 1);
  if (result == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < length; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }

  result[length] = '\0';
  return (void *)result;
};

void *s21_insert(const char *src, const char *str, size_t start_index) {
  /*Возвращает новую строку, в которой указанная строка (str) вставлена 
  в указанную позицию (start_index) в данной строке (src). 
  В случае какой-либо ошибки следует вернуть значение NULL.
  */
 char *result = S21_NULL;
  if (src == NULL || str == NULL) {//проверяю, что переданныеы массивы не равны нулю
    return NULL;
  }

  size_t src_length = s21_strlen(src);
  size_t str_length = s21_strlen(str);

  if (start_index > 0 && start_index < src_length) {//проверяю, что длина вставки не больше длины самого массива и индекс не отрицательный
    size_t result_lenght = src_length + str_length;
    char *result = (char *)malloc(result_lenght + 1);//выделяем, память под новый массив
    if (result == NULL) {
      return NULL;
    }

  s21_memcpy(result, src, start_index);//копирую src в result на start_index байтов 
  s21_memcpy(result + start_index, str, str_length);//копирует массив str в result начиная с start_index и вплоть до str_lenght
  s21_memcpy(result + start_index + str_length, src + start_index, src_length - start_index);//копирует оставшуюся часть массива

  result[result_lenght] = '\0';


  } else {

    return NULL;
  }
  
  return (void *)result;
}

void *s21_trim(const char *src, const char *trim_chars){
  if (src == NULL || trim_chars == NULL)//проверяю на корректность переданной строки
  {
    return NULL;
  }
  size_t src_length = s21_strlen(src);
  size_t trim_length = s21_strlen(trim_chars);//длины строк

  
  if (trim_length == 0) {
    trim_chars = " \t\n\r";
    trim_length = s21_strlen(trim_chars);
  }

  
  size_t start = 0;//определяю начало
  while (start < src_length && s21_strchr(trim_chars, src[start]) != NULL) {
    start++;
  }

  
  size_t end = src_length;//определяю конец, пропускаю символы из trim
  while (end > start && s21_strchr(trim_chars, src[end - 1]) != NULL) {
    end--;
  }

  
  size_t result_length = end - start;//память под строку
  char *result = (char *)malloc(result_length + 1);
  if (result == NULL) {
    return NULL;
  }


  s21_memcpy(result, src + start, result_length);
  result[result_length] = '\0';

  return (void *)result;

  
};
