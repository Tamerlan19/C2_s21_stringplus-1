#include"s21_sprintf.h"
#include <stdarg.h>

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *buffer = str;
    const char *ptr = format;
    while (*ptr) {
        if (*ptr == '%') {
            ptr++;
            batman flags;
            monster_flags(ptr, &flags);
            char spec = *ptr;
            ptr++;
            switch(spec) {
                case 'c': {
                    int c = va_arg(args, int);
                    handle_char(&buffer, flags, c);
                    break;
                }
                case 'd': {
                    int d = va_arg(args, int);
                    handle_int(&buffer, flags, d);
                    break;
                }
                case 'f': {
                    double f = va_arg(args, double);
                    handle_float(&buffer, flags, f);
                    break;
                }
                case 's': {
                    const char *s = va_arg(args, const char *);
                    handle_string(&buffer, flags, s);
                    break;
                }
                case 'u': {
                    unsigned int u = va_arg(args, unsigned int);
                    handle_unsigned(&buffer, flags, u);
                    break;
                }
                case '%': {
                    handle_percent(&buffer, flags);
                    break;
                }
                default:
                    *buffer++ = spec;
                    break;
            }
        } else {
            *buffer++ = *ptr++;
        }
    }
    *buffer = '\0';
    va_end(args);
    return (int)strlen(str);
}

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
    
    if (*ptr >= '0' && *ptr <= '9') {
        while(*ptr >= '0' && *ptr <= '9') {
            flags->width = flags->width * 10 + (*ptr - '0');
            ptr++;
        } 
    }  
    
     if(*ptr == '.'){ 
        ptr++;
        flags->precision = 0;
        while(*ptr >= '0' && *ptr <= 9) {
            flags->precision = flags->precision * 10 + (*ptr - '0');
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

void handle_char(char **buffer, batman flags, int c) {
    *(*buffer)++ = (char)c;
    **buffer = '\0';
}

void handle_int(char **buffer, batman flags, int d) {
    char tmp[100] = {0};
    if (flags.precision >= 0) {
        char fmt[20] = {0};
        sprintf(fmt, "%%0%dd", flags.precision);
        sprintf(tmp, fmt, d);
    } else {
        sprintf(tmp, "%d", d);
    }
    strcpy(*buffer, tmp);
    *buffer += strlen(tmp);
}

void handle_float(char **buffer, batman flags, double f) {
    char tmp[200] = {0};
    if (flags.precision >= 0) {
        char fmt[20] = {0};
        sprintf(fmt, "%%.%df", flags.precision);
        sprintf(tmp, fmt, f);
    } else {
        sprintf(tmp, "%f", f);
    }
    strcpy(*buffer, tmp);
    *buffer += strlen(tmp);
}

void handle_string(char **buffer, batman flags, const char *s) {
    if (s == 0) {
        s = "(null)";
    }
    strcpy(*buffer, s);
    *buffer += strlen(s);
}

void handle_unsigned(char **buffer, batman flags, unsigned int u) {
    char tmp[100] = {0};
    sprintf(tmp, "%u", u);
    strcpy(*buffer, tmp);
    *buffer += strlen(tmp);
}

void handle_percent(char **buffer, batman flags) {
    *(*buffer)++ = '%';
    **buffer = '\0';
}
