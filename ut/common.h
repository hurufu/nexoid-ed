#pragma once

#include "tag_retrival.h"
#include "pklr.h"
#include "gtd.h"

#define lastof(Array) ((Array) + sizeof(Array) - 1)

#define ck_assert_op(Op, A, B, AString, BString)\
    ck_assert_msg((A) Op (B), "Assertion '"#A" "#Op" "#B"' failed. "#A" == %s and "#B" == %s", AString, (BString))

#define ck_assert_dol_result(Op, A, B)\
    ck_assert_op(Op, A, B, dol_result_tostring(A), dol_result_tostring(B))

#define ck_assert_dol_result_eq(A, B)\
    ck_assert_dol_result(==, A, B)

#define ck_assert_dol_result_neq(A, B)\
    ck_assert_dol_result(!=, A, B)

#define ck_assert_tl(Tl, Result, Length, BytesLeft, NextCursor, ...)\
    ck_assert_tl_impl((Tl), (Result), (&(uint8_t[sizeof(tlv_tag_t)]){ __VA_ARGS__ }), (Length), (BytesLeft), (NextCursor))
void ck_assert_tl_impl(
    struct Extracted_Tl tl,
    enum ProcedureResult expected_result,
    const uint8_t (*tag)[sizeof(tlv_tag_t)],
    size_t length,
    size_t bytes_left,
    const uint8_t* next_cursor
);

static const char* dol_result_tostring(enum ProcedureResult r);
