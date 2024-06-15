#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *str_copy = S21_NULL;
  if (str != NULL) {
    str_copy = (unsigned char *)str;
    for (unsigned long int i = 0; i < n; i++) {
      str_copy[i] = c;
    }
    // memset перезаписывает '\0', если n == strlen + 1
  }
  return str_copy;
}
