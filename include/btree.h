//
// Created by sparkai on 22-10-24.
//

#ifndef CDATASTRUCTS_BTREE_H
#define CDATASTRUCTS_BTREE_H

#include <stddef.h>
#include "common.h"

typedef enum {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    LEVEL_ORDER,
} TraversalOrder;

typedef struct __BTNode {
    void *data;
    struct __BTNode *left;
    struct __BTNode *right;
} bnode;

typedef struct __BTree {
    bnode *root;
    size_t size;
    size_t elemSize;

    FreeFunction freeFn;
    CompareFunction cmpFn;
} btree;

void btreeInit(btree* this, size_t elemSize, CompareFunction cmpFn, FreeFunction freeFn);
void btreeDestroy(btree *this);
void btreeInsert(btree *this, void *valueAddr);
void btreePrint(btree *this, PrintFunction printFn);
void btreeMap(btree *this, TraversalOrder order, MapFunction mapFn, void *auxData);

#endif //CDATASTRUCTS_BTREE_H
