#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверяем корректность матриц A и B
  if (s21_check_matrix(A) || s21_check_matrix(B)) {
    return UNCORRECT_MATRIX;  // Возвращаем ошибку, если матрицы некорректны
  }
  // Проверяем соответствие размеров матриц A и B
  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;  // Возвращаем ошибку вычисления, если размеры
                               // матриц не совпадают
  }

  // Создаем матрицу result с размерами A
  int error = s21_create_matrix(A->rows, A->columns, result);

  // Если создание матрицы result прошло успешно, складываем соответствующие
  // элементы матриц A и B
  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  // Если произошла ошибка при создании матрицы result, освобождаем ее память
  if (error != OK) s21_remove_matrix(result);

  return error;
}

// Функция для вычитания одной матрицы из другой
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверяем корректность матриц A и B
  if (s21_check_matrix(A) || s21_check_matrix(B)) {
    return UNCORRECT_MATRIX;  // Возвращаем ошибку, если матрицы некорректны
  }
  // Проверяем соответствие размеров матриц A и B
  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;  // Возвращаем ошибку вычисления, если размеры
                               // матриц не совпадают
  }

  // Создаем матрицу result с размерами A
  int error = s21_create_matrix(A->rows, A->columns, result);

  // Если создание матрицы result прошло успешно, вычитаем соответствующие
  // элементы матриц A и B
  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  // Если произошла ошибка при создании матрицы result, освобождаем ее память
  if (error != OK) s21_remove_matrix(result);

  return error;
}

// Функция умножает матрицу на матрицу
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверка корректности матриц
  if (s21_check_matrix(A) || s21_check_matrix(B)) {
    return UNCORRECT_MATRIX;
  }
  // Проверка, что количество столбцов в первой матрице совпадает с количеством
  // строк во второй
  if (A->columns != B->rows) {
    return CALCULATION_ERROR;
  }
  // Создание новой матрицы для результата
  int error = s21_create_matrix(A->rows, B->columns, result);

  // Если матрица успешно создана, производим умножение матриц
  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  // Если матрица не была успешно создана, удаляем результат
  if (error != OK) s21_remove_matrix(result);

  return error;
}

// Функция умножает матрицу на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  // Проверка корректности матрицы
  if (s21_check_matrix(A)) {
    return UNCORRECT_MATRIX;
  }

  // Создание новой матрицы для результата
  int error = s21_create_matrix(A->rows, A->columns, result);

  // Если матрица успешно создана, умножаем каждый элемент исходной матрицы на
  // число
  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  // Если матрица не была успешно создана, удаляем результат
  if (error != OK) s21_remove_matrix(result);

  // Возвращаем код ошибки
  return error;
}

/* // Функция для сравнения двух матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  // Проверяем, что указатели на матрицы не равны NULL и что их размеры
  // совпадают
  if (A == NULL || B == NULL ||
      (A->rows != B->rows || A->columns != B->columns)) {
    return FAILURE;  // Возвращаем FAILURE, если матрицы не могут быть сравнены
  }

  int res = SUCCESS;  // Инициализируем переменную результата как SUCCESS
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      // Сравниваем значения элементов матриц A и B с заданной точностью
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7)  // 0.0000001
        return FAILURE;  // Возвращаем FAILURE, если элементы не равны с
                         // заданной точностью
    }
  }

  return res;  // Возвращаем результат сравнения матриц (SUCCESS, если они
               // эквивалентны)
}*/

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || A->rows != B->rows ||
      A->columns != B->columns) {
    return FAILURE;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
        return FAILURE;
      }
    }
  }

  return SUCCESS;
}
