//
// Created by sparkai on 22-10-24.
//
#include <stdio.h>
#include "queue.h"


int main() {

    queue q;
    queueInit(q, sizeof(int), NULL);

    int popInt;

    int ix = 3, iy = 4, iz = 5;
    queuePush(q, &ix); printf("Push value %d; size=%lu\n", ix, queueSize(q));
    queuePush(q, REF_INT(1));  printf("Push value %d; size=%lu\n", 1, queueSize(q));
    queuePop(q, &popInt); printf("Pop value %d; size=%lu\n", popInt, queueSize(q));

    queuePush(q, &iy); printf("Push value %d; size=%lu\n", iy, queueSize(q));
    queuePush(q, REF_INT(2));  printf("Push value %d; size=%lu\n", 2, queueSize(q));
    queuePop(q, &popInt); printf("Pop value %d; size=%lu\n", popInt, queueSize(q));

    queuePush(q, &iz); printf("Push value %d; size=%lu\n", iz, queueSize(q));
    queuePush(q, REF_INT(3));  printf("Push value %d; size=%lu\n", 3, queueSize(q));
    queuePop(q, &popInt); printf("Pop value %d; size=%lu\n", popInt, queueSize(q));


    queueDestroy(q);

    return 0;
}