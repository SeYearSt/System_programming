#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<winsock2.h>
#include<stdio.h>
#include <conio.h>

#pragma comment(lib,"ws2_32.lib") 

#define BUFLEN 512 
#define PORT 8888  

int main()
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	slen = sizeof(si_other);

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", GetLastError());
		_getch();
		return -1;
	}

	s = socket(AF_INET, SOCK_DGRAM, 0);

	if (s == INVALID_SOCKET){
		printf("Could not create socket : %d", GetLastError());
	}

	printf("Socket created.\n");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", GetLastError());
		_getch();
		return -1;
	}
	puts("Bind done");

	while (1)
	{
		printf("Waiting for data...");
		fflush(stdout);

		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			_getch();
			return -1;
		}


		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n", buf);

	
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			_getch();
			return -1;
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}