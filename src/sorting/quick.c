//
// Created by chris on 2022/10/29.
//
#include <assert.h>
#include "sort.h"

static ssize_t partition(void *data, size_t elemSize, ssize_t left, ssize_t right, CompareFunction cmpFn) {
    assert(left < right);
    void *pivot = (char*) data + left * elemSize;
    ssize_t low = left + 1;
    ssize_t high = right;

    while (low <= high) {
        while (low <= high && cmpFn((char*) data + low * elemSize, pivot))
            ++low;
        while (low <= high && cmpFn(pivot, (char*) data + high * elemSize))
            --high;
        if (low < high)
            memswap((char*) data + low * elemSize, (char*) data + high * elemSize, elemSize);
    }
    memswap(pivot, (char*) data + high * elemSize, elemSize);
    return high;
}

static void quickSortRecursive(void *data, size_t elemSize, ssize_t left, ssize_t right, CompareFunction cmpFn) {
    if (right <= left) return;

    ssize_t pivotIdx = partition(data, elemSize, left, right, cmpFn);
    quickSortRecursive(data, elemSize, left, pivotIdx - 1, cmpFn);
    quickSortRecursive(data, elemSize, pivotIdx + 1, right, cmpFn);
}

void quickSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn) {
    if (size <= 1) return;
    quickSortRecursive(data, elemSize, 0, (ssize_t) size - 1, cmpFn);
}
