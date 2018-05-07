#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

bool isPrime(int number);

DWORD WINAPI threadFunc(LPVOID t);

int main() {
	HANDLE hThread = CreateThread(NULL, 0, threadFunc, NULL, CREATE_SUSPENDED, NULL);

	printf("Press any key to start printing prime numbers");
	
	_getch();

	ResumeThread(hThread);

	printf("Press any key to stop printing prime numbers");

	_getch();

	TerminateThread(hThread, NULL);

	printf("Thread stoped");

	_getch();

	return 0;
}

bool isPrime(int number) {
	bool isPrime = true;
	for (int i = 2; i <= sqrt(number); ++i)
	{
		if (number % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}

DWORD WINAPI threadFunc(LPVOID t) {
	for (int i = 1; ; i++) {
		if (isPrime(i)) {
			printf("%d ", i);
		}
		Sleep(1);
	}
	return 0;
}