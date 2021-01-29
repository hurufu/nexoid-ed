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
