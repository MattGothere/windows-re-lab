#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main()
{
    HANDLE snap; // create a handle, helping us to access proccess information                        
    bool handle_closeing;

    snap = CreateToolhelp32Snapshot(    
        TH32CS_SNAPPROCESS,             // include all process in the system
        0                               // current process
    );

    if (snap == INVALID_HANDLE_VALUE) {
        std::cout << "failed to create snapshot. \n";
        return 0;
    }

    PROCESSENTRY32 pe;                    // open up a "sheet" to let functions fill in   
    pe.dwSize = sizeof(pe);    // initialize dwsize

    bool first;                             
    first = Process32First(                 // fill up the very first sheet
        snap,
        &pe
    );

    if (!first) {
        std::cout << "failed to copy process list. \n";
        handle_closeing = CloseHandle(snap);            // close the handle if failed
        return 0;
    }

    // ***全部改用寬字元串流***
    std::wcout << L"process name: " << pe.szExeFile 
               << L" PID: " << pe.th32ProcessID 
               << L" Threads: " << pe.cntThreads 
               << std::endl;


    while (Process32Next(snap, &pe)) {                 // keep listing if there's still next
    std::wcout
        << L"process name: " << pe.szExeFile
        << L" PID: " << pe.th32ProcessID
        << L" Threads: " << pe.cntThreads
        << std::endl;
    }

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        std::cout << "Process32Next failed.\n";
    }

    handle_closeing = CloseHandle(snap);

    return 0;
}
