#pragma once

/* EAPI - EMV Chip API
 * FIXME: Consider some better name for this interface (EMV L1 ?)
 */

#include "common.h"

/* Shall perform RESET and ATR, or any other equivalent action after which it
 * is possible to perform Application Selection
 */
enum ProcedureResult Activate_Contacts_And_Reset_Chip(void);

/** Shall perform a Warm Chip reset as descibed in EMV Book 1 section 6.1.3.2
 */
enum ProcedureResult Reset_Chip(void);

enum ProcedureResult Select_Application(const struct Aid*);

enum ProcedureResult Select_Next_Application(const struct Aid*);
