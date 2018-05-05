//#include <Windows.h>
//#include <stdio.h>
//#include <conio.h>
//DWORD WINAPI threadExecut1(LPVOID);
//DWORD WINAPI threadExecut2(LPVOID);
//int const N = 50;
//
//
//CRITICAL_SECTION CriticalSection;
//
//
//DWORD WINAPI thread1Proc(LPVOID t) {
//	EnterCriticalSection(&CriticalSection);
//	for (int i = 1; i <= N; ++i) {
//		printf("%d ", i);
//		Sleep(1);
//	}
//	printf("\n");
//	LeaveCriticalSection(&CriticalSection);
//	return 0;
//}
//
//DWORD WINAPI thread2Proc(LPVOID t) {
//	EnterCriticalSection(&CriticalSection);
//	for (int j = -1; j >= -N; --j) {
//		printf("%d ", j);
//		Sleep(1);
//	}
//	LeaveCriticalSection(&CriticalSection);
//	return 0;
//}
//
////bool isPrime(int number) {
////	bool isPrime = true;
////	for (int i = 2; i <= number / 2; ++i)
////	{
////		if (number % i == 0)
////		{
////			isPrime = false;
////			break;
////		}
////	}
////	return isPrime;
////}
////
////DWORD WINAPI thread3Proc(LPVOID t) {
////	int i = 1;
////	while (true) {
////		if (isPrime(i)) std::cout << i << std::endl;
////		i++;
////		Sleep(1);
////	}
////	return 0;
////}
//int main() {
//	InitializeCriticalSection(&CriticalSection);
//	//std::cout << "Program start:" << std::endl;
//	HANDLE thread1 = CreateThread(NULL, 0, thread1Proc, NULL, CREATE_SUSPENDED, NULL);
//	HANDLE thread2 = CreateThread(NULL, 0, thread2Proc, NULL, CREATE_SUSPENDED, NULL);
//	//HANDLE thread3 = CreateThread(NULL, 0, thread3Proc, NULL, CREATE_SUSPENDED, NULL);
//	Sleep(1000);
//	SetThreadPriority(thread1, THREAD_PRIORITY_BELOW_NORMAL);  //3
//	SetThreadPriority(thread2, THREAD_PRIORITY_ABOVE_NORMAL);  //3
//	ResumeThread(thread1);
//	ResumeThread(thread2);
//	Sleep(1000);
//	DeleteCriticalSection(&CriticalSection);
//	/*std::cout << "Press Enter to start printing prime numbers" << std::endl;;
//	std::cout << "Press Enter again to stop printing prime numbers" << std::endl;;
//	std::cin.get();
//	ResumeThread(thread3);
//	std::cin.get();
//	TerminateThread(thread3, 0);
//	std::cout << "Thread eliminated" << std::endl;
//	std::cin.get();
//	std::cin.get();*/
//	return 0;
//}