#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include "atlstr.h"
#define bufSize 256
using namespace std;



void main(int argc, char *argv[]) {

	//LPCTSTR fname = TEXT("myFile.txt");
	if (argc < 3) {
		cout << "Incorrect count of argumens!";
		_getch();
		return;
	}

	TCHAR message[512];
	_tcscpy(message, A2T(argv[2]));


	LPCTSTR mapName = TEXT(argv[1]);
	LPCTSTR pBuf;
	HANDLE hMap;
	//HANDLE hFile;
	//TCHAR szMsg[] = message;

	hMap = CreateFileMapping(/*hFile*/INVALID_HANDLE_VALUE, NULL,/* PAGE_READONLY */PAGE_READWRITE, NULL, bufSize/*NULL*/, mapName);

	cout << "Try to create file map\n";

	if (hMap == NULL) {
		cout << "Fail to create map file: \"" << mapName << "\"\n";
		cout << "Error: " << GetLastError();
		_getch();
		return;
	}

	cout << "FileMapping finished successfuly\n";
	cout << "File map was created, access by name: \"" << mapName <<"\"\n";

	pBuf = (LPCTSTR) MapViewOfFile(hMap, /*FILE_MAP_READ*/FILE_MAP_ALL_ACCESS, NULL, NULL,/*bufSize*/NULL);

	cout << "Try to get virtual adress\n";

	if (pBuf == NULL) {
		cout << "Fail while getting adress\n";
		cout << "Error: " << GetLastError();
		_getch();
		return;
	}

	cout << "Getting virtual adress was success\n";
	
	CopyMemory((PVOID)pBuf, message, (_tcslen(message) * sizeof(TCHAR)));

	if (GetLastError() == 0) {
		cout << "CopyMemory function done well.\n";
	}
	else {
		cout << "Fail while writing message to map object\n";
		_getch();
		return;
	}


//	cout << GetFileSize(hMap, NULL);

	//FlushViewOfFile(hMap, GetFileSize(hMap, NULL));

	//CopyMemory((PVOID)buf, pBuf, (_tcslen(pBuf) * sizeof(TCHAR)));

	// output text in mapping file
	//cout << pBuf;

	cout << "Press any key to close map file\n";

	_getch();

	UnmapViewOfFile(pBuf);

	CloseHandle(hMap);

	cout << "End...";
	_getch();


}