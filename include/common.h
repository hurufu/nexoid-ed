#pragma once

#include "utils.h"
#include "mem.h"
#include "bool.h"

#include <ptmalloc3.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define PACKED __attribute__(( __packed__ ))

#define MAX_CARDHOLDER_MESSAGES (6)

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
  , PR_MANUAL_ENTRY
  , PR_REINITIALISE
  , PR_NEW_EVENT
  , PR_RETRY_AFTER_CONTACTLESS
  , PR_FALLBACK

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
    N_NONE = PR_MAX + 2364
  , N_NOT_IMPLEMENTED
  , N_ORIGINAL_TRX_NOT_FOUND
  , N_TECHNICAL_ERROR
  , N_MISSING_DATA
  , N_NO_PERMISSION
  , N_CONFIGURATION_ERROR
  , N_AMOUNT_ERROR
  , N_KERNEL_ERROR
  , N_DATA_ERROR
  , N_NO_CARD_INSERTED
  , N_CANCELLED
  , N_ABORTED
  , N_TIMEOUT
  , N_CARD_MISSING
  , N_NO_PROFILE

  , N_MAX
};

enum Outcome {
    O_NONE = N_MAX + 9745
  , O_ONLINE_REQUEST
  , O_TRY_ANOTHER_INTERFACE
  , O_END_APPLICATION

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
// FIXME: Rename IdleEvent to NexoEvent, because it's not used in idle screen only
enum IdleEvent {                  // Service Start Event? // Technology Selection?
    // NEXO
    E_LANGUAGE_SELECTION = 0      // No                      No
  , E_CHOICE_OF_APPLICATION       // No                      Yes
  , E_SERVICE_SELECTION           // No                      No
  , E_ACQUIRER_PRESELECTION       // No                      No
  , E_CARDHOLDER_DETECTION        // Yes                     No
  , E_AMOUNT_ENTRY                // Yes                     No
  , E_CARD_INSERTED               // Yes                     Yes
  , E_CARD_SWIPED                 // Yes                     Yes
  , E_MANUAL_ENTRY                // Yes                     Yes
  , E_REFERENCE_ENTRY             // Yes                     No
  , E_ACCEPT                      // Yes                     No
  , E_ATTENDANT_FORCED_ONLINE     // No                      No
  , E_ADDITIONAL_TRANSACTION_DATA // No                      No
  , E_CARD_REMOVAL                // No                      Yes(?)
  , E_CANCEL                      // No                      Yes

  // Non Nexo
  , E_REBOOT_REQUESTED            // No                      No
  , E_TERMINATION_REQUESTED       // No                      No
  , E_SHUTDOWN_REQUESTED          // No                      No
  , E_NONE                        // No                      No(?)

  // Technology selection
  , E_TIMEOUT                     // No                      Yes
  , E_ONE_CTLS_CARD_ACTIVATED     // No                      Yes
  , E_CTLS_COLLISION              // No                      Yes

  , E_MAX                         // N/A                     N/A
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
        F,
        START_MAX
    } Start;
    unsigned char FieldOffRequest;
};

enum CtlssIndicatorStatus {
    STATUS_NONE = START_MAX
  , STATUS_NOT_READY
  , STATUS_IDLE
  , STATUS_READY_TO_READ
  , STATUS_PROCESSING
  , STATUS_CARD_READ_SUCCESSFULLY
  , STATUS_PROCESSING_ERROR

  , STATUS_MAX
};

enum PACKED Technology {
    TECH_NONE = 0x00
  , TECH_EMV_CHIP = 0x01
  , TECH_MAGNETIC_STRIPE = 0x02
  , TECH_MANUAL_ENTRY = 0x03
  , TECH_NON_EMV_CHIP = 0x04
  , TECH_FALLBACK = 0x05// To MSR
  , TECH_CONTACTLESS = 0x06

  , TECH_MAX
};

enum PACKED CardholderMessage {
    CRDHLDR_MSG_CARD_ERROR = 0x06
  , CRDHLDR_MSG_WELCOME = 0x14
  , CRDHLDR_MSG_NONE = 0x1E
  , CRDHLDR_MSG_CHOOSE_APPLICATION = 0xDC
  , CRDHLDR_MSG_PRINTER_OUT_OF_ORDER = 0xE1
};

enum Kernel {
    KERNEL_NONE = START_MAX + 209
  , KERNEL_M
};

struct HoldTime {
    uint8_t bcd[6];
};

union TerminalSettings {
    unsigned char raw[5];
    struct {
        unsigned char hasPreReadCombinedReader : 1;
        unsigned char hasPostReadCombinedReader : 1;
        unsigned char hasCombinedReader : 1;
        unsigned char hasMotorisedCombinedReader : 1;
        unsigned char allowedSupplementaryAmt : 1;
        unsigned char requiredSaleSystemAuthorisation : 1;
        unsigned char merchantReceiptPrintedFirst : 1;
        unsigned char confirmationByCardNotAllowedForMsr: 1;

        unsigned char allowedAttendantForcingTrxOnline : 1;
        unsigned char /* RFU */ : 7;

        unsigned char allowedLastTrxCancellation : 1;
        unsigned char useTrxLogForCancellation : 1;
        unsigned char allowedCancellationWihOnlineApprovalIfTrxLogIsNotUsed : 1;
        unsigned char allowedVoiceAuthForLastTrx : 1;
        unsigned char retrieveUpdatePreAuthFromTrxLog : 1;
        unsigned char /* RFU */ : 2;
        unsigned char retrieveVoiceAuthFromTrxLog : 1;

        unsigned char printApprovedCardholderReceipt : 1;
        unsigned char printDeclinedCardholderReceipt : 1;
        unsigned char printVoiceAuthCardholderReceipt : 1;
        unsigned char printAbortedCardholderReceipt : 1;
        unsigned char /* RFU */ : 1;
        unsigned char printDolOnApprovedAndAbortedAndVoiceAuthCardholderReceipt : 1;
        unsigned char printDolOnDeclinedAndAbortedCardholderReceipt : 1;
        unsigned char /* RFU */ : 1;

        unsigned char printApprovedMerchantReceipt : 1;
        unsigned char printDeclinedMerchantReceipt : 1;
        unsigned char printVoiceAuthMerchantReceipt : 1;
        unsigned char printAbortedMerchantReceipt : 1;
        unsigned char /* RFU */ : 1;
        unsigned char printDolOnApprovedAndAbortedMerchantReceipt : 1;
        unsigned char printDolOnDeclinedAndAbortedMerchantReceipt : 1;
        unsigned char /* RFU */ : 1;
    };
};

union AdditionalTerminalCapabilities {
    unsigned char raw[5];
    struct {
        struct TransactionTypeCapability {
            unsigned char cash : 1;
            unsigned char goods : 1;
            unsigned char services : 1;
            unsigned char cashback : 1;
            unsigned char inquiry : 1;
            unsigned char transfer : 1;
            unsigned char payment : 1;
            unsigned char administrative : 1;

            unsigned char cashDeposit : 1;
            unsigned char /* RFU */ : 1;
        } TransactionType;

        struct TransactionDataInputCapability {
            unsigned char numericKeys : 1;
            unsigned char alphabeticAndSpecialCharactersKeys : 1;
            unsigned char commandKeys : 1;
            unsigned char functionKeys : 1;
            unsigned char /* RFU */ : 4;
        } TerminalDataInput;

        struct TransactionDataOutputCapability {
            unsigned char printAttendant : 1;
            unsigned char printCardholder : 1;
            unsigned char displayAttendant : 1;
            unsigned char displayCardholder : 1;
            unsigned char /* RFU */ : 2;
            // ISO/IEC 8859
            unsigned char codeTable10 : 1;
            unsigned char codeTable9 : 1;

            unsigned char codeTable8 : 1;
            unsigned char codeTable7 : 1;
            unsigned char codeTable6 : 1;
            unsigned char codeTable5 : 1;
            unsigned char codeTable4 : 1;
            unsigned char codeTable3 : 1;
            unsigned char codeTable2 : 1;
            unsigned char codeTable1 : 1;
        } TerminalDataOutput;
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
        uint8_t contactChipHasPriority : 1;
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

// 5F2D
union LanguagePreference {
    char raw[8];
    // TODO: Use proper country code enum in LanguagePreference union
#   if 0
    union Country lang[4];
#   endif
};

struct UiParameters {
    enum CardholderMessage Id;
    enum CtlssIndicatorStatus Status;
    struct HoldTime HoldTime;
    union LanguagePreference* LanguagePreference; // Not used in nexo
    enum ValueQualifier {
        UI_VALUE_QUILIFIER_NONE
      , UI_VALUE_QUILIFIER_AMOUNT
      , UI_VALUE_QUILIFIER_BALANCE
    } ValueQualifier;
    union Amount Value;
    union Currency CurrencyCode;
};

// NOTE: Strings in Track2 aren't null terminated
// FIXME: Track2 struct isn't compliant with Nexo definition
struct Track2 {
    char pan[19];
    union {
        char full[4];
        struct {
            char year[2];
            char month[2];
        };
    } expiryDate;
    union {
        char raw[3]; // Same as ServiceCodeMs in the spec
        struct {
            enum PACKED {
                InternationalOk = '1'
              , InternationalUseIcWhereFeasible = '2'
              , NationalOnlyExceptUnderBilateralAgreement = '5'
              , NationalOnlyExceptUnderBilateralAgreementUseIcWhereFeasible = '6'
              , NoInterchangeExceptUnderBilateralAgreementClosedLoop = '7'
              , TestCard = '9'
            } interchangeRules;
            enum PACKED {
                NormalAuthorisation = '0'
              , ContactIssuerViaOnlineMeans = '2'
              , ContactIssuerViaOnlineMeansExceptUnderBilateralAgreement = '4'
            } authorisationProcessing;
            enum PACKED {
                NoRestrictionsPinRequired = '0'
              , NoRestrictions = '1'
              , GoodsAndServicesOnlyNoCash = '2'
              , AtmOnlyPinRequired = '3'
              , CashOnly = '4'
              , GoodsAndServicesOnlyNocashPinRequired = '5'
              , NoRestrictionsUsePinWhereFeasible = '6'
              , GoodsAndServicesOnlyNoCashUsePinWhereFeasible = '7'
            } rangeOfServices;
        };
    } serviceCode;
    struct {
        enum {
            DD_NONE,
            DD_PVKI,
            DD_PVV,
            DD_CVC,
            DD_CVV
        } type;
        union {
            char pvki;
            char pvv[4];
            char cvc[3];
            char cvv[3];
        };
    } discretionaryData;
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

struct TerminalListOfBid {
    struct Bid {
        uint8_t size;
        unsigned char value[16 + 1];
    } Bid;

    struct MatchingPattern {
        enum {
            MATCH_PREFIX
          , MATCH_RANGE
        } type;
        union {
            struct Prefix {
                uint8_t size;
                unsigned char value[19];
            } prefix;
            struct PrefixRange {
                uint8_t size;
                unsigned char value[19];
            } prefixRange;

        };
        struct MatchingPattern* next;
    } matchingPattern;

    struct TerminalListOfBid* next;
};

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
    enum TechnologySelected* TechnologyOfProfile;

    struct ApplicationProfileSelectionTableNonChip* next;
};

union ProcessingStatus {
    unsigned char raw[4];
    struct {
        unsigned char technologySelectionNonFallbackMode : 1;
        unsigned char buildingCandidateListUsingPse : 1;
        unsigned char buildingCandidateListUsingListOfAids : 1;
        unsigned char finalAppSelectionForEmv : 1;
        unsigned char appProfileSelectionForEmv : 1;
        unsigned char appInitialisationAndOdaMethodDeterminedForEmv : 1;
        unsigned char appInitialisationFromFirstDecodeAflEntryForEmv : 1;
        unsigned char initialOda: 1; // Offline Data Authentication

        unsigned char cardholderVerification: 1;
        unsigned char processingRestrictions: 1;
        unsigned char terminalRiskManagement: 1;
        unsigned char terminalActionAnalysis: 1;
        unsigned char firstGenerateAc: 1;
        unsigned char onlineRequestOutcome: 1;
        unsigned char terminalActionAnalysisUnableToGoOnline: 1;
        unsigned char issuerAuthentication: 1;

        unsigned char issuerScriptProcessingBefore2ndGenerateAc: 1;
        unsigned char secondGenerateAc: 1;
        unsigned char issuerScriptProcessingAfter2ndGenerateAc: 1;
        unsigned char transactionCompletionForEmvChip: 1;
        unsigned char technologySelectionFallbackMode: 1;
        unsigned char cardProductSelectionForNonChip: 1;
        unsigned char appProfileSelectionForNonChip: 1;
        unsigned char fullMagStripeOrManualEntry: 1;

        unsigned char cvmForMagStripe: 1;
        unsigned char onlineRequestOutcomeForMagStripeOrManualEntry: 1;
        unsigned char transactionCompletionForNonChip: 1;
        unsigned char transactionCompletionForCtlss: 1;
        unsigned char /* RFU */: 4;
    };
};

union EeaProcessSettings {
    unsigned char raw[2];
    struct {
        unsigned char upfrontButtonOnScreenSupported: 1;
    };
};

enum PrinterStatus {
    PRINTER_UNAVAILABLE
};

union TerminalType {
    uint8_t b[1];

    union {
        struct {
            enum PACKED {
                OPERATED_BY_FINANCIAL_INSTITUTION = 0x1
              , OPERATED_BY_MERCHANT = 0x2
              , OPERATED_BY_CARDHOLDER = 0x3
            } operationalControl : 4;
        };

        struct {
            uint8_t : 4;
            enum PACKED {
                ATTENDED_ONLINE_ONLY = 0x1
              , ATTENDED_OFFLINE_AND_ONLINE = 0x2
              , ATTENDED_OFFLINE_ONLY = 0x3
              , UNATTENDED_ONLINE_ONLY = 0x4
              , UNATTENDED_OFFLINE_AND_ONLINE = 0x5
              , UNATTENDED_OFFLINE_ONLY = 0x6

              /*
              , ATTENDED = 0x1
              , ATTENDED = 0x2
              , ATTENDED = 0x3

              , UNATTENDED = 0x4
              , UNATTENDED = 0x5
              , UNATTENDED = 0x6

              , ONLINE_ONLY = 0x1
              , ONLINE_ONLY = 0x4

              , OFFLINE_ONLY = 0x3
              , OFFLINE_ONLY = 0x6

              , OFFLINE_AND_ONLINE = 0x2
              , OFFLINE_AND_ONLINE = 0x5
              */
            } operationalEnvironment : 4;
        };

        enum PACKED {
            ATTENDED_ONLINE_ONLY_OPERATED_BY_FINANCIAL_INSTITUTION = 0x11
          , ATTENDED_OFFLINE_AND_ONLINE_OPERATED_BY_FINANCIAL_INSTITUTION = 0x12
          , ATTENDED_OFFLINE_ONLY_OPERATED_BY_FINANCIAL_INSTITUTION = 0x13
          , ATTENDED_ONLINE_ONLY_OPERATED_BY_MERCHANT = 0x21
          , ATTENDED_OFFLINE_AND_ONLINE_OPERATED_BY_MERCHANT = 0x22
          , ATTENDED_OFFLINE_ONLY_OPERATED_BY_MERCHANT = 0x23
          , ATTENDED_ONLINE_ONLY_OPERATED_BY_CARDHOLDER = 0x31
          , ATTENDED_OFFLINE_AND_ONLINE_OPERATED_BY_CARDHOLDER = 0x32
          , ATTENDED_OFFLINE_ONLY_OPERATED_BY_CARDHOLDER = 0x33

          , UNATTENDED_ONLINE_ONLY_OPERATED_BY_FINANCIAL_INSTITUTION = 0x14
          , UNATTENDED_OFFLINE_AND_ONLINE_OPERATED_BY_FINANCIAL_INSTITUTION = 0x15
          , UNATTENDED_OFFLINE_ONLY_OPERATED_BY_FINANCIAL_INSTITUTION = 0x16
          , UNATTENDED_ONLINE_ONLY_OPERATED_BY_MERCHANT = 0x24
          , UNATTENDED_OFFLINE_AND_ONLINE_OPERATED_BY_MERCHANT = 0x25
          , UNATTENDED_OFFLINE_ONLY_OPERATED_BY_MERCHANT = 0x26
          , UNATTENDED_ONLINE_ONLY_OPERATED_BY_CARDHOLDER = 0x34
          , UNATTENDED_OFFLINE_AND_ONLINE_OPERATED_BY_CARDHOLDER = 0x35
          , UNATTENDED_OFFLINE_ONLY_OPERATED_BY_CARDHOLDER = 0x36
        } e;
    };
};

struct CurrentTransactionData {
    // Operations
    bool AcquirerPreSelected;
    bool CardholderLanguageIsSelected;
    bool CardholderRequestedChoiceOfApplication;
    unsigned char PreSelectedAcquirerNumber;
    enum PrinterStatus PrinterStatus;

    // Service
    bool ApplicationInitialised;
    union ServiceSettings* SelectedServiceSettings;
    union ServiceStartEvents* SelectedServiceStartEvents;
    enum CardholderMessage CardholderInitialMessage;

    // Transaction
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
    bool FallbackFlag;
    unsigned char SelectedApplicationProfileNumber;

    // EMV
    enum Kernel KernelId;
    enum Technology TechnologySelected;
    enum Outcome Outcome; // FIXME: Outcome shall be an optional struct
    union ProcessingStatus ProcessingStatus;
    bool ExceptionFileCheckPerformed;
    bool Continue;
    bool ConfirmationByCard;
    bool WasPresentOneCardOnlyMessageDisplayed;
    unsigned char NumberOfRemainingChipTries;

    // UI
    struct UiParameters* UiParametersForOutcome;
    struct UiParameters* UiParametersForRestart;
    struct UiParameters* UiParametersForTrxCompletion;
    bool UiRequestPostponed;

    // Cashback
    union Amount CashbackAmount;

    // Card data
    union Country* IssuerCountry;
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

    // Magnetic stripe
    bool InvalidSwipeOccured;
    struct Track2 Track2;
    const unsigned char (* Pan)[19];
    const struct Bid* SelectedBid;
    unsigned char PanMatchLength; // integer

    // Manual Entry
    bool PanEnteredManually;

    // Contactless
    struct CombinationsListAndParametersEntry* CombListWorkingTable;

    // Yes, there are actually two variables to control contactless in spec
    bool NoContactlessAllowed;
    bool ContactlessAllowed;

    // IFR
    bool ShowUpfrontButton;
};

struct NexoConfiguration {
    // Terminal configuration
    union TerminalType TerminalType;
    union TerminalSettings TerminalSettings;
    union AdditionalTerminalCapabilities AdditionalTerminalCapabilities;

    // EMV configuration
    unsigned char MaxNumberOfChipTries;

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

    // MSR
    struct TerminalListOfBid* TerminalListOfBid;
    struct ApplicationProfileSelectionTableNonChip* ApplicationProfileSelectionTableNonChip;

    // IFR
    union EeaProcessSettings* EeaProcessSettings;
};

extern struct CurrentTransactionData g_Ctd;
extern struct NexoConfiguration g_Nexo;

const char* ProcedureResult_tostring(enum ProcedureResult f);
const char* CardholderMessage_tostring(const enum CardholderMessage m);
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
