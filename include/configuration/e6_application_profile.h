#pragma once

#include "c2.h"
#include "c4.h"
#include "emv.h"

struct bcd4 {
    unsigned char v[4];
};

// TODO: Add tlv retrieval by tag
// FIXME: Consider header generation from ASN.1 module

enum PACKED FallbackParameterChip {
    FALLBACK_TRANSACTION_ALLOWED_FOR_CHIP = 0x01
};

// source nexo-IS 4.0
// configuration: Application Profile
// presence: M
struct ApplicationProfile {
    // Unique Application Profile ID:
    bcd_t profileNumber;
    bcd_t acquirerNumber;

    // Application Profile Parameters:
    struct bcd6 acquirerIdentifier;
    void* additionalDataElements; // TODO: Define EF template
    union TerminalVerificationResults* additionalRestrictionsForForcedAcceptance;
    union AdditionalTerminalCapabilities* additionalTerminalCapabilities;
    struct bcd2 terminalCountryCode;
    struct ans_16 applicationLabelDefault;
    union ApplicationProfileSettings applicationProfileSettings;
    union ApplicationProfileSettingsForCancellation* applicationProfileSettingsForCancellation;
    union Amount* cashAdvanceMaximumAmount;
    union Amount* cashbackMaximumAmount;
    union CvmCapability* cvmCapabilityCvmRequired;
    union CvmCapability* cvmCapabilityNoCvmRequired;
    union MagStripeCvmCapability* magStripeCvmCapabilityCvmRequired;
    union MagStripeCvmCapability* magStripeCvmCapabilityNoCvmRequired;

    // missing Default DDA DOL (DF1A)
    bcd_t holdTimeValue;
    union Kernel2Configuration* kernel2Configuration;
    union Kernel4ReaderCapabilities* kernel4ReaderCapabilities;
    union Kernel4Settings* kernel4Settings;
    union MsrCvmCapability* msrCvmCapabilityCvmRequired;
    union MsrCvmCapability* msrCvmCapabilityNoCvmRequired;
    struct bcd2* maxTargetPercentageForBiasedRandomSelection;
    struct bcd4 merchantCategoryCode;
    uint8_t (* merchantCustomData)[20];
    char merchantIdentifier[15];
    char* merchantNameAndLocation;

    enum FallbackParameterChip fallbackParameterChip;
};
