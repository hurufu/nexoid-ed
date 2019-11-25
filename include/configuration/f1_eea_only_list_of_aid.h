#pragma once

// source: nexo-FAST v.3.2 section 13.3.59
// size: at least 50
// configuration: Terminal
// presence: O

struct EeaOnlyListOfAid {
    struct {
        size_t l;
        struct Aid a[50];
    } terminalAid;
};
