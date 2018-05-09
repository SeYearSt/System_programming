#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<winsock2.h>
#include<stdio.h>
#include<conio.h>

#pragma comment(lib,"ws2_32.lib")

#define SERVER "127.0.0.1" 
#define BUFLEN 512  
#define PORT 8888  

int main(void)
{
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];


	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", GetLastError());
		_getch();
		return -1;
	}

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", GetLastError());
		getch();
		return -1;
	}

	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	while (true)
	{
		printf("Enter message : ");
		fgets(message, BUFLEN, stdin);


		if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", GetLastError());
			getch();
			return -1;
		}

		ZeroMemory(buf, BUFLEN);
		

		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", GetLastError());
			getch();
			return -1;
		}

		puts(buf);
	}

	closesocket(s);
	WSACleanup();

	return 0;
}