#pragma once

#include "ptmalloc3/ptmalloc3.h"

#define acpval(Src) ({\
    typeof(Src)* __dst = mspace_malloc(s_msp, sizeof(Src));\
    *__dst = (Src);\
    __dst;\
})

#define acpptr(SrcPtr) ({\
    typeof(SrcPtr) __src = (SrcPtr), __dst = __src ? acpval(*__src) : (void*)0;\
    __dst;\
})
