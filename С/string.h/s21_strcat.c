#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  // dest – указатель на массив в который будет добавлена строка.
  // src – указатель на массив из которого будет скопирована строка.
  int c = 0;
  size_t sc;

  while (dest[c] != 0) {
    c++;
  }

  for (sc = 0; sc < s21_strlen(src); sc++) {
    dest[sc + c] = src[sc];
  }

  dest[sc + c] = 0;

  return dest;
}
