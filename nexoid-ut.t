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

#test Dummy
    ck_assert(1);
