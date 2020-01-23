#include "bool.h"
#include "local.h"
#include "gtd.h"
#include "dmapi.h"

#include <stdio.h>

bool isIssuerCountryExcludedForDcc(void) {
    return false;
}

union ConfiguredServices
ServiceId_to_ConfiguredServices(const enum ServiceId s) {
    union ConfiguredServices ret = { };
    switch (s) {
        case S_PAYMENT:
            ret.payment = 1;
            break;
        case S_REFUND:
            ret.refund = 1;
            break;
        case S_CANCELLATION:
            ret.cancellation = 1;
            break;
        case S_PRE_AUTH:
            ret.preAuthorisation = 1;
            break;
        case S_UPDATE_PRE_AUTH:
            ret.updatePreAuthorisation = 1;
            break;
        case S_PAYMENT_COMPLETION:
            ret.paymentCompletion = 1;
            break;
        case S_CASH_ADVANCE:
            ret.cashAdvance = 1;
            break;
        case S_DEFFERED_PAYMENT:
            ret.deferredPayment = 1;
            break;
        case S_DEFFERED_PAYMENT_COMPLETION:
            ret.deferredPaymentCompletion = 1;
            break;
        case S_VOICE_AUTHORISATION:
            ret.voiceAuthorisation = 1;
            break;
        case S_CARDHOLDER_DETECTION:
            ret.cardholderDetection = 1;
            break;
        case S_CARD_VALIDITY_CHECK:
            ret.cardValidityCheck = 1;
            break;
        case S_NO_SHOW:
            ret.noShow = 1;
            break;
        default:
            break;
    }
    return ret;
}

union ServiceStartEvents
ServiceId_to_AllowedServiceStartEvents(const enum ServiceId s) {
    union ServiceStartEvents ret = { };
    switch (s) {
        case S_PAYMENT:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 0, .manualEntry = 1, .accept = 0, .cardholderDetect = 1 }; break;
        case S_DEFFERED_PAYMENT:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 0, .manualEntry = 1, .accept = 1, .cardholderDetect = 1 }; break;
        case S_DEFFERED_PAYMENT_COMPLETION:
            ret = (union ServiceStartEvents){ .cardInserted = 0, .cardSwiped = 0, .amountEntry = 1, .referenceEntry = 1, .manualEntry = 0, .accept = 0, .cardholderDetect = 0 }; break;
        case S_REFUND:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 0, .manualEntry = 1, .accept = 0, .cardholderDetect = 0 }; break;
        case S_CANCELLATION:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 1, .manualEntry = 1, .accept = 1, .cardholderDetect = 0 }; break;
        case S_PRE_AUTH:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 0, .manualEntry = 1, .accept = 0, .cardholderDetect = 1 }; break;
        case S_UPDATE_PRE_AUTH:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 1, .manualEntry = 1, .accept = 0, .cardholderDetect = 1 }; break;
        case S_PAYMENT_COMPLETION:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 1, .manualEntry = 1, .accept = 0, .cardholderDetect = 1 }; break;
        case S_NO_SHOW:
            ret = (union ServiceStartEvents){ .cardInserted = 0, .cardSwiped = 0, .amountEntry = 1, .referenceEntry = 1, .manualEntry = 1, .accept = 0, .cardholderDetect = 0 }; break;
        case S_CARD_VALIDITY_CHECK:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 0, .referenceEntry = 0, .manualEntry = 1, .accept = 0, .cardholderDetect = 1 }; break;
        case S_CASH_ADVANCE:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 1, .referenceEntry = 0, .manualEntry = 1, .accept = 0, .cardholderDetect = 1 }; break;
        case S_VOICE_AUTHORISATION:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 0, .referenceEntry = 1, .manualEntry = 1, .accept = 1, .cardholderDetect = 0 }; break;
        case S_CARDHOLDER_DETECTION:
            ret = (union ServiceStartEvents){ .cardInserted = 1, .cardSwiped = 1, .amountEntry = 0, .referenceEntry = 1, .manualEntry = 0, .accept = 0, .cardholderDetect = 1 }; break;
        case S_NONE:
        case S_MAX:
            ret = (union ServiceStartEvents){ .cardInserted = 0, .cardSwiped = 0, .amountEntry = 0, .referenceEntry = 0, .manualEntry = 0, .accept = 0, .cardholderDetect = 0 }; break;
    }
    if (TERMINAL_TYPE_UNATTENDED(e1.terminalType)) {
        ret.raw[0] &= ~(union ServiceStartEvents){ .manualEntry = 1, .accept = 1 }.raw[0];
    } else {
        ret.raw[0] &= ~(union ServiceStartEvents){ .cardholderDetect = 1 }.raw[0];
    }
    return ret;
}

struct CombinationListAndParameters*
Copy_Combination_Lists_Entry(const struct CombinationListAndParameters* const r) {
    struct CombinationListAndParameters tmp = {
        .terminalAid = r->terminalAid,
        .kernelId = r->kernelId,
        .terminalTransactionQualifiers = acpptr(r->terminalTransactionQualifiers),
        .statusCheckSupportFlag = acpptr(r->statusCheckSupportFlag),
        .zeroAmountAllowedFlag = acpptr(r->zeroAmountAllowedFlag),
        .readerCtlessTransactionLimit = acpptr(r->readerCtlessTransactionLimit),
        .readerCtlessFloorLimit = acpptr(r->readerCtlessFloorLimit),
        .readerCvmRequiredLimit= acpptr(r->readerCvmRequiredLimit),
        .extendedSelectionSupported = acpptr(r->extendedSelectionSupported),
        .next = NULL
    };
    if (ttd.transactionAmountEntered) {
        tmp.statusCheckRequested = acpval(false);
        tmp.zeroAmount = acpval(false);
        tmp.ctlessApplicationNotAllowed = acpval(false);
        tmp.readerCtlessFloorLimitNotAllowed = acpval(false);
        tmp.readerCvmRequiredLimitExceeded = acpval(false);
    } else {
        tmp.statusCheckRequested = acpptr(r->statusCheckRequested);
        tmp.zeroAmount = acpptr(r->zeroAmount);
        tmp.ctlessApplicationNotAllowed = acpptr(r->ctlessApplicationNotAllowed);
        tmp.readerCtlessFloorLimitNotAllowed = acpptr(r->readerCtlessFloorLimitNotAllowed);
        tmp.readerCvmRequiredLimitExceeded = acpptr(r->readerCvmRequiredLimitExceeded);
    }
    return acpval(tmp);
}
