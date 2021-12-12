#pragma once

#include "dmapi.h"
#include "types.h"

// TODO: Consider moving Extract_Tag_And_Length_Pair() and struct Extracted_Tl away from this header
struct Extracted_Tl {
    union TagExpanded tag;
    size_t length;
    enum ProcedureResult result;
    size_t size;
    const uint8_t* cursor;
};

/** Extract Tag and Length from DOL string
 *
 *  @note nexo FAST v.3.2, note 220-20
 *
 *  @returns PR_OK on success, PR_DONE on empty string, PR_NOK on error and
 *  PR_SKIP if resulting tag doesn't fit into a machine word, but is otherwise
 *  correct. Members `size` and `cursor` are always set to some meaningfull
 *  values even in case of an error.
 */
struct Extracted_Tl Extract_Tag_And_Length_Pair(size_t size, const uint8_t cursor[]);

enum ProcedureResult Append_Dol_Entry(size_t Length, uint8_t Dol[Length], union TagExpanded tag, size_t length);
