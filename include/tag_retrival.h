#pragma once

#include "common.h"
#include "c2.h"

typedef uintmax_t tlv_tag_t;
typedef size_t tlv_size_t;

enum TagType {
    TAG_UNKNOWN
  , TAG_BOOLEAN
  , TAG_BOOLEAN_PTR
  , TAG_C19
  , TAG_BID
  , TAG_BCD1
  , TAG_BCD2
  , TAG_ANS_16
  , TAG_TVR
  , TAG_TVR_PTR
  , TAG_ATC
  , TAG_ATC_PTR
  , TAG_TC
  , TAG_TC_PTR
  , TAG_APS
  , TAG_APSC_PTR
  , TAG_AMOUNT
  , TAG_AMOUNT_PTR
  , TAG_CVM_CAPABILITY_PTR
  , TAG_MSR_CVM_CAPABILITY_PTR
  , TAG_KERNEL2_CONFIGURATION_PTR
  , TAG_FORBIDDEN
};

enum TagType2 {
    TAG_BCD
  , TAG_CBCD
  , TAG_NON_NUMERIC
};

union TagExpanded {
    uint8_t raw[sizeof(tlv_tag_t)];
    tlv_tag_t i;
    struct {
        union {
            uint8_t head;
            struct {
                uint8_t nmbr : 5;
                uint8_t constructed : 1;
                enum {
                    TLV_CLASS_UNIVERSAL = 0b00,
                    TLV_CLASS_APPLICATION = 0b01,
                    TLV_CLASS_CONTEXT_SPECIFIC = 0b10,
                    TLV_CLASS_PRIVATE = 0b11
                } type : 2;
            };
        };
        uint8_t tail[sizeof(tlv_tag_t) - sizeof(uint8_t)];
    };
};

struct TagTypePointer {
    enum TagType type;
    union {
        const bool* b;
        const char (*c19)[19];
        const struct Bid* bid;
        const bcd_t* bcd;
        const struct bcd2* bcd2;
        const struct ans_16* ans_16;
        const union TerminalVerificationResults* tvr;
        const union AdditionalTerminalCapabilities* atc;
        const union TerminalCapabilities* tc;
        const union ApplicationProfileSettings* aps;
        const union ApplicationProfileSettingsForCancellation* apsc;
        const union Amount* amount;
        const union CvmCapability* cvmCapability;
        const union MagStripeCvmCapability* magstripeCvmCapability;
        const union Kernel2Configuration* kernel2Configuration;
    } value;
};

struct TypeLengthValue {
    enum TagType2 type;
    size_t length;
    uint8_t value[];
};

static inline
uint8_t* getv_bool(const bool* v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    *ret = *v;
    return ret;
}

static inline
uint8_t* getv_c19(const char (*const v)[19]) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, *v, sizeof(*v));
    return ret;
}

static inline
uint8_t* getv_bid(const struct Bid* const v) {
    uint8_t* const ret = mempool_malloc(v->size);
    memcpy(ret, v->value, v->size);
    return ret;
}

static inline
uint8_t* getv_bcd(const bcd_t* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    *ret = *v;
    return ret;
}

static inline
uint8_t* getv_bcd2(const struct bcd2* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->v, sizeof(v->v));
    return ret;
}

static inline
uint8_t* getv_ans_16(const struct ans_16* const v) {
    uint8_t* const ret = mempool_malloc(v->l);
    memcpy(ret, v->v, v->l);
    return ret;
}

static inline
uint8_t* getv_tvr(const union TerminalVerificationResults* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_atc(const union AdditionalTerminalCapabilities* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_tc(const union TerminalCapabilities* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_aps(const union ApplicationProfileSettings* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_apsc(const union ApplicationProfileSettingsForCancellation* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_amount(const union Amount* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->bcd, sizeof(v->bcd));
    return ret;
}

static inline
uint8_t* getv_cvmCapability(const union CvmCapability* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_msrCvmCapability(const union MagStripeCvmCapability* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_kernel2Configuration(const union Kernel2Configuration* const v) {
    uint8_t* const ret = mempool_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bool(const bool* v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = 1;
    ret->value[0] = *v;
    return ret;
}

static inline
struct TypeLengthValue* gettylv_c19(const char (*const v)[19]) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(*v);
    memcpy(ret->value, *v, sizeof(*v));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bid(const struct Bid* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(v->size));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(*v);
    memcpy(ret->value, v->value, v->size);
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bcd(const bcd_t* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_BCD;
    ret->length = 1;
    ret->value[0] = *v;
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bcd2(const struct bcd2* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_BCD;
    ret->length = 1;
    memcpy(ret->value, v->v, sizeof(v->v));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_ans_16(const struct ans_16* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(v->l));
    ret->type = TAG_NON_NUMERIC;
    ret->length = v->l;
    memcpy(ret->value, v->v, v->l);
    return ret;
}

static inline
struct TypeLengthValue* gettylv_tvr(const union TerminalVerificationResults* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_atc(const union AdditionalTerminalCapabilities* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_tc(const union TerminalCapabilities* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_aps(const union ApplicationProfileSettings* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_apsc(const union ApplicationProfileSettingsForCancellation* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_amount(const union Amount* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_BCD;
    ret->length = sizeof(v->bcd);
    memcpy(ret, v->bcd, sizeof(v->bcd));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_cvmCapability(const union CvmCapability* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_msrCvmCapability(const union MagStripeCvmCapability* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_kernel2Configuration(const union Kernel2Configuration* const v) {
    struct TypeLengthValue* const ret = mempool_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}
