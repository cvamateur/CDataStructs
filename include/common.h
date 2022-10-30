//
// Created by chris on 2022/10/23.
//

#ifndef CDATASTRUCTS_COMMON_H
#define CDATASTRUCTS_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char tmp_char;
extern short tmp_short;
extern int tmp_int;
extern long tmp_long;
extern long long tmp_longlong;
extern float tmp_float;
extern double tmp_double;
extern char *tmp_string;

#define REF_CHAR(X)         ((tmp_char = (char)(X)), &tmp_char)
#define REF_SHORT(X)        ((tmp_short = (short)(X)), &tmp_short)
#define REF_INT(X)          ((tmp_int = (int)(X)), &tmp_int)
#define REF_LONG(X)         ((tmp_long = (long)(X)), &tmp_long)
#define REF_LONGLONG(X)     ((tmp_longlong = (long long)(X)), &tmp_longlong)
#define REF_FLOAT(X)        ((tmp_float = (float)(X)), &tmp_float)
#define REF_DOUBLE(X)       ((tmp_double = (double)(X)), &tmp_double)
#define REF_STRING(X)       ((tmp_string = (char *)(X)), &tmp_string)

#define STD_ENDL()        (printf("\n"))


typedef int (*CompareFunction)(const void *elemAddr1, const void *elemAddr2);
typedef void (*PrintFunction)(const void *elemAddr);
typedef void (*FreeFunction)(void *elemAddr);
typedef void (*MapFunction)(void *elemAddr, void *auxData);

#define swap(a, b)              (__swap(&(a), &(b), sizeof(a)))
#define memswap(a, b, s)        (__swap(a, b, s))
extern void __swap(void *a, void *b, const size_t elemSize);

#define MAX(a, b)           ((a) >= (b) ? (a) : (b))
#define MIN(a, b)           ((a) <= (b) ? (a) : (b))

size_t rand64(void);
size_t randint(size_t a, size_t b);
double randfloat(double a, double b);


#endif //CDATASTRUCTS_COMMON_H
