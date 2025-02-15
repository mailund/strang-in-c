#pragma once

#include <stddef.h>
#include <stdlib.h>

static inline void cstr_vec_resize_(void **elements, size_t new_size,
                                    size_t *old_size, size_t elm_size) {
  if (new_size <= *old_size) {
    return;
  }

  // FIXME: Ignoring realloc failures here...
  *elements = realloc(*elements, elm_size * new_size);
  *old_size = new_size;
}
#define cstr_vec_resize(vec, new_size)                                         \
  cstr_vec_resize_((void **)&vec._elements, new_size, &vec._elm_capacity,      \
                   vec._elm_size)
#define cstr_vec_grow(vec)                                                     \
  {                                                                            \
    if (vec._elm_used == vec._elm_capacity) {                                  \
      cstr_vec_resize(vec, vec._elm_capacity * 2);                             \
    }                                                                          \
  }

#define cstr_vec(TYPE)                                                         \
  struct {                                                                     \
    TYPE *_elements;                                                           \
    size_t _elm_size;                                                          \
    size_t _elm_used;                                                          \
    size_t _elm_capacity;                                                      \
  }

#define cstr_new_vec(TYPE, SIZE)                                               \
  {._elements = malloc(sizeof(TYPE) * SIZE),                                   \
   ._elm_size = sizeof(TYPE),                                                  \
   ._elm_used = 0,                                                             \
   ._elm_capacity = SIZE}

#define cstr_vec_append(vec, value)                                            \
  do {                                                                         \
    cstr_vec_grow(vec);                                                        \
    vec._elements[vec._elm_used++] = value;                                    \
  } while (0)
#define cstr_vec_set(vec, index, value)                                        \
  do {                                                                         \
    cstr_vec_resize(vec, index + 1);                                           \
    vec._elements[index] = value;                                              \
  } while (0)
#define cstr_vec_get(vec, index) vec._elements[index]

#define cstr_vec_size(vec) vec._elm_used

#define cstr_vec_free(vec) free(vec._elements)