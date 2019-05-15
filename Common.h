#pragma once

#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define TRACE(Fmt, ...)\
    printf(Fmt"\t%s\t%d\t%s\n", ##__VA_ARGS__, __FILE__, __LINE__, __func__)

enum ProcedureResult {
    PR_UNINITIALISED = 239
  , PR_NOT_IMPLEMENTED

  , PR_OK
  , PR_NOK
  , PR_NON_EMV
  , PR_TAP_AGAIN
  , PR_END_APPLICATION
  , PR_REFERENCE_ENTRY
  , PR_ACCEPT
  , PR_NOT_FOUND
  , PR_NOT_SUPPORTED
  , PR_MATCH
  , PR_NO_MATCH
  , PR_DONE
  , PR_ONLINE
  , PR_UNABLE_TO_GO_ONLINE
  , PR_CONDITIONS_SATISFIED
  , PR_CONDITIONS_NOT_SATISFIED
  , PR_REINITIALISE
  , PR_NEW_EVENT

  , PR_MAX
};

enum ServiceId {
    S_NONE = 0x00
  , S_PAYMENT = 0x01
  , S_REFUND = 0x02
  , S_CANCELLATION = 0x03
  , S_PRE_AUTH = 0x04
  , S_UPDATE_PRE_AUTH = 0x05
  , S_PAYMENT_COMPLETION = 0x06
  , S_CASH_ADVANCE = 0x07
  , S_DEFFERED_PAYMENT = 0x08
  , S_DEFFERED_PAYMENT_COMPLETION = 0x09
  , S_VOICE_AUTHORISATION = 0x10
  , S_CARDHOLDER_DETECTION = 0x11
  , S_CARD_VALIDITY_CHECK = 0x12
  , S_NO_SHOW = 0x13

  , S_MAX
} __attribute__((__packed__));

enum NokReason {
    N_NOT_IMPLEMENTED = PR_MAX + 2364
  , N_ORIGINAL_TRX_NOT_FOUND
  , N_TECHNNICAL_ERROR
  , N_MISSING_DATA
  , N_NO_PERMISSION

  , N_MAX
};

enum Outcome {
    O_ONLINE_REQUEST = N_MAX + 9745

  , O_MAX
};

enum TransactionResult {
    T_NONE = O_MAX + 8273
  , T_ABORTED
  , T_NOT_SUPPORTED
  , T_APPROVED
  , T_DECLINED

  , T_MAX
};

enum TransactionType {
    TT_UNKNOWN
} __attribute__((packed));

enum IdleEvent {                  // Service Start Event?
    E_LANGUAGE_SELECTION = 0      // No
  , E_CHOICE_OF_APPLICATION       // No
  , E_SERVICE_SELECTION           // No
  , E_ACQUIRER_PRESELECTION       // No
  , E_CARDHOLDER_DETECTION        // Yes
  , E_AMOUNT_ENTRY                // Yes
  , E_CARD_INSERTED               // Yes
  , E_CARD_SWIPED                 // Yes
  , E_MANUAL_ENTRY                // Yes
  , E_REFERENCE_ENTRY             // Yes
  , E_ACCEPT                      // Yes
  , E_ATTENDANT_FORCED_ONLINE     // No
  , E_ADDITIONAL_TRANSACTION_DATA // No
  , E_CARD_REMOVAL                // No
  , E_CANCEL                      // No

  , E_MAX                         // N/A
};

enum TerminalErrorReason {
    TE_NONE = T_MAX + 2423
  , TE_HARDWARE_ERROR
  , TE_MEMORY_FAILURE
  , TE_CONFIGURATION_ERROR
  , TE_CRYPTOGRAPHIC_KEYS_MISSING
  , TE_LOG_LIMIT_EXCEEDED
  , TE_COMMUNICATION_ERROR
  , TE_UNSPECIFIED
  , TE_NEXO_FAST_FAILURE
  , TE_INTERACTION_ERROR
  , TE_OVERSPEND
};

struct Out {
    enum Start {
        NONE = T_MAX + 2398,
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
        uint8_t ContactChipPrioritized : 1;
        uint8_t ServiceProtected : 1;
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

union Amount {
    unsigned char bcd[6];
    int64_t i; // Used for quick zeroing
};

union Country {
    enum {
        Country_pl = MULTICHAR('p','l')
    } Code;
    char Str[3];
};

union Currency {
    enum {
        Currency_EUR = MULTICHAR('E','U','R'),
        Currency_PLN = MULTICHAR('P','L','N')
    } Code;
    char Str[4];
};

struct AuthorisationResponseCode {
    uint8_t v[2];
};

struct CurrentTransactionData {
    // Transaction
    const int KernelId;
    enum Outcome Outcome;
    struct Out Out;
    union Amount TransactionAmount;
    bool TransactionAmountEntered;
    enum TransactionType TransactionType;
    enum TransactionResult TransactionResult;
    enum NokReason NokReason;
    enum ServiceId SelectedService;
    union Currency TransactionCurrency;
    struct AuthorisationResponseCode AuthorisationResponseCode;
    bool AttendantForcedTransactionOnline;
    char ReferenceData[35 + 1];

    // Card data
    const union Country* IssuerCountry;
    unsigned char (* PAN)[11];

    // DCC
    volatile bool isDccEligible;
    bool DccPerformedOnce;

    // Service startup
    bool SecurityPermission;
    union Country SelectedLanguage;
    bool Event[E_MAX];
    enum TerminalErrorReason TerminalErrorReason;
    bool TerminalErrorIndicator;
};

struct NexoConfiguration {
    // Terminal configuration
    uint8_t TerminalType;
    union TerminalSettings TerminalSettings;
    enum ServiceId DefaultService;

    // Application configuration
    union Currency* ApplicationCurrency;
    union Country CardholderDefaultLanguage;

    // Service configuration
    union ServiceStartEvents ServiceStartEvents[S_MAX];
    union ServiceSettings ServiceSettings[S_MAX];
    union ApplicationProfileSettings ApplicationProfileSettings;

    // CVC
    union Amount* CvcDefaultAmount;

    // DCC
    union Amount DccMinimumAllowedAmount;
};

extern struct CurrentTransactionData g_Ctd;
extern struct NexoConfiguration g_Nexo;

const char* ProcedureResult_tostring(enum ProcedureResult f);
const char* TransactionResult_tostring(enum TransactionResult);
struct small_string TerminalSettings_tostring(union TerminalSettings);
struct small_string ServiceStartEvent_tostring(union ServiceStartEvents);
void ctd_print(const struct CurrentTransactionData*);

static inline bool isIssuerCountryExcludedForDcc(void) {
    return false;
}
