#pragma once

#include "macro.h"

#define PACKED __attribute__(( __packed__ ))

#define elementsof(Array) (sizeof(Array)/sizeof((Array)[0]))

#define MULTICHAR(...) NUMBERED_MACRO(MULTICHAR, __VA_ARGS__)

#define ONEOF(...) NUMBERED_MACRO(ONEOF, __VA_ARGS__)

// A → B
#define IMPLY(A, B) (~(A) | (B))

// A ↛ B
#define NIMPLY(A, B) (~IMPLY(A, B))

#define MIN(...) NUMBERED_MACRO(MIN, __VA_ARGS__)
