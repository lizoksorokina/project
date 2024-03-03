#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  if (str1 && str2) {
    int match = 0, i = 0;
    char *str1_copy = (char *)str1, *str2_copy = (char *)str2;

    for (; str1_copy[i] && match == 0; i++) {
      for (int j = 0; str2_copy[j] && match == 0; j++) {
        if (str1_copy[i] == str2_copy[j]) {
          len = (s21_size_t)i;
          match = 1;
        }
      }
    }

    if (match == 0) len = i;
  }
  return len;
}