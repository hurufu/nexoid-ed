#pragma once

#include <stdlib.h>
#include <talloc.h>

struct drn_mem {
    struct drn_mem* next;
    unsigned char mem[];
};

struct drn_mem* drn_memctx;

static inline void* bad_malloc(const size_t s) {
    longjmp();
}

static inline void* drn_malloc(const size_t s) {
    drn_memptr->next = drn_memptr;
    drn_memptr = malloc(sizeof(struct drn_mem) + s) ?: bad_malloc(s);
    return drn_memptr.mem;
}

#define acpval(Src) ({\
    typeof(Src)* __dst = malloc(sizeof(Src));\
    *__dst = (Src);\
    __dst;\
})

#define acpptr(SrcPtr) ({\
    typeof(SrcPtr) __src = (SrcPtr), __dst = __src ? acpval(*__src) : (void*)0;\
    __dst;\
})
