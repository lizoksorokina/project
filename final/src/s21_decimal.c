// В этом файле не должно быть никаких других функций кроме функций библиотеки.
// Вспомогательные функции должны быть вынесены в utils.c

#include "s21_decimal.h"

#include "utils.h"

// Arithmetic Operators

int s21_add(s21_decimal a, s21_decimal b, s21_decimal *result) {}

int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *result) {}

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result) {}

int s21_div(s21_decimal a, s21_decimal b, s21_decimal *result) {}

// Comparison Operators

int s21_is_less(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) == 2) res = 1;
  return res;
}

// Возвращает:
//  0 - равно
//  1 - первое больше
//  2 - первое меньше
//  -1 - ошибка

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) != 1) res = 1;
  return res;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) == 1) res = 1;
  return res;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) != 2) res = 1;
  return res;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) == 0) res = 1;
  return res;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) != 0) res = 1;
  return res;
}

// Convertors and parsers

int s21_from_int_to_decimal(int src, s21_decimal *dst) {}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {}

// Another functions

int s21_floor(s21_decimal value, s21_decimal *result) {}

int s21_round(s21_decimal value, s21_decimal *result) {}

int s21_truncate(s21_decimal value, s21_decimal *result) {}

int s21_negate(s21_decimal value, s21_decimal *result) {}