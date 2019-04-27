#pragma once

#include "utils.h"
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
  , R_DONE
  , R_ONLINE
  , R_UNABLE_TO_GO_ONLINE
  , R_START_CONDITIONS_SATISFIED
  , R_REINITIALISE
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
} __attribute__((__packed__));

enum NokReason {
    N_NOT_IMPLEMENTED
  , N_ORIGINAL_TRX_NOT_FOUND
  , N_TECHNNICAL_ERROR
  , N_MISSING_DATA
};

enum Outcome {
    O_ONLINE_REQUEST
};

enum TransactionResult {
    T_NONE
  , T_ABORTED
  , T_NOT_SUPPORTED
  , T_APPROVED
  , T_DECLINED
};

enum TransactionType {
    TT_UNKNOWN
};

enum IdleEvent {                  // Service Start Event?
    E_LANGUAGE_SELECTION          // No
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

union Amount {
    unsigned char bcd[6];
    int64_t i;
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

struct Ctd {
    const union Amount* const CvcDefaultAmount;
    const int KernelId;
    enum Outcome Outcome;
    struct Out Out;
    union Amount TransactionAmount;
    enum TransactionResult TransactionResult;
    enum TransactionType TransactionType;

    enum FunctionResult Result;

    enum NokReason NokReason;
    bool TransactionAmountEntered;
    const enum ServiceId SelectedService;
    union Currency TransactionCurrency;
    unsigned char (* PAN)[11];
    struct AuthorisationResponseCode AuthorisationResponseCode;
    bool AttendantForcedTransactionOnline;
    union ServiceStartEvents ServiceStartEvents;

    // CONF
    const union ServiceSettings ServiceSettings;
    const union ApplicationProfileSettings ApplicationProfileSettings;
    const union Currency* ApplicationCurrency;
    const union Country* IssuerCountry;
    const union TerminalSettings TerminalSettings;

    // DCC
    volatile bool isDccEligible;
    bool DccPerformedOnce;
};

extern struct Ctd* tg_ctd;
extern enum FunctionResult g_Result;
extern bool g_Event[E_MAX];

const char* FunctionResult_tostring(enum FunctionResult f);
const char* TransactionResult_tostring(enum TransactionResult);
struct small_string TerminalSettings_tostring(union TerminalSettings);
struct small_string ServiceStartEvent_tostring(union ServiceStartEvents);
void ctd_print(const struct Ctd*);

static inline bool isIssuerCountryExcludedForDcc(void) {
    return false;
}
