// dllmain.cpp : DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONG_PTR g_lGdiPlusToken = 0;

static AFX_EXTENSION_MODULE CherryCtrlDLL = { NULL, NULL };

extern "C" int APIENTRY

DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// lpReserved�� ����ϴ� ��� ������ �����Ͻʽÿ�.
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("CherryCtrl.DLL�� �ʱ�ȭ�ϰ� �ֽ��ϴ�.\n");
		
		// Ȯ�� DLL�� �� ���� �ʱ�ȭ�մϴ�.
		if (!AfxInitExtensionModule(CherryCtrlDLL, hInstance))
			return 0;

		GdiplusStartupInput gdiPlusStartupInput;

		if (Ok != GdiplusStartup(&g_lGdiPlusToken, &gdiPlusStartupInput, NULL))
		{
			TRACE(_T("[CherryCtrl.dll] Start GDI+ failure."));
			return 0;
		}
		// �� DLL�� ���ҽ� ü�ο� �����մϴ�.
		// ����: �� Ȯ�� DLL�� MFC ���� ���α׷���
		//  �ƴ� ActiveX ��Ʈ�Ѱ� ���� MFC �⺻ DLL��
		//  ���� ��������� ��ũ�Ǿ� �ִ� ��쿡��
		//  DllMain���� �� ���� �����ϰ�, ������ ���� �� Ȯ�� DLL����
		//  ������ ������ �Լ��� �߰��մϴ�.
		//  �׷� ���� �� Ȯ�� DLL�� ����ϴ� �⺻ DLL��
		//  �ش� �Լ��� ��������� ȣ���Ͽ� �� Ȯ�� DLL�� �߰��ؾ� �մϴ�.
		//  �׷��� ������ CDynLinkLibrary ��ü��
		//  �⺻ DLL�� ���ҽ� ü�ο� �߰����� �����Ƿ�
		//  �ɰ��� ������ �߻��մϴ�.

		new CDynLinkLibrary(CherryCtrlDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("CherryCtrl.DLL�� �����ϰ� �ֽ��ϴ�.\n");

		GdiplusShutdown(g_lGdiPlusToken);

		// �Ҹ��ڰ� ȣ��Ǳ� ���� ���̺귯���� �����մϴ�.
		AfxTermExtensionModule(CherryCtrlDLL);
	}
	return 1;   // Ȯ��
}
