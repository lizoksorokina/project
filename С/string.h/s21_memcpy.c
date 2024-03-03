#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dest_to_edit = s21_NULL, *src_to_read = s21_NULL;

  if (src != NULL && dest != NULL) {
    dest_to_edit = (char *)dest;
    /*
    Приводит указатель dest к типу  char*  и присваивает его переменной
    dest_to_edit . Приведение типов позволяет обращаться к элементам блока
    памяти dest_to_edit по индексу.
    */
    src_to_read = (char *)src;
    /*
    Приводит указатель src к типу char* и присваивает его переменной src_to_read
    . Такое приведение типов позволяет обращаться к элементам блока памяти
    src_to_read по индексу.
    */
    for (unsigned long int i = 0; i < n;
         i++) {  // выполняется от 0 до n-1 (включительно)
      dest_to_edit[i] =
          src_to_read[i];  // копирует значение элемента блока памяти
                           // src_to_read с индексом i в элемент блока памяти
                           // dest_to_edit с индексом i
    }
  }

  return dest_to_edit;
}
