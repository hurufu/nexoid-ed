#pragma once

#include "dmapi.h"
#include "papi.h"
#include "scapi.h"
#include "eapi.h"
#include "hapi.h"
#include "pklr.h"
#include "tmapi.h"
#include "gtd.h"
#include "local.h"
#include "bool.h"

#include "tag_retrival.h"

#include <string.h>
#include <stdlib.h>

// FIXME: Definition of ApplicationLabelList is probably wrong
struct ApplicationLabelList {
    struct Aid adf;
    struct string16 applicationLabel;
    struct string16 applicationPreferredName;
    enum IssuerCodeTableIndex issuerCodeTableIndex;
    struct ApplicationLabelList* next;
};

struct ApplicationKernelAndAppProfileSelection {
    bool cardholderConfirmedOnce;
    struct ApplicationLabelList* applicationLabelList;
    unsigned char panMatchLength; // integer
};

struct TechnologySelection {
    unsigned char numberOfRemainingChipTries;
    bool invalidSwipeOccured;
    union ServiceCodeMs* serviceCodeMs;
    bool contactlessAllowed;
    bool showUpfrontButton;
};

enum DeliveryResult {
    DELIVERY_OK,
    DELIVERY_NOK,
    DELIVERY_PARTIAL
};

struct TransactionCompletion {
    bool printCardholderReceipt;
    bool printMerchantReceipt;
    enum DeliveryResult deliveryResult;
    union bcd6 reducedAmount;
};

struct CardholderVerification {
    uint8_t* pinTryCounter;
    struct CvRule* cvRule;
};

struct TerminalRiskManagement {
    // NEXO: More optimal checkedAmount is used instean of lastTransactionAmount
    union bcd randomNumberforBsr;
    union bcd trxTargetPercentage;
};

static struct ApplicationKernelAndAppProfileSelection s_akps;
static struct TechnologySelection s_ts;
static struct TransactionCompletion s_tc;
static struct CardholderVerification s_cv;
static struct TerminalRiskManagement s_trm;
