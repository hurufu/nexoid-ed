#pragma once

#define MACRO_REDIRECT4(_0, _1, _2, _3, Name, ...) Name

#define NUMBERED_MACRO(Macro, ...) MACRO_REDIRECT4(, ##__VA_ARGS__, Macro##3, Macro##2, Macro##1, Macro##0)(__VA_ARGS__)

#define MULTICHAR0()           (0 | (0 | (0 | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR1(A)          (A | (0 | (0 | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR2(A, B)       (A | (B | (0 | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR3(A, B, C)    (A | (B | (C | (0 << 8) << 8) << 8) << 8)
#define MULTICHAR4(A, B, C, D) (A | (B | (C | (D << 8) << 8) << 8) << 8)
