#pragma once

// Data that is used only by Application, Kernel and Applicaion Profile
// Selection

// FIXME: Definition of ApplicationLabelList is probably wrong
struct ApplicationLabelList {
    struct Aid adf;
    struct string16 applicationLabel;
    struct string16 applicationPreferredName;
    enum IssuerCodeTableIndex issuerCodeTableIndex;
    struct ApplicationLabelList* next;
};

struct ApplicationKernelAndAppProfileSelection {
    bool cardholderConfirmedOnce;
    struct ApplicationLabelList* applicationLabelList;
    unsigned char panMatchLength; // integer
};
