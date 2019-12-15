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
#include "e2_application_profile_selection_table.h"
#include "e4_service_settings_table.h"
#include "e7_terminal_list_of_bid.h"
#include "e8_application_selection_table_non_chip.h"
#include "ec_combination_list_and_parameters.h"
#include "tag_retrival.h"

#include <string.h>

static struct ApplicationKernelAndAppProfileSelection s_akps;
static struct TechnologySelection s_ts;
static struct TransactionCompletion s_tc;
