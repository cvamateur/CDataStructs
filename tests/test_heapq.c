//
// Created by chris on 2022/10/28.
//
#include <stdio.h>
#include "heapq.h"

static int IntLess(void *vp1, void *vp2) {
    return *(int *) vp1 < *(int *) vp2;
}

static int IntGreater(void *vp1, void *vp2) {
    return *(int*) vp1 > *(int *) vp2;
}

static void PrintInt(void *data, void* delimiter) {
    printf("%d%s", *(int*) data, (char*) delimiter);
}

int main() {
    heapq hq;
    int topInt;

    int arr[10] = {6, 5, 2, 4, 3, 8, 9, 10, 7, 1};
    heapqInit(&hq, 0, sizeof(int), IntGreater, NULL);

    printf("Heap Push:\n");
    for (int i = 0; i < 10; ++i) {
        heapqPush(&hq, &arr[i]);
        printf("size=%zu; pushValue=%d; heap=", heapqSize(&hq), arr[i]);
        heapqMap(&hq, PrintInt, " "); STD_ENDL();
    }
    printf("Heap Pop:\n");
    for (int i = 0; i < 5; ++i) {
        heapqPop(&hq, &topInt);
        printf("size=%zu; popValue=%d; heap=", heapqSize(&hq), topInt);
        heapqMap(&hq, PrintInt, " "); STD_ENDL();
    }

    printf("Heap PushPop:\n");
    for (int i = 5; i < 7; ++i) {
        heapqPushPop(&hq, &arr[i], &topInt);
        printf("size=%zu; pushValue=%d, popValue=%d, heap=", heapqSize(&hq), arr[i], topInt);
        heapqMap(&hq, PrintInt, " "); STD_ENDL();
    }
    printf("Heap Pop Push:\n");
    for (int i = 7; i < 10; ++i) {
        heapqPopPush(&hq, &arr[i], &topInt);
        printf("size=%zu; pushValue=%d, popValue=%d, heap=", heapqSize(&hq), arr[i], topInt);
        heapqMap(&hq, PrintInt, " "); STD_ENDL();
    }

    heapqDestroy(&hq);

    printf("Inplace turn arr into heap:\n");
    heapify(arr, 10, sizeof(int), IntLess);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    } STD_ENDL();

    printf("Inplace Heap-Sort:\n");
    int arr2[10] = {6, 5, 2, 4, 3, 8, 9, 10, 7, 1};
    heapSort(arr2, 10, sizeof(int), IntLess);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr2[i]);
    } STD_ENDL();

    return 0;
}

