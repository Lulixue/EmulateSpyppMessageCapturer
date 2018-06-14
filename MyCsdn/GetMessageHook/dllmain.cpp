// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <stdio.h>

extern HINSTANCE g_hGmInst;
void StopGetMessageHook();
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:		
		g_hGmInst = hModule;
		printf("<GetMessage>process attach\n");  // ��̬���ӣ���̬����LoadLibrary
		break;
	case DLL_THREAD_ATTACH:
		printf("<GetMessage>thread attach\n");  // �߳��м���
		break;
	case DLL_THREAD_DETACH:
		printf("<GetMessage>thread detach\n");  // �߳���ж��
		break;
	case DLL_PROCESS_DETACH:
		printf("<GetMessage>process detach\n");   // ��̬���ӽ�������̬����FreeLibrary�������˳�
		StopGetMessageHook();
		break;
	}
	return TRUE;
}

