#pragma once

struct tlv {
    union {
        uint8_t head;
        struct {
            uint8_t nmbr : 5;
            uint8_t tmpl : 1;
            uint8_t type : 2;
        };
    };
    uint8_t tail[];
};
