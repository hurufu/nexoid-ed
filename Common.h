#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum FunctionResult {
    R_OK
  , R_NOK
  , R_NON_EMV
  , R_TAP_AGAIN
  , R_END_APPLICATION
  , R_REFERENCE_ENTRY
  , R_ACCEPT
  , R_NOT_FOUND
  , R_NOT_SUPPORTED
  , R_MATCH
  , R_NO_MATCH
};

enum ServiceId {
    S_NONE = 0x00
  , S_PAYMENT = 0x01
  , S_REFUND = 0x02
  , S_CARD_VALIDITY_CHECK = 0x12
  , S_NO_SHOW = 0x13
} __attribute__((__packed__));

enum NokReason {
    N_NOT_IMPLEMENTED
};

enum Outcome {
    O_ONLINE_REQUEST
};

enum TransactionResult {
    T_NONE
  , T_ABORTED
  , T_NOT_SUPPORTED
  , T_APPROVED
};

enum TransactionType {
    TT_UNKNOWN
};

struct Out {
    enum Start {
        NONE,
        A,
        B,
        C,
        D,
        E,
        F
    } Start;
};

union TerminalSettings {
    unsigned char raw[5];
    struct {
        unsigned char : 7;
        unsigned char retrievePreauth : 1;
    };
};

union ServiceStartEvents {
    uint8_t raw[1];
    struct {
        uint8_t cardInserted : 1;
        uint8_t cardSwiped : 1;
        uint8_t amountEntry : 1;
        uint8_t manualEntry : 1;
        uint8_t referenceEntry : 1;
        uint8_t accept : 1;
        uint8_t cardholderDetect : 1;
        uint8_t /* RFU */ : 1;
    };
};

union ServiceSettings {
    uint8_t raw[2];
    struct {
        uint8_t isContactChipPrioritized : 1;
    };
};

union ApplicationProfileSettings {
    uint8_t raw[0];
    struct {
        uint8_t isDccAcceptorModeAllowed : 1;
    };
};

struct SearchLogCriteria {
    bool closed;
    char* referenceData;
    struct {
        size_t s;
        enum ServiceId v[];
    }* selectedService;
    enum TransactionResult tRes;
};

struct small_string {
    char hex[sizeof(int)];
};

struct Amount {
    unsigned char bcd[6];
};

union Country {
    uint16_t Code;
    char Str[3];
};

union Currency {
    struct {
        uint32_t Code : 3 * 8;
    };
    char Str[4];
};

struct Ctd {
    const struct Amount* const CvcDefaultAmount;
    const int KernelId;
    enum Outcome Outcome;
    struct Out Out;
    struct Amount TransactionAmount;
    enum TransactionResult TransactionResult;
    enum TransactionType TransactionType;

    enum FunctionResult Result;

    enum NokReason NokReason;
    bool TransactionAmountEntered;
    const enum ServiceId SelectedService;
    union Currency TransactionCurrency;

    // CONF
    const union ServiceSettings ServiceSettings;
    const union ServiceStartEvents ServiceStartEvents;
    const union ApplicationProfileSettings ApplicationProfileSettings;
    const union Currency* ApplicationCurrency;
    const union Country* IssuerCountry;

    // DCC
    volatile bool isDccEligible;
    bool DccPerformedOnce;
};

extern struct Ctd* tg_ctd;

const char* FunctionResult_tostring(enum FunctionResult f);
const char* TransactionResult_tostring(enum TransactionResult);
struct small_string TerminalSettings_tostring(union TerminalSettings);
struct small_string ServiceStartEvent_tostring(union ServiceStartEvents);
void ctd_print(const struct Ctd*);

static inline bool isIssuerCountryExcludedForDcc(void) {
    return false;
}
