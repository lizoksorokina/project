#include "tests.h"

START_TEST(test_from_decimal_to_float) {
  {
    s21_decimal dec;
    int result = 0;
    float number = 0.0;
    long int c = 2147483648;
    dec.bits[0] = 1812;
    dec.bits[1] = 0;
    dec.bits[2] = 0;
    dec.bits[3] = c;
    result = s21_from_decimal_to_float(dec, &number);
    ck_assert_float_eq(number, -1812);
    ck_assert_int_eq(result, 0);
  }
  {
    s21_decimal src1;
    float src2;
    float *srcp = &src2;
    src1.bits[0] = 0b00000000000000000000000000101101;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000010000000000000000;
    s21_from_decimal_to_float(src1, srcp);
    char var3str[1000];
    char result[1000];
    snprintf(var3str, sizeof(var3str), "%.6f", -4.5);
    snprintf(result, sizeof(result), "%f", src2);
    ck_assert_str_eq(result, var3str);
  }
  {
    s21_decimal src1;
    float src2;
    float *srcp = &src2;
    src1.bits[0] = 0b01100101111011101101100101011111;
    src1.bits[1] = 0b01011100001001010100001101000110;
    src1.bits[2] = 0b00000000000000000000000000000001;
    src1.bits[3] = 0b00000000000100110000000000000000;
    s21_from_decimal_to_float(src1, srcp);
    char var3str[1000];
    char result[1000];
    snprintf(var3str, sizeof(var3str), "%.6f", 2.50865312689741);
    snprintf(result, sizeof(result), "%f", src2);
    ck_assert_str_eq(result, var3str);
  }
  {
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int code = s21_from_decimal_to_float(decimal, NULL);
    ck_assert_int_eq(code, 1);
  }
  {
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);
    ck_assert_int_eq(code, 1);
  }
  {
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);
    ck_assert_int_eq(code, 1);
  }
  {
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    float result;
    int code = s21_from_decimal_to_float(decimal, &result);
    ck_assert_int_eq(code, 1);
  }
  {
    s21_decimal value = {{0x0, 0x5553F400, 0x373, 0x20000}};
    float check = 162946235432826621132.80f;
    float result = 0;
    int return_value = s21_from_decimal_to_float(value, &result);
    ck_assert_float_eq(result, check);
    ck_assert_int_eq(return_value, 0);
  }
  {
    s21_decimal value = {{0x0, 0x5553F400, 0x373, 0x80020000}};
    float check = -162946235432826621132.80f;
    float result = 0;
    int return_value = s21_from_decimal_to_float(value, &result);
    ck_assert_float_eq(result, check);
    ck_assert_int_eq(return_value, 0);
  }
  {
    s21_decimal value = {{0x0, 0x12345678, 0x9ABCDEF0, 0x10000}};
    float check = 4.78890227e+27f;
    float result = 0;
    int return_value = s21_from_decimal_to_float(value, &result);
    ck_assert_float_eq(result, check);
    ck_assert_int_eq(return_value, 0);
  }
}
END_TEST

Suite *from_decimal_to_float_suite(void) {
  Suite *s = suite_create("from_decimal_to_float");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_from_decimal_to_float);
  suite_add_tcase(s, tc_core);

  return s;
}