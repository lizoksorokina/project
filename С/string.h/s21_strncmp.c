#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int match = 0;

  if (str1 && str2 && n) {
    char *str1_copy = (char *)str1, *str2_copy = (char *)str2;
    for (unsigned long int i = 0; i < n && match == 0; i++) {
      match = str1_copy[i] - str2_copy[i];
    }
  }

  return match;
}