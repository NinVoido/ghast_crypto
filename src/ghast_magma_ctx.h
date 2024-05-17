/**
 * @file ghast_magma_ctx.h
 * @brief Definitions for cipher context types
 */

#ifndef __GHAST_MAGMA_CTX_H
#define __GHAST_MAGMA_CTX_H

#include <stdint.h>

typedef enum {
    CBC,
    ECB,
} CipherType;

typedef struct MagmaCtx_ MagmaCtx;

/** 
 * @brief Structure for generic Magma cipher context
 *
 * Contains vtable for various methods to allow for generic usage and holds IV\n
 * 
 * @example test_magma_enc.c
 * Usage example with ECB used
 */
struct MagmaCtx_ {
    void (*ghast_magma_set_key)(MagmaCtx*, uint8_t* key); /**< @brief Function pointer to key setter*/
    void (*ghast_magma_encrypt)(MagmaCtx*, uint8_t* block); /**< @brief Function pointer to encrypt one block*/
    void (*ghast_magma_decrypt)(MagmaCtx*, uint8_t* block); /**< @brief Function pointer to decrypt one block*/
    uint8_t* key; /**< @brief Pointer to bytes of cipher key*/
    uint8_t iv[8]; /**< @brief IV for internal usage by cipher*/
};

#endif
