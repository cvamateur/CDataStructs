//
// Created by sparkai on 22-10-25.
//

#ifndef CDATASTRUCTS_DEQUE_H
#define CDATASTRUCTS_DEQUE_H
#include "list.h"

typedef     list    deque;

#define dequeInit(dq, elemSize, freeFn)     listInit(&(dq), elemSize, freeFn)
#define dequeDestroy(dq)                    listDestroy(&(dq))
#define dequePushBack(dq, vaddr)            listPushBack(&(dq), vaddr)
#define dequePushFront(dq, vaddr)           listPushFront(&(dq), vaddr)
#define dequePopBack(dq, vaddr)             listPopBack(&(dq), vaddr)
#define dequePopFront(dq, vaddr)            listPopFront(&(dq), vaddr)
#define dequeEmpty(dq)                      ((dq).size == 0)
#define dequeSize(dq)                       ((dq).size)


#endif //CDATASTRUCTS_DEQUE_H
