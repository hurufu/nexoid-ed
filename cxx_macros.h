#pragma once

#ifdef __cplusplus
#   define EXTERN_C_PREAMBLE extern "C" {
#   define EXTERN_C_EPILOGUE }
#   define NOEXCEPT noexcept
#else
#   define EXTERN_C_PREAMBLE
#   define EXTERN_C_EPILOGUE
#   define NOEXCEPT
#endif

/** Macro used to specify size of array parameter
 *
 * @see https://wiki.sei.cmu.edu/confluence/display/c/API05-C.+Use+conformant+array+parameters#API05C.Useconformantarrayparameters-Exceptions
 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ > 199901L && !defined(__STDC_NO_VLA__)
#   define FEATURE_CONFORMANT_ARRAY_PARAMETERS
#endif
#ifdef FEATURE_CONFORMANT_ARRAY_PARAMETERS
#   define N(x) (x)
#else
#   define N(x)
#endif

/** Flexible array indicator
 *
 *  @see http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1039r0.html
 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ > 199901L
#   define FEATURE_FLEXIBLE_ARRAY_MEMBERS
#endif
#ifdef FEATURE_FLEXIBLE_ARRAY_MEMBERS
#   define FLEX
#else
#   define FLEX 0
#endif

#if defined(_GNU_SOURCE) && defined(FEATURE_FLEXIBLE_ARRAY_MEMBERS)
#   define FEATURE_NON_FINAL_FLEXIBLE_ARRAY_MEMBERS
#endif
#ifdef FEATURE_NON_FINAL_FLEXIBLE_ARRAY_MEMBERS
#   define NFLEX
#else
#   define NFLEX 0
#endif
