
// CherryUpdateExam.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCherryUpdateExamApp:
// �� Ŭ������ ������ ���ؼ��� CherryUpdateExam.cpp�� �����Ͻʽÿ�.
//

class CCherryUpdateExamApp : public CWinApp
{
public:
	CCherryUpdateExamApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCherryUpdateExamApp theApp;