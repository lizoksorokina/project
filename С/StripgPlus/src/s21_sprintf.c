#include <stdarg.h>

#include "s21_string.h"

#define noOption -1
#define widthOption 0
#define precOption 1
#define endOption 2

void resetOption(struct option *formatOptions) {
  formatOptions->width = -1;
  formatOptions->prec = -1;
  formatOptions->space = 0;
  formatOptions->len = 0;
  formatOptions->ljust = 0;
  formatOptions->sign = 0;
  formatOptions->l = 0;
  formatOptions->h = 0;
  formatOptions->L = 0;
  formatOptions->u = 0;
  formatOptions->f = 0;
  formatOptions->numberBase = 0;
  formatOptions->hash = 0;
  formatOptions->upper = 0;
  formatOptions->e = -2281337;
  formatOptions->zeroP = 0;
  formatOptions->g = 0;
}

int s21_sprintf(char *outputString, const char *formatString, ...) {
  va_list variableArguments;
  va_start(variableArguments, formatString);

  struct option formatOptions;
  resetOption(&formatOptions);

  char charArgument;

  char *buff = malloc(BUFF_SIZE + 1);
  char *strArg = malloc(BUFF_SIZE + 1);
  s21_strcpy(buff, "");

  unsigned long integerArgument;
  long double doubleArgument;
  int stringIterator = 0;
  int isArgument = 0;
  int currentOption = noOption;
  char currentCharacter = *formatString;

  while (formatString != s21_NULL && *(formatString + stringIterator) != '\0') {
    currentCharacter = *(formatString + stringIterator);
    if (currentCharacter == '%' && isArgument == 0) {
      isArgument = 1;
      currentOption = noOption;
    } else if (isArgument == 0) {
      s21_strncat(buff, &currentCharacter, 1);
    } else if (isArgument == 1) {
      if (isdigit(currentCharacter)) {
        if (currentOption == noOption) {
          if (currentCharacter == '0') {
            formatOptions.zeroP = 1;
            currentOption = precOption;
            formatOptions.prec = 0;
          } else {
            currentOption = widthOption;
            formatOptions.width = currentCharacter - '0';
          }
        } else if (currentOption == widthOption) {
          formatOptions.width =
              formatOptions.width * 10 + currentCharacter - '0';
        } else if (currentOption == precOption) {
          formatOptions.prec = formatOptions.prec * 10 + currentCharacter - '0';
        }
      } else if (currentCharacter == '.') {
        if (currentOption != precOption) {
          currentOption = precOption;
          formatOptions.prec = 0;
        } else {
          formatOptions.width = 0;
          formatOptions.zeroP = 0;
          formatOptions.prec = 0;
        }
      } else if (currentCharacter == '-') {
        formatOptions.ljust = 1;
        currentOption = noOption;
      } else if (currentCharacter == '+') {
        formatOptions.sign = 1;
        currentOption = noOption;
      } else if (currentCharacter == ' ') {
        formatOptions.space = 1;
        currentOption = noOption;
      } else if (currentCharacter == 'h') {
        formatOptions.h = 1;
        currentOption = noOption;
      } else if (currentCharacter == 'l') {
        formatOptions.l = 1;
        currentOption = noOption;
      } else if (currentCharacter == 'L') {
        formatOptions.L = 1;
        currentOption = noOption;
      } else if (currentCharacter == '#') {
        formatOptions.hash = 1;
        currentOption = noOption;
      } else if (currentCharacter == '*') {
        if (currentOption == precOption) {
          formatOptions.prec = va_arg(variableArguments, int);
        } else {
          formatOptions.width = va_arg(variableArguments, int);
        }
        currentOption = noOption;
      } else {
        isArgument = 0;
        currentOption = endOption;
      }
    }
    if (currentOption == endOption) {
      if (currentCharacter == 'c' || currentCharacter == '%') {
        formatOptions.prec = -1;
        if (currentCharacter == '%') {
          processString(&formatOptions, buff, "%");
        } else {
          charArgument = va_arg(variableArguments, int);
          s21_strcpy(strArg, &charArgument);
          strArg[1] = 0;
          processString(&formatOptions, buff, strArg);
        }

      } else if (currentCharacter == 's') {
        s21_strcpy(strArg, va_arg(variableArguments, char *));
        processString(&formatOptions, buff, strArg);

      } else if (currentCharacter == 'p') {
        formatOptions.numberBase = 16;
        formatOptions.upper = 2;
        integerArgument = (long)va_arg(variableArguments, void *);
        processDecimal(&formatOptions, buff, integerArgument);

      } else if (currentCharacter == 'd' || currentCharacter == 'i') {
        formatOptions.numberBase = 10;
        integerArgument = va_arg(variableArguments, long);
        processDecimal(&formatOptions, buff, integerArgument);
      } else if (currentCharacter == 'o') {
        formatOptions.numberBase = 8;
        integerArgument = va_arg(variableArguments, long);
        processDecimal(&formatOptions, buff, integerArgument);
      } else if (currentCharacter == 'b') {
        formatOptions.numberBase = 2;
        integerArgument = va_arg(variableArguments, long);
        processDecimal(&formatOptions, buff, integerArgument);
      } else if (currentCharacter == 'u') {
        formatOptions.numberBase = 10;
        formatOptions.u = 1;
        integerArgument = va_arg(variableArguments, long);
        processDecimal(&formatOptions, buff, integerArgument);
      } else if (currentCharacter == 'x') {
        formatOptions.numberBase = 16;
        formatOptions.u = 1;
        integerArgument = va_arg(variableArguments, long);
        processDecimal(&formatOptions, buff, integerArgument);
      } else if (currentCharacter == 'X') {
        formatOptions.numberBase = 16;
        formatOptions.upper = 1;
        formatOptions.u = 1;
        integerArgument = va_arg(variableArguments, long);
        processDecimal(&formatOptions, buff, integerArgument);
      } else if (currentCharacter == 'f') {
        formatOptions.numberBase = 10;
        formatOptions.f = 1;
        if (formatOptions.L) {
          doubleArgument = va_arg(variableArguments, long double);
        } else {
          doubleArgument = va_arg(variableArguments, double);
        }
        ProcessFloat(&formatOptions, buff, doubleArgument);
      } else if (currentCharacter == 'g' || currentCharacter == 'G') {
        formatOptions.g = 1;
        formatOptions.numberBase = 10;
        formatOptions.f = 1;
        if (formatOptions.L) {
          doubleArgument = va_arg(variableArguments, long double);
        } else {
          doubleArgument = va_arg(variableArguments, double);
        }
        long long inum = (long long)log10l(fabsl(doubleArgument));
        if (formatOptions.prec == -1 && inum > 0) {
          formatOptions.prec = 5 - inum;
        } else if (formatOptions.prec == -1) {
          formatOptions.prec = 6;
        }
        if (formatOptions.prec == 0 && inum > -6) {
          formatOptions.prec = find_nonzero(doubleArgument);
        } else if (inum <= -5 && doubleArgument != 0) {
          formatOptions.e = inum - 1;
          if (currentCharacter == 'G') {
            formatOptions.upper = 1;
          }
          doubleArgument = (doubleArgument / pow(10, formatOptions.e));
        }

        ProcessFloat(&formatOptions, buff, doubleArgument);
      } else if (currentCharacter == 'e' || currentCharacter == 'E') {
        if (currentCharacter == 'E') {
          formatOptions.upper = 1;
        }
        formatOptions.numberBase = 10;
        formatOptions.f = 1;
        if (formatOptions.L) {
          doubleArgument = va_arg(variableArguments, long double);
          formatOptions.e = (long long)log10l(fabsl(doubleArgument));
          if (formatOptions.e < 0) {
            formatOptions.e--;
          }
          long double mantissa = (doubleArgument / powl(10, formatOptions.e));
          doubleArgument = mantissa;
        } else {
          doubleArgument = va_arg(variableArguments, double);
          formatOptions.e = (long long)log10(fabsl(doubleArgument));
          if (formatOptions.e > -1e10 && formatOptions.e < 0) {
            formatOptions.e--;
          }
          double mantissa = (doubleArgument / pow(10, formatOptions.e));
          doubleArgument = mantissa;
        }
        ProcessFloat(&formatOptions, buff, doubleArgument);
      }
      currentOption = noOption;
      resetOption(&formatOptions);
    }
    stringIterator++;
  }
  s21_strcpy(outputString, buff);

  int answ = (int)s21_strlen(buff);
  free(buff);
  free(strArg);
  va_end(variableArguments);
  return answ;
}

char *itoa(int numberValue, char *convertedString, int numberBase,
           struct option *formatOptions) {
  if (numberBase < 2 || numberBase > 36) {
    *convertedString = '\0';
    return convertedString;
  }

  char *stringPointer = convertedString,
       *reverseStringPointer = convertedString, tempChar;
  long long tempValue;

  do {
    tempValue = numberValue;
    numberValue /= numberBase;
    int index = 35 + (tempValue - numberValue * numberBase);
    *stringPointer++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[index];

    if (formatOptions->f == 0) {
      formatOptions->prec--;
    }
  } while (numberValue);

  if (formatOptions->prec > -1 && formatOptions->f == 0) {
    while (formatOptions->prec) {
      *stringPointer++ = '0';
      formatOptions->prec--;
    }
  }

  if (tempValue < 0) {
    *stringPointer++ = '-';
  } else if (tempValue >= 0 && formatOptions->sign == 1) {
    *stringPointer++ = '+';
  } else if (formatOptions->space) {
    *stringPointer++ = ' ';
  }

  *stringPointer-- = '\0';
  while (reverseStringPointer < stringPointer) {
    tempChar = *stringPointer;
    *stringPointer-- = *reverseStringPointer;
    *reverseStringPointer++ = tempChar;
  }
  return convertedString;
}

char *litoa(long long numberValue, char *convertedString, int numberBase,
            struct option *formatOptions) {
  if (numberBase < 2 || numberBase > 36) {
    *convertedString = '\0';
    return convertedString;
  }

  char *stringPointer = convertedString,
       *reverseStringPointer = convertedString, tempChar;
  long long tempValue;

  do {
    tempValue = numberValue;
    numberValue /= numberBase;
    int index = 35 + (tempValue - numberValue * numberBase);
    *stringPointer++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[index];

    if (formatOptions->f == 0) {
      formatOptions->prec--;
    }
  } while (numberValue);

  if (formatOptions->prec > -1 &&
      (formatOptions->f == 0 || formatOptions->zeroP == 1)) {
    while (formatOptions->prec) {
      *stringPointer++ = '0';
      formatOptions->prec--;
    }
  }

  if (tempValue < 0) {
    *stringPointer++ = '-';
  } else if (tempValue >= 0 && formatOptions->sign == 1) {
    *stringPointer++ = '+';
  } else if (formatOptions->space) {
    *stringPointer++ = ' ';
  }

  *stringPointer-- = '\0';
  while (reverseStringPointer < stringPointer) {
    tempChar = *stringPointer;
    *stringPointer-- = *reverseStringPointer;
    *reverseStringPointer++ = tempChar;
  }
  return convertedString;
}

char *hitoa(short numberValue, char *convertedString, int numberBase,
            struct option *formatOptions) {
  if (numberBase < 2 || numberBase > 36) {
    *convertedString = '\0';
    return convertedString;
  }

  char *stringPointer = convertedString,
       *reverseStringPointer = convertedString, tempChar;
  long long tempValue;

  do {
    tempValue = numberValue;
    numberValue /= numberBase;
    int index = 35 + (tempValue - numberValue * numberBase);
    *stringPointer++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[index];

    formatOptions->prec--;
  } while (numberValue);

  if (formatOptions->prec > -1) {
    while (formatOptions->prec) {
      *stringPointer++ = '0';
      formatOptions->prec--;
    }
  }

  if (tempValue < 0) {
    *stringPointer++ = '-';
  } else if (tempValue >= 0 && formatOptions->sign == 1) {
    *stringPointer++ = '+';
  } else if (formatOptions->space) {
    *stringPointer++ = ' ';
  }

  *stringPointer-- = '\0';
  while (reverseStringPointer < stringPointer) {
    tempChar = *stringPointer;
    *stringPointer-- = *reverseStringPointer;
    *reverseStringPointer++ = tempChar;
  }
  return convertedString;
}

char *uitoa(unsigned int numberValue, char *convertedString, int numberBase,
            struct option *formatOptions) {
  if (numberBase < 2 || numberBase > 36) {
    *convertedString = '\0';
    return convertedString;
  }

  char *stringPointer = convertedString,
       *reverseStringPointer = convertedString, tempChar;
  long long tempValue;

  do {
    tempValue = numberValue;
    numberValue /= numberBase;
    int index = 35 + (tempValue - numberValue * numberBase);
    *stringPointer++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[index];

    formatOptions->prec--;
  } while (numberValue);

  if (formatOptions->prec > -1) {
    while (formatOptions->prec) {
      *stringPointer++ = '0';
      formatOptions->prec--;
    }
  }

  *stringPointer-- = '\0';
  while (reverseStringPointer < stringPointer) {
    tempChar = *stringPointer;
    *stringPointer-- = *reverseStringPointer;
    *reverseStringPointer++ = tempChar;
  }
  return convertedString;
}

char *ulitoa(unsigned long long numberValue, char *convertedString,
             int numberBase, struct option *formatOptions) {
  if (numberBase < 2 || numberBase > 36) {
    *convertedString = '\0';
    return convertedString;
  }

  char *stringPointer = convertedString,
       *reverseStringPointer = convertedString, tempChar;
  long long tempValue;

  do {
    tempValue = numberValue;
    numberValue /= numberBase;
    int index = 35 + (tempValue - numberValue * numberBase);
    *stringPointer++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[index];

    formatOptions->prec--;
  } while (numberValue);

  if (formatOptions->prec > -1) {
    while (formatOptions->prec) {
      *stringPointer++ = '0';
      formatOptions->prec--;
    }
  }

  *stringPointer-- = '\0';
  while (reverseStringPointer < stringPointer) {
    tempChar = *stringPointer;
    *stringPointer-- = *reverseStringPointer;
    *reverseStringPointer++ = tempChar;
  }
  return convertedString;
}

char *uhitoa(unsigned short numberValue, char *convertedString, int numberBase,
             struct option *formatOptions) {
  if (numberBase < 2 || numberBase > 36) {
    *convertedString = '\0';
    return convertedString;
  }

  char *stringPointer = convertedString,
       *reverseStringPointer = convertedString, tempChar;
  long long tempValue;

  do {
    tempValue = numberValue;
    numberValue /= numberBase;
    int index = 35 + (tempValue - numberValue * numberBase);
    *stringPointer++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[index];

    formatOptions->prec--;
  } while (numberValue);

  if (formatOptions->prec > -1) {
    while (formatOptions->prec) {
      *stringPointer++ = '0';
      formatOptions->prec--;
    }
  }

  *stringPointer-- = '\0';
  while (reverseStringPointer < stringPointer) {
    tempChar = *stringPointer;
    *stringPointer-- = *reverseStringPointer;
    *reverseStringPointer++ = tempChar;
  }
  return convertedString;
}

void ftoa(long double n, char *res, int afterpoint,
          struct option *formatOptions) {
  long long ipart = (long long)n;
  char currNum;
  long double fpart = n - (long double)ipart;
  char ibuff[BUFF_SIZE];

  litoa(ipart, ibuff, 10, formatOptions);
  s21_strcpy(res, ibuff);

  if (afterpoint != 0) {
    s21_strcat(res, ".");
  }
  if (fpart < 0) {
    fpart = -1 * fpart;
  }

  while (afterpoint > 0) {
    afterpoint--;
    if (afterpoint == 0) {
      if (((fpart * 10) - (long long)((fpart + 1e-9) * 10)) * 10 >= 5) {
        currNum = '0' + (long long)((fpart + 1e-9) * 10) + 1;
      } else {
        currNum = '0' + (long long)((fpart + 1e-9) * 10);
      }
    } else {
      currNum = '0' + (long long)((fpart + 1e-9) * 10);
    }

    s21_strncat(res, &currNum, 1);
    fpart = (fpart * 10) - (long long)((fpart + 1e-9) * 10);
  }
}

char *elitoa(long long numberValue, char *convertedString, int numberBase,
             struct option *formatOptions) {
  if (numberBase < 2 || numberBase > 36) {
    *convertedString = '\0';
    return convertedString;
  }

  char *stringPointer = convertedString,
       *reverseStringPointer = convertedString, tempChar;
  long long tempValue;

  do {
    tempValue = numberValue;
    numberValue /= numberBase;
    int index = 35 + (tempValue - numberValue * numberBase);
    *stringPointer++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[index];

    if (formatOptions->f == 0) {
      formatOptions->prec--;
    }
  } while (numberValue);
  if (formatOptions->prec > -1 &&
      (formatOptions->f == 0 || formatOptions->zeroP == 1)) {
    while (formatOptions->prec - 4 - (8)) {
      *stringPointer++ = '0';
      formatOptions->prec--;
    }
  }

  if (tempValue < 0) {
    *stringPointer++ = '-';
  } else if (tempValue >= 0 && formatOptions->sign == 1) {
    *stringPointer++ = '+';
  } else if (formatOptions->space) {
    *stringPointer++ = ' ';
  }

  *stringPointer-- = '\0';
  while (reverseStringPointer < stringPointer) {
    tempChar = *stringPointer;
    *stringPointer-- = *reverseStringPointer;
    *reverseStringPointer++ = tempChar;
  }
  return convertedString;
}

void eftoal(long double n, char *res, int afterpoint,
            struct option *formatOptions) {
  long long ipart = (long long)n;
  char currNum;
  long double fpart = n - (long double)ipart;
  if (fpart * 10 >= 5 && formatOptions->prec == 0) {
    ipart++;
  }
  if (n != n) {
    ipart = 0;
  }
  char ibuff[BUFF_SIZE];
  elitoa(ipart, ibuff, 10, formatOptions);
  s21_strcpy(res, ibuff);
  if (afterpoint != 0) {
    s21_strcat(res, ".");
  }
  if (fpart < 0) {
    fpart = -1 * fpart;
  }

  while (afterpoint > 0) {
    afterpoint--;
    if (afterpoint == 0) {
      if (((fpart * 10) - (long long)(fpart * 10)) * 10 >= 5 &&
          ((long long)(fpart * 10)) != 9) {
        currNum = '0' + (long long)(fpart * 10) + 1;
      } else {
        currNum = '0' + (long long)(fpart * 10);
      }
    } else {
      currNum = '0' + (long long)(fpart * 10);
    }

    s21_strncat(res, &currNum, 1);
    fpart = (fpart * 10) - (long long)(fpart * 10);
  }
}

void eftoa(double n, char *res, int afterpoint, struct option *formatOptions) {
  long long ipart = (long long)n;
  char currNum;
  double fpart = n - (double)ipart;
  if (fpart * 10 >= 5 && formatOptions->prec == 0) {
    ipart++;
  }
  if (n != n) {
    ipart = 0;
  }
  char ibuff[BUFF_SIZE];
  elitoa(ipart, ibuff, 10, formatOptions);
  s21_strcpy(res, ibuff);
  if (afterpoint != 0) {
    s21_strcat(res, ".");
  }
  if (fpart < 0) {
    fpart = -1 * fpart;
  }

  while (afterpoint > 0) {
    afterpoint--;
    if (afterpoint == 0) {
      if (((fpart * 10) - (long long)(fpart * 10)) * 10 >= 5 &&
          ((long long)(fpart * 10)) != 9) {
        currNum = '0' + (long long)(fpart * 10) + 1;
      } else {
        currNum = '0' + (long long)(fpart * 10);
      }
    } else {
      currNum = '0' + (long long)(fpart * 10);
    }

    s21_strncat(res, &currNum, 1);
    fpart = (fpart * 10) - (long long)(fpart * 10);
  }
}

void processString(struct option *formatOptions, char *buff,
                   char *outputString) {
  int stringIterator = 0;
  char currentCharacter = *outputString;
  int formatW;

  if (formatOptions->prec == -1 ||
      formatOptions->prec > (int)s21_strlen(outputString)) {
    formatW = (int)s21_strlen(outputString);
  } else {
    formatW = formatOptions->prec;
  }
  if (formatOptions->width != -1) {
    if (formatOptions->width <= formatW) {
    } else if (formatOptions->ljust == 0) {
      for (int stringIterator = 0;
           stringIterator < formatOptions->width - formatW; stringIterator++) {
        s21_strncat(buff, " ", 1);
      }
    }
  }

  while (*(outputString + stringIterator) != '\0' &&
         (formatOptions->prec <= -1 || formatOptions->prec > 0)) {
    currentCharacter = *(outputString + stringIterator);
    s21_strncat(buff, &currentCharacter, 1);
    stringIterator++;
    formatOptions->prec--;
  }
  if (formatOptions->ljust == 1 && formatOptions->width > formatW) {
    for (int stringIterator = 0;
         stringIterator < formatOptions->width - formatW; stringIterator++) {
      s21_strncat(buff, " ", 1);
    }
  }
}

void processDecimal(struct option *formatOptions, char *buff, long long num) {
  int stringIterator = 0;
  char *outputString = malloc(BUFF_SIZE);
  s21_strcpy(outputString, "");
  char currentCharacter;
  int shift = 0;

  if (num == 0 && formatOptions->prec == 0) {
  } else if (formatOptions->l) {
    if (formatOptions->u) {
      ulitoa(num, outputString, formatOptions->numberBase, formatOptions);
    } else {
      litoa(num, outputString, formatOptions->numberBase, formatOptions);
    }

  } else if (formatOptions->h) {
    if (formatOptions->u) {
      uhitoa(num, outputString, formatOptions->numberBase, formatOptions);
    } else {
      hitoa(num, outputString, formatOptions->numberBase, formatOptions);
    }
  } else {
    if (formatOptions->u) {
      uitoa(num, outputString, formatOptions->numberBase, formatOptions);
    } else {
      itoa(num, outputString, formatOptions->numberBase, formatOptions);
    }
  }

  if (num != 0 && (formatOptions->hash != 0 || formatOptions->upper == 2)) {
    if (formatOptions->numberBase == 8) {
      shift = 1;
    } else if (formatOptions->numberBase == 16 && formatOptions->upper == 1) {
      shift = 2;
    } else if (formatOptions->numberBase == 16 && formatOptions->upper == 2) {
      shift = 4;
    } else if (formatOptions->numberBase == 16) {
      shift = 2;
    }
  } else if (num == 0 && formatOptions->upper == 2) {
    shift = 2;
  }

  if (formatOptions->upper == 1) {
    int stringIterator = 0;
    while (*(outputString + stringIterator)) {
      *(outputString + stringIterator) =
          toupper(*(outputString + stringIterator));
      stringIterator++;
    }
  }

  if (formatOptions->width != -1) {
    if (formatOptions->width <= (int)s21_strlen(outputString) + shift) {
    } else if (formatOptions->ljust == 0) {
      for (int stringIterator = 0;
           stringIterator <
           formatOptions->width - (int)s21_strlen(outputString) - shift;
           stringIterator++) {
        s21_strncat(buff, " ", 1);
      }
    }
  }

  if (num != 0 && (formatOptions->hash != 0 || formatOptions->upper == 2)) {
    if (formatOptions->numberBase == 8) {
      s21_strncat(buff, "0", 1);
    } else if (formatOptions->numberBase == 16 && formatOptions->upper == 1) {
      s21_strncat(buff, "0X", 2);
    } else if (formatOptions->numberBase == 16 && formatOptions->upper == 2) {
      s21_strncat(buff, "0x10", 4);
    } else if (formatOptions->numberBase == 16) {
      s21_strncat(buff, "0x", 2);
    }
  } else if (num == 0 && formatOptions->upper == 2) {
    s21_strncat(buff, "0x", 2);
  }

  while (*(outputString + stringIterator) != '\0') {
    currentCharacter = *(outputString + stringIterator);
    s21_strncat(buff, &currentCharacter, 1);
    stringIterator++;
  }
  if (formatOptions->ljust == 1 &&
      formatOptions->width > (int)s21_strlen(outputString) + shift) {
    for (int stringIterator = 0;
         stringIterator <
         formatOptions->width - (int)s21_strlen(outputString) - shift;
         stringIterator++) {
      s21_strncat(buff, " ", 1);
    }
  }
  free(outputString);
}

void remove_trailing_zeroes(char *buff) {
  int len = s21_strlen(buff);
  char *dot = s21_strchr(buff, '.');
  if (dot) {
    for (int stringIterator = len - 1; buff[stringIterator] != s21_dot;
         stringIterator--) {
      if (buff[stringIterator] == '0')
        buff[stringIterator] = '\0';
      else
        break;
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

void ProcessFloat(struct option *formatOptions, char *buff, long double num) {
  int stringIterator = 0;
  char *outputString = malloc(BUFF_SIZE);
  char currentCharacter;
  int afterpoint = formatOptions->prec;

  if (formatOptions->zeroP == 1) {
    afterpoint = 6;
  }

  if (formatOptions->e == -2281337) {
    if (formatOptions->prec != -1) {
      ftoa(num, outputString, afterpoint, formatOptions);
    } else {
      ftoa(num, outputString, 6, formatOptions);
    }
  } else {
    if (formatOptions->prec != -1) {
      if (formatOptions->L != -1) {
        eftoal(num, outputString, afterpoint, formatOptions);
      } else {
        eftoa(num, outputString, afterpoint, formatOptions);
      }
    } else {
      if (formatOptions->L != -1) {
        eftoal(num, outputString, 6, formatOptions);
      } else {
        eftoa(num, outputString, 6, formatOptions);
      }
    }
  }

  if (formatOptions->g == 1) {
    remove_trailing_zeroes(outputString);
  }

  if (formatOptions->e != -2281337 && formatOptions->upper == 1) {
    char exp[6];
    s21_sprintf(exp, "E%+02d", formatOptions->e);
    s21_strncat(outputString, exp, 5);
  } else if (formatOptions->e != -2281337) {
    char exp[6];
    s21_sprintf(exp, "e%+02d", formatOptions->e);
    s21_strncat(outputString, exp, 5);
  }

  if (formatOptions->width != -1) {
    if (formatOptions->width <= (int)s21_strlen(outputString)) {
    } else if (formatOptions->ljust == 0) {
      for (int stringIterator = 0;
           stringIterator <
           formatOptions->width - (int)s21_strlen(outputString);
           stringIterator++) {
        s21_strncat(buff, " ", 1);
      }
    }
  }

  while (*(outputString + stringIterator) != '\0') {
    currentCharacter = *(outputString + stringIterator);
    s21_strncat(buff, &currentCharacter, 1);
    stringIterator++;
  }
  if (formatOptions->ljust == 1 &&
      formatOptions->width > (int)s21_strlen(outputString)) {
    for (int stringIterator = 0;
         stringIterator < formatOptions->width - (int)s21_strlen(outputString);
         stringIterator++) {
      s21_strncat(buff, " ", 1);
    }
  }
  free(outputString);
}

int find_nonzero(double num) {
  int pow = 0;
  while (num < 1) {
    num = num * 10;
    pow++;
  }
  return pow;
}
