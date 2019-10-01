#pragma once

typedef uint8_t bcd_t;

// Packed BCD max n12 padded with zeros to the right
struct bcd6 {
    bcd_t v[6];
};

struct bcd2 {
    bcd_t v[2];
};

struct ans16 {
    char v[16];
};

struct ans_16 {
    uint8_t l;
    char v[16];
};
