#pragma once

#include "utils.h"
#include "mem.h"
#include "bool.h"
#include "outcome.h"

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
  , PR_BAIL

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
  , N_CONF_ERROR
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
  , N_CHIP_ERROR
  , N_NO_PROFILE
  , N_FALLBACK_PROHIBITED
  , N_TECHNOLOGY_NOT_SUPPORTED

  , N_MAX
};

enum TransactionResult {
    T_NONE = N_MAX + 8273
  , T_ABORTED
  , T_NOT_SUPPORTED
  , T_APPROVED
  , T_PARTIALLY_APPROVED
  , T_VOICE_AUTHORISATION
  , T_PAYMENT_PART_ONLY
  , T_DECLINED

  , T_MAX
};

enum PACKED TransactionType {
    TRX_NONE = 0xFF
  , TRX_DEBIT_GOODS_AND_SERVICES = 0x00
  , TRX_DEBIT_CASH = 0x01
  , TRX_DEBIT_GOODS_AND_SERVICES_WITH_CASH_DISBURSEMENT = 0x09
  , TRX_CREDIT_RETURN = 0x20
};

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

  // Optional
  , E_PRINTER_STATUS              // No                      No

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
  , TER_INTERFACE_CONTRACT_VIOLATION

  , TER_MAX
};

enum CtlssIndicatorStatus {
    STATUS_NONE
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
    CRDHLDR_ACT_NONE = 0x00 // No change of the cardholder display, no-op
  , CRDHLDR_EMV_APPROVED = 0x03
  , CRDHLDR_EMV_VOICE_AUTH_REQUIRED = 0x04 // aka "Call your bank"
  , CRDHLDR_EMV_CARD_ERROR = 0x06
  , CRDHLDR_EMV_DECLINED = 0x07
  , CRDHLDR_EMV_INCORRECT_PIN = 0x0A
  , CRDHLDR_EMV_INSERT_CARD = 0x0B
  , CRDHLDR_EMV_PLEASE_WAIT = 0x0E
  , CRDHLDR_EMV_PROCESSING_ERROR = 0x0F
  , CRDHLDR_EMV_REMOVE_CARD = 0x10
  , CRDHLDR_EMV_USE_CHIP_READER = 0x11
  , CRDHLDR_EMV_USE_MAG_STRIPE = 0x12
  , CRDHLDR_EMV_TRY_AGAIN = 0x13
  , CRDHLDR_MSG_WELCOME = 0x14
  , CRDHLDR_MSG_PRESENT_CARD = 0x15
  , CRDHLDR_MSG_PROCESSING = 0x16
  , CRDHLDR_MSG_CARD_READ_OK_REMOVE_CARD = 0x17
  , CRDHLDR_MSG_PLEASE_INSERT_OR_SWIPE_CARD = 0x18
  , CRDHLDR_MSG_PLEASE_INSERT_ONE_CARD_ONLY = 0x19
  , CRDHLDR_MSG_APPROVED_PLEASE_SIGN = 0x1A
  , CRDHLDR_MSG_AUTHORISING_PLEASE_WAIT = 0x1B
  , CRDHLDR_MSG_INSERT_SWIPE_OR_TRY_ANOTHER_CARD = 0x1C
  , CRDHLDR_MSG_PLEASE_INSERT_CARD = 0x1D
  , CRDHLDR_ACT_CLEAR = 0x1E // Clear display
  , CRDHLDR_MSG_SEE_PHONE_FOR_INSTRUCTIONS = 0x20
  , CRDHLDR_MSG_PRESENT_CARD_AGAIN = 0x21
  , CRDHLDR_MSG_CARD_WRONG_WAY_OR_NO_CHIP = 0xC0
  , CRDHLDR_MSG_READ_ERROR = 0xC1
  , CRDHLDR_MSG_AMOUNT = 0xC2
  , CRDHLDR_MSG_MAX_AMOUNT = 0xC3
  , CRDHLDR_MSG_ENTER_PIN = 0xC4 // Special id, it has 3 wordings
  , CRDHLDR_MSG_ENTER = 0xC5
  , CRDHLDR_MSG_AMOUNT_AUTHORISED = 0xC6
  , CRDHLDR_MSG_LEFT_TO_BE_PAID = 0xC7
  , CRDHLDR_MSG_TRANSACTION_ABORTED = 0xC9
  , CRDHLDR_MSG_PAYMENT_APPROVED_CASHBACK_DECLINED = 0xD1
  , CRDHLDR_MSG_CHIP_ERROR_RE_ENTER_PIN = 0xD3
  , CRDHLDR_MSG_PRESENT_CARD_OR_USE_MAGSTRIPE = 0xD4
  , CRDHLDR_MSG_INSERT_OR_PRESENT_CARD = 0xD5
  , CRDHLDR_MSG_INSERT_OR_SWIPE_CARD = 0xD9
  , CRDHLDR_MSG_NO_PIN = 0xDA
  , CRDHLDR_MSG_DIFFERENT_CHOICE = 0xDB
  , CRDHLDR_MSG_CHOOSE_APPLICATION = 0xDC
  , CRDHLDR_MSG_AMOUNT_ESTIMATED = 0xDD
  , CRDHLDR_MSG_FINAL_AMOUNT = 0xDE
  , CRDHLDR_MSG_AMOUNT_INCREMENT = 0xDF
  , CRDHLDR_MSG_AMOUNT_DECREMENT = 0xE0
  , CRDHLDR_MSG_PRINTER_OUT_OF_ORDER = 0xE1
  , CRDHLDR_MSG_TIP = 0xE2
  , CRDHLDR_MSG_CASHBACK = 0xE3
  , CRDHLDR_MSG_PAYMENT = 0xE4
  , CRDHLDR_MSG_TOTAL = 0xE5

  /* Outside of nexo FAST spec */
  , CRDHLDR_MSG_REQUEST_SIGNATURE = 0x32
  , CRDHLDR_MSG_RECEIPT_PRINTING_FAILED = 0x33

  /* Extended messages */
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_OUTCOME = 0x80
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_RESTART = 0x81
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_COMPLETION = 0x82
  , CRDHLDR_SRC_DECLINE_DISPLAY_MESSAGE = 0x83
  , CRDHLDR_SRC_SELECTED_SERVICE = 0x84
  , CRDHLDR_SRC_CARDHOLDER_MESSAGE = 0x85
  , CRDHLDR_SRC_NOK_REASON = 0x86
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_OUTCOME_STATUS_ONLY = 0x87

  /* Sale system notification */
  , CRDHLDR_SSN_CARD_REMOVAL_REQUESTED = 0x90
  , CRDHLDR_SSN_CARD_REMOVED = 0x91
  , CRDHLDR_SSN_REQUEST_SIGNATURE = 0x92
  , CRDHLDR_SSN_RECEIPT_PRINTING_FAILED = 0x93
};

enum PACKED Kernel {
    KERNEL_NONE = 0x00
  , KERNEL_M = 0x3F
  , KERNEL_E = 0x3E
};

enum KernelMode {
    KERNEL_MODE_NONE
  , KERNEL_MODE_FULL
  , KERNEL_MODE_EXTRACT_PAN

  , KERNEL_MODE_MAX
};

enum PrintMessage {
    PRINT_MERCHANT_RECEIPT
  , PRINT_CARDHOLDER_RECEIPT
};

enum PACKED FallbackParameterMagneticStripe {
    FALLBACK_TRANSACTION_PROHIBITED = 0x00
  , FALLBACK_TRANSACTION_ALLOWED = 0x01
  , TRACK2_ONLY_PRODUCT = 0x02
};

enum PACKED CvmMagneticStripe {
    CVM_MSR_ONLINE_PIN = 0x01
  , CVM_MSR_SIGNATURE = 0x02
  , CVM_MSR_NO_CVM = 0x03
  , CVM_MSR_ACCORDING_TO_RANGE_OF_SERVICES = 0x04 // aka 'SIGNATURE or ONLINE PIN'
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
        unsigned char referralAllowed : 1; // Defined only in nexo flow
        unsigned char /* RFU */ : 6;

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

union TerminalCapabilities {
    uint8_t raw[3];
    struct {
        uint8_t signature: 1; // [2, 6]
    };
} /* 9F33 */;

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
    uint8_t raw[5];
    struct {
        uint8_t isDccAcceptorModeAllowed : 1;
        uint8_t isMerchantSignatureRequiredForApprovedRefund : 1;
        uint8_t performExceptionFileChecking : 1;
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

enum PACKED AuthorisationResponseCode {
    ARC_ONLINE_APPROVED = 0x00
  , ARC_UNABLE_TO_GO_ONLINE_OFFLINE_DECLINED = MULTICHAR('Z','3')
  , ARC_UNABLE_TO_GO_ONLINE_OFFLINE_AUTHORISED = MULTICHAR('Y','3')
  , ARC_OFFLINE_APPROVED = MULTICHAR('Y','1')
  , ARC_OFFLINE_DECLINED = MULTICHAR('Z','1')
  , ARC_NONE = 0xFF
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
        UI_VALUE_QUALIFIER_NONE
      , UI_VALUE_QUALIFIER_AMOUNT
      , UI_VALUE_QUALIFIER_BALANCE
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
    union ServiceCodeMs {
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
    enum TechnologySelected* TechnologyOfProfile; // WUT?

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
  , PRINTER_OPERATIONAL
};

#define TERMINAL_TYPE_ATTENDED(T)\
    ONEOF((T).operationalEnvironment, ATTENDED_ONLINE_ONLY, ATTENDED_OFFLINE_AND_ONLINE, ATTENDED_OFFLINE_ONLY)
#define TERMINAL_TYPE_UNATTENDED(T)\
    ONEOF((T).operationalEnvironment, UNATTENDED_ONLINE_ONLY, UNATTENDED_OFFLINE_AND_ONLINE, UNATTENDED_OFFLINE_ONLY)
#define TERMINAL_TYPE_ONLINE_ONLY(T)\
    ONEOF((T).operationalEnvironment, ATTENDED_ONLINE_ONLY, UNATTENDED_ONLINE_ONLY)
#define TERMINAL_TYPE_OFFLINE_ONLY(T)\
    ONEOF((T).operationalEnvironment, ATTENDED_OFFLINE_ONLY, UNATTENDED_OFFLINE_ONLY)
#define TERMINAL_TYPE_OFFLINE_WITH_ONLINE_CAPABILITY(T)\
    ONEOF((T).operationalEnvironment, ATTENDED_OFFLINE_AND_ONLINE, UNATTENDED_OFFLINE_AND_ONLINE)

union TerminalType {
    uint8_t b[1];

    union {
        struct {
            enum PACKED {
                OPERATED_BY_FINANCIAL_INSTITUTION = 0x1
              , OPERATED_BY_MERCHANT = 0x2
              , OPERATED_BY_CARDHOLDER = 0x3
            } operationalControl : 4;
            uint8_t : 4;
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
    bool IsCardInReader; // TODO: Consider making IsCardInReader an atomic variable

    // Service
    bool ApplicationInitialised;
    union ServiceSettings* SelectedServiceSettings;
    union ServiceStartEvents* SelectedServiceStartEvents;

    // Transaction
    union Amount TransactionAmount;
    bool TransactionAmountEntered;
    enum TransactionType TransactionType;
    enum TransactionResult TransactionResult;
    enum NokReason NokReason;
    enum ServiceId SelectedService;
    union Currency TransactionCurrency;
    enum AuthorisationResponseCode AuthorisationResponseCode;
    bool AttendantForcedTransactionOnline;
    char ReferenceData[35 + 1];
    bool FallbackFlag;
    unsigned char SelectedApplicationProfileNumber;
    union ApplicationProfileSettings* SelectedApplicationProfileSettings; // FIXME: Delete?

    // Online
    bool UnableToGoOnline;

    // EMV
    enum Kernel KernelId;
    enum KernelMode KernelMode;
    enum Technology TechnologySelected;
    union ProcessingStatus ProcessingStatus;
    bool ExceptionFileCheckPerformed;
    bool ExceptionFileMatch;
    bool Continue;
    bool ConfirmationByCard;
    bool WasPresentOneCardOnlyMessageDisplayed;
    unsigned char NumberOfRemainingChipTries;

    // Outcome
    enum Outcome Outcome;
    struct OutcomeParameters Out;

    // UI
    struct UiParameters UiParametersForOutcome;
    struct UiParameters UiParametersForRestart;
    struct UiParameters UiParametersForTrxCompletion;
    bool UiRequestPostponed;
    bool PrintCardholderReceipt;
    bool PrintMerchantReceipt;
    bool SignatureLine;
    bool SignatureLineMerchant;
    bool SignatureLineForVoiceAuthorisation;
    char DeclineDisplayMessage[40 + 1];

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
    bool TransactionConfirmedByCardholder;
    struct Track2 Track2;
    union ServiceCodeMs* ServiceCodeMs;
    const unsigned char (* Pan)[19];
    const struct Bid* SelectedBid;
    unsigned char PanMatchLength; // integer

    // Manual Entry
    bool PanEnteredManually;

    // Contactless
    struct CombinationsListAndParametersEntry* CombListWorkingTable;
    bool TimeoutIndicator;

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
    union TerminalCapabilities TerminalCapabilities;
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
    enum FallbackParameterMagneticStripe FallbackParameterMagneticStripe; //TODO: Move to AP
    enum CvmMagneticStripe CvmMagneticStripe; // TODO: Move to AP

    // Application Profile
    enum CardholderMessage CardholderInitialMessage;

    // IFR
    union EeaProcessSettings* EeaProcessSettings;
};

extern struct CurrentTransactionData g_Ctd;
extern struct NexoConfiguration g_Nexo;

const char* NokReason_tostring(enum NokReason n);
const char* PrintMessage_tostring(enum PrintMessage);
const char* ProcedureResult_tostring(enum ProcedureResult f);
const char* CardholderMessage_tostring(enum CardholderMessage m);
const char* TransactionResult_tostring(enum TransactionResult);
const char* ServiceId_tostring(enum ServiceId s);
struct small_string TerminalSettings_tostring(union TerminalSettings);
struct small_string ServiceStartEvent_tostring(union ServiceStartEvents);
void ctd_print(const struct CurrentTransactionData*);
bool isIssuerCountryExcludedForDcc(void);
union ConfiguredServices ServiceId_to_ConfiguredServices(enum ServiceId);
struct CombinationsListAndParametersEntry* Copy_Combination_Lists_Entry(const struct CombinationsListAndParametersEntry*);
