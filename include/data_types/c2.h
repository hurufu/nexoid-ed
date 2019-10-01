#pragma once

#include "utils.h"

#include <stdint.h>

// FIXME: All bitmasks are little endian only

union Kernel2Configuration {
    uint8_t raw[1];
    struct {
/*1-3*/ uint8_t /* RFU */ : 3;
/*4*/   uint8_t /* Reserved for Payment System */ : 1;
/*5*/   uint8_t relayResistanceProtocolSupported : 1;
/*6*/   uint8_t onDeviceCvmSupported : 1;
/*7*/   uint8_t ctlsEmvModeNotSupported : 1;
/*8*/   uint8_t ctlsMsModeNotSupported : 1;
    };
};

// TODO: Consider moving this to common EMV header

union CvmCapability {
    uint8_t raw[1];
    struct {
/*1-3*/ uint8_t /* RFU */ : 3;
/*4*/   uint8_t noCvm : 1;
/*5*/   uint8_t encipheredPinForOfflineVerification : 1;
/*6*/   uint8_t signatureOnPaper : 1;
/*7*/   uint8_t encipheredPinForOnlineVerification : 1;
/*8*/   uint8_t plainTextForIccVerification : 1;
    };
};

union MagStripeCvmCapability {
    uint8_t raw[1];
    struct {
/*1-4*/ uint8_t /* RFU */ : 4;
        enum PACKED {
            MSR_CVM_NO_CVM = 0x0
          , MSR_CVM_OBTAIN_SIGNATURE = 0x1
          , MSR_CVM_ONLINE_PIN = 0x2
          , MSR_CVM_NA = 0xF
/*5-8*/ } e : 4;
    };
};
