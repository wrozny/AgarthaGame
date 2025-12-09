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