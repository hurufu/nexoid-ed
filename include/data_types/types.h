#pragma once

#include <stdint.h>

typedef uint8_t bcd_t;

// Packed BCD max n12 padded with zeros to the right
struct bcd6 {
    bcd_t v[6];
};

struct bcd2 {
    bcd_t v[2];
};

struct bcd3 {
    bcd_t v[3];
};

struct ans_16 {
    uint8_t l;
    char v[16];
};

struct ans_34 {
    uint8_t l;
    char v[34];
};

struct as_34 {
    uint8_t l;
    char v[34];
};
