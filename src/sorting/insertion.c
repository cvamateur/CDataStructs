//
// Created by sparkai on 22-10-25.
//
#include "sort.h"


void insertionSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn) {
    void *pa, *pb;
    for (ssize_t i = 1; i < size; ++i)
        for (ssize_t j = i; j > 0; --j) {
            pa = (char *) data + j * elemSize;
            pb = (char *) data + (j - 1) * elemSize;
            if (cmpFn(pa, pb))
                memswap(pa, pb, elemSize);
        }
}