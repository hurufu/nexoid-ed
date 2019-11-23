#pragma once

// source: nexo-FAST v.3.2 section 13.3.15
// size: at least 60
struct ApplicationProfileSelectionTableNonChip {
    struct Bid Bid;
    unsigned char ApplicationProfileNumber;
    union ConfiguredServices SupportedServices;
    unsigned char* ApplicationProfileAcquirerNumber;
    struct {
        struct Prefix value;
        struct Prefix* next;
    }* prefix;
    struct Prefix* prefixMask;
    enum TechnologySelected* TechnologyOfProfile; // WUT?

    struct ApplicationProfileSelectionTableNonChip* next;
};
