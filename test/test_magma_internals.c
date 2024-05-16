#define __GHAST_EXPOSE_INTERNALS

#include "../src/ghast_magma_internal.h"
#include <assert.h>

#define TEST_T(X, Y) assert(ghast_magma_round_f((X)) == (Y));


int main() {
    TEST_T(0xfdb97531, 0x2a196f34);
    TEST_T(0x2a196f34, 0xebd9f03a);
    TEST_T(0xebd9f03a, 0xb039bb3d);
    TEST_T(0xb039bb3d, 0x68695433);
}
