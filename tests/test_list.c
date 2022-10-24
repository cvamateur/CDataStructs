//
// Created by chris on 2022/10/23.
//
#include <stdio.h>
#include "list.h"
#include "common.h"


static void PrintInt(void *vp) {
    printf("%d", *(int *) vp);
}

static void PrintDouble(void *vp) {
    printf("%g", *(double *) vp);
}

static void PrintString(void *vp) {
    printf("\"%s\"", *(char **) vp);
}

static void freeString(void *vp) {
    char *str = *(char **) vp;
    free(str);
}


int main() {
    list l;

    int ix = 3, iy = 4, iz = 5;
    listInit(&l, sizeof(int), NULL);
    listPushBack(&l, REF_INT(1));
    listPushBack(&l, REF_INT(2));
    listPushBack(&l, REF_INT(3));
    listPushBack(&l, &ix);
    listPushBack(&l, &iy);
    listPushBack(&l, &iz);
    listPrint(&l, PrintInt);  BREAK_LINE();

    int res_x;
    listPopBack(&l, &res_x); printf("Pop an integer: %d\n", res_x);
    listPopBack(&l, &res_x); printf("Pop an integer: %d\n", res_x);
    listPopBack(&l, &res_x); printf("Pop an integer: %d\n", res_x);
    listDestroy(&l);


    double dx = 3.3, dy = 4.4, dz = 5.5;
    listInit(&l, sizeof(double), NULL);
    listPushFront(&l, REF_DOUBLE(2));
    listPushFront(&l, REF_DOUBLE(1));
    listPushBack(&l, &dx);
    listPushBack(&l, &dy);
    listPushBack(&l, &dz);
    listPrint(&l, PrintDouble); BREAK_LINE();
    listDestroy(&l);


    const char* strs[] = {"Hello", "World!", "Generic C Programming"};
    listInit(&l, sizeof(char *), NULL);
    listPushBack(&l, REF_STRING("123"));
    listPushBack(&l, REF_STRING("abc"));
    listPushBack(&l, REF_STRING("DEF"));
    listPushFront(&l, &strs[0]);
    listPushFront(&l, &strs[1]);
    listPushFront(&l, &strs[2]);
    listPrint(&l, PrintString);  BREAK_LINE();


    char* buffer;
    listPopFront(&l, &buffer); printf("FrontPop a string: \"%s\"\n", buffer);
    listPopBack(&l, &buffer); printf("BackPop a string: \"%s\"\n", buffer);


    listDestroy(&l);
}