#include <windows.h>
#include <stdio.h>
#include "NTAPI_funcs.h"


extern DWORD CustomError(void);


// Function to get a module handle

HMODULE GetMod(IN LPCWSTR moduleName) {
    HMODULE hModule = NULL;
    info("Trying to get a handle to %ls", moduleName);

    hModule = GetModuleHandleW(moduleName);

    if (hModule == NULL) {
        Warning("failed to get handle to the module, error 0x%lx\n", GetLastError());
        return NULL;
    }
    else {
        okay("Got handle on the module : %ls \n", moduleName);
        info("\\______[ %ls _0x%p]", moduleName, hModule);
        return hModule;
    }
}

int main(int argc, char* argv[]) {
    DWORD PID = NULL;
    HANDLE hProcess = NULL;
    HMODULE hNTDLL = NULL;
    NTSTATUS STATUS = NULL;
    fn_PROCESS_BASIC_INFORMATION pbi;
    ULONG ReturnLength = NULL;


    info("Getting the TEB ------\n");
    PTEB pTeb = getTEB();
    okay("We got the TEB  0x%p ", pTeb);

    if (argc < 2) {
        Warning("Usage : Ntapi_AntiDebug_Checker.exe PID");
        return EXIT_FAILURE;
    }


    PID = atoi(argv[1]);

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
    if (hProcess == NULL) {
        Warning("Process can't be opened, the PID doesn't exist");
        return EXIT_FAILURE;
    }

    info("Great process opened");


    info("Trying to get handle on hNTDLL");
    hNTDLL = GetMod(L"NTDLL");
    if (hNTDLL == NULL) {
        Warning("Failed to get handle to ntdll.dll");
        return EXIT_FAILURE;
    }

    info("We got the NTDLL on the address : 0x%p", hNTDLL);

    //-------Here we start Populating the function of the NTAPI-------------

    MyNtQueryInformationProcess R0m4Query = (MyNtQueryInformationProcess)GetProcAddress(hNTDLL, "NtQueryInformationProcess");

    STATUS = R0m4Query(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), &ReturnLength);

    if (STATUS != STATUS_SUCCESS) {
        Warning("We failed to retrieve the ProcessBasicInformation with a status of : 0x%lx", STATUS);
        CloseHandle(hProcess);
        return EXIT_FAILURE;
    }

    //Use the process information as needed
    info("We retrieved the pebBaseAdress 0x%lx", pbi.PebBaseAddress);

    BYTE BeingDebugged,BeingDebuggedChecker = NULL;
    SIZE_T bytesRead  = NULL;
    SIZE_T bytesWritten;
    BYTE BeingPatched = 0;
    if (!ReadProcessMemory(hProcess, (LPCVOID)((PBYTE)pbi.PebBaseAddress + 0x2), &BeingDebugged, sizeof(BeingDebugged), &bytesRead)) {
        Warning("Failed to retrieve the Being Debugged flag, error 0x%lx", CustomError());
        return EXIT_FAILURE;
    }
    else {
        info("BeingDebugged flag: %d", BeingDebugged);
    }

    if (BeingDebugged != 0) {
        Warning("Process is being debugged");
        info("We are going to change the beingdebugged flag! ");

        if (!WriteProcessMemory(hProcess, (LPVOID)((PBYTE)pbi.PebBaseAddress + 0x2), &BeingPatched, sizeof(BeingPatched), &bytesWritten)) {
            Warning("The process still not patched,an error 0x%lx has occured", CustomError());
            ReadProcessMemory(hProcess, (LPCVOID)((PBYTE)pbi.PebBaseAddress + 0x2), &BeingDebuggedChecker, sizeof(BeingDebuggedChecker), &bytesRead);
            if (BeingDebuggedChecker == NULL) {
                Warning("Failed to retrieve the Being Debugged flag, error 0x%lx", CustomError());
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        info("The Flag has been patched already , great one ");
        if (BeingDebuggedChecker == 0) {
            Warning(" changed the Being Debugged flag ------------ BeingDebugged = %lx", BeingDebuggedChecker);
        }

        return EXIT_SUCCESS;
    }
    else {
        Warning("Debugger not detected !!!!");
    }


}
