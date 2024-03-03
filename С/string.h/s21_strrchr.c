#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *str_copy = S21_NULL;
  int match = 0;

  if (str) {
    str_copy = (char *)str;

    for (int i = s21_strlen(str_copy); i >= 0 && !match; i--) {
      if (str[i] == c) {
        str_copy = &str_copy[i];
        match = 1;
      }
    }
  }

  if (match == 0) str_copy = S21_NULL;
  return str_copy;
}