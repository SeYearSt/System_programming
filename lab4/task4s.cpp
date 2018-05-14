//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <conio.h>

using namespace std;

#pragma comment (lib, "ws2_32.lib")

#define BUFFSIZE 512
#define PORT 8888


int Respond(SOCKET sock, char* buffer, int& size);

DWORD WINAPI serverFunc(LPVOID param);

int main() {

	DWORD wVersion;
	WSADATA wsaDATA;
	wVersion = MAKEWORD(2, 2);

	cout << "Try to initialize winsock\n";

	if (WSAStartup(wVersion, &wsaDATA) != 0) {
		cout << "Cannot use winsock lib.\n";
		cout << "Error: " << GetLastError() << endl;
		_getch();
		return -1;
	}

	cout << "Winsock`s initializing finished\n";

	cout << "Creating listening socket\n";

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	cout << "Listening socket created successfully\n";

	sockaddr_in sinAddr;

	sinAddr.sin_family = AF_INET;
	sinAddr.sin_port = htons(PORT);
	sinAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	cout << "Try to bind listening socket\n";

	if (bind(listening, (sockaddr*)&sinAddr, sizeof(sinAddr)) == SOCKET_ERROR) {
		cout << "Cannot bind listening socket\n";
		cout << "Error: " << GetLastError() << endl;
		_getch();
		return -1;
	}


	cout << "Try to put listening socket in listen mode\n";

	if (listen(listening, SOMAXCONN) == SOCKET_ERROR) {
		cout << "Listening socket can`t be putted in listen mode\n";
		cout << "Error: " << GetLastError() << endl;
		closesocket(listening);
		WSACleanup();
		_getch();
		return -1;
	}

	cout << "Listening socket putted successfully\n";


	
	while (true) {
		char buff[BUFFSIZE];

		cout << "Wait for Client\n";

		SOCKET sock = accept(listening, NULL, NULL);


		if (sock == INVALID_SOCKET) {
			cout << "Cannot create socket for sending/receiving messages\n";
			cout << "Error: " << GetLastError() << endl;
			_getch();
			return -1;
		}
		else {
			cout << "Try to create new thread\n";

			HANDLE serverThread = CreateThread(NULL, 0, serverFunc, &sock, NULL, 0);
			if (serverThread == NULL)
			{
				cout << "Can't create server thread" << endl;
			}
			CloseHandle(serverThread);			
		}
	}
	
	cout << "Listening socked binded successfully\n";


	WSACleanup();

	cout << "Press any key to close application\n";
	_getch();

	return 1;
}

int Respond(SOCKET sock, char* buffer, int &size) {
	buffer[size] = '\0';
	cout << buffer << endl;

	if (send(sock, buffer, size, 0) == SOCKET_ERROR) {
		*buffer = '\0';
		size = 0;
		return -1;
	}

}

DWORD WINAPI serverFunc(LPVOID param) {

	char buff[BUFFSIZE];

	SOCKET sock = *(SOCKET *)param;

	int iResult;
	do {
		iResult = recv(sock, buff, BUFFSIZE - 1, 0);
		if (iResult > 0) {
			Respond(sock, buff, iResult);
			cout << "Bytes received: " << iResult << endl;

		}
		else if (iResult == 0)
			cout << "Connection closed\n";
		else
			cout << "recv failed with Eror: " << WSAGetLastError() << endl;

	} while (iResult > 0);

	closesocket(sock);

	return (DWORD)1;
}