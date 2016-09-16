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

/////////////////////////////////////////////////////////////////
// C/C++ functions
#ifdef __cplusplus
extern "C" 
{
#endif
	CHERRYUTIL_DECL_API DWORD	GetDllVersion(_In_ LPCTSTR lpszDllName, _Out_ DWORD &dwMajorVersion, _Out_ DWORD &dwMinorVersion, _Out_ DWORD &dwBuildNumber);
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////
// C++ only functions

// Get special path functions
CHERRYUTIL_DECL_API CString		GetCurrentPath();

// WinInet functions
CHERRYUTIL_DECL_API BOOL		RequestHttp(_In_ LPCTSTR lpszUrl, _In_ BOOL bPost, _In_ LPCTSTR lpszPostData, _Out_ CString &strResponse);
CHERRYUTIL_DECL_API BOOL		DownloadFile(_In_ LPCTSTR lpszUrl, _In_ LPCTSTR lpszDownloadPath);

CHERRYUTIL_DECL_API CString		ConvertAnsiToUnicode(_In_ LPCSTR lpszAnsi);
CHERRYUTIL_DECL_API CStringA	ConvertUnicodeToAnsi(_In_ LPCWSTR lpszUnicode);
CHERRYUTIL_DECL_API CString		ConvertUtf8ToUnicode(_In_ LPCWSTR lpszUtf8);
CHERRYUTIL_DECL_API CStringA	ConvertUtf8ToAnsi(_In_ LPCSTR lpszUtf8);

CHERRYUTIL_DECL_API BOOL		GetFileSize(_In_ LPCTSTR lpszFilePath, _Out_ LONGLONG &llFileSize);
CHERRYUTIL_DECL_API BOOL		ExecuteProcess(_In_ LPCTSTR lpszPath, _In_ LPCTSTR lpszParam, _In_ BOOL bWaitProcess);
CHERRYUTIL_DECL_API int			CompareVersion(LPCTSTR lpszCurrentVersion, LPCTSTR lpszNewVersion);

CHERRYUTIL_DECL_API void		CreateDirectoryAndParent(LPTSTR lpszPath);				// ���丮 ����(path �� ���� ���丮�� ���ٸ� ���� ����)
CHERRYUTIL_DECL_API BOOL		DeleteDirectoryAndChild(LPCTSTR lpszPath);				// ���丮 ����(���� ���丮, ���� ��� ����)