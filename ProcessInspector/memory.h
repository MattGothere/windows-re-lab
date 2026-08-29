#pragma once

#include <iostream>
#include <Windows.h>

class Memory {
public:
	Memory(const wchar_t* appname);
	~Memory();

	DWORD getProcessID();
	uintptr_t getBaseAddress(const wchar_t* moduname);

	template<typename T>
	bool Read(uintptr_t address, T& value) {
		SIZE_T bytesRead = 0;

		return ReadProcessMemory(
			this->appHandle,
			reinterpret_cast<LPCVOID>(address),
			&value,
			sizeof(T),
			&bytesRead
		) && bytesRead == sizeof(T);
	}

	template<typename T>
	bool Write(uintptr_t address, const T& alter) {
		SIZE_T bytesWritten = 0;

		if (WriteProcessMemory(
			this->appHandle,
			reinterpret_cast<LPVOID>(address),
			&alter,
			sizeof(T),
			&bytesWritten
		)) {
			return bytesWritten == sizeof(T);
		}

		return false;
	}

private:
	DWORD PID = 0;
	HANDLE appHandle = nullptr;
};