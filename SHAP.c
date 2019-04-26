#include "Interface.h"
#include "Common.h"

#include <stdio.h>

void HAP_Online_Request_to_Dcc_Provider(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void SearchReservationsByRefData(void) {
    puts(__func__);
    tg_ctd->Result = R_OK;
}

void OnlineApprovalRequest(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void SearchReservationsByPan(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void SCAP_Cardholder_Confirmation(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void SCAP_Search_Transaction_Result_List(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void SCAP_NoOriginalTransaction(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void CopyDataFromSearchResultToCtd(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void UpdatePreAuthAmountConfirmation(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void UpdatePreAuthAmountEntry(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}

void SetUpdatePreAuthTotalAmount(void) {
    puts(__func__);
    tg_ctd->Result = R_NOK;
}
