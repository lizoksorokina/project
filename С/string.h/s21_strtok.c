#include "s21_string.h"

unsigned int is_delim(char c, const char *delim) {
  while (*delim != '\0') {
    if (c == *delim) return 1;
    delim++;
  }
  return 0;
}
char *s21_strtok(char *str, const char *delim) {
  // str – указатель на разбиваемую строку.
  // delim – указатель на строку, содержащую набор символов разделителей.

  static char *backup_string;
  if (!str) {
    str = backup_string;
  }
  if (!str) {
    return 0;
  }
  while (1) {
    if (is_delim(*str, delim)) {
      str++;
      continue;
    }
    if (*str == '\0') {
      return 0;
    }
    break;
  }
  char *ret = str;
  while (1) {
    if (*str == '\0') {
      backup_string = str;
      return ret;
    }
    if (is_delim(*str, delim)) {
      *str = '\0';
      backup_string = str + 1;
      return ret;
    }
    str++;
  }
}
