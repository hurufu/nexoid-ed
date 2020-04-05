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

/* Used as a hapi_Search_Transactions results container
 */
extern struct SearchTransactionResultList* sl;

// Controls if TMS should be contacted
//
// It's defined only in nexo-IS, and this document is sometimes inconsistent
// with nexo-FAST. Like here, in IS it's written that this variable may be
// set during Authorisation Request, but may be handled only in Idle, FAST
// defines what Idle is, and Default Service Initialisation will always preceed
// it, so if this variable will be part of ttd, then it will be always reset
// and won't trigger anything, if implement it according to the specification.
// That's why it's move outside of ttd as a separated free global variable
//
// TODO: Figure out something better
extern enum TmsContactLevel g_callTms;
