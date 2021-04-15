#include "ctl-io.h"
#include "gtd.h"
#include "NexoFast.h"

#include <stdio.h>
#include <stdlib.h>

void set_PermanentTerminalSpecificData(
        struct PermanentTerminalSpecificData* const dst,
        const ctl_PermanentTerminalSpecificData* const src) {
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

void free_PermanentTerminalSpecificData(struct PermanentTerminalSpecificData* const d) {
    free(d->ifdSerialNumber);
    free(d->commandKeyBypassPinLabel);
    memset(d, 0, sizeof(*d));
}

void print_PermanentTerminalSpecificData(const struct PermanentTerminalSpecificData* const d) {
    printf("[%s] [%s] [%s] [%s] [%s]",
            (d->ifdSerialNumber ?: &(struct string8){})->s,
            (d->commandKeyBypassPinLabel ?: &(struct string6){})->s,
            d->commandKeyClearLabel.s,
            d->commandKeyEnterLabel.s,
            d->commandKeyScrollLabel.s);
}

void run_program(void) {
    set_PermanentTerminalSpecificData(&e0, &ctl_e0);
    printf("Read E0: ");
    print_PermanentTerminalSpecificData(&e0);
    putchar('\n');
    const enum ProcedureResult pRes = Main();
    printf("NEXO Main exited with %d\n", pRes);
    free_PermanentTerminalSpecificData(&e0);
}
