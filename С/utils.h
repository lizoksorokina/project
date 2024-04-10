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

#include <math.h>
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
int s21_is_owerflow(s21_decimal value);
int s21_is_zero(s21_decimal value);
void s21_mul_big_ten_arr(int value[]);
int s21_is_zero_bigarr(int array[]);
void s21_sum_of_bigtenarr(int value_1[], int value_2[]);
int s21_sub_of_bigtenarr(int value_1[], int value_2[]);
int div_bigtenarr(int value_1[], int value_2[], int result[]);
int s21_is_owerflow_mantissa(int res_exp, int big_ten_array[]);
int s21_compare_ten_array(int a[], int b[]);
void s21_banking_round_for_mult(int big_ten_array[], int remainder);
int s21_is_zero_array_for_big_decimal(int a[]);
int s21_set_bitt_for_big_decimal(s21_big_decimal *result, int position,
                                 int value);
int s21_div_tenarray_for_big_decimal(int value[]);
int s21_get_bit_big_decimal(s21_big_decimal value, int position);
void s21_from_ten_array_to_big_decimal(int array[], s21_big_decimal *result);
int s21_set_bitt(s21_decimal *result, int position, int value);
int s21_cpy_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst);
int s21_set_exp(s21_decimal value, s21_decimal *result, int exp);
int get_bit(s21_decimal dec, int pos);
void set_bit(s21_decimal *dec, int bit, int val);
int get_sign(s21_decimal dec);
void set_sign(s21_decimal *dec, int sign);
int get_exp(s21_decimal d);
void set_exp(s21_decimal *dec, int power);
int copy_to_buffer(s21_decimal src, s21_decimal *dst);
void init_decimal(s21_decimal *d);
int get_float_exp_from_string(char *str);
int check_F2D(float src, s21_decimal *dst);
void get_pow_10_multiDec(int exp, s21_decimal *dst);
unsigned int get_rid_ofZeros(char *sci_str, int *exp);
int binary_add(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);
int binary_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);
int binary_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);
s21_decimal binary_div(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);
int shift_left(s21_decimal *dec);
void shift_right(s21_decimal *dec);
int is_less_simple(s21_decimal dec1, s21_decimal dec2);
int is_equal_simple(s21_decimal dec1, s21_decimal dec2);
int is_less_or_equal_simple(s21_decimal dec1, s21_decimal dec2);
int is_more_simple(s21_decimal dec1, s21_decimal dec2);
int is_more_or_equal_simple(s21_decimal dec1, s21_decimal dec2);
int ipow(int base, int exponent);

int s21_get_bit(s21_decimal decl, int index);
int get_pow(s21_decimal value);
int set_pow(s21_decimal value, s21_decimal *result, int int_pow);
void div_by_ten(s21_decimal *value);
void s21_set_bit(s21_decimal *decl, int index, int bit);
s21_decimal abs_dec(s21_decimal value);

#endif