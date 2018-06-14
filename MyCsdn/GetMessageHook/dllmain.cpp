// dllmain.cpp : 定义 DLL 应用程序的入口点。
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
		printf("<GetMessage>process attach\n");  // 静态链接，动态链接LoadLibrary
		break;
	case DLL_THREAD_ATTACH:
		printf("<GetMessage>thread attach\n");  // 线程中加载
		break;
	case DLL_THREAD_DETACH:
		printf("<GetMessage>thread detach\n");  // 线程中卸载
		break;
	case DLL_PROCESS_DETACH:
		printf("<GetMessage>process detach\n");   // 静态链接结束，动态链接FreeLibrary，程序退出
		StopGetMessageHook();
		break;
	}
	return TRUE;
}

