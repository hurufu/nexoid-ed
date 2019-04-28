#pragma once

// HAP
extern void HAP_Online_Request_to_Dcc_Provider(void);
extern void OnlineApprovalRequest(void);
extern void SearchReservationsByRefData(void);
extern void SearchReservationsByPan(void);
extern void Log_Entry_Data_Retrieval(void);
extern void Initialiase_Basic_Data(void);

// SCAP
extern void SCAP_Cardholder_Confirmation(void);
extern void SCAP_Search_Transaction_Result_List(void);
extern void SCAP_NoOriginalTransaction(void);
extern void UpdatePreAuthAmountConfirmation(void);
extern void UpdatePreAuthAmountEntry(void);
extern void SetUpdatePreAuthTotalAmount(void);
extern void Wait_For_Event(void);
extern void OutputAmountError(void);
extern void OutputTransactionAmount(void);
extern void Authorise_Service(void);
extern void Update_Cardholder_Initial_Message(void);
extern void Output(int);
extern void DeactivateAllInterfaces(void);
extern void Enable_Allowed_Interfaces(void);
