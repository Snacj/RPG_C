#pragma once

#include <stdlib.h>

typedef struct {
    void *data;
    size_t elem_size;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v, size_t elem_size);
void vector_push_back(Vector *v, void *elem);
void *vector_get(Vector *v, size_t index);
void vector_free(Vector *v);
