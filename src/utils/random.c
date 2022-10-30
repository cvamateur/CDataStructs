//
// Created by chris on 2022/10/30.
//
#include "common.h"
#include <time.h>

#define IMAX_BITS(m) ((m)/((m)%255+1) / 255%255*8 + 7-86/((m)%255+12))
#define RAND_MAX_WIDTH IMAX_BITS(RAND_MAX)
_Static_assert((RAND_MAX & (RAND_MAX + 1u)) == 0, "RAND_MAX not a Mersenne number");


size_t rand64(void) {
    size_t r = 0;
    for (int i = 0; i < 64; i += RAND_MAX_WIDTH) {
        r << RAND_MAX_WIDTH;
        r ^= (unsigned) rand();
    }
    return r;
}

size_t randint(size_t a, size_t b) {
//    srand(time(NULL));
    return rand64() % (b - a + 1) + a;
}

double randfloat(double a, double b) {
//    srand(time(NULL));
    double f = (double) rand() / RAND_MAX;
    return a + f * (b - a);
}

