#pragma once

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint64_t hash64;

/*
    Generates 64 bit fnv-1a hash 
*/
static inline hash64 Hash_fnv_1a64(const char* bytes) {
    hash64 hash = 0xcbf29ce484222325ULL;

    while(*bytes) {
        hash = hash ^ (unsigned char)*bytes++;
        hash = hash * 0x100000001b3ULL;
    }

    return hash;
}

/*
    Generates 16 bytes of random characters between ASCII 33-125
*/
static inline char* Hash_NewRandomId() {
    char* data = (char*)malloc(sizeof(char) * 17);

    for(int i = 0; i < 16; i++) {
        data[i] = (char) (33 + (rand() % 93));
    }

    data[16] = '\0';

    return data;
}


/*
    Returns fnv-1a hash for 2 integers of 64 bits
*/
static inline hash64 Hash_2intfnv_1a(int16_t a, int16_t b) {
    char *buffer = malloc(sizeof(char) * 14);
    sprintf_s(buffer, 14, "%d_%d", a, b);
    hash64 hash = Hash_fnv_1a64(buffer);
    free(buffer);
    return hash;
}