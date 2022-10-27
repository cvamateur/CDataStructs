//
// Created by sparkai on 22-10-25.
//
#include <stdio.h>
#include "deque.h"

static int IntsLessThan(const void* p1, const void* p2) {
    return *(int*) p1 <= *(int*)p2;
}

static void printInt(void *vp1, void *delimiter) {
    printf("%d%s", *(int*)vp1, (char*) delimiter);
}

int main() {

    deque q;
    int ix = 3, iz = 5;
    int popInt;

    dequeInit(q, sizeof(int), NULL);

    dequePushBack(q, &ix); printf("Push value %d; size=%lu\n", ix, dequeSize(q));
    dequePushFront(q, REF_INT(1));  printf("Push value %d; size=%lu\n", 1, dequeSize(q));
    dequePopBack(q, &popInt); printf("Pop value %d; size=%lu\n", popInt, dequeSize(q));

    dequePushFront(q, &iz); printf("Push value %d; size=%lu\n", iz, dequeSize(q));
    dequePushBack(q, REF_INT(2));  printf("Push value %d; size=%lu\n", 2, dequeSize(q));
    dequePopFront(q, &popInt); printf("Pop value %d; size=%lu\n", popInt, dequeSize(q));

    dequeDestroy(q);

    return 0;
}