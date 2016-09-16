// CherryFlyout.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CherryNotificationIcon.h"

#include "CherryUtil.h"
#ifdef _DEBUG
#pragma comment(lib, "CherryUtilD.lib")
#else
#pragma comment(lib, "CherryUtil.lib")
#endif

#include "rpc.h"	// for GUID
#pragma comment(lib, "rpcrt4.lib")

#include "VersionHelpers.h"

// CCherryNotificationIcon

#define ID_TIMER_NOTIFICATION_ICON_ANIMATION		0
#define ID_TIMER_FLYOUT_WINDOW_SHOW_TIME			1
#define ID_TIMER_FLYOUT_WINDOW_ALPHA				2	

IMPLEMENT_DYNAMIC(CCherryNotificationIcon, CWnd)

const UINT CCherryNotificationIcon::m_nTaskbarCreatedMessage = RegisterWindowMessage(_T("TaskbarCreated"));

CCherryNotificationIcon::CCherryNotificationIcon()
:
// Win XP �̻�
m_bWinXPOrLater(IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0)),	// OS ������ ����
m_notifyIconDataSize(GetNotifyIconDataSize())
{
	Initialize();
}

CCherryNotificationIcon::CCherryNotificationIcon(HICON hIcon, LPCTSTR lpszToolTip, UINT nContextMenuID, UINT nCallbackMessage, CWnd *pParentWnd, UINT nID)
: 
m_bWinXPOrLater(IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0)),	// OS ������ ����
m_notifyIconDataSize(GetNotifyIconDataSize())
{
	Initialize();

	Create(hIcon, lpszToolTip, nContextMenuID, nCallbackMessage, pParentWnd, nID);
}

CCherryNotificationIcon::~CCherryNotificationIcon()
{
	Destroy();
}

BEGIN_MESSAGE_MAP(CCherryNotificationIcon, CWnd)
	ON_WM_TIMER()
	ON_REGISTERED_MESSAGE(CCherryNotificationIcon::m_nTaskbarCreatedMessage, OnTaskbarCreated)
END_MESSAGE_MAP()

void CCherryNotificationIcon::Initialize()
{
	ZeroMemory(&m_notifyIconData, m_notifyIconDataSize);
	
	m_pParentWnd	= NULL;
	m_hIcon			= NULL;
	m_bEnabled		= FALSE;
	m_bAdded		= FALSE;
	m_bVisible		= FALSE;
	m_nTimerID		= 0;
	m_nCount		= 0;	// ���ϸ��̼��� ����
	m_hIconList.clear();

	m_nAddedID = -1;
	m_nContextMenuID = 0;
	m_nContextMenuDefaultItem = 0;
	m_bContextMenuDefaultByPos = FALSE;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief    Shell32.dll �������� NOTIFYICONDATA ������ �������� �Լ�
/// \author   ogoons
/// \date     2013-09-05
/// \param    
/// \return   
/// \remark   
/// \section  
///
///////////////////////////////////////////////////////////////////////////

size_t CCherryNotificationIcon::GetNotifyIconDataSize() const
{
	DWORD dwMajorVersion, dwMinorVersion, dwBuildNumber;
	DWORD dwDllVer = GetDllVersion(_T("Shell32.dll"), dwMajorVersion, dwMinorVersion, dwBuildNumber);

	size_t size;

	if (dwDllVer)
	{
		// 2k ���� ������
		if (dwMajorVersion < 5)
			size = NOTIFYICONDATA_V1_SIZE;
		// 2k
		else if (dwMajorVersion == 5 && dwMinorVersion == 0)
			size = NOTIFYICONDATA_V2_SIZE;
		// XP
		else if (dwMajorVersion == 6 && dwMinorVersion == 0 && (dwBuildNumber / 1000) < 6)
			size = NOTIFYICONDATA_V3_SIZE;
		// Vista �̻�
		else
			size = sizeof(NOTIFYICONDATA);
	}

	/*
	// MAKELONG ��� ����
	// 2k ���� ������
	if (dwDllVer < (dwTargetVer = MAKELONG(5, 0)))
		size = NOTIFYICONDATA_V1_SIZE;
	// 2k
	else if (dwDllVer == (dwTargetVer = MAKELONG(5, 0)))
		size = NOTIFYICONDATA_V2_SIZE;
	// XP
	else if (dwDllVer == (dwTargetVer = MAKELONG(6, 0)))
		size = NOTIFYICONDATA_V3_SIZE;
	// Vista �̻�
	else if (dwDllVer > (dwTargetVer = MAKELONG(6, 0)))
		size = sizeof(NOTIFYICONDATA);
	*/

	return size;
}

CHERRY_RET CCherryNotificationIcon::Create(HICON hIcon, LPCTSTR lpszToolTip, UINT nContextMenuID, UINT nCallbackMessage, CWnd *pParentWnd, UINT nID)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;
	
	try
	{
		//if (!CWnd::Create(AfxRegisterWndClass(0), NULL, WS_CHILD, CRect(0, 0, 0, 0), pParentWnd, nID))
		if (!CWnd::CreateEx(0, AfxRegisterWndClass(0), NULL, WS_POPUP, CRect(0, 0, 0, 0), pParentWnd, 0))
			throw CCherryException::ERROR_NOTIFICATIONICON_CREATE_FAIL;

		m_pParentWnd = pParentWnd;	// Target Window
		m_bEnabled = TRUE;
		m_nContextMenuID = nContextMenuID;

		m_notifyIconData.cbSize = m_notifyIconDataSize;
		m_notifyIconData.hWnd = GetSafeHwnd();
		m_notifyIconData.uID = nID;
		m_notifyIconData.hIcon = m_hIcon = hIcon;	// �⺻ �������� ����� ������ �ִ´�.
		m_notifyIconData.uCallbackMessage = nCallbackMessage;
		_tcsncpy_s(m_notifyIconData.szTip, lpszToolTip, sizeof(m_notifyIconData.szTip));

		// Win7 �̻��� ��� GUID�� �̿��Ѵ�.
		if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0))
		{
			// GUID �ڵ� ���� -> uID ����� ���õ�
			if (RPC_S_OK != UuidCreate(&m_notifyIconData.guidItem))
				m_notifyIconData.guidItem = GUID_NULL;
		}

	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::Destroy()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		RemoveIcon();
		m_hIconList.clear();

		//if (m_pFlyout)
		//HideFlyout();

		if (!CWnd::DestroyWindow())
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief    ������ �߰�
/// \author   ogoons
/// \date     2013-09-13
/// \param    
/// \return   
/// \remark   �̹� �߰��� �����ܿ� ���� ���� �޽��� ó�� �ʿ�
/// \section  
///
///////////////////////////////////////////////////////////////////////////

CHERRY_RET CCherryNotificationIcon::AddIcon()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		if (m_bAdded)
			RemoveIcon();

		m_notifyIconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;

		if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0))
			m_notifyIconData.uFlags |= NIF_GUID;

		if (!(m_bAdded = m_bVisible = Shell_NotifyIcon(NIM_ADD, &m_notifyIconData)))
		{
			// ���� ���̵� �ߺ����� Ȯ�� �� ���� ���� to do
			if (m_nAddedID == (int)m_notifyIconData.uID)
				throw CCherryException::ERROR_NOTIFICATIONICON_ALREADY_EXISTS_ID;

			throw CCherryException::ERROR_CHERRY_FAILURE;
		}

		// ��Ÿ �̻��̸�
		if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0))
			m_notifyIconData.uVersion = NOTIFYICON_VERSION_4;
		// ��Ÿ���� ���� OS�̸�
		else
			m_notifyIconData.uVersion = NOTIFYICON_VERSION;

		Shell_NotifyIcon(NIM_SETVERSION, &m_notifyIconData);
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

HICON CCherryNotificationIcon::GetIcon() const
{
	return m_bEnabled ? m_notifyIconData.hIcon : NULL;
}

HICON CCherryNotificationIcon::GetDefaultIcon() const
{
	return m_bEnabled ? m_hIcon : NULL;
}

HICON CCherryNotificationIcon::GetIconFromList(INT_PTR nPos) const
{
	if (!m_bEnabled)
		return NULL;

	if (m_hIconList.empty())
		return NULL;

	if ((INT_PTR)m_hIconList.size() > nPos)
		return NULL;

	return m_hIconList[nPos];
}

CHERRY_RET CCherryNotificationIcon::SetIcon(HICON hIcon)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		m_notifyIconData.uFlags = NIF_ICON;

		if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0))
			m_notifyIconData.uFlags |= NIF_GUID;

		m_notifyIconData.hIcon = hIcon;

		if (!Shell_NotifyIcon(NIM_MODIFY, &m_notifyIconData))
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::SetIcon(LPCTSTR lpszIconPath)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!PathFileExists(lpszIconPath))
			throw CCherryException::ERROR_NOTIFICATIONICON_FILE_NOT_FOUND;

		HICON hIcon = (HICON)LoadImage(AfxGetResourceHandle(), lpszIconPath, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);

		if (!hIcon)
			throw CCherryException::ERROR_NOTIFICATIONICON_INVALID_HANDLE;

		DWORD dwRet = SetIcon(hIcon);
		DestroyIcon(hIcon);
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::SetIcon(UINT nID)
{
	return SetIcon(MAKEINTRESOURCE(nID));
}

CHERRY_RET CCherryNotificationIcon::SetIconFromList(UINT nPos)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_hIconList.empty())
			throw CCherryException::ERROR_NOTIFICATIONICON_ICON_LIST_EMPTY;

		if (nPos > (UINT)m_hIconList.size())
			throw CCherryException::ERROR_NOTIFICATIONICON_ICON_LIST_OUT_OF_BOUND;

		cherryRet = SetIcon(m_hIconList[nPos]);
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::RemoveIcon()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled/* || !m_bAdded*/)
			throw cherryRet;

		if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0))
			m_notifyIconData.uFlags = NIF_GUID;

		m_bAdded = m_bVisible = !Shell_NotifyIcon(NIM_DELETE, &m_notifyIconData);
		m_notifyIconData.uFlags = 0;

		if (!m_bAdded)
			m_nAddedID = -1;
		else
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::ShowIcon()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bVisible)
			throw cherryRet;

		if (!m_bAdded)
			return AddIcon();

		if (m_bWinXPOrLater)
		{
			m_notifyIconData.uFlags = NIF_STATE;
			m_notifyIconData.dwState = 0;
			m_notifyIconData.dwStateMask = NIS_HIDDEN;

			m_bVisible = Shell_NotifyIcon(NIM_MODIFY, &m_notifyIconData);
		}
		else
		{
			return AddIcon();
		}

		if (!m_bVisible)
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::HideIcon()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bVisible || !m_bAdded)
			throw cherryRet;

		if (!m_bWinXPOrLater)
			return RemoveIcon();

		m_notifyIconData.uFlags = NIF_STATE;
		m_notifyIconData.dwState = NIS_HIDDEN;
		m_notifyIconData.dwStateMask = NIS_HIDDEN;

		m_bVisible = !Shell_NotifyIcon(NIM_MODIFY, &m_notifyIconData);

		if (!m_bVisible)
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

BOOL CCherryNotificationIcon::IsEnabled() const
{
	return m_bEnabled;
}

BOOL CCherryNotificationIcon::IsVisible() const
{
	if (m_bWinXPOrLater)
		return m_bVisible;

	return m_bAdded;
}

CHERRY_RET CCherryNotificationIcon::SetFocus()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		if (!Shell_NotifyIcon(NIM_SETFOCUS, &m_notifyIconData))
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::StartAnimation(UINT nElapse)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (m_hIconList.empty())
			throw CCherryException::ERROR_NOTIFICATIONICON_ICON_LIST_EMPTY;

		if ((m_nTimerID = SetTimer(ID_TIMER_NOTIFICATION_ICON_ANIMATION, nElapse, NULL)) == 0)
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::StepAnimation()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (m_hIconList.empty())
			throw CCherryException::ERROR_NOTIFICATIONICON_ICON_LIST_OUT_OF_BOUND;

		if (m_nCount >= (UINT)m_hIconList.size())
			m_nCount = 0;

		cherryRet = SetIcon(m_hIconList[m_nCount++]);
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::PauseAnimation()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (m_nTimerID != 0)
		{
			if (!KillTimer(ID_TIMER_NOTIFICATION_ICON_ANIMATION))
				throw CCherryException::ERROR_CHERRY_FAILURE;
		}
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::StopAnimation()
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;
	
	try
	{
		if (m_nTimerID != 0)
		{
			if (!KillTimer(0))
				cherryRet = CCherryException::ERROR_CHERRY_FAILURE;
		}

		m_nCount = 0;

		if (m_hIcon)
			SetIcon(m_hIcon);
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

CHERRY_RET CCherryNotificationIcon::SetIconList(UINT nFirstIconID, UINT nLastIconID)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		if (nFirstIconID > nLastIconID)
			throw CCherryException::ERROR_NOTIFICATIONICON_INVALID_RANGE;

		const CWinApp *pApp = AfxGetApp();

		if (!pApp)
			throw CCherryException::ERROR_CHERRY_FAILURE;

		m_hIconList.clear();

		for (UINT i = nFirstIconID; i <= nLastIconID; i++)
			m_hIconList.push_back(pApp->LoadIcon(i));
	}
	catch (CMemoryException *e)
	{
		e->ReportError();
		e->Delete();	// ����� ����
		
		m_hIconList.clear();

		cherryRet = CCherryException::ERROR_NOTIFICATIONICON_MEMORY_EXCEPTION;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

void CCherryNotificationIcon::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == ID_TIMER_NOTIFICATION_ICON_ANIMATION)
		StepAnimation();

	CWnd::OnTimer(nIDEvent);
}

CString CCherryNotificationIcon::GetToolTipText() const
{
// 	if (!m_bEnabled)
// 		return _T("");

	return static_cast<CString>(m_notifyIconData.szTip);
}

CHERRY_RET CCherryNotificationIcon::SetToolTipText(LPCTSTR lpszToolTip)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		m_notifyIconData.uFlags = NIF_TIP;
		_tcsncpy_s(m_notifyIconData.szTip, lpszToolTip, sizeof(m_notifyIconData.szTip));

		if (!m_bAdded)
			throw cherryRet;

		if (!Shell_NotifyIcon(NIM_MODIFY, &m_notifyIconData))
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

UINT CCherryNotificationIcon::GetCallbackMessage() const
{
	if (!m_bEnabled)
		return 0;

	return m_notifyIconData.uCallbackMessage;
}

DWORD CCherryNotificationIcon::SetCallbackMessage(UINT nCallbackMessage)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		m_notifyIconData.uFlags = NIF_MESSAGE;
		m_notifyIconData.uCallbackMessage = nCallbackMessage;

		if (!m_bAdded)
			throw cherryRet;

		if (!Shell_NotifyIcon(NIM_MODIFY, &m_notifyIconData))
			throw CCherryException::ERROR_CHERRY_FAILURE;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief		Ʈ���� ������ ���콺 �޽��� �ڵ鸵
/// \author		ogoons
/// \date		2013-09-03
/// \param		
/// \return		
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

LRESULT CCherryNotificationIcon::OnNotificationIcon(WPARAM wParam, LPARAM lParam)
{
	if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0))
	{
		UINT nID = (UINT)HIWORD(lParam);

		if ((UINT)HIWORD(lParam) != m_notifyIconData.uID)
			return 0L;	
	}
	else
	{
		if ((UINT)wParam != m_notifyIconData.uID)
			return 0L;
	}

	CMenu menu, *pSubMenu;
	
	switch (LOWORD(lParam))
	{
	// ����Ʈ�� �����Ǿ��� �޴��� �����Ѵ�.
	case WM_LBUTTONDBLCLK:
		{
			m_pParentWnd->SetForegroundWindow();  

			UINT nItem;

			if (m_nContextMenuDefaultItem)
			{
				if (!menu.LoadMenu(m_nContextMenuID))
					return 0L;

				if (!(pSubMenu = menu.GetSubMenu(0)))
					return 0L;

				nItem = pSubMenu->GetMenuItemID(m_nContextMenuDefaultItem);

				menu.DestroyMenu();
			}
			else
			{
				nItem = m_nContextMenuDefaultItem;
			}

			m_pParentWnd->PostMessage(WM_COMMAND, nItem, 0);
		}
		break;
	case WM_CONTEXTMENU:
		{
			if (!menu.LoadMenu(m_nContextMenuID))
				return 0L;

			if (!(pSubMenu = menu.GetSubMenu(0)))
				return 0L;

			pSubMenu->SetDefaultItem(m_nContextMenuDefaultItem, m_bContextMenuDefaultByPos);
			
			int x = (int)LOWORD(wParam);
			int y = (int)HIWORD(wParam);

			m_pParentWnd->SetForegroundWindow();
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, x , y, m_pParentWnd);	
			m_pParentWnd->PostMessage(WM_NULL, 0, 0);

			menu.DestroyMenu();
		}
		break;
#if (_WIN32_IE >= 0x0501)
	case NIN_BALLOONSHOW:		// Ȯ�� ǳ�������� ��µ� ��
		break;
	case NIN_BALLOONHIDE:		// Ȯ�� ǳ�������� ���� ��
		break;
	case NIN_BALLOONTIMEOUT:	// Ȯ�� ǳ�������� �ð��ʰ��� ���� ��
		break;
	case NIN_BALLOONUSERCLICK:	// Ȯ�� ǳ�������� Ŭ������ ��
		break;
#endif
#if (NTDDI_VERSION >= NTDDI_VISTA)
	case NIN_POPUPOPEN:			// ǥ�� ǳ�������� ��µ� ��
		break;
	case NIN_POPUPCLOSE:		// ǥ�� ǳ�������� ���� ��
		break;
#endif
	}

	return 0L;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief		Taskbar ������ ȣ���
/// \author		ogoons
/// \date		2013-09-03
/// \param		
/// \return		
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

LRESULT CCherryNotificationIcon::OnTaskbarCreated(WPARAM wParam, LPARAM lParam)
{
	AddIcon();

	return 0L;
}

LRESULT CCherryNotificationIcon::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == m_notifyIconData.uCallbackMessage)
		return OnNotificationIcon(wParam, lParam);

	return CWnd::WindowProc(message, wParam, lParam);
}

CHERRY_RET CCherryNotificationIcon::SetContextMenu(UINT nContextMenuID)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		m_nContextMenuID = nContextMenuID;

	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

void CCherryNotificationIcon::GetContextMenuDefaultItem(UINT &nItem, BOOL &bByPos)
{
	nItem = m_nContextMenuDefaultItem;
	bByPos = m_bContextMenuDefaultByPos;
}

CHERRY_RET CCherryNotificationIcon::SetContextMenuDefaultItem(UINT nItem, BOOL bByPos)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (m_nContextMenuDefaultItem == nItem && m_bContextMenuDefaultByPos == bByPos)
			throw cherryRet;

		m_nContextMenuDefaultItem = nItem;
		m_bContextMenuDefaultByPos = bByPos;

		CMenu menu, *pSubMenu;

		if (!menu.LoadMenu(m_nContextMenuID))
			throw CCherryException::ERROR_NOTIFICATIONICON_LOAD_MENU_FAIL;

		if (!(pSubMenu = menu.GetSubMenu(0)))
			throw CCherryException::ERROR_NOTIFICATIONICON_LOAD_MENU_FAIL;

		if (!SetMenuDefaultItem(pSubMenu->m_hMenu, nItem, bByPos))
			throw CCherryException::ERROR_CHERRY_FAILURE;

		menu.DestroyMenu();
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief		OS ������ ���õǴ� ǳ������ ȣ�� �Լ�
/// \author		ogoons
/// \date		2013-09-25
/// \param		nTimeout: WinXP ~ WinVista
///				hBalloonIcon: WinVista
/// \return		
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

CHERRY_RET CCherryNotificationIcon::ShowBalloon(LPCTSTR lpszText, LPCTSTR lpszTitle, DWORD dwIcon, UINT nTimeout, HICON hBalloonIcon)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		if (!m_bEnabled)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_CREATED;

		if (!m_bAdded)
			throw CCherryException::ERROR_NOTIFICATIONICON_NOT_ADDED;

		if (!m_bWinXPOrLater)
			throw CCherryException::ERROR_NOTIFICATIONICON_WIN2K_AND_LATER_AVAILABLE;

		// OS ���� �� �ɼ� ����ó�� (MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/bb773352(v=vs.85).aspx)
		if (dwIcon & NIIF_USER)
		{
			// Win XP SP2���� ���� �����̸�
			if (false == IsWindowsXPSP2OrGreater())
				throw CCherryException::ERROR_NOTIFICATIONICON_BALLOON_OPTION_DO_NOT_SUPPORTED_OS;
		}

		if (dwIcon & NIIF_NOSOUND)
		{
			// Win XP ���� ���� �����̸�
			if (false == IsWindowsXPOrGreater())
				throw CCherryException::ERROR_NOTIFICATIONICON_BALLOON_OPTION_DO_NOT_SUPPORTED_OS;
		}

		if (dwIcon & NIIF_LARGE_ICON)
		{
			// Win Vista ���� ���� �����̸�
			if (false == IsWindowsVistaOrGreater())
				throw CCherryException::ERROR_NOTIFICATIONICON_BALLOON_OPTION_DO_NOT_SUPPORTED_OS;
		}

		if (dwIcon & NIIF_RESPECT_QUIET_TIME)
		{
			// Win 7 ���� ���� �����̸�
			if (false == IsWindows7OrGreater())
				throw CCherryException::ERROR_NOTIFICATIONICON_BALLOON_OPTION_DO_NOT_SUPPORTED_OS;
		}

		m_notifyIconData.uFlags = NIF_INFO;

		if (true == IsWindows7OrGreater())
			m_notifyIconData.uFlags |= NIF_GUID;

		_tcsncpy_s(m_notifyIconData.szInfo, lpszText, _countof(m_notifyIconData.szInfo));

		if (lpszTitle)
			_tcsncpy_s(m_notifyIconData.szInfoTitle, lpszTitle, _countof(m_notifyIconData.szInfoTitle));
		else
			m_notifyIconData.szInfoTitle[0] = _T('\0');

		m_notifyIconData.dwInfoFlags = dwIcon;

		if (true == IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN2K), LOBYTE(_WIN32_WINNT_WIN2K), 0))
			m_notifyIconData.uTimeout = nTimeout;	// Win2k �̻󿡼� ��� ����

		if (true == IsWindowsVistaOrGreater())
			m_notifyIconData.hBalloonIcon;	// Vista �̻󿡼��� hBalloonIcon ����� ������ ���

		if (FALSE == Shell_NotifyIcon(NIM_MODIFY, &m_notifyIconData))
			cherryRet = CCherryException::ERROR_CHERRY_FAILURE;

		m_notifyIconData.szInfo[0] = _T('\0');
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

///////////////////////////////////////////////////////////////////////////
///
/// \brief		OS ������ ���þ��� ��� ������ ǳ������ ȣ�� �Լ�
/// \author		ogoons
/// \date		2013-10-16
/// \param		
/// \return		
/// \remark		
/// \section	
///
///////////////////////////////////////////////////////////////////////////

CHERRY_RET CCherryNotificationIcon::ShowBalloon(LPCTSTR lpszText, LPCTSTR lpszTitle, DWORD dwIcon)
{
	return ShowBalloon(lpszText, lpszTitle, dwIcon, 0, NULL);
}

NOTIFYICONDATA *CCherryNotificationIcon::GetNotifyIconData()
{
	return &m_notifyIconData;
}

// CCherryNotificationIconFlyout

IMPLEMENT_DYNAMIC(CCherryNotificationIconFlyout, CCherryDialog)

	CCherryNotificationIconFlyout::CCherryNotificationIconFlyout()
{
}

CCherryNotificationIconFlyout::CCherryNotificationIconFlyout(UINT nIDTemplate, CWnd *pParent)
	: CCherryDialog(nIDTemplate, pParent)
{
}

CCherryNotificationIconFlyout::~CCherryNotificationIconFlyout()
{
}

// CCherryNotificationIconFlyout �޽��� ó�����Դϴ�.
BEGIN_MESSAGE_MAP(CCherryNotificationIconFlyout, CCherryDialog)
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

CHERRY_RET CCherryNotificationIconFlyout::Create(CCherryNotificationIcon *pNotificationIcon, UINT nWidth, UINT nHeight)
{
	CHERRY_RET cherryRet = CCherryException::ERROR_CHERRY_SUCCESS;

	try
	{
		CRect flyoutRect = GetAnchorRect(pNotificationIcon, nWidth, nHeight);

		const DWORD dwStyle = WS_POPUP | WS_THICKFRAME | WS_VISIBLE;

		// adjust the window size to take the frame into account
		AdjustWindowRectEx(&flyoutRect, dwStyle, FALSE, WS_EX_TOOLWINDOW);

		if (!CCherryDialog::CreateEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, AfxRegisterWndClass(0), NULL, dwStyle, flyoutRect, this, 0))
			throw CCherryException::ERROR_NOTIFICATIONICON_FLYOUT_CREATE_FAIL;
	}
	catch (const CHERRY_RET &errorRet)
	{
		cherryRet = errorRet;
	}

	return cherryRet;
}

BOOL CCherryNotificationIconFlyout::OnInitDialog()
{
	CCherryDialog::OnInitDialog();

	return TRUE;
}

BOOL CCherryNotificationIconFlyout::OnCreateCherry()
{
	return TRUE;
}

void CCherryNotificationIconFlyout::OnDrawCherry(CCherryMemDC *pDC)
{
}

LRESULT CCherryNotificationIconFlyout::OnNcHitTest(CPoint point)
{
	// ������ ������ ������ ���´�.
	return 0L;
}

CRect CCherryNotificationIconFlyout::GetAnchorRect(NOTIFYICONDATA *pNotifyIconData, UINT nWidth, UINT nHeight)
{
	CRect windowRect;

	NOTIFYICONIDENTIFIER notifyIconIdentifier;
	notifyIconIdentifier.cbSize		= sizeof(NOTIFYICONIDENTIFIER);
	notifyIconIdentifier.hWnd		= pNotifyIconData->hWnd;
	notifyIconIdentifier.uID		= pNotifyIconData->uID;
	notifyIconIdentifier.guidItem	= pNotifyIconData->guidItem;

	CRect iconRect;
	HRESULT hRet = Shell_NotifyIconGetRect(&notifyIconIdentifier, &iconRect);

	if (SUCCEEDED(hRet))
	{
		// display the flyout in an appropriate position close to the printer icon
		CPoint anchorPoint((iconRect.left + iconRect.right) / 2, (iconRect.top + iconRect.bottom) / 2);
		CSize windowSize(nWidth, nHeight);

		if (CalculatePopupWindowPosition(&anchorPoint, &windowSize, TPM_VERTICAL | TPM_VCENTERALIGN | TPM_CENTERALIGN | TPM_WORKAREA, &iconRect, &windowRect))
		{
			int nShadowWidth = 0, nShadowHeight = 0;

			// �׸��� ���� �����ϱ� ���� Taskbar ��ġ �˾ƿ���
			APPBARDATA appBarData;
			appBarData.cbSize = sizeof(APPBARDATA);
			SHAppBarMessage(ABM_GETTASKBARPOS, &appBarData);

			const int nWindowCenterX = windowRect.CenterPoint().x;
			const int nWindowCenterY = windowRect.CenterPoint().y;
			const int nShadowSize = 16;

			switch (appBarData.uEdge)
			{
			case ABE_LEFT:
				if (nWindowCenterY != anchorPoint.y)
					nShadowHeight = -nShadowSize;

				nShadowWidth = nShadowSize;
				break;
			case ABE_TOP:
				if (nWindowCenterX != anchorPoint.x)
					nShadowWidth = -nShadowSize;

				nShadowHeight = nShadowSize;
				break;
			case ABE_RIGHT:
				if (nWindowCenterY != anchorPoint.y)
					nShadowHeight = -nShadowSize;

				nShadowWidth = -nShadowSize;
				break;
			case ABE_BOTTOM:
				if (nWindowCenterX != anchorPoint.x)
					nShadowWidth = -nShadowSize;

				nShadowHeight = -nShadowSize;
				break;
			}

			windowRect.left += nShadowWidth;
			windowRect.top += nShadowHeight;
			windowRect.right += nShadowWidth;
			windowRect.bottom += nShadowHeight;
		}
	}

	return windowRect;
}

CRect CCherryNotificationIconFlyout::GetAnchorRect(CCherryNotificationIcon *pNotificationIcon, UINT nWidth, UINT nHeight)
{
	return GetAnchorRect(pNotificationIcon->GetNotifyIconData(), nWidth, nHeight);
}

void CCherryNotificationIconFlyout::OnKillFocus(CWnd* pNewWnd)
{
	CCherryDialog::OnKillFocus(pNewWnd);

	CWnd *pChildWnd = GetWindow(GW_CHILD);

	while (NULL != pChildWnd)
	{
		if (pChildWnd == pNewWnd)
			return;

		pChildWnd = pChildWnd->GetNextWindow(GW_HWNDNEXT);
	}

	DestroyWindow();
}

void CCherryNotificationIconFlyout::PostNcDestroy()
{
	delete this;

	CCherryDialog::PostNcDestroy();
}
