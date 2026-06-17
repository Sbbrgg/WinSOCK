#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono_literals;

bool finish = false;

HANDLE hMutex;

void Plus()
{
	while (!finish)
	{
		
		WaitForSingleObject
		(
			hMutex, 
			INFINITE	//будет ждать освобождения сколько угодно
		);

		cout << "+ ";
		std::this_thread::sleep_for(1ms);

		ReleaseMutex(hMutex);
	}
}

void Minus()
{
	while (!finish)
	{
		WaitForSingleObject(hMutex, INFINITE);

		cout << "- ";
		std::this_thread::sleep_for(1ms);

		ReleaseMutex(hMutex);
	}
}

void main()
{
	setlocale(LC_ALL, "RU");
	hMutex = CreateMutex
	(
		NULL,	//дефолтные параметры безопасности
		FALSE,	//мьютекс изначально свободен (не принадлежит создавшему потоку)
		NULL	//безымянный мьютекс
	);

	if (hMutex == NULL)
	{
		cout << "Ошибка создания мьютекса: " << GetLastError() << endl;
		return;
	}

	std::thread plus_thread(Plus);
	std::thread minus_thread(Minus);

	cin.get();
	finish = true;

	if (minus_thread.joinable()) minus_thread.join();
	if (plus_thread.joinable()) plus_thread.join();

	CloseHandle(hMutex);
}