#include "utils.h"

int s21_get_exp(s21_decimal value) {
  value.bits[3] = value.bits[3] << 1;
  value.bits[3] = value.bits[3] >> 17;
  return value.bits[3];
}

// функция возвращает значение бита в указанной позиции
int s21_bit(s21_decimal value, int position) {  //-1 ошибка
  int res = -1;
  if (position > -1 && position < 128) {
    int byte = position / 32;
    int bit = position % 32;
    res = value.bits[byte] & ((unsigned int)1 << bit);
    if (res != 0) res = 1;
  }
  return res;
}

// проверка экспоненты если вернула 0, то все ок в остальных случаях превышает
int s21_exponent_check(s21_decimal a, s21_decimal b) {
  int res = 0;
  if ((s21_get_exp(a) > 28 && s21_bit(a, 127) == 0) ||
      (s21_get_exp(b) > 28 && s21_bit(b, 127) == 0))
    res = 1;
  else if ((s21_get_exp(a) > 28 && s21_bit(a, 127) == 1) ||
           (s21_get_exp(b) > 28 && s21_bit(b, 127) == 1))
    res = 2;
  return res;
}

// для копирования значения числа типа  s21_decimal  в структуру s21_big_decimal
int s21_copy_decimal_to_bigdecimal(s21_decimal src,
                                   s21_big_decimal *dst) {  // 0 - OK, 1 - ERROR
  int res = OK;
  if (dst != NULL) {
    for (int i = 0; i < 3; i++) dst->bits[i] = src.bits[i];

    for (int i = 3; i < 7; i++) dst->bits[i] = 0;

    dst->bits[7] = src.bits[3];

  } else
    res = NULL_POINTER_EXEPTION;
  return res;
}
void s21_from_big_decimal_to_ten_array(s21_big_decimal value, int result[]) {
  int add[90] = {0};
  add[0] = 1;
  for (int i = 0; i < 224; i++) {
    if (s21_bit_big_decimal(value, i)) {
      s21_sum_of_ten_array_for_big_decimal(result, add);
    }
    s21_sum_of_ten_array_for_big_decimal(add, add);
  }
}

// функция возвращает значение бита в указанной позиции
int s21_bit_big_decimal(s21_big_decimal value,
                        int position) {  // -1 - ERROR, position 0-127
  int res = -1;
  if ((position > -1 && position < 256)) {
    int byte = position / 32;
    int bit = position % 32;
    res = value.bits[byte] & ((unsigned int)1 << bit);
    if (res != 0) res = 1;
  }
  return res;
}

void s21_sum_of_ten_array_for_big_decimal(int a[], const int b[]) {
  int remainder = 0;
  for (int i = 0; i < 90; i++) {
    int res = a[i] + b[i] + remainder;
    a[i] = res % 10;
    remainder = res / 10;
  }
}
// Сравнивает два десятичных массива, если первое больше, то возвращае  1, если
// второе больше  -1, если равны - 0
int s21_compare_bigten_array(const int a[], const int b[]) {
  int res = 0;
  for (int i = 89; i >= 0; i--) {
    if (a[i] > b[i]) {
      res = 1;
      break;
    } else if (b[i] > a[i]) {
      res = -1;
      break;
    }
  }
  return res;
}

int s21_compare_two_decimals(s21_decimal a, s21_decimal b) {
  int res = 1;

  int flag_eq = 1;

  if (s21_is_zero(a) == 0 && s21_is_zero(b) == 0) return 0;

  for (int i = 0; i < 4; i++) {  // цикл по байтам
    if (a.bits[i] != b.bits[i]) {  // если хотя бы один символ не равен
      flag_eq = 0;
      break;
    }
  }
  if (flag_eq == 1) return 0;  // если равны

  if (s21_exponent_check(a, b) != 0)
    return -1;  // если фун вернула не 0, то ошибка эксп

  int sign_1 = s21_bit(a, 127);  // получение знаков
  int sign_2 = s21_bit(b, 127);
  if (sign_1 == 0 && sign_2 == 1)
    return 1;
  else if (sign_1 == 1 && sign_2 == 0)
    return 2;

  s21_big_decimal big_1 = {0};
  s21_big_decimal big_2 = {0};
  s21_copy_decimal_to_bigdecimal(a, &big_1);
  s21_copy_decimal_to_bigdecimal(b, &big_2);
  int array_1[90] = {0};
  int array_2[90] = {0};
  s21_from_big_decimal_to_ten_array(
      big_1, array_1);  // преобр числа в массив десятичных цифр
  s21_from_big_decimal_to_ten_array(big_2, array_2);
  int exp_1 = s21_get_exp(a);
  int exp_2 = s21_get_exp(b);

  int difference = exp_1 - exp_2;  // вычисление разницы между эксп

  if (difference > 0) {  // если разн положит сдвиг вправо 2-го числа
    for (int i = 0; i < difference;
         i++) {  // Цикл для нормализации массива с меньшей экспонентой.
      for (int j = 89; j > 0; j--) array_2[j] = array_2[j - 1];
      array_2[0] = 0;
    }
  } else if (difference < 0) {  // если разн отрицат сдвиг вправо 1-го числа
    for (int i = 0; i < -difference;
         i++) {  // Цикл для нормализации массива с большей экспонентой.
      for (int j = 89; j > 0; j--) array_1[j] = array_1[j - 1];
      array_1[0] = 0;
    }
  }
  // сравнение
  int compare = s21_compare_bigten_array(array_1, array_2);
  if ((compare == 1 && sign_1 == 0) || (compare == -1 && sign_1 == 1))
    res = 1;
  else if ((compare == -1 && sign_1 == 0) || (compare == 1 && sign_1 == 1))
    res = 2;
  else if (compare == 0)
    res = 0;

  return res;
}
// проверка на переполнение
int s21_is_overflow(s21_decimal value) {
  int res = 0;

  if (value.bits[0] == INFINITY || value.bits[1] == INFINITY ||
      value.bits[2] == INFINITY) {  // проверка в мантиссах и эксп
    if (s21_bit(value, 127) == 0)  // положительно переполнение
      res = 1;
    else
      res = 2;  // отрицательное переполнение
  }

  return res;
}
// возвращает 1 если число !=0
int s21_is_zero(s21_decimal value) {
  return !(value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

void s21_set_to_zero(s21_decimal *value) {
  for (int i = 0; i <= 3; i++) value->bits[i] = 0;
}

// просто умножает большой десятичный массив на 10 // сдвиг вправо на 1 и добавл
//  0 в крайнюю левую позицию
void s21_mul_big_ten_arr(int value[]) {
  for (int j = 89; j > 0; j--) value[j] = value[j - 1];
  value[0] = 0;
}
// проверка большего на нул
int s21_is_zero_bigarr(const int array[]) {
  int res = 1;
  for (int i = 0; i < 90; i++) {
    if (array[i] != 0) {
      res = 0;
      break;
    }
  }
  return res;
}

// сложение двух массивов
void s21_sum_of_bigtenarr(int value_1[], const int value_2[]) {
  int remain = 0;  // для хранения ост от предыдущего разряда
  for (int i = 0; i < 90; i++) {
    int res = value_1[i] + value_2[i] + remain;
    value_1[i] = res % 10;
    remain = res / 10;
  }

}  // функция выполняет вычитание одного большого десятичного массива из другого
   // с операцией заема
int s21_sub_of_bigtenarr(int value_1[], const int value_2[]) {
  int error = 0;
  for (int i = 0; i < 90; i++) {
    if (value_1[i] < value_2[i]) {
      value_1[i] += 10;
      if (i != 89)
        value_1[i + 1]--;
      else
        error = 1;
    }
    value_1[i] -= value_2[i];
  }
  return error;
}
int div_bigtenarr(const int value_1[], int value_2[], int result[]) {
  int res_exp = 0;  // для хран. рез эксп
  int c = 0;
  int a[90] = {0};  // для хранения уменьшаемого
  int b[90] = {0};  // для хранения вычитаемого
  int ab_size = 0;
  int count_res = 0;
  int reverse_result[90] = {0};
  // нахождение первого индекса числа в массиве
  for (int i = 89; i >= 0; i--) {
    if (value_1[i] != 0) {
      c = i;
      break;
    }
  }
  // нахождение sizeab
  for (int i = 89; i >= 0; i--) {
    if (value_2[i] != 0) {
      ab_size = i + 1;
      break;
    }
  }
  if (ab_size > c + 1) ab_size = c + 1;
  // определяем изначальное а (переписываем первые size_of_ab цифр из value_1)
  for (int i = 0; i < ab_size; i++) {
    a[i] = value_1[c - ab_size + 1 + i];
  }
  c = c - ab_size + 1;
  while (s21_is_zero_bigarr(a) == 0 || c != 0) {
    // изначально b это и есть value_2
    for (int i = 0; i < 89; i++) b[i] = value_2[i];

    int quotient = 1;  // частное на каждом шаге

    int counter_of_null = 0;
    // если а меньше b, то в а сносим ещё одну цифру
    if (s21_compare_bigten_array(a, b) == -1) {
      // если дошли до конца и больше сносить нечего, то сносим 0, а
      // результирующую экспоненту увеличивает на 1
      if (c == 0) {
        s21_mul_big_ten_arr(a);
        res_exp++;

        if (a[0] == 0)
          counter_of_null++;
        else
          counter_of_null = 0;
      }
      // если есть, что сносить, то сносим цифру под индексом counter-1, сам
      //  counter сдвигаем дальше
      else {
        s21_mul_big_ten_arr(a);
        c--;
        a[0] = value_1[c];

        if (a[0] == 0)
          counter_of_null++;
        else
          counter_of_null = 0;
      }
    }

    while (s21_compare_bigten_array(a, b) == -1) {
      quotient = 1;
      // если дошли до конца и больше сносить нечего, то сносим 0, а
      // результирующую экспоненту увеличивает на 1
      if (c == 0) {
        for (int i = 0; i < counter_of_null; i++) {
          reverse_result[count_res] = 0;
          count_res++;
        }
        break;

        s21_mul_big_ten_arr(a);
      }
      // если есть, что сносить, то сносим цифру под индексом counter-1, сам
      //  counter сдвигаем дальше
      else {
        s21_mul_big_ten_arr(a);
        c--;
        a[0] = value_1[c];

        if (a[0] == 0)
          counter_of_null++;
        else
          counter_of_null = 0;
      }
    }

    // к b прибавляем value_2 до тех пор, пока b не станет максимально
    // возможным, но все еще меньше a
    while (s21_compare_bigten_array(a, b) == 1) {
      s21_sum_of_bigtenarr(b, value_2);
      quotient++;
    }
    // если перестарались и теперь b стало больше a, вычитаем один value_2 из b
    // обратно
    if (s21_compare_bigten_array(a, b) == -1) {
      s21_sub_of_bigtenarr(b, value_2);
      quotient--;
    }

    // записываем quotient в результат
    if (quotient != 0) {
      reverse_result[count_res] = quotient;
      count_res++;
    }

    // вычитаем b из а, теперь а это результат вычитания
    s21_sub_of_bigtenarr(a, b);

    if (count_res == 90) break;
  }

  // перенесем из revers_result в нормальный result (но следим за количеством
  // записанных чисел)
  int count_tmp = 0;
  for (int i = count_res - 1; i >= 0; i--) {
    result[count_tmp] = reverse_result[i];
    count_tmp++;
  }

  if (res_exp > 89) res_exp = 89;

  return res_exp;
}
// Сравнивает два десятичных массива, если первое больше, то возвращае т 1, если
// второе больше - -1, если равны - 0
int s21_compare_ten_array(const int a[], const int b[]) {
  int res = 0;
  for (int i = 29; i >= 0; i--) {
    if (a[i] > b[i]) {
      res = 1;
      break;
    } else if (b[i] > a[i]) {
      res = -1;
      break;
    }
  }
  return res;
}
// возвращает 1 если переполнено
int s21_is_overflow_mantissa(int res_exp, const int big_ten_array[]) {
  int flag = 0;
  // нужно проверить, вмещается ли целая часть в мантиссу (сравнить с
  // максимальным беззнаковым инт децимала в рамках десятичного массива),
  //  остальное (цифры после запятой) при переводе в обычный децимал можно
  //  отбросить, применив банковское округление
  int max_ten_array[] = {5, 3, 3, 0, 5, 9, 3, 4, 5, 3, 9, 5, 7, 3, 3,
                         4, 6, 2, 4, 1, 5, 2, 6, 1, 8, 2, 2, 9, 7, 0};
  int mantisa_ten_array[90] = {0};
  int counter = 0;
  for (int i = res_exp; i < 90; i++) {
    mantisa_ten_array[counter] = big_ten_array[i];
    if (counter >= 28 && big_ten_array[i] != 0) {
      flag = 1;
      break;
    }
    counter++;
  }
  if (s21_compare_ten_array(mantisa_ten_array, max_ten_array) == 1) flag = 1;

  return flag;
}
// Производит банковское округление, в зависимости от остатка (следующего числа,
// не вошедшего в конечный результат) Изменяет непосредственно большой
// десятичный массив
void s21_banking_round_for_mult(int big_ten_array[], int remainder) {
  int one[90] = {0};
  one[0] = 1;
  if ((remainder > 5) || (remainder == 5 && big_ten_array[0] % 2 == 1))
    s21_sum_of_ten_array_for_big_decimal(big_ten_array, one);
}

void s21_banking_round_for_add(s21_decimal value_1, s21_decimal *result) {
  int reminder = 0;
  int is_even = 0;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal response = {{DEC_ZERO}};
  s21_decimal response_1 = {{DEC_ZERO}};
  s21_decimal response_2 = {{DEC_ZERO}};
  s21_decimal divider = {{10, 0, 0, 0}};

  s21_decimal reminder_1 = binary_div(value_1, divider, &response_1);
  s21_decimal reminder_2 = binary_div(value_1, divider, &response_2);

  reminder = reminder_1.bits[0] + reminder_2.bits[0];
  binary_add(response_1, response_2, &response);

  if (reminder > 10) {
    binary_add(response, one, &response);
    reminder /= 10;
  }

  is_even = get_bit(*result, 0);

  if ((reminder == 5 && !is_even) || reminder > 5) {
    binary_add(response, one, &response);
  }

  copy_to_buffer(response, result);
}

int s21_is_zero_array_for_big_decimal(const int a[]) {
  int res = 1;
  for (int i = 0; i < 90; i++) {
    if (a[i] != 0) {
      res = 0;
      break;
    }
  }
  return res;
}
int s21_set_bitt_for_big_decimal(
    s21_big_decimal *result, int position,
    int value) {  // 0 - OK, 1 - ERROR, position 0-127
  int res = 0;
  if ((result != NULL) && (position > -1 && position < 256) &&
      (value == 0 || value == 1)) {
    int byte = position / 32;
    int bit = position % 32;
    if (value == 1)
      result->bits[byte] |= (1 << bit);
    else
      result->bits[byte] &= ~(1 << bit);
  } else
    res = 1;
  return res;
}
int s21_div_tenarray_for_big_decimal(int value[]) {
  int res[90] = {0};
  int flag_start = 0;
  int remainder = 0, quotient = 0;
  for (int i = 89; i >= 0; i--) {
    if (flag_start == 0 && value[i] == 0)
      continue;
    else {
      flag_start = 1;
      quotient = value[i] + (remainder * 10);
      res[i] = quotient / 2;
      remainder = quotient % 2;
    }
  }

  for (int i = 0; i <= 89; i++) value[i] = res[i];

  return remainder;
}

void s21_from_ten_array_to_big_decimal(int array[], s21_big_decimal *result) {
  s21_big_decimal copy_result = {0};
  int i = 0;
  while (s21_is_zero_array_for_big_decimal(array) != 1) {
    s21_set_bitt_for_big_decimal(&copy_result, i,
                                 s21_div_tenarray_for_big_decimal(array));
    i++;
  }

  for (int j = 0; j < 96; j++) {
    s21_set_bitt_for_big_decimal(result, j,
                                 s21_bit_big_decimal(copy_result, j));
  }
}
int s21_set_bitt(s21_decimal *result, int position,
                 int value) {  // 0 - OK, 1 - ERROR, position 0-127
  int res = 0;
  if ((result != NULL) && (position > -1 && position < 128) &&
      (value == 0 || value == 1)) {
    int byte = position / 32;
    int bit = position % 32;
    if (value == 1)
      result->bits[byte] |= (1 << bit);
    else
      result->bits[byte] &= ~(1 << bit);
  } else
    res = 1;
  return res;
}
void s21_cpy_decimal(s21_decimal src, s21_decimal *dest) {
  for (int i = 0; i < 4; i++) dest->bits[i] = src.bits[i];
}

int s21_set_exp(s21_decimal value, s21_decimal *result,
                int exp) {  // 0 - OK, 1 - ERROR
  int res = 1;

  if (exp >= 0 && exp <= 28) {
    s21_cpy_decimal(value, result);
    int sign = s21_bit(value, 127);
    exp = exp << 16;
    result->bits[3] = exp;
    if (sign) s21_set_bitt(result, 127, 1);
    res = 0;
  }

  return res;
}
// bites functions

int get_bit(s21_decimal dec,
            int pos) {  // возвращает значение бита по позиции /pos/. 0 или 1
  return ((dec.bits[pos / 32] >> (pos % 32)) & 1u);
}

void set_bit(s21_decimal *dec, int bit, int val) {  // val = 1 or 0
  if (val) {
    dec->bits[bit / 32] |= (1 << (bit % 32));
  } else {
    dec->bits[bit / 32] &= ~(1 << (bit % 32));
  }
}

int get_sign(s21_decimal dec) { return get_bit(dec, 127); }

void set_sign(s21_decimal *dec, int sign) { set_bit(dec, 127, sign); }

int get_exp(s21_decimal d) {
  return (d.bits[3] & 0x00FF0000) >> 16;  // ислоьзование маски и смещения влево
                                          // для получения инта экспоненты
}

void set_exp(s21_decimal *dec, int power) {
  dec->bits[3] =
      ((unsigned int)get_sign(*dec) << 31 | ((unsigned int)power << 16));
}

// additional functions

int copy_to_buffer(s21_decimal src, s21_decimal *dst) {
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[3];
  return 0;
}

void init_decimal(s21_decimal *d) {
  if (d != NULL) {
    d->bits[0] = 0u;
    d->bits[1] = 0u;
    d->bits[2] = 0u;
    d->bits[3] = 0u;
  }
}

int get_float_exp_from_string(char *str) {
  int result = 0;
  char *ptr = str;
  while (*ptr && *ptr != 'E') ptr++;
  result += strtol(++ptr, NULL, 10);
  return result;
}

// проверка граничных условий для s21_from_int_to_decimal

int check_F2D(float src, s21_decimal *dst) {
  int codeError = 0;
  unsigned int mask = 0xFFFE0001;  // 0x0000FFFF for bits 0 to 15 and 0x7F000000
                                   // for bits 24 to 30
                                   // проверки на предельные значения
  if (DECIMAL_MINIMUM > fabsf(src) || DECIMAL_MAX < fabsf(src)) {
    if (0.0f == fabsf(src)) {
      init_decimal(dst);
      if (signbit(src) != 0) {
        set_sign(dst, 1);
      }
    } else {
      codeError = 1;
      if (DECIMAL_MINIMUM > fabsf(src)) init_decimal(dst);
    }
  }
  // проверка на нан, инф, -инф
  if (isinf(src) || isnan(src)) {
    codeError = 1;
    if (signbit(src) != 0) set_sign(dst, 1);
  }
  // проверка на правильность конечной точки
  if ((dst->bits[3] & mask) != 0) codeError = 1;
  return codeError;
}

void get_pow_10_multiDec(int exp, s21_decimal *dst) {
  int tempExp = exp;
  s21_decimal inti = {{10u, 0u, 0u, 0u}};
  // экспоненты
  s21_decimal buff = {{0u, 0u, 0u, 0u}};
  copy_to_buffer(*dst, &buff);

  for (int i = 0; i < tempExp; i++, exp--) {
    s21_mul(inti, buff, dst);
    copy_to_buffer(*dst, &buff);
  }
}

int mul_by_ten_n_times(int exp, s21_decimal *dst) {
  int tempExp = exp;
  s21_decimal inti = {{10u, 0u, 0u, 0u}};
  s21_decimal buff = {{0u, 0u, 0u, 0u}};
  copy_to_buffer(*dst, &buff);
  int mul_status = 0;
  int curr_exp = get_exp(*dst);

  for (int i = 0; i < tempExp && mul_status == 0; i++) {
    mul_status = s21_mul(inti, buff, dst);
    if (mul_status == 0) {
      set_exp(dst, 0);
      copy_to_buffer(*dst, &buff);
    } else {
      copy_to_buffer(buff, dst);
    }

    curr_exp++;
  }

  if (mul_status != 0) {
    set_exp(dst, curr_exp);
  }

  return mul_status;
}

unsigned int get_rid_ofZeros(const char *sci_str, int *exp) {
  unsigned int newNumber = 0u;
  int posE = 0, hasDot = 0;
  while (sci_str[posE] != 'E') posE++;
  hasDot = (sci_str[1] == '.' || sci_str[1] == ',') ? 1 : 0;
  int pos_noZero = posE;
  while ((sci_str[pos_noZero] == 'E' || sci_str[pos_noZero] == '0') &&
         pos_noZero >= 0)
    pos_noZero--;
  int tempExp = pos_noZero - hasDot;
  char new_str[8] = {'\0'};
  memcpy(new_str, sci_str, sizeof(char) * (++pos_noZero));
  *exp -= tempExp;
  double tmp = round(strtod(new_str, NULL) * pow(10, tempExp));
  newNumber = (unsigned int)tmp;
  return newNumber;
}

// binary helpers functions

int binary_add(s21_decimal dec1, s21_decimal dec2, s21_decimal *res) {
  init_decimal(res);
  int owerflow = 0, reserv = 0;
  for (int i = 0; i < 96; i++) {
    int bit1 = get_bit(dec1, i);
    int bit2 = get_bit(dec2, i);
    set_bit(res, i, bit1 ^ bit2 ^ reserv);
    reserv = (bit1 && bit2) || (bit1 && reserv) || (bit2 && reserv);
    if (i == 95 && reserv) {
      owerflow = 1;
    }
  }
  return owerflow;
}

int binary_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal *res) {
  int owerflow = 0;
  s21_decimal result = {0};

  for (int i = 0; i < 96 && !owerflow; i++) {
    if (get_bit(dec2, i) == 1) {
      s21_decimal shift_binary_number = dec1;

      for (int j = 0; j < i; j++) {
        if (shift_left(&shift_binary_number)) {
          owerflow = 1;
          break;
        }
      }
      if (owerflow || binary_add(shift_binary_number, result, &result)) {
        owerflow = 1;
        break;
      }
    }
  }
  if (!owerflow) *res = result;
  return owerflow;
}

int binary_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal *res) {
  init_decimal(res);
  int borrow = 0;
  for (int i = 0; i < 96; i++) {
    int bit1 = get_bit(dec1, i);
    int bit2 = get_bit(dec2, i);
    int diff = bit1 - bit2 - borrow;
    if (diff <
        0) {      // If the result is negative, borrow from the next higher bit
      diff += 2;  // Adding 2 because we're dealing with binary (0 or 1)
      borrow = 1;
    } else {
      borrow = 0;
    }
    set_bit(res, i, diff);
  }

  return borrow;
}

s21_decimal binary_div(s21_decimal dec1, s21_decimal dec2,
                       s21_decimal *res) {  // mod
  init_decimal(res);                        // return remainder
  s21_decimal remainder = {0};              // res integer part
  s21_decimal extra_dec = {0};
  set_bit(&extra_dec, 0, 1);
  if (is_more_simple(dec1, dec2)) {
    while (is_more_or_equal_simple(dec1, dec2)) {
      s21_decimal copy_dec2 = dec2;
      init_decimal(&extra_dec);
      set_bit(&extra_dec, 0, 1);
      while (is_more_or_equal_simple(dec1, copy_dec2) &&
             !(get_bit(dec1, 95) && get_bit(copy_dec2, 95))) {
        shift_left(&copy_dec2);
        shift_left(&extra_dec);
      }
      if (!(get_bit(dec1, 95) && get_bit(copy_dec2, 95)) ||
          (is_more_or_equal_simple(copy_dec2, dec1))) {
        shift_right(&copy_dec2);
        shift_right(&extra_dec);
      }
      binary_sub(dec1, copy_dec2, &dec1);
      binary_add(*res, extra_dec, res);
    }
  } else if (is_equal_simple(dec1, dec2)) {
    *res = extra_dec;
    init_decimal(&dec1);
  }
  remainder = dec1;
  return remainder;
}

// shift functions

int shift_left(s21_decimal *dec) {
  int owerflow = get_bit(*dec, 95);
  for (int i = 95; i >= 0; i--) {
    if (i != 0) {
      set_bit(dec, i, get_bit(*dec, i - 1));
    } else {
      set_bit(dec, i, 0);
    }
  }
  return owerflow;
}

void shift_right(s21_decimal *dec) {
  for (int i = 0; i < 96; i++) {
    if (i != 95) {
      set_bit(dec, i, get_bit(*dec, i + 1));
    } else {
      set_bit(dec, i, 0);
    }
  }
}

// conditions

int is_less_simple(s21_decimal dec1, s21_decimal dec2) {
  int total = 0;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(dec1, i) ^ get_bit(dec2, i)) {
      total = get_bit(dec2, i);
      break;
    }
  }
  return total;
}

int is_equal_simple(s21_decimal dec1, s21_decimal dec2) {
  int total = 1;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(dec1, i) != get_bit(dec2, i)) {
      total = 0;
      break;
    }
  }
  return total;
}

int is_less_or_equal_simple(s21_decimal dec1, s21_decimal dec2) {
  return is_less_simple(dec1, dec2) || is_equal_simple(dec1, dec2);
}

int is_more_simple(s21_decimal dec1, s21_decimal dec2) {
  return !is_less_or_equal_simple(dec1, dec2);
}

int is_more_or_equal_simple(s21_decimal dec1, s21_decimal dec2) {
  return is_more_simple(dec1, dec2) || is_equal_simple(dec1, dec2);
}

int ipow(int base, int exponent) {
  int result = 1;
  while (exponent != 0) {
    if ((exponent & 1) == 1) {
      result *= base;
    }
    base *= base;
    exponent >>= 1;
  }
  return result;
}

void s21_set_bit(s21_decimal *decl, int index, int bit) {
  int ind32 = index / 32, num32 = index % 32;
  if (bit == 1) {
    decl->bits[ind32] |= (1u << num32);  // Устанавливаем бит в позиции num32 в
                                         // элементе массива bits
  } else {
    decl->bits[ind32] &= (~(
        (1u)
        << num32));  // Сбрасываем бит в позиции num32 в элементе массива bits
  }
}

void div_by_ten(s21_decimal *value) {
  int rest = 0;  // Остаток при делении на 10
  for (int i = 2; i >= 0;
       i--) {  // Проходимся по всем элементам массива, начиная с последнего
    long initial = rest * 4294967296 + value->bits[i];  // 2^32
    value->bits[i] =
        initial / 10;  // Сохраняем результат деления в текущий элемент массива
    rest = initial -
           value->bits[i] * 10;  // Обновляем остаток для следующей итерации
  }
}

int set_pow(s21_decimal value, s21_decimal *result, int int_pow) {
  *result = value;  // Устанавливаем результат равным входному числу

  if (int_pow <= 28) {
    // Проходимся по битам степени
    for (int i = 112; i < 120; i++) {
      // Устанавливаем бит в соответствии с текущим значением степени
      if (int_pow % 2)
        set_bit(result, i, 1);
      else
        set_bit(result, i, 0);
      int_pow = int_pow /
                2;  // Уменьшаем значение степени на 2 для следующей итерации
    }
  } else {
    return 1;  // Возвращаем ошибку, если значение степени превышает 28
  }
  return 0;  // Возвращаем успешное выполнение
}

int get_pow(s21_decimal value) {
  int power = 0;    // Результат
  int counter = 0;  // Счетчик битов степени
  int length = 16;  // Начальная длина
  // Проходимся по всем битам степени
  while (length <= 23) {
    // Извлекаем текущий бит степени и добавляем его значение к результату
    int bit = ((value.bits[3] & (1 << length)) != 0);
    power += bit * pow(2, counter);
    length++;
    counter++;
  }
  return power;  // Возвращаем результат
}

int s21_get_bit(s21_decimal decl, int index) {
  int ind32 = index / 32,
      num32 = index % 32;  // Определяем индекс элемента массива и индекс бита в
                           // этом элементе
  return (decl.bits[ind32] & (1u << num32)) >>
         num32;  // Извлекаем бит из элемента массива и возвращаем его значение
}

s21_decimal abs_dec(s21_decimal value) {
  if (get_bit(value, 127) != 0) set_bit(&value, 127, 0);
  return value;
}

void normolize_up(s21_decimal *value, int pow) {
  int exp = get_exp(*value);
  int multiplications_amount = pow - exp;
  set_exp(value, 0);
  int pow_status = mul_by_ten_n_times(multiplications_amount, value);

  if (pow_status == 0) {
    set_exp(value, pow);
  }
}

void normolize_down(s21_decimal *value, int pow) {
  int exp = get_exp(*value);
  int sign = get_sign(*value);
  int divisions_amount = exp - pow;
  s21_decimal divider = {{10, 0, 0, 0}};
  s21_decimal temp = {{DEC_ZERO}};
  s21_decimal result = {{DEC_ZERO}};
  s21_decimal five = {{5, 0, 0, 0}}, one = {{1, 0, 0, 0}};

  mul_by_ten_n_times(divisions_amount - 1, &divider);
  copy_to_buffer(*value, &temp);
  set_exp(&temp, 0);
  s21_decimal remainder = binary_div(*value, divider, &result);
  copy_to_buffer(result, value);
  set_exp(value, 0);

  s21_set_to_zero(&divider);
  s21_set_to_zero(&result);
  divider.bits[0] = 10;

  for (int i = divisions_amount; i > 0; i--) {
    remainder = binary_div(temp, divider, &result);
    copy_to_buffer(result, &temp);
    s21_set_to_zero(&result);
  }

  if (s21_is_zero(remainder) && s21_is_greater_or_equal(remainder, five)) {
    s21_add(*value, one, value);
  }

  if (s21_is_zero(*value)) {
    set_exp(value, pow);
    set_sign(value, sign);
  }
}

int normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int exp_1 = s21_get_exp(*value_1);
  int exp_2 = s21_get_exp(*value_2);

  if (exp_1 > exp_2) {
    normolize_up(value_2, exp_1);
    exp_2 = get_exp(*value_2);

    if (exp_1 != exp_2) {
      normolize_down(value_1, exp_2);
    }
  } else if (exp_1 < exp_2) {
    normolize_up(value_1, exp_2);
    exp_1 = get_exp(*value_1);

    if (exp_1 != exp_2) {
      normolize_down(value_2, exp_1);
    }
  }

  return get_exp(*value_1);
}
// Вычитание двух десятичных значений (value1 - value2) с результатом в res.
void bit_substraction(s21_decimal value1, s21_decimal value2,
                      s21_decimal *res) {
  // Инициализация переменных для хранения битов и промежуточного значения
  int tmp = 0;

  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(value1, i);
    int bit2 = s21_get_bit(value2, i);
    int sub = bit1 - bit2;
    switch (sub) {
      // Установка результата вычитания и учет заемного бита
      case (-1): {
        s21_set_bit(res, i, 1);
        tmp = 1;
        break;
      }
      case (0): {
        s21_set_bit(res, i, 0);
        break;
      }
      case (1): {
        s21_set_bit(res, i, 1);
        break;
      }
    }
    if (tmp == 1) {
      for (int j = i + 1; j < 96; j++) {
        if (s21_get_bit(value1, j) == 1) {
          s21_set_bit(&value1, j, 0);
          break;
        } else {
          s21_set_bit(&value1, j, 1);
        }
      }
      tmp = 0;
    }
  }
}
