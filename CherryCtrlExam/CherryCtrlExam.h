
// CherryCtrlExam.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCherryCtrlExamApp:
// �� Ŭ������ ������ ���ؼ��� CherryCtrlExam.cpp�� �����Ͻʽÿ�.
//

class CCherryCtrlExamApp : public CWinApp
{
public:
	CCherryCtrlExamApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCherryCtrlExamApp theApp;