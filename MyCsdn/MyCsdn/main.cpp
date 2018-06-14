#include <iostream>
#include <fstream>
#include <Windows.h>
#include <Shlobj.h>
#include <boost/tokenizer.hpp> 
#include <process.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <math.h>

using namespace std;


// 获取程序主线程ID
DWORD GetThreadIdByProcessID(DWORD dwProcessId)
{
	HANDLE hThreadSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessId);
	if(hThreadSnap == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	THREADENTRY32 te32 = { sizeof(te32) };
	if(::Thread32First(hThreadSnap, &te32))
	{
		do
		{
			if(te32.th32OwnerProcessID == dwProcessId)
			{
				::CloseHandle(hThreadSnap);
				return te32.th32ThreadID;
			}
		}while(::Thread32Next(hThreadSnap, &te32));
	}

	::CloseHandle(hThreadSnap);
	return -1;
}

DWORD GetProcessIdByName(LPCWSTR processName)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 pe;          
	pe.dwSize = sizeof(PROCESSENTRY32); 
	if(!Process32First(hSnapShot,&pe))  
	{          
		return NULL;    
	}          
	BOOL clearprocess = FALSE;
	while (Process32Next(hSnapShot,&pe))  
	{                       
		if(!_tcsicmp(processName, pe.szExeFile))    
		{  
			::CloseHandle(hSnapShot);
			return pe.th32ProcessID;
		} 
	}      
	::CloseHandle(hSnapShot);
	return -1;
}

bool g_bThreadRunning = true;
void DllWinThread(LPVOID lP)
{
	g_bThreadRunning = true;

	wchar_t wstrExe[256] = {0};
	cout << "The program to hook: ";
	wcin >> wstrExe;

	DWORD dwProcessId = GetProcessIdByName(wstrExe);
	if (dwProcessId == -1)
	{
		g_bThreadRunning = false;
		system("pause");
		return;
	}
	DWORD dwThreadId = GetThreadIdByProcessID(dwProcessId);

	typedef void (*STARTHOOK)(int);
	HINSTANCE hinst = LoadLibrary(TEXT("CallWndProcHook.dll"));
	HINSTANCE hinst2 = LoadLibrary(TEXT("GetMessageHook.dll"));
	HINSTANCE hinst3 = LoadLibrary(TEXT("CallWndProcRetHook.dll"));


	STARTHOOK cwpSt = (STARTHOOK)GetProcAddress(hinst, "StartCallWndHook");
	STARTHOOK gmSt = (STARTHOOK)GetProcAddress(hinst2, "StartGetMessageHook");
	STARTHOOK cwprSt = (STARTHOOK)GetProcAddress(hinst3, "StartCallWndRetHook");

	cwpSt(dwThreadId);
	cwprSt(dwThreadId);
	gmSt(dwThreadId);

	int nTimeout = 500;
	while (nTimeout--)
	{
		Sleep(100);
	}

	FreeLibrary(hinst);
	FreeLibrary(hinst3);
	FreeLibrary(hinst2);
	g_bThreadRunning = false;
}


int main(int argc, char **argv)
{
	HANDLE hThread = CreateThread(NULL, 0, 
		(LPTHREAD_START_ROUTINE)DllWinThread,	// 线程函数
		NULL,			// 函数参数
		0, NULL);


	while (g_bThreadRunning)
	{
		Sleep(50);
	}
	CloseHandle(hThread);

 	system("pause");
	return 0;
}
