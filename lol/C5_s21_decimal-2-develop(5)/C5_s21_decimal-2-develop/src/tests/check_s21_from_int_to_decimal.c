#include "tests.h"

START_TEST(test_from_int_to_decimal) {
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    s21_decimal res = {{2147483646, 0, 0, 0}};
    unsigned int dst = 2147483646;
    s21_from_int_to_decimal(dst, &dec);
    ck_assert_int_eq(s21_is_equal(dec, res), 1);
  }
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    s21_decimal res = {{65, 0, 0, MASK_MINUS}};
    unsigned int dst = -65;
    s21_from_int_to_decimal(dst, &dec);
    ck_assert_int_eq(s21_is_equal(dec, res), 1);
  }
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    s21_decimal res = {{0b01111111111111111111111111111111, 0, 0, 0}};
    unsigned int dst = 0b01111111111111111111111111111111;
    s21_from_int_to_decimal(dst, &dec);
    ck_assert_int_eq(s21_is_equal(dec, res), 1);
  }
  {
    s21_decimal dec = {{0, 0, 0, 0}};
    int result = s21_from_int_to_decimal(0, &dec);
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_uint_eq(result, 0);

    result = s21_from_int_to_decimal(-0, &dec);
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_uint_eq(result, 0);
  }
  {
    s21_decimal dec = {0};
    int result = s21_from_int_to_decimal(INT_MAX, &dec);
    ck_assert_uint_eq(dec.bits[0], INT_MAX);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_uint_eq(result, 0);

    result = s21_from_int_to_decimal(INT_MIN, &dec);
    ck_assert_uint_eq(dec.bits[0], 2147483648);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 2147483648);
    ck_assert_uint_eq(result, 0);
  }
  {
    s21_decimal dec_1 = {0}, dec_2 = {0};
    dec_1.bits[0] = 0b00000000000000000000000000000001;
    dec_1.bits[1] = 0b00000000000000000000000000000000;
    dec_1.bits[2] = 0b00000000000000000000000000000000;
    dec_1.bits[3] = 0b00000000000000000000000000000000;
    int result = s21_from_int_to_decimal(1, &dec_2);
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
    ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
    ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
    ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
  }
  {
    s21_decimal dec_1 = {0}, dec_2 = {0};
    dec_1.bits[0] = 0b00000000000000000000000000000001;
    dec_1.bits[1] = 0b00000000000000000000000000000000;
    dec_1.bits[2] = 0b00000000000000000000000000000000;
    dec_1.bits[3] = 0b10000000000000000000000000000000;
    int result = s21_from_int_to_decimal(-1, &dec_2);
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
    ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
    ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
    ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
  }
  {
    s21_decimal dec = {0};
    int number = 499559;
    dec.bits[0] = 0b00010001000010000010000010000001;
    dec.bits[1] = 0b01000100001110000001000000010000;
    dec.bits[2] = 0b00001000100100101000010001000100;
    dec.bits[3] = 0b10000000000000000000000000000000;
    int result = s21_from_int_to_decimal(number, &dec);
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(dec.bits[0], number);
    ck_assert_int_eq(dec.bits[1], 0);
    ck_assert_int_eq(dec.bits[2], 0);
    ck_assert_int_eq(dec.bits[3], 0);
  }
  {
    int result = s21_from_int_to_decimal(123456, NULL);
    ck_assert_int_eq(result, 1);
  }
  {
    s21_decimal dec = {0};
    int values[12] = {-rand(), rand(), -rand(), rand(), -rand(), rand()};
    int i = _i;
    int result = s21_from_int_to_decimal(values[i], &dec);
    ck_assert_uint_eq(dec.bits[0], abs(values[i]));
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], values[i] > 0 ? 0 : 2147483648);
    ck_assert_uint_eq(result, 0);
  }
  {
    int src = -2147483648;
    s21_decimal check = {{2147483648u, 0u, 0u, 0u}};
    set_sign(&check, 1);
    s21_decimal result;
    s21_from_int_to_decimal(src, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    int return_value = s21_from_int_to_decimal(src, &result);
    ck_assert_int_eq(return_value, 0);
  }
  {
    int src = -49135648;
    s21_decimal check = {{49135648u, 0u, 0u, 0u}};
    set_sign(&check, 1);
    s21_decimal result;
    s21_from_int_to_decimal(src, &result);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    int return_value = s21_from_int_to_decimal(src, &result);
    ck_assert_int_eq(return_value, 0);
  }
  {
    int a = 123123;
    s21_decimal result = {0};
    s21_from_int_to_decimal(a, &result);
    ck_assert_uint_eq(result.bits[0], a);
    ck_assert_int_eq(get_sign(result), 0);
    ck_assert_int_eq(get_exp(result), 0);
  }
  {}
}
END_TEST

Suite *from_int_to_decimal_suite(void) {
  Suite *s = suite_create("from_int_to_decimal");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_from_int_to_decimal);
  suite_add_tcase(s, tc_core);

  return s;
}