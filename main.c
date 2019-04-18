#include "CardValidityCheck.h"
#include "Common.h"
#include <stdio.h>
#include <string.h>

static struct Ctd s_ctd = {
    .CvcDefaultAmount = &(const struct Amount){ .bcd = { 0x00, 0x00, 0x00, 0x00, 0x11, 0x00 } },
    .KernelId = 0xC1,
    .Outcome = O_ONLINE_REQUEST,
    .Out = { .Start = NONE },
    .TransactionAmount = { .bcd = { 0x00, 0x00, 0x00, 0x00, 0x05, 0x00 } },
    .TransactionResult = T_NONE,
    .TransactionType = TT_UNKNOWN,
    .TransactionCurrency = { .Str = "PLN" },
    .Result = R_NOK,
    .NokReason = N_NOT_IMPLEMENTED,
    .ServiceSettings = { .isContactChipPrioritized = 1 },
    .ServiceStartEvents = { .cardInserted = 1 },
    .ApplicationProfileSettings = { .isDccAcceptorModeAllowed = 1 },
    .ApplicationCurrency = &(union Currency){ .Str = "EUR" },
    .IssuerCountry = &(union Country){ .Str = "pl" },
    .TransactionAmountEntered = false,
    .SelectedService = S_CARD_VALIDITY_CHECK
};

int main() {
    tg_ctd = &s_ctd;
    Card_Validity_Check();
    ctd_print(tg_ctd);
    tg_ctd = NULL;
    memset(&s_ctd, 0, sizeof(s_ctd));

    return 0;
}
