//
// Created by sparkai on 22-10-24.
//
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "btree.h"
#include "stack.h"
#include "queue.h"

static void bnode_init(bnode *node, void *valueAddr, size_t elemSize) {
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->data = malloc(sizeof(elemSize));
    assert(node->data != NULL);
    memcpy(node->data, valueAddr, elemSize);
}

void bnode_print(const bnode *node, char* prefix, int isLeft, void (*printDataFn)(void *)) {
    if (node == NULL) return;

    printf("%s", prefix);
    printf("%s", isLeft ? "├── " : "└── ");
    printDataFn(node->data);
    printf("\n");

    char* nextPrefix = malloc(strlen(prefix) + 5);
    strcpy(nextPrefix, prefix);
    strcat(nextPrefix, isLeft ? "│   " : "    ");

    bnode_print(node->left, nextPrefix, 1, printDataFn);
    bnode_print(node->right, nextPrefix, 0, printDataFn);

    free(nextPrefix);
}


#define HEIGHT(node)        (((node) == NULL) ? (0) : (node)->height)
#define SKEW(node)          (HEIGHT((node)->left) - HEIGHT((node)->right))

/* *****************************************************************
 *      _____<D>__       rotate_right(<D>)     __<B>___________
 *    __<B>__    <E>          =>              <A>          __<D>__
 *   <A>   <C>   / \                          / \         <C>   <E>
 *   / \   / \  /___\         <=             /___\        / \   / \
 *  /___\ /___\          rotate_left(<B>)                /___\ /___\
 * ****************************************************************** */
static inline void update_property(bnode *node) {
    node->height = 1 + MAX(HEIGHT(node->left), HEIGHT(node->right));
}

static void rightRotate(bnode **nodeRef) {
    bnode *leftTree = (*nodeRef)->left;
    assert(leftTree != NULL);

    (*nodeRef)->left = leftTree->right;
    leftTree->right = *nodeRef;
    *nodeRef = leftTree;
    update_property((*nodeRef)->right);
    update_property(*nodeRef);
}

static void leftRotate(bnode **nodeRef) {
    bnode *rightTree = (*nodeRef)->right;
    assert(rightTree != NULL);

    (*nodeRef)->right = rightTree->left;
    rightTree->left = *nodeRef;
    *nodeRef = rightTree;
    update_property((*nodeRef)->left);
    update_property(*nodeRef);
}

static void maintain(bnode **nodeRef) {
    if (*nodeRef == NULL) return;

    switch (SKEW(*nodeRef)) {
        case -2: {
            if (SKEW((*nodeRef)->right) > 0)
                rightRotate(&(*nodeRef)->right);
            leftRotate(nodeRef);
            return;
        }
        case 2: {
            if (SKEW((*nodeRef)->left) < 0)
                leftRotate(&(*nodeRef)->left);
            rightRotate(nodeRef);
            return;
        }
    }
    update_property(*nodeRef);
}

static void bnode_insert_recursive(bnode **nodeRef, bnode *other, CompareFunction cmpFn) {
    bnode *node = *nodeRef;
    if (node == NULL) {
        *nodeRef = other;
        return;
    }

    if (cmpFn(other->data, node->data) <= 0)
        bnode_insert_recursive(&(node->left), other, cmpFn);
    else
        bnode_insert_recursive(&(node->right), other, cmpFn);

    maintain(nodeRef);
}

static bnode **bnode_find(bnode **nodeRef, void *valueAddr, CompareFunction cmpFn) {
    if (*nodeRef == NULL)
        return NULL;

    int cmpResult = cmpFn(valueAddr, (*nodeRef)->data);
    if (cmpResult == 0)
        return nodeRef;
    else if (cmpResult < 0)
        return bnode_find(&(*nodeRef)->left, valueAddr, cmpFn);
    else
        return bnode_find(&(*nodeRef)->right, valueAddr, cmpFn);
}

static int bnode_delete_recursive(bnode **nodeRef, void *valueAddr, CompareFunction cmpFn, FreeFunction freeFn) {
    if (*nodeRef == NULL)
        return 0;

    int foundValue;
    int cmpResult = cmpFn(valueAddr, (*nodeRef)->data);
    if (cmpResult < 0)
        foundValue = bnode_delete_recursive(&(*nodeRef)->left, valueAddr, cmpFn, freeFn);
    else if (cmpResult > 0)
        foundValue = bnode_delete_recursive(&(*nodeRef)->right, valueAddr, cmpFn, freeFn);
    else {
        bnode *current = *nodeRef;
        bnode **tmpNodeRef;
        // 1. If the node is a leaf: delete it
        if (current->left == NULL && current->right == NULL) {
            if (freeFn != NULL)
                freeFn(current->data);
            free(current);
            *nodeRef = NULL;
            foundValue = 1;

        // 2. If the node has left subtree, replace value with the "last-node" in left and
        //    recurse down from the "last-node"
        } else if (current->left != NULL) {
            tmpNodeRef = &current->left;
            while ((*tmpNodeRef)->right != NULL)
                tmpNodeRef = &(*tmpNodeRef)->right;
            swap(current->data, (*tmpNodeRef)->data);
            foundValue = bnode_delete_recursive(tmpNodeRef, valueAddr, cmpFn, freeFn);

        // 3. If the node has right subtree, replace value with the "first-node" in right and
        //    recurse down the "first-node"
        } else {
            tmpNodeRef = &current->right;
            while ((*tmpNodeRef)->left != NULL)
                tmpNodeRef = &(*tmpNodeRef)->left;
            swap(current->data, (*tmpNodeRef)->data);
            foundValue = bnode_delete_recursive(tmpNodeRef, valueAddr, cmpFn, freeFn);
        }
    }
    if (foundValue)
        maintain(nodeRef);
    return foundValue;
}

void btreeInit(btree *this, size_t elemSize, CompareFunction cmpFn, FreeFunction freeFn) {
    this->root = NULL;
    this->size = 0;
    this->elemSize = elemSize;
    this->cmpFn = cmpFn;
    this->freeFn = freeFn;
}

void btreeDestroy(btree *this) {
    stack s;
    bnode *trashNode;

    stackInitEmpty(s, sizeof(bnode *), NULL);
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
    bnode_insert_recursive(&this->root, newNode, this->cmpFn);
    ++this->size;
}

int btreeDelete(btree *this, void *valueAddr) {
    if (this->root == NULL) return 0;
    int deleted = bnode_delete_recursive(&this->root, valueAddr, this->cmpFn, this->freeFn);
    if (deleted)
        --this->size;
    return deleted;
}

static inline void btreePreOrder(btree *this, MapFunction mapFn, void *auxData) {
    stack s;
    bnode *node;

    stackInitEmpty(s, sizeof(bnode *), NULL);
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
    bnode *current = this->root;

    stackInitEmpty(s, sizeof(bnode *), NULL);
    for (;;) {
        if (current != NULL) {
            stackPush(s, &current);
            current = current->left;
        } else if (!stackEmpty(s)) {
            stackPop(s, &current);
            mapFn(current->data, auxData);
            current = current->right;
        } else {
            break;
        }
    }
    stackDestroy(s);
}
static inline void btreePostOrder(btree *this, MapFunction mapFn, void *auxData) {
    stack s1;
    stack s2;
    bnode *node;

    stackInitEmpty(s1, sizeof(bnode *), NULL);
    stackInitEmpty(s2, sizeof(bnode *), NULL);
    stackPush(s1, &this->root);
    while (!stackEmpty(s1)) {
        stackPop(s1, &node);
        if (node == NULL) continue;
        stackPush(s2, &node);
        stackPush(s1, &node->left);
        stackPush(s1, &node->right);
    }
    while (!stackEmpty(s2)) {
        stackPop(s2, &node);
        mapFn(node->data, auxData);
    }
    stackDestroy(s1);
    stackDestroy(s2);
}
static inline void btreeLevelOrder(btree *this, MapFunction mapFn, void *auxData) {
    queue q;
    bnode *node;

    queueInit(q, sizeof(bnode *), NULL);
    queuePush(q, &this->root);
    while (!queueEmpty(q)) {
        queuePop(q, &node);
        if (node == NULL) continue;
        queuePush(q, &node->left);
        queuePush(q, &node->right);
        mapFn(node->data, auxData);
    }
    queueDestroy(q);
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
bnode *btreeFind(btree *this, void *valueAddr) {
    bnode **found =  bnode_find(&this->root, valueAddr, this->cmpFn);
    return found == NULL ? NULL : *found;
}

void btreePrint(btree *this, void (*printDataFn)(void *)) {
    printf(".\n");
    bnode_print(this->root, "", 0, printDataFn);
}

void _btreeBuild(btree *this, size_t num, ...) {
    va_list ap;
    void *valueAddr;

    va_start(ap, num);
    for (size_t i = 0;  i < num; ++i) {
        valueAddr = va_arg(ap, void*);
        btreeInsert(this, valueAddr);
    }
    va_end(ap);
}