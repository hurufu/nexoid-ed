#pragma once

#include "termainal.h"

#include <stdint.h>

// nexo-FAST v.3.2 section 13.1.62
// ISO/IEC 7816 4
// EMV 4.3 Book 1 table 43~45

// FIXME: Consider using generic format like `struct tlv`
struct FciIssierProprietaryDataElement {
    struct FciIssierProprietaryDataElement* next;
    uintmax_t t;
    size_t l;
    unsigned char v[];
};

struct FciIssuerDiscretionaryData {
    // FIXME: Consider better type for logEntry;
    // [9F4D]
    unsigned char logEntry[2];

    // On or more proprietary data elements
    struct FciIssierProprietaryDataElement* proprietary;
};

// [A5]
struct FciProprietaryTemplate {
    // nexo-FAST v.3.2 section 13.1.17
    // [50]
    struct string16 applicationLabel;

    // [87]
    union ApplicationPriorityIndicator* applicationPriorityIndicator;

    // [9F38]
    struct Dol* pdol;

    // [5F2D]
    struct string8* languagePreference;

    // [9F11]
    enum IssuerCodeTableIndex* issuerCodeTableIndex;

    // [9F12]
    struct string16* applicationPreferredName;

    // [BF0C]
    struct FciIssuerDiscretionaryData* issuerDiscretionaryData;
};

// [6F]
struct FileControlInformation {
    // [84]
    struct Aid DfName;
    // [A5]
    struct FciProprietaryTemplate a5;
};
