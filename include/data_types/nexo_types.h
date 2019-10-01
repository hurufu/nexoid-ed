#pragma once

// Based on nexo-FAST section 13.3

union ApplicationProfileSettings {
    uint8_t raw[5];
    struct {
        uint8_t approvalOfPaymentPartOnlyAllowed : 1;
        uint8_t /* RFU */ : 2;
        uint8_t terminalInitiatedVoiceAuthAllowed : 1;
        uint8_t referralAllowed : 1;
        uint8_t supplementaryAmountAllowed : 1;
        uint8_t cashbackAllowed : 1;
        uint8_t checkAmountsAgainstMinMax : 1;

        uint8_t cardholderConfirmationRequiredForDeferredPaymentTrxAmt : 1;
        uint8_t refundOnline : 1;
        uint8_t forcedApprovalAllowedForOnlineDeclinedTrx : 1;
        uint8_t forcedApprovalAllowedForOfflineDeclinedTrx : 1;
        uint8_t pinBypassAllowed : 1;
        uint8_t cvdRequiredForManualEntry : 1;
        uint8_t cdaRequiredForTcIn2ndGenAc : 1;
        uint8_t cdaRequiredForArqcIn2ndGenAc : 1;

        uint8_t retrieveVoiceAuthFromTrxLog : 1;
        uint8_t performExceptionFileChecking : 1;
        uint8_t /* RFU */ : 1;
        uint8_t retrieveUpdatePreAuthFromTrxLog : 1;
        uint8_t /* RFU */ : 1;
        uint8_t partialApprovalSupported : 1;
        uint8_t isDccAcceptorModeAllowed : 1; // TODO: Place it into the proper bit
        uint8_t balanceDisplaySupported : 1;

        union ReceiptSettings merchantReceipt;
        union ReceiptSettings cardholderReceipt;

    };
};

union ApplicationProfileSettingsForCancellation {
    uint8_t raw[2];
    struct {
        uint8_t /* RFU */ : 3;
        uint8_t cancellationOfCashAdvanceAllowed : 1;
        uint8_t cancellationOfPaymentCompletionAllowed : 1;
        uint8_t cancellationOfPreAuthAllowed : 1;
        uint8_t cancellationOfRefundAllowed : 1;
        uint8_t cancellationOfPaymentAllowed : 1;

        // TODO: Use some better names for each bit
        uint8_t /* RFU */ : 3;
        uint8_t cancellationOfReconciledTransactionAllowed : 1;
        uint8_t capturedOnline : 1;
        uint8_t captured : 1;
        uint8_t online : 1;
    };
};
