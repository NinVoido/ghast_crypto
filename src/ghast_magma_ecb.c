#include "./ghast_magma_ecb.h"
#include "./ghast_magma_internal.h"
#include "./ghast_string.h"

#ifdef PRINTF_DEBUG
#include <stdio.h>
#endif

#define XOR4(A, B) A[0] ^= B[0]; A[1] ^= B[1]; A[2] ^= B[2]; A[3] ^= B[3];

#define SWAP(BUFA, BUFB) XOR4(BUFA, BUFB); XOR4(BUFB, BUFA); XOR4(BUFA, BUFB);


void ghast_magma_ecb_set_key(MagmaCtx* ctx, uint8_t* key) {
    ctx->key = key;
}

#define PRINTF_DEBUG
#undef PRINTF_DEBUG

void ghast_magma_ecb_encrypt_block(MagmaCtx* ctx, uint8_t* block) {
    for (int i = 0; i < 24; ++i) {
        _ghast_magma_round_G(block, ctx->key + ((i & 7) << 2));
#ifdef PRINTF_DEBUG
        printf("%02x%02x%02x%02x %02x%02x%02x%02x\n", block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7]);
#endif
    }
    for (int i = 0; i < 8; ++i) {
        _ghast_magma_round_G(block, ctx->key + ((7 - i) << 2));
#ifdef PRINTF_DEBUG
        printf("%02x%02x%02x%02x %02x%02x%02x%02x\n", block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7]);
#endif
    }
    SWAP(block, (block + 4));
}

void ghast_magma_ecb_decrypt_block(MagmaCtx* ctx, uint8_t* block) {
    for (int i = 0; i < 8; ++i) {
        _ghast_magma_round_G(block, ctx->key + (i << 2));
#ifdef PRINTF_DEBUG
        printf("iter %d: %02x%02x%02x%02x %02x%02x%02x%02x\n", i + 8, block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7]);
#endif
    }
    for (int i = 0; i < 24; ++i) {
        _ghast_magma_round_G(block, ctx->key + ((7 - (i & 7)) << 2));
#ifdef PRINTF_DEBUG
        printf("iter %d: %02x%02x%02x%02x %02x%02x%02x%02x\n", i + 8, block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7]);
#endif
    }

    SWAP(block, (block + 4));
}

void ghast_magma_ecb_init_ctx(MagmaCtx* ctx) {
    ctx->ghast_magma_encrypt = ghast_magma_ecb_encrypt_block;
    ctx->ghast_magma_decrypt = ghast_magma_ecb_decrypt_block;
    ctx->ghast_magma_set_key = ghast_magma_ecb_set_key;
}
