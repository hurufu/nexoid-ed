#pragma once

#include "Common.h"

enum HapResult {
    HAP_OK
  , HAP_NOK
  , HAP_UNABLE_TO_GO_ONLINE
};

enum HapResult HAPI_searchTransaction(void);
