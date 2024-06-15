#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *str_copy = S21_NULL;
  if (str) {
    int len = s21_strlen(str);
    str_copy = malloc(len + 1);

    for (int len = 0; *(str + len); len++) {
      int symb = *(str + len);
      if (symb >= 65 && symb <= 90)
        str_copy[len] = symb + 32;
      else
        str_copy[len] = symb;
    }
    str_copy[len] = '\0';
  }
  return str_copy;
}
