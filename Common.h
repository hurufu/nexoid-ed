#pragma once

#include <stdbool.h>
#include <stddef.h>

enum FunctionResult {
    FUNRES_NOK
  , FUNRES_OK
  , FUNRES_REFERENCE_ENTRY
  , FUNRES_ACCEPT
  , FUNRES_NOT_FOUND
  , FUNRES_NOT_SUPPORTED
};

enum TransactionResult {
    TRANRES_NOT_SUPPORTED
  , TRANRES_ABORTED
  , TRANRES_APPROVED
};

enum Service {
    PAYMENT
  , PREAUTH_COMPLETION
};

union TerminalSettings {
    unsigned char raw[1];
    struct {
        unsigned char : 7;
        unsigned char retrievePreauth : 1;
    };
};

union ServiceStartEvents {
    unsigned char raw[1];
    struct {
        unsigned char : 7;
        unsigned char referenceEntry : 1;
    };
};

struct SearchLogCriteria {
    bool closed;
    char* referenceData;
    struct {
        size_t s;
        enum Service v[];
    }* selectedService;
    enum TransactionResult tRes;
};

struct small_string {
    char hex[sizeof(int)];
};

const char* FunctionResult_tostring(enum FunctionResult f);
const char* TransactionResult_tostring(enum TransactionResult);
struct small_string TerminalSettings_tostring(union TerminalSettings);
struct small_string ServiceStartEvent_tostring(union ServiceStartEvents);
