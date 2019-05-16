#include "Interface.h"
#include "Common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum ProcedureResult
HAP_Online_Request_to_Dcc_Provider(void) {
    puts(__func__);
    return PR_NOK;
}

enum ProcedureResult
SearchReservationsByRefData(void) {
    puts(__func__);
    return PR_OK;
}

enum ProcedureResult
OnlineApprovalRequest(void) {
    puts(__func__);
    return PR_UNABLE_TO_GO_ONLINE;
}

enum ProcedureResult
SearchReservationsByPan(void) {
    puts(__func__);
    return PR_NOK;
}

enum ProcedureResult
SCAP_Cardholder_Confirmation(void) {
    puts(__func__);
    return PR_NOK;
}

enum ProcedureResult
SCAP_Search_Transaction_Result_List(void) {
    puts(__func__);
    return PR_DONE;
}

enum ProcedureResult
SCAP_NoOriginalTransaction(void) {
    puts(__func__);
    return PR_NOK;
}

enum ProcedureResult
Log_Entry_Data_Retrieval(void) {
    puts(__func__);
    return PR_OK;
}

enum ProcedureResult
Initialiase_Basic_Data(void) {
    puts(__func__);
    return PR_OK;
}

enum ProcedureResult
UpdatePreAuthAmountConfirmation(void) {
    puts(__func__);
    return PR_NOK;
}

enum ProcedureResult
UpdatePreAuthAmountEntry(void) {
    puts(__func__);
    return PR_DONE;
}

enum ProcedureResult
SetUpdatePreAuthTotalAmount(void) {
    puts(__func__);
    return PR_NOK;
}

enum ProcedureResult Wait_For_Event(bool (* const Event)[E_MAX],
                                    char (* const ReferenceData)[35 + 1],
                                    union Amount* TransactionAmount,
                                    enum ServiceId* const SelectedService) {
    static bool terminate = false;
    puts(__func__);

    if (terminate) {
        (*Event)[E_TERMINATION_REQUESTED] = true;
    } else {
        (*Event)[E_SERVICE_SELECTION] = true;
        *SelectedService = S_CARD_VALIDITY_CHECK;

        (*Event)[E_AMOUNT_ENTRY] = true;
        TransactionAmount->i = 0;
    }
    terminate = true;

    return PR_NEW_EVENT;
}

enum ProcedureResult
OutputAmountError(void) {
    puts(__func__);
    return PR_OK;
}

enum ProcedureResult Entry(int msgId) {
    printf("%s %d\n", __func__, msgId);
    return PR_OK;
}

enum ProcedureResult
OutputTransactionAmount(void) {
    puts(__func__);
    return PR_OK;
}

bool Authorise_Service(void) {
    puts(__func__);
    return true;
}

enum ProcedureResult
Update_Cardholder_Initial_Message(void) {
    puts(__func__);
    return PR_OK;
}

enum ProcedureResult
Output(int msgId) {
    printf("%s %d\n", __func__, msgId);
    return PR_OK;
}

enum ProcedureResult
DeactivateAllInterfaces(void) {
    puts(__func__);
    return PR_OK;
}

enum ProcedureResult
Enable_Allowed_Interfaces(void) {
    puts(__func__);
    return PR_DONE;
}

enum ProcedureResult Proprietary_Startup_Sequence(void) {
    puts(__func__);
    g_Nexo = (struct NexoConfiguration){
        // Terminal configuration
        .TerminalType = 0x03,
        .TerminalSettings = {
            .retrievePreauth = 0
        },

        // Application configuration
        .DefaultService = S_PAYMENT,
        .ApplicationCurrency = NULL,
        .CardholderDefaultLanguage = { Country_pl },

        .ServiceStartEvents = {
            [S_PRE_AUTH] = {
                .referenceEntry = 1
            },
            [S_CARD_VALIDITY_CHECK] = {
                .cardInserted = 1,
                .cardSwiped = 1
            }
        },
        .ServiceSettings = {
            [S_PRE_AUTH] = {
                .ContactChipPrioritized = 1,
                .ServiceProtected = 1
            },
            [S_CARD_VALIDITY_CHECK] = {
                .ContactChipPrioritized = 1,
                .ServiceProtected = 1
            }
        },
        .ApplicationProfileSettings = {
            .isDccAcceptorModeAllowed = 1
        },

        // CVC
        .CvcDefaultAmount = NULL,

        // DCC
        .DccMinimumAllowedAmount = {{ 0x00, 0x00, 0x00, 0x00, 0x15, 0x00 }},

        // Contactless
        .CombListsAndParams = acpval(
            ((struct CombinationsListAndParametersEntry){
                .terminalAid = {
                    .size = 6,
                    .value = { 0x43, 0x00, 0x01 }
                },
                .kernelId = 0x01,
                .supportingServices = {
                    .raw = { 0xFF, 0xFF }
                },
                .cashbackPresent = acpval(false),
                .zeroAmountAllowed = acpval(true),

                .next = NULL
            })
        )
    };
    return PR_OK;
}

enum ProcedureResult Diagnostics_Maintenance_Recovery(void) {
    puts(__func__);
    if (fork() == 0) {
        abort();
    } else {
        wait(NULL);
    }
    return PR_NOK;
}

void Force_Reboot(void) {
    puts(__func__);
}

void Force_Termination(void) {
    puts(__func__);
}

void Force_Shutdown(void) {
    puts(__func__);
}
