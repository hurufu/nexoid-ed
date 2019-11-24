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

enum ProcedureResult Get_Processing_Options(); // FIXME: Signature isn't yet defined

/* EMV L2 */

/* Perform FINAL SELECT using AID from kd.aidTerminal or other data element
 * that can be used for this purpose, like index in the Candidate List with
 * possibly any additional data element (possibly proprietary) if needed.
 */
enum ProcedureResult eapi_Final_Application_Selection(void);
