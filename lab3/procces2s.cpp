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

	HANDLE hNamedPipe = CreateNamedPipe(
		TEXT("\\\\.\\pipe\\my_pipe"),  // назва каналу 
		PIPE_ACCESS_DUPLEX,  // відкриття в дуплексному режиму (READONLY | WRITEONLY)
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,  // передавання повідмолень як повідомлення а не побайтно
		PIPE_UNLIMITED_INSTANCES, // система сама визначає скільки можна створити екзмеплярів залежно від ресурсів
		szBuffer, // розмір буферу виходу	
		szBuffer, // розмір буферу входу
		NMPWAIT_USE_DEFAULT_WAIT, // дефолтне чекання
		NULL); // атрибути безпеки

	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		std::cout << "Problem with create pipe\n";
		std::cout << "Error: " << GetLastError();
		_getch();
		return -1;
	}

	bool exit = false;

	int clientCount = 0;

	std::cout << "Server started\n";

	while (!exit) {

		std::cout << "Wait for client...\n";

		ConnectNamedPipe(hNamedPipe, NULL);

		std::cout << "Client #" << ++clientCount << " connected\n";

		while (ReadFile(hNamedPipe, ReadBuffer, szBuffer - 1, &dwBytesRead, NULL)) {

			if (dwBytesRead > 0 && dwBytesRead <= szBuffer - 1)
			{
				ReadBuffer[dwBytesRead] = '\0'; 

				std::cout << "Client> "<<ReadBuffer << "\n";

				if (strcmp(ReadBuffer, "Server close") == 0) {
					exit = true;
					break;
				}
			}

			std::cout << "Server> ";
			std::cin.getline(WriteBuffer, szBuffer);

			/*if (strcmp(WriteBuffer, "Exit chat") == 0) {
				DisconnectNamedPipe(hNamedPipe);
			}


			if (strcmp(WriteBuffer, "Close server") == 0) {
				DisconnectNamedPipe(hNamedPipe);
				CloseHandle(hNamedPipe);
				return 1;
			}*/


			dwBytesToWrite = (DWORD)strlen(WriteBuffer);

			if (!WriteFile(hNamedPipe, WriteBuffer, dwBytesToWrite, &dwBytesWritten, NULL)) {
				std::cout << "Fail while writing to pipe\n";
				std::cout << "Error: " << GetLastError();
			}
		}

		DisconnectNamedPipe(hNamedPipe);
		std::cout << "Connection closed.\n";
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