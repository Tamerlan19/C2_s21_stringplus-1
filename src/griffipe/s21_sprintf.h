#ifndef S21_SPRINTF
#define S21_SPRINTF
#define NULL

typedef struct {
    int plus;         
    int minus;         
    int space;         
    int width;         
    int precision;     
    char length_modifier; 
} batman;

void monster_flags(const char *format, batman *flags);
void handle_char(char **buffer, batman flags, int c);
void handle_int(char **buffer, batman flags, int d);
void handle_float(char **buffer, batman flags, double f);
void handle_string(char **buffer, batman flags, const char *s);
void handle_unsigned(char **buffer, batman flags, unsigned int u);
void handle_percent(char **buffer, batman flags);
int s21_sprintf(char *str, const char *format, ...);
#endif