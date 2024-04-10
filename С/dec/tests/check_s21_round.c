#include "tests.h"

START_TEST(test_round) {
  {
    // 79228162514264337593543950335
    s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

    uint8_t flag = s21_round(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x11111111}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;

    uint8_t flag = s21_round(dec1, &result);
    ck_assert_int_eq(flag, 1);
  }
  {
    // -0
    s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x80000000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x80000000}};

    uint8_t flag = s21_round(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
  {
    // 0
    s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x00000000}};
    s21_decimal result;
    for (int i = 0; i < 4; i++) result.bits[i] = 0;
    s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x00000000}};

    uint8_t flag = s21_round(dec1, &result);
    uint8_t res = s21_is_equal(result, dec2);
    ck_assert_int_eq(flag, 0);
    ck_assert_int_eq(res, 1);
  }
}
END_TEST

Suite *round_suite(void) {
  Suite *s = suite_create("round");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_round);
  suite_add_tcase(s, tc_core);

  return s;
}