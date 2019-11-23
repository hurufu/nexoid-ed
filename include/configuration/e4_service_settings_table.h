#pragma once

#include <stddef.h>

// source: nexo-FAST v.3.2 section 13.3.120
// size: up to 20
// configuration: Terminal
// presence: M

struct ServiceSettingsEntry {
    enum CardholderMessage cardholderInitialMessage;
    union ServiceSettings serviceSettings;
};

struct ServiceSettingsTable {
    size_t s;
    struct ServiceSettingsEntry a[20];
};
