#ifndef TYPES_H
#define TYPES_H

#include "utils.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdalign.h>

#define MAX_CARDHOLDER_MESSAGES (6)

/* Data types defintions
 *
 * TODO: This file should be generated from the ASN.1 source
// FIXME: All bitmasks are little endian only
 */

// FIXME: An experiment with using implict null byte for constant-width strings
#define STRING_SENTINEL struct { char : 1; }

typedef uint8_t bcd_t;

typedef uintmax_t tlv_tag_t;
typedef size_t tlv_size_t;

union PACKED bcd {
    uint8_t raw;
    struct PACKED {
        uint8_t low: 4;
        uint8_t high: 4;
    };
};

union PACKED zbcd {
    char raw;
    struct {
        uint8_t v : 4;
        uint8_t p : 4;
    };
};

struct n6 {
    uint8_t bcd[6];
};

// Packed BCD max n12 padded with zeros to the right
struct bcd2 {
    bcd_t v[2];
};

struct bcd3 {
    bcd_t v[3];
};

struct bcd4 {
    bcd_t v[4];
};

// Packed BCD max n12 padded with 0xF to the left
struct cbcd6 {
    bcd_t v[6];
};

struct cbcd_6 {
    uint8_t l;
    struct cbcd6 v;
};

union bcd6 {
    bcd_t v[6];
    int64_t i;
    uint64_t u;
};

struct ans15 {
    char v[15];
};

struct ans_16 {
    uint8_t l;
    char v[16];
};

struct ans_34 {
    uint8_t l;
    char v[34];
};

struct ans_35 {
    uint8_t l;
    char v[35];
};

struct as_34 {
    uint8_t l;
    char v[34];
};

struct string5 {
    char s[5];
    STRING_SENTINEL;
};

struct string6 {
    char s[6];
    STRING_SENTINEL;
};

struct string16 {
    char s[16];
    STRING_SENTINEL;
};

struct string8 {
    char s[8];
    STRING_SENTINEL;
};

struct binary {
    size_t l;
    uint8_t r[1024];
};

union binary2 {
    uint8_t r[2];
    uint16_t u;
};

union yymmdd {
    struct bcd3 bcd;
    struct PACKED {
        bcd_t y;
        bcd_t m;
        bcd_t d;
    };
    uint32_t u;
};

// FIXME: CAST_TAG() works only with 2-byte tags
#define CAST_TAG(TagV) \
    (TagV & (0xFF << 0)) << 8 | \
    (TagV & (0xFF << 8)) >> 8

// EMV - Data elements defined by EMV or ISO and used by nexo-FAST (section 13.1)
// ENU - Data elements defined by EMV and not used by nexo-FAST (section 13.2)
// NXO - Data elements defined by nexo-FAST for use outside of kernel processing (section 13.3)
// NXE - Data elements defined by nexo-FAST for use in kernel E (section 13.4)
// NNA - Not known, not applicable
// NIS - Defined by nIS only

enum Tag {
    // Unique Application Profile ID:
    T_NNA_PROFILE_NUMBER = CAST_TAG(0xDF19)
  , T_NNA_ACQUIRER_NUMBER = CAST_TAG(0xDF1B)

    // Application Profile Parameters:
  , T_NIS_APPLICATION_PROFILE = CAST_TAG(0xE6)
  , T_EMV_ACQUIRER_IDENTIFIER = CAST_TAG(0x9F10)
  , T_NNA_ADDITIONAL_DATA_ELEMENTS = CAST_TAG(0xEF)
  , T_NXO_ADDITIONAL_RESTRICTIONS_OF_FORCED_ACCEPTANCE = CAST_TAG(0xDF26)
  , T_EMV_ADDITIONAL_TERMINAL_CAPABILITIES = CAST_TAG(0x9F40)
  , T_EMV_TERMINAL_COUNTRY_CODE = CAST_TAG(0x9F1A)
  , T_NXO_APPLICATION_LABEL_DEFAULT = CAST_TAG(0xDF41)
  , T_NXO_APPLICATION_PROFILE_SETTINGS = CAST_TAG(0xDF27)
  , T_NXO_APPLICATION_PROFILE_SETINGS_FOR_CANCELLATION = CAST_TAG(0xDF28)
  , T_NXO_CASH_ADVANCE_MAXIMUM_AMOUNT = CAST_TAG(0xDF29)
  , T_EMV_CVM_CAPABILITY_CVM_REQUIRED = CAST_TAG(0xDF8118)
  , T_EMV_CVM_CAPABILITY_NO_CVM_REQUIRED = CAST_TAG(0xDF8119)
  , T_EMV_DDOL = CAST_TAG(0xDF1A)
  , T_EMV_HOLD_TIME_VALUE = CAST_TAG(0xDF8130)
  , T_EMV_KERNEL_2_CONFIGURATION = CAST_TAG(0xDF811B)
  , T_EMV_KERNEL_4_READER_CAPABILITIES = CAST_TAG(0x9F6D)
  , T_EMV_TERMINAL_CAPABILITIES = CAST_TAG(0x9F33)
  , T_NXO_CASHBACK_MAXIMUM_AMOUNT = CAST_TAG(0xDF2A)
  , T_NXO_REFUND_PROTECTION_AMOUNT = CAST_TAG(0xDF3C)
  , T_NXO_CVM_MAGNETIC_STRIPE = CAST_TAG(0xDF42)
  , T_NXO_CARD_VALIDITY_CHECK_DEFAULT_AMOUNT = CAST_TAG(0xDF58)

  // Chip card
  , T_EMV_APPLICATION_INTERCHANGE_PROFILE = CAST_TAG(0x82) // a.k.a. AIP
};

union PACKED TagExpanded {
    uint8_t raw[sizeof(tlv_tag_t)];
    tlv_tag_t i;
    enum Tag e;
    struct PACKED {
        union PACKED {
            uint8_t head;
            struct PACKED {
                uint8_t nmbr : 5;
                uint8_t constructed : 1;
                enum {
                    TLV_CLASS_UNIVERSAL = 0b00,
                    TLV_CLASS_APPLICATION = 0b01,
                    TLV_CLASS_CONTEXT_SPECIFIC = 0b10,
                    TLV_CLASS_PRIVATE = 0b11
                } type : 2;
            };
        };
        union PACKED {
            uint8_t c;
            struct PACKED {
                uint8_t value : 7;
                uint8_t next : 1;
            } v;
        } tail[sizeof(tlv_tag_t) - sizeof(uint8_t)];
    };
};


enum PACKED IssuerCodeTableIndex {
    ISO_CODE_TABLE_1 = 0x01 // ISO 8589-1
};

// Kernel ID
// [DF38]
enum PACKED Kernel {
    KERNEL_NONE = 0x00
  , KERNEL_C1 = 0x01
  , KERNEL_C2 = 0x02
  , KERNEL_C3 = 0x03
  , KERNEL_C4 = 0x04
  , KERNEL_C5 = 0x05
  , KERNEL_C6 = 0x06
  , KERNEL_C7 = 0x07
  , KERNEL_M = 0x3F
  , KERNEL_E = 0x3E

  // May have size: 1 or 3~8
};

struct Rid {
    uint8_t v[5];
};

struct Aid {
    size_t l_raw;
    union {
        uint8_t raw[16];
        struct {
            struct Rid rid;
            uint8_t pix[];
        };
    };
};

// C2

union Kernel2Configuration {
    uint8_t raw[1];
    struct {
/*1-3*/ uint8_t /* RFU */ : 3;
/*4*/   uint8_t /* Reserved for Payment System */ : 1;
/*5*/   uint8_t relayResistanceProtocolSupported : 1;
/*6*/   uint8_t onDeviceCvmSupported : 1;
/*7*/   uint8_t ctlsEmvModeNotSupported : 1;
/*8*/   uint8_t ctlsMsModeNotSupported : 1;
    };
};


// C4

union Kernel4ReaderCapabilities {
    uint8_t raw[1];
};

union ApplicationPriorityIndicator {
    struct {
        uint8_t priority : 4;
        uint8_t /* RFU */ : 3;
        uint8_t cardholderConfirmationRequired : 1; // EMV Book 1 table 48
    };
    struct {
        enum PACKED {
            NO_PRIORITY = 0
        } e : 4;
    };
    uint8_t u;
};

struct CandidateApplication {
    union ApplicationPriorityIndicator ApplicationPriorityIndicator; // {61|A5}.87
    struct string16 ApplicationLabel; // {61|A5}.50
    struct string16 ApplicationPreferredName; // {61|A5}.9F12
    enum IssuerCodeTableIndex IssuerCodeTableIndex; // A5.9F11
    uint8_t EeaProductIdentification[5]; // DF51
    uint8_t TerminalPriorityIndicator; // -

    union {
        // If List of AID Selection
        struct {
            // Dedicated File (DF) Name
            struct Aid DfName; // 6F.84
        };

        // If PSE Selection
        struct {
            // Application Identifier (AID) - Card (ADF Name)
            struct Aid AdfName; // 61.4F
            enum Kernel KernelId;
            struct Aid TerminalAid;
            struct ExtendedAid* ExtendedAid;
        };
    };
};

struct CandidateList {
    size_t l_entry;
    struct CandidateApplication entry[100];
};

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

enum PACKED CvmConditionCode {
    CVM_IF_ALWAYS = 0x00,
    CVM_IF_UNATTENDED_CASH = 0x01,
    CVM_IF_NO_CASH = 0x02, // If not unattended cash and not manual cash and not purchase with cashback
    CVM_IF_SUPPORTED = 0x03,
    CVM_IF_MANUAL_CASH = 0x04,
    CVM_IF_PURCHASE_WITH_CASHBACK = 0x05,
    CVM_IF_TRX_IS_IN_APP_CURRENCY_AND_UNDER_X = 0x06,
    CVM_IF_TRX_IS_IN_APP_CURRENCY_AND_OVER_X = 0x07,
    CVM_IF_TRX_IS_IN_APP_CURRENCY_AND_UNDER_Y = 0x08,
    CVM_IF_TRX_IS_IN_APP_CURRENCY_AND_OVER_Y = 0x09,
    // 0x0A~0x7F - RFU
    // 0x80~0xFF - Reserved for use by individual payment systems
};

// TODO: Clean up naming, make this header a complete documentation of EMV status codes
//
// Prefixes:
//
//   I_* - informational
//   W_* - warning
//   E_* - error
//   S_* - security
//   X_* - any

union EmvStatus {
    uint8_t raw[2];
    struct {
        enum PACKED {
            X_APPLICATION_RELATED_STATUS = 0x9
          , X_OTHER_STATUS = 0x6
        } _status: 4;
    };
    struct {
        enum PACKED {
            E_CLASS_NOT_SUPPORTED = 0x60
          , I_RESPONSE_BYTES_STILL_AVAILABLE = 0x61
          , W_STATE_OF_NON_VOLATILE_MEMORY_UNCHANGED = 0x62
          , W_STATE_OF_NON_VOLATILE_MEMORY_CHANGED = 0x63
          , E_STATE_OF_NON_VOLATILE_MEMORY_UNCHANGED = 0x64
          , E_STATE_OF_NON_VOLATILE_MEMORY_CHANGED = 0x65
          , S_SECURITY = 0x66
          , E_PARSE_ERROR = 0x67
          , E_FUNCTIONS_IN_CLA_NOT_SUPPORTED = 0x68
          , E_COMMAND_NOT_ALLOWED = 0x69
          , E_WRONG_PARAMETER = 0x6A
          , E_WRONG_PARAMETER_CONTINUED = 0x6B
          , E_WRONG_LENGTH_LE = 0x6C
          , E_INSTRUCTION_CODE_ERROR = 0x6D
          , E_NOT_SUPPORTED = 0x6E
          , E_INTERNAL_EXCEPTION = 0x6F
          , X_INFORMATIONAL = 0x90
        } status;
        uint8_t qualifier;
    };
    enum PACKED {
        W_NVRM_NOT_CHANGED_NO_INFORMATION_GIVEN = MULTICHAR(0x62, 0x00)
      , W_SELECTED_FILE_INVALIDATED = MULTICHAR(0x62, 0x83)
      , W_PART_OF_RETURNED_DATA_MAY_BE_CORRUPTED = MULTICHAR(0x62, 0x81)
      , W_VERIFY_FAILED_NO_TRIES_LEFT = MULTICHAR(0x63, 0xC0)
      , W_VERIFY_FAILED_1_TRY_LEFT = MULTICHAR(0x63, 0xC1)
      , W_VERIFY_FAILED_2_TRIES_LEFT = MULTICHAR(0x63, 0xC2)
      , W_VERIFY_FAILED_3_TRIES_LEFT = MULTICHAR(0x63, 0xC3)
      , W_VERIFY_FAILED_4_TRIES_LEFT = MULTICHAR(0x63, 0xC4)
      , W_VERIFY_FAILED_5_TRIES_LEFT = MULTICHAR(0x63, 0xC5)
      , W_VERIFY_FAILED_6_TRIES_LEFT = MULTICHAR(0x63, 0xC6)
      , W_VERIFY_FAILED_7_TRIES_LEFT = MULTICHAR(0x63, 0xC7)
      , W_VERIFY_FAILED_8_TRIES_LEFT = MULTICHAR(0x63, 0xC8)
      , W_VERIFY_FAILED_9_TRIES_LEFT = MULTICHAR(0x63, 0xC9)
      , W_VERIFY_FAILED_10_TRIES_LEFT = MULTICHAR(0x63, 0xCA)
      , W_VERIFY_FAILED_11_TRIES_LEFT = MULTICHAR(0x63, 0xCB)
      , W_VERIFY_FAILED_12_TRIES_LEFT = MULTICHAR(0x63, 0xCC)
      , W_VERIFY_FAILED_13_TRIES_LEFT = MULTICHAR(0x63, 0xCD)
      , W_VERIFY_FAILED_14_TRIES_LEFT = MULTICHAR(0x63, 0xCE)
      , W_VERIFY_FAILED_15_TRIES_LEFT = MULTICHAR(0x63, 0xCF)
      , E_AUTHENTICATION_METHOD_BLOCKED = MULTICHAR(0x69, 0x83)
      , E_REFERENCED_DATA_REVERSIBLY_BLOCKED = MULTICHAR(0x69, 0x84) // Invalidated
      , E_CONDITIONS_OF_USE_NOT_SATISFIED = MULTICHAR(0x69, 0x85)
      , E_FUNCTION_NOT_SUPPORTED = MULTICHAR(0x6A, 0x81)
      , I_COMMAND_OK = MULTICHAR(0x90, 0x00)
    } e;
};

enum PinType {
    PIN_NONE
  , PIN_ONLINE
  , PIN_OFFLINE
};

// nexo-FAST v.3.2, section 13.1.13
// EMV v.4.3 Book 3, section 10.2
// [94]
struct PACKED ApplicationFileLocator {
    size_t raw_size;
    union {
        uint8_t raw[252];
        struct ApplicationFileLocatorEntry {
            uint8_t zero : 3;
            uint8_t sfi : 5;
            uint8_t firstRecordNumber;
            uint8_t lastRecordNumber;
            uint8_t numberOfOdaAuthenticatedRecords;
        } a[252 / 4];
    };
};

// nexo-FAST v.3.2, section 13.1.16
// EMV v.4.3 Book 3, table 37
// [82]
union PACKED ApplicationInterchangeProfile {
    uint8_t a[2];
    struct {
        uint8_t cdaSupported : 1;
        uint8_t /* RFU */ : 1;
        uint8_t issuerAuthenticationIsSupported : 1; // aka EXTERNAL AUTHENTICATE is supported
        uint8_t terminalRiskManagementIsToBePerformed : 1;
        uint8_t cardholderVerificationIsSupported : 1;
        uint8_t ddaSupported : 1;
        uint8_t sdaSupported : 1;
        uint8_t /* RFU */ : 1;

        uint8_t /* RFU */ : 7;
        uint8_t /* Reserved for use by the EMV Contactless Specifications */ : 1;
    };
};

// nexo-FAST v.3.2, section 13.1.26
// EMV v.4.3 Book 3, annex C3
// [9F07]
union PACKED ApplicationUsageControl {
    uint8_t a[2];
    struct {
        uint8_t validAtTerminalsOtherThanAtms : 1;
        uint8_t validAtAtms : 1;
        uint8_t validForInternationalServices : 1;
        uint8_t validForDomesticServices : 1;
        uint8_t validForInternationalGoods : 1;
        uint8_t validForDomesticGoods : 1;
        uint8_t validForInternationalCash : 1;
        uint8_t validForDomesticCash : 1;

        uint8_t /* RFU */ : 6;
        uint8_t validForInternationalCashback : 1;
        uint8_t validForDomesticCashback : 1;
    };
};

// Custom tag, not defined anywhere
union PACKED ApplicationProcurementControl {
    uint8_t a;
    struct {
        uint8_t /* RFU */ : 4;
        uint8_t services : 1;
        uint8_t goods : 1;
        uint8_t cash : 1;
        uint8_t cashback : 1;
    };
};

// Custom tag, not defined anywhere
union PACKED ApplicationLocationControl {
    uint8_t a;
    struct {
        uint8_t /* RFU */ : 6;
        uint8_t otherThenAtm : 1;
        uint8_t atm : 1;
    };
};

// Custom tag, not defined anywhere
union PACKED ApplicationContextControl {
    uint8_t a[3];
    struct {
        union ApplicationLocationControl location;
        union ApplicationProcurementControl international;
        union ApplicationProcurementControl domestic;
    };
};

// EMV Book 3 v.4.3, section 6.5.12.2
union PACKED PlainTextPinBlock {
    uint8_t raw[8];
    struct {
        struct {
            uint8_t length : 4;
            enum PACKED {
                PIN_BLOCK_CONTROL = 0x2
            } control : 4;
        };
        struct cbcd6 pin;
        uint8_t padding[1];
    };
};

union PinBlock {
    union PlainTextPinBlock* offlinePinBlock;
    void* encipheredPinData;
};

union CountryCode {
    struct bcd2 bcd;
    uint16_t u;
};

struct CardData {
    /** @{ */
    /** Members populated with raw or parsed card responses */
    union EmvStatus sw1Sw2;
    struct FileControlInformation* fci;
    struct ResponseMessageTemplate* responseMessageTemplate;
    struct ReadRecordResponseMessageTemplate* readRecordResponeMessageTemplate;
    struct ResponseData responseData;
    /** @} */
    bool responseDataParsed; // non-NEXO

    struct string16 applicationLabel;
    union ApplicationPriorityIndicator* applicationPriorityIndicator;
    struct Dol* pdol;
    struct TerminalSupportedLanguageList* languagePreference;
    enum IssuerCodeTableIndex* issuerCodeTableIndex;
    struct string16* applicationPreferredName;
    struct ApplicationFileLocator afl;
    struct StaticDataAuthenticationTagList* staticDataAuthenticationTagList;
    union ApplicationInterchangeProfile aip;
    struct CvmList* cvmList;
    union CurrencyCode* applicationCurrencyCode;
    union binary2* applicationVersionNumber_Card; // 0x9F08

    // [84]
    struct Aid dfName; // FIXME: Fix type

    // [9F07]
    union ApplicationUsageControl* auc;

    // [5F28]
    union CountryCode* issuerCountryCode;

    // [5F25]
    union yymmdd* applicationEffectiveDate;

    // [5F24]
    union yymmdd* applicationExpirationDate;

    // [5F34]
    union bcd* panSequenceNumber;

    // [9F17]
    uint8_t* pinTryCounter;

    // [9F14]
    uint8_t* lcol; // Lower Consecutive Offline Limit

    // [9F23]
    uint8_t* ucol; // Upper Consecutive Offline Limit

    // [9F0D]
    union TerminalVerificationResults* iacDefault;

    // [9F0E]
    union TerminalVerificationResults* iacDenial;

    // [9F0F]
    union TerminalVerificationResults* iacOnline;

    // [-]
    // NEXO: Tag [99] is not used by nexo-FAST
    union PinBlock pinData;

    union PlainTextPinBlock* offlinePinBlock;
    void* encipheredPinData;

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

/** Container for card data retrieved during "App, Kernel, Profile Selection".
 *
 *  NEXO: This struct isn't explicitly defined by nexo. Rationale, in nexo they
 *  don't distinguish card data container for App Selection and for Kernel
 *  Processing, but it's implied that they are different in Kernel Activation,
 *  when they copy all card data to Kernel Data as part of Kernel Transaction
 *  Data, and don't use common shared data holder.
 *
 *  nexo-FAST v.3.2, section 3.3, section 13.1
 */
struct EntryPointData {
};

enum TmsContactLevel {
    CALL_TMS_NONE
  , CALL_TMS_ASAP
  , CALL_TMS_CRITICAL
  , CALL_TMS_DATE_TIME
};

enum ProcedureResult {
    PR_UNINITIALISED = 239
  , PR_NOT_IMPLEMENTED
  , PR_INTERNAL_INCONSISTENCY
  , PR_REBOOT
  , PR_TERMINATE
  , PR_SHUTDOWN
  , PR_STARTUP_SEQUENCE
  , PR_CONTACT_TMS
  , PR_BAIL

  , PR_OK
  , PR_NOK
  , PR_NON_EMV
  , PR_TAP_AGAIN
  , PR_END_APPLICATION
  , PR_REFERENCE_ENTRY
  , PR_ACCEPT
  , PR_FOUND
  , PR_NOT_FOUND
  , PR_SUCCESSFUL
  , PR_NOT_SUCCESSFUL
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
  , PR_PSE_UNSUCCESSFUL
  , PR_A // FIXME: Use better name
  , PR_B // FIXME: Use better name
  , PR_C // FIXME: Use better name
  , PR_D // FIXME: Use better name
  , PR_E // FIXME: Use better name
  , PR_PARTIAL_MATCH
  , PR_EXACT_MATCH
  , PR_SKIP

  , PR_CVM_APPLICABLE
  , PR_CVM_NOT_APPLICABLE
  , PR_CVM_SUCCESSFUL
  , PR_CVM_UNSUCCESSFUL
  , PR_CVM_SUPPORTED
  , PR_CVM_NOT_SUPPORTED
  , PR_CVM_RETRY

  , PR_MAX
};

enum ProcedureResultOk {
    PR1_OK
  , PR1_NOK
};

enum ProcedureResultDone {
    PR2_DONE
  , PR2_NOK
};

enum ProcedureResultBinaryMatch {
    PR3_MATCH
  , PR3_NO_MATCH
};

enum ProcedureResultMatch {
    PR4_EXACT_MATCH
  , PR4_PARTIAL_MATCH
  , PR4_NO_MATCH
};

enum PACKED ServiceId {
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
};

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
  , N_GPO6985 // Aka "Conditions of use not satisfied"
  , N_CARD_BLOCKED
  , N_EMPTY_LIST

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
  , TRX_DEBIT_ADJUSTMENT = 0x02 // Not defined in nexo
  , TRX_DEBIT_GOODS_AND_SERVICES_WITH_CASH_DISBURSEMENT = 0x09
  , TRX_CREDIT_RETURN = 0x20
  , TRX_AVAILABLE_FUNDS_INQUIRY = 0x30
  , TRX_BALANCE_INQUIRY = 0x31
  , TRX_PAYMENT_FROM_ACCOUNT = 0x50
  , TRX_PAYMENT_TO_ACCOUNT = 0x53
  , TRX_MOBILE_TOPUP = 0x57
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
  , TER_INTERNAL_ERROR

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
  , CRDHLDR_MSG_TERMINAL_MANAGMENT_IN_PROGRESS = 0x34
  , CRDHLDR_MSG_FORCE_TRANSACTION_APPROVAL = 0x35

  /* Extended messages */
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_OUTCOME = 0x80
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_RESTART = 0x81
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_COMPLETION = 0x82
  , CRDHLDR_SRC_DECLINE_DISPLAY_MESSAGE = 0x83
  , CRDHLDR_SRC_SELECTED_SERVICE = 0x84
  , CRDHLDR_SRC_CARDHOLDER_MESSAGE = 0x85
  , CRDHLDR_SRC_NOK_REASON = 0x86
  , CRDHLDR_SRC_UI_PARAMETERS_FOR_OUTCOME_STATUS_ONLY = 0x87
  , CRDHLDR_SRC_APPLICATION_LABEL_DISPLAYED = 0x88
  , CRDHLDR_SRC_PAYMENT_AMOUNT = 0x89
  , CRDHLDR_SRC_COMMAND_KEY_ENTER_LABEL = 0x8A
  , CRDHLDR_SRC_TRX_CURRENCY_ALPHA3 = 0x8B
  , CRDHLDR_SRC_TRX_AMOUNT = 0x8C
  , CRDHLDR_SRC_COMMAND_KEY_CHANGE_APPLICATION_LABEL = 0x8D
  , CRDHLDR_SRC_CASHBACK_AMOUNT = 0x8E
  , CRDHLDR_SRC_SUPPLEMENTARY_AMOUNT = 0x8F
  , CRDHLDR_SRC_COMMAND_KEY_PIN_BYPASS_LABEL = 0x90

  /* Sale system notification */
  , CRDHLDR_SSN_CARD_REMOVAL_REQUESTED = 0xA0
  , CRDHLDR_SSN_CARD_REMOVED = 0xA1
  , CRDHLDR_SSN_REQUEST_SIGNATURE = 0xA2
  , CRDHLDR_SSN_RECEIPT_PRINTING_FAILED = 0xA3
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

union ReceiptSettings {
    uint8_t raw[1];
    struct {
        uint8_t printApproved : 1;
        uint8_t printDeclined : 1;
        uint8_t printVoiceAuth : 1;
        uint8_t printAborted : 1;
        uint8_t isMerchantSignatureRequiredForApprovedRefund : 1; // Only for ATC[4,4]
        uint8_t printDolOnApprovedAndAbortedAndVoiceAuth : 1;
        uint8_t printDolOnDeclinedAndAborted : 1;
        uint8_t specificPanProcessingForEmvChip : 1; // Only for ATC[5,1]
    };
};

union TerminalSettings {
    unsigned char raw[5];
    struct PACKED {
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

        union ReceiptSettings cardholderReceipt;
        union ReceiptSettings merchantReceipt;
    };
};

// nexo FAST v.3.2, section 13.1.136
// EMV v.4.3 Book 4, annex A2
union TerminalCapabilities {
    uint8_t raw[3];
    struct {
        struct {
            uint8_t manualKeyEntry: 1;
            uint8_t magneticStripe: 1;
            uint8_t icWithContacts: 1;
            uint8_t /* RFU */: 5;
        } cardDataInputCapability;

        struct {
            uint8_t /* RFU */: 3;
            uint8_t noCvmRequired: 1;
            uint8_t encipheredPinForOfflineVerification: 1;
            uint8_t signature: 1; // [2, 6]
            uint8_t encipheredPinForOnlineVerification: 1;
            uint8_t plainTextPinForIccVerification: 1;
        } cvmCapability;

        struct {
            uint8_t /* RFU */: 3;
            uint8_t cda: 1;
            uint8_t /* RFU */: 1;
            uint8_t cardCapture: 1;
            uint8_t dda: 1;
            uint8_t sda: 1;
        } securityCapability;
    };
} /* 9F33 */;

union ServiceStartEvents {
    uint8_t raw[1];
    uint8_t u;
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
    uint16_t u;
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
        uint8_t crdhlrConfirmationByCardNotAllowed : 1;
        uint8_t crdhlrConfirmationAlwaysRequired : 1;
        uint8_t preauthTrxAmountRequired : 1;
        uint8_t /* RFU */ : 3;
    };
};

struct SearchLogCriteria {
    bool* onlyLastTransaction;
    bool* mostRecent;
    bool* closed;
    bool* cancellable;

    char (* pan)[19]; // FIXME: Use proper type for PAN
    struct ans_35* referenceData;

    struct SlcServiceId {
        size_t s;
        enum ServiceId v[];
    }* sid;

    struct SlcTransactionResult {
        size_t s;
        enum TransactionResult v[];
    }* trxResult;
};

struct small_string {
    char hex[sizeof(int)];
};

/** Transaction log search results
 *
 * nexo-FAST, v.3.2, section 13.3.114
 */
struct SearchTransactionResult {
    // [DF01]
    union bcd entryReference;

    // [DF02]
    enum ServiceId selectedService;

    // [DF03]
    union bcd6 transactionAmount;

    // [DF04]
    union yymmdd transactionDate;

    // [DF05]
    // transactionTime;

    // [DF06]
    enum TransactionResult transactionResult;

    // [DF07]
    // panMasked;

    // [DF08]
    // * panSequenceNumber;

    // [DF09]
    // * authorisationCode;

    // [DF0A]
    // * preauthorisationValidityNumberOfDays;

    // [DF0B]
    bool* cancellationHasToBeOnline;

    // [DF0C]
    bcd_t profileNumber;

    // [DF0D]
    bool* entryExpired;

    // [DF56]
    union bcd6* updatePreAuthTotalAmount;
};

/* NEXO: In the spec tag value isn't specified for this struct, but it's
 * actually needed, because this struct is required to be shared between FAST
 * and HAP.
 *
 *  TODO: Specify globally unique tag number
 */
struct SearchTransactionResultList {
    struct SearchTransactionResult v;
    struct SearchTransactionResultList* next;
};

enum PACKED CountryAlpha2 {
    COUNTRY_PL = MULTICHAR('p','l')
};

enum PACKED LanguageAlpha2 {
    LANG_AFAR = MULTICHAR('a','a'),
    LANG_ABKHAZIAN = MULTICHAR('a','b'),
    LANG_AFRIKAANS = MULTICHAR('a','f'),
    LANG_AKAN = MULTICHAR('a','k'),
    LANG_AMHARIC = MULTICHAR('a','m'),
    LANG_ARAGONESE = MULTICHAR('a','n'),
    LANG_ARABIC = MULTICHAR('a','r'),
    LANG_ASSAMESE = MULTICHAR('a','s'),
    LANG_AVAR = MULTICHAR('a','v'),
    LANG_AYMARA = MULTICHAR('a','y'),
    LANG_AZERBAIJANI = MULTICHAR('a','z'),
    LANG_BASHKIR = MULTICHAR('b','a'),
    LANG_BELARUSIAN = MULTICHAR('b','e'),
    LANG_BULGARIAN = MULTICHAR('b','g'),
    LANG_BIHARI = MULTICHAR('b','h'),
    LANG_BISLAMA = MULTICHAR('b','i'),
    LANG_BAMBARA = MULTICHAR('b','m'),
    LANG_BENGALI = MULTICHAR('b','n'),
    LANG_TIBETAN = MULTICHAR('b','o'),
    LANG_BRETON = MULTICHAR('b','r'),
    LANG_BOSNIAN = MULTICHAR('b','s'),
    LANG_CATALAN = MULTICHAR('c','a'),
    LANG_CHECHEN = MULTICHAR('c','e'),
    LANG_CHAMORRO = MULTICHAR('c','h'),
    LANG_CORSICAN = MULTICHAR('c','o'),
    LANG_CREE = MULTICHAR('c','r'),
    LANG_CZECH = MULTICHAR('c','s'),
    LANG_OLD_CHURCH_SLAVONIC = MULTICHAR('c','u'),
    LANG_CHUVASH = MULTICHAR('c','v'),
    LANG_WELSH = MULTICHAR('c','y'),
    LANG_DANISH = MULTICHAR('d','a'),
    LANG_GERMAN = MULTICHAR('d','e'),
    LANG_DIVEHI = MULTICHAR('d','v'),
    LANG_DZONGKHA = MULTICHAR('d','z'),
    LANG_EWE = MULTICHAR('e','e'),
    LANG_GREEK = MULTICHAR('e','l'),
    LANG_ENGLISH = MULTICHAR('e','n'),
    LANG_ESPERANTO = MULTICHAR('e','o'),
    LANG_SPANISH = MULTICHAR('e','s'),
    LANG_ESTONIAN = MULTICHAR('e','t'),
    LANG_BASQUE = MULTICHAR('e','u'),
    LANG_PERSIAN = MULTICHAR('f','a'),
    LANG_PEUL = MULTICHAR('f','f'),
    LANG_FINNISH = MULTICHAR('f','i'),
    LANG_FIJIAN = MULTICHAR('f','j'),
    LANG_FAROESE = MULTICHAR('f','o'),
    LANG_FRENCH = MULTICHAR('f','r'),
    LANG_WEST_FRISIAN = MULTICHAR('f','y'),
    LANG_IRISH = MULTICHAR('g','a'),
    LANG_SCOTTISH_GAELIC = MULTICHAR('g','d'),
    LANG_GALICIAN = MULTICHAR('g','l'),
    LANG_GUARANI = MULTICHAR('g','n'),
    LANG_GUJARATI = MULTICHAR('g','u'),
    LANG_MANX = MULTICHAR('g','v'),
    LANG_HAUSA = MULTICHAR('h','a'),
    LANG_HEBREW = MULTICHAR('h','e'),
    LANG_HINDI = MULTICHAR('h','i'),
    LANG_HIRI_MOTU = MULTICHAR('h','o'),
    LANG_CROATIAN = MULTICHAR('h','r'),
    LANG_HAITIAN = MULTICHAR('h','t'),
    LANG_HUNGARIAN = MULTICHAR('h','u'),
    LANG_ARMENIAN = MULTICHAR('h','y'),
    LANG_HERERO = MULTICHAR('h','z'),
    LANG_INTERLINGUA = MULTICHAR('i','a'),
    LANG_INDONESIAN = MULTICHAR('i','d'),
    LANG_INTERLINGUE = MULTICHAR('i','e'),
    LANG_IGBO = MULTICHAR('i','g'),
    LANG_SICHUAN_YI = MULTICHAR('i','i'),
    LANG_INUPIAK = MULTICHAR('i','k'),
    LANG_IDO = MULTICHAR('i','o'),
    LANG_ICELANDIC = MULTICHAR('i','s'),
    LANG_ITALIAN = MULTICHAR('i','t'),
    LANG_INUKTITUT = MULTICHAR('i','u'),
    LANG_JAPANESE = MULTICHAR('j','a'),
    LANG_JAVANESE = MULTICHAR('j','v'),
    LANG_GEORGIAN = MULTICHAR('k','a'),
    LANG_KONGO = MULTICHAR('k','g'),
    LANG_KIKUYU = MULTICHAR('k','i'),
    LANG_KUANYAMA = MULTICHAR('k','j'),
    LANG_KAZAKH = MULTICHAR('k','k'),
    LANG_GREENLANDIC = MULTICHAR('k','l'),
    LANG_CAMBODIAN = MULTICHAR('k','m'),
    LANG_KANNADA = MULTICHAR('k','n'),
    LANG_KOREAN = MULTICHAR('k','o'),
    LANG_KANURI = MULTICHAR('k','r'),
    LANG_KASHMIRI = MULTICHAR('k','s'),
    LANG_KURDISH = MULTICHAR('k','u'),
    LANG_KOMI = MULTICHAR('k','v'),
    LANG_CORNISH = MULTICHAR('k','w'),
    LANG_KIRGHIZ = MULTICHAR('k','y'),
    LANG_LATIN = MULTICHAR('l','a'),
    LANG_LUXEMBOURGISH = MULTICHAR('l','b'),
    LANG_GANDA = MULTICHAR('l','g'),
    LANG_LIMBURGIAN = MULTICHAR('l','i'),
    LANG_LINGALA = MULTICHAR('l','n'),
    LANG_LAOTIAN = MULTICHAR('l','o'),
    LANG_LITHUANIAN = MULTICHAR('l','t'),
    LANG_LUBA_KATANGA = MULTICHAR('l','u'),
    LANG_LATVIAN = MULTICHAR('l','v'),
    LANG_MALAGASY = MULTICHAR('m','g'),
    LANG_MARSHALLESE = MULTICHAR('m','h'),
    LANG_MAORI = MULTICHAR('m','i'),
    LANG_MACEDONIAN = MULTICHAR('m','k'),
    LANG_MALAYALAM = MULTICHAR('m','l'),
    LANG_MONGOLIAN = MULTICHAR('m','n'),
    LANG_MOLDOVAN = MULTICHAR('m','o'),
    LANG_MARATHI = MULTICHAR('m','r'),
    LANG_MALAY = MULTICHAR('m','s'),
    LANG_MALTESE = MULTICHAR('m','t'),
    LANG_BURMESE = MULTICHAR('m','y'),
    LANG_NAURUAN = MULTICHAR('n','a'),
    LANG_NORWEGIAN = MULTICHAR('n','o'),
    LANG_NORWEGIAN_BOKMAL = MULTICHAR('n','b'),
    LANG_NORWEGIAN_NYNORSK = MULTICHAR('n','n'),
    LANG_NEPALI = MULTICHAR('n','e'),
    LANG_NDONGA = MULTICHAR('n','g'),
    LANG_DUTCH = MULTICHAR('n','l'),
    LANG_NORTH_NDEBELE = MULTICHAR('n','d'),
    LANG_SOUTH_NDEBELE = MULTICHAR('n','r'),
    LANG_NAVAJO = MULTICHAR('n','v'),
    LANG_CHICHEWA = MULTICHAR('n','y'),
    LANG_OCCITAN = MULTICHAR('o','c'),
    LANG_OJIBWA = MULTICHAR('o','j'),
    LANG_OROMO = MULTICHAR('o','m'),
    LANG_ORIYA = MULTICHAR('o','r'),
    LANG_OSSETIAN = MULTICHAR('o','s'),
    LANG_PANJABI = MULTICHAR('p','a'),
    LANG_PALI = MULTICHAR('p','i'),
    LANG_POLISH = MULTICHAR('p','l'),
    LANG_PASHTO = MULTICHAR('p','s'),
    LANG_PORTUGUESE = MULTICHAR('p','t'),
    LANG_QUECHUA = MULTICHAR('q','u'),
    LANG_RAETO_ROMANCE = MULTICHAR('r','m'),
    LANG_KIRUNDI = MULTICHAR('r','n'),
    LANG_ROMANIAN = MULTICHAR('r','o'),
    LANG_RUSSIAN = MULTICHAR('r','u'),
    LANG_RWANDI = MULTICHAR('r','w'),
    LANG_SANSKRIT = MULTICHAR('s','a'),
    LANG_SARDINIAN = MULTICHAR('s','c'),
    LANG_SINDHI = MULTICHAR('s','d'),
    LANG_NORTHERN_SAMI = MULTICHAR('s','e'),
    LANG_SANGO = MULTICHAR('s','g'),
    LANG_SERBO_CROATIAN = MULTICHAR('s','h'),
    LANG_SINHALESE = MULTICHAR('s','i'),
    LANG_SLOVAK = MULTICHAR('s','k'),
    LANG_SLOVENIAN = MULTICHAR('s','l'),
    LANG_SAMOAN = MULTICHAR('s','m'),
    LANG_SHONA = MULTICHAR('s','n'),
    LANG_SOMALIA = MULTICHAR('s','o'),
    LANG_ALBANIAN = MULTICHAR('s','q'),
    LANG_SERBIAN = MULTICHAR('s','r'),
    LANG_SWATI = MULTICHAR('s','s'),
    LANG_SOUTHERN_SOTHO = MULTICHAR('s','t'),
    LANG_SUNDANESE = MULTICHAR('s','u'),
    LANG_SWEDISH = MULTICHAR('s','v'),
    LANG_SWAHILI = MULTICHAR('s','w'),
    LANG_TAMIL = MULTICHAR('t','a'),
    LANG_TELUGU = MULTICHAR('t','e'),
    LANG_TAJIK = MULTICHAR('t','g'),
    LANG_THAI = MULTICHAR('t','h'),
    LANG_TIGRINYA = MULTICHAR('t','i'),
    LANG_TURKMEN = MULTICHAR('t','k'),
    LANG_TAGALOG = MULTICHAR('t','l'),
    LANG_TSWANA = MULTICHAR('t','n'),
    LANG_TONGA = MULTICHAR('t','o'),
    LANG_TURKISH = MULTICHAR('t','r'),
    LANG_TSONGA = MULTICHAR('t','s'),
    LANG_TATAR = MULTICHAR('t','t'),
    LANG_TWI = MULTICHAR('t','w'),
    LANG_TAHITIAN = MULTICHAR('t','y'),
    LANG_UYGHUR = MULTICHAR('u','g'),
    LANG_UKRAINIAN = MULTICHAR('u','k'),
    LANG_URDU = MULTICHAR('u','r'),
    LANG_UZBEK = MULTICHAR('u','z'),
    LANG_VENDA = MULTICHAR('v','e'),
    LANG_VIETNAMESE = MULTICHAR('v','i'),
    LANG_VOLAPUK = MULTICHAR('v','o'),
    LANG_WALLOON = MULTICHAR('w','a'),
    LANG_WOLOF = MULTICHAR('w','o'),
    LANG_XHOSA = MULTICHAR('x','h'),
    LANG_YIDDISH = MULTICHAR('y','i'),
    LANG_YORUBA = MULTICHAR('y','o'),
    LANG_ZHUANG = MULTICHAR('z','a'),
    LANG_CHINESE = MULTICHAR('z','h'),
    LANG_ZULU = MULTICHAR('z','u')
};

// TODO: Remouve union Country
union Country {
    enum CountryAlpha2 Code;
    char Str[3];
};

union Iso639_1 {
    enum LanguageAlpha2 e;
    char c[2];
};

union CurrencyAlpha3 {
    enum {
        Currency_EUR = MULTICHAR('E','U','R'),
        Currency_PLN = MULTICHAR('P','L','N')
    } Code;
    char Str[4];
};

union CurrencyCode {
    uint8_t raw[2];
    enum PACKED {
        // FIXME: Use proper macro
        CURRENCY_CODE_EUR = 0x7809
      , CURRENCY_CODE_PLN = 0x8509
    } e;
};

enum PACKED AuthorisationResponseCode {
    ARC_ONLINE_APPROVED = 0x00
  , ARC_UNABLE_TO_GO_ONLINE_OFFLINE_DECLINED = MULTICHAR('Z','3')
  , ARC_UNABLE_TO_GO_ONLINE_OFFLINE_AUTHORISED = MULTICHAR('Y','3')
  , ARC_OFFLINE_APPROVED = MULTICHAR('Y','1')
  , ARC_OFFLINE_DECLINED = MULTICHAR('Z','1')
  , ARC_VISA_SCA_REQUIRED_PIN_NOT_SUPPORTED = MULTICHAR('1','A')
  , ARC_VISA_SCA_REQUIRED_SUPPORTED_ONLINE_PIN = MULTICHAR('7','0')
  , ARC_MASTERCARD_SCA_REQUIRED = MULTICHAR('6','5')
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
    union bcd6 HoldTime;
    union LanguagePreference* LanguagePreference; // Not used in nexo
    enum ValueQualifier {
        UI_VALUE_QUALIFIER_NONE
      , UI_VALUE_QUALIFIER_AMOUNT
      , UI_VALUE_QUALIFIER_BALANCE
    } ValueQualifier;
    union bcd6 Value;
    union CurrencyAlpha3 CurrencyCode;
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

struct Bid {
    uint8_t size;
    unsigned char value[16 + 1];
} Bid;

struct Prefix {
    uint8_t size;
    unsigned char value[19];
};

struct PrefixRange {
    uint8_t size;
    unsigned char value[19];
};

union ProcessingStatus {
    unsigned char raw[4];
    struct {
        unsigned char technologySelectionNonFallbackMode : 1;
        unsigned char buildingCandidateListUsingPse : 1;
        unsigned char buildingCandidateListUsingListOfAid : 1;
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
        } transactionType;

        struct TransactionDataInputCapability {
            unsigned char numericKeys : 1;
            unsigned char alphabeticAndSpecialCharactersKeys : 1;
            unsigned char commandKeys : 1;
            unsigned char functionKeys : 1;
            unsigned char /* RFU */ : 4;
        } terminalDataInput;

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
        } terminalDataOutput;
    };
};

union EeaProcessSettings {
    unsigned char raw[2];
    struct {
        unsigned char upfrontButtonOnScreenSupported: 1;
        uint8_t offerOverride: 1; // [1,6]
        uint8_t doNotOfferOverrideWhenOnlyOneEntry: 1; // [1,5]
    };
};

enum PrinterStatus {
    PRINTER_UNAVAILABLE
  , PRINTER_OPERATIONAL
  , PRINTER_PERMANENT_FAILURE // Not defined in nexo
};

#define TERMINAL_TYPE_ATTENDED(T)\
    ONEOF3((T).operationalEnvironment, ATTENDED_ONLINE_ONLY, ATTENDED_OFFLINE_AND_ONLINE, ATTENDED_OFFLINE_ONLY)
#define TERMINAL_TYPE_UNATTENDED(T)\
    ONEOF3((T).operationalEnvironment, UNATTENDED_ONLINE_ONLY, UNATTENDED_OFFLINE_AND_ONLINE, UNATTENDED_OFFLINE_ONLY)
#define TERMINAL_TYPE_ONLINE_ONLY(T)\
    ONEOF2((T).operationalEnvironment, ATTENDED_ONLINE_ONLY, UNATTENDED_ONLINE_ONLY)
#define TERMINAL_TYPE_OFFLINE_ONLY(T)\
    ONEOF2((T).operationalEnvironment, ATTENDED_OFFLINE_ONLY, UNATTENDED_OFFLINE_ONLY)
#define TERMINAL_TYPE_OFFLINE_WITH_ONLINE_CAPABILITY(T)\
    ONEOF2((T).operationalEnvironment, ATTENDED_OFFLINE_AND_ONLINE, UNATTENDED_OFFLINE_AND_ONLINE)

enum PACKED TerminalOperationalControl {
    OPERATED_BY_FINANCIAL_INSTITUTION = 0x1
  , OPERATED_BY_MERCHANT = 0x2
  , OPERATED_BY_CARDHOLDER = 0x3
};

enum PACKED TerminalOperationalEnvironment {
    ATTENDED_ONLINE_ONLY = 0x1
  , ATTENDED_OFFLINE_AND_ONLINE = 0x2
  , ATTENDED_OFFLINE_ONLY = 0x3
  , UNATTENDED_ONLINE_ONLY = 0x4
  , UNATTENDED_OFFLINE_AND_ONLINE = 0x5
  , UNATTENDED_OFFLINE_ONLY = 0x6
};

enum PACKED TerminalTypeEnum {
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
};

union TerminalType {
    uint8_t b[1];
    struct {
        enum TerminalOperationalEnvironment operationalEnvironment : 4;
        enum TerminalOperationalControl operationalControl : 4;
    };
    enum TerminalTypeEnum e;
};

enum InterfaceStatus {
    INTERFACE_CHIP_READER = (1 << 0),
    INTERFACE_MAGNETIC_STRIPE_READER = (1 << 1),
    INTERFACE_ATTENDANT_NUMERIC_KEYPAD = (1 << 2),
    INTERFACE_ATTENDANT_F_KEY_MANUAL_ENTRY = (1 << 3),
    INTERFACE_ATTENDANT_F_KEY_REFERENCE_ENTRY = (1 << 4),
    INTERFACE_ATTENDANT_F_KEY_ACCEPT = (1 << 5),
    INTERFACE_CONTACTLESS_READER = (1 << 6),
    INTERFACE_CARDHOLDER_DETECT = (1 << 7),

    INTERFACE_DISABLE_ALL = 0x0000,
    INTERFACE_ENABLE_ALL = INTERFACE_CHIP_READER
                         | INTERFACE_MAGNETIC_STRIPE_READER
                         | INTERFACE_ATTENDANT_NUMERIC_KEYPAD
                         | INTERFACE_ATTENDANT_F_KEY_MANUAL_ENTRY
                         | INTERFACE_ATTENDANT_F_KEY_REFERENCE_ENTRY
                         | INTERFACE_ATTENDANT_F_KEY_ACCEPT
                         | INTERFACE_CONTACTLESS_READER
                         ,
    INTERFACE_NO_CONTACTLESS =  INTERFACE_ENABLE_ALL
                             & ~INTERFACE_CONTACTLESS_READER
                             ,
};

// FIXME: Rename to Table
struct TerminalApplicationVersionList {
    size_t s;
    struct TerminalApplicationVersionEntry {
        struct Rid rid;
        union binary2 applicationVersionNumber;
    } entry[50];
};

// TODO: Rename list to table
struct TerminalSupportedLanguageList {
    size_t l;
    union Iso639_1 a[30];
};


union CommandTemplate {
    uint8_t raw[2];
};

// source nexo-IS v.4.0, section 4.5.3.3
// E0
struct PermanentTerminalSpecificData {
    // 9F1E
    struct string8* ifdSerialNumber;
    // DF50
    struct string6* commandKeyBypassPinLabel;
    // DF14
    struct string5 commandKeyClearLabel;
    // DF15
    struct string5 commandKeyEnterLabel;
    // DF16
    struct string5 commandKeyScrollLabel;
    // DF53
    struct string5 commandKeyChangeApplicationLabel;
};

// source: nexo-IS v.4.0, section 4.5.3.3
// E1
struct TerminalSpecificData {
    // 9F40
    union AdditionalTerminalCapabilities additionalTerminalCapabilities;
    // DF13
    union ConfiguredServices configuredServices;
    // DF17
    enum ServiceId defaultCardService;
    // DF12
    union Iso639_1 cardholderDefaultLanguage;
    // DF18
    union bcd maxNumberOfChipTries; // WARNING: Set default value to 0x01
    // DF40
    struct TerminalApplicationVersionList terminalApplicationVersionListContact;
    // DF49
    struct TerminalApplicationVersionList* terminalApplicationVersionListCtlss;
    // 9F33
    union TerminalCapabilities terminalCapabilities;
    // 9F1A
    // TODO: Add terminalCountryCode
    // 9F1B
    // FIXME: Check if terminalFloorLimit can be present in E1
    union bcd6* terminalFloorLimit;
    // 9F1C
    // TODO: Consider replacing string8 with an8
    struct string8 tid;
    // DF34
    union TerminalSettings terminalSettings;
    // DF33
    struct TerminalSupportedLanguageList terminalSupportedLanguageList;
    // 9F35
    union TerminalType terminalType;
    // DF35
    // TODO: Add terminalTransactionCurrencyCode
    // DF47
    union CurrencyAlpha3 currencyCodeAlpha3;
    // DF36
    union bcd terminalTransactionCurrencyExponent;
    // DF46
    union bcd* unpredictableNumberRange;
    // DF52
    union EeaProcessSettings* eeaProcessSettings; // FIXME: shouldn't be a pointer
};

//E2
struct BankIdentifierCode {
    enum PACKED {
        BIC_C8
      , BIC_C11
    } type;
    union {
        struct {
            uint8_t a[8];
        } c8;
        struct {
            uint8_t a[11];
        } c11;
    };
};

struct BankIdentifierCodeList {
    struct BankIdentifierCode value;
    struct BankIdentifierCodeList* next;
};

struct IssuerCountryCodeAlpha2List {
    union Country value;
    struct IssuerCountryCodeAlpha2List* next;
};

struct IssuerCountryCodeAlpha3List {
    // FIXME: IssuerCountryCodeAlpha3List isn't defined
    struct IssuerCountryCodeAlpha2List* next;
};

struct IssuerIdentificationNumberList {
    struct bcd3 value;
    struct IssuerIdentificationNumberList* next;
};

struct IssuerIdentificationMaskList {
    uint8_t value[3];
    struct IssuerIdentificationMaskList* next;
};

struct IbanComparisonValueList {
    struct ans_34 value;
    struct IbanComparisonValueList* next;
};

struct KernelIdList {
    enum Kernel value;
    struct KernelIdList* next;
};

struct EeaProductIdentificationList {
    uint8_t value[5];
    struct EeaProductIdentificationList* next;
};

// source: nexo-FAST v.3.2 section 13.3.14
// size: at least 60
// presence: M
// configuration: Terminal
// [E2]
struct ApplicationProfileSelectionTable {
    struct Aid applicationProfileAid;
    bcd_t profileNumber;
    union ConfiguredServices supportedServices;

    bcd_t* applicationProfileAcquirerNumber;
    bool* aidMatchCriteria;
    struct BankIdentifierCodeList* bic;
    struct IssuerCountryCodeAlpha2List* issuerCountryCodeAlpha2;
    struct IssuerCountryCodeAlpha3List* issuerCountryCodeAlpha3;
    struct IssuerIdentificationNumberList* iin;
    struct IssuerIdentificationMaskList* iinMask;
    struct IbanComparisonValueList* ibanComparisonValue;
    struct as_34* ibanMask;
    union bcd6* applicationProfileAmount;
    bool* cashBackPresent;
    enum TechnologySelected* technologyOfProfile;
    struct KernelIdList* applicationProfileKernelId;
    struct EeaProductIdentificationList* productTypeComparisonValue;
    uint8_t (*productTypeMask)[5];

    // TODO: Optional other private tags

    struct ApplicationProfileSelectionTable* next;
};

// source: nexo-FAST v.3.2 section 13.3.33
// size: at least 6
// configuration: Terminal
// presence: C

struct CertificationAuthorityPublicKeyTable {
};

// source: nexo-FAST v.3.2 section 13.3.120
// size: up to 20
// configuration: Terminal
// presence: M
struct ServiceSettingsEntry {
    // DF01
    enum ServiceId serviceIdentifier;
    // DF10
    union ServiceSettings serviceSettings;
    // DF02
    enum CardholderMessage cardholderInitialMessage;
    // DF11
    union ServiceStartEvents allowedServiceStartEvents;
    // DF0F
    struct MinimumServiceStartConditionsTable {
        size_t s;
        union ServiceStartEvents a[10];
    } minimumServiceStartConditions;
};

// [E4]
struct ServiceSettingsTable {
    size_t s;
    struct ServiceSettingsEntry a[20];
};

enum PACKED FallbackParameterChip {
    FALLBACK_TRANSACTION_ALLOWED_FOR_CHIP = 0x01
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

// Based on nexo-FAST section 13.3
union ApplicationProfileSettings {
    uint8_t raw[5];
    struct {
        uint8_t approvalOfPaymentPartOnlyAllowed : 1;
        uint8_t /* RFU */ : 2;
        uint8_t terminalInitiatedVoiceAuthAllowed : 1;
        uint8_t referralAllowed : 1;
        uint8_t supplementaryAmountAllowed : 1;
        uint8_t cashbackAllowed : 1;
        uint8_t checkAmountsAgainstMinMax : 1;

        uint8_t cardholderConfirmationRequiredForDeferredPaymentTrxAmt : 1;
        uint8_t refundOnline : 1;
        uint8_t forcedApprovalAllowedForOnlineDeclinedTrx : 1;
        uint8_t forcedApprovalAllowedForOfflineDeclinedTrx : 1;
        uint8_t pinBypassAllowed : 1;
        uint8_t cvdRequiredForManualEntry : 1;
        uint8_t cdaRequiredForTcIn2ndGenAc : 1;
        uint8_t cdaRequiredForArqcIn2ndGenAc : 1;

        uint8_t retrieveVoiceAuthFromTrxLog : 1;
        uint8_t performExceptionFileChecking : 1;
        uint8_t /* RFU */ : 1;
        uint8_t retrieveUpdatePreAuthFromTrxLog : 1;
        uint8_t /* RFU */ : 1;
        uint8_t partialApprovalSupported : 1;
        uint8_t isDccAcceptorModeAllowed : 1; // TODO: Place it into the proper bit
        uint8_t balanceDisplaySupported : 1;

        union ReceiptSettings merchantReceipt;
        union ReceiptSettings cardholderReceipt;

    };
};

union PACKED MerchantCategoryCode {
    struct bcd2 bcd;
    uint8_t raw[2];
    enum PACKED MerchantCategoryCodeEnum {
        // Based on some random document from the internet claiming to be Visa'a classification
        MCC_VETERINARY_SERVICES = MULTICHAR(0x07,0x42),
        MCC_AGRICULTURAL_CO_OPERATIVES = MULTICHAR(0x07,0x63),
        MCC_HORTICULTURAL_SERVICES = MULTICHAR(0x07,0x80),
    } e;
};

// source nexo-IS 4.0
// configuration: Application Profile
// presence: M
// [E6]
struct ApplicationProfile {
    // Unique Application Profile ID:
    bcd_t profileNumber;
    bcd_t acquirerNumber;

    // Application Profile Parameters:
    union bcd6 acquirerIdentifier;
    void* additionalDataElements; // TODO: Define EF template
    union TerminalVerificationResults* additionalRestrictionsForForcedAcceptance;
    union AdditionalTerminalCapabilities* additionalTerminalCapabilities; // FIXME: Not mentioned in nexo-FAST 13.1.2
    union TerminalCapabilities* terminalCapabilities;
    union CountryCode terminalCountryCode;
    struct ans_16 applicationLabelDefault;
    union ApplicationProfileSettings applicationProfileSettings;
    union ApplicationProfileSettingsForCancellation* applicationProfileSettingsForCancellation;
    union bcd6* cashAdvanceMaximumAmount;
    union bcd6* cashbackMaximumAmount;
    union CvmCapability* cvmCapabilityCvmRequired;
    union CvmCapability* cvmCapabilityNoCvmRequired;
    union MagStripeCvmCapability* magStripeCvmCapabilityCvmRequired;
    union MagStripeCvmCapability* magStripeCvmCapabilityNoCvmRequired;
    union bcd6* cvcDefaultAmount;
    union bcd6* dccMinimumAllowedAmount;
    union bcd6 refundProtectionAmount; // FIXME: Make refundProtectionAmount optional
    union bcd6* terminalFloorLimit;

    // missing Default DDA DOL (DF1A)
    bcd_t holdTimeValue;
    union Kernel2Configuration* kernel2Configuration;
    union Kernel4ReaderCapabilities* kernel4ReaderCapabilities;
    union Kernel4Settings* kernel4Settings;
    union MsrCvmCapability* msrCvmCapabilityCvmRequired;
    union MsrCvmCapability* msrCvmCapabilityNoCvmRequired;
    struct bcd2* maxTargetPercentageForBiasedRandomSelection;
    union bcd* targetPercentageForBiasedRandomSelection;

    // DF1D
    union bcd6* thresholdValueForBiasedRandomSelection;

    // DF1E
    union TerminalVerificationResults* tacDefault;

    // DF1F
    union TerminalVerificationResults* tacDenial;

    // DF20
    union TerminalVerificationResults* tacOnline;

    union MerchantCategoryCode merchantCategoryCode;
    uint8_t (* merchantCustomData)[20];
    struct ans15 merchantIdentifier;
    char* merchantNameAndLocation;

    enum FallbackParameterChip fallbackParameterChip;
    enum FallbackParameterMagneticStripe fallbackParameterMagneticStripe;
    enum CvmMagneticStripe cvmMagneticStripe;
};

struct ApplicationProfileList {
    struct ApplicationProfile entry;
    struct ApplicationProfileList* next;
};

// source: nexo-FAST v.3.2 section 13.3.135
// size: at least 50
// configuration: Terminal
// presence: C

struct TerminalListOfBid {
    struct Bid Bid;

    struct MatchingPattern {
        enum {
            MATCH_PREFIX
          , MATCH_RANGE
        } type;
        union {
            struct Prefix prefix;
            struct PrefixRange prefixRange;
        };
        struct MatchingPattern* next;
    } matchingPattern;

    struct TerminalListOfBid* next;
};

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

struct ExceptionFileEntry {
    // [DF01]
    struct Prefix prefix;

    // [DF02]
    union bcd* panSequenceNumber;
};

// source: nexo-FAST v.3.2, 13.3.63
// size: at least 5000
// configuration: Terminal
// presence: O
// [E9]
struct ExceptionFile {
    struct ExceptionFileEntry entry;
    struct ExceptionFile* next;
};

// source: nexo-FAST v.3.2 section 13.3.76
// size: up to 4
// configuration: Application Profile
// presence: O

struct LimitSetList {
};

// source: nexo-FAST v.3.2 section 13.3.53
// size: at least 50
// configuration: Terminal
// presence: C

struct DefaultKernelIdAndAppLabelPerAid {
};

// source: nexo-FAST v.3.2 section 13.3.36
// size: at least 80
// configuration: Terminal
// presence: C

struct CombinationListAndParameters {
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
    union bcd6* readerCtlessTransactionLimit;
    union bcd6* readerCtlessFloorLimit;
    union bcd6* readerCvmRequiredLimit;
    bool* extendedSelectionSupported;

    // Predefined indicators
    bool* statusCheckRequested;
    bool* zeroAmount;
    bool* ctlessApplicationNotAllowed;
    bool* readerCtlessFloorLimitNotAllowed;
    bool* readerCvmRequiredLimitExceeded;
    bool* readerCtlessFloorLimitExceeded;

    struct CombinationListAndParameters* next;
};

// source: nexo-FAST v.3.2 section 13.3.2
// size: >= 25
// configuration: Terminal
// presence: M
// [ED]
struct AcquirerParameterTable {
    // A reference number uniquely identifying the acquirer for the nexo FAST application
    // [DF01]
    struct bcd2 acquirerNumber;

    // Mnemonic identifying the acquirer as known by the attendant
    // [DF02]
    struct ans_16 acquirerLabel;

    // Set to true when this acquirer label is presented to the attendant during
    // the Acquirer Pre-Selection process
    // [DF03]
    bool usedForPreSelection;
};

enum PACKED ApplicationSelectionIndicator {
    ASI_PARTIAL_MATCH_OK = 0x00
  , ASI_EXACT_MATCH = 0x01
};

struct SubordinatedApplication {
    // (Partial) Card AID of a subordinated appplications
    // [DF01]
    struct Aid cardAid;

    struct SubordinatedApplication* next;
};

// source: nexo-FAST v.3.2 section 13.3.6
// size: at least 50
// presence: O
// [EE]
struct AidPreferenceTable {
    // (Partial) Card AID of a preferred card application
    // [DF01]
    struct Aid cardAid;

    // [DF02]
    enum ApplicationSelectionIndicator applicationSelectionIndicator;

    // [BF02]
    struct SubordinatedApplication subordinatedApplication;

    struct AidPreferenceTable* next;
};

// TODO: Defince AdditionalDataElements structure
// source: nexo-FAST v.3.2 section 13.3.4
// size: <= 256
// configuration: Application Profile
// presence: O
// [EF]
struct AdditionalDataElements {
};

union TerminalVerificationResults {
    uint8_t raw[5];
    uint64_t u;
    struct {
        uint8_t /* RFU */ : 1;
        uint8_t sdaSelected : 1;
        uint8_t cdaFailed : 1;
        uint8_t ddaFailed : 1;
        uint8_t cardNumberAppearsOnHotlist : 1;
        uint8_t iccDataMissing : 1;
        uint8_t sdaFailed : 1;
        uint8_t offlineDataAuthenticationWasNotPerformed : 1;

        uint8_t /* RFU */ : 3;
        uint8_t newCard : 1;
        uint8_t requestedServiceNotAllowedForCardProduct : 1;
        uint8_t applicationNotYetEffective : 1;
        uint8_t expiredApplication : 1;
        uint8_t cardAndTerminalHaveDifferentApplicationVersions : 1;

        uint8_t /* RFU */ : 2;
        uint8_t onlinePinEntered : 1;
        uint8_t pinEntryRequiredPinPadPresentButPinWasNotEntered : 1;
        uint8_t pinEntryRequiredButNoPinPadPresentOrNotWorking : 1;
        uint8_t pinEntryTryLimitExceeded : 1;
        uint8_t unrecognisedCvm : 1;
        uint8_t cardholderVerificationWasNotSuccessful : 1;

        uint8_t /* RFU */ : 3;
        uint8_t merchantForcedTransactionOnline : 1;
        uint8_t transactionSelectedRandomlyForOnLineProcessing : 1;
        uint8_t upperConsecutiveOfflineLimitExceeded : 1;
        uint8_t lowerConsecutiveOfflineLimitExceeded : 1;
        uint8_t transactionExceedsFloorLimit : 1;

/*1~4*/ uint8_t /* RFU */ : 4;
        uint8_t scriptProcessingFailedAfterFinalGenerateAc : 1;
        uint8_t scriptProcessingFailedBeforeFinalGenerateAc : 1;
        uint8_t issuerAuthenticationFailed : 1;
/*8*/   uint8_t defaultTdolUsed : 1;
    };
};

union CvmCapability {
    uint8_t raw[1];
    struct {
/*1-3*/ uint8_t /* RFU */ : 3;
/*4*/   uint8_t noCvm : 1;
/*5*/   uint8_t encipheredPinForOfflineVerification : 1;
/*6*/   uint8_t signatureOnPaper : 1;
/*7*/   uint8_t encipheredPinForOnlineVerification : 1;
/*8*/   uint8_t plainTextForIccVerification : 1;
    };
};

union MagStripeCvmCapability {
    uint8_t raw[1];
    struct {
/*1-4*/ uint8_t /* RFU */ : 4;
        enum PACKED {
            MSR_CVM_NO_CVM = 0x0
          , MSR_CVM_OBTAIN_SIGNATURE = 0x1
          , MSR_CVM_ONLINE_PIN = 0x2
          , MSR_CVM_NA = 0xF
/*5-8*/ } e : 4;
    };
};

union CvmCode {
    unsigned char raw;
    struct {
        enum PACKED {
            CVM_SUCCESS = 0b000000, // It's called "Fail CVM in nexo-FAST v.3.2, figure 172
            CVM_PLAINTEXT_PIN_VERIFICATION_PERFORMED_BY_ICC = 0b000001,
            CVM_ENCIPHERED_PIN_VERIFIED_ONLINE = 0b000010,
            CVM_PLAINTEXT_PIN_VERIFICATION_PERFORMED_BY_ICC_AND_SIGNATURE = 0b000011,
            CVM_ENCIPHERED_PIN_VERIFIED_BY_ICC = 0b000100,
            CVM_ENCIPHERED_PIN_VERIFIED_BY_ICC_AND_SIGNATURE = 0b000101,
            CVM_SIGNATURE = 0b011110,
            CMV_NO_CVM_REQUIRED = 0b011111
        } cvm : 6;
        unsigned char applyRuleOnFail : 1;
        unsigned char /* RFU */ : 1;
    };
};

enum PACKED CvmResults {
    CVM_RESULT_UNKNOWN = 0x00,
    // Also if not CVM conditions were satisfied or CVM code was not
    // recognised or not supported
    CVM_RESULT_FAILED = 0x01,
    CVM_RESULT_SUCCESS = 0x02
};

// EMV v.4.3 Book 3, annex C3
struct PACKED CvRule {
    union CvmCode cvmCode;
    enum CvmConditionCode cvmConditionCode;
};

struct CvRuleTable {
    size_t l;
    struct CvRule a[123];
};

union Cvm {
    unsigned char raw[3];
    struct {
        struct CvRule cvRule;
        enum CvmResults result;
    };
};

// nexo-FAST v.3.2, section 13.1.39
// EMV v.4.3 Book 3, section 10.5
// [8E]
struct CvmList {
    uint32_t amountX;
    uint32_t amountY;
    struct CvRuleTable cvRule;
};

// FIXME: Consider better struct to represent DOL
struct Dol {
    size_t s;
    unsigned char a[100];
};

// based on EMV 4.3 Book 3 Annex C6
// [9B]
union TransactionStatusInformation {
    uint8_t raw[2];
    struct {
        uint8_t offlineDataAuthenticationWasPerformed : 1;
        uint8_t cardholderVerificationWasPerformed : 1;
        uint8_t cardRiskManagementWasPerformed : 1;
        uint8_t issuerAuthenticationWasPerformed : 1;
        uint8_t terminalRiskManagementsWasPerformed : 1;
        uint8_t scriptProcessingWasPerformed : 1;
        uint8_t /* RFU */ : 2;

        uint8_t /* RFU */ : 8;
    };
};


// source: nexo-FAST v.3.2 section 13.3.61
// size: at least 50
// configuration: Terminal
// presence: O
struct EeaProcessTable {
};

// source: nexo-FAST v.3.2 section 13.3.59
// size: at least 50
// configuration: Terminal
// presence: O

struct EeaOnlyListOfAid {
    struct {
        size_t l;
        struct Aid a[50];
    } terminalAid;
};

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
    struct TerminalSupportedLanguageList* languagePreference;

    // [9F11]
    enum IssuerCodeTableIndex* issuerCodeTableIndex;

    // [9F12]
    struct string16* applicationPreferredName;

    // [BF0C]
    struct FciIssuerDiscretionaryData* issuerDiscretionaryData;
};

// FIXME: Use proper type for DF Name
struct DfName {
    size_t l;
    char v[36];
};

// [6F]
struct FileControlInformation {
    // [84]
    struct Aid DfName; // FIXME: Type
    // [A5]
    struct FciProprietaryTemplate a5;
};

// Definition pf OpaquePinData should be provided by the Trusted Layer
struct OpaquePinData;

// Struct is used instead of union to avoid accidental mixup of plain text PIN
// (mainly used for debugging) with OpaquePinData
struct PinData {
    struct OpaquePinData* opaquePinData;
    char* plainTextPin;
};

union PACKED KeySerialNumber {
    uint8_t raw[10];
    struct KeySetId {
        uint8_t issuerId[3];
        uint8_t merchantId;
        uint8_t groupId;
    } ksi;
    struct {
        uint64_t /* ignored */ : 8 * sizeof(uint64_t) - 19 - 21;
        uint64_t counter: 21;
        uint64_t deviceId: 19;
    };
};

struct KernelData {
    enum AuthorisationResponseCode authorisationResponseCode;
    union TerminalVerificationResults tvr;
    union TransactionStatusInformation tsi;
    // FIXME: I have no idea were to put commandTemplate
    union CommandTemplate commandTemplate;

    uint8_t responseData[256];
    struct Aid aidTerminal;

    struct binary staticDataToBeAuthenticated;

    // FIXME: IssuerCountry is actually a card data
    union Country* issuerCountry;

    // Application version number for selected ICC application, specific to the terminal
    // Selected from DF40/DF49
    union binary2 applicationVersionNumber_Terminal; // 9F09

    union Cvm cvmResults;

    struct PinData pinData;
    union KeySerialNumber* ksn;
};

struct E1KernelConfigurationData {
    // [9F01]
    union bcd6 acquirerIdentifier;

    // [9F40]
    union AdditionalTerminalCapabilities additionalTerminalCapabilities;

    // [DF27]
    union ApplicationProfileSettings aps;

    // Application version number for selected ICC application, specific to the terminal
    // Selected from DF40/DF49
    // [9F09]
    union binary2 applicationVersionNumber_Terminal;

    // [DF12]
    union Iso639_1 cardholderDefaultLanguage;

    // CaPublicKeyCheckSum

    // CaPublicKeyExponent

    // [9F22]
    // CaPublicKeyIndex_Terminal

    // CaPublicKeyModulus

    // [E3]
    // CaPublicKeyTable

    // [DF14]
    struct string5 commandKeyClearLabel;

    // [DF15]
    struct string5 commandKeyEnterLabel;

    // [DF16]
    struct string5 commandKeyScrollLabel;

    // [DF1A]
    struct Dol* ddol;

    // [DF44]
    enum FallbackParameterChip fallbackParameterChip;

    // [9F1E]
    struct string8* ifdSerialNumber;

    // [DF1C]
    struct bcd2* maxTargetPercentageForBiasedRandomSelection;

    // [9F15]
    union MerchantCategoryCode merchantCategoryCode;

    // [9F16]
    struct ans15 merchantIdentifier;

    // [9F4E]
    char* merchantNameAndLocation;

    // [DF10]
    union ServiceSettings serviceSettings;

    // [DF1D]
    union bcd* targetPercentageForBiasedRandomSelection;

    // [DF1E]
    union TerminalVerificationResults tacDefault;

    // [DF1F]
    union TerminalVerificationResults tacDenial;

    // [DF20]
    union TerminalVerificationResults tacOnline;

    // [9F33]
    union TerminalCapabilities terminalCapabilities;

    // [9F1A]
    // terminalCountryCode

    // [9F1B]
    union bcd6* terminalFloorLimit;

    // [DF35]
    // terminalTransactionCurrencyCode

    // [DF36]
    union bcd terminalTransactionCurrencyExponent;

    // [9F35]
    union TerminalType terminalType;

    // [DF21]
    union bcd6* thresholdValueForBiasedRandomSelection;

    // [9F53]
    // transactionCategoryCode
};

struct E1KernelTransactionData {
    // [81]
    uint32_t amountAuthorisedBinary;

    // [9F02]
    union bcd6 amountAuthorisedNumeric;

    // [9F04]
    uint32_t amountOtherBinary;

    // [9F03]
    union bcd6 amountOtherNumeric;

    // [9F26]
    // applicationCryptogram;

    // [9F42]
    union CurrencyCode* applicationCurrencyCode;

    // [9F44]
    union bcd* applicationCurrencyExponent;

    // [9F05]
    // applicationDiscretionaryData

    // [5F25]
    union yymmdd* applicationEffectiveDate;

    // [5F24]
    union yymmdd applicationExpirationDate;

};

struct E1KernelActivationData {
    enum KernelMode kernelMode;
    struct FileControlInformation* fci;
    union EmvStatus* sw1Sw2;
    bool* unableToGoOnline;
};

struct E1KernelData {
    struct E1KernelConfigurationData cf;
    struct E1KernelTransactionData td;
    struct E1KernelActivationData ad;
};

// TODO: This struct should completely replace KernelData
struct NewKernelData {
    // NEXO: Kernel ID isn't part of Kernel Data according to nexo, but it's
    // better to have it, for technical reasons, so it will be easier to debug
    enum Kernel kernelId;
    union {
        struct E1KernelData* e1;
    };
};

// Based on nexo-FAST section 13.3
union ApplicationProfileSettingsForCancellation {
    uint8_t raw[2];
    struct {
        uint8_t /* RFU */ : 3;
        uint8_t cancellationOfCashAdvanceAllowed : 1;
        uint8_t cancellationOfPaymentCompletionAllowed : 1;
        uint8_t cancellationOfPreAuthAllowed : 1;
        uint8_t cancellationOfRefundAllowed : 1;
        uint8_t cancellationOfPaymentAllowed : 1;

        // TODO: Use some better names for each bit
        uint8_t /* RFU */ : 3;
        uint8_t cancellationOfReconciledTransactionAllowed : 1;
        uint8_t capturedOnline : 1;
        uint8_t captured : 1;
        uint8_t online : 1;
    };
};

// nexo-FAST v.3.2, section 13.1.78
// [91]
struct IssuerAuthenticationData {
    size_t s;
    union {
        uint8_t raw[16];
    };
};

struct OnlineResponseData {
    enum AuthorisationResponseCode authorisationResponseCode;
    char declineDisplayMessage[40 + 1];
    struct IssuerAuthenticationData* iatd;

    // WARNING: declineDisplayMessageId isn't defined by nexo.
    //
    // According to nexo-FAST v.3.2, section 13.3.50 type of Decline Display
    // Message should be an...40, but in section 12.1.3.2 it's mentioned that
    // HAP in some circumstances should set it to Cardholder Message 0x1D,
    // which is inconsistent with it's definition or common software
    // engeneering practice under any interpetation of the passage. Namely if
    // we interpret it as if HAP should populate this data element with proper
    // translated text based on message id 0x1D, then suddenly HAP needs access
    // to all (or partial) cardholder or attendant translations, which is in
    // scope of SCAP only (no citation), but if we interpret it as if HAP
    // should copy byte 0x1D verbatim into this data element then it's
    // inconsitent with it's definition, because 0x1D isn't an alphanumeric
    // character. As a temporary workaround new optional data element is added:
    // Decline Display Message Id that can hold Cardholder Message Id
    enum CardholderMessage* declineDisplayMessageId;
};

enum Outcome {
    O_NONE

  // Final outcome
  , O_APPROVED
  , O_DECLINED
  , O_ONLINE_REQUEST
  , O_TRY_ANOTHER_INTERFACE
  , O_END_APPLICATION

  // Non final outcome
  , O_SELECT_NEXT
  , O_TRY_AGAIN
};

enum Start {
    NONE
  , A
  , B
  , C
  , D
  , E
  , F
};

enum OnlineResponseType {
    ONLINE_RES_NONE
  , ONLINE_RES_EMV_DATA
  , ONLINE_RES_ANY
};

enum CvmOutcome {
    CVM_NONE
  , CVM_ONLINE_PIN
  , CVM_CONFIRMATION_CODE_VERIFIED
  , CVM_OBTAIN_SIGNATURE
  , CVM_NO_CVM
};

enum AlternateInterfacePreference {
    INTERFACE_PREFERENCE_NONE
  , INTERFACE_PREFERENCE_CONTACT_CHIP
  , INTERFACE_PREFERENCE_MAGSTRIPE
};

enum Receipt {
    RECEIPT_NONE
  , RECEIPT_PRINT
};

struct OutcomeParameters {
    enum Start Start;
    enum OnlineResponseType OnlineResponseType; // It's called Online Response Data in nexo
    enum CvmOutcome Cvm;
    bool UiRequestOnOutcomePresent;
    bool UiRequestOnRestartPresent;
    bool DataRecordPresent;
    bool DiscretionaryDataPresent;
    enum AlternateInterfacePreference AlternateInterfacePreference;
    enum Receipt Receipt;
    uint8_t FieldOffRequest;
    uint8_t RemovalTimeout;
};

// nexo-FAST v.3.2, section 13.1.126 and 13.1.125
// EMV v.4.3 Book 3, section 6.5.8.4
// [77] or [80]
struct ResponseMessageTemplate {
    // [82]
    union ApplicationInterchangeProfile aip;

    // [94]
    struct ApplicationFileLocator afl;

    // TODO: Additional proprietary data objects
    // TODO: Add CVM List
};

// [9F4A]
struct StaticDataAuthenticationTagList {
    union TagExpanded tag;
    struct StaticDataAuthenticationTagList* next;
};

// nexo-FAST v.3.2, section 13.1.121
// EMV v.4.3 Book 3, table 33 and secion 6.5.11.4
// [70]
struct ReadRecordResponseMessageTemplate {
    struct StaticDataAuthenticationTagList* staticDataAuthenticationTagList;
    struct CvmList* cvmList;

    // [9F42]
    union CurrencyCode* applicationCurrencyCode;
};

/* Configuration options defined once per terminal application
 * TODO: Consider generation of thise header file from ASN.1 sources
 */

struct ExtendedAid {
    size_t l_raw;
    union {
        uint8_t raw[16];
        struct {
            uint8_t rid[5];
            uint8_t ext[];// Proprietary Extended Selection 0x9F29
        };
    };
};

struct TerminalListOfAidEntry {
    struct Aid terminalAid; // 0xDF01
    bool applicationSelectionIndicator; // 0xDF02
};

// source: nexo-FAST v.3.2
// size: at least 50
// configuration: Terminal
// presence: M
struct TerminalListOfAid {
    size_t l_entry;
    struct TerminalListOfAidEntry entry[50]; // 0xBF01
};

enum OdaMethod {
    ODA_METHOD_NONE
  , ODA_METHOD_SDA
  , ODA_METHOD_DDA
  , ODA_METHOD_CDA
};

struct TerminalTransactionData {
    bool acquirerPreSelected;
    bcd_t preSelectedAcquirerNumber;
    bool cardholderLanguageIsSelected;
    bool applicationInitialised;
    union bcd transactionCurrencyExponent;
    union bcd6 transactionAmount;
    union bcd6 amountAuthorisedNumeric;
    uint32_t amountAuthorisedBinary;
    union bcd6 cashbackAmount;
    union bcd6 supplementaryAmount;
    bool supplementaryAmountConfirmed;
    bool transactionAmountEntered;
    bool cardholderRequestedChoiceOfApplication;
    bool cardholderRequestedChangeOfApplication;
    bool cardholderAcceptedSelectedApplication;
    bool changeApplicationAllowed;
    bool eeaIdentifiedCard;
    bool cardholderSelectedApplicationOfChoice;
    enum TransactionResult transactionResult;
    enum NokReason nokReason;
    union CurrencyAlpha3 transactionCurrencyCodeAlpha3;
    bool attendantForcedTransactionOnline;
    bool fallbackFlag;
    bool unableToGoOnline;
    enum Kernel kernelId;
    enum KernelMode kernelMode;
    enum Technology technologySelected;
    union ProcessingStatus processingStatus;
    bool exceptionFileCheckPerformed;
    bool exceptionFileMatch;
    bool continueFlag; // Original nexo name 'continue' is a reserved word in C
    bool confirmationByCard;
    bool candidateListHasOneEntry;
    bool pinPadNotWorking;
    struct UiParameters uiParametersForOutcome;
    struct UiParameters uiParametersForRestart;
    struct UiParameters uiParametersForTrxCompletion;
    bool cdaFailed; // FIXME: Delete this parameter
    bool onlineRequired; // FIXME: Delete this parameter
    bool aacReceived; // FIXME: Delete this parameter
    bool tcReceived; // FIXME: Delete thi parameter
    bool uiRequestPostponed;
    bool signatureLine;
    bool signatureLineMerchant;
    bool signatureLineForVoiceAuthorisation;
    char (* pan)[19]; // FIXME: Use proper structure for PAN
    bool isDccEligible;
    bool dccPerformedOnce;
    bool pinBypassAllowed;
    bool* minus; // FIXME: Consider making minus a value, and not a pointer
    bool amountDisplayed;
    union Iso639_1 selectedLanguage;
    enum TerminalErrorReason terminalErrorReason;
    bool terminalErrorIndicator;
    bool transactionConfirmedByCardholder; // EMV also
    struct Track2 track2Data; // FIXME: Use proper structure for Track 2
    const struct Bid* selectedBid;
    bool panEnteredManually;
    struct CombinationListAndParameters* combListWorkingTable;
    bool timeoutIndicator;
    bool noContactlessAllowed;
    union ServiceStartEvents serviceStartEvents;
    enum OdaMethod odaMethodToBePerformed;
    bool pinEntryBypassed;
    bool chipPinEntered;
    union yymmdd transactionDate;

    // FIXME: Consider moving to a different location
    struct EventTable {
        bool Table[E_MAX];
    } event;

    // NOTE: IsCardInReader isn't defined by nexo
    // TODO: Consider making IsCardInReader an atomic variable
    bool isCardInReader;

    // NOTE: forcedTransactionApproval isn't defined by nexo, it's only
    // referenced briefly in nexo-FAST v.3.2 figure 64
    bool forcedTransactionApproval;

    // NOTE: forcedTransactionApproval isn't defined by nexo, it's only
    // referenced briefly in nexo-FAST v.3.2  note 105-10
    bool wasPresentOneCardOnlyMessageDisplayed;

    // FIXME: Consider different place for transactionType
    enum TransactionType transactionType;

    // FIXME: Consider different place for selectedService or even removal,
    // because this information may be available in ServiceConfiguration
    enum ServiceId selectedService;

    // FIXME: Consider removing authorisationResponseCode, as it is alread
    // defined in OnlineResponseData and KernelData, conversly it may be a good
    // idea to leave it here so it will be populated by any of the previous
    // values
    enum AuthorisationResponseCode authorisationResponseCode;

    // FIXME: Same as previous, but may be set by any process
    union TerminalVerificationResults tvr;

    // FIXME: Consider better type for referenceData
    char referenceData[35 + 1];

    // FIXME: Consider different place for selectedApplicationProfileNumber or
    // even removal, because this information may be available in ServiceConfiguration
    bcd_t selectedApplicationProfileNumber;

    // FIXME: Consider different place for Out and Outcome
    enum Outcome outcome;
    struct OutcomeParameters out;
};

enum TerminalTransactionDataTag {
    TTD_ACQUIRER_PRE_SELECTED,
    TTD_AMOUNT_DISPLAYED,
    TTD_APPLICATION_INITIALISED,
    TTD_ATTENDANT_FORCED_TRANSACTIONONLINE,
    TTD_CANDIDATE_LIST_HAS_ONE_ENTRY,
    TTD_CARDHOLDER_ACCEPTED_SELECTED_APPLICATION,
    TTD_CARDHOLDER_LANGUAGE_IS_SELECTED,
    TTD_CARDHOLDER_REQUESTED_CHANGE_OF_APPLICATION,
    TTD_CARDHOLDER_REQUESTED_CHOICE_OF_APPLICATION,
    TTD_CDA_FAILED,
    TTD_CONFIRMATION_BY_CARD,
    TTD_CONTINUE_FLAG,
    TTD_DCC_PERFORMED_ONCE,
    TTD_EXCEPTION_FILE_CHECK_PERFORMED,
    TTD_EXCEPTION_FILE_MATCH,
    TTD_FALLBACK_FLAG,
    TTD_IS_DCC_ELIGIBLE,
    TTD_NO_CONTACTLESS_ALLOWED,
    TTD_ONLINE_REQUIRED,
    TTD_PAN_ENTERED_MANUALLY,
    TTD_PIN_PAD_NOT_WORKING,
    TTD_SIGNATURE_LINE,
    TTD_SIGNATURE_LINE_FOR_VOICE_AUTHORISATION,
    TTD_SIGNATURE_LINE_MERCHANT,
    TTD_TERMINAL_ERROR_INDICATOR,
    TTD_TIMEOUT_INDICATOR,
    TTD_TRANSACTION_AMOUNT_ENTERED,
    TTD_TRANSACTION_CONFIRMED_BY_CARDHOLDER,
    TTD_UI_REQUEST_POSTPONED,
    TTD_UNABLE_TO_GO_ONLINE,

    TTD_MINUS,

    TTD_PAN,

    TTD_SELECTED_BID,

    TTD_MAX
};

# if 0

    const struct Bid* selectedBid;
    enum Kernel kernelId;
    struct UiParameters uiParametersForOutcome;
    struct UiParameters uiParametersForRestart;
    struct UiParameters uiParametersForTrxCompletion;
    union Country selectedLanguage;
    union CurrencyAlpha3 transactionCurrencyCodeAlpha3;
    union ProcessingStatus processingStatus;
    union ServiceStartEvents serviceStartEvents;

    struct bcd2 preSelectedAcquirerNumber;
    union bcd6 cashbackAmount;
    union bcd6 transactionAmount;
    enum KernelMode kernelMode;
    enum NokReason nokReason;
    enum Technology technologySelected;
    enum TerminalErrorReason terminalErrorReason;
    enum TransactionResult transactionResult;
    struct Track2 track2Data; // FIXME: Use proper structure for Track 2
    struct CombinationListAndParameters* combListWorkingTable;
#endif

#endif // TYPES_H
