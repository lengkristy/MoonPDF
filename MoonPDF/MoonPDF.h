#pragma once

// MoonPDF.h : MoonPDF.DLL 的主头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CMoonPDFApp : 有关实现的信息，请参阅 MoonPDF.cpp。

class CMoonPDFApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//导入mupdf相关库，使用的库版本为：mupdf-1.15.0
#ifdef DEBUG
#pragma comment(lib, "lib\\debug\\libmupdf.lib")
#pragma comment(lib, "lib\\debug\\libresources.lib")
#pragma comment(lib, "lib\\debug\\libthirdparty.lib")
#else
#pragma comment(lib, "lib\\release\\libmupdf.lib")
#pragma comment(lib, "lib\\release\\libresources.lib")
#pragma comment(lib, "lib\\release\\libthirdparty.lib")
#endif