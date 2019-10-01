#pragma once

#include "bool.h"
#include "common.h"

#include <inttypes.h>

/* Configuration options defined once per terminal application
 * TODO: Consider generation of thise header file from ASN.1 sources
 */

struct Aid {
    size_t l_raw;
    union {
        uint8_t raw[16];
        struct {
            uint8_t rid[5];
            uint8_t pix[];
        };
    };
};

struct ExtendedAid {
    size_t l_raw;
    union {
        uint8_t raw[16];
        struct {
            uint8_t rid[5];
            uint8_t ext[];// Proprietary Extended Selection 0x9F29
        };
    };
};

struct TerminalListOfAidEntry {
    struct Aid terminalAid; // 0xDF01
    bool applicationSelectionIndicator; // 0xDF02
};

struct TerminalListOfAid {
    size_t l_entry;
    struct TerminalListOfAidEntry entry[50]; // 0xBF01
};

extern struct TerminalListOfAid* g_TerminalListOfAid; // 0xE5
