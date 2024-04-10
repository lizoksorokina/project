#include "tests.h"

START_TEST(test_from_decimal_to_int) {
  {
    s21_decimal val = {{123456789, 0, 0, 0}};
    int res = 123456789;
    int tmp = 0;
    int *dst = &tmp;
    s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(*dst, res);
  }
  {
    s21_decimal val = {{1, 1, 0, 0}};
    int tmp = 0;
    int *dst = &tmp;
    int err = s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(err, 1);
    ck_assert_int_eq(tmp, 0);
  }
  {
    s21_decimal val = {{0, 0, 1, 0}};
    int tmp = 0;
    int *dst = &tmp;
    int err = s21_from_decimal_to_int(val, dst);
    ck_assert_int_eq(err, 1);
    ck_assert_int_eq(tmp, 0);
  }
  {
    s21_decimal value = {{49135648, 0, 0, 0}};
    set_exp(&value, 1);
    int dst;
    int check = 4913564;
    int return_value = s21_from_decimal_to_int(value, &dst);
    ck_assert_int_eq(dst, check);
    ck_assert_int_eq(return_value, 0);
  }
  {
    s21_decimal a = {{123, 0, 0, 0}};
    set_exp(&a, 1);
    int int_a;

    s21_from_decimal_to_int(a, &int_a);
    ck_assert_int_eq(int_a, 12);
  }
  {
    int a = 0;
    s21_decimal temp;
    init_decimal(&temp);
    temp.bits[0] = 1U;
    set_sign(&temp, 1);
    s21_from_decimal_to_int(temp, &a);
    ck_assert_int_eq(a, -1);

    a = 0;
    init_decimal(&temp);
    temp.bits[0] = 1U;
    temp.bits[3] = 0;
    s21_from_decimal_to_int(temp, &a);
    ck_assert_int_eq(a, 1);

    a = 0;
    init_decimal(&temp);
    temp.bits[0] = 123;
    temp.bits[1] = 123;
    int res = 0;
    res = s21_from_decimal_to_int(temp, &a);
    ck_assert_uint_eq(res, 1);
  }
}
END_TEST

Suite *from_decimal_to_int_suite(void) {
  Suite *s = suite_create("from_decimal_to_int");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_from_decimal_to_int);
  suite_add_tcase(s, tc_core);

  return s;
}