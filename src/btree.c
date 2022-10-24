//
// Created by sparkai on 22-10-24.
//
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"
#include "stack.h"

static void bnode_init(bnode *this, void *valueAddr, size_t elemSize) {
    this->left = NULL;
    this->right = NULL;
    this->data = malloc(sizeof(elemSize));
    assert(this->data != NULL);
    memcpy(this->data, valueAddr, elemSize);
}

static bnode* bnode_insert(bnode *this, bnode *other, CompareFunction cmpFn) {
    if (this == NULL)
        return other;
    if (cmpFn(other->data, this->data))
        this->left = bnode_insert(this->left, other, cmpFn);
    else
        this->right = bnode_insert(this->right, other, cmpFn);
    return this;
}

void btreeInit(btree* this, size_t elemSize, CompareFunction cmpFn, FreeFunction freeFn) {
    this->root = NULL;
    this->size = 0;
    this->elemSize = elemSize;
    this->cmpFn = cmpFn;
    this->freeFn = freeFn;
}

void btreeDestroy(btree *this) {
    stack s;
    bnode *trashNode;

    stackInitEmpty(s, sizeof(bnode*), NULL);
    stackPush(s, &this->root);
    while (!stackEmpty(s)) {
        stackPop(s, &trashNode);
        if (trashNode == NULL) continue;
        stackPush(s, &trashNode->left);
        stackPush(s, &trashNode->right);
        if (trashNode->data != NULL && this->freeFn != NULL)
            this->freeFn(trashNode->data);
        free(trashNode);
    }
    stackDestroy(s);
}

void btreeInsert(btree *this, void *valueAddr) {
    bnode *newNode = malloc(sizeof(bnode));
    bnode_init(newNode, valueAddr, this->elemSize);
    assert(newNode != NULL);
    this->root = bnode_insert(this->root, newNode, this->cmpFn);
    ++this->size;
}

static inline void btreePreOrder(btree *this, MapFunction mapFn, void *auxData) {
    stack s;
    bnode *node;

    stackInitEmpty(s, sizeof(bnode*), NULL);
    stackPush(s, &this->root);
    while (!stackEmpty(s)) {
        stackPop(s, &node);
        if (node == NULL) continue;
        mapFn(node->data, auxData);
        stackPush(s, &node->right);
        stackPush(s, &node->left);
    }
    stackDestroy(s);
}

static inline void btreeInOrder(btree *this, MapFunction mapFn, void *auxData) {
    stack s;
    bnode *node = this->root;

    stackInitEmpty(s, sizeof(bnode*), NULL);
    for(;;) {
        if (node != NULL) {
            stackPush(s, &node);
            node = node->left;
        } else if (!stackEmpty(s)) {
            stackPop(s, &node);
            mapFn(node->data, auxData);
            node = node->right;
        } else {
            break;
        }
    }
    stackDestroy(s);
}

static inline void btreePostOrder(btree *this, MapFunction mapFn, void *auxData) {

}

static inline void btreeLevelOrder(btree *this, MapFunction mapFn, void *auxData) {

}

void btreeMap(btree *this, TraversalOrder order, MapFunction mapFn, void *auxData) {
    switch (order) {
        default:
        case PRE_ORDER:
            btreePreOrder(this, mapFn, auxData);
            break;
        case IN_ORDER:
            btreeInOrder(this, mapFn, auxData);
            break;
        case POST_ORDER:
            btreePostOrder(this, mapFn, auxData);
            break;
        case LEVEL_ORDER:
            btreeLevelOrder(this, mapFn, auxData);
            break;
    }
}