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
    printf("%x %x %x %x\n", A[0], A[1], A[2], A[3]);

#define TEST_t(A, B) _ghast_magma_round_t(A);\
    printf("%x %x %x %x\n", A[0], A[1], A[2], A[3]);

#define TEST_g(A, B, buf, C) add_to_ghast_be_uint32_t(A, B);\
    _ghast_magma_round_f(A, buf);\
    printf("%x %x %x %x\n", buf[0], buf[1], buf[2], buf[3]);

#define TEST_enc(G, KEY) _ghast_magma_round_G(G, KEY);\
    printf("%x %x %x %x %x %x %x %x\n", G[0], G[1], G[2], G[3], G[4], G[5], G[6], G[7]);

#endif


#ifndef use_8_bits_uint32
#define TEST_g(A, B, Y) printf("%x %x\n", _ghast_magma_round_f(((uint32_t) A + (uint32_t) B)), (Y));\
    assert(_ghast_magma_round_f(((uint32_t) A + (uint32_t) B)) == (uint32_t) (Y));

#define TEST_t(A, B) printf("%x %x\n", _ghast_magma_round_t((uint32_t) (A)), (B));\
    assert(_ghast_magma_round_t((uint32_t) (A)) == (B));
#endif

int main() {
#ifndef use_8_bits_uint32
    uint16_t a[2] = {0x1234, 0x5678}, b[2] = {0x5678, 0xffff};
    TEST_add_mod_32(a, b);
#else
    uint8_t a[4] = {0x12, 0x34, 0x56, 0x78}, b[4] = {0x56, 0x78, 0xff, 0xff};
    TEST_add_mod_32(a, b);
#endif
    
#ifdef use_8_bits_uint32
    uint8_t aa[4] = {0xfd, 0xb9, 0x75, 0x31}, bb[4] = {0x2a, 0x19, 0x6f, 0x34};
    TEST_t(aa, bb);

    a[0] = 0x87; a[1] = 0x65; a[2] = 0x43; a[3] = 0x21;
    b[0] = 0xfe; b[1] = 0xdc; b[2] = 0xba; b[3] = 0x98;
    uint8_t buf[4];
    TEST_g(a, b, buf, aa);

    uint8_t pt[8] = {0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10}, key[4] = {0xff, 0xee, 0xdd, 0xcc};
    TEST_enc(pt, key);
#else 
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
#endif
}
