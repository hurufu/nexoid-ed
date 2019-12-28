#pragma once

#include <stdint.h>
#include "utils.h"

// nexo-FAST v.3.2, section 13.1.16
// EMV v.4.3 Book 3, table 37
// [82]
union PACKED ApplicationInterchangeProfile {
    uint8_t a[2];
    struct {
        uint8_t cdaSupported : 1;
        uint8_t /* RFU */ : 1;
        uint8_t issuerAuthenticationIsSupported : 1; // aka EXTERNAL AUTHENTICATE is supported
        uint8_t terminalRiskManagementIsToBePerformed : 1;
        uint8_t cardholderVerificationIsSupported : 1;
        uint8_t ddaSupported : 1;
        uint8_t sdaSupported : 1;
        uint8_t /* RFU */ : 1;

        uint8_t /* RFU */ : 7;
        uint8_t /* Reserved for use by the EMV Contactless Specifications */ : 1;
    };
};

// nexo-FAST v.3.2, section 13.1.13
// EMV v.4.3 Book 3, section 10.2
// [94]
struct PACKED ApplicationFileLocator {
    size_t raw_size;
    union {
        uint8_t raw[252];
        struct {
            uint8_t zero : 3;
            uint8_t sfi : 5;
            uint8_t firstRecordNumber;
            uint8_t lastRecordNumber;
            uint8_t numberOfOdaAuthenticatedRecords;
        } a[252 / 4];
    };
};

// nexo-FAST v.3.2, section 13.1.126 and 13.1.125
// EMV v.4.3 Book 3, section 6.5.8.4
// [77] or [80]
struct ResponseMessageTemplate {
    // [82]
    union ApplicationInterchangeProfile aip;

    // [94]
    struct ApplicationFileLocator afl;

    // TODO: Additional proprietary data objects
};
