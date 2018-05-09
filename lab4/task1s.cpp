#include <iostream>
#include <ws2tcpip.h>

#define BUFSIZE 1024

#pragma comment(lib, "ws2_32.lib")

int main() {

	// init winsock
	
	WSADATA wsData;

	WORD ver = MAKEWORD(2, 2);

	if (WSAStartup(ver, &wsData) != 0) {
		std::cout << "Fail to init Windows sockets\n";
		return -1;
	}

	// create socket

	std::cout << "Listening socket...\n";

	SOCKET listening = socket(AF_INET, SOCK_STREAM, NULL);

	if (listening == INVALID_SOCKET) {
		std::cout << "Cannot create listening socket!\n";
		return -1;
	}

	//bind the socket to an ip address and port
	
	sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(2000);
	sockAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr *)&sockAddr, sizeof(sockAddr));

	
	// tell the winsock  is for listening

	listen(listening, SOMAXCONN);

	// wait for conection

	sockaddr_in client;
	int clientSize = sizeof(client);

	std::cout << "Wait client...\n";
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Cannot create client socket\n";
		std::cout << "Eror: " << GetLastError();
		WSACleanup();
		return -1;
	}

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host,NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		std::cout << host << " connected on port " << service << "\n";
 	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << " connected on port " << htons(client.sin_port) << "\n";
	}

	//close listening sock
	
	closesocket(listening);


	// while loop: acept and echo message back to client
	
	char readBuf[BUFSIZE];
	char sendBuf[BUFSIZE];

	while (true) {
		ZeroMemory(readBuf, BUFSIZE);
		ZeroMemory(sendBuf, BUFSIZE);


		// Wait for client
		int bytesRecived = recv(clientSocket, readBuf, BUFSIZE, 0);

		if (bytesRecived == SOCKET_ERROR) {
			std::cout << "Erorr while reciving.\n";
			std::cout << "Erorr: " << GetLastError();
			break;
		}

		if (bytesRecived == 0) {
			std::cout << "Client disconnected\n";
			break;
		}

		std::cout << "Client >" << readBuf << "\n";
		//make message back

		std::cout << "> ";
		std::cin.getline(sendBuf, BUFSIZE);
		send(clientSocket, sendBuf, sizeof(sendBuf), 0);
	}

	//close socket
	closesocket(clientSocket);

	//shut donw winsock
	WSACleanup();

}