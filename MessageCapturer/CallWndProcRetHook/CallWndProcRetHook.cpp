// CallWndProcRetHook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include <tchar.h>
#include <string>
#include <Windows.h>
#include <stdio.h>

#include "../Shared/Shared.h"
#pragma comment(lib, "../Debug/Shared.lib")

HINSTANCE g_hCwrInst;
HHOOK g_hookCallWndRetProc;

LRESULT CALLBACK CallWndRetHookProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	static map<UINT, string> mapSymbolicMsgs;
	if (code == HC_ACTION) 
	{
		PCWPRETSTRUCT pMsg = (PCWPRETSTRUCT)lParam;		// WH_CALLWNDPROC

		if (mapSymbolicMsgs.size() == 0)
		{
			InitSymbolicMsg(mapSymbolicMsgs);
		}
		char buffer[200] = {0};
		sprintf_s(buffer, "%08X R Msg: %s(%04X), lResult: %08X\n", 
			pMsg->hwnd, GetSymbolicMsg(pMsg->message, mapSymbolicMsgs), pMsg->message, pMsg->lResult);
		AppendDebug(NULL, buffer, strlen(buffer));
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}


void StartCallWndRetHook(int threadId)
{
	g_hookCallWndRetProc = SetWindowsHookEx(WH_CALLWNDPROCRET, CallWndRetHookProc, g_hCwrInst, threadId);
}

void StopCallWndRetHook()
{
	UnhookWindowsHookEx(g_hookCallWndRetProc);
}


