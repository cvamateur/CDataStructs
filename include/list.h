//
// Created by chris on 2022/10/23.
//

#ifndef CDATASTRUCTS_LIST_H
#define CDATASTRUCTS_LIST_H
#include <stddef.h>

typedef struct __DLNode {
    struct __DLNode *prev;
    struct __DLNode *next;
    void *data;
} DLNode;

void DLNode_init(DLNode *this, void *valueAddr, size_t elemSize);

typedef struct {
    const size_t elemSize;
    size_t size;
    DLNode *head;
    DLNode *tail;

    void (*freeFn)(void *);
} list;


void listInit(list* this, size_t elemSize, void (*freeFn)(void *));
void listDestroy(list *this);
void listPushFront(list *this, void *valueAddr);
void listPopFront(list *this, void *valueAddr);
void listPushBack(list *this, void *valueAddr);
void listPopBack(list *this, void *valueAddr);
void listPrint(list *this, void printFn(void *));

#endif //CDATASTRUCTS_LIST_H
