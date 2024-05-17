#include "ghast_magma_internal.h"
#include "ghast_stdint.h"
#include "ghast_string.h"

#define XOR4(A, B) A[0] ^= B[0]; A[1] ^= B[1]; A[2] ^= B[2]; A[3] ^= B[3];

static uint8_t SBOX_1[16] = {0xC, 0x4, 0x6, 0x2, 0xA, 0x5, 0xB, 0x9, 0xE, 0x8, 0xD, 0x7, 0x0, 0x3, 0xF, 0x1};
static uint8_t SBOX_2[16] = {0x6, 0x8, 0x2, 0x3, 0x9, 0xA, 0x5, 0xC, 0x1, 0xE, 0x4, 0x7, 0xB, 0xD, 0x0, 0xF}; 
static uint8_t SBOX_3[16] = {0xB, 0x3, 0x5, 0x8, 0x2, 0xF, 0xA, 0xD, 0xE, 0x1, 0x7, 0x4, 0xC, 0x9, 0x6, 0x0};
static uint8_t SBOX_4[16] = {0xC, 0x8, 0x2, 0x1, 0xD, 0x4, 0xF, 0x6, 0x7, 0x0, 0xA, 0x5, 0x3, 0xE, 0x9, 0xB};
static uint8_t SBOX_5[16] = {0x7, 0xF, 0x5, 0xA, 0x8, 0x1, 0x6, 0xD, 0x0, 0x9, 0x3, 0xE, 0xB, 0x4, 0x2, 0xC};
static uint8_t SBOX_6[16] = {0x5, 0xD, 0xF, 0x6, 0x9, 0x2, 0xC, 0xA, 0xB, 0x7, 0x8, 0x1, 0x4, 0x3, 0xE, 0x0};
static uint8_t SBOX_7[16] = {0x8, 0xE, 0x2, 0x5, 0x6, 0x9, 0x1, 0xC, 0xF, 0x4, 0xB, 0x0, 0xD, 0xA, 0x3, 0x7};
static uint8_t SBOX_8[16] = {0x1, 0x7, 0xE, 0xD, 0x0, 0x5, 0x8, 0x3, 0x4, 0xF, 0xA, 0x6, 0x9, 0xC, 0xB, 0x2};


#ifdef use_8_bits_uint32
void add_to_ghast_be_uint32_t(ghast_be_uint32_t a, ghast_be_uint32_t b) {
    uint8_t carry = 0, backup;
    if (a[3] > UINT8_MAX - b[3]) {
        carry = 1;
    }
    a[3] += b[3];
    backup = carry;
    if ((b[2] == 0xff && carry) || a[2] > UINT8_MAX - b[2] - carry) {
        carry = 1;
    } else {
        carry = 0;
    }
    a[2] += b[2] + backup;
    backup = carry;
    if ((b[1] == 0xff && carry) || a[1] > UINT8_MAX - b[1] - carry) {
        carry = 1;
    } else {
        carry = 0;
    }
    a[1] += b[1] + backup;
    a[0] += b[0] + carry;
}
#else
void add_to_ghast_be_uint32_t(ghast_be_uint32_t a, ghast_be_uint32_t b) {
    uint8_t carry = 0;
    if (a[1] > UINT16_MAX - b[1] - carry) {
        carry = 1;
    } else {
        carry = 0;
    }
    a[1] += b[1];
    a[0] += b[0] + carry;
}
#endif

#ifdef use_8_bits_uint32

void _ghast_magma_round_t(ghast_be_uint32_t a) {
    a[0] = (SBOX_8[a[0] >> 4] << 4) | (SBOX_7[a[0] & 15]);
    a[1] = (SBOX_6[a[1] >> 4] << 4) | (SBOX_5[a[1] & 15]);
    a[2] = (SBOX_4[a[2] >> 4] << 4) | (SBOX_3[a[2] & 15]);
    a[3] = (SBOX_2[a[3] >> 4] << 4) | (SBOX_1[a[3] & 15]);
}

void _ghast_magma_round_f(ghast_be_uint32_t a, ghast_be_uint32_t dst) {
    a[0] = (SBOX_8[a[0] >> 4] << 4) | (SBOX_7[a[0] & 15]);
    a[1] = (SBOX_6[a[1] >> 4] << 4) | (SBOX_5[a[1] & 15]);
    a[2] = (SBOX_4[a[2] >> 4] << 4) | (SBOX_3[a[2] & 15]);
    a[3] = (SBOX_2[a[3] >> 4] << 4) | (SBOX_1[a[3] & 15]);

    dst[0] = ((a[1] & 31) << 3) | (a[2] >> 5);
    dst[1] = ((a[2] & 31) << 3) | (a[3] >> 5);
    dst[2] = ((a[3] & 31) << 3) | (a[0] >> 5);
    dst[3] = ((a[0] & 31) << 3) | (a[1] >> 5);
}
#else
uint32_t _ghast_magma_round_t(uint32_t a) {
    a = ((uint32_t) SBOX_8[a >> 28 & 15]) << 28 |
        ((uint32_t) SBOX_7[a >> 24 & 15]) << 24 |
        ((uint32_t) SBOX_6[a >> 20 & 15]) << 20 |
        ((uint32_t) SBOX_5[a >> 16 & 15]) << 16 |
        ((uint32_t) SBOX_4[a >> 12 & 15]) << 12 |
        ((uint32_t) SBOX_3[a >> 8 & 15]) << 8 |
        ((uint32_t) SBOX_2[a >> 4 & 15]) << 4 |
        ((uint32_t) SBOX_1[a & 15]);
    return a; 
}

uint32_t _ghast_magma_round_f(uint32_t a) {
    a = ((uint32_t) SBOX_8[a >> 28 & 15]) << 28 |
        ((uint32_t) SBOX_7[a >> 24 & 15]) << 24 |
        ((uint32_t) SBOX_6[a >> 20 & 15]) << 20 |
        ((uint32_t) SBOX_5[a >> 16 & 15]) << 16 |
        ((uint32_t) SBOX_4[a >> 12 & 15]) << 12 |
        ((uint32_t) SBOX_3[a >> 8 & 15]) << 8 |
        ((uint32_t) SBOX_2[a >> 4 & 15]) << 4 |
        ((uint32_t) SBOX_1[a & 15]);
    return (a << 11 | a >> 21);
}
#endif

void _ghast_magma_round_G(uint8_t* block, uint8_t* key) {
    uint8_t buf[4];
    uint8_t buf2[4];

    memcpy(buf, block + 4, 4);
    memcpy(buf2, buf, 4);
    add_to_ghast_be_uint32_t(buf, key);
    _ghast_magma_round_f(buf, block + 4);
    XOR4((block + 4), block);
    memcpy(block, buf2, 4);
}

void _ghast_magma_round_final(uint8_t* block, uint8_t* key) {
    uint8_t buf[4];
    uint8_t buf2[4];

    memcpy(buf, block + 4, 4);
    add_to_ghast_be_uint32_t(buf, key);
    _ghast_magma_round_f(buf2, buf);
    XOR4(block, buf2);
}
