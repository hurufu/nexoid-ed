#pragma once

#include "utils.h"

enum PACKED ApplicationSelectionIndicator {
    ASI_PARTIAL_MATCH_OK = 0x00
  , ASI_EXACT_MATCH = 0x01
};

struct SubordinatedApplication {
    // (Partial) Card AID of a subordinated appplications
    // [DF01]
    struct Aid cardAid;

    struct SubordinatedApplication* next;
};

// source: nexo-FAST v.3.2 section 13.3.6
// size: at least 50
// presence: O
// [EE]
struct AidPreferenceTable {
    // (Partial) Card AID of a preferred card application
    // [DF01]
    struct Aid cardAid;

    // [DF02]
    enum ApplicationSelectionIndicator applicationSelectionIndicator;

    // [BF02]
    struct SubordinatedApplication subordinatedApplication;

    struct AidPreferenceTable* next;
};
