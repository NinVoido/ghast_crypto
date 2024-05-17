#ifndef __GHAST_MAGMA_INTERNAL_H
#define __GHAST_MAGMA_INTERNAL_H

#include "ghast_stdint.h"

void _ghast_magma_encrypt_block(uint8_t* block, uint8_t* key);
void _ghast_magma_decrypt_block(uint8_t* block, uint8_t* key);

void _ghast_magma_round_t(ghast_be_uint32_t a);
void _ghast_magma_round_f(ghast_be_uint32_t a, ghast_be_uint32_t dst);
void _ghast_magma_round_G(uint8_t* block, uint8_t* key);

#endif
