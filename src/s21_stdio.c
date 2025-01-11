#include <stdio.h>
#include "s21_stdio.h"
#include <stdarg.h>
#include <string.h>
/**
 TODO:    
 - [ ] int sprintf(char *str, const char *format, ...) — отправляет форматированный вывод в строку, на которую указывает str.
 - [ ] int sscanf(const char *str, const char *format, ...) — считывает форматированный ввод из строки.
 * str — это С-строка, которую функция обрабатывает в качестве источника для извлечения данных;
 * format — это С-строка, содержащая один или несколько следующих элементов: пробельный символ, непробельный символ и спецификаторы формата. 
 * Спецификатор формата для печатающих функций следует прототипу: %[флаги][ширина][.точность][длина]спецификатор. 
 * Спецификатор формата для сканирующих функций следует прототипу: %[*][ширина][длина]спецификатор.
 * №
Спецификатор
Part 2.
 - [x] c   Символ
 - [x] d   Знаковое десятичное целое число
 - [x] f    Десятичное число с плавающей точкой или научная нотация (мантисса/экспонента)
 - [x] s    Строка символов
 - [x] u    Беззнаковое десятичное целое число
 - [ ] %    Символ %
Part 3.
 - [ ] g    Десятичное число с плавающей точкой или научная нотация (мантисса/экспонента)
 - [ ] G    Десятичное число с плавающей точкой или научная нотация (мантисса/экспонента)
 - [ ] e    Десятичное число с плавающей точкой или научная нотация (мантисса/экспонента)
 - [ ] E    Десятичное число с плавающей точкой или научная нотация (мантисса/экспонента)
 - [ ] x    Беззнаковое шестнадцатеричное целое число (любые буквы)
 - [ ] X    Беззнаковое шестнадцатеричное целое число (любые буквы)
 - [ ] o    Беззнаковое восьмеричное число
 - [ ] p    Адрес указателя
Спецификаторы не указанные в задании, но есть в описании задания.
 - [ ] n    Количество символов, считаных до появления %n
 - [ ] i   Знаковое целое число (может быть десятичным, восьмеричным или шестнадцатеричным)
 */

int main(){

    // int r = 45;
    // char ch='Z';
    // char a=' ';
    // char f=' ';
    const char *str = "-420G 3.14 Hello";
    // struct Specifiers st;
    // sprintf(str,"New string, test=%1n",r);
    // sprintf(buf,"New string, test2=%n",r);

    // parse_specifiers("%#*f", st);
    // printf("RESULT=%i\n",r);
    // s21_sscanf(str, "%c%%%c", &ch,&f,&a);
    // printf("RESULT=%c\n",ch);
    // printf("RESULT=%c\n",f);
    // printf("RESULT=%c\n",a);

    int i=777;
    s21_sscanf(str, "%d", &i);
    printf("RESULT s21_sscanf=%i\n",i);
    i=777;
    sscanf(str, "%d", &i);
    printf("RESULT sscanf=%i\n",i);

    i=777;
    s21_sscanf("0547", "%i", &i);
    printf("RESULT s21_sscanf=%i\n",i);
    i=777;
    sscanf("0547", "%i", &i);
    printf("RESULT sscanf=%i\n",i);


    float f=7.77;
    s21_sscanf("5.47", "%f", &f);
    printf("RESULT s21_sscanf=%f\n",f);
    f=7.77;
    sscanf("5.47", "%f", &f);
    printf("RESULT sscanf=%f\n",f);

//%[*][ширина][длина]спецификатор
    char buf[200];
    memset(buf, 0, sizeof(str));
    s21_sscanf("Test47! string 1", "%5Ls", buf);
    printf("RESULT s21_sscanf=%s\n",buf);
    memset(buf, 0, sizeof(buf));
    sscanf("Test47! string 1", "%s", buf);
    printf("RESULT sscanf=%s\n",buf);

    return 0;

}

struct Specifiers parse_specifiers(const char *format){
    struct Specifiers st_spec={0};
        format++;
        //Flags
        if(*(format) == '+' || *(format) == '-' ||  *(format) == ' ' ||  *(format) == '#' ||  *(format) == '0'){
            st_spec.flag = *(format);
            printf("DEBUG: FLAGS=%c\n",st_spec.flag);
            format++;
        }
        //Width
        if(is_digit(*(format)) || *(format) == '*'){   
            st_spec.width=0;
            if (*(format) == '*')
                st_spec.width=-1;
            else{
                while(is_digit(*(format))){
                    st_spec.width = st_spec.width*10 + *(format)-'0';
                    format++;
            }
            }
                printf("DEBUG: Width=%i\n",st_spec.width);
        }
        //Precision
        if(*(format) == '.'){
            format++;
            st_spec.precision=0;
            if (*(format) == '*')
                st_spec.precision=-1;
            else{
                while(is_digit(*(format))){
                    st_spec.precision = st_spec.precision*10 + *(format)-'0';
                    format++;
                }
            }
            printf("DEBUG: Precision=%i\n",st_spec.precision);
        } 

        //Length
        if(*(format) == 'h' || *(format) == 'l' || *(format) == 'L' ){
            st_spec.length = *(format);
            format++;
            printf("DEBUG: Length=%c\n",st_spec.length);
        }

        //Specifiers
        if (*format == 'c' || *format == 'd' || *format == 'i' || *format == 'f' || *format == 's' || *format == 'u' || *format == '%' || *format == 'g' || *format == 'G' || *format == 'e' || *format == 'E' || *format == 'x' || *format == 'X' || *format == 'o' || *format == 'p') {
            st_spec.specifier = *format;
            format++;
            printf("DEBUG: Specifier=%c\n",st_spec.specifier);
        } else {
        st_spec.specifier='0';
    }
    format++;   
   return st_spec;
}

int is_digit(char c){
    return (c>='0' && c<='9');
}

/*TODO: Flags
 - [ ] #    При использовании со спецификаторами o, x или X перед числом вставляется 0, 0x или 0X соответственно (для значений, отличных от нуля). При использовании с e, E и f «заставляет» записанный вывод содержать десятичную точку, даже если за ней не последует никаких цифр. По умолчанию, если не следует никаких цифр, десятичная точка не записывается. При использовании с g или G результат такой же, как и с e или E, но конечные нули не удаляются.
 - [ ] 0    Заполняет число слева нулями (0) вместо пробелов, где указан спецификатор ширины (см. подспецификатор ширины).
*/ 

/*TODO: Width
 - [ ] (число)  Минимальное количество печатаемых символов. Если выводимое значение короче этого числа, результат дополняется пробелами. Значение не усекается, даже если результат больше.
 - [ ] *    В sprintf знак * значит, что ширина указывается не в строке формата, а в качестве дополнительного аргумента целочисленного значения, предшествующего аргументу, который необходимо отформатировать. В sscanf знак *, помещенный после % и перед спецификатором формата, считывает данные указанного типа, но подавляет их присваивание.
 */

/*TODO: Длина
 - [ ] h    Аргумент интерпретируется как короткое int или короткое int без знака (применяется только к целочисленным спецификаторам: i, d, o, u, x и X).
 - [ ] l    Аргумент интерпретируется как длинное int или длинное int без знака для целочисленных спецификаторов (i, d, o, u, x и X) и как широкий символ или строка широких символов для спецификаторов c и s.
 - [ ] L    Аргумент интерпретируется как длинный double (применяется только к спецификаторам с плавающей точкой — e, E, f, g и G).
*/


int s21_sscanf(const char *str, const char *format, ...){
    va_list args;
    va_start(args, format);
    struct Specifiers st_spec;
    const char *p = str;  // Указатель на входную строку
    const char *fmt = format;  // Указатель на строку формата
    //%[*][ширина][длина]спецификатор.
    int res=0;
    while (*fmt)
    {
        if(*fmt == '%'){
            st_spec = parse_specifiers(fmt);
            printf("\n!!! Flag=%c, Width=%i, Length=%c, Precision=%i, Specifiers=%c\n",st_spec.flag,st_spec.width,st_spec.length,st_spec.precision,st_spec.specifier);
            
            if(st_spec.specifier == 'c'){
                printf("DEBUG: Char=%c\n",*p);
                char *ch = va_arg(args, char*);
                *ch = *p;
                p++;           
            
            }else if(st_spec.specifier == 'd'){
                int znak=1;
                int i=0;
                int result=0;
                if(*p=='-'){
                    znak=-1;
                    p++;
                }
                while (is_digit(*p)){
                    result = result*10 + *p - '0';
                    p++;
                    i++;
                }
                if (i>0){
                    int *ch = va_arg(args, int*);
                    result = result*znak;
                    *ch = result;    
                    p++;
                    printf("DEBUG: Digit=%d\n",result);
                }

            
            }else if(st_spec.specifier == 'f'){
                int znak=1;
                int i=0;
                float result=0;
                if(*p=='-'){
                    znak=-1;
                    p++;
                }
                while (is_digit(*p)){
                    result = result*10 + *p - '0';
                    p++;
                    i++;
                }
                if (*p == '.'){
                    p++;
                    float ost=1;
                    while (is_digit(*p)){
                        ost = ost*0.1f;
                        result = result + (*p - '0')*ost;
                        p++;
                        i++;
                    }
                }
                if (i>0){
                    float *ch = va_arg(args, float*);
                    result = result*znak;
                    *ch = result;    
                    p++;
                    printf("DEBUG: Digit=%f\n",result);
                }

            }else if(st_spec.specifier == 's'){
                char *ch = va_arg(args, char*);
                // *ch = result; 

                int i=0;
                //char result[sizeof(ch)];

                while ((*p!=' ')){
                    *ch = *p;
                    // result[i] = *p;
                    p++;
                    ch++;
                    // result++;
                    i++;
                }
                if (i>0){
                    //    p++;
                    printf("DEBUG: String=%s\n",ch);
                }


            } else if(st_spec.specifier == '%'){
                printf("DEBUG: Char=%c\n",*p);
                p++;
                fmt++;
            }


            }else if(st_spec.specifier == 'i'){
                int znak=1;
                int i=0;
                int result=0;
                if(*p=='-'){
                    znak=-1;
                    p++;
                }
                if(*p=='0'){
                    p++;
                    if(*p=='x' || *p=='X'){
                        p++;   
                    } else{
                        printf("DEBUG: octal number\n");
                        while ((*p>='0' && *p<='8')){
                            result = result*8 + *p - '0';
                            p++;
                            i++;
                        }
                    }
                }
                while (is_digit(*p)){
                    result = result*10 + *p - '0';
                    p++;
                    i++;
                }
                if (i>0){
                    int *ch = va_arg(args, int*);
                    result = result*znak;
                    *ch = result;    
                    p++;
                    printf("DEBUG: Digit=%d\n",result);
                }
        }
    fmt++;
    }
    return res;
}


