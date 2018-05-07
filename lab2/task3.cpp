#include <windows.h>
#include <stdio.h>
#include <conio.h>

DWORD WINAPI thread1Func(LPVOID);
DWORD WINAPI thread2Func(LPVOID);

int const N = 500;

void main() {

	HANDLE hThread1 = CreateThread(NULL, 0, thread1Func, NULL, CREATE_SUSPENDED, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, thread2Func, NULL, CREATE_SUSPENDED, NULL);

	SetThreadPriority(hThread1, THREAD_PRIORITY_BELOW_NORMAL);
	SetThreadPriority(hThread2, THREAD_PRIORITY_ABOVE_NORMAL);

	ResumeThread(hThread1);
	ResumeThread(hThread2);

	_getch();
}

DWORD WINAPI thread1Func(LPVOID) {
	printf("---------------------------------------------------------------------------------\n");
	printf("First thread is started\n");
	for (int i = 1; i <= N; ++i) {
		printf("%d ", i);
	}
	printf("\n");
	printf("First thread is finished\n");
	printf("---------------------------------------------------------------------------------\n");
	return 0;
}

DWORD WINAPI thread2Func(LPVOID) {
	printf("---------------------------------------------------------------------------------\n");
	printf("Second thread is started\n");
	for (int i = -1; i >= -N; --i) {
		printf("%d ", i);
	}
	printf("\n");
	printf("Second thread is finished\n");
	printf("---------------------------------------------------------------------------------\n");
	return 0;
}


