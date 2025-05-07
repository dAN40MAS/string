#define _USE_MATH_DEFINES
#define _GNU_SOURCE

#include <string.h>

#include "s21_check.h"
#include "s21_string.h"

START_TEST(test_s21_memchr) {
  const char str[] = "123Good_day456";
  int ch = 'o';
  size_t len = strlen(str);

  ck_assert_ptr_eq(s21_memchr(str, ch, len), memchr(str, ch, len));
  ck_assert_ptr_eq(s21_memchr(str, 'x', len), memchr(str, 'x', len));
}
END_TEST

START_TEST(test_s21_memcmp) {
  const char str1[] = "Hi, world!";
  const char str2[] = "Hi, world!";
  const char str3[] = "Hi, worle!";
  size_t len = strlen(str1);

  ck_assert_int_eq(s21_memcmp(str1, str2, len), memcmp(str1, str2, len));
  ck_assert_int_eq(s21_memcmp(str1, str3, len), memcmp(str1, str3, len));
  ck_assert_int_eq(s21_memcmp(str3, str1, len), memcmp(str3, str1, len));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char dest1[50] = "";
  char dest2[50] = "";
  const char src[] = "make all";
  size_t len = strlen(src);

  s21_memcpy(dest1, src, len);
  memcpy(dest2, src, len);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strrchr_found) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), &str[8]);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'x'), NULL);
}
END_TEST

START_TEST(test_strrchr_first_char) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'H'), &str[0]);
}
END_TEST

START_TEST(test_strrchr_last_char) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, '!'), &str[12]);
}
END_TEST

START_TEST(test_strstr_found) {
  char haystack[] = "Hello, world!";
  char needle[] = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), &haystack[7]);
}
END_TEST

START_TEST(test_strstr_not_found) {
  char haystack[] = "Hello, world!";
  char needle[] = "planet";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), NULL);
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  char haystack[] = "Hello, world!";
  char needle[] = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), haystack);
}
END_TEST

START_TEST(test_strstr_partial_match) {
  char haystack[] = "Hello, world!";
  char needle[] = "worl";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), &haystack[7]);
}
END_TEST

START_TEST(test_strtok_basic) {
  char str[] = "Hello, world!";
  char *token = s21_strtok(str, " ,!");
  ck_assert_str_eq(token, "Hello");

  token = s21_strtok(NULL, " ,!");
  ck_assert_str_eq(token, "world");
}
END_TEST

START_TEST(test_strtok_no_delim) {
  char str[] = "HelloWorld";
  char *token = s21_strtok(str, " ,!");
  ck_assert_str_eq(token, "HelloWorld");

  token = s21_strtok(NULL, " ,!");
  ck_assert_ptr_eq(token, NULL);
}
END_TEST

START_TEST(test_strtok_consecutive_delim) {
  char str[] = "Hello,,world";
  char *token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "Hello");

  token = s21_strtok(NULL, ",");
  ck_assert_str_eq(token, "world");
}
END_TEST

START_TEST(test_strerror) {
  char *src = s21_strerror(1);
  ck_assert_pstr_eq(src, strerror(1));

  char *src1 = s21_strerror(70);
  ck_assert_pstr_eq(src1, strerror(70));

  char *src2 = s21_strerror(876);
  ck_assert_pstr_eq(src2, strerror(876));
}
END_TEST

START_TEST(test_strlen) {
  size_t res1 = s21_strlen("Nikita");
  size_t res2 = strlen("Nikita");

  ck_assert_int_eq(res1, res2);

  res1 = s21_strlen("");
  res2 = strlen("");

  ck_assert_int_eq(res1, res2);
}

START_TEST(test_strpbrk) {
  char str1[7] = "Nikita";
  char str2[4] = "ale";
  char *result, *result2;

  result = s21_strpbrk(str1, str2);
  result2 = strpbrk(str1, str2);
  ck_assert_pstr_eq(result, result2);

  result = s21_strpbrk("", str2);
  result2 = strpbrk("", str2);
  ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(s21_strchr_test) {
  char s1[50] = "Hello";
  char s2[50] = "World";
  char s3[50] = "";
  char s4[50] = "Hello_World";

  ck_assert_ptr_eq(s21_strchr(s1, 'e'), strchr(s1, 'e'));
  ck_assert_ptr_eq(s21_strchr(s2, 'p'), strchr(s2, 'p'));
  ck_assert_ptr_eq(s21_strchr(s3, 'H'), strchr(s3, 'H'));
  ck_assert_ptr_eq(s21_strchr(s4, 'o'), strchr(s4, 'o'));
}
END_TEST

START_TEST(s21_strncat_test) {
  char s1[50] = "Hello";
  char s2[50] = "World";
  char s3[50] = "";
  char s4[50] = "Hello_World";

  ck_assert_ptr_eq(s21_strncat(s1, "World", 4), strncat(s1, "World", 4));
  ck_assert_ptr_eq(s21_strncat(s2, "HELP ME", 6), strncat(s2, "HELP ME", 6));
  ck_assert_ptr_eq(s21_strncat(s3, "Hello", 3), strncat(s3, "Hello", 3));
  ck_assert_ptr_eq(s21_strncat(s4, "", 5), strncat(s4, "", 5));
}
END_TEST

START_TEST(s21_memset_test) {
  char s1[50] = "Hello";
  char s2[50] = "World";
  char s3[50] = "";
  char s4[50] = "Hello_World";

  ck_assert_ptr_eq(s21_memset(s1, 'a', 5), memset(s1, 'a', 5));
  ck_assert_ptr_eq(s21_memset(s2, 'a', 3), memset(s2, 'a', 3));
  ck_assert_ptr_eq(s21_memset(s3, '.', 2), memset(s3, 'a', 2));
  ck_assert_ptr_eq(s21_memset(s4 + 2, '.', 4), memset(s4 + 2, '.', 4));
}
END_TEST

START_TEST(test_s21_strncmp) {
  const char str1[] = "Hello, world!";
  const char str2[] = "Hello, world!";
  const char str3[] = "Hello, there!";
  const char str4[] = "Hello";

  size_t len1 = 5;
  size_t len2 = 5;
  size_t len3 = 3;

  ck_assert_int_eq(s21_strncmp(str1, str2, len1), strncmp(str1, str2, len1));
  ck_assert_int_eq(s21_strncmp(str1, str3, len2), strncmp(str1, str3, len2));
  ck_assert_int_eq(s21_strncmp(str4, str1, len3), strncmp(str4, str1, len3));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char dest1[50] = "";
  char dest2[50] = "";
  const char src[] = "copy this text";
  size_t len = strlen(src);

  s21_strncpy(dest1, src, len);
  strncpy(dest2, src, len);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_strcspn) {
  const char str1[] = "Hello, world!";
  const char str2[] = "aeiou";
  const char str3[] = "xyz";

  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
  ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));
}
END_TEST

START_TEST(sprintf_string_1) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "padding:\t[%2s]\n";
  char *_1 = "Hello, world!";
  int res = sprintf(str, format, _1);
  int s21_res = s21_sprintf(s21_str, format, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_string_2) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "padding:\t[%-2s]\n";
  char *_1 = "Hello, world!";
  int res = sprintf(str, format, _1);
  int s21_res = s21_sprintf(s21_str, format, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_string_4) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "trunc:\t[%.5s]\n";
  char *_1 = "Hello, world!";
  int res = sprintf(str, format, _1);
  int s21_res = s21_sprintf(s21_str, format, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_string_5) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "trunc:\t[%*s]\n";
  char *_1 = "Hello, world!";
  int res = sprintf(str, format, 4, _1);
  int s21_res = s21_sprintf(s21_str, format, 4, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_string_6) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "\t[%1.5s]\n\t[%-1.5s]\n";
  char *_1 = "Hello, world!";
  int res = sprintf(str, format, _1, _1);
  int s21_res = s21_sprintf(s21_str, format, _1, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_char_1) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "chars:\t[%c%%]\n";
  char _1 = '1';
  int res = sprintf(str, format, _1);
  int s21_res = s21_sprintf(s21_str, format, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_char_2) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "chars:\t[%.5c%%]\n";
  char _1 = '1';
  int res = sprintf(str, format, _1);
  int s21_res = s21_sprintf(s21_str, format, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_char_3) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "chars:\t[%-c%%]\n";
  char _1 = '1';
  int res = sprintf(str, format, 5, _1);
  int s21_res = s21_sprintf(s21_str, format, 5, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_char_4) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "chars:\t[%-%]\t[%10%]\n";
  int res = sprintf(str, format, 5, 5);
  int s21_res = s21_sprintf(s21_str, format, 5, 5);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_int_1) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "%d %.6d";
  int _1 = 1;
  int _2 = 2;
  int res = sprintf(str, format, _1, _2);
  int s21_res = s21_sprintf(s21_str, format, _1, _2);
  ck_assert_int_eq(s21_res, res);
  ck_assert_str_eq(str, s21_str);
}
END_TEST

START_TEST(sprintf_int_2) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "dec:\t%i %d %+i %+d %.6i %.6d %4.2i %4.2d %+.0i %+.0d\n";
  int _1 = 0;
  int res = sprintf(str, format, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1);
  int s21_res =
      s21_sprintf(s21_str, format, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_int_3) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "dec:\t%i %d %+i %+d %.6i %.6d %4.2i %4.2d %+.0i %+.0d\n";
  int _1 = -1;
  int _2 = -2;
  int _3 = -3;
  int _4 = -4;
  int _5 = -5;
  int res = sprintf(str, format, _1, _1, _2, _2, _3, _3, _4, _4, _5, _5);
  int s21_res =
      s21_sprintf(s21_str, format, _1, _1, _2, _2, _3, _3, _4, _4, _5, _5);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_int_14) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "unsign:\t%-u %+.2u %6.0u %u\n";
  int _1 = 4;
  int _2 = 10;
  int _3 = 0;
  int _4 = -4;
  int res = sprintf(str, format, 4, _1, _2, _3, _4);
  int s21_res = s21_sprintf(s21_str, format, 4, _1, _2, _3, _4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_int_15) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "wide int:\t %+.2d %6.0hu\n";
  short int _1 = 4;
  int _2 = 10;
  short int _3 = 0;
  long int _4 = 40;
  int res = sprintf(str, format, 4, _1, _2, _3, _4);
  int s21_res = s21_sprintf(s21_str, format, 4, _1, _2, _3, _4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_float_1) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "round:\t%.*f % .0f %.0f %.16f\n";
  double _1 = M_PI;
  double _2 = M_SQRT2;
  double _3 = M_E;
  double _4 = M_PI;
  int res = sprintf(str, format, 1, _1, _2, _3, _4);
  int s21_res = s21_sprintf(s21_str, format, 1, _1, _2, _3, _4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_float_2) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "padding:\t%*.2lf %+7.2lf % .2f %05.2f\n";
  double _1 = -1 / M_PI;
  double _2 = M_SQRT2;
  double _3 = M_E;
  double _4 = M_PI;
  int res = sprintf(str, format, -10, _1, _2, _3, _4);
  int s21_res = s21_sprintf(s21_str, format, -10, _1, _2, _3, _4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_float_3) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "sci:\t%f %f %-+10.0f %+.8f\n";
  double _1 = -1 / M_PI;
  double _2 = M_SQRT2 * 100;
  double _3 = M_E / 1e+6;
  double _4 = M_PI;
  int res = sprintf(str, format, _1, _2, _3, _4);
  int s21_res = s21_sprintf(s21_str, format, _1, _2, _3, _4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_float_4) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "sci:\t%f %f %+-10.0f %+.7f\n";
  double _1 = -1 / M_PI;
  double _2 = M_SQRT2 * 100;
  double _3 = M_E / 1e+6;
  double _4 = M_PI;
  int res = sprintf(str, format, _1, _2, _3, _4);
  int s21_res = s21_sprintf(s21_str, format, _1, _2, _3, _4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_float_6) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "zero:%-+5.0f %10.2f % 10f %+ 10f % f\n";
  float _1 = 0.0;
  float _2 = 0.0;

  int res = sprintf(str, format, _1, _2, _1, _1, _2);
  int s21_res = s21_sprintf(s21_str, format, _1, _2, _1, _1, _2);

  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_num_1) {
  char str[STRLEN] = {0};
  char s21_str[STRLEN] = {0};
  char *format = "%s:\t[%n] [%+7n] [% -7n]\n";
  char *_1 = "num";
  int out_1 = 0, out_2 = 0, out_3 = 0, out_4 = 0;
  int s21_out_1 = 0, s21_out_2 = 0, s21_out_3 = 0, s21_out_4 = 0;

  int res = sprintf(str, format, _1, &out_1, &out_2, &out_3, &out_4);
  int s21_res = s21_sprintf(s21_str, format, _1, &s21_out_1, &s21_out_2,
                            &s21_out_3, &s21_out_4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
  ck_assert_int_eq(s21_out_4, out_4);
}
END_TEST

START_TEST(sprintf_octal_1) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%o %o %o %o\n";
  int out_1 = 10;
  int out_2 = 5;
  int out_3 = 12;
  int out_4 = -4;

  int res = sprintf(str, format, out_1, out_2, out_3, out_4);
  int s21_res = s21_sprintf(s21_str, format, out_1, out_2, out_3, out_4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}

END_TEST

START_TEST(sprintf_octal_2) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%o %#o %#o %o\n";
  int out_1 = 10;
  int out_2 = 5;
  int out_3 = 12;
  int out_4 = -4;

  int res = sprintf(str, format, out_1, out_2, out_3, out_4);
  int s21_res = s21_sprintf(s21_str, format, out_1, out_2, out_3, out_4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}

END_TEST

START_TEST(sprintf_hex_1) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%x %x %x %x\n";
  int out_1 = 10;
  int out_2 = 5;
  int out_3 = 12;
  int out_4 = -4;

  int res = sprintf(str, format, out_1, out_2, out_3, out_4);
  int s21_res = s21_sprintf(s21_str, format, out_1, out_2, out_3, out_4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_hex_2) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%x %X %x %X\n";
  int out_1 = 10;
  int out_2 = 5;
  int out_3 = 12;
  int out_4 = -4;

  int res = sprintf(str, format, out_1, out_2, out_3, out_4);
  int s21_res = s21_sprintf(s21_str, format, out_1, out_2, out_3, out_4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}
END_TEST

START_TEST(sprintf_hex_3) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%x %#X %#x %X\n";
  int out_1 = 10;
  int out_2 = 5;
  int out_3 = 12;
  int out_4 = -4;

  int res = sprintf(str, format, out_1, out_2, out_3, out_4);
  int s21_res = s21_sprintf(s21_str, format, out_1, out_2, out_3, out_4);
  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}

END_TEST

START_TEST(sprintf_sci_1) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%e %e %e %e\n";
  double out_1 = 1012334534435.123;
  double out_2 = 0.001235;
  double out_3 = 12.10215;
  double out_4 = -4.4114353453;

  int res = sprintf(str, format, out_1, out_2, out_3, out_4);
  int s21_res = s21_sprintf(s21_str, format, out_1, out_2, out_3, out_4);

  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}

END_TEST

START_TEST(sprintf_sci_2) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%e %E %e %E\n";
  double out_1 = 1012334534435.123;
  double out_2 = 0.001235;
  double out_3 = 12.10215;
  double out_4 = -4.4114353453;

  int res = sprintf(str, format, out_1, out_2, out_3, out_4);
  int s21_res = s21_sprintf(s21_str, format, out_1, out_2, out_3, out_4);

  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}

END_TEST

START_TEST(sprintf_pointer_1) {
  char str[STRLEN];
  char s21_str[STRLEN];
  char *format = "%p %p %p %p\n";
  double out_1 = 1012334534435.123;
  double out_2 = 0.001235;
  double out_3 = 12.10215;
  double out_4 = -4.4114353453;

  int res = sprintf(str, format, &out_1, &out_2, &out_3, &out_4);
  int s21_res = s21_sprintf(s21_str, format, &out_1, &out_2, &out_3, &out_4);

  ck_assert_int_eq(s21_res, res);
  ck_assert_pstr_eq(s21_str, str);
}

END_TEST

START_TEST(sscanf_c_1) {
  char *format = "%c";
  char *str = "He\tllo, world!";
  char out = 0, s21_out = 0;
  int res = sscanf(str, format, &out);
  int s21_res = s21_sscanf(str, format, &s21_out);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out, out);
}
END_TEST

START_TEST(sscanf_c_2) {
  char *format = "%c";
  char *str = "";
  char out = 0, s21_out = 0;
  int res = sscanf(str, format, &out);
  int s21_res = s21_sscanf(str, format, &s21_out);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_c_3) {
  char *format = "%10c %c %c";
  char *str = "Hello world!";
  char out_1[STRLEN] = {0}, s21_out_1[STRLEN] = {0};
  char out_2 = 0, out_3 = 0, s21_out_2 = 0, s21_out_3 = 0;
  int res = sscanf(str, format, out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_mem_eq(s21_out_1, out_1, 10);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_c_4) {
  char *format = "%c %c %c";
  char *str = "He\tllo, world!";
  char out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
       s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_c_5) {
  char *format = "%c %*c %c %c";
  char *str = "He\tllo, world!";
  char out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
       s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_c_6) {
  char *format = "%lc%Lc%Lc";
  char *str = "English Юникод держи!";
  wchar_t out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
          s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_c_7) {
  char *format = "%c%cello %c";
  char *str = "Hello world!";
  char out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
       s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
}
END_TEST

START_TEST(sscanf_d_1) {
  char *format = "%d %d %d";
  char *str = "1 2  3 4";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_2) {
  char *format = "%1d %2d %3d";
  char *str = "0001 2 3 4";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_4) {
  char *format = "%d 3%d 5%*d %d";
  char *str = "12 34 56 7";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_5) {
  char *format = "%d/%d/%d";
  char *str = "24/07/2024";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_6) {
  char *format = "%d / %d / %d";
  char *str = "24/07/2024";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_7) {
  char *format = "%d%d%d";
  char *str = "1\t2\n3 4";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_8) {
  char *format = "%d %d %d";
  char *str = "+1 +02 -3 4";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_9) {
  char *format = "%ld %d %*ld %Ld";
  char *str = "1 -2 -3 +4";
  long int out_1 = 0, s21_out_1 = 0;
  long long int out_3 = 0, s21_out_3 = 0;
  int out_2 = 0, s21_out_2 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_d_10) {
  char *format = "%hd %d %*hd %hd";
  char *str = "1 -2 -3 +4";
  short int out_1 = 0, out_3 = 0, s21_out_1 = 0, s21_out_3 = 0;
  int out_2 = 0, s21_out_2 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_s_1) {
  char *format = "%s";
  char *str = "Hello, world!";
  char out_1[STRLEN] = {0};
  char s21_out_1[STRLEN] = {0};
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_str_eq(s21_out_1, out_1);
}
END_TEST

START_TEST(sscanf_s_2) {
  char *format = "%s";
  char *str = "";
  char out_1[STRLEN] = {0};
  char s21_out_1[STRLEN] = {0};
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_res, -1);
}
END_TEST

START_TEST(sscanf_s_3) {
  char *format = "%s %s %s";
  char *str = "Hello,\tworld!\nHi, test!";
  char out_1[STRLEN] = {0}, out_2[STRLEN] = {0}, out_3[STRLEN] = {0};
  char s21_out_1[STRLEN] = {0}, s21_out_2[STRLEN] = {0},
       s21_out_3[STRLEN] = {0};
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_str_eq(s21_out_1, out_1);
  ck_assert_str_eq(s21_out_2, out_2);
  ck_assert_str_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_s_4) {
  char *format = "%2s %3s %4s";
  char *str = "Hello, world! Hi, test!";
  char out_1[STRLEN] = {0}, out_2[STRLEN] = {0}, out_3[STRLEN] = {0};
  char s21_out_1[STRLEN] = {0}, s21_out_2[STRLEN] = {0},
       s21_out_3[STRLEN] = {0};
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_str_eq(s21_out_1, out_1);
  ck_assert_str_eq(s21_out_2, out_2);
  ck_assert_str_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_s_5) {
  char *format = "%s %*s %s %s";
  char *str = "Hello, world! Hi, test!";
  char out_1[STRLEN] = {0}, out_2[STRLEN] = {0}, out_3[STRLEN] = {0};
  char s21_out_1[STRLEN] = {0}, s21_out_2[STRLEN] = {0},
       s21_out_3[STRLEN] = {0};
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_str_eq(s21_out_1, out_1);
  ck_assert_str_eq(s21_out_2, out_2);
  ck_assert_str_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_s_6) {
  char *format = "%s %5ls %s";
  char *str = "Hello, world! Hi, test!";
  char out_1[STRLEN] = {0}, out_3[STRLEN] = {0};
  char s21_out_1[STRLEN] = {0}, s21_out_3[STRLEN] = {0};
  wchar_t out_2[STRLEN] = {0}, s21_out_2[STRLEN] = {0};
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_str_eq(s21_out_1, out_1);
  ck_assert_mem_eq(s21_out_2, out_2, 10);
  ck_assert_str_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_f_1) {
  char *format = "%f %f %f";
  char *str =
      "1.41421356237309504880 2.71828182845904523536 3.14159265358979323846";
  float out_1, out_2, out_3;
  float s21_out_1, s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_float_eq(s21_out_2, out_2);
  ck_assert_float_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_f_2) {
  char *format = "%f %*f %f";
  char *str =
      "1.41421356237309504880 2.71828182845904523536 3.14159265358979323846";
  float out_1, out_2;
  float s21_out_1, s21_out_2;
  int res = sscanf(str, format, &out_1, &out_2);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_float_eq(s21_out_2, out_2);
}
END_TEST

START_TEST(sscanf_f_3) {
  char *format = "%f %7f %*ld %f";
  char *str =
      "1.41421356237309504880 2.71828182845904523536 3.14159265358979323846";
  float out_1, out_2, out_3;
  float s21_out_1, s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_float_eq(s21_out_2, out_2);
  ck_assert_float_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_f_4) {
  char *format = "%f %*7f %ld %f";
  char *str =
      "1.41421356237309504880 2.71828182845904523536 3.14159265358979323846";
  long int out_2, s21_out_2;
  float out_1, out_3;
  float s21_out_1, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_float_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_f_5) {
  char *format = "%f %f %*f %f";
  char *str = "NAN -NaN +NAn -nan";
  float out_1, out_2, out_3;
  float s21_out_1, s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_nan(out_1);
  ck_assert_float_nan(out_2);
  ck_assert_float_nan(out_3);
}
END_TEST

START_TEST(sscanf_f_6) {
  char *format = "%f %f %*f %f";
  char *str = "INF -Inf +INf -inf";
  float out_1, out_2, out_3;
  float s21_out_1, s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_float_eq(s21_out_2, out_2);
  ck_assert_float_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_f_7) {
  char *format = "%lf %Lf %Lf";
  char *str =
      "1.41421356237309504880 2.71828182845904523536 3.14159265358979323846";
  double out_1;
  double s21_out_1;
  long double out_2, out_3;
  long double s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_double_eq_tol(s21_out_1, out_1, 1e-7);
  ck_assert_ldouble_eq_tol(s21_out_2, out_2, 1e-7);
  ck_assert_ldouble_eq_tol(s21_out_3, out_3, 1e-7);
}
END_TEST

START_TEST(sscanf_f_8) {
  char *format = "%*llf %*Lf %Lf";
  char *str =
      "1.41421356237309504880 2.71828182845904523536 3.14159265358979323846";
  long double out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_double_eq(s21_out_1, out_1);
}
END_TEST
START_TEST(sscanf_f_9) {
  char *format = "%f";
  char *str = "text without digit";
  float out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_i_1) {
  char *format = "%i%i%i";
  char *str = "010 10 0x10";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_i_2) {
  char *format = "%*i%i%*i%i%*i%i";
  char *str = "010 020 10 20 0x10 0x20";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_i_3) {
  char *format = "%i%i%i";
  char *str = "+010 -10 +0x10";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_i_4) {
  char *format = "%*2i%i%10i%2i";
  char *str = "010 10 0x10";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_i_5) {
  char *format = "%hi%2hi%*hi%hi";
  char *str = "010 10 0x10 0x8000";
  short int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
            s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_i_6) {
  char *format = "%li%2li%*li%li";
  char *str = "010 10 0x10 0x8000000000000000";
  long int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
           s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_i_7) {
  char *format = "%i";
  char *str = "text without digit";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_o_1) {
  char *format = "%o%o%o";
  char *str = "+011 -0010 109";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_o_2) {
  char *format = "%3o%*d%*3o%o%3o";
  char *str = "+011 -0010 109";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_o_3) {
  char *format = "%ho%23lo%*ho%lo";
  char *str = "+010 -1000000000000000000001 -0010 +1000000000000000000000";
  short int out_1 = 0, s21_out_1 = 0;
  long int out_2, out_3, s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_o_4) {
  char *format = "%o";
  char *str = "text without digit";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_x_1) {
  char *format = "%x%X%X";
  char *str = "+011 -0010 10G";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_x_2) {
  char *format = "%3x%*d%*3X%x%3X";
  char *str = "+011 -0010 10G";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_x_3) {
  char *format = "%hx%23lX%*hx%lX";
  char *str = "+010 -8000000000000001 -0010 +8000000000000000";
  short int out_1 = 0, s21_out_1 = 0;
  long int out_2, out_3, s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_x_4) {
  char *format = "%x";
  char *str = "text without digit";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_u_1) {
  char *format = "%u%u%u";
  char *str = "+010 -001 4294967296";
  unsigned int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
               s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_u_2) {
  char *format = "%3u%*d%*3u%u%3u";
  char *str = "+010 -001 42A4967296";
  unsigned int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
               s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_u_3) {
  char *format = "%hu%23lu%*hu%lu";
  char *str = "+010 -1 -0010 4294967296";
  short unsigned int out_1 = 0, s21_out_1 = 0;
  long unsigned int out_2, out_3, s21_out_2, s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_u_4) {
  char *format = "%u";
  char *str = "text without digit";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sprintf_g_1) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%g", 2345.4324);
  int r2 = s21_sprintf(str2, "%g", 2345.4324);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_g_2) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%G", 43242.43242);
  int r2 = s21_sprintf(str2, "%G", 43242.43242);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_p_1) {
  char *format = "%p%p%p";
  char *str = "0x7ffddddddddd 0x7ffdcccccccc 0x7ffdbbbbbbbb";
  void *out_1, *out_2, *out_3, *s21_out_1, *s21_out_2, *s21_out_3;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_ptr_eq(s21_out_1, out_1);
  ck_assert_ptr_eq(s21_out_2, out_2);
  ck_assert_ptr_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_p_2) {
  char *format = "%p";
  char *str = "text without digit";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_n_1) {
  char *format = "%i %*s %*s %40d %n";
  char *str = "-012 Hello, world! +0x34";
  int out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
      s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
  ck_assert_int_eq(s21_out_2, out_2);
  ck_assert_int_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_e_1) {
  char *format = "%e%E%E";
  char *str = "+011 -0010 0010G";
  float out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
        s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_float_eq(s21_out_2, out_2);
  ck_assert_float_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_e_2) {
  char *format = "%e%E%E";
  char *str = "1e2 1E0 0e2";
  float out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
        s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_float_eq(s21_out_2, out_2);
  ck_assert_float_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_e_3) {
  char *format = "%e%*c%E%E";
  char *str = "1e+2e .5E-1 0.4e.2";
  float out_1 = 0, out_2 = 0, out_3 = 0, s21_out_1 = 0, s21_out_2 = 0,
        s21_out_3 = 0;
  int res = sscanf(str, format, &out_1, &out_2, &out_3);
  int s21_res = s21_sscanf(str, format, &s21_out_1, &s21_out_2, &s21_out_3);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
  ck_assert_float_eq(s21_out_2, out_2);
  ck_assert_float_eq(s21_out_3, out_3);
}
END_TEST

START_TEST(sscanf_e_4) {
  char *format = "%e";
  char *str = "text without digit";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_pct_1) {
  char *format = "%*s %*s %d %% %*s";
  char *str = "our targer 100% result";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
  ck_assert_float_eq(s21_out_1, out_1);
}
END_TEST

START_TEST(sscanf_pct_2) {
  char *format = "%%";
  char *str = "text without percents";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1);
  int s21_res = s21_sscanf(str, format, &s21_out_1);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(sscanf_default_1) {
  char *format = "%d %j";
  char *str = "100 and brocen specifyre";
  int out_1 = 0, s21_out_1 = 0;
  int res = sscanf(str, format, &out_1, 5);
  int s21_res = s21_sscanf(str, format, &s21_out_1, 5);
  ck_assert_int_eq(s21_res, res);
  ck_assert_int_eq(s21_out_1, out_1);
}
END_TEST

START_TEST(test_s21_to_upper_basic) {
  const char *str = "hello, World!";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO, WORLD!");
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  const char *str = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_no_change) {
  const char *str = "HELLO, WORLD!";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO, WORLD!");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_basic) {
  const char *str = "Hello, WORLD!";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "hello, world!");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  const char *str = "";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_no_change) {
  const char *str = "hello, world!";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "hello, world!");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_basic) {
  const char *src = "Hello, ";
  const char *str = "beautiful";
  char *result = s21_insert(src, str, 7);
  ck_assert_str_eq(result, "Hello, beautiful");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_start) {
  const char *src = "world!";
  const char *str = "Hello, ";
  char *result = s21_insert(src, str, 0);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_end) {
  const char *src = "Hello, ";
  const char *str = "world!";
  char *result = s21_insert(src, str, 7);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_basic) {
  const char *src = "  Hello, world!  ";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_chars) {
  const char *src = "--Hello, world!--";
  const char *trim_chars = "-";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_no_trim) {
  const char *src = "Hello, world!";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_string");

  tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_memchr);
  tcase_add_test(tc, test_s21_memcmp);
  tcase_add_test(tc, test_s21_memcpy);

  tcase_add_test(tc, test_s21_strncmp);
  tcase_add_test(tc, test_s21_strncpy);
  tcase_add_test(tc, test_s21_strcspn);

  tcase_add_test(tc, test_strrchr_found);
  tcase_add_test(tc, test_strrchr_not_found);
  tcase_add_test(tc, test_strrchr_first_char);
  tcase_add_test(tc, test_strrchr_last_char);

  tcase_add_test(tc, test_strstr_found);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_partial_match);

  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_no_delim);
  tcase_add_test(tc, test_strtok_consecutive_delim);

  tcase_add_test(tc, test_strerror);
  tcase_add_test(tc, test_strlen);
  tcase_add_test(tc, test_strpbrk);

  tcase_add_test(tc, s21_strchr_test);
  tcase_add_test(tc, s21_strncat_test);
  tcase_add_test(tc, s21_memset_test);

  tcase_add_test(tc, sprintf_string_1);
  tcase_add_test(tc, sprintf_string_2);
  tcase_add_test(tc, sprintf_string_4);
  tcase_add_test(tc, sprintf_string_5);
  tcase_add_test(tc, sprintf_string_6);

  tcase_add_test(tc, sprintf_char_1);
  tcase_add_test(tc, sprintf_char_2);
  tcase_add_test(tc, sprintf_char_3);
  tcase_add_test(tc, sprintf_char_4);

  tcase_add_test(tc, sprintf_int_1);
  tcase_add_test(tc, sprintf_int_2);
  tcase_add_test(tc, sprintf_int_3);
  tcase_add_test(tc, sprintf_int_14);
  tcase_add_test(tc, sprintf_int_15);

  tcase_add_test(tc, sprintf_float_1);
  tcase_add_test(tc, sprintf_float_2);
  tcase_add_test(tc, sprintf_float_3);
  tcase_add_test(tc, sprintf_float_4);
  tcase_add_test(tc, sprintf_float_6);

  tcase_add_test(tc, sprintf_num_1);

  tcase_add_test(tc, sprintf_octal_1);
  tcase_add_test(tc, sprintf_octal_2);

  tcase_add_test(tc, sprintf_hex_1);
  tcase_add_test(tc, sprintf_hex_2);
  tcase_add_test(tc, sprintf_hex_3);

  tcase_add_test(tc, sprintf_g_1);
  tcase_add_test(tc, sprintf_g_2);

  tcase_add_test(tc, sprintf_sci_1);
  tcase_add_test(tc, sprintf_sci_2);

  tcase_add_test(tc, sprintf_pointer_1);

  tcase_add_test(tc, sscanf_c_1);
  tcase_add_test(tc, sscanf_c_2);
  tcase_add_test(tc, sscanf_c_3);
  tcase_add_test(tc, sscanf_c_4);
  tcase_add_test(tc, sscanf_c_5);
  tcase_add_test(tc, sscanf_c_6);
  tcase_add_test(tc, sscanf_c_7);

  tcase_add_test(tc, sscanf_d_1);
  tcase_add_test(tc, sscanf_d_2);
  tcase_add_test(tc, sscanf_d_4);
  tcase_add_test(tc, sscanf_d_5);
  tcase_add_test(tc, sscanf_d_6);
  tcase_add_test(tc, sscanf_d_7);
  tcase_add_test(tc, sscanf_d_8);
  tcase_add_test(tc, sscanf_d_9);
  tcase_add_test(tc, sscanf_d_10);

  tcase_add_test(tc, sscanf_s_1);
  tcase_add_test(tc, sscanf_s_2);
  tcase_add_test(tc, sscanf_s_3);
  tcase_add_test(tc, sscanf_s_4);
  tcase_add_test(tc, sscanf_s_5);
  tcase_add_test(tc, sscanf_s_6);

  tcase_add_test(tc, sscanf_f_1);
  tcase_add_test(tc, sscanf_f_2);
  tcase_add_test(tc, sscanf_f_3);
  tcase_add_test(tc, sscanf_f_4);
  tcase_add_test(tc, sscanf_f_5);
  tcase_add_test(tc, sscanf_f_6);
  tcase_add_test(tc, sscanf_f_7);
  tcase_add_test(tc, sscanf_f_8);
  tcase_add_test(tc, sscanf_f_9);

  tcase_add_test(tc, sscanf_i_1);
  tcase_add_test(tc, sscanf_i_2);
  tcase_add_test(tc, sscanf_i_3);
  tcase_add_test(tc, sscanf_i_4);
  tcase_add_test(tc, sscanf_i_5);
  tcase_add_test(tc, sscanf_i_6);
  tcase_add_test(tc, sscanf_i_7);

  tcase_add_test(tc, sscanf_o_1);
  tcase_add_test(tc, sscanf_o_2);
  tcase_add_test(tc, sscanf_o_3);
  tcase_add_test(tc, sscanf_o_4);

  tcase_add_test(tc, sscanf_x_1);
  tcase_add_test(tc, sscanf_x_2);
  tcase_add_test(tc, sscanf_x_3);
  tcase_add_test(tc, sscanf_x_4);

  tcase_add_test(tc, sscanf_u_1);
  tcase_add_test(tc, sscanf_u_2);
  tcase_add_test(tc, sscanf_u_3);
  tcase_add_test(tc, sscanf_u_4);

  tcase_add_test(tc, sscanf_p_1);
  tcase_add_test(tc, sscanf_p_2);

  tcase_add_test(tc, sscanf_n_1);

  tcase_add_test(tc, sscanf_e_1);
  tcase_add_test(tc, sscanf_e_2);
  tcase_add_test(tc, sscanf_e_3);
  tcase_add_test(tc, sscanf_e_4);

  tcase_add_test(tc, sscanf_pct_1);
  tcase_add_test(tc, sscanf_pct_2);

  tcase_add_test(tc, sscanf_default_1);

  tcase_add_test(tc, test_s21_to_upper_basic);
  tcase_add_test(tc, test_s21_to_upper_empty);
  tcase_add_test(tc, test_s21_to_upper_no_change);

  tcase_add_test(tc, test_s21_to_lower_basic);
  tcase_add_test(tc, test_s21_to_lower_empty);
  tcase_add_test(tc, test_s21_to_lower_no_change);

  tcase_add_test(tc, test_s21_insert_basic);
  tcase_add_test(tc, test_s21_insert_start);
  tcase_add_test(tc, test_s21_insert_end);

  tcase_add_test(tc, test_s21_trim_basic);
  tcase_add_test(tc, test_s21_trim_chars);
  tcase_add_test(tc, test_s21_trim_no_trim);

  suite_add_tcase(s, tc);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
