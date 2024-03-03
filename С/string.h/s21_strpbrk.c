#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *str1_copy = s21_NULL, *str2_copy = s21_NULL;
  int match = 0;

  if (str1 && str2) {
    str1_copy = (char *)str1, str2_copy = (char *)str2;

    for (int i = 0; str1_copy[i] && !match; i++) {
      for (int j = 0; str2_copy[j] && !match; j++) {
        if (str1_copy[i] == str2_copy[j]) {
          str1_copy = &str1_copy[i];

          match = 1;
        }
      }
    }
  }

  if (match == 0) str1_copy = s21_NULL;
  return str1_copy;
}