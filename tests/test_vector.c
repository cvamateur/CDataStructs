//
// Created by chris on 2022/10/23.
//
#include <stdio.h>
#include "vector.h"

static void PrintString(const void *vp) {
    printf("\"%s\"", *(char**) vp);
}

static int CompareString(const void *vp1, const void* vp2) {
    char* str1 = *(char**) vp1;
    char* str2 = *(char**) vp2;
    return strcmp(str1, str2);
}


int main() {
    vector v;

    const char* strs[] = {"Hello", "World!", "Generic C Programming"};
    vectorInit(&v, sizeof(char*), NULL, 0);
    vectorPushBack(&v, &strs[0]);
    vectorPushBack(&v, &strs[1]);
    vectorPushBack(&v, &strs[2]);
    vectorInsert(&v, REF_STRING("123"), 0);
    vectorInsert(&v, REF_STRING("DEF"), v.size);
    vectorPrint(&v, PrintString);  STD_ENDL();

    vectorReplace(&v, REF_STRING("C++"), 2);
    vectorReplace(&v, REF_STRING("Python"), 0);
    vectorPrint(&v, PrintString); STD_ENDL();

    char* key = "Python";
    long foundIdx = vectorSearch(&v, &key, CompareString, 0, 0);
    if (foundIdx != -1)
        printf("Found string `Python` at index %ld\n", foundIdx);
    else
        printf("No string `Python` in vector\n");

    vectorSort(&v, CompareString);
    vectorPrint(&v, PrintString); STD_ENDL();

    foundIdx = vectorSearch(&v, &key, CompareString, 0, 1);
    if (foundIdx != -1)
        printf("Found string `Python` at index %ld\n", foundIdx);
    else
        printf("No string `Python` in vector\n");

    vectorDelete(&v, 0);
    vectorPrint(&v, PrintString); STD_ENDL();


    char* buffer;
    vectorPopBack(&v, &buffer); PrintString(&buffer); STD_ENDL();
    vectorPopBack(&v, &buffer); PrintString(&buffer); STD_ENDL();

    vectorDestroy(&v);

    return 0;
}