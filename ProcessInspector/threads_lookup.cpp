#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {
    // goal 1 : to list the "Notepad.exe"'s threads
    //      2 : show the executable path 
    // =======================================================
    // thoughts : enumerate all the threads in the system, and
    //            find the parent process by comparing.

    std::wstring target;
    std::wcout << L"Enter the name of application: ";
    std::wcin >> target;

    // ======== create snapshots needed ========

    HANDLE ProcSnap = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS,
        0
    );

    HANDLE ThreSnap = CreateToolhelp32Snapshot(
        TH32CS_SNAPTHREAD,
        0
    );

    if (ProcSnap == INVALID_HANDLE_VALUE) {
        std::cout << "error : snap with INVALID_HANDLE_VALUE \n ";
        return 0;
    }

    if (ThreSnap == INVALID_HANDLE_VALUE) {
        std::cout << "error : thre with INVALID_HANDLE_VALUE \n ";
        return 0;
    }

    THREADENTRY32 tListEntry;
    tListEntry.dwSize = sizeof(THREADENTRY32);

    PROCESSENTRY32 pListEntry;
    pListEntry.dwSize = sizeof(PROCESSENTRY32);

    // ======== gathering *Proc \ Thre* snapshots information ========

    bool FirstProc = Process32First(
        ProcSnap,
        &pListEntry
    );

    if (!FirstProc) {
        std::cout << "failed to copy process list. \n";
        CloseHandle(ProcSnap);
        return 0;
    }

    bool FirstThre = Thread32First(
        ThreSnap,
        &tListEntry
    );

    if (!FirstThre) {
        std::cout << "failed to copy thread list. \n";
        CloseHandle(ThreSnap);
        return 0;
    }

    // ======== finding target process ========

    DWORD targetID;
    bool procfound = FALSE; // if found

    // compare the first to target
    if (std::wstring(pListEntry.szExeFile) == target) {
        procfound = TRUE;
        targetID = pListEntry.th32ProcessID;
    }

    while (!procfound && Process32Next(ProcSnap, &pListEntry)) {
        if (std::wstring(pListEntry.szExeFile) == target) {
            procfound = TRUE;
            targetID = pListEntry.th32ProcessID;
        }
    }

    if (!procfound) {
        std::cout << "Process not found... \n";
        CloseHandle(ProcSnap);
        CloseHandle(ThreSnap);
        return 0;
    }

    std::wcout << L"PID: " << targetID << std::endl;

    // ======== finding target's executable path ========
    
    HANDLE ModuSnap = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE,
        targetID
    );

    if (ModuSnap == INVALID_HANDLE_VALUE) {
        std::cout << "error: modu with INVALID_HANDLE_VALUE \n ";
        return 0;
    }

    MODULEENTRY32 mListEntry;
    mListEntry.dwSize = sizeof(MODULEENTRY32);

    bool FirstModu = Module32First(
        ModuSnap,
        &mListEntry
    );

    if (!FirstModu) {
        std::cout << "failed to copy modu list. \n";

        DWORD errorCode = GetLastError();
        std::cout << "error code: " << errorCode << std::endl;
        CloseHandle(ModuSnap);  
        return 0;
    }

    std::wcout << L"executable path: " << mListEntry.szExePath << std::endl;


    // ======== finding target's thread ========

    // compare the first
    int threadCount = 0;

    if (tListEntry.th32OwnerProcessID == targetID) {
        threadCount ++;
        std::wcout << L"thread #" << threadCount << L": " << tListEntry.th32ThreadID << std::endl;
    }
    // compare the rest
    while (Thread32Next(ThreSnap, &tListEntry)) {
        if (tListEntry.th32OwnerProcessID == targetID) {
            threadCount++;
            std::wcout << L"thread #" << threadCount << L": " << tListEntry.th32ThreadID << std::endl;
        }
    }

    std::wcout << L"PROCESSENTRY32 reported threads: " << pListEntry.cntThreads << std::endl;

    CloseHandle(ProcSnap);
    CloseHandle(ThreSnap);
    CloseHandle(ModuSnap);
    return 0;
}