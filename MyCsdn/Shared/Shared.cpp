// Shared.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Shared.h"
#include <fstream>
#include <tchar.h>
#include <boost/tokenizer.hpp>  
using std::ifstream;



SHARED_API void AppendDebug(char *pFilename, LPVOID pBuf, int length)
{
	FILE *pFile;
	if (pFilename == NULL)
	{
		fopen_s(&pFile, "C:\\test.txt", "ab");
	}
	else
	{
		fopen_s(&pFile, pFilename, "ab");
	}
	if (pFile != NULL)
	{
		fwrite(pBuf, sizeof(char), length, pFile);
		fclose(pFile);
	}
}

SHARED_API void ShowDebug(LPTSTR lpstrFormat, ...)
{
	va_list VAList;
	va_start(VAList, lpstrFormat);

	TCHAR szBuf[MAX_PATH * 2] = {0};
	_vstprintf_s(szBuf, MAX_PATH, lpstrFormat, VAList);

	OutputDebugString(szBuf);
}

// 十六进制字符串转为十进制
int HexToDec(string strHex)
{
	int nRet = 0;
	if (strHex.at(1) == 'x')
	{
		strHex = strHex.substr(2);
	}
	int nLen = strHex.size();
	int nBase = 1;
	int para = 0;
	char ch = 0;
	for (int i = nLen-1, bi = 0; i >= 0; i--, bi++)
	{
		ch = strHex.at(i);
		if (ch >= '0' && ch <= '9')
		{
			para = ch - '0';
		}
		else if (ch >= 'a' && ch <= 'f')
		{
			para = ch - 'a' + 10;
		}	
		else if (ch >= 'A' && ch <= 'F')
		{
			para = ch - 'A' + 10;
		}
		else	// 非法字符
		{
			return -1;
		}
		nRet += para * nBase;
		nBase *= 16;
	}

	return nRet;
}

SHARED_API void InitSymbolicMsg(map<UINT, string> &mapSymbolicMsgs)
{
	ifstream ifs;
	ifs.open("C:\\SymbolicMessages.h", std::ios::in);
	mapSymbolicMsgs.clear();

	if (!ifs.is_open())
	{
		return;
	}

	boost::char_separator<char> custcs(" ");	// 自己指定
	char line[256] = {0};
	string strLine;
	while (!ifs.eof())
	{
		ifs.getline(line, 255);
		strLine = line;
		// 使用" "空格进行分割
		if ( (strLine.find("#define") != string::npos) && (strLine.find("WM_") != string::npos))
		{
			boost::tokenizer<boost::char_separator<char> > tok(strLine, custcs);

			boost::tokenizer<boost::char_separator<char> >::iterator cit = tok.begin();
			cit++;
			if (cit == tok.end())
			{
				continue;
			}
			string msg(*cit);
			cit++;
			if (cit == tok.end())
			{
				continue;
			}
			string val(*cit);
			UINT nVal = HexToDec(val);
			if (nVal == -1)
			{
				continue;
			}
			mapSymbolicMsgs.insert(std::make_pair<UINT, string>(nVal, msg));
		}
		memset(line, 0, 256);
	}
	ifs.close();
}

SHARED_API const char * GetSymbolicMsg(UINT message, map<UINT, string> &mapSymbolicMsgs)
{
	map<UINT, string>::const_iterator cit = mapSymbolicMsgs.begin();
	
	for (; cit != mapSymbolicMsgs.end(); cit++)
	{
		if (cit->first == message)
		{
			return (cit->second).c_str();
		}
	}

	return ("User_Define");
}
