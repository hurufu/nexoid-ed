#pragma once

#include "common.h"

#if 0
#   define DEPRECATED(Msg) __attribute__(( __deprecated__(Msg) ))
#   define WARN(Msg) __attribute__(( __warning__(Msg) ))
#else
#   define DEPRECATED(Msg)
#   define WARN(Msg)
#endif

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
enum ProcedureResult Output(size_t size, const enum CardholderMessage msg[size]);
enum ProcedureResult Data_Output_Interaction(size_t size, const struct UiParameters msg[size]) DEPRECATED("Use Data_Output_Interaction instead");
enum ProcedureResult Entry(int) DEPRECATED("Use Date_Entry_Interaction instead");
enum ProcedureResult Date_Entry_Interaction() WARN("Function signature isn't yet defined");
enum ProcedureResult DeactivateAllInterfaces(void);
enum ProcedureResult Enable_Allowed_Interfaces(void);
