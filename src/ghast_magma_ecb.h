#ifndef __GHAST_MAGMA_ECB_H
#define __GHAST_MAGMA_ECB_H

#include "./ghast_magma_ctx.h"
#include "./ghast_magma_internal.h"

void ghast_magma_ecb_encrypt_block(MagmaCtx* ctx, uint8_t* block);
void ghast_magma_ecb_decrypt_block(MagmaCtx* ctx, uint8_t* block);
void ghast_magma_ecb_init_ctx(MagmaCtx* ctx);

#endif
