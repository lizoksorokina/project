#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  unsigned char *str_copy = S21_NULL;
  if (str && !c) {
    str_copy = (unsigned char *)str;
    str_copy = &str_copy[s21_strlen(str)];
  }

  if (str && c) {
    str_copy = (unsigned char *)str;
    int match = 0;
    for (int i = 0; str_copy[i] && match == 0; i++) {
      if (str[i] == c) {
        str_copy = &str_copy[i];
        match = 1;
      }
    }
    if (match == 0) str_copy = S21_NULL;
  }
  return (char *)str_copy;
}