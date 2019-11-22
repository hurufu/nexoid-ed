#pragma once

struct KernelData {
    enum AuthorisationResponseCode authorisationResponseCode;
    union TerminalVerificationResults tvr;
    // FIXME: I have no idea were to put commandTemplate
    union CommandTemplate commandTemplate;

    union EmvStatus sw1Sw2;
    uint8_t responseData[256];
    struct Aid aidTerminal;

    // FIXME: IssuerCountry is actually a card data
    union Country* issuerCountry;
};
