#pragma once

// or nexo-IS v.4.0 section 4.5.1

// FIXME: Probably should be replaced with E1 and E0
struct TerminalConfiguration {
    union TerminalType terminalType;
    union TerminalSettings terminalSettings;
    union TerminalCapabilities terminalCapabilities;
    union AdditionalTerminalCapabilities additionalTerminalCapabilities;
    union ConfiguredServices configuredServices;
    unsigned char maxNumberOfChipTries;
    union CurrencyAlpha3* applicationCurrency; // FIXME: not specified by nexo
    union Country cardholderDefaultLanguage;
    union EeaProcessSettings* eeaProcessSettings; // FIXME: shouldn't be a pointer
};
