#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>

#define MASK_MINUS 0x80000000

#define SUCCESS 0
#define ERROR_TOO_SMALL 2
#define ERROR_TOO_BIG 1

#define DEC_ZERO 0, 0, 0, 0
#define DEC_MAX UINT_MAX, UINT_MAX, UINT_MAX, 0
#define DEC_MIN UINT_MAX, UINT_MAX, UINT_MAX, MASK_MINUS

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// Arithmetic Operators

int s21_add(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_div(s21_decimal a, s21_decimal b, s21_decimal *result);

// Comparison Operators

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

// Convertors and parsers

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif