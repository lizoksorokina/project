#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest != NULL && src != NULL && n != 0) {
    unsigned long int len = s21_strlen(dest), i = 0;
    for (; i < n && src; i++) {
      dest[len + i] = src[i];
    }
    dest[len + i] = '\0';
  }
  return dest;
}