//
// Created by chris on 2022/10/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

static inline void vectorAutoGrow(vector *this) {
    this->capacity = this->capacity == 0 ? 1 : 2 * this->capacity;
    this->data = realloc(this->data, this->capacity * this->elemSize);
    assert(this->data != NULL);
}

void vectorInit(vector *this, size_t elemSize, size_t size, FreeFunction freeFn) {
    *(size_t *) &this->elemSize = elemSize;
    this->capacity = size;
    this->size = 0;
    this->freeFn = freeFn;
    this->data = (size == 0 ? NULL : malloc(size * elemSize));
}

void vectorDestroy(vector *this) {
    if (this->data != NULL) {
        if (this->freeFn != NULL)
            for (int i = 0; i < this->size; ++i)
                this->freeFn((char *) this->data + i * this->elemSize);
        free(this->data);
    }
    *(size_t *) &this->elemSize = 0;
    this->capacity = 0;
    this->size = 0;
    this->data = NULL;
}

void vectorPushBack(vector *this, void *valueAddr) {
    if (this->size == this->capacity)
        vectorAutoGrow(this);
    void *target = (char *) this->data + this->size * this->elemSize;
    memcpy(target, valueAddr, this->elemSize);
    ++this->size;
}

void vectorPopBack(vector *this, void *valueAddr) {
    assert(this->size > 0);
    --this->size;
    void *source = (char *) this->data + this->size * this->elemSize;
    memcpy(valueAddr, source, this->elemSize);
}

void vectorPrint(vector *this, PrintFunction printFn) {
    printf("[");
    for (int i = 0; i < this->size; ++i) {
        printFn((char *) this->data + i * this->elemSize);
        if (i != this->size - 1)
            printf(", ");
    }
    printf("]");
}

void *vectorNth(vector *this, size_t index) {
    return (char *) this->data + index * this->elemSize;
}

void vectorInsert(vector *this, void *valueAddr, size_t index) {
    if (this->size == this->capacity)
        vectorAutoGrow(this);
    void *target = (char *) this->data + index * this->elemSize;
    memmove((char *) target + this->elemSize,
            target,
            (this->size - index) * this->elemSize);
    memcpy(target, valueAddr, this->elemSize);
    ++this->size;
}

void vectorDelete(vector *this, size_t index) {
    assert(index < this->size);
    void *target = (char *) this->data + index * this->elemSize;
    memmove(target,
            (char *) target + this->elemSize,
            (this->size - index) * this->elemSize);
    --this->size;
}

void vectorGet(vector *this, size_t index, void *valueAddr) {
    assert(index < this->size);
    void *source = (char*) this->data + index * this->elemSize;
    memcpy(valueAddr, source, this->elemSize);
}

void vectorSet(vector *this, size_t index, void *valueAddr) {
    assert(index < this->size);
    void *target = (char*) this->data + index * this->elemSize;
    memcpy(target, valueAddr, this->elemSize);
}

void vectorReplace(vector *this, void *valueAddr, size_t index) {
    void *target = (char *) this->data + index * this->elemSize;
    if (this->freeFn != NULL)
        this->freeFn(target);
    memcpy(target, valueAddr, this->elemSize);
}

void vectorSort(vector *this, CompareFunction cmpFn) {
    qsort(this->data, this->size, this->elemSize, cmpFn);
}

static void *lsearch(const void *key,
                     const void *base,
                     const size_t nmemb,
                     const size_t elemSize,
                     CompareFunction cmpFn) {
    void *elemAddr;
    for (size_t i = 0; i < nmemb; ++i) {
        elemAddr = (char *) base + i * elemSize;
        if (cmpFn(key, elemAddr) == 0)
            return elemAddr;
    }
    return NULL;
}

long vectorSearch(const vector *this, const void *key, CompareFunction cmpFn, size_t startIdx, int isSorted) {
    void *found;
    if (isSorted)
        found = bsearch(key,
                        this->data + startIdx * this->elemSize,
                        this->size,
                        this->elemSize,
                        cmpFn);
    else
        found = lsearch(key,
                        this->data + startIdx * this->elemSize,
                        this->size,
                        this->elemSize,
                        cmpFn);
    return (long) (found ? ((char *) found - (char *) this->data) / this->elemSize : -1);
}

void vectorMap(vector *this, MapFunction mapFn, void *auxData) {
    void *elemAddr;
    for (size_t i = 0; i < this->size; ++i) {
        elemAddr = (char *) this->data + i * this->elemSize;
        mapFn(elemAddr, auxData);
    }
}

void vectorMap2(vector *this, MapFunction2 mapFn, void *auxData) {
    void *elemAddr;
    for (size_t i = 0; i < this->size; ++i) {
        elemAddr = (char*) this->data + i * this->elemSize;
        mapFn(elemAddr, i, auxData);
    }
}