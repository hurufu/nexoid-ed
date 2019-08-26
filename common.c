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
        case CRDHLDR_MSG_CARD_ERROR: return "CRDHLDR_MSG_CARD_ERROR";
        case CRDHLDR_MSG_WELCOME: return "CRDHLDR_MSG_WELCOME";
        case CRDHLDR_MSG_NONE: return "CRDHLDR_MSG_NONE";
        case CRDHLDR_MSG_CHOOSE_APPLICATION: return "CRDHLDR_MSG_CHOOSE_APPLICATION";
        case CRDHLDR_MSG_PRINTER_OUT_OF_ORDER: return "CRDHLDR_MSG_PRINTER_OUT_OF_ORDER";
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
