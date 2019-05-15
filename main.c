#include "NexoFast.h"
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>

int run_nexo_fast_application(void) {
    const enum ProcedureResult pRes = Main();
    printf("Main procedure of NEXO Fast application returned %d [%s]\n",
            pRes, ProcedureResult_tostring(pRes));
    switch (pRes) {
        case PR_OK:
            puts("Ok.");
            return 0;
        case PR_REBOOT:
            puts("System reboot requested.");
            return 2;
        case PR_NOK:
            puts("Fail.");
            return 1;
        default:
            puts("Unexpected error.");
            return 1;
    }
}

int main() {
    puts("NEXO Fast application");
    return run_nexo_fast_application();
}
