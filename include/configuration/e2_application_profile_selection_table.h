#pragma once

#include "termainal.h"
#include "utils.h"
#include "emv.h"
#include "types.h"

struct BankIdentifierCodeList {
    struct BankIdentifierCode value;
    struct BankIdentifierCodeList* next;
};

struct IssuerCountryCodeAlpha2List {
    union Country value;
    struct IssuerCountryCodeAlpha2List* next;
};

struct IssuerCountryCodeAlpha3List {
    // FIXME: IssuerCountryCodeAlpha3List isn't defined
    struct IssuerCountryCodeAlpha2List* next;
};

struct IssuerIdentificationNumberList {
    struct bcd3 value;
    struct IssuerIdentificationNumberList* next;
};

struct IssuerIdentificationMaskList {
    uint8_t value[3];
    struct IssuerIdentificationMaskList* next;
};

struct IbanComparisonValueList {
    struct ans_34 value;
    struct IbanComparisonValueList* next;
};

struct KernelIdList {
    enum Kernel value;
    struct KernelIdList* next;
};

struct EeaProductIdentificationList {
    uint8_t value[5];
    struct EeaProductIdentificationList* next;
};

// source: nexo-FAST v.3.2 section 13.3.14
// size: at least 60
// presence: M
// configuration: Terminal
// [E2]
struct ApplicationProfileSelectionTable {
    struct Aid applicationProfileAid;
    bcd_t profileNumber;
    union ConfiguredServices supportedServices;

    bcd_t* applicationProfileAcquirerNumber;
    bool* aidMatchCriteria;
    struct BankIdentifierCodeList* bic;
    struct IssuerCountryCodeAlpha2List* issuerCountryCodeAlpha2;
    struct IssuerCountryCodeAlpha3List* issuerCountryCodeAlpha3;
    struct IssuerIdentificationNumberList* iin;
    struct IssuerIdentificationMaskList* iinMask;
    struct IbanComparisonValueList* ibanComparisonValue;
    struct as_34* ibanMask;
    union Amount* applicationProfileAmount;
    bool* cashBackPresent;
    enum TechnologySelected* technologyOfProfile;
    struct KernelIdList* applicationProfileKernelId;
    struct EeaProductIdentificationList* productTypeComparisonValue;
    uint8_t (*productTypeMask)[5];

    // TODO: Optional other private tags

    struct ApplicationProfileSelectionTable* next;
};
