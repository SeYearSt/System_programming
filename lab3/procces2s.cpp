#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#define szBuf 1024

int main(void)
{
	HANDLE hPipe;
	char buffer[1024];
	DWORD dwRead;


	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,  
		1,
		szBuf * 16,
		szBuf * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	while (hPipe != INVALID_HANDLE_VALUE)
	{
		static int pr = 0;
		if (!pr) {
			printf("Server started!\n");
			printf("Wait fo Message!\n");
		}
		pr = 1;
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				buffer[dwRead] = '\0';

				printf("%s", buffer);

				if (buffer[0] == '!') {
					break;
				}
			}
		}
		printf("Close pipe\n");
		DisconnectNamedPipe(hPipe);
	}

	return 0;
}