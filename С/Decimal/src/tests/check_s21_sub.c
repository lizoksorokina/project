#include "tests.h"

START_TEST(test_s21_sub) {
  {
    // Положительные числа, первое больше второго, результат положителен
    s21_decimal value_1 = {0};
    s21_decimal value_2 = {0};
    s21_decimal result = {0};

    value_1.bits[0] = 155;
    value_2.bits[0] = 55;
    s21_decimal correct_result = {0};
    correct_result.bits[0] = 100;

    s21_sub(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], correct_result.bits[0]);
  }
  {
    // Второе число больше первого, результат отрицателен
    s21_decimal value_1 = {0};
    s21_decimal value_2 = {0};
    s21_decimal result = {0};
    value_1.bits[0] = 50;
    value_2.bits[0] = 150;
    s21_decimal correct_result = {0};
    correct_result.bits[0] = 100;
    set_sign(&correct_result, 1);  // Установка знака результата в отрицательный

    s21_sub(value_1, value_2, &result);
    int sign = get_sign(result);

    ck_assert_uint_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(sign, 1);
  }
  {
    // Вычитание отрицательных чисел с одинаковой степенью, результат
    // отрицателен
    s21_decimal value_1 = {0};
    s21_decimal value_2 = {0};
    s21_decimal result = {0};
    value_1.bits[0] = 150;
    value_2.bits[0] = 50;
    set_sign(&value_1, 1);
    set_sign(&value_2, 1);
    s21_decimal correct_result = {0};
    correct_result.bits[0] = 100;

    s21_sub(value_1, value_2, &result);
    int sign = get_sign(result);

    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(sign, 1);
  }
  {
    // Один отрицательный и один положительный, результат отрицателен
    s21_decimal value_1 = {0};
    s21_decimal value_2 = {0};
    s21_decimal result = {0};
    value_1.bits[0] = 50;
    value_2.bits[0] = 150;
    set_sign(&value_2, 1);

    s21_sub(value_1, value_2, &result);
    s21_decimal correct_result = {0};
    correct_result.bits[0] = 200;

    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    int sign_result = get_sign(result);
    ck_assert_int_eq(sign_result, 0);
  }
  {
    // Положительные числа, первое больше второго, степень одинакова
    s21_decimal result = {0};
    s21_decimal a = {{321, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, 0}};
    s21_decimal correct_result = {{198, 0, 0, 0}};

    ck_assert_int_eq((s21_sub(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    // Второе больше первого, степень одинаковая
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{444, 0, 0, MASK_MINUS}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{567, 0, 0, 0}};
    ck_assert_int_eq((s21_sub(a, b, &result)), 0);
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
    s21_decimal correct_result = {{198, 0, 0, 0}};

    ck_assert_int_eq((s21_sub(a, b, &result)), 0);
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
    s21_decimal correct_result = {{567, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_sub(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
  {
    s21_decimal result = {0};
    s21_decimal a = {{123, 0, 0, MASK_MINUS}};
    s21_decimal b = {{123, 0, 0, MASK_MINUS}};
    s21_decimal correct_result = {{0, 0, 0, MASK_MINUS}};
    ck_assert_int_eq((s21_sub(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
  }
  {
    // Положительное число минус отрицательное число
    s21_decimal result = {0};
    s21_decimal a = {{500, 0, 0, 0}};
    s21_decimal b = {{200, 0, 0, MASK_MINUS}};
    s21_decimal correct_result = {{700, 0, 0, 0}};
    ck_assert_int_eq((s21_sub(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
}
END_TEST

Suite *sub_suite(void) {
  Suite *s = suite_create("s21_sub");
  TCase *tc_sub = tcase_create("Sub");

  tcase_add_test(tc_sub, test_s21_sub);

  suite_add_tcase(s, tc_sub);

  return s;
}