#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest && src) {
    char *src_to_read = S21_NULL;
    src_to_read = (char *)src;
    unsigned long int i = 0;
    for (; i < n && src_to_read[i]; i++) dest[i] = src_to_read[i];
    dest[i] = '\0';
  }
  return dest;
}