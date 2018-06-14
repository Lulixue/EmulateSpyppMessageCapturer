// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <stdio.h>

void ShowDebug(LPTSTR lpstrFormat, ...);
void StopCallWndHook();
extern HINSTANCE g_hCwInst;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:		
		g_hCwInst = hModule;
		printf("<CallWndProc>process attach\n");  // ��̬���ӣ���̬����LoadLibrary
		break;
	case DLL_THREAD_ATTACH:
		printf("<CallWndProc>thread attach\n");  // �߳��м���
		break;
	case DLL_THREAD_DETACH:
		printf("<CallWndProc>thread detach\n");  // �߳���ж��
		break;
	case DLL_PROCESS_DETACH:
		printf("<CallWndProc>process detach\n");   // ��̬���ӽ�������̬����FreeLibrary�������˳�
		StopCallWndHook();
		break;
	}
	return TRUE;
}

