#include<windows.h>
#include<iostream>
#include<conio.h>

#define INIT_SEM_COUNT 2
#define MAX_SEM_COUNT 2

using namespace std;

void main()
{


	// ---------------------- MUTEX -----------------------------
	HANDLE hMutex = CreateMutex(NULL, TRUE, "process1_mutex");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout << "Mutex exists!" << endl;
		system("pause");
		//ReleaseMutex(hMutex);
		CloseHandle(hMutex);
		return;
	}
	else if (hMutex)
	{
		cout << "Mutex created!" << endl;
	}
	else cout << "Failed to create mutex - Error #" << GetLastError() << endl;

	
	// ---------------------- SEMAPHORE -----------------------------
	HANDLE hSemaphore = CreateSemaphore(NULL, INIT_SEM_COUNT, MAX_SEM_COUNT, "process1_semaphore");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		cout << "Semaphore exists!" << endl;
		system("pause");
		//ReleaseSemaphore(hSemaphore,1,NULL);
		CloseHandle(hSemaphore);
		return;
	}
	else if (hSemaphore) {
		cout << "Semaphore created\n";
	}
	else cout << "Failed to create Semaphore - Error #" << GetLastError() << endl;

	//---------------------- TIMER -----------------------------
	HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, "process1_timer");

	LARGE_INTEGER dueTime;
	DWORD Count = 0;
	dueTime.QuadPart = -100000000;

	if (GetLastError() == ERROR_ALREADY_EXISTS) {

		cout << "Timer is exist\n";
		system("pause");
		CloseHandle(hTimer);
		return;
	}
	else if (hTimer)
	{

		cout << "Timer created!" << endl;
		cout << "Timer is ticking!" << endl;

		SetWaitableTimer(hTimer, &dueTime, 1000, NULL, &Count, TRUE);

		WaitForSingleObject(hTimer, INFINITE);

		cout << "Timer finished ticking." << endl;
	}
	else cout << "Failed to create timer - Error #" << GetLastError() << endl;

	
	ReleaseMutex(hMutex);
	ReleaseSemaphore(hSemaphore, MAX_SEM_COUNT, NULL);

	cout << "Press any key to create new process" << endl;
	system("pause");


	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	char cmdLn[] = "process4";

	if (CreateProcess(NULL, cmdLn, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	else
	{
		cout << "Error: " << GetLastError();
	}

	/*STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	char cmdLn[] = "process3\0";

	if (CreateProcess("childProcess", cmdLn, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		cout << "Proccess create success\n";
	}
	else {
		cout << "Fail to create new procces\n";
		cout << "Error: " << GetLastError() << endl;
	}*/

	cout << "Press any key to close handles mutex,semaphore,timer..." << endl;
	system("pause");

	CloseHandle(hMutex);
	CloseHandle(hTimer);
	CloseHandle(hSemaphore);

}