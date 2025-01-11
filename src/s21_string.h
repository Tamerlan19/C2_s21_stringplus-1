#ifndef STR_LIB_H
#define STR_LIB_H
#define NULL ((void *)0) //macros for NULL

int s21_strlen(const char *str);
int s21_strcmp(const char* str1, const char* str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *destination, const char *append);
char *s21_strchr(char *str, int ch);
int s21_sprintf(char *str, const char *format, ...);
#endif