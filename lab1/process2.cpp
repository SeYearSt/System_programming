#include<windows.h>
#include<iostream>
#include <conio.h>

#define INIT_SEM_COUNT 2
#define MAX_SEM_COUNT 2

using namespace std;

void main()
{
	// ---------------------- MUTEX -----------------------------
	HANDLE hMutex = CreateMutex(NULL, FALSE, "process1_mutex");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout << "Mutex exists!" << endl;
		cout << "Wait for Mutex..." << endl;
		WaitForSingleObject(hMutex, INFINITE);
		cout << "Mutex captured!" << endl;
	}
	else if (hMutex)
	{
		cout << "Mutex created!" << endl;
		system("pause");
		CloseHandle(hMutex);
		return;
	}
	else cout << "Failed to create mutex - Error #" << GetLastError() << endl;

	// ---------------------- SEMAPHORE -----------------------------
	HANDLE hSemaphore = CreateSemaphore(NULL, INIT_SEM_COUNT, MAX_SEM_COUNT, "process1_semaphore");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		cout << "Semaphore exists!" << endl;
		cout << "Wait for Semaphore..." << endl;
		WaitForSingleObject(hSemaphore, INFINITE);
		cout << "Semaphore captured!" << endl;		
	}
	else if (hSemaphore) {
		cout << "Semaphore created\n";
		system("pause");
		CloseHandle(hSemaphore);
		return;
	}
	else cout << "Failed to create Semaphore - Error #" << GetLastError() << endl;
	
	//---------------------- TIMER -----------------------------
	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, "process1_timer");

	LARGE_INTEGER dueTime;
	DWORD Count = 0;
	dueTime.QuadPart = -100000000;

	if (GetLastError() == ERROR_ALREADY_EXISTS) {

		cout << "Wait for timer..." << endl;
		WaitForSingleObject(hTimer, INFINITE);
		cout << "Timer is captured!\n";

		cout << "Timer is ticking" << endl;
		SetWaitableTimer(hTimer, &dueTime, 1000, NULL, &Count, TRUE);

		WaitForSingleObject(hTimer, INFINITE);

		cout << "Timer finished ticking." << endl;
		
		system("pause");
	}
	else if (hTimer)
	{
		cout << "Timer created!" << endl;
		system("pause");
		CloseHandle(hTimer);
		return;
	}
	else cout << "Failed to create timer - Error #" << GetLastError() << endl;

	CloseHandle(hMutex);
	CloseHandle(hSemaphore);
	CloseHandle(hTimer);

}