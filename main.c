#include "CardValidityCheck.h"
#include "Common.h"
#include <stdio.h>

static struct Ctd s_ctd = {
    .CvcDefaultAmount = &(unsigned char[]){ 0x00, 0x00, 0x00, 0x00, 0x11, 0x00 },
    .KernelId = 1,
    .Outcome = O_ONLINE_REQUEST,
    .Out = { .Start = NONE },
    .TransactionAmount = &(unsigned char[]){ 0x00, 0x00, 0x00, 0x00, 0x05, 0x00 },
    .TransactionResult = T_NONE,
    .TransactionType = TT_UNKNOWN
};

int main() {
    tg_ctd = &s_ctd;
    Card_Validity_Check();
    ctd_print(tg_ctd);
    tg_ctd = NULL;

    return 0;
}
