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
    // Результат положительный, но степень переполнения
    s21_decimal a = {{536870912, 0, 0, 0}};  // 2^29
    s21_decimal b = {{536870912, 0, 0, 0}};  // 2^29
    s21_decimal result = {0};
    s21_decimal correct_result = {{1073741824, 0, 0, MASK_MINUS}};  // -2^30
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
}
END_TEST

Suite *add_suite(void) {
  Suite *s = suite_create("add");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_add);
  suite_add_tcase(s, tc_core);

  return s;
}
