#include "../src/ghast_magma_ecb.h"

int main() {
    MagmaCtx ctx;
    uint8_t buf[40];
    ghast_magma_ecb_init_ctx(&ctx);
    ctx.ghast_magma_encrypt(&ctx, buf);
}
