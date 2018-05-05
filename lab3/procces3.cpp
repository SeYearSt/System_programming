#include <windows.h>
#include <stdio.h>
#include <conio.h>
#define MAX_COUNT 2 
#define szBuf 512
#define sName "procces3Semaphore"
#define mpName "MapFileObject.txt"
//#define message "Hello"

HANDLE hSemaphore = CreateSemaphore(NULL,MAX_COUNT,MAX_COUNT,sName);

void main() {

	

	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		printf("Semaphore already exist!\n");

		printf("Try to capture semaphore!\n");
		
		WaitForSingleObject(hSemaphore, INFINITE);

		printf("Semaphore captured!\n");

		HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,mpName);

		if (hMap == NULL) {
			printf("Fail while getting mappedFile \n");
			printf("Error: %d", GetLastError());
			_getch();
			return;
		}

		LPSTR pMappedFile = (LPSTR)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, NULL);

		if (pMappedFile == NULL) {
			printf("Fail while getting mappedFile adress\n");
			printf("Error: %d", GetLastError());
			_getch();
			return;
		}

		printf("Message: %s", pMappedFile);


		printf("Pres any key to finish procces\n");
		_getch();

	}
	else {

		char message[255];

		printf("Enter message: ");
		fgets(message, 255, stdin);


		HANDLE hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, NULL, szBuf, mpName);
	
		printf("Try to create file map\n");

		if (hMap == NULL) {
			printf("Fail to create map objects!");
			_getch();
			return;
		}

		printf("FileMapping finished successfuly\n");
		printf("File map was created, access by name: \"%s\"\n", mpName);


		printf("Try to get virtual adress\n");

		LPSTR pMappedFile = (LPSTR)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, NULL);

		if (pMappedFile == NULL) {
			printf("Fail while getting adress\n");
			printf("Error: %d",GetLastError());
			_getch();
			return;
		}

		printf("Getting virtual adress was success\n");
		
		LPSTR pMappedFileTmp = pMappedFile;

		if (pMappedFile == NULL) {
			printf("Fail to get adrees map objects!");
			_getch();
			return;
		}

		printf("Try write in map\n");

		for (int i = 0; i < strlen(message); i++)
		{
			*pMappedFileTmp = (CHAR)message[i];
			pMappedFileTmp++;
		}
		
		printf("Try is finished\n");

	


		printf("Semaphore created!\n");

		STARTUPINFO si = { sizeof(si) };

		PROCESS_INFORMATION pi;
		char cmdLn[] = "procces3";

		printf("Press any key to creat 2 new proccess!\n");
		_getch();

		for (int i = 0; i < 2; ++i) {
			if (CreateProcess(NULL, cmdLn, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
			{
				printf("Procces created with pid: %d\n", pi.hProcess);

			}
			else
			{
				printf("Error: %d\n", GetLastError());
				_getch();
			}
		}
		
		printf("Press any key to close procces!\n");


		_getch();


		UnmapViewOfFile(pMappedFile);
		CloseHandle(hMap);

	}
}