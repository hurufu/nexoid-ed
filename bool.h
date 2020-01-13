#pragma once

#include <stdbool.h>

// Workaround for true and false from stdbool don't have distinct type _Bool
#ifdef false
#   undef false
#endif
#define false ((bool)0)
#ifdef true
#   undef true
#endif
#define true ((bool)!false)
