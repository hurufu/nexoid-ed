#pragma once

#include "common.h"

// SCAP
enum ProcedureResult SCAP_Cardholder_Confirmation(void);
enum ProcedureResult SCAP_Search_Transaction_Result_List(void);
enum ProcedureResult SCAP_NoOriginalTransaction(void);
enum ProcedureResult UpdatePreAuthAmountConfirmation(void);
enum ProcedureResult UpdatePreAuthAmountEntry(void);
enum ProcedureResult SetUpdatePreAuthTotalAmount(void);
enum ProcedureResult Wait_For_Event(void);
enum ProcedureResult OutputAmountError(void);
enum ProcedureResult OutputTransactionAmount(void);
bool Authorise_Service(void);
enum ProcedureResult Update_Cardholder_Initial_Message(void);
enum ProcedureResult Output(int);
enum ProcedureResult Entry(int);
enum ProcedureResult DeactivateAllInterfaces(void);
enum ProcedureResult Enable_Allowed_Interfaces(void);
