
#ifndef STR_LIB_H
#define STR_LIB_H
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>
#include "s21_utils.h"

#define S21_NULL ((void *)0) // macros NULL

#ifdef _WIN64                     // macros s21_size_t
typedef unsigned long s21_size_t; // 64-bit Windows
#elif __x86_64__ || __ppc64__ || __aarch64__
typedef unsigned long s21_size_t; // 64-bit Linux/macOS
#else
typedef unsigned int s21_size_t; // 32-bit
#endif


void *s21_memchr(const void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int ch);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);

s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

char *s21_strerror(int errnum);



#endif
