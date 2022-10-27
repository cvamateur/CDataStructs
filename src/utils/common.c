//
// Created by sparkai on 22-10-26.
//
#include "common.h"

char tmp_char;
short tmp_short;
int tmp_int;
long tmp_long;
long long tmp_longlong;
float tmp_float;
double tmp_double;
char *tmp_string;


void __swap(void *a, void *b, const size_t elemSize) {
    char buffer[elemSize];
    memcpy(buffer, a, elemSize);
    memcpy(a, b, elemSize);
    memcpy(b, buffer, elemSize);
}