#define ONLY_MSPACES 1
#define MSPACES 1
#include "ptmalloc3/ptmalloc3.h"

static mspace s_msp;

void mempool_init(void) {
    s_msp = create_mspace(0, 0);
}

void mempool_dtor(void) {
    destroy_mspace(s_msp);
}

__attribute__(( malloc ))
void* mempool_malloc(size_t s) {
    return mspace_malloc(s_msp, s);
}
