
// ChangeToGray.h : ChangeToGray Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CChangeToGrayApp:
// �йش����ʵ�֣������ ChangeToGray.cpp
//

class CChangeToGrayApp : public CWinAppEx
{
public:
	CChangeToGrayApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChangeToGrayApp theApp;
