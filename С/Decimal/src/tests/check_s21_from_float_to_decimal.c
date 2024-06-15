#include "tests.h"

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
  {
    float src = 56.986;
    s21_decimal z = {{0u, 0u, 0u, 0u}};
    int n1 = s21_from_float_to_decimal(src, &z);
    char res1[1000], res2[1000] = "56986 0 0 196608";
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
    ck_assert_int_eq(n1, 0);
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
  {
    double src = 0.0;
    s21_decimal z = {{0u, 0u, 0u, 0u}};
    int n1 = s21_from_float_to_decimal(src, &z);
    char res1[1000], res2[1000] = "0 0 0 0";
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
    ck_assert_int_eq(n1, 0);
  }
  {
    long double src = 0.;
    s21_decimal z = {{0u, 0u, 0u, 0u}};
    int n1 = s21_from_float_to_decimal(src, &z);
    char res1[1000], res2[1000] = "0 0 0 0";
    snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
             z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
    ck_assert_int_eq(n1, 0);
  }
  {
    s21_decimal temp;
    init_decimal(&temp);
    float a = 0.0f;
    s21_from_float_to_decimal(a, &temp);
    ck_assert_int_eq(temp.bits[0], 0);
    ck_assert_int_eq(get_sign(temp), 0);

    init_decimal(&temp);
    a = 20.0;
    s21_from_float_to_decimal(a, &temp);
    ck_assert_int_eq(temp.bits[0], 20);
    ck_assert_int_eq(get_sign(temp), 0);
    ck_assert_int_eq(get_exp(temp), 0);

    init_decimal(&temp);
    a = -20.0;
    s21_from_float_to_decimal(a, &temp);
    ck_assert_int_eq(temp.bits[0], 20);
    ck_assert_int_eq(get_sign(temp), 1);
    ck_assert_int_eq(get_exp(temp), 0);

    init_decimal(&temp);
    a = NAN;
    int res = s21_from_float_to_decimal(a, &temp);
    ck_assert_int_eq(res, 1);

    init_decimal(&temp);
    a = 1.0 / 0.0;
    res = 0;
    res = s21_from_float_to_decimal(a, &temp);
    ck_assert_int_eq(res, 1);

    init_decimal(&temp);
    a = -1.0 / 0.0;
    res = 0;
    res = s21_from_float_to_decimal(a, &temp);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = 1.0 / 0.0;
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = -1.0 / 0.0;
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = NAN;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = 248e-30;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_uint_eq(dec.bits[0], 2);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 1835008);

    ck_assert_int_eq(res, 0);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = 248e30;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);

    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = -248e30;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_uint_eq(dec.bits[0], 0);
    ck_assert_uint_eq(dec.bits[1], 0);
    ck_assert_uint_eq(dec.bits[2], 0);
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = 248e26;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_uint_eq(dec.bits[0],
                      3758096384);  // 11100000000000000000000000000000
    ck_assert_uint_eq(dec.bits[1],
                      3788270668);  // 11100001110011000110110001001100

    ck_assert_uint_eq(dec.bits[2],
                      1344410693);  // 1010000001000100001010001000101
    // 10100000010001000010100010001011110000111001100011011000100110011100000000000000000000000000000
    // конвертируется в 24800000000000000000000000000
    ck_assert_uint_eq(dec.bits[3], 0);
    ck_assert_int_eq(res, 0);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = 7.922815e28;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_int_eq(res, 0);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = 7.922816e28;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_int_eq(res, 0);
  }
  {
    s21_decimal dec = {{0u, 0u, 0u, 0u}};
    float a = -248e26;
    int res = s21_from_float_to_decimal(a, &dec);
    ck_assert_uint_eq(dec.bits[0], 3758096384);
    ck_assert_uint_eq(dec.bits[1], 3788270668);

    ck_assert_uint_eq(dec.bits[2], 1344410693);
    ck_assert_uint_eq(get_sign(dec), 1);

    ck_assert_int_eq(res, 0);
  }
  {
    float inp = -1.078071E+10;
    s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
    int error = s21_from_float_to_decimal(inp, &out);
    s21_decimal res = {{0x82949470, 0x00000002, 0x00000000, 0x80000000}};
    for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
    ck_assert_int_eq(error, 0);
  }
  {
    float inp = -5.447201E-28;
    s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
    int error = s21_from_float_to_decimal(inp, &out);
    s21_decimal res = {{0x00000005, 0x00000000, 0x00000000, 0x801C0000}};
    for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
    ck_assert_int_eq(error, 0);
  }
  {
    float inp = 0.00000000000000000000000858598287381972;
    s21_decimal out = {{32131, 1231435, 2311, 3121441}};
    int error = s21_from_float_to_decimal(inp, &out);
    ck_assert_int_eq(error, 1);
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
