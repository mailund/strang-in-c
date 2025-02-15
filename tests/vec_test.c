#include <cstr.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
  cstr_vec(int) vec = cstr_new_vec(int, 10);
    
    for (int i = 0; i < 10; i++)
        cstr_vec_append(vec, i);
    
    assert(cstr_vec_size(vec) == 10);
    
    for (int i = 0; i < 10; i++)
        assert(cstr_vec_get(vec, i) == i);

    cstr_vec_free(vec);

  return 0;
}
