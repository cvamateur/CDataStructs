//
// Created by chris on 2022/10/23.
//
#ifndef CDATASTRUCTS_VECTOR_H
#define CDATASTRUCTS_VECTOR_H
#include <stddef.h>
#include "common.h"


typedef struct __Vector {
    const size_t elemSize;  // Element size in bytes
    size_t capacity;        // Allocated size
    size_t size;            // Logical size
    void* data;

    void (*freeFn)(void *);
} vector;

/**
 * Initialize an empty vector.
 * @param v Address of a vector to initialize.
 * @param freeFn Function that free element.
 * @param elemSize Number of bytes for each element.
 */
void vectorInit(vector* this, size_t elemSize, size_t size, FreeFunction freeFn);

/**
 * Destroy a vector, free all resources and set it to empty.
 * @param v Address of the vector to destroy.
 */
void vectorDestroy(vector *this);

/**
 * Append a element at the end.
 * @param v Address of the vector.
 * @param valueAddr Address of the element to push.
 */
void vectorPushBack(vector *this, void *valueAddr);

/**
 * Pop the last element, save in valueAddr. It's user's responsibility to
 * manage the resources if valueAddr is an pointer pointing to a dynamically
 * allocated resources.
 * @param this Address of the vector.
 * @param valueAddr Address of the value being popped.
 */
void vectorPopBack(vector *this, void *valueAddr);

/**
 * Print all elements in a vector.
 * @param this Address of the vector.
 * @param printElem Function to print each element.
 */
void vectorPrint(vector *this, PrintFunction printFn);

/**
 * Get the value at position.
 * @param this Address of the vector.
 * @param index Index of which value to return.
 * @return Address of the of the returned value.
 */
void* vectorNth(vector* this, size_t index);

/**
 * Insert value at index `index`.
 * @param this Address of the vector.
 * @param valueAddr Address of the value to be inserted.
 * @param index Index to insert.
 */
void vectorInsert(vector *this, void *valueAddr, size_t index);

void vectorDelete(vector *this, size_t index);

void vectorGet(vector *this, size_t index, void *valueAddr);

void vectorSet(vector *this, size_t index, void *valueAddr);

void vectorReplace(vector *this, void *valueAddr, size_t index);

void vectorSort(vector *this, CompareFunction cmpFn);

long vectorSearch(const vector *this, const void *key, CompareFunction cmpFn, size_t startIdx, int isSorted);

void vectorMap(vector *this, MapFunction mapFn, void *auxData);

#endif //CDATASTRUCTS_VECTOR_H
