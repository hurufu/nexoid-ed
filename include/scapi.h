#pragma once

#include "types.h"

/* SCAPI - Sale system, cardholder, attendant API
 *
 * TODO: Remove preauth related API, that can be simplified and unified
 */

/* Allowed return codes for SCAPI
 */
enum ScapiResult {
    SCAPI_OK = 60
  , SCAPI_NOK
  , SCAPI_NEW_EVENT
};

enum ScapiResult scapi_Cardholder_Confirmation(void);

enum ScapiResult scapi_Search_Transaction_Result_List(void);

enum ScapiResult scapi_No_Original_Transaction(void);

enum ScapiResult scapi_Update_Pre_Auth_Amount_Confirmation(void);

enum ScapiResult scapi_Update_Pre_Auth_Amount_Entry(void);

enum ScapiResult scapi_Set_Update_Pre_Auth_Total_Amount(void);

/* Blocks until an event from SCAP is received
 *
 * This is the most complex function to implement, consider some simplifications.
 *
 * Global tags that are expected to be set for each event (if applicable):
 *
 * E_AMOUNT_ENTRY:
 *   ~ ttd.transactionAmount
 *   ~ ttd.cashbackAmount
 *   ~ ttd.supplementaryAmount
 *   ~ ttd.supplementaryAmountConfirmed
 *   ~ ttd.minus
 * E_SERVICE_SELECTION:
 *   ~ ttd.selectedService
 * E_LANGUAGE_SELECTION:
 *   ~ ttd.selectedLanguage
 * E_ACQUIRER_PRESELECTION:
 *   ~ ttd.preSelectedAcquirerNumber
 * E_CHOICE_OF_APPLICATION:
 *   ~ nothing
 * E_CARD_INSERTED:
 *   ~ nothing
 * E_CARD_SWIPED:
 *   ~ ttd.pan // Nexo specifies different place
 *   ~ ttd.expiryDate // Nexo specifies different place
 * E_MANUAL_ENTRY:
 *   ~ ttd.pan
 *   ~ ttd.expiryDate
 * E_ACCEPT:
 *   ~ nothing
 * E_REFERENCE_ENTRY:
 *   ~ ttd.referenceData
 *
 * @returns SCAPI_NEW_EVENT if new event was received, or SCAPI_NOK if an error occured.
 */
enum ScapiResult scapi_Wait_For_Event(void);

enum ScapiResult scapi_Update_Interfaces(enum InterfaceStatus);

enum ScapiResult scapi_Data_Output_Interaction(size_t size, const enum CardholderMessage msg[size]);

enum ScapiResult scapi_Data_Print_Interaction(enum PrintMessage);

/*
 * TODO: Function signature isn't yet defined
 */
enum ScapiResult scapi_Data_Entry_Interaction(void);

/* Called before strting protected service during Service_Initialisation
 *
 * TODO: Consider changing return value to `enum ScapiResult`
 *
 * nexo-FAST v.3.2, figure 21
 */
bool scapi_Authorise_Service(void);
