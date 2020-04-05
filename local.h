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
