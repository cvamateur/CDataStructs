//
// Created by chris on 2022/10/23.
//

#ifndef CDATASTRUCTS_COMMON_H
#define CDATASTRUCTS_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char tmp_char;
static short tmp_short;
static int tmp_int;
static long tmp_long;
static long long tmp_longlong;
static float tmp_float;
static double tmp_double;
static char *tmp_string;

#define REF_CHAR(X)         ((tmp_char = (char)(X)), &tmp_char)
#define REF_SHORT(X)        ((tmp_short = (short)(X)), &tmp_short)
#define REF_INT(X)          ((tmp_int = (int)(X)), &tmp_int)
#define REF_LONG(X)         ((tmp_long = (long)(X)), &tmp_long)
#define REF_LONGLONG(X)     ((tmp_longlong = (long long)(X)), &tmp_longlong)
#define REF_FLOAT(X)        ((tmp_float = (float)(X)), &tmp_float)
#define REF_DOUBLE(X)       ((tmp_double = (double)(X)), &tmp_double)
#define REF_STRING(X)       ((tmp_string = (char *)(X)), &tmp_string)
#define BREAK_LINE()        (printf("\n"))

typedef int (*CompareFunction)(const void* elemAddr1, const void* elemAddr2);
typedef void (*PrintFunction)(const void* elemAddr);
typedef void (*FreeFunction)(void * elemAddr);
typedef void (*MapFunction)(void *elemAddr, void* auxData);

#endif //CDATASTRUCTS_COMMON_H
