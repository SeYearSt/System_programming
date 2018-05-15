#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <iostream>
#include <string>
#include <conio.h>
#include <tchar.h>

#define szBuffer 512

int main(int argc, char * argv[]) {

	char ReadBuffer[szBuffer] = { 0 };
	char WriteBuffer[szBuffer] = "Default message";
	char pipName[] = "";


	char pipeName[szBuffer] = "\\\\.\\pipe\\";

	if (argc >= 2) {
		strcat(pipeName, argv[1]);
	}
	else {
		strcat(pipeName, "my_pipe");
	}


	DWORD dwBytesToWrite;
	DWORD dwBytesWritten = 0;

	DWORD dwBytesRead;

	HANDLE hNamedPipe;

	if (!WaitNamedPipe(pipeName, NMPWAIT_USE_DEFAULT_WAIT)) {
		std::cout << "Server is unaccessible.\n";
		_getch();
		return -1;
	}

	hNamedPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		std::cout << "Problem with creating pipe\n";
		std::cout << "Error: " << GetLastError();
		_getch();
		return -1;
	}

	while (true) {

			std::cout << "Client> ";
			std::cin.getline(WriteBuffer, szBuffer);

			if (strcmp(WriteBuffer,"Close connection") == 0) {
				break;
			}

			dwBytesToWrite = (DWORD)strlen(WriteBuffer);

			if (!WriteFile(hNamedPipe, WriteBuffer, dwBytesToWrite, &dwBytesWritten, NULL)) {
				std::cout << "Fail while writing to pipe\n";
				std::cout << "Error: " << GetLastError();
			}

			if (strcmp(WriteBuffer, "Server close") == 0) {
				break;
			}

			ReadFile(hNamedPipe, ReadBuffer, szBuffer - 1, &dwBytesRead, NULL);

			ReadBuffer[dwBytesRead] = '\0';
			std::cout << "Server> " << ReadBuffer << "\n";
		}

	CloseHandle(hNamedPipe);

	std::cout << "Press any key to close application\n";
	_getch();
	return 0;
}
