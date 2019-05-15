#include "Common.h"
#include "utils.h"
#include <stdio.h>

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
        case PR_MAX:
            break;
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
        case T_MAX:
            break;
    }
    return NULL;
}

const char*
NokReason_tostring(const enum NokReason n) {
    switch (n) {
        case N_NOT_IMPLEMENTED: return "N_NOT_IMPLEMENTED";
        case N_ORIGINAL_TRX_NOT_FOUND: return "N_ORIGINAL_TRX_NOT_FOUND";
        case N_TECHNICAL_ERROR: return "N_TECHNICAL_ERROR";
        case N_MISSING_DATA: return "N_MISSING_DATA";
        case N_NO_PERMISSION: return "N_NO_PERMISSION";
        case N_CONFIGURATION_ERROR: return "N_CONFIGURATION_ERROR";
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
