#include "tests.h"

START_TEST(test_s21_add) {
  {
    // Положительные числа с одинаковой степенью
    s21_decimal result = {0};
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{321, 0, 0, 0}};
    s21_decimal correct_result = {{444, 0, 0, 0}};

    ck_assert_int_eq((s21_add(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Второе отрицательное и меньше первого, степень одинаковая
    s21_decimal a = {{444, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{321, 0, 0, 0}};
    ck_assert_int_eq((s21_add(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Отрицательные числа с одинаковой степенью
    s21_decimal result = {0};
    s21_decimal a = {{123, 0, 0, MASK_MINUS}};
    s21_decimal b = {{321, 0, 0, MASK_MINUS}};
    s21_decimal correct_result = {{444, 0, 0, MASK_MINUS}};

    ck_assert_int_eq((s21_add(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Первое отрицательное и больше второго, степень одинаковая
    s21_decimal a = {{444, 0, 0, MASK_MINUS}};
    s21_decimal b = {{123, 0, 0, 0}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{321, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_add(a, b, &result)), 0);
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
    ck_assert_int_eq((s21_add(a, b, &result)), ERROR_TOO_BIG);
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
    ck_assert_int_eq((s21_add(a, b, &result)), ERROR_TOO_SMALL);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Сложение максимальных decimal
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{DEC_MAX}};
    set_exp(&a, 1);
    set_exp(&b, 1);
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal correct_result = {{0b00110011001100110011001100110011,
                                   0b00110011001100110011001100110011,
                                   0b110011001100110011001100110011, 0}};
    ck_assert_int_eq((s21_add(a, b, &result)), SUCCESS);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // 1 и 26 степень
    s21_decimal value_1 = {
        {0b00000110000000000000000000000010, 0b10011010100011000000100011111010,
         0b1110011110011100010011, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b01001010000000000000000000000001, 0b00010110000101000000000101001000,
         0b10000100010110010101, 0b00000000000110100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000101110111000,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000001000000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 1 и 26 степень
    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b00000000000110100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000000000001111,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 1 и 27 степень
    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b00000000000110110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000000000000111,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }

  {
    // 1 и 26 степень
    s21_decimal value_1 = {
        {0b00000110000000000000000000000010, 0b10011010100011000000100011111010,
         0b1110011110011100010011, 0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b01001010000000000000000000000001, 0b00010110000101000000000101001000,
         0b10000100010110010101, 0b10000000000110100000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000001111101000,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000001000000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 1 и 27 степень
    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b10000000000110110000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01110000000000000000000000000101,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    // 1 и 26 степени
    s21_decimal value_1 = {{0b01110000000000000000000000000110,
                            0b10110011000000110001000010100111,
                            0b11100010001011101010010010010011,
                            0b00000000000000010000000000000000}};
    s21_decimal value_2 = {
        {0b10011010000000000000000000000001, 0b11000110101101000000101110001010,
         0b10010100111001000111101, 0b10000000000110100000000000000000}};

    s21_decimal result = {{DEC_ZERO}};
    s21_decimal check = {{0b01101111111111111111111111111101,
                          0b10110011000000110001000010100111,
                          0b11100010001011101010010010010011,
                          0b00000000000000010000000000000000}};

    ck_assert_int_eq((s21_add(value_1, value_2, &result)), OK);
    // s21_print_decimal(result);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
}
END_TEST

Suite *add_suite(void) {
  Suite *s = suite_create("add");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_add);
  suite_add_tcase(s, tc_core);

  return s;
}
