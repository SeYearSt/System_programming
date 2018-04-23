#include <windows.h>
#include <iostream>
using namespace std;

void main() {
	DWORD pid = GetCurrentProcessId();

	HANDLE hMutex = CreateMutex(NULL,true,"MutexProcessExist");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout << "Process already started\n";
		system("pause");
		return;
	}
	else
	{
		cout << "Process "<< pid << " Started\n";

		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		char cmdLn[] = "process4";

		if (CreateProcess(NULL, cmdLn, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			cout << "Process: " << pid << "-->" << pi.dwProcessId << endl;
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
		}
		else
		{
			cout << "Process " << pid << "Error: " << GetLastError();
		}
	}

	system("pause");
}