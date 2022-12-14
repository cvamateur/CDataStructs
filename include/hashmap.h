//
// Created by chris on 2022/10/29.
//

#ifndef CDATASTRUCTS_HASHMAP_H
#define CDATASTRUCTS_HASHMAP_H

#include <stddef.h>
#include "common.h"

#define INITIAL_SIZE    (8)
#define FILL_RATIO      (0.75)
#define MAX_SIZE        (1 << 30)
#define PRIME_NUM       ((size_t) (1 << 31) - 1)


typedef size_t (*HashFunction)(const void *);
typedef int (*KeyEqualFunction)(const void *, const void *);
typedef struct __Pair {
    void *p_key;
    void *p_value;
} pair;

typedef struct __HashNode {
    pair *p_item;
    struct __HashNode *next;
} hashmapNode;

typedef struct __HashMap {
    hashmapNode **data;
    size_t capacity;
    size_t size;
    size_t keySize;
    size_t valueSize;
    size_t _a;

    HashFunction hash;
    CompareFunction keyEqual;
    FreeFunction freeKey;
    FreeFunction freeValue;
} hashmap;

void hashmapInit(hashmap *this, size_t keySize, size_t valueSize,
                 HashFunction hashFn, KeyEqualFunction keyEqualFn,
                 FreeFunction freeKey, FreeFunction freeValue);
void hashmapDestroy(hashmap *this);
void hashmapSet(hashmap *this, void *keyAddr, void *valueAddr);
void hashmapGet(hashmap *this, void *keyAddr, void *outputAddr, void *defaultValue);
void hashmapPop(hashmap *this, void *keyAddr, void *outputAddr, void *defaultValue);
int  hashmapContain(hashmap *this, void *keyAddr);

size_t hashChar(const void *keyAddr);
size_t hashShort(const void *keyAddr);
size_t hashInt(const void *keyAddr);
size_t hashLong(const void *keyAddr);
size_t hashLongLong(const void *keyAddr);
size_t hashFloat(const void*keyAddr);
size_t hashDouble(const void* keyAddr);
size_t hashString(const void *keyAddr);
int CharEqual(const void *vp1, const void *vp2);
int ShortEqual(const void *vp1, const void *vp2);
int IntEqual(const void *vp1, const void *vp2);
int LongEqual(const void *vp1, const void *vp2);
int LongLongEqual(const void *vp1, const void *vp2);
int FloatEqual(const void *vp1, const void *vp2);
int DoubleEqual(const void *vp1, const void *vp2);
int StringEqual(const void *vp1, const void *vp2);

#endif //CDATASTRUCTS_HASHMAP_H
