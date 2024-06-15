#include "s21_matrix.h"

// Вычисление минора матрицы
int s21_minor(matrix_t *A, double *result, int delete_row, int delete_col) {
  // Создание новой матрицы, которая меньше исходной на одну строку и столбец
  matrix_t m;
  s21_create_matrix(A->rows - 1, A->columns - 1, &m);
  int mi = 0;
  int mj = 0;
  // Заполнение новой матрицы значениями исходной, исключая указанные строку и
  // столбец
  for (int i = 0; i < A->rows; ++i) {
    if (i == delete_row) {
      continue;
    }
    mj = 0;
    for (int j = 0; j < A->columns; ++j) {
      if (j == delete_col) {
        continue;
      }
      m.matrix[mi][mj] = A->matrix[i][j];
      mj++;
    }
    mi++;
  }
  // Вычисление определителя полученной матрицы
  s21_determinant(&m, result);
  // Удаление временной матрицы
  s21_remove_matrix(&m);
  return OK;
}

// Вычисление алгебраического дополнения
int s21_complement(matrix_t *A, double *result, int delete_row,
                   int delete_col) {
  // Если матрица имеет размер 1x1, дополнение равно 1
  if (A->columns == 1 && A->rows == 1) {
    *result = 1;
    return OK;
  }
  // Если сумма индексов строки и столбца четная, дополнение равно минору
  if ((delete_row + delete_col) % 2 == 0) {
    return s21_minor(A, result, delete_row, delete_col);
  }
  // Если сумма индексов строки и столбца нечетная, дополнение равно минус
  // минору
  s21_minor(A, result, delete_row, delete_col);
  *result *= (double)-1;
  return OK;
}

// Вычисление определителя матрицы
int s21_determinant(matrix_t *A, double *result) {
  // Проверка корректности матрицы и указателя на результат
  if (s21_check_matrix(A) == UNCORRECT_MATRIX || result == NULL) {
    return UNCORRECT_MATRIX;
  }
  // Проверка, что матрица является квадратной
  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }
  // Если матрица имеет размер 1x1, определитель равен единственному элементу
  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }
  // Вычисление определителя как суммы произведений элементов первой строки и их
  // алгебраических дополнений
  *result = 0;
  for (int i = 0; i < A->columns; ++i) {
    double compl = 0;
    s21_complement(A, &compl, 0, i);
    *result = *result + A->matrix[0][i] * compl ;
  }
  return OK;
}

// Функция создаеет матрицу с  алгеброическим дополнением для матрицы
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // Проверка корректности матрицы и указателя на результат
  if (s21_check_matrix(A) == UNCORRECT_MATRIX || result == NULL) {
    return UNCORRECT_MATRIX;
  }
  // Проверка, что матрица является квадратной и не имеет размер 1x1
  if (A->rows != A->columns || A->rows == 1) {
    return CALCULATION_ERROR;
  }
  // Создание новой матрицы для результата
  s21_create_matrix(A->rows, A->columns, result);

  // Вычисление дополнения для каждого элемента матрицы
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      double compl = 0;
      s21_complement(A, &compl, i, j);
      result->matrix[i][j] = compl ;
    }
  }
  return OK;
}
