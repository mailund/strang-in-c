#include "cstr.h"

#include <stdio.h>
#include <stdlib.h>

const char *naive(const char *x, const char *p) {
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
