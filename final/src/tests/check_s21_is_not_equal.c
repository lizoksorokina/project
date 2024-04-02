#include "tests.h"

START_TEST(test_is_not_equal) {
  {
    // Одинаковые мантисы, одинаковые знаки и степени
    s21_decimal a = {{6543, 2345, 3, 0b10000000000001101000000000000000}};
    s21_decimal b = {{6543, 2345, 3, 0b10000000000001101000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{876, 7, 98765, MASK_MINUS}};
    s21_decimal b = {{876, 7, 98765, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Числа одинаковые но записаны по разному
    s21_decimal a = {{58, 0, 0, 0}};
    s21_decimal b = {{580000000, 0, 0, 0b00000000000001110000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Числа одинаковые но записаны по разному
    s21_decimal a = {{0, 1000, 0, 0b00000000000000110000000000000000}};
    s21_decimal b = {{0, 100, 0, 0b00000000000000100000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{DEC_MAX}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{DEC_ZERO}};
    s21_decimal b = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{0, 1215, 1, MASK_MINUS}};
    s21_decimal b = {{0, 1215, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Числа одинаковые, степень одинаковая
    s21_decimal a = {{211, 0, 313, 0b10000000000101000000000000000000}};
    s21_decimal b = {{211, 0, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
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
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Нули с разными знаками
    s21_decimal a = {{0, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Нули с разными степенями
    s21_decimal a = {{0, 0, 0, 0b00000000000010110000000000000000}};
    s21_decimal b = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы, разные знаки
    s21_decimal a = {{0, 876, 0, MASK_MINUS}};
    s21_decimal b = {{0, 876, 0, 0}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 1);
  }
  {
    // Одинаковые мантисы, разный показатель степени
    s21_decimal a = {{6, 54, 321, 0}};
    s21_decimal b = {{6, 254, 321, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 1);
  }
  {
    // Одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal a = {{0, 1000, 0, 0b00000000000001110000000000000000}};
    s21_decimal b = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 1);
  }

  {
    // Числа с разными мантисами, степень одинаковая
    s21_decimal a = {{654, 0, 1, MASK_MINUS}};
    s21_decimal b = {{345, 0, 1, MASK_MINUS}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 1);
  }
  {
    // Числа с разными мантисами, степень одинаковая
    s21_decimal a = {{7654, 1, 7654, 0b10000000000101000000000000000000}};
    s21_decimal b = {{7654, 0, 7654, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 1);
  }
  {
    // Числа с разными мантисами, и степенями
    s21_decimal a = {{87654, 1, 8765, 0b10000000000111000000000000000000}};
    s21_decimal b = {{7654, 0, 8765, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 1);
  }
  {
    // Числа с одинаковыми мантисами, и степенями, но разными знаками
    s21_decimal a = {{23, 0, 321, 0b00000000000101000000000000000000}};
    s21_decimal b = {{23, 0, 321, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_not_equal(a, b)), 1);
  }
}
END_TEST

Suite *is_not_equal_suite(void) {
  Suite *s = suite_create("is_not_equal");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_is_not_equal);
  suite_add_tcase(s, tc_core);

  return s;
}