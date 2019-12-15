#pragma once

#include "fci.h"

enum CommandName {
    COMMAND_SELECT_PSE,
    COMMAND_READ_PSD_REC,
    COMMAND_SELECT_ADF,
    COMMAND_SELECT_PPSE,
    COMMAND_GPO,
    COMMAND_READ_REC,
    COMMAND_INT_AUT,
    COMMAND_GEN_AC
};

// nexo-FAST v.3.2 section 13.3.111
struct ResponseData {
    size_t s;
    unsigned char c[256];
};

struct DolData {
    size_t s;
    unsigned char c[1024];
};

struct CardData {
    union EmvStatus sw1Sw2;
    struct FileControlInformation* fci;
    struct ResponseData responseData;
    bool responseDataParsed; // non-NEXO

    struct string16 applicationLabel;
    union ApplicationPriorityIndicator* applicationPriorityIndicator;
    struct Dol* pdol;
    struct string8* languagePreference;
    enum IssuerCodeTableIndex* issuerCodeTableIndex;
    struct string16* applicationPreferredName;

    struct DolData dolData;
    struct DolData cdaTransactionData;
};
