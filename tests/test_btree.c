//
// Created by sparkai on 22-10-24.
//
#include <stdio.h>
#include "btree.h"

int IntsLessThan(const void* p1, const void* p2) {
    return *(int*) p1 <= *(int*)p2;
}

void MapPrintInt(void *vp1, void *delimiter) {
    printf("%d%s", *(int*)vp1, (char*) delimiter);
}

int main() {
    btree *tree = malloc(sizeof(btree));

    btreeInit(tree, sizeof(int), IntsLessThan, NULL);
    btreeInsert(tree, REF_INT(5));
    btreeInsert(tree, REF_INT(3));
    btreeInsert(tree, REF_INT(7));
    btreeInsert(tree, REF_INT(2));
    btreeInsert(tree, REF_INT(8));
    btreeInsert(tree, REF_INT(4));
    btreeMap(tree, PRE_ORDER, MapPrintInt, " ");
    btreeDestroy(tree);

    free(tree);
    return 0;
}