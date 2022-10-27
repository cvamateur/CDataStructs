//
// Created by chris on 2022/10/23.
//
#include <stdio.h>
#include "list.h"

static void PrintInt(void *vp, void *delimiter) {
    printf("%d%s", *(int*)vp, (char*) delimiter);
}

static int CompareInts(const void *vp1, const void *vp2) {
    return *(int*) vp1 - *(int*) vp2;
}

int main() {
    list l;

    listInit(&l, sizeof(int), NULL);
    listPushBack(&l, REF_INT(3));
    listPushBack(&l, REF_INT(1));
    listPushBack(&l, REF_INT(8));
    listPushBack(&l, REF_INT(5));
    listPushBack(&l, REF_INT(7));
    listMap(&l, PrintInt, " ");  STD_ENDL();

    printf("After sort: ");
    listSort(&l, CompareInts);
    listMap(&l, PrintInt, " ");  STD_ENDL();

    printf("Reverse: ");
    listReverse(&l);
    listMap(&l, PrintInt, " ");  STD_ENDL();
    listReverse(&l);

    printf("Sorted Merge\n");
    list l2;
    listInit(&l2, sizeof(int), NULL);
    listPushBack(&l2, REF_INT(5));
    listPushBack(&l2, REF_INT(2));
    listPushBack(&l2, REF_INT(9));
    listSort(&l2, CompareInts);

    listSortedMerge(&l, &l2, CompareInts);
    printf("After sorted merge l=: ");
    listMap(&l, PrintInt, " ");  STD_ENDL();
    printf("After sorted merge l2=: ");
    listMap(&l2, PrintInt, " ");  STD_ENDL();

    listDestroy(&l);
    listDestroy(&l2);
}