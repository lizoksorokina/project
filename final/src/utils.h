#ifndef UTILS_H
#define UTILS_H
#define SIGN_BIT 0x80000000
#define OK 0
#define NULL_POINTER_EXEPTION 1
#define EXPONENT_EXEPTION 2
#define S21_MAX_UINT 4294967295
#define U_MAX_INT 4294967295
#define EXPONENT_MINUS_1 2147549184   // 0b10000000000000010000000000000000
#define EXPONENT_PLUS_1 65536         // 0b00000000000000010000000000000000
#define EXPONENT_PLUS_2 196608        // 0b00000000000000110000000000000000
#define EXPONENT_MINUS_28 2149318656  // 0b10000000000111000000000000000000
#define EXPONENT_PLUS_28 1835008      // 0b00000000000111000000000000000000
#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -79228162514264337593543950335.0F

#include <string.h>

#include "s21_decimal.h"
typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

int s21_get_exp(s21_decimal value);
int s21_bit(s21_decimal value, int position);
int s21_exponent_check(s21_decimal a, s21_decimal b);
int s21_copy_decimal_to_bigdecimal(s21_decimal src, s21_big_decimal *dst);
void s21_from_big_decimal_to_ten_array(s21_big_decimal value, int result[]);
int s21_bit_big_decimal(s21_big_decimal value, int position);
void s21_sum_of_ten_array_for_big_decimal(int a[], int b[]);
int s21_compare_bigten_array(int a[], int b[]);
int s21_compare_two_decimals(s21_decimal a, s21_decimal b);
#endif