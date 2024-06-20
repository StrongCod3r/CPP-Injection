
#include "Utils.h"



int main() {

    OutputDebugString(L"TestCall\n");

    WCHAR processNamee[] = L"TestProg.exe";
    DWORD processIdd = getProcessIdByName(&processNamee[0]);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processIdd);

    const char* dllPath = "D:\\DEV\PROJECTS\\CallFunctionInjection\\x64\\Release\\TestInjection.dll";
    void* pLibRemote = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

    WriteProcessMemory(hProcess, pLibRemote, (void*)dllPath, strlen(dllPath) + 1, NULL);

    HMODULE hKernel32 = GetModuleHandle(TEXT("Kernel32"));
    FARPROC pLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, pLibRemote, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);

    VirtualFreeEx(hProcess, pLibRemote, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    return 0;
}