#pragma once

#include "types.h"
#include <string.h>

struct ServiceInitialisation {
    bool SecurityPermission;
};

static inline bool Aid_eq(const struct Aid* const a, const struct Aid* const b) {
    if (a->l_raw != b->l_raw) {
        return false;
    }
    return memcmp(a->raw, b->raw, a->l_raw) == 0;
}

// TODO: Consider removal of global variabled here
struct TerminalListOfAid* g_TerminalListOfAid;
struct CandidateList* g_CandidateList;
enum PrinterStatus g_PrinterStatus;

union ConfiguredServices ServiceId_to_ConfiguredServices(enum ServiceId);
union ServiceStartEvents ServiceId_to_AllowedServiceStartEvents(enum ServiceId s);
struct CombinationListAndParameters* Copy_Combination_Lists_Entry(const struct CombinationListAndParameters* r);
bool isIssuerCountryExcludedForDcc(void);

struct cbcd6 String_To_Cbcd6(const char* str);

int yymmdd_cmp(union yymmdd lhs, union yymmdd rhs);
