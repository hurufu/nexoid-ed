#pragma once

// nexo-FAST v.3.2, section 13.1.78
// [91]
struct IssuerAuthenticationData {
    size_t s;
    union {
        uint8_t raw[16];
    };
};

struct OnlineResponseData {
    enum AuthorisationResponseCode authorisationResponseCode;
    char declineDisplayMessage[40 + 1];
    struct IssuerAuthenticationData* iatd;
};
