#include "s21_matrix.h"

// Функция для проверки корректности количества строк и столбцов матрицы
int s21_check(int rows, int columns) {
  // Проверяем, что количество строк и столбцов больше нуля
  if (rows <= 0 || columns <= 0) {
    return CALCULATION_ERROR;  // Возвращаем ошибку вычисления, если условие не
                               // выполняется
  }
  return OK;  // Возвращаем ОК, если количество строк и столбцов корректное
}

// Функция для инициализации матрицы A значениями из одномерного массива matrix
void s21_init_matrix(int rows, int columns, matrix_t *A, double matrix[]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A->matrix[i][j] = matrix[j + i * columns];
    }
  }
}

// Функция для проверки корректности матрицы A
int s21_check_matrix(matrix_t *A) {
  int retrn_code = OK;
  // Проверяем, что матрица и ее размеры корректны
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0)
    retrn_code = UNCORRECT_MATRIX;
  // Проверяем каждую строку матрицы на корректность
  for (int i = 0; retrn_code == OK && i < A->rows; i++) {
    if (A->matrix[i] == NULL) retrn_code = UNCORRECT_MATRIX;
  }
  return retrn_code;
}