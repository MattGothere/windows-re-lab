#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {
    // goal :
    // to list the " Notepad.exe's threads "

    std::wstring target;
    std::wcout << L"Enter the name of application: ";
    std::wcin >> target;

    HANDLE ProcSnap = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS,
        0
    );

    if (ProcSnap == INVALID_HANDLE_VALUE) {
        std::cout << "error : INVALID_HANDLE_VALUE \n ";
        return 0;
    }

    PROCESSENTRY32 ListEntry;
    ListEntry.dwSize = sizeof(PROCESSENTRY32);

    bool FirstProc = Process32First(
        ProcSnap,
        &ListEntry
    );

    if (!FirstProc) {
        std::cout << "failed to copy process list. \n";
        CloseHandle(ProcSnap);
        return 0;
    }

    DWORD targetID;
    bool found = FALSE; // if found

    // compare the first to target
    if (std::wstring(ListEntry.szExeFile) == target) {
        found = TRUE;
        targetID = ListEntry.th32ProcessID;
    }

    while (!found && Process32Next(ProcSnap, &ListEntry)) {
        if (std::wstring(ListEntry.szExeFile) == target) {
            found = TRUE;
            targetID = ListEntry.th32ProcessID;
        }
    }

    if (!found) {
        std::cout << "Application not found... \n";
        CloseHandle(ProcSnap);
        return 0;
    }

    std::wcout << targetID;
    CloseHandle(ProcSnap);

    return 0;
}