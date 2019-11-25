#pragma once

#include "common.h"

// Proprietary
enum ProcedureResult Proprietary_Startup_Sequence(void);
enum ProcedureResult Diagnostics_Maintenance_Recovery(void);
void Force_Reboot(void);
void Force_Termination(void);
void Force_Shutdown(void);
