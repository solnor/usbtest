#pragma once
//#ifndef COMMUNICATION_H
//#define COMMUNICATION_H
#include <Windows.h>
constexpr int n_odrv = 4;
int com_init(HANDLE handles[n_odrv], LPCSTR odrv_ports[n_odrv]);
int com_read_ln(HANDLE handle, char* c, int n_bytes_to_read);
int com_write_ln(HANDLE handle, char c[]);

//#endif