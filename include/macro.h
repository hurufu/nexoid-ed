#pragma once

#define MACRO_REDIRECT4(_0, _1, _2, _3, Name, ...) Name

#define NUMBERED_MACRO(Macro, ...) MACRO_REDIRECT4(, ##__VA_ARGS__, Macro##3, Macro##2, Macro##1, Macro##0)(__VA_ARGS__)

#define MULTICHAR0()           (0 | (0 | (0 | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR1(A)          (A | (0 | (0 | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR2(A, B)       (A | (B | (0 | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR3(A, B, C)    (A | (B | (C | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR4(A, B, C, D) (A | (B | (C | (D << 8) << 8) << 8) << 8)

// TODO: Replace ONEOF macro with proper map/reduce equivalent
#define ONEOF0(X)                 (((X)))
#define ONEOF1(X, A1)             (((X) == (A1)))
#define ONEOF2(X, A1, A2)         (((X) == (A1)) || ((X) == (A2)))
#define ONEOF3(X, A1, A2, A3)     (((X) == (A1)) || ((X) == (A2)) || ((X) == (A3)))
#define ONEOF4(X, A1, A2, A3, A4) (((X) == (A1)) || ((X) == (A2)) || ((X) == (A3)) || ((X) == (A4)))

#define MIN1(A1)             ( (A1)                                  )
#define MIN2(A1, A2)         ( (A1) < (A2) ? (A1) : MIN1(A2)         )
#define MIN3(A1, A2, A3)     ( (A1) < (A2) ? (A1) : MIN2(A2, A3)     )
#define MIN4(A1, A2, A3, A4) ( (A1) < (A2) ? (A1) : MIN3(A2, A3, A4) )
