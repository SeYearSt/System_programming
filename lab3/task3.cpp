#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <stdio.h> 
#include <string.h>
#include <strsafe.h>

#define BUFSIZE 512

DWORD WINAPI InstanceThread(LPVOID);
VOID GetAnswerToRequest(char *, char *, LPDWORD);

int main(int argc, char * argv[])
{
	BOOL   fConnected = FALSE;
	DWORD  dwThreadId = 0;
	HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
	
	char pipeName[BUFSIZE] = "\\\\.\\pipe\\";

	if (argc > 1) {
		strcat(pipeName, argv[1]);
	}
	else {
		strcat(pipeName, "my_pipe");
	}

	for (;;)
	{
		printf("Pipe Server: Main thread is waiting client connection.\n");

		hPipe = CreateNamedPipe(
			pipeName,           
			PIPE_ACCESS_DUPLEX,     
			PIPE_TYPE_MESSAGE |     
			PIPE_READMODE_MESSAGE |  
			PIPE_WAIT,                
			PIPE_UNLIMITED_INSTANCES,  
			BUFSIZE,                  
			BUFSIZE,                  
			0,                        
			NULL);                    

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			printf("CreateNamedPipe failed, Eror: %d.\n", GetLastError());
			return -1;
		}

		printf("Pipe Handle is: %d\n", hThread);
	
		if (ConnectNamedPipe(hPipe, NULL))
		{
			printf("Client connected, creating a processing thread.\n");
 
			hThread = CreateThread(
				NULL,              
				0,                  
				InstanceThread,    
				(LPVOID)hPipe,    
				0,                  
				&dwThreadId);       

			printf("Thread id: %d\n", dwThreadId);

			if (hThread == NULL)
			{
				printf("CreateThread failed, Eror: %d.\n", GetLastError());
				return -1;
			}

			else CloseHandle(hThread);

		}
		else
			CloseHandle(hPipe);
	}

	return 0;
}

DWORD WINAPI InstanceThread(LPVOID lpvParam){

	char request [BUFSIZE];
	char reply[BUFSIZE];

	DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
	BOOL fSuccess = FALSE;
	HANDLE hPipe = NULL;

	if (lpvParam == NULL)
	{
		printf("\nERROR - Pipe Server Failure:\n");
		printf("   InstanceThread got an unexpected NULL value in lpvParam.\n");
		return (DWORD)-1;
	}

	printf("InstanceThread created, receiving and processing messages.\n");

	hPipe = (HANDLE)lpvParam;

	while (1)
	{
		fSuccess = ReadFile(
			hPipe,        
			request,   
			BUFSIZE * sizeof(char),
			&cbBytesRead, 
			NULL);       

		request[cbBytesRead] = '\0';

		if (!fSuccess || cbBytesRead == 0)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE)
			{
				printf("InstanceThread: client disconnected.\n");
			}
			else
			{
				printf("InstanceThread ReadFile failed, Eror: %d.\n");
			}
			break;
		}

		GetAnswerToRequest(request, reply, &cbReplyBytes);

		fSuccess = WriteFile(
			hPipe, 
			reply,     
			cbReplyBytes, 
			&cbWritten,  
			NULL);      

		if (!fSuccess || cbReplyBytes != cbWritten)
		{
			printf("InstanceThread WriteFile failed, EROR: %d.\n", GetLastError());
			break;
		}
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	printf("InstanceThread exitting.\n");
	return 1;
}

VOID GetAnswerToRequest(char* request,
	char * reply,
	LPDWORD pchBytes)
{

	printf("Client`s request: %s\n", request);

	printf("Checking client requst...\n");
	Sleep(1000);

	// Check the outgoing message to make sure it's not too long for the buffer.
	if (FAILED(StringCchCopy(reply, BUFSIZE, "Default message from server")))
	{
		*pchBytes = 0;
		reply[0] = 0;
		printf("String copy failed, escape without outgoing message.\n");
		return;
	}
	*pchBytes = (lstrlen(reply) + 1) * sizeof(char);
}

