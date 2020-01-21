#pragma once

#include "macro.h"

#define PACKED __attribute__(( __packed__ ))

#define elementsof(Array) (sizeof(Array)/sizeof((Array)[0]))

#define MULTICHAR(...) NUMBERED_MACRO(MULTICHAR, __VA_ARGS__)

#define ONEOF(...) NUMBERED_MACRO(ONEOF, __VA_ARGS__)
