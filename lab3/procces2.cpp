#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#define bufSize 256
using namespace std;


void main(int argc, char *argv[]) {

	if (argc < 2) {
		cout << "Incorrect count of argumens!";
		_getch();
		return;
	}


	LPCTSTR mapName = TEXT(argv[1]);
	LPCTSTR pBuf;
	HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, mapName);

	cout << "Try to open file map\n";

	if (hMap == NULL) {
		cout << "Fail while opening map file: \"" << mapName << "\"\n";
		cout << "Cannnot open map file object\n";
		cout << "Error: " << GetLastError();
		_getch();
		return;
	}

	cout << "FileMapping finished successfuly\n";
	cout << "File map was created, access by name: \"" << mapName << "\"\n";

	pBuf = (LPCTSTR)MapViewOfFile(hMap, /*FILE_MAP_READ*/FILE_MAP_ALL_ACCESS, NULL, NULL,bufSize);

	cout << "Try to get virtual adress\n";

	if (pBuf == NULL) {
		cout << "Fail while getting adress\n";
		cout << "Error: " << GetLastError();
		_getch();
		return;
	}

	cout << "Getting virtual adress was success\n";

	//MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);

	cout << "Message from first procces: " << pBuf << endl;

	UnmapViewOfFile(pBuf);

	CloseHandle(hMap);

	cout << "End...";
	_getch();


}