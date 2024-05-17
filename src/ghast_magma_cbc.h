#ifndef __GHAST_MAGMA_CBC_H
#define __GHAST_MAGMA_CBC_H

#include "./ghast_magma_ctx.h"
#include "./ghast_magma_internal.h"

void ghast_magma_cbc_set_key(MagmaCtx* ctx, uint8_t* key);
void ghast_magma_cbc_encrypt_block(MagmaCtx* ctx, uint8_t* block);
void ghast_magma_cbc_decrypt_block(MagmaCtx* ctx, uint8_t* block);
void ghast_magma_cbc_init_ctx(MagmaCtx* ctx);

#endif
