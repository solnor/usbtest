#include "communication.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <fileapi.h>
#include <cassert>
#include <cstdlib>

#include <sstream>
#include <vector>
#include <iterator>

#include <chrono>


HANDLE handles[n_odrv];
constexpr LPCSTR odrv0_port = "\\\\.\\COM4";
constexpr LPCSTR odrv1_port = "\\\\.\\COM5";
constexpr LPCSTR odrv2_port = "\\\\.\\COM6";
constexpr LPCSTR odrv3_port = "\\\\.\\COM7";
LPCSTR odrv_ports[n_odrv] = { odrv0_port, odrv1_port, odrv2_port, odrv3_port };

// https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template <typename Out>
void split(const std::string& s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}


int main() {
	//std::string port = "\\\\.\\COM1";
	//LPCSTR port = "\\\\.\\COM4";
	//HANDLE handle = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//assert(handle != INVALID_HANDLE_VALUE, "Unable to open serial line");

	//DCB serialParams;
	//GetCommState(handle, &serialParams);
	//serialParams.BaudRate = 115200;
	//serialParams.ByteSize = 8;
	//serialParams.StopBits = ONESTOPBIT;
	//serialParams.Parity = NOPARITY;
	//SetCommState(handle, &serialParams);

	//COMMTIMEOUTS serialTimeouts;
	//GetCommTimeouts(handle, &serialTimeouts);
	//serialTimeouts.ReadIntervalTimeout = MAXDWORD;
	//serialTimeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
	//serialTimeouts.ReadTotalTimeoutConstant = 100; // 100 ms to respond after trying to read from the device
	//serialTimeouts.WriteTotalTimeoutMultiplier = 0;
	//serialTimeouts.WriteTotalTimeoutConstant = 0;

	//SetCommTimeouts(handle, &serialTimeouts);
	int init_suc = com_init(handles, odrv_ports);
	char c[] = "f 0\n";
	//int rw = com_write_ln(handles[0], c);
	//LPDWORD n = 0;
	//FlushFileBuffers(handles[0]);
	//int rg = WriteFile(handles[0], &cw, strlen(cw), n, NULL);
	//std::cout << "write_ln n: " << rw << std::endl;
	//std::cout << handles[0] << std::endl;
	//FlushFileBuffers(handles[0]);
	//char res[] = "12.859047 0.002598";
	//char res[] = "00.000000 0.000000\n";
	char res[] = "רררררררררררררררררררררררררררררררררררר";
	//char res[] = "רררררררררררררררררררררררררררררררררררר";
	//char res[] = "רררררררררררררררררררררררררררררררררררר";
	struct results {
		char res[25];
	};

	results result0;
	results result1;
	results result2;
	results result3;
	std::vector <results> all_results;
	all_results.push_back(result0);
	all_results.push_back(result1);
	all_results.push_back(result2);
	all_results.push_back(result3);
	
	//int rr = ReadFile(handles[0], res, strlen(res), n, NULL);
	/*int rr = com_read_ln(handles[0], res, strlen(res));
	int size = strlen(res);
	
	FlushFileBuffers(handles[0]);*/
	int size = 21;
	//std::cout << "Response:" << res << std::endl;
	//int r = 0;
	
	//auto now = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start);
	//char* csplit;
	//std::vector<std::string> csplit;
	int iter = 0;
	char kk = '\n';
	while (iter < 10) {
		auto start = std::chrono::high_resolution_clock::now();
		for (uint8_t i = 0; i < 4; i++) {
			com_write_ln(handles[i], c);
			//Sleep(5);
			FlushFileBuffers(handles[i]);
			//std::cout << "Hey" << std::endl;
			uint8_t j = 0;
			while (1) {
				//printf("nlhex: %x\n", kk);
				com_read_ln(handles[i], &all_results[i].res[j], 1);
				//std::cout << (all_results[i].res[j] == 0x0a) << std::endl;
				//std::cout << "while: " << all_results[i].res[j] << std::endl;
				//printf("Hex: %x\n", all_results[i].res[j]);
				
				if (all_results[i].res[j] == 0x0a) {
					break;
				}

				j++;
			}
			
			//printf("Response from odrive%u: ", i);
			//std::string resS = all_results[i].res;
			//std::cout << resS << std::endl;
			//std::cout << resS.substr(0, resS.find("\n")) << std::endl;
			//csplit = strtok(res, " \n");
			//std::vector<std::string> csplit = split(resS, "\n");
			//std::cout << resS.find("\n") << std::endl;
			//std::cout << std::stof(resS.substr(0, resS.find("ר"))) << std::endl;
			//std::cout << std::stof(resS.substr(resS.find(" ")+1,10)) << std::endl;
			/*while (csplit != NULL) {
				std::cout << csplit << std::endl;
				csplit = strtok(NULL, " ");
			}*/
			//std::cout << atof(res) << std::endl;
			//std::cout << atof(res) << std::endl;
			
		}
		//Sleep(1);
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
		std::cout << "duration: " << duration.count() << std::endl;
		iter++;
	}

	system("pause");
	return 0;




	////LPDWORD n = 0;
	//char c[] = "f 0\n";
	////std::string c = "f 0\n";
	////LPCVOID c = "f 0\n";
	////std::cout << strlen(c) << std::endl;
	//auto start = std::chrono::high_resolution_clock::now();
	//int r = WriteFile(handles[0], &c, strlen(c), n, NULL);
	////printf("WriteFile n: %i\n", n);
	////printf("WriteFile r : %i\n", r);
	//r = FlushFileBuffers(handles[0]);
	////printf("FlushFileBuffers r : %i\n", r);
	////std::string res = "f 0\n";
	////char res[] = "12.859047 0.002598";
	////std::cout << "Size: " << strlen(res) << std::endl;
	//r = ReadFile(handles[0], res, strlen(res), n, NULL);
	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//std::cout << "duration: " << duration.count() << std::endl;
	//printf("ReadFile n: %i\n", n);
	//printf("ReadFile r : %i\n", r);
	//DWORD nRead;
	////r = ReadFile(handle, buff2, 40, &nRead, NULL);

	//// Timeouts, se
	//	// https ://learn.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-commtimeouts
	////std::cout << std::isprint(c) << std::endl;
	//std::cout << "Response:" << res << std::endl;
	////std::cout << static_cast<unsigned>(c) << std::endl;
	////std::cout << "Hello World!" << std::endl;
	//system("pause");
	//return 0;
}