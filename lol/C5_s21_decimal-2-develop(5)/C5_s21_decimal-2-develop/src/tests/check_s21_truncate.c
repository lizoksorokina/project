#include "tests.h"

START_TEST(test_truncate) {
  {
    // Отрицательное, без дробной части
    s21_decimal value = {{7654, 0, 0, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {{7654, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // 34,1 -> 34
    s21_decimal value = {{341, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal correct_result = {{34, 0, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};

    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // 4 294 967 296, 000 -> 4 294 967 296
    s21_decimal value = {{0, 1000, 0, 0b00000000000000110000000000000000}};
    s21_decimal correct_result = {{0, 1, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};

    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }

  {
    // 40,5 -> 40
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal value = {{405, 0, 0, 0b10000000000000010000000000000000}};
    s21_decimal correct_result = {
        {40, 0, 0, 0b10000000000000000000000000000000}};

    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Нет целой части (десятичная дробь с целой частью 0)
    // 0,4 -> 0

    s21_decimal value = {{40, 0, 0, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {{0, 0, 0, 0}};

    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // 14 757 395 258 967 641 292, 800 -> 14 757 395 258 967 641 292
    s21_decimal value = {{0, 0, 800, 0b00000000000000110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {{0b11001100110011001100110011001100,
                                   0b11001100110011001100110011001100, 0, 0}};

    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // 00000000000000000000000100111001 = 313
    // 00000000000000000000000011010011 = 211
    // 5 773 830 8, 95 071 089 656 019 -> 5 773 830 8 (14 степень)
    s21_decimal value = {{211, 0, 313, 0b00000000000011100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {
        {0b00000011011100010000010001000100, 0, 0, 0}};

    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // 00000000000000000000000100111001 = 313
    //  00000000000000000000000011010011 =211
    // -5 7, 73 830 895 071 089 656 019 -> -57 (20 степень)
    s21_decimal value = {{211, 0, 313, 0b10000000000101000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {{57, 0, 0, MASK_MINUS}};

    ck_assert_int_eq((s21_truncate(value, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
}
END_TEST

Suite *truncate_suite(void) {
  Suite *s = suite_create("truncate");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_truncate);
  suite_add_tcase(s, tc_core);

  return s;
}