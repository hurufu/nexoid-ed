#pragma once

#include "termainal.h"

// nexo FAST 13.1.62
// ISO/IEC 7816 4

struct FileControlInformation {
    struct Aid DfName;
};

extern struct FileControlInformation* g_Fci; // 6F
