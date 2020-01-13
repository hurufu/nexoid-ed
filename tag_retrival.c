#include "dmapi.h"
#include "tag_retrival.h"
#include "gtd.h"

#include <byteswap.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

enum TagType2 {
    TAG_BCD
  , TAG_CBCD
  , TAG_NON_NUMERIC
};

union PACKED Length {
    uint8_t raw[sizeof(tlv_size_t) + 1];
    struct {
        struct {
            uint8_t value : 7;
            uint8_t isLong : 1;
        } length;
        union {
            tlv_size_t z;
            uint8_t a[sizeof(tlv_size_t)];
        } longLength;
    };
};

struct TypeLengthValue {
    enum TagType2 type;
    size_t length;
    uint8_t value[];
};

struct Extracted_Tag {
    enum ProcedureResult result;
    size_t size;
    const uint8_t* cursor;
    union TagExpanded tag;
};

struct Extracted_Len {
    enum ProcedureResult result;
    size_t size;
    const uint8_t* cursor;
    size_t length;
};

struct ttp {
    bool isOptional;
    enum {
        TAG_UNKNOWN
      , TAG_BOOLEAN
      , TAG_C19
      , TAG_BID
      , TAG_BCD1
      , TAG_BCD2
      , TAG_ANS_16
      , TAG_TVR
      , TAG_ATC
      , TAG_TC
      , TAG_APS
      , TAG_AMOUNT
      , TAG_FORBIDDEN
    } type;
    const void* value;
};

static inline
uint8_t* getv_bool(const bool* v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    *ret = *v;
    return ret;
}

static inline
uint8_t* getv_c19(const char (*const v)[19]) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, *v, sizeof(*v));
    return ret;
}

static inline
uint8_t* getv_bid(const struct Bid* const v) {
    uint8_t* const ret = dmapi_malloc(v->size);
    memcpy(ret, v->value, v->size);
    return ret;
}

static inline
uint8_t* getv_bcd(const bcd_t* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    *ret = *v;
    return ret;
}

static inline
uint8_t* getv_bcd2(const struct bcd2* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->v, sizeof(v->v));
    return ret;
}

static inline
uint8_t* getv_ans_16(const struct ans_16* const v) {
    uint8_t* const ret = dmapi_malloc(v->l);
    memcpy(ret, v->v, v->l);
    return ret;
}

static inline
uint8_t* getv_tvr(const union TerminalVerificationResults* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_atc(const union AdditionalTerminalCapabilities* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_tc(const union TerminalCapabilities* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_aps(const union ApplicationProfileSettings* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_apsc(const union ApplicationProfileSettingsForCancellation* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_amount(const struct bcd6* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->v, sizeof(v->v));
    return ret;
}

static inline
uint8_t* getv_cvmCapability(const union CvmCapability* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_msrCvmCapability(const union MagStripeCvmCapability* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
uint8_t* getv_kernel2Configuration(const union Kernel2Configuration* const v) {
    uint8_t* const ret = dmapi_malloc(sizeof(*v));
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bool(const bool* v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = 1;
    ret->value[0] = *v;
    return ret;
}

static inline
struct TypeLengthValue* gettylv_c19(const char (*const v)[19]) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(*v);
    memcpy(ret->value, *v, sizeof(*v));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bid(const struct Bid* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(v->size));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(*v);
    memcpy(ret->value, v->value, v->size);
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bcd(const bcd_t* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_BCD;
    ret->length = 1;
    ret->value[0] = *v;
    return ret;
}

static inline
struct TypeLengthValue* gettylv_bcd2(const struct bcd2* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_BCD;
    ret->length = sizeof(v->v);
    memcpy(ret->value, v->v, sizeof(v->v));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_ans_16(const struct ans_16* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(v->l));
    ret->type = TAG_NON_NUMERIC;
    ret->length = v->l;
    memcpy(ret->value, v->v, v->l);
    return ret;
}

static inline
struct TypeLengthValue* gettylv_tvr(const union TerminalVerificationResults* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_atc(const union AdditionalTerminalCapabilities* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_tc(const union TerminalCapabilities* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_aps(const union ApplicationProfileSettings* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_apsc(const union ApplicationProfileSettingsForCancellation* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_amount(const struct bcd6* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_BCD;
    ret->length = sizeof(v->v);
    memcpy(ret->value, v->v, sizeof(v->v));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_cvmCapability(const union CvmCapability* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_msrCvmCapability(const union MagStripeCvmCapability* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret->value, v->raw, sizeof(v->raw));
    return ret;
}

static inline
struct TypeLengthValue* gettylv_kernel2Configuration(const union Kernel2Configuration* const v) {
    struct TypeLengthValue* const ret = dmapi_malloc(sizeof(struct TypeLengthValue) + sizeof(*v));
    ret->type = TAG_NON_NUMERIC;
    ret->length = sizeof(v->raw);
    memcpy(ret, v->raw, sizeof(v->raw));
    return ret;
}

static struct ttp ApplicationProfile_get_ttv(const struct ApplicationProfile* const p, const union TagExpanded t) {
    struct ttp r;
    switch (t.e) {
        case T_EMV_TERMINAL_COUNTRY_CODE:                        r = (struct ttp){ .isOptional = false, .type = TAG_BCD2,                      .value = &p->terminalCountryCode                       }; break;
        case T_EMV_TERMINAL_CAPABILITIES:                        r = (struct ttp){ .isOptional = true,  .type = TAG_TC,                        .value =  p->terminalCapabilities                      }; break;
        case T_EMV_ADDITIONAL_TERMINAL_CAPABILITIES:             r = (struct ttp){ .isOptional = true,  .type = TAG_ATC,                       .value =  p->additionalTerminalCapabilities            }; break;
        case T_NNA_PROFILE_NUMBER:                               r = (struct ttp){ .isOptional = false, .type = TAG_BCD1,                      .value = &p->profileNumber                             }; break;
        case T_NNA_ACQUIRER_NUMBER:                              r = (struct ttp){ .isOptional = false, .type = TAG_BCD1,                      .value = &p->acquirerNumber                            }; break;
        case T_NXO_CASH_ADVANCE_MAXIMUM_AMOUNT:                  r = (struct ttp){ .isOptional = true,  .type = TAG_AMOUNT,                    .value =  p->cashAdvanceMaximumAmount                  }; break;
        case T_NXO_CASHBACK_MAXIMUM_AMOUNT:                      r = (struct ttp){ .isOptional = true,  .type = TAG_AMOUNT,                    .value =  p->cashbackMaximumAmount                     }; break;
        case T_NXO_REFUND_PROTECTION_AMOUNT:                     r = (struct ttp){ .isOptional = false, .type = TAG_AMOUNT,                    .value = &p->refundProtectionAmount                    }; break;
        case T_NXO_APPLICATION_LABEL_DEFAULT:                    r = (struct ttp){ .isOptional = false, .type = TAG_ANS_16,                    .value = &p->applicationLabelDefault                   }; break;
      //case T_NXO_CVM_MAGNETIC_STRIPE:                          r = (struct ttp){ .isOptional = true,  .type = TAG_MSR_CVM_CAPABILITY,        .value =  p->magStripeCvmCapabilityCvmRequired         }; break;
      //case XXX:                                                r = (struct ttp){ .isOptional = true,  .type = TAG_MSR_CVM_CAPABILITY,        .value =  p->magStripeCvmCapabilityNoCvmRequired       }; break;
      //case T_EMV_CVM_CAPABILITY_CVM_REQUIRED:                  r = (struct ttp){ .isOptional = true,  .type = TAG_CVM_CAPABILITY,            .value =  p->cvmCapabilityCvmRequired                  }; break;
      //case T_EMV_CVM_CAPABILITY_NO_CVM_REQUIRED:               r = (struct ttp){ .isOptional = true,  .type = TAG_CVM_CAPABILITY,            .value =  p->cvmCapabilityNoCvmRequired                }; break;
        case T_NXO_APPLICATION_PROFILE_SETTINGS:                 r = (struct ttp){ .isOptional = false, .type = TAG_APS,                       .value = &p->applicationProfileSettings                }; break;
      //case T_EMV_KERNEL_2_CONFIGURATION:                       r = (struct ttp){ .isOptional = true,  .type = TAG_KERNEL2_CONFIGURATION_PTR, .value =  p->kernel2Configuration                      }; break;
        case T_NXO_CARD_VALIDITY_CHECK_DEFAULT_AMOUNT:           r = (struct ttp){ .isOptional = true,  .type = TAG_AMOUNT,                    .value =  p->cvcDefaultAmount                          }; break;
        case T_NXO_ADDITIONAL_RESTRICTIONS_OF_FORCED_ACCEPTANCE: r = (struct ttp){ .isOptional = true,  .type = TAG_TVR,                       .value =  p->additionalRestrictionsForForcedAcceptance }; break;
      //case T_NXO_APPLICATION_PROFILE_SETINGS_FOR_CANCELLATION: r = (struct ttp){ .isOptional = true,  .type = TAG_APSC,                      .value =  p->applicationProfileSettingsForCancellation }; break;
        default:                                                 r = (struct ttp){ .isOptional = false, .type = TAG_UNKNOWN                                                                  }; break;
    }
    return r;
}

static struct TypeLengthValue* ApplicationProfile_get_tylv(const struct ApplicationProfile* const ap, const union TagExpanded tag) {
    const struct ttp t = ApplicationProfile_get_ttv(ap, tag);
    assert(t.isOptional || t.value);
    if (t.isOptional && !t.value) {
        return NULL;
    }
    switch (t.type) {
        case TAG_C19:                       return gettylv_c19(t.value);
        case TAG_BID:                       return gettylv_bid(t.value);
        case TAG_BCD1:                      return gettylv_bcd(t.value);
        case TAG_BCD2:                      return gettylv_bcd2(t.value);
        case TAG_ANS_16:                    return gettylv_ans_16(t.value);
        case TAG_APS:                       return gettylv_aps(t.value);
        case TAG_AMOUNT:                    return gettylv_amount(t.value);
        case TAG_BOOLEAN:                   return gettylv_bool(t.value);
        case TAG_TVR:                       return gettylv_tvr(t.value);
        case TAG_ATC:                       return gettylv_atc(t.value);
        case TAG_TC:                        return gettylv_tc(t.value);
        case TAG_FORBIDDEN:
        case TAG_UNKNOWN:
            break;
    }
    return NULL;
}

static struct Extracted_Tag extract_tag(const size_t s, const uint8_t c[static const s]) {
    if (s == 0 || !c) {
        return (struct Extracted_Tag){ .result = PR_NOK, .size = s, .cursor = c };
    }
    struct Extracted_Tag t = {
        .cursor = c + 1,
        .size = s - 1,
        .tag.head = *c,
        .result = PR_OK
    };
    if (0x1F != t.tag.nmbr) {
        return t;
    }

    size_t i;
    for (i = 0; i < elementsof(t.tag.tail) && t.size > 0; t.size--, i++, t.cursor++) {
        t.tag.tail[i].c = *t.cursor;
        if (!t.tag.tail[i].v.next) {
            t.size--, i++, t.cursor++;
            break;
        }
    }
    if (0 == i) {
        // Input string ended
        t.result = PR_NOK;
    }
    if (t.tag.tail[i-1].v.next) {
        // Tag doesn't fit into internal type
        for (size_t j = 0; t.size > 0; t.size--, j++, t.cursor++) {
            if (!t.tag.tail[i+j].v.next) {
                t.size--, j++, t.cursor++;
                break;
            }
        }
        t.tag.i = 0;
        t.result = PR_SKIP;
    }
    return t;
}

static struct Extracted_Len extract_length(const size_t s, const uint8_t c[static const s]) {
    if (0 == s) {
        return (struct Extracted_Len){
            .cursor = c,
            .size = 0,
            .result = PR_NOK,
            .length = 0
        };
    }
    struct Extracted_Len ret = {
        .cursor = c + 1,
        .size = s - 1,
        .result = PR_OK
    };
    union Length l = { .raw = { *c } };
    if (!l.length.isLong) {
        ret.length = l.length.value;
        // OK - Length has only 1 byte
        return ret;
    }
    if (l.length.value > elementsof(l.longLength.a)) {
        ret.length = SIZE_MAX;
        ret.result = PR_NOK;
        ret.size -= l.length.value;
        ret.cursor += l.length.value;
        // NOK - Length is larger then supported by the platform
        return ret;
    }
    if (s < l.length.value) {
        ret = (struct Extracted_Len){
            .length = 0,
            .result = PR_NOK,
            .cursor = c + s,
            .size = 0
        };
        // NOK - length is OK, but `c` doesn't contain enough bytes to read
        return ret;
    }
    memcpy(l.longLength.a, ret.cursor, l.length.value);
    // TODO: Refactor, optimize and make cross platform byte swapping
    const uint_fast8_t most_significant_non_zero_byte =
            l.longLength.a[7] ? 0 :
            l.longLength.a[6] ? 1 :
            l.longLength.a[5] ? 2 :
            l.longLength.a[4] ? 3 :
            l.longLength.a[3] ? 4 :
            l.longLength.a[2] ? 5 :
            l.longLength.a[1] ? 6 :
            l.longLength.a[0] ? 7 : 8;
    ret.length = bswap_64(l.longLength.z) >> (most_significant_non_zero_byte * CHAR_BIT);
    ret.size -= l.length.value;
    ret.cursor += l.length.value;

    // OK - Length has multiple bytes
    return ret;
}

struct Extracted_Tl
Extract_Tag_And_Length_Pair(const size_t size, const uint8_t cursor[static const size]) {
    if (!cursor) {
        return (struct Extracted_Tl){ .result = PR_NOK };
    }
    if (size == 0) {
        return (struct Extracted_Tl){ .result = PR_DONE, .cursor = cursor };
    }
    const struct Extracted_Tag t = extract_tag(size, cursor);
    const struct Extracted_Len l = extract_length(t.size, t.cursor);
    const struct Extracted_Tl ret = {
        .result = ((PR_OK == t.result && PR_OK == l.result) ? PR_OK : PR_NOK),
        .size = l.size,
        .cursor = l.cursor,
        .tag = t.tag,
        .length = l.length
    };
    return ret;
}

// TODO: Consider moving an Append_Dol_Entry implementation to the Drakon
enum ProcedureResult Append_Dol_Entry(const size_t Length, uint8_t Dol[const Length], const union TagExpanded tag, const size_t tagLength) {
    // TODO: Look for the tag in different global elements, not only `ap`
    struct TypeLengthValue* const t = ApplicationProfile_get_tylv(&ap, tag);
    if (!t) {
        return PR_NOK;
    }
    if (tagLength < t->length) {
        if (t->length < tagLength) {
            return PR_NOK;
        }
        switch (t->type) {
            case TAG_BCD:
                memcpy(Dol, t->value + t->length - tagLength, t->length);
                break;
            case TAG_CBCD:
            case TAG_NON_NUMERIC:
                memcpy(Dol, t->value, t->length);
                break;
        }
    } else if (tagLength > t->length) {
        if (Length < tagLength) {
            return PR_NOK;
        }
        switch (t->type) {
            case TAG_BCD:
                memcpy(Dol + tagLength - t->length, t->value, t->length);
                break;
            case TAG_CBCD:
                memcpy(Dol, t->value, t->length);
                memset(Dol, 0xFF, tagLength - t->length);
                break;
            case TAG_NON_NUMERIC:
                memcpy(Dol, t->value, t->length);
                break;
        }
    } else {
        if (Length < tagLength) {
            return PR_NOK;
        }
        memcpy(Dol, t->value, t->length);
    }
    return PR_OK;
}
