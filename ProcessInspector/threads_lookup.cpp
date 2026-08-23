#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {
    // goal : to list the "Notepad.exe"'s threads
    // 
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

    if (ProcSnap == INVALID_HANDLE_VALUE) {
        std::cout << "error : modu with INVALID_HANDLE_VALUE \n ";
        return 0;
    }

    THREADENTRY32 tListEntry;
    tListEntry.dwSize = sizeof(THREADENTRY32);

    PROCESSENTRY32 pListEntry;
    pListEntry.dwSize = sizeof(PROCESSENTRY32);

    // ======== gathering snapshots information ========

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
    return 0;
}