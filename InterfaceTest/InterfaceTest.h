
// InterfaceTest.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CInterfaceTestApp:
// � ���������� ������� ������ ��. InterfaceTest.cpp
//

class CInterfaceTestApp : public CWinApp
{
public:
	CInterfaceTestApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CInterfaceTestApp theApp;