#pragma once

#include "macro.h"

#define elementsof(Array) (sizeof(Array)/sizeof((Array)[0]))

#define MULTICHAR(...) NUMBERED_MACRO(MULTICHAR, ##__VA_ARGS__)

#define PACKED __attribute__(( __packed__ ))
