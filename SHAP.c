#include "Interface.h"
#include "Common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum ProcedureResult
HAP_Online_Request_to_Dcc_Provider(void) {
    puts(__func__);
    return R_NOK;
}

enum ProcedureResult
SearchReservationsByRefData(void) {
    puts(__func__);
    return R_OK;
}

enum ProcedureResult
OnlineApprovalRequest(void) {
    puts(__func__);
    return R_UNABLE_TO_GO_ONLINE;
}

enum ProcedureResult
SearchReservationsByPan(void) {
    puts(__func__);
    return R_NOK;
}

enum ProcedureResult
SCAP_Cardholder_Confirmation(void) {
    puts(__func__);
    return R_NOK;
}

enum ProcedureResult
SCAP_Search_Transaction_Result_List(void) {
    puts(__func__);
    return R_DONE;
}

enum ProcedureResult
SCAP_NoOriginalTransaction(void) {
    puts(__func__);
    return R_NOK;
}

enum ProcedureResult
Log_Entry_Data_Retrieval(void) {
    puts(__func__);
    return R_OK;
}

enum ProcedureResult
Initialiase_Basic_Data(void) {
    puts(__func__);
    return R_OK;
}

enum ProcedureResult
UpdatePreAuthAmountConfirmation(void) {
    puts(__func__);
    return R_NOK;
}

enum ProcedureResult
UpdatePreAuthAmountEntry(void) {
    puts(__func__);
    return R_DONE;
}

enum ProcedureResult
SetUpdatePreAuthTotalAmount(void) {
    puts(__func__);
    return R_NOK;
}

enum Wait_For_Event Wait_For_Event(bool (* const Event)[E_MAX],
                                   char (* const ReferenceData)[35 + 1],
                                   enum ServiceId* const SelectedService
                                  ) {
    static bool oneTime = false;
    puts(__func__);

    if (!oneTime) {
        oneTime = true;
        (*Event)[E_SERVICE_SELECTION + 100] = true;
        *SelectedService = S_UPDATE_PRE_AUTH;

        (*Event)[E_REFERENCE_ENTRY] = true;
        snprintf(*ReferenceData, sizeof(*ReferenceData), "%d", 624523454);
    } else {
        exit(0);
    }
    return Wait_For_Event_OK;
}

enum ProcedureResult
OutputAmountError(void) {
    puts(__func__);
}

enum ProcedureResult
OutputTransactionAmount(void) {
    puts(__func__);
}

bool Authorise_Service(void) {
    puts(__func__);
    return true;
}

enum ProcedureResult
Update_Cardholder_Initial_Message(void) {
    puts(__func__);
    return R_OK;
}

enum ProcedureResult
Output(int msgId) {
    printf("%s %d\n", __func__, msgId);
    return R_OK;
}

enum ProcedureResult
DeactivateAllInterfaces(void) {
    puts(__func__);
    return R_OK;
}

enum ProcedureResult
Enable_Allowed_Interfaces(void) {
    puts(__func__);
    return R_DONE;
}

enum ProcedureResult Proprietary_Startup_Sequence(void) {
    puts(__func__);
    return R_OK;
}
