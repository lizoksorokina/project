#include "tests.h"

START_TEST(test_s21_mul) {
  {
    // Оба числа положительные
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{15129, 0, 0, 0}};
    ck_assert_int_eq((s21_mul(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Второе число отрицательное и больше первого
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{321, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{39483, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Второе число отрицательное и меньше первого
    s21_decimal a = {{321, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{39483, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Первое отрицательное и меньше второго
    s21_decimal a = {{123, 0, 0, MASK_MINUS}};
    s21_decimal b = {{321, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{39483, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Первое отрицательное и больше второго
    s21_decimal a = {{321, 0, 0, MASK_MINUS}};
    s21_decimal b = {{123, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{39483, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_mul(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Оба отрицательные
    s21_decimal a = {{123, 0, 0, MASK_MINUS}};
    s21_decimal b = {{321, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{39483, 0, 0, 0}};
    ck_assert_int_eq((s21_mul(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Переполнение вверх
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{320, 0, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_mul(a, b, &result)), ERROR_TOO_BIG);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Переполнение вниз
    s21_decimal a = {{DEC_MIN}};
    s21_decimal b = {{320, 0, 0, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_mul(a, b, &result)), ERROR_TOO_BIG);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
}
END_TEST

Suite *mul_suite(void) {
  Suite *s = suite_create("mul");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_mul);
  suite_add_tcase(s, tc_core);

  return s;
}