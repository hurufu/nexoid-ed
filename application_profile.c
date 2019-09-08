#include "include/tag_retrival.h"
#include "include/application_profile.h"

struct tlv*
ApplicationProfile_gettag(
        const struct ApplicationProfile* const p
      , const enum ApplicationProfileTag t
) {
    switch (p) {
        case TAG_EMV_ACQUIRER_IDENTIFIER:
            return MAKE_TAG(p, &p->acquirerIdentifier);
        case TAG_EMV_CVM_CAPABILITY_CVM_REQUIRED:
            return MAKE_TAG(p, &p->cvmCapabilityCvmRequired);
        case TAG_EMV_CVM_CAPABILITY_NO_CVM_REQUIRED:
            return MAKE_TAG(p, &p->cvmCapabilityNoCvmRequired);
        case TAG_EMV_DDOL:
            return MAKE_TAG(p, &p->ddol);
        case TAG_EMV_HOLD_TIME_VALUE:
            return MAKE_TAG(p, &p->holdTimeValue);
    }
    return NULL;
}
