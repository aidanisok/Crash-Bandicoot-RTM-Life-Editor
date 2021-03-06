﻿// CrashBandicootLives.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;

#define CRASH_LIVES 0x20AE09E2AF0

int main()
{
	DWORD lwError;

	HWND win = FindWindowA(NULL, "Crash Bandicoot™ N. Sane Trilogy");
	if (win == NULL)
	{
		printf("Window not found, please launch Crash Bandicoot");
		Sleep(5000);
		exit(-1);
	}

	DWORD procId;
	GetWindowThreadProcessId(win, &procId);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	if (handle == NULL)
	{
		printf("Process not found. Run application as admin");
		Sleep(5000);
		exit(-1);
	}

	//check current lives
	int currentLives = 1;
	bool result = ReadProcessMemory(handle, (LPVOID)CRASH_LIVES, &currentLives, sizeof(currentLives), 0);
	if (result == false)
	{
		DWORD error = GetLastError();
		cout << "ReadProcessMemory Error: " << error << endl;
		Sleep(5000);
		exit(-1);
	}
	printf("Current lives: %i \n\n", currentLives);


	int lives;
	printf("Enter number of lives: ");
	cin >> lives;
	
	//write new value to memory
	result = WriteProcessMemory(handle, (LPVOID)CRASH_LIVES, &lives, sizeof(lives), 0);
	if (result == false)
	{
		DWORD error = GetLastError();
		cout << "WriteProcessMemory Error: " << error << endl;
		Sleep(5000);
		exit(-1);
	}

	//confirm new lives
	result = ReadProcessMemory(handle, (LPVOID)CRASH_LIVES, &currentLives, sizeof(currentLives), 0);
	if (result == false)
	{
		DWORD error = GetLastError();
		cout << "ReadProcessMemory Error: " << error << endl;
		Sleep(5000);
		exit(-1);
	}

	if (currentLives == lives)
	{
		printf("Current lives updated to %i\nEnjoy!", lives);
		Sleep(3000);
		exit(-1);
	}

	printf("Uh oh...");
	Sleep(3000);
	exit(-1);
}

