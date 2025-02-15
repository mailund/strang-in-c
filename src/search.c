#include "cstr.h"

#include <stdlib.h>

const char *naive_search(const char *x, const char *p) {
  for (const char *i = x; *i != '\0'; i++) {
    for (const char *j = p; /* check in body*/; i++, j++)
      if (*j == '\0') // We reached the end of p
        return i;
      else if (*i != *j) // We hit a mismatch
        break;
  }
  return NULL;
}
