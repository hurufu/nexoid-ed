#pragma once

#include "terminal_configuration_data.h"
#include "terminal_transaction_data.h"
#include "kernel_data.h"
#include "card_data.h"
#include "online_response_data.h"
#include "e6_application_profile.h"

// This header should be included only by nexo application and by the trusted
// layer, because it contains all the references that are available to the nexo
// application during transaction
//
// Trusted layer shall implement policies regarding sharing of those data
// elements

extern struct TerminalConfiguration tc;
extern struct ApplicationProfile ap;
extern struct ServiceConfiguration sc;
extern struct TerminalTransactionData ttd;
extern struct KernelData kd;
extern struct CardData cd;
extern struct OnlineResponseData ord;
