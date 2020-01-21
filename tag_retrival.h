#pragma once

#include "dmapi.h"
#include "types.h"

// FIXME: CAST_TAG() works only with 2-byte tags
#define CAST_TAG(TagV) \
    (TagV & (0xFF << 0)) << 8 | \
    (TagV & (0xFF << 8)) >> 8

// EMV - Data elements defined by EMV or ISO and used by nexo-FAST (section 13.1)
// ENU - Data elements defined by EMV and not used by nexo-FAST (section 13.2)
// NXO - Data elements defined by nexo-FAST for use outside of kernel processing (section 13.3)
// NXE - Data elements defined by nexo-FAST for use in kernel E (section 13.4)
// NNA - Not known, not applicable
// NIS - Defined by nIS only

enum Tag {
    // Unique Application Profile ID:
    T_NNA_PROFILE_NUMBER = CAST_TAG(0xDF19)
  , T_NNA_ACQUIRER_NUMBER = CAST_TAG(0xDF1B)

    // Application Profile Parameters:
  , T_NIS_APPLICATION_PROFILE = CAST_TAG(0xE6)
  , T_EMV_ACQUIRER_IDENTIFIER = CAST_TAG(0x9F10)
  , T_NNA_ADDITIONAL_DATA_ELEMENTS = CAST_TAG(0xEF)
  , T_NXO_ADDITIONAL_RESTRICTIONS_OF_FORCED_ACCEPTANCE = CAST_TAG(0xDF26)
  , T_EMV_ADDITIONAL_TERMINAL_CAPABILITIES = CAST_TAG(0x9F40)
  , T_EMV_TERMINAL_COUNTRY_CODE = CAST_TAG(0x9F1A)
  , T_NXO_APPLICATION_LABEL_DEFAULT = CAST_TAG(0xDF41)
  , T_NXO_APPLICATION_PROFILE_SETTINGS = CAST_TAG(0xDF27)
  , T_NXO_APPLICATION_PROFILE_SETINGS_FOR_CANCELLATION = CAST_TAG(0xDF28)
  , T_NXO_CASH_ADVANCE_MAXIMUM_AMOUNT = CAST_TAG(0xDF29)
  , T_EMV_CVM_CAPABILITY_CVM_REQUIRED = CAST_TAG(0xDF8118)
  , T_EMV_CVM_CAPABILITY_NO_CVM_REQUIRED = CAST_TAG(0xDF8119)
  , T_EMV_DDOL = CAST_TAG(0xDF1A)
  , T_EMV_HOLD_TIME_VALUE = CAST_TAG(0xDF8130)
  , T_EMV_KERNEL_2_CONFIGURATION = CAST_TAG(0xDF811B)
  , T_EMV_KERNEL_4_READER_CAPABILITIES = CAST_TAG(0x9F6D)
  , T_EMV_TERMINAL_CAPABILITIES = CAST_TAG(0x9F33)
  , T_NXO_CASHBACK_MAXIMUM_AMOUNT = CAST_TAG(0xDF2A)
  , T_NXO_REFUND_PROTECTION_AMOUNT = CAST_TAG(0xDF3C)
  , T_NXO_CVM_MAGNETIC_STRIPE = CAST_TAG(0xDF42)
  , T_NXO_CARD_VALIDITY_CHECK_DEFAULT_AMOUNT = CAST_TAG(0xDF58)
};

typedef uintmax_t tlv_tag_t;
typedef size_t tlv_size_t;

union PACKED TagExpanded {
    uint8_t raw[sizeof(tlv_tag_t)];
    tlv_tag_t i;
    enum Tag e;
    struct PACKED {
        union PACKED {
            uint8_t head;
            struct PACKED {
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
        union PACKED {
            uint8_t c;
            struct PACKED {
                uint8_t value : 7;
                uint8_t next : 1;
            } v;
        } tail[sizeof(tlv_tag_t) - sizeof(uint8_t)];
    };
};

// TODO: Consider moving Extract_Tag_And_Length_Pair() and struct Extracted_Tl away from this header
struct Extracted_Tl {
    union TagExpanded tag;
    size_t length;
    enum ProcedureResult result;
    size_t size;
    const uint8_t* cursor;
};

/** Extract Tag and Length from DOL string
 *
 *  @note nexo FAST v.3.2, note 220-20
 *
 *  @returns PR_OK on success, PR_DONE on empty string, PR_NOK on error and
 *  PR_SKIP if resulting tag doesn't fit into a machine word, but is otherwise
 *  correct. Members `size` and `cursor` are always set to some meaningfull
 *  values even in case of an error.
 */
struct Extracted_Tl Extract_Tag_And_Length_Pair(size_t size, const uint8_t cursor[size]);

enum ProcedureResult Append_Dol_Entry(size_t Length, uint8_t Dol[Length], union TagExpanded tag, size_t length);
