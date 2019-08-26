#include "common.h"
#include "utils.h"
#include <stdio.h>

#define TRACE(Fmt, ...)\
    printf(Fmt"\t%s\t%d\t%s\n", ##__VA_ARGS__, __FILE__, __LINE__, __func__)

const char*
ProcedureResult_tostring(const enum ProcedureResult f) {
    switch (f) {
        case PR_END_APPLICATION: return "PR_END_APPLICATION";
        case PR_TAP_AGAIN: return "PR_TAP_AGAIN";
        case PR_NOK: return "F_NOK";
        case PR_OK: return "F_OK";
        case PR_REFERENCE_ENTRY: return "F_REFERENCE_ENTRY";
        case PR_ACCEPT: return "F_ACCEPT";
        case PR_NOT_FOUND: return "F_NOT_FOUND";
        case PR_NOT_SUPPORTED: return "F_NOT_SUPPORTED";
        case PR_NON_EMV: return "PR_NON_EMV";
        case PR_MATCH: return "PR_MATCH";
        case PR_NO_MATCH: return "PR_NO_MATCH";
        case PR_DONE: return "PR_DONE";
        case PR_ONLINE: return "PR_ONLINE";
        case PR_UNABLE_TO_GO_ONLINE: return "PR_UNABLE_TO_GO_ONLINE";
        case PR_CONDITIONS_SATISFIED: return "PR_CONDITIONS_SATISFIED";
        case PR_CONDITIONS_NOT_SATISFIED: return "PR_CONDITIONS_NOT_SATISFIED";
        case PR_REINITIALISE: return "PR_REINITIALISE";
        case PR_NOT_IMPLEMENTED: return "PR_NOT_IMPLEMENTED";
        case PR_UNINITIALISED: return "PR_UNINITIALISED";
        case PR_NEW_EVENT: return "PR_NEW_EVENT";
        case PR_INTERNAL_INCONSISTENCY: return "PR_INTERNAL_INCONSISTENCY";
        case PR_REBOOT: return "PR_REBOOT";
        case PR_TERMINATE: return "PR_TERMINATE";
        case PR_SHUTDOWN: return "PR_SHUTDOWN";
        case PR_STARTUP_SEQUENCE: return "PR_STARTUP_SEQUENCE";
        case PR_MANUAL_ENTRY: return "PR_MANUAL_ENTRY";
        case PR_RETRY_AFTER_CONTACTLESS: return "PR_RETRY_AFTER_CONTACTLESS";
        case PR_FALLBACK: return "PR_FALLBACK";
        case PR_MAX:
            break;
    }
    return NULL;
}

const char*
CardholderMessage_tostring(const enum CardholderMessage m) {
    switch (m) {
        case CRDHLDR_ACT_NONE: return "CRDHLDR_ACT_NONE";
        case CRDHLDR_EMV_APPROVED: return "CRDHLDR_EMV_APPROVED";
        case CRDHLDR_EMV_VOICE_AUTH_REQUIRED: return "CRDHLDR_EMV_VOICE_AUTH_REQUIRED";
        case CRDHLDR_EMV_CARD_ERROR: return "CRDHLDR_EMV_CARD_ERROR";
        case CRDHLDR_EMV_DECLINED: return "CRDHLDR_EMV_DECLINED";
        case CRDHLDR_EMV_INCORRECT_PIN: return "CRDHLDR_EMV_INCORRECT_PIN";
        case CRDHLDR_EMV_INSERT_CARD: return "CRDHLDR_EMV_INSERT_CARD";
        case CRDHLDR_EMV_PLEASE_WAIT: return "CRDHLDR_EMV_PLEASE_WAIT";
        case CRDHLDR_EMV_PROCESSING_ERROR: return "CRDHLDR_EMV_PROCESSING_ERROR";
        case CRDHLDR_EMV_REMOVE_CARD: return "CRDHLDR_EMV_REMOVE_CARD";
        case CRDHLDR_EMV_USE_CHIP_READER: return "CRDHLDR_EMV_USE_CHIP_READER";
        case CRDHLDR_EMV_USE_MAG_STRIPE: return "CRDHLDR_EMV_USE_MAG_STRIPE";
        case CRDHLDR_EMV_TRY_AGAIN: return "CRDHLDR_EMV_TRY_AGAIN";
        case CRDHLDR_MSG_WELCOME: return "CRDHLDR_MSG_WELCOME";
        case CRDHLDR_MSG_PRESENT_CARD: return "CRDHLDR_MSG_PRESENT_CARD";
        case CRDHLDR_MSG_PROCESSING: return "CRDHLDR_MSG_PROCESSING";
        case CRDHLDR_MSG_CARD_READ_OK_REMOVE_CARD: return "CRDHLDR_MSG_CARD_READ_OK_REMOVE_CARD";
        case CRDHLDR_MSG_PLEASE_INSERT_OR_SWIPE_CARD: return "CRDHLDR_MSG_PLEASE_INSERT_OR_SWIPE_CARD";
        case CRDHLDR_MSG_PLEASE_INSERT_ONE_CARD_ONLY: return "CRDHLDR_MSG_PLEASE_INSERT_ONE_CARD_ONLY";
        case CRDHLDR_MSG_APPROVED_PLEASE_SIGN: return "CRDHLDR_MSG_APPROVED_PLEASE_SIGN";
        case CRDHLDR_MSG_AUTHORISING_PLEASE_WAIT: return "CRDHLDR_MSG_AUTHORISING_PLEASE_WAIT";
        case CRDHLDR_MSG_INSERT_SWIPE_OR_TRY_ANOTHER_CARD: return "CRDHLDR_MSG_INSERT_SWIPE_OR_TRY_ANOTHER_CARD";
        case CRDHLDR_MSG_PLEASE_INSERT_CARD: return "CRDHLDR_MSG_PLEASE_INSERT_CARD";
        case CRDHLDR_ACT_CLEAR: return "CRDHLDR_ACT_CLEAR";
        case CRDHLDR_MSG_SEE_PHONE_FOR_INSTRUCTIONS: return "CRDHLDR_MSG_SEE_PHONE_FOR_INSTRUCTIONS";
        case CRDHLDR_MSG_PRESENT_CARD_AGAIN: return "CRDHLDR_MSG_PRESENT_CARD_AGAIN";
        case CRDHLDR_MSG_CARD_WRONG_WAY_OR_NO_CHIP: return "CRDHLDR_MSG_CARD_WRONG_WAY_OR_NO_CHIP";
        case CRDHLDR_MSG_READ_ERROR: return "CRDHLDR_MSG_READ_ERROR";
        case CRDHLDR_MSG_AMOUNT: return "CRDHLDR_MSG_AMOUNT";
        case CRDHLDR_MSG_MAX_AMOUNT: return "CRDHLDR_MSG_MAX_AMOUNT";
        case CRDHLDR_MSG_ENTER_PIN: return "CRDHLDR_MSG_ENTER_PIN";
        case CRDHLDR_MSG_ENTER: return "CRDHLDR_MSG_ENTER";
        case CRDHLDR_MSG_AMOUNT_AUTHORISED: return "CRDHLDR_MSG_AMOUNT_AUTHORISED";
        case CRDHLDR_MSG_LEFT_TO_BE_PAID: return "CRDHLDR_MSG_LEFT_TO_BE_PAID";
        case CRDHLDR_MSG_TRANSACTION_ABORTED: return "CRDHLDR_MSG_TRANSACTION_ABORTED";
        case CRDHLDR_MSG_PAYMENT_APPROVED_CASHBACK_DECLINED: return "CRDHLDR_MSG_PAYMENT_APPROVED_CASHBACK_DECLINED";
        case CRDHLDR_MSG_CHIP_ERROR_RE_ENTER_PIN: return "CRDHLDR_MSG_CHIP_ERROR_RE_ENTER_PIN";
        case CRDHLDR_MSG_PRESENT_CARD_OR_USE_MAGSTRIPE: return "CRDHLDR_MSG_PRESENT_CARD_OR_USE_MAGSTRIPE";
        case CRDHLDR_MSG_INSERT_OR_PRESENT_CARD: return "CRDHLDR_MSG_INSERT_OR_PRESENT_CARD";
        case CRDHLDR_MSG_INSERT_OR_SWIPE_CARD: return "CRDHLDR_MSG_INSERT_OR_SWIPE_CARD";
        case CRDHLDR_MSG_NO_PIN: return "CRDHLDR_MSG_NO_PIN";
        case CRDHLDR_MSG_DIFFERENT_CHOICE: return "CRDHLDR_MSG_DIFFERENT_CHOICE";
        case CRDHLDR_MSG_CHOOSE_APPLICATION: return "CRDHLDR_MSG_CHOOSE_APPLICATION";
        case CRDHLDR_MSG_AMOUNT_ESTIMATED: return "CRDHLDR_MSG_AMOUNT_ESTIMATED";
        case CRDHLDR_MSG_FINAL_AMOUNT: return "CRDHLDR_MSG_FINAL_AMOUNT";
        case CRDHLDR_MSG_AMOUNT_INCREMENT: return "CRDHLDR_MSG_AMOUNT_INCREMENT";
        case CRDHLDR_MSG_AMOUNT_DECREMENT: return "CRDHLDR_MSG_AMOUNT_DECREMENT";
        case CRDHLDR_MSG_PRINTER_OUT_OF_ORDER: return "CRDHLDR_MSG_PRINTER_OUT_OF_ORDER";
        case CRDHLDR_MSG_TIP: return "CRDHLDR_MSG_TIP";
        case CRDHLDR_MSG_CASHBACK: return "CRDHLDR_MSG_CASHBACK";
        case CRDHLDR_MSG_PAYMENT: return "CRDHLDR_MSG_PAYMENT";
        case CRDHLDR_MSG_TOTAL: return "CRDHLDR_MSG_TOTAL";
        case CRDHLDR_SRC_UI_PARAMETERS_FOR_OUTCOME: return "CRDHLDR_SRC_UI_PARAMETERS_FOR_OUTCOME";
        case CRDHLDR_SRC_UI_PARAMETERS_FOR_RESTART: return "CRDHLDR_SRC_UI_PARAMETERS_FOR_RESTART";
        case CRDHLDR_SRC_UI_PARAMETERS_FOR_COMPLETION: return "CRDHLDR_SRC_UI_PARAMETERS_FOR_COMPLETION";
        case CRDHLDR_SRC_DECLINE_DISPLAY_MESSAGE: return "CRDHLDR_SRC_DECLINE_DISPLAY_MESSAGE";
        case CRDHLDR_SRC_SELECTED_SERVICE: return "CRDHLDR_SRC_SELECTED_SERVICE";
        case CRDHLDR_SRC_CARDHOLDER_MESSAGE: return "CRDHLDR_SRC_CARDHOLDER_MESSAGE";
        case CRDHLDR_SRC_NOK_REASON: return "CRDHLDR_SRC_NOK_REASON";
        case CRDHLDR_SSN_CARD_REMOVAL_REQUESTED: return "CRDHLDR_SSN_CARD_REMOVAL_REQUESTED";
        case CRDHLDR_SSN_CARD_REMOVED: return "CRDHLDR_SSN_CARD_REMOVED";
    }
    return NULL;
}

const char*
TransactionResult_tostring(const enum TransactionResult t) {
    switch (t) {
        case T_NONE: return "T_NONE";
        case T_NOT_SUPPORTED: return "T_NOT_SUPPORTED";
        case T_ABORTED: return "T_ABORTED";
        case T_APPROVED: return "T_APPROVED";
        case T_DECLINED: return "T_DECLINED";
        case T_PARTIALLY_APPROVED: return "T_PARTIALLY_APPROVED";
        case T_VOICE_AUTHORISATION: return "T_VOICE_AUTHORISATION";
        case T_PAYMENT_PART_ONLY: return "T_PAYMENT_PART_ONLY";
        case T_MAX:
            break;
    }
    return NULL;
}

const char*
NokReason_tostring(const enum NokReason n) {
    switch (n) {
        case N_NONE: return "N_NONE";
        case N_NOT_IMPLEMENTED: return "N_NOT_IMPLEMENTED";
        case N_ORIGINAL_TRX_NOT_FOUND: return "N_ORIGINAL_TRX_NOT_FOUND";
        case N_TECHNICAL_ERROR: return "N_TECHNICAL_ERROR";
        case N_MISSING_DATA: return "N_MISSING_DATA";
        case N_NO_PERMISSION: return "N_NO_PERMISSION";
        case N_CONFIGURATION_ERROR: return "N_CONFIGURATION_ERROR";
        case N_AMOUNT_ERROR: return "N_AMOUNT_ERROR";
        case N_KERNEL_ERROR: return "N_KERNEL_ERROR";
        case N_DATA_ERROR: return "N_DATA_ERROR";
        case N_NO_CARD_INSERTED: return "N_NO_CARD_INSERTED";
        case N_CANCELLED: return "N_CANCELLED";
        case N_CARD_MISSING: return "N_CARD_MISSING";
        case N_NO_PROFILE: return "N_NO_PROFILE";
        case N_ABORTED: return "N_ABORTED";
        case N_TIMEOUT: return "N_TIMEOUT";
        case N_MAX:
            break;
    }
    return NULL;
}

const char*
ServiceId_tostring(const enum ServiceId s) {
    switch (s) {
        case S_NONE: return "S_NONE";
        case S_PAYMENT: return "S_PAYMENT";
        case S_REFUND: return "S_REFUND";
        case S_CANCELLATION: return "S_CANCELLATION";
        case S_PRE_AUTH: return "S_PRE_AUTH";
        case S_UPDATE_PRE_AUTH: return "S_UPDATE_PRE_AUTH";
        case S_PAYMENT_COMPLETION: return "S_PAYMENT_COMPLETION";
        case S_CASH_ADVANCE: return "S_CASH_ADVANCE";
        case S_DEFFERED_PAYMENT: return "S_DEFFERED_PAYMENT";
        case S_DEFFERED_PAYMENT_COMPLETION: return "S_DEFFERED_PAYMENT_COMPLETION";
        case S_VOICE_AUTHORISATION: return "S_VOICE_AUTHORISATION";
        case S_CARDHOLDER_DETECTION: return "S_CARDHOLDER_DETECTION";
        case S_CARD_VALIDITY_CHECK: return "S_CARD_VALIDITY_CHECK";
        case S_NO_SHOW: return "S_NO_SHOW";
        case S_MAX: return "S_MAX";
    }
    return NULL;
}

static struct small_string
byte_tostring(const unsigned char b) {
    struct small_string ret;
    snprintf(ret.hex, elementsof(ret.hex), "%02x", b);
    return ret;
}

struct small_string
TerminalSettings_tostring(const union TerminalSettings t) {
    return byte_tostring(t.raw[0]);
}

struct small_string
ServiceStartEvent_tostring(const union ServiceStartEvents s) {
    return byte_tostring(s.raw[0]);
}

void ctd_print(const struct CurrentTransactionData* const ctd) {
    printf("CTD: "
           ", TransactionResult: %s"
           ", NokReason: %s"
           " }\n",
        TransactionResult_tostring(ctd->TransactionResult),
        NokReason_tostring(ctd->NokReason)
    );
}
