#ifndef __GHAST_STDINT_H
#define __GHAST_STDINT_H

#include "ghast_config.h"

#ifdef CODEMASTER96
#include <stdint.h>
#endif

#define use_8_bits_uint32

#ifdef use_8_bits_uint32
typedef uint8_t ghast_be_uint32_t[4];
#else
typedef uint16_t ghast_be_uint32_t[2];
#endif

void add_to_ghast_be_uint32_t(ghast_be_uint32_t a, ghast_be_uint32_t b);


#endif
