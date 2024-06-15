#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#define SUCCESS 1
#define FAILURE 0
#define EPSILON 1e-7

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum retrn { OK, UNCORRECT_MATRIX, CALCULATION_ERROR };

int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_check(int rows, int columns);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void s21_init_matrix(int rows, int columns, matrix_t *A, double matrix[]);
int s21_check_matrix(matrix_t *A);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_complement(matrix_t *A, double *result, int delete_row, int delete_col);
void s21_init_range_matrix(matrix_t *A);

#endif