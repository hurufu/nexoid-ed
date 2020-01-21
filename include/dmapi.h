#pragma once

#include <stddef.h>

/* Dynamic memory interface.
 *
 * This interface isn't defined in nexo, because of it's purely technical
 * nature.
 *
 * The goal is to use dynamic memory only when it's unavoidable and in the
 * future to completely drop it as a required dependency and provide a version
 * of libnexoid for systems without dynamic memory support.
 *
 * WARNING: Current interface explicitly supports only single memory pool for
 * the whole libnexoid lifetime, if this simple approach will prove insufficient
 * this API should be redesigned.
 */

/* Allocate a shallow copy of an input argument.
 *
 * Used ubiquitously in libnexoid, and it's an expected way for allocating
 * objects in the Trusted Layer.
 *
 * WARNING: arrays aren't supported, but pointers to an array are.
 */
#define acpval(Src) ({\
    typeof(Src)* __dst = dmapi_malloc(sizeof(Src));\
    *__dst = (Src);\
    __dst;\
})

/* Allocate a shallow copy of an object pointed by an input argument.
 *
 * Similar to `acpval`.
 */
#define acpptr(SrcPtr) ({\
    typeof(SrcPtr) __src = (SrcPtr), __dst = __src ? acpval(*__src) : (void*)0;\
    __dst;\
})

/* Allowed return codes for DMAPI
 */
enum DmapiResult {
    DMAPI_OK = 10
  , DMAPI_NOK
};

/* Perform any inital setup for a underlying memory pool.
 *
 * This functions will be called only once before `Proprietary_Startup_Sequence()`.
 */
enum DmapiResult dmapi_init(void);

/* Allocate an object of a given size in current memory pool.
 *
 * Used only and exclusively as an implementation of `acpval` and `acpptr`
 * macros. It's used eg. during copying of Combination List or allocating
 * optional values in global data elements.
 */
__attribute__(( malloc ))
void* dmapi_malloc(size_t s);

/* Release all objects in current memory pool.
 *
 * TODO: Define points during nexo execution when dmapi_dtor will be called.
 * Possible candidates are:
 *
 *   * after each transaction
 *   * after Diagnostics_Maintenance_Recovery
 *   * before dmapi_init
 *
 * WARNING: In the current implementation this function is never called.
 */
void dmapi_dtor(void);

/* Used for manual free'ing of elements inside current memory pool.
 *
 * Most oftenly may be defined as `free()`
 *
 * libnexoid will never call this function. It is relying only on
 * dmapi_dtor() functionality.
 */
void dmapi_free(void* p);
