#include <windows.h> 
#include <iostream>
#include <string>
#include <conio.h>
#include <tchar.h>

#define szBuffer 255

int main() {

	char ReadBuffer[szBuffer] = { 0 };
	char WriteBuffer[szBuffer] = "Default message";

	DWORD dwBytesToWrite;
	DWORD dwBytesWritten = 0;

	DWORD dwBytesRead;

	HANDLE hNamedPipe;

	if (!WaitNamedPipe("\\\\.\\pipe\\my_pipe", NMPWAIT_USE_DEFAULT_WAIT)) {
		std::cout << "Server is unaccessible.\n";
		_getch();
		return -1;
	}

	hNamedPipe = CreateFile("\\\\.\\pipe\\my_pipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		std::cout << "Problem with create pipe\n";
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


//int main(int argc, char *argv[])
//{
//	if (argc < 2) {
//		printf("Incorrect count of arguments\n");
//		_getch();
//		return 0;
//	}
//
//
//	HANDLE hPipe;
//	char buffer[szBuffer];
//	DWORD dwRead;
//
//
//	std::string strPipename("\\\\.\\pipe\\");
//	strPipename += argv[1];
//
//	hPipe = CreateNamedPipe(TEXT(strPipename.c_str()), PIPE_ACCESS_DUPLEX,
//		PIPE_TYPE_MESSAGE,  
//		1,
//		szBuffer * 16,
//		szBuffer * 16,
//		NMPWAIT_USE_DEFAULT_WAIT,
//		NULL);
//
//	while (hPipe != INVALID_HANDLE_VALUE)
//	{
//		static int pr = 0;
//		if (!pr) {
//			printf("Server started!\n");
//			printf("Waiting for client...!\n");
//		}
//		pr = 1;
//			if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
//			{
//				std::cout << "Smb connected.\n";
//
//				while (ReadFile(hPipe, buffer, szBuffer - 1, &dwRead, NULL) != FALSE)
//				{
//					buffer[dwRead] = '\0';
//
//					std::cout << buffer << "\n";
//
//					if (buffer[dwRead - 1] == '%') {
//						break;
//					}
//				}
//			}
//
//		printf("Close pipe\n");
//		DisconnectNamedPipe(hPipe);
//	}
//
//	return 0;
//}


























//#include <windows.h> 
//#include <string>
//#include <iostream>
//#include <stdio.h>
//#include <conio.h>
//#include <tchar.h>
//
//#define BUFSIZE 512
//
//int _tmain(int argc, TCHAR *argv[])
//{
//	HANDLE hPipe;
//	TCHAR  chBuf[BUFSIZE];
//
//	std::string strPipename = "\\\\.\\pipe\\";
//	std::string message;
//
//	if (argc < 3) {
//		printf("Incorrect count of arguments\n");
//		_getch();
//		return 0;
//	}
//
//	strPipename += argv[1]; //open pip by this name 
//
//	message = argv[2];  // save message to send
//
//	// Try to open a named pipe; wait for it, if necessary. s
//	LPCSTR lpszPipename = TEXT(strPipename.c_str());
//	LPCSTR lpvMessage = TEXT(message.c_str());
//
//	DWORD dwWritten;
//
//
//	hPipe = CreateFile(TEXT(strPipename.c_str()),
//			GENERIC_READ | GENERIC_WRITE,
//			0,
//			NULL,
//			OPEN_EXISTING,
//			0,
//			NULL);
//		if (hPipe != INVALID_HANDLE_VALUE)
//		{
//			WriteFile(hPipe,
//				message.c_str(),
//				message.length(),  
//				&dwWritten,
//				NULL);
//
//			CloseHandle(hPipe);
//		}
//
//		return (0);
//	}
