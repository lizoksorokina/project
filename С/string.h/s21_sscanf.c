#include "s21_string.h"

struct Arguments {
  short star;
  int wdh;
  char v_type;
  int res_counter;
};

int ifd(va_list valist, const char *str, struct Arguments *complicates);
void ifd_write_to_destination(va_list valist, struct Arguments *complicates,
                              long int *assign_numb);
int ifi(va_list valist, const char *str, struct Arguments *complicates);
int ifx(va_list valist, const char *str, struct Arguments *complicates);
long ifx_notation(const char *str, struct Arguments *complicates, int *sdvig);
int ifo(va_list valist, const char *str, struct Arguments *complicates);
int ifc(va_list valist, const char *str, struct Arguments *complicates);
int ifs(va_list valist, const char *str, struct Arguments *complicates);
void ifn(va_list valist, int assign_numb, struct Arguments *complicates);
int ifu(va_list valist, const char *str, struct Arguments *complicates);
int ifp(va_list valist, const char *str, struct Arguments *complicates);
int if_f(va_list valist, const char *str, struct Arguments *complicates,
         int *total_count);
int ife(const char *str, long double *assign_numb, int *sdvig,
        struct Arguments *complicates);
long int_notation(const char *str, struct Arguments *complicates, int *sdvig);

int s21_sscanf(const char *str, const char *format, ...) {
  long all_assign_ch = 0;
  va_list valist;
  va_start(valist, format);
  char *all_spec = "cdieEfgGosuxXpn%";
  int ifpercent = 0;
  int counter = 0;
  for (; *format;) {
    if (*format++ == '%') {
      int was_ifn = 0;
      long str_sdvig = 0;
      struct Arguments complicates = {0, -1, '\0', 0};
      do {
        if (*format == '*') {
          complicates.star = 1;
        } else if ('0' <= *format && *format <= '9') {
          if (complicates.wdh == -1)
            complicates.wdh = (*format - '0');
          else
            complicates.wdh = complicates.wdh * 10 + (*format - '0');
        } else if (*format == 'h' || *format == 'l' || *format == 'L') {
          complicates.v_type = *format;
        } else if (*format == 'd') {
          str_sdvig += ifd(valist, str, &complicates);
        } else if (*format == 'i') {
          str_sdvig += ifi(valist, str, &complicates);
        } else if (*format == 'o') {
          str_sdvig += ifo(valist, str, &complicates);
        } else if (*format == 'x' || *format == 'X') {
          str_sdvig += ifx(valist, str, &complicates);
        } else if (*format == 'c') {
          str_sdvig += ifc(valist, str, &complicates);
        } else if (*format == 's') {
          str_sdvig += ifs(valist, str, &complicates);
        } else if (*format == 'u') {
          str_sdvig += ifu(valist, str, &complicates);
        } else if (*format == 'p') {
          str_sdvig += ifp(valist, str, &complicates);
        } else if (*format == 'e' || *format == 'E' || *format == 'g' ||
                   *format == 'G' || *format == 'f') {
          str_sdvig += if_f(valist, str, &complicates, &counter);
        } else if (*format == 'n') {
          was_ifn = 1;
          ifn(valist, all_assign_ch, &complicates);
        } else if (*format == '%') {
          ifpercent = 1;
          while (*str == ' ' || *str == '%') {
            complicates.res_counter = -1;
            all_assign_ch++;
            str++;
          }
        }
      } while (s21_strchr(all_spec, *format++) == s21_NULL);
      if (complicates.res_counter == 0 || complicates.res_counter == -1) break;
      if (complicates.star) complicates.res_counter = 0;
      if (was_ifn) complicates.res_counter = 0;
      counter += complicates.res_counter;
      str += str_sdvig;
      all_assign_ch += str_sdvig;
    }
  }
  va_end(valist);
  int itog;
  if (ifpercent && counter == 0) {
    itog = 0;
  } else if (counter == 0) {
    itog = -1;
  } else {
    itog = counter;
  }
  return itog;
}

int ifd(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;
  long assign_numb = int_notation(str, complicates, &sdvig);
  if (complicates->star == 0) {
    if (complicates->v_type == '\0') {
      *(int *)va_arg(valist, int *) = (int)assign_numb;
    } else if (complicates->v_type == 'h') {
      *(short *)va_arg(valist, short *) = (short)assign_numb;
    } else if (complicates->v_type == 'l') {
      *(long *)va_arg(valist, long *) = (long)assign_numb;
    }
  }
  return sdvig;
}

int ifi(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;
  while (*str == ' ') {
    str++;
    sdvig++;
  }
  if (*str == '0') {
    str++;
    sdvig++;
    if (*str != 'x') {
      sdvig += ifo(valist, str, complicates);
    } else {
      sdvig += ifx(valist, str, complicates);
    }
  } else if ((*str >= '0' && *str <= '9') || *str == '-' || *str == '+') {
    sdvig += ifd(valist, str, complicates);
  }
  return sdvig;
}

int ifo(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;
  long in_oct = int_notation(str, complicates, &sdvig);

  int many_minus_plus = 0;
  while (*str == ' ' || *str == '-' || *str == '+' || *str == '0') {
    if (*str == '-' || *str == '+') many_minus_plus++;
    str++;
  }

  if (many_minus_plus <= 1) {
    long in_dec = 0;
    int i = 0;
    if (complicates->wdh == -1) {
      while (in_oct != 0) {
        in_dec = in_dec + (in_oct % 10) * pow(8, i++);
        in_oct /= 10;
      }
    } else {
      while (in_oct != 0 && complicates->wdh--) {
        in_dec = in_dec + (in_oct % 10) * pow(8, i++);
        in_oct /= 10;
      }
    }

    if (complicates->star == 0) {
      if (complicates->v_type == '\0') {
        *(int *)va_arg(valist, int *) = (int)in_dec;
      } else if (complicates->v_type == 'h') {
        *(short *)va_arg(valist, short *) = (short)in_dec;
      } else if (complicates->v_type == 'l') {
        *(long *)va_arg(valist, long *) = (long)in_dec;
      }
    }
  }
  return sdvig;
}

long int_notation(const char *str, struct Arguments *complicates, int *sdvig) {
  long res = 0;
  int flag_minus = 0;
  while (*str == ' ' || *str == '-' || *str == '+') {
    if (*str == '-') {
      flag_minus = 1;
      complicates->wdh--;
    } else if (*str == '+') {
      complicates->wdh--;
    }
    str++;
    (*sdvig)++;
  }
  while (*str >= '0' && *str <= '9' && complicates->wdh--) {
    res = res * 10 + (*str - '0');
    str++;
    (*sdvig)++;
    complicates->res_counter = 1;
  }

  if (flag_minus) res *= -1;

  return res;
}

int ifx(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;
  long in_dec = ifx_notation(str, complicates, &sdvig);
  if (complicates->star == 0) {
    if (complicates->v_type == '\0') {
      *(int *)va_arg(valist, int *) = (int)in_dec;
    } else if (complicates->v_type == 'h') {
      *(short *)va_arg(valist, short *) = (short)in_dec;
    } else if (complicates->v_type == 'l') {
      *(long *)va_arg(valist, long *) = (long)in_dec;
    }
  }
  return sdvig;
}

long ifx_notation(const char *str, struct Arguments *complicates, int *sdvig) {
  long in_dec = 0;
  int flag_minus = 0;
  int many_minus_plus = 0;
  while (*str == ' ' || *str == '-' || *str == '+' || *str == '0' ||
         *str == 'x' || *str == 'X') {
    if (*str == '-' || *str == '+') many_minus_plus++;
    if (*str == '-') flag_minus = 1;
    str++;
    (*sdvig)++;
  }

  if (many_minus_plus <= 1) {
    // int i = 0;
    int len = 0;
    while ((*str && *str != ' ' && *str != '\n') &&
           ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f') ||
            (*str >= 'A' && *str <= 'F')) &&
           complicates->wdh--) {
      len++;
      (*sdvig)++;
      str++;
    }
    str -= len;
    len--;
    while ((*str && *str != ' ' && *str != '\n')) {
      int temp = 0;
      if (*str >= '0' && *str <= '9') temp = *str - 48;
      if (*str >= 'A' && *str <= 'F') temp = *str - 55;
      if (*str >= 'a' && *str <= 'f') temp = *str - 87;
      complicates->res_counter = 1;
      in_dec += temp * pow(16, len);
      len--;
      // i++;
      str++;
      if (len == -1) break;
    }
  }

  if (flag_minus) in_dec *= -1;

  return in_dec;
}

int ifc(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;
  if (complicates->star == 0 && complicates->wdh <= 0) {
    if (complicates->v_type == 'l') {
      *(wchar_t *)va_arg(valist, wchar_t *) = *str;
    } else {
      *(char *)va_arg(valist, char *) = *str;
    }
    sdvig++;
    complicates->res_counter = 1;
  } else {
    sdvig += ifs(valist, str, complicates);
  }
  return sdvig;
}

int ifs(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;
  while (*str == ' ' || *str == '\n') {
    str++;
    sdvig++;
  }

  if (complicates->star != 0) {
    while (*str && *str != ' ' && *str != '\n' && complicates->wdh--) {
      str++;
      sdvig++;
      complicates->res_counter = 1;
    }
  } else {
    if (complicates->v_type == 'l') {
      wchar_t *str_var = va_arg(valist, wchar_t *);
      while (*str && *str != ' ' && *str != '\n' && complicates->wdh--) {
        sdvig++;
        *str_var++ = *str++;
        complicates->res_counter = 1;
      }
      *str_var = '\0';
    } else {
      char *str_var = va_arg(valist, char *);
      while (*str && *str != ' ' && *str != '\n' && complicates->wdh--) {
        sdvig++;
        *str_var++ = *str++;
        complicates->res_counter = 1;
      }
      *str_var = '\0';
    }
  }
  return sdvig;
}

void ifn(va_list valist, int assign_numb, struct Arguments *complicates) {
  if (complicates->v_type == '\0') {
    *(int *)va_arg(valist, int *) = (int)assign_numb;
  } else if (complicates->v_type == 'h') {
    *(short *)va_arg(valist, short *) = (short)assign_numb;
  } else if (complicates->v_type == 'l') {
    *(long *)va_arg(valist, long *) = (long)assign_numb;
  }
  complicates->res_counter = 1;
}

int ifu(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;
  long assign_numb = int_notation(str, complicates, &sdvig);
  if (complicates->star == 0) {
    if (complicates->v_type == '\0') {
      *(unsigned int *)va_arg(valist, unsigned int *) =
          (unsigned int)assign_numb;
    } else if (complicates->v_type == 'h') {
      *(unsigned short *)va_arg(valist, unsigned short *) =
          (unsigned short)assign_numb;
    } else if (complicates->v_type == 'l') {
      *(unsigned long *)va_arg(valist, unsigned long *) =
          (unsigned long)assign_numb;
    }
  } else {
    int_notation(str, complicates, &sdvig);
  }
  return sdvig;
}

int ifp(va_list valist, const char *str, struct Arguments *complicates) {
  int sdvig = 0;

  long in_dec = ifx_notation(str, complicates, &sdvig);
  if (complicates->star == 0) {
    void **str_var = va_arg(valist, void **);
    *str_var = (void *)(0x0 + in_dec);
  }

  return sdvig;
}

int if_f(va_list valist, const char *str, struct Arguments *complicates,
         int *total_count) {
  int sdvig = 0;
  long double before_e_point = int_notation(str, complicates, &sdvig);
  long double assign_numb = before_e_point;

  int sign = 1;

  const char *str_temp = str;
  while (*str_temp == ' ') str_temp++;
  if (*str_temp == '-') sign = -1;

  str += sdvig;

  if (*str == '.') {
    str++;
    int after_point = 0;
    long double itog_after_point = int_notation(str, complicates, &after_point);
    sdvig += after_point + 1;

    for (int n = after_point; n > 0; n--) itog_after_point /= 10;

    if (!before_e_point && !itog_after_point && sign == -1)
      assign_numb = 0;
    else if (sign == -1)
      assign_numb -= itog_after_point;
    else
      assign_numb += itog_after_point;

    str += after_point;
  } else if (*str == 'e' || *str == 'E') {
    if (complicates->wdh == 1) {
      if (complicates->v_type == 'l') {
        *(double *)va_arg(valist, double *) = (double)assign_numb;
      } else if (complicates->v_type == 'L') {
        *(long double *)va_arg(valist, long double *) =
            (long double)assign_numb;
      } else {
        *(float *)va_arg(valist, float *) = (float)assign_numb;
      }
      complicates->res_counter = 0;
      (*total_count)++;
    }
    str += ife(str, &assign_numb, &sdvig, complicates);
  }
  if (*str == 'e' || *str == 'E') ife(str, &assign_numb, &sdvig, complicates);
  if (complicates->star == 0 && complicates->res_counter) {
    if (complicates->v_type == 'l') {
      *(double *)va_arg(valist, double *) = (double)assign_numb;
    } else if (complicates->v_type == 'L') {
      *(long double *)va_arg(valist, long double *) = (long double)assign_numb;
    } else {
      *(float *)va_arg(valist, float *) = (float)assign_numb;
    }
  }
  return sdvig;
}

int ife(const char *str, long double *assign_numb, int *sdvig,
        struct Arguments *complicates) {
  str++;
  complicates->wdh--;
  int all_ch_e = 1;

  int n = int_notation(str, complicates, &all_ch_e);

  if (*str == '+' || (*str >= '0' && *str <= '9')) {
    while (n--) *assign_numb *= 10.0;
  } else if (*str == '-') {
    while (n++) *assign_numb /= 10.0;
  }

  *sdvig += all_ch_e;
  return all_ch_e;
}
