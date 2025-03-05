#include "s21_string.h"
#include <check.h>
#include <stdio.h>
#include <string.h>

START_TEST(test_s21_sprintf_basic_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Hello, World!";

  int ret = sprintf(buffer, "%s", fmt);
  int ret_s21 = s21_sprintf(buffer_s21, "%s", fmt);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
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
  char buffer_s21[1024];
  const char *fmt = "Number: %5d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision_flag) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Float: %.2f";
  int ret = sprintf(buffer, fmt, 3.14759);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 3.14759);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_d_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Number: %05d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_d_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Number: %-5d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_simple_char) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%c";

  int ret = sprintf(buffer, fmt, 'A');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'A');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_width) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%5c";

  int ret = sprintf(buffer, fmt, 'B');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'B');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_left_align) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%-5c";

  int ret = sprintf(buffer, fmt, 'C');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'C');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_zero_padding) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%5c";
  int ret = sprintf(buffer, fmt, 'D');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'D');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_min_width_one) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%1c";

  int ret = sprintf(buffer, fmt, 'E');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'E');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_c_negative_width) {
  char buffer[256];
  char buffer_s21[256];
  const char *fmt = "%-5c";

  int ret = sprintf(buffer, fmt, 'F');
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 'F');

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_d_int) {
  char buffer[100];
  char buffer_s21[100];
  const char *fmt = "Number: %d";

  int ret = sprintf(buffer, fmt, 42);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 42);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_f_float) {
  char buffer[100];
  char buffer_s21[100];
  const char *fmt = "Float: %.2f";

  int ret = sprintf(buffer, fmt, 3.14159);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, 3.14159);

  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
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

START_TEST(test_s21_sprintf_s_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %.3s";
  const char *str = "testing";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %10s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %10.3s";
  const char *str = "testing";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %-10s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_empty_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = "";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_null_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %s";
  const char *str = NULL;
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_long_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %.10s";
  const char *str = "This is a very long string";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %010s";
  const char *str = "Hello";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_s_exceed_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "String: %5s";
  const char *str = "LongerString";
  int ret = sprintf(buffer, fmt, str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_basic) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %u";
  unsigned int value = 12345;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %10u";
  unsigned int value = 789;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %.5u";
  unsigned int value = 45;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_width_precision) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %10.5u";
  unsigned int value = 678;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_left_alignment) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %-10u";
  unsigned int value = 123;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_zero_padding) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %010u";
  unsigned int value = 456;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_zero_value) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %.5u";
  unsigned int value = 0;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_large_number) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %u";
  unsigned int value = 4294967295; // Максимальное значение для unsigned int
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u_exceed_width) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Unsigned: %5u";
  unsigned int value = 123456789;
  int ret = sprintf(buffer, fmt, value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_basic) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %o";
    unsigned int value = 64; // Восьмеричное представление: 100
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_hash_flag) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %#o";
    unsigned int value = 64; // Восьмеричное представление: 100
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_width) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %5o";
    unsigned int value = 64; // Восьмеричное представление: 100
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_zero_padding) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %05o";
    unsigned int value = 64; // Восьмеричное представление: 100
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_dynamic_width) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %*o";
    unsigned int value = 64; // Восьмеричное представление: 100
    int width = 5;
    int ret = sprintf(buffer, fmt, width, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, width, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_dynamic_precision) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %.*o";
    unsigned int value = 64; // Восьмеричное представление: 100
    int precision = 5;
    int ret = sprintf(buffer, fmt, precision, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, precision, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_zero_value) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %o";
    unsigned int value = 0; // Нулевое значение
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_hash_zero_value) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %#o";
    unsigned int value = 0; // Нулевое значение
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_width_zero_padding) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %05o";
    unsigned int value = 10; // Восьмеричное представление: 12
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o_large_number) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Octal: %o";
    unsigned int value = 4294967295; // Максимальное значение для unsigned int (восьмеричное: 37777777777)
    int ret = sprintf(buffer, fmt, value);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, value);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_basic) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %p";
    int value = 42;
    int *ptr = &value;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_null_pointer) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %p";
    void *ptr = NULL;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_hash_flag) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %#p";
    int value = 42;
    int *ptr = &value;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_dynamic_width) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %*p";
    int value = 42;
    int *ptr = &value;
    int width = 20; // Динамическая ширина
    int ret = sprintf(buffer, fmt, width, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, width, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_zero_padding) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %016p";
    int value = 42;
    int *ptr = &value;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_dynamic_precision) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %.*p";
    int value = 42;
    int *ptr = &value;
    int precision = 16; // Динамическая точность
    int ret = sprintf(buffer, fmt, precision, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, precision, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_width_zero_padding) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %020p";
    int value = 42;
    int *ptr = &value;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_long_address) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %p";
    long long value = 123456789012345LL;
    long long *ptr = &value;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_left_alignment) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %-20p";
    int value = 42;
    int *ptr = &value;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p_zero_padding_with_width) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Pointer: %010p";
    int value = 42;
    int *ptr = &value;
    int ret = sprintf(buffer, fmt, ptr);
    int ret_s21 = s21_sprintf(buffer_s21, fmt, ptr);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_hs_short_string) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short String: %hs";
  char short_str[6] = "Hello"; // Массив char вместо строки
  int ret = sprintf(buffer, fmt, short_str);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, short_str);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ls_wide_string) {
    setlocale(LC_ALL, "en_US.utf8");

    wchar_t buffer[1024];
    char buffer_s21[1024];
    wchar_t buffer_s21_wide[1024]; // Буфер для преобразования buffer_s21 в wide string

    const char *fmt_narrow = "Wide String: %ls";
    wchar_t fmt_wide[1024];
    mbstowcs(fmt_wide, fmt_narrow, strlen(fmt_narrow) + 1); // Конвертируем формат в wchar_t

    wchar_t wide_str[] = L"Привет"; // Строка широких символов

    int ret = swprintf(buffer, 1024, fmt_wide, wide_str); // Форматируем wide string
    s21_sprintf(buffer_s21, fmt_narrow, wide_str); // Форматируем с помощью s21_sprintf

    // Преобразуем buffer_s21 в wide string
    size_t converted = mbstowcs(buffer_s21_wide, buffer_s21, 1024);
if (converted == (size_t)-1) {
    printf("Ошибка преобразования buffer_s21 в wide string\n");
    ck_abort(); // Аборт теста с сообщением об ошибке
}

    // Проверяем длину строки
    ck_assert_int_eq(ret, wcslen(buffer));
    // Сравниваем wide строки
    ck_assert_int_eq(wcscmp(buffer, buffer_s21_wide), 0);
}
END_TEST

START_TEST(test_s21_sprintf_hc_short_char) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Char: %hc";
  short int short_char = 'A'; // Короткий символ
  int ret = sprintf(buffer, fmt, short_char);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, short_char);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lc_wide_char) {
    setlocale(LC_ALL, "en_US.utf8");

    wchar_t buffer[1024];
    char buffer_s21[1024];
    wchar_t buffer_s21_wide[1024]; // Буфер для преобразования buffer_s21 в wide string

    const char *fmt_narrow = "Wide Char: %lc";
    wchar_t fmt_wide[1024];
    size_t len = strlen(fmt_narrow) + 1;
    mbstowcs(fmt_wide, fmt_narrow, len); // Конвертируем формат в wchar_t

    wchar_t wide_char = L'П'; // Широкий символ

    int ret = swprintf(buffer, 1024, fmt_wide, wide_char); // Форматируем wide character
    s21_sprintf(buffer_s21, fmt_narrow, wide_char);       // Форматируем с помощью s21_sprintf

    // Преобразуем buffer_s21 в wide string
    size_t converted = mbstowcs(buffer_s21_wide, buffer_s21, 1024);
    if (converted == (size_t)-1) {
        printf("Ошибка преобразования buffer_s21 в wide string\n");
        ck_abort();
    }

    // Проверяем длину строки
    ck_assert_int_eq(ret, wcslen(buffer));
    // Сравниваем wide строки
    ck_assert_int_eq(wcscmp(buffer, buffer_s21_wide), 0);
}
END_TEST

START_TEST(test_s21_sprintf_hd_short_int) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Int: %hd";
  short int short_value = -32768; // Минимальное значение для short int
  int ret = sprintf(buffer, fmt, short_value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, short_value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_ld_long_int) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Int: %ld";
  long int long_value = 2147483647L; // Максимальное значение для long int
  int ret = sprintf(buffer, fmt, long_value);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, long_value);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_hu_short_unsigned) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Short Unsigned: %hu";
  unsigned short int short_uvalue =
      65535; // Максимальное значение для unsigned short
  int ret = sprintf(buffer, fmt, short_uvalue);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, short_uvalue);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_lu_long_unsigned) {
  char buffer[1024];
  char buffer_s21[1024];
  const char *fmt = "Long Unsigned: %lu";
  unsigned long int long_uvalue =
      4294967295UL; // Максимальное значение для unsigned long
  int ret = sprintf(buffer, fmt, long_uvalue);
  int ret_s21 = s21_sprintf(buffer_s21, fmt, long_uvalue);
  ck_assert_int_eq(ret, ret_s21);
  ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

TCase *tcase_s21_sprintf_e(void);
TCase *tcase_s21_sprintf_x(void);
TCase *tcase_s21_sprintf_g(void);

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");

  TCase *tc_core_e = tcase_s21_sprintf_e();
  suite_add_tcase(s, tc_core_e);

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sprintf_basic_string);
  tcase_add_test(tc_core, test_s21_sprintf_d_int_format);
  tcase_add_test(tc_core, test_s21_sprintf_d_int);
  tcase_add_test(tc_core, test_s21_sprintf_d_left_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_d_width_flag);
  tcase_add_test(tc_core, test_s21_sprintf_d_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_ld_long_int_format);
  tcase_add_test(tc_core, test_s21_sprintf_negative_hd_short_int_format);
  tcase_add_test(tc_core, test_s21_sprintf_hd_short_int_format);
  tcase_add_test(tc_core, test_s21_sprintf_c_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_c_simple_char);
  tcase_add_test(tc_core, test_s21_sprintf_c_width);
  tcase_add_test(tc_core, test_s21_sprintf_c_left_align);
  tcase_add_test(tc_core, test_s21_sprintf_c_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_c_min_width_one);
  tcase_add_test(tc_core, test_s21_sprintf_c_negative_width);
  tcase_add_test(tc_core, test_s21_sprintf_c_width);
  tcase_add_test(tc_core, test_s21_sprintf_negative_ld_long_int_format);
  tcase_add_test(tc_core, test_s21_sprintf_f_large_number);
  tcase_add_test(tc_core, test_s21_sprintf_f_small_number);
  tcase_add_test(tc_core, test_s21_sprintf_f_left_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_f_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_f_negative_sign_flag);
  tcase_add_test(tc_core, test_s21_sprintf_f_positive_sign_flag);
  tcase_add_test(tc_core, test_s21_sprintf_f_width_precision_format);
  tcase_add_test(tc_core, test_s21_sprintf_f_width_format);
  tcase_add_test(tc_core, test_s21_sprintf_negative_f_format);
  tcase_add_test(tc_core, test_s21_sprintf_f_float);
  tcase_add_test(tc_core, test_s21_sprintf_f_precision_format);
  tcase_add_test(tc_core, test_s21_sprintf_ld_double_format);
  tcase_add_test(tc_core, test_s21_sprintf_f_precision_flag);

  tcase_add_test(tc_core, test_s21_sprintf_u_basic);
  tcase_add_test(tc_core, test_s21_sprintf_u_width);
  tcase_add_test(tc_core, test_s21_sprintf_u_precision);
  tcase_add_test(tc_core, test_s21_sprintf_u_left_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_u_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_u_zero_value);
  tcase_add_test(tc_core, test_s21_sprintf_u_large_number);
  tcase_add_test(tc_core, test_s21_sprintf_u_exceed_width);
  tcase_add_test(tc_core, test_s21_sprintf_u_width_precision);

  tcase_add_test(tc_core, test_s21_sprintf_s_basic);
  tcase_add_test(tc_core, test_s21_sprintf_s_precision);
  tcase_add_test(tc_core, test_s21_sprintf_s_width);
  tcase_add_test(tc_core, test_s21_sprintf_s_width_precision);
  tcase_add_test(tc_core, test_s21_sprintf_s_left_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_s_empty_string);
  tcase_add_test(tc_core, test_s21_sprintf_s_null_string);
  tcase_add_test(tc_core, test_s21_sprintf_s_long_string);
  tcase_add_test(tc_core, test_s21_sprintf_s_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_s_exceed_width);

  tcase_add_test(tc_core, test_s21_sprintf_o_basic);
  tcase_add_test(tc_core, test_s21_sprintf_o_hash_flag);
  tcase_add_test(tc_core, test_s21_sprintf_o_width);
  tcase_add_test(tc_core, test_s21_sprintf_o_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_o_dynamic_width);
  tcase_add_test(tc_core, test_s21_sprintf_o_dynamic_precision);
  tcase_add_test(tc_core, test_s21_sprintf_o_zero_value);
  tcase_add_test(tc_core, test_s21_sprintf_o_hash_zero_value);
  tcase_add_test(tc_core, test_s21_sprintf_o_width_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_o_large_number);

  tcase_add_test(tc_core, test_s21_sprintf_p_basic);
  tcase_add_test(tc_core, test_s21_sprintf_p_null_pointer);
  tcase_add_test(tc_core, test_s21_sprintf_p_hash_flag);
  tcase_add_test(tc_core, test_s21_sprintf_p_dynamic_width);
  tcase_add_test(tc_core, test_s21_sprintf_p_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_p_dynamic_precision);
  tcase_add_test(tc_core, test_s21_sprintf_p_width_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_p_long_address);
  tcase_add_test(tc_core, test_s21_sprintf_p_left_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_p_zero_padding_with_width);

  tcase_add_test(tc_core, test_s21_sprintf_hs_short_string);
  tcase_add_test(tc_core, test_s21_sprintf_ls_wide_string);
  tcase_add_test(tc_core, test_s21_sprintf_hc_short_char);
  tcase_add_test(tc_core, test_s21_sprintf_lc_wide_char);
  tcase_add_test(tc_core, test_s21_sprintf_hd_short_int);
  tcase_add_test(tc_core, test_s21_sprintf_ld_long_int);
  tcase_add_test(tc_core, test_s21_sprintf_hu_short_unsigned);
  tcase_add_test(tc_core, test_s21_sprintf_lu_long_unsigned);

  suite_add_tcase(s, tc_core);

  //[ ] удалить отладочные кейсы
  //   TCase *tc_debug;
  //   tc_debug = tcase_create("Debug");
  //   tcase_add_test(tc_debug, test_s21_sprintf_u_complex_case);
  // tcase_add_test(tc_debug, test_s21_sprintf_f_large_number);
  // suite_add_tcase(s, tc_debug);

  return s;
}
