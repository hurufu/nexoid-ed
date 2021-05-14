#include "common.h"

#include "tag_retrival.h"
#include "local.h"

#include <check.h>
#include <limits.h>

#suite tag_retrival

#test tag_expanded_struct_is_consistent
    const union TagExpanded t = { .raw = { 0xDF, 0x81, 0x18 } };
    ck_assert_uint_eq(sizeof(t), sizeof(t.raw));
    ck_assert_uint_eq(sizeof(t), sizeof(tlv_tag_t));
    ck_assert_uint_eq(t.head, 0xDF);
    ck_assert_uint_eq(t.nmbr, 0x1F);
    ck_assert(!t.constructed);
    ck_assert(TLV_CLASS_PRIVATE == t.type);
    ck_assert_mem_eq(t.tail, ((uint8_t[sizeof(tlv_tag_t) - 1]){ 0x81, 0x18 }), sizeof(tlv_tag_t) - 1);
    ck_assert(t.tail[0].v.next);
    ck_assert(!t.tail[1].v.next);

#test tl_is_extracted
    const uint8_t s[] = { 0x9F, 0x1A, 0x02, 0xDF, 0x27, 0x03 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 2, 3, s + 3, 0x9F, 0x1A);

#test tl_is_extracted_from_one_correct_pair
    const uint8_t s[] = { 0x9F, 0x1A, 0x02 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 2, 0, lastof(s) + 1, 0x9F, 0x1A);

#test result_is_done_if_input_is_empty
    const uint8_t s[0];
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_DONE, 0, 0, s);

#test result_is_nok_if_input_is_null
    ck_assert_tl(Extract_Tag_And_Length_Pair(10, NULL), PR_NOK, 0, 0, NULL);

#test result_is_nok_if_input_is_empty_and_null
    ck_assert_tl(Extract_Tag_And_Length_Pair(0, NULL), PR_NOK, 0, 0, NULL);

#test result_is_nok_if_input_is_zeroed
    const uint8_t s[16] = { };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 0, 14, s + 2);

#test max_tag_length
    const uint8_t s[] = { 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x07, 0x01 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 1, 0, lastof(s) + 1, 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x07);

#test tag_is_too_large
    const uint8_t s[] = { 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x03 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_NOK, 3, 0, lastof(s) + 1);

#test not_enough_input_bytes_for_tag
    const uint8_t s[] = { 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_NOK, 0, 0, lastof(s) + 1);

#test length_has_two_bytes
    const uint8_t s[] = { 0xCA, 0x82, 0x01, 0x02 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 0x0102, 0, lastof(s) + 1, 0xCA);

#test max_length
    const uint8_t s[] = { 0xCA, 0x88, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 0x0102030405060708, 0, lastof(s) + 1, 0xCA);

#test over_max_length
    const uint8_t s[] = { 0xCA, 0x8A, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_NOK, SIZE_MAX, 0, lastof(s) + 1, 0xCA);

#test max_length_and_tag
    const uint8_t s[] = { 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x07, 0x88, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 0x0102030405060708, 0, lastof(s) + 1, 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x07);

#test not_enough_input_bytes_for_length
    const uint8_t s[] = { 0x07, 0x85, 0xA1, 0xA2 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_NOK, 0, 0, lastof(s) + 1, 0x07);

#suite utils

#test cbcd6_is_converted_from_even_number_of_digits
    const struct cbcd6 converted = String_To_Cbcd6("1234");
    const struct cbcd6 expected = { .v = { 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF } };
    ck_assert_mem_eq(converted.v, expected.v, 6);

#test cbcd6_conversion_handles_null_input
    const struct cbcd6 converted = String_To_Cbcd6(NULL);
    const struct cbcd6 expected = { .v = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
    ck_assert_mem_eq(converted.v, expected.v, 6);

#test cbcd6_conversion_handles_empty_input
    const struct cbcd6 converted = String_To_Cbcd6("");
    const struct cbcd6 expected = { .v = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
    ck_assert_mem_eq(converted.v, expected.v, 6);

#test cbcd6_is_converted_from_odd_number_of_digits
    const struct cbcd6 converted = String_To_Cbcd6("12345");
    const struct cbcd6 expected = { .v = { 0x12, 0x34, 0x5F, 0xFF, 0xFF, 0xFF } };
    ck_assert_mem_eq(converted.v, expected.v, 6);

#test cbcd6_handles_too_big_input
    const struct cbcd6 converted = String_To_Cbcd6("1234567890123");
    const struct cbcd6 expected = { .v = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
    ck_assert_mem_eq(converted.v, expected.v, 6);

#test cbcd6_handles_non_numeric_input
    const struct cbcd6 converted = String_To_Cbcd6("123ab23");
    const struct cbcd6 expected = { .v = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
    ck_assert_mem_eq(converted.v, expected.v, 6);

#test yymmdd_dates_equal
    const union yymmdd a = { .y = 0x20, .m = 0x04, .d = 0x04 };
    const union yymmdd b = { .y = 0x20, .m = 0x04, .d = 0x04 };
    ck_assert_int_eq(yymmdd_cmp(a, b), 0);

#test yymmdd_years_differ
    const union yymmdd a = { .y = 0x20, .m = 0x04, .d = 0x04 };
    const union yymmdd b = { .y = 0x19, .m = 0x04, .d = 0x04 };
    ck_assert_int_eq(yymmdd_cmp(a, b), 1);
    ck_assert_int_eq(yymmdd_cmp(b, a), -1);

#test atc_has_correct_memory_layout
    const union AdditionalTerminalCapabilities c = {
        .transactionType = {
            .cashDeposit = 1,
            .administrative = 1,
        },
        .terminalDataInput = {
            .functionKeys = 1,
            .numericKeys = 1,
        },
        .terminalDataOutput = {
            .codeTable3 = 1,
            .codeTable9 = 1,
            .codeTable1 = 1,
        },
    };
    const unsigned char expected[sizeof(c.raw)] = { 0x01,0x80,0x90,0x01,0x05 };
    ck_assert_uint_eq(sizeof(c), sizeof(c.raw));
    ck_assert_mem_eq(c.raw, expected, sizeof(c.raw));
    ck_assert_uint_eq(code_tables_get(c), 0x0105);
    for (int i = 1; i <= 10; i++) {
        const bool test = is_code_table_supported(c, i);
        ck_assert_msg((ONEOF3(i,1,3,9)? test : !test), "Bit #%d is reversed (expected: !%d)", i, test);
    }
