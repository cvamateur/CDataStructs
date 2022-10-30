//
// Created by chris on 2022/10/29.
//
#include "sort.h"


void selectionSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn) {
    void *pa, *pb, *pc;
    size_t i, j;
    for (i = 0; i < size - 1; ++i) {
        pa = (char *) data + i * elemSize;
        pb = (char *) data + (i + 1) * elemSize;
        for (j = i + 2; j < size; ++j) {
            pc = (char*)data + j * elemSize;
            if (cmpFn(pc, pb))
                pb = pc;
        }
        if (cmpFn(pb, pa))
            memswap(pa, pb, elemSize);
    }
}