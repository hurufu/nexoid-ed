#pragma once

#include <stdint.h>
#include <bool.h>

enum Outcome {
    O_NONE

  // Final outcome
  , O_APPROVED
  , O_DECLINED
  , O_ONLINE_REQUEST
  , O_TRY_ANOTHER_INTERFACE
  , O_END_APPLICATION

  // Non final outcome
  , O_SELECT_NEXT
  , O_TRY_AGAIN
};

enum Start {
    NONE
  , A
  , B
  , C
  , D
  , E
  , F
};

enum OnlineResponseData {
    ONLINE_RES_NONE
  , ONLINE_RES_EMV_DATA
  , ONLINE_RES_ANY
};

enum Cvm {
    CVM_NONE
  , CVM_ONLINE_PIN
  , CVM_CONFIRMATION
  , CVM_CODE_VERIFIED
  , CVM_OBTAIN_SIGNATURE
  , CVM_NO_CVM
};

enum AlternateInterfacePreference {
    INTERFACE_PREFERENCE_NONE
  , INTERFACE_PREFERENCE_CONTACT_CHIP
  , INTERFACE_PREFERENCE_MAGSTRIPE
};

enum Receipt {
    RECEIPT_NONE
  , RECEIPT_PRINT
};

struct OutcomeParameters {
    enum Start Start;
    enum OnlineResponseData OnlineResponseData;
    enum Cvm Cvm;
    bool UiRequestOnOutcomePresent;
    bool UiRequestOnRestartPresent;
    bool DataRecordPresent;
    bool DiscretionaryDataPresent;
    enum AlternateInterfacePreference AlternateInterfacePreference;
    enum Receipt Receipt;
    uint8_t FieldOffRequest;
    uint8_t RemovalTimeout;
};
