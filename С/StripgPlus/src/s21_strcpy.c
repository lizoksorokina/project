#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  // dest – указатель на строку, в которую будут скопированы данные.
  // srс – указатель на строку источник копируемых данных.
  int n = s21_strlen(src);
  for (int i = 0; i <= n + 1; i++) {
    dest[i] = src[i];
  }
  return dest;
}

#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  // dest – указатель на строку в которую будут скопированы данные.
  // src – указатель на строку источник копируемых данных.
  // n – ограничение длинны копирования
  s21_memset(dest, '\0', n);

  for (s21_size_t i = 0; i < n && src[i]; i++) {
    dest[i] = src[i];
  }

  return dest;
}