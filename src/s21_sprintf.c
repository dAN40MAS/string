#include "s21_string.h"

void format_flags(char *buff, Flags f, bool is_unsigned) {
  char tmp[BUFF_SIZE] = {'\0'};

  if (f.plus && buff[0] != '-' && !is_unsigned) {
    tmp[0] = '+';
    s21_strcpy(tmp + 1, buff);
    s21_strcpy(buff, tmp);
  } else if (f.space && buff[0] != '-') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buff);
    s21_strcpy(buff, tmp);
  } else if (f.hash) {
    if (f.specifier == 'x' || f.specifier == 'X') {
      tmp[0] = '0';
      tmp[1] = f.specifier;
      s21_strcpy(tmp + 2, buff);
      s21_strcpy(buff, tmp);
    } else if (f.specifier == 'o') {
      tmp[0] = '0';
      s21_strcpy(tmp + 1, buff);
      s21_strcpy(buff, tmp);
    }
  }
}

void remove_trailing_zeroes(char *buff) {
  char *dot = s21_strchr(buff, '.');
  if (dot) {
    char *end = buff + s21_strlen(buff) - 1;
    while (end > dot && *end == '0') {
      *end = '\0';
      end--;
    }
    if (end == dot) *end = '\0';
  }
}

void format_precision(char *buff, Flags f) {
  int len = s21_strlen(buff);

  if (f.precision > len) {
    char tmp[BUFF_SIZE] = {'\0'};
    int pad = f.precision - len;
    s21_memset(tmp, '0', pad);
    s21_strcpy(tmp + pad, buff);
    s21_strcpy(buff, tmp);
  }

  if (f.is_precision_set && f.precision == 0 && buff[0] == '0') {
    buff[0] = '\0';
  }
}

void format_width(char *buff, Flags f) {
  int len = s21_strlen(buff);
  if (f.width > len) {
    char tmp[BUFF_SIZE] = {'\0'};
    int pad = f.width - len;

    if (f.minus) {
      s21_strcpy(tmp, buff);
      s21_memset(tmp + len, ' ', pad);
    } else {
      s21_memset(tmp, f.zero ? '0' : ' ', pad);
      s21_strcpy(tmp + pad, buff);
    }

    s21_strcpy(buff, tmp);
  }
}

void int_to_string(int64_t val, char *ret, int base, Flags f) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0;

  if (neg) val = -val;
  if (val == 0) {
    if ((f.precision > 0 && f.is_precision_set) ||
        (f.precision == 0 && !f.is_precision_set)) {
      tmp[idx--] = '0';
    }
  } else {
    while (val > 0) {
      tmp[idx--] = "0123456789abcdef"[val % base];
      val /= base;
    }
  }

  if (f.is_precision_set &&
      (s21_size_t)f.precision > s21_strlen(&tmp[idx + 1]) && f.precision > 0) {
    int pad = f.precision - s21_strlen(&tmp[idx + 1]);
    s21_memset(&tmp[idx - pad + 1], '0', pad);
    idx -= pad;
  }

  if (neg) tmp[idx--] = '-';

  s21_strcpy(ret, &tmp[idx + 1]);
  // format_precision(ret, f);
  format_flags(ret, f, false);
  format_width(ret, f);
}

void unsigned_to_string(uint64_t val, char *ret, int base,
                        bool is_big_base_note) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;

  if (val == 0) {
    tmp[idx--] = '0';
  } else {
    while (val > 0) {
      if (is_big_base_note) {
        tmp[idx--] = "0123456789ABCDEF"[val % base];
      } else {
        tmp[idx--] = "0123456789abcdef"[val % base];
      }

      val /= base;
    }
  }

  s21_strcpy(ret, &tmp[idx + 1]);
}

void double_to_string(long double val, char *ret, Flags f, bool is_sci,
                      bool is_big_sci_note) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0;

  int sci_counter = 0;

  if (neg) val = -val;
  long double int_part, frac_part;

  int_part = 0;
  frac_part = 0;

  long double *int_part_pointer = &int_part;

  if (f.precision == 0 && f.is_precision_set) {
    val = roundl(val);
  }
  if (!f.is_precision_set) {
    f.precision = 6;
    f.is_precision_set = true;
  }

  if (is_sci) {
    bool is_neg_science = false;
    bool is_pos_science = false;

    while (val > 10) {
      val /= 10;
      sci_counter++;
      is_pos_science = true;
    }

    while (val < 1) {
      val *= 10;
      sci_counter++;
      is_neg_science = true;
    }

    if (!is_neg_science) {
      is_pos_science = true;
    }

    for (int i = 0; i < 2; i++) {
      tmp[idx--] = "0123456789"[sci_counter % 10];
      sci_counter /= 10;
    }

    if (is_pos_science) {
      tmp[idx--] = '+';
    } else if (is_neg_science) {
      tmp[idx--] = '-';
    }

    if (is_big_sci_note) {
      tmp[idx--] = 'E';
    } else {
      tmp[idx--] = 'e';
    }
  }

  frac_part = modfl(val, int_part_pointer);

  int trail_zeroes_counter = 0;

  int j = 0;
  if (frac_part != 0) {
    while ((j < f.precision) || (j < 6 && !f.is_precision_set)) {
      frac_part *= 10;
      j++;

      if (frac_part < 1 && f.precision > 6) {
        trail_zeroes_counter++;
      }
    }
  }

  long long int frac_part_int = (long long int)roundl(frac_part);

  int start_idx = idx + 1;

  if (f.is_precision_set || frac_part != 0) {
    if (!f.is_precision_set) {
      while (tmp[start_idx] == '0' && start_idx < BUFF_SIZE - 1) {
        tmp[start_idx--] = '\0';
      }
    }

    for (int i = 0;
         i < f.precision || ((frac_part_int != 0 && !f.is_precision_set));
         i++) {
      tmp[idx--] = "0123456789"[frac_part_int % 10];
      frac_part_int /= 10;
    }

    while (trail_zeroes_counter != 0) {
      tmp[idx--] = '0';
      trail_zeroes_counter--;
    }

    if ((f.precision == 0 && !f.is_precision_set) ||
        (f.precision != 0 && f.is_precision_set)) {
      tmp[idx--] = '.';
    }
  }

  if (int_part == 0) {
    tmp[idx--] = '0';
  } else {
    while (int_part >= 1) {
      tmp[idx--] = "0123456789"[((int64_t)int_part) % 10];
      int_part /= 10;
    }
  }

  if (neg) tmp[idx--] = '-';

  s21_strcpy(ret, &tmp[idx + 1]);
  // format_flags(ret, f);
  // format_width(ret, f);
}

void format_integer(Flags f, char *buff, va_list va) {
  int64_t val = (f.length == 'l') ? va_arg(va, int64_t) : va_arg(va, int32_t);
  int_to_string(val, buff, 10, f);
}

void format_unsigned(Flags f, char *buff, va_list va, int base,
                     bool is_big_base_note) {
  uint64_t val =
      (f.length == 'l') ? va_arg(va, uint64_t) : va_arg(va, uint32_t);
  unsigned_to_string(val, buff, base, is_big_base_note);
  format_precision(buff, f);
  format_flags(buff, f, true);
  format_width(buff, f);
}

void format_pointer(char *buff, va_list va) {
  uintptr_t val = va_arg(va, uintptr_t);
  buff[0] = '0';
  buff[1] = 'x';
  unsigned_to_string(val, &buff[2], HEX, false);
}

void format_char(Flags f, char *buff, va_list va) {
  char c = (char)va_arg(va, int);
  buff[0] = c;
  buff[1] = '\0';
  format_width(buff, f);
}

void format_string(Flags f, char *buff, va_list va) {
  const char *str = va_arg(va, const char *);
  if (!str) str = "(null)";
  s21_strcpy(buff, str);
  if (f.is_precision_set) buff[f.precision] = '\0';
  format_width(buff, f);
}

void format_float(Flags f, char *buff, va_list va, bool is_sci,
                  bool is_big_sci_note) {
  long double val = 0.0;
  val = (f.length == 'L') ? va_arg(va, long double) : va_arg(va, double);
  double_to_string(val, buff, f, is_sci, is_big_sci_note);
  format_flags(buff, f, false);
  format_width(buff, f);
}

void format_gG_precision(char *buff, int precision) {
  int sig_digits = 0;
  bool non_zero_found = false;
  for (size_t i = 0; buff[i] != '\0'; i++) {
    if (buff[i] != '0' && buff[i] != '.') non_zero_found = true;
    if (non_zero_found && s21_isdigit(buff[i])) sig_digits++;
    if (sig_digits == precision) {
      if (buff[i + 1] == '.' || buff[i + 1] >= '5') buff[i]++;
      buff[i + 1] = '\0';
      break;
    }
  }
}

void format_scientific_notation(Flags f, char *buff, va_list va) {
  long double val =
      (f.length == 'L') ? va_arg(va, long double) : va_arg(va, double);
  int precision = f.is_precision_set ? f.precision : 6;
  double_to_string(val, buff, f, false, false);
  format_gG_precision(buff, precision);
  remove_trailing_zeroes(buff);
  format_flags(buff, f, false);
  format_width(buff, f);
}

void handle_specifier(Flags f, char *buff, va_list va) {
  switch (f.specifier) {
    case 'd':
    case 'i':
      format_integer(f, buff, va);
      break;
    case 'u':
      format_unsigned(f, buff, va, DECIMAL, false);
      break;
    case 'c':
      format_char(f, buff, va);
      break;
    case 's':
      format_string(f, buff, va);
      break;
    case 'f':
      format_float(f, buff, va, false, false);
      break;
    case 'x':
      format_unsigned(f, buff, va, HEX, false);
      break;
    case 'X':
      format_unsigned(f, buff, va, HEX, true);
      break;
    case 'o':
      format_unsigned(f, buff, va, OCTAL, false);
      break;
    case 'e':
      format_float(f, buff, va, true, false);
      break;
    case 'E':
      format_float(f, buff, va, true, true);
      break;
    case 'g':
    case 'G':
      format_scientific_notation(f, buff, va);
      break;
    case 'p':
      format_pointer(buff, va);
      break;
    case '%':
      buff[0] = '%';
      break;
    default:
      buff[0] = '\0';
      break;
  }
}

const char *parse_flags(const char *format, Flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#') {
    switch (*format) {
      case '-':
        f->minus = true;
        break;
      case '+':
        f->plus = true;
        break;
      case ' ':
        f->space = true;
        break;
      case '#':
        f->hash = true;
        break;
    }
    format++;
  }
  return format;
}

const char *parse_width(const char *format, Flags *f, va_list va) {
  if (*format == '*') {
    format++;
    f->width = va_arg(va, int);
    if (f->width < 0) {
      f->width = -f->width;
      f->minus = true;
    }
  } else if (s21_isdigit(*format)) {
    if (*format == '0') {
      f->zero = true;
    }
    f->width = atoi(format);
    while (s21_isdigit(*format)) format++;
  }
  return format;
}

const char *parse_precision(const char *format, Flags *f, va_list va) {
  if (*format == '.') {
    format++;
    f->is_precision_set = true;
    if (*format == '*') {
      format++;
      f->precision = va_arg(va, int);
    } else if (s21_isdigit(*format)) {
      f->precision = atoi(format);
      while (s21_isdigit(*format)) format++;
    }
  }
  return format;
}

const char *parse_length(const char *format, Flags *f) {
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    f->length = *format;
    format++;
  }
  return format;
}

bool is_all_zeroes(const char *buff) {
  while (*buff) {
    if (*buff != '0') return false;
    buff++;
  }
  return true;
}

void parse_format(const char **format, Flags *f, va_list va) {
  *format = parse_flags(*format, f);
  *format = parse_width(*format, f, va);
  *format = parse_precision(*format, f, va);
  *format = parse_length(*format, f);
  f->specifier = **format;
  (*format)++;
}

int s21_sprintf(char *str, const char *format, ...) {
  Flags f = {0};
  va_list va;
  va_start(va, format);
  const char *str_beginning = str;

  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;
      s21_memset(&f, 0, sizeof(Flags));

      parse_format(&format, &f, va);

      char buff[BUFF_SIZE] = {'\0'};
      handle_specifier(f, buff, va);

      s21_strcpy(str, buff);
      str += s21_strlen(buff);

      if (f.specifier == 'n') {
        int *ret = va_arg(va, int *);
        *ret = str - str_beginning;
      }
    }
  }

  *str = '\0';
  va_end(va);
  return str - str_beginning;
}