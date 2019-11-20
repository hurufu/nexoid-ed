#pragma once

// source: nexo-FAST v.3.2 section 13.3.6
// size: at least 50
// presence: O
// [EE]
struct AidPreferenceTable {
    // (Partial) Card AID of a preferred card application
    // [DF01]
    struct Aid cardAid;

    // [DF02]
    bcd_t applicationSelectionIndicator;

    // [BF02]
    struct {
        size_t l;
        struct Aid a[10]; // FIXME: Consider better dynamic array handling
    } subordinatedApplication;
};
