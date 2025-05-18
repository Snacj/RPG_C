/*
 * util.c
 *
 * This file contains utility functions for the game.
 * It includes functions for vector operations.
 */
#include "util.h"
#include <string.h>

/**
* @brief initialize a vector
* @param v the vector to initialize, size_t elem_size
* @return void
*/
void vector_init(Vector *v, size_t elem_size) {
    v->elem_size = elem_size;
    v->size = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * elem_size);
}

/**
* @brief push an element to the vector
* @param v the vector to push to, void* elem
* @return void
*/
void vector_push_back(Vector *v, void *elem) {
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * v->elem_size);
    }
    void *target = (char *)v->data + (v->size * v->elem_size);
    memcpy(target, elem, v->elem_size);
    v->size++;
}

/**
* @brief get an element from the vector
* @param v the vector to get from, size_t index
* @return void
*/
void *vector_get(Vector *v, size_t index) {
    return (char *)v->data + (index * v->elem_size);
}

/**
* @brief free the vector
* @param v the vector to free
* @return void
*/
void vector_free(Vector *v) {
    free(v->data);
}
