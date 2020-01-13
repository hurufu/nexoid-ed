#pragma once

#include "types.h"

/* Proprietary procedure interface
 */

/* Allowed return codes for PAPI
 */
enum PapiResult {
    PAPI_OK = 40
  , PAPI_NOK
  , PAPI_STARTUP_SEQUENCE
  , PAPI_REBOOT
  , PAPI_TERMINATE
};

/* Perform any actions required by the platform prior to nexo app startup
 *
 * Possible actions that may be performed by this procedure:
 *
 *   * Populating of all configuration elements like e0, e1, and all others.
 *   * Setting up printer
 *
 *  nexo-FAST v.3.2, figure 15
 */
enum ProcedureResult Proprietary_Startup_Sequence(void);

/* Perform any actions required to handle error conditions
 *
 * Possible actions:
 *
 *   * Dump the core and send it for diagnosis
 *   * Analyse global data structure and determine if recovery is possible
 *   * Prepare system to a shutdown or reboot
 *   * Trigger reinitialisation of nexo application
 *
 * TODO: Add some guarantees about preserving state of all global elements
 * variables just before calling this function
 *
 *  This function isn't defined by nexo, but it's briefly mentioned in nexo.
 *
 *  nexo-FAST v.3.2, figure 15
 */
enum ProcedureResult Diagnostics_Maintenance_Recovery(void);

/* Prepare system to reboot.
 *
 * This function may be safely ignored. Will be called just before exiting from
 * `Main()`
 *
 * TODO: Specify if it's allowed to reboot the device inside this function
 */
void Force_Reboot(void);

/* Prepare system for premature nexo shutdown.
 *
 * This function may be safely ignored. It's allways invoked in response to
 * TERMINATE event during main waiting loop. It will be called just before exiting
 * from `Main()`
 */
void Force_Termination(void);
