#pragma once

#include "tag_retrieval.h"

#include <inttypes.h>

enum ApplicationProfileTag {
    TAG_EMV_ACQUIRER_IDENTIFIER = 0x9F10
  , TAG_EMV_CVM_CAPABILITY_CVM_REQUIRED = 0xDF8118
  , TAG_EMV_CVM_CAPABILITY_NO_CVM_REQUIRED = 0xDF8119
  , TAG_EMV_DDOL = 0xDF1A
  , TAG_EMV_HOLD_TIME_VALUE = 0xDF8130
};

struct ApplicationProfile {
    uint8_t acquirerIdentifier[6];
    bool cvmCapabilityCvmRequired;
    bool cvmCapabilityNoCvmRequired;
    struct {
        size_t l;
        uint8_t* e;
    } ddol;
    uint8_t holdTimeValue;
};

struct tlv* ApplicationProfile_gettag(const struct ApplicationProfile*);
