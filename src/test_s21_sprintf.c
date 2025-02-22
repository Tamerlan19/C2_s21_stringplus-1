#include "s21_string.h"
#include <check.h>
#include <stdio.h>
#include <string.h>

START_TEST(test_s21_sprintf_basic_string) {
  char buffer[1024];
  s21_sprintf(buffer, "Hello, World!");
  ck_assert_str_eq(buffer, "Hello, World!");
}
END_TEST

START_TEST(test_s21_sprintf_d_int_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};

    s21_sprintf(buffer, "Number: %d", 42);
    sprintf(original_buffer, "Number: %d", 42);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_hd_short_int_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};

    short int short_value = 32767; // Максимальное значение для short
    s21_sprintf(buffer, "Short Number: %hd", short_value);
    sprintf(original_buffer, "Short Number: %hd", short_value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_ld_long_int_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};

    long int long_value = 2147483647L; // Максимальное значение для long
    s21_sprintf(buffer, "Long Number: %ld", long_value);
    sprintf(original_buffer, "Long Number: %ld", long_value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_negative_hd_short_int_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};

    short int negative_short = -32767;
    s21_sprintf(buffer, "Negative Short: %hd", negative_short);
    sprintf(original_buffer, "Negative Short: %hd", negative_short);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_negative_ld_long_int_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};

    long int negative_long = -2147483647L;
    s21_sprintf(buffer, "Negative Long: %ld", negative_long);
    sprintf(original_buffer, "Negative Long: %ld", negative_long);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST
START_TEST(test_s21_sprintf_d_width_flag) {
  char buffer[1024];
  s21_sprintf(buffer, "Number: %5d", 42);
  ck_assert_str_eq(buffer, "Number:    42");
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_flag) {
  char buffer[1024];
  char buffer2[1024];
  int ret_s21 = s21_sprintf(buffer, "Float: %.2f", 3.14759);
  int ret = sprintf(buffer2, "Float: %.2f", 3.14759);

  ck_assert_str_eq(buffer, buffer2);
  ck_assert_str_eq(ret, ret_s21);
}
END_TEST

START_TEST(test_s21_sprintf_d_zero_padding) {
  char buffer[1024];
  s21_sprintf(buffer, "Number: %05d", 42);
  ck_assert_str_eq(buffer, "Number: 00042");
}
END_TEST

START_TEST(test_s21_sprintf_d_left_alignment) {
  char buffer[1024];
  s21_sprintf(buffer, "Number: %-5d", 42);
  ck_assert_str_eq(buffer, "Number: 42   ");
}
START_TEST(test_s21_sprintf_c_simple_char) {
    char buffer[256] = {0};
    s21_sprintf(buffer, "%c", 'A'); // Передаем буфер явно
    ck_assert_str_eq(buffer, "A");
}
END_TEST

// Тест 2: Ширина больше одного символа
START_TEST(test_s21_sprintf_c_width) {
    char buffer[256] = {0};
    s21_sprintf(buffer, "%5c", 'B'); // Передаем буфер явно
    ck_assert_str_eq(buffer, "    B");
}
END_TEST

// Тест 3: Левое выравнивание
START_TEST(test_s21_sprintf_c_left_align) {
    char buffer[256] = {0};
    s21_sprintf(buffer, "%-5c", 'C'); // Передаем буфер явно
    ck_assert_str_eq(buffer, "C    ");
}
END_TEST

// Тест 4: Заполнение нулями
START_TEST(test_s21_sprintf_c_zero_padding) {
    char buffer[256] = {0};
    s21_sprintf(buffer, "%05c", 'D'); // Передаем буфер явно
    ck_assert_str_eq(buffer, "0000D");
}
END_TEST

// Тест 5: Минимальная ширина равна единице
START_TEST(test_s21_sprintf_c_min_width_one) {
    char buffer[256] = {0};
    s21_sprintf(buffer, "%1c", 'E'); // Передаем буфер явно
    ck_assert_str_eq(buffer, "E");
}
END_TEST

// Тест 6: Отрицательная ширина (должна игнорироваться)
START_TEST(test_s21_sprintf_c_negative_width) {
    char buffer[256] = {0};
    s21_sprintf(buffer, "%-5c", 'F'); // Передаем буфер явно
    ck_assert_str_eq(buffer, "F    ");
}
END_TEST

START_TEST(test_s21_sprintf_s_basic) {
    char buffer[100];
    s21_sprintf(buffer, "Hello, %s!", "world");
    ck_assert_str_eq(buffer, "Hello, world!");
}
END_TEST

START_TEST(test_s21_sprintf_d_int) {
    char buffer[100];
    s21_sprintf(buffer, "Number: %d", 42);
    ck_assert_str_eq(buffer, "Number: 42");
}
END_TEST

START_TEST(test_s21_sprintf_f_float) {
    char buffer[100];
    s21_sprintf(buffer, "Float: %.2f", 3.14159);
    ck_assert_str_eq(buffer, "Float: 3.14");
}
END_TEST

START_TEST(test_s21_sprintf_s_precision) {
    char buffer[100];
    s21_sprintf(buffer, "%.3s", "testing");
    ck_assert_str_eq(buffer, "tes");
}
END_TEST

// Тестовый кейс 1: Простое число без дополнительных форматов
START_TEST(test_s21_sprintf_u_simple_number) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %u", 123);
    ck_assert_str_eq(buffer, "Number: 123");
}
END_TEST

// Тестовый кейс 2: Число с шириной поля 
START_TEST(test_s21_sprintf_u_with_width) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %5u", 45);
    ck_assert_str_eq(buffer, "Number:    45");
}
END_TEST

// Тестовый кейс 3: Число с точностью
START_TEST(test_s21_sprintf_u_with_precision) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %.5u", 678);
    ck_assert_str_eq(buffer, "Number: 00678");
}
END_TEST

// Тестовый кейс 4: Левое выравнивание
START_TEST(test_s21_sprintf_u_left_alignment) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %-5u", 45);
    ck_assert_str_eq(buffer, "Number: 45   ");
}
END_TEST

// Тестовый кейс 5: Заполнение нулями
START_TEST(test_s21_sprintf_u_zero_padding) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %05u", 45);
    ck_assert_str_eq(buffer, "Number: 00045");
}
END_TEST

// Тестовый кейс 6: Число равно 0 с точностью 0
START_TEST(test_s21_sprintf_u_zero_with_zero_precision) {
    char buffer[1024];
    s21_sprintf(buffer, "Number: %.0u", 0);
    ck_assert_str_eq(buffer, "Number: ");
}
END_TEST

// Тестовый кейс 7: Комбинация ширины, точности и заполнения нулями
START_TEST(test_s21_sprintf_u_complex_case) {
    char buffer[1024]={0};
    char fmt[30]="Number: %08u";
    s21_sprintf(buffer, fmt, 789);
    ck_assert_str_eq(buffer, "Number: 00000789");
    printf("%s",fmt);
}
END_TEST
START_TEST(test_s21_sprintf_ld_double_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double long_value = 123456789.987654321;
    s21_sprintf(buffer, "Long Number: %lf", long_value);
    sprintf(original_buffer, "Long Number: %lf", long_value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_negative_f_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double negative_value = -123.456;
    s21_sprintf(buffer, "Negative Number: %f", negative_value);
    sprintf(original_buffer, "Negative Number: %f", negative_value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    s21_sprintf(buffer, "Number: %.2f", value);
    sprintf(original_buffer, "Number: %.2f", value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_width_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    s21_sprintf(buffer, "Number: %10f", value);
    sprintf(original_buffer, "Number: %10f", value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_width_precision_format) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    s21_sprintf(buffer, "Number: %10.2f", value);
    sprintf(original_buffer, "Number: %10.2f", value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_positive_sign_flag) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    s21_sprintf(buffer, "Number: %+f", value);
    sprintf(original_buffer, "Number: %+f", value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_negative_sign_flag) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double negative_value = -123.456;
    s21_sprintf(buffer, "Number: %+f", negative_value);
    sprintf(original_buffer, "Number: %+f", negative_value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_zero_padding) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    s21_sprintf(buffer, "Number: %010f", value);
    sprintf(original_buffer, "Number: %010f", value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_left_alignment) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double value = 123.456;
    s21_sprintf(buffer, "Number: %-10f", value);
    sprintf(original_buffer, "Number: %-10f", value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_small_number) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double small_value = 0.000123;
    s21_sprintf(buffer, "Small Number: %f", small_value);
    sprintf(original_buffer, "Small Number: %f", small_value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

START_TEST(test_s21_sprintf_f_large_number) {
    char buffer[1024] = {0};
    char original_buffer[1024] = {0};
    double large_value = 123456789.987654321;
    s21_sprintf(buffer, "Large Number: %.6f", large_value);
    sprintf(original_buffer, "Large Number: %.6f", large_value);
    ck_assert_str_eq(buffer, original_buffer);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

tcase_add_test(tc_core, test_s21_sprintf_basic_string);
tcase_add_test(tc_core, test_s21_sprintf_d_int_format);
tcase_add_test(tc_core, test_s21_sprintf_d_int);
tcase_add_test(tc_core, test_s21_sprintf_d_left_alignment);
tcase_add_test(tc_core, test_s21_sprintf_d_width_flag);
tcase_add_test(tc_core,test_s21_sprintf_d_zero_padding);
tcase_add_test(tc_core, test_s21_sprintf_ld_long_int_format);
tcase_add_test(tc_core, test_s21_sprintf_ld_long_int_format);
tcase_add_test(tc_core,test_s21_sprintf_negative_hd_short_int_format);
tcase_add_test(tc_core, test_s21_sprintf_hd_short_int_format);
tcase_add_test(tc_core, test_s21_sprintf_c_zero_padding);
tcase_add_test(tc_core, test_s21_sprintf_c_simple_char);
tcase_add_test(tc_core, test_s21_sprintf_c_width);
tcase_add_test(tc_core, test_s21_sprintf_c_left_align);
tcase_add_test(tc_core, test_s21_sprintf_c_zero_padding);
tcase_add_test(tc_core, test_s21_sprintf_c_min_width_one);
tcase_add_test(tc_core, test_s21_sprintf_c_negative_width);
tcase_add_test(tc_core, test_s21_sprintf_c_width);
tcase_add_test(tc_core,test_s21_sprintf_negative_ld_long_int_format);
tcase_add_test(tc_core,test_s21_sprintf_f_large_number);
tcase_add_test(tc_core,test_s21_sprintf_f_large_number);
tcase_add_test(tc_core,test_s21_sprintf_f_small_number);
tcase_add_test(tc_core,test_s21_sprintf_f_left_alignment);
tcase_add_test(tc_core,test_s21_sprintf_f_zero_padding);
tcase_add_test(tc_core,test_s21_sprintf_f_negative_sign_flag);
tcase_add_test(tc_core,test_s21_sprintf_f_positive_sign_flag);
tcase_add_test(tc_core,test_s21_sprintf_f_width_precision_format);
tcase_add_test(tc_core,test_s21_sprintf_f_width_format);
tcase_add_test(tc_core,test_s21_sprintf_negative_f_format);
tcase_add_test(tc_core, test_s21_sprintf_f_float);
tcase_add_test(tc_core,test_s21_sprintf_f_precision_format);
tcase_add_test(tc_core,test_s21_sprintf_ld_double_format);
tcase_add_test(tc_core, test_s21_sprintf_f_precision_flag);

tcase_add_test(tc_core, test_s21_sprintf_s_precision);
tcase_add_test(tc_core, test_s21_sprintf_s_basic);

tcase_add_test(tc_core, test_s21_sprintf_u_simple_number);
tcase_add_test(tc_core, test_s21_sprintf_u_with_width);
tcase_add_test(tc_core, test_s21_sprintf_u_with_precision);
tcase_add_test(tc_core, test_s21_sprintf_u_left_alignment);
tcase_add_test(tc_core, test_s21_sprintf_u_zero_padding);
tcase_add_test(tc_core, test_s21_sprintf_u_zero_with_zero_precision);
tcase_add_test(tc_core, test_s21_sprintf_u_complex_case);


  suite_add_tcase(s, tc_core);

  return s;
}
