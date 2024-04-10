#include "tests.h"

int main(void) {
  int number_failed;

  Suite *s_add, *s_sub, *s_mul, *s_div, *s_is_less, *s_is_less_or_equal,
      *s_is_greater, *s_is_greater_or_equal, *s_is_equal, *s_is_not_equal,
      *s_from_int_to_decimal, *s_from_float_to_decimal, *s_from_decimal_to_int,
      *s_from_decimal_to_float, *s_floor, *s_round, *s_truncate, *s_negate;
  SRunner *sr;

  s_add = add_suite();
  //  s_sub = sub_suite();
  s_mul = mul_suite();
  s_div = div_suite();

  s_is_less = is_less_suite();
  s_is_less_or_equal = is_less_or_equal_suite();
  s_is_greater = is_greater_suite();
  s_is_greater_or_equal = is_greater_or_equal_suite();
  s_is_equal = is_equal_suite();
  s_is_not_equal = is_not_equal_suite();

  s_from_int_to_decimal = from_int_to_decimal_suite();
  s_from_float_to_decimal = from_float_to_decimal_suite();
  s_from_decimal_to_int = from_decimal_to_int_suite();
  s_from_decimal_to_float = from_decimal_to_float_suite();

  s_floor = floor_suite();
  s_round = round_suite();
  s_truncate = truncate_suite();
  s_negate = negate_suite();

  sr = srunner_create(s_add);
  //  srunner_add_suite(sr, s_sub);
  srunner_add_suite(sr, s_mul);
  srunner_add_suite(sr, s_div);
  srunner_add_suite(sr, s_is_less);

  srunner_add_suite(sr, s_is_less_or_equal);
  srunner_add_suite(sr, s_is_greater);
  srunner_add_suite(sr, s_is_greater_or_equal);
  srunner_add_suite(sr, s_is_equal);
  srunner_add_suite(sr, s_is_not_equal);

  srunner_add_suite(sr, s_from_int_to_decimal);
  srunner_add_suite(sr, s_from_float_to_decimal);
  srunner_add_suite(sr, s_from_decimal_to_int);
  srunner_add_suite(sr, s_from_decimal_to_float);

  srunner_add_suite(sr, s_floor);
  srunner_add_suite(sr, s_round);
  srunner_add_suite(sr, s_truncate);
  srunner_add_suite(sr, s_negate);

  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}