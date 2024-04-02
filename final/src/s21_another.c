#include "s21_decimal.h"
//Возвращаемое значение - код ошибки:
// 0 - OK, 1 - ошибка вычисления

//Возвращает целые цифры Decimal числа, дробные цифры отбрасываются
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int int_pow = 0;//хранит целую часть числа 
  *result = value; // изменять его без изменения исходного значения 

  if (result == NULL)
    error = 1;
  for (int i = 126; i >= 96 && !error; i--) { //начиная слева проходит по битам числа
    if ((i > 119 || i < 112) && get_bit(value, i)) // только дробная часть числа
      error = 1;
    else if ((i < 120 && i > 111)) { //находится ли текущий бит в диапазоне, который соответствует дробной части числа
      int_pow += get_bit(value, i) * pow(2, i - 112);//вычисляем цеулю часть бита
      if (int_pow > 28)
        error = 1;
    }
  }
  if (!error && int_pow) {
    for (int i = 119; i > 111; i--)
      set_bit(result, i, 0); //обнуляются биты с 112 по 119 
    for (int i = 0; i < int_pow; i++)
      div_by_ten(result);//обрезает до целой части 
  }
  return error;
}
//Возвращает результат умножения указанного Decimal на -1
int s21_negate(s21_decimal value, s21_decimal *result) {
     int error = 0;
  *result = value;

  if (result == NULL)
    error = 1;
  for (int i = 126; i > 95 && !error; i--) {
    if ((i > 119 || (i < 112 && i > 95)) && get_bit(value, i))//находиться ли бит в диапазоне  
                                                            //дробной части и установлен ли
      error = 1;//если в недопустимой позиции
  }
  if (!error)
    set_bit(result, 127, !get_bit(value, 127));//установка знака противоположного числа
  return error;
}   
//Округляет Decimal до ближайшего целого числа в сторону отрицательной бесконечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int zero_value = 1;

  for (int i = 95; i >= 0 && zero_value; i--)//проверка на ноль диапазаон числа value
    if (get_bit(value, i)) zero_value = 0;
  error = s21_truncate(value, result);//обрезает дробную часть
  if (!error && !zero_value && get_bit(*result, 127) && //если дробная часть не ноль и отрицательное
      get_pow(value)) { //отрицательоне дробное
    int i = 0;
    while (get_bit(*result, i)) { //уменьшить на едиицу
      set_bit(result, i, 0);
      i++;
    }
    set_bit(result, i, 1);
  }
  return error;
}
//Округляет Decimal до ближайшего целого числа
int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int zero_value = 1;//дробная часть ноль

  for (int i = 95; i >= 0 && zero_value; i--)//все ли биты дробной части ноль
    if (get_bit(value, i)) zero_value = 0;//если отличный от нуля
  error = s21_truncate(value, result);
  if (!error && !zero_value && get_pow(value)) {//если дробная часть не ноль и экспонента не ноль
    s21_decimal diff = {0};
    s21_sub(value, *result, &diff);
    s21_decimal zerohalf = {0};
    s21_from_int_to_decimal(5, &zerohalf);
    set_pow(zerohalf, &zerohalf, 1);
    if (s21_is_greater_or_equal(abs_dec(diff),
                                zerohalf)) {
      int i = 0;
      while (get_bit(*result, i)) {
        set_bit(result, i, 0);
        i++;
      }
      set_bit(result, i, 1);
    }
  }
  return error;
}

