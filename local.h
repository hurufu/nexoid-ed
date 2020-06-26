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
extern struct TerminalListOfAid* g_TerminalListOfAid;
extern struct CandidateList* g_CandidateList;
extern enum PrinterStatus g_PrinterStatus;

union ConfiguredServices ServiceId_to_ConfiguredServices(enum ServiceId);
union ServiceStartEvents ServiceId_to_AllowedServiceStartEvents(enum ServiceId s);
struct CombinationListAndParameters* Copy_Combination_Lists_Entry(const struct CombinationListAndParameters* r);
bool isIssuerCountryExcludedForDcc(void);

struct cbcd6 String_To_Cbcd6(const char* str);

int bcd6_add(union bcd6 a, union bcd6 b, union bcd6* c);

int yymmdd_cmp(union yymmdd lhs, union yymmdd rhs);

// FIXME: Fix this ugly hack with allocations
// nexo-FAST v.3.2, note 182-10
struct SearchLogCriteria* alloc_SearchLogCriteria_For_FloorLimit(void);

static inline union ApplicationContextControl Auc_to_Acc(const union ApplicationUsageControl auc) {
    const union ApplicationContextControl ret = {
        .location = {
            .atm = auc.validAtAtms,
            .otherThenAtm = auc.validAtTerminalsOtherThanAtms
        },
        .international = {
            .services = auc.validForInternationalServices,
            .goods = auc.validForInternationalGoods,
            .cash = auc.validForInternationalCash,
            .cashback = auc.validForInternationalCashback,
        },
        .domestic = {
            .services = auc.validForDomesticServices,
            .goods = auc.validForDomesticGoods,
            .cash = auc.validForDomesticCash,
            .cashback = auc.validForDomesticCashback,
        }
    };
    return ret;
}

static inline uint8_t Bcd_To_Binary(const union bcd bcd) {
    return bcd.high * 10 + bcd.low;
}

static inline uint32_t Bcd6_To_U32(const union bcd6 bcd) {
    uint32_t acc = 0;
    for (int i = 0; i < 6; i++) {
        const union bcd tmp = { .raw = bcd.v[i] };
        const uint8_t tmp_acc = Bcd_To_Binary(tmp);
        acc = acc * 100 + tmp_acc;
        // TODO: Check for overflow
    }
    return acc;
}
