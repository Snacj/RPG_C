#include "util.h"
#include <string.h>

void vector_init(Vector *v, size_t elem_size) {
    v->elem_size = elem_size;
    v->size = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * elem_size);
}

void vector_push_back(Vector *v, void *elem) {
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * v->elem_size);
    }
    void *target = (char *)v->data + (v->size * v->elem_size);
    memcpy(target, elem, v->elem_size);
    v->size++;
}

void *vector_get(Vector *v, size_t index) {
    return (char *)v->data + (index * v->elem_size);
}

void vector_free(Vector *v) {
    free(v->data);
}
