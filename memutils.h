#pragma once

#include <ptmalloc3.h>

#define acpval(Src) ({\
    typeof(Src)* __dst = mempool_malloc(sizeof(Src));\
    *__dst = (Src);\
    __dst;\
})

#define acpptr(SrcPtr) ({\
    typeof(SrcPtr) __src = (SrcPtr), __dst = __src ? acpval(*__src) : (void*)0;\
    __dst;\
})

void mempool_init(void);

__attribute__(( malloc ))
void* mempool_malloc(size_t s);
