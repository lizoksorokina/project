#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *str_copy = S21_NULL;

  if (src && str) {
    long unsigned int len = s21_strlen(src);

    if (start_index <= len) {
      len += s21_strlen(str);
      str_copy = malloc(len + 1);

      long unsigned int cur_index = 0;
      for (; cur_index < start_index; src++) str_copy[cur_index++] = *src;
      for (; *str; str++) str_copy[cur_index++] = *str;
      for (; *src; src++) str_copy[cur_index++] = *src;

      str_copy[len] = '\0';
    }
  }
  return str_copy;
}