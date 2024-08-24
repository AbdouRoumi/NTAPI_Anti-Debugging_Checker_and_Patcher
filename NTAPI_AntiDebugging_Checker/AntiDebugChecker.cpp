#include <windows.h>
#include <stdio.h>
#include "NTAPI_funcs.h"

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
        okay("Got handle on the module : %s \n", moduleName);
        info("\\______[ %s _0x%p]", moduleName, hModule);
        return hModule;
    }
}

int main(int argc, char* argv[]) {
    DWORD PID = NULL;
    HANDLE hProcess = NULL;
    HMODULE hNTDLL = NULL;
    NTSTATUS STATUS = NULL;


    if (argc < 2) {
        Warning("Usage : Ntapi_AntiDebug_Checker.exe PID");
        return EXIT_FAILURE;
    }


    PID = atoi(argv[1]);

    hNTDLL = GetMod(L"hNTDLL");
    

    //-------Here we start Populating the function of the NTAPI-------------


    NtQueryInformationProcess R0m4Query = (NtQueryInformationProcess)GetProcAddress(hNTDLL, "NtQueryInformationProcess");

    STATUS = NtQueryInformationProcess()


}
