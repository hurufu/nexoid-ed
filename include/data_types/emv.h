#pragma once

union TerminalVerificationResults {
    uint8_t raw[5];
    struct {
        uint8_t /* RFU */ : 1;
        uint8_t sdaSelected : 1;
        uint8_t cdaFailed : 1;
        uint8_t ddaFailed : 1;
        uint8_t cardNumberAppearsOnHotlist : 1;
        uint8_t iccDataMissing : 1;
        uint8_t sdaFailed : 1;
        uint8_t offlineDataProcessingWasNotPerformed : 1;

        uint8_t /* RFU */ : 3;
        uint8_t newCard : 1;
        uint8_t requestedServiceNotAllowedForCardProduct : 1;
        uint8_t applicationNotYetEffective : 1;
        uint8_t expiredApplication : 1;
        uint8_t cardAndTerminalHaveDifferentApplicationVersions : 1;

        uint8_t /* RFU */ : 2;
        uint8_t onlinePinEntered : 1;
        uint8_t pinEntryRequiredPinPadPresentButPinWasNotEntered : 1;
        uint8_t pinEntryRequiredButNoPinPadPresentOrNotWorking : 1;
        uint8_t pinEntryTryLimitExceeded : 1;
        uint8_t unrecognisedCvm : 1;
        uint8_t cardholderVerificationWasNotSuccessful : 1;

        uint8_t /* RFU */ : 3;
        uint8_t merchantForcedTransactionOnline : 1;
        uint8_t transactionSelectedRandomlyForOnLineProcessing : 1;
        uint8_t upperConsecutiveOfflineLimitExceeded : 1;
        uint8_t lowerConsecutiveOfflineLimitExceeded : 1;
        uint8_t transactionExceedsFloorLimit : 1;

/*1~4*/ uint8_t /* RFU */ : 4;
        uint8_t scriptProcessingFailedAfterFinalGenerateAc : 1;
        uint8_t scriptProcessingFailedBeforeFinalGenerateAc : 1;
        uint8_t issuerAuthenticationFailed : 1;
/*8*/   uint8_t defaultTdolUsed : 1;
    };
};

union ReceiptSettings {
    uint8_t raw[1];
    struct {
        uint8_t printApproved : 1;
        uint8_t printDeclined : 1;
        uint8_t printVoiceAuth : 1;
        uint8_t printAborted : 1;
        uint8_t isMerchantSignatureRequiredForApprovedRefund : 1; // Only for ATC[4,4]
        uint8_t printDolOnApprovedAndAbortedAndVoiceAuth : 1;
        uint8_t printDolOnDeclinedAndAborted : 1;
        uint8_t specificPanProcessingForEmvChip : 1; // Only for ATC[5,1]
    };
};

union AdditionalTerminalCapabilities {
    unsigned char raw[5];
    struct {
        struct TransactionTypeCapability {
            unsigned char cash : 1;
            unsigned char goods : 1;
            unsigned char services : 1;
            unsigned char cashback : 1;
            unsigned char inquiry : 1;
            unsigned char transfer : 1;
            unsigned char payment : 1;
            unsigned char administrative : 1;

            unsigned char cashDeposit : 1;
            unsigned char /* RFU */ : 1;
        } transactionType;

        struct TransactionDataInputCapability {
            unsigned char numericKeys : 1;
            unsigned char alphabeticAndSpecialCharactersKeys : 1;
            unsigned char commandKeys : 1;
            unsigned char functionKeys : 1;
            unsigned char /* RFU */ : 4;
        } terminalDataInput;

        struct TransactionDataOutputCapability {
            unsigned char printAttendant : 1;
            unsigned char printCardholder : 1;
            unsigned char displayAttendant : 1;
            unsigned char displayCardholder : 1;
            unsigned char /* RFU */ : 2;
            // ISO/IEC 8859
            unsigned char codeTable10 : 1;
            unsigned char codeTable9 : 1;

            unsigned char codeTable8 : 1;
            unsigned char codeTable7 : 1;
            unsigned char codeTable6 : 1;
            unsigned char codeTable5 : 1;
            unsigned char codeTable4 : 1;
            unsigned char codeTable3 : 1;
            unsigned char codeTable2 : 1;
            unsigned char codeTable1 : 1;
        } terminalDataOutput;
    };
};

union CvmCapability {
    uint8_t raw[1];
    struct {
/*1-3*/ uint8_t /* RFU */ : 3;
/*4*/   uint8_t noCvm : 1;
/*5*/   uint8_t encipheredPinForOfflineVerification : 1;
/*6*/   uint8_t signatureOnPaper : 1;
/*7*/   uint8_t encipheredPinForOnlineVerification : 1;
/*8*/   uint8_t plainTextForIccVerification : 1;
    };
};

union MagStripeCvmCapability {
    uint8_t raw[1];
    struct {
/*1-4*/ uint8_t /* RFU */ : 4;
        enum PACKED {
            MSR_CVM_NO_CVM = 0x0
          , MSR_CVM_OBTAIN_SIGNATURE = 0x1
          , MSR_CVM_ONLINE_PIN = 0x2
          , MSR_CVM_NA = 0xF
/*5-8*/ } e : 4;
    };
};
