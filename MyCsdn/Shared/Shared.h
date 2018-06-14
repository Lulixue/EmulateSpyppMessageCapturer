// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SHARED_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SHARED_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SHARED_EXPORTS
#define SHARED_API __declspec(dllexport)
#else
#define SHARED_API __declspec(dllimport)
#endif

#include <map>
#include <string>
using std::map;
using std::string;

SHARED_API void AppendDebug(char *pFilename, LPVOID pBuf, int length);
SHARED_API void ShowDebug(LPTSTR lpstrFormat, ...);
SHARED_API void InitSymbolicMsg(map<UINT, string>&);
SHARED_API const char * GetSymbolicMsg(UINT message, map<UINT, string>&m);
