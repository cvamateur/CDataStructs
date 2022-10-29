//
// Created by chris on 2022/10/28.
//

#ifndef CDATASTRUCTS_HEAPQ_H
#define CDATASTRUCTS_HEAPQ_H

#include "stddef.h"
#include "common.h"

typedef struct __Vector vector;
typedef int (*HeapCompareFunc)(void *, void *);
typedef struct __Heap {
    vector* container;
    HeapCompareFunc cmpFn;
} heapq;


void heapqInit(heapq *this, size_t capacity, size_t elemSize, HeapCompareFunc cmpFn, FreeFunction freeFn);
void heapqDestroy(heapq *this);
size_t heapqSize(heapq *this);
int heapqEmpty(heapq *this);
void* heapqTop(heapq *this);
void heapqPush(heapq* this, void *valueAddr);
void heapqPop(heapq* this, void *valueAddr);
void heapqPushPop(heapq *this, void *iValueAddr, void *oValueAddr);
void heapqPopPush(heapq *this, void *iValueAddr, void *oValueAddr);

void heapqMap(heapq *this, MapFunction mapFn, void *auxData);


void heapify(void *data, size_t size, size_t elemSize, HeapCompareFunc cmpFn);
void heapSort(void *data, size_t size, size_t elemSize, HeapCompareFunc cmpFn);


#endif //CDATASTRUCTS_HEAPQ_H
