#include <cstr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void search_empty_x(void) {
  const char *x = "";
  const char *p = "abc";
  const char *result = naive_search(x, p);
  if (result != NULL) {
    fprintf(stderr, "search_empty_x failed\n");
    exit(1);
  }
}

static void search_empty_p(void) {
  const char *x = "abc";
  const char *p = "";
  const char *result = naive_search(x, p);
  if (result != x) {
    fprintf(stderr, "search_empty_p failed\n");
    exit(1);
  }
}

static void search_01(void) {
  const char *x = "abracadabra";
  const char *p = "abr";

  cstr_vec(int) expected = cstr_new_vec(int, 2);
  cstr_vec_append(expected, 0);
  cstr_vec_append(expected, 7);

  cstr_vec(int) result = cstr_new_vec(int, 1);

  for (const char *i = naive_search(x, p); i; i = naive_search(i + 1, p)) {
    cstr_vec_append(result, i - x);
  }

  if (!cstr_vec_eq(expected, result)) {
    fprintf(stderr, "search_01 failed\n");
    exit(1);
  }
}

static void search_02(void) {
  const char *x = "abracadabra";
  const char *p = "cad";

  cstr_vec(int) expected = cstr_new_vec(int, 1);
  cstr_vec_append(expected, 5);

  cstr_vec(int) result = cstr_new_vec(int, 1);
  for (const char *i = naive_search(x, p); i; i = naive_search(i + 1, p)) {
    cstr_vec_append(result, i - x);
  }

  if (!cstr_vec_eq(expected, result)) {
    fprintf(stderr, "search_02 failed\n");
    exit(1);
  }
}

static void search_03(void) {
  const char *x = "abracadabra";
  const char *p = "dab";

  cstr_vec(int) expected = cstr_new_vec(int, 1);
  cstr_vec_append(expected, 6);

  cstr_vec(int) result = cstr_new_vec(int, 1);
  for (const char *i = naive_search(x, p); i; i = naive_search(i + 1, p)) {
    cstr_vec_append(result, i - x);
  }

  if (!cstr_vec_eq(expected, result)) {
    fprintf(stderr, "search_03 failed\n");
    exit(1);
  }
}

static void search_when_p_is_longer_than_x(void) {
  const char *x = "abracadabra";
  const char *p = "abracadabra!";

  const char *result = naive_search(x, p);
  if (result != NULL) {
    fprintf(stderr, "search_when_p_is_longer_than_x failed\n");
    exit(1);
  }
}

int main(void) {
  search_empty_x();
  search_empty_p();
  search_01();
  search_02();
  search_03();
  search_when_p_is_longer_than_x();
  return 0;
}
