#include "Utils.h"

std::wstring ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}




DWORD getProcessIdByName(PWCHAR processNameIn) {
    PROCESSENTRY32 proc = { 0 };
    proc.dwSize = sizeof(PROCESSENTRY32);
    HANDLE handleInst = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    Process32First(handleInst, &proc);
    //if (!Process32First(handleInst, &proc)) return false;

    int processNum = 0;
    do {

        processNum++;


        if (wcscmp(processNameIn, proc.szExeFile) == 0) {
            //wprintf(L"\nprocess name: %s\n\n", proc.szExeFile);
            //printf("process id: %d\n\n", proc.th32ProcessID);
            return proc.th32ProcessID;
        }

    } while (Process32Next(handleInst, &proc));
    //printf("processes: %d\n\n", processNum);
    CloseHandle(handleInst);
    return false;
}


bool getModuleInfoByName(HANDLE process, PWCHAR name, MODULEINFO* moduleInfo) {

    DWORD sizeNeed = 0;
    bool success = EnumProcessModules(process, NULL, 0, &sizeNeed);
    HMODULE* moduleList = (HMODULE*)malloc(sizeNeed);
    success = EnumProcessModules(process, moduleList, sizeNeed, &sizeNeed);
    WCHAR moduleName[128];
    for (DWORD i = 0; i < (sizeNeed / sizeof(HMODULE)); i++) {

        success = GetModuleBaseName(process, *moduleList, &moduleName[0], sizeof(moduleName));
        if (wcscmp(name, moduleName) == 0) {
            //wprintf(L"found module (%ls)\n", moduleName);
            success = GetModuleInformation(process, *moduleList, moduleInfo, sizeof(MODULEINFO));
            if (success) return true;
        }



        moduleList++;
    }


    return false;
}
