// CherryUtil.h : CherryUtil DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

// CHERRYUTIL.H
#ifdef CHERRYUTIL_IMPL
#define CHERRYUTIL_DECL_API __declspec(dllexport)
#else
#define CHERRYUTIL_DECL_API __declspec(dllimport)
#endif

#ifdef CHERRYUTIL_IMPL
#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCherryUtilApp
// �� Ŭ������ ������ ������ CherryUtil.cpp�� �����Ͻʽÿ�.
//

class CCherryUtilApp : public CWinApp
{
public:
	CCherryUtilApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
#endif

/*
�Ǵ� ������ Windows ����

- Windows XP
- Windows XP SP1
- Windows XP SP2
- Windows XP SP3
- Windows Vista SP1
- Windows Vista SP2
- Windows 7
- Windows 7 SP1
- Windows 8
- Windows 8.1
*/

extern "C" CHERRYUTIL_DECL_API BOOL		IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor);
extern "C" CHERRYUTIL_DECL_API DWORD	GetDllVersion(_In_ LPCTSTR lpszDllName, _Out_ DWORD &dwMajorVersion, _Out_ DWORD &dwMinorVersion, _Out_ DWORD &dwBuildNumber);