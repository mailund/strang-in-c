#include <assert.h>
#include <cstr.h>
#include <stdio.h>

void test_single_char(void) {
  int b[1];
  border_array("a", b);
  assert(b[0] == 0);
}

void test_no_borders(void) {
  int b[3];
  border_array("abc", b);
  assert(b[0] == 0);
  assert(b[1] == 0);
  assert(b[2] == 0);
}

void test_repeated_pattern(void) {
  int b[4];
  border_array("aaaa", b);
  assert(b[0] == 0);
  assert(b[1] == 0);
  assert(b[2] == 0);
  assert(b[3] == 3);
}

void test_complex_pattern(void) {
  int b[8];
  border_array("ababcaba", b);
  for (int i = 0; i < 8; i++)
    printf("%d ", b[i]);
  printf("\n");
  assert(b[0] == 0); // a
  assert(b[1] == 0); // ab
  assert(b[2] == 0); // aba[b]
  assert(b[3] == 2); // abab[c]
  assert(b[4] == 0); // ababc[a]
  assert(b[5] == 0); // ababca[b]
  assert(b[6] == 0); // ababcab[a]
  assert(b[7] == 3); // ababcaba[$]
}

int main(void) {
  test_single_char();
  test_no_borders();
  test_repeated_pattern();
  test_complex_pattern();
  printf("All border array tests passed!\n");
  return 0;
}
