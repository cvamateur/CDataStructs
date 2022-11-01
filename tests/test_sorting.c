//
// Created by chris on 2022/10/29.
//
#include <stdio.h>
#include "sort.h"

static int IntLess(const void *vp1, const void *vp2) {
    return *(int*) vp1 <= *(int*) vp2;
}

static void PrintArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[10] = {4, 2, 3, 1, 7, 6, 9, 0, 8, 5};
    bubbleSort(arr, 10, sizeof(int), IntLess);
    PrintArray(arr, 10);

    int arr1[10] = {4, 2, 3, 1, 7, 6, 9, 0, 8, 5};
    insertionSort(arr1, 10, sizeof(int), IntLess);
    PrintArray(arr1, 10);

    int arr2[10] = {4, 2, 3, 1, 7, 6, 9, 0, 8, 5};
    selectionSort(arr2, 10, sizeof(int), IntLess);
    PrintArray(arr2, 10);

    int arr3[10] = {4, 2, 3, 1, 7, 6, 9, 0, 8, 5};
    quickSort(arr2, 10, sizeof(int), IntLess);
    PrintArray(arr2, 10);
}