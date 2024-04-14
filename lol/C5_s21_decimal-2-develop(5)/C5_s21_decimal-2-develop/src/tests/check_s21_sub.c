#include "tests.h"

START_TEST(test_s21_sub) {
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
    s21_decimal correct_result = {{321, 0, 0, MASK_MINUS}};
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
    s21_decimal correct_result = {{444, 0, 0, MASK_MINUS}};

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
    // Переполнение при вычитании положительных чисел
    s21_decimal result = {0};
    s21_decimal a = {{0, 0, 0, 0}};           // 0
    s21_decimal b = {{1, 0, 0, MASK_MINUS}};  // -1
    ck_assert_int_eq((s21_sub(a, b, &result)),
                     -1);  // Ожидается код ошибки -1
  }
  {
    // Переполнение при вычитании отрицательных чисел
    s21_decimal result = {0};
    s21_decimal a = {{0, 0, 0, MASK_MINUS}};  // -0
    s21_decimal b = {{1, 0, 0, 0}};           // 1
    ck_assert_int_eq((s21_sub(a, b, &result)),
                     -1);  // Ожидается код ошибки -1
  }
  {
    // Результат вычитания равен нулю
    s21_decimal result = {0};
    s21_decimal a = {{123, 0, 0, MASK_MINUS}};
    s21_decimal b = {{123, 0, 0, MASK_MINUS}};
    s21_decimal correct_result = {{0, 0, 0, 0}};
    ck_assert_int_eq((s21_sub(a, b, &result)), 0);
    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
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
  {
    // Cдвиг на 4 бита
    s21_decimal a = {{DEC_MAX}};
    s21_decimal b = {{6, 0, 0, 0b00000000000000010000000000000000}};
    s21_decimal result = {0};
    s21_decimal correct_result = {{0b11111111111111111111111111111110, UINT_MAX,
                                   UINT_MAX,
                                   0b00000000000000000000000000000000}};

    ck_assert_int_eq((s21_sub(a, b, &result)), 0);

    ck_assert_int_eq(result.bits[0], correct_result.bits[0]);
    ck_assert_int_eq(result.bits[1], correct_result.bits[1]);
    ck_assert_int_eq(result.bits[2], correct_result.bits[2]);
    ck_assert_int_eq(result.bits[3], correct_result.bits[3]);
  }
}
END_TEST

Suite *sub_suite(void) {
  Suite *s = suite_create("sub");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_sub);
  suite_add_tcase(s, tc_core);

  return s;
}
