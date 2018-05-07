#include <windows.h>
#include <stdio.h>
#include <conio.h>

DWORD WINAPI thread1Func(LPVOID);
DWORD WINAPI thread2Func(LPVOID);

int const N = 50;

void main() {
	
	HANDLE hThread1 = CreateThread(NULL, 0, thread1Func, NULL, NULL, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, thread2Func, NULL, NULL, NULL);

	_getch();

	CloseHandle(hThread1);
	CloseHandle(hThread2);

}

DWORD WINAPI thread1Func(LPVOID) {
	printf("---------------------------------------------------------------------------------\n");
	printf("First thread is started\n");
	for (int i = 1; i <=N; ++i) {
		printf("%d ",i);
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


