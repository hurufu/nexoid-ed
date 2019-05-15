#pragma once

#include "Common.h"

// HAP
enum ProcedureResult HAP_Online_Request_to_Dcc_Provider(void);
enum ProcedureResult OnlineApprovalRequest(void);
enum ProcedureResult SearchReservationsByRefData(void);
enum ProcedureResult SearchReservationsByPan(void);
enum ProcedureResult Log_Entry_Data_Retrieval(void);
enum ProcedureResult Initialiase_Basic_Data(void);

// SCAP
enum ProcedureResult SCAP_Cardholder_Confirmation(void);
enum ProcedureResult SCAP_Search_Transaction_Result_List(void);
enum ProcedureResult SCAP_NoOriginalTransaction(void);
enum ProcedureResult UpdatePreAuthAmountConfirmation(void);
enum ProcedureResult UpdatePreAuthAmountEntry(void);
enum ProcedureResult SetUpdatePreAuthTotalAmount(void);

enum Wait_For_Event {
    Wait_For_Event_OK = R_OK,
    Wait_For_Event_NOK = R_NOK
} Wait_For_Event(
        bool (* Event)[E_MAX],
        char (* ReferenceData)[35 + 1],
        enum ServiceId* const SelectedService)
    __attribute__((nonnull(1), warn_unused_result));

enum ProcedureResult OutputAmountError(void);
enum ProcedureResult OutputTransactionAmount(void);
bool Authorise_Service(void);
enum ProcedureResult Update_Cardholder_Initial_Message(void);
enum ProcedureResult Output(int);
enum ProcedureResult DeactivateAllInterfaces(void);
enum ProcedureResult Enable_Allowed_Interfaces(void);

// Proprietary
enum ProcedureResult Proprietary_Startup_Sequence(void);
