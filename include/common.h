#pragma once

#include "utils.h"
#include "mem.h"
#include "bool.h"

#include <ptmalloc3.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum ProcedureResult {
    PR_UNINITIALISED = 239
  , PR_NOT_IMPLEMENTED
  , PR_INTERNAL_INCONSISTENCY
  , PR_REBOOT
  , PR_TERMINATE
  , PR_SHUTDOWN
  , PR_STARTUP_SEQUENCE

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
  , N_TECHNICAL_ERROR
  , N_MISSING_DATA
  , N_NO_PERMISSION
  , N_CONFIGURATION_ERROR
  , N_AMOUNT_ERROR

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

// Array is indexed by enum IdleEvent
enum IdleEvent {                  // Service Start Event?
    // NEXO
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

  // Non Nexo
  , E_REBOOT_REQUESTED            // No
  , E_TERMINATION_REQUESTED       // No
  , E_SHUTDOWN_REQUESTED          // No

  , E_MAX                         // N/A
};

enum TerminalErrorReason {
  // Specified in NEXO
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

  // Not specified in NEXO
  , TER_NOT_IMPLEMENTED

  , TER_MAX
};

struct Out {
    enum Start {
        NONE = TER_MAX + 2398,
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

union ConfiguredServices {
    uint8_t raw[2];
    uint16_t i;
    struct {
        uint8_t payment : 1;
        uint8_t refund : 1;
        uint8_t cancellation : 1;
        uint8_t preAuthorisation : 1;
        uint8_t updatePreAuthorisation : 1;
        uint8_t paymentCompletion : 1;
        uint8_t cashAdvance : 1;
        uint8_t deferredPayment : 1;

        uint8_t deferredPaymentCompletion : 1;
        uint8_t cardholderDetection : 1;
        uint8_t cardValidityCheck : 1;
        uint8_t noShow : 1;
        uint8_t voiceAuthorisation : 1;
        uint8_t /* RFU */ : 3;
    };
};

union TerminalTransactionQualifiers {
    uint8_t raw[4];
    uint32_t i;
    union {
        struct {
            uint8_t msrModeSupported : 1;
            uint8_t /* RFU */ : 1;
            uint8_t emvModeSupported : 1;
            uint8_t emvContactChipModeSupported : 1;
            uint8_t offlineOnlyReader : 1;
            uint8_t onlinePinSupported : 1;
            uint8_t signatureSupported : 1;
            uint8_t offlineDataAuthenticationForOnlineAuthSupported : 1;

            uint8_t onlineCryptogramRequired : 1;
            uint8_t cvmRequired : 1;
            uint8_t contactChipOfflinePinSupported : 1;
            uint8_t /* RFU */ : 5;

            uint8_t issuerUpdateProcessingSupported : 1;
            uint8_t consumerDeviceCvmSupported : 1;
            uint8_t /* RFU */ : 6;

            uint8_t /* RFU */ : 8;
        } kernel3;

        struct {
            uint8_t msrModeSupported : 1;
            uint8_t /* RFU */ : 1;
            uint8_t emvModeSupported : 1;
            uint8_t emvContactChipModeSupported : 1;
            uint8_t offlineOnlyReader : 1;
            uint8_t onlinePinSupported : 1;
            uint8_t signatureSupported : 1;
            uint8_t /* RFU */ : 1;

            uint8_t onlineCryptogramRequired : 1;
            uint8_t cvmRequired : 1;
            uint8_t contactChipOfflinePinSupported : 1;
            uint8_t /* RFU */ : 5;

            uint8_t issuerUpdateProcessingSupported : 1;
            uint8_t consumerDeviceCvmSupported : 1;
            uint8_t /* RFU */ : 1;
            uint8_t consumerDeviceCvmRequired : 1;
            uint8_t /* RFU */ : 3;

            uint8_t /* RFU */ : 8;
        } kernel6;

        struct {
            uint8_t /* RFU */ : 1;
            uint8_t fullCtlsTransactionFlowSupported : 1;
            uint8_t emvModeSupported : 1;
            uint8_t fullContactTransactionFlowSupported : 1;
            uint8_t offlineOnlyReader : 1;
            uint8_t onlinePinSupported : 1;
            uint8_t signatureSupported : 1;
            uint8_t /* RFU */ : 1;

            uint8_t onlineCryptogramRequired : 1;
            uint8_t cvmRequired : 1;
            uint8_t /* RFU */ : 6;

            uint8_t /* RFU */ : 8;

            uint8_t supprtedFddaV1_0 : 1;
            uint8_t /* RFU */ : 7;
        } kernel7;
    };
};

union ServiceSettings {
    uint8_t raw[2];
    struct {
        uint8_t ContactChipPrioritized : 1;
        uint8_t msrProcessingModeSupported : 1;
        uint8_t msrProcessingModeSupportedForCashback : 1;
        uint8_t ServiceProtected : 1;
        uint8_t manualEntryProcessingModeSupported : 1;
        uint8_t ctlsProcessingModeSupported : 1;
        uint8_t automaticAppSelection : 1;
        uint8_t contactProcessingModeSupported : 1;

        uint8_t deferredPaymentTrxAmountRequired : 1;
        uint8_t deferredPaymentAdditionalSalesInfo : 1;
        uint8_t crdhlrConfirmationNotAllowed : 1;
        uint8_t crdhlrConfirmationRequired : 1;
        uint8_t preauthTrxAmountRequired : 1;
        uint8_t /* RFU */ : 3;
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

struct CombinationsListAndParametersEntry {
    struct {
        uint8_t size : 5;
        unsigned char value[16];
    } terminalAid;
    unsigned char kernelId;
    union ConfiguredServices supportingServices;
    bool* cashbackPresent;
    union TerminalTransactionQualifiers* terminalTransactionQualifiers;
    bool* statusCheckSupportFlag;
    bool* zeroAmountAllowedFlag;
    union Amount* readerCtlessTransactionLimit;
    union Amount* readerCtlessFloorLimit;
    union Amount* readerCvmRequiredLimit;
    bool* extendedSelectionSupported;

    // Predefined indicators
    bool* statusCheckRequested;
    bool* zeroAmount;
    bool* ctlessApplicationNotAllowed;
    bool* readerCtlessFloorLimitNotAllowed;
    bool* readerCvmRequiredLimitExceeded;
    bool* readerCtlessFloorLimitExceeded;

    struct CombinationsListAndParametersEntry* next;
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

    // Cashback
    union Amount CashbackAmount;

    // Card data
    const union Country* IssuerCountry;
    unsigned char (* PAN)[11];

    // DCC
    volatile bool isDccEligible;
    bool DccPerformedOnce;

    // Pre-Authorisation
    bool* Minus;

    // Service startup
    bool SecurityPermission;
    bool AmountDisplayed;
    union Country SelectedLanguage;
    struct EventTable {
        bool Table[E_MAX];
    } Event;
    enum TerminalErrorReason TerminalErrorReason;
    bool TerminalErrorIndicator;

    // Contactless
    struct CombinationsListAndParametersEntry* CombListWorkingTable;
    bool NoContactlessAllowed;
};

struct NexoConfiguration {
    // Terminal configuration
    uint8_t TerminalType;
    union TerminalSettings TerminalSettings;

    // Application configuration
    enum ServiceId DefaultService;
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

    // Refund
    union Amount RefundProtectionAmount;

    // Contactless
    struct CombinationsListAndParametersEntry* CombListsAndParams;
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

static inline union ConfiguredServices
ServiceId_to_ConfiguredServices(const enum ServiceId s) {
    union ConfiguredServices ret = { };
    switch (s) {
        case S_PAYMENT:
            ret.payment = 1;
            break;
        case S_REFUND:
            ret.refund = 1;
            break;
        case S_CANCELLATION:
            ret.cancellation = 1;
            break;
        case S_PRE_AUTH:
            ret.preAuthorisation = 1;
            break;
        case S_UPDATE_PRE_AUTH:
            ret.updatePreAuthorisation = 1;
            break;
        case S_PAYMENT_COMPLETION:
            ret.paymentCompletion = 1;
            break;
        case S_CASH_ADVANCE:
            ret.cashAdvance = 1;
            break;
        case S_DEFFERED_PAYMENT:
            ret.deferredPayment = 1;
            break;
        case S_DEFFERED_PAYMENT_COMPLETION:
            ret.deferredPaymentCompletion = 1;
            break;
        case S_VOICE_AUTHORISATION:
            ret.voiceAuthorisation = 1;
            break;
        case S_CARDHOLDER_DETECTION:
            ret.cardholderDetection = 1;
            break;
        case S_CARD_VALIDITY_CHECK:
            ret.cardValidityCheck = 1;
            break;
        case S_NO_SHOW:
            ret.noShow = 1;
            break;
        default:
            break;
    }
    return ret;
}

static inline struct CombinationsListAndParametersEntry*
Copy_Combination_Lists_Entry(const struct CombinationsListAndParametersEntry* const r) {
    struct CombinationsListAndParametersEntry tmp = {
        .terminalAid = r->terminalAid,
        .kernelId = r->kernelId,
        .terminalTransactionQualifiers = acpptr(r->terminalTransactionQualifiers),
        .statusCheckSupportFlag = acpptr(r->statusCheckSupportFlag),
        .zeroAmountAllowedFlag = acpptr(r->zeroAmountAllowedFlag),
        .readerCtlessTransactionLimit = acpptr(r->readerCtlessTransactionLimit),
        .readerCtlessFloorLimit = acpptr(r->readerCtlessFloorLimit),
        .readerCvmRequiredLimit= acpptr(r->readerCvmRequiredLimit),
        .extendedSelectionSupported = acpptr(r->extendedSelectionSupported),
        .next = NULL
    };
    if (g_Ctd.TransactionAmountEntered) {
        tmp.statusCheckRequested = acpval(false);
        tmp.zeroAmount = acpval(false);
        tmp.ctlessApplicationNotAllowed = acpval(false);
        tmp.readerCtlessFloorLimitNotAllowed = acpval(false);
        tmp.readerCvmRequiredLimitExceeded = acpval(false);
    } else {
        tmp.statusCheckRequested = acpptr(r->statusCheckRequested);
        tmp.zeroAmount = acpptr(r->zeroAmount);
        tmp.ctlessApplicationNotAllowed = acpptr(r->ctlessApplicationNotAllowed);
        tmp.readerCtlessFloorLimitNotAllowed = acpptr(r->readerCtlessFloorLimitNotAllowed);
        tmp.readerCvmRequiredLimitExceeded = acpptr(r->readerCvmRequiredLimitExceeded);
    }
    return acpval(tmp);
}
