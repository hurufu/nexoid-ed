#pragma once

#include "common.h"

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

extern struct CandidateList* g_CandidateList; // -
