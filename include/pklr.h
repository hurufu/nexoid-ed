#pragma once

#include "types.h"

/** PKLR - Proprietary Kernel Link Redirect
 *
 *  This interface is used for proprietary algorithms for kernel API selection
 *
 *  WARNING: Interface specified in this header shall be used only to redirect
 *  actual control back to nexo or to some proprietary API.
 *
 *  Nexoid is expecting CTD to contain all relevant data after function return.
 *  It will perform only sanity checks and will abort transaction if they fail
 *  or terminate an application if severe violation was found. It's
 *  responsibility of PKLR module as a member of Trusted Layer to perform all
 *  necessary checks and guarantee CTD consistency after crossing code boundary
 *  between nexoid and (if any) external module.
 *
 *  TODO: Add License and Copyright
 */

/* Allowed return codes for PKLR
 */
enum PklrResult {
    PKLR_OK = 50
  , PKLR_DONE
  , PKLR_NOK
  , PKLR_BAIL
  , PKLR_SKIP
  , PKLR_SUCCESSFUL
  , PKLR_UNSUCCESSFUL
};

struct PklrConfiguration {
    bool buildCandidateList;
};

/* Used to enable or disable PKLR for different procedures
 *
 * Should be defined in the Trusted Layer
 */
extern struct PklrConfiguration pklr;

/** Redirect to API that will perform Building of Candidate List as specified
 *  in EMV Book 1 section 12, after which Final Application will be performed
 *  be nexoid.
 *
 *  @return PKLR_OK on success or PKLR_NOK on any error
 *
 *  @warning Any other return value is an external interface contract violation
 *  and will cause immediate shift of nexo application into maintenance mode
 *  or its termination
 *
 *  If it is desirable to use nexoid L2 kernel, implementation may look as
 *  simple as this:
 *
 *      enum PklrResult pklr_Build_Candidate_List(void) {
 *          return Build_Candidate_List();
 *      }
 *
 *  Or in case of a proprietary EMV L2 API, the implementation may consist of
 *  the following steps:
 *
 *      enum PklrResult pklr_Build_Candidate_List(void) {
 *          // 0. Populate kernel data from CTD if needed
 *          // 1. Call Proprietary Build Candidate List or analogous function
 *          // 2. Convert data returned by kernel to format applicable to nexoid
 *          // 3. Populate CTD with that data
 *          return PKLR_OK;
 *      }
 */
enum PklrResult pklr_Build_Candidate_List(void);

/**  Redirect to API that will complete EMV transaction
 *
 *  Redirect to API that will perform:
 *    * issuer authentication
 *    * 2nd GENERATE AC command
 *    * script processing
 */
enum PklrResult pklr_Emv_Completion(void);

/** Experimental API to hide all Kernel 1E related processing
 *  @warning Probably it's not compatible with nexo, but it's useful as a dummy
 */
enum PklrResult pklr_Kernel_E_Processing(void);

/** Redirect to API that will perform all necessary READ RECORD commands
 *
 *  @warning Expected behaviour isn't yet defined
 */
enum PklrResult pklr_Process_Read_Record(void);

/** Redirect to API that will perform SDA or DDA
 *
 *  @return PKLR_SUCCESSFUL if SDA or DDA succeeded, PKLR_UNSUCCESSFUL if SDA
 *  or DDA didn't succeed, PKLR_SKIP if CDA is selected, PKLR_NOK if an error
 *  occured.
 *
 *  In case of error it's expected that ttd.terminalErrorIndicator is enabled
 *  and `ttd.terminalErrorReason` is set to an appropriate value.
 *
 *  EMV v.4.3 Book 3, section 10.3
 *  nexo-FAST v.3.2, figure 164
 */
enum PklrResult pklr_Offline_Data_Authentication(void);

/** Redirect to an API that will perform 1st GENERATE AC command and perform
 *  Card Action Analysis
 *
 *  This function will be called usually after Terminal Action Analysis step
 */
enum PklrResult pklr_First_Generate_Ac_Processing(void);

/** Redirect to an API that will perform issuer script processing before 2nd
 *  GENERATE AC.
 *
 *  @return PKLR_OK on success regardless of script processing result, PKLR_NOK
 *  on unrecoverable error.
 *
 *  If PKLR_NOK is returned, then `ttd.nokReason` is expected to be set to
 *
 *  N_CARD_MISSING:
 *   ~  If card was removed during chip processing
 *  N_CHIP_ERROR:
 *   ~  If error in communication with the chip occured
 *
 *  If PKLR_OK is returned and Template 71 or 72 were available in `ord`, then
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
enum PklrResult pklr_First_Issuer_Script_Processing(void);

/** Redirect to an API that will perform issuer script processing after 2nd
 *  GENERATE AC.
 *
 *  Similar to pklr_Issuer_Script_Processing_1
 */
enum PklrResult pklr_Second_Issuer_Script_Processing(void);

/** Redirect to an API that will perform 2st GENERATE AC command
 */
enum PklrResult pklr_Second_Generate_Ac_Processing(void);
