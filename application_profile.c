#include "tag_retrival.h"
#include "e6_application_profile.h"
#include "global_data_elements.h"

#define T(T) T

static struct TagTypePointer ApplicationProfile_get_ttv(const struct ApplicationProfile* const p, const union TagExpanded t) {
    struct TagTypePointer ret;
    switch (t.i) {
        case T(0xDF1B): ret = (struct TagTypePointer){ .type = TAG_BCD1, .value.bcd = &p->acquirerNumber }; break;
        case T(0xDF19): ret = (struct TagTypePointer){ .type = TAG_BCD1, .value.bcd = &p->profileNumber }; break;
        case T(0xDF26): ret = (struct TagTypePointer){ .type = TAG_TVR_PTR, .value.tvr = p->additionalRestrictionsForForcedAcceptance }; break;
        case T(0x9F40): ret = (struct TagTypePointer){ .type = TAG_ATC_PTR, .value.atc = p->additionalTerminalCapabilities }; break;
        case T(0x9F33): ret = (struct TagTypePointer){ .type = TAG_TC_PTR, .value.tc = p->terminalCapabilities }; break;
        case T(0x9F1A): ret = (struct TagTypePointer){ .type = TAG_BCD2, .value.bcd2 = &p->terminalCountryCode }; break;
        case T(0xDF41): ret = (struct TagTypePointer){ .type = TAG_ANS_16, .value.ans_16 = &p->applicationLabelDefault }; break;
        case T(0xDF27): ret = (struct TagTypePointer){ .type = TAG_APS, .value.aps = &p->applicationProfileSettings }; break;
        case T(0xDF28): ret = (struct TagTypePointer){ .type = TAG_APSC_PTR, .value.apsc = p->applicationProfileSettingsForCancellation }; break;
        case T(0xDF29): ret = (struct TagTypePointer){ .type = TAG_AMOUNT_PTR, .value.amount = p->cashAdvanceMaximumAmount }; break;
        case T(0xDF2A): ret = (struct TagTypePointer){ .type = TAG_AMOUNT_PTR, .value.amount = p->cashbackMaximumAmount }; break;
        case T(0xDF8118): ret = (struct TagTypePointer){ .type = TAG_CVM_CAPABILITY_PTR, .value.cvmCapability = p->cvmCapabilityCvmRequired }; break;
        case T(0xDF8119): ret = (struct TagTypePointer){ .type = TAG_CVM_CAPABILITY_PTR, .value.cvmCapability = p->cvmCapabilityNoCvmRequired }; break;
        case T(0xDF42): ret = (struct TagTypePointer){ .type = TAG_MSR_CVM_CAPABILITY_PTR, .value.magstripeCvmCapability = p->magStripeCvmCapabilityCvmRequired }; break;
        //case T(): ret = (struct TagTypePointer){ .type = TAG_MSR_CVM_CAPABILITY_PTR, .value.magstripeCvmCapability = p->magStripeCvmCapabilityNoCvmRequired }; break;
        case T(0xDF58): ret = (struct TagTypePointer){ .type = TAG_AMOUNT_PTR, .value.amount = p->cvcDefaultAmount }; break;
        case T(0xDF3C): ret = (struct TagTypePointer){ .type = TAG_AMOUNT, .value.amount = &p->refundProtectionAmount }; break;
        case T(0xDF811B): ret = (struct TagTypePointer){ .type = TAG_KERNEL2_CONFIGURATION_PTR, .value.kernel2Configuration = p->kernel2Configuration}; break;
        default: ret = (struct TagTypePointer){ .type = TAG_UNKNOWN }; break;
    }
    return ret;
}

uint8_t* ApplicationProfile_getv(const struct ApplicationProfile* const ap, const union TagExpanded tag) {
    const struct TagTypePointer t = ApplicationProfile_get_ttv(ap, tag);
    switch (t.type) {
        case TAG_BOOLEAN: return getv_bool(t.value.b);
        case TAG_BOOLEAN_PTR: return t.value.b ? getv_bool(t.value.b) : NULL;
        case TAG_C19: return getv_c19(t.value.c19);
        case TAG_BID: return getv_bid(t.value.bid);
        case TAG_BCD1: return getv_bcd(t.value.bcd);
        case TAG_BCD2: return getv_bcd2(t.value.bcd2);
        case TAG_ANS_16: return getv_ans_16(t.value.ans_16);
        case TAG_TVR: return getv_tvr(t.value.tvr);
        case TAG_TVR_PTR: return t.value.tvr ? getv_tvr(t.value.tvr) : NULL;
        case TAG_ATC: return getv_atc(t.value.atc);
        case TAG_ATC_PTR: return t.value.atc ? getv_atc(t.value.atc) : NULL;
        case TAG_TC: return getv_tc(t.value.tc);
        case TAG_TC_PTR: return t.value.tc ? getv_tc(t.value.tc) : NULL;
        case TAG_APS: return getv_aps(t.value.aps);
        case TAG_APSC_PTR: return t.value.apsc ? getv_apsc(t.value.apsc) : NULL;
        case TAG_AMOUNT: return getv_amount(t.value.amount);
        case TAG_AMOUNT_PTR: return t.value.amount ? getv_amount(t.value.amount) : NULL;
        case TAG_CVM_CAPABILITY_PTR: return t.value.cvmCapability ? getv_cvmCapability(t.value.cvmCapability) : NULL;
        case TAG_MSR_CVM_CAPABILITY_PTR: return t.value.magstripeCvmCapability ? getv_msrCvmCapability(t.value.magstripeCvmCapability) : NULL;
        case TAG_KERNEL2_CONFIGURATION_PTR: return t.value.kernel2Configuration ? getv_kernel2Configuration(t.value.kernel2Configuration) : NULL;
        case TAG_UNKNOWN:
        case TAG_FORBIDDEN:
        default:
            return NULL;
    }
}
