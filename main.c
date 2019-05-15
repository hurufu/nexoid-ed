#include "CardValidityCheck.h"
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const enum ProcedureResult pRes = Main();
    printf("Main procedure of NEXO Fast application returned %d [%s]\n",
            pRes, ProcedureResult_tostring(pRes));

    return EXIT_SUCCESS;
}
