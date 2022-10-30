//
// Created by chris on 2022/10/30.
//
#include "hashmap.h"

static int IntEqual(const void *vp1, const void *vp2) {
    return *(int*) vp1 == *(int*) vp2;
}

static int StringEqual(const void *vp1, const void *vp2) {
    char *key = *(char**) vp1;
    char *check = *(char**) vp2;
    return (int) strcmp(key, check) == 0;
}

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
    hashmapDestroy(&map);;

    return 0;
}