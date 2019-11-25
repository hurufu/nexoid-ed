#pragma once

#include "macro.h"

#define elementsof(Array) (sizeof(Array)/sizeof((Array)[0]))

#define MULTICHAR(...) NUMBERED_MACRO(MULTICHAR, ##__VA_ARGS__)

#define PACKED __attribute__(( __packed__ ))

#define STRING_SENTINEL struct { char : 1; }

// TODO: Replace ONEOF macro with proper map/reduce equivalent
#define ONEOF1(X, A1)             (((X) == (A1)))
#define ONEOF2(X, A1, A2)         (((X) == (A1)) || ((X) == (A2)))
#define ONEOF3(X, A1, A2, A3)     (((X) == (A1)) || ((X) == (A2)) || ((X) == (A3)))
#define ONEOF4(X, A1, A2, A3, A4) (((X) == (A1)) || ((X) == (A2)) || ((X) == (A3)) || ((X) == (A4)))

struct string16 {
    char s[16];
    STRING_SENTINEL;
};

struct string8 {
    char s[8];
    STRING_SENTINEL;
};
