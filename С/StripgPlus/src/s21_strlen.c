#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {  // принимает указатель на символ и
                                          // возвращает значение типа s21_size_t
  s21_size_t length = 0;  // хранение длины строки
  for (; *(str + length); length++) {
    ;  // внутри цикла ничего не выполняется
  }  // length инициализирована до использования цикла
  return length;  // возвращает длину строки
}