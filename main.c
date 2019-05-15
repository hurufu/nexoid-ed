#include "CardValidityCheck.h"
#include "Common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    const enum ProcedureResult pRes = Main();
    printf("NEXO Fast Application exited with %s (%d)\n",
            ProcedureResult_tostring(pRes), pRes);

    return EXIT_FAILURE;
}
