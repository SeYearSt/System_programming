#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define N 1000

HANDLE hEvent;

DWORD WINAPI thread1Func(LPVOID);
DWORD WINAPI thread2Func(LPVOID);

void main() {

	char choose;

	printf("Choose between 'm'- manual-reset, 'a' - auto-reset event object\n");

	scanf("%c", &choose);

	switch (choose)
	{
	case 'm': {
		hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		break;
	}
	case 'a':
	{
		hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
		break;
	}
	default: {
		printf("incorrect choose\n");
		return;
	}
	}


	HANDLE hThread1 = CreateThread(NULL, 0, thread1Func, NULL, NULL, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, thread2Func, NULL, NULL, NULL);

	WaitForSingleObject(hThread1, INFINITE);
	printf("Thread 1 finished.\n");

	WaitForSingleObject(hThread2, INFINITE);
	printf("Thread 2 finished.\n");

	printf("Press any key to close program.\n");

	_getch();

	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hEvent);

}

DWORD WINAPI thread1Func(LPVOID) {
	printf("Thread id:%d started\n", GetCurrentThreadId());

	printf("Thread id:%d wait for event object\n", GetCurrentThreadId());

	WaitForSingleObject(hEvent, INFINITE);

	printf("Thread id:%d got event object\n", GetCurrentThreadId());

	for (int i = 1; i <= N; ++i) {
		printf("%d ", i);
		Sleep(3);
	}
	SetEvent(hEvent);
	return 0;
}

DWORD WINAPI thread2Func(LPVOID) {
	printf("Thread id:%d started\n", GetCurrentThreadId());

	printf("Thread id:%d wait for event object\n", GetCurrentThreadId());

	WaitForSingleObject(hEvent, INFINITE);

	printf("Thread id:%d got event object\n", GetCurrentThreadId());

	for (int i = -1; i >= -N; --i) {
		printf("%d ", i);
		Sleep(3);
	}
	return 0;
}