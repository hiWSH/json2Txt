
// Json2Txt.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJson2TxtApp:
// �йش����ʵ�֣������ Json2Txt.cpp
//

class CJson2TxtApp : public CWinApp
{
public:
	CJson2TxtApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJson2TxtApp theApp;