
#include <Windows.h>
#include <iostream>
#include <functional>


template <typename T>
T FunDef(uintptr_t address)
{
    return reinterpret_cast<T>(address);
}


// Prototypes
using pPrintMsg = void(*)(const char* format, ...);


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    OutputDebugString(L"DllMain\n");

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugString(L"DLL_PROCESS_ATTACH -> TestInjection\n");
    case DLL_THREAD_ATTACH:
        OutputDebugString(L"DLL_THREAD_ATTACH -> TestInjection\n");
    case DLL_THREAD_DETACH:
        OutputDebugString(L"DLL_THREAD_DETACH -> TestInjection\n");
    case DLL_PROCESS_DETACH:
        OutputDebugString(L"DLL_PROCESS_DETACH -> TestInjection\n");
        break;
    }


    /*if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        auto PrintMsg = FunDef<pPrintMsg>(0x00007FF6D0EC1010);

        for (size_t i = 0; i < 10; i++)
        {
            PrintMsg("--> Inyect %d\n", i);
            Sleep(1000);
        }

    }*/



    return TRUE;
}



