#suite memory_layout

#include "types.h"

#test static_tests
    _Static_assert(sizeof(union TagExpanded) == sizeof(tlv_tag_t));
    ck_assert(sizeof(union TagExpanded) == sizeof(tlv_tag_t));

#test single_byte_tag_has_correct_structure
    const union TagExpanded a = { .e = T_EMV_APPLICATION_INTERCHANGE_PROFILE }, b = { .raw = "\x82" };
    const uint8_t expected[sizeof(tlv_tag_t)] = "\x82";

    // Check if tags that are constructed differently represent the same tag
    ck_assert_mem_eq(a.raw, expected, sizeof(expected));
    ck_assert_mem_eq(b.raw, expected, sizeof(expected));
    ck_assert_int_eq(a.e, b.e);
    ck_assert_uint_eq(a.i, b.i);

    // Check if structure is ok
    ck_assert_uint_eq(a.constructed, 0);
    ck_assert_uint_eq(a.nmbr, 0x02u);
    ck_assert_uint_eq(a.type, TLV_CLASS_CONTEXT_SPECIFIC);
    for (size_t i = 0; i < sizeof(tlv_tag_t); i++) {
        ck_assert_uint_eq(a.tail[i].c, 0);
        ck_assert_uint_eq(a.tail[i].v.value, 0);
        ck_assert_uint_eq(a.tail[i].v.next, 0);
    }

#test two_byte_tag_has_correct_structure
    const union TagExpanded a = { .e = T_NNA_PROFILE_NUMBER }, b = { .raw = "\xDF\x19" };
    const uint8_t expected[sizeof(tlv_tag_t)] = "\xDF\x19";

    // Check if tags that are constructed differently represent the same tag
    ck_assert_mem_eq(a.raw, expected, sizeof(expected));
    ck_assert_mem_eq(b.raw, expected, sizeof(expected));
    ck_assert_int_eq(a.e, b.e);
    ck_assert_uint_eq(a.i, b.i);

    // Check if structure is ok
    ck_assert_uint_eq(a.constructed, 0);
    ck_assert_uint_eq(a.nmbr, 0x1Fu);
    ck_assert_uint_eq(a.type, TLV_CLASS_PRIVATE);
    ck_assert_uint_eq(a.tail[0].v.next, 0);
    ck_assert_uint_eq(a.tail[0].v.value, 0x19u);
    ck_assert_uint_eq(a.tail[0].c, 0x19u);
    for (size_t i = 1; i < sizeof(tlv_tag_t); i++) {
        ck_assert_uint_eq(a.tail[i].c, 0);
        ck_assert_uint_eq(a.tail[i].v.value, 0);
        ck_assert_uint_eq(a.tail[i].v.next, 0);
    }

#test three_byte_tag_has_correct_structure
    const union TagExpanded a = { .e = T_EMV_KERNEL_2_CONFIGURATION }, b = { .raw = "\xDF\x81\x1B" };
    const uint8_t expected[sizeof(tlv_tag_t)] = "\xDF\x81\x1B";

    // Check if tags that are constructed differently represent the same tag
    ck_assert_mem_eq(a.raw, expected, sizeof(expected));
    ck_assert_mem_eq(b.raw, expected, sizeof(expected));
    ck_assert_int_eq(a.e, b.e);
    ck_assert_uint_eq(a.i, b.i);

    // Check if structure is ok
    ck_assert_uint_eq(a.constructed, 0);
    ck_assert_uint_eq(a.nmbr, 0x1Fu);
    ck_assert_uint_eq(a.type, TLV_CLASS_PRIVATE);
    ck_assert_uint_eq(a.tail[0].v.next, 1);
    ck_assert_uint_eq(a.tail[0].v.value, 0x1u);
    ck_assert_uint_eq(a.tail[0].c, 0x81u);
    ck_assert_uint_eq(a.tail[1].v.next, 0);
    ck_assert_uint_eq(a.tail[1].v.value, 0x1Bu);
    ck_assert_uint_eq(a.tail[1].c, 0x1Bu);
    for (size_t i = 2; i < sizeof(tlv_tag_t); i++) {
        ck_assert_uint_eq(a.tail[i].c, 0);
        ck_assert_uint_eq(a.tail[i].v.value, 0);
        ck_assert_uint_eq(a.tail[i].v.next, 0);
    }
