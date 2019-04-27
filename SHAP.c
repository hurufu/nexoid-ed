#include "Interface.h"
#include "Common.h"

#include <stdio.h>

void HAP_Online_Request_to_Dcc_Provider(void) {
    puts(__func__);
    g_Result = R_NOK;
}

void SearchReservationsByRefData(void) {
    puts(__func__);
    g_Result = R_OK;
}

void OnlineApprovalRequest(void) {
    puts(__func__);
    g_Result = R_UNABLE_TO_GO_ONLINE;
}

void SearchReservationsByPan(void) {
    puts(__func__);
    g_Result = R_NOK;
}

void SCAP_Cardholder_Confirmation(void) {
    puts(__func__);
    g_Result = R_NOK;
}

void SCAP_Search_Transaction_Result_List(void) {
    puts(__func__);
    g_Result = R_DONE;
}

void SCAP_NoOriginalTransaction(void) {
    puts(__func__);
    g_Result = R_NOK;
}

void Log_Entry_Data_Retrieval(void) {
    puts(__func__);
    g_Result = R_OK;
}

void UpdatePreAuthAmountConfirmation(void) {
    puts(__func__);
    g_Result = R_NOK;
}

void UpdatePreAuthAmountEntry(void) {
    puts(__func__);
    g_Result = R_DONE;
}

void SetUpdatePreAuthTotalAmount(void) {
    puts(__func__);
    g_Result = R_NOK;
}

void Wait_For_Event(void) {
    puts(__func__);
}

void OutputAmountError(void) {
    puts(__func__);
}

void OutputTransactionAmount(void) {
    puts(__func__);
}
