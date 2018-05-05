#include <Windows.h>
#include <stdio.h>
#include <conio.h>
DWORD WINAPI threadExecut1(LPVOID);
DWORD WINAPI threadExecut2(LPVOID);
int const N = 50;


void main() {
	
	HANDLE thread1 = CreateThread(NULL, 0, threadExecut1, NULL, CREATE_SUSPENDED, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, threadExecut2, NULL, CREATE_SUSPENDED, NULL);

	ResumeThread(thread1);
	ResumeThread(thread2);

	printf("Main thread has finished\n");
	_getch();
}

DWORD WINAPI threadExecut1(LPVOID) {
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


