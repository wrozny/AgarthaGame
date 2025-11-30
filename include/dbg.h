#ifndef _DBG_H
#define _DBG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Block {
    void* dataPtr;
    size_t blockSize;
} Block_t;

static int allocations = 0;
static int frees = 0;


/*
    Malloc wrapper
*/
static inline void* _dbg_malloc(size_t size) {
    allocations++;
    return malloc(size);
}

/*
    Free wrapper
*/
static inline void _dbg_free(void* block) {
    frees++;
    free(block);
}

/*
    Calloc wrapper
*/
static inline void* _dbg_calloc(size_t count, size_t size) {
    allocations++;
    return calloc(count, size);
}

static inline char* _dbg_strdup(const char* str) {
    allocations++;
    return strdup(str);
}

/*
    Prints out memory allocated and unallocated
*/
static inline void dbg_printMemoryRaport() {
    printf("Memory allocated: %d\nMemory freed: %d\n", allocations, frees);
}


//#define DEBUG
#ifdef DEBUG

#define malloc(SIZE) _dbg_malloc(SIZE)
#define free(PTR) _dbg_free(PTR)
#define calloc(COUNT, SIZE) _dbg_calloc(COUNT, SIZE)
#define strdup(STR) _dbg_strdup(STR)

#endif
#endif