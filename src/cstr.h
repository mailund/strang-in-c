#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Vector implementation
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

static inline bool cstr_vec_eq_(const void *a, const void *b, size_t no_elm,
                                size_t elm_size) {
  return memcmp(a, b, no_elm * elm_size) == 0;
}
#define cstr_vec_eq(a, b)                                                      \
  (a._elm_used == b._elm_used) && (a._elm_size == b._elm_size) &&              \
      cstr_vec_eq_(a._elements, b._elements, a._elm_used, a._elm_size)

#define cstr_vec_free(vec) free(vec._elements)

// String implementation
const char *naive_search(const char *x, const char *p);