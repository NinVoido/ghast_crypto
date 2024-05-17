#define use_8_bits_uint32

#include "../src/ghast_magma_internal.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "../src/ghast_stdint.h"

#ifndef use_8_bits_uint32
#define TEST_add_mod_32(A, B) add_to_ghast_be_uint32_t(A, B); \
    printf("%x %x\n", A[0], A[1]);
#else
#define TEST_add_mod_32(A, B) add_to_ghast_be_uint32_t(A, B); \
    printf("%x %x %x %x\n", A[0], A[1], a[2], a[3]);
#endif

#define TEST_g(A, B, Y) printf("%x %x\n", _ghast_magma_round_f(((uint32_t) A + (uint32_t) B)), (Y));\
    assert(_ghast_magma_round_f(((uint32_t) A + (uint32_t) B)) == (uint32_t) (Y));

#define TEST_t(A, B) printf("%x %x\n", _ghast_magma_round_t((uint32_t) (A)), (B));\
    assert(_ghast_magma_round_t((uint32_t) (A)) == (B));

int main() {
#ifndef use_8_bits_uint32
    uint16_t a[2] = {0x1234, 0x5678}, b[2] = {0x5678, 0xffff};
    TEST_add_mod_32(a, b);
#else
    uint8_t a[4] = {0x12, 0x34, 0x56, 0x78}, b[4] = {0x56, 0x78, 0xff, 0xff};
    TEST_add_mod_32(a, b);
#endif

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
