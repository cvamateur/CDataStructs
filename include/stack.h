//
// Created by sparkai on 22-10-24.
//

#ifndef CDATASTRUCTS_STACK_H
#define CDATASTRUCTS_STACK_H
#include "vector.h"

typedef  vector  stack;


#define stackInit(s, elemSize, initSize, freeFn)    vectorInit(&(s), elemSize, initSize, freeFn)
#define stackInitEmpty(s, elemSize, freeFn)         vectorInit(&(s), elemSize, 0, freeFn)
#define stackDestroy(s)                             vectorDestroy(&(s))
#define stackPush(s, vaddr)                         vectorPushBack(&(s), vaddr)
#define stackPop(s, vaddr)                          vectorPopBack(&(s), vaddr)
#define stackEmpty(s)                               ((s).size == 0)


#endif //CDATASTRUCTS_STACK_H
