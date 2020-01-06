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

    // WARNING: declineDisplayMessageId isn't defined by nexo.
    //
    // According to nexo-FAST v.3.2, section 13.3.50 type of Decline Display
    // Message should be an...40, but in section 12.1.3.2 it's mentioned that
    // HAP in some circumstances should set it to Cardholder Message 0x1D,
    // which is inconsistent with it's definition or common software
    // engeneering practice under any interpetation of the passage. Namely if
    // we interpret it as if HAP should populate this data element with proper
    // translated text based on message id 0x1D, then suddenly HAP needs access
    // to all (or partial) cardholder or attendant translations, which is in
    // scope of SCAP only (no citation), but if we interpret it as if HAP
    // should copy byte 0x1D verbatim into this data element then it's
    // inconsitent with it's definition, because 0x1D isn't an alphanumeric
    // character. As a temporary workaround new optional data element is added:
    // Decline Display Message Id that can hold Cardholder Message Id
    enum CardholderMessage* declineDisplayMessageId;
};
