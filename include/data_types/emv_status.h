#pragma once

#include "utils.h"

#include <stdint.h>

// TODO: Clean up naming, make this header a complete documentation of EMV status codes
//
// Prefixes:
//
//   I_* - informational
//   W_* - warning
//   E_* - error
//   S_* - security
//   X_* - any

union EmvStatus {
    uint8_t raw[2];
    struct {
        enum PACKED {
            X_APPLICATION_RELATED_STATUS = 0x9
          , X_OTHER_STATUS = 0x6
        } _status: 4;
    };
    struct {
        enum PACKED {
            E_CLASS_NOT_SUPPORTED = 0x60
          , I_RESPONSE_BYTES_STILL_AVAILABLE = 0x61
          , W_STATE_OF_NON_VOLATILE_MEMORY_UNCHANGED = 0x62
          , W_STATE_OF_NON_VOLATILE_MEMORY_CHANGED = 0x63
          , E_STATE_OF_NON_VOLATILE_MEMORY_UNCHANGED = 0x64
          , E_STATE_OF_NON_VOLATILE_MEMORY_CHANGED = 0x65
          , S_SECURITY = 0x66
          , E_PARSE_ERROR = 0x67
          , E_FUNCTIONS_IN_CLA_NOT_SUPPORTED = 0x68
          , E_COMMAND_NOT_ALLOWED = 0x69
          , E_WRONG_PARAMETER = 0x6A
          , E_WRONG_PARAMETER_CONTINUED = 0x6B
          , E_WRONG_LENGTH_LE = 0x6C
          , E_INSTRUCTION_CODE_ERROR = 0x6D
          , E_NOT_SUPPORTED = 0x6E
          , E_INTERNAL_EXCEPTION = 0x6F
          , X_INFORMATIONAL = 0x90
        } status;
        uint8_t qualifier;
    };
    enum PACKED {
        W_NVRM_NOT_CHANGED_NO_INFORMATION_GIVEN = MULTICHAR(0x62, 0x00)
      , W_SELECTED_FILE_INVALIDATED = MULTICHAR(0x62, 0x83)
      , W_PART_OF_RETURNED_DATA_MAY_BE_CORRUPTED = MULTICHAR(0x62, 0x81)
      , E_FUNCTION_NOT_SUPPORTED = MULTICHAR(0x6A, 0x81)
      , I_COMMAND_OK = MULTICHAR(0x90, 0x00)
    } e;
};
