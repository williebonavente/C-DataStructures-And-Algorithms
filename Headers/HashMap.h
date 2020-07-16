#ifndef C_DATASTRUCTURES_HASHMAP_H
#define C_DATASTRUCTURES_HASHMAP_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HashMapItem {
    void *value;
    int sizeOfItem;
} HashMapItem;

typedef struct Entry {
    void *key;
    HashMapItem *item;
    int sizeOfKey;
} Entry;


typedef struct HashMap {
    Entry **arr;
    int length;
    int count;
    int bPrime;
} HashMap;


HashMap *hashMapInitialization(void (*freeKey)(void *key), void (*freeItem)(void *item),
                               int (*keyComp)(const void *key1, int s1, const void *key2, int s2));

void hashMapInsert(HashMap *map, void *key, int sizeOfKey, void *item, int sizeOfItem);

int hashMapContains(HashMap *map, void *key, int sizeOfKey);

void *hashMapGet(HashMap *map, void *key, int sizeOfKey);

void hashMapDelete(HashMap *map, void *key, int sizeOfKey);

void **hashMapToArray(HashMap *map);

Entry **hashMapToEntryArray(HashMap *map);

int hashMapGetLength(HashMap *map);

int hashMapIsEmpty(HashMap *map);

void clearHashMap(HashMap *map);

void destroyHashMap(HashMap *map);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_HASHMAP_H
