#include <iostream>

#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <fileapi.h>
#include <cassert>
#include <cstdlib>

#include "communication.h"
int com_init(HANDLE handles[n_odrv], LPCSTR odrv_ports[n_odrv]) {

	DCB serialParams;
	COMMTIMEOUTS serialTimeouts;

	for (uint8_t i = 0; i < n_odrv; i++) {

		handles[i] = CreateFileA(odrv_ports[i],
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
		assert(handles[i] != INVALID_HANDLE_VALUE, "Unable to open serial line");

		GetCommState(handles[i], &serialParams);
		serialParams.BaudRate = 115200;
		serialParams.ByteSize = 8;
		serialParams.StopBits = ONESTOPBIT;
		serialParams.Parity = NOPARITY;
		SetCommState(handles[i], &serialParams);

		GetCommTimeouts(handles[i], &serialTimeouts);
		serialTimeouts.ReadIntervalTimeout = MAXDWORD;
		serialTimeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
		serialTimeouts.ReadTotalTimeoutConstant = 20; // 5 ms to respond after trying to read from the device
		serialTimeouts.WriteTotalTimeoutMultiplier = 0;
		serialTimeouts.WriteTotalTimeoutConstant = 0;
		SetCommTimeouts(handles[i], &serialTimeouts);
		std::cout << handles[i] << std::endl;
	}
	return 1;
}

int com_read_ln(HANDLE handle, char* c, int n_bytes_to_read) {
	LPDWORD n = 0;
	int r = ReadFile(handle, c, n_bytes_to_read, n, NULL);
	if (!r) {
		std::cout << "Failed to read line.\n" << std::endl;
	}
	return (int)n;
}

int com_write_ln(HANDLE handle, char c[]) {
	LPDWORD n = 0;
	int r = WriteFile(handle, c, strlen(c), n, NULL);
	if (!r) {
		std::cout << "Failed to write line.\n" << std::endl;
	}
	//FlushFileBuffers(handle);
	return (int)n;
}