#include "tests.h"

START_TEST(test_is_equal) {
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{534, 0, 0, MASK_MINUS}};
    s21_decimal b = {{534, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Числа одинаковые но записаны по разному
    s21_decimal a = {{320, 0, 0, 0}};
    s21_decimal b = {{3200, 0, 0, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Числа одинаковые но записаны по разному
    s21_decimal a = {{0, 1000, 0, 0b00000000000000110000000000000000}};
    s21_decimal b = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{DEC_MAX}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{DEC_ZERO}};
    s21_decimal b = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{0, 0, 1, MASK_MINUS}};
    s21_decimal b = {{0, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{432, 0, 432, 0b10000000000101000000000000000000}};
    s21_decimal b = {{432, 0, 432, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Числа одинаковые но записаны по разному
    // 1733237036125865400000000 ^ -8
    s21_decimal a = {{0b10000111000100101101111000000000,
                      0b11110111110011101101100100010110,
                      0b00000000000000010110111100000110,
                      0b00000000000010000000000000000000}};
    s21_decimal b = {{0b11110010011111111001001010011110,
                      0b00000000001111011001001110110010, 0,
                      0b00000000000000000000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Нули с разными знаками
    s21_decimal a = {{0, 0, 0, MASK_MINUS}};
    s21_decimal b = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Нули с разными степенями
    s21_decimal a = {{0, 0, 0, 0b00000000000001110000000000000000}};
    s21_decimal b = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_equal(a, b)), 1);
  }
  {
    // Одинаковые мантисы, одинаковые знаки, разный показатель степени
    s21_decimal a = {{5, 422, 45, 0b00000000000000010000000000000000}};
    s21_decimal b = {{5, 422, 45, 0b00000000000000110000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы, разные знаки, одинаковый показатель степени
    s21_decimal a = {{123, 345, 765, 0b00000000000000110000000000000000}};
    s21_decimal b = {{123, 345, 765, 0b10000000000000110000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы, разные знаки, разные показатели степени
    s21_decimal a = {{7654, 345, 9876, 0b00000000000000110000000000000000}};
    s21_decimal b = {{7654, 345, 9876, 0b10000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Все разное
    s21_decimal a = {{7654, 234, 76, 0b00000000000000110000000000000000}};
    s21_decimal b = {{2345, 765654, 234, 0b10000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal a = {{0, 10000, 0, 0b00000000000001110000000000000000}};
    s21_decimal b = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, степень одинаковая
    s21_decimal a = {{8765, 0, 1, MASK_MINUS}};
    s21_decimal b = {{234, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, степень одинаковая
    s21_decimal a = {{765, 65, 23, 0b10000000000101000000000000000000}};
    s21_decimal b = {{9876, 0, 2343, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, и степенями
    s21_decimal a = {{389787, 1, 678, 0b10000000000111000000000000000000}};
    s21_decimal b = {{672314, 0, 9876, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы, разные знаки
    s21_decimal a = {{654, 0, 0, MASK_MINUS}};
    s21_decimal b = {{654, 0, 0, 0}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы, разный показатель степени
    s21_decimal a = {{8765, 0, 0, 0}};
    s21_decimal b = {{8765, 0, 0, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal a = {{0, 1000, 0, 0b00000000000001110000000000000000}};
    s21_decimal b = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }

  {
    // Числа с разными мантисами, степень одинаковая
    s21_decimal a = {{534, 0, 1, MASK_MINUS}};
    s21_decimal b = {{0, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, степень одинаковая
    s21_decimal a = {{5345, 1, 4333, 0b10000000000101000000000000000000}};
    s21_decimal b = {{5345, 0, 4333, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_equal(a, b)), 0);
  }
}
END_TEST

Suite *is_equal_suite(void) {
  Suite *s = suite_create("is_equal");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_is_equal);
  suite_add_tcase(s, tc_core);

  return s;
}