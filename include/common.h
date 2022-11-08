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
extern void *tmp_nan;

#define REF_CHAR(X)         ((tmp_char = (char)(X)), &tmp_char)
#define REF_SHORT(X)        ((tmp_short = (short)(X)), &tmp_short)
#define REF_INT(X)          ((tmp_int = (int)(X)), &tmp_int)
#define REF_LONG(X)         ((tmp_long = (long)(X)), &tmp_long)
#define REF_LONGLONG(X)     ((tmp_longlong = (long long)(X)), &tmp_longlong)
#define REF_FLOAT(X)        ((tmp_float = (float)(X)), &tmp_float)
#define REF_DOUBLE(X)       ((tmp_double = (double)(X)), &tmp_double)
#define REF_STRING(X)       ((tmp_string = (char *)(X)), &tmp_string)
#define REF_NAN(X)          ((tmp_nan = (void *)(X), &tmp_nan)

#define STD_ENDL()        (printf("\n"))

typedef int (*CompareFunction)(const void *elemAddr1, const void *elemAddr2);
typedef void (*PrintFunction)(const void *elemAddr);
typedef void (*FreeFunction)(void *elemAddr);
typedef void (*MapFunction)(void *elemAddr, void *auxData);

#define swap(a, b)              (__swap(&(a), &(b), sizeof(a)))
#define memswap(a, b, s)        (__swap(a, b, s))
extern void __swap(void *a, void *b, const size_t elemSize);

#define MAX(a, b)   ({ \
    __typeof__ (a) _a = a; \
    __typeof__ (b) _b = b; \
    _a >= _b ? _a : _b; \
})

#define MIN(a, b)   ({ \
    __typeof__ (a) _a = a; \
    __typeof__ (b) _b = b; \
    _a <= _b ? _a : _b; \
})

size_t rand64(void);
size_t randint(size_t a, size_t b);
double randfloat(double a, double b);


/**
 * Count the number of variadic arguments.
 */
#define PP_NARG(...)  PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
     _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
    _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
    _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
    _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
    63,62,61,60,                   \
    59,58,57,56,55,54,53,52,51,50, \
    49,48,47,46,45,44,43,42,41,40, \
    39,38,37,36,35,34,33,32,31,30, \
    29,28,27,26,25,24,23,22,21,20, \
    19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

#endif //CDATASTRUCTS_COMMON_H
