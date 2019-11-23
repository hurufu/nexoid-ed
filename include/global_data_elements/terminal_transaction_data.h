#pragma once

#include "bool.h"
#include "types.h"

struct TerminalTransactionData {
    bool acquirerPreSelected;
    struct bcd2 preSelectedAcquirerNumber;
    bool cardholderLanguageIsSelected;
    bool applicationInitialised;
    union Amount transactionAmount;
    union Amount cashbackAmount;
    bool transactionAmountEntered;
    bool cardholderRequestedChoiceOfApplication;
    bool cardholderRequestedChangeOfApplication;
    bool cardholderAcceptedSelectedApplication;
    enum TransactionResult transactionResult;
    enum NokReason nokReason;
    union CurrencyAlpha3 transactionCurrencyCodeAlpha3;
    bool attendantForcedTransactionOnline;
    bool fallbackFlag;
    bool unableToGoOnline;
    enum Kernel kernelId;
    enum KernelMode kernelMode;
    enum Technology technologySelected;
    union ProcessingStatus processingStatus;
    bool exceptionFileCheckPerformed;
    bool exceptionFileMatch;
    bool continueFlag; // Original nexo name 'continue' is a reserved word in C
    bool confirmationByCard;
    bool candidateListHasOneEntry;
    bool pinPadNotWorking;
    struct UiParameters uiParametersForOutcome;
    struct UiParameters uiParametersForRestart;
    struct UiParameters uiParametersForTrxCompletion;
    bool cdaFailed; // FIXME: Delete this parameter
    bool onlineRequired; // FIXME: Delete this parameter
    bool aacReceived; // FIXME: Delete this parameter
    bool tcReceived; // FIXME: Delete thi parameter
    bool uiRequestPostponed;
    bool signatureLine;
    bool signatureLineMerchant;
    bool signatureLineForVoiceAuthorisation;
    unsigned char (* pan)[11]; // FIXME: Use proper structure for PAN
    bool isDccEligible;
    bool dccPerformedOnce;
    bool* minus; // FIXME: Consider making minus a value, and not a pointer
    bool amountDisplayed;
    union Country selectedLanguage;
    enum TerminalErrorReason terminalErrorReason;
    bool terminalErrorIndicator;
    bool transactionConfirmedByCardholder; // EMV also
    struct Track2 track2Data; // FIXME: Use proper structure for Track 2
    const struct Bid* selectedBid;
    bool panEnteredManually;
    struct CombinationListAndParameters* combListWorkingTable;
    bool timeoutIndicator;
    bool noContactlessAllowed;
    union ServiceStartEvents serviceStartEvents;

    // FIXME: Consider moving to a different location
    struct EventTable {
        bool Table[E_MAX];
    } event;

    // NOTE: IsCardInReader isn't defined by nexo
    // TODO: Consider making IsCardInReader an atomic variable
    bool isCardInReader;

    // NOTE: forcedTransactionApproval isn't defined by nexo, it's only
    // referenced briefly in nexo-FAST v.3.2 figure 64
    bool forcedTransactionApproval;

    // NOTE: forcedTransactionApproval isn't defined by nexo, it's only
    // referenced briefly in nexo-FAST v.3.2  note 105-10
    bool wasPresentOneCardOnlyMessageDisplayed;

    // FIXME: Consider different place for transactionType
    enum TransactionType transactionType;

    // FIXME: Consider different place for selectedService or even removal,
    // because this information may be available in ServiceConfiguration
    enum ServiceId selectedService;

    // FIXME: Consider removing authorisationResponseCode, as it is alread
    // defined in OnlineResponseData and KernelData, conversly it may be a good
    // idea to leave it here so it will be populated by any of the previous
    // values
    enum AuthorisationResponseCode authorisationResponseCode;

    // FIXME: Same as previous, but may be set by any process
    union TerminalVerificationResults tvr;

    // FIXME: Consider better type for referenceData
    char referenceData[35 + 1];

    // FIXME: Consider different place for selectedApplicationProfileNumber or
    // even removal, because this information may be available in ServiceConfiguration
    unsigned char selectedApplicationProfileNumber;

    // FIXME: Consider different place for Out and Outcome
    enum Outcome outcome;
    struct OutcomeParameters out;
};
