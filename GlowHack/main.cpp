#include "Includes.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        DisableThreadLibraryCalls(hModule);
        HideDll DLL(hModule);
        DLL.RemoveLDR();
        DLL.RemoveMAP();
        DLL.RemovePEH();
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)C_Hack::Init, hModule, NULL, NULL);

        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
