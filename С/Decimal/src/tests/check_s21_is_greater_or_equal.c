#include "tests.h"

START_TEST(test_s21_is_greater_or_equal) {
  {
    // Числа одинаковые, степень второго больше
    s21_decimal a = {{4534532, 43, 0, 0b00000000000111000000000000000000}};
    s21_decimal b = {{4534532, 43, 0, 0b00000000001111000000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Числа разные, после нормализации второе округляется
    s21_decimal a = {{22981, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal b = {{229803, 0, 0, 0b00000000000111010000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Разные числа, одна степень
    s21_decimal a = {{4413499, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal b = {{448022, 0, 0, 0b00000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Разные числа, одна степень, отрицателные
    s21_decimal a = {{5232244, 0, 0, 0b10000000000000010000000000000000}};
    s21_decimal b = {{52433, 0, 0, 0b10000000000000010000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Числа одинаковые, разная степень
    s21_decimal a = {{0, 1, 0, 0b00000000000000110000000000000000}};
    s21_decimal b = {{0, 1, 0, 0b00000000000001010000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Одинаковые числа с разными знаками
    s21_decimal a = {{6543, 2345, 765, 0}};
    s21_decimal b = {{6543, 2345, 765, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Одинаковые числа, степени и знаки
    s21_decimal a = {{87654, 87654, 87654, MASK_MINUS}};
    s21_decimal b = {{87654, 87654, 87654, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Числа и знаки разные
    s21_decimal a = {{23456, 98765, 23456, 0}};
    s21_decimal b = {{23456, 98765, 23456, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{DEC_MIN}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    s21_decimal a = {{DEC_ZERO}};
    s21_decimal b = {{DEC_MIN}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // 0.0000000000000000000000000001 и 0
    s21_decimal a = {{1, 0, 0, 0b00000000000111000000000000000000}};
    s21_decimal b = {{DEC_ZERO}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // 0 и -0.0000000000000000000000000001
    s21_decimal a = {{DEC_ZERO}};
    s21_decimal b = {{1, 0, 0, 0b10000000000001110000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // 0 и -0
    s21_decimal a = {{DEC_ZERO}};
    s21_decimal b = {{0, 0, 0, 0b10000000000000000000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Одинаковые мантисы, одинаковые знаки, разный показатель степени
    s21_decimal a = {{543, 2345, 7654, 0b00000000000000110000000000000000}};
    s21_decimal b = {{543, 2345, 7654, 0b00000000000000100000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Разные мантисы, разные знаки, одинаковый показатель степени
    s21_decimal a = {{87654, 543, 1234, 0b00000000000000110000000000000000}};
    s21_decimal b = {{87654, 543, 1234, 0b00000000000000110000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
  {
    // Одинаковые мантисы, оба отрицательные, разные показатели степени
    s21_decimal a = {{987654, 3456, 6543, 0b10000000000000110000000000000000}};
    s21_decimal b = {{987654, 3456, 6543, 0b10000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Разное все
    s21_decimal a = {{54, 14421, 645, 0b10000000000000110000000000000000}};
    s21_decimal b = {{532, 24, 3545434, 0b00000000000100110000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal a = {{0, 10000, 0, 0b00000000000001110000000000000000}};
    s21_decimal b = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal a = {{8985934, 0, 0, MASK_MINUS}};
    s21_decimal b = {{7834, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal a = {{8943, 39849, 999, 0b10000000000101000000000000000000}};
    s21_decimal b = {{8394, 89, 89, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, одинаковые степени, оба отрицательные
    s21_decimal a = {{97986, 1, 68776, 0b10000000000101000000000000000000}};
    s21_decimal b = {{88888, 0, 6777, 0b00000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы, разные знаки
    s21_decimal a = {{78876767, 0, 0, MASK_MINUS}};
    s21_decimal b = {{78876767, 0, 0, 0}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы, разный показатель степени
    s21_decimal a = {{564645654, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal b = {{564645654, 0, 0, 0}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Одинаковые мантисы (можно нормализовать), разный показатель степени
    s21_decimal a = {{0, 1000, 0, 0b00000000000001110000000000000000}};
    s21_decimal b = {{0, 1, 0, 0}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 0);
  }
  {
    // Числа с разными мантисами, степень одинаковая, оба отрицательные
    s21_decimal a = {{211, 10, 313, 0b10000000000101000000000000000000}};
    s21_decimal b = {{211, 21, 313, 0b10000000000101000000000000000000}};
    ck_assert_int_eq((s21_is_greater_or_equal(a, b)), 1);
  }
}
END_TEST

Suite *is_greater_or_equal_suite(void) {
  Suite *s = suite_create("is_greater_or_equal");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_is_greater_or_equal);
  suite_add_tcase(s, tc_core);

  return s;
}