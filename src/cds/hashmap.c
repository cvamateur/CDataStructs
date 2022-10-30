//
// Created by chris on 2022/10/29.
//

#include <stdlib.h>
#include <assert.h>
#include "hashmap.h"

#define HASH(map, keyAddr)  ((map)->_a * (map)->hash(keyAddr) % PRIME_NUM % (map)->capacity)


static inline void hashNodeInit(hashNode *this, void *keyAddr, size_t keySize, void *valueAddr, size_t valueSize) {
    this->p_item = malloc(sizeof(pair));
    assert(this->p_item != NULL);
    this->p_item->p_key = malloc(sizeof(keySize));
    assert(this->p_item->p_key != NULL);
    this->p_item->p_value = malloc(sizeof(valueSize));
    assert(this->p_item->p_value != NULL);
    memcpy(this->p_item->p_key, keyAddr, keySize);
    memcpy(this->p_item->p_value, valueAddr, valueSize);
    this->next = NULL;
}

void hashmapInit(hashmap *this, size_t keySize, size_t valueSize,
                 HashFunction hashFn, KeyEqualFunction keyEqualFn,
                 FreeFunction freeKey, FreeFunction freeValue) {
    this->capacity = INITIAL_SIZE;
    this->size = 0;
    this->keySize = keySize;
    this->valueSize = valueSize;
    this->hash = hashFn;
    this->keyEqual = keyEqualFn;
    this->data = NULL;
    this->_a = randint(1, PRIME_NUM - 1);
    this->freeKey = freeKey;
    this->freeValue = freeValue;
}

static inline void hashMapAutoGrow(hashmap *this) {
    if (2 * this->capacity >= MAX_SIZE ||
        this->size < (size_t) (FILL_RATIO * (double) this->capacity))
        return;
    this->capacity *= 2;
    hashNode **newData = malloc(this->capacity * sizeof(hashNode*));
    assert(newData != NULL);
    memset(newData, 0, this->capacity * sizeof(hashNode*));
    this->_a = randint(1, PRIME_NUM - 1);

    hashNode *item = NULL;
    for (int i = 0; i < this->capacity / 2; ++i) {
        while (this->data[i] != NULL) {
            size_t hashCode = HASH(this, this->data[i]->p_item->p_key);
            item = this->data[i];
            this->data[i] = item->next;
            item->next = newData[hashCode];
            newData[hashCode] = item;
        }
    }
    free(this->data);
    this->data = newData;
}

void hashmapDestroy(hashmap *this) {
    hashNode *node, *trash;
    for (size_t i = 0; i < this->size; ++i) {
        node = this->data[i];
        while (node != NULL) {
            trash = node;
            node = node->next;
            if (this->freeKey != NULL)
                this->freeKey(trash->p_item->p_key);
            if (this->freeValue != NULL)
                this->freeValue(trash->p_item->p_value);
            free(trash->p_item->p_key);
            free(trash->p_item->p_value);
            free(trash->p_item);
            free(trash);
        }
    }
    free(this->data);
}

void hashmapSet(hashmap *this, void *keyAddr, void *valueAddr) {
    if (this->data == NULL) {
        this->data = malloc(INITIAL_SIZE * sizeof(hashNode *));
        memset(this->data, 0, INITIAL_SIZE * sizeof(hashNode *));
    }

    size_t hashCode = HASH(this, keyAddr);
    if (this->data[hashCode] == NULL) {
        hashNode *newNode = malloc(sizeof(hashNode));
        assert(newNode != NULL);
        hashNodeInit(newNode, keyAddr, this->keySize, valueAddr, this->valueSize);
        newNode->next = this->data[hashCode];
        this->data[hashCode] = newNode;
    } else {
        hashNode *item = this->data[hashCode];
        while (item != NULL) {
            if (this->keyEqual(keyAddr, item->p_item->p_key)) {
                if (this->freeValue != NULL)
                    this->freeValue(item->p_item->p_value);
                memcpy(item->p_item->p_value, valueAddr, this->valueSize);
                break;
            }
            item = item->next;
        }
        if (item == NULL) {
            hashNode *newNode = malloc(sizeof(hashNode));
            assert(newNode != NULL);
            hashNodeInit(newNode,  keyAddr, this->keySize, valueAddr, this->valueSize);
            newNode->next = this->data[hashCode];
            this->data[hashCode] = newNode;
        }
    }
    ++this->size;
    hashMapAutoGrow(this);
}

void hashmapGet(hashmap *this, void *keyAddr, void *outputAddr, void *defaultValue) {
    if (this->data != NULL) {
        size_t hashCode = HASH(this, keyAddr);

        hashNode *found = this->data[hashCode];
        while (found != NULL) {
            pair *item = found->p_item;
            if (this->keyEqual(keyAddr, item->p_key)) {
                memcpy(outputAddr, item->p_value, this->valueSize);
                return;
            }
            found = found->next;
        }
    }
    memcpy(outputAddr, defaultValue, this->valueSize);
}

void hashmapPop(hashmap *this, void *keyAddr, void *outputAddr, void *defaultValue) {
    if (this->data != NULL) {
        size_t hashCode = HASH(this, keyAddr);

        hashNode **nodeRef = &this->data[hashCode];
        while (*nodeRef != NULL) {
            pair *item = (*nodeRef)->p_item;
            if (this->keyEqual(keyAddr, item->p_key)) {
                memcpy(outputAddr, item->p_value, this->valueSize);
                *nodeRef = (*nodeRef)->next;
                if (this->freeKey != NULL)
                    this->freeKey(item->p_key);
                if (this->freeValue != NULL)
                    this->freeValue(item->p_value);
                free(item->p_key);
                free(item->p_value);
                free(item);
                return;
            }
            nodeRef = &(*nodeRef)->next;
        }
    }
    memcpy(outputAddr, defaultValue, this->valueSize);
}


size_t hashInt(const void* keyAddr) {
    return (size_t) *(int*)keyAddr;
}

size_t hashDouble(const void* keyAddr) {
    return (size_t) *(double*)keyAddr;
}

size_t  hashString(const void* keyAddr) {
    size_t r = 0;
    char* key = *(char**) keyAddr;
    for (int i = 0; i < strlen(key); ++i) {
        r += (size_t) key[i];
    }
    return r;
}

int IntEqual(const void *vp1, const void *vp2) {
    return *(int *) vp1 == *(int *) vp2;
}

int StringEqual(const void *vp1, const void *vp2) {
    char *key = *(char **) vp1;
    char *check = *(char **) vp2;
    return (int) strcmp(key, check) == 0;
}