// В этом файле не должно быть никаких других функций кроме функций библиотеки.
// Вспомогательные функции должны быть вынесены в utils.c

#include "s21_decimal.h"

#include "utils.h"

// Arithmetic Operators

int s21_add(s21_decimal a, s21_decimal b, s21_decimal *result) {
  int response = OK;
  int exp = normalize(&a, &b);
  int a_sign = get_sign(a), b_sign = get_sign(b);
  s21_decimal result_buffer = {{DEC_ZERO}};

  if (a_sign == b_sign) {
    int overflow = binary_add(a, b, &result_buffer);

    if (overflow) {
      if (exp > 0) {
        s21_banking_round_for_add(a, &result_buffer);
        exp--;
      } else {
        response = a_sign ? ERROR_TOO_SMALL : ERROR_TOO_BIG;
      }
    }

    if (a_sign) {
      set_sign(&result_buffer, 1);
    }

    set_exp(&result_buffer, exp);
  } else {
    s21_decimal negatiated = {{0, 0, 0, 0}};

    if (a_sign) {
      s21_negate(a, &negatiated);
      response = s21_sub(b, negatiated, &result_buffer);
    } else {
      s21_negate(b, &negatiated);
      response = s21_sub(a, negatiated, &result_buffer);
    }
  }

  if (response == 0) {
    copy_to_buffer(result_buffer, result);
  }

  return response;
}

int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *result) {
  // Инициализация результата нулями
  memset(result, 0, sizeof(s21_decimal));
  int res = 0, sign1 = s21_get_bit(a, 127), sign2 = s21_get_bit(b, 127);
  int scale1;

  // Проверка знаков чисел
  if (sign1 != sign2) {
    s21_set_bit(&b, 127, sign1);
    res = s21_add(a, b, result);
    scale1 = get_exp(a);
  } else {
    // Выравнивание масштабов чисел
    scale1 = normalize(&a, &b);
    // Выполнение вычитания в зависимости от модуля чисел
    if (s21_is_greater_or_equal(abs_dec(a), abs_dec(b))) {
      bit_substraction(a, b, result);
      s21_set_bit(result, 127, sign1);
    } else {
      bit_substraction(b, a, result);
      s21_set_bit(result, 127, sign2 == 0 ? 1 : 0);
    }
  }
  // Установка масштаба результата
  set_pow(*result, result, scale1);

  return res;
}

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result) {
  init_decimal(result);
  int total = 0;
  s21_decimal zero = {0};
  s21_decimal digit_num;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  int sign = 1;

  int degree = get_exp(a) + get_exp(b);
  if (get_sign(a) == get_sign(b)) sign = 0;
  set_sign(&a, 0);
  set_sign(&b, 0);
  if (!is_equal_simple(b, zero) && !is_equal_simple(a, zero)) {
    total = binary_mul(a, b, result);
    if (!total) {
      if (degree > 28) {
        while (degree != 29) {
          binary_div(*result, ten, result);
          degree--;
        }
        degree--;
        digit_num = binary_div(*result, ten, result);
        if (digit_num.bits[0] > 5) {
          binary_add(*result, one, result);
        } else if (digit_num.bits[0] == 5) {
          s21_decimal buff = {0};
          digit_num = binary_div(*result, ten, &buff);
          if (digit_num.bits[0] % 2 == 1) {
            binary_add(*result, one, result);
          }
        }
      }
      set_sign(result, sign);
      set_exp(result, degree);
    }
  }
  if (total == 1 && sign) total = 2;
  return total;
}

int s21_div(s21_decimal a, s21_decimal b, s21_decimal *result) {
  int res = 0;

  int error = 0;
  error = s21_is_overflow(a);
  if (error != 0 && s21_bit(a, 127) == 1) return 2;
  if (error != 0 && s21_bit(a, 127) == 0) return 1;
  error = s21_is_overflow(b);
  if (error != 0 && s21_bit(b, 127) == 1) return 2;
  if (error != 0 && s21_bit(b, 127) == 0) return 1;
  error = s21_exponent_check(a, b);
  if (error != 0) return 2;

  // проверяем, не равно ли a нулю
  if (s21_is_zero(b) == 0) return 3;

  // проверяем, равен ли a нулю, если да, децимал всегда
  // равен 0
  if (s21_is_zero(a) == 0) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;
  }

  // определяем знак  децимала (0 - плюс, 1 - минус)
  int sign = 0;
  if ((s21_bit(a, 127) == 1 && s21_bit(b, 127) == 0) ||
      (s21_bit(a, 127) == 0 && s21_bit(b, 127) == 1))
    sign = 1;

  // переводим всё в биг децималы и биг десятичные массивы
  s21_big_decimal big_a = {0};
  s21_big_decimal big_b = {0};
  s21_copy_decimal_to_bigdecimal(a, &big_a);
  s21_copy_decimal_to_bigdecimal(b, &big_b);

  int big_ten_array_a[90] = {0};
  int big_ten_array_b[90] = {0};
  s21_from_big_decimal_to_ten_array(big_a, big_ten_array_a);
  s21_from_big_decimal_to_ten_array(big_b, big_ten_array_b);
  int big_ten_array_result[90] = {0};

  // нужно избавиться от экспонент и превратить оба числа в "целые"
  // для этого находим разность экспонент и столько раз домножаем число с
  // меньшей экспонентой на 10 при этом обе экспоненты становятся равными нулю
  int exp_1 = s21_get_exp(a);
  int exp_2 = s21_get_exp(b);
  int diff_exp = exp_1 - exp_2;
  // у первой экспонента больше, поэтому двигаем вторую
  if (diff_exp > 0) {
    for (int i = 0; i < diff_exp; i++) s21_mul_big_ten_arr(big_ten_array_b);
  }
  // у второй экспонента больше, значит двигаем первую
  else if (diff_exp < 0) {
    for (int i = 0; i < -diff_exp; i++) s21_mul_big_ten_arr(big_ten_array_a);
  }

  // непосредственно деление мантисс (алгоритм как у обычного деления в столбик)
  int exp_rez =
      div_bigtenarr(big_ten_array_a, big_ten_array_b, big_ten_array_result);

  // проверяем мантиссу на переполнение
  int flag_owerflow_mantisa =
      s21_is_overflow_mantissa(exp_rez, big_ten_array_result);

  int remainder =
      0;  // запоминает последнюю усеченную цифру (для последующего округления)
  const int max_ten_array[] = {5, 3, 3, 0, 5, 9, 3, 4, 5, 3, 9, 5, 7, 3, 3,
                               4, 6, 2, 4, 1, 5, 2, 6, 1, 8, 2, 2, 9, 7, 0};
  if (flag_owerflow_mantisa == 0) {
    int max_big_ten_array[90] = {0};
    for (int i = 0; i < 30; i++) max_big_ten_array[i] = max_ten_array[i];

    // пока наш большой десятичный массив больше максимально возможного,
    // отрезаем числа после запятой плюс запоминаем последнее усеченное число,
    // чтобы потом применить банковское округление
    while (s21_compare_bigten_array(big_ten_array_result, max_big_ten_array) ==
               1 ||
           exp_rez > 28) {
      exp_rez--;
      remainder = big_ten_array_result[0];
      for (int j = 0; j < 89; j++)
        big_ten_array_result[j] = big_ten_array_result[j + 1];
      big_ten_array_result[89] = 0;
    }
  } else {
    if (sign == 0)
      res = 1;
    else
      res = 2;
  }

  // применяем банковское округление
  s21_banking_round_for_mult(big_ten_array_result, remainder);

  // переводим результат обратно в биг децимал
  s21_big_decimal copy = {0};
  s21_from_ten_array_to_big_decimal(big_ten_array_result, &copy);

  // превращаем биг децимал в обычный децимал
  for (int i = 0; i < 3; i++) result->bits[i] = copy.bits[i];
  s21_set_bitt(result, 127, sign);
  s21_set_exp(*result, result, exp_rez);

  return res;
}

// Comparison Operators

int s21_is_less(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) == 2) res = 1;
  return res;
}

// Возвращает:
//  0 - равно
//  1 - первое больше
//  2 - первое меньше
//  -1 - ошибка

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) != 1) res = 1;
  return res;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) == 1) res = 1;
  return res;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) != 2) res = 1;
  return res;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) == 0) res = 1;
  return res;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (s21_compare_two_decimals(a, b) != 0) res = 1;
  return res;
}

// Convertors and parsers

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  if (dst) {
    init_decimal(dst);
    if (src < 0) {
      set_sign(dst, 1);
    }
    dst->bits[0] = src > 0 ? src : ~(src - 1);
  } else
    error++;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int codeError = check_F2D(src, dst);
  if (!codeError && dst) {
    init_decimal(dst);
    char sci_src[64];
    int sign = src < 0.f ? 1 : 0;
    sprintf(sci_src, "%.6E", fabsf(src));
    int exp = get_float_exp_from_string(sci_src);
    if (exp <= -23) {
      int float_precision = exp + 28;
      sprintf(sci_src, "%.*E", float_precision, fabsf(src));
    }
    if (abs(exp) > 28) codeError = 1;
    if (!codeError) {
      init_decimal(dst);
      unsigned int newDec = get_rid_ofZeros(sci_src, &exp);
      dst->bits[0] = newDec;
      if (exp > 0)
        get_pow_10_multiDec(exp, dst);
      else
        set_exp(dst, abs(exp));
      if (sign) set_sign(dst, 1);
    }
  } else
    codeError = 1;
  return codeError;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst && src.bits[1] == 0 && src.bits[2] == 0 && get_bit(src, 31) == 0) {
    int expo = get_exp(src);
    if (expo <= 28) {
      int divisor = ipow(10, expo);
      *dst = src.bits[0] / divisor;
      *dst *= get_sign(src) ? -1 : 1;
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0, expo = get_exp(src);
  // s21_decimal mx_d = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal mn_d = {{4294967295u, 4294967295u, 4294967295u, 0}};
  set_sign(&mn_d, 1);
  // if (!(s21_is_less_or_equal(src, mx_d) || s21_is_greater_or_equal(src,
  // mn_d))) error = 1;
  if (expo > 28) error = 1;
  if (dst && !error) {
    int sign = (get_sign(src) ? -1 : 1);
    int mantiss = get_exp(src);
    double_t temp = 0.0;
    for (int a = 0; a <= 95; a++) {
      if (get_bit(src, a) == 1) temp += pow(2, a);
    }
    *dst = (float)(temp / pow(10, mantiss) * sign);
  } else
    error = 1;
  return error;
}

// Another functions

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int zero_value = 1;
  for (int i = 95; i >= 0 && zero_value; i--)
    if (s21_get_bit(value, i)) zero_value = 0;

  error = s21_truncate(value, result);

  if (!error && !zero_value && s21_get_bit(*result, 127) && get_pow(value)) {
    int i = 0;
    while (s21_get_bit(*result, i)) {
      s21_set_bit(result, i, 0);
      i++;
    }
    s21_set_bit(result, i, 1);
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int zero_value = 1;  // Проверка, что дробная часть равна нулю
  for (int i = 95; i >= 0 && zero_value; i--)
    if (s21_get_bit(value, i)) zero_value = 0;
  error = s21_truncate(value, result);

  // Если нет ошибок и дробная часть не ноль и экспонента не ноль
  if (!error && !zero_value && get_pow(value)) {
    s21_decimal diff = {0};
    s21_sub(
        value, *result,
        &diff);  // Вычисляем разницу между исходным числом и его округлением
    s21_decimal zerohalf = {0};             // Половина от 0.5
    s21_from_int_to_decimal(5, &zerohalf);  // Конвертируем 0.5 в Decimal
    set_pow(zerohalf, &zerohalf, 1);  // Устанавливаем экспоненту

    if (s21_is_greater_or_equal(abs_dec(diff), zerohalf)) {
      int i = 0;
      while (s21_get_bit(*result, i)) {
        s21_set_bit(result, i, 0);
        i++;
      }
      s21_set_bit(result, i, 1);
    }
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int int_part = 0;
  *result = value;

  for (int i = 126; i >= 96 && !error; i--) {
    if ((i > 119 || i < 112) && s21_get_bit(value, i))
      error = 1;
    else if ((i < 120 && i > 111)) {
      int_part += s21_get_bit(value, i) * pow(2, i - 112);
      if (int_part > 28) error = 1;
    }
  }
  if (!error && int_part) {
    for (int i = 119; i > 111; i--) s21_set_bit(result, i, 0);
    for (int i = 0; i < int_part; i++) div_by_ten(result);
  }
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  *result = value;

  for (int i = 126; i > 95 && !error; i--) {
    if ((i > 119 || (i < 112 && i > 95)) && s21_get_bit(value, i)) error = 1;
  }
  if (!error) s21_set_bit(result, 127, !s21_get_bit(value, 127));

  return error;
}