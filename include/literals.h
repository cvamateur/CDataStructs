//
// Created by chris on 2022/10/23.
//

#ifndef CDATASTRUCTS_LITERALS_H
#define CDATASTRUCTS_LITERALS_H

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

#define PTR_CHAR(X)         ((tmp_char = (char)(X)), &tmp_char)
#define PTR_SHORT(X)        ((tmp_short = (short)(X)), &tmp_short)
#define PTR_INT(X)          ((tmp_int = (int)(X)), &tmp_int)
#define PTR_LONG(X)         ((tmp_long = (long)(X)), &tmp_long)
#define PTR_LONGLONG(X)     ((tmp_longlong = (long long)(X)), &tmp_longlong)
#define PTR_FLOAT(X)        ((tmp_float = (float)(X)), &tmp_float)
#define PTR_DOUBLE(X)       ((tmp_double = (double)(X)), &tmp_double)
#define PTR_STRING(X)       ((tmp_string = (char *)(X)), &tmp_string)

#define BREAK_LINE()        (printf("\n"))

#endif //CDATASTRUCTS_LITERALS_H
