#pragma once

extern void HAP_Online_Request_to_Dcc_Provider(void);
extern void SearchReservationsByRefData(void);
extern void SearchReservationsByPan(void);

extern void SCAP_Cardholder_Confirmation(void);
extern void SCAP_Search_Transaction_Result_List(void);
extern void SCAP_NoOriginalTransaction(void);

extern void CopyDataFromSearchResultToCtd(void);
