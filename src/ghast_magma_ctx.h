#ifndef __GHAST_MAGMA_CTX_H
#define __GHAST_MAGMA_CTX_H

#include <stdint.h>

typedef enum {
    CBC,
    ECB,
} CipherType;

typedef struct MagmaCtx_ MagmaCtx;

struct MagmaCtx_ {
    void (*ghast_magma_set_key)(MagmaCtx);
    void (*ghast_magma_encrypt)(MagmaCtx);
    void (*ghast_magma_decrypt)(MagmaCtx);
    uint8_t key[256];
    uint8_t iv[8];
};

#endif
