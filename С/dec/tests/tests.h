#ifndef S21_TESTS
#define S21_TESTS

#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"
#include "../utils.h"

Suite *add_suite(void);
Suite *sub_suite(void);
Suite *mul_suite(void);
Suite *div_suite(void);

Suite *is_less_suite(void);
Suite *is_less_or_equal_suite(void);
Suite *is_greater_suite(void);
Suite *is_greater_or_equal_suite(void);
Suite *is_equal_suite(void);
Suite *is_not_equal_suite(void);

Suite *from_int_to_decimal_suite(void);
Suite *from_float_to_decimal_suite(void);
Suite *from_decimal_to_int_suite(void);
Suite *from_decimal_to_float_suite(void);

Suite *floor_suite(void);
Suite *round_suite(void);
Suite *truncate_suite(void);
Suite *negate_suite(void);

#endif