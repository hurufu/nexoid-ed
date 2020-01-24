#pragma once

#include "types.h"

/** Terminal Managment System API
 */

enum TmapiResult {
    TMAPI_OK = 70
  , TMAPI_NOK
};

/* Send Status Report and handle it's response.
 *
 * In response Managment Plan Replacement, Acceptor Configuration Update or any
 * other relevant action may be performed.
 *
 * WARNING: This function isn't used in libnexoid and will be considered for
 * removal.
 *
 * It's expected that ttd.callTms will be set apropriately inside this function
 *
 * nexo-IS v.4.0, section 4.2
 */
enum TmapiResult tmapi_Perform_Terminal_Managment_Session(void);
