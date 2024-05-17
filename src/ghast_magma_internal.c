#include "ghast_magma_internal.h"
#include "ghast_stdint.h"
#include "ghast_string.h"

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

void _ghast_magma_encrypt_block(uint8_t* block, uint8_t* key) {
    uint8_t buf[4];

    for (int i = 0; i < 31; ++i) {
        memcpy(buf, block + 4, 4);
     //   (uint32_t*) (block + 4) = _ghast_magma_round_f(*(uint32_t*)(block) + 
    }
}

