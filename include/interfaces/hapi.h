#pragma once

#include "common.h"

// HAP
enum ProcedureResult HAP_Online_Request_to_Dcc_Provider(void);
enum ProcedureResult OnlineApprovalRequest(void);
enum ProcedureResult SearchReservationsByRefData(void);
enum ProcedureResult SearchReservationsByPan(void);
enum ProcedureResult Log_Entry_Data_Retrieval(void);
enum ProcedureResult Initialiase_Basic_Data(void);
enum ProcedureResult Transaction_Finalisation(void);
enum ProcedureResult Transaction_Data_Storage(void);
