#ifndef __GHAST_MAGMA_INTERNAL_H
#define __GHAST_MAGMA_INTERNAL_H

#include "ghast_stdint.h"

void _ghast_magma_encrypt_block(uint8_t* block, uint8_t* key);
void _ghast_magma_decrypt_block(uint8_t* block, uint8_t* key);

uint32_t _ghast_magma_round_t(uint32_t a);
uint32_t _ghast_magma_round_f(uint32_t a);

#endif
