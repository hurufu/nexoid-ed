#pragma once

union TerminalVerificationResults {
    uint8_t raw[5];
    struct {
        // TODO: Fill TVR bitfield
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
        } TransactionType;

        struct TransactionDataInputCapability {
            unsigned char numericKeys : 1;
            unsigned char alphabeticAndSpecialCharactersKeys : 1;
            unsigned char commandKeys : 1;
            unsigned char functionKeys : 1;
            unsigned char /* RFU */ : 4;
        } TerminalDataInput;

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
        } TerminalDataOutput;
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
