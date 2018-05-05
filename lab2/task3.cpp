#include <Windows.h>
#include <stdio.h>
#include <conio.h>

DWORD WINAPI threadExecut1(LPVOID);
DWORD WINAPI threadExecut2(LPVOID);
int const N = 50;


void main() {

	HANDLE hThread1 = CreateThread(NULL, 0, threadExecut1, NULL, CREATE_SUSPENDED, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, threadExecut2, NULL, CREATE_SUSPENDED, NULL);

	SetThreadPriority(hThread1, THREAD_PRIORITY_BELOW_NORMAL);
	SetThreadPriority(hThread2, THREAD_PRIORITY_ABOVE_NORMAL);

	ResumeThread(hThread2);
	ResumeThread(hThread1);

	printf("Main thread has finished\n");
	_getch();
}

DWORD WINAPI threadExecut1(LPVOID) {
	Sleep(10);
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

DWORD WINAPI threadExecut2(LPVOID) {
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


