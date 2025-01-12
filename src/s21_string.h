#ifndef STR_LIB_H
#define STR_LIB_H
#define NULL ((void *)0) //macros for NULL

//Data type size_t
#ifdef _WIN64
    typedef unsigned long size_t;  // 64-bit Windows
#elif __x86_64__ || __ppc64__ || __aarch64__
    typedef unsigned long size_t;  // 64-bitLinux/macOS
#else
    typedef unsigned int size_t;        // 32-bit
#endif

size_t s21_strlen(const char *str);
int s21_strncmp(const char *str1, const char *str2, size_t n);
int s21_strcmp(const char* str1, const char* str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *destination, const char *append);
char *s21_strchr(char *str, int ch);
int s21_sprintf(char *str, const char *format, ...);
#endif