#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main()
{
    HANDLE Procsnap; // create a handle, helping us to access proccess information
    HANDLE Modusnap;

    Procsnap = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS,             // include all process in the system
        0                               // current process
    );

    if (Procsnap == INVALID_HANDLE_VALUE) {
        std::cout << "failed to create Process snapshot. \n";
        return 0;
    }

    PROCESSENTRY32 pe;                    // open up a "sheet" to let functions fill in   
    pe.dwSize = sizeof(pe);    // initialize dwsize

    bool firstProc;
    firstProc = Process32First(                 // fill up the very first sheet
        Procsnap,
        &pe
    );

    if (!firstProc) {
        std::cout << "failed to copy process list. \n";
        CloseHandle(Procsnap);            // close the handle if failed
        return 0;
    }

    // ***全部改用寬字元串流***
    std::wcout << L"process name: " << pe.szExeFile
        << L" PID: " << pe.th32ProcessID
        << L" Threads: " << pe.cntThreads
        << std::endl;


    while (Process32Next(Procsnap, &pe)) {                 // keep listing if there's still next
        std::wcout
            << L"process name: " << pe.szExeFile
            << L" PID: " << pe.th32ProcessID
            << L" Threads: " << pe.cntThreads
            << std::endl;
    }

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        std::cout << "Process32Next failed.\n";
    }

    CloseHandle(Procsnap);

    return 0;
}
