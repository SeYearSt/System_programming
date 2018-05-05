#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#define szBuf 512

int main(void)
{
	HANDLE hPipe;
	DWORD dwWritten;
	char message[szBuf];

	hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		bool exit = false;
		while (!exit) {
		
			printf("Enter message: ");

			fgets(message, szBuf,stdin);

			WriteFile(hPipe,
				message,
				strlen(message) + 1,
				&dwWritten,
				NULL);
			
			if (message[0] == '!') {
				exit = true;
			}
		}
		CloseHandle(hPipe);
	}
	else {
		printf("absent pipe!\n");
	}

	_getch();
	return (0);
}