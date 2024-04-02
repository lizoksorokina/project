#include "utils.h"

int s21_get_exp(s21_decimal value) {
  value.bits[3] = value.bits[3] << 1;
  value.bits[3] = value.bits[3] >> 17;
  return value.bits[3];
}
//функция возвращает значение бита в указанной позиции
int s21_bit(s21_decimal value, int position) {  //-1 ошибка
  int res = -1;
  if (position > -1 && position < 128) {
    int byte = position / 32;
    int bit = position % 32;
    res = value.bits[byte] & (1 << bit);
    if (res != 0) res = 1;
  }
  return res;
}
//проверка экспоненты если вернула 0, то все ок в остальных случаях превышает
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
//для копирования значения числа типа  s21_decimal  в структуру  s21_big_decimal
//.
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
//функция возвращает значение бита в указанной позиции
int s21_bit_big_decimal(s21_big_decimal value,
                        int position) {  // -1 - ERROR, position 0-127
  int res = -1;
  if ((position > -1 && position < 256)) {
    int byte = position / 32;
    int bit = position % 32;
    res = value.bits[byte] & (1 << bit);
    if (res != 0) res = 1;
  }
  return res;
}
void s21_sum_of_ten_array_for_big_decimal(int a[], int b[]) {
  int remainder = 0;
  for (int i = 0; i < 90; i++) {
    int res = a[i] + b[i] + remainder;
    a[i] = res % 10;
    remainder = res / 10;
  }
}
//Сравнивает два десятичных массива, если первое больше, то возвращае  1, если
//второе больше  -1, если равны - 0
int s21_compare_bigten_array(int a[], int b[]) {
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
  for (int i = 0; i < 4; i++) {  //цикл по байтам
    if (a.bits[i] != b.bits[i]) {  //если хотя бы один символ не равен
      flag_eq = 0;
      break;
    }
  }
  if (flag_eq == 1) return 0;  //если равны

  if (s21_exponent_check(a, b) != 0)
    return -1;  //если фун вернула не 0, то ошибка эксп

  int sign_1 = s21_bit(a, 127);  //получение знаков
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
      big_1, array_1);  //преобр числа в массив десятичных цифр
  s21_from_big_decimal_to_ten_array(big_2, array_2);
  int exp_1 = s21_get_exp(a);
  int exp_2 = s21_get_exp(b);

  int difference = exp_1 - exp_2;  //вычисление разницы между эксп

  if (difference > 0) {  //если разн положит сдвиг вправо 2-го числа
    for (int i = 0; i < difference;
         i++) {  //Цикл для нормализации массива с меньшей экспонентой.
      for (int j = 89; j > 0; j--) array_2[j] = array_2[j - 1];
      array_2[0] = 0;
    }
  } else if (difference < 0) {  //если разн отрицат сдвиг вправо 1-го числа
    for (int i = 0; i < -difference;
         i++) {  //Цикл для нормализации массива с большей экспонентой.
      for (int j = 89; j > 0; j--) array_1[j] = array_1[j - 1];
      array_1[0] = 0;
    }
  }
  //сравнение
  int compare = s21_compare_bigten_array(array_1, array_2);
  if ((compare == 1 && sign_1 == 0) || (compare == -1 && sign_1 == 1))
    res = 1;
  else if ((compare == -1 && sign_1 == 0) || (compare == 1 && sign_1 == 1))
    res = 2;
  else if (compare == 0)
    res = 0;

  return res;
}
