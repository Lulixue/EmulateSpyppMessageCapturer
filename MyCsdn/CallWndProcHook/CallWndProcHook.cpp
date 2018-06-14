// CallWndProcHook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <string>
#include <Windows.h>
#include <stdio.h>

#include "../Shared/Shared.h"
#pragma comment(lib, "../Debug/Shared.lib")   // H+LIB+DLL的方式加载DLL

HINSTANCE g_hCwInst;
HHOOK g_hookCallWndProc;

LRESULT CALLBACK CallWndHookProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	static map<UINT, string> mapSymbolicMsgs;
	if (code == HC_ACTION) 
	{
		PCWPSTRUCT pMsg = (PCWPSTRUCT)lParam;		// WH_CALLWNDPROC
		char buffer[200] = {0};
		if (mapSymbolicMsgs.size() == 0)
		{
			InitSymbolicMsg(mapSymbolicMsgs);
		}
		sprintf_s(buffer, "%08X S Msg: %s(%04X), wParam: %08X, lParam: %08X\n", pMsg->hwnd, 
			GetSymbolicMsg(pMsg->message, mapSymbolicMsgs), pMsg->message, (int)pMsg->wParam, (int)pMsg->lParam);
		AppendDebug(NULL, buffer, strlen(buffer));
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}


void StartCallWndHook(int threadId)
{
	g_hookCallWndProc = SetWindowsHookEx(WH_CALLWNDPROC, CallWndHookProc, g_hCwInst, threadId);
}

void StopCallWndHook()
{
	UnhookWindowsHookEx(g_hookCallWndProc);
}