#pragma once

#include <stdbool.h>
#include <stddef.h>

enum FunctionResult {
    R_OK
  , R_NOK
  , R_NON_EMV
  , R_TAP_AGAIN
  , R_END_APPLICATION
  , R_REFERENCE_ENTRY
  , R_ACCEPT
  , R_NOT_FOUND
  , R_NOT_SUPPORTED
};

enum ServiceId {
    S_NONE = 0x00
  , S_PAYMENT = 0x01
  , S_REFUND = 0x02
  , S_CARD_VALIDITY_CHECK = 0x12
} __attribute__((__packed__));

enum NokReason {
    N_NOT_IMPLEMENTED
};

enum Outcome {
    O_ONLINE_REQUEST
};

enum TransactionResult {
    T_NONE
  , T_ABORTED
  , T_NOT_SUPPORTED
  , T_APPROVED
};

enum TransactionType {
    TT_UNKNOWN
};

struct Out {
    enum Start {
        NONE,
        A,
        B,
        C,
        D,
        E,
        F
    } Start;
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
        enum ServiceId v[];
    }* selectedService;
    enum TransactionResult tRes;
};

struct small_string {
    char hex[sizeof(int)];
};

struct Ctd {
    const unsigned char (* const CvcDefaultAmount)[6];
    const int KernelId;
    const enum Outcome Outcome;
    const struct Out Out;
    const unsigned char (* TransactionAmount)[6];
    enum TransactionResult TransactionResult;
    const enum TransactionType TransactionType;

    enum FunctionResult Result;

    enum NokReason NokReason;
    const unsigned char* const ServiceSettings;
    const unsigned char* const ServiceStartEvents;
    bool TransactionAmountEntered;

    const enum ServiceId SelectedService;
};

extern _Thread_local struct Ctd* tg_ctd;

const char* FunctionResult_tostring(enum FunctionResult f);
const char* TransactionResult_tostring(enum TransactionResult);
struct small_string TerminalSettings_tostring(union TerminalSettings);
struct small_string ServiceStartEvent_tostring(union ServiceStartEvents);
void ctd_print(const struct Ctd*);
