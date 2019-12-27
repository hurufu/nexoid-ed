#include <check.h>
#include <nexoid/tag_retrival.h>
#include <nexoid/global_data_elements.h>
#include <limits.h>

struct TerminalConfiguration tc;
struct ApplicationProfile ap;
struct ServiceSettingsEntry sc;
struct TerminalTransactionData ttd;
struct KernelData kd;
struct CardData cd;
struct OnlineResponseData ord;

struct TerminalSpecificData e1;
struct ApplicationProfileSelectionTable* e2;
struct ServiceSettingsTable e4;
struct ApplicationProfileList* e6;
struct TerminalListOfBid* e7;
struct ApplicationProfileSelectionTableNonChip* e8;
struct CombinationListAndParameters* ec;
struct AidPreferenceTable* ee;

struct CandidateList* g_CandidateList;
enum PrinterStatus g_PrinterStatus;
struct TerminalListOfAid* g_TerminalListOfAid;

#define lastof(Array) ((Array) + sizeof(Array) - 1)

#define ck_assert_tl(Tl, Result, Length, BytesLeft, NextCursor, ...)\
    ck_assert_tl_impl((Tl), (Result), (&(uint8_t[sizeof(tlv_tag_t)]){ __VA_ARGS__}), (Length), (BytesLeft), (NextCursor))

#define ck_assert_op(Op, A, B, AString, BString)\
    ck_assert_msg((A) Op (B), "Assertion '"#A" "#Op" "#B"' failed. "#A" == %s and "#B" == %s", AString, (BString))

#define ck_assert_dol_result(Op, A, B)\
    ck_assert_op(Op, A, B, dol_result_tostring(A), dol_result_tostring(B))

#define ck_assert_dol_result_eq(A, B)\
    ck_assert_dol_result(==, A, B)

#define ck_assert_dol_result_neq(A, B)\
    ck_assert_dol_result(!=, A, B)

static
const char*
dol_result_tostring(const enum ProcedureResult r) {
    switch (r) {
        case PR_OK: return "PR_OK";
        case PR_NOK: return "PR_NOK";
        case PR_SKIP: return "PR_SKIP";
        case PR_DONE: return "PR_DONE";
        default: return NULL;
    }
}

static
void
ck_assert_tl_impl(
        const struct Extracted_Tl tl,
        const enum ProcedureResult expected_result,
        const uint8_t (*const tag)[sizeof(tlv_tag_t)],
        const size_t length,
        const size_t bytes_left,
        const uint8_t* next_cursor
    ) {
    ck_assert_dol_result_eq(tl.result, expected_result);
    ck_assert_uint_eq(tl.length, length);
    ck_assert_mem_eq(tl.tag.raw, *tag, sizeof(*tag));
    ck_assert_uint_eq(tl.size, bytes_left);
    if (next_cursor) {
        ck_assert_ptr_nonnull(tl.cursor);
        ck_assert_ptr_eq(tl.cursor, next_cursor);
    } else {
        ck_assert_ptr_null(tl.cursor);
    }
}

#suite tag_retrival

#test tag_expanded_struct_is_consistent
    const union TagExpanded t = { 0xDF, 0x81, 0x18 };
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

// FIXME: Swap endinannes in test cases for length

#test length_has_two_bytes
    const uint8_t s[] = { 0xCA, 0x82, 0x01, 0x02 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 0x0102, 0, lastof(s) + 1, 0xCA);

#test max_length
    const uint8_t s[] = { 0xCA, 0x88, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 0x01020304050607080, 0, lastof(s) + 1, 0xCA);

#test over_max_length
    const uint8_t s[] = { 0xCA, 0x8A, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_NOK, 0, 0, lastof(s) + 1, 0xCA);

#test max_length_and_tag
    const uint8_t s[] = { 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    ck_assert_tl(Extract_Tag_And_Length_Pair(sizeof(s), s), PR_OK, 0x0102030405060708, 0, lastof(s) + 1, 0x9F, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87);
