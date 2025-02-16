#include "cstr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *naive(const char *x, const char *p) {
  if (!x[0] || !p[0])
    return NULL;

  for (; *x; x++) {
    for (const char *i = x, *j = p; /* check in body*/; i++, j++)
      if (*j == '\0') // We reached the end of p
        return x;
      else if (*i != *j) // We hit a mismatch
        break;
  }
  return NULL;
}

void border_array(const char *p, int *b) {
  // Classical border array
  b[0] = 0;
  int j = 0;
  for (int i = 1; p[i]; i++) {
    while (j > 0 && p[i] != p[j])
      j = b[j - 1];
    if (p[i] == p[j])
      j++;
    b[i] = j;
  }
  // Making it strict
  if (!p[0] || !p[1])
    return;
  for (int i = 1; p[i + 1]; i++)
    if (b[i] && p[b[i]] == p[i + 1])
      b[i] = b[b[i] - 1];
}

struct kmp_iter kmp_iter_init(const char *x, const char *p) {
  int *b = malloc(strlen(p) * sizeof *b);
  border_array(p, b);
  struct kmp_iter iter = {.x = x, .p = p, .b = b, .i = 0, .j = 0};
  return iter;
}
const char *kmp_iter_next(struct kmp_iter *iter) {
  if (!iter->x[0] || !iter->p[0])
    return NULL;

  for (; iter->x[iter->i]; iter->i++) {
    // Shift pattern down
    while (iter->j > 0 && iter->x[iter->i] != iter->p[iter->j])
      iter->j = iter->b[iter->j - 1];

    // Move one step forward (if we can)
    if (iter->x[iter->i] == iter->p[iter->j])
      iter->j++;

    // If we reached the end of the pattern, we found a match
    if (iter->p[iter->j] == '\0') {
      const char *result = iter->x + iter->i - iter->j + 1;
      // Updating iter for next iteration
      iter->j = 0;
      iter->i++;
      return result;
    }
  }
  return NULL;
}
void kmp_iter_free(struct kmp_iter *iter) { free(iter->b); }
