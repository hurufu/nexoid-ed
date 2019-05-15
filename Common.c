#include "Common.h"
#include "utils.h"
#include <stdio.h>

const char*
ProcedureResult_tostring(const enum ProcedureResult f) {
    switch (f) {
        case R_END_APPLICATION: return "R_END_APPLICATION";
        case R_TAP_AGAIN: return "R_TAP_AGAIN";
        case R_NOK: return "F_NOK";
        case R_OK: return "F_OK";
        case R_REFERENCE_ENTRY: return "F_REFERENCE_ENTRY";
        case R_ACCEPT: return "F_ACCEPT";
        case R_NOT_FOUND: return "F_NOT_FOUND";
        case R_NOT_SUPPORTED: return "F_NOT_SUPPORTED";
        case R_NON_EMV: return "R_NON_EMV";
        case R_MATCH: return "R_MATCH";
        case R_NO_MATCH: return "R_NO_MATCH";
        case R_DONE: return "R_DONE";
        case R_ONLINE: return "R_ONLINE";
        case R_UNABLE_TO_GO_ONLINE: return "R_UNABLE_TO_GO_ONLINE";
        case R_START_CONDITIONS_SATISFIED: return "R_START_CONDITIONS_SATISFIED";
        case R_REINITIALISE: return "R_REINITIALISE";
        case R_NOT_IMPLEMENTED: return "R_NOT_IMPLEMENTED";
        case R_UNINITIALISED: return "R_UNINITIALISED";
        case R_MAX:
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
        case N_TECHNNICAL_ERROR: return "N_TECHNNICAL_ERROR";
        case N_MISSING_DATA: return "N_MISSING_DATA";
        case N_NO_PERMISSION: return "N_NO_PERMISSION";
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
