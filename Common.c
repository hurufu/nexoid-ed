#include "Common.h"
#include "utils.h"
#include <stdio.h>

const char*
FunctionResult_tostring(const enum FunctionResult f) {
    switch (f) {
        case FUNRES_NOK: return "FUNRES_NOK";
        case FUNRES_OK: return "FUNRES_OK";
        case FUNRES_REFERENCE_ENTRY: return "FUNRES_REFERENCE_ENTRY";
        case FUNRES_ACCEPT: return "FUNRES_ACCEPT";
        case FUNRES_NOT_FOUND: return "FUNRES_NOT_FOUND";
        case FUNRES_NOT_SUPPORTED: return "FUNRES_NOT_SUPPORTED";
    }
    return NULL;
}

const char*
TransactionResult_tostring(const enum TransactionResult t) {
    switch (t) {
        case TRANRES_NOT_SUPPORTED: return "TRANRES_NOT_SUPPORTED";
        case TRANRES_ABORTED: return "TRANRES_ABORTED";
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
TerminalSettings_tostring(const union TerminalSetings t) {
    return byte_tostring(t.raw[0]);
}

struct small_string
ServiceStartEvent_tostring(const union ServiceStartEvent s) {
    return byte_tostring(s.raw[0]);
}
