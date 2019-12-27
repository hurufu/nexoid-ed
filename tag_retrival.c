#include "tag_retrival.h"
#include "global_data_elements.h"
#include <byteswap.h>
#include <limits.h>

struct Extracted_Tag {
    enum ProcedureResult result;
    size_t size;
    const uint8_t* cursor;
    union TagExpanded tag;
};

struct Extracted_Len {
    enum ProcedureResult result;
    size_t size;
    const uint8_t* cursor;
    size_t length;
};

static struct Extracted_Tag extract_tag(const size_t s, const uint8_t c[static const s]) {
    if (s == 0 || !c) {
        return (struct Extracted_Tag){ .result = PR_NOK, .size = s, .cursor = c };
    }
    struct Extracted_Tag t = {
        .cursor = c + 1,
        .size = s - 1,
        .tag.head = *c,
        .result = PR_OK
    };
    if (0x1F != t.tag.nmbr) {
        return t;
    }

    size_t i;
    for (i = 0; i < elementsof(t.tag.tail) && t.size > 0; t.size--, i++, t.cursor++) {
        t.tag.tail[i].c = *t.cursor;
        if (!t.tag.tail[i].v.next) {
            t.size--, i++, t.cursor++;
            break;
        }
    }
    if (0 == i) {
        // Input string ended
        t.result = PR_NOK;
    }
    if (t.tag.tail[i-1].v.next) {
        // Tag doesn't fit into internal type
        for (size_t j = 0; t.size > 0; t.size--, j++, t.cursor++) {
            if (!t.tag.tail[i+j].v.next) {
                t.size--, j++, t.cursor++;
                break;
            }
        }
        t.tag.i = 0;
        t.result = PR_SKIP;
    }
    return t;
}

static struct Extracted_Len extract_length(const size_t s, const uint8_t c[static const s]) {
    struct Extracted_Len ret = {
        .cursor = c + 1,
        .size = s - 1,
        .result = PR_OK
    };
    union Length l = { .raw = { *c } };
    if (!l.length.isLong) {
        ret.length = l.length.value;
        // OK - Length has only 1 byte
        return ret;
    }
    if (l.length.value > elementsof(l.longLength.a)) {
        ret.length = SIZE_MAX;
        ret.result = PR_NOK;
        ret.size -= l.length.value;
        ret.cursor += l.length.value;
        // NOK - Length is larger then supported by the platform
        return ret;
    }
    if (s < l.length.value) {
        ret = (struct Extracted_Len){
            .length = 0,
            .result = PR_NOK,
            .cursor = c + s,
            .size = 0
        };
        // NOK - length is OK, but `c` doesn't contain enough bytes to read
        return ret;
    }
    memcpy(l.longLength.a, ret.cursor, l.length.value);
    // TODO: Refactor, optimize and make cross platform byte swapping
    const uint_fast8_t most_significant_non_zero_byte =
            l.longLength.a[7] ? 0 :
            l.longLength.a[6] ? 1 :
            l.longLength.a[5] ? 2 :
            l.longLength.a[4] ? 3 :
            l.longLength.a[3] ? 4 :
            l.longLength.a[2] ? 5 :
            l.longLength.a[1] ? 6 :
            l.longLength.a[0] ? 7 : 8;
    ret.length = bswap_64(l.longLength.z) >> (most_significant_non_zero_byte * CHAR_BIT);
    ret.size -= l.length.value;
    ret.cursor += l.length.value;

    // OK - Length has multiple bytes
    return ret;
}

struct Extracted_Tl
Extract_Tag_And_Length_Pair(const size_t size, const uint8_t cursor[static const size]) {
    if (!cursor) {
        return (struct Extracted_Tl){ .result = PR_NOK };
    }
    if (size == 0) {
        return (struct Extracted_Tl){ .result = PR_DONE, .cursor = cursor };
    }
    const struct Extracted_Tag t = extract_tag(size, cursor);
    const struct Extracted_Len l = extract_length(t.size, t.cursor);
    const struct Extracted_Tl ret = {
        .result = ((PR_OK == t.result && PR_OK == l.result) ? PR_OK : PR_NOK),
        .size = l.size,
        .cursor = l.cursor,
        .tag = t.tag,
        .length = l.length
    };
    return ret;
}

enum ProcedureResult Append_Dol_Entry(const size_t Length, uint8_t Dol[const Length], const union TagExpanded tag, const size_t tagLength) {
    struct TypeLengthValue* const t = ApplicationProfile_get_tylv(&ap, tag);
    if (!t) {
        return PR_NOK;
    }
    if (tagLength < t->length) {
        if (t->length < tagLength) {
            return PR_NOK;
        }
        switch (t->type) {
            case TAG_BCD:
                memcpy(Dol, t->value + t->length - tagLength, t->length);
                break;
            case TAG_CBCD:
            case TAG_NON_NUMERIC:
                memcpy(Dol, t->value, t->length);
                break;
        }
    } else if (tagLength > t->length) {
        if (Length < tagLength) {
            return PR_NOK;
        }
        switch (t->type) {
            case TAG_BCD:
                memcpy(Dol + tagLength - t->length, t->value, t->length);
                break;
            case TAG_CBCD:
                memcpy(Dol, t->value, t->length);
                memset(Dol, 0xFF, tagLength - t->length);
                break;
            case TAG_NON_NUMERIC:
                memcpy(Dol, t->value, t->length);
                break;
        }
    } else {
        if (Length < tagLength) {
            return PR_NOK;
        }
        memcpy(Dol, t->value, t->length);
    }
    return PR_OK;
}
