
// InterfaceTest.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CInterfaceTestApp:
// О реализации данного класса см. InterfaceTest.cpp
//

class CInterfaceTestApp : public CWinApp
{
public:
	CInterfaceTestApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CInterfaceTestApp theApp;