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

/** Experimental API to hide all Kernel 1E related processing
 *  @warning Probably it's not compatible with nexo, but it's useful as a dummy
 */
enum ProcedureResult pklr_Kernel_E_Processing(void);

/** Redirect to API that will perform all necessary READ RECORD commands
 *
 *  @warning Expected behaviour isn't yet defined
 */
enum ProcedureResult pklr_Process_Read_Record(void);

/** Redirect to an API that will perform 1st GENERATE AC command and perform
 *  Card Action Analysis
 *
 *  This function will be called usually after Terminal Action Analysis step
 */
enum ProcedureResult pklr_First_Generate_Ac_Processing(void);

/** Redirect to an API that will perform issuer script processing before 2nd
 *  GENERATE AC.
 *
 *  @return PR_OK on success regardless of script processing result, PR_NOK on
 *          unrecoverable error
 *
 *  If `PR_NOK` is returned, then `ttd.nokReason` is expected to be set to
 *
 *  N_CARD_MISSING:
 *   ~  If card was removed during chip processing
 *  N_CHIP_ERROR:
 *   ~  If error in communication with the chip occured
 *
 *  If `PR_OK` is returned and Template 71 or 72 were available in `ord`, then
 *  Issuer Script Results should be present and pass internal sanity checks.
 *
 *  @warning If any of the above conditions will not be satisfied then it's
 *  treated as an external interface contract violation.
 *
 *  It's expected that `ttd.tvr` and `kd.tsi` will be updated to reflect status
 *  of the script that have been processed according to EMV Book 3 v.4.3,
 *  section 10.10. Those values aren't subject to internal sanity checks,
 *  because there is no way for nexoid to check factual correctness of these
 *  bit fields.
 *
 *  If it's desireable to use nexoid L2 kernel, then simply redirect it's call
 *  to Issuer_Script_Processing_1
 */
enum ProcedureResult pklr_First_Issuer_Script_Processing(void);

/** Redirect to an API that will perform issuer script processing after 2nd
 *  GENERATE AC.
 *
 *  Similar to pklr_Issuer_Script_Processing_1
 */
enum ProcedureResult pklr_Second_Issuer_Script_Processing(void);

/** Redirect to an API that will perform 2st GENERATE AC command
 */
enum ProcedureResult pklr_Second_Generate_Ac_Processing(void);
