#include "../src/ghast_magma_internal.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#define TEST_g(A, B, Y) printf("%x %x\n", _ghast_magma_round_f(((uint32_t) A + (uint32_t) B)), (Y));\
    assert(_ghast_magma_round_f(((uint32_t) A + (uint32_t) B)) == (uint32_t) (Y));

#define TEST_t(A, B) printf("%x %x\n", _ghast_magma_round_t((uint32_t) (A)), (B));\
    assert(_ghast_magma_round_t((uint32_t) (A)) == (B));

int main() {
    TEST_t(0xfdb97531, 0x2a196f34);
    TEST_t(0x2a196f34, 0xebd9f03a);
    TEST_t(0xebd9f03a, 0xb039bb3d);
    TEST_t(0xb039bb3d, 0x68695433);
    printf("t transform test successful\n");
    TEST_g(0x87654321, 0xfedcba98, 0xfdcbc20c);
    TEST_g(0xfdcbc20c, 0x87654321, 0x7e791a4b);
    TEST_g(0x7e791a4b, 0xfdcbc20c, 0xc76549ec);
    TEST_g(0xc76549ec, 0x7e791a4b, 0x9791c849);
    printf("g transform test successful\n");
}
