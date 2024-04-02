#include "tests.h"

START_TEST(test_s21_is_less_or_equal) {
  {
    // Разные мантисы, одинаковые знаки и степени
    s21_decimal a = {{581, 348, 471, 0b10000000000001101000000000000000}};
    s21_decimal b = {{581, 348, 174, 0b10000000000001101000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Числа одинаковые, степень одинаковая, оба отрицатеьные
    s21_decimal a = {{581, 348, 471554, MASK_MINUS}};
    s21_decimal b = {{581, 348, 471554, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Числа разные, но после нормализации 2е округляется, 30я степень
    s21_decimal a = {{180, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal b = {{18041, 0, 0, 0b00000000000111100000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Числа одинаковые но записаны по разному
    s21_decimal a = {{8, 0, 0, 0}};
    s21_decimal b = {{80000000, 0, 0, 0b00000000000001110000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Числа одинаковые но записаны по разному
    s21_decimal a = {{0, 2000, 0, 0b00000000000000110000000000000000}};
    s21_decimal b = {{0, 200, 0, 0b00000000000000100000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{DEC_MAX}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    s21_decimal a = {{DEC_ZERO}};
    s21_decimal b = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    s21_decimal a = {{758, 532, 3210, MASK_MINUS}};
    s21_decimal b = {{875, 532, 3210, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 0);
  }
  {
    s21_decimal a = {{65211, 90, 1313, 0b10000000000101000000000000000000}};
    s21_decimal b = {{65211, 90, 1313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Числа одинаковые но записаны по разному
    s21_decimal a = {{0b10000111000100101101111000000000,
                      0b11110111110011101101100100010110,
                      0b00000000000000010110111100000110,
                      0b00000000000010000000000000000000}};
    s21_decimal b = {{0b11110010011111111001001010011110,
                      0b00000000001111011001001110110010, 0,
                      0b00000000000000000000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Нули с разными знаками
    s21_decimal a = {{0, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 0);
  }
  {
    // Нули с разными степенями
    s21_decimal a = {{0, 0, 0, 0b00000000000011110000000000000000}};
    s21_decimal b = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Одинаковые мантисы, разные знаки, одна степень
    s21_decimal a = {{0, 95784, 0, 0}};
    s21_decimal b = {{0, 95784, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less_or_equal(b, a)), 1);
  }
  {
    // Одинаковые мантисы, разный показатель степени
    s21_decimal a = {{66, 33, 9999, 0}};
    s21_decimal b = {{66, 33, 9999, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(b, a)), 1);
  }
  {
    // Разные мантисы, разный показатель степени
    s21_decimal a = {{0, 1000, 0, 0b00000000000000010000000000000000}};
    s21_decimal b = {{0, 2, 0, 0}};
    ck_assert_int_eq((s21_is_less_or_equal(b, a)), 1);
  }

  {
    // Числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal a = {{1815, 0, 2, MASK_MINUS}};
    s21_decimal b = {{183, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_less_or_equal(b, a)), 0);
  }
  {
    // Числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal a = {{21811, 0, 3131, 0b10000000000101000000000000000000}};
    s21_decimal b = {{21811, 11, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(b, a)), 0);
  }
  {
    // Числа с разными мантисами, и степенями, оба отрицаьельные
    s21_decimal a = {{2112, 1, 313, 0b10000000000011000000000000000000}};
    s21_decimal b = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(a, b)), 1);
  }
  {
    // Нули с разными знаками и степенями
    s21_decimal a = {{0, 0, 0, MASK_MINUS}};
    s21_decimal b = {{0, 0, 0, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_less_or_equal(b, a)), 1);
  }
  {
    // Мелкое число и 0
    s21_decimal a = {{1, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal b = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_less_or_equal(b, a)), 1);
  }
}
END_TEST

Suite *is_less_or_equal_suite(void) {
  Suite *s = suite_create("is_less_or_equal");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_is_less_or_equal);
  suite_add_tcase(s, tc_core);

  return s;
}