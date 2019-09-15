#pragma once

#include "c2.h"
#include "c4.h"
#include "emv.h"

#include <stdint.h>
#include <stddef.h>

// TODO: Add tlv retrieval by tag
// WARNING: Tag values will be probably reversed in the future
// FIXME: Consider header generation from ASN.1 module

// _EMV_ - Data elements defined by EMV or ISO and used by nexo-FAST (section 13.1)
// _ENU_ - Data elements defined by EMV and not used by nexo-FAST (section 13.2)
// _NXO_ - Data elements defined by nexo-FAST for use outside of kernel processing (section 13.3)
// _NXE_ - Data elements defined by nexo-FAST for use in kernel E (section 13.4)
// _NNA_ - Not know, not applicable
// _NIS_ - Defined by nIS only

enum ApplicationProfileTag {
    // Unique Application Profile ID:
    T_AP_NNA_PROFILE_NUMBER = 0xDF19
  , T_AP_NNA_ACQUIRER_NUMBER = 0xDF1B

    // Application Profile Parameters:
  , T_AP_EMV_ACQUIRER_IDENTIFIER = 0x9F10
  , T_AP_NNA_ADDITIONAL_DATA_ELEMENTS = 0xEF
  , T_AP_NXO_ADDITIONAL_RESTRICTIONS_OF_FORCED_ACCEPTANCE = 0xDF26
  , T_AP_EMV_ADDITIONAL_TERMINAL_CAPABILITIES = 0x9F40
  , T_AP_EMV_TERMINAL_COUNTRY_CODE = 0x9F1A
  , T_AP_NXO_APPLICATION_LABEL_DEFAULT = 0xDF41
  , T_AP_NXO_APPLICATION_PROFILE_SETTINGS = 0xDF27
  , T_AP_NXO_APPLICATION_PROFILE_SETINGS_FOR_CANCELLATION = 0xDF28
  , T_AP_NXO_CASH_ADVANCE_MAXIMUM_AMOUNT = 0xDF29
  , T_AP_EMV_CVM_CAPABILITY_CVM_REQUIRED = 0xDF8118
  , T_AP_EMV_CVM_CAPABILITY_NO_CVM_REQUIRED = 0xDF8119
  , T_AP_EMV_DDOL = 0xDF1A
  , T_AP_EMV_HOLD_TIME_VALUE = 0xDF8130
  , T_AP_EMV_KERNEL_2_CONFIGURATION = 0xDF811B
  , T_AP_EMV_KERNEL_4_READER_CAPABILITIES = 0x9F6D
};

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

    struct ApplicationProfile_ddol {
        size_t l;
        uint8_t* e;
    } ddol; // Isn't defined in nIS
    bcd_t holdTimeValue;
    union Kernel2Configuration* kernel2Configuration;
    union Kernel4ReaderCapabilities* kernel4ReaderCapabilities;
};
