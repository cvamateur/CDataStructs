//
// Created by sparkai on 22-10-25.
//
#include "sort.h"

#define getNth(data, i, s)      ((char*) data + (i) * (s))

void bubbleSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn) {
    void *pa, *pb;
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size - i - 1; ++j) {
            pa = getNth(data, j, elemSize);
            pb = getNth(data, j + 1, elemSize);
            if (cmpFn(pb, pa)) {
                memswap(pa, pb, elemSize);
            }
        }
}