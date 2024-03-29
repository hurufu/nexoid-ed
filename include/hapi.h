#pragma once

#include "types.h"

/* HAP Interface as defined by nexo-FAST v.3.2, section 12.1.3
 */

/* Allowed return codes for HAPI
 */
enum HapiResult {
    HAPI_OK = 30
  , HAPI_NOK
  , HAPI_NOT_FOUND
  , HAPI_UNABLE_TO_GO_ONLINE
};

/* Send a Currency Conversion request to the DCC provider
 */
enum HapiResult hapi_Online_Request_to_Dcc_Provider(void);

/* Send Authorisation Request to the acquirer.
 *
 * Data should be taken from `ttd` or configuration internal to HAP (which was
 * received eg. by AcceptorConfigurationUpdate message) and `ord` should be
 * updated upon exit to relevant values.
 *
 * @returns HAPI_OK on success, HAPI_NOK if mandatory data is missing in `ttd`,
 * and HAPI_UNABLE_TO_GO_ONLINE if host is unavaliable
 *
 * Nexo specifies that only missing mandatory data shall cause HAPI_NOK status,
 * and for everything else they are expecting this function to return
 * HAPI_UNABLE_TO_GO_ONLINE, even in case when terminal received rejection from
 * the host, which is in my opinion a subompitmal solution, because eg.
 * retransmission will hardly ever help in such case.
 *
 * nexo-FAST v.3.2, section 12.1.3.2
 * nexo-IS v.4.0, section 3.2
 * ISO 20022 MDR, section 2 and 3
 * ISO 20022 MUG, section 4.2
 */
enum HapiResult hapi_Online_Approval_Request(void);

/* Perform status check
 *
 * If HAP will determine that contacting TMS is needed then ttd.callTms is
 * expected to be in this function. It's not defined in nexo, but may be
 * implicitly deduced, because during Financial Startup contact to TMS should
 * be somehow triggered after hapi_Status.
 *
 * nexo-FAST v.3.2, section 12.1.3.1
 * nexo-IS v.4.0, section 3.1
 */
enum HapiResult hapi_Status(void);

/* Perform search of previous tansactions in the log and prepare for consecutive data retrieval
 *
 * It's expected that global `sl` pointer will hold actual search results after
 * this functions exits with HAPI_OK. If that pointer is NULL, then result is
 * treated as if this function returned HAPI_NOK. Any other return value is an ICV.
 *
 * nexo-FAST v.3.2, section 12.1.3.5
 * nexo-IS v.4.0, section 3.5
 */
enum HapiResult hapi_Search_Transactions(const struct SearchLogCriteria* slc);

enum HapiResult hapi_SearchReservationsByRefData(void);

enum HapiResult hapi_SearchReservationsByPan(void);

enum HapiResult hapi_Log_Entry_Data_Retrieval(void);

enum HapiResult hapi_Initialiase_Basic_Data(void);

enum HapiResult hapi_Transaction_Finalisation(void);

enum HapiResult hapi_Transaction_Data_Storage(void);
