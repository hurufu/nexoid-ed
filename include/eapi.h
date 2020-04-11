#pragma once

#include "types.h"

/* EAPI - EMV Chip API
 *
 * TODO: Consider splitting this header into L1 and L2 interfaces
 */

/* Allowed return codes for EAPI
 */
enum EapiResult {
    EAPI_OK = 20
  , EAPI_NOK
};

/* EMV L1
 */

/* Perform RESET and ATR, or any other equivalent action after which it is
 * possible to perform Application Selection
 */
enum EapiResult eapi_Activate_Contacts_And_Reset_Chip(void);

/* Shall perform a Warm Chip reset as descibed in EMV Book 1 section 6.1.3.2
 */
enum EapiResult eapi_Reset_Chip(void);

enum EapiResult eapi_Select_Pse(void);

enum EapiResult eapi_Select_Application(const struct Aid*);

enum EapiResult eapi_Select_Next_Application(const struct Aid*);

enum EapiResult eapi_Generate_Ac(); // FIXME: Signature isn't yet defined

enum EapiResult eapi_Read_Record(uint8_t p1, uint8_t p2);

enum EapiResult eapi_Verify_Pin_Block(void);

/* EMV L2
 */

/* Perform FINAL SELECT using AID from kd.aidTerminal or other data element
 * that can be used for this purpose, like index in the Candidate List with
 * possibly any additional data element (possibly proprietary) if needed.
 *
 * It's expected to set cd.responseData with raw response data from the last
 * APDU or if it's not available by underlying kernel then cd.fci shall be
 * populated accordingly and cd.responseDataParsed flags shall be set to true.
 * It's expected to set cd.sw1Sw2 to values recevied from the card.
 *
 * Expected values are specified by EMV 4.3 Book 1 table 45.
 *
 * It shall return PR_OK on success, PR_NOK otherwise, any other value will
 * trigger interface violation error.
 */
enum EapiResult eapi_Final_Application_Selection(void);

/* Perform GET PROCESSING OPTIONS using all tags that were specified in PDOL
 * nexo also additionally requires kd.commandTemplate to be used as it is
 * set in libnexoid
 *
 * On success `cd.responseMessageTemplate` is expected to be populated
 *
 * TODO: Replace with pklr_Application_Initialisation
 */
enum EapiResult eapi_Get_Processing_Options(void);

/** Perform EXTERNAL AUTHENTICATE using `ord.issuerAuthenticationData`
 *  @warning Signature if this function isn't yet established, consider passing
 *      issuerAuthenticationData as an argument
 */
enum EapiResult eapi_External_Authenticate(void);
