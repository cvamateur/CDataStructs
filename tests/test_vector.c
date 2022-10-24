//
// Created by chris on 2022/10/23.
//
#include <stdio.h>
#include "vector.h"
#include "literals.h"

static void PrintInt(const void *vp) {
    printf("%d", *(int*)vp);
}

static void PrintDouble(const void *vp) {
    printf("%g", *(double*)vp);
}

static void PrintString(const void *vp) {
    printf("\"%s\"", *(char**) vp);
}

static void FreeString(void *vp) {
    char* str = *(char**) vp;
    free(str);
}

static int CompareString(const void *vp1, const void* vp2) {
    char* str1 = *(char**) vp1;
    char* str2 = *(char**) vp2;
    return strcmp(str1, str2);
}

static void MapFnIncInt(void *vp1, void* auxData) {
    *(int*) vp1 = *(int*) vp1 + *(int*) auxData;
}

static void MapFnIncDouble(void *vp1, void* auxData) {
    *(double*) vp1 = *(double*) vp1 + *(double*) auxData;
}


int main() {
    vector v;

    int ix = 3, iy = 4, iz = 5;
    vectorInit(&v, sizeof(int), NULL, 0);
    vectorPushBack(&v, PTR_INT(1));
    vectorPushBack(&v, PTR_INT(2));
    vectorPushBack(&v, &ix);
    vectorPushBack(&v, &iy);
    vectorPushBack(&v, &iz);
    vectorPrint(&v, PrintInt);  BREAK_LINE();

    vectorMap(&v, MapFnIncInt, PTR_INT(3));
    vectorPrint(&v, PrintInt);  BREAK_LINE();
    vectorDestroy(&v);


    double dx = 3.3, dy = 4.4, dz = 5.5;
    vectorInit(&v, sizeof(double), NULL, 0);
    vectorInsert(&v, PTR_DOUBLE(1.1), 0);
    vectorInsert(&v, PTR_DOUBLE(2.2), 1);
    vectorPushBack(&v, &dx);
    vectorPushBack(&v, &dy);
    vectorPushBack(&v, &dz);
    vectorPrint(&v, PrintDouble); BREAK_LINE();

    vectorMap(&v, MapFnIncDouble, PTR_DOUBLE(3.0));
    vectorPrint(&v, PrintDouble);  BREAK_LINE();
    vectorDestroy(&v);


    const char* strs[] = {"Hello", "World!", "Generic C Programming"};
    vectorInit(&v, sizeof(char*), NULL, 0);
    vectorPushBack(&v, &strs[0]);
    vectorPushBack(&v, &strs[1]);
    vectorPushBack(&v, &strs[2]);
    vectorInsert(&v, PTR_STRING("123"), 0);
    vectorInsert(&v, PTR_STRING("abc"), 1);
    vectorInsert(&v, PTR_STRING("DEF"), v.size);
    vectorPrint(&v, PrintString);  BREAK_LINE();

    vectorReplace(&v, PTR_STRING("C++"), 2);
    vectorReplace(&v, PTR_STRING("Python"), 0);
    vectorPrint(&v, PrintString); BREAK_LINE();

    char* key = "Python";
    long foundIdx = vectorSearch(&v, &key, CompareString, 0, 0);
    if (foundIdx != -1)
        printf("Found string `Python` at index %ld\n", foundIdx);
    else
        printf("No string `Python` in vector\n");

    vectorSort(&v, CompareString);
    vectorPrint(&v, PrintString); BREAK_LINE();

    foundIdx = vectorSearch(&v, &key, CompareString, 0, 1);
    if (foundIdx != -1)
        printf("Found string `Python` at index %ld\n", foundIdx);
    else
        printf("No string `Python` in vector\n");

    vectorDelete(&v, 0);
    vectorPrint(&v, PrintString); BREAK_LINE();


    char* buffer;
    vectorPopBack(&v, &buffer); PrintString(&buffer); BREAK_LINE();
    vectorPopBack(&v, &buffer); PrintString(&buffer); BREAK_LINE();

    vectorDestroy(&v);

    return 0;
}