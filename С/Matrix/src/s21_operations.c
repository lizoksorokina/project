#include "s21_matrix.h"

// Функция для создания матрицы заданного размера и сохранения ее в структуре
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // Проверяем, что указатель result не равен NULL и что количество строк и
  // столбцов корректное
  if (result == NULL || s21_check(rows, columns) == CALCULATION_ERROR) {
    return UNCORRECT_MATRIX;  // Возвращаем код ошибки, если условия не
                              // выполняются
  }

  // память под двумерный массив размером rows x columns
  double **matrix = malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(columns * sizeof(double));
    for (int j = 0; j < columns; j++) {
    }
  }

  // Сохраняем созданную матрицу, количество столбцов и строк в структуре result
  result->matrix = matrix;
  result->columns = columns;
  result->rows = rows;

  return OK;
}

// Функция для удаления матрицы и освобождения выделенной памяти
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL && A->rows > 0 && A->columns > 0) {
      // Освобождение каждого массива по отдельности
      for (int i = 0; i < A->rows; i++) {
        if (A->matrix[i] != NULL) free(A->matrix[i]);
        A->matrix[i] = NULL;  // Присваиваем NULL, чтобы убедиться, что он
                              // больше не ссылается на эту область памяти
      }
      // Освобождаем указатель на массив
      free(A->matrix);
    }
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

// Функция транспонирует матрицу
int s21_transpose(matrix_t *A, matrix_t *result) {
  // Проверка корректности матрицы
  if (s21_check_matrix(A)) {
    return UNCORRECT_MATRIX;
  }
  // Создание новой матрицы для результата
  int error = s21_create_matrix(A->columns, A->rows, result);

  // Если матрица успешно создана, производим транспонирование матрицы
  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        // Замена строк на столбцы и столбцов на строки
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  // Если матрица не была успешно создана, удаляем результат
  if (error != OK) s21_remove_matrix(result);
  return error;
}

// Функция вычисляет обратную матрицу
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  // Проверка корректности матрицы и указателя на результат
  if (s21_check_matrix(A) == UNCORRECT_MATRIX || result == NULL) {
    return UNCORRECT_MATRIX;
  }
  // Проверка, что матрица является квадратной
  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }
  // Вычисление определителя матрицы
  double det = 0;
  s21_determinant(A, &det);
  // Проверка, что определитель не равен 0
  if (fabs(det) < 1e-7) {
    return CALCULATION_ERROR;
  }
  // Если матрица имеет размер 1x1, обратной матрицей будет матрица 1x1 с
  // элементом, равным 1/элемент исходной матрицы
  if (A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = (double)1 / A->matrix[0][0];
    return OK;
  }
  // Вычисление транспонированной матрицы
  matrix_t transposed;
  if (s21_transpose(A, &transposed) == UNCORRECT_MATRIX) {
    return UNCORRECT_MATRIX;
  }
  // Вычисление матрицы алгебраических дополнений для транспонированной матрицы
  matrix_t adjugate;
  s21_calc_complements(&transposed, &adjugate);
  // Умножение матрицы алгебраических дополнений на 1/определитель
  s21_mult_number(&adjugate, (double)1 / det, result);
  // Удаление временных матриц
  s21_remove_matrix(&transposed);
  s21_remove_matrix(&adjugate);
  return OK;
}
