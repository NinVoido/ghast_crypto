#ifndef __GHAST_MAGMA_INTERNAL_H
#define __GHAST_MAGMA_INTERNAL_H

#include "ghast_stdint.h"

void _ghast_magma_encrypt_block(uint8_t* block);
void _ghast_magma_decrypt_block(uint8_t* block);

#ifdef __GHAST_EXPOSE_INTERNALS
uint32_t ghast_magma_round_f(uint32_t a);
#endif

#endif
