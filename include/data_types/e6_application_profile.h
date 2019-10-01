#pragma once

#include "c2.h"
#include "c4.h"
#include "emv.h"

// TODO: Add tlv retrieval by tag
// FIXME: Consider header generation from ASN.1 module

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

    bcd_t holdTimeValue;
    union Kernel2Configuration* kernel2Configuration;
    union Kernel4ReaderCapabilities* kernel4ReaderCapabilities;
};
