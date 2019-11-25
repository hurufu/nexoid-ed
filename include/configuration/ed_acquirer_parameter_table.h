#pragma once

#include "types.h"
#include "bool.h"

// source: nexo-FAST v.3.2 section 13.3.2
// size: >= 25
// configuration: Terminal
// presence: M
// [ED]
struct AcquirerParameterTable {
    // A reference number uniquely identifying the acquirer for the nexo FAST application
    // [DF01]
    struct bcd2 acquirerNumber;

    // Mnemonic identifying the acquirer as known by the attendant
    // [DF02]
    struct ans_16 acquirerLabel;

    // Set to true when this acquirer label is presented to the attendant during
    // the Acquirer Pre-Selection process
    // [DF03]
    bool usedForPreSelection;
};
