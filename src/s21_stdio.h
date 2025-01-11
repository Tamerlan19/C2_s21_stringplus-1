#include "s21_string.h"

//FIXIT: [флаги][ширина][.точность][длина]
struct Specifiers
{
    char flag;
    int width;
    int precision;
    int length;
    char specifier;
};

struct Specifiers parse_specifiers(const char *format);
int is_digit(char c);
int s21_sprintf(const char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);
//