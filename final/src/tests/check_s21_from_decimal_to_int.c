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
}
END_TEST

Suite *from_decimal_to_int_suite(void) {
  Suite *s = suite_create("from_decimal_to_int");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_from_decimal_to_int);
  suite_add_tcase(s, tc_core);

  return s;
}