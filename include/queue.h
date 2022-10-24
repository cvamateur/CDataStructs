//
// Created by sparkai on 22-10-24.
//

#ifndef CDATASTRUCTS_QUEUE_H
#define CDATASTRUCTS_QUEUE_H

#include "list.h"

typedef     list    queue;

#define queueInit(q, elemSize, freeFn)      listInit(&(q), elemSize, freeFn)
#define queueDestroy(q)                     listDestroy(&(q))
#define queuePush(q, vaddr)                 listPushBack(&(q), vaddr)
#define queuePop(q, vaddr)                  listPopFront(&(q), vaddr)
#define queueEmpty(q)                       (q.size == 0)
#define queueSize(q)                        (q.size)


#endif //CDATASTRUCTS_QUEUE_H
