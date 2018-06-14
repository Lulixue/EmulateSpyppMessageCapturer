// GetMessageHook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>
#include <stdio.h>

#include "../Shared/Shared.h"
#pragma comment(lib, "../Debug/Shared.lib")

HINSTANCE g_hGmInst;
HHOOK g_hookGetMessage;

LRESULT CALLBACK GetMessageProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	static map<UINT, string> mapSymbolicMsgs;
	if (code == HC_ACTION) 
	{
		PMSG pMsg = (PMSG)lParam;		// WH_CALLWNDPROC

		if (mapSymbolicMsgs.size() == 0)
		{
			InitSymbolicMsg(mapSymbolicMsgs);
		}
		char buffer[250] = {0};
		sprintf_s(buffer, "%08X P Msg: %s(%04X), wParam: %08X, lParam: %08X\n", 
			pMsg->hwnd, GetSymbolicMsg(pMsg->message, mapSymbolicMsgs), pMsg->message, (int)pMsg->wParam, (int)pMsg->lParam);
		AppendDebug(NULL, buffer, strlen(buffer));
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}


void StartGetMessageHook(int threadId)
{
	g_hookGetMessage = SetWindowsHookEx(WH_GETMESSAGE, GetMessageProc, g_hGmInst, threadId);
}

void StopGetMessageHook()
{
	UnhookWindowsHookEx(g_hookGetMessage);
}