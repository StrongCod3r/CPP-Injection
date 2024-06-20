#pragma once
#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <TlHelp32.h>

std::wstring ExePath();
DWORD getProcessIdByName(PWCHAR processNameIn);
bool getModuleInfoByName(HANDLE process, PWCHAR name, MODULEINFO* moduleInfo);