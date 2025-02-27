#ifndef S21_LIB_UTIL
#define S21_LIB_UTIL
#include "s21_string.h"
#include <locale.h>

#ifdef DEBUG
#include <stdio.h>
#define DEBUG_PRINT(fmt, ...)                                                  \
  {                                                                            \
    printf("DEBUG (%s:%d %s): " fmt, __FILE__, __LINE__, __func__,             \
           ##__VA_ARGS__);                                                     \
  }
#else
#define DEBUG_PRINT(fmt, ...)                                                  \
  {}
#endif

#ifdef _WIN64
typedef unsigned long s21_size_t; // 64-bit Windows
#elif __x86_64__ || __ppc64__ || __aarch64__
typedef unsigned long s21_size_t; // 64-bit Linux/macOS
#else
typedef unsigned int s21_size_t; // 32-bit
#endif

typedef struct {
  char flag;
  int width;
  int precision;
  char length;
  char specifier;
} Specifiers;

int contains_char(const char *str, char ch);
int parse_specifiers(const char *format, Specifiers *st_spec);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
int is_digit(char c);
int is_alpha(char c);
int is_space(char c);
void noop_space(const char **str);
int contains_char(const char *str, char ch);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *destination, const char *append);

int is_hex(char c);
int is_octa(char c);
int is_digit(char c);
int is_alpha(char c);
int is_space(char c);
long double s21_pow(int x, int y);
int is_alpha(char c);
int is_digit(char c);
int is_space(char c);
void int_to_str(int num, char *str, int base);

#endif