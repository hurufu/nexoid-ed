#include "PaymentCompletion.h"
#include "Common.h"
#include <stdio.h>

int main() {
    PaymentCompletion(
        (union TerminalSettings){ .retrievePreauth = 1 }
      , (union ServiceStartEvents){ .referenceEntry = 1 }
    );

    return 0;
}
