#pragma once

#include <stdlib.h>

#define acpval(Src) ({\
    typeof(Src)* __dst = malloc(sizeof(Src));\
    *__dst = (Src);\
    __dst;\
})

#define acpptr(SrcPtr) ({\
    typeof(SrcPtr) __src = (SrcPtr), __dst = __src ? acpval(*__src) : (void*)0;\
    __dst;\
})
