#include "common.h"
#include "hapi.h"
#include "papi.h"
#include "scapi.h"
#include "tmapi.h"
#include "eapi.h"
#include "candidate_list.h"
#include "global_data_elements.h"
#include "application_kernel_and_app_profile_selection.h"
#include "technology_selection.h"
#include "transaction_completion.h"

#include <string.h>

static struct ApplicationKernelAndAppProfileSelection s_akps;
static struct TechnologySelection s_ts;
static struct TransactionCompletion s_tc;
