#include "ctl-io.h"
#include "gtd.h"
#include "NexoFast.h"

#include <stdio.h>
#include <stdlib.h>

static const char* hexstring(const size_t s, const uint8_t d[s], char b[s*2+1]) {
    char* c = b;
    for (int i = 0; i < s; i++) {
        c += snprintf(c, 3, "%02X", d[i]);
    }
    return b;
}

static struct TransactionTypeCapability conv_TransactionTypeCapability(const ctl_TransactionTypeCapability src) {
    return (struct TransactionTypeCapability){
        .cash = src.cash,
        .goods = src.goods,
        .services = src.services,
        .cashback = src.cashback,
        .inquiry = src.inquiry,
        .transfer = src.transfer,
        .payment = src.payment,
        .administrative = src.administrative,
        .cashDeposit = src.cashDeposit,
    };
}

static struct TransactionDataInputCapability conv_TransactionDataInputCapability(const ctl_TransactionDataInputCapability src) {
    return (struct TransactionDataInputCapability){
        .numericKeys = src.numericKeys,
        .alphabeticAndSpecialCharactersKeys = src.alphabeticAndSpecialCharactersKeys,
        .commandKeys = src.commandKeys,
        .functionKeys = src.functionKeys,
    };
}

static struct TransactionDataOutputCapability conv_TransactionDataOutputCapability(const ctl_TransactionDataOutputCapability src) {
    return (struct TransactionDataOutputCapability){
        .printAttendant = src.printAttendant,
        .printCardholder = src.printCardholder,
        .displayAttendant = src.displayAttendant,
        .displayCardholder = src.displayCardholder,
        .codeTable10 = src.codeTable10,
        .codeTable9 = src.codeTable9,
        .codeTable8 = src.codeTable8,
        .codeTable7 = src.codeTable7,
        .codeTable6 = src.codeTable6,
        .codeTable5 = src.codeTable5,
        .codeTable4 = src.codeTable4,
        .codeTable3 = src.codeTable3,
        .codeTable2 = src.codeTable2,
        .codeTable1 = src.codeTable1,
    };
}

static union AdditionalTerminalCapabilities conv_AdditionalTerminalCapabilities(const ctl_AdditionalTerminalCapabilities src) {
    return (union AdditionalTerminalCapabilities){
        .transactionType = conv_TransactionTypeCapability(src.transactionType),
        .terminalDataInput = conv_TransactionDataInputCapability(src.terminalDataInput),
        .terminalDataOutput = conv_TransactionDataOutputCapability(src.terminalDataOutput),
    };
}

static union EeaProcessSettings conv_EeaProcessSettings(const ctl_EeaProcessSettings s) {
    return (union EeaProcessSettings){
        .upfrontButtonOnScreenSupported = s.upfrontButtonOnScreenSupported,
        .offerOverride = s.offerOverride,
        .doNotOfferOverrideWhenOnlyOneEntry = s.doNotOfferOverrideWhenOnlyOneEntry,
    };
}

static void set_PermanentTerminalSpecificData(struct PermanentTerminalSpecificData* const dst, const ctl_PermanentTerminalSpecificData* const src) {
    if (src->ifdSerialNumber) {
        dst->ifdSerialNumber = malloc(sizeof(struct string8));
        strncpy(dst->ifdSerialNumber->s, src->ifdSerialNumber, sizeof(dst->ifdSerialNumber->s));
    }
    if (src->commandKeyBypassPinLabel) {
        dst->commandKeyBypassPinLabel = malloc(sizeof(struct string8));
        strncpy(dst->commandKeyBypassPinLabel->s, src->commandKeyBypassPinLabel, sizeof(dst->commandKeyBypassPinLabel->s));
    }
    strncpy(dst->commandKeyClearLabel.s, src->commandKeyClearLabel, sizeof(dst->commandKeyClearLabel.s));
    strncpy(dst->commandKeyEnterLabel.s, src->commandKeyEnterLabel, sizeof(dst->commandKeyEnterLabel.s));
    strncpy(dst->commandKeyScrollLabel.s, src->commandKeyScrollLabel, sizeof(dst->commandKeyScrollLabel.s));
}

static void set_TerminalSpecificData(struct TerminalSpecificData* const dst, const ctl_TerminalSpecificData* const src) {
    dst->additionalTerminalCapabilities = conv_AdditionalTerminalCapabilities(src->additionalTerminalCapabilities);
    dst->eeaProcessSettings = malloc(sizeof(src->eeaProcessSettings));
    *dst->eeaProcessSettings = conv_EeaProcessSettings(src->eeaProcessSettings);
}

static void print_AdditionalTerminalCapabilities(const union AdditionalTerminalCapabilities atc) {
    char buf[sizeof(atc.raw) * 2 + 1];
    printf("ATC: [%s]", hexstring(sizeof(atc.raw), atc.raw, buf));
}

static void print_EeaProcessSettings(const union EeaProcessSettings s) {
    char buf[sizeof(s.raw) * 2 + 1];
    printf("EEA PS: [%s]", hexstring(sizeof(s.raw), s.raw, buf));
}

static void print_TerminalSpecificData(struct TerminalSpecificData* const d) {
    print_AdditionalTerminalCapabilities(d->additionalTerminalCapabilities);
    if (d->eeaProcessSettings)
        printf(", ");
        print_EeaProcessSettings(*d->eeaProcessSettings);
}

static void print_PermanentTerminalSpecificData(const struct PermanentTerminalSpecificData* const d) {
    printf("[%s] [%s] [%s] [%s] [%s]",
            (d->ifdSerialNumber ?: &(struct string8){})->s,
            (d->commandKeyBypassPinLabel ?: &(struct string6){})->s,
            d->commandKeyClearLabel.s,
            d->commandKeyEnterLabel.s,
            d->commandKeyScrollLabel.s);
}

static void free_PermanentTerminalSpecificData(struct PermanentTerminalSpecificData* const d) {
    free(d->ifdSerialNumber);
    free(d->commandKeyBypassPinLabel);
    memset(d, 0, sizeof(*d));
}

static void free_TerminalSpecificData(struct TerminalSpecificData* const d) {
    free(d->eeaProcessSettings);
    memset(d, 0, sizeof(*d));
}

void run_program(void) {
    set_PermanentTerminalSpecificData(&e0, &ctl_e0);
    printf("Read E0: ");
    print_PermanentTerminalSpecificData(&e0);
    putchar('\n');

    set_TerminalSpecificData(&e1, &ctl_e1);
    printf("Read E1: ");
    print_TerminalSpecificData(&e1);
    putchar('\n');

    const enum ProcedureResult pRes = Main();
    printf("NEXO Main exited with %d\n", pRes);

    free_PermanentTerminalSpecificData(&e0);
    free_TerminalSpecificData(&e1);
}
