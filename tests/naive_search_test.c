#include <cstr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

static bool compare_with_exected(const char *x, const char *p, int *expected,
                                 int expected_hits) {
  const char *i = x;
  printf("Lort %s and %s\n", x, p);
  for (int hit = 0; hit < expected_hits; hit++) {
    i = naive_search(i, p);
    printf("%s\n", i);
    if (expected[hit] != i - x) {
      fprintf(stderr, "Expected %d but got %ld\n", expected[hit], i - x);
      return false;
    }
    i++;
  }
  i = naive_search(i + 1, p);
  return i == NULL;
}

static void search_01(void) {
  const char *x = "abracadabra";
  const char *p = "abr";

  int expected[] = {0, 7};
  int res = compare_with_exected(x, p, expected, 2);
  if (!res) {
    fprintf(stderr, "search_01 failed\n");
    exit(1);
  }
}

static void search_02(void) {
  const char *x = "abracadabra";
  const char *p = "cad";

  int expected[] = {4};
  int res = compare_with_exected(x, p, expected, 1);
  if (!res) {
    fprintf(stderr, "search_02 failed\n");
    exit(1);
  }
}

static void search_03(void) {
  const char *x = "abracadabra";
  const char *p = "dab";

  int expected[] = {6};
  int res = compare_with_exected(x, p, expected, 1);
  if (!res) {
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
