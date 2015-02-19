// CherryUtil.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "CherryUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CCherryUtilApp

BEGIN_MESSAGE_MAP(CCherryUtilApp, CWinApp)
END_MESSAGE_MAP()


// CCherryUtilApp ����

CCherryUtilApp::CCherryUtilApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CCherryUtilApp ��ü�Դϴ�.

CCherryUtilApp theApp;


// CCherryUtilApp �ʱ�ȭ

BOOL CCherryUtilApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief		Windows ���� Ȯ��
/// \author		ogoons
/// \date		2013-11-07
/// \param		
/// \return		BOOL
/// \remark		�Ķ���ͷ� �Էµ� ���� �̻��̸� TRUE ���� �����̸� FALSE
/// \section	
///
///////////////////////////////////////////////////////////////////////////
extern "C" CHERRYUTIL_DECL_API BOOL IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OSVERSIONINFOEX osVersionInfoEx = { sizeof(OSVERSIONINFOEX), 0, 0, 0, 0, { 0 }, 0, 0 };
	DWORDLONG const dwlConditionMask = VerSetConditionMask(
		VerSetConditionMask(
		VerSetConditionMask(
		0, VER_MAJORVERSION, VER_GREATER_EQUAL),
		VER_MINORVERSION, VER_GREATER_EQUAL),
		VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

	osVersionInfoEx.dwMajorVersion = wMajorVersion;
	osVersionInfoEx.dwMinorVersion = wMinorVersion;
	osVersionInfoEx.wServicePackMajor = wServicePackMajor;

	return VerifyVersionInfo(&osVersionInfoEx, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief		DLL ���� ��������
/// \author		ogoons
/// \date		2013-09-04
/// \param		
/// \return		
/// \remark		DWORD�� HIWORD, LOWORD�� ���� �� �ִ�.
/// \section	
///
///////////////////////////////////////////////////////////////////////////
extern "C" CHERRYUTIL_DECL_API DWORD GetDllVersion(_In_ LPCTSTR lpszDllName, _Out_ DWORD &dwMajorVersion, _Out_ DWORD &dwMinorVersion, _Out_ DWORD &dwBuildNumber)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	DWORD dwVersion = 0;
	HINSTANCE hDll = LoadLibrary(lpszDllName);

	if (hDll)
	{
		DLLGETVERSIONPROC pDllGetVersion;
		pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hDll, "DllGetVersion");

		if (pDllGetVersion)
		{
			DLLVERSIONINFO dllVersionInfo;	

			ZeroMemory(&dllVersionInfo, sizeof(DLLVERSIONINFO));
			dllVersionInfo.cbSize = sizeof(DLLVERSIONINFO);

			HRESULT hr = (*pDllGetVersion)(&dllVersionInfo);

			if (SUCCEEDED(hr))
			{
				dwVersion = MAKELONG(dllVersionInfo.dwMajorVersion, dllVersionInfo.dwMinorVersion);

				dwMajorVersion = dllVersionInfo.dwMajorVersion;
				dwMinorVersion = dllVersionInfo.dwMinorVersion;
				dwBuildNumber = dllVersionInfo.dwBuildNumber;
			}
			else
			{
				// �����ϸ� ��� 0
				dwMajorVersion = dwMinorVersion = dwBuildNumber = 0;
			}
		}

		FreeLibrary(hDll);
	}

	return dwVersion;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief		���� ���μ����� ���丮 ��θ� ��ȯ
/// \author		ogoons
/// \date		2015-01-20
/// \param		
/// \return		CString
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////
CHERRYUTIL_DECL_API CString GetCurrentPath()
{
	CString strPath;
	GetModuleFileName(NULL, strPath.GetBuffer(MAX_PATH), MAX_PATH);
	strPath.ReleaseBuffer();

	PathRemoveFileSpec(strPath.GetBuffer(MAX_PATH));
	strPath.ReleaseBuffer();

	return strPath;
}
