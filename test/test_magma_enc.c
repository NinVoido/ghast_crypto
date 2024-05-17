#include "../src/ghast_magma_ecb.h"
#include <stdio.h>

uint8_t block[8] = {0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
uint8_t key[32] = {0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff};

int main() {
    MagmaCtx ctx;
    ghast_magma_ecb_init_ctx(&ctx);
    
    ctx.ghast_magma_set_key(&ctx, key);
    ctx.ghast_magma_encrypt(&ctx, block);

    for (int i = 0; i < 8; ++i) {
        printf("%02x", block[i]);
    }

    printf("\n");

    ctx.ghast_magma_decrypt(&ctx, block);
    for (int i = 0; i < 8; ++i) {
        printf("%02x", block[i]);
    }
}
