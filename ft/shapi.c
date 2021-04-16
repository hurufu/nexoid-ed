#include "NexoFast.h"
#include "scapi.h"
#include "hapi.h"
#include "pklr.h"
#include "eapi.h"
#include "tmapi.h"
#include "papi.h"
#include "gtd.h"

static struct E1KernelData s_e1kd;
static struct TerminalListOfAid s_TerminalListOfAid;

struct PklrConfiguration pklr;

struct PermanentTerminalSpecificData e0;
struct TerminalSpecificData e1;
struct ApplicationProfileSelectionTable* e2;
struct CaPublicKeyTable* e3;
struct ServiceSettingsTable e4;
struct ApplicationProfileList* e6;
struct TerminalListOfBid* e7;
struct ApplicationProfileSelectionTableNonChip* e8;
struct ExceptionFile* e9;
struct CombinationListAndParameters* ec;
struct AidPreferenceTable* ee;

struct ApplicationProfile ap;
struct ServiceSettingsEntry sc;
struct TerminalTransactionData ttd;
struct EntryPointData ep;
struct CardResponse* cr;
struct E1KernelData* e1kd = &s_e1kd;
struct OnlineResponseData ord;
struct SearchTransactionResultList* sl;

enum PrinterStatus g_PrinterStatus = PRINTER_UNAVAILABLE;
enum TmsContactLevel g_callTms = CALL_TMS_NONE;
struct TerminalListOfAid* g_TerminalListOfAid = &s_TerminalListOfAid;
struct CandidateList* g_CandidateList = NULL;
struct AidPreferenceTable* g_AidPreferenceTable = NULL;

enum HapiResult hapi_Search_Transactions(const struct SearchLogCriteria* const slc) {
    (void)slc;
    return HAPI_NOK;
}

enum HapiResult hapi_SearchReservationsByPan(void) {
    return HAPI_NOK;
}

enum HapiResult hapi_Online_Request_to_Dcc_Provider(void) {
    return HAPI_NOK;
}

enum HapiResult hapi_Online_Approval_Request(void) {
    return HAPI_NOK;
}

enum HapiResult hapi_Transaction_Data_Storage(void) {
    return HAPI_NOK;
}

enum HapiResult hapi_Transaction_Finalisation(void) {
    return HAPI_NOK;
}

enum HapiResult hapi_SearchReservationsByRefData(void) {
    return HAPI_NOK;
}

enum HapiResult hapi_Status(void) {
    return HAPI_OK;
}

enum HapiResult hapi_Log_Entry_Data_Retrieval(void) {
    return HAPI_NOK;
}

enum ScapiResult scapi_Data_Entry_Interaction(size_t size, const enum CardholderMessage msg[static const size]) {
    (void)msg;
    return SCAPI_NOK;
}

enum ScapiResult scapi_Cardholder_Confirmation(void) {
    return SCAPI_NOK;
}

enum ScapiResult scapi_Search_Transaction_Result_List(void) {
    return SCAPI_NOK;
}

enum ScapiResult scapi_No_Original_Transaction(void) {
    return SCAPI_NOK;
}

enum ScapiResult scapi_Update_Interfaces(const enum InterfaceStatus status) {
    (void)status;
    return SCAPI_NOK;
}


enum ProcedureResult Initialiase_Basic_Data(void) {
    return PR_NOK;
}

enum ScapiResult scapi_Update_Pre_Auth_Amount_Confirmation(void) {
    return SCAPI_NOK;
}

enum ScapiResult scapi_Update_Pre_Auth_Amount_Entry(void) {
    return SCAPI_NOK;
}

enum ScapiResult scapi_Set_Update_Pre_Auth_Total_Amount(void) {
    return SCAPI_NOK;
}

enum ScapiResult scapi_Wait_For_Event(void) {
    return SCAPI_NEW_EVENT;
}

enum ScapiResult scapi_Output_Amount_Error(void) {
    return SCAPI_NOK;
}

enum ScapiResult scapi_Output_Transaction_Amount(void) {
    return SCAPI_NOK;
}

bool scapi_Authorise_Service(void) {
    return false;
}

enum ProcedureResult Update_Cardholder_Initial_Message(void) {
    return PR_NOK;
}

enum ScapiResult scapi_Data_Output_Interaction(const size_t size, const enum CardholderMessage msg[const size]) {
    (void)msg;
    return SCAPI_NOK;
}

enum ScapiResult scapi_Data_Print_Interaction(const enum PrintMessage m) {
    (void)m;
    return SCAPI_NOK;
}

enum PapiResult papi_Proprietary_Startup_Sequence(void) {
    return PAPI_OK;
}

enum ProcedureResult papi_Diagnostics_Maintenance_Recovery(void) {
    return PR_REBOOT;
}

enum PapiResult papi_Specific_Processing_Based_On_Pan(void) {
    return PAPI_DONE;
}

enum PapiCvmResult papi_Proprietary_Cvm_Condition_Code_Processing(const struct CvRule cvRule) {
    (void)cvRule;
    return PAPI_CVM_NOT_APPLICABLE;
}

enum PapiCvmResult papi_Proprietary_Cvm_Support_Check(const struct CvRule cvRule) {
    (void)cvRule;
    return PAPI_CVM_NOT_SUPPORTED;
}

enum EapiResult eapi_Activate_Contacts_And_Reset_Chip(void) {
    return EAPI_NOK;
}

enum EapiResult eapi_Reset_Chip(void) {
    return EAPI_NOK;
}

enum EapiResult eapi_Select_Pse(void) {
    return EAPI_NOK;
}

enum EapiResult eapi_Select_Application(const struct Aid* const aid) {
    (void)aid;
    return EAPI_NOK;
}

enum EapiResult eapi_Read_Record(const uint8_t p1, const uint8_t p2) {
    (void)p1, (void)p2;
    return EAPI_NOK;
}

enum EapiResult eapi_Final_Application_Selection(void) {
    return EAPI_NOK;
}

enum EapiResult eapi_Select_Next_Application(const struct Aid* const aid) {
    (void)aid;
    return EAPI_NOK;
}

enum EapiResult eapi_Get_Processing_Options(const uint8_t commandTemplate, const struct DolData* const cdaTransactionData) {
    (void)commandTemplate, (void)cdaTransactionData;
    return EAPI_NOK;
}

enum EapiResult eapi_External_Authenticate(void) {
    return EAPI_NOK;
}

enum EapiResult eapi_Verify_Pin_Block(const uint8_t p2) {
    (void)p2;
    return EAPI_NOK;
}

enum EapiResult eapi_Get_Challenge(void) {
    return EAPI_NOK;
}

enum PklrResult pklr_Process_Read_Record(const uint8_t p1, const uint8_t p2) {
    (void)p1, (void)p2;
    return PKLR_NOK;
}

enum PklrResult pklr_Offline_Data_Authentication(void) {
    return PKLR_NOK;
}

enum PklrResult pklr_Build_Candidate_List(void) {
    return PKLR_NOK;
}

enum PklrResult pklr_Kernel_E_Processing(void) {
    return Kernel_E_Processing();
}

enum PklrResult pklr_First_Generate_Ac_Processing(const uint8_t p1) {
    (void)p1;
    return PKLR_NOK;
}

enum PklrResult pklr_Second_Generate_Ac_Processing(const uint8_t p1) {
    (void)p1;
    return PKLR_NOK;
}

enum PklrResult pklr_First_Issuer_Script_Processing(void) {
    return PKLR_NOK;
}

enum PklrResult pklr_Second_Issuer_Script_Processing(void) {
    return PKLR_NOK;
}

enum TmapiResult tmapi_Perform_Terminal_Managment_Session(void) {
    return TMAPI_NOK;
}

enum ScapiResult sped_Generate_Enciphered_Pin_Data(struct CvRule cvRule) {
    (void)cvRule;
    return SCAPI_NOK;
}

enum ScapiResult sped_Generate_Offline_Pin_Block(struct CvRule cvRule) {
    (void)cvRule;
    return SCAPI_NOK;
}

enum ScapiResult sped_Encrypt_Pin_Block(const struct EncipherablePinBlock* const pb, struct binary** const epb) {
    (void)pb, (void)epb;
    return SCAPI_NOK;
}

enum ScapiResult randapi_Generate_Random_Number(const uint8_t upperLimit, uint8_t* randomNumber) {
    (void)upperLimit, (void)randomNumber;
    return SCAPI_NOK;
}

enum ScapiResult randapi_Generate_Random_Bytes(const size_t size, uint8_t randomBytes[static const size]) {
    (void)randomBytes;
    return SCAPI_NOK;
}
