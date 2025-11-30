#include "ds/vector.h"

// Create vector
Vector* create_vector(int initial_capacity) {
    if (initial_capacity <= 0) {
        initial_capacity = VECTOR_INITIAL_CAPACITY;
    }

    Vector *v = malloc(sizeof(Vector));
    if (!v) return NULL;

    v->capacity = initial_capacity;
    v->size = 0;
    v->items = malloc(sizeof(void*) * v->capacity);

    if (!v->items) {
        free(v);
        return NULL;
    }

    return v;
}

// Internal function to resize vector
static void vec_resize(Vector *v, int new_capacity) {
    v->capacity = new_capacity;
    v->items = realloc(v->items, sizeof(void*) * v->capacity);
}

// Push item to end
void vec_push(Vector *v, void *item) {
    if (v->size == v->capacity) {
        vec_resize(v, v->capacity * 2);
    }
    v->items[v->size++] = item;
}

// Get item at index
void* vec_get(Vector *v, int index) {
    if (index < 0 || index >= v->size) return NULL;
    return v->items[index];
}

// Set item at index (returns old item)
void* vec_set(Vector *v, int index, void *item) {
    if (index < 0 || index >= v->size) return NULL;
    void *old = v->items[index];
    v->items[index] = item;
    return old;
}

// Insert item at index (shifts others)
void vec_insert(Vector *v, int index, void *item) {
    if (index < 0 || index > v->size) return;

    if (v->size == v->capacity) {
        vec_resize(v, v->capacity * 2);
    }

    memmove(&v->items[index + 1], &v->items[index], (v->size - index) * sizeof(void*));
    v->items[index] = item;
    v->size++;
}

// Remove item at index (returns removed item)
void* vec_remove(Vector *v, int index) {
    if (index < 0 || index >= v->size) return NULL;

    void *removed = v->items[index];
    memmove(&v->items[index], &v->items[index + 1], (v->size - index - 1) * sizeof(void*));
    v->size--;

    // Optional shrink if wasteful
    if (v->size > 0 && v->size <= v->capacity / 4) {
        vec_resize(v, v->capacity / 2);
    }

    return removed;
}

// Pop last item
void* vec_pop(Vector *v) {
    if (v->size == 0) return NULL;
    return v->items[--v->size];
}

// Clear vector contents but leave capacity
void vec_clear(Vector *v) {
    v->size = 0;
}

// Free vector (does NOT free pointed-to items)
void vec_free(Vector *v) {
    free(v->items);
    free(v);
}

// Free vector and free each item with a custom function
void vec_deep_free(Vector *v, void (*free_func)(void*)) {
    if (!free_func) {
        vec_free(v);
        return;
    }
    for (int i = 0; i < v->size; i++) {
        free_func(v->items[i]);
    }
    vec_free(v);
}