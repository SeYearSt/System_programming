#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

bool isPrime(int number) {
	bool isPrime = true;
	for (int i = 2; i <= /*number / 2*/sqrt(number); ++i)
	{
		if (number % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}

DWORD WINAPI threadExecut(LPVOID t) {
	for (int i = 1; ; i++) {
		if (isPrime(i)) {
			printf("%d ", i);
		}
		Sleep(1);
	}
	return 0;
}

int main() {
	HANDLE thread3 = CreateThread(NULL, 0, threadExecut, NULL, NULL, NULL);
	printf("Press Enter to start printing prime numbers");
	printf("Press Enter again to stop printing prime numbers");
	_getch();
	TerminateThread(thread3, 0);
	printf("Thread eliminated");
	_getch();
	return 0;
}