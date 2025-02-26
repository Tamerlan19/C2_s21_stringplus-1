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

START_TEST(test_s21_sprintf_percent_basic) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Percent: %%";
    int ret = snprintf(buffer, sizeof(buffer), fmt); // Используем snprintf вместо sprintf
    int ret_s21 = s21_sprintf(buffer_s21, fmt);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_percent_with_text) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Start %% End";
    int ret = snprintf(buffer, sizeof(buffer), fmt); // Используем snprintf
    int ret_s21 = s21_sprintf(buffer_s21, fmt);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_percent_multiple) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "%% %% %%";
    int ret = snprintf(buffer, sizeof(buffer), fmt); // Используем snprintf
    int ret_s21 = s21_sprintf(buffer_s21, fmt);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_percent_with_width) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Percent: %5%";
    int ret = snprintf(buffer, sizeof(buffer), fmt); // Используем snprintf
    int ret_s21 = s21_sprintf(buffer_s21, fmt);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_percent_left_alignment) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Percent: %-5%";
    int ret = snprintf(buffer, sizeof(buffer), fmt); // Используем snprintf
    int ret_s21 = s21_sprintf(buffer_s21, fmt);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_percent_with_precision) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Percent: %.2%";
    int ret = snprintf(buffer, sizeof(buffer), fmt); // Используем snprintf
    int ret_s21 = s21_sprintf(buffer_s21, fmt);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

START_TEST(test_s21_sprintf_percent_width_precision) {
    char buffer[1024];
    char buffer_s21[1024];
    const char *fmt = "Percent: %5.2%";
    int ret = snprintf(buffer, sizeof(buffer), fmt); // Используем snprintf
    int ret_s21 = s21_sprintf(buffer_s21, fmt);
    ck_assert_int_eq(ret, ret_s21);
    ck_assert_str_eq(buffer, buffer_s21);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_debug;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");
  tc_debug = tcase_create("Debug");

  tcase_add_test(tc_core, test_s21_sprintf_basic_string);
  tcase_add_test(tc_core, test_s21_sprintf_d_int_format);
  tcase_add_test(tc_core, test_s21_sprintf_d_int);
  tcase_add_test(tc_core, test_s21_sprintf_d_left_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_d_width_flag);
  tcase_add_test(tc_core, test_s21_sprintf_d_zero_padding);
  tcase_add_test(tc_core, test_s21_sprintf_ld_long_int_format);
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

  tcase_add_test(tc_core, test_s21_sprintf_percent_basic);
  tcase_add_test(tc_core, test_s21_sprintf_percent_with_text);
  tcase_add_test(tc_core, test_s21_sprintf_percent_multiple);
  tcase_add_test(tc_core, test_s21_sprintf_percent_with_width);
  tcase_add_test(tc_core, test_s21_sprintf_percent_left_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_percent_with_precision);
  tcase_add_test(tc_core, test_s21_sprintf_percent_width_precision);


tcase_add_test(tc_debug, test_s21_sprintf_f_large_number);

  suite_add_tcase(s, tc_core);
  suite_add_tcase(s, tc_debug);

  return s;
}
