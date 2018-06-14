// dllmain.cpp : 定义 DLL 应用程序的入口点。
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
		printf("<CallWndProcRet>process attach\n");  // 静态链接，动态链接LoadLibrary
		break;
	case DLL_THREAD_ATTACH:
		printf("<CallWndProcRet>thread attach\n");  // 线程中加载
		break;
	case DLL_THREAD_DETACH:
		printf("<CallWndProcRet>thread detach\n");  // 线程中卸载
		break;
	case DLL_PROCESS_DETACH:
		printf("<CallWndProcRet>process detach\n");   // 静态链接结束，动态链接FreeLibrary，程序退出
		StopCallWndRetHook();
		break;
	}
	return TRUE;
}

