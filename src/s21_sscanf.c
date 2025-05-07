#include "s21_string.h"

void assign_float(va_list args, int long_long_flag, char *num_convert,
                  int *neg_num_flag, int science_delim, int sci_neg_flag,
                  int long_flag, int sci_flag) {
  if (long_long_flag) {
    long double x = strtold(num_convert, S21_NULL);

    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }

    long double *arg_ptr = va_arg(args, long double *);
    if (sci_neg_flag && sci_flag) {
      x *= pow(10, -science_delim);
      sci_neg_flag = 0;
    } else if (sci_flag) {
      x *= pow(10, science_delim);
    }

    *arg_ptr = x;
  }

  if (!long_flag && !long_long_flag) {
    float x = strtof(num_convert, NULL);

    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }

    float *arg_ptr = va_arg(args, float *);
    if (sci_neg_flag && sci_flag) {
      x *= pow(10, -science_delim);
      sci_neg_flag = 0;
    } else if (sci_flag) {
      x *= pow(10, science_delim);
    }

    *arg_ptr = x;
  } else if (long_flag && !long_long_flag) {
    double x = strtod(num_convert, NULL);

    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }

    double *arg_ptr = va_arg(args, double *);
    if (sci_neg_flag && sci_flag) {
      x *= pow(10, -science_delim);
      sci_neg_flag = 0;
    } else if (sci_flag) {
      x *= pow(10, science_delim);
    }

    *arg_ptr = x;
  }
}

void assign_int(va_list args, int *neg_num_flag, int *long_flag,
                int *short_flag, char *num_convert, int *long_long_flag) {
  if (*short_flag) {
    short int x = strtol(num_convert, S21_NULL, 10);
    short int *arg_ptr = va_arg(args, short int *);
    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }
    *arg_ptr = x;
  }

  if (*long_flag == 0 && !*long_long_flag && !*short_flag) {
    int x = strtol(num_convert, S21_NULL, 10);
    int *arg_ptr = va_arg(args, int *);
    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }
    *arg_ptr = x;
  }
  if (*long_flag) {
    long int x = strtol(num_convert, S21_NULL, 10);
    long int *arg_ptr = va_arg(args, long int *);
    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }
    *arg_ptr = x;
  }
  if (*long_long_flag) {
    long long int x = strtol(num_convert, S21_NULL, 10);
    long long int *arg_ptr = va_arg(args, long long int *);
    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }
    *arg_ptr = x;
  }
}

void assign_unsigned_int(va_list args, int *neg_num_flag, int *long_flag,
                         int *short_flag, char *output_string, int num_system) {
  if (*short_flag) {
    short int x = strtoul(output_string, S21_NULL, num_system);

    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }

    unsigned short int *arg_ptr = va_arg(args, unsigned short int *);
    *arg_ptr = x;
  }

  else if (*long_flag == 0) {
    int x = strtoul(output_string, S21_NULL, num_system);
    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }

    unsigned int *arg_ptr = va_arg(args, unsigned int *);
    *arg_ptr = x;
  } else if (*long_flag) {
    long long int x = strtoll(output_string, S21_NULL, num_system);

    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }
    int changed = 0;
    if (x == 9223372036854775807) {
      x = x * -1 - 1;
      changed = 1;
    }
    if (x == -9223372036854775807 && !changed) {
      x = 9223372036854775807;
    }

    long long int *arg_ptr = va_arg(args, long long int *);
    *arg_ptr = x;
  }
}

void assign_unsigned_i(va_list args, int *neg_num_flag, int *long_flag,
                       int *short_flag, char *output_string, int num_system) {
  if (*short_flag) {
    short int x = strtoul(output_string, S21_NULL, num_system);

    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }

    unsigned short int *arg_ptr = va_arg(args, unsigned short int *);
    *arg_ptr = x;
  }

  else if (*long_flag == 0) {
    int x = strtoul(output_string, S21_NULL, num_system);
    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }

    unsigned int *arg_ptr = va_arg(args, unsigned int *);
    *arg_ptr = x;
  } else if (*long_flag) {
    long long int x = strtoll(output_string, S21_NULL, num_system);

    if (*neg_num_flag) {
      x *= -1;
      *neg_num_flag = 0;
    }
    int changed = 0;
    if (x == 9223372036854775807 && num_system == OCTAL) {
      x = x * -1 - 1;
      changed = 1;
    }
    if (x == -9223372036854775807 && !changed) {
      x = 9223372036854775807;
    }

    long long int *arg_ptr = va_arg(args, long long int *);
    *arg_ptr = x;
  }
}

int is_num_my(char x) {
  if (x >= '0' && x <= '9') {
    return 1;
  }

  return 0;
}

void s21_flag_c(char **str, va_list args, int *num_of_succsess, int *supress,
                int *width, int *long_flag, int *long_long_flag) {
  char *tmp = *str;
  int i = 0;

  if (!*supress) {
    if (*long_flag || *long_long_flag) {
      wchar_t *c = (wchar_t *)va_arg(args, wchar_t *);
      while (i < *width && (*width != 0)) {
        c[i] = (wchar_t)*tmp;
        tmp++;
        i++;
      }
      if (*width == 0) {
        *c = (wchar_t)*tmp;
        tmp++;
      }
      *str = tmp;
      (*num_of_succsess)++;
    } else {
      char *c = (char *)va_arg(args, char *);
      while (i < *width && (*width != 0)) {
        c[i] = *tmp;
        tmp++;
        i++;
      }
      if (*width == 0) {
        *c = *tmp;
        tmp++;
      }
      *str = tmp;
      (*num_of_succsess)++;
    }

  } else {
    *supress = 0;
    while (i < *width && (*width != 0)) {
      tmp++;
    }
    if (*width == 0) {
      tmp++;
    }
    *str = tmp;
  }
}

void s21_flag_e(char **cpy_str, va_list args, int *neg_num_flag,
                int science_delim, int sci_neg_flag, int *num_of_succsess,
                char *num_convert, int *long_flag, int *long_long_flag,
                int *width, int *supress, int *americanish_format) {
  char *tmp = *cpy_str;
  int i = 1;

  if ((*neg_num_flag == 0 && *width != 0)) {
    *width += 1;
  }

  while (is_num_my(*tmp) ||
         ((*tmp == '.' && is_num_my(*(tmp + 1))) && (i < *width || !*width))) {
    num_convert[i - 1] = *tmp;
    i++;
    tmp++;
  }

  num_convert[i - 1] = '\0';
  if (*tmp == 'e' || *tmp == 'E') {
    tmp++;

    if (*tmp == '+') {
      tmp++;
    }

    if (*tmp == '-') {
      sci_neg_flag = 1;
      tmp++;
      science_delim = *tmp - 48;
    } else if (is_num_my(*tmp)) {
      science_delim = *tmp - 48;
    }
    if (*americanish_format) {
      *americanish_format = 0;
      science_delim += 1;
    }
  }

  if (*supress) {
    *num_of_succsess = *num_of_succsess - 1;
    *supress = 0;
  } else if (*num_convert != '\0') {
    assign_float(args, *long_long_flag, num_convert, neg_num_flag,
                 science_delim, sci_neg_flag, *long_flag, 1);
  }

  (*num_of_succsess)++;
  tmp++;
  *cpy_str = tmp;
}

void s21_flag_d(char **cpy_str, int *num_of_succsess, va_list args,
                char *num_convert, int *neg_num_flag, int *long_flag,
                int *short_flag, int *width, int *supress,
                int *long_long_flag) {
  char *tmp = *cpy_str;
  int i = 1;

  if (*neg_num_flag == 0 && *width != 0) {
    *width += 1;
  }

  while (is_num_my(*tmp) && (i < *width || !*width)) {
    num_convert[i - 1] = *tmp;
    tmp++;
    i++;
  }
  num_convert[i - 1] = '\0';
  if (*supress) {
    *supress = 0;
  } else if (num_convert[0] != '\0') {
    assign_int(args, neg_num_flag, long_flag, short_flag, num_convert,
               long_long_flag);
    (*num_of_succsess)++;
  }

  *cpy_str = tmp;
}

void s21_flag_u(char **cpy_str, int *num_of_succsess, va_list args,
                char *num_convert, int *long_flag, int *short_flag, int *width,
                int *supress, int *neg_num_flag) {
  char *tmp = *cpy_str;
  int i = 1;
  int num_is_written = 0;
  while (is_num_my(*tmp) && (i < *width || !*width)) {
    num_convert[i - 1] = *tmp;
    i++;
    tmp++;
    num_is_written = 1;
  }

  num_convert[i - 1] = '\0';

  if (*supress) {
    *supress = 0;
  } else {
    if (num_is_written) {
      (*num_of_succsess)++;
    }
    assign_unsigned_int(args, neg_num_flag, long_flag, short_flag, num_convert,
                        DECIMAL);
  }

  *cpy_str = tmp;
}

void s21_flag_o(char **cpy_str, int *num_of_succsess, va_list args,
                char *num_convert, int *long_flag, int *short_flag, int *width,
                int *supress, int *neg_num_flag) {
  char *tmp = *cpy_str;
  int i = 1;
  if (*tmp == '0') {
    tmp++;
    if (*width != 0 && *width != 1) {
      *width -= 1;
    }
  }

  int num_is_written = 0;
  while (is_num_my(*tmp) && (i < *width || !*width)) {
    num_convert[i - 1] = *tmp;
    i++;
    tmp++;
    num_is_written = 1;
  }

  num_convert[i - 1] = '\0';

  if (*supress) {
    *supress = 0;
  } else {
    assign_unsigned_int(args, neg_num_flag, long_flag, short_flag, num_convert,
                        OCTAL);
    if (num_is_written) {
      (*num_of_succsess)++;
    }
  }

  *cpy_str = tmp;
}

void s21_flag_x(char **cpy_str, va_list args, int *num_of_succsess,
                int *neg_num_flag, int *long_flag, int *short_flag, int *width,
                int *supress) {
  char *tmp = *cpy_str;
  int i = 0;
  char output_string[STRLEN] = {'\0'};
  if (*tmp == '0' && tmp[1] == 'x') {
    tmp++;
    tmp++;
    if (*width != 0 && *width != 2) {
      *width -= 2;
    }
  }

  int num_is_written = 0;
  while (*tmp != ' ' && *tmp != '\0' &&
         ((*tmp >= '0' && *tmp <= '9') || (*tmp >= 'a' && *tmp <= 'f') ||
          (*tmp >= 'A' && *tmp <= 'F') || (*tmp == 'x')) &&
         (i < *width || !*width)) {
    output_string[i] = *tmp;
    tmp++;
    i++;
    num_is_written = 1;
  }

  output_string[i] = '\0';

  if (*supress) {
    *supress = 0;
  } else {
    if (num_is_written) {
      (*num_of_succsess)++;
    }
    assign_unsigned_int(args, neg_num_flag, long_flag, short_flag,
                        output_string, HEX);
  }

  *cpy_str = tmp;
}

void s21_flag_p(char **cpy_str, va_list args, int *num_of_succsess, int *width,
                int *supress) {
  char *tmp = *cpy_str;
  int i = 0;
  char output_string[STRLEN] = {'\0'};
  int num_is_written = 0;
  while (*tmp != ' ' && *tmp != '\0' &&
         ((*tmp >= '0' && *tmp <= '9') || (*tmp >= 'a' && *tmp <= 'f') ||
          (*tmp >= 'A' && *tmp <= 'F') || (*tmp == 'x')) &&
         (i < *width || !*width)) {
    output_string[i] = *tmp;
    tmp++;
    i++;
    num_is_written = 1;
  }

  output_string[i] = '\0';

  long int x = strtol(output_string, S21_NULL, 16);

  if (*supress) {
    *supress = 0;
  } else {
    long int *arg_ptr = va_arg(args, long int *);
    *arg_ptr = x;
    if (num_is_written) {
      (*num_of_succsess)++;
    }
  }

  *cpy_str = tmp;
}

void s21_flag_f(char **cpy_str, int *num_of_succsess, va_list args,
                char *num_convert, int *neg_num_flag, int *long_flag,
                int *long_long_flag, int *width, int *supress) {
  char *tmp = *cpy_str;
  int i = 1;

  if (*neg_num_flag == 0 && *width != 0) {
    *width += 1;
  }

  while ((is_num_my(*tmp) || (*tmp == '.' && is_num_my(*(tmp + 1)))) &&
         (i < *width || !*width)) {
    num_convert[i - 1] = *tmp;
    i++;
    tmp++;
  }

  num_convert[i - 1] = '\0';

  if (*supress) {
    *supress = 0;
  } else {
    (*num_of_succsess)++;
    assign_float(args, *long_long_flag, num_convert, neg_num_flag, 0, 0,
                 *long_flag, 0);
  }

  *cpy_str = tmp;
}

void s21_flag_i(char **cpy_str, int *num_of_succsess, va_list args,
                char *num_convert, int *neg_num_flag, int *long_flag,
                int *short_flag, int *width, int *supress) {
  int octal_flag = 0;
  int hex_flag = 0;

  char *tmp = *cpy_str;
  int i = 1;

  if ((*neg_num_flag == 0 && *width != 0)) {
    *width += 1;
  }

  if (*tmp == '0' && tmp[1] == 'x') {
    hex_flag = 1;
    tmp++;
    tmp++;
    if (*width != 0 && *width != 2) {
      *width -= 2;
    }
  }
  if (*tmp == '0') {
    tmp++;
    octal_flag = 1;
    if (*width != 0 && *width != 1) {
      *width -= 1;
    }
  }

  if (octal_flag) {
    while ((*tmp >= '0' && *tmp <= '7') && (i < *width || !*width)) {
      num_convert[i - 1] = *tmp;
      i++;
      tmp++;
    }
    if (!*supress) {
      (*num_of_succsess)++;
      assign_unsigned_int(args, neg_num_flag, long_flag, short_flag,
                          num_convert, OCTAL);
    } else {
      *supress = 0;
    }
  }
  if (hex_flag) {
    while (((*tmp >= '0' && *tmp <= '9') || (*tmp >= 'a' && *tmp <= 'f') ||
            (*tmp >= 'A' && *tmp <= 'F')) &&
           (i < *width || !*width)) {
      num_convert[i - 1] = *tmp;
      i++;
      tmp++;
    }
    if (!*supress) {
      (*num_of_succsess)++;
      assign_unsigned_i(args, neg_num_flag, long_flag, short_flag, num_convert,
                        HEX);
    } else {
      *supress = 0;
    }
  }

  else if (!octal_flag && !hex_flag) {
    while ((*tmp >= '0' && *tmp <= '9') && (i < *width || !*width)) {
      num_convert[i - 1] = *tmp;
      i++;
      tmp++;
    }
    if (!*supress) {
      (*num_of_succsess)++;
      assign_unsigned_int(args, neg_num_flag, long_flag, short_flag,
                          num_convert, DECIMAL);
    } else {
      *supress = 0;
    }
  }

  *cpy_str = tmp;
}

int check_inf(char **str) {
  int result = 0;
  if (tolower(**str) == 'i') {
    if (tolower((*str)[1]) == 'n')
      if (tolower((*str)[2]) == 'f') {
        result = 1;
        (*str) += 3;
      }
  }
  return result;
}

int check_nan(char **str) {
  int result = 0;
  if (tolower(**str) == 'n') {
    if (tolower((*str)[1]) == 'a')
      if (tolower((*str)[2]) == 'n') {
        result = 1;
        (*str) += 3;
      }
  }
  return result;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int flag_found = 0;
  const char *start = str;

  char *cpy_str = (char *)str;

  int neg_num_flag = 0;

  int science_delim = 0;
  int sci_neg_flag = 0;
  int americanish_format = 0;

  int num_of_succsess = 0;

  int long_flag = 0;
  int short_flag = 0;
  int long_long_flag = 0;

  int width_size = 0;
  int width_convert_index = 1;

  int write_suppress = 0;

  int no_errors = 1;

  if (format == S21_NULL) {
    no_errors = 0;
    num_of_succsess = -1;
  }
  if (*cpy_str == '\0') {
    num_of_succsess = -1;
  }
  while (*cpy_str && format != S21_NULL && *format && no_errors) {
    neg_num_flag = 0;
    while (*format == ' ') {
      format++;
    }

    while (*cpy_str > 0 && *cpy_str <= 32) {
      cpy_str++;
    }
    flag_found = 0;
    if (*format == '%') {
      flag_found = 1;
      format++;

      long_flag = 0;
      short_flag = 0;
      long_long_flag = 0;

      if (*format == '*') {
        write_suppress = 1;
        format++;
      }

      char width_num[STRLEN] = {'\0'};
      width_convert_index = 1;

      while (is_num_my(*format)) {
        width_num[width_convert_index - 1] = *format;
        width_convert_index++;
        format++;
      }

      width_size = strtol(width_num, NULL, 10);

      if (*format == 'l') {
        long_flag = 1;
        format++;
        if (*format == 'l') {
          format++;
        }

      } else if (*format == 'h') {
        short_flag = 1;
        format++;
      } else if (*format == 'L') {
        long_long_flag = 1;
        format++;
      }
    }
    if (flag_found == 1) {
      char num_convert[STRLEN] = {'\0'};
      switch (*format) {
        case 'c':
          s21_flag_c(&cpy_str, args, &num_of_succsess, &write_suppress,
                     &width_size, &long_flag, &long_long_flag);
          break;
        case 'n':
          *va_arg(args, int *) = (int)(cpy_str - start);
          break;
        case 'e':
        case 'E':
          while (*cpy_str == ' ') {
            cpy_str++;
          }
          if (*cpy_str == '-') {
            neg_num_flag = 1;
            cpy_str++;
          }
          if (*cpy_str == '+') {
            cpy_str++;
          }
          if (*cpy_str == '.') {
            cpy_str++;
            americanish_format = 1;
          }
          if (is_num_my(*cpy_str)) {
            s21_flag_e(&cpy_str, args, &neg_num_flag, science_delim,
                       sci_neg_flag, &num_of_succsess, num_convert, &long_flag,
                       &long_long_flag, &width_size, &write_suppress,
                       &americanish_format);
          } else {
            format++;
            continue;
          }
          break;
        case 'd':
          if (*cpy_str == '-') {
            neg_num_flag = 1;
            cpy_str++;
          }
          if (*cpy_str == '+') {
            if (width_size != 0) {
              width_size--;
            }
            cpy_str++;
          }
          if (is_num_my(*cpy_str)) {
            s21_flag_d(&cpy_str, &num_of_succsess, args, num_convert,
                       &neg_num_flag, &long_flag, &short_flag, &width_size,
                       &write_suppress, &long_long_flag);
          } else {
            format++;
            continue;
          }
          break;
        case 'f':
        case 'g':
        case 'G':
          while (*cpy_str == ' ') {
            cpy_str++;
          }
          if (*cpy_str == '+') {
            cpy_str++;
          }
          if (*cpy_str == '-') {
            neg_num_flag = 1;
            cpy_str++;
          }
          if (is_num_my(*cpy_str)) {
            s21_flag_f(&cpy_str, &num_of_succsess, args, num_convert,
                       &neg_num_flag, &long_flag, &long_long_flag, &width_size,
                       &write_suppress);
          } else if (check_nan(&cpy_str) == 1) {
            if (!write_suppress) {
              float *arg_ptr = va_arg(args, float *);
              *arg_ptr = NAN;
              num_of_succsess++;
            } else {
              write_suppress = 0;
            }
          } else if (check_inf(&cpy_str) == 1) {
            if (!write_suppress) {
              float *arg_ptr = va_arg(args, float *);
              *arg_ptr = neg_num_flag ? -1 * INFINITY : INFINITY;
              num_of_succsess++;
            } else {
              write_suppress = 0;
            }
          } else {
            format++;
            continue;
          }
          break;
        case 's':
          int i = 0;
          if (!write_suppress) {
            if (long_flag || long_long_flag) {
              wchar_t *arg_ptr = va_arg(args, wchar_t *);

              while (*cpy_str != ' ' && *cpy_str != '\0' && *cpy_str != '\n' &&
                     *cpy_str != '\t' && (i < width_size || !width_size)) {
                arg_ptr[i] = (wchar_t)*cpy_str;
                cpy_str++;
                i++;
              }
              num_of_succsess++;

            } else {
              char *arg_ptr = va_arg(args, char *);

              while (*cpy_str != ' ' && *cpy_str != '\0' && *cpy_str != '\n' &&
                     *cpy_str != '\t' && (i < width_size || !width_size)) {
                arg_ptr[i] = *cpy_str;
                cpy_str++;
                i++;
              }
              num_of_succsess++;
            }

          } else {
            while (*cpy_str != ' ' && *cpy_str != '\0' && *cpy_str != '\n' &&
                   *cpy_str != '\t' && (i < width_size || !width_size)) {
              cpy_str++;
              i++;
            }
            write_suppress = 0;
          }

          break;
        case 'p':
          s21_flag_p(&cpy_str, args, &num_of_succsess, &width_size,
                     &write_suppress);
          break;
        case 'x':
        case 'X':
          if (*cpy_str == '+') {
            cpy_str++;
            if (width_size != 0) {
              width_size--;
            }
          }
          if (*cpy_str == '-') {
            neg_num_flag = 1;
            cpy_str++;
            if (width_size != 0) {
              width_size--;
            }
          }
          s21_flag_x(&cpy_str, args, &num_of_succsess, &neg_num_flag,
                     &long_flag, &short_flag, &width_size, &write_suppress);
          break;
        case 'u':
          if (*cpy_str == '+') {
            cpy_str++;
          }
          if (*cpy_str == '-') {
            neg_num_flag = 1;
            cpy_str++;
          }
          s21_flag_u(&cpy_str, &num_of_succsess, args, num_convert, &long_flag,
                     &short_flag, &width_size, &write_suppress, &neg_num_flag);
          break;
        case 'o':
          if (*cpy_str == '+') {
            cpy_str++;
          }
          if (*cpy_str == '-') {
            neg_num_flag = 1;
            cpy_str++;
          }
          s21_flag_o(&cpy_str, &num_of_succsess, args, num_convert, &long_flag,
                     &short_flag, &width_size, &write_suppress, &neg_num_flag);
          break;
        case 'i':
          if (*cpy_str == '-') {
            neg_num_flag = 1;
            cpy_str++;
          }
          if (*cpy_str == '+') {
            cpy_str++;
          }
          if (is_num_my(*cpy_str)) {
            s21_flag_i(&cpy_str, &num_of_succsess, args, num_convert,
                       &neg_num_flag, &long_flag, &short_flag, &width_size,
                       &write_suppress);
          } else {
            format++;
            continue;
          }
          break;
        default:
          break;
      }
      format++;
    } else {
      if (*format != *cpy_str) {
        no_errors = 0;
      } else {
        format++;
        cpy_str++;
      }
    }
  }

  va_end(args);

  return num_of_succsess;
}
