#include "Interface.h"
#include "Common.h"

#include <stdio.h>

void HAP_Online_Request_to_Dcc_Provider(void) {
    puts(__func__);
}

void SearchReservationsByRefData(void) {
    puts(__func__);
    tg_ctd->Result = R_NOT_FOUND;
}

void SearchReservationsByPan(void) {
    puts(__func__);
}

void SCAP_Cardholder_Confirmation(void) {
    puts(__func__);
}

void SCAP_Search_Transaction_Result_List(void) {
    puts(__func__);
}

void SCAP_NoOriginalTransaction(void) {
    puts(__func__);
}

void CopyDataFromSearchResultToCtd(void) {
    puts(__func__);
}
