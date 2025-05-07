#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *r = dest;
  while (*src) {
    *(dest++) = *(src++);
  }

  *dest = '\0';

  return r;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  s21_size_t i = 0;
  while (i != n) {
    if (*((char *)str + i) == c) {
      return (char *)str + i;
    }
    i++;
  }

  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr1 = (const unsigned char *)str1;
  const unsigned char *ptr2 = (const unsigned char *)str2;

  s21_size_t i = 0;
  while (i != n) {
    if (ptr1[i] > ptr2[i]) {
      return 1;
    } else if (ptr1[i] < ptr2[i]) {
      return -1;
    }
    i++;
  }

  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ptr1 = (unsigned char *)dest;
  const unsigned char *ptr2 = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    ptr1[i] = ptr2[i];
  }

  return dest;
}

void *s21_memset(void *s, int c, s21_size_t n) {
  unsigned char *p = s;

  for (s21_size_t i = 0; i < n; i++) {
    p[i] = c;
  }

  return s;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *p = dest;
  while (*p) {
    p++;
  }

  while (*src && n) {
    *p = *src;
    p++;
    src++;
    n--;
  }
  *p = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  while (*str != c && *str != '\0') {
    str++;
  }

  if (*str != c) {
    str = S21_NULL;
  }

  return (char *)str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;
  int flag = 0;
  while (i < n && (str1[i] != '\0' || str2[i] != '\0')) {
    if (str1[i] > str2[i]) {
      flag = 1;
      break;
    } else if (str1[i] < str2[i]) {
      flag = -1;
      break;
    }
    i++;
  }

  return flag;
}

char *s21_strncpy(char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;

  while (i < n && str2[i] != '\0') {
    str1[i] = str2[i];
    i++;
  }
  str1[i] = '\0';

  return str1;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i, j;

  for (i = 0; str1[i] != '\0'; i++) {
    for (j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return i;
      }
    }
  }

  return i;
}

char *s21_strerror(int errnum) {
  char *err[] = ERROR;
  static char resNum[70];
  int max = 133;
  if (*err[0] == 'U') {
    max = 107;
  }
  if (errnum > 0 && errnum <= max) {
    s21_strcpy(resNum, err[errnum]);
  } else {
    char num[10] = {0};
    if (errnum < 0) {
      num[0] = '-';
      errnum *= -1;
    }
    s21_strcpy(resNum, "Unknown error ");
    int i;
    for (i = 8; errnum != 0; errnum /= 10, i--) {
      num[i] = errnum % 10 + '0';
    }
    if (num[0] == '-') {
      resNum[15] = '-';
      resNum[16] = '\0';
    }
    s21_strncat(resNum, num + i + 1, s21_strlen(resNum));
  }
  return resNum;
}

s21_size_t s21_strlen(const char *str) {
  int count = 0;
  while (*str++ != '\0') {
    count++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  int len1 = s21_strlen(str1);
  int len2 = s21_strlen(str2);
  char *index = S21_NULL;
  for (int i = 0; i < len1; i++) {
    if (index != S21_NULL) {
      break;
    }
    for (int j = 0; j < len2; j++) {
      if (*(str1 + i) == *(str2 + j)) {
        index = (char *)(str1 + i);
      }
    }
  }
  return index;
}

char *s21_strrchr(const char *str, int c) {
  const char *p = S21_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      p = str;
    }
    str++;
  }

  return (char *)p;
}

char *s21_strstr(const char *haystack, const char *needle) {
  const char *p = haystack;
  s21_size_t len = s21_strlen(needle);
  char *result = S21_NULL;

  if (len == 0) {
    result = (char *)haystack;
  } else {
    while ((p = s21_strchr(p, *needle)) != S21_NULL) {
      if (s21_strncmp(p, needle, len) == 0) {
        result = (char *)p;
        break;
      }
      p++;
    }
  }

  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *static_str = S21_NULL;
  char *token = S21_NULL;

  if (str != S21_NULL) {
    static_str = str;
  }

  if (static_str != S21_NULL) {
    while (*static_str && s21_strchr(delim, *static_str)) {
      static_str++;
    }

    if (*static_str != '\0') {
      token = static_str;

      while (*static_str && !s21_strchr(delim, *static_str)) {
        static_str++;
      }

      if (*static_str != '\0') {
        *static_str = '\0';
        static_str++;
      } else {
        static_str = S21_NULL;
      }
    } else {
      static_str = S21_NULL;
    }
  }

  return token;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *d = dest;
  const char *s = src;

  if (d < s) {
    while (n--) *d++ = *s++;
  } else {
    const char *last_s = s + (n - 1);
    char *last_d = d + (n - 1);
    while (n--) *last_d-- = *last_s--;
  }

  return dest;
}

int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }

void *s21_to_upper(const char *str) {
  char *newString;

  if (str == S21_NULL) {
    newString = S21_NULL;
  } else {
    newString = calloc(1, s21_strlen(str) + 1);
    for (s21_size_t n = 0; str[n] != '\0'; n++) {
      if (str[n] >= 'a' && str[n] <= 'z') {
        newString[n] = str[n] - 32;
      } else {
        newString[n] = str[n];
      }
    }
  }

  return newString;
}

void *s21_to_lower(const char *str) {
  char *newString;

  if (str == S21_NULL) {
    newString = S21_NULL;
  } else {
    newString = calloc(1, s21_strlen(str) + 1);
    for (s21_size_t n = 0; str[n] != '\0'; n++) {
      if (str[n] >= 'A' && str[n] <= 'Z') {
        newString[n] = str[n] + 32;
      } else {
        newString[n] = str[n];
      }
    }
  }

  return newString;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t len;
  char *dest;
  if (src == S21_NULL || str == S21_NULL) {
    dest = S21_NULL;
  } else if (start_index > s21_strlen(src)) {
    dest = S21_NULL;
  } else {
    len = s21_strlen(src) + s21_strlen(str);
    dest = calloc(len + 1, 1);
    s21_strncpy(dest, src, start_index);
    s21_strncat(dest, str, len);
    s21_strncat(dest, src + start_index, len);
  }

  return dest;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) {
    return S21_NULL;
  }

  int length = 0;
  while (src[length] != '\0') {
    length++;
  }

  int start = 0;
  while (start < length) {
    int found = 0;
    for (int i = 0; trim_chars[i] != '\0'; i++) {
      if (src[start] == trim_chars[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      break;
    }
    start++;
  }

  int end = length - 1;
  while (end >= start) {
    int found = 0;
    for (int i = 0; trim_chars[i] != '\0'; i++) {
      if (src[end] == trim_chars[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      break;
    }
    end--;
  }

  int new_length = end - start + 1;

  char *newString = (char *)malloc((new_length + 1) * sizeof(char));
  if (newString == S21_NULL) {
    return S21_NULL;
  }

  for (int i = 0; i < new_length; i++) {
    newString[i] = src[start + i];
  }
  newString[new_length] = '\0';

  return newString;
}
