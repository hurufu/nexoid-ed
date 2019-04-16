#include "Common.h"
#include "utils.h"
#include <stdio.h>

_Thread_local struct Ctd* tg_ctd;

const char*
FunctionResult_tostring(const enum FunctionResult f) {
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
