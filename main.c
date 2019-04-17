#include "CardValidityCheck.h"
#include "Common.h"
#include <stdio.h>

static struct Ctd s_ctd = {
    .CvcDefaultAmount = &(const struct Amount){ .bcd = { 0x00, 0x00, 0x00, 0x00, 0x11, 0x00 } },
    .KernelId = 0xC1,
    .Outcome = O_ONLINE_REQUEST,
    .Out = { .Start = NONE },
    .TransactionAmount = { .bcd = { 0x00, 0x00, 0x00, 0x00, 0x05, 0x00 } },
    .TransactionResult = T_NONE,
    .TransactionType = TT_UNKNOWN,
    .Result = R_NOK,
    .NokReason = N_NOT_IMPLEMENTED,
    .ServiceSettings = { .isContactChipPrioritized = 1 },
    .ServiceStartEvents = { .cardInserted = 1 },
    .TransactionAmountEntered = false,
    .SelectedService = S_CARD_VALIDITY_CHECK
};

int main() {
    tg_ctd = &s_ctd;
    Card_Validity_Check();
    ctd_print(tg_ctd);
    tg_ctd = NULL;

    return 0;
}
