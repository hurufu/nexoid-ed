#include "dmapi.h"
#include <stdio.h>
#define ONLY_MSPACES 1
#define MSPACES 1
#include <ptmalloc3.h>

static mspace s_msp;

enum DmapiResult dmapi_init(void) {
    s_msp = create_mspace(0, 0);
    return s_msp ? DMAPI_OK : DMAPI_NOK;
}

void dmapi_dtor(void) {
    destroy_mspace(s_msp);
}

__attribute__(( malloc ))
void* dmapi_malloc(size_t s) {
    return mspace_malloc(s_msp, s);
}

void dmapi_free(void* const ptr) {
    mspace_free(s_msp, ptr);
}
