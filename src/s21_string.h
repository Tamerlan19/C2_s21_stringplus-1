
#ifndef STR_LIB_H
#define STR_LIB_H
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

#define S21_NULL ((void *)0) // macros for NULL

#ifdef DEBUG
#include <stdio.h>
#define DEBUG_PRINT(fmt, ...)                                                  \
  do {                                                                         \
    printf("DEBUG (%s:%d %s): " fmt, __FILE__, __LINE__, __func__,             \
           ##__VA_ARGS__);                                                     \
  } while (0)
#else
#define DEBUG_PRINT(fmt, ...) ;
#endif

// Data type size_t
#ifdef _WIN64
typedef unsigned long s21_size_t; // 64-bit Windows
#elif __x86_64__ || __ppc64__ || __aarch64__
typedef unsigned long s21_size_t; // 64-bit Linux/macOS
#else
typedef unsigned int s21_size_t; // 32-bit
#endif

#define asterisk -1 // for width='*'

typedef struct {
  char flag;
  int width;
  int precision;
  char length;
  char specifier;
} Specifiers;

char *s21_strchr(const char *str, int ch);
s21_size_t s21_strlen(const char *str);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *destination, const char *append);

void *s21_memcpy(void *dest, const void *src, s21_size_t n);
int s21_sprintf(char *str, const char *format, ...);

// int s21_sprintf(const char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

#endif
