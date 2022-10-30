//
// Created by sparkai on 22-10-25.
//

#ifndef CDATASTRUCTS_SORT_H
#define CDATASTRUCTS_SORT_H

#include <stddef.h>
#include "common.h"

void bubbleSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn);
void insertionSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn);
void selectionSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn);
void quickSort(void *data, size_t size, size_t elemSize, CompareFunction cmpFn);

#endif //CDATASTRUCTS_SORT_H
