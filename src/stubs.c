#include "dmapi.h"
#include "papi.h"
#include "scapi.h"
#include "eapi.h"
#include "hapi.h"
#include "pklr.h"
#include "tmapi.h"
#include "gtd.h"

#include <stdlib.h>

#define UNUSED __attribute__((__unused__))
#define NORETURN  __attribute__((__noreturn__))
#define DLLSTUB NORETURN

struct TerminalTransactionData ttd;
struct ApplicationProfile ap;
struct CardResponse* cr;
struct PermanentTerminalSpecificData e0;
struct TerminalSpecificData e1;
struct E1KernelData* e1kd;
struct ApplicationProfileSelectionTable* e2;
struct ServiceSettingsTable e4;
struct ApplicationProfileList* e6;
struct TerminalListOfBid* e7;
struct ApplicationProfileSelectionTableNonChip* e8;
struct ExceptionFile* e9;
struct CombinationListAndParameters* ec;
struct AidPreferenceTable* ee;
struct PklrConfiguration pklr;
struct CandidateList* g_CandidateList;
enum PrinterStatus g_PrinterStatus;
enum TmsContactLevel g_callTms;
struct TerminalListOfAid* g_TerminalListOfAid;
struct OnlineResponseData ord;
struct SearchTransactionResultList* sl;
struct ServiceSettingsEntry sc;
struct EntryPointData ep;

static NORETURN void stub_impl(void) {
    abort();
}

DLLSTUB void dmapi_dtor(void) { stub_impl(); }
DLLSTUB enum DmapiResult dmapi_init(void) { stub_impl(); }
void* dmapi_malloc(size_t x UNUSED) { return NULL; }

DLLSTUB enum EapiResult eapi_Activate_Contacts_And_Reset_Chip(void) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Reset_Chip(void) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Select_Pse(void) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Select_Application(const struct Aid* x UNUSED) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Select_Next_Application(const struct Aid* x UNUSED) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Generate_Ac() { stub_impl(); }
DLLSTUB enum EapiResult eapi_Read_Record(uint8_t p1 UNUSED, uint8_t p2 UNUSED) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Verify_Pin_Block(uint8_t p2 UNUSED) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Get_Challenge(void) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Final_Application_Selection(void) { stub_impl(); }
DLLSTUB enum EapiResult eapi_Get_Processing_Options(uint8_t x UNUSED, const struct DolData* y UNUSED) { stub_impl(); }
DLLSTUB enum EapiResult eapi_External_Authenticate(void) { stub_impl(); }

DLLSTUB enum HapiResult hapi_Online_Request_to_Dcc_Provider(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_Online_Approval_Request(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_Status(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_Search_Transactions(const struct SearchLogCriteria* slc UNUSED) { stub_impl(); }
DLLSTUB enum HapiResult hapi_SearchReservationsByRefData(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_SearchReservationsByPan(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_Log_Entry_Data_Retrieval(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_Initialiase_Basic_Data(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_Transaction_Finalisation(void) { stub_impl(); }
DLLSTUB enum HapiResult hapi_Transaction_Data_Storage(void) { stub_impl(); }

DLLSTUB enum PapiResult papi_Proprietary_Startup_Sequence(void) NOEXCEPT { stub_impl(); }
DLLSTUB enum ProcedureResult papi_Diagnostics_Maintenance_Recovery(void) NOEXCEPT { stub_impl(); }
DLLSTUB void papi_Force_Reboot(void) NOEXCEPT { stub_impl(); }
DLLSTUB void papi_Force_Termination(void) NOEXCEPT { stub_impl(); }
DLLSTUB enum PapiResult papi_Specific_Processing_Based_On_Pan(void) NOEXCEPT { stub_impl(); }
DLLSTUB enum PapiCvmResult papi_Proprietary_Cvm_Condition_Code_Processing(struct CvRule cvRule UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB enum PapiCvmResult papi_Proprietary_Cvm_Support_Check(struct CvRule cvRule UNUSED) NOEXCEPT { stub_impl(); }

DLLSTUB enum PklrResult pklr_Build_Candidate_List(void) { stub_impl(); }
DLLSTUB enum PklrResult pklr_Emv_Completion(void) { stub_impl(); }
DLLSTUB enum PklrResult pklr_Kernel_E_Processing(void) { stub_impl(); }
DLLSTUB enum PklrResult pklr_Process_Read_Record(uint8_t p1 UNUSED, uint8_t p2 UNUSED) { stub_impl(); }
DLLSTUB enum PklrResult pklr_Offline_Data_Authentication(void) { stub_impl(); }
DLLSTUB enum PklrResult pklr_First_Generate_Ac_Processing(uint8_t p1 UNUSED) { stub_impl(); }
DLLSTUB enum PklrResult pklr_First_Issuer_Script_Processing(void) { stub_impl(); }
DLLSTUB enum PklrResult pklr_Second_Issuer_Script_Processing(void) { stub_impl(); }
DLLSTUB enum PklrResult pklr_Second_Generate_Ac_Processing(uint8_t p1 UNUSED) { stub_impl(); }

DLLSTUB enum ScapiResult randapi_Generate_Random_Number(uint8_t upperLimit UNUSED, uint8_t* randomNumber UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB enum ScapiResult randapi_Generate_Random_Bytes(size_t size UNUSED, uint8_t randomBytes[N(size)] UNUSED) NOEXCEPT { stub_impl(); }

DLLSTUB enum ScapiResult scapi_Wait_For_Event(void) NOEXCEPT { stub_impl(); }
DLLSTUB enum ScapiResult scapi_Update_Interfaces(enum InterfaceStatus x UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB enum ScapiResult scapi_Data_Output_Interaction(size_t size UNUSED, const enum CardholderMessage msg[N(size)] UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB enum ScapiResult scapi_Data_Print_Interaction(enum PrintMessage x UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB enum ScapiResult scapi_Data_Entry_Interaction(size_t size UNUSED, const enum CardholderMessage msg[N(size)] UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB bool scapi_Authorise_Service(void) { stub_impl(); }

DLLSTUB enum ScapiResult sped_Generate_Enciphered_Pin_Data(struct CvRule x UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB enum ScapiResult sped_Generate_Offline_Pin_Block(struct CvRule x UNUSED) NOEXCEPT { stub_impl(); }
DLLSTUB enum ScapiResult sped_Encrypt_Pin_Block(const struct EncipherablePinBlock* pb UNUSED, struct binary** encryptedPinBlock UNUSED) NOEXCEPT { stub_impl(); }

DLLSTUB enum TmapiResult tmapi_Perform_Terminal_Managment_Session(void) { stub_impl(); }
