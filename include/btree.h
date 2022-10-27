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

typedef struct __BSTNode {
    void *data;
    struct __BSTNode *left;
    struct __BSTNode *right;
    int height;
} bnode;

typedef struct __BSTree {
    bnode *root;
    size_t size;
    size_t elemSize;

    FreeFunction freeFn;
    CompareFunction cmpFn;
} btree;

void btreeInit(btree* this, size_t elemSize, CompareFunction cmpFn, FreeFunction freeFn);
void btreeDestroy(btree *this);
void btreeInsert(btree *this, void *valueAddr);
void btreeDelete(btree *this, void *valueAddr);

/**
 * Return a pointer to the node if found or NULL otherwise.
 */
bnode *btreeFind(btree *this, void *valueAddr);

void btreeMap(btree *this, TraversalOrder order, MapFunction mapFn, void *auxData);

void btreePrint(btree *this, void (*printDataFn)(void *));

#endif //CDATASTRUCTS_BTREE_H
