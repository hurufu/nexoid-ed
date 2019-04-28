#pragma once

// HAP
void HAP_Online_Request_to_Dcc_Provider(void);
void OnlineApprovalRequest(void);
void SearchReservationsByRefData(void);
void SearchReservationsByPan(void);
void Log_Entry_Data_Retrieval(void);
void Initialiase_Basic_Data(void);

// SCAP
void SCAP_Cardholder_Confirmation(void);
void SCAP_Search_Transaction_Result_List(void);
void SCAP_NoOriginalTransaction(void);
void UpdatePreAuthAmountConfirmation(void);
void UpdatePreAuthAmountEntry(void);
void SetUpdatePreAuthTotalAmount(void);
void Wait_For_Event(void);
void OutputAmountError(void);
void OutputTransactionAmount(void);
void Authorise_Service(void);
void Update_Cardholder_Initial_Message(void);
void Output(int);
void DeactivateAllInterfaces(void);
void Enable_Allowed_Interfaces(void);
