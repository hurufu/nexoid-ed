#pragma once

#include "cxx_macros.h"

EXTERN_C_PREAMBLE

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
 * E_PRINTER_STATUS:
 *   ~ g_PrinterStatus
 * E_ATTENDANT_FORCED_ONLINE:
 *   ~ nothing
 * E_CARD_REMOVAL:
 *   ~ nothing
 * E_CANCEL:
 *   ~ nothing
 * E_REBOOT_REQUESTED:
 *   ~ nothing
 * E_TERMINATION_REQUESTED:
 *   ~ nothing
 *
 * @returns SCAPI_NEW_EVENT if new event was received, or SCAPI_NOK if an error occured.
 */
enum ScapiResult scapi_Wait_For_Event(void) NOEXCEPT;

enum ScapiResult scapi_Update_Interfaces(enum InterfaceStatus) NOEXCEPT;

enum ScapiResult scapi_Data_Output_Interaction(size_t size, const enum CardholderMessage msg[N(size)]) NOEXCEPT;

enum ScapiResult scapi_Data_Print_Interaction(enum PrintMessage) NOEXCEPT;

/*
 * TODO: Function signature isn't yet defined
 */
enum ScapiResult scapi_Data_Entry_Interaction(size_t size, const enum CardholderMessage msg[N(size)]) NOEXCEPT;

/* Called before strting protected service during Service_Initialisation
 *
 * TODO: Consider changing return value to `enum ScapiResult`
 *
 * nexo-FAST v.3.2, figure 21
 */
bool scapi_Authorise_Service(void) NOEXCEPT
__attribute__((__deprecated__));

/*
 * NOTE: As a general rule for security sensitive functions it's proposed that
 *       nexo-FAST shouldn't allocate any local buffers and shouldn't send
 *       pointers to such locally allocated buffers to avoid possibility of
 *       internal stack corruption by the implementation of an interface. So
 *       each interface is expected to allocat such buffer using DMAPI.
 * TODO: Check if memory allocation delagation is actually safer then just
 *       passing a pointer to a local buffer
 */

/* 
 * TODO: Consider moving to separate API
 */
enum ScapiResult sped_Generate_Enciphered_Pin_Data(struct CvRule) NOEXCEPT;

/* Generate PIN Block for Offline Authentication
 *
 * On success kd.offlinePinBlock should not be NULL
 *
 * TODO: Consider moving to separate API
 */
enum ScapiResult sped_Generate_Offline_Pin_Block(struct CvRule) NOEXCEPT;

/* Encrypt PIN block using RSA
 *
 * This procedure should perform RSA recovery using ICC PIN Encipherment Public Key
 *
 * EMV Book 2 v.4.3, annex B2.1.3
 * nexo-FAST v.3.2, section 8.2.14.2.9 (last action in a diagram)
 * EMV Book 3 v.4.3, figure 11 (action named "Encipher PIN using recovered ICC key")
 */
enum ScapiResult sped_Encrypt_Pin_Block(const struct EncipherablePinBlock* pb, struct binary** encryptedPinBlock) NOEXCEPT;

/* Generate random number in the range
 */
enum ScapiResult randapi_Generate_Random_Number(uint8_t upperLimit, uint8_t* randomNumber) NOEXCEPT;

/* Allocate and generate random bytes
 *
 */
enum ScapiResult randapi_Generate_Random_Bytes(size_t size, uint8_t randomBytes[N(size)]) NOEXCEPT;

EXTERN_C_EPILOGUE
