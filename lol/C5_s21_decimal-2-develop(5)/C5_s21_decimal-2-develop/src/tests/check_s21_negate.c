#include "tests.h"

START_TEST(test_negate) {
  {
    s21_decimal value = {{0, 0, 0, 0b00000000000001110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0, 0, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{65, 345, 43, 0b00000000000000010000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{65, 345, 43, 0b10000000000000010000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {
        {98765, 345, 7654, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {
        {98765, 345, 7654, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {
        {76543, 2345, 76543, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {
        {76543, 2345, 76543, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{1234, 654, 1234, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{1234, 654, 1234, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{0, 6543, 0, 0b00000000000001110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0, 6543, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{987654, 0, 1, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{987654, 0, 1, 0}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{12, 3456, 789, 0b10000000000101000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{12, 3456, 789, 0b00000000000101000000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{987654, 3, 21, 0b10000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{987654, 3, 21, 0b00000000000111000000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{543, 0, 0, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{543, 0, 0, 0}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{12345, 0, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{12345, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{0, 5432, 0, 0b00000000000001110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0, 5432, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }

  {
    s21_decimal value = {{432, 0, 1, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{432, 0, 1, 0}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    s21_decimal value = {{123, 123, 123, 0b10000000000101000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{123, 123, 123, 0b00000000000101000000000000000000}};
    ck_assert_int_eq((s21_negate(value, &result)), 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
}
END_TEST

Suite *negate_suite(void) {
  Suite *s = suite_create("negate");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_negate);
  suite_add_tcase(s, tc_core);

  return s;
}