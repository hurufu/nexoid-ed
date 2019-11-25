#pragma once

/* EAPI - EMV Chip API
 */

#include "common.h"

/* EMV L1 */

/* Perform RESET and ATR, or any other equivalent action after which it is
 * possible to perform Application Selection
 */
enum ProcedureResult Activate_Contacts_And_Reset_Chip(void);

/* Shall perform a Warm Chip reset as descibed in EMV Book 1 section 6.1.3.2
 */
enum ProcedureResult Reset_Chip(void);

enum ProcedureResult Select_Application(const struct Aid*);

enum ProcedureResult Select_Next_Application(const struct Aid*);

enum ProcedureResult Generate_Ac(); // FIXME: Signature isn't yet defined

/* EMV L2 */

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
enum ProcedureResult eapi_Final_Application_Selection(void);

/* Perform GET PROCESSING OPTIONS using all tags that were specified in PDOL
 * nexo also aadditionally requires kd.commandTemplate to be used as it is
 * set in libnexoid
 */
enum ProcedureResult Get_Processing_Options(void);
