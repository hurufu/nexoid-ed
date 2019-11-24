#pragma once

#include "utils.h"
#include "emv.h"

struct KernelData {
    enum AuthorisationResponseCode authorisationResponseCode;
    union TerminalVerificationResults tvr;
    // FIXME: I have no idea were to put commandTemplate
    union CommandTemplate commandTemplate;

    uint8_t responseData[256];
    struct Aid aidTerminal;

    // FIXME: IssuerCountry is actually a card data
    union Country* issuerCountry;

    union Cvm cvmResults;
};
