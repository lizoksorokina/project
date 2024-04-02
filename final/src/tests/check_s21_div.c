#include "tests.h"

START_TEST(test_div) {
  {
    // Отрицательное, младшие биты, делится нацело
    s21_decimal a = {{17, 0, 0, MASK_MINUS}};
    s21_decimal b = {{5, 0, 0, 0}};
    s21_decimal correct_result = {
        {34, 0, 0, 0b10000000000000010000000000000000}};

    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Отрицательное, средние биты, делится нацело
    s21_decimal a = {{59, 0, 0, 0}};
    s21_decimal b = {{4, 0, 0, 0}};
    s21_decimal correct_result = {
        {1475, 0, 0, 0b00000000000000100000000000000000}};

    s21_decimal result = {{DEC_ZERO}};

    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Деление на 0
    s21_decimal a = {{87654, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal correct_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 3);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Деление большого числа на мелкое
    s21_decimal a = {{15, 20, 45, 0}};
    s21_decimal b = {{5, 0, 0, 0b00000000000011110000000000000000}};
    s21_decimal correct_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 1);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Деление большого числа
    s21_decimal a = {{15, 20, 45, 0b00000000000000110000000000000000}};
    s21_decimal b = {{3, 0, 0, 0b00000000000101100000000000000000}};
    s21_decimal correct_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 1);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }

  {
    // Деление большого числа
    s21_decimal a = {{15, 20, 45, MASK_MINUS}};
    s21_decimal b = {{5, 0, 0, 0b00000000000011110000000000000000}};
    s21_decimal correct_result = {{DEC_ZERO}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 2);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Деление большого числа на мелкое, без переполнения
    s21_decimal a = {{0b00000000000000000000000000001111,
                      0b11010000000000000000000000010100, 0b10, 0}};
    s21_decimal b = {{5, 0, 0, 0}};
    s21_decimal correct_result = {{0b00000000000000000000000000000011,
                                   0b10010000000000000000000000000100, 0, 0}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }

  {
    // Деление большого числа на мелкое, без переполнения
    s21_decimal a = {{0b00000000000000000000000000001111,
                      0b11010000000000000000000000010100, 0b10, MASK_MINUS}};
    s21_decimal b = {{5, 0, 0, 0b00000000000000110000000000000000}};
    s21_decimal correct_result = {{0b00000000000000000000101110111000,
                                   0b10000000000000000000111110100000,
                                   0b1000110010, MASK_MINUS}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Мантиса 1-го числа меньше мантисы 2-го числа
    s21_decimal a = {{15, 0, 0, 0}};
    s21_decimal b = {{25, 0, 0, 0}};
    s21_decimal correct_result = {
        {6, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    // Мантиса 1го числа меньше мантисы 2го числа, и 2е число занимает всю
    // мантису
    s21_decimal a = {{0b0, 0b11111111111111111111111111111111,
                      0b11111111111111111111111111111111, 0}};
    s21_decimal b = {{DEC_MAX}};
    s21_decimal correct_result = {{0b11101111101100000011000110100001,
                                   0b00111110001001010000001001100000,
                                   0b00100000010011111100111001011110,
                                   0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    s21_decimal a = {{4, 0, 0, 0}};
    s21_decimal b = {{6, 0, 0, 0}};
    s21_decimal correct_result = {{0b00001010101010101010101010101011,
                                   0b00101001011011100000000110010110,
                                   0b00010101100010101000100110010100,
                                   0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {
    s21_decimal a = {{8, 0, 0, 0}};
    s21_decimal b = {{9, 0, 0, 0}};
    s21_decimal correct_result = {{0b10111000111000111000111000111001,
                                   0b00110111001111010101011101110010,
                                   0b00011100101110001011011101110000,
                                   0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
  {  // 0.6 / 9
    s21_decimal a = {{6, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal b = {{9, 0, 0, 0}};
    s21_decimal correct_result = {{0b10011010101010101010101010101011,
                                   0b01101010100010110000000000101000,
                                   0b00000010001001110111010000101000,
                                   0b00000000000111000000000000000000}};
    s21_decimal result = {{DEC_ZERO}};
    ck_assert_int_eq((s21_div(a, b, &result)), 0);
    ck_assert_int_eq(correct_result.bits[0], result.bits[0]);
    ck_assert_int_eq(correct_result.bits[1], result.bits[1]);
    ck_assert_int_eq(correct_result.bits[2], result.bits[2]);
    ck_assert_int_eq(correct_result.bits[3], result.bits[3]);
  }
}
END_TEST

Suite *div_suite(void) {
  Suite *s = suite_create("div");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_div);
  suite_add_tcase(s, tc_core);

  return s;
}