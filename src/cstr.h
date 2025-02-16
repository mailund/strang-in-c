#pragma once

const char *naive(const char *x, const char *p);
void border_array(const char *p, int *b);

struct kmp_iter {
  const char *x;
  const char *p;
  int *b;
  int i;
  int j;
};

struct kmp_iter kmp_iter_init(const char *x, const char *p);
const char *kmp_iter_next(struct kmp_iter *iter);
void kmp_iter_free(struct kmp_iter *iter);