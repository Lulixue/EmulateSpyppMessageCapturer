// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 SHARED_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// SHARED_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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
