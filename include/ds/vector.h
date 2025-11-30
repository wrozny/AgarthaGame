#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Vector {
    void **items;
    int size;
    int capacity;
} Vector;

#define VECTOR_INITIAL_CAPACITY 4


// Create vector
Vector* create_vector(int initial_capacity);

// Internal function to resize vector
static void vec_resize(Vector *v, int new_capacity);

// Push item to end
void vec_push(Vector *v, void *item);

// Get item at index
void* vec_get(Vector *v, int index);

// Set item at index (returns old item)
void* vec_set(Vector *v, int index, void *item);

// Insert item at index (shifts others)
void vec_insert(Vector *v, int index, void *item);

// Remove item at index (returns removed item)
void* vec_remove(Vector *v, int index);

// Pop last item
void* vec_pop(Vector *v);

// Clear vector contents but leave capacity
void vec_clear(Vector *v);

// Free vector (does NOT free pointed-to items)
void vec_free(Vector *v);

// Free vector and free each item with a custom function
void vec_deep_free(Vector *v, void (*free_func)(void*));

#endif