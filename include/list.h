//
// Created by chris on 2022/10/23.
//

#ifndef CDATASTRUCTS_LIST_H
#define CDATASTRUCTS_LIST_H
#include <stddef.h>
#include "common.h"

typedef struct __DLNode {
    struct __DLNode *prev;
    struct __DLNode *next;
    void *data;
} DLNode;

typedef struct __DLList {
    const size_t elemSize;
    size_t size;
    DLNode *head;
    DLNode *tail;

    FreeFunction freeFn;
} list;

void listInit(list* this, size_t elemSize, FreeFunction freeFn);
void listDestroy(list *this);
void listPushFront(list *this, void *valueAddr);
void listPopFront(list *this, void *valueAddr);
void listPushBack(list *this, void *valueAddr);
void listPopBack(list *this, void *valueAddr);
void listMap(list *this, MapFunction mapFn, void *auxData);
void listMapReverse(list *this, MapFunction mapFn, void *auxData);
void listReverse(list *this);
void listSort(list *this, CompareFunction cmpFn);
void listSortedMerge(list *this, list *other, CompareFunction cmpFn);

#endif //CDATASTRUCTS_LIST_H
