//
// Created by chris on 2022/10/23.
//
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void DLNode_init(DLNode *this, void *valueAddr, const size_t elemSize) {
    this->prev = NULL;
    this->next = NULL;
    this->data = malloc(elemSize);
    memcpy(this->data, valueAddr, elemSize);
}

static void DLNode_FrontBackSplit(DLNode *head, DLNode *tail,
                                  DLNode **frontHead, DLNode **frontTail,
                                  DLNode **backHead, DLNode **backTail) {
    if (head == NULL || head->next == NULL) {
        *frontHead = head;
        *frontTail = tail;
        *backHead = NULL;
        *backTail = NULL;
    } else {
        DLNode *slow, *fast;
        slow = head;
        fast = head->next;
        while (fast != NULL) {
            *backTail = fast;
            fast = fast->next;
            if (fast != NULL) {
                *backTail = fast;
                slow = slow->next;
                fast = fast->next;
            }
        }
        *frontHead = head;
        *frontTail = slow;
        *backHead = slow->next;
        slow->next->prev = NULL;
        slow->next = NULL;
    }
}

static void DLNode_sortedMerge(DLNode *thisHead, DLNode *thisTail,
                               DLNode *otherHead, DLNode *otherTail,
                               DLNode **resHeadRef, DLNode **resTailRef,
                               CompareFunction cmpFn) {

    DLNode *result = NULL;
    DLNode **resTail = &result;
    DLNode *prevNode = NULL;

    for (;;) {
        if (thisHead == NULL) {
            otherHead->prev = prevNode;
            *resTail = otherHead;
            *resTailRef = otherTail;
            break;
        } else if (otherHead == NULL) {
            thisHead->prev = prevNode;
            *resTail = thisHead;
            *resTailRef = thisTail;
            break;
        } else {
            if (cmpFn(thisHead->data, otherHead->data) <= 0) {
                thisHead->prev = prevNode;
                *resTail = thisHead;
                prevNode = thisHead;
                thisHead = thisHead->next;
                resTail = &(*resTail)->next;
            } else {
                otherHead->prev = prevNode;
                *resTail = otherHead;
                prevNode = otherHead;
                otherHead = otherHead->next;
                resTail = &(*resTail)->next;
            }
        }
    }
    *resHeadRef = result;
}

static void DLNode_mergeSort(DLNode **headRef, DLNode **tailRef, CompareFunction cmpFn) {
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    DLNode *lHead = NULL, *lTail = NULL;
    DLNode *rHead = NULL, *rTail = NULL;
    DLNode_FrontBackSplit(*headRef, *tailRef,
                          &lHead, &lTail,
                          &rHead, &rTail);
    DLNode_mergeSort(&lHead, &lTail, cmpFn);
    DLNode_mergeSort(&rHead, &rTail, cmpFn);

    DLNode_sortedMerge(lHead, lTail,
                       rHead, rTail,
                       headRef, tailRef, cmpFn);
}

void DLNode_reverse(DLNode **headRef, DLNode **tailRef) {
    *tailRef = *headRef;

    DLNode *head = *headRef;
    DLNode *result = NULL;
    DLNode *tmpNode;
    while (head != NULL) {
        tmpNode = head;
        head = head->next;
        tmpNode->next = result;
        if (result != NULL)
            result->prev = tmpNode;
        result = tmpNode;
    }
    if (result != NULL)
        result->prev = NULL;
    *headRef = result;
}

void listInit(list *this, size_t elemSize, FreeFunction freeFn) {
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
        if (trash->data != NULL && this->freeFn != NULL)
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

void listMap(list *this, MapFunction mapFn, void *auxData) {
    DLNode *node = this->head;
    while (node != NULL) {
        mapFn(node->data, auxData);
        node = node->next;
    }
}

void listMapReverse(list *this, MapFunction mapFn, void *auxData) {
    DLNode *node = this->tail;
    while (node != NULL) {
        mapFn(node->data, auxData);
        node = node->prev;
    }
}

void listReverse(list *this) {
    DLNode_reverse(&this->head, &this->tail);
}

void listSort(list *this, CompareFunction cmpFn) {
    DLNode_mergeSort(&this->head, &this->tail, cmpFn);
}

void listSortedMerge(list *this, list *other, CompareFunction cmpFn) {
    DLNode_sortedMerge(this->head, this->tail,
                       other->head, other->tail,
                       &this->head, &this->tail, cmpFn);
    this->size += other->size;
    other->size = 0;
    other->head = NULL;
    other->tail = NULL;
}