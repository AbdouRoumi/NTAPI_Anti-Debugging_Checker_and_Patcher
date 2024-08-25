
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>


#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define okay(msg,...) printf("[+]" msg "\n",__VA_ARGS__)
#define info(msg,...) printf("[+]" msg "\n",__VA_ARGS__)
#define Warning(msg,...) printf("[+]" msg "\n",__VA_ARGS__)

extern "C" PTEB getTEB(void);
extern "C" DWORD CustomError(void);


//here I defined each NTAPI func  with it's own structures , I used ntdoc and Virgilius project


//--------------Functions prototypes--------------------------


typedef struct fn_PROCESS_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;
    PPEB PebBaseAddress;
    KAFFINITY AffinityMask;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE Inheritedfn_FromUniqueProcessId;
} fn_PROCESS_BASIC_INFORMATION, * Pfn_PROCESS_BASIC_INFORMATION;

typedef struct my_PEB {
    BYTE                          Reserved1[2];
    BYTE                          BeingDebugged;
    BYTE                          Reserved2[1];
    PVOID                         Reserved3[2];
    PPEB_LDR_DATA                 Ldr;
    PRTL_USER_PROCESS_PARAMETERS  ProcessParameters;
    PVOID                         Reserved4[3];
    PVOID                         AtlThunkSListPtr;
    PVOID                         Reserved5;
    ULONG                         Reserved6;
    PVOID                         Reserved7;
    ULONG                         Reserved8;
    ULONG                         AtlThunkSListPtr32;
    PVOID                         Reserved9[45];
    BYTE                          Reserved10[96];
    PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
    BYTE                          Reserved11[128];
    PVOID                         Reserved12[1];
    ULONG                         SessionId;
} my_PEB, * Pmy_PEB;


typedef NTSTATUS(*MyNtQueryInformationProcess)(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
    );
