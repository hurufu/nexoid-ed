#include <check.h>
#include <nexoid/tag_retrival.h>
#include <nexoid/global_data_elements.h>

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

static
void
ck_assert_tl_impl(
        const struct Extracted_Tl* tl,
        const enum ProcedureResult result,
        const uint8_t (*const tag)[sizeof(tlv_tag_t)],
        const size_t length,
        const size_t bytes_left,
        const uint8_t* next_cursor
    ) {
    ck_assert(tl->result == result);
    ck_assert_uint_eq(tl->length, length);
    ck_assert_mem_eq(tl->tag.raw, *tag, sizeof(*tag));
    ck_assert_uint_eq(tl->size, bytes_left);

    if (next_cursor) {
        ck_assert_ptr_nonnull(tl->cursor);
        ck_assert_ptr_eq(tl->cursor, next_cursor);
    } else {
        ck_assert_ptr_null(tl->cursor);
    }
}

#test Dummy
    ck_assert(1);

#suite tag_retrival

#test tl_is_extracted
    const uint8_t s[] = { 0x9F, 0x1A, 0x02, 0xDF, 0x27, 0x03 };
    const struct Extracted_Tl tl = Extract_Tag_And_Length_Pair(sizeof(s), s);
    ck_assert_tl(&tl, PR_OK, 2, 3, s + 3, 0x9F, 0x1A);

#test tl_is_extracted_from_one_correct_pair
    const uint8_t s[] = { 0x9F, 0x1A, 0x02 };
    const struct Extracted_Tl tl = Extract_Tag_And_Length_Pair(sizeof(s), s);
    ck_assert_tl(&tl, PR_OK, 2, 0, lastof(s) + 1, 0x9F, 0x1A);

#test result_is_done_if_input_is_empty
    const uint8_t s[0];
    const struct Extracted_Tl tl = Extract_Tag_And_Length_Pair(sizeof(s), s);
    ck_assert_tl(&tl, PR_DONE, 0, 0, s);

#test result_is_nok_if_input_is_null
    const struct Extracted_Tl tl = Extract_Tag_And_Length_Pair(10, NULL);
    ck_assert_tl(&tl, PR_NOK, 0, 0, NULL);

#test result_is_nok_if_input_is_empty_and_null
    const struct Extracted_Tl tl = Extract_Tag_And_Length_Pair(0, NULL);
    ck_assert_tl(&tl, PR_NOK, 0, 0, NULL);
