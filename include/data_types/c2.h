#pragma once

#include "types.h"

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
