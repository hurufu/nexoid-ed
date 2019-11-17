#pragma once

#include "common.h"

/** PKLR - Proprietary Kernel Link Redirect
 *
 *  This interface is used for proprietary algorithms for kernel API selection
 *
 *  @warning Interface specified in this header shall be used only to redirect
 *  actual control back to nexo or to some proprietary API.
 *
 *  Nexoid is expecting CTD to contain all relevant data after function return.
 *  It will perform only sanity checks and will abort transaction if they fail
 *  or terminate an application if severe violation was found. It's
 *  responsibility of PKLR module as a member of Trusted Layer to perform all
 *  necessary checks and guarantee CTD consistency after crossing code boundary
 *  between nexoid and (if any) external module.
 *
 *  @todo: Add License and Copyright
 *  @todo: Restrict enum for return values
 */


/** Redirect to API that will perform Building of Candidate List as specified
 *  in EMV Book 1 section 12, after which Final Application will be performed
 *  be nexoid.
 *
 *  @return PR_OK on success or PR_NOK on any error
 *
 *  @warning Any other return value is an external interface contract violation
 *  and will cause immediate shift of nexo application into maintenance mode
 *  or its termination
 *
 *  If it is desirable to use nexoid L2 kernel, implementation may look as
 *  simple as this:
 *
 *      enum ProcedureResult PKLR_Build_Candidate_List(void) {
 *          return Build_Candidate_List();
 *      }
 *
 *  Or in case of a proprietary EMV L2 API, the implementation may consist of
 *  the following steps:
 *
 *      enum ProcedureResult PKLR_Build_Candidate_List(void) {
 *          // 0. Populate kernel data from CTD if needed
 *          // 1. Call Proprietary Build Candidate List or analogous function
 *          // 2. Convert data returned by kernel to format applicable to nexoid
 *          // 3. Populate CTD with that data
 *          return PR_OK;
 *      }
 */
enum ProcedureResult PKLR_Build_Candidate_List(void);

/**  Redirect to API that will complete EMV transaction
 *
 *  Redirect to API that will perform:
 *    * issuer authentication
 *    * 2nd GENERATE AC command
 *    * script processing
 */
enum ProcedureResult pklr_Emv_Completion(void);
