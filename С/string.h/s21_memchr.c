#include "s21_string.h"

void *s21_memchr(
    const void *str, int c,
    s21_size_t n) {  // ищет первое вхождение символа c в массиве str длиной n
  char *str_copy = S21_NULL;  // объявляет переменную  str_copy  типа  char *  и
                              // инициализирует ее значением  S21_NULL

  if (str != NULL && n != 0) {
    int match = 0;
    str_copy = (char *)str;
    /*
    приводит указатель  str  к типу  char *  и присваивает его переменной
    str_copy. Такое приведение типов позволяет обращаться к элементам массива
    str_copy  по индексу.
    */
    for (long unsigned int i = 0;
         i < n && match == 0 && i <= s21_strlen(str_copy);
         i++) {  // выполняется от 0 до n-1 (включительно), пока match равно 0 и
                 // i не превышает длину строки str_copy
      if ((char)c ==
          str_copy[i]) {  // если str_copy[i] равен c , то str_copy
                          // присваивается &str_copy[i] и match присваивается 1
        str_copy = &str_copy[i];
        match = 1;
      }
    }
    if (match == 0) {
      str_copy = S21_NULL;
    }
  }
  return str_copy;
}