#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int match = 0;

  if (str1 != NULL && str2 != NULL && n != 0) {
    char *str1_copy = (char *)str1, *str2_copy = (char *)str2;
    /*
    Переменные str1_copy и str2_copy типа char * и указатели str1 и str2 типа
    char *. Таким образом, мы можем обращаться к элементам блоков памяти по
    индексу.
    */
    for (unsigned long int i = 0; i < n && match == 0; i++) {
      match = str1_copy[i] - str2_copy[i];
    }
  }

  return match;
}