// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <stdio.h>

void StopCallWndRetHook();
extern HINSTANCE g_hCwrInst;

BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:		
		g_hCwrInst = hModule;
		printf("<CallWndProcRet>process attach\n");  // ��̬���ӣ���̬����LoadLibrary
		break;
	case DLL_THREAD_ATTACH:
		printf("<CallWndProcRet>thread attach\n");  // �߳��м���
		break;
	case DLL_THREAD_DETACH:
		printf("<CallWndProcRet>thread detach\n");  // �߳���ж��
		break;
	case DLL_PROCESS_DETACH:
		printf("<CallWndProcRet>process detach\n");   // ��̬���ӽ�������̬����FreeLibrary�������˳�
		StopCallWndRetHook();
		break;
	}
	return TRUE;
}

