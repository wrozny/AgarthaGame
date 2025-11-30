#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "hashing.h"

#ifdef _WIN32
    #define strdup _strdup
#endif

struct m_node1d {
    void *data;
    const char* key;
    struct m_node1d *next;
};

typedef struct m_node1d m_node1d_t;

typedef struct Map {
    m_node1d_t *buckets;
    size_t capacity;
} Map;


/*
    Allocates memory for new map instance
*/
Map* MapCreate(size_t initialCapacity);

/*
    Frees the map from memory
*/
void MapFree(Map* map);

/*
    Expands the size of a map resulting in less collision.
    doubled automatically when 12:16 elements to capacity ratio reached
*/
void MapExpand(Map* map, size_t newCapacity);

/*
    Sets the value of a key to the value address in the map
*/
void MapSet(Map* map, const char* key, void* valueAddr);

/*
    Removes the value with given key from the map
*/
void MapRemove(Map* map, const char* key);

/*
    Returns pointer to the value with given key or null if key isn't set
*/
void* MapGet(Map* map, const char* key);

/*
    Prints out every populated bucket inside the map
*/
void MapPrint(Map* map);