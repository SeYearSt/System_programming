#include <windows.h>
#include <stdio.h>
#include <conio.h>

DWORD WINAPI thread1Func(LPVOID);
DWORD WINAPI thread2Func(LPVOID);

int const N = 50;

CRITICAL_SECTION CriticalSection;


int main() {

	InitializeCriticalSection(&CriticalSection);

	HANDLE threads[2];

	threads[0] = CreateThread(NULL, 0, thread1Func, NULL, NULL, NULL);
	threads[1] = CreateThread(NULL, 0, thread2Func, NULL, NULL, NULL);

	WaitForMultipleObjects(2, threads, TRUE, INFINITE);

	DeleteCriticalSection(&CriticalSection);

	_getch();
	return 0;
}


DWORD WINAPI thread1Func(LPVOID t) {
	EnterCriticalSection(&CriticalSection);
	printf("---------------------------------------------------------------------------------\n");
	printf("First thread is started\n");
	for (int i = 1; i <= N; ++i) {
		printf("%d ", i);
		Sleep(1);
	}
	printf("\n");
	printf("First thread is finished\n");
	printf("---------------------------------------------------------------------------------\n");
	LeaveCriticalSection(&CriticalSection);
	return 0;
}

DWORD WINAPI thread2Func(LPVOID t) {
	EnterCriticalSection(&CriticalSection);
	printf("---------------------------------------------------------------------------------\n");
	printf("Second thread is started\n");
	for (int j = -1; j >= -N; --j) {
		printf("%d ", j);
		Sleep(1);
	}
	printf("\n");
	printf("Second thread is finished\n");
	printf("---------------------------------------------------------------------------------\n");
	LeaveCriticalSection(&CriticalSection);
	return 0;
}
