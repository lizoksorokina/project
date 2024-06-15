#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *str = S21_NULL;

  if (haystack && needle) str = (char *)haystack;
  if (haystack && needle && *needle) {
    char *need = (char *)needle;
    int match = 0;

    str = s21_strchr(str, need[0]);
    for (; str && match < (int)s21_strlen(need); match++) {
      if (str[match] != need[match]) {
        match = 0;
        str++;
        str = s21_strchr(str, need[0]);
      }
    }
  }

  return str;
}