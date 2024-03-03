#ifndef _SRC_S21_STRING_H_
#define _SRC_S21_STRING_H_

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef long unsigned int s21_size_t;
typedef long unsigned s21_size_t;

#define BUFF_SIZE 512
#define s21_NULL ((void *)0)
#define s21_dot ','

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);

s21_size_t s21_strlen(const char *str);

size_t s21_strspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
char *s21_strrchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
s21_size_t s21_strcspn(const char *str1, const char *str2);

int s21_sprintf(char *output, const char *str, ...);
int s21_sscanf(const char *str, const char *format, ...);
s21_size_t s21_strlen(const char *str);

// Sprintf
struct option {
  int width;
  int prec;
  int space;
  int len;
  int ljust;
  int sign;
  int l;
  int h;
  int L;
  int u;
  int f;
  int numberBase;
  int hash;
  int upper;
  int g;
  long long e;
  int zeroP;
};

#define S21_NULL ((void *)0);

char *itoa(int numberValue, char *convertedString, int numberBase,
           struct option *formatOptions);
char *litoa(long long numberValue, char *convertedString, int numberBase,
            struct option *formatOptions);
char *litoa(long long numberValue, char *convertedString, int numberBase,
            struct option *formatOptions);
char *hitoa(short numberValue, char *convertedString, int numberBase,
            struct option *formatOptions);
char *uitoa(unsigned int numberValue, char *convertedString, int numberBase,
            struct option *formatOptions);
char *ulitoa(unsigned long long numberValue, char *convertedString,
             int numberBase, struct option *formatOptions);
char *uhitoa(unsigned short numberValue, char *convertedString, int numberBase,
             struct option *formatOptions);
void ftoa(long double n, char *res, int afterpoint,
          struct option *formatOptions);
char *elitoa(long long numberValue, char *convertedString, int numberBase,
             struct option *formatOptions);
void eftoal(long double n, char *res, int afterpoint,
            struct option *formatOptions);
void eftoa(double n, char *res, int afterpoint, struct option *formatOptions);

void processString(struct option *formatOptions, char *buff,
                   char *outputString);

void processDecimal(struct option *formatOptions, char *buff, long long num);
void remove_trailing_zeroes(char *buff);

void ProcessFloat(struct option *formatOptions, char *buff, long double num);
int find_nonzero(double num);

#endif
