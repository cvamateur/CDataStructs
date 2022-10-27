//
// Created by sparkai on 22-10-24.
//
#include <stdio.h>
#include "btree.h"

static int CompareInts(const void *p1, const void *p2) {
    return *(int *) p1 - *(int *) p2;
}

static void printInt(void *vp1, void *delimiter) {
    printf("%d%s", *(int *) vp1, (char *) delimiter);
}

static void printData(void *data) {
    printf("%d", *(int *) data);
}


int main() {
    btree tree;

    btreeInit(&tree, sizeof(int), CompareInts, NULL);

    // AVL insert values
    for (int i = 0; i < 13; ++i) {
        printf("\n\nInsert %d\n", i);
        btreeInsert(&tree, &i);
        printf("tree = "); btreeMap(&tree, IN_ORDER, printInt, " ");
        printf("\n");
        btreePrint(&tree, printData);
    }

    // AVL delete values
    int deleteValues[3] = {7, 6, 11};
    for (int i = 0; i < 3; ++i) {
        printf("\n\nDelete %d\n", deleteValues[i]);
        btreeDelete(&tree, &deleteValues[i]);
        printf("tree = "); btreeMap(&tree, IN_ORDER, printInt, " ");
        printf("\n");
        btreePrint(&tree, printData);
    }

    // find value
    int aInt = 4;
    printf("\n\nIf %d in the tree?\n", aInt);
    bnode *node = btreeFind(&tree, &aInt);
    if (node != NULL)
        printf("Yes, value %d has found\n", aInt);
    else
        printf("Not, value %d has not found\n", aInt);

    btreeDestroy(&tree);
    return 0;
}