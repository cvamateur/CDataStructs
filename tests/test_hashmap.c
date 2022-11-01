//
// Created by chris on 2022/10/30.
//
#include "hashmap.h"


int main() {

    hashmap map;
    hashmapInit(&map, sizeof(char*), sizeof(int), hashString, StringEqual, NULL, NULL);

    char* keys[10] = {"10", "20", "30", "40", "50", "60", "70", "80", "90", "100"};
    int values[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

    for (int i = 0; i < 10; ++i) {
        printf("Set value %s=%d\n", keys[i], values[i]);
        hashmapSet(&map, &keys[i], &values[i]);
    }

    int intValue;
    for (int i = 0; i < 10; ++i) {
        hashmapGet(&map, &keys[i], &intValue, REF_INT(0));
        printf("Get value %s=%d\n", keys[i], intValue);
    }

    int popValue;
    char *popKeys[] = {"10", "20", "40", "10", "20", "40", };
    for (int i = 0; i < 6; ++i) {
        hashmapPop(&map, &popKeys[i], &popValue, REF_INT(0));
        printf("Pop value %s=%d\n", popKeys[i], popValue);
    }

    hashmapDestroy(&map);;

    return 0;
}