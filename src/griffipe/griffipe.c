#ifndef S21_SPRINTF
#define S21_SPRINTF

typedef struct {
int plus;
int minus;
int space;
int width;
int precision;
char length_modifier;
} batman;

void monster_flags(const char *format, batman *flags);
#endif 
а это си файл : 

#include"s21_sprintf.h"

void monster_flags(const char *format, batman *flags){
flags->plus = 0;
flags->minus = 0;
flags->space = 0;
flags->width = 0;
flags->precision = -1 ;
flags->length_modifier = 0;

const char *ptr = format;

while(*ptr == '+' || *ptr == '-' || *ptr == ' ') {
if(*ptr == '+'){
flags->plus = 1;
}
if(*ptr == '-') {
flags->minus = 1;
}
if(*ptr == ' ') {
flags->space = 1;
}

ptr++;
}

if (ptr >= '0' && ptr <= '9') {
flags->width = 0;
while(ptr >= '0' && ptr <= '9') {
flags->width = flags->width 10 + (ptr - '0');
ptr++;
}
}

if(*ptr == '.'){
ptr++;
flags->precision = 0;
while(ptr >= '0' && ptr <= 9) {
flags->precision = flags->precision * 10 + *(ptr - '0');
ptr++;
}

}

if(*ptr == 'h') {
flags->length_modifier= 'h';
ptr++;
} else if(*ptr == 'l') {
flags->length_modifier = 'l';
ptr++;
}
}