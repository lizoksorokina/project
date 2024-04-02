#include "s21_decimal.h"

//Использование 1u вместо просто 1 гарантирует, что число будет обрабатываться 
//как unsigned int, что может быть важно для предотвращения проблем с переполнением

int get_bit(s21_decimal decl, int index) {
  int ind32 = index / 32, num32 = index % 32; //определяем в каком из 4 элементов находится нужный бит
  return (decl.bits[ind32] & (1u << num32)) >> num32; //побитовое И и сдвиг вправо:
                                                     // извлекаем бит и возвращаем его значение
}

/*Эта функция устанавливает значение бита в указанной позиции  index  в структуре  s21_decimal .
Если  bit  равен 1, то бит устанавливается в 1, иначе он устанавливается в 0. */

void set_bit(s21_decimal *decl, int index, int bit) {
  int ind32 = index / 32, num32 = index % 32;
  if (bit == 1) {
    decl->bits[ind32] |= (1u << num32); //устанавливает бит в позиции num32 в элементе массива 
                                       // bits, на который указывает указатель 
                                       // decl , путем выполнения побитовой операции "ИЛИ" с присваиванием.
  } else {
    decl->bits[ind32] &= (~((1u) << num32)); //обнуляет бит в позиции num32 в элементе массива bits, 
                                             //на который указывает указатель declс помощью побитовой операции "И" с присваиванием.
  }
} 

void div_by_ten(s21_decimal *value) { //деление десятичного числа на 10
  long initial = 0;
  int rest = 0;
  for (int i = 2; i >= 0; i--) { //с самого правого элемннта до его начала 
    initial = rest * 4294967296 + value->bits[i]; //2**32
    value->bits[i] = initial / 10;
    rest = initial - value->bits[i] * 10;//новый остаток 
  }
}

int set_pow(s21_decimal value, s21_decimal *result, int int_pow) {
  int error = 0;
  *result = value;
  if (result == NULL) {
    error = 1;
  }
  if (int_pow <= 28) {
    for (int i = 112; i < 120; i++) {
      if (fmod(int_pow, 2))
        set_bit(result, i, 1);
      else
        set_bit(result, i, 0);
      int_pow = int_pow / 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int get_pow(s21_decimal value) {
  int power = 0;
  int counter = 0;
  int length = 16;
  int bit = 0;
  while (length <= 23) {
    bit = ((value.bits[3] & (1 << length)) != 0);
    power += bit * pow(2, counter);
    length++;
    counter++;
  }
  return power;
}

s21_decimal abs_dec(s21_decimal value) {
  if (get_bit(value, 127) != 0) set_bit(&value, 127, 0);
  return value;
}