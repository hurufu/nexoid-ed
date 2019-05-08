#pragma once

#include "Common.h"

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

enum Wait_For_Event {
    Wait_For_Event_OK = R_OK,
    Wait_For_Event_NOK = R_NOK
} Wait_For_Event(
        bool (* Event)[E_MAX],
        char (* ReferenceData)[35 + 1],
        enum ServiceId* const SelectedService)
    __attribute__((nonnull(1), warn_unused_result));

void OutputAmountError(void);
void OutputTransactionAmount(void);
void Authorise_Service(void);
void Update_Cardholder_Initial_Message(void);
void Output(int);
void DeactivateAllInterfaces(void);
void Enable_Allowed_Interfaces(void);

// Proprietary
void Proprietary_Startup_Sequence(void);
