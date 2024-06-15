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
    int num1 = -32768;
    int num2 = 2;
    int res_origin = -16384;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    int num1 = 100;
    int num2 = 50;
    int res_origin = 2;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
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
    int num1 = 0;
    int num2 = 5;
    int res_origin = num1 / num2;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    s21_decimal dec1 = {{10.0e3, 0, 0, 0}};
    s21_decimal dec2 = {{2.00e2, 0, 0, 0}};

    int res_s21 = 0;
    int res = 50;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_int(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
  }
  {
    s21_decimal dec1 = {{1110, 0, 0, 0}};
    s21_decimal dec2 = {{0, 0, 0, 0}};

    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 3);
  }
  {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{50, 0, 0, 0}};
    s21_decimal res = {{0, 0, 0, 0}};
    s21_div(a, b, &res);
    ck_assert_int_eq(res.bits[0], 2);
    ck_assert_int_eq(res.bits[1], 0);
    ck_assert_int_eq(res.bits[2], 0);
    ck_assert_int_eq(res.bits[3], 0);
  }
  {
    int num1 = 2;
    int num2 = 2;
    int res_origin = 1;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
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
    int num1 = 2;
    int num2 = 2;
    int res_origin = 1;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal res = {0};
    ck_assert_int_eq(s21_div(a, b, &res), 3);
  }
  {
    int num1 = 100;
    int num2 = 50;
    int res_origin = 2;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    int num1 = -32768;
    int num2 = 2;
    int res_origin = -16384;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
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
    int num1 = 2;
    int num2 = 2;
    int res_origin = 1;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    int num1 = 0;
    int num2 = 5;
    int res_origin = num1 / num2;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_div(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    s21_decimal dec1 = {{100, 0, 0, 0}};
    s21_decimal dec2 = {{99999, 0, 0, 0}};

    float res_s21 = 0;
    float res = 100.0 / 99999.0;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
  }
  {
    s21_decimal dec1 = {{1000, 0, 0, 0}};  // 100.0
    s21_set_exp(dec1, &dec1, 1);
    s21_decimal dec2 = {{5, 0, 0, 0}};  // 0.5
    s21_set_exp(dec2, &dec2, 1);

    float res_s21 = 0.0;
    float res = 200;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq(res_s21, res);
  }
  {
    s21_decimal dec1;
    s21_decimal dec2;
    int tmp1 = -100;
    int tmp2 = -99999;
    float res_s21 = 0;
    float res = 0.00100001;
    s21_from_int_to_decimal(tmp1, &dec1);
    s21_from_int_to_decimal(tmp2, &dec2);
    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
  }
  {
    s21_decimal dec1 = {{1005, 0, 0, 0}};  // -100.5
    s21_set_exp(dec1, &dec1, 1);

    s21_set_bitt(&dec1, 127, 1);
    s21_decimal dec2 = {{999995, 0, 0, 0}};  // -99999.5
    s21_set_exp(dec2, &dec2, 1);

    s21_set_bitt(&dec2, 127, 1);

    float res_s21 = 0;
    float res = 0.001005005;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_float(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
  }
  {
    s21_decimal dec1 = {{10.0e3, 0, 0, 0}};
    s21_decimal dec2 = {{2.00e2, 0, 0, 0}};

    int res_s21 = 0;
    int res = 50;

    s21_decimal res1;
    s21_div(dec1, dec2, &res1);
    s21_from_decimal_to_int(res1, &res_s21);
    ck_assert_float_eq_tol(res_s21, res, 6);
  }
  {
    s21_decimal dec1 = {{1110, 0, 0, 0}};
    s21_decimal dec2 = {{0, 0, 0, 0}};

    s21_decimal res1;
    int res = s21_div(dec1, dec2, &res1);
    ck_assert_int_eq(res, 3);
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