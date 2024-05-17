#ifndef __GHAST_MAGMA_CTX_H
#define __GHAST_MAGMA_CTX_H

#include <stdint.h>

typedef enum {
    CBC,
    ECB,
} CipherType;

typedef struct MagmaCtx_ MagmaCtx;

struct MagmaCtx_ {
    void (*ghast_magma_set_key)(MagmaCtx*, uint8_t* key);
    void (*ghast_magma_encrypt)(MagmaCtx*, uint8_t* block);
    void (*ghast_magma_decrypt)(MagmaCtx*, uint8_t* block);
    uint8_t* key;
    uint8_t iv[8];
};

#endif
