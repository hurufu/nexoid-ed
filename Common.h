#pragma once

#include <stdbool.h>
#include <stddef.h>

enum FunctionResult {
    FUNRES_NOK
  , FUNRES_OK
  , FUNRES_REFERENCE_ENTRY
  , FUNRES_ACCEPT
  , FUNRES_NOT_FOUND
};

enum TransactionResult {
    TRANRES_NOT_SUPPORTED
  , TRANRES_ABORTED
};

enum Service {
    PAYMENT
  , PREAUTH_COMPLETION
};

union TerminalSetings {
    unsigned char raw[1];
    struct {
        unsigned char retrievePreauth : 1;
    };
};

union ServiceStartEvent {
    unsigned char raw[1];
    struct {
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
