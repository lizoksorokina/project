#include "tests.h"

int compare_numbers(float f, s21_decimal *check) {
  int flag;
  s21_decimal result = {0};
  flag = s21_from_float_to_decimal(f, &result);
  if (!flag) {
    ck_assert_int_eq(result.bits[0], check->bits[0]);
    ck_assert_int_eq(result.bits[1], check->bits[1]);
    ck_assert_int_eq(result.bits[2], check->bits[2]);
    ck_assert_int_eq(result.bits[3], check->bits[3]);
  }
  return flag;
}

START_TEST(test_from_float_to_decimal) {
  {
    float f = 10.0;
    s21_decimal result;
    s21_decimal check = {{10, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, 0);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
  }
  {
    float f = 3e15;
    s21_decimal result;
    s21_decimal check = {{1234567, 0x0, 0x0, 0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, 0);
    ck_assert_int_eq(s21_is_equal(result, check), 0);
  }
  {
    float f = -0.0f;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);

    ck_assert_int_eq(code, 0);
    ck_assert_int_eq(result.bits[0], check.bits[0]);
    ck_assert_int_eq(result.bits[1], check.bits[1]);
    ck_assert_int_eq(result.bits[2], check.bits[2]);
    ck_assert_int_eq(result.bits[3], check.bits[3]);
  }
  {
    float f = 2.28401628E-19f;
    s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}};
    ck_assert_int_eq(compare_numbers(f, &decimal_check), 0);
  }
  {
    float f = 5.92141241E+23f;
    s21_decimal decimal_check = {{0x0, 0xa800000, 0x7D64, 0x0}};
    ck_assert_int_eq(compare_numbers(f, &decimal_check), 0);
  }
  {
    s21_decimal dec = {0};
    float f = 1e-30f;
    s21_from_float_to_decimal(f, &dec);
    ck_assert_int_eq(dec.bits[0], 0);
    ck_assert_int_eq(dec.bits[1], 0);
    ck_assert_int_eq(dec.bits[2], 0);
    ck_assert_int_eq(dec.bits[3], 0);
  }
  {
    float src = 1.0 / 0.0;
    s21_decimal z = {{0u, 0u, 0u, 0u}};
    int n1 = s21_from_float_to_decimal(src, &z);
    char res1[1000], res2[1000] = "0 0 0 0";
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
    ck_assert_int_eq(n1, 1);
  }
  {
    float src = -1.596;
    s21_decimal z = {{0u, 0u, 0u, 0u}};
    int n1 = s21_from_float_to_decimal(src, &z);
    char res1[1000], res2[1000] = "1596 0 0 2147680256";
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
    ck_assert_int_eq(n1, 0);
  }
  {
    float src = 1 / 0.0;
    s21_decimal z = {{0u, 0u, 0u, 0u}};
    int n1 = s21_from_float_to_decimal(src, &z);
    char res1[1000], res2[1000] = "0 0 0 0";
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
    ck_assert_int_eq(n1, 1);
  }
}
END_TEST

Suite *from_float_to_decimal_suite(void) {
  Suite *s = suite_create("from_float_to_decimal");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_from_float_to_decimal);
  suite_add_tcase(s, tc_core);

  return s;
}
