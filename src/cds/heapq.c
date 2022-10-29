//
// Created by chris on 2022/10/28.
//
#include "heapq.h"
#include "vector.h"
#include <stdlib.h>
#include <assert.h>

static int flag_fixed_heap = 0;

#define     PARENT(i)       ((i) > 0 ? ((i) - 1) / 2 : (i))
#define     LEFT(i, n)      ((2 * (i) + 1) < (n) ? 2 * (i) + 1 : (i))
#define     RIGHT(i, n)     ((2 * (i) + 2) < (n) ? 2 * (i) + 2 : (i))


static void heapify_down(void *data, size_t size, size_t elemSize, size_t pIdx, HeapCompareFunc cmpFn) {
    size_t lIdx = LEFT(pIdx, size);
    size_t rIdx = RIGHT(pIdx, size);
    void *pData = (char *) data + pIdx * elemSize;
    void *lData = (char *) data + lIdx * elemSize;
    void *rData = (char *) data + rIdx * elemSize;

    size_t cIdx;
    void *cData;
    if (cmpFn(lData, rData)) {
        cIdx = lIdx;
        cData = lData;
    } else {
        cIdx = rIdx;
        cData = rData;
    }

    if (cmpFn(cData, pData)) {
        memswap(cData, pData, elemSize);
        heapify_down(data, size, elemSize, cIdx, cmpFn);
    }
}

static void heapify_up(void *data, size_t size, size_t elemSize, size_t cIdx, HeapCompareFunc cmpFn) {
    size_t pIdx = PARENT(cIdx);
    void *pData = (char *) data + pIdx * elemSize;
    void *cData = (char *) data + cIdx * elemSize;
    char *buffer[elemSize];
    if (cmpFn(cData, pData)) {
        memswap(cData, pData, elemSize);
        heapify_up(data, size, elemSize, pIdx, cmpFn);
    }
}

void heapqInit(heapq *this, size_t capacity, size_t elemSize, HeapCompareFunc cmpFn, FreeFunction freeFn) {
    this->container = malloc(sizeof(vector));
    vectorInit(this->container, elemSize, capacity, freeFn);
    this->cmpFn = cmpFn;
    flag_fixed_heap = (capacity != 0);
}

void heapqDestroy(heapq *this) {
    vectorDestroy(this->container);
    free(this->container);
}

inline size_t heapqSize(heapq *this) {
    return this->container->size;
}

inline int heapqEmpty(heapq *this) {
    return this->container->size == 0;
}

inline void *heapqTop(heapq *this) {
    return this->container->data;
}

void heapqPush(heapq *this, void *valueAddr) {
    assert(!flag_fixed_heap || this->container->size < this->container->capacity);
    vectorPushBack(this->container, valueAddr);
    heapify_up(this->container->data, this->container->size, this->container->elemSize,
               this->container->size - 1, this->cmpFn);
}

void heapqPop(heapq *this, void *valueAddr) {
    assert(this->container->size > 0);
    void *pFirst = vectorNth(this->container, 0);
    void *pLast = vectorNth(this->container, this->container->size - 1);
    memswap(pFirst, pLast, this->container->elemSize);
    vectorPopBack(this->container, valueAddr);
    heapify_down(this->container->data, this->container->size, this->container->elemSize, 0, this->cmpFn);
}

void heapqPushPop(heapq *this, void *iValueAddr, void *oValueAddr) {
    assert(!flag_fixed_heap || this->container->size < this->container->capacity);
    if (this->cmpFn(iValueAddr, heapqTop(this)))
        memcpy(oValueAddr, iValueAddr, this->container->elemSize);
    else {
        memcpy(oValueAddr, heapqTop(this), this->container->elemSize);
        memcpy(heapqTop(this), iValueAddr, this->container->elemSize);
        heapify_down(this->container->data, this->container->size, this->container->elemSize, 0, this->cmpFn);
    }
}

void heapqPopPush(heapq *this, void *iValueAddr, void *oValueAddr) {
    assert(this->container->size > 0);
    memcpy(oValueAddr, heapqTop(this), this->container->elemSize);
    memcpy(heapqTop(this), iValueAddr, this->container->elemSize);
    heapify_down(this->container->data, this->container->size, this->container->elemSize, 0, this->cmpFn);
}

void heapqMap(heapq *this, MapFunction mapFn, void *auxData) {
    void *data;
    for (size_t i = 0; i < this->container->size; ++i) {
        data = vectorNth(this->container, i);
        mapFn(data, auxData);
    }
}

void heapify(void *data, size_t size, size_t elemSize, HeapCompareFunc cmpFn) {
    if (size < 2) return;
    for (long long i = (long long) size / 2; i >= 0; --i)
        heapify_down(data, size, elemSize, i, cmpFn);
}

void heapSort(void *data, size_t size, size_t elemSize, HeapCompareFunc cmpFn) {
    heapify(data, size, elemSize, cmpFn);
    for (long long i = (long long) size - 1; i >= 0; --i) {
        memswap(data, (char*) data + i * elemSize, elemSize);
        heapify_down(data , i, elemSize, 0, cmpFn);
    }
}