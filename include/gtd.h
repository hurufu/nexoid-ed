#pragma once

#include "types.h"

/* Global Terminal Data
 */

extern struct TerminalTransactionData ttd;
extern struct ApplicationProfile ap;
extern struct CardData cd;
extern struct KernelData kd;
extern struct TerminalConfiguration tc;
extern struct OnlineResponseData ord;
extern struct ServiceSettingsEntry sc;

extern struct PermanentTerminalSpecificData e0;
extern struct TerminalSpecificData e1;
extern struct ApplicationProfileSelectionTable* e2;
extern struct ServiceSettingsTable e4;
extern struct ApplicationProfileList* e6;
extern struct TerminalListOfBid* e7;
extern struct ApplicationProfileSelectionTableNonChip* e8;
extern struct CombinationListAndParameters* ec;
extern struct AidPreferenceTable* ee;
