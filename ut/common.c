#include "common.h"

#include <check.h>

struct ApplicationProfile ap;
struct ServiceSettingsEntry sc;
struct TerminalTransactionData ttd;
struct CardData cd;
struct CardResponse* cr;
struct E1KernelData* e1kd;
struct EntryPointData ep;
struct OnlineResponseData ord;
struct SearchTransactionResultList* sl;

struct PermanentTerminalSpecificData e0;
struct TerminalSpecificData e1;
struct ApplicationProfileSelectionTable* e2;
struct ServiceSettingsTable e4;
struct ApplicationProfileList* e6;
struct TerminalListOfBid* e7;
struct ApplicationProfileSelectionTableNonChip* e8;
struct ExceptionFile* e9;
struct CombinationListAndParameters* ec;
struct AidPreferenceTable* ee;

struct PklrConfiguration pklr = {
    .buildCandidateList = true
};

struct CandidateList* g_CandidateList;
enum PrinterStatus g_PrinterStatus;
enum TmsContactLevel g_callTms;
struct TerminalListOfAid* g_TerminalListOfAid;

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

void
ck_assert_tl_impl(
        const struct Extracted_Tl tl,
        const enum ProcedureResult expected_result,
        const uint8_t (*const tag)[sizeof(tlv_tag_t)],
        const size_t length,
        const size_t bytes_left,
        const uint8_t* const next_cursor
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
