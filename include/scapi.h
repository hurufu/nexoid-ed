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
};

enum ScapiResult scapi_Cardholder_Confirmation(void);

enum ScapiResult scapi_Search_Transaction_Result_List(void);

enum ScapiResult scapi_No_Original_Transaction(void);

enum ScapiResult scapi_Update_Pre_Auth_Amount_Confirmation(void);

enum ScapiResult scapi_Update_Pre_Auth_Amount_Entry(void);

enum ScapiResult scapi_Set_Update_Pre_Auth_Total_Amount(void);

enum ScapiResult scapi_Wait_For_Event(void);

enum ScapiResult scapi_Output_Amount_Error(void);

enum ScapiResult scapi_Output_Transaction_Amount(void);

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
bool Authorise_Service(void);
