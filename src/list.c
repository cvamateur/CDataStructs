//
// Created by chris on 2022/10/23.
//
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void DLNode_init(DLNode *this, void *valueAddr, const size_t elemSize) {
    this->prev = NULL;
    this->next = NULL;
    this->data = malloc(elemSize);
    memcpy(this->data, valueAddr, elemSize);
}

void listInit(list *this, size_t elemSize, void (*freeFn)(void *)) {
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;
    this->freeFn = freeFn;
    *(size_t *) &this->elemSize = elemSize;
}

void listDestroy(list *this) {
    DLNode *trash;
    while ((trash = this->head) != NULL) {
        this->head = trash->next;
        if (this->freeFn != NULL)
            this->freeFn(trash->data);
        free(trash);
    }
    this->size = 0;
    this->tail = NULL;
    *(size_t *) &this->elemSize = 0;
}

void listPushFront(list *this, void *valueAddr) {
    DLNode *newNode = malloc(sizeof(DLNode));
    DLNode_init(newNode, valueAddr, this->elemSize);

    if (++this->size == 1) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
    }
}

void listPopFront(list *this, void *valueAddr) {
    assert(this->size > 0);
    DLNode *popNode = this->head;
    memcpy(valueAddr, popNode->data, this->elemSize);

    if (--this->size == 0) {
        this->head = NULL;
        this->tail = NULL;
    } else {
        this->head = popNode->next;
        this->head->prev = NULL;
    }
    free(popNode);
}

void listPushBack(list *this, void *valueAddr) {
    DLNode *newNode = malloc(sizeof(DLNode));
    DLNode_init(newNode, valueAddr, this->elemSize);

    if (++this->size == 1) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        newNode->prev = this->tail;
        this->tail->next = newNode;
        this->tail = newNode;
    }
}

void listPopBack(list *this, void *valueAddr) {
    assert(this->tail != NULL);
    DLNode *popNode = this->tail;
    memcpy(valueAddr, popNode->data, this->elemSize);

    if (--this->size == 0) {
        this->head = NULL;
        this->tail = NULL;
    } else {
        this->tail = popNode->prev;
        this->tail->next = NULL;
    }
    free(popNode);
}

void listPrint(list *this, void printFn(void *)) {
    printf("[");
    for (DLNode *node = this->head; node != NULL; node = node->next) {
        printFn(node->data);
        if (node != this->tail)
            printf(", ");
    }
    printf("]");
}