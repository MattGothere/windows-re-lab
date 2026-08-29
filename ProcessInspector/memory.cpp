#include "memory.h"

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

Memory::Memory(const wchar_t* appname) {
	this->appHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (appHandle == INVALID_HANDLE_VALUE) {
		std::wcout << L"failed to create memory object \n";
		this->appHandle = nullptr;
		return;
	}

	PROCESSENTRY32 pentry;
	pentry.dwSize = sizeof(pentry);

	bool found = FALSE;

	if (Process32First(this->appHandle, &pentry)) {
		if (wcscmp(appname, pentry.szExeFile) == 0) {
			this->PID = pentry.th32ProcessID;
			found = TRUE;
		}
	}
	else {
		std::wcout << L"failed to copy first process info \n";
		CloseHandle(this->appHandle);
		this->appHandle = nullptr;
		return;
	}

	while (!found && Process32Next(this->appHandle, &pentry)) {
		if (wcscmp(appname, pentry.szExeFile) == 0) {
			this->PID = pentry.th32ProcessID;
			found = true;
		}
	}
	if (!found) {
		std::wcout << L"couldn't find process\n";

		CloseHandle(this->appHandle);
		this->appHandle = nullptr;
		return;
	}
	// openprocess

	this->appHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->PID);
	if (!this->appHandle) {
		std::wcout << L"failed to openprocess" << std::endl;
		this->appHandle = nullptr;
		return;
	}
}

Memory::~Memory() {
	if (this->appHandle != nullptr) {
		CloseHandle(this->appHandle);
	}
}

DWORD Memory::getProcessID() {
	return this->PID;
}

uintptr_t Memory::getBaseAddress(const wchar_t* moduname) {

	if (this->PID == 0) {
		return 0;
	}

	HANDLE moduleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->PID);
	if (moduleSnapshot == INVALID_HANDLE_VALUE) {
		std::wcout << L"failed to create module snapshot \n";
		return 0;
	}

	MODULEENTRY32 mentry;
	mentry.dwSize = sizeof(mentry);

	bool found = FALSE;

	if (Module32First(moduleSnapshot, &mentry)) {
		if (wcscmp(moduname, mentry.szModule) == 0) {
			uintptr_t result = reinterpret_cast<uintptr_t>(mentry.modBaseAddr);
			found = TRUE;
			CloseHandle(moduleSnapshot);
			return result;
		}
	}
	else {
		std::wcout << L"failed to copy module info \n";
		CloseHandle(moduleSnapshot);
		return 0;
	}

	while (!found && Module32Next(moduleSnapshot, &mentry)) {
		if (wcscmp(moduname, mentry.szModule) == 0) {
			uintptr_t result = reinterpret_cast<uintptr_t>(mentry.modBaseAddr);
			found = TRUE;
			CloseHandle(moduleSnapshot);
			return result;
		}
	}
	if (!found) {
		std::wcout << L"couldn't find module \n";
		CloseHandle(moduleSnapshot);
		return 0;
	}
}