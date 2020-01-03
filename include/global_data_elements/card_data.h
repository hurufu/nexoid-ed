#pragma once

#include "fci.h"
#include "response_message_template.h"

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
//
// Currently isn't used, because it's assumed for now that Trusted layer will
// populate special CardData members (like FCI, Response Message Template
// Format 1 and 2, etc).
struct ResponseData {
    size_t s;
    unsigned char c[256];
};

struct DolData {
    size_t s;
    unsigned char c[1024];
};

// nexo-FAST v.3.2, section 13.1.39
// TODO: Consider renaming to cvmTable
// [8E]
struct CvmList {
    size_t s;
    union {
        uint8_t raw[252];
        struct CvmListEntry {
            uint8_t amountX[4];
            uint8_t amountY[4];
            union {
                union {
                    uint8_t cvRule[2];
                    struct {
                        uint8_t : 1;
                        uint8_t applyNext: 1;

                        uint8_t : 8;
                    };
                };
                struct {
                    uint8_t : 2;
                    uint8_t cvmCode: 6; // 6 least significant bits

                    enum PACKED CvmConditionCode {
                        CVM_SUPPORTED = 0x03
                    } cvmConditionCode;
                };
            };
        } a[252 / 4];
    };
};

struct CardData {
    /** @{ */
    /** Members populated with raw or parsed card responses */
    union EmvStatus sw1Sw2;
    struct FileControlInformation* fci;
    struct ResponseMessageTemplate* responseMessageTemplate;
    struct ResponseData responseData;
    /** @} */
    bool responseDataParsed; // non-NEXO

    struct string16 applicationLabel;
    union ApplicationPriorityIndicator* applicationPriorityIndicator;
    struct Dol* pdol;
    struct string8* languagePreference;
    enum IssuerCodeTableIndex* issuerCodeTableIndex;
    struct string16* applicationPreferredName;
    struct ApplicationFileLocator afl;
    union ApplicationInterchangeProfile aip;
    struct CvmList* cvmList;

    struct DolData dolData;
    /** @{ */
    /** Data objects that are expected to be sent to the card */
    struct DolData cdaTransactionData;
    // TODO: Replace p1, p2 and p1ForGenAc type with some self-describing enum
    // TODO: Consider removing p1ForGenAc
    uint8_t p1;
    uint8_t p2;
    uint8_t p1ForGenAc;
    /** @} */
};
